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

#pragma once
#if !defined(OPENNURBS_STRING_VALUE_INC_)
#define OPENNURBS_STRING_VALUE_INC_

class ON_CLASS ON_LengthValue
{
public:
  ON_LengthValue() = default;
  ~ON_LengthValue() = default;
  ON_LengthValue(const ON_LengthValue&) = default;
  ON_LengthValue& operator=(const ON_LengthValue&) = default;

  static const ON_LengthValue Unset;
  static const ON_LengthValue Zero;

  bool IsUnset() const;
  bool IsSet() const;

  bool Write(
    class ON_BinaryArchive& archive
  ) const;

  bool Read(
    class ON_BinaryArchive& archive
  );

  /*
  Description:
    Create an ON_LengthValue by parsing a string.
  Parameters:
    parse_settings - [in]
      Pass ON_ParseSettings(context_length_unit_system,context_angle_unit_system,context_locale_id)
    string - [in]
      null terminated string to parse.
  Returns:
    If the string is valid, the exact length value is returned.
    If the string is not valid or parsing ends before the string's null terminator,
    the ON_LengthValue::Unset is returned.
  Remarks:
    If the entire string is not parsed, that is an error condition.
    Use CreateFromSubString() to permit parsing a portion of the string.
  */
  static ON_LengthValue CreateFromString(
    ON_ParseSettings parse_settings,
    const wchar_t* string
  );

  /*
  Description:
    Create an ON_LengthValue by parsing a string.
  Parameters:
    parse_settings - [in]
      Pass ON_ParseSettings(context_length_unit_system,context_angle_unit_system,context_locale_id)
    string - [in]
      null terminated string to parse.
    string_count - [in]
      string[] and string_count specify the string to parse.
      If string_count >= 0, it specifies the maximum number of elements in string[]
      that may be parsed.  If string_count = -1, then the string must contain a 
      character that terminates length parsing.
    string_end - [out]
      If string_end is not nullptr, then *string_end points to the first 
      element in the string that was not parsed.
  Returns:
    If the string is valid, the exact length value is returned.
    If the string is not valid or parsing ends before the string's null terminator,
    the ON_LengthValue::Unset is returned.
  Remarks:
    If the entire string is not parsed, that is an error condition.
    Use CreateFromSubString() to permit parsing a portion of the string.
  */
  static ON_LengthValue CreateFromSubString(
    ON_ParseSettings parse_settings,
    const wchar_t* string,
    int string_count,
    const wchar_t** string_end
  );

  /*
  Returns:
    A ON_LengthValue with the same length value and unit system = None.
  */
  const ON_LengthValue RemoveUnitSystem() const;

  /*
  Parameters:
    length_value - [in]
      New length.
  Returns:
    A ON_LengthValue with the new length and other settings copied from this.
  */
  const ON_LengthValue ChangeLength(
    double length_value
    ) const;

#pragma region RH_C_SHARED_ENUM [ON_LengthValue::StringFormat] [Rhino.LengthValue.StringFormat] [nested:byte]
  /// <summary>
  /// Formatting to apply when creating a length value from a double.
  /// </summary>
  enum class StringFormat : unsigned char
  {
    ///<summary>Use exact decimal string.</summary>
    ExactDecimal = 0,

    ///<summary>If possible, use exact integer-fraction format (1.125 becomes 1-1/8).</summary>
    ExactProperFraction = 1,

     ///<summary>If possible, use exact fraction format (1.125 becomes 9/8).</summary>
    ExactImproperFraction = 2,

    ///<summary>The value may be adjusted slightly to improve clarity (1.124999... becomes 1.125).</summary>
    CleanDecimal = 3, 

    ///<summary>The value may be adjusted slightly to improve clarity (1.124999... becomes 1-1/8).</summary>
    CleanProperFraction = 4,

    ///<summary>The value may be adjusted slightly to improve clarity (1.124999... becomes 9/8).</summary>
    CleanImproperFraction = 5
  };
#pragma endregion

  static ON_LengthValue::StringFormat LengthStringFormatFromUnsigned(
    unsigned int string_format_as_unsigned
  );

  /*
  Parameters:
    length_value - [in]
    length_unit_system - [in]
    bUseFractionsInString - [in]
      If bUseFractions is true and length_value can be represented as a common
      fraction, then the string form will contain a fraction rather than a decimal.
    locale_id - [in]
      locale id for the string length unit system
      0 will select ON_Locale::CurrentCulture.
    string_format - [in]
      Determines the format of the string representation
  Returns:
    Length in the specified length unit system
  Remarks:
    If you don't like the automatically created string value, then 
    format the string yourself and use ON_LengthValue::CreateFromString().
  */ 
  static ON_LengthValue Create(
    double length_value,
    const class ON_UnitSystem& length_unit_system,
    unsigned int locale_id,
    ON_LengthValue::StringFormat string_format
  );

  /*
  Parameters:
    length_value - [in]
    length_unit_system - [in]
    bUseFractionsInString - [in]
      If bUseFractions is true and length_value can be represented as a common
      fraction, then the string form will contain a fraction rather than a decimal.
    locale_id - [in]
      locale id for the string length unit system
    bool 
  Returns:
    Length in the specified length unit system
  Remarks:
    If you don't like the automatically created string value, then 
    format the string yourself and use ON_LengthValue::CreateFromString().
  */ 
  static ON_LengthValue Create(
    double length_value,
    const ON::LengthUnitSystem length_unit_system,
    unsigned int locale_id,
    ON_LengthValue::StringFormat string_format
  );

  static ON_LengthValue Create(
    double length_value,
    const class ON_LengthUnitName& length_unit_system,
    ON_LengthValue::StringFormat string_format
  );

  /*
  Parameters:
    context_unit_system - [in]
      length unit system for the returned value.
      Pass ON_UnitSystem::None to ignore the length unit system and get the value save in this class. 
  Returns:
    Length in the specified length unit system
  */
  double Length(
    const class ON_UnitSystem& context_unit_system
  ) const;

  /*
  Parameters:
    context_unit_system - [in]
      length unit system for the returned value.
      Pass ON::LengthUnitSystem::None to ignore the length unit system and get the value save in this class. 
  Returns:
    Length in the specified length unit system
  */
  double Length(
    ON::LengthUnitSystem context_unit_system
  ) const;

  /*
  Returns:
    Length unit system for this class.
  */
  const class ON_UnitSystem& LengthUnitSystem() const;

  /*
  Returns:
    The length as a string.
  Remarks:
    If ON_LengthValue::CreateFromString() or ON_LengthValue::CreateFromSubString()
    were used to create this ON_LengthValue, a copy of that string
    is returned.
  */
  const ON_wString& LengthAsString() const;
  const wchar_t* LengthAsStringPointer() const;

  const ON_ParseSettings LengthStringParseSettings() const;

  /*
  Returns:
    Format processing applied to input values.
  */
  ON_LengthValue::StringFormat LengthStringFormat() const;

  /*
  Returns:
    Locale used to parse input strings and create unit names.
  */
  unsigned int ContextLocaleId() const;

  /*
  Returns:
    Angle unit system used to parse input strings.
  */
  ON::AngleUnitSystem ContextAngleUnitSystem() const;

  const ON_SHA1_Hash ContentHash() const;
  static int Compare(
    const ON_LengthValue& lhs,
    const ON_LengthValue& rhs
  );

private:
  // parsing context
  unsigned int m_context_locale_id = 0;
  ON::AngleUnitSystem m_context_angle_unit_system = ON::AngleUnitSystem::Unset;
  ON_LengthValue::StringFormat m_string_format = ON_LengthValue::StringFormat::ExactDecimal;

  ON_UnitSystem m_length_unit_system = ON_UnitSystem::Unset;
  double m_length = ON_DBL_QNAN;

  ON_wString m_length_as_string;
};


class ON_CLASS ON_AngleValue
{
public:
  ON_AngleValue() = default;
  ~ON_AngleValue() = default;
  ON_AngleValue(const ON_AngleValue&) = default;
  ON_AngleValue& operator=(const ON_AngleValue&) = default;

  bool Write(
    class ON_BinaryArchive& archive
  ) const;

  bool Read(
    class ON_BinaryArchive& archive
  );

  static const ON_AngleValue Unset;
  static const ON_AngleValue Zero;

  bool IsUnset() const;
  bool IsSet() const;

  /// <summary>
  /// ON_AngleValue::StringFormat identifies the formatting to apply when creating 
  /// a length value from a double.
  /// </summary>
  enum class StringFormat : unsigned char
  {
    ///<summary>Use exact decimal string.</summary>
    ExactDecimal = 0,

    ///<summary>If possible, use exact fraction format (1.125 becomes 9/8).</summary>
    ExactFraction = 1,

    ///<summary>The value may be adjusted slightly to improve clarity (1.124999... becomes 1.125).</summary>
    CleanDecimal = 2, 

    ///<summary>The value may be adjusted slightly to improve clarity (1.124999... becomes 9/8).</summary>
    CleanFraction = 3
  };

  static ON_AngleValue::StringFormat AngleStringFormatFromUnsigned(
    unsigned int string_format_as_unsigned
  );


  /*
  Description:
    Create an ON_AngleValue by parsing a string.
  Parameters:
    parse_settings - [in]
      Pass ON_ParseSettings(context_length_unit_system,context_angle_unit_system,context_locale_id)
    string - [in]
      null terminated string to parse.
  Returns:
    If the string is valid, the exact angle value is returned.
    If the string is not valid or parsing ends before the string's null terminator,
    the ON_AngleValue::Unset is returned.
  Remarks:
    If the entire string is not parsed, that is an error condition.
    Use CreateFromSubString() to permit parsing a portion of the string.
  */
  static ON_AngleValue CreateFromString(
    ON_ParseSettings parse_settings,
    const wchar_t* string
  );
  
  /*
  Description:
    Create an ON_AngleValue by parsing a string.
  Parameters:
    parse_settings - [in]
      Pass ON_ParseSettings(context_length_unit_system,context_angle_unit_system,context_locale_id)
    string - [in]
      null terminated string to parse.
    string_count - [in]
      string[] and string_count specify the string to parse.
      If string_count >= 0, it specifies the maximum number of elements in string[]
      that may be parsed.  If string_count = -1, then the string must contain a 
      character that terminates angle parsing.
    string_end - [out]
      If string_end is not nullptr, then *string_end points to the first 
      element in the string that was not parsed.
  Returns:
    If the string is valid, the exact angle value is returned.
    If the string is not valid or parsing ends before the string's null terminator,
    the ON_AngleValue::Unset is returned.
  Remarks:
    If the entire string is not parsed, that is an error condition.
    Use CreateFromSubString() to permit parsing a portion of the string.
  */
  static ON_AngleValue CreateFromSubString(
    ON_ParseSettings parse_settings,
    const wchar_t* string,
    int string_count,
    const wchar_t** string_end
  );

  /*
  Parameters:
    angle_value - [in]
    angle_unit_system - [in]
    bUseFractionsInString - [in]
      If bUseFractions is true and angle_value can be represented as a common
      fraction, then the string form will contain a fraction rather than a decimal.
    locale_id - [in]
      locale id for the string angle unit system
    bool 
  Returns:
    Angle in the specified angle unit system
  Remarks:
    If you don't like the automatically created string value, then 
    format the string yourself and use ON_AngleValue::CreateFromString().
  */ 
  static ON_AngleValue Create(
    double angle_value,
    ON::AngleUnitSystem angle_unit_system,
    unsigned int locale_id,
    ON_AngleValue::StringFormat string_format
  );

  static ON_AngleValue Create(
    double angle_value,
    const class ON_AngleUnitName& angle_unit_system,
    ON_AngleValue::StringFormat string_format
  );

  /*
  Parameters:
    context_unit_system - [in]
      angle unit system for the returned value.
      Pass ON::AngleUnitSystem::None to ignore the angle unit system and get the value save in this class. 
  Returns:
    Angle in the specified angle unit system
  */
  double Angle(
    ON::AngleUnitSystem context_unit_system
  ) const;

  /*
  Returns:
    Angle unit system for this class.
  */
  ON::AngleUnitSystem AngleUnitSystem() const;

  /*
  Returns:
    The angle as a string.
  Remarks:
    If ON_AngleValue::CreateFromString() or ON_AngleValue::CreateFromSubString()
    were used to create this ON_AngleValue, a copy of that string
    is returned.
  */
  const ON_wString& AngleAsString() const;
  const wchar_t* AngleAsStringPointer() const;

  const ON_ParseSettings AngleStringParseSettings() const;

private:
  // parsing context
  unsigned int m_context_locale_id = 0;
  ON::LengthUnitSystem m_context_length_unit_system = ON::LengthUnitSystem::None;
  ON_AngleValue::StringFormat m_string_format = ON_AngleValue::StringFormat::ExactDecimal;
  
  ON::AngleUnitSystem m_angle_unit_system = ON::AngleUnitSystem::Unset;
  double m_angle = ON_DBL_QNAN;

  ON_wString m_angle_as_string;
};

class ON_CLASS ON_ScaleValue
{
public:
  ON_ScaleValue() = default;
  ~ON_ScaleValue() = default;
  ON_ScaleValue(const ON_ScaleValue&) = default;
  ON_ScaleValue& operator=(const ON_ScaleValue&) = default;

  static const ON_ScaleValue Unset;
  static const ON_ScaleValue OneToOne;

  bool IsUnset() const;
  bool IsSet() const;

  bool Write(
    class ON_BinaryArchive& archive
  ) const;

  bool Read(
    class ON_BinaryArchive& archive
  );

#pragma region RH_C_SHARED_ENUM [ON_ScaleValue::ScaleStringFormat] [Rhino.ScaleValue.ScaleStringFormat] [nested:byte]
  /// <summary>
  /// Specifies preferred formats for automatically
  /// created string descriptions of a scale value.
  /// </summary>
  enum class ScaleStringFormat : unsigned char
  {
    /// <summary>
    /// No preference for automatically created string descriptions of a scale value.
    /// </summary>
    None = 0,

    /// <summary>
    /// Prefer the ratio format using a colon, like "1:4" or "4:1".
    /// </summary>
    RatioFormat = 1,

    /// <summary>
    /// Prefer the equation format using an equal sign, like "1 = 4" or "4 = 1".
    /// </summary>
    EquationFormat = 2,

    /// <summary>
    /// Prefer the fraction format using a slash, like "1/4" or "4/1".
    /// </summary>
    FractionFormat = 3,

    /// <summary>
    /// ON_ScaleValue::ScaleStringFormat::Unset is used to indicate no preference is set.
    /// This condition is different from ON_ScaleValue::ScaleStringFormat::None.
    /// </summary>
    Unset = 0xFF
  };
#pragma endregion

  static ON_ScaleValue::ScaleStringFormat ScaleStringFormatFromUnsigned(
    unsigned int scale_string_format_as_unsigned
  );

  /*
  Description:
    Create an ON_ScaleValue by parsing a string.
  Parameters:
    parse_settings - [in]
      Pass ON_ParseSettings(context_length_unit_system,context_angle_unit_system,context_locale_id)
    string - [in]
      null terminated string to parse.
  Returns:
    If the string is valid, the exact scale value is returned.
    If the string is not valid or parsing ends before the string's null terminator,
    the ON_ScaleValue::Unset is returned.
  Remarks:
    If the entire string is not parsed, that is an error condition.
    Use CreateFromSubString() to permit parsing a portion of the string.
  Examples:
    "1:4", "1=4", "1/4", "0.25"
    will set LeftToRightScale() = 4, RightToLeftScale() = 0.25

    "4:1", "4=1", "4/1", "4"
    will set LeftToRightScale() = 0.25, RightToLeftScale() = 4

    "100:1", "100=1", "1 meter = 1 centimeter"
    will set LeftToRightScale() = 0.01, RightToLeftScale() = 100

    "1:100", "1=100", "1 centimeter = 1 meter"
    will set LeftToRightScale() = 100, RightToLeftScale() = 0.01

    "12:1", "12=1", "12/1", "12", "1 foot = 1 inch"
    will set LeftToRightScale() = 0.08333..., RightToLeftScale() = 12

    "1:12", "1=12", "1/12", "1 inch = 1 foot"
    will set LeftToRightScale() = 12, RightToLeftScale() = 0.08333...

    "1:48", "1 = 48", "1/4 inch = 1 foot"
    will set LeftToRightScale() = 48, RightToLeftScale() = 0.0208333...
  */
  static ON_ScaleValue CreateFromString(
    ON_ParseSettings parse_settings,
    const wchar_t* string
  );

  /*
  Description:
    Create an ON_ScaleValue by parsing a string.
  Parameters:
    parse_settings - [in]
      Pass ON_ParseSettings(context_length_unit_system,context_angle_unit_system,context_locale_id)
    string - [in]
      null terminated string to parse.
    string_count - [in]
      string[] and string_count specify the string to parse.
      If string_count >= 0, it specifies the maximum number of elements in string[]
      that may be parsed.  If string_count = -1, then the string must contain a 
      character that terminates scale parsing.
    string_end - [out]
      If string_end is not nullptr, then *string_end points to the first 
      element in the string that was not parsed.
  Returns:
    If the string is valid, the exact scale value is returned.
    If the string is not valid or parsing ends before the string's null terminator,
    the ON_ScaleValue::Unset is returned.
  Remarks:
    If the entire string is not parsed, that is an error condition.
    Use CreateFromSubString() to permit parsing a portion of the string.
  
  Examples:
    "1:4", "1=4", "1/4", "0.25"
    will set LeftToRightScale() = 4, RightToLeftScale() = 0.25

    "4:1", "4=1", "4/1", "4"
    will set LeftToRightScale() = 0.25, RightToLeftScale() = 4

    "100:1", "100=1", "1 meter = 1 centimeter"
    will set LeftToRightScale() = 0.01, RightToLeftScale() = 100

    "1:100", "1=100", "1 centimeter = 1 meter"
    will set LeftToRightScale() = 100, RightToLeftScale() = 0.01

    "12:1", "12=1", "12/1", "12", "1 foot = 1 inch"
    will set LeftToRightScale() = 0.08333..., RightToLeftScale() = 12

    "1:12", "1=12", "1/12", "1 inch = 1 foot"
    will set LeftToRightScale() = 12, RightToLeftScale() = 0.08333...

    "1:48", "1 = 48", "1/4 inch = 1 foot"
    will set LeftToRightScale() = 48, RightToLeftScale() = 0.0208333...
  */
  static ON_ScaleValue CreateFromSubString(
    ON_ParseSettings parse_settings,
    const wchar_t* string,
    int string_count,
    const wchar_t** string_end
  );

  /*
  Parameters:
    left_length - [in]
    right_length - [in]
  Returns:
    A scale value for converting a distance from source_length to
    destination_length.
  Remarks:
    If you don't like the automatically created string value, then 
    format the string yourself and use ON_ScaleValue::CreateFromString().
  */ 
  static ON_ScaleValue Create(
    const class ON_LengthValue& left_side_length,
    const class ON_LengthValue& right_side_length,
    ON_ScaleValue::ScaleStringFormat string_format_preference
  );

  /*
  Returns:
    A dimensionless scale factor.
    The word "dimensionless" is critical. Differences in left and right
    side unit systems are accounted for in the returned value.
  Remarks:
    LeftToRightScale() = 1.0/RightToLeftScale()
  Examples:
    "1:4", "1=4", "1/4", "0.25"
    will set LeftToRightScale() = 4, RightToLeftScale() = 0.25

    "4:1", "4=1", "4/1", "4"
    will set LeftToRightScale() = 0.25, RightToLeftScale() = 4

    "100:1", "100=1", "1 meter = 1 centimeter"
    will set LeftToRightScale() = 0.01, RightToLeftScale() = 100

    "1:100", "1=100", "1 centimeter = 1 meter"
    will set LeftToRightScale() = 100, RightToLeftScale() = 0.01

    "12:1", "12=1", "12/1", "12", "1 foot = 1 inch"
    will set LeftToRightScale() = 0.08333..., RightToLeftScale() = 12

    "1:12", "1=12", "1/12", "1 inch = 1 foot"
    will set LeftToRightScale() = 12, RightToLeftScale() = 0.08333...

    "1:48", "1 = 48", "1/4 inch = 1 foot"
    will set LeftToRightScale() = 48, RightToLeftScale() = 0.0208333...
  */
  double LeftToRightScale() const;

  /*
  Returns:
    A dimensionless scale factor.
    The word "dimensionless" is critical. Differences in left and right
    side unit systems are accounted for in the returned value.
  Remarks:
    RightToLeftScale() = 1.0/LeftToRightScale()
  Examples:
    "1:4", "1=4", "1/4", "0.25"
    will set LeftToRightScale() = 4, RightToLeftScale() = 0.25

    "4:1", "4=1", "4/1", "4"
    will set LeftToRightScale() = 0.25, RightToLeftScale() = 4

    "100:1", "100=1", "1 meter = 1 centimeter"
    will set LeftToRightScale() = 0.01, RightToLeftScale() = 100

    "1:100", "1=100", "1 centimeter = 1 meter"
    will set LeftToRightScale() = 100, RightToLeftScale() = 0.01

    "12:1", "12=1", "12/1", "12", "1 foot = 1 inch"
    will set LeftToRightScale() = 0.08333..., RightToLeftScale() = 12

    "1:12", "1=12", "1/12", "1 inch = 1 foot"
    will set LeftToRightScale() = 12, RightToLeftScale() = 0.08333...

    "1:48", "1 = 48", "1/4 inch = 1 foot"
    will set LeftToRightScale() = 48, RightToLeftScale() = 0.0208333...
  */
  double RightToLeftScale() const;


  const class ON_LengthValue& LeftLengthValue() const;
  const class ON_LengthValue& RightLengthValue() const;

  /*
  Returns:
    The scale as a string.
  Remarks:
    If ON_ScaleValue::CreateFromString() or ON_ScaleValue::CreateFromSubString()
    were used to create this ON_ScaleValue, a copy of that string is returned.
  */
  const ON_wString& ScaleAsString() const;
  const wchar_t* ScaleAsStringPointer() const;

  const ON_ParseSettings ScaleStringParseSettings() const;

  /*
  Description
    Exchange the left and right lengths.
  */
  void SwapLeftAndRight();

  const ON_SHA1_Hash ContentHash() const;

  static int Compare(
    const ON_ScaleValue& lhs,
    const ON_ScaleValue& rhs
  );

private:
  double m_left_to_right_scale = ON_DBL_QNAN;
  double m_right_to_left_scale = ON_DBL_QNAN;

  // parsing context
  unsigned int m_context_locale_id = 0;
  ON::LengthUnitSystem m_context_length_unit_system = ON::LengthUnitSystem::None;
  ON::AngleUnitSystem m_context_angle_unit_system = ON::AngleUnitSystem::None;
  ON_ScaleValue::ScaleStringFormat m_string_format_preference = ON_ScaleValue::ScaleStringFormat::Unset;

  ON_wString m_scale_as_string;

  ON_LengthValue m_left_length = ON_LengthValue::Unset;
  ON_LengthValue m_right_length = ON_LengthValue::Unset;
};

#endif

