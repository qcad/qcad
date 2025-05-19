//
// Copyright (c) 1993-2022 Robert McNeel & Associates. All rights reved.
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

#pragma region DimStyleContext

ON_DimStyleContext::~ON_DimStyleContext()
{};

const ON_DimStyle& ON_DimStyleContext::CurrentDimStyle() const
{
  const ON::LengthUnitSystem model_unit_system = ModelUnitSystem();

  if (ON::IsUnitedStatesCustomaryLengthUnit(model_unit_system))
  {
    if ( ON::LengthUnitSystem::Feet == model_unit_system )
      return ON_DimStyle::DefaultFootInchArchitecture;
    return ON_DimStyle::DefaultInchDecimal;
  }

  if (ON::UnitScale(model_unit_system, ON::LengthUnitSystem::Meters) >= 1.0)
    return ON_DimStyle::DefaultMillimeterLarge;

  return ON_DimStyle::DefaultMillimeterSmall;
}

const ON_DimStyle* ON_DimStyleContext::DimStyleFromId(
  ON_UUID id,
  const ON_DimStyle* not_found_result
) const
{
  const ON_DimStyle& system_dim_style = ON_DimStyle::SystemDimstyleFromId(id);
  if (&ON_DimStyle::Unset != &system_dim_style)
    return &system_dim_style;
  return not_found_result;
}

const ON_DimStyle* ON_DimStyleContext::DimStyleFromName(
  const ON_NameHash& name_hash,
  const ON_DimStyle* not_found_result
) const
{
  const ON_DimStyle& system_dim_style = ON_DimStyle::SystemDimstyleFromName(name_hash);
  if (&ON_DimStyle::Unset != &system_dim_style)
    return &system_dim_style;
  return not_found_result;
}

const ON_DimStyle* ON_DimStyleContext::DimStyleFromContentHash(
  const ON_SHA1_Hash& content_hash,
  const ON_DimStyle* not_found_result
) const
{
  const ON_DimStyle& system_dim_style = ON_DimStyle::SystemDimstyleFromContentHash(content_hash);
  if (&ON_DimStyle::Unset != &system_dim_style)
    return &system_dim_style;
  return not_found_result;
}

const ON_DimStyle* ON_DimStyleContext::DimStyleFromFont(
  const ON_Font& font,
  double model_space_text_scale,
  double text_height,
  ON::LengthUnitSystem text_height_unit_system,
  bool bReturnClosestMatch,
  const ON_DimStyle* not_found_result
) const
{
  const ON_DimStyle& current_dimstyle = CurrentDimStyle();
  if (
    &ON_DimStyle::Unset != &current_dimstyle
    && current_dimstyle.Font().ManagedFontSerialNumber() == font.ManagedFontSerialNumber()
    )
  {
    return &current_dimstyle;
  }
  return not_found_result;
}

ON::LengthUnitSystem ON_DimStyleContext::ModelUnitSystem() const
{
  return m_unit_system;
}

ON__UINT64 ON_DimStyleContext::ModelSerialNumber() const
{
  return m_model_serial_number;
}

bool ON_DimStyleContext::AddDimStyle(
  const ON_DimStyle& dim_style,
  bool bResolveNameAndIdConflicts
)
{
  return false;
}

bool ON_DimStyleContext::ModifyDimStyle(
  ON_UUID model_dim_style_id,
  const ON_DimStyle& dim_style
)
{
  return false;
}

const ON_DimStyle* ON_DimStyleContext::FirstDimStyle(
  bool bIncludeSystemDimStyles,
  bool bIncludeDeletedDimStyles
) const
{
  return nullptr;
}


const ON_DimStyle* ON_DimStyleContext::NextDimStyle(
  ON_UUID id,
  bool bIncludeSystemDimStyles,
  bool bIncludeDeletedDimStyles
) const
{
  return nullptr;
}

const ON_DimStyle* ON_DimStyleContext::PrevDimStyle(
  ON_UUID id,
  bool bIncludeSystemDimStyles,
  bool bIncludeDeletedDimStyles
) const
{
  return nullptr;
}


#pragma endregion DimStyleContext


#pragma region Arrowheads

bool ON_Arrowhead::operator!=(const ON_Arrowhead& other) const
{
  return !operator==(other);
}

bool ON_Arrowhead::operator==(const ON_Arrowhead& other) const
{
  if (m_arrowhead_type == other.m_arrowhead_type)
  {
    if (m_arrowhead_type == arrow_type::UserBlock)
      return (m_arrow_block_id == other.m_arrow_block_id);
    else
      return true;
  }
  else
    return false;
}

ON_Arrowhead::arrow_type ON_Arrowhead::ArrowTypeFromUnsigned(
  unsigned int type_as_unsigned
  )
{
  switch (type_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Arrowhead::arrow_type::None);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Arrowhead::arrow_type::UserBlock);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Arrowhead::arrow_type::SolidTriangle);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Arrowhead::arrow_type::Dot);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Arrowhead::arrow_type::Tick);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Arrowhead::arrow_type::ShortTriangle);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Arrowhead::arrow_type::OpenArrow);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Arrowhead::arrow_type::Rectangle);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Arrowhead::arrow_type::LongTriangle);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_Arrowhead::arrow_type::LongerTriangle);
  }
  ON_ERROR("Invalid type_as_unsigned parameter.");
  return (ON_Arrowhead::arrow_type::None);
}

ON_DimStyle::LengthDisplay ON_DimStyle::LengthDisplayFromUnsigned(
  unsigned int length_display_as_unsigned
)
{
  switch (length_display_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::LengthDisplay::ModelUnits);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::LengthDisplay::Millmeters);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::LengthDisplay::Centimeters);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::LengthDisplay::Meters);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::LengthDisplay::Kilometers);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::LengthDisplay::InchesDecimal);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::LengthDisplay::InchesFractional);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::LengthDisplay::FeetDecimal);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::LengthDisplay::FeetAndInches);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::LengthDisplay::Miles);
  }
  ON_ERROR("Invalid length_display_as_unsigned parameter.");
  return (ON_DimStyle::LengthDisplay::ModelUnits);
}


bool ON_DimStyle::LengthDisplayIsDecimal(
  ON_DimStyle::LengthDisplay dimension_length_display
)
{
  return
    ON_DimStyle::LengthDisplay::InchesFractional != dimension_length_display
    && ON_DimStyle::LengthDisplay::FeetAndInches != dimension_length_display;
}

ON::LengthUnitSystem ON_DimStyle::LengthUnitSystemFromLengthDisplay(
  ON_DimStyle::LengthDisplay dimension_length_display
)
{
  switch (dimension_length_display)
  {
  case LengthDisplay::ModelUnits:
    return ON::LengthUnitSystem::None;
  case LengthDisplay::Millmeters:
    return ON::LengthUnitSystem::Millimeters;
  case LengthDisplay::Centimeters:
    return ON::LengthUnitSystem::Centimeters;
  case LengthDisplay::Meters:
    return ON::LengthUnitSystem::Meters;
  case LengthDisplay::Kilometers:
    return ON::LengthUnitSystem::Kilometers;
  case LengthDisplay::InchesDecimal:
    return ON::LengthUnitSystem::Inches;
  case LengthDisplay::InchesFractional:
    return ON::LengthUnitSystem::Inches;
  case LengthDisplay::FeetDecimal:
    return ON::LengthUnitSystem::Feet;
  case LengthDisplay::FeetAndInches:
    return ON::LengthUnitSystem::Feet;
  case LengthDisplay::Miles:
    return ON::LengthUnitSystem::Miles;
  }
  return ON::LengthUnitSystem::None;
}

ON_DimStyle::tolerance_format ON_DimStyle::ToleranceFormatFromUnsigned(
  unsigned int format_as_unsigned
  )
{
  switch (format_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::tolerance_format::None);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::tolerance_format::Symmetrical);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::tolerance_format::Deviation);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::tolerance_format::Limits);
  }
  ON_ERROR("invalid format_as_unsigned parameter.");
  return (ON_DimStyle::tolerance_format::None);
}

ON_DimStyle::ContentAngleStyle ON_DimStyle::ContentAngleStyleFromUnsigned(
  unsigned int alignment_as_unsigned
  )
{
  switch (alignment_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::ContentAngleStyle::Horizontal);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::ContentAngleStyle::Aligned);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::ContentAngleStyle::Rotated);
  }
  ON_ERROR("invalid alignment_as_unsigned parameter.");
  return (ON_DimStyle::ContentAngleStyle::Horizontal);
}

ON_DimStyle::leader_curve_type ON_DimStyle::LeaderCurveTypeFromUnsigned(
  unsigned int type_as_unsigned
  )
{
  switch (type_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::leader_curve_type::None);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::leader_curve_type::Polyline);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::leader_curve_type::Spline);
  }
  ON_ERROR("invalid type_as_unsigned parameter.");
  return (ON_DimStyle::leader_curve_type::Polyline);
}

ON_DimStyle::field ON_DimStyle::FieldFromUnsigned(
  unsigned int field_as_unsigned
  )
{
  switch (field_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::Unset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::Name);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::Index);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ExtensionLineExtension);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ExtensionLineOffset);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::Arrowsize);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::LeaderArrowsize);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::Centermark);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::TextGap);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::TextHeight);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimTextLocation);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::MaskFrameType);
    // OBSOLETE // //ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::OBSOLETE_LengthFormat_);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::LengthResolution);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::AngleFormat);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::AngleResolution);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::Font);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::LengthFactor);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::Alternate);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::AlternateLengthFactor);
    // OBSOLETE // //ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::OBSOLETE_AlternateLengthFormat_);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::AlternateLengthResolution);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::Prefix);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::Suffix);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::AlternatePrefix);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::AlternateSuffix);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimensionLineExtension);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::SuppressExtension1);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::SuppressExtension2);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ExtLineColorSource);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimLineColorSource);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ArrowColorSource);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::TextColorSource);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ExtLineColor);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimLineColor);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ArrowColor);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::TextColor);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ExtLinePlotColorSource);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimLinePlotColorSource);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ArrowPlotColorSource);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::TextPlotColorSource);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ExtLinePlotColor);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimLinePlotColor);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ArrowPlotColor);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::TextPlotColor);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ExtLinePlotWeightSource);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimLinePlotWeightSource);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ExtLinePlotWeight_mm);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimLinePlotWeight_mm);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ToleranceFormat);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ToleranceResolution);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ToleranceUpperValue);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ToleranceLowerValue);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::AltToleranceResolution);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ToleranceHeightScale);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::BaselineSpacing);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DrawMask);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::MaskColorSource);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::MaskColor);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::MaskBorder);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimensionScale);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimscaleSource);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::FixedExtensionLength);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::FixedExtensionOn);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::TextRotation);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::SuppressArrow1);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::SuppressArrow2);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::TextmoveLeader);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ArclengthSymbol);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::StackTextheightScale);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::StackFormat);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::AltRound);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::Round);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::AngularRound);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::AltZeroSuppress);
    // OBSOLETE // ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ToleranceZeroSuppress);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::AngleZeroSuppress);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ZeroSuppress);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::AltBelow);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ArrowType1);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ArrowType2);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::LeaderArrowType);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ArrowBlockId1);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ArrowBlockId2);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::LeaderArrowBlock);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimRadialTextLocation);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::TextVerticalAlignment);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::LeaderTextVerticalAlignment);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::LeaderContentAngleStyle);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::LeaderCurveType);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::LeaderContentAngle);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::LeaderHasLanding);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::LeaderLandingLength);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::MaskFlags);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::CentermarkStyle);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::TextHorizontalAlignment);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::LeaderTextHorizontalAlignment);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DrawForward);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::SignedOrdinate);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::UnitSystem);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::TextMask);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::TextOrientation);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::LeaderTextOrientation);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimTextOrientation);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimRadialTextOrientation);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimTextAngleStyle);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimRadialTextAngleStyle);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::TextUnderlined);
    // OBSOLETE // //ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::OBSOLETE_DimensionUnitSystem_);
    // OBSOLETE // //ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::OBSOLETE_AlternateDimensionUnitSystem_);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DimensionLengthDisplay);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::AlternateDimensionLengthDisplay);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ForceDimLine);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::TextFit);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::ArrowFit);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::field::DecimalSeparator);
  }
  if (field_as_unsigned > static_cast<unsigned int>(ON_DimStyle::field::AlternateDimensionLengthDisplay))
  {
    ON_ERROR("invalid field_as_unsigned parameter.");
  }
  return (ON_DimStyle::field::Unset);
}

ON_DimStyle::angle_format ON_DimStyle::AngleFormatFromUnsigned(
  unsigned int format_as_unsigned
  )
{
  switch (format_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::angle_format::DecimalDegrees);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::angle_format::DegMinSec);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::angle_format::Radians);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::angle_format::Grads);
  }
  ON_ERROR("invalid format_as_unsigned parameter.");
  return (ON_DimStyle::angle_format::DecimalDegrees);
}

ON_DimStyle::stack_format ON_DimStyle::StackFormatFromUnsigned(
  unsigned int format_as_unsigned
  )
{
  switch (format_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::stack_format::None);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::stack_format::StackHorizontal);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::stack_format::StackDiagonal);
  }
  ON_ERROR("invalid format_as_unsigned parameter.");
  return (ON_DimStyle::stack_format::None);
}


ON_DimStyle::centermark_style ON_DimStyle::CentermarkStyleFromUnsigned(
  unsigned int centermark_as_unsigned
)
{
  switch (centermark_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::centermark_style::None);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::centermark_style::Mark);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::centermark_style::MarkAndLines);
  }
  ON_ERROR("invalid centermark_as_unsigned parameter.");
  return (ON_DimStyle::centermark_style::None);
}

ON_DimStyle::OBSOLETE_length_format ON_DimStyle::OBSOLETE_LengthFormatFromUnsigned(
  unsigned int format_as_unsigned
  )
{
  switch (format_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::OBSOLETE_length_format::Decimal);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::OBSOLETE_length_format::Fractional);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::OBSOLETE_length_format::FeetInches);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::OBSOLETE_length_format::FeetDecimalInches);
  }
  ON_ERROR("invalid format_as_unsigned parameter.");
  return (ON_DimStyle::OBSOLETE_length_format::Decimal);
}

ON_DimStyle::arrow_fit ON_DimStyle::ArrowFitFromUnsigned(
  unsigned int arrow_fit_as_unsigned
)
{
  switch (arrow_fit_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::arrow_fit::Auto);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::arrow_fit::ArrowsInside);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::arrow_fit::ArrowsOutside);
  }
  ON_ERROR("invalid arrow_fit_as_unsigned parameter.");
  return (ON_DimStyle::arrow_fit::Auto);
}

ON_DimStyle::text_fit ON_DimStyle::TextFitFromUnsigned(
  unsigned int text_fit_as_unsigned
)
{
  switch (text_fit_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::text_fit::Auto);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::text_fit::TextInside);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::text_fit::TextRight);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::text_fit::TextLeft);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::text_fit::TextHintRight);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::text_fit::TextHintLeft);
  }
  ON_ERROR("invalid text_fit_as_unsigned parameter.");
  return (ON_DimStyle::text_fit::Auto);
}


ON_DimStyle::OBSOLETE_length_format ON_DimStyle::OBSOLETE_LengthFormatFromLengthDisplay(
  ON_DimStyle::LengthDisplay dimension_length_display,
  ON::LengthUnitSystem model_unit_system
)
{
  if (ON_DimStyle::LengthDisplay::FeetAndInches == dimension_length_display)
    return ON_DimStyle::OBSOLETE_length_format::FeetInches;

  if (ON_DimStyle::LengthDisplay::InchesFractional == dimension_length_display
    && ON::LengthUnitSystem::Inches == model_unit_system
    )
    return ON_DimStyle::OBSOLETE_length_format::Fractional;

  return ON_DimStyle::OBSOLETE_length_format::Decimal;
}

ON_DimStyle::OBSOLETE_length_format ON_DimStyle::OBSOLETE_LengthFormatFromLengthDisplay(
  ON_DimStyle::LengthDisplay dimension_length_display,
  unsigned int model_serial_number
)
{
  return ON_DimStyle::OBSOLETE_LengthFormatFromLengthDisplay(
    dimension_length_display,
    ON::ModelLengthUnitSystem(model_serial_number)
  );
}


ON_DimStyle::TextLocation ON_DimStyle::TextLocationFromUnsigned(
  unsigned int dim_text_location_as_unsigned
  )
{
  switch (dim_text_location_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::TextLocation::AboveDimLine);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::TextLocation::InDimLine);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::TextLocation::BelowDimLine);
  }
  ON_ERROR("invalid dim_text_location_as_unsigned parameter.");
  return (ON_DimStyle::TextLocation::AboveDimLine);
}

ON_DimStyle::suppress_zero ON_DimStyle::ZeroSuppressFromUnsigned(
  unsigned int suppress_ero_as_unsigned
)
{
  switch (suppress_ero_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::suppress_zero::None);
    break;
  ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::suppress_zero::SuppressLeading);
    break;
  ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::suppress_zero::SuppressTrailing);
    break;
  ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::suppress_zero::SuppressLeadingAndTrailing);
    break;
  ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::suppress_zero::SuppressZeroFeet);
    break;
  ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::suppress_zero::SuppressZeroInches);
    break;
  ON_ENUM_FROM_UNSIGNED_CASE(ON_DimStyle::suppress_zero::SuppressZeroFeetAndZeroInches);
    break;
  }
  ON_ERROR("invalid suppress_zero_as_unsigned parameter.");
  return ON_DimStyle::suppress_zero::None;
}

ON_DimStyle::LengthDisplay ON_DimStyle::LengthDisplayFromUnitsAndFormat(
  ON::LengthUnitSystem dimunits, 
  ON_DimStyle::OBSOLETE_length_format lengthformat)
{
  ON_DimStyle::LengthDisplay display = ON_DimStyle::LengthDisplay::ModelUnits;

  if (
    ON_DimStyle::OBSOLETE_length_format::FeetInches == lengthformat
    || ON_DimStyle::OBSOLETE_length_format::FeetDecimalInches == lengthformat
    )
  {
    display = ON_DimStyle::LengthDisplay::FeetAndInches;
  }
  else
  {
    switch (dimunits)
    {
    case ON::LengthUnitSystem::Millimeters:
      display = ON_DimStyle::LengthDisplay::Millmeters;
      break;
    case ON::LengthUnitSystem::Centimeters:
      display = ON_DimStyle::LengthDisplay::Centimeters;
      break;
    case ON::LengthUnitSystem::Meters:
      display = ON_DimStyle::LengthDisplay::Meters;
      break;
    case ON::LengthUnitSystem::Kilometers:
      display = ON_DimStyle::LengthDisplay::Kilometers;
      break;
    case ON::LengthUnitSystem::Miles:
      display = ON_DimStyle::LengthDisplay::Miles;
      break;
    case ON::LengthUnitSystem::Inches:
      if (ON_DimStyle::OBSOLETE_length_format::Fractional == lengthformat)
        display = ON_DimStyle::LengthDisplay::InchesFractional;
      else
        display = ON_DimStyle::LengthDisplay::InchesDecimal;
      break;
    case ON::LengthUnitSystem::Feet:
      display = ON_DimStyle::LengthDisplay::FeetDecimal;
      break;
    default:
      break;
    }
  }
  return display;
}

ON_DimStyle::ON_DimStyle::LengthDisplay ON_DimStyle::DimensionLengthDisplay() const
{
  return m_dimension_length_display;
}

ON_DimStyle::ON_DimStyle::LengthDisplay ON_DimStyle::AlternateDimensionLengthDisplay() const
{
  return m_alternate_dimension_length_display;
}

void ON_DimStyle::SetDimensionLengthDisplay(ON_DimStyle::ON_DimStyle::LengthDisplay length_display)
{
  if (m_dimension_length_display != length_display)
  {
    m_dimension_length_display = length_display;
    Internal_ContentChange();
    if (!ON_DimStyle::ZeroSuppressMatchesLengthDisplay(ZeroSuppress(), length_display))
      SetZeroSuppress(suppress_zero::None);
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::DimensionLengthDisplay);
}

void ON_DimStyle::SetAlternateDimensionLengthDisplay(ON_DimStyle::LengthDisplay length_display)
{
  if (m_alternate_dimension_length_display != length_display)
  {
    m_alternate_dimension_length_display = length_display;
    Internal_ContentChange();
    if (!ON_DimStyle::ZeroSuppressMatchesLengthDisplay(AlternateZeroSuppress(), length_display))
      SetAlternateZeroSuppress(suppress_zero::None);
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::AlternateDimensionLengthDisplay);
}

static ON::LengthUnitSystem Internal_DimensionLengthDisplay(
  const ON_ModelComponent& model_component,
  ON_DimStyle::LengthDisplay dim_length_display,
  unsigned int model_sn
)
{
  ON::LengthUnitSystem us = ON_DimStyle::LengthUnitSystemFromLengthDisplay(dim_length_display);
  if (ON::LengthUnitSystem::None == us)
  {
    if (ON_UNSET_UINT_INDEX == model_sn)
      model_sn = model_component.ModelSerialNumber();
    if ( model_sn > 0)
      us = ON::ModelLengthUnitSystem(model_sn);
  }
  return us;
}

ON::LengthUnitSystem ON_DimStyle::DimensionLengthDisplayUnit(
  unsigned int model_sn
) const
{
  return Internal_DimensionLengthDisplay(*this, DimensionLengthDisplay(), model_sn);
}

ON::LengthUnitSystem ON_DimStyle::AlternateDimensionLengthDisplayUnit(
  unsigned int model_sn
) const
{
  return Internal_DimensionLengthDisplay(*this, AlternateDimensionLengthDisplay(), model_sn);
}

ON_Arrowhead::arrow_type ON_Arrowhead::ArrowheadType() const
{
  return m_arrowhead_type;
}

void ON_Arrowhead::SetArrowheadType(ON_Arrowhead::arrow_type type)
{
  m_arrowhead_type = type;
}

ON_UUID ON_Arrowhead::ArrowBlockId() const
{
  return m_arrow_block_id;
}

void ON_Arrowhead::SetArrowBlockId(ON_UUID id)
{
  m_arrow_block_id = id;
}

ON_Arrowhead::arrow_type ON_Arrowhead::DefaultArrowType()
{
  return ON_Arrowhead::arrow_type::SolidTriangle;
}

ON__UINT32 ON_Arrowhead::GetPoints(arrow_type type, const double*& points)
{
  // Polygon points for built-in arrowheads
  // SolidTriangle
  static double a2[] = { 0.0, 0.0, -1.0, 0.25, -1.0, -0.25 };
  // Dot
  static double a3[] = { 0.5, 0.0, 0.483, 0.129, 0.433, 0.25, 0.353, 0.353, 0.25, 0.433, 0.129, 0.483,
    0.0, 0.5, -0.129, 0.483, -0.25, 0.433, -0.353, 0.353, -0.433, 0.25, -0.483, 0.129,
    -0.5, 0.0, -0.483, -0.129, -0.433, -0.25, -0.353, -0.353, -0.25, -0.433, -0.129, -0.483,
    0.0, -0.5, 0.129, -0.483, 0.25, -0.433, 0.353, -0.353, 0.433, -0.25, 0.483, -0.129 };
  // Tick
  static double a4[] = { -0.46, -0.54, 0.54, 0.46, 0.46, 0.54, -0.54, -0.46 };
  // ShortTriangle
  static double a5[] = { 0.0, 0.0, -0.5, 0.5, -0.5, -0.5 };
  // Arrow
  static double a6[] = { 0.0, 0.0, -0.707, 0.707, -0.777, 0.636, -0.141, 0.0, -0.777, -0.636, -0.707, -0.707 };
  // Rectangle
  static double a7[] = { 0.0, 0.0, -1.0, 0.0, -1.0, 0.2, 0.0, 0.2 };
  // LongTriangle
  static double a8[] = { 0.0, 0.0, -1.0, 0.125, -1.0, -0.125 };
  // LongerTriangle
  static double a9[] = { 0.0, 0.0, -1.0, 0.0833, -1.0, -0.0833 };

  static double* arrow_points[] = { 0, 0, a2, a3, a4, a5, a6, a7, a8, a9 };
  static unsigned int c[] = {
    0,  // NoArrow
    0,  // User
    sizeof(a2) / sizeof(a2[0]) / 2,
    sizeof(a3) / sizeof(a3[0]) / 2,
    sizeof(a4) / sizeof(a4[0]) / 2,
    sizeof(a5) / sizeof(a5[0]) / 2,
    sizeof(a6) / sizeof(a6[0]) / 2,
    sizeof(a7) / sizeof(a7[0]) / 2,
    sizeof(a8) / sizeof(a8[0]) / 2,
    sizeof(a9) / sizeof(a9[0]) / 2
  };
  ON__UINT32 pointcount = 0;
  if (arrow_type::UserBlock < type && arrow_type::LongerTriangle >= type)
  {
    pointcount = c[(int)type];
    points = arrow_points[(int)type];
  }
  return pointcount;
}

ON__UINT32 ON_Arrowhead::GetPoints(arrow_type type, ON_2dPointArray& points)
{
  const double* pts = nullptr;
  unsigned int pcount = ON_Arrowhead::GetPoints(type, pts);
  if (0 < pcount)
  {
    points.Empty();
    points.Reserve(pcount);
    points.Append(pcount, (ON_2dPoint*)pts);
  }
  return pcount;
}

bool ON_Arrowhead::GetArrowheadBoundingBox(
  ON_Arrowhead::arrow_type arrowtype,
  ON_UUID arrow_block_id,
  ON_Xform xform,
  ON_BoundingBox& bbox,
  bool grow)
{
  bool rc = false;

  if (!grow)
    bbox.Destroy();
  if (ON_Arrowhead::arrow_type::UserBlock != arrowtype && ON_Arrowhead::arrow_type::None != arrowtype)
  {
    // Draw polygon from built-in shapes
    ON_2dPointArray points2d;
    int count = ON_Arrowhead::GetPoints(arrowtype, points2d);
    if (2 < count)
    {
      ON_3dPointArray points3d(count);
      for (int i = 0; i < count; i++)
      {
        ON_3dPoint& p = points3d.AppendNew();
        p = points2d[i];
        p.Transform(xform);
        bbox.Set(p, grow);
        grow = true;
      }
      rc = true;
    }
  }
  else if (ON_Arrowhead::arrow_type::UserBlock == arrowtype)
  {
    ON_3dPoint points[4] = {
      ON_3dPoint( 0.0, -0.5, 0.0 ),
      ON_3dPoint( 1.0, -0.5, 0.0 ),
      ON_3dPoint( 1.0, 0.5, 0.0 ),
      ON_3dPoint( 0.0, 0.5, 0.0 ) };

    for (int i = 0; i < 4; i++)
    {
      points[i].Transform(xform);
      bbox.Set(points[i], grow);
      grow = true;
    }
    rc = true;
  }
  return rc;
}


#pragma endregion Arrowheads

#pragma region TextMask

const ON_SHA1_Hash& ON_TextMask::ContentHash() const
{
  if (m_content_hash.IsZeroDigest())
  {
    ON_SHA1 sha1;
    unsigned int u[3] = {
      (m_bDrawMask ? 1U : 0U),
      (unsigned int)(static_cast<unsigned char>(m_mask_type)),
      (unsigned int)(static_cast<unsigned char>(m_mask_frame))
    };
    sha1.AccumulateUnsigned32(u[0]);
    sha1.AccumulateUnsigned32(u[1]);
    sha1.AccumulateUnsigned32(u[2]);
    sha1.AccumulateUnsigned32(m_mask_color);
    sha1.AccumulateDouble(m_mask_border);
    m_content_hash = sha1.Hash();
  }
  return m_content_hash;
}

int ON_TextMask::Compare(
  const ON_TextMask& lhs,
  const ON_TextMask& rhs
  )
{
  return ON_SHA1_Hash::Compare(lhs.ContentHash(), rhs.ContentHash());
}

bool operator==(
  const ON_TextMask& lhs,
  const ON_TextMask& rhs
  )
{
  return 0 == ON_TextMask::Compare(lhs, rhs);
}

bool operator!=(
  const ON_TextMask& lhs,
  const ON_TextMask& rhs
  )
{
  return 0 != ON_TextMask::Compare(lhs, rhs);
}

bool ON_TextMask::DrawTextMask() const
{
  return m_bDrawMask;
}

void ON_TextMask::SetDrawTextMask(bool bDraw)
{
  bool b = bDraw ? true : false;
  if (m_bDrawMask != b)
  {
    m_bDrawMask = b;
    m_content_hash = ON_SHA1_Hash::ZeroDigest;
  }
}

ON_TextMask::MaskType  ON_TextMask::MaskFillType() const
{
  return m_mask_type;
}

void ON_TextMask::SetMaskFillType(ON_TextMask::MaskType  type)
{
  if (m_mask_type != type)
  {
    m_mask_type = type;
    m_content_hash = ON_SHA1_Hash::ZeroDigest;
  }
}

ON_TextMask::MaskFrame ON_TextMask::MaskFrameType() const
{
  return m_mask_frame;
}

void ON_TextMask::SetMaskFrameType(ON_TextMask::MaskFrame frame) 
{
  if (m_mask_frame != frame)
  {
    m_mask_frame = frame;
    m_content_hash = ON_SHA1_Hash::ZeroDigest;
  }
}

ON_Color ON_TextMask::MaskColor() const
{
  return m_mask_color;
}

void ON_TextMask::SetMaskColor(ON_Color color)
{
  if (color != ON_Color::UnsetColor && m_mask_color != color)
  {
    m_mask_color = color;
    m_content_hash = ON_SHA1_Hash::ZeroDigest;
  }
}

double ON_TextMask::MaskBorder() const
{
  return m_mask_border;
}

void ON_TextMask::SetMaskBorder(double border)
{
  if (border >= 0.0 && m_mask_border != border)
  {
    m_mask_border = border;
    m_content_hash = ON_SHA1_Hash::ZeroDigest;
  }
}

ON_TextMask::MaskType ON_TextMask::MaskTypeFromUnsigned(
  unsigned int mask_type_as_unsigned
)
{
  switch (mask_type_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_TextMask::MaskType::BackgroundColor);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_TextMask::MaskType::MaskColor);
  }
  ON_ERROR("mask_type_as_unsigned parameter is not valid");
  return ON_TextMask::MaskType::BackgroundColor;
}

ON_TextMask::MaskFrame ON_TextMask::MaskFrameFromUnsigned(
  unsigned int mask_frame_as_unsigned
)
{
  switch (mask_frame_as_unsigned)
  {
    ON_ENUM_FROM_UNSIGNED_CASE(ON_TextMask::MaskFrame::NoFrame);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_TextMask::MaskFrame::RectFrame);
    ON_ENUM_FROM_UNSIGNED_CASE(ON_TextMask::MaskFrame::CapsuleFrame);
  }
  ON_ERROR("mask_type_as_unsigned parameter is not valid");
  return ON_TextMask::MaskFrame::NoFrame;
}


bool ON_TextMask::Write(
  ON_BinaryArchive& archive
) const
{
  const int chunk_version = 1;  // Oct. 9, 2019 - mask_frame
  if (!archive.BeginWrite3dmAnonymousChunk(chunk_version))
    return false;

  bool rc = false;

  for (;;)
  {
    if (!archive.WriteBool(m_bDrawMask))
      break;
    const unsigned int mask_type_as_unsigned = (unsigned int)(static_cast<unsigned char>(m_mask_type));
    if (!archive.WriteInt(mask_type_as_unsigned))
      break;
    if (!archive.WriteColor(m_mask_color))
      break;
    if (!archive.WriteDouble(m_mask_border))
      break;
    // DO NOT write m_content_hash
    // END of chunk_version = 0 information

    const unsigned int mask_frame_as_unsigned = (unsigned int)(static_cast<unsigned char>(m_mask_frame));
    if (!archive.WriteInt(mask_frame_as_unsigned))
      break;
    // END of chunk_version = 1 information

    rc = true;
    break;
  }

  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}


bool ON_TextMask::Read(
  ON_BinaryArchive& archive
) 
{
  *this = ON_TextMask::None;
  int chunk_version = 0;
  if (!archive.BeginRead3dmAnonymousChunk(&chunk_version))
    return false;

  bool rc = false;

  for (;;)
  {
    if (!archive.ReadBool(&m_bDrawMask))
      break;
    unsigned int mask_type_as_unsigned = (unsigned int)(static_cast<unsigned char>(m_mask_type));
    if (!archive.ReadInt(&mask_type_as_unsigned))
      break;
    m_mask_type = ON_TextMask::MaskTypeFromUnsigned(mask_type_as_unsigned);
    if (!archive.ReadColor(m_mask_color))
      break;
    if (!archive.ReadDouble(&m_mask_border))
      break;
    // END of chunk_version = 0 information

    if (chunk_version > 0)
    {
      unsigned int mask_frame_as_unsigned = (unsigned int)(static_cast<unsigned char>(m_mask_frame));
      if (!archive.ReadInt(&mask_frame_as_unsigned))
        break;
      m_mask_frame = ON_TextMask::MaskFrameFromUnsigned(mask_frame_as_unsigned);
    }

    rc = true;
    break;
  }

  if (!archive.EndRead3dmChunk())
    rc = false;
  return rc;
}

#pragma endregion TextMask



ON_OBJECT_IMPLEMENT(ON_DimStyle, ON_ModelComponent, "67AA51A5-791D-4BEC-8AED-D23B462B6F87");

const ON_DimStyle* ON_DimStyle::FromModelComponentRef(
  const class ON_ModelComponentReference& model_component_reference,
  const ON_DimStyle* none_return_value
  )
{
  const ON_DimStyle* p = ON_DimStyle::Cast(model_component_reference.ModelComponent());
  return (nullptr != p) ? p : none_return_value;
}

#pragma region Legacy dimstyle conversions
// convert ON_DimStyle::OBSOLETE_length_format enum to ON::OBSOLETE_DistanceDisplayMode enum
ON::OBSOLETE_DistanceDisplayMode ON_DimStyle::DistanceDisplayModeFromLengthFormat(
  ON_DimStyle::OBSOLETE_length_format lf
  )
{
  ON::OBSOLETE_DistanceDisplayMode ddm;
  switch (lf)
  {
  case ON_DimStyle::OBSOLETE_length_format::Decimal:
    ddm = ON::OBSOLETE_DistanceDisplayMode::Decimal;
    break;
  case ON_DimStyle::OBSOLETE_length_format::Fractional:
    ddm = ON::OBSOLETE_DistanceDisplayMode::Fractional;
    break;
  case ON_DimStyle::OBSOLETE_length_format::FeetInches:
    ddm = ON::OBSOLETE_DistanceDisplayMode::FeetInches;
    break;
  default:
    ddm = ON::OBSOLETE_DistanceDisplayMode::Decimal;
    break;
  }
  return ddm;
}

ON_DimStyle::OBSOLETE_length_format ON_DimStyle::LengthFormatFromDistanceDisplayMode(
  ON::OBSOLETE_DistanceDisplayMode ddm
  )
{
  ON_DimStyle::OBSOLETE_length_format lf;
  switch (ddm)
  {
  case ON::OBSOLETE_DistanceDisplayMode::Decimal:
    lf = ON_DimStyle::OBSOLETE_length_format::Decimal;
    break;
  case ON::OBSOLETE_DistanceDisplayMode::Fractional:
    lf = ON_DimStyle::OBSOLETE_length_format::Fractional;
    break;
  case ON::OBSOLETE_DistanceDisplayMode::FeetInches:
    lf = ON_DimStyle::OBSOLETE_length_format::FeetInches;
    break;
  default:
    lf = ON_DimStyle::OBSOLETE_length_format::Decimal;
    break;
  }
  return lf;
}


int ON_DimStyle::V5ArrowType(ON_Arrowhead::arrow_type v6type)
{
  int v5type;
  switch (v6type)
  {
  default:
  case ON_Arrowhead::arrow_type::SolidTriangle:
  case ON_Arrowhead::arrow_type::UserBlock:
    v5type = ON_V5x_DimStyle::eArrowType::solidtriangle;
    break;
  case ON_Arrowhead::arrow_type::Dot:
    v5type = ON_V5x_DimStyle::eArrowType::dot;
    break;
  case ON_Arrowhead::arrow_type::Tick:
    v5type = ON_V5x_DimStyle::eArrowType::tick;
    break;
  case ON_Arrowhead::arrow_type::ShortTriangle:
    v5type = ON_V5x_DimStyle::eArrowType::shorttriangle;
    break;
  case ON_Arrowhead::arrow_type::OpenArrow:
    v5type = ON_V5x_DimStyle::eArrowType::arrow;
    break;
  case ON_Arrowhead::arrow_type::Rectangle:
    v5type = ON_V5x_DimStyle::eArrowType::rectangle;
    break;
  case ON_Arrowhead::arrow_type::LongTriangle:
    v5type = ON_V5x_DimStyle::eArrowType::longtriangle;
    break;
  case ON_Arrowhead::arrow_type::LongerTriangle:
    v5type = ON_V5x_DimStyle::eArrowType::longertriangle;
    break;
  }

  return v5type;
}

int ON_DimStyle::V5LengthFormat(ON_DimStyle::OBSOLETE_length_format v6format)
{
  int v5format = 0;
  switch (v6format)
  {
  default:
  case ON_DimStyle::OBSOLETE_length_format::Decimal:
    v5format = 0;
    break;
  case ON_DimStyle::OBSOLETE_length_format::Fractional:
    v5format = 1;
    break;
  case ON_DimStyle::OBSOLETE_length_format::FeetInches:
    v5format = 2;
    break;
  }
  return v5format;
}

int ON_DimStyle::V5AngleFormat(ON_DimStyle::angle_format v6format)
{
  int v5format = 0;
  return v5format;
}

int ON_DimStyle::V5ToleranceFormat(ON_DimStyle::tolerance_format v6format)
{
  int v5style = 0;
  switch (v6format)
  {
  default:
  case ON_DimStyle::tolerance_format::None:
    v5style = 0;
    break;
  case ON_DimStyle::tolerance_format::Symmetrical:
    v5style = 1;
    break;
  case ON_DimStyle::tolerance_format::Deviation:
    v5style = 2;
    break;
  case ON_DimStyle::tolerance_format::Limits:
    v5style = 3;
    break;
  }
  return v5style;
}

int ON_DimStyle::V5MaskColorSourceFromV6MaskType(ON_TextMask::MaskType mask_type)
{
  return
    (mask_type == ON_TextMask::MaskType::MaskColor)
    ? 1
    : 0;
}

ON_Arrowhead::arrow_type ON_DimStyle::V6ArrowType(int v5type)
{
  ON_Arrowhead::arrow_type v6type;
  switch (v5type)
  {
  case ON_V5x_DimStyle::eArrowType::solidtriangle:
    v6type = ON_Arrowhead::arrow_type::SolidTriangle;
    break;
  case ON_V5x_DimStyle::eArrowType::dot:
    v6type = ON_Arrowhead::arrow_type::Dot;
    break;
  case ON_V5x_DimStyle::eArrowType::tick:
    v6type = ON_Arrowhead::arrow_type::Tick;
    break;
  case ON_V5x_DimStyle::eArrowType::shorttriangle:
    v6type = ON_Arrowhead::arrow_type::ShortTriangle;
    break;
  case ON_V5x_DimStyle::eArrowType::arrow:
    v6type = ON_Arrowhead::arrow_type::OpenArrow;
    break;
  case ON_V5x_DimStyle::eArrowType::rectangle:
    v6type = ON_Arrowhead::arrow_type::Rectangle;
    break;
  case ON_V5x_DimStyle::eArrowType::longtriangle:
    v6type = ON_Arrowhead::arrow_type::LongTriangle;
    break;
  case ON_V5x_DimStyle::eArrowType::longertriangle:
    v6type = ON_Arrowhead::arrow_type::LongerTriangle;
    break;
  default:
    v6type = ON_DimStyle::Default.ArrowType1();
    break;
  }
  return v6type;
}

ON_DimStyle::OBSOLETE_length_format ON_DimStyle::V6LengthFormat(int v5format)
{
  ON_DimStyle::OBSOLETE_length_format v6format = ON_DimStyle::OBSOLETE_length_format::Decimal;
  switch (v5format)
  {
  default:
  case 0:
    v6format = ON_DimStyle::OBSOLETE_length_format::Decimal;
    break;
  case 1:
    v6format = ON_DimStyle::OBSOLETE_length_format::Fractional;
    break;
  case 2:
    v6format = ON_DimStyle::OBSOLETE_length_format::FeetInches;
    break;
  }
  return v6format;
}

ON_DimStyle::angle_format ON_DimStyle::V6AngleFormat(int v5format)
{
  ON_DimStyle::angle_format v6format = ON_DimStyle::angle_format::DecimalDegrees;
  return v6format;
}

ON_DimStyle::tolerance_format ON_DimStyle::V6ToleranceFormat(int v5style)
{
  ON_DimStyle::tolerance_format  v6style = ON_DimStyle::tolerance_format::None;
  switch (v5style)
  {
  default:
  case ON_V5x_DimStyle::eToleranceStyle::tsNone:
    v6style = ON_DimStyle::tolerance_format::None;
    break;
  case ON_V5x_DimStyle::eToleranceStyle::tsSymmetrical:
    v6style = ON_DimStyle::tolerance_format::Symmetrical;
    break;
  case ON_V5x_DimStyle::eToleranceStyle::tsDeviation:
    v6style = ON_DimStyle::tolerance_format::Deviation;
    break;
  case ON_V5x_DimStyle::eToleranceStyle::tsLimits:
    v6style = ON_DimStyle::tolerance_format::Limits;
    break;
  }
  return v6style;
}

ON_TextMask::MaskType ON_DimStyle::V6MaskTypeFromV5MaskColorSource(int v5_mask_source)
{
  return
    (1 == v5_mask_source)
    ? ON_TextMask::MaskType::MaskColor
    : ON_TextMask::None.MaskFillType();
}

void ON_DimStyle::Internal_ContentChange() const
{
  IncrementContentVersionNumber();
  m_content_hash = ON_SHA1_Hash::EmptyContentHash;
}


ON_DimStyle::ON_DimStyle()
  : ON_ModelComponent(ON_ModelComponent::Type::DimStyle)
{
}

struct V5_to_V6_field_id_map 
{
  ON_V5x_DimStyle::Field m_v5_field_id;
  ON_DimStyle::field m_v6_field_id;
};

static const struct V5_to_V6_field_id_map* GetDimStyleFieldIdMap(
  size_t* field_id_map_count
)
{
  static V5_to_V6_field_id_map field_id_map[] =
  {
    {ON_V5x_DimStyle::Field::fn_name,ON_DimStyle::field::Name},
    {ON_V5x_DimStyle::Field::fn_index,ON_DimStyle::field::Index},
    {ON_V5x_DimStyle::Field::fn_extextension,ON_DimStyle::field::ExtensionLineExtension},
    {ON_V5x_DimStyle::Field::fn_extoffset,ON_DimStyle::field::ExtensionLineOffset},
    {ON_V5x_DimStyle::Field::fn_arrowsize,ON_DimStyle::field::Arrowsize},
    {ON_V5x_DimStyle::Field::fn_centermark,ON_DimStyle::field::Centermark},
    {ON_V5x_DimStyle::Field::fn_textgap,ON_DimStyle::field::TextGap},
    {ON_V5x_DimStyle::Field::fn_textheight,ON_DimStyle::field::TextHeight},
    {ON_V5x_DimStyle::Field::fn_textalign,ON_DimStyle::field::DimTextLocation},
    {ON_V5x_DimStyle::Field::fn_arrowtype,ON_DimStyle::field::ArrowType1},
    {ON_V5x_DimStyle::Field::fn_arrowtype,ON_DimStyle::field::ArrowType2},
    {ON_V5x_DimStyle::Field::fn_angularunits,ON_DimStyle::field::Unset},
    // OBSOLETE // //{ON_V5x_DimStyle::Field::fn_lengthformat,ON_DimStyle::field::OBSOLETE_LengthFormat_},
    {ON_V5x_DimStyle::Field::fn_angleformat,ON_DimStyle::field::AngleFormat},
    {ON_V5x_DimStyle::Field::fn_angleresolution,ON_DimStyle::field::AngleResolution},
    {ON_V5x_DimStyle::Field::fn_lengthresolution,ON_DimStyle::field::LengthResolution},
    {ON_V5x_DimStyle::Field::fn_fontindex,ON_DimStyle::field::Font},
    {ON_V5x_DimStyle::Field::fn_lengthfactor,ON_DimStyle::field::LengthFactor},
    {ON_V5x_DimStyle::Field::fn_bAlternate,ON_DimStyle::field::Alternate},
    {ON_V5x_DimStyle::Field::fn_alternate_lengthfactor,ON_DimStyle::field::AlternateLengthFactor},
    // OBSOLETE // //{ON_V5x_DimStyle::Field::fn_alternate_lengthformat,ON_DimStyle::field::OBSOLETE_LengthFormat_}, 
    {ON_V5x_DimStyle::Field::fn_alternate_lengthresolution,ON_DimStyle::field::AlternateLengthResolution},
    {ON_V5x_DimStyle::Field::fn_alternate_angleformat,ON_DimStyle::field::AngleFormat}, 
    {ON_V5x_DimStyle::Field::fn_alternate_angleresolution,ON_DimStyle::field::AngleResolution},
    {ON_V5x_DimStyle::Field::fn_prefix,ON_DimStyle::field::Prefix},
    {ON_V5x_DimStyle::Field::fn_suffix,ON_DimStyle::field::Suffix},
    {ON_V5x_DimStyle::Field::fn_alternate_prefix,ON_DimStyle::field::AlternatePrefix},
    {ON_V5x_DimStyle::Field::fn_alternate_suffix,ON_DimStyle::field::AlternateSuffix},
    {ON_V5x_DimStyle::Field::fn_dimextension,ON_DimStyle::field::DimensionLineExtension},
    {ON_V5x_DimStyle::Field::fn_leaderarrowsize,ON_DimStyle::field::LeaderArrowsize},
    {ON_V5x_DimStyle::Field::fn_leaderarrowtype,ON_DimStyle::field::LeaderArrowType},
    {ON_V5x_DimStyle::Field::fn_suppressextension1,ON_DimStyle::field::SuppressExtension1},
    {ON_V5x_DimStyle::Field::fn_suppressextension2,ON_DimStyle::field::SuppressExtension2},
    {ON_V5x_DimStyle::Field::fn_overall_scale,ON_DimStyle::field::Unset},
    {ON_V5x_DimStyle::Field::fn_ext_line_color_source,ON_DimStyle::field::ExtLineColorSource},
    {ON_V5x_DimStyle::Field::fn_dim_line_color_source,ON_DimStyle::field::DimLineColorSource},
    {ON_V5x_DimStyle::Field::fn_arrow_color_source,ON_DimStyle::field::ArrowColorSource},
    {ON_V5x_DimStyle::Field::fn_text_color_source,ON_DimStyle::field::TextColorSource},
    {ON_V5x_DimStyle::Field::fn_ext_line_color,ON_DimStyle::field::ExtLineColor},
    {ON_V5x_DimStyle::Field::fn_dim_line_color,ON_DimStyle::field::DimLineColor},
    {ON_V5x_DimStyle::Field::fn_arrow_color,ON_DimStyle::field::ArrowColor},
    {ON_V5x_DimStyle::Field::fn_text_color,ON_DimStyle::field::TextColor},
    {ON_V5x_DimStyle::Field::fn_ext_line_plot_color_source,ON_DimStyle::field::ExtLinePlotColorSource},
    {ON_V5x_DimStyle::Field::fn_dim_line_plot_color_source,ON_DimStyle::field::DimLineColorSource},
    {ON_V5x_DimStyle::Field::fn_arrow_plot_color_source,ON_DimStyle::field::ArrowPlotColorSource},
    {ON_V5x_DimStyle::Field::fn_text_plot_color_source,ON_DimStyle::field::TextPlotColorSource},
    {ON_V5x_DimStyle::Field::fn_ext_line_plot_color ,ON_DimStyle::field::ExtLinePlotColor},
    {ON_V5x_DimStyle::Field::fn_dim_line_plot_color,ON_DimStyle::field::DimLinePlotColor},
    {ON_V5x_DimStyle::Field::fn_arrow_plot_color,ON_DimStyle::field::ArrowPlotColor},
    {ON_V5x_DimStyle::Field::fn_text_plot_color,ON_DimStyle::field::TextPlotColor},
    {ON_V5x_DimStyle::Field::fn_ext_line_plot_weight_source,ON_DimStyle::field::ExtLinePlotWeightSource},
    {ON_V5x_DimStyle::Field::fn_dim_line_plot_weight_source,ON_DimStyle::field::DimLinePlotWeightSource},
    {ON_V5x_DimStyle::Field::fn_ext_line_plot_weight_mm,ON_DimStyle::field::ExtLinePlotWeight_mm},
    {ON_V5x_DimStyle::Field::fn_dim_line_plot_weight_mm,ON_DimStyle::field::DimLinePlotWeight_mm},
    {ON_V5x_DimStyle::Field::fn_tolerance_style,ON_DimStyle::field::ToleranceFormat},
    {ON_V5x_DimStyle::Field::fn_tolerance_resolution,ON_DimStyle::field::ToleranceResolution},
    {ON_V5x_DimStyle::Field::fn_tolerance_upper_value,ON_DimStyle::field::ToleranceUpperValue},
    {ON_V5x_DimStyle::Field::fn_tolerance_lower_value,ON_DimStyle::field::ToleranceLowerValue},
    {ON_V5x_DimStyle::Field::fn_tolerance_height_scale,ON_DimStyle::field::ToleranceHeightScale},
    {ON_V5x_DimStyle::Field::fn_baseline_spacing,ON_DimStyle::field::BaselineSpacing},
    {ON_V5x_DimStyle::Field::fn_draw_mask,ON_DimStyle::field::DrawMask},
    {ON_V5x_DimStyle::Field::fn_mask_color_source,ON_DimStyle::field::MaskColorSource},
    {ON_V5x_DimStyle::Field::fn_mask_color,ON_DimStyle::field::MaskColor},
    {ON_V5x_DimStyle::Field::fn_mask_border,ON_DimStyle::field::MaskBorder},
    {ON_V5x_DimStyle::Field::fn_dimscale,ON_DimStyle::field::DimensionScale},
    {ON_V5x_DimStyle::Field::fn_dimscale_source,ON_DimStyle::field::DimscaleSource},
    {ON_V5x_DimStyle::Field::fn_fixed_extension_len,ON_DimStyle::field::FixedExtensionLength},
    {ON_V5x_DimStyle::Field::fn_fixed_extension_on,ON_DimStyle::field::FixedExtensionOn},
    {ON_V5x_DimStyle::Field::fn_text_rotation,ON_DimStyle::field::TextRotation},
    {ON_V5x_DimStyle::Field::fn_tolerance_alt_resolution,ON_DimStyle::field::AltToleranceResolution},
    {ON_V5x_DimStyle::Field::fn_tolerance_textheight_fraction,ON_DimStyle::field::Unset},
    {ON_V5x_DimStyle::Field::fn_suppress_arrow1,ON_DimStyle::field::SuppressArrow1},
    {ON_V5x_DimStyle::Field::fn_suppress_arrow2,ON_DimStyle::field::SuppressArrow2},
    {ON_V5x_DimStyle::Field::fn_textmove_leader,ON_DimStyle::field::TextmoveLeader},
    {ON_V5x_DimStyle::Field::fn_arclength_sym,ON_DimStyle::field::ArclengthSymbol},
    {ON_V5x_DimStyle::Field::fn_stack_textheight_fraction,ON_DimStyle::field::StackTextheightScale},
    {ON_V5x_DimStyle::Field::fn_stack_format,ON_DimStyle::field::StackFormat},
    {ON_V5x_DimStyle::Field::fn_alt_round,ON_DimStyle::field::AltRound},
    {ON_V5x_DimStyle::Field::fn_round,ON_DimStyle::field::Round},
    {ON_V5x_DimStyle::Field::fn_alt_zero_suppress,ON_DimStyle::field::AltZeroSuppress},
    // OBSOLETE // {ON_V5x_DimStyle::Field::fn_tol_zero_suppress,ON_DimStyle::field::ToleranceZeroSuppress},
    {ON_V5x_DimStyle::Field::fn_ang_zero_suppress,ON_DimStyle::field::AngleZeroSuppress},
    {ON_V5x_DimStyle::Field::fn_zero_suppress,ON_DimStyle::field::ZeroSuppress},
    {ON_V5x_DimStyle::Field::fn_alt_below,ON_DimStyle::field::AltBelow},
    {ON_V5x_DimStyle::Field::fn_dim_arrow_type1,ON_DimStyle::field::ArrowType1},
    {ON_V5x_DimStyle::Field::fn_dim_arrow_type2,ON_DimStyle::field::ArrowType2},
    {ON_V5x_DimStyle::Field::fn_dim_arrow_blockname1,ON_DimStyle::field::ArrowBlockId1},
    {ON_V5x_DimStyle::Field::fn_dim_arrow_blockname2,ON_DimStyle::field::ArrowBlockId2}
  };

  *field_id_map_count = sizeof(field_id_map) / sizeof(field_id_map[0]);
  return field_id_map;
}

static void Internal_V6LengthDisplayFromV5LengthFormatAndFactor(
  ON::LengthUnitSystem model_unit_system,
  int v5_length_format, // 0 = decimal, 1 = fractional, 2 = feet and inches
  double v5_length_factor,
  ON_DimStyle::LengthDisplay& v6_dimension_length_display,
  double& v6_length_factor
)
{
  if ( 2 == v5_length_format)
  {
    v6_dimension_length_display = ON_DimStyle::LengthDisplay::FeetAndInches;
    v6_length_factor = 1.0;
    return;
  }

  if (!(v5_length_factor > 0.0 && v5_length_factor < ON_UNSET_POSITIVE_VALUE))
    v5_length_factor = 1.0;

  v6_dimension_length_display = ON_DimStyle::LengthDisplay::ModelUnits;
  v6_length_factor = v5_length_factor;

  if (false == ON::IsTerrestrialLengthUnit(model_unit_system))
  {
    return;
  }

  if (fabs(1.0 - v5_length_factor) <= 0.001)
  {
    v6_length_factor = 1.0;
    if (1 == v5_length_format && ON::LengthUnitSystem::Inches == model_unit_system)
      v6_dimension_length_display = ON_DimStyle::LengthDisplay::InchesFractional;
    return;
  }

  // See if v5_length_factor is a V5 length unit scale factor
  const ON::LengthUnitSystem dim_style_unit_systems[]
    = {
    ON::LengthUnitSystem::Millimeters,
    ON::LengthUnitSystem::Centimeters,
    ON::LengthUnitSystem::Meters,
    ON::LengthUnitSystem::Kilometers,
    ON::LengthUnitSystem::Inches,
    ON::LengthUnitSystem::Feet,
    ON::LengthUnitSystem::Miles
  };

  const int dim_style_unit_systems_count = (int)(sizeof(dim_style_unit_systems) / sizeof(dim_style_unit_systems[0]));
  ON::LengthUnitSystem dim_style_unit_system = ON::LengthUnitSystem::None;
  double dim_style_unit_system_delta = 1e300;
  for (int i = 0; i < dim_style_unit_systems_count; i++)
  {
    const double lf = ON::UnitScale(model_unit_system, dim_style_unit_systems[i]);
    if (!(lf > 0.0))
      continue;
    const double delta = fabs(lf - v5_length_factor);
    if (!(delta >= 0.0))
      continue;
    if (delta > 0.001*lf)
      continue;

    if (delta < dim_style_unit_system_delta)
    {
      dim_style_unit_system_delta = delta;
      dim_style_unit_system = dim_style_unit_systems[i];
    }
  }

  switch (dim_style_unit_system)
  {
    case ON::LengthUnitSystem::Millimeters: 
      v6_length_factor = 1.0;
      v6_dimension_length_display = ON_DimStyle::LengthDisplay::Millmeters;
      break;

    case ON::LengthUnitSystem::Centimeters:
      v6_length_factor = 1.0;
      v6_dimension_length_display = ON_DimStyle::LengthDisplay::Centimeters;
      break;

    case ON::LengthUnitSystem::Meters:
      v6_length_factor = 1.0;
      v6_dimension_length_display = ON_DimStyle::LengthDisplay::Meters;
      break;

    case ON::LengthUnitSystem::Kilometers:
      v6_length_factor = 1.0;
      v6_dimension_length_display = ON_DimStyle::LengthDisplay::Kilometers;
      break;

    case ON::LengthUnitSystem::Inches:
      v6_length_factor = 1.0;
      if (1 == v5_length_format)
        v6_dimension_length_display = ON_DimStyle::LengthDisplay::InchesFractional;
      else
        v6_dimension_length_display = ON_DimStyle::LengthDisplay::InchesDecimal;
      break;

    case ON::LengthUnitSystem::Feet:
      v6_length_factor = 1.0;
      v6_dimension_length_display = ON_DimStyle::LengthDisplay::FeetDecimal;
      break;

    case ON::LengthUnitSystem::Miles:
      v6_length_factor = 1.0;
      v6_dimension_length_display = ON_DimStyle::LengthDisplay::Miles;
      break;
    default:
      break;
  }

  return;
}

// Convert from V5 ON_dDimStyle to V6 ON_Dimstyle
ON_DimStyle::ON_DimStyle(
  ON::LengthUnitSystem model_length_unit_system,
  const ON_V5x_DimStyle& src
)
  : ON_ModelComponent(src)
{
  // ON_ModelComponent(src) copies the parent id

  bool bV5LengthFactorOverride = false;
  bool bV5AltLengthFactorOverride = false;
  bool bV5LengthFormatOverride = false;
  bool bV5AltLengthFormatOverride = false;

  if ( src.ParentIdIsNotNil() && src.m_field_override_count > 0)
  {
    // src.m_field_override_count > 0) indicates some of the settings on the V5 dimstyle
    // are independent of the parent dimstyle. When we find those, 
    // we will set them on this as well.
    size_t field_id_map_count = 0;
    const struct V5_to_V6_field_id_map* field_id_map = GetDimStyleFieldIdMap(&field_id_map_count);
    for (size_t i = 0; i < field_id_map_count; i++)
    {
      if (ON_V5x_DimStyle::Field::fn_unset == field_id_map[i].m_v5_field_id)
        continue; // no mapping from V6 setting to V6 ON_V5x_DimStyle
      if (ON_DimStyle::field::Unset == field_id_map[i].m_v6_field_id)
        continue; // no mapping from V5 setting to V6 ON_DimStyle
      if (ON_DimStyle::field::Name == field_id_map[i].m_v6_field_id || ON_DimStyle::field::Index == field_id_map[i].m_v6_field_id)
        continue; // name and index are never from parent
      if (src.IsFieldOverride(field_id_map[i].m_v5_field_id))
        this->SetFieldOverride(field_id_map[i].m_v6_field_id, true);
    }

    // Now handle obsolete overrides that convert to dimension length display override
    bV5LengthFormatOverride = src.IsFieldOverride(ON_V5x_DimStyle::Field::fn_lengthformat);
    bV5AltLengthFormatOverride = src.IsFieldOverride(ON_V5x_DimStyle::Field::fn_alternate_lengthformat);
    bV5LengthFactorOverride = src.IsFieldOverride(ON_V5x_DimStyle::Field::fn_lengthfactor);
    bV5AltLengthFactorOverride = src.IsFieldOverride(ON_V5x_DimStyle::Field::fn_alternate_lengthfactor);
  }

  m_extextension = src.m_extextension;
  m_extoffset = src.m_extoffset;
  m_arrowsize = src.m_arrowsize;
  m_centermark = src.m_centermark;
  m_textgap = src.m_textgap;
  m_textheight = src.m_textheight;


  // V5 had a single ON_INTERNAL_OBSOLETE::V5_TextDisplayMode enum
  // V6 has 8 separate settings and 2 enums
  switch (src.m_dimstyle_textalign)
  {
  case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kNormal:
    m_dim_text_location = ON_DimStyle::TextLocation::AboveDimLine;
    m_dimradial_text_location = ON_DimStyle::TextLocation::InDimLine;
    m_dimradial_text_angle_style = ON_DimStyle::ContentAngleStyle::Horizontal;
    break;

  case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalToScreen:
    m_dim_text_location = ON_DimStyle::TextLocation::InDimLine;
    m_dimradial_text_location = ON_DimStyle::TextLocation::InDimLine;
    m_leader_text_orientation     = ON::TextOrientation::InView;
    m_dim_text_orientation        = ON::TextOrientation::InView;
    m_dimradial_text_orientation  = ON::TextOrientation::InView;
    m_dimradial_text_angle_style = ON_DimStyle::ContentAngleStyle::Horizontal;
    break;

  case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine:
    m_dim_text_location = ON_DimStyle::TextLocation::AboveDimLine;
    m_dimradial_text_location = ON_DimStyle::TextLocation::InDimLine;
    m_dimradial_text_angle_style = ON_DimStyle::ContentAngleStyle::Horizontal;
    break;

  case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kInLine:
    m_dim_text_location = ON_DimStyle::TextLocation::InDimLine;
    m_dimradial_text_location = ON_DimStyle::TextLocation::InDimLine;
    m_dimradial_text_angle_style = ON_DimStyle::ContentAngleStyle::Horizontal;
    break;

  case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalInCplane:
    m_dim_text_location = ON_DimStyle::TextLocation::InDimLine;
    m_dimradial_text_location = ON_DimStyle::TextLocation::InDimLine;
    m_dim_text_angle_style = ON_DimStyle::ContentAngleStyle::Horizontal;
    m_dimradial_text_angle_style = ON_DimStyle::ContentAngleStyle::Horizontal;
    break;
  }

  m_arrow_type_1 = V6ArrowType(src.m_arrowtype);
  m_arrow_type_2 = V6ArrowType(src.m_arrowtype);
  m_angleformat = ON_DimStyle::angle_format::DecimalDegrees;

  // Set m_dimension_length_display and m_lengthfactor
  const ON_DimStyle::LengthDisplay dimension_length_display0 = m_dimension_length_display;
  Internal_V6LengthDisplayFromV5LengthFormatAndFactor(
    model_length_unit_system,
    src.m_lengthformat, // 0 = decimal, 1 = fractional, 2 = feet and inches
    src.m_lengthfactor,
    m_dimension_length_display,
    m_lengthfactor
  );
  if (bV5LengthFormatOverride || bV5LengthFactorOverride)
  {
    if (dimension_length_display0 != m_dimension_length_display)
    {
      this->SetFieldOverride(ON_DimStyle::field::DimensionLengthDisplay, true);
      if ( 1.0 == m_lengthfactor )
        this->SetFieldOverride(ON_DimStyle::field::LengthFactor, false);
    }
    if( m_lengthfactor != src.m_lengthfactor && bV5LengthFactorOverride)
      this->SetFieldOverride(ON_DimStyle::field::LengthFactor, false);
  }

  // Set m_alternate_dimension_length_display and m_alternate_lengthfactor
  const ON_DimStyle::LengthDisplay alternate_dimension_length_display0 = m_alternate_dimension_length_display;
  Internal_V6LengthDisplayFromV5LengthFormatAndFactor(
    model_length_unit_system,
    src.m_alternate_lengthformat, // 0 = decimal, 1 = fractional, 2 = feet and inches
    src.m_alternate_lengthfactor,
    m_alternate_dimension_length_display,
    m_alternate_lengthfactor
  );
  if (bV5AltLengthFormatOverride || bV5AltLengthFactorOverride)
  {
    if (alternate_dimension_length_display0 != m_alternate_dimension_length_display)
    {
      this->SetFieldOverride(ON_DimStyle::field::AlternateDimensionLengthDisplay, true);
      if ( 1.0 == m_alternate_lengthfactor )
        this->SetFieldOverride(ON_DimStyle::field::AlternateLengthFactor, false);
    }
    if( m_alternate_lengthfactor != src.m_alternate_lengthfactor && bV5AltLengthFactorOverride)
      this->SetFieldOverride(ON_DimStyle::field::AlternateLengthFactor, false);
  }

  m_lengthresolution = src.m_lengthresolution;
  m_angleresolution = src.m_angleresolution;
  SetFont( src.V5TextStyle().Font() );
  m_bAlternate = src.m_bAlternate;

  m_alternate_lengthresolution = src.m_alternate_lengthresolution;
  m_prefix = src.m_prefix;
  m_suffix = src.m_suffix;
  m_alternate_prefix = src.m_alternate_prefix;
  m_alternate_suffix = src.m_alternate_suffix;
  m_dimextension = src.m_dimextension;
  m_leaderarrowsize = src.m_leaderarrowsize;
  m_leader_arrow_type = V6ArrowType(src.m_leaderarrowtype);
  m_bSuppressExtension1 = src.m_bSuppressExtension1;
  m_bSuppressExtension2 = src.m_bSuppressExtension2;
  m_source_dimstyle = src.m_source_dimstyle;
  m_tolerance_format = V6ToleranceFormat(src.m_tolerance_style);
  m_tolerance_resolution = src.m_tolerance_resolution;
  m_tolerance_upper_value = src.m_tolerance_upper_value;
  m_tolerance_lower_value = src.m_tolerance_lower_value;
  m_tolerance_height_scale = src.m_tolerance_height_scale;
  m_baseline_spacing = src.m_baseline_spacing;
  SetDrawTextMask(src.m_bDrawMask);
  SetMaskFillType(V6MaskTypeFromV5MaskColorSource(src.m_mask_color_source));
  SetMaskColor(src.m_mask_color);
  SetMaskBorder(src.m_textgap);
  //m_dimscale = src.m_dimscale;
  SetDimScale( src.m_dimscale); // sets m_scale_value and m_dimscale fields.
  m_dimscale_source = src.m_dimscale_source;
  m_leader_landing_length = m_textheight;

  switch (src.m_dimstyle_textalign)
  {

  case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalToScreen:
  case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalInCplane:
    m_leader_content_angle_style = ON_DimStyle::ContentAngleStyle::Horizontal;
    break;

  case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kNormal:
  case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine:
  case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kInLine:
  default:
    m_leader_content_angle_style = ON_DimStyle::ContentAngleStyle::Aligned;
    break;
  }

  m_leader_has_landing = false; // V5 had no landing concept.  V5 Leaders have an extra horizontal segment

  if (ON_DimStyle::LengthDisplay::FeetAndInches == m_dimension_length_display)
  {
    // this matches V5 default behavior.
    m_zero_suppress = ON_DimStyle::suppress_zero::SuppressZeroFeet;
  }


  // Make sure zero suppression settings are valid
  if (false == ON_DimStyle::ZeroSuppressMatchesLengthDisplay(m_zero_suppress, m_dimension_length_display))
    m_zero_suppress = ON_DimStyle::suppress_zero::None;

  if (false == ON_DimStyle::ZeroSuppressMatchesLengthDisplay(m_alt_zero_suppress, m_alternate_dimension_length_display))
    m_alt_zero_suppress = ON_DimStyle::suppress_zero::None;

  // any decimal format will do to test m_ang_zero_suppress
  if (false == ON_DimStyle::ZeroSuppressMatchesLengthDisplay(m_ang_zero_suppress, ON_DimStyle::LengthDisplay::ModelUnits))
    m_ang_zero_suppress = ON_DimStyle::suppress_zero::None;
}

ON_INTERNAL_OBSOLETE::V5_TextDisplayMode ON_INTERNAL_OBSOLETE::V5TextDisplayModeFromV6DimStyle(
  const ON_DimStyle& V6_dim_style
)
{
  if (V6_dim_style.DimTextOrientation() == ON::TextOrientation::InView)
  {
    return ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalToScreen;
  }

  switch (V6_dim_style.DimTextLocation())
  {
  case ON_DimStyle::TextLocation::AboveDimLine:
    return ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine;
    break;

  case ON_DimStyle::TextLocation::InDimLine:
    return (ON_DimStyle::ContentAngleStyle::Horizontal == V6_dim_style.DimTextAngleStyle() )
      ? ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalInCplane
      : ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kInLine;
    break;

  case ON_DimStyle::TextLocation::BelowDimLine:
    return ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine;
    break;

  default:
    break;
  }

  return ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kNormal;
}

static void Internal_SetV5LengthFormatAndFactorFromV6LengthDisplay(
  ON::LengthUnitSystem model_length_units,
  ON_DimStyle::LengthDisplay V6length_display,
  double V6_length_factor,
  int& V5_lengthformat,
  double& V5_lengthfactor
)
{
  if (!(V6_length_factor > 0.0 && V6_length_factor < ON_UNSET_POSITIVE_VALUE))
    V6_length_factor = 1.0;

  V5_lengthformat = 0;
  V5_lengthfactor = V6_length_factor;

  if (ON_DimStyle::LengthDisplay::ModelUnits == V6length_display)
  {
    return;
  }

  if (ON_DimStyle::LengthDisplay::FeetAndInches == V6length_display)
  {
    V5_lengthformat = 2;
    return;
  }

  if (false == ON::IsTerrestrialLengthUnit(model_length_units))
  {
    return;
  }

  const ON::LengthUnitSystem V6length_display_unit_system = ON_DimStyle::LengthUnitSystemFromLengthDisplay(V6length_display);
  if ( ON::LengthUnitSystem::None == V6length_display_unit_system || false == ON::IsTerrestrialLengthUnit(V6length_display_unit_system))
  {
    return;
  }

  V5_lengthfactor = V6_length_factor*ON::UnitScale(model_length_units, V6length_display_unit_system);

  if (ON_DimStyle::LengthDisplay::InchesFractional == V6length_display)
  {
    V5_lengthformat = 1;
    return;
  }

  return; 
}

// Convert from V6 ON_Dimstyle to v5 ON_Dimstyle
ON_V5x_DimStyle::ON_V5x_DimStyle(
  ON::LengthUnitSystem model_length_unit_system,
  const ON_DimStyle& src
)
  : ON_ModelComponent(src)
{
  ClearAllFieldOverrides();
  if ( src.ParentIdIsNotNil() )
  {
    ///ClearId(); // why?
    ///ClearIndex(); // why?
    ClearModelSerialNumber(); // why?

    SetParentId(src.ParentId());
    if ( src.HasOverrides() )
    {
      size_t field_id_map_count = 0;
      const struct V5_to_V6_field_id_map* field_id_map = GetDimStyleFieldIdMap(&field_id_map_count);
      for (size_t i = 0; i < field_id_map_count; i++)
      {        
        if ( ON_V5x_DimStyle::Field::fn_unset == field_id_map[i].m_v5_field_id )
          continue; // no mapping from V6 setting to V6 ON_V5x_DimStyle
        if ( ON_DimStyle::field::Unset == field_id_map[i].m_v6_field_id)
          continue; // no mapping from V5 setting to V6 ON_DimStyle
        if ( ON_DimStyle::field::Name == field_id_map[i].m_v6_field_id)
          continue; // name is never from parent
        if ( ON_DimStyle::field::Index == field_id_map[i].m_v6_field_id)
          continue; // index is never from parent
        if ( src.IsFieldOverride(field_id_map[i].m_v6_field_id) )
          SetFieldOverride(field_id_map[i].m_v5_field_id, true);
      }
    }
  }

  m_extextension = src.m_extextension;
  m_extoffset = src.m_extoffset;
  m_arrowsize = src.m_arrowsize;
  m_centermark = src.m_centermark;
  m_textgap = src.m_textgap;
  m_textheight = src.m_textheight;
  m_dimstyle_textalign = ON_INTERNAL_OBSOLETE::V5TextDisplayModeFromV6DimStyle(src);
  m_arrowtype = ON_DimStyle::V5ArrowType(src.m_arrow_type_1);
  m_angularunits = 0;

  m_lengthformat = 0;
  m_lengthfactor = 1.0;
  Internal_SetV5LengthFormatAndFactorFromV6LengthDisplay(
    model_length_unit_system,
    src.m_dimension_length_display,
    src.m_lengthfactor,
    m_lengthformat,
    m_lengthfactor
  );

  m_alternate_lengthformat = 0;
  m_alternate_lengthfactor = 1.0;
  Internal_SetV5LengthFormatAndFactorFromV6LengthDisplay(
    model_length_unit_system,
    src.m_alternate_dimension_length_display,
    src.m_alternate_lengthfactor,
    m_alternate_lengthformat,
    m_alternate_lengthfactor
  );

  m_angleformat = ON_DimStyle::V5AngleFormat(src.m_angleformat);

  //const ON_DimStyle::OBSOLETE_length_format obsolete_v6_length_format = ON_DimStyle::OBSOLETE_LengthFormatFromLengthDisplay(
  //  src.DimensionLengthDisplay(),
  //  src.ModelSerialNumber()
  //);
  
  m_lengthresolution = src.m_lengthresolution;
  m_angleresolution = src.m_angleresolution;
  m_v5_text_style.SetFont(src.Font());
  m_bAlternate = src.m_bAlternate;

  //const ON_DimStyle::OBSOLETE_length_format obsolete_v6_alt_length_format = ON_DimStyle::OBSOLETE_LengthFormatFromLengthDisplay(
  //  src.AlternateDimensionLengthDisplay(),
  //  src.ModelSerialNumber()
  //);

  m_alternate_lengthresolution = src.m_alternate_lengthresolution;
  m_prefix = src.m_prefix;
  m_suffix = src.m_suffix;
  m_alternate_prefix = src.m_alternate_prefix;
  m_alternate_suffix = src.m_alternate_suffix;
  m_dimextension = src.m_dimextension;
  m_leaderarrowsize = src.m_leaderarrowsize;
  m_leaderarrowtype = ON_DimStyle::V5ArrowType(src.m_leader_arrow_type);
  m_bSuppressExtension1 = src.m_bSuppressExtension1;
  m_bSuppressExtension2 = src.m_bSuppressExtension2;
  m_source_dimstyle = src.m_source_dimstyle;
  m_tolerance_style = ON_DimStyle::V5ToleranceFormat(src.m_tolerance_format);
  m_tolerance_resolution = src.m_tolerance_resolution;
  m_tolerance_upper_value = src.m_tolerance_upper_value;
  m_tolerance_lower_value = src.m_tolerance_lower_value;
  m_tolerance_height_scale = src.m_tolerance_height_scale;
  m_baseline_spacing = src.m_baseline_spacing;
  m_bDrawMask = src.DrawTextMask();
  m_mask_color_source = ON_DimStyle::V5MaskColorSourceFromV6MaskType(src.MaskFillType());
  m_mask_color = src.MaskColor();
  m_dimscale = src.DimScale();
  m_dimscale_source = src.m_dimscale_source;
}


#pragma endregion Legacy dimstyle conversions

unsigned int ON_DimStyle::Internal_GetSystemDimstyleList(
  ON_SimpleArray<const ON_DimStyle*>& system_dimstyle_list
)
{
  system_dimstyle_list.SetCount(0);
  system_dimstyle_list.Reserve(8);
  system_dimstyle_list.Append(&ON_DimStyle::Default);
  system_dimstyle_list.Append(&ON_DimStyle::DefaultInchDecimal);
  system_dimstyle_list.Append(&ON_DimStyle::DefaultInchFractional);
  system_dimstyle_list.Append(&ON_DimStyle::DefaultFootInchArchitecture);
  system_dimstyle_list.Append(&ON_DimStyle::DefaultMillimeterSmall);
  system_dimstyle_list.Append(&ON_DimStyle::DefaultMillimeterLarge);
  system_dimstyle_list.Append(&ON_DimStyle::DefaultMillimeterArchitecture);
  return system_dimstyle_list.UnsignedCount();
}

const ON_DimStyle& ON_DimStyle::DimStyleOrDefault(
  const class ON_DimStyle* dimstyle
)
{
  if (nullptr == dimstyle)
    dimstyle = &ON_DimStyle::Default;
  return *dimstyle;
}


const ON_DimStyle& ON_DimStyle::SystemDimstyleFromId(
  ON_UUID id
)
{
  if (id != ON_nil_uuid)
  {
    ON_SimpleArray<const ON_DimStyle*> system_dimstyle_list;
    const unsigned int count = ON_DimStyle::Internal_GetSystemDimstyleList(system_dimstyle_list);
    for (unsigned int i = 0; i < count; i++)
    {
      if (id == system_dimstyle_list[i]->Id())
        return *system_dimstyle_list[i];
    }
  }
  return ON_DimStyle::Unset;
}

const ON_DimStyle& ON_DimStyle::SystemDimstyleFromIndex(
  int index
)
{
  if (index < 0 && index > ON_UNSET_INT_INDEX)
  {
    ON_SimpleArray<const ON_DimStyle*> system_dimstyle_list;
    const unsigned int count = ON_DimStyle::Internal_GetSystemDimstyleList(system_dimstyle_list);
    for (unsigned int i = 0; i < count; i++)
    {
      if (index == system_dimstyle_list[i]->Index())
        return *system_dimstyle_list[i];
    }
  }
  return ON_DimStyle::Unset;
}

const ON_DimStyle& ON_DimStyle::SystemDimstyleFromName(
  const ON_NameHash& name_hash
)
{
  if (name_hash.IsValidAndNotEmpty())
  {
    ON_SimpleArray<const ON_DimStyle*> system_dimstyle_list;
    const unsigned int count = ON_DimStyle::Internal_GetSystemDimstyleList(system_dimstyle_list);
    for (unsigned int i = 0; i < count; i++)
    {
      if ( name_hash == system_dimstyle_list[i]->NameHash() )
        return *system_dimstyle_list[i];
    }
  }
  return ON_DimStyle::Unset;
}


const ON_DimStyle& ON_DimStyle::SystemDimstyleFromContentHash(
  const ON_SHA1_Hash& content_hash
)
{
  if (false == content_hash.IsZeroDigestOrEmptyContentHash())
  {
    ON_SimpleArray<const ON_DimStyle*> system_dimstyle_list;
    const unsigned int count = ON_DimStyle::Internal_GetSystemDimstyleList(system_dimstyle_list);
    for (unsigned int i = 0; i < count; i++)
    {
      if ( content_hash == system_dimstyle_list[i]->ContentHash() )
        return *system_dimstyle_list[i];
    }
  }
  return ON_DimStyle::Unset;
}

// construct from V4 and earier ON_3dmAnnotationSettings and add a couple of fields
ON_DimStyle::ON_DimStyle(const ON_3dmAnnotationSettings& src)
  : ON_ModelComponent(ON_ModelComponent::Type::DimStyle)
{
  m_extextension = src.m_dimexe;
  m_extoffset = src.m_dimexo;
  m_arrowsize = src.m_arrowlength;
  m_centermark = src.m_centermark;
  m_textgap = src.m_dimexo / 2.0;
  m_textheight = src.m_textheight;
  m_dimension_length_display
    = (2 == src.m_lengthformat)
    ? ON_DimStyle::LengthDisplay::FeetAndInches
    : ON_DimStyle::LengthDisplay::ModelUnits;
  m_angleformat = (ON_DimStyle::angle_format) src.m_angleformat;
  m_lengthresolution = src.m_resolution;
  m_angleresolution = src.m_resolution;
  m_dimension_length_display
    = (2 == src.m_lengthformat)
    ? ON_DimStyle::LengthDisplay::FeetAndInches
    : ON_DimStyle::LengthDisplay::ModelUnits;
}

bool ON_DimStyle::Internal_EqualOverrideParentFields(
    const ON_DimStyle& a,
    const ON_DimStyle& b
  )
{
  return (
    a.m_field_override_parent_count == b.m_field_override_parent_count
    && a.m_field_override_parent_bits0 == b.m_field_override_parent_bits0
    && a.m_field_override_parent_bits1 == b.m_field_override_parent_bits1
    && a.m_field_override_parent_bits2 == b.m_field_override_parent_bits2
    && a.m_field_override_parent_bits3 == b.m_field_override_parent_bits3
    );
}

bool ON_DimStyle::CompareDimstyle(const ON_DimStyle& style) const
{
  return (
    0 == ON_ModelComponent::CompareNameExact(*this, style)
    && CompareFields(style)
    && ON_DimStyle::Internal_EqualOverrideParentFields(*this,style)
    );
}

bool ON_DimStyle::CompareFields(const ON_DimStyle& style) const
{
  if (
    Font().ManagedFontSerialNumber() == style.Font().ManagedFontSerialNumber() && // text rendered the same way
    0 == ON_Font::CompareFontCharacteristics(m_font_characteristics,style.m_font_characteristics) && // same values passed to set font
    m_extextension == style.m_extextension &&
    m_extoffset == style.m_extoffset &&
    m_arrowsize == style.m_arrowsize &&
    m_centermark == style.m_centermark &&
    m_centermark_style == style.m_centermark_style &&
    m_textgap == style.m_textgap &&
    m_textheight == style.m_textheight &&
    m_dim_text_location == style.m_dim_text_location &&
    m_dimradial_text_location == style.m_dimradial_text_location &&

    m_dimension_length_display == style.m_dimension_length_display &&
    m_alternate_dimension_length_display == style.m_alternate_dimension_length_display &&

    m_lengthresolution == style.m_lengthresolution &&
    m_angleformat == style.m_angleformat &&
    m_angleresolution == style.m_angleresolution &&
    m_lengthfactor == style.m_lengthfactor &&

    m_bAlternate == style.m_bAlternate &&
    m_alternate_lengthfactor == style.m_alternate_lengthfactor &&
    m_alternate_lengthresolution == style.m_alternate_lengthresolution &&

    m_prefix == style.m_prefix &&
    m_suffix == style.m_suffix &&
    m_alternate_prefix == style.m_alternate_prefix &&
    m_alternate_suffix == style.m_alternate_suffix &&

    m_dimextension == style.m_dimextension &&
    m_bSuppressExtension1 == style.m_bSuppressExtension1 &&
    m_bSuppressExtension2 == style.m_bSuppressExtension2 &&

    ParentId() == style.ParentId() &&
    m_source_dimstyle == style.m_source_dimstyle &&

    m_tolerance_format == style.m_tolerance_format &&
    m_tolerance_resolution == style.m_tolerance_resolution &&
    m_alternate_tolerance_resolution == style.m_alternate_tolerance_resolution &&
    m_tolerance_upper_value == style.m_tolerance_upper_value &&
    m_tolerance_lower_value == style.m_tolerance_lower_value &&
    m_tolerance_height_scale == style.m_tolerance_height_scale &&
    m_baseline_spacing == style.m_baseline_spacing &&
    m_text_mask == style.m_text_mask &&
    DimScale() == style.DimScale() &&
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
    m_alternate_tolerance_resolution == style.m_alternate_tolerance_resolution &&
    m_suppress_arrow1 == style.m_suppress_arrow1 &&
    m_suppress_arrow2 == style.m_suppress_arrow2 &&
    m_textmove_leader == style.m_textmove_leader &&
    m_arclength_sym == style.m_arclength_sym &&
    m_stack_textheight_fraction == style.m_stack_textheight_fraction &&
    m_stack_format == style.m_stack_format &&
    m_alt_round == style.m_alt_round &&
    m_round == style.m_round &&
    m_angular_round == style.m_angular_round &&
    m_alt_zero_suppress == style.m_alt_zero_suppress &&
    m_zero_suppress == style.m_zero_suppress &&
    m_ang_zero_suppress == style.m_ang_zero_suppress &&

    m_arrow_type_1 == style.m_arrow_type_1 &&
    m_arrow_type_2 == style.m_arrow_type_2 &&
    m_leader_arrow_type == style.m_leader_arrow_type &&
    m_arrow_block_id_1 == style.m_arrow_block_id_1 &&
    m_arrow_block_id_2 == style.m_arrow_block_id_2 &&
    m_leader_arrow_block_id == style.m_leader_arrow_block_id &&

    m_text_vertical_alignment == style.m_text_vertical_alignment &&
    m_leader_text_vertical_alignment == style.m_leader_text_vertical_alignment &&
    m_leader_text_horizontal_alignment == style.m_leader_text_horizontal_alignment &&
    m_leader_content_angle_style == style.m_leader_content_angle_style &&
    m_leader_curve_type == style.m_leader_curve_type &&
    m_leader_content_angle == style.m_leader_content_angle &&
    m_leader_has_landing == style.m_leader_has_landing &&
    m_leader_landing_length == style.m_leader_landing_length &&
    m_draw_forward == style.m_draw_forward &&
    m_signed_ordinate == style.m_signed_ordinate &&

    m_scale_value.LeftToRightScale() == style.m_scale_value.LeftToRightScale() &&
    m_dimstyle_unitsystem == style.m_dimstyle_unitsystem &&
    m_text_orientation == style.m_text_orientation &&
    m_leader_text_orientation == style.m_leader_text_orientation &&
    m_dim_text_orientation == style.m_dim_text_orientation &&
    m_dimradial_text_orientation == style.m_dimradial_text_orientation &&
    m_dim_text_angle_style == style.m_dim_text_angle_style &&
    m_dimradial_text_angle_style == style.m_dimradial_text_angle_style &&
    m_text_underlined == style.m_text_underlined &&
    
    m_bForceDimLine == style.m_bForceDimLine &&
    m_ArrowFit == style.m_ArrowFit &&
    m_TextFit == style.m_TextFit &&
    m_decimal_separator == style.m_decimal_separator
    )
    return true;
  else
    return false;
}

//////////////////////////////////////////////////////////////////////
//
// ON_Object overrides

bool ON_DimStyle::IsValid(ON_TextLog* text_log) const
{
  return (NameIsNotEmpty() && Index() >= 0);
}

void ON_DimStyle::Dump(ON_TextLog& dump) const
{
  ON_ModelComponent::Dump(dump);
  dump.Print("Font\n");
  dump.PushIndent();
  m_font_characteristics.Dump(dump);
  dump.PopIndent();
}


/////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////





bool ON_DimStyle::Write(
  ON_BinaryArchive& file // serialize definition to binary archive
  ) const
{
  if (!file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, 1, 9))
    return false;

  bool rc = false;
  for (;;)
  {
    if (!file.WriteModelComponentAttributes(*this, ON_ModelComponent::Attributes::BinaryArchiveAttributes))
      break;

    unsigned int u;

    if (!file.WriteDouble(m_extextension)) break;
    if (!file.WriteDouble(m_extoffset)) break;
    if (!file.WriteDouble(m_arrowsize)) break;
    if (!file.WriteDouble(m_leaderarrowsize)) break;
    if (!file.WriteDouble(m_centermark)) break;
    if (!file.WriteDouble(m_textgap)) break;
    if (!file.WriteDouble(m_textheight)) break;


    ON_INTERNAL_OBSOLETE::V5_TextDisplayMode obsolete_dimstyle_textalign = ON_INTERNAL_OBSOLETE::V5TextDisplayModeFromV6DimStyle(*this);
    u = static_cast<unsigned int>(obsolete_dimstyle_textalign);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned char>(m_angleformat);
    if (!file.WriteInt(u)) break;

    // do not pass in model_sn - we want ON::LengthUnitSystem::None from ON_DimStyle::LengthDisplay::ModelUnits.
    const ON::LengthUnitSystem dim_length_display_unit = DimensionLengthDisplayUnit(0);
    const ON::LengthUnitSystem alt_dim_length_display_unit = AlternateDimensionLengthDisplayUnit(0);

    // write obsolete ON_DimStyle::OBSOLETE_LengthForma enum value
    u = static_cast<unsigned char>(
      ON_DimStyle::OBSOLETE_LengthFormatFromLengthDisplay(
        DimensionLengthDisplay(),
        dim_length_display_unit
      )
      );
    if (!file.WriteInt(u)) break;

    if (!file.WriteInt(m_angleresolution)) break;
    if (!file.WriteInt(m_lengthresolution)) break;

    if (file.Archive3dmVersion() >= 60)
    {
      int ignored_text_style_index = ON_UNSET_INT_INDEX;
      if (!file.WriteInt(ignored_text_style_index))
        break;
    }
    else
    {
      // ON_ModelComponent::Type::TextStyle, Index() are not  mistakes.
      // The code in Write3dmReferencedComponentIndex() will convert the dim style index to an approprate
      // value tht depends on the version ofr 3dm archive (<= V5 or >= V6) being saved.
      if (!file.Write3dmReferencedComponentIndex(ON_ModelComponent::Type::TextStyle, Index())) break;
    }

    if (!file.WriteDouble(m_lengthfactor)) break;
    if (!file.WriteBool(m_bAlternate)) break;
    if (!file.WriteDouble(m_alternate_lengthfactor)) break;

    // write alternate obsolete ON_DimStyle::OBSOLETE_LengthForma enum value
    u = static_cast<unsigned char>(
      ON_DimStyle::OBSOLETE_LengthFormatFromLengthDisplay(
        AlternateDimensionLengthDisplay(),
        alt_dim_length_display_unit
      )
      );
    if (!file.WriteInt(u)) break;

    if (!file.WriteInt(m_alternate_lengthresolution)) break;

    // The ON_wString::IsValid calls prevent corrupt strings from breaking file IO
    m_prefix.IsValid(true);
    if (!file.WriteString(m_prefix)) break;

    m_suffix.IsValid(true);
    if (!file.WriteString(m_suffix)) break;

    m_alternate_prefix.IsValid(true);
    if (!file.WriteString(m_alternate_prefix)) break;

    m_alternate_suffix.IsValid(true);
    if (!file.WriteString(m_alternate_suffix)) break;

    if (!file.WriteDouble(m_dimextension)) break;
    if (!file.WriteBool(m_bSuppressExtension1)) break;
    if (!file.WriteBool(m_bSuppressExtension2)) break;

    if (!file.WriteUuid(ParentId())) break;

    unsigned int ignored_legacy_value = m_field_override_parent_count;
    if (!file.WriteInt(ignored_legacy_value)) break;

    bool bOverrides = (m_field_override_parent_count > 0);
    if (!file.WriteBool(bOverrides)) break;
    if (bOverrides)
    {
      const unsigned int count = static_cast<unsigned int>(ON_DimStyle::field::Count);
      ON_SimpleArray<bool> overrides(count);
      for (unsigned int i = 0; i < count; i++)
      {
        overrides.Append(this->IsFieldOverride(ON_DimStyle::FieldFromUnsigned(i)));
      }
      if (!file.WriteArray(overrides)) break;
    }

    u = static_cast<unsigned char>(m_tolerance_format);
    if (!file.WriteInt(u)) break;

    if (!file.WriteInt(m_tolerance_resolution)) break;
    if (!file.WriteDouble(m_tolerance_upper_value)) break;   // or both upper and lower in symmetrical style
    if (!file.WriteDouble(m_tolerance_lower_value)) break;
    if (!file.WriteDouble(m_tolerance_height_scale)) break;  // relative to the main dimension text

    if (!file.WriteDouble(m_baseline_spacing)) break;

    // The text mask settings used to be a collection of several member variables
    // on ON_DimStyle and are now in an ON_TextMask class and a m_text_mask on ON_DimStyle.
    // These values are written here so the file format is not broken and 
    // older versions of Rhino can read newer file.
    if (!file.WriteBool(DrawTextMask())) break;
    u = (unsigned int)(static_cast<unsigned char>(MaskFillType()));
    if (!file.WriteInt(u)) break;
    if (!file.WriteColor(MaskColor())) break;

    if (!file.WriteDouble( DimScale() )) break;
    if (!file.WriteInt(m_dimscale_source)) break;

    if (!file.WriteUuid(m_source_dimstyle)) break;
    if (!file.WriteChar(m_ext_line_color_source)) break;
    if (!file.WriteChar(m_dim_line_color_source)) break;
    if (!file.WriteChar(m_arrow_color_source)) break;
    if (!file.WriteChar(m_text_color_source)) break;
    if (!file.WriteColor(m_ext_line_color)) break;
    if (!file.WriteColor(m_dim_line_color)) break;
    if (!file.WriteColor(m_arrow_color)) break;
    if (!file.WriteColor(m_text_color)) break;
    if (!file.WriteChar(m_ext_line_plot_color_source)) break;
    if (!file.WriteChar(m_dim_line_plot_color_source)) break;
    if (!file.WriteChar(m_arrow_plot_color_source)) break;
    if (!file.WriteChar(m_text_plot_color_source)) break;
    if (!file.WriteColor(m_ext_line_plot_color)) break;
    if (!file.WriteColor(m_dim_line_plot_color)) break;
    if (!file.WriteColor(m_arrow_plot_color)) break;
    if (!file.WriteColor(m_text_plot_color)) break;
    if (!file.WriteChar(m_ext_line_plot_weight_source)) break;
    if (!file.WriteChar(m_dim_line_plot_weight_source)) break;
    if (!file.WriteDouble(m_ext_line_plot_weight_mm)) break;
    if (!file.WriteDouble(m_dim_line_plot_weight_mm)) break;

    if (!file.WriteDouble(m_fixed_extension_len)) break;
    if (!file.WriteBool(m_fixed_extension_len_on)) break;

    if (!file.WriteDouble(m_text_rotation)) break;
    if (!file.WriteInt(m_alternate_tolerance_resolution)) break;
    if (!file.WriteDouble(m_tol_textheight_fraction)) break;

    if (!file.WriteBool(m_suppress_arrow1)) break;
    if (!file.WriteBool(m_suppress_arrow2)) break;
    if (!file.WriteInt(m_textmove_leader)) break;
    if (!file.WriteInt(m_arclength_sym)) break;
    if (!file.WriteDouble(m_stack_textheight_fraction)) break;

    u = static_cast<unsigned char>(m_stack_format);
    if (!file.WriteInt(u)) break;
    if (!file.WriteDouble(m_alt_round)) break;
    if (!file.WriteDouble(m_round)) break;
    if (!file.WriteDouble(m_angular_round)) break;

    u = static_cast<unsigned char>(m_alt_zero_suppress);
    if (!file.WriteInt(u)) break;

    u = 0;// OBSOLETE; static_cast<unsigned char>(m_tol_zero_suppress);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned char>(m_zero_suppress);
    if (!file.WriteInt(u)) break;
    u = static_cast<unsigned char>(m_ang_zero_suppress);
    if (!file.WriteInt(u)) break;


    if (!file.WriteBool(m_alt_below)) break;

    // true: display alternate text after main text
    u = static_cast<unsigned int>(m_arrow_type_1);
    if (!file.WriteInt(u)) break;
    u = static_cast<unsigned int>(m_arrow_type_2);
    if (!file.WriteInt(u)) break;
    u = static_cast<unsigned int>(m_leader_arrow_type);
    if (!file.WriteInt(u)) break;

    // Dale Lear April 8, 2016 
    //  working on http://mcneel.myjetbrains.com/youtrack/issue/RH-31796
    //
    //   It appears that when this code got changed from something that
    //   wrote 16 bytes to something that wrote 3 uuids, the chunk's
    //   minor version number was not increased and no provision was
    //   made to read files that had the the 16 bytes.
    //
    //   The file "layer_test.3dm" written by Windows Rhino WIP built on October 21, 2015
    //   is an example. See the comment in ON_DimStyle::Read() for more details
    //   and a fix that allows us to read the earlier files.
    //
    if (!file.WriteUuid(m_arrow_block_id_1)) break;
    if (!file.WriteUuid(m_arrow_block_id_2)) break;
    if (!file.WriteUuid(m_leader_arrow_block_id)) break;

    // End of version chunk 1.0 fields (in most cases - see comment above)

    // June 10, 2016
    // http://mcneel.myjetbrains.com/youtrack/issue/RH-33795
    // chunk version 1.1 information added

    // BEGIN chunk version 1.1 information

    u = 1; // OBSOLETE ON_DimStyle::leader_content_type::Text
    if (!file.WriteInt(u)) break;

    ON_INTERNAL_OBSOLETE::V5_vertical_alignment obsolete_text_valign = ON_INTERNAL_OBSOLETE::V5VerticalAlignmentFromV6VerticalAlignment(m_text_vertical_alignment);
    u = static_cast<unsigned int>(obsolete_text_valign);
    if (!file.WriteInt(u)) break;

    ON_INTERNAL_OBSOLETE::V5_vertical_alignment obsolete_leader_valign = ON_INTERNAL_OBSOLETE::V5VerticalAlignmentFromV6VerticalAlignment(m_leader_text_vertical_alignment);
    u = static_cast<unsigned int>(obsolete_leader_valign);
    if (!file.WriteInt(u)) break;


    u = static_cast<unsigned int>(m_leader_content_angle_style);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned int>(m_leader_curve_type);
    if (!file.WriteInt(u)) break;

    if (!file.WriteDouble(m_leader_content_angle)) break;
    if (!file.WriteBool(m_leader_has_landing)) break;
    if (!file.WriteDouble(m_leader_landing_length)) break;

    ON_INTERNAL_OBSOLETE::V5_horizontal_alignment obsolete_text_halign = ON_INTERNAL_OBSOLETE::V5HorizontalAlignmentFromV6HorizontalAlignment(m_text_horizontal_alignment);
    u = static_cast<unsigned int>(obsolete_text_halign);
    if (!file.WriteInt(u)) break;

    ON_INTERNAL_OBSOLETE::V5_horizontal_alignment obsolete_leader_halign = ON_INTERNAL_OBSOLETE::V5HorizontalAlignmentFromV6HorizontalAlignment(m_leader_text_horizontal_alignment);
    u = static_cast<unsigned int>(obsolete_leader_halign);
    if (!file.WriteInt(u)) break;

    if (!file.WriteBool(m_draw_forward)) break;
    if (!file.WriteBool(m_signed_ordinate)) break;

    if (!m_scale_value.Write(file)) break;

    u = static_cast<unsigned int>(this->UnitSystem());
    if (!file.WriteInt(u)) break;

    // END chunk version 1.1 information

    // August 2016 added m_font_characteristics to archive.
    if (!m_font_characteristics.Write(file)) break;

    // END chunk version 1.2 information

    // October 2016 added m_text_mask
    if (!m_text_mask.Write(file)) break;

    // END chunk version 1.3 information

    // Feb 2017 added enum values
    u = static_cast<unsigned int>(m_dim_text_location);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned int>(m_dimradial_text_location);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned int>(m_text_vertical_alignment);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned int>(m_text_horizontal_alignment);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned int>(m_leader_text_vertical_alignment);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned int>(m_leader_text_horizontal_alignment);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned int>(m_text_orientation);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned int>(m_leader_text_orientation);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned int>(m_dim_text_orientation);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned int>(m_dimradial_text_orientation);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned int>(m_dim_text_angle_style);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned int>(m_dimradial_text_angle_style);
    if (!file.WriteInt(u)) break;

    if (!file.WriteBool(m_text_underlined)) break;

    // END chunk version 1.4 information

    // June 16, 2017 chunk 1.5 information
    // added m_dimension_unitsystem and m_alt_dimension_unitsystem 
    u = static_cast<unsigned int>(dim_length_display_unit);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned int>(alt_dim_length_display_unit);
    if (!file.WriteInt(u)) break;

    // END chunk version 1.5 information

    // June 29, 2017 chunk 1.6 added 
    // m_dimension_length_display and m_alternate_dimension_length_display
    u = static_cast<unsigned int>(m_dimension_length_display);
    if (!file.WriteInt(u)) break;
    u = static_cast<unsigned int>(m_alternate_dimension_length_display);
    if (!file.WriteInt(u)) break;
    // END chunk version 1.6 information

    u = static_cast<unsigned int>(m_centermark_style);
    if (!file.WriteInt(u)) break;
    // END chunk version 1.7 information

    if (!file.WriteBool(m_bForceDimLine)) break;

    u = static_cast<unsigned int>(m_TextFit);
    if (!file.WriteInt(u)) break;

    u = static_cast<unsigned int>(m_ArrowFit);
    if (!file.WriteInt(u)) break;
    // END chunk version 1.8 information

    u = static_cast<unsigned int>(m_decimal_separator);
    if (!file.WriteInt(u)) break;
    // END chunk version 1.9 information

    rc = true;
    break;
  }
  if (!file.EndWrite3dmChunk())
    rc = false;

  return rc;
}

bool ON_DimStyle::Read(
  ON_BinaryArchive& file // restore definition from binary archive
  )
{
  *this = ON_DimStyle::Unset;

  int major_version = 0;
  int minor_version = 0;
  if (!file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version))
    return false;

  ON__UINT32 archive_field_override_parent_count = 0;
  ON__UINT32 archive_field_override_parent_bits0 = 0;
  ON__UINT32 archive_field_override_parent_bits1 = 0;
  ON__UINT32 archive_field_override_parent_bits2 = 0;
  ON__UINT32 archive_field_override_parent_bits3 = 0;

  bool rc = false;
  for (;;)
  {
    if (1 != major_version)
      break;

    if (!file.ReadModelComponentAttributes(*this, nullptr))
      break;

    unsigned int u;

    if (!file.ReadDouble(&m_extextension)) break;
    if (!file.ReadDouble(&m_extoffset)) break;
    if (!file.ReadDouble(&m_arrowsize)) break;
    if (!file.ReadDouble(&m_leaderarrowsize)) break;
    if (!file.ReadDouble(&m_centermark)) break;
    if (!file.ReadDouble(&m_textgap)) break;
    if (!file.ReadDouble(&m_textheight)) break;

    u = 0;
    if (!file.ReadInt(&u)) break;
    ON_INTERNAL_OBSOLETE::V5_TextDisplayMode obsolete_dimstyle_textalign = ON_INTERNAL_OBSOLETE::V5TextDisplayModeFromUnsigned(u);
    switch (obsolete_dimstyle_textalign)
    {
    case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalToScreen:
      m_dim_text_location = ON_DimStyle::TextLocation::InDimLine;
      m_dimradial_text_location = ON_DimStyle::TextLocation::InDimLine;
      m_text_orientation = ON::TextOrientation::InPlane;
      m_leader_text_orientation = ON::TextOrientation::InView;
      m_dim_text_orientation = ON::TextOrientation::InView;
      m_dimradial_text_orientation = ON::TextOrientation::InView;
      m_dim_text_angle_style = ON_DimStyle::ContentAngleStyle::Horizontal;
      m_dimradial_text_angle_style = ON_DimStyle::ContentAngleStyle::Horizontal;
      break;
    case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalInCplane:
      m_dim_text_location = ON_DimStyle::TextLocation::InDimLine;
      m_dimradial_text_location = ON_DimStyle::TextLocation::InDimLine;
      m_text_orientation = ON::TextOrientation::InPlane;
      m_leader_text_orientation = ON::TextOrientation::InPlane;
      m_dim_text_orientation = ON::TextOrientation::InPlane;
      m_dimradial_text_orientation = ON::TextOrientation::InPlane;
      m_dim_text_angle_style = ON_DimStyle::ContentAngleStyle::Horizontal;
      m_dimradial_text_angle_style = ON_DimStyle::ContentAngleStyle::Horizontal;
      break;
    case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kNormal:
      m_dim_text_location = ON_DimStyle::TextLocation::AboveDimLine;
      m_dimradial_text_location = ON_DimStyle::TextLocation::InDimLine;
      break;
    case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine:
      m_dim_text_location = ON_DimStyle::TextLocation::AboveDimLine;
      m_dimradial_text_location = ON_DimStyle::TextLocation::AboveDimLine;
      break;
    case ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kInLine:
      m_dim_text_location = ON_DimStyle::TextLocation::InDimLine;
      m_dimradial_text_location = ON_DimStyle::TextLocation::InDimLine;
      break;
    default:
      // DO NO HARM ... use ON_DimStyle constructor defaults.
      break;
    }


    u = static_cast<unsigned char>(m_angleformat);
    if (!file.ReadInt(&u)) break;
    m_angleformat = ON_DimStyle::AngleFormatFromUnsigned(u);

    // obsolete dim length format setting
    int obsolete_length_format = 0;
    // (ON_DimStyle::OBSOLETE_length_format) 0 = decimal, 1 = fractional, 2,3 = fett and inches
    if (!file.ReadInt(&obsolete_length_format)) break;
    if (3 == obsolete_length_format)
      obsolete_length_format = 2;

    if (!file.ReadInt(&m_angleresolution)) break;
    if (!file.ReadInt(&m_lengthresolution)) break;
    int text_style_index = ON_UNSET_INT_INDEX;
    if (!file.ReadInt(&text_style_index)) break;
    const ON_TextStyle* text_style = file.ArchiveTextStyleFromArchiveTextStyleIndex(text_style_index);
    if (nullptr != text_style)
    {
      SetFont(text_style->Font());
    }
    
    if (!file.ReadDouble(&m_lengthfactor)) break;

    // Now we have both obsolete_length_format and m_lengthfactor.
    // Try to use this information to m_dimension_length_display.
    if (minor_version <= 5)
    {
      // obsolete_length_format and current m_lengthfactor are V5-ish
      Internal_V6LengthDisplayFromV5LengthFormatAndFactor(
        file.Archive3dmSettings().m_ModelUnitsAndTolerances.m_unit_system.UnitSystem(),
        obsolete_length_format, 
        m_lengthfactor,
        m_dimension_length_display,
        m_lengthfactor
      );
      m_lengthfactor = 1.0;
    }
    else
    {
      ON_Internal_FixBogusDimStyleLengthFactor(file, m_lengthfactor);
    }

    if (!file.ReadBool(&m_bAlternate)) break;
    if (!file.ReadDouble(&m_alternate_lengthfactor)) break;

    // obsolete alternate dim length format setting
    int obsolete_alternate_length_format = 0;
    // (ON_DimStyle::OBSOLETE_length_format) 0 = decimal, 1 = fractional, 2,3 = fett and inches
    if (!file.ReadInt(&obsolete_alternate_length_format)) break;
    if (3 == obsolete_alternate_length_format)
      obsolete_alternate_length_format = 2;

    // Now we have both obsolete_alternate_length_format and m_alternate_lengthfactor
    // Try to use this information to m_alternate_dimension_length_display.
    if (minor_version <= 5)
    {
      // obsolete_alternate_length_format and current m_alternate_lengthfactor are V5-ish
      Internal_V6LengthDisplayFromV5LengthFormatAndFactor(
        file.Archive3dmSettings().m_ModelUnitsAndTolerances.m_unit_system.UnitSystem(),
        obsolete_alternate_length_format, 
        m_alternate_lengthfactor,
        m_alternate_dimension_length_display,
        m_alternate_lengthfactor
      );
      m_alternate_lengthfactor = 1.0;
    }
    else
    {
      ON_Internal_FixBogusDimStyleLengthFactor(file, m_alternate_lengthfactor);
    }

    if (!file.ReadInt(&m_alternate_lengthresolution)) break;
    if (!file.ReadString(m_prefix)) break;
    if (!file.ReadString(m_suffix)) break;
    if (!file.ReadString(m_alternate_prefix)) break;
    if (!file.ReadString(m_alternate_suffix)) break;
    if (!file.ReadDouble(&m_dimextension)) break;
    if (!file.ReadBool(&m_bSuppressExtension1)) break;
    if (!file.ReadBool(&m_bSuppressExtension2)) break;

    ON_UUID parent_dimstyle_id = ParentId();
    if (!file.ReadUuid(parent_dimstyle_id)) break;
    SetParentId(parent_dimstyle_id);

    unsigned int unused_legacy_value = 0;
    if (!file.ReadInt(&unused_legacy_value)) break;

    bool bHasPropertyOverrideBools = false;
    if (!file.ReadBool(&bHasPropertyOverrideBools)) break;
    if (bHasPropertyOverrideBools)
    {
      ON_SimpleArray<bool> property_override_bool;
      if (!file.ReadArray(property_override_bool)) break;
      unsigned int overridescount = property_override_bool.UnsignedCount();
      if (overridescount > static_cast<unsigned int>(ON_DimStyle::field::Count))
      {
        overridescount = static_cast<unsigned int>(ON_DimStyle::field::Count);
        property_override_bool.SetCount(overridescount);
      }
      for (unsigned int i = static_cast<unsigned int>(ON_DimStyle::field::Index)+1; i < overridescount; i++)
      {
        SetFieldOverride(ON_DimStyle::FieldFromUnsigned(i), property_override_bool[i]);
      }
    }

    // The reading below calls some Set functions which may change the m_field_override_parent_* values.
    // Save what came from the archive so we can restore it.
    archive_field_override_parent_count = m_field_override_parent_count;
    archive_field_override_parent_bits0 = m_field_override_parent_bits0;
    archive_field_override_parent_bits1 = m_field_override_parent_bits1;
    archive_field_override_parent_bits2 = m_field_override_parent_bits2;
    archive_field_override_parent_bits3 = m_field_override_parent_bits3;
    
    u = static_cast<unsigned char>(m_tolerance_format);
    if (!file.ReadInt(&u)) break;
    m_tolerance_format = ON_DimStyle::ToleranceFormatFromUnsigned(u);

    if (!file.ReadInt(&m_tolerance_resolution)) break;
    if (!file.ReadDouble(&m_tolerance_upper_value)) break;   // or both upper and lower in symmetrical style
    if (!file.ReadDouble(&m_tolerance_lower_value)) break;
    if (!file.ReadDouble(&m_tolerance_height_scale)) break;  // relative to the main dimension text

    if (!file.ReadDouble(&m_baseline_spacing)) break;

    // The text mask settings used to be a collection of several member variables
    // on ON_DimStyle and are now in an ON_TextMask class and a m_text_mask on ON_DimStyle.
    // These values are written here so the file format is not broken and 
    // older versions of Rhino can read newer file.
    bool b = DrawTextMask();
    if (!file.ReadBool(&b)) break;
    SetDrawTextMask(b);
    u = (unsigned int)(static_cast<unsigned char>(MaskFillType()));
    if (!file.ReadInt(&u)) break;
    SetMaskFillType(ON_TextMask::MaskTypeFromUnsigned(u));
    ON_Color c = MaskColor();
    if (!file.ReadColor(c)) break;
    SetMaskColor(c);

    double dimscale = DimScale();
    if (!file.ReadDouble(&dimscale)) break;
    if ( dimscale > 0.0 && dimscale != DimScale() )
      SetDimScale(dimscale);
    if (!file.ReadInt(&m_dimscale_source)) break;

    if (!file.ReadUuid(m_source_dimstyle)) break;
    if (!file.ReadChar(&m_ext_line_color_source)) break;
    if (!file.ReadChar(&m_dim_line_color_source)) break;
    if (!file.ReadChar(&m_arrow_color_source)) break;
    if (!file.ReadChar(&m_text_color_source)) break;
    if (!file.ReadColor(m_ext_line_color)) break;
    if (!file.ReadColor(m_dim_line_color)) break;
    if (!file.ReadColor(m_arrow_color)) break;
    if (!file.ReadColor(m_text_color)) break;
    if (!file.ReadChar(&m_ext_line_plot_color_source)) break;
    if (!file.ReadChar(&m_dim_line_plot_color_source)) break;
    if (!file.ReadChar(&m_arrow_plot_color_source)) break;
    if (!file.ReadChar(&m_text_plot_color_source)) break;
    if (!file.ReadColor(m_ext_line_plot_color)) break;
    if (!file.ReadColor(m_dim_line_plot_color)) break;
    if (!file.ReadColor(m_arrow_plot_color)) break;
    if (!file.ReadColor(m_text_plot_color)) break;
    if (!file.ReadChar(&m_ext_line_plot_weight_source)) break;
    if (!file.ReadChar(&m_dim_line_plot_weight_source)) break;
    if (!file.ReadDouble(&m_ext_line_plot_weight_mm)) break;
    if (!file.ReadDouble(&m_dim_line_plot_weight_mm)) break;

    if (!file.ReadDouble(&m_fixed_extension_len)) break;
    if (!file.ReadBool(&m_fixed_extension_len_on)) break;

    if (!file.ReadDouble(&m_text_rotation)) break;
    if (!file.ReadInt(&m_alternate_tolerance_resolution)) break;
    if (!file.ReadDouble(&m_tol_textheight_fraction)) break;

    if (!file.ReadBool(&m_suppress_arrow1)) break;
    if (!file.ReadBool(&m_suppress_arrow2)) break;
    if (!file.ReadInt(&m_textmove_leader)) break;
    if (!file.ReadInt(&m_arclength_sym)) break;
    if (!file.ReadDouble(&m_stack_textheight_fraction)) break;

    u = static_cast<unsigned char>(m_stack_format);
    if (!file.ReadInt(&u)) break;
    m_stack_format = ON_DimStyle::StackFormatFromUnsigned(u);

    if (!file.ReadDouble(&m_alt_round)) break;
    if (!file.ReadDouble(&m_round)) break;
    if (!file.ReadDouble(&m_angular_round)) break;

    u = static_cast<unsigned char>(m_alt_zero_suppress);
    if (!file.ReadInt(&u)) break;
    m_alt_zero_suppress = ON_DimStyle::ZeroSuppressFromUnsigned(u);

    u = 0;
    if (!file.ReadInt(&u)) break; // read obsolete value and throw it away
    // OBSOLETE // m_tol_zero_suppress = ON_DimStyle::ZeroSuppressFromUnsigned(u);

    u = static_cast<unsigned char>(m_zero_suppress);
    if (!file.ReadInt(&u)) break;
    m_zero_suppress = ON_DimStyle::ZeroSuppressFromUnsigned(u);

    u = static_cast<unsigned char>(m_ang_zero_suppress);
    if (!file.ReadInt(&u)) break;
    m_ang_zero_suppress = ON_DimStyle::ZeroSuppressFromUnsigned(u);

    if (!file.ReadBool(&m_alt_below)) break;

    // true: display alternate text after main text
    u = static_cast<unsigned int>(m_arrow_type_1);
    if (!file.ReadInt(&u)) break;
    m_arrow_type_1 = ON_Arrowhead::ArrowTypeFromUnsigned(u);

    u = static_cast<unsigned int>(m_arrow_type_2);
    if (!file.ReadInt(&u)) break;
    m_arrow_type_2 = ON_Arrowhead::ArrowTypeFromUnsigned(u);

    u = static_cast<unsigned int>(m_leader_arrow_type);
    if (!file.ReadInt(&u)) break;
    m_leader_arrow_type = ON_Arrowhead::ArrowTypeFromUnsigned(u);

    if (minor_version <= 0)
    {
      // old files do not contain unit system information
      if (false == UnitSystemIsSet())
        SetUnitSystemFromContext(true,file.Archive3dmSettings().m_ModelUnitsAndTolerances.m_unit_system.UnitSystem(),ON::LengthUnitSystem::Unset);

      if (60 == file.Archive3dmVersion() && file.ArchiveOpenNURBSVersion() <= 2348833437)
      {
        // Dale Lear April 8, 2016 
        //  working on http://mcneel.myjetbrains.com/youtrack/issue/RH-31796
        //
        //   It appears that when this code got changed from something that
        //   read 16 bytes to something that read 3 uuids, the chunk's
        //   minor version number was not increased and no provision was
        //   made to read files that had the the 16 bytes.
        //
        //   Unfortunately, there are files that do not contain 3 uuids and do
        //   contain 16 bytes and these files need to be read.
        //
        //   The file "layer_test.3dm" written by a Windows Rhino WIP built on October 21, 2015
        //   is an example. This file contains everything up to the m_leader_arrow_type unsigned int
        //   but does not contain these uuids. 
        //
        //   The version of opennurbs that wrote that file was 2348833437. So,
        //   I have to add this check and stop reading here to permit files 
        //   written before the the date the m_arrow_block_id_1 IO code was shipped (date unknown)
        //   to read. We know this date is sometime after October 21, 2015 and some version
        //   of opennurbs after version 2348833437.
        rc = true;
        break;
      }
    }

    if (!file.ReadUuid(m_arrow_block_id_1)) break;
    if (!file.ReadUuid(m_arrow_block_id_2)) break;
    if (!file.ReadUuid(m_leader_arrow_block_id)) break;
    // End of version chunk 1.0 fields (in most cases)

    if (minor_version <= 0)
    {
      rc = true;
      break;
    }

    // June 10, 2016
    // http://mcneel.myjetbrains.com/youtrack/issue/RH-33795
    // chunk version 1.1 information added

    // BEGIN chunk version 1.1 information

    // OBSOLETE leader content type
    u = 0;
    if (!file.ReadInt(&u)) break;

    u = 0;
    if (!file.ReadInt(&u)) break;
    ON_INTERNAL_OBSOLETE::V5_vertical_alignment obsolete_text_valign = ON_INTERNAL_OBSOLETE::V5VerticalAlignmentFromUnsigned(u);
    m_text_vertical_alignment = ON_INTERNAL_OBSOLETE::V6VerticalAlignmentFromV5VerticalAlignment(obsolete_text_valign);

    u = 0;
    if (!file.ReadInt(&u)) break;
    ON_INTERNAL_OBSOLETE::V5_vertical_alignment obsolete_leader_valign = ON_INTERNAL_OBSOLETE::V5VerticalAlignmentFromUnsigned(u);
    m_leader_text_vertical_alignment = ON_INTERNAL_OBSOLETE::V6VerticalAlignmentFromV5VerticalAlignment(obsolete_leader_valign);

    u = static_cast<unsigned int>(m_leader_content_angle_style);
    if (!file.ReadInt(&u)) break;
    m_leader_content_angle_style = ContentAngleStyleFromUnsigned(u);

    u = static_cast<unsigned int>(m_leader_curve_type);
    if (!file.ReadInt(&u)) break;
    m_leader_curve_type = LeaderCurveTypeFromUnsigned(u);

    if (!file.ReadDouble(&m_leader_content_angle)) break;
    if (!file.ReadBool(&m_leader_has_landing)) break;
    if (!file.ReadDouble(&m_leader_landing_length)) break;
    
    u = 0;
    if (!file.ReadInt(&u)) break;
    ON_INTERNAL_OBSOLETE::V5_horizontal_alignment obsolete_text_halign = ON_INTERNAL_OBSOLETE::V5HorizontalAlignmentFromUnsigned(u);
    m_text_horizontal_alignment = ON_INTERNAL_OBSOLETE::V6HorizontalAlignmentFromV5HorizontalAlignment(obsolete_text_halign);

    u = 0;
    if (!file.ReadInt(&u)) break;
    ON_INTERNAL_OBSOLETE::V5_horizontal_alignment obsolete_leader_halign = ON_INTERNAL_OBSOLETE::V5HorizontalAlignmentFromUnsigned(u);
    m_leader_text_horizontal_alignment = ON_INTERNAL_OBSOLETE::V6HorizontalAlignmentFromV5HorizontalAlignment(obsolete_leader_halign);

    if (!file.ReadBool(&m_draw_forward)) break;
    if (!file.ReadBool(&m_signed_ordinate)) break;

    if (!m_scale_value.Read(file)) break;

    u = static_cast<unsigned int>(this->UnitSystem());
    if (!file.ReadInt(&u)) break;
    m_dimstyle_unitsystem = ON::LengthUnitSystemFromUnsigned(u);
    if (ON::LengthUnitSystem::Unset == m_dimstyle_unitsystem || ON::LengthUnitSystem::CustomUnits == m_dimstyle_unitsystem)
      m_dimstyle_unitsystem = ON::LengthUnitSystem::None;
    
    // END chunk version 1.1 information
    if (minor_version <= 1)
    {
      rc = true;
      break;
    }

    // August 2016 - added m_font_characteristics
    if (!m_font_characteristics.Read(file)) break;
    m_managed_font = m_font_characteristics.ManagedFont();

    // END chunk version 1.2 information
    if (minor_version <= 2)
    {
      rc = true;
      break;
    }

    if (!m_text_mask.Read(file)) break;

    // END chunk version 1.3 information
    if (minor_version <= 3)
    {
      rc = true;
      break;
    }

    // Feb 2017 added enum values
    u = static_cast<unsigned int>(m_dim_text_location);
    if (!file.ReadInt(&u)) break;
    m_dim_text_location = ON_DimStyle::TextLocationFromUnsigned(u);

    u = static_cast<unsigned int>(m_dimradial_text_location);
    if (!file.ReadInt(&u)) break;
    m_dimradial_text_location = ON_DimStyle::TextLocationFromUnsigned(u);


    u = static_cast<unsigned int>(m_text_vertical_alignment);
    if (!file.ReadInt(&u)) break;
    m_text_vertical_alignment = ON::TextVerticalAlignmentFromUnsigned(u);

    u = static_cast<unsigned int>(m_text_horizontal_alignment);
    if (!file.ReadInt(&u)) break;
    m_text_horizontal_alignment = ON::TextHorizontalAlignmentFromUnsigned(u);

    u = static_cast<unsigned int>(m_leader_text_vertical_alignment);
    if (!file.ReadInt(&u)) break;
    m_leader_text_vertical_alignment = ON::TextVerticalAlignmentFromUnsigned(u);

    u = static_cast<unsigned int>(m_leader_text_horizontal_alignment);
    if (!file.ReadInt(&u)) break;
    m_leader_text_horizontal_alignment = ON::TextHorizontalAlignmentFromUnsigned(u);

    u = static_cast<unsigned int>(m_text_orientation);
    if (!file.ReadInt(&u)) break;
    m_text_orientation = ON::TextOrientationFromUnsigned(u);

    u = static_cast<unsigned int>(m_leader_text_orientation);
    if (!file.ReadInt(&u)) break;
    m_leader_text_orientation = ON::TextOrientationFromUnsigned(u);

    u = static_cast<unsigned int>(m_dim_text_orientation);
    if (!file.ReadInt(&u)) break;
    m_dim_text_orientation = ON::TextOrientationFromUnsigned(u);

    u = static_cast<unsigned int>(m_dimradial_text_orientation);
    if (!file.ReadInt(&u)) break;
    m_dimradial_text_orientation = ON::TextOrientationFromUnsigned(u);

    u = static_cast<unsigned int>(m_dim_text_angle_style);
    if (!file.ReadInt(&u)) break;
    m_dim_text_angle_style = ON_DimStyle::ContentAngleStyleFromUnsigned(u);

    u = static_cast<unsigned int>(m_dimradial_text_angle_style);
    if (!file.ReadInt(&u)) break;
    m_dimradial_text_angle_style = ON_DimStyle::ContentAngleStyleFromUnsigned(u);

    if (!file.ReadBool(&m_text_underlined)) break;

    // END chunk version 1.4 information
    if (minor_version <= 4)
    {
      rc = true;
      break;
    }
    // June 16, 2017 chunk 1.5 information
    // added m_dimension_unitsystem and m_alt_dimension_unitsystem 

    //ON::LengthUnitSystem obsolete_dim_length_us = ON::LengthUnitSystem::None;
    //u = static_cast<unsigned int>(obsolete_dim_length_us);
    u = 0;
    if (!file.ReadInt(&u)) break;
    //obsolete_dim_length_us = ON::LengthUnitSystemFromUnsigned(u);


    //ON::LengthUnitSystem obsolete_alt_dim_length_us = ON::LengthUnitSystem::None;
    //u = static_cast<unsigned int>(obsolete_alt_dim_length_us);
    u = 0;
    if (!file.ReadInt(&u)) break;
    //obsolete_alt_dim_length_us = ON::LengthUnitSystemFromUnsigned(u);

    // END chunk version 1.5 information
    if (minor_version <= 5)
    {
      rc = true;
      break;
    }
    u = static_cast<unsigned int>(m_dimension_length_display);
    if (!file.ReadInt(&u)) break;
    m_dimension_length_display = ON_DimStyle::LengthDisplayFromUnsigned(u);
    
    u = static_cast<unsigned int>(m_dimension_length_display);
    if (!file.ReadInt(&u)) break;
    m_alternate_dimension_length_display = ON_DimStyle::LengthDisplayFromUnsigned(u);
    // END chunk version 1.6 information
    if (minor_version <= 6)
    {
      rc = true;
      break;
    }

    u = static_cast<unsigned int>(m_centermark_style);
    if (!file.ReadInt(&u)) break;
    m_centermark_style = ON_DimStyle::CentermarkStyleFromUnsigned(u);
    // END chunk version 1.7 information

    if (minor_version <= 7)
    {
      rc = true;
      break;
    }

    if (!file.ReadBool(&m_bForceDimLine)) break;

    u = static_cast<unsigned int>(m_TextFit);
    if (!file.ReadInt(&u)) break;
    m_TextFit = ON_DimStyle::TextFitFromUnsigned(u);

    u = static_cast<unsigned int>(m_ArrowFit);
    if (!file.ReadInt(&u)) break;
    m_ArrowFit = ON_DimStyle::ArrowFitFromUnsigned(u);
    // END chunk version 1.8 information

    if (minor_version <= 8)
    {
      rc = true;
      break;
    }
    u = static_cast<unsigned int>(m_decimal_separator);
    if (!file.ReadInt(&u)) break;
    m_decimal_separator = (wchar_t)u;
    // END chunk version 1.9 information

    rc = true;
    break;
  }
  // Dale Lear April 8, 2016 
  //  working on http://mcneel.myjetbrains.com/youtrack/issue/RH-31796
  //  bSupressPartiallyReadChunkWarning suppresses a partially read chunk warning
  //  of skipping 16 bytes.

  const bool bSupressPartiallyReadChunkWarning
    = 60 == file.Archive3dmVersion()
    && file.ArchiveOpenNURBSVersion() <= 2348833437
    && 1 == major_version
    && 0 == minor_version
    ;
  if (!file.EndRead3dmChunk(bSupressPartiallyReadChunkWarning))
    rc = false;

  if (nullptr == m_managed_font)
  {
    m_font_characteristics = ON_Font::Default;
    m_managed_font = &ON_Font::Default;
  }

  // Make sure zero suppression settings are valid
  if (false == ON_DimStyle::ZeroSuppressMatchesLengthDisplay(m_zero_suppress, m_dimension_length_display ))
    m_zero_suppress = ON_DimStyle::suppress_zero::None;

  if (false == ON_DimStyle::ZeroSuppressMatchesLengthDisplay(m_alt_zero_suppress, m_alternate_dimension_length_display))
    m_alt_zero_suppress = ON_DimStyle::suppress_zero::None;

  // Any decimal format will work to test m_ang_zero_suppress.
  if (false == ON_DimStyle::ZeroSuppressMatchesLengthDisplay(m_ang_zero_suppress, ON_DimStyle::LengthDisplay::ModelUnits))
    m_ang_zero_suppress = ON_DimStyle::suppress_zero::None;

  m_field_override_parent_count = archive_field_override_parent_count;
  m_field_override_parent_bits0 = archive_field_override_parent_bits0;
  m_field_override_parent_bits1 = archive_field_override_parent_bits1;
  m_field_override_parent_bits2 = archive_field_override_parent_bits2;
  m_field_override_parent_bits3 = archive_field_override_parent_bits3;
  
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

void ON_DimStyle::Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field field_id)
{
  // When a dimstyle is an override candidate, any call to a Set...() function sets that field as overridden.
  if (this->IsOverrideDimStyleCandidate(ParentId(), false))
    this->SetFieldOverride(field_id, true);
}

bool ON_DimStyle::Internal_SetBoolMember(
  ON_DimStyle::field field_id,
  bool value,
  bool& class_member
)
{
  bool bValueChanged = false;
  const bool b = value ? true : false;
  if (b != class_member)
  {
    class_member = b;
    Internal_ContentChange();
    bValueChanged = true;
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(field_id);
  return bValueChanged;
}

bool ON_DimStyle::Internal_SetUnsignedCharMember(
  ON_DimStyle::field field_id,
  unsigned char value,
  unsigned char& class_member
)
{
  bool bValueChanged = false;
  if (value != class_member)
  {
    class_member = value;
    Internal_ContentChange();
    bValueChanged = true;
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(field_id);
  return bValueChanged;
}

bool ON_DimStyle::Internal_SetIntMember(
  ON_DimStyle::field field_id,
  int value,
  int& class_member
)
{
  bool bValueChanged = false;
  if (value != class_member)
  {
    class_member = value;
    Internal_ContentChange();
    bValueChanged = true;
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(field_id);
  return bValueChanged;
}


bool ON_DimStyle::Internal_SetColorMember(
  ON_DimStyle::field field_id,
  ON_Color value,
  ON_Color& class_member
)
{
  bool bValueChanged = false;
  if (value != class_member)
  {
    class_member = value;
    Internal_ContentChange();
    bValueChanged = true;
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(field_id);
  return bValueChanged;
}

bool ON_DimStyle::Internal_SetDoubleMember(
  ON_DimStyle::field field_id,
  double value,
  double& class_member
)
{
  bool bValueChanged = false;
  if (ON_IsValid(value))
  {
    // !(value == class_member) is used instead of (value != class_member)
    // so that when class_member = NaN, its value can be changed.
    if ( !(value == class_member) )
    {
      class_member = value;
      Internal_ContentChange();
      bValueChanged = true;
    }
    Internal_SetOverrideDimStyleCandidateFieldOverride(field_id);
  }
  return bValueChanged;
}

bool ON_DimStyle::Internal_SetIdMember(
  ON_DimStyle::field field_id,
  ON_UUID value,
  ON_UUID& class_member
)
{
  bool bValueChanged = false;
  if (value != class_member)
  {
    class_member = value;
    Internal_ContentChange();
    bValueChanged = true;
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(field_id);
  return bValueChanged;
}

bool ON_DimStyle::Internal_SetStringMember(
  ON_DimStyle::field field_id,
  const wchar_t* value,
  ON_wString& class_member
)
{
  if (false == class_member.IsValid(true))
  {
    // just in case value pointed to the bogus string array.
    value = L"";
  }
  bool bValueChanged = false;
  if (false == class_member.EqualOrdinal(value,false) )
  {
    class_member = value;
    Internal_ContentChange();
    bValueChanged = true;
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(field_id);
  return bValueChanged;
}


double ON_DimStyle::ExtExtension() const
{
  return m_extextension;
}

void ON_DimStyle::SetExtExtension(const double e)
{
  double x = fabs(e);
  Internal_SetDoubleMember(ON_DimStyle::field::ExtensionLineExtension, x, m_extextension);
}

double ON_DimStyle::ExtOffset() const
{
  return m_extoffset;
}

void ON_DimStyle::SetExtOffset(const double e)
{
  Internal_SetDoubleMember(ON_DimStyle::field::ExtensionLineOffset, e, m_extoffset);
}

double ON_DimStyle::ArrowSize() const
{
  return m_arrowsize;
}

void ON_DimStyle::SetArrowSize(const double e)
{
  Internal_SetDoubleMember(ON_DimStyle::field::Arrowsize, e, m_arrowsize);
}

double ON_DimStyle::LeaderArrowSize() const
{
  return m_leaderarrowsize;
}

void ON_DimStyle::SetLeaderArrowSize(const double e)
{
  Internal_SetDoubleMember( ON_DimStyle::field::LeaderArrowsize, e, m_leaderarrowsize);
}

double ON_DimStyle::CenterMark() const
{
  return m_centermark;
}

void ON_DimStyle::SetCenterMark(const double e)
{
  Internal_SetDoubleMember(ON_DimStyle::field::Centermark, e, m_centermark);
}

ON_DimStyle::centermark_style ON_DimStyle::CenterMarkStyle() const
{
  return m_centermark_style;
}

void ON_DimStyle::SetCenterMarkStyle(ON_DimStyle::centermark_style style)
{
  if (m_centermark_style != style)
  {
    m_centermark_style = style;
    Internal_ContentChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::CentermarkStyle);
}

ON_DimStyle::TextLocation ON_DimStyle::DimTextLocation() const
{
  return m_dim_text_location;
}

void ON_DimStyle::SetDimTextLocation(ON_DimStyle::TextLocation a)
{
  if (m_dim_text_location != a)
  {
    m_dim_text_location = a;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::DimTextLocation);
}


ON_DimStyle::TextLocation ON_DimStyle::DimRadialTextLocation() const
{
  return m_dimradial_text_location;
}

void ON_DimStyle::SetDimRadialTextLocation(ON_DimStyle::TextLocation a)
{
  if (m_dimradial_text_location != a)
  {
    m_dimradial_text_location = a;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::DimRadialTextLocation);
}

ON_DimStyle::angle_format ON_DimStyle::AngleFormat() const
{
  return m_angleformat;
}

void ON_DimStyle::SetAngleFormat(ON_DimStyle::angle_format f)
{
  if (m_angleformat != f)
  {
    m_angleformat = f;
    Internal_ContentChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::AngleFormat);
}

int ON_DimStyle::LengthResolution() const
{
  return m_lengthresolution;
}

void ON_DimStyle::SetLengthResolution(int r)
{
  if (r >= 0 && r < 16)
    Internal_SetIntMember(ON_DimStyle::field::LengthResolution, r, m_lengthresolution);
}

int ON_DimStyle::AngleResolution() const
{
  return m_angleresolution;
}

void ON_DimStyle::SetAngleResolution(int r)
{
  if (r >= 0 && r < 16)
    Internal_SetIntMember(ON_DimStyle::field::AngleResolution, r, m_angleresolution);
}

const ON_Font& ON_DimStyle::Font() const
{
  return (nullptr != m_managed_font) ? *m_managed_font : ON_Font::Default;
}

const ON_Font& ON_DimStyle::ParentDimStyleFont() const
{
  // If this dimstyle has a parent dimstyle and this dimstyle's font overrides the parent dimstyle's font,
  // then the parent dimstyle's font is returned. Otherwise this dimstyle's font is returned.
  return
    (nullptr != m_parent_dimstyle_managed_font && false == (ON_nil_uuid == ParentId()) && IsFieldOverride(ON_DimStyle::field::Font) ) 
    ? *m_parent_dimstyle_managed_font 
    : Font();
}

const bool ON_DimStyle::FontSubstituted() const
{
  return
    (nullptr == m_managed_font)
    || (0 != ON_Font::CompareFontCharacteristics(*m_managed_font, m_font_characteristics))
    || (m_managed_font->Description() != m_font_characteristics.Description())
    ;
}

const ON_Font& ON_DimStyle::FontCharacteristics() const
{
  return m_font_characteristics;
}

void ON_DimStyle::SetFont(
  const ON_Font& font_characteristics
)
{
  const ON_Font* managed_font = font_characteristics.ManagedFont();
  if (nullptr == managed_font)
  {
    ON_ERROR("ON_Font::GetManagedFont(font_characteristics) failed.");
    return;
  }

  const bool bManagedFontChanged = (m_managed_font != managed_font);

  const bool bFontChanged
    = bManagedFontChanged
    || (0 != ON_Font::CompareFontCharacteristics(font_characteristics, m_font_characteristics))
    || m_font_characteristics.Description() != font_characteristics.Description()
    ;

  // copy font_characteristics unconditionally in case compare missed some detail.
  m_font_characteristics = font_characteristics;

  if (bFontChanged)
  {
    m_managed_font = managed_font;
    Internal_TextPositionPropertiesChange();
  }

  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::Font);
}

ON_DimStyle* ON_DimStyle::CreateFromFont(
  const ON_Font* font_characteristics,
  double model_view_text_scale,
  const ON_DimStyle* dimstyle_settings,
  const class ON_ComponentManifest* manifest,
  ON_DimStyle* destination
)
{
  if (nullptr == font_characteristics)
    font_characteristics = &ON_Font::Default;

  if (nullptr == dimstyle_settings)
  {
    dimstyle_settings = &ON_DimStyle::Default;
  }
  if (nullptr == destination)
    destination = new ON_DimStyle(*dimstyle_settings);
  else 
  {
    if (destination != dimstyle_settings)
      *destination = *dimstyle_settings;
  }

  destination->ClearModelComponentAttributes(ON_ModelComponent::Attributes::AllAttributes);

  destination->SetFont(*font_characteristics);

  if ( model_view_text_scale > 0.0 && ON_IsValid(model_view_text_scale))
    destination->SetDimScale(model_view_text_scale);

  // Dale Lear RH-63824 May 3, 2021
  // It is critical that bIncludeNotOnDevice be set to false.
  // Otherwise missing fonts will have a description beginning with "[Not on device]"
  // and square brackets are not permitted in names.
  // This code is inventing a Rhino 6/7 dimstyle name from a V4 text style.
  // The text style names were unreliable in V4 and we've used the font
  // description as a proxy for years now.
  const bool bIncludeNotOnDevice = false;

  const ON_wString font_description = font_characteristics->Description(ON_Font::NameLocale::LocalizedFirst, ON_wString::HyphenMinus, ON_wString::Space, true, bIncludeNotOnDevice);
  if (font_description.IsNotEmpty())
  {
    const ON_wString name
      = (nullptr != manifest)
      ? manifest->UnusedName(ON_ModelComponent::Type::DimStyle, ON_nil_uuid, font_description, nullptr, nullptr, 0, nullptr)
      : font_description;
    destination->SetName(name);
  }

  // The calls to destination->SetFont() and destination->SetDimScale()
  // set the overrides.
  destination->ClearAllFieldOverrides();

  return destination;
}

const class ON_SHA1_Hash ON_DimStyle::TextPositionPropertiesHash() const
{
  // sha1 hash of properties that have any possible effect on annotation text appearance, size, shape
  if (m_text_position_properties_hash.IsEmptyContentHash())
  {
    ON_SHA1 sha1;
    
    const ON_SHA1_Hash font_hash
      = nullptr != m_managed_font
      ? m_managed_font->FontCharacteristicsHash()
      : m_font_characteristics.FontCharacteristicsHash();
    sha1.AccumulateSubHash(font_hash);
    sha1.AccumulateDouble(DimScale());
    sha1.AccumulateDouble(m_extextension);
    sha1.AccumulateDouble(m_extoffset);
    sha1.AccumulateDouble(m_textheight);
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_dim_text_location));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_dimradial_text_location));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_angleformat));

    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_dimension_length_display));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_alternate_dimension_length_display));

    sha1.AccumulateInteger32(m_angleresolution);
    sha1.AccumulateInteger32(m_lengthresolution);
    sha1.AccumulateDouble(m_lengthfactor);
    sha1.AccumulateBool(m_bAlternate);
    sha1.AccumulateDouble(m_alternate_lengthfactor);
    sha1.AccumulateInteger32(m_alternate_lengthresolution);

    m_prefix.IsValid(true);
    sha1.AccumulateString(m_prefix);

    m_suffix.IsValid(true);
    sha1.AccumulateString(m_suffix);

    m_alternate_prefix.IsValid(true);
    sha1.AccumulateString(m_alternate_prefix);

    m_alternate_suffix.IsValid(true);
    sha1.AccumulateString(m_alternate_suffix);

    sha1.AccumulateDouble(m_dimextension);
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_tolerance_format));
    sha1.AccumulateInteger32(m_tolerance_resolution);
    sha1.AccumulateDouble(m_tolerance_upper_value);
    sha1.AccumulateDouble(m_tolerance_lower_value);
    sha1.AccumulateDouble(m_tolerance_height_scale);
    sha1.AccumulateDouble(m_text_rotation);
    sha1.AccumulateInteger32(m_alternate_tolerance_resolution);
    sha1.AccumulateDouble(m_tol_textheight_fraction);
    sha1.AccumulateInteger32(m_textmove_leader);
    sha1.AccumulateInteger32(m_arclength_sym);
    sha1.AccumulateDouble(m_stack_textheight_fraction);
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_stack_format));
    sha1.AccumulateDouble(m_alt_round);
    sha1.AccumulateDouble(m_round);
    sha1.AccumulateDouble(m_angular_round);
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_alt_zero_suppress));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_zero_suppress));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_ang_zero_suppress));
    sha1.AccumulateBool(m_alt_below);
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_text_vertical_alignment));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_text_horizontal_alignment));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_leader_text_vertical_alignment));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_leader_text_horizontal_alignment));
    sha1.AccumulateDouble(m_scale_value.LeftToRightScale());

    sha1.AccumulateUnsigned32(static_cast<unsigned int>(this->UnitSystem()));

    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_text_orientation));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_leader_text_orientation));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_dim_text_orientation));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_dimradial_text_orientation));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_dim_text_angle_style));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_dimradial_text_angle_style));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_text_underlined));
    
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_ArrowFit));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_TextFit));

    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_decimal_separator));

    // Save hash in mutable m_text_position_properties_hash
    m_text_position_properties_hash = sha1.Hash();
  }
  return m_text_position_properties_hash;
}

const class ON_SHA1_Hash& ON_DimStyle::ContentHash() const
{
  if (m_content_hash.IsEmptyContentHash())
  {
    ON_SHA1 sha1;

    ON_SHA1_Hash text_position_hash = TextPositionPropertiesHash();
    sha1.AccumulateSubHash(text_position_hash);

    sha1.AccumulateDouble(m_arrowsize);
    sha1.AccumulateDouble(m_leaderarrowsize);
    sha1.AccumulateDouble(m_centermark);
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_centermark_style));
    sha1.AccumulateDouble(m_textgap);

    sha1.AccumulateBool(m_bSuppressExtension1);
    sha1.AccumulateBool(m_bSuppressExtension2);
    sha1.AccumulateUnsigned32(m_field_override_parent_count);
    sha1.AccumulateUnsigned32(m_field_override_parent_bits0);
    sha1.AccumulateUnsigned32(m_field_override_parent_bits1);
    sha1.AccumulateUnsigned32(m_field_override_parent_bits2);
    sha1.AccumulateUnsigned32(m_field_override_parent_bits3);

    sha1.AccumulateDouble(m_baseline_spacing);
    sha1.AccumulateSubHash(m_text_mask.ContentHash());
    sha1.AccumulateSubHash(m_scale_value.ContentHash());
    sha1.AccumulateInteger32(m_dimscale_source);
    sha1.AccumulateId(m_source_dimstyle);
    sha1.AccumulateUnsigned8(m_ext_line_color_source);
    sha1.AccumulateUnsigned8(m_dim_line_color_source);
    sha1.AccumulateUnsigned8(m_arrow_color_source);
    sha1.AccumulateUnsigned8(m_text_color_source);
    sha1.AccumulateUnsigned32(m_ext_line_color);
    sha1.AccumulateUnsigned32(m_dim_line_color);
    sha1.AccumulateUnsigned32(m_arrow_color);
    sha1.AccumulateUnsigned32(m_text_color);
    sha1.AccumulateUnsigned8(m_ext_line_plot_color_source);
    sha1.AccumulateUnsigned8(m_dim_line_plot_color_source);
    sha1.AccumulateUnsigned8(m_arrow_plot_color_source);
    sha1.AccumulateUnsigned8(m_text_plot_color_source);
    sha1.AccumulateUnsigned32(m_ext_line_plot_color);
    sha1.AccumulateUnsigned32(m_dim_line_plot_color);
    sha1.AccumulateUnsigned32(m_arrow_plot_color);
    sha1.AccumulateUnsigned32(m_text_plot_color);
    sha1.AccumulateUnsigned8(m_ext_line_plot_weight_source);
    sha1.AccumulateUnsigned8(m_dim_line_plot_weight_source);
    sha1.AccumulateDouble(m_ext_line_plot_weight_mm);
    sha1.AccumulateDouble(m_dim_line_plot_weight_mm);
    sha1.AccumulateDouble(m_fixed_extension_len);
    sha1.AccumulateBool(m_fixed_extension_len_on);

    sha1.AccumulateBool(m_suppress_arrow1);
    sha1.AccumulateBool(m_suppress_arrow2);

    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_arrow_type_1));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_arrow_type_2));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_leader_arrow_type));
    sha1.AccumulateId(m_arrow_block_id_1);
    sha1.AccumulateId(m_arrow_block_id_2);
    sha1.AccumulateId(m_leader_arrow_block_id);

    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_leader_content_angle_style));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_leader_curve_type));
    sha1.AccumulateDouble(m_leader_content_angle);
    sha1.AccumulateBool(m_leader_has_landing);

    sha1.AccumulateBool(m_draw_forward);
    sha1.AccumulateBool(m_signed_ordinate);

    sha1.AccumulateBool(static_cast<unsigned int>(m_bForceDimLine));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_ArrowFit));
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_TextFit));

    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_decimal_separator));

    // Save hash in mutable m_content_hash
    m_content_hash = sha1.Hash();
  }

  return m_content_hash;
}

void ON_DimStyle::Internal_TextPositionPropertiesChange()
{
  m_text_position_properties_hash = ON_SHA1_Hash::EmptyContentHash;
  Internal_ContentChange();
}

double ON_DimStyle::TextGap() const
{
  return m_textgap;
}

void ON_DimStyle::SetTextGap(double gap)
{
  if (gap >= 0.0)
    Internal_SetDoubleMember(ON_DimStyle::field::TextGap, gap, m_textgap);
}

double ON_DimStyle::TextHeight() const
{
  return m_textheight;
}

double ON_DimStyle::TextAdvanceOfCodePoint(unsigned unicode_code_point) const
{
  for (;;)
  {
    const double text_height = TextHeight();
    if (false == text_height > 0.0 && text_height < ON_UNSET_POSITIVE_VALUE)
      break;

    const ON_Font& font = Font();
    const ON_FontGlyph* glyph = font.CodePointGlyph(unicode_code_point);
    if (nullptr == glyph)
      break;

    const ON_TextBox font_unit_bbox = glyph->FontUnitGlyphBox();
    const ON_TextBox normalized_bbox = glyph->GlyphBox();

    const ON_FontMetrics& normalized_fm = font.FontMetrics();
    const ON_FontMetrics& font_unit_fm = font.FontUnitFontMetrics();

    const int normalized_cap_height = normalized_fm.AscentOfCapital();
    const int normalized_glyph_advance = normalized_bbox.m_advance.i; // positive even for fonts designed for R to L locales
    const int font_unit_cap_height = font_unit_fm.AscentOfCapital();
    const int font_unit_glyph_advance = font_unit_bbox.m_advance.i; // positive even for fonts designed for R to L locales
    
    const double normalized_scale = normalized_cap_height > 0 ? (((double)normalized_glyph_advance) / ((double)normalized_cap_height)) : 0.0;    
    const double font_unit_scale = font_unit_cap_height > 0 ? (((double)font_unit_glyph_advance) / ((double)font_unit_cap_height)) : 0.0;

    const double s = (font_unit_scale >= normalized_scale) ? font_unit_scale : normalized_scale;

    const double width_of_space = s * text_height;
    if (width_of_space > 0.0 && width_of_space < ON_UNSET_POSITIVE_VALUE)
      return width_of_space;

    break; // damaged or really odd font
  }

  return 0.0;
}

double ON_DimStyle::TextWidthOfEmSpace() const
{
  // This is the fundamental WidthOfXSpace() function.
  // Other WidthOfXSpace() functions call TextWidthOfEmSpace() when TextAdvanceOfCodePoint(obvious code point) fails.
  // This function may only call TextAdvanceOfCodePoint() and TextHeight().
  double w = TextAdvanceOfCodePoint(ON_UnicodeCodePoint::ON_EmSpace);
  if (false == w > 0.0)
  {
    w = TextAdvanceOfCodePoint('M');
    if (false == w > 0.0)
    {
      w = 2.0 * TextAdvanceOfCodePoint(ON_UnicodeCodePoint::ON_EnSpace);
      if (false == w > 0.0)
      {
        w = 2.0 * TextAdvanceOfCodePoint('N');
        if (false == w > 0.0)
        {
          w = 4.0 * TextAdvanceOfCodePoint(ON_UnicodeCodePoint::ON_Space);
          if (false == w > 0.0)
            w = 1.5 * TextHeight();
        }
      }
    }
  }
  return w;
}

double ON_DimStyle::TextWidthOfEnSpace() const
{
  double w = TextAdvanceOfCodePoint(ON_UnicodeCodePoint::ON_EnSpace);
  // Don't test 'N' in this function. 
  // It is critical that 2*TextWidthOfEnSpace() = TextWidthOfEmSpace()
  // unless the font designer explicitly deviated from this standard.
  return w > 0.0 ? w : 0.5 * TextWidthOfEmSpace();
}

double ON_DimStyle::TextWidthOfSpace() const
{
  double w = TextAdvanceOfCodePoint(ON_UnicodeCodePoint::ON_Space);
  return w > 0.0 ? w : 0.25 * TextWidthOfEmSpace();
}

double ON_DimStyle::TextWidthOfFigureSpace() const
{
  double w = TextAdvanceOfCodePoint(ON_UnicodeCodePoint::ON_FigureSpace);
  if (false == w > 0.0)
  {
    w = TextAdvanceOfCodePoint('0');
    if (false == w > 0.0)
      w = 0.55 * TextWidthOfEmSpace();
  }
  return w;
}

double ON_DimStyle::TextWidthOfIdeographicSpace() const
{
  double w = TextAdvanceOfCodePoint(ON_UnicodeCodePoint::ON_IdeographicSpace);
  return w > 0.0 ? w : TextWidthOfEmSpace();
}

double ON_DimStyle::TextWidthOfMediumMathematicalSpace() const
{
  double w = TextAdvanceOfCodePoint(ON_UnicodeCodePoint::ON_MediumMathematicalSpace);
  return w > 0.0 ? w : (2.0/9.0)*TextWidthOfEmSpace();
}

void ON_DimStyle::SetTextHeight(double height)
{
  if (ON_IsValid(height) && height > ON_SQRT_EPSILON)
  {
    if (Internal_SetDoubleMember(ON_DimStyle::field::TextHeight, height, m_textheight))
      Internal_TextPositionPropertiesChange();
  }
}

double ON_DimStyle::LengthFactor() const
{
  return m_lengthfactor;
}

void ON_DimStyle::SetLengthFactor(double factor)
{
  Internal_SetDoubleMember(ON_DimStyle::field::LengthFactor, factor, m_lengthfactor);
}

bool ON_DimStyle::Alternate() const
{
  return m_bAlternate;
}
void ON_DimStyle::SetAlternate(bool bAlternate)
{
  if ( Internal_SetBoolMember(ON_DimStyle::field::Alternate, bAlternate, m_bAlternate) )
    Internal_TextPositionPropertiesChange();
}

double ON_DimStyle::AlternateLengthFactor() const
{
  return m_alternate_lengthfactor;
}

void ON_DimStyle::SetAlternateLengthFactor(double factor)
{
  Internal_SetDoubleMember(ON_DimStyle::field::AlternateLengthFactor, factor, m_alternate_lengthfactor);
}

int ON_DimStyle::AlternateLengthResolution() const
{
  return m_alternate_lengthresolution;
}

void ON_DimStyle::SetAlternateLengthResolution(int resolution)
{
  Internal_SetIntMember(ON_DimStyle::field::AlternateLengthResolution, resolution, m_alternate_lengthresolution);
}

const ON_wString& ON_DimStyle::Prefix() const
{
  m_prefix.IsValid(true);
  return m_prefix;
}

void ON_DimStyle::SetPrefix(const wchar_t* prefix)
{
  Internal_SetStringMember(ON_DimStyle::field::Prefix, prefix, m_prefix);
}

const ON_wString& ON_DimStyle::Suffix() const
{
  m_suffix.IsValid(true);
  return m_suffix;
}

void ON_DimStyle::SetSuffix(const wchar_t* suffix)
{
  Internal_SetStringMember(ON_DimStyle::field::Suffix, suffix, m_suffix);
}

const ON_wString& ON_DimStyle::AlternatePrefix() const
{
  m_alternate_prefix.IsValid(true);
  return m_alternate_prefix;
}

void ON_DimStyle::SetAlternatePrefix(const wchar_t* prefix)
{
  Internal_SetStringMember(ON_DimStyle::field::AlternatePrefix, prefix, m_alternate_prefix);
}

const ON_wString& ON_DimStyle::AlternateSuffix() const
{
  m_alternate_suffix.IsValid(true);
  return m_alternate_suffix;
}

void ON_DimStyle::SetAlternateSuffix(const wchar_t* suffix)
{
  Internal_SetStringMember(ON_DimStyle::field::AlternateSuffix, suffix, m_alternate_suffix);
}

bool ON_DimStyle::SuppressExtension1() const
{
  return m_bSuppressExtension1;
}

void ON_DimStyle::SetSuppressExtension1(bool suppress)
{
  Internal_SetBoolMember(ON_DimStyle::field::SuppressExtension1, suppress, m_bSuppressExtension1);
}

bool ON_DimStyle::SuppressExtension2() const
{
  return m_bSuppressExtension2;
}

void ON_DimStyle::SetSuppressExtension2(bool suppress)
{
  Internal_SetBoolMember(ON_DimStyle::field::SuppressExtension2, suppress, m_bSuppressExtension2);
}

double ON_DimStyle::DimExtension() const
{
  return m_dimextension;
}

void ON_DimStyle::SetDimExtension(const double e)
{
  // Allow negative for hollow user arrows
  Internal_SetDoubleMember(ON_DimStyle::field::DimensionLineExtension, e, m_dimextension);
}

# pragma region SubObjectDisplay
void ON_DimStyle::SetExtensionLineColorSource(const ON::object_color_source src)
{
  Internal_SetUnsignedCharMember(ON_DimStyle::field::ExtLineColorSource, (unsigned char)src, m_ext_line_color_source);
}

ON::object_color_source ON_DimStyle::ExtensionLineColorSource() const
{
  return (ON::object_color_source)m_ext_line_color_source;
}
void ON_DimStyle::SetDimensionLineColorSource(const ON::object_color_source src)
{
  Internal_SetUnsignedCharMember(ON_DimStyle::field::DimLineColorSource, (unsigned char)src, m_dim_line_color_source);
}

ON::object_color_source ON_DimStyle::DimensionLineColorSource() const
{
  return (ON::object_color_source)m_dim_line_color_source;
}

void ON_DimStyle::SetArrowColorSource(const ON::object_color_source src)
{
  Internal_SetUnsignedCharMember(ON_DimStyle::field::ArrowColorSource, (unsigned char)src, m_arrow_color_source);
}

ON::object_color_source ON_DimStyle::ArrowColorSource() const
{
  return (ON::object_color_source)m_arrow_color_source;
}

void ON_DimStyle::SetTextColorSource(const ON::object_color_source src)
{
  Internal_SetUnsignedCharMember(ON_DimStyle::field::TextColorSource, (unsigned char)src, m_text_color_source);
}

ON::object_color_source ON_DimStyle::TextColorSource() const
{
  return (ON::object_color_source)m_text_color_source;
}

void ON_DimStyle::SetExtensionLineColor(ON_Color c)
{
  Internal_SetColorMember(ON_DimStyle::field::ExtLineColor, c, m_ext_line_color);
}

ON_Color ON_DimStyle::ExtensionLineColor() const
{
  return m_ext_line_color;
}

void ON_DimStyle::SetDimensionLineColor(ON_Color c)
{
  Internal_SetColorMember(ON_DimStyle::field::DimLineColor, c, m_dim_line_color);
}

ON_Color ON_DimStyle::DimensionLineColor() const
{
  return m_dim_line_color;
}

void ON_DimStyle::SetArrowColor(ON_Color c)
{
  Internal_SetColorMember(ON_DimStyle::field::ArrowColor, c, m_arrow_color);
}

ON_Color ON_DimStyle::ArrowColor() const
{
  return m_arrow_color;
}

void ON_DimStyle::SetTextColor(ON_Color c)
{
  Internal_SetColorMember(ON_DimStyle::field::TextColor, c, m_text_color);
}

ON_Color ON_DimStyle::TextColor() const
{
  return m_text_color;
}

void ON_DimStyle::SetExtensionLinePlotColorSource(const ON::plot_color_source src)
{
  Internal_SetUnsignedCharMember(ON_DimStyle::field::ExtLinePlotColorSource, (unsigned char)src, m_ext_line_plot_color_source);
}

ON::plot_color_source ON_DimStyle::ExtensionLinePlotColorSource() const
{
  return (ON::plot_color_source)m_ext_line_plot_color_source;
}

void ON_DimStyle::SetDimensionLinePlotColorSource(const ON::plot_color_source src)
{
  Internal_SetUnsignedCharMember(ON_DimStyle::field::DimLinePlotColorSource, (unsigned char)src,m_dim_line_plot_color_source);
}

ON::plot_color_source ON_DimStyle::DimensionLinePlotColorSource() const
{
  return (ON::plot_color_source)m_dim_line_plot_color_source;
}

void ON_DimStyle::SetArrowPlotColorSource(const ON::plot_color_source src)
{
  Internal_SetUnsignedCharMember(ON_DimStyle::field::ArrowPlotColorSource, (unsigned char)src,m_arrow_plot_color_source);
}

ON::plot_color_source ON_DimStyle::ArrowPlotColorSource() const
{
  return (ON::plot_color_source)m_arrow_plot_color_source;
}

void ON_DimStyle::SetTextPlotColorSource(const ON::object_color_source src)
{
  Internal_SetUnsignedCharMember(ON_DimStyle::field::TextPlotColorSource, (unsigned char)src,m_text_plot_color_source);
}

ON::object_color_source ON_DimStyle::TextPlotColorSource() const
{
  return (ON::object_color_source)m_text_plot_color_source;
}

void ON_DimStyle::SetExtensionLinePlotColor(ON_Color c)
{
  Internal_SetColorMember(ON_DimStyle::field::ExtLinePlotColor, c, m_ext_line_plot_color);
}

ON_Color ON_DimStyle::ExtensionLinePlotColor() const
{
  return m_ext_line_plot_color;
}

void ON_DimStyle::SetDimensionLinePlotColor(ON_Color c)
{
  Internal_SetColorMember(ON_DimStyle::field::DimLinePlotColor, c, m_dim_line_plot_color);
}

ON_Color ON_DimStyle::DimensionLinePlotColor() const
{
  return m_dim_line_plot_color;
}

void ON_DimStyle::SetArrowPlotColor(ON_Color c)
{
  Internal_SetColorMember(ON_DimStyle::field::ArrowPlotColor, c, m_arrow_plot_color);
}

ON_Color ON_DimStyle::ArrowPlotColor() const
{
  return m_arrow_plot_color;
}

void ON_DimStyle::SetTextPlotColor(ON_Color c)
{
  Internal_SetColorMember(ON_DimStyle::field::TextPlotColor, c, m_text_plot_color);
}

ON_Color ON_DimStyle::TextPlotColor() const
{
  return m_text_plot_color;
}

void ON_DimStyle::SetExtensionLinePlotWeightSource(const ON::plot_weight_source src)
{
  Internal_SetUnsignedCharMember(ON_DimStyle::field::ExtLinePlotWeightSource, (unsigned char)src, m_ext_line_plot_weight_source);
}

ON::plot_weight_source ON_DimStyle::ExtensionLinePlotWeightSource() const
{
  return (ON::plot_weight_source)m_ext_line_plot_weight_source;
}

void ON_DimStyle::SetDimensionLinePlotWeightSource(const ON::plot_weight_source src)
{
  Internal_SetUnsignedCharMember(ON_DimStyle::field::DimLinePlotWeightSource, (unsigned char)src, m_dim_line_plot_weight_source);
}

ON::plot_weight_source ON_DimStyle::DimensionLinePlotWeightSource() const
{
  return (ON::plot_weight_source)m_dim_line_plot_weight_source;
}

void ON_DimStyle::SetExtensionLinePlotWeight(double w)
{
  if (w >= 0.0)
    Internal_SetDoubleMember(ON_DimStyle::field::ExtLinePlotWeight_mm, w, m_ext_line_plot_weight_mm);
}

double ON_DimStyle::ExtensionLinePlotWeight() const
{
  return m_ext_line_plot_weight_mm;
}

void ON_DimStyle::SetDimensionLinePlotWeight(double w)
{
  if (w >= 0.0)
    Internal_SetDoubleMember(ON_DimStyle::field::DimLinePlotWeight_mm, w, m_dim_line_plot_weight_mm);
}

double ON_DimStyle::DimensionLinePlotWeight() const
{
  return m_dim_line_plot_weight_mm;
}
# pragma endregion SubObjectDisplay

void ON_DimStyle::SetFixedExtensionLen(double l)
{
  if (l >= 0.0)
    Internal_SetDoubleMember(ON_DimStyle::field::FixedExtensionLength, l, m_fixed_extension_len);
}

double ON_DimStyle::FixedExtensionLen() const
{
  return m_fixed_extension_len;
}

void ON_DimStyle::SetFixedExtensionLenOn(bool on)
{
  Internal_SetBoolMember(ON_DimStyle::field::FixedExtensionOn, on, m_fixed_extension_len_on);
}

bool ON_DimStyle::FixedExtensionLenOn() const
{
  return m_fixed_extension_len_on;
}

void ON_DimStyle::SetTextRotation(double r)
{
  Internal_SetDoubleMember(ON_DimStyle::field::TextRotation, r, m_text_rotation);
}

double ON_DimStyle::TextRotation() const
{
  return m_text_rotation;
}

void ON_DimStyle::SetAlternateToleranceResolution(int r)
{
  if (r >= 0)
    Internal_SetIntMember(ON_DimStyle::field::AltToleranceResolution, r, m_alternate_tolerance_resolution);
}

int ON_DimStyle::AlternateToleranceResolution() const
{
  return m_alternate_tolerance_resolution;
}

void ON_DimStyle::SetSuppressArrow1(bool s)
{
  Internal_SetBoolMember(ON_DimStyle::field::SuppressArrow1, s, m_suppress_arrow1);
}

bool ON_DimStyle::SuppressArrow1() const
{
  return m_suppress_arrow1;
}

void ON_DimStyle::SetSuppressArrow2(bool s)
{
  Internal_SetBoolMember(ON_DimStyle::field::SuppressArrow2, s, m_suppress_arrow2);
}

bool ON_DimStyle::SuppressArrow2() const
{
  return m_suppress_arrow2;
}

void ON_DimStyle::SetTextMoveLeader(int m)
{
  Internal_SetIntMember(ON_DimStyle::field::TextmoveLeader, m, m_textmove_leader);
}

int ON_DimStyle::TextMoveLeader() const
{
  return m_textmove_leader;
}

void ON_DimStyle::SetArcLengthSymbol(int m)
{
  Internal_SetIntMember(ON_DimStyle::field::ArclengthSymbol, m, m_arclength_sym);
}

int ON_DimStyle::ArcLengthSymbol() const
{
  return m_arclength_sym;
}

void ON_DimStyle::SetStackFractionFormat(ON_DimStyle::stack_format f)
{
  if (m_stack_format != f)
  {
    m_stack_format = f;
    Internal_ContentChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::StackFormat);
}

ON_DimStyle::stack_format ON_DimStyle::StackFractionFormat() const
{
  return m_stack_format;
}

void ON_DimStyle::SetStackHeightScale(double f)
{
  if (f > ON_SQRT_EPSILON)
    Internal_SetDoubleMember(ON_DimStyle::field::StackTextheightScale, f, m_stack_textheight_fraction);
}

double ON_DimStyle::StackHeightScale() const
{
  return m_stack_textheight_fraction;
}

void ON_DimStyle::SetRoundOff(double r)
{
  Internal_SetDoubleMember(ON_DimStyle::field::Round, r, m_round);
}

double ON_DimStyle::RoundOff() const
{
  return m_round;
}

void ON_DimStyle::SetAlternateRoundOff(double r)
{
  Internal_SetDoubleMember(ON_DimStyle::field::AltRound, r, m_alt_round);
}

double ON_DimStyle::AlternateRoundOff() const
{
  return m_alt_round;
}

void ON_DimStyle::SetAngleRoundOff(double r)
{
  Internal_SetDoubleMember(ON_DimStyle::field::AngularRound, r, m_angular_round);
}

double ON_DimStyle::AngleRoundOff() const
{
  return m_angular_round;
}

void ON_DimStyle::SetZeroSuppress(ON_DimStyle::suppress_zero s)
{
  if (m_zero_suppress != s)
  {
    if (ON_DimStyle::ZeroSuppressMatchesLengthDisplay(s, DimensionLengthDisplay()))
    {
      m_zero_suppress = s;
      Internal_ContentChange();
    }
    //else
    //{
    //  ON_ERROR("Attempting to set zero suppression to a value that doesn't match length display.");
    //}
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::ZeroSuppress);
}

ON_DimStyle::suppress_zero ON_DimStyle::ZeroSuppress() const
{
  return m_zero_suppress;
}

void ON_DimStyle::SetAlternateZeroSuppress(ON_DimStyle::suppress_zero s)
{
  if (m_alt_zero_suppress != s)
  {
    m_alt_zero_suppress = s;
    Internal_ContentChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::AltZeroSuppress);
}

ON_DimStyle::suppress_zero ON_DimStyle::AlternateZeroSuppress() const
{
  return m_alt_zero_suppress;
}

void ON_DimStyle::SetToleranceZeroSuppress(ON_DimStyle::suppress_zero s)
{
  // OBSOLETE PROPERTY
  // The ZeroSuppress() or  AlternateZeroSuppress() property
  // is used to format tolerance display.  ToleranceZeroSuppress() is ignored.
}

ON_DimStyle::suppress_zero ON_DimStyle::ToleranceZeroSuppress() const
{
  // OBSOLETE PROPERTY
  // The ZeroSuppress() or  AlternateZeroSuppress() property
  // is used to format tolerance display.  ToleranceZeroSuppress() is ignored.
  return ON_DimStyle::suppress_zero::None;
}

void ON_DimStyle::SetAngleZeroSuppress(ON_DimStyle::suppress_zero s)
{
  if (m_ang_zero_suppress != s)
  {
    m_ang_zero_suppress = s;
    Internal_ContentChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::AngleZeroSuppress);
}

ON_DimStyle::suppress_zero ON_DimStyle::AngleZeroSuppress() const
{
  return m_ang_zero_suppress;
}

void ON_DimStyle::SetAlternateBelow(bool below)
{
  Internal_SetBoolMember(ON_DimStyle::field::AltBelow, below, m_alt_below);
}

bool ON_DimStyle::AlternateBelow() const
{
  return m_alt_below;
}

void ON_DimStyle::SetArrowType1(ON_Arrowhead::arrow_type type)
{
  if (m_arrow_type_1 != type)
  {
    m_arrow_type_1 = type;
    Internal_ContentChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::ArrowType1);
}

ON_Arrowhead::arrow_type ON_DimStyle::ArrowType1() const
{
  return m_arrow_type_1;
}

void  ON_DimStyle::SetArrowType1And2(ON_Arrowhead::arrow_type type)
{
  SetArrowType1(type);
  SetArrowType2(type);
}


void ON_DimStyle::SetArrowType2(ON_Arrowhead::arrow_type type)
{
  if (m_arrow_type_2 != type)
  {
    m_arrow_type_2 = type;
    Internal_ContentChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::ArrowType2);
}

ON_Arrowhead::arrow_type ON_DimStyle::ArrowType2() const
{
  return m_arrow_type_2;
}

void ON_DimStyle::SetLeaderArrowType(ON_Arrowhead::arrow_type type)
{
  if (m_leader_arrow_type != type)
  {
    m_leader_arrow_type = type;
    Internal_ContentChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::LeaderArrowType);
}

ON_Arrowhead::arrow_type ON_DimStyle::LeaderArrowType() const
{
  return m_leader_arrow_type;
}

void ON_DimStyle::SetArrowBlockId1(ON_UUID id)
{
  Internal_SetIdMember(ON_DimStyle::field::ArrowBlockId1, id, m_arrow_block_id_1);
}

ON_UUID ON_DimStyle::ArrowBlockId1() const
{
  return m_arrow_block_id_1;
}

void ON_DimStyle::SetArrowBlockId2(ON_UUID id)
{
  Internal_SetIdMember(ON_DimStyle::field::ArrowBlockId2, id, m_arrow_block_id_2);
}

ON_UUID ON_DimStyle::ArrowBlockId2() const
{
  return m_arrow_block_id_2;
}

void ON_DimStyle::SetLeaderArrowBlockId(ON_UUID id)
{
  Internal_SetIdMember(ON_DimStyle::field::LeaderArrowBlock, id, m_leader_arrow_block_id);
}

ON_UUID ON_DimStyle::LeaderArrowBlockId() const
{
  return m_leader_arrow_block_id;
}

ON::TextVerticalAlignment ON_DimStyle::TextVerticalAlignment() const
{
  return m_text_vertical_alignment;
}

void ON_DimStyle::SetTextVerticalAlignment(ON::TextVerticalAlignment style)
{
  if (m_text_vertical_alignment != style)
  {
    m_text_vertical_alignment = style;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::TextVerticalAlignment);
}

ON::TextVerticalAlignment ON_DimStyle::LeaderTextVerticalAlignment() const
{
  return m_leader_text_vertical_alignment;
}

void ON_DimStyle::SetLeaderTextVerticalAlignment(ON::TextVerticalAlignment style)
{
  if (m_leader_text_vertical_alignment != style)
  {
    m_leader_text_vertical_alignment = style;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::LeaderTextVerticalAlignment);
}

ON_DimStyle::ContentAngleStyle ON_DimStyle::LeaderContentAngleStyle() const
{
  return m_leader_content_angle_style;
}

void ON_DimStyle::SetLeaderContentAngleStyle(ON_DimStyle::ContentAngleStyle alignment)
{
  if (m_leader_content_angle_style != alignment)
  {
    m_leader_content_angle_style = alignment;
    Internal_ContentChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::LeaderContentAngleStyle);
}

double ON_DimStyle::LeaderContentAngleRadians() const
{
  return m_leader_content_angle;
}

void ON_DimStyle::SetLeaderContentAngleRadians(double angle_radians)
{
  if (!(angle_radians >= -2.1*ON_PI && angle_radians <= 2.1*ON_PI))
  {
    ON_ERROR("Invalid angle_radians parameter in ON_DimStyle::SetContentAngle().");
    return;
  }
  
  // positive value so commpare function will work as expected.
  while (angle_radians < 0.0)
    angle_radians += 2.0*ON_PI;
  while (angle_radians >= 2.0*ON_PI)
    angle_radians -= 2.0*ON_PI;

  Internal_SetDoubleMember(ON_DimStyle::field::LeaderContentAngle, angle_radians, m_leader_content_angle);
}

double ON_DimStyle::LeaderContentAngleDegrees() const
{
  return LeaderContentAngleRadians() * ON_RADIANS_TO_DEGREES;
}

void ON_DimStyle::SetLeaderContentAngleDegrees(double angle_degrees)
{
  SetLeaderContentAngleRadians(angle_degrees * ON_DEGREES_TO_RADIANS);
}

ON_DimStyle::leader_curve_type ON_DimStyle::LeaderCurveType() const
{
  return m_leader_curve_type;
}

void ON_DimStyle::SetLeaderCurveType(ON_DimStyle::leader_curve_type type)
{
  if (m_leader_curve_type != type)
  {
    m_leader_curve_type = type;
    Internal_ContentChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::LeaderCurveType);
}

ON::TextHorizontalAlignment ON_DimStyle::LeaderTextHorizontalAlignment() const
{
  return m_leader_text_horizontal_alignment;
}

void ON_DimStyle::SetLeaderTextHorizontalAlignment(ON::TextHorizontalAlignment halign)
{
  if (m_leader_text_horizontal_alignment != halign)
  {
    m_leader_text_horizontal_alignment = halign;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::LeaderTextHorizontalAlignment);
}

ON::TextHorizontalAlignment ON_DimStyle::TextHorizontalAlignment() const
{
  return m_text_horizontal_alignment;
}

void ON_DimStyle::SetTextHorizontalAlignment(ON::TextHorizontalAlignment halign)
{
  if ( m_text_horizontal_alignment != halign )
  {
    m_text_horizontal_alignment = halign;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::TextHorizontalAlignment);
}

bool ON_DimStyle::DrawForward() const
{
  return m_draw_forward;
}

void ON_DimStyle::SetDrawForward(bool drawforward)
{
  if (m_draw_forward != drawforward)
  {
    m_draw_forward = drawforward;
    Internal_ContentChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::DrawForward);
}

bool ON_DimStyle::LeaderHasLanding() const
{
  return m_leader_has_landing;
}

void ON_DimStyle::SetLeaderHasLanding(bool landing)
{
  if (m_leader_has_landing != landing)
  {
    m_leader_has_landing = landing;
    Internal_ContentChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::LeaderHasLanding);
}

double ON_DimStyle::LeaderLandingLength() const
{
  return m_leader_landing_length;
}

void ON_DimStyle::SetLeaderLandingLength(double length)
{
  if (!(length > ON_UNSET_VALUE && length < ON_UNSET_POSITIVE_VALUE))
  {
    ON_ERROR("Invalid length parameter in ON_DimStyle::SetLandingLength().");
    return;
  }
  Internal_SetDoubleMember(ON_DimStyle::field::LeaderLandingLength, length, m_leader_landing_length);
}

bool ON_DimStyle::SignedOrdinate() const
{
  return m_signed_ordinate;
}

void ON_DimStyle::SetSignedOrdinate(bool allowsigned)
{
  Internal_SetBoolMember(ON_DimStyle::field::SignedOrdinate, allowsigned, m_signed_ordinate);
}

ON::LengthUnitSystem ON_DimStyle::UnitSystem() const
{
  /// NOTE WELL: A dimstyle unit system was added in V6, but has never been fully used.
  /// The idea was this would make it easier to figure out what text height/ arrow size, 
  /// ... actually meant. Especially in situations where model space and page space have
  /// different unit systems, and in more complex cases like text in instance definitions
  /// and inserting annotation from models with mismatched unit systems.
  /// It is used internally to get some scales properly set and use in limited
  /// merging contexts.
  ///   
  /// From a user's perspective, in Rhino 6 and Rhino 7 ON_DimStyle lengths like TextHeight(), ArrowSize(), ... 
  /// are with respect to the context the annotation resides in. For example, if TextHeight() = 3.5,
  /// model units = meters, page units = millimters, and DimScale() = 1, then 
  /// text created in model space will be 3.5 meters high and
  /// text created in page space will be 3.5 millimeters high.
  /// 
  /// Ideally, ON_DimStyle::UnitSystem() would specify the text height units 
  /// and ON_DimStyle::DimScale() could be adjusted as model space extents require.
  /// Text in instance definitions would have a well defined height and references
  /// to those instance definitions would display predictably in both model space and page space.

  // It is critical that this function never return Unset or CustomUnits.
  // returning None insures unknown scal values are 1 instead of ON_DBL_QNAN
  if (ON::LengthUnitSystem::Unset == m_dimstyle_unitsystem || ON::LengthUnitSystem::CustomUnits == m_dimstyle_unitsystem)
    return ON::LengthUnitSystem::None;

  return m_dimstyle_unitsystem;
}

void ON_DimStyle::SetUnitSystem(ON::LengthUnitSystem us)
{
  /// NOTE WELL: A dimstyle unit system was added in V6, but has never been fully used.
  /// The idea was this would make it easier to figure out what text height/ arrow size, 
  /// ... actually meant. Especially in situations where model space and page space have
  /// different unit systems, and in more complex cases like text in instance definitions
  /// and inserting annotation from models with mismatched unit systems.
  /// It is used internally to get some scales properly set and use in limited
  /// merging contexts.
  ///   
  /// From a user's perspective, in Rhino 6 and Rhino 7 ON_DimStyle lengths like TextHeight(), ArrowSize(), ... 
  /// are with respect to the context the annotation resides in. For example, if TextHeight() = 3.5,
  /// model units = meters, page units = millimeters, and DimScale() = 1, then
  /// text created in model space will be 3.5 meters high and
  /// text created in page space will be 3.5 millimeters high.
  /// 
  /// Ideally, ON_DimStyle::UnitSystem() would specify the text height units 
  /// and ON_DimStyle::DimScale() could be adjusted as model space extents require.
  /// Text in instance definitions would have a well defined height and references
  /// to those instance definitions would display predictably in both model space and page space.
  if (ON::LengthUnitSystem::CustomUnits == us || ON::LengthUnitSystem::Unset == us)
  {
    ON_ERROR("Annotation styles cannot have unset or custom length units.");
    us = ON::LengthUnitSystem::Millimeters; // Using None insures scale values are 1 instead of ON_DBL_QNAN
  }

  if (m_dimstyle_unitsystem != us)
  {
    m_dimstyle_unitsystem = us;
    Internal_ContentChange();
  }

  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::UnitSystem);
}

void ON_DimStyle::SetUnitSystemFromContext(
  bool bUseName,
  ON::LengthUnitSystem source_unit_system,
  ON::LengthUnitSystem destination_unit_system
)
{
  /// NOTE WELL: A dimstyle unit system was added in V6, but has never been fully used.
  /// The idea was this would make it easier to figure out what text height/ arrow size, 
  /// ... actually meant. Especially in situations where model space and page space have
  /// different unit systems, and in more complex cases like text in instance definitions
  /// and inserting annotation from models with mismatched unit systems.
  /// It is used internally to get some scales properly set and use in limited
  /// merging contexts.
  ///   
  /// From a user's perspective, in Rhino 6 and Rhino 7 ON_DimStyle lengths like TextHeight(), ArrowSize(), ... 
  /// are with respect to the context the annotation resides in. For example, if TextHeight() = 3.5,
  /// model units = meters, page units = millimeters, and DimScale() = 1, then
  /// text created in model space will be 3.5 meters high and
  /// text created in page space will be 3.5 millimeters high.
  /// 
  /// Ideally, ON_DimStyle::UnitSystem() would specify the text height units 
  /// and ON_DimStyle::DimScale() could be adjusted as model space extents require.
  /// Text in instance definitions would have a well defined height and references
  /// to those instance definitions would display predictably in both model space and page space.


  ON::LengthUnitSystem dim_style_units = ON::LengthUnitSystemFromUnsigned(static_cast<unsigned int>(UnitSystem()));

  switch (dim_style_units)
  {
    case ON::LengthUnitSystem::None:
    case ON::LengthUnitSystem::CustomUnits:
    case ON::LengthUnitSystem::Unset:
      dim_style_units = ON::LengthUnitSystem::None;
      break;
    default:
      break;
  }
  
  for (int pass = 0; pass < 3; pass++)
  {
    if (ON::LengthUnitSystem::None != dim_style_units)
      break;
    if (0 == pass && false == bUseName)
      continue;
    switch (pass)
    {
    case 0: // search dimstyle name for metric or United States customary unit system names
      {
        const ON_NameHash name_hash = NameHash();
        if (name_hash.IsValidAndNotEmpty())
        {
          const ON_DimStyle& from_name = ON_DimStyle::SystemDimstyleFromName(name_hash);
          if (name_hash == from_name.NameHash() && name_hash != ON_DimStyle::Default.NameHash())
          {
            dim_style_units = from_name.UnitSystem();
            continue;
          }
        }
    
        const ON_UUID id = Id();
        if (ON_nil_uuid != id )
        {
          const ON_DimStyle& from_id = ON_DimStyle::SystemDimstyleFromId(id);
          if (id == from_id.Id() && id != ON_DimStyle::Default.Id() )
          {
            dim_style_units = from_id.UnitSystem();
            continue;
          }
        }

        ON_wString dim_style_name = Name();
        dim_style_name.TrimLeftAndRight();
        dim_style_name.MakeLowerOrdinal();
        if (dim_style_name.IsEmpty())
          break;
        const int dim_style_name_length = dim_style_name.Length();
        if (dim_style_name_length <= 0)
          break;

        const size_t name_list_capacity = ON_LengthUnitName::GetLengthUnitNameList(0, nullptr);
        if (name_list_capacity <= 0)
          break;

        ON_SimpleArray<ON_LengthUnitName> name_list(name_list_capacity);
        name_list.SetCount((int)name_list_capacity);
        ON_LengthUnitName::GetLengthUnitNameList(name_list.UnsignedCount(), name_list.Array());
        
        for (unsigned int i = 0; i < name_list.UnsignedCount(); i++)
        {
          ON::LengthUnitSystem name_us = name_list[i].LengthUnit();
          if (false == ON::IsTerrestrialLengthUnit(name_us))
            continue;
          if (
            false == ON::IsMetricLengthUnit(name_us)
            && false == ON::IsUnitedStatesCustomaryLengthUnit(name_us) 
            )
            continue;
          ON_wString unit_name = name_list[i].LengthUnitName();
          unit_name.TrimLeftAndRight();
          unit_name.MakeLowerOrdinal();
          if (unit_name.IsEmpty())
            continue;
          const int name_length = unit_name.Length();
          if (name_length <= 0)
            continue;
          if (name_length > dim_style_name_length )
            continue;

          const wchar_t* s = static_cast<const wchar_t*>(dim_style_name);
          const wchar_t* s1 = s + dim_style_name_length - name_length;
          for (/*empty init*/; s <= s1; s++)
          {
            if (ON_wString::EqualOrdinal(static_cast<const wchar_t*>(unit_name), name_length, s, name_length, false))
            {
              if (ON::IsUnitedStatesCustomaryLengthUnit(name_us))
                dim_style_units = ON::LengthUnitSystem::Inches;
              else
                dim_style_units = ON::LengthUnitSystem::Millimeters;
              break;
            }
          }
          if (ON::LengthUnitSystem::None != dim_style_units)
            break;
        }
      }
      break;

    case 1:
    case 2:
      {
        const ON::LengthUnitSystem context_us
          = (1 == pass)
          ? source_unit_system
          : destination_unit_system;
        if (ON::IsUnitedStatesPrinterLengthUnit(context_us))
          dim_style_units = context_us;
        else if (ON::IsTerrestrialLengthUnit(context_us))
        {
          if (ON::IsUnitedStatesCustomaryLengthUnit(context_us))
            dim_style_units = ON::LengthUnitSystem::Inches;
          else if (ON::IsMetricLengthUnit(context_us))
            dim_style_units = ON::LengthUnitSystem::Millimeters;
        }
      }
      break;
    }
  }

  if (ON::LengthUnitSystem::None == dim_style_units)
    dim_style_units = ON::LengthUnitSystem::Millimeters;

  if( dim_style_units != UnitSystem() )
    SetUnitSystem(dim_style_units);

  return;
}

static bool Internal_IsUnsetDimstyleUnitSystem(
  ON::LengthUnitSystem us
)
{
  return (
    ON::LengthUnitSystem::Unset == us
    || ON::LengthUnitSystem::None == us
    || ON::LengthUnitSystem::CustomUnits == us
    );
}

bool ON_DimStyle::UnitSystemIsSet() const
{
  return false == Internal_IsUnsetDimstyleUnitSystem(this->UnitSystem());
}

void ON_DimStyle::SetDimScale(
  double left_val,
  ON::LengthUnitSystem left_us,
  double right_val,
  ON::LengthUnitSystem right_us)
{
  const unsigned int locale_id = 0; // Will result in current locale id being used
  //const double clean_format_tol = 0.0;


  const ON_LengthValue::StringFormat left_string_format
    = (left_us == ON::LengthUnitSystem::Inches)
    ? ON_LengthValue::StringFormat::CleanProperFraction
    : ON_LengthValue::StringFormat::CleanDecimal;
  ON_LengthValue lvl = ON_LengthValue::Create(left_val, left_us, locale_id, left_string_format);

  const ON_LengthValue::StringFormat right_string_format
    = (right_us == ON::LengthUnitSystem::Inches)
    ? ON_LengthValue::StringFormat::CleanProperFraction
    : ON_LengthValue::StringFormat::CleanDecimal;
  ON_LengthValue lvr = ON_LengthValue::Create(right_val, right_us, locale_id, right_string_format);

  const ON_ScaleValue::ScaleStringFormat fmt = ON_ScaleValue::ScaleStringFormat::None;
  ON_ScaleValue sv = ON_ScaleValue::Create(lvl, lvr, fmt);
  if (sv.IsSet())
  {
    ON_DimStyle::SetDimScale(sv);
  }
}

void ON_DimStyle::SetDimScale(double scale)
{
  if (ON_IsValid(scale) && 0.0 < scale)
  {
    ON_ScaleValue sv;
    const ON_ScaleValue::ScaleStringFormat fmt = ON_ScaleValue::ScaleStringFormat::None;
    const unsigned int locale_id = 0; // will result in using the current locale id
    const ON_LengthValue::StringFormat lv_fmt = ON_LengthValue::StringFormat::CleanDecimal;
    //const double lv_clean_tol = 0.0;

    ON_LengthValue left_lv; // unset
    ON_LengthValue right_lv;
    ON::LengthUnitSystem left_us = UnitSystem();
    ON::LengthUnitSystem right_us = UnitSystem();
    double left_val = 1.0;
    double right_val = 1.0;

    if (m_scale_value.IsSet())
    {
      left_lv = m_scale_value.LeftLengthValue();
      right_lv = m_scale_value.RightLengthValue();
    }
    if (left_lv.IsSet())
    {
      left_us = left_lv.LengthStringParseSettings().ContextLengthUnitSystem();
      left_val = left_lv.Length(left_us);
    }

    if (right_lv.IsSet())
    {
      right_us = right_lv.LengthStringParseSettings().ContextLengthUnitSystem();
      right_val = right_lv.Length(right_us);
    }

    double unit_scale = ON::UnitScale(right_us, left_us);
    right_val = scale * left_val / unit_scale;

    const ON_LengthValue scale_left_lv
      = ON_LengthValue::Create(left_val, left_us, locale_id, lv_fmt);

    const ON_LengthValue scale_right_lv
      = ON_LengthValue::Create(right_val, right_us, locale_id, lv_fmt);

    sv = ON_ScaleValue::Create(scale_left_lv, scale_right_lv, fmt);

    if (sv.IsSet())
      SetDimScale(sv);
  }
}


double ON_DimStyle::DimScale() const
{
  return m_scale_value.RightToLeftScale();
}

void ON_DimStyle::SetDimScale(ON_ScaleValue sv)
{
  if (0 != ON_ScaleValue::Compare(m_scale_value,sv))
  {
    Internal_ContentChange();
    Internal_TextPositionPropertiesChange();
  }
  m_scale_value = sv;
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::DimensionScale);
}

const ON_ScaleValue& ON_DimStyle::ScaleValue() const
{
  return m_scale_value;
}

double ON_DimStyle::ScaleLeftLength_mm() const
{
  double d = 1.0;
  const ON_LengthValue& lv = m_scale_value.LeftLengthValue();
  d = lv.Length(ON::LengthUnitSystem::Millimeters);
  return d;
}

double ON_DimStyle::ScaleRightLength_mm() const
{
  double d = 1.0;
  const ON_LengthValue& lv = m_scale_value.RightLengthValue();
  d = lv.Length(ON::LengthUnitSystem::Millimeters);
  return d;
}

void ON_DimStyle::SetTextOrientation(ON::TextOrientation orientation)
{
  if (m_text_orientation != orientation)
  {
    m_text_orientation = orientation;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::TextOrientation);
}

ON::TextOrientation ON_DimStyle::TextOrientation() const
{
  return m_text_orientation;
}

void ON_DimStyle::SetLeaderTextOrientation(ON::TextOrientation orientation)
{ 
  if (m_leader_text_orientation != orientation)
  {
    m_leader_text_orientation = orientation;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::LeaderTextOrientation);
}

ON::TextOrientation ON_DimStyle::LeaderTextOrientation() const
{
  return m_leader_text_orientation;
}

void ON_DimStyle::SetDimTextOrientation(ON::TextOrientation orientation)
{
  if (m_dim_text_orientation != orientation)
  {
    m_dim_text_orientation = orientation;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::DimTextOrientation);
}

ON::TextOrientation ON_DimStyle::DimTextOrientation() const
{
  return m_dim_text_orientation;
}

void ON_DimStyle::SetDimRadialTextOrientation(ON::TextOrientation orientation)
{
  if (m_dimradial_text_orientation != orientation)
  {
    m_dimradial_text_orientation = orientation;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::DimRadialTextOrientation);
}

ON::TextOrientation ON_DimStyle::DimRadialTextOrientation() const
{
  return m_dimradial_text_orientation;
}

void ON_DimStyle::SetDimTextAngleStyle(ON_DimStyle::ContentAngleStyle style)
{
  if (m_dim_text_angle_style != style)
  {
    m_dim_text_angle_style = style;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::DimTextAngleStyle);
}

ON_DimStyle::ContentAngleStyle ON_DimStyle::DimTextAngleStyle() const
{
  return m_dim_text_angle_style;
}

void ON_DimStyle::SetDimRadialTextAngleStyle(ON_DimStyle::ContentAngleStyle style)
{
  if (m_dimradial_text_angle_style != style)
  {
    m_dimradial_text_angle_style = style;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::DimRadialTextAngleStyle);
}

ON_DimStyle::ContentAngleStyle ON_DimStyle::DimRadialTextAngleStyle() const
{
  return m_dimradial_text_angle_style;
}

bool ON_DimStyle::TextUnderlined() const
{
  return m_text_underlined;
}

void ON_DimStyle::SetTextUnderlined(bool underlined)
{
  if (m_text_underlined != underlined)
  {
    m_text_underlined = underlined;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::TextUnderlined);
}

bool ON_DimStyle::ForceDimLine() const
{
  return m_bForceDimLine;
}
void ON_DimStyle::SetForceDimLine(bool forcedimline)
{
  if (m_bForceDimLine != forcedimline)
  {
    m_bForceDimLine = forcedimline;
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::ForceDimLine);
}

void ON_DimStyle::SetArrowFit(ON_DimStyle::arrow_fit arrowfit)
{
  if (m_ArrowFit != arrowfit)
  {
    m_ArrowFit = arrowfit;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::ArrowFit);
}

ON_DimStyle::arrow_fit ON_DimStyle::ArrowFit() const
{
  return m_ArrowFit;
}

void ON_DimStyle::SetTextFit(ON_DimStyle::text_fit textfit)
{
  if (m_TextFit != textfit)
  {
    m_TextFit = textfit;
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::TextFit);
}

ON_DimStyle::text_fit ON_DimStyle::TextFit() const
{
  return m_TextFit;
}

void ON_DimStyle::SetDecimalSeparator(wchar_t separator)
{
  if(separator == ON_wString::DecimalAsComma)
    m_decimal_separator = ON_wString::DecimalAsComma;
  else
    m_decimal_separator = ON_wString::DecimalAsPeriod;
}

wchar_t ON_DimStyle::DecimalSeparator() const 
{
  return m_decimal_separator;
}

ON__UINT32* ON_DimStyle::Internal_GetOverrideParentBit(ON_DimStyle::field field_id, ON__UINT32* mask) const
{
  unsigned int bitdex = 0;
  unsigned int i = static_cast<unsigned int>(field_id);
  if (i >= static_cast<unsigned int>(ON_DimStyle::field::Count))
  {
    ON_ERROR("Invalid field_id value.");
    return nullptr;
  }

  if (i <= static_cast<unsigned int>(ON_DimStyle::field::Index))
  {
    // query makes no sense for Unset, Name and Index
    // because these cannot be inherited from parent.
    // false is returned instead of the more accurate true
    // because that's the way this code has worked for years
    // and being accurate would cause bugs at this point.
    return nullptr; 
  }

  while (i >= 32 && bitdex < 4)
  {
    bitdex++;
    i -= 32;
  }
  *mask = (1 << i);

  const ON__UINT32* bits;
  if (0 == bitdex)
    bits = &m_field_override_parent_bits0;
  else if (1 == bitdex)
    bits = &m_field_override_parent_bits1;
  else if (2 == bitdex)
    bits = &m_field_override_parent_bits2;
  else if (3 == bitdex)
    bits = &m_field_override_parent_bits3;
  else
  {
    ON_ERROR("field_id too big - add another m_independent_of_parent_bitsN = 0 member.");
    bits = nullptr;
    *mask = 0;
  }

  return const_cast<ON__UINT32*>(bits);
}


bool ON_DimStyle::IsFieldOverride(ON_DimStyle::field field_id) const
{
  ON__UINT32 mask = 0;
  const ON__UINT32* bits
    = (m_field_override_parent_count > 0)
    ? Internal_GetOverrideParentBit(field_id, &mask)
    : nullptr;
  return (nullptr == bits) ? false : (0 != (*bits & mask));
}

void ON_DimStyle::SetFieldOverrideAll(bool bOverrideParent)
{
  if (false == bOverrideParent)
  {
    const bool bContentChange = (0 != m_field_override_parent_count);
    m_field_override_parent_count = 0;
    m_field_override_parent_bits0 = 0;
    m_field_override_parent_bits1 = 0;
    m_field_override_parent_bits2 = 0;
    m_field_override_parent_bits3 = 0;
    if (bContentChange)
      Internal_ContentChange();
  }
  else
  {
    const unsigned int field_id_count = static_cast<unsigned int>(ON_DimStyle::field::Count);
    for (
      unsigned int field_id = static_cast<unsigned int>(ON_DimStyle::field::Index) + 1;
      field_id < field_id_count;
      field_id++)
    {
      SetFieldOverride(ON_DimStyle::FieldFromUnsigned(field_id), true);
    }
  }
}

void ON_DimStyle::OverrideFieldsWithDifferentValues(
  const ON_DimStyle& source,
  const ON_DimStyle& parent
)
{
  if (source.ContentHash() == parent.ContentHash())
  {
    SetFieldOverrideAll(false);
  }
  else
  {
    SetFieldOverrideAll(true);
    // OverrideFields() will set to false any fields that have equal property values.
    OverrideFields(source, parent);
  }
}

void ON_DimStyle::SetFieldOverride(ON_DimStyle::field field_id, bool bOverrideParent)
{
  // Note well:
  //   The Name and Index properties cannot be inherited from a parent dimension style.
  if (
    static_cast<unsigned int>(field_id) > static_cast<unsigned int>(ON_DimStyle::field::Index)
    && static_cast<unsigned int>(field_id) < static_cast<unsigned int>(ON_DimStyle::field::Count)
    && (m_field_override_parent_count > 0 || bOverrideParent)
    )
  {
    ON__UINT32 mask = 0;
    ON__UINT32* bits = Internal_GetOverrideParentBit(field_id, &mask);
    if (nullptr != bits)
    {
      const ON__UINT32 bits0 = *bits;
      if (bOverrideParent)
      {
        // field_id bit = 1 indicates the field value is independent of the parent.
        *bits |= mask;
        if (*bits != bits0)
        {
          m_field_override_parent_count++;
          Internal_ContentChange();
        }
      }
      else
      {
        // field_id bit = 0 indicates the field value is inherited from the parent.
        *bits &= ~mask;
        if (*bits != bits0)
        {
          m_field_override_parent_count--;
          Internal_ContentChange();
        }
      }
    }
  }
}

void ON_DimStyle::ClearAllFieldOverrides()
{
  SetFieldOverrideAll(false);
}

const ON_DimStyle ON_DimStyle::CreateOverrideCandidate() const
{
  ON_DimStyle override_candidate(*this);
  
  // NOTE:
  // parent_id can be nil. This allows a default constructed dimstyle to be
  // used as an override candidate.
  if ( this->IsOverrideDimStyleCandidate(ParentId(), false))
    return override_candidate;

  ON_UUID parent_id
    = override_candidate.ParentIdIsNotNil()
    ? override_candidate.ParentId()
    : override_candidate.Id();

  override_candidate.ClearId();
  override_candidate.ClearName();
  override_candidate.ClearIndex();

  if (ON_nil_uuid == parent_id)
  {
    parent_id = ON_DimStyle::Default.Id();
  }
  
  override_candidate.SetParentId(parent_id);

  if (override_candidate.HasOverrides())
  {
    const ON_DimStyle& system_parent = ON_DimStyle::SystemDimstyleFromId(parent_id);
    if (system_parent.Id() == parent_id)
      override_candidate.OverrideFields(override_candidate, system_parent);
  }

  if (false == override_candidate.IsOverrideDimStyleCandidate(parent_id, false))
  {
    ON_ERROR("Failed to create valid override candidate.");
  }

  return override_candidate;  
}

const ON_SHA1_Hash& ON_DimStyle::ParentContentHash() const
{
  // The value of m_parent_dim_style_content_hash cannot be reliably cleared 
  // because ParentId() is maintained on a base class. So a "lazy" check on
  // a mutable m_parent_dim_style_content_hash is used.
  if (ParentIdIsNil() && m_field_override_parent_count <= 0)
  {
    // no parent at this point.
    m_parent_dim_style_content_hash = ON_SHA1_Hash::EmptyContentHash;
  }
  return m_parent_dim_style_content_hash;
}

bool ON_DimStyle::HasOverrides() const
{
  return (m_field_override_parent_count > 0);
}

ON__UINT32 ON_DimStyle::OverrideCount() const
{
  return m_field_override_parent_count;
}

void ON_DimStyle::OverrideFields(const ON_DimStyle& source, const ON_DimStyle& parent)
{
  if (ParentId() != parent.Id())
  {
    SetParentId(parent.Id());
  }
  m_parent_dimstyle_managed_font = parent.m_managed_font;

  // leave the Unset, Name, Index fields as is. They cannot be overridden
  for (unsigned int i = static_cast<unsigned int>(ON_DimStyle::field::Index)+1; i < static_cast<unsigned int>(ON_DimStyle::field::Count); i++)
  {
    // NOTE WELL:
    //  "this" could be source or parent, so do not modify member values until they are no longer needed.

    const ON_DimStyle::field field_id = ON_DimStyle::FieldFromUnsigned(i);
    if (ON_DimStyle::field::Unset == field_id)
      continue;

    bool bClearOverrideTest = false;

    const ON_DimStyle* copyfrom;
    if (source.IsFieldOverride(field_id))
    {
      // override the parent setting.
      SetFieldOverride(field_id, true);
      copyfrom = &source; // copy the independent value from source
      bClearOverrideTest = (*this != &parent);
    }
    else
    {
      // inherit the value from the parent
      SetFieldOverride(field_id, false);
      copyfrom = &parent;
    }

    if (this == copyfrom && false == bClearOverrideTest)
      continue; // nothing to do.


    // NOTE: If you change ON_INTERNAL_UPDATE_PROPERTY, then also update ON_DimStyle::field::Font: case below
#define ON_INTERNAL_UPDATE_PROPERTY(PROP) if (this != copyfrom) this->Set ## PROP(copyfrom->PROP()); if (false == bClearOverrideTest || this->PROP() == parent.PROP()) this->SetFieldOverride(field_id, false)

    switch (field_id)
    {
    case ON_DimStyle::field::ExtensionLineExtension:
      ON_INTERNAL_UPDATE_PROPERTY(ExtExtension);
      break;
    case ON_DimStyle::field::ExtensionLineOffset:
      ON_INTERNAL_UPDATE_PROPERTY(ExtOffset);
      break;
    case ON_DimStyle::field::Arrowsize:
      ON_INTERNAL_UPDATE_PROPERTY(ArrowSize);
      break;
    case ON_DimStyle::field::LeaderArrowsize:
      ON_INTERNAL_UPDATE_PROPERTY(LeaderArrowSize);
      break;
    case ON_DimStyle::field::Centermark:
      ON_INTERNAL_UPDATE_PROPERTY(CenterMark);
      break;
    case ON_DimStyle::field::TextGap:
      ON_INTERNAL_UPDATE_PROPERTY(TextGap);
      break;
    case ON_DimStyle::field::TextHeight:
      ON_INTERNAL_UPDATE_PROPERTY(TextHeight);
      break;
    case ON_DimStyle::field::DimTextLocation:
      ON_INTERNAL_UPDATE_PROPERTY(DimTextLocation);
      break;
    case ON_DimStyle::field::MaskFrameType:
      ON_INTERNAL_UPDATE_PROPERTY(MaskFrameType);
      break;
    case ON_DimStyle::field::LengthResolution:
      ON_INTERNAL_UPDATE_PROPERTY(LengthResolution);
      break;
    case ON_DimStyle::field::AngleFormat:
      ON_INTERNAL_UPDATE_PROPERTY(AngleFormat);
      break;
    case ON_DimStyle::field::AngleResolution:
      ON_INTERNAL_UPDATE_PROPERTY(AngleResolution);
      break;
    case ON_DimStyle::field::Font:
      // SPECIAL CASE
      // The ON_Font operator == is not the correct choice for a compare
      if (this != copyfrom) 
        SetFont(copyfrom->m_font_characteristics);
      if (false == bClearOverrideTest || m_font_characteristics.FontCharacteristicsHash() == parent.m_font_characteristics.FontCharacteristicsHash())
        SetFieldOverride(field_id, false);
      break;
    case ON_DimStyle::field::LengthFactor:
      ON_INTERNAL_UPDATE_PROPERTY(LengthFactor);
      break;
    case ON_DimStyle::field::Alternate:
      ON_INTERNAL_UPDATE_PROPERTY(Alternate);
      break;
    case ON_DimStyle::field::AlternateLengthFactor:
      ON_INTERNAL_UPDATE_PROPERTY(AlternateLengthFactor);
      break;
    case ON_DimStyle::field::AlternateLengthResolution:
      ON_INTERNAL_UPDATE_PROPERTY(AlternateLengthResolution);
      break;
    case ON_DimStyle::field::Prefix:
      ON_INTERNAL_UPDATE_PROPERTY(Prefix);
      break;
    case ON_DimStyle::field::Suffix:
      ON_INTERNAL_UPDATE_PROPERTY(Suffix);
      break;
    case ON_DimStyle::field::AlternatePrefix:
      ON_INTERNAL_UPDATE_PROPERTY(AlternatePrefix);
      break;
    case ON_DimStyle::field::AlternateSuffix:
      ON_INTERNAL_UPDATE_PROPERTY(AlternateSuffix);
      break;
    case ON_DimStyle::field::DimensionLineExtension:
      ON_INTERNAL_UPDATE_PROPERTY(DimExtension);
      break;
    case ON_DimStyle::field::SuppressExtension1:
      ON_INTERNAL_UPDATE_PROPERTY(SuppressExtension1);
      break;
    case ON_DimStyle::field::SuppressExtension2:
      ON_INTERNAL_UPDATE_PROPERTY(SuppressExtension2);
      break;
    case ON_DimStyle::field::ExtLineColorSource:
      ON_INTERNAL_UPDATE_PROPERTY(ExtensionLineColorSource);
      break;
    case ON_DimStyle::field::DimLineColorSource:
      ON_INTERNAL_UPDATE_PROPERTY(DimensionLineColorSource);
      break;
    case ON_DimStyle::field::ArrowColorSource:
      ON_INTERNAL_UPDATE_PROPERTY(ArrowColorSource);
      break;
    case ON_DimStyle::field::TextColorSource:
      ON_INTERNAL_UPDATE_PROPERTY(TextColorSource);
      break;
    case ON_DimStyle::field::ExtLineColor:
      ON_INTERNAL_UPDATE_PROPERTY(ExtensionLineColor);
      break;
    case ON_DimStyle::field::DimLineColor:
      ON_INTERNAL_UPDATE_PROPERTY(DimensionLineColor);
      break;
    case ON_DimStyle::field::ArrowColor:
      ON_INTERNAL_UPDATE_PROPERTY(ArrowColor);
      break;
    case ON_DimStyle::field::TextColor:
      ON_INTERNAL_UPDATE_PROPERTY(TextColor);
      break;
    case ON_DimStyle::field::ExtLinePlotColorSource:
      ON_INTERNAL_UPDATE_PROPERTY(ExtensionLinePlotColorSource);
      break;
    case ON_DimStyle::field::DimLinePlotColorSource:
      ON_INTERNAL_UPDATE_PROPERTY(DimensionLinePlotColorSource);
      break;
    case ON_DimStyle::field::ArrowPlotColorSource:
      ON_INTERNAL_UPDATE_PROPERTY(ArrowPlotColorSource);
      break;
    case ON_DimStyle::field::TextPlotColorSource:
      ON_INTERNAL_UPDATE_PROPERTY(TextPlotColorSource);
      break;
    case ON_DimStyle::field::ExtLinePlotColor:
      ON_INTERNAL_UPDATE_PROPERTY(ExtensionLinePlotColor);
      break;
    case ON_DimStyle::field::DimLinePlotColor:
      ON_INTERNAL_UPDATE_PROPERTY(DimensionLinePlotColor);
      break;
    case ON_DimStyle::field::ArrowPlotColor:
      ON_INTERNAL_UPDATE_PROPERTY(ArrowPlotColor);
      break;
    case ON_DimStyle::field::TextPlotColor:
      ON_INTERNAL_UPDATE_PROPERTY(TextPlotColor);
      break;
    case ON_DimStyle::field::ExtLinePlotWeightSource:
      ON_INTERNAL_UPDATE_PROPERTY(ExtensionLinePlotWeightSource);
      break;
    case ON_DimStyle::field::DimLinePlotWeightSource:
      ON_INTERNAL_UPDATE_PROPERTY(DimensionLinePlotWeightSource);
      break;
    case ON_DimStyle::field::ExtLinePlotWeight_mm:
      ON_INTERNAL_UPDATE_PROPERTY(ExtensionLinePlotWeight);
      break;
    case ON_DimStyle::field::DimLinePlotWeight_mm:
      ON_INTERNAL_UPDATE_PROPERTY(DimensionLinePlotWeight);
      break;
    case ON_DimStyle::field::ToleranceFormat:
      ON_INTERNAL_UPDATE_PROPERTY(ToleranceFormat);
      break;
    case ON_DimStyle::field::ToleranceResolution:
      ON_INTERNAL_UPDATE_PROPERTY(ToleranceResolution);
      break;
    case ON_DimStyle::field::ToleranceUpperValue:
      ON_INTERNAL_UPDATE_PROPERTY(ToleranceUpperValue);
      break;
    case ON_DimStyle::field::ToleranceLowerValue:
      ON_INTERNAL_UPDATE_PROPERTY(ToleranceLowerValue);
      break;
    case ON_DimStyle::field::AltToleranceResolution:
      ON_INTERNAL_UPDATE_PROPERTY(AlternateToleranceResolution);
      break;
    case ON_DimStyle::field::ToleranceHeightScale:
      ON_INTERNAL_UPDATE_PROPERTY(ToleranceHeightScale);
      break;
    case ON_DimStyle::field::BaselineSpacing:
      ON_INTERNAL_UPDATE_PROPERTY(BaselineSpacing);
      break;
    case ON_DimStyle::field::DrawMask:
      ON_INTERNAL_UPDATE_PROPERTY(DrawTextMask);
      break;
    case ON_DimStyle::field::MaskColorSource:
      ON_INTERNAL_UPDATE_PROPERTY(MaskFillType);
      break;
    case ON_DimStyle::field::MaskColor:
      ON_INTERNAL_UPDATE_PROPERTY(MaskColor);
      break;
    case ON_DimStyle::field::MaskBorder:
      ON_INTERNAL_UPDATE_PROPERTY(MaskBorder);
      break;
    case ON_DimStyle::field::DimensionScale:
      ON_INTERNAL_UPDATE_PROPERTY(DimScale);
      break;
    case ON_DimStyle::field::DimscaleSource:
      ON_INTERNAL_UPDATE_PROPERTY(DimScaleSource);
      break;
    case ON_DimStyle::field::FixedExtensionLength:
      ON_INTERNAL_UPDATE_PROPERTY(FixedExtensionLen);
      break;
    case ON_DimStyle::field::FixedExtensionOn:
      ON_INTERNAL_UPDATE_PROPERTY(FixedExtensionLenOn);
      break;
    case ON_DimStyle::field::TextRotation:
      ON_INTERNAL_UPDATE_PROPERTY(TextRotation);
      break;
    case ON_DimStyle::field::SuppressArrow1:
      ON_INTERNAL_UPDATE_PROPERTY(SuppressArrow1);
      break;
    case ON_DimStyle::field::SuppressArrow2:
      ON_INTERNAL_UPDATE_PROPERTY(SuppressArrow2);
      break;
    case ON_DimStyle::field::TextmoveLeader:
      ON_INTERNAL_UPDATE_PROPERTY(TextMoveLeader);
      break;
    case ON_DimStyle::field::ArclengthSymbol:
      ON_INTERNAL_UPDATE_PROPERTY(ArcLengthSymbol);
      break;
    case ON_DimStyle::field::StackTextheightScale:
      ON_INTERNAL_UPDATE_PROPERTY(StackHeightScale);
      break;
    case ON_DimStyle::field::StackFormat:
      ON_INTERNAL_UPDATE_PROPERTY(StackFractionFormat);
      break;
    case ON_DimStyle::field::AltRound:
      ON_INTERNAL_UPDATE_PROPERTY(AlternateRoundOff);
      break;
    case ON_DimStyle::field::Round:
      ON_INTERNAL_UPDATE_PROPERTY(RoundOff);
      break;
    case ON_DimStyle::field::AngularRound:
      ON_INTERNAL_UPDATE_PROPERTY(AngleRoundOff);
      break;
    case ON_DimStyle::field::AltZeroSuppress:
      ON_INTERNAL_UPDATE_PROPERTY(AlternateZeroSuppress);
      break;
    //case ON_DimStyle::field::ToleranceZeroSuppress:
    //  ON_INTERNAL_UPDATE_PROPERTY(ToleranceZeroSuppress);
    //  break;
    case ON_DimStyle::field::AngleZeroSuppress:
      ON_INTERNAL_UPDATE_PROPERTY(AngleZeroSuppress);
      break;
    case ON_DimStyle::field::ZeroSuppress:
      ON_INTERNAL_UPDATE_PROPERTY(ZeroSuppress);
      break;
    case ON_DimStyle::field::AltBelow:
      ON_INTERNAL_UPDATE_PROPERTY(AlternateBelow);
      break;
    case ON_DimStyle::field::ArrowType1:
      ON_INTERNAL_UPDATE_PROPERTY(ArrowType1);
      break;
    case ON_DimStyle::field::ArrowType2:
      ON_INTERNAL_UPDATE_PROPERTY(ArrowType2);
      break;
    case ON_DimStyle::field::LeaderArrowType:
      ON_INTERNAL_UPDATE_PROPERTY(LeaderArrowType);
      break;
    case ON_DimStyle::field::ArrowBlockId1:
      ON_INTERNAL_UPDATE_PROPERTY(ArrowBlockId1);
      break;
    case ON_DimStyle::field::ArrowBlockId2:
      ON_INTERNAL_UPDATE_PROPERTY(ArrowBlockId2);
      break;
    case ON_DimStyle::field::LeaderArrowBlock:
      ON_INTERNAL_UPDATE_PROPERTY(LeaderArrowBlockId);
      break;
    case ON_DimStyle::field::DimRadialTextLocation:
      ON_INTERNAL_UPDATE_PROPERTY(DimRadialTextLocation);
      break;
    case ON_DimStyle::field::TextVerticalAlignment:
      ON_INTERNAL_UPDATE_PROPERTY(TextVerticalAlignment);
      break;      
    case ON_DimStyle::field::LeaderTextVerticalAlignment:
      ON_INTERNAL_UPDATE_PROPERTY(LeaderTextVerticalAlignment);
      break;
    case ON_DimStyle::field::LeaderContentAngleStyle:
      ON_INTERNAL_UPDATE_PROPERTY(LeaderContentAngleStyle);
      break;
    case ON_DimStyle::field::LeaderCurveType:
      ON_INTERNAL_UPDATE_PROPERTY(LeaderCurveType);
      break;
    case ON_DimStyle::field::LeaderContentAngle:
      ON_INTERNAL_UPDATE_PROPERTY(LeaderContentAngleRadians);
      break;
    case ON_DimStyle::field::LeaderHasLanding:
      ON_INTERNAL_UPDATE_PROPERTY(LeaderHasLanding);
      break;
    case ON_DimStyle::field::LeaderLandingLength:
      ON_INTERNAL_UPDATE_PROPERTY(LeaderLandingLength);
      break;
    case ON_DimStyle::field::MaskFlags: 
      // SPECIAL CASE
      // field not used   
      SetFieldOverride(ON_DimStyle::field::MaskFlags, false);
      break;
    case ON_DimStyle::field::CentermarkStyle:
      ON_INTERNAL_UPDATE_PROPERTY(CenterMarkStyle);
      break;
    case ON_DimStyle::field::TextHorizontalAlignment:
      ON_INTERNAL_UPDATE_PROPERTY(TextHorizontalAlignment);
      break;
    case ON_DimStyle::field::LeaderTextHorizontalAlignment:
      ON_INTERNAL_UPDATE_PROPERTY(LeaderTextHorizontalAlignment);
      break;
    case ON_DimStyle::field::DrawForward:
      ON_INTERNAL_UPDATE_PROPERTY(DrawForward);
      break;
    case ON_DimStyle::field::SignedOrdinate:
      ON_INTERNAL_UPDATE_PROPERTY(SignedOrdinate);
      break;
    case ON_DimStyle::field::UnitSystem:
      ON_INTERNAL_UPDATE_PROPERTY(UnitSystem);
      break;
    case ON_DimStyle::field::TextMask:
      // SPECIAL CASE
      // The TextMask values are all modified individually by the cases for
      // ON_DimStyle::field::DrawMask:
      // ON_DimStyle::field::MaskColorSource:
      // ON_DimStyle::field::MaskColor:
      // ON_DimStyle::field::MaskBorder:
      //
      ////HIDEME_SetTextMask(copyfrom->TextMask());
      SetFieldOverride(field_id, false);
      break;
    case ON_DimStyle::field::TextOrientation:
      ON_INTERNAL_UPDATE_PROPERTY(TextOrientation);
      break;
    case ON_DimStyle::field::LeaderTextOrientation:
      ON_INTERNAL_UPDATE_PROPERTY(LeaderTextOrientation);
      break;
    case ON_DimStyle::field::DimTextOrientation:
      ON_INTERNAL_UPDATE_PROPERTY(DimTextOrientation);
      break;
    case ON_DimStyle::field::DimRadialTextOrientation:
      ON_INTERNAL_UPDATE_PROPERTY(DimRadialTextOrientation);
      break;
    case ON_DimStyle::field::DimTextAngleStyle:
      ON_INTERNAL_UPDATE_PROPERTY(DimTextAngleStyle);
      break;
    case ON_DimStyle::field::DimRadialTextAngleStyle:
      ON_INTERNAL_UPDATE_PROPERTY(DimRadialTextAngleStyle);
      break;
    case ON_DimStyle::field::TextUnderlined:
      ON_INTERNAL_UPDATE_PROPERTY(TextUnderlined);
      break;
    case ON_DimStyle::field::DimensionLengthDisplay:
      ON_INTERNAL_UPDATE_PROPERTY(DimensionLengthDisplay);
      break;
    case ON_DimStyle::field::AlternateDimensionLengthDisplay:
      ON_INTERNAL_UPDATE_PROPERTY(AlternateDimensionLengthDisplay);
      break;
    case ON_DimStyle::field::ForceDimLine:
      ON_INTERNAL_UPDATE_PROPERTY(ForceDimLine);
      break;
    case ON_DimStyle::field::TextFit:
      ON_INTERNAL_UPDATE_PROPERTY(TextFit);
      break;
    case ON_DimStyle::field::ArrowFit:
      ON_INTERNAL_UPDATE_PROPERTY(ArrowFit);
      break;
    case ON_DimStyle::field::DecimalSeparator:
      ON_INTERNAL_UPDATE_PROPERTY(DecimalSeparator);
      break;
    default:
      ON_ERROR("The switch statement in this function has gaps!");
      SetFieldOverride(field_id, false);
      break;
    }

#undef ON_INTERNAL_UPDATE_PROPERTY

    //// DEBUGGING CODE TO BREAK ON VALUES THAT ARE ACTUALLY OVERRIDDEN
    //if ( bClearOverrideTest && this->IsFieldOverride(field_id) )
    //{
    //  int i = 99;
    //}

  }

  m_parent_dim_style_content_hash = parent.ContentHash();


  return;
}

void ON_DimStyle::InheritFields(const ON_DimStyle& parent)
{
  this->OverrideFields(*this, parent);
}

bool ON_DimStyle::IsChildDimstyle() const
{
  return ParentIdIsNotNil();
}

bool ON_DimStyle::IsChildOf(const ON_UUID& parent_id) const
{
  return (parent_id != ON_nil_uuid && ParentId() == parent_id);
}

ON_DimStyle::tolerance_format ON_DimStyle::ToleranceFormat() const
{
  return m_tolerance_format;
}

int ON_DimStyle::ToleranceResolution() const
{
  return m_tolerance_resolution;
}

double ON_DimStyle::ToleranceUpperValue() const
{
  return m_tolerance_upper_value;
}

double ON_DimStyle::ToleranceLowerValue() const
{
  return m_tolerance_lower_value;
}

double ON_DimStyle::ToleranceHeightScale() const
{
  // Intentionally using StackHeightScale for both fractions and tolerances
  // Tolerances aren't allowed with fractional formats
  return StackHeightScale();
//  return m_tolerance_height_scale;
}

double ON_DimStyle::BaselineSpacing() const
{
  return m_baseline_spacing;
}

//-------------------

static bool Internal_IsValidDimStyleScale(double scale)
{
  return ON_IsValidPositiveNumber(scale)  && fabs(scale - 1.0) > ON_ZERO_TOLERANCE;
}

void ON_DimStyle::Scale(double scale)
{
  // If you modify this code, be sure to update ON_Annotation::ScaleOverrideDimstyle().

  if (Internal_IsValidDimStyleScale(scale))
  {
    m_extextension *= scale;
    m_extoffset *= scale;
    m_arrowsize *= scale;
    m_centermark *= scale;
    m_textgap *= scale;
    m_textheight *= scale;
    m_dimextension *= scale;
    m_baseline_spacing *= scale;
    m_fixed_extension_len *= scale;
    m_leaderarrowsize *= scale;
    m_leader_landing_length *= scale;
    SetMaskBorder(MaskBorder() * scale);
    Internal_ContentChange();
  }
}



double Internal_ScaleOverrideLength(
  double parent_dimstyle_length,
  double current_dimstyle_length,
  double scale
)
{
  // returns scaled dimstyle length
  const double x = current_dimstyle_length * scale;
  const double rel_tol = 1.0e-6 * fabs(parent_dimstyle_length);
  const double abs_tol = ON_ZERO_TOLERANCE;
  const double delta = fabs(x - parent_dimstyle_length);
  return (delta <= rel_tol || delta <= abs_tol) ? parent_dimstyle_length : x;
}

void ON_Annotation::ScaleOverrideDimstyle(
  const ON_DimStyle* parent_dimstyle,
  double scale
)
{
  // Dale Lear Setp 2020 https://mcneel.myjetbrains.com/youtrack/issue/RH-60536
  // I added this function to scale the appearance of annotation
  // in layout/page views. Using DimScale() does not work in layout/page
  // views because it only applies to annotation in model space views.

  if (Internal_IsValidDimStyleScale(scale))
  {
    // The list of properties here must exactly match what is in void ON_DimStyle::Scale(double scale).
    const ON_DimStyle d0 = ON_DimStyle::DimStyleOrDefault(parent_dimstyle);

    // x0 = current value (may already be an override and different from the d0 value)
    // x1 = scaled value (may end up being the d0 value)
    double x0, x1;

    // m_extextension *= scale;
    x0 = this->ExtensionLineExtension(parent_dimstyle);
    x1 = Internal_ScaleOverrideLength(d0.ExtExtension(), x0, scale);
    this->SetExtensionLineExtension(parent_dimstyle, x1);

    // m_extoffset *= scale
    x0 = this->ExtensionLineOffset(parent_dimstyle);
    x1 = Internal_ScaleOverrideLength(d0.ExtOffset(), x0, scale);
    this->SetExtensionLineOffset(parent_dimstyle, x1);

    // m_arrowsize *= scale;
    x0 = this->ArrowSize(parent_dimstyle);
    x1 = Internal_ScaleOverrideLength(d0.ArrowSize(), x0, scale);
    this->SetArrowSize(parent_dimstyle, x1);

    // m_centermark *= scale;
    x0 = this->CenterMarkSize(parent_dimstyle);
    x1 = Internal_ScaleOverrideLength(d0.CenterMark(), x0, scale);
    this->SetCenterMarkSize(parent_dimstyle, x1);

    // m_textgap *= scale;
    x0 = this->TextGap(parent_dimstyle);
    x1 = Internal_ScaleOverrideLength(d0.TextGap(), x0, scale);
    this->SetTextGap(parent_dimstyle, x1);
    
    // m_textheight *= scale
    x0 = this->TextHeight(parent_dimstyle);
    x1 = Internal_ScaleOverrideLength(d0.TextHeight(), x0, scale);
    this->SetTextHeight(parent_dimstyle, x1);
    
    // m_dimextension *= scale;
    x0 = this->DimExtension(parent_dimstyle);
    x1 = Internal_ScaleOverrideLength(d0.DimExtension(), x0, scale);
    this->SetDimExtension(parent_dimstyle, x1);
    
    // m_baseline_spacing *= scale;
    x0 = this->BaselineSpacing(parent_dimstyle);
    x1 = Internal_ScaleOverrideLength(d0.BaselineSpacing(), x0, scale);
    this->SetBaselineSpacing(parent_dimstyle, x1);
    
    // m_fixed_extension_len *= scale;
    x0 = this->FixedExtensionLength(parent_dimstyle);
    x1 = Internal_ScaleOverrideLength(d0.FixedExtensionLen(), x0, scale);
    this->SetFixedExtensionLength(parent_dimstyle, x1);
    
    // m_leaderarrowsize *= scale;
    x0 = this->LeaderArrowSize(parent_dimstyle);
    x1 = Internal_ScaleOverrideLength(d0.LeaderArrowSize(), x0, scale);
    this->SetLeaderArrowSize(parent_dimstyle, x1);
    
    // m_leader_landing_length *= scale;
    x0 = this->LeaderLandingLength(parent_dimstyle);
    x1 = Internal_ScaleOverrideLength(d0.LeaderLandingLength(), x0, scale);
    this->SetLeaderLandingLength(parent_dimstyle, x1);
  }

}

void ON_DimStyle::SetToleranceFormat(ON_DimStyle::tolerance_format format)
{
  if (m_tolerance_format != format)
  {
    m_tolerance_format = format;
    Internal_ContentChange();
    Internal_TextPositionPropertiesChange();
  }
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::ToleranceFormat);
}

void ON_DimStyle::SetToleranceResolution(int resolution)
{
  if (resolution >= 0 && resolution < 16)
    Internal_SetIntMember(ON_DimStyle::field::ToleranceResolution, resolution, m_tolerance_resolution);
}

void ON_DimStyle::SetToleranceUpperValue(double upper_value)
{
  if (ON_IsValid(upper_value))
    Internal_SetDoubleMember(ON_DimStyle::field::ToleranceUpperValue, upper_value, m_tolerance_upper_value);
}

void ON_DimStyle::SetToleranceLowerValue(double lower_value)
{
  if (ON_IsValid(lower_value))
    Internal_SetDoubleMember(ON_DimStyle::field::ToleranceLowerValue, lower_value, m_tolerance_lower_value);
}

void ON_DimStyle::SetToleranceHeightScale(double scale)
{
  // Intentionally using StackHeightScale for both fractions and tolerances
  // Tolerances aren't allowed with fractional formats
  SetStackHeightScale(scale);
  //if (ON_IsValid(scale) && scale > ON_SQRT_EPSILON)
  //  Internal_SetDoubleMember(ON_DimStyle::field::ToleranceHeightScale, scale, m_tolerance_height_scale);
}

void ON_DimStyle::SetBaselineSpacing(double spacing)
{
  if (ON_IsValid(spacing) && spacing > ON_SQRT_EPSILON)
    Internal_SetDoubleMember(ON_DimStyle::field::BaselineSpacing, spacing, m_baseline_spacing);
}

const ON_TextMask& ON_DimStyle::TextMask() const
{
  return m_text_mask;
}

void ON_DimStyle::SetTextMask(const ON_TextMask& mask)
{
  // In order for overrides to work correctly, each text mask property must be
  // set individually.
  const ON_TextMask local_mask(mask);
  SetDrawTextMask(local_mask.DrawTextMask());
  SetMaskColor(local_mask.MaskColor());
  SetMaskFillType(local_mask.MaskFillType());
  SetMaskBorder(local_mask.MaskBorder());
  SetMaskFrameType(local_mask.MaskFrameType());
}

void ON_DimStyle::Internal_SetTextMask(
  const ON_TextMask& text_mask
)
{
  if (m_text_mask != text_mask)
  {
    m_text_mask = text_mask;
    Internal_ContentChange();
  }
  SetFieldOverride(ON_DimStyle::field::MaskFlags, false); // currently never used.
}

bool ON_DimStyle::DrawTextMask() const
{
  // This function is for legacy compatibility.
  // In October 2016, text mask information was moved from
  // a collection of individual values on ON_DimStyle to
  // an ON_TextMask class and a single ON_TextMask m_text_mask member
  // on ON_DimStyle.
  return TextMask().DrawTextMask();
}

void ON_DimStyle::SetDrawTextMask(bool bDraw)
{
  // This function is for legacy compatibility.
  // In October 2016, text mask information was moved from
  // a collection of individual values on ON_DimStyle to
  // an ON_TextMask class and a single ON_TextMask m_text_mask member
  // on ON_DimStyle.
  ON_TextMask text_mask = TextMask();
  text_mask.SetDrawTextMask(bDraw);
  Internal_SetTextMask(text_mask);
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::DrawMask);
}

ON_TextMask::MaskType  ON_DimStyle::MaskFillType() const
{
  // This function is for legacy compatibility.
  // In October 2016, text mask information was moved from
  // a collection of individual values on ON_DimStyle to
  // an ON_TextMask class and a single ON_TextMask m_text_mask member
  // on ON_DimStyle.
  return TextMask().MaskFillType();
}

void ON_DimStyle::SetMaskFillType(ON_TextMask::MaskType source)
{
  // This function is for legacy compatibility.
  // In October 2016, text mask information was moved from
  // a collection of individual values on ON_DimStyle to
  // an ON_TextMask class and a single ON_TextMask m_text_mask member
  // on ON_DimStyle.
  ON_TextMask text_mask = TextMask();
  text_mask.SetMaskFillType(source);
  Internal_SetTextMask(text_mask);
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::MaskColorSource);
}

ON_TextMask::MaskFrame  ON_DimStyle::MaskFrameType() const
{
  // This function is for legacy compatibility.
  // In October 2016, text mask information was moved from
  // a collection of individual values on ON_DimStyle to
  // an ON_TextMask class and a single ON_TextMask m_text_mask member
  // on ON_DimStyle.
  return TextMask().MaskFrameType();
}

void ON_DimStyle::SetMaskFrameType(ON_TextMask::MaskFrame source)
{
  // This function is for legacy compatibility.
  // In October 2016, text mask information was moved from
  // a collection of individual values on ON_DimStyle to
  // an ON_TextMask class and a single ON_TextMask m_text_mask member
  // on ON_DimStyle.
  ON_TextMask text_mask = TextMask();
  text_mask.SetMaskFrameType(source);
  Internal_SetTextMask(text_mask);
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::MaskFrameType);
}

ON_Color ON_DimStyle::MaskColor() const
{
  // This function is for legacy compatibility.
  // In October 2016, text mask information was moved from
  // a collection of individual values on ON_DimStyle to
  // an ON_TextMask class and a single ON_TextMask m_text_mask member
  // on ON_DimStyle.
  return TextMask().MaskColor();
}

void ON_DimStyle::SetMaskColor(ON_Color color)
{
  // This function is for legacy compatibility.
  // In October 2016, text mask information was moved from
  // a collection of individual values on ON_DimStyle to
  // an ON_TextMask class and a single ON_TextMask m_text_mask member
  // on ON_DimStyle.
  ON_TextMask text_mask = TextMask();
  text_mask.SetMaskColor(color);
  Internal_SetTextMask(text_mask);
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::MaskColor);
}

double ON_DimStyle::MaskBorder() const
{
  // This function is for legacy compatibility.
  // In October 2016, text mask information was moved from
  // a collection of individual values on ON_DimStyle to
  // an ON_TextMask class and a single ON_TextMask m_text_mask member
  // on ON_DimStyle.
  return TextMask().MaskBorder();
}

void ON_DimStyle::SetMaskBorder(double border)
{
  // This function is for legacy compatibility.
  // In October 2016, text mask information was moved from
  // a collection of individual values on ON_DimStyle to
  // an ON_TextMask class and a single ON_TextMask m_text_mask member
  // on ON_DimStyle.
  ON_TextMask text_mask = TextMask();
  text_mask.SetMaskBorder(border);
  Internal_SetTextMask(text_mask);
  Internal_SetOverrideDimStyleCandidateFieldOverride(ON_DimStyle::field::MaskBorder);
}

void ON_DimStyle::SetDimScaleSource(int source)
{
  Internal_SetIntMember(ON_DimStyle::field::DimscaleSource, source, m_dimscale_source);
}

int ON_DimStyle::DimScaleSource() const
{
  return m_dimscale_source;
}

void ON_DimStyle::SetSourceDimstyle(ON_UUID source_uuid)
{
  // Can be ON_nil_uuid
  if (m_source_dimstyle != source_uuid)
  {
    m_source_dimstyle = source_uuid;
    Internal_ContentChange();
  }
}

ON_UUID ON_DimStyle::SourceDimstyle() const
{
  return m_source_dimstyle;
}

const ON_DimStyle ON_DimStyle::CreateFromProperties(
  const ON_DimStyle& parent_dim_style,
  ON::AnnotationType annotation_type,
  const ON_Font* font,
  double model_space_text_scale,
  double text_height,
  ON::LengthUnitSystem text_height_unit_system
)
{
  ON_DimStyle dim_style(parent_dim_style.CreateOverrideCandidate());

  Internal_CreateFromProperties(
    parent_dim_style,
    annotation_type,
    font,
    model_space_text_scale,
    text_height,
    text_height_unit_system,
    false,
    ON::TextVerticalAlignment::Middle,       // value ignored
    ON::TextHorizontalAlignment::Center,     // value ignored
    false,
    ON::TextOrientation::InPlane,            // value ignored
    false,
    ON_DimStyle::TextLocation::AboveDimLine, // value ignored
    dim_style
  );

  return dim_style;
}

const ON_DimStyle ON_DimStyle::CreateFromProperties(
  const ON_DimStyle& parent_dim_style,
  ON::AnnotationType annotation_type,
  const ON_Font* font,
  double model_space_text_scale,
  double text_height,
  ON::LengthUnitSystem text_height_unit_system,
  ON::TextVerticalAlignment valign,
  ON::TextHorizontalAlignment halign
)
{
  ON_DimStyle dim_style(parent_dim_style.CreateOverrideCandidate());

  Internal_CreateFromProperties(
    parent_dim_style,
    annotation_type,
    font,
    model_space_text_scale,
    text_height,
    text_height_unit_system,
    true,
    valign,
    halign,
    false,
    ON::TextOrientation::InPlane,            // value ignored
    false,
    ON_DimStyle::TextLocation::AboveDimLine, // value ignored
    dim_style
  );

  return dim_style;
}

const ON_DimStyle ON_DimStyle::CreateFromProperties(
  const ON_DimStyle& parent_dim_style,
  ON::AnnotationType annotation_type,
  const ON_Font* font,
  double model_space_text_scale,
  double text_height,
  ON::LengthUnitSystem text_height_unit_system,
  ON::TextVerticalAlignment valign,
  ON::TextHorizontalAlignment halign,
  ON::TextOrientation orientation,
  ON_DimStyle::TextLocation dim_text_location
  )
{
  ON_DimStyle dim_style(parent_dim_style.CreateOverrideCandidate());

  Internal_CreateFromProperties(
    parent_dim_style,
    annotation_type,
    font,
    model_space_text_scale,
    text_height,
    text_height_unit_system,
    true,
    valign,
    halign,
    true,
    orientation,
    true,
    dim_text_location,
    dim_style
  );

  return dim_style;
}

void ON_DimStyle::Internal_CreateFromProperties(
  const ON_DimStyle& parent_dim_style,
  ON::AnnotationType annotation_type,
  const ON_Font* font,
  double model_space_text_scale,
  double text_height,
  ON::LengthUnitSystem text_height_unit_system,
  bool bSetAlignment,
  ON::TextVerticalAlignment valign,
  ON::TextHorizontalAlignment halign,
  bool bSetOrientation,
  ON::TextOrientation orientation,
  bool bSetLocation,
  ON_DimStyle::TextLocation location,
  ON_DimStyle& destination
)
{
  if (nullptr != font)
  {
    if (0 != ON_Font::CompareFontCharacteristics(*font, parent_dim_style.Font()))
      destination.SetFont(*font);
  }

  if (model_space_text_scale > 0.0)
  {
    if (fabs(model_space_text_scale - parent_dim_style.DimScale()) > 0.001*model_space_text_scale )
      destination.SetDimScale(model_space_text_scale);
  }

  if (text_height > 0.0)
  {
    double x = ON::UnitScale(text_height_unit_system, parent_dim_style.UnitSystem())*text_height;
    if (x > 0.0 && fabs(x - parent_dim_style.TextHeight()) > 0.001*x )
      destination.SetTextHeight(x);
  }

  /////////////////////////////////////////////////
  //
  // Use annotation_type parameter to determine what annotation types are effected by the settings
  //
  const bool bAllAnnotationTypes = (ON::AnnotationType::Unset == annotation_type);
  const bool bDimLinearType 
    = ON::AnnotationType::Aligned == annotation_type 
    || ON::AnnotationType::Rotated == annotation_type
    ;
  const bool bDimAngularType 
    = ON::AnnotationType::Angular == annotation_type
    || ON::AnnotationType::Angular3pt == annotation_type
    ;
  const bool bDimRadialType 
    = ON::AnnotationType::Radius == annotation_type
    || ON::AnnotationType::Diameter == annotation_type
    ;

  const bool bSetTextProps 
    = (bAllAnnotationTypes || ON::AnnotationType::Text == annotation_type);

  const bool bSetLeaderProps
    = (bAllAnnotationTypes || ON::AnnotationType::Leader == annotation_type);

  const bool bSetDimProps
    = (bAllAnnotationTypes || bDimLinearType || bDimAngularType || ON::AnnotationType::Ordinate == annotation_type);

  const bool bSetDimRadialProps
    = (bAllAnnotationTypes || bDimRadialType);

  /////////////////////////////////////////////////
  //
  // Override type specific properties as needed
  //
  if (bSetAlignment)
  {
    const bool bOverrideTextHAlign = bSetTextProps && halign != parent_dim_style.TextHorizontalAlignment();
    const bool bOverrideLeaderHAlign = bSetLeaderProps && halign != parent_dim_style.LeaderTextHorizontalAlignment();
    if (bOverrideTextHAlign)
      destination.SetTextHorizontalAlignment(halign);
    if (bOverrideLeaderHAlign)
      destination.SetLeaderTextHorizontalAlignment(halign);

    const bool bOverrideTextVAlign = bSetTextProps && valign != parent_dim_style.TextVerticalAlignment();
    const bool bOverrideLeaderVAlign = bSetLeaderProps && valign != parent_dim_style.LeaderTextVerticalAlignment();
    if (bOverrideTextVAlign)
      destination.SetTextVerticalAlignment(valign);
    if (bOverrideLeaderVAlign)
      destination.SetLeaderTextVerticalAlignment(valign);
  }
  
  if (bSetOrientation)
  {
    const bool bOverrideTextOrientation = bSetTextProps && orientation != parent_dim_style.TextOrientation();
    const bool bOverrideLeaderOrientation = bSetLeaderProps && orientation != parent_dim_style.LeaderTextOrientation();
    const bool bOverrideDimOrientation = bSetDimProps && orientation != parent_dim_style.DimTextOrientation();
    const bool bOverrideDimRadialOrientation = bSetDimRadialProps && orientation != parent_dim_style.DimRadialTextOrientation();
    if (bOverrideTextOrientation)
      destination.SetTextOrientation(orientation);
    if (bOverrideLeaderOrientation)
      destination.SetLeaderTextOrientation(orientation);
    if (bOverrideDimOrientation)
      destination.SetDimTextOrientation(orientation);
    if (bOverrideDimRadialOrientation)
      destination.SetDimRadialTextOrientation(orientation);
  }

  if (bSetLocation)
  {
    const bool bOverrideDimTextLocation = bSetDimProps && location != parent_dim_style.DimTextLocation();
    const bool bOverrideDimRadialTextLocation = bSetDimRadialProps && location != parent_dim_style.DimRadialTextLocation();
    if (bOverrideDimTextLocation)
      destination.SetDimTextLocation(location);
    if (bOverrideDimRadialTextLocation)
      destination.SetDimRadialTextLocation(location);
  }
}
