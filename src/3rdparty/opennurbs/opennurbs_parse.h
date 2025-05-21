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

#if !defined(ON_PARSE_INC_)
#define ON_PARSE_INC_

class ON_CLASS ON_ArithmeticCalculator
{
public:
  ON_ArithmeticCalculator();
  ON_ArithmeticCalculator(const ON_ArithmeticCalculator&);
  ON_ArithmeticCalculator(ON_ArithmeticCalculator&&);
  ON_ArithmeticCalculator& operator=(const ON_ArithmeticCalculator&);
  ON_ArithmeticCalculator& operator=(ON_ArithmeticCalculator&&);

  ////////////////////////////////////////////////////////////
  //
  // Configuration Settings
  //
  bool ImpliedMultiplication() const;
  void SetImpliedMultiplication(
    bool bEnable
    );


  ////////////////////////////////////////////////////////////
  //
  // Current Status
  //
  enum ERROR_CONDITION
  {
    no_error = 0,

    program_error = 1,
      // The part of the computer running the ON_ArithmeticCalculator 
      // code is corrupt or damaged or there is a bug in the
      // ON_ArithmeticCalculator code.

    invalid_expression_error = 2, 
      // The input expression does not make sense.

    divide_by_zero_error = 3,
      // A calculation requested division by zero.
    
    overflow_error = 4,
      // A calculation produced a number the computer cannot represent
  };

  ERROR_CONDITION ErrorCondition() const;
  
  /*
  Returns:
    True if a unary plus is pending and will be applied
    to the next number or parenthetical expression.
  */
  bool PendingUnaryPlus() const;

  /*
  Returns:
    True if a unary minus is pending and will be applied
    to the next number or parenthetical expression.
  */
  bool PendingUnaryMinus() const;

  /*
  Returns:
    True if a unary plus or unary minus is pending
  */
  bool PendingUnaryOperation() const;

  /*
  Returns:
    True if an implied multiplication will be applied
    to the next number or parenthetical expression.
  */
  bool PendingImpliedMultiplication() const;

  /*
  Returns:
    The current number of parenthetic expressions that 
    are not completed.
  */
  unsigned int ParenthesesDepth() const;
  
  ////////////////////////////////////////////////////////////
  //
  // Calculator keys
  //

  /*
  Description:
    Enter a number that can be used as an implied multiplication
    operand when implied multiplication is enabled and appropriate.
  */
  bool Number(double x);

  /*
  Description:
    Enter a number that will never use implied multiplication.
  */
  bool SimpleNumber(double x);

  /*
  Description:
    Enter an explicit multiplication operator whose operands
    are the previous value and the next value, where a value
    is a number, simple number, or parenthetic expression.
  */
  bool Multiply();

  /*
  Description:
    Enter an explicit division operator whose operands
    are the previous value and the next value, where a value
    is a number, simple number, or parenthetic expression.
    If the second value is zero, the calculator state
    is set to error.
  */
  bool Divide();

  /*
  Description:
    Enter an explicit addition operator whose operands
    are the previous value and the next value, where a value
    is a number, simple number, or parenthetic expression.
  */
  bool Add();

  /*
  Description:
    Enter an explicit subtraction operator whose operands
    are the previous value and the next value, where a value
    is a number, simple number, or parenthetic expression.
  */
  bool Subtract();

  /*
  Description:
    Enter an unary plus operator whose operand is the next
    number, simple number, or parenthetic expression.
  */
  bool UnaryPlus();

  /*
  Description:
    Enter an unary minus operator whose operand is the next
    number, simple number, or parenthetic expression.
  */
  bool UnaryMinus();

  /*
  Description:
    Begin a parenthetic expression.
  */
  bool LeftParenthesis();

  /*
  Description:
    End a parenthetic expression.
  */
  bool RightParenthesis();

  /*
  Description:
    Calculate the current value.
  */
  bool Evaluate(double* value);

  /*
  Description:
    Clear all status, values and expressions.
  */
  void ClearAll();

private:
  class ON_ArithmeticCalculatorImplementation* m_pCalc;
  double m_inplace_buffer[127]; // used for in-place construction of pCalc.
};

class ON_CLASS ON_LengthUnitName
{
public:
  ON_LengthUnitName() = default;
  ~ON_LengthUnitName() = default;
  ON_LengthUnitName(const ON_LengthUnitName&) = default;
  ON_LengthUnitName& operator=(const ON_LengthUnitName&) = default;

  static const ON_LengthUnitName None;

  /*
  Description:
    Get list of length unit names and abbreviations and their corresponding
    unit systems that are recognized by ON_ParseLengthUnitSystemName().

  Parameters:
    length_unit_list_capacity - [in]
      number of available elements in length_unit_list[]
      If length_unit_list_capacity is zero and length_unit_list is null,
      then the number of length unit names is returned.
    length_unit_list - [out]
      The list of length unit names is returned here.

  Returns:
    Number of length unit names and abbreviations.

  Example:
            unsigned int count = ON_GetLengthUnitNameList(0,0);
            ON_UnitName* length_unit_list = new (std::nothrow) ON_UnitName[capacity];
            count = ON_GetLengthUnitNameList(count,length_unit_list);
            ...
            delete[] length_unit_list;
  Remarks:
    If length_unit_list_capacity is zero and length_unit_list is null,
    then the number of length unit names is returned.
  */
  static unsigned int GetLengthUnitNameList( 
    size_t length_unit_list_capacity,
    class ON_LengthUnitName* length_unit_list
    );

  static ON_LengthUnitName Create(
    unsigned int locale_id,
    ON::LengthUnitSystem length_unit_system,
    bool bPlural
  );

  /*
  Description:
    Dictionary compare of all ON_LengthUnitName information in the order
    unit system, locale id, name, singular, plural
  */
  static int CompareUnitSystemLocaleIdName(
    const ON_LengthUnitName& a,
    const ON_LengthUnitName& b
  );

  /*
  Description:
    Dictionary compare of all ON_LengthUnitName information in the order
    locale id, unit system, name, singular, plural
  */  
  static int CompareLocaleIdUnitSystemName(
    const ON_LengthUnitName& a,
    const ON_LengthUnitName& b
  );

  unsigned int LocaleId() const;

  ON::LengthUnitSystem LengthUnit() const;

  /*
  Returns:
    True if the length unit system is set.
    False if length unit system is ON::LengthUnitSystem::None or ON::LengthUnitSystem::Unset.
  */
  bool LengthUnitIsSet() const;

  /*
  Returns:
    True if the length unit system is set or is ON::LengthUnitSystem::None
  */
  bool LengthUnitIsSetOrNone() const;

  /*
  Returns:
    True if the length unit system is set and the name is not empty.
    False if length unit system is ON::LengthUnitSystem::None or ON::LengthUnitSystem::Unset or the name is empty.
  */
  bool LengthUnitAndNameAreSet() const;

  /*
  Returns:
    A pointer to a localized length unit name or a pointer to an empty string.
  Remarks:
    Never returns nullptr.
  */
  const wchar_t* LengthUnitName() const;

  bool LengthUnitNameIsEmpty() const;

  bool LengthUnitNameIsNotEmpty() const;

  /*
  Remarks:
    True if the length unit name is singular in languages where that question
    has a meaningful answer.
  Remarks:
    Some names and name abbreviations are both singular and plural.
  */
  bool LengthUnitNameIsSingular() const;

  /*
  Remarks:
    True if the length unit name is plural in languages where that question
    has a meaningful answer.
  Remarks:
    Some names and name abbreviations are both singular and plural.
  */
  bool LengthUnitNameIsPlural() const;

private:
  // Microsoft locale id // http://msdn.microsoft.com/en-us/library/ms912047(v=winembedded.10).aspx
  unsigned int m_locale_id = 0; 
  ON::LengthUnitSystem m_length_unit_system = ON::LengthUnitSystem::None;        
  bool m_bNameIsSingular = false;
  bool m_bNameIsPlural = false;
  const wchar_t* m_name = nullptr;

private:
  static int Internal_Compare(
    unsigned int order_selector,
    const ON_LengthUnitName& a,
    const ON_LengthUnitName& b
  );
};

ON_DECL
bool operator==(
  const ON_LengthUnitName& a,
  const ON_LengthUnitName& b
  );

ON_DECL
bool operator!=(
  const ON_LengthUnitName& a,
  const ON_LengthUnitName& b
  );

class ON_CLASS ON_AngleUnitName
{
public:
  ON_AngleUnitName() = default;
  ~ON_AngleUnitName() = default;
  ON_AngleUnitName(const ON_AngleUnitName&) = default;
  ON_AngleUnitName& operator=(const ON_AngleUnitName&) = default;

  static const ON_AngleUnitName None;

  /*
  Description:
    Get list of angle unit names and abbreviations and their corresponding
    unit systems that are recognized by ON_ParseAngleUnitName().

  Parameters:
    angle_unit_list_capacity - [in]
      number of available elements in angle_unit_list[]
      If angle_unit_list_capacity is zero and angle_unit_list is null,
      then the number of angle unit names is returned.
    angle_unit_list - [out]
      The list of angle unit names is returned here.

  Returns:
    Number of angle unit names and abbreviations.

  Example:
            unsigned int count = ON_GetAngleUnitNameList(0,0);
            ON_UnitName* angle_unit_list = new (std::nothrow) ON_UnitName[capacity];
            count = ON_GetAngleUnitNameList(count,angle_unit_list);
            ...
            delete[] angle_unit_list;
  Remarks:
    If angle_unit_list_capacity is zero and angle_unit_list is null,
    then the number of angle unit names is returned.
  */
  static unsigned int GetAngleUnitNameList( 
    size_t angle_unit_list_capacity,
    class ON_AngleUnitName* angle_unit_list
    );

  static ON_AngleUnitName Create(
    unsigned int locale_id,
    ON::AngleUnitSystem angle_unit_system,
    bool bPlural
  );

  /*
  Description:
    Dictionary compare of all ON_LengthUnitName information in the order
    unit system, locale id, name, singular, plural
  */
  static int CompareUnitSystemLocaleIdName(
    const ON_AngleUnitName& a,
    const ON_AngleUnitName& b
  );

  /*
  Description:
    Dictionary compare of all ON_LengthUnitName information in the order
    locale id, unit system, name, singular, plural
  */  
  static int CompareLocaleIdUnitSystemName(
    const ON_AngleUnitName& a,
    const ON_AngleUnitName& b
  );

  unsigned int LocaleId() const;

  ON::AngleUnitSystem AngleUnit() const;

  /*
  Returns:
    True if the angle unit system is set.
    False if angle unit system is ON::AngleUnitSystem::None or ON::AngleUnitSystem::Unset.
  */
  bool AngleUnitIsSet() const;

  /*
  Returns:
    True if the angle unit system is set or is ON::AngleUnitSystem::None
  */
  bool AngleUnitIsSetOrNone() const;  

  /*
  Returns:
    True if the angle unit system is set and the name is not empty.
    False if length unit system is ON::AngleUnitSystem::None or ON::AngleUnitSystem::Unset or the name is empty.
  */
  bool AngleUnitAndNameAreSet() const;

  
  /*
  Returns:
    A pointer to a localized angle unit name or a pointer to an empty string.
  Remarks:
    Never returns nullptr.
  */
  const wchar_t* AngleUnitName() const;

  bool AngleUnitNameIsEmpty() const;

  bool AngleUnitNameIsNotEmpty() const;

  /*
  Remarks:
    True if the angle unit name is singular in languages where that question
    has a meaningful answer.
  Remarks:
    Some names and name abbreviations are both singular and plural.
  */
  bool AngleUnitNameIsSingular() const;

  /*
  Remarks:
    True if the angle unit name is plural in languages where that question
    has a meaningful answer.
  Remarks:
    Some names and name abbreviations are both singular and plural.
  */
  bool AngleUnitNameIsPlural() const;

private:
  // Microsoft locale id // http://msdn.microsoft.com/en-us/library/ms912047(v=winembedded.10).aspx
  unsigned int m_locale_id = 0; 
  ON::AngleUnitSystem m_angle_unit_system = ON::AngleUnitSystem::None;   
  bool m_bNameIsSingular = false;
  bool m_bNameIsPlural = false;
  const wchar_t* m_name = nullptr;

private:
  static int Internal_Compare(
    unsigned int order_selector,
    const ON_AngleUnitName& a,
    const ON_AngleUnitName& b
  );
};

ON_DECL
bool operator==(
  const ON_AngleUnitName& a,
  const ON_AngleUnitName& b
  );

ON_DECL
bool operator!=(
  const ON_AngleUnitName& a,
  const ON_AngleUnitName& b
  );

class ON_CLASS ON_ParseSettings
{
public:
  enum
  {
    // maximum number of wchar_t elements in a number
    max_number_str_count = 2000,

    // maximum number of wchar_t elements in an expression
    max_expression_str_count = 2147483645,
  };

  /*
  Description:
    The default constructor uses the default settings.
  */
  ON_ParseSettings();

  /*
  Description:
    Default settings constructor sets the context information.
  */
  ON_ParseSettings(
    const class ON_UnitSystem& context_length_unit_system,
    ON::AngleUnitSystem context_angle_unit_system,
    unsigned int context_locale_id
  );
  ON_ParseSettings(
    ON::LengthUnitSystem context_length_unit_system,
    ON::AngleUnitSystem context_angle_unit_system,
    unsigned int context_locale_id
  );

  /*
  Description:
    - The default settings parse just about everything in
      a reasonable way.  
    - Any angle values with unspecified units will be
      treated as radians. Angles without units can be
      encountered while parsing formulas, lengths and 
      points and need to be thoughtfully considered in
      most parsing situations.
  */
  static const ON_ParseSettings DefaultSettings;

  /*
  Description:
    - The default settings parse just about everything in
      a reasonable way.
    - Any angle values with unspecified units will be
      treated as radians. Angles without units can be
      encountered while parsing formulas, lengths and 
      points and need to be thoughtfully considered in
      most parsing situations.
  */
  static const ON_ParseSettings DefaultSettingsInRadians;

  /*
    Description:
    - The default settings parse just about everything in
      a reasonable way.
    - Any angle values with unspecified units will be
      treated as degrees. Angles without units can be
      encountered while parsing formulas, lengths and
      points and need to be thoughtfully considered in
      most parsing situations.
  */
  static const ON_ParseSettings DefaultSettingsInDegrees;

  /*
  Description:
    The integer settings parse and optional unary + or unary - and
    then parses one or more digits. Parsing stops after the last
    digit.
  */
  static const ON_ParseSettings IntegerNumberSettings;

  /*
  Description:
    The rational number settings parse and optional unary + or unary -
    and then parse one or more digits. If a rational number fraction
    bar follows the last digit in the numerator, then it is parsed
    and an integer denominator is parsed. The denominator cannot 
    have a unary + or - preceding the digits. Parsing stops after
    the last digit in the denominator.
  */
  static const ON_ParseSettings RationalNumberSettings;

  /*
  Description:
    The double number settings parse and optional unary + or unary -
    and then parse a number that can be integer, decimal, or 
    scientific e notation.
  */
  static const ON_ParseSettings DoubleNumberSettings;

  /*
  Description:
    The real number settings parse and optional unary + or unary -
    and then parse a number that can be integer, decimal, 
    scientific e notation or pi.  
  */
  static const ON_ParseSettings RealNumberSettings;

  /*
  Description:
    ON_ParseSetting::FalseSettings has all parsing options
    set to false.
  Remarks:
    A common use of ON_ParseSettings FalseSettings is to initialize
    ON_ParseSettings classes that are used to report what happened
    during parsing. Any parsing results value set to true after 
    parsing indicates that type of parsing occurred.
  */
  static const ON_ParseSettings FalseSettings;

  static const int Compare(
    const ON_ParseSettings* a,
    const ON_ParseSettings* b
    );

  ON_ParseSettings& operator|=(const ON_ParseSettings& other);
  ON_ParseSettings& operator&=(const ON_ParseSettings& other);


  /*
  Remarks:
    The default value is true.
  */
  bool ParseSpaceAsWhiteSpace() const;

  /*
  Remarks:
    The default value is true.
  */
  bool ParseNoBreakSpaceAsWhiteSpace() const;

  /*
  Remarks:
    The default value is true.
  */
  bool ParseHorizontalTabAsWhiteSpace() const;

  /*
  Remarks:
    The default value is true.
  */
  bool ParseThinSpaceAsWhiteSpace() const;

  /*
  Remarks:
    The default value is true.
  */
  bool ParseNoBreakThinSpaceAsWhiteSpace() const;

  /*
  Remarks:
    The default value is true.
  */
  bool ParseLineFeedAsLeadingWhiteSpace() const;

  /*
  Remarks:
    The default value is true.
  */
  bool ParseFormFeedAsLeadingWhiteSpace() const;

  /*
  Remarks:
    The default value is true.
  */
  bool ParseCarriageReturnAsLeadingWhiteSpace() const;

  /*
  Remarks:
    The default value is true.
  */
  bool ParseVerticalTabAsLeadingWhiteSpace() const;

  /*
  Remarks:
    The default value is true.
  */
  bool ParseLineFeedAsTrailingWhiteSpace() const;

  /*
  Remarks:
    The default value is true.
  */
  bool ParseFormFeedAsTrailingWhiteSpace() const;

  /*
  Remarks:
    The default value is true.
  */
  bool ParseCarriageReturnAsTrailingWhiteSpace() const;

  /*
  Remarks:
    The default value is true.
  */
  bool ParseVerticalTabAsTrailingWhiteSpace() const;


    /*
  Remarks:
    The default value is true.
  */
  void SetParseSpaceAsWhiteSpace( 
    bool bParseSpaceAsWhiteSpace );

  /*
  Remarks:
    The default value is true.
  */
  void SetParseNoBreakSpaceAsWhiteSpace( 
    bool bParseNoBreakSpaceAsWhiteSpace );

  /*
  Remarks:
    The default value is true.
  */
  void SetParseHorizontalTabAsWhiteSpace(
    bool bParseHorizontalTabAsWhiteSpace );

  /*
  Remarks:
    The default value is true.
  */
  void SetParseThinSpaceAsWhiteSpace(
    bool bParseThinSpaceAsWhiteSpace );

  /*
  Remarks:
    The default value is true.
  */
  void SetParseNoBreakThinSpaceAsWhiteSpace(
    bool bParseNoBreakThinSpaceAsWhiteSpace );

  /*
  Remarks:
    The default value is true.
  */
  void SetParseLineFeedAsLeadingWhiteSpace(
    bool bParseLineFeedAsLeadingWhiteSpace );

  /*
  Remarks:
    The default value is true.
  */
  void SetParseFormFeedAsLeadingWhiteSpace(
    bool bParseFormFeedAsLeadingWhiteSpace );

  /*
  Remarks:
    The default value is true.
  */
  void SetParseCarriageReturnAsLeadingWhiteSpace(
    bool bParseCarriageReturnAsLeadingWhiteSpace );

  /*
  Remarks:
    The default value is true.
  */
  void SetParseVerticalTabAsLeadingWhiteSpace( 
    bool bParseVerticalTabAsLeadingWhiteSpace );

  /*
  Remarks:
    The default value is true.
  */
  void SetParseLineFeedAsTrailingWhiteSpace(
    bool bParseLineFeedAsTrailingWhiteSpacee );

  /*
  Remarks:
    The default value is true.
  */
  void SetParseFormFeedAsTrailingWhiteSpace( 
    bool bParseParseFormFeedAsTrailingWhiteSpace );

  /*
  Remarks:
    The default value is true.
  */
  void SetParseCarriageReturnAsTrailingWhiteSpace(
    bool bParseParseCarriageReturnAsTrailingWhiteSpace );

  /*
  Remarks:
    The default value is true.
  */
  void SetParseVerticalTabAsTrailingWhiteSpace(
    bool bParseParseVerticalTabAsTrailingWhiteSpace );


  /*
  Returns:
    True if leading white space should be parsed.
  Remarks:
    The default value is true.
  */
  bool ParseLeadingWhiteSpace() const;

  /*
  Returns:
    True if a arithmetic should be parsed in expressions.
  Example:
    If parsing expression arithmetic is enabled, then the 
    string "3/0.25" will return a value of 12.
  Remarks:
    - The default value is true.
    - Currently multiplication and division are supported.
    - When parsing pi is enabled, strings like "2pi" will
      return 6.2831853071795865 even when parsing expression
      arithmetic is disabled.
    - When rational number or integer-dash-fraction parsing
      is enabled, strings like 3/4 will return 0.75 even when
      parsing expression arithmetic is disabled.
    - Parsing functions with the word "Expression" in their name,
      like ON_ParseNumberExpression, ON_ParseLengthExpression,
      and ON_ParseAngleExpression, support arithmetic parsing.
  */
  bool ParseArithmeticExpression() const;


  /*
  Returns:
    True if the math functions 
      sin, cos, tan
      asin, acos, atan, atan2,
      sinh, cosh, tanh,
      ln, exp, log10, pow,
    should be parsed in expressions.
  Remarks:
    - The default value is true.
    - In functions that take 2 or more parameter values, 
      a comma is used to separate parameter values.
    - Parentheses are used to delimit math function parameters;
      for example sin(pi/4).
    - The angle parameters to trigonometry functions may have angle
      units specified.  For example, sin(30degrees).  If no angle
      unit is specified, the number is assumed to be in radians.
  */
  bool ParseMathFunctions() const;

  /*
  Returns:
    True if a formulae contained bracketed on the left by
    =( and on the right by ) should be parsed in expressions.
  Example:
    If parsing expression formulae is enabled, then the string 
    "=((1+sqrt(5))/2)" will return a value of 1.6180339887498948.
  Remarks:
    - The default value is true. 
    - A formula is delimited at the start by =( and 
      terminated by a matching ).
    - Parsing functions with the word "Expression" in their name,
      like ON_ParseNumberExpression, ON_ParseLengthExpression,
      and ON_ParseAngleExpression, support formula parsing.
  */
  bool ParseExplicitFormulaExpression() const;

  /*
  Returns:
    True if a number may begin with a unary minus.
  Remarks:
    The default value is true.
  */
  bool ParseUnaryMinus() const;

  /*
  Returns:
    True if a number may begin with a unary plus.
  Remarks:
    The default value is true.
  */
  bool ParseUnaryPlus() const; 

  /*
  Returns:
    True if digits before a decimal point should be parsed
    in a decimal number or scientific E notation number.
  Remarks:
    The default value is true.
  */
  bool ParseSignificandIntegerPart() const;

  /*
  Returns:
    True if the decimal points should be parsed
    in a decimal number or scientific E notation number.
  Remarks:
    The default is true.
  */
  bool ParseSignificandDecimalPoint() const;

  /*
  Returns:
    True if digits after a decimal point should be parsed
    in a decimal number or scientific E notation number.
  Remarks:
    The default is true.
  */
  bool ParseSignificandFractionalPart() const;

  /*
  Returns:
    True if digit separators should be parsed in a 
    decimal number or scientific E notation number.
  Remarks:
    The default value is true.
  */
  bool ParseSignificandDigitSeparators() const;

  /*
  Returns:
    True if a number may use scientific E notation to specify
    multiplication by a power of 10.
  Example:
    If parsing scientific E notation is enables, then the string
    "2.99792458e8" will be parsed as 2999792458.
  Remarks:
    - The default value is true.
    - The "E" may be 'e', 'E', unicode decimal exponent symbol
      (code point 0x23E8).  
  See Also:
    ON_ParseSettings::ParseScientificDNotation.
  */
  bool ParseScientificENotation() const;

  /*
  Returns:
    True if a number may use scientific E notation may use
    'D' or 'E' to specify multiplication by a power of 10.
  Example:
    If parsing 'D' as 'E' in scientific E notation is enabled,
    then the string "2.99792458D8" will be parsed as 2999792458.
  Remarks:
    - The default value is false.
    - The "D" may be 'd', 'D'.
    - This feature is added to parse values in IGES files and
      text generated by FORTRAN programs.
  See Also:
    ON_ParseSettings::ParseScientificENotation.
  */
  bool ParseDAsExponentInScientificENotation() const;

  /*
  Returns:
    True if a full stop (period) should be parsed as a decimal point.
  Remarks:
    - The default value is true.
  See Also:
    ON_ParseSettings::ParseCommaAsDecimalPoint()
    ON_ParseSettings::ParseFullStopAsDigitSeparator()
    ON_ParseSettings::ParseCommaAsDigitSeparator()
  */
  bool ParseFullStopAsDecimalPoint() const;

  /*
  Returns:
    True if a full stop (period) should be parsed as a digit separator.
  Remarks:
    - The default value is false.
  See Also:
    ON_ParseSettings::ParseFullStopAsDecimalPoint()
    ON_ParseSettings::ParseCommaAsDecimalPoint()
    ON_ParseSettings::ParseCommaAsDigitSeparator()
    ON_ParseSettings::ParseSpaceAsDigitSeparator()
    ON_ParseSettings::ParseThinSpaceAsDigitSeparator()
    ON_ParseSettings::ParseNoBreakSpaceAsDigitSeparator()
    ON_ParseSettings::ParseNoBreakThinSpaceAsDigitSeparator()
  */
  bool ParseFullStopAsDigitSeparator() const;  

  /*
  Returns:
    True if a comma should be parsed as a decimal point.
  Remarks:
    - The default value is false.
  See Also:
    ON_ParseSettings::ParseFullStopAsDecimalPoint()
    ON_ParseSettings::ParseFullStopAsDigitSeparator()
    ON_ParseSettings::ParseCommaAsDigitSeparator()
  */
  bool ParseCommaAsDecimalPoint() const;

  /*
  Returns:
    True if a comma should be parsed as a digit separator.
  Remarks:
    - The default value is false.
  See Also:
    ON_ParseSettings::ParseFullStopAsDecimalPoint()
    ON_ParseSettings::ParseCommaAsDecimalPoint()
    ON_ParseSettings::ParseFullStopAsDigitSeparator()
    ON_ParseSettings::ParseSpaceAsDigitSeparator()
    ON_ParseSettings::ParseThinSpaceAsDigitSeparator()
    ON_ParseSettings::ParseNoBreakSpaceAsDigitSeparator()
    ON_ParseSettings::ParseNoBreakThinSpaceAsDigitSeparator()
  */
  bool ParseCommaAsDigitSeparator() const;

  /*
  Returns:
    True if a comma should be parsed as a digit separator.
  Remarks:
    - The default value is false.
  See Also:
    ON_ParseSettings::ParseFullStopAsDigitSeparator()
    ON_ParseSettings::ParseCommaAsDigitSeparator()
    ON_ParseSettings::ParseSpaceAsDigitSeparator()
    ON_ParseSettings::ParseThinSpaceAsDigitSeparator()
    ON_ParseSettings::ParseNoBreakSpaceAsDigitSeparator()
    ON_ParseSettings::ParseNoBreakThinSpaceAsDigitSeparator()
  */
  bool ParseSpaceAsDigitSeparator() const;

  /*
  Returns:
    True if a comma should be parsed as a digit separator.
  Remarks:
    - The default value is false.
  See Also:
    ON_ParseSettings::ParseFullStopAsDigitSeparator()
    ON_ParseSettings::ParseCommaAsDigitSeparator()
    ON_ParseSettings::ParseSpaceAsDigitSeparator()
    ON_ParseSettings::ParseThinSpaceAsDigitSeparator()
    ON_ParseSettings::ParseNoBreakSpaceAsDigitSeparator()
    ON_ParseSettings::ParseNoBreakThinSpaceAsDigitSeparator()
  */
  bool ParseThinSpaceAsDigitSeparator() const;

  /*
  Returns:
    True if a comma should be parsed as a digit separator.
  Remarks:
    - The default value is false.
  See Also:
    ON_ParseSettings::ParseFullStopAsDigitSeparator()
    ON_ParseSettings::ParseCommaAsDigitSeparator()
    ON_ParseSettings::ParseSpaceAsDigitSeparator()
    ON_ParseSettings::ParseThinSpaceAsDigitSeparator()
    ON_ParseSettings::ParseNoBreakSpaceAsDigitSeparator()
    ON_ParseSettings::ParseNoBreakThinSpaceAsDigitSeparator()
  */
  bool ParseNoBreakSpaceAsDigitSeparator() const;

  /*
  Returns:
    True if a comma should be parsed as a digit separator.
  Remarks:
    - The default value is true.
  See Also:
    ON_ParseSettings::ParseFullStopAsDigitSeparator()
    ON_ParseSettings::ParseCommaAsDigitSeparator()
    ON_ParseSettings::ParseSpaceAsDigitSeparator()
    ON_ParseSettings::ParseThinSpaceAsDigitSeparator()
    ON_ParseSettings::ParseNoBreakSpaceAsDigitSeparator()
    ON_ParseSettings::ParseNoBreakThinSpaceAsDigitSeparator()
  */
  bool ParseNoBreakThinSpaceAsDigitSeparator() const;

  /*
  Returns:
    True if a unicode hyphen-minus (code point 0x002D) should be parsed
    as a number dash during integer-dash-fraction parsing.
  Remarks:
    - The default value is true.  This is because the hyphen-minus
      character is the easiest to type. 
    - For robust parsing, use the unicode figure dash (code point 0x2012)
      to specify a number dash.
  See Also:
    ON_ParseSettings::ParseIntegerDashFraction()
    ON_ParseSettings::ParseHyphenMinusAsNumberDash()
    ON_ParseSettings::ParseHyphenAsNumberDash()
    ON_ParseSettings::ParseNoBreakHyphenAsNumberDash()
  */
  bool ParseHyphenMinusAsNumberDash() const;

  /*
  Returns:
    True if a unicode hyphen (code point 0x2010) should be parsed
    as a number dash during integer-dash-fraction parsing.
  Remarks:
    - The default value is false.
    - For robust parsing, use the unicode figure dash (code point 0x2012)
      to specify a number dash.
  See Also:
    ON_ParseSettings::ParseIntegerDashFraction()
    ON_ParseSettings::ParseHyphenMinusAsNumberDash()
    ON_ParseSettings::ParseHyphenAsNumberDash()
    ON_ParseSettings::ParseNoBreakHyphenAsNumberDash()
  */
  bool ParseHyphenAsNumberDash() const;

  /*
  Returns:
    True if a unicode non-breaking hyphen (code point 0x2011) 
    should be parsed as a number dash during integer-dash-fraction 
    parsing.
  Remarks:
    - The default value is false.
    - For robust parsing, use the unicode figure dash (code point 0x2012)
      to specify a number dash.
  See Also:
    ON_ParseSettings::ParseIntegerDashFraction()
    ON_ParseSettings::ParseHyphenMinusAsNumberDash()
    ON_ParseSettings::ParseHyphenAsNumberDash()
    ON_ParseSettings::ParseNoBreakHyphenAsNumberDash()
  */
  bool ParseNoBreakHyphenAsNumberDash() const;
      
  /*
  Returns:
    True if rational numbers should be parsed.
  Example:
    If this property is true, then strings "3/4" and "8/5"
    will be parsed.  The numerator and denominator must
    parse as integers.  If you: decimal points and scientific notation
    cannot appear
  Remarks:
    - The default value is true.
    - The numerator and denominator must be integers.
    - Strings like "1.0/3.0", "3.5/2" or "pi/2" are not parsed
      as rational numbers. Use ON_ParseSettings::ParseDivision
      to control parsing of these types of strings.
  */
  bool ParseRationalNumber() const;

  /*
  Returns:
    True if the value of pi may be specified as "pi", "PI", 
    "Pi", "pI", unicode Greek capital letter pi (code point 0x03A0),
    or unicode Greek small letter pi (code point 0x03C0).
  Example:
    If this property is true, then strings "pi", "PI", "Pi", "pI",
    L"\x03A0" (unicode greek capital letter pi)  and 
    L"\x03C0" (unicode greek small letter pi) 
    will be parsed as if they were "3.141592653589793238462643".
    In addition, if the pi strings appear next to something that
    is parsed as a number, the result will be multiplied by pi. 
    For example, 
      "3pi" and pi3.0 will return 3.0*ON_PI. 
      If division parsing is enabled, then "3pi/4" and 3/4pi" will
      return 0.75*ON_PI.
  Remarks:
    The default value is true.
  */
  bool ParsePi() const;

  /*
  Returns:
    True if multiplication signs that appear between numbers will be
    parsed.
  Example:
    If this property is true, then strings like 2*3 will be parsed
    as 6.0
  Remarks:
    - The default value is true.
    - Parsing functions with the word "Expression" in their name,
      like ON_ParseNumberExpression, ON_ParseLengthExpression,
      and ON_ParseAngleExpression, support multiplication parsing.
  */
  bool ParseMultiplication() const;

  /*
  Returns:
    True if division signs that appear between numbers will be
    parsed.
  Example:
    If this property is true, then strings like 1/4 will be parsed
    as 0.25.
  Remarks:
    - The default value is true.
    - Parsing functions with the word "Expression" in their name,
      like ON_ParseNumberExpression, ON_ParseLengthExpression,
      and ON_ParseAngleExpression, support division parsing.
  */
  bool ParseDivision() const;

  /*
  Returns:
    True if addition signs that appear between numbers will be
    parsed.
  Example:
    If this property is true, then strings like 1+2 will be parsed
    as 3.
  Remarks:
    - The default value is true.
    - Parsing functions with the word "Expression" in their name,
      like ON_ParseNumberExpression, ON_ParseLengthExpression,
      and ON_ParseAngleExpression, support division parsing.
  */
  bool ParseAddition() const;

  /*
  Returns:
    True if subtraction signs that appear between numbers will be
    parsed.
  Example:
    If this property is true, then strings like 2-1 will be parsed
    as 1.
  Remarks:
    - The default value is true.
    - Parsing functions with the word "Expression" in their name,
      like ON_ParseNumberExpression, ON_ParseLengthExpression,
      and ON_ParseAngleExpression, support division parsing.
  */
  bool ParseSubtraction() const;


  /*
  Returns:
    True if paired parentheses symbols that are encountered during
    number parsing will be parsed.
  Example:
    If this property is true, then strings like 2(3+4) will be parsed
    as 14.
  Remarks:
    - The default value is true.
    - Parsing functions with the word "Expression" in their name,
      like ON_ParseNumberExpression, ON_ParseLengthExpression,
      and ON_ParseAngleExpression, support division parsing.
  */
  bool ParsePairedParentheses() const;  
  
  /*
  Returns:
    True if a number may be specified as an integer followed by
    a dash and a fraction.
  Example:
    If this property is true, then the string "4-3/8" will return
    a value of 4.375.
  Remarks:
    - The default value is true.
    - The numerator must be an integer > 0.
    - The denominator must be greater than the numerator.
    - ON_ParseSettings::IsNumberDash() controls what characters
      are interpreted as number dashes.
  See Also:
    ON_ParseSettings::ParseRationalNumber()
  */
  bool ParseIntegerDashFraction() const;

  /*
  Returns:
    True if a length value may be specified as combination
    of US customary feet and inch lengths.
  Example:
    If this property is true, then strings like these
      1'-4-3/8"
      1ft-3-3/8in
      1'4.375"
      1.0feet4.375inches
    will be parsed as 16.375 inches.
  Remarks:
    The default value is true.
  */
  bool ParseFeetInches() const;

  /*
  Returns:
    True if an angle value may be specified as a combination of
    arc degrees, arc minutes and arc seconds.
  Example:
    If this property is true, then strings like these
      2degrees30minutes
      2deg30'
    will be parsed as 2.0*60.0 + 30.0 arc minutes
      2degrees14minutes15seconds
      2deg14'15"
    will be parsed as (2*60.0 + 14.0)*60.0 + 15.0 arc seconds.
  Remarks:
    The default value is true.
  */
  bool ParseArcDegreesMinutesSeconds() const;


  /*
  Returns:
    True if whitespace between a value and unit system will
    is permitted.
  Example:
    If this property is true, then strings like these
      2 meters
      2meters
      2 m
      2m
    will be parsed as 2 meters
  Remarks:
    The default value is true.
  */
  bool ParseWhiteSpaceBetweenValueAndUnitSystem() const;

  /*
  Returns:
    True if whitespace between a length in feet and a length in inches
    will is permitted.
  Example:
    If this property is true, then strings like these
      1'3"
      1' 3"
      1ft3in
      1ft 3in
    will be parsed as 15 inches
  Remarks:
    The default value is true.
  */
  bool ParseWhiteSpaceBetweenFeetAndInches() const;


  /*
  Returns:
    True if an angle values may be specified using surveyor's notation.
  Example:
    If this property is true, then strings like these
      N30W
      S12<degree symbol>15'22"W
      N45.7899E
      S47'E
    will be parsed as angles.
  Remarks:
    The first character must be N, n, S or s.
    The angle must be a specified as a combination of arc degrees,
    arc minutes and arc seconds.
    The last character must be E, e, W or w.
  */
  bool ParseSurveyorsNotation() const;

  /*
  Returns:
    The Microsoft locale id that identifies the locale that should
    be used to resolve ambiguous parsing situations. The default
    value is zero, which means ambiguous situations are not parsed.
  Example:
    When parsing angles, the string "Grad" is ambiguous. 
    In German "Grad" identifies arc degree angle units and in
    English "Grad" identifies gradian angle units. If angle parsing
    encounters "Grad", it uses the value of ContextLocaleId()
    to determine what arc unit system is being identified.
  */
  unsigned int ContextLocaleId() const;

  /*
  Returns:
    The default angle unit system that is used when a value must be
    parsed as an angle and no angle unit system is explicitly or 
    implicitly specified.
  */
  ON::LengthUnitSystem ContextLengthUnitSystem() const;
  
  /*
  Returns:
    The default angle unit system that is used when a value must be
    parsed as an angle and no angle unit system is explicitly or 
    implicitly specified.
  */
  ON::AngleUnitSystem ContextAngleUnitSystem() const;
  
  /*
  Description:
    Deprecated. Use ContextLocaleId().
  */
  // ON_DEPRECTATED
  unsigned int PreferedLocaleId() const;

  /*
  Description:
    Deprecated. Use ContextAngleUnitSystem().
  */
  // ON_DEPRECTATED
  ON::AngleUnitSystem DefaultAngleUnitSystem() const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as leading white space
  */
  bool IsLeadingWhiteSpace(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as trailing white space
  */
  bool IsTrailingWhiteSpace(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as interior white space.
  */
  bool IsInteriorWhiteSpace(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as unary minus
  */
  bool IsUnaryMinus(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as unary plus
  */
  bool IsUnaryPlus(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    Returns '0' through '9' if c is a digit, otherwise returns 0.
  */
  char IsDigit(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as a digit separator
  */
  bool IsDigitSeparator(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as a decimal point
  */
  bool IsDecimalPoint(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as decimal exponent symbol
  */
  bool IsDecimalExponentSymbol(ON__UINT32 c) const; // e E (optionally d and/or D)

  /*
  Parameters:
    c - [in]
  Returns:
    True if c is 0x03A or 0x03C
  */
  bool IsGreekPi(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as a multiplication operator
  */
  bool IsMultiplicationSymbol(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as a division operator
  */
  bool IsDivisionSymbol(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as an addition operator
  */
  bool IsAdditionSymbol(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as a subtraction operator
  */
  bool IsSubtractionSymbol(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as a left parenthesis symbol
  */
  bool IsLeftParenthesisSymbol(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as a right parenthesis symbol
  */
  bool IsRightParenthesisSymbol(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as a rational number fraction bar
  */
  bool IsRationalNumberFractionBar(ON__UINT32 c) const;

  /*
  Parameters:
    c - [in]
  Returns:
    True if c should be parsed as number dash when parsing
    strings like "1-3/4".
  */
  bool IsNumberDash(ON__UINT32 c) const;

  /*
  Parameters:
    bParseLeadingWhiteSpace - [in]
      True if leading white space should be parsed.
  Remarks:
    See ON_ParseSettings::ParseLeadingWhiteSpace()
    for details about this property.
  */
  void SetParseLeadingWhiteSpace(
    bool bParseLeadingWhiteSpace
    );

  /*
  Parameters:
    bParseArithmeticExpression - [in]
      True if formulae should be parsed.
  Remarks:
    See ON_ParseSettings::ParseArithmeticExpression()
    for details about this property.
  */
  void SetParseArithmeticExpression(
    bool bParseArithmeticExpression
    );

  /*
  Parameters:
    bParseMathFunctions - [in]
      True if math functions should be parsed in expressions.
  Remarks:
    See ON_ParseSettings::ParseMathFunctions()
    for details about this property.
  */
  void SetParseMathFunctions(
    bool bParseMathFunctions
    );
  
  /*
  Parameters:
    bParseExplicitFormulaExpression - [in]
      True if explicitly formulae should be parsed.
  Remarks:
    See ON_ParseSettings::ParseExplicitFormulaExpression()
    for details about this property.
  */
  void SetParseExplicitFormulaExpression(
    bool bParseExplicitFormulaExpression
    );

  /*
  Parameters:
    bParseUnaryMinus - [in]
      True if unary minus should be parsed.
  Remarks:
    See ON_ParseSettings::ParseUnaryMinus()
    for details about this property.
  */
  void SetParseUnaryMinus(
    bool bParseUnaryMinus
    );

  /*
  Parameters:
    bParseUnaryPlus - [in]
      True if unary plus should be parsed.
  Remarks:
    See ON_ParseSettings::ParseUnaryPlus()
    for details about this property.
  */
  void SetParseUnaryPlus(
    bool bParseUnaryPlus
    ); 

  /*
  Parameters:
    bParseSignificandIntegerPart - [in]
      True if digits before a decimal point in a decimal
      number or the significand of a scientific E notation
      number should be parsed.
  Remarks:
    See ON_ParseSettings::ParseSignificandIntegerPart()
    for details about this property.
  */
  void SetParseSignificandIntegerPart(
      bool bParseSignificandIntegerPart
    ); 

  /*
  Parameters:
    bParseSignificandDecimalPoint - [in]
      True if a decimal point in a decimal point in a decimal
      number or the significand of a scientific E notation
      number should be parsed.
  Remarks:
    See ON_ParseSettings::ParseSignificandDecimalPoint()
    for details about this property.
  */
  void SetParseSignificandDecimalPoint(
      bool bParseSignificandDecimalPoint
    ); 

  /*
  Parameters:
    bParseSignificandFractionalPart - [in]
      True if digits after the decimal point in a decimal
      number or the significand of a scientific E notation
      number should be parsed.
  Remarks:
    See ON_ParseSettings::ParseSignificandFractionalPart()
    for details about this property.
  */
  void SetParseSignificandFractionalPart(
      bool bParseSignificandFractionalPart
    ); 

  /*
  Parameters:
    bParseSignificandDigitSeparators - [in]
      True if digit separators in a decimal number or a significand
      of a scientific E notation number should be parsed.
  Remarks:
    See ON_ParseSettings::ParseSignificandDigitSeparators()
    for details about this property.
  */
  void SetParseSignificandDigitSeparators(
    bool bParseSignificandDigitSeparators
    );

  /*
  Parameters:
    bDecimalPoint - [in]
      True if a decimal point should be parsed.
  Remarks:
    See ON_ParseSettings::ParseDecimalPoint()
    for details about this property.
  */
  void SetParseDecimalPoint(
    bool bParseDecimalPoint
    );

  /*
  Parameters:
    bParseDAsExponentInScientificENotation - [in]
      True if both 'D' and 'E' can mark the beginning
      of the exponent in scientific E notation.
  Remarks:
    See ON_ParseSettings::ParseDAsExponentInScientificENotation()
    for details about this property.
  */
  void SetParseDAsExponentInScientificENotation(
    bool bParseDAsExponentInScientificENotation
    );

  /*
  Parameters:
    bParseScientificENotation - [in]
      True if scientific E notation should be parsed.
  Remarks:
    See ON_ParseSettings::ParseScientificENotation()
    for details about this property.
  */
  void SetParseScientificENotation(
    bool bParseScientificENotation
    );

  void SetParseFullStopAsDecimalPoint( bool bParse );
  void SetParseFullStopAsDigitSeparator( bool bParse );
  void SetParseCommaAsDecimalPoint( bool bParse );
  void SetParseCommaAsDigitSeparator( bool bParse );
  void SetParseSpaceAsDigitSeparator( bool bParse );
  void SetParseThinSpaceAsDigitSeparator( bool bParse );
  void SetParseNoBreakSpaceAsDigitSeparator( bool bParse );
  void SetParseNoBreakThinSpaceAsDigitSeparator( bool bParse );
  void SetParseHyphenMinusAsNumberDash( bool bParse );
  void SetParseHyphenAsNumberDash( bool bParse );
  void SetParseNoBreakHyphenAsNumberDash( bool bParse );

  /*
  Parameters:
    bParseRationalNumber - [in]
      True if rational numbers like 3/4 and 8/5 
      should be parsed.
  Remarks:
    See ON_ParseSettings::ParseRationalNumber()
    for details about this property.
  */
  void SetParseRationalNumber(
    bool bParseRationalNumber
    );

  /*
  Parameters:
    bParsePi - [in]
      True if number parsing should treat "PI", "Pi" "pi", 
      and unicode code points 0x03A0 and 0x03C0 as 
      3.141592653589793238462643.
  Remarks:
    See ON_ParseSettings::ParsePi()
    for details about this property.
  */
  void SetParsePi(
    bool bParsePi
    );

  /*
  Parameters:
    bParseMultiplication - [in]
      True if multiplication should be permitted in number parsing.
  Remarks:
    See ON_ParseSettings::ParseMultiplication()
    for details about this property.
  */
  void SetParseMultiplication(
    bool bParseMultiplication
    );

  /*
  Parameters:
    bParseDivision - [in]
      True if division should be permitted in number parsing.
  Remarks:
    See ON_ParseSettings::ParseDivision()
    for details about this property.
  */
  void SetParseDivision(
    bool bParseDivision
    );

  /*
  Parameters:
    bParseDivision - [in]
      True if addition should be permitted in number parsing.
  Remarks:
    See ON_ParseSettings::ParseAddition()
    for details about this property.
  */
  void SetParseAddition(
    bool bParseAddition
    );

  /*
  Parameters:
    bParseDivision - [in]
      True if subtraction should be permitted in number parsing.
  Remarks:
    See ON_ParseSettings::ParseSubtraction()
    for details about this property.
  */
  void SetParseSubtraction(
    bool bParseSubtraction
    );

  /*
  Parameters:
    bParseDivision - [in]
      True if paired parentheses should be permitted in number parsing.
  Remarks:
    See ON_ParseSettings::PairedParentheses()
    for details about this property.
  */
  void SetParsePairedParentheses(
    bool bParsePairedParentheses
    );

  /*
  Parameters:
    bParseIntegerDashFraction - [in]
      True if strings like "5-3/8" should be parsed as
      a single number
  Remarks:
    See ON_ParseSettings::ParseIntegerDashFraction()
    for details about this property.
  */
  void SetParseIntegerDashFraction(
    bool bParseIntegerDashFraction
    );

  /*
  Parameters:
    bParseFeetInches - [in]
      True if length value parsing should parse strings 
      like 1'4-3/8" and return a length value of 16.375 inches.
  Remarks:
    See ON_ParseSettings::ParseFeetInches()
    for details about this property.
  */
  void SetParseFeetInches(
    bool bParseFeetInches
    );

  /*
  Parameters:
    bParseArcDegreesMinutesSeconds - [in]
      True if angle value parsing should parse strings 
      like 2deg17'15" and return a length value of 
      ((2.0*60.0 + 17..0)*60.0 + 15.0) arc seconds
  Remarks:
    See ON_ParseSettings::ParseArcDegreesMinutesSeconds()
    for details about this property.
  */
  void SetParseArcDegreesMinutesSeconds(
    bool bParseArcDegreesMinutesSeconds
    );

  /*
  Parameters:
    bParseWhiteSpaceBetweenValueAndUnitSystem - [in]
    True if then strings like these
      2 meters
      2meters
      2 m
      2m
    should be parsed as 2 meters.
  Remarks:
    See ON_ParseSettings::ParseWhiteSpaceBetweenValueAndUnitSystem()
    for details about this property.
  */
  void SetParseWhiteSpaceBetweenValueAndUnitSystem(
    bool bParseWhiteSpaceBetweenValueAndUnitSystem
    );

  /*
  Parameters:
    bParseWhiteSpaceBetweenFeetAndInches - [in]
    True if strings like these
      1' 3"
      1ft 3in
    will be parsed as 15 inches
  Remarks:
    See ON_ParseSettings::ParseWhiteSpaceBetweenFeetAndInches()
    for details about this property.
  */
  void SetParseWhiteSpaceBetweenFeetAndInches(
    bool bParseWhiteSpaceBetweenFeetAndInches
    );

  /*
  Parameters:
    bParseSurveyorsNotation - [in]
      True if angle value parsing should parse
      surveyor's notation like N30W.
  Remarks:
    See ON_ParseSettings::ParseSurveyorsNotation()
    for details about this property.
  */
  void SetParseSurveyorsNotation(
    bool bParseSurveyorsNotation
    );

  /*
  Description:
    Set the preferred locale id for parsing unit names.  This local
    id is used to resolve ambiguous unit names.

  Parameters:
    prefered_locale_id - [in]
      The Microsoft locale id that identifies the locale that should
      be used to resolve ambiguous parsing situations.  The default
      value is zero, which means ambiguous situations are not parsed.

  Example:
    When parsing angles, the string "Grad" is ambiguous. 
    In German "Grad" identifies arc degree angle units and in
    English "Grad" identifies gradian angle units. If angle parsing
    encounters "Grad" and the preferred locale id is 1031 (de-de),
    then parsing reports the angle value as arc degree units.
    If angle parsing encounters "Grad" and the preferred locale id 
    is 1033 (en-us), then parsing reports the angle values as
    gradian units.
  */
  void SetContextLocaleId(
    unsigned int context_locale_id
    );

  /*
  Description:
    The context angle unit system determines what length unit system
    is used when a value must be parsed as a length with units and no
    length unit system is explicitly or implicitly specified. The default
    is ON::LengthUnitSystem::None. 

  Parameters:
    context_length_unit_system - [in]
      ON::LengthUnitSystem::Custom and ON::LengthUnitSystem::Unset
      select ON::LengthUnitSystem::None.
  */
  void SetContextLengthUnitSystem(
    ON::LengthUnitSystem context_length_unit_system
    );

  /*
  Description:
    The context angle unit system determines what angle unit system
    is used when a value must be parsed as an angle and no angle
    unit system is explicitly or implicitly specified. The default
    is ON::LengthUnitSystem::Radians. 

  Parameters:
    default_angle_unit_system - [in]
      ON::AngleUnitSystem::None and ON::AngleUnitSystem::Unset
      select ON::LengthUnitSystem::Radians.
  */
  void SetContextAngleUnitSystem(
    ON::AngleUnitSystem context_angle_unit_system
    );

  /*
  Description:
    Deprecated. Use SetConextLocaleId().
  */
  // ON_DEPRECTATED
  void SetPreferedLocaleId(
    unsigned int context_locale_id
    );
  /*
  Description:
    Deprecated. Use SetContextAngleUnitSystem().
  */
  // ON_DEPRECTATED
  void SetDefaultAngleUnitSystem(
    ON::AngleUnitSystem context_angle_unit_system
    );

  /*
  Description:
    Set every possible setting to false or zero.
  */
  void SetAllToFalse();


  /*
  Description:
    Set every possible expression parsing setting to false.
  Remarks:
    This is a simple way to disable all possible parsing of
    expressions. This function calls
    this->SetParseExplicitFormulaExpression(false);
    this->SetParseArithmeticExpression(false);
    this->SetParseMultiplication(false);
    this->SetParseDivision(false);  
    this->SetParseAddition(false);
    this->SetParseSubtraction(false);
    this->SetParseMathFunctions(false);
    this->SetParseMathFunctions(false);
    this->SetParsePairedParentheses(false);
  */
  void SetAllExpressionSettingsToFalse();


  /*
  Returns:
    True if any of the following are true.
      ParseInvalidExpressionError()
      ParseDivideByZeroError()
      ParseOverflowError()
  */
  bool ParseError() const;

  /*
  Returns:
    True if parsing and expression resulted in a divide by zero.
  */
  bool ParseDivideByZeroError() const;

  /*
  Returns:
    True if parsing and expression created a number that a double
    cannot represent.
  */
  bool ParseOverflowError() const;
  
  /*
  Returns:
    True if parsing and expression failed because the expression
    did not make sense.
  */
  bool ParseInvalidExpressionError() const;

  void SetParseDivideByZeroError(
    bool bParseDivideByZeroError
    );

  void SetParseOverflowError(
    bool bParseOverflowError
    );

  void SetParseInvalidExpressionError(
    bool bParseInvalidExpressionError
    );

private:
  // default constructor sets all elements to zero.
  ON__UINT32 m_true_default_bits[2];  // a "0" bit is true  - used for defaults that are true
  ON__UINT32 m_false_default_bits[2]; // a "0" bit is false - used for defaults that are false

  ON__UINT32 m_reserved_bits = 0;

  // The value of m_context_locale_id is used to resolve
  // ambiguities that occur when parsing unit system names.
  // In German "Grad" identifies arc degree angle units and in
  // English "Grad" identifies gradian angle units. If angle parsing
  // encounters "Grad", it uses the value of m_context_locale_id
  // to determine what arc unit system is being identified.
  ON__UINT16 m_context_locale_id = 0;

  // The value of m_context_angle_unit_system determines the
  // angle unit system that is used when a value must be parsed
  // as an angle and no angle unit system is explicitly or 
  // implicitly specified.
  // If m_default_angle_unit_system is 0, then radians are used.  
  // If m_default_angle_unit_system is not 0 and is equal to an
  // ON::AngleUnitSystem value, that angle unit system is used.
  // In all other cases, radians are used.
  ON__UINT8 m_context_angle_unit_system = 0;

  // The value of m_context_length_unit_system determines the
  // length unit system that is used when a value must be parsed
  // as a length and no length unit system is explicitly or 
  // implicitly specified.
  // If m_context_length_unit_system is 0, then it is ignored.
  // If m_context_length_unit_system is not 0 and is equal to an
  // ON::LengthUnitSystem value, that length unit system is used.
  // Presently this value is not relevant to internal parsing code,
  // but may be passed along in parse settings to code that
  // use parsing.
  ON__UINT8 m_context_length_unit_system = 0;

  ON__UINT64 m_reserved = 0;

private:
  void Internal_DefaultCtor();
};

/*
Descriptions:
  result true if a and b are identical.
*/
ON_DECL
bool operator==(
  const class ON_ParseSettings& a,
  const class ON_ParseSettings& b
  );

/*
Descriptions:
  result true if a and b are not identical.
*/
ON_DECL
bool operator!=(
  const class ON_ParseSettings& a,
  const class ON_ParseSettings& b
  );

/*
Descriptions:
  result setting value = a setting value OR b setting value
Returns:
  Logical OR of the parse settings in a and b.
*/
ON_DECL
ON_ParseSettings operator&&(
  const class ON_ParseSettings& a,
  const class ON_ParseSettings& b
  );

/*
Descriptions:
  result setting value = a setting value AND b setting value
Returns:
  Logical AND of the parse settings in a and b.
*/
ON_DECL
ON_ParseSettings operator||(
  const class ON_ParseSettings& a,
  const class ON_ParseSettings& b
  );

/*
Description:
  Parses str to determine if it specifies a number.

Parameters:
  str - [in]

  str_count - [in]
    str[] and str_count specify the string to parse.
    If str_count >= 0. it specifies the maximum number of elements in str[]
    that may be parsed.  If str_count = -1, then the string must contain a 
    character that terminates number parsing.  This character can
    be a null, arithmetic operator, or a unicode 
    code point <= 0x0020 (0x0020 = space = 32 decimal).

 parse_settings - [in]
   The value of parse_settings controls what input may be parsed.
   Use one of the predefined
     ON_ParseSettings::DefaultSettings
     ON_ParseSettings::IntegerNumberSettings
     ON_ParseSettings::RationalNumberSettings
     ON_ParseSettings::RealNumberSettings
   for common parsing tasks.

 parse_results - [out]
   The value of parse_results reports what was parsed.

 value - [out]
   The value of the parsed number.

Returns:
  Number of elements of str[] that were parsed. 
  A return value of 0 indicates that str[] could not be 
  parsed as a number.

See Also:
  ON_ParseNumberExpression
  ON_ParseLengthExpression
  ON_ParseAngleExpression
*/
ON_DECL
int ON_ParseNumber( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  ON_ParseSettings* parse_results,
  double* value
  );

/*
Description:
  Parses str to determine if it specifies a number.
  Expression parsing includes support for parsing in-line multiplication,
  in-line division, automatic multiplication by pi, and formula parsing.

Parameters:
  str - [in]

  str_count - [in]
    str[] and str_count specify the string to parse.
    If str_count >= 0. it specifies the maximum number of elements in str[]
    that may be parsed.  If str_count = -1, then the string must contain a 
    character that terminates number parsing.  This character can
    be a null, arithmetic operator, or a unicode 
    code point <= 0x0020 (0x0020 = space = 32 decimal).

 parse_settings - [in]
   The value of parse_settings controls what input may be parsed.
   Use one of the predefined
     ON_ParseSettings::DefaultSettings
     ON_ParseSettings::IntegerNumberSettings
     ON_ParseSettings::RationalNumberSettings
     ON_ParseSettings::RealNumberSettings
   for common parsing tasks.

 parse_results - [out]
   The value of parse_results reports what was parsed.

 value - [out]
   The value of the parsed number.

Returns:
  Number of elements of str[] that were parsed. 
  A return value of 0 indicates that str[] could not be 
  parsed as a number.

See Also:
  ON_ParseNumber
  ON_ParseLengthExpression
  ON_ParseAngleExpression
*/
ON_DECL
int ON_ParseNumberExpression( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  ON_ParseSettings* parse_results,
  double* value
  );

/*
Description:
  Parses str if it is a recognized length unit system name or abbreviation. 

Parameters:
  str - [in]

  str_count - [in]
    str[] and str_count specify the string to parse.
    If str_count >= 0. it specifies the maximum number of elements in str[]
    that may be parsed.  If str_count = -1, then the string must contain a 
    character that terminates unit system name parsing.  This character can
    be a null, digit, punctuation, arithmetic operator, or a unicode 
    code point <= 0x0020 (0x0020 = space = 32 decimal).

  prefered_locale_id - [in]
    If the parsed length unit name identifies different length unit systems
    in different locales, then this value is used to resolve the
    ambiguity.  A list of Microsoft locale id values can be found at
    http://msdn.microsoft.com/en-us/library/ms912047(v=winembedded.10).

  bParseLeadingWhitespace - [in]
    If true, leading white space will be parsed.
    If false, the unit name must begin with element str[0].

  length_unit_system - [out] (can be null)
    If length_unit_system is not null, it is set to identify the unit
    system specified by str.  If str does not identify a known unit 
    system, then *length_unit_system is set to ON::LengthUnitSystem::None.


Returns:
  Number of elements of str that were parsed. A return value of
  0 indicates that str did not match know unit system names or 
  abbreviations.

Remarks:
  Currently common names and abbreviations for millimeters, centimeters,
  meters and kilometers are supported in Czech (cs-*), English (en-*),
  French (fr-*), German (de-*), Portuguese (pt-*) and Spanish (es-*).

  Common names and abbreviations for the following United States customary
  length units are supported in United States English (en-US). 
    If the first element of str is quotation mark (double quote), unicode 
    code point 0x0022, the string is parsed as United States customary inch.
    If the first element of str is apostrophe, unicode code point 0x0027, 
    the string is parsed as United States customary foot. 
    All conversions to meters are exact.
      microinch =    2.54e-8 meters (1.0e-6 inches)
      mil       =    2.54e-5 meters (0.001 inches)
      inch      =    0.0254  meters (1/12 foot)
      foot      =    0.3048  meters (12 inches)
      yard      =    0.9144  meters (36 inches)
      mile      = 1609.344   meters (5280 feet) (US statue or land mile)
*/
ON_DECL
int ON_ParseLengthUnitName( 
  const wchar_t* str,
  int str_count,
  int prefered_locale_id,
  ON::LengthUnitSystem* length_unit_system
  );

ON_DECL
int ON_ParseLengthUnitName( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  ON::LengthUnitSystem* length_unit_system
  );

/*
Description:
  Parses str to determine if it specifies a length value.

Parameters:
  str - [in]

  str_count - [in]
    str[] and str_count specify the string to parse.
    If str_count >= 0, it specifies the maximum number of elements in str[]
    that may be parsed.  If str_count = -1, then the string must contain a 
    character that terminates length parsing.

 parse_settings - [in]
   The input parse_settings parameter controls what input may be
   parsed and how it is parsed.
   Use ON_ParseSettings::DefaultSettings for common parsing tasks.

 length_value_unit_system - [in]
   Length unit system for the returned value.  
   For example, if you want the returned value to be in meters,
   you would specify ON::LengthUnitSystem::Meters here. If you want to use custom
   units, you must use the override with the ON_UnitSystem
   parameter.

 length_value - [out]
   The value of the parsed length.
   
 parse_results - [out] (input pointer can be null)
   The output parse_results parameter reports what was parsed.
   
 str_length_unit_system - [out] (input pointer can be null)
   length unit in the parsed string. When the 
   length_value_unit_system specifies a unit system and a
   a different length unit system is parsed, the number returned
   in length_value is always converted to the unit system 
   specified by the length_value_unit_system parameter.
   If needed, you can inspect str_length_unit_system to determine
   if the length unit system scaling was applied.

Returns:
  Number of elements of str that were parsed. A return value of
  0 indicates that str could not be parsed as a length value.
*/
ON_DECL
int ON_ParseLengthExpression( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  double* length_value,
  ON_ParseSettings* parse_results,
  ON::LengthUnitSystem* str_length_unit_system
  );

ON_DECL
int ON_ParseLengthExpression( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  ON::LengthUnitSystem length_value_unit_system,
  double* length_value,
  ON_ParseSettings* parse_results,
  ON::LengthUnitSystem* str_length_unit_system
  );

ON_DECL
int ON_ParseLengthExpression( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  const ON_UnitSystem& length_value_unit_system,
  double* length_value,
  ON_ParseSettings* parse_results,
  ON::LengthUnitSystem* str_length_unit_system
  );

ON_DECL
int ON_ParseLengthExpression( 
  const wchar_t* str,
  int str_count,
  ON::AngleUnitSystem default_str_angle_unit_system,
  ON::LengthUnitSystem length_value_unit_system,
  double* length_value
  );

ON_DECL
int ON_ParseLengthExpression( 
  const wchar_t* str,
  int str_count,
  ON::AngleUnitSystem default_str_angle_unit_system,
  const ON_UnitSystem& length_value_unit_system,
  double* length_value
  );



/*
Description:
  Parses str if it is a recognized angle unit system name or abbreviation. 

Parameters:
  str - [in]

  str_count - [in]
    str[] and str_count specify the string to parse.
    If str_count >= 0. it specifies the maximum number of elements in str[]
    that may be parsed.  If str_count = -1, then the string must contain a 
    character that terminates angle unit system name parsing.  
    This character can be a null, digit, punctuation, arithmetic operator,
    or a unicode code point <= 0x0020 (0x0020 = space = 32 decimal).

  prefered_locale_id - [in]
    If the parsed angle unit name identifies different angle unit systems
    in different locales, then this value is used to resolve the
    ambiguity.  A list of Microsoft locale id values can be found at
    http://msdn.microsoft.com/en-us/library/ms912047(v=winembedded.10).
    For example, "Grad" identifies ON::degrees in German and ON::gradians
    in US English.
    
  bParseLeadingWhitespace - [in]
    If true, leading white space will be parsed.
    If false, the unit name must begin with element str[0].

  angle_unit_system - [out] (can be null)
    If angle_unit_system is not null, it is set to the identify the
    angle unit system specified by str. If str does not identify a 
    known angle unit system, then *angle_unit_system is set to 
    ON::AngleUnitSystem::None.

Returns:
  Number of elements of str that were parsed. A return value of
  0 indicates that str did not match know unit system names or 
  abbreviations.

Remarks:
  Currently common names and abbreviations for radians, turns,
  gradians, arc degrees, arc minutes and arc seconds are supported
  in Czech (cs-*), English (en-*), French (fr-*), German (de-*), 
  Portuguese (pt-*) and Spanish (es-*).

  If the first element of str is quotation mark (double quote), unicode 
  code point 0x0022, the string is parsed as arc seconds.
  If the first element of str is apostrophe, unicode code point 0x0027, 
  the string is parsed as arc minutes.
*/
ON_DECL
int ON_ParseAngleUnitName( 
  const wchar_t* str,
  int str_count,
  int prefered_locale_id,
  ON::AngleUnitSystem* angle_unit_system
  );

ON_DECL
int ON_ParseAngleUnitName( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  ON::AngleUnitSystem* angle_unit_system
  );


/*
Description:
  Parses str to determine if it specifies a angle value.

Parameters:
  str - [in]

  str_count - [in]
    str[] and str_count specify the string to parse.
    If str_count >= 0. it specifies the maximum number of elements in str[]
    that may be parsed.  If str_count = -1, then the string must contain a 
    character that terminates angle parsing.

 parse_settings - [in]
   The input parse_settings parameter controls what input may be
   parsed and how it is parsed.
   Use ON_ParseSettings::DefaultSettings for common parsing tasks.

 angle_value_unit_system - [in]
   Angle unit system for the returned value.  
   For example, if you want the returned value to be in degrees,
   you would specify ON::AngleUnitSystem::Degrees here.

 angle_value - [out]
   The value of the parsed angle.
   
 parse_results - [out] (input pointer can be null)
   The output parse_results parameter reports what was parsed.
   
 str_angle_unit_system - [out] (input pointer can be null)
   angle unit in the parsed string. When the 
   angle_value_unit_system specifies an angle unit system and a
   a different angle unit system is parsed, the number returned
   in angle_value is always converted to the angle unit system 
   specified by the angle_value_unit_system parameter.
   If needed, you can inspect str_angle_unit_system to determine
   if the angle unit system scaling was applied.

Returns:
  Number of elements of str that were parsed. A return value of
  0 indicates that str could not be parsed as a angle value.
*/
ON_DECL
int ON_ParseAngleExpression( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  double* angle_value,
  ON_ParseSettings* parse_results,
  ON::AngleUnitSystem* str_angle_unit_system
  );

ON_DECL
int ON_ParseAngleExpression( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  const ON::AngleUnitSystem angle_value_unit_system,
  double* angle_value,
  ON_ParseSettings* parse_results,
  ON::AngleUnitSystem* str_angle_unit_system
  );

/*
Description:
  Parses str to determine if it specifies a angle value.

Parameters:
  str - [in]

  str_count - [in]
    str[] and str_count specify the string to parse.
    If str_count >= 0. it specifies the maximum number of elements in str[]
    that may be parsed.  If str_count = -1, then the string must contain a 
    character that terminates angle parsing.

 default_str_angle_unit_system - [in]
   If an angle unit system is not specified in the parsed string,
   then default_str_angle_units determines what unit system will
   be used.  If default_str_angle_units is ON::AngleUnitSystem::None,
   then ON::radians will be used.

 angle_value_in_radians - [out]
   The value of the parsed angle, converted to radians, is returned here.
   
Returns:
  Number of elements of str that were parsed. A return value of
  0 indicates that str could not be parsed as a angle value.

Remarks:
  This function uses ON_ParseAngleExpression() with the 
  angle_value_unit_system parameter set to ON::radians
  to parse the string. If you need more control over parsing
  options, then use ON_ParseAngleExpression().
*/
ON_DECL
int ON_ParseAngleRadiansExpression( 
  const wchar_t* str,
  int str_count,
  ON::AngleUnitSystem default_str_angle_unit_system,
  double* angle_value_in_radians
  );

/*
Description:
  Parses str to determine if it specifies a angle value.

Parameters:
  str - [in]

  str_count - [in]
    str[] and str_count specify the string to parse.
    If str_count >= 0. it specifies the maximum number of elements in str[]
    that may be parsed.  If str_count = -1, then the string must contain a 
    character that terminates angle parsing.

  default_str_angle_unit_system - [in]
    If an angle unit system is not specified in the parsed string,
    then default_str_angle_units determines what unit system will
    be used.  If default_str_angle_units is ON::AngleUnitSystem::None,
    then ON::radians will be used.
    
 angle_value_in_radians - [out]
   The value of the parsed angle, converted to arc degrees, 
   is returned here.
   
Returns:
  Number of elements of str that were parsed. A return value of
  0 indicates that str could not be parsed as a angle value.

Remarks:
  This function uses ON_ParseAngleExpression() with the 
  angle_value_unit_system parameter set to ON::AngleUnitSystem::Degrees
  to parse the string. If you need more control over parsing
  options, then use ON_ParseAngleExpression().
*/
ON_DECL
int ON_ParseAngleArcDegreesExpression( 
  const wchar_t* str,
  int str_count,
  ON::AngleUnitSystem default_str_angle_unit_system,
  double* angle_value_in_arc_degrees
  );

/*
Description:
  Parses str to determine if it specifies a point value.

Parameters:
  str - [in]

  str_count - [in]
    str[] and str_count specify the string to parse.
    If str_count >= 0. it specifies the maximum number of elements in str[]
    that may be parsed.  If str_count = -1, then the string must contain a 
    character that terminates length parsing.

  default_str_angle_unit_system - [in]
    If an angle unit system is not specified in the parsed string,
    then default_str_angle_units determines what unit system will
    be used.  If default_str_angle_units is ON::AngleUnitSystem::None,
    then ON::radians will be used.

 parse_settings - [in]
   The input parse_settings parameter controls what input may be
   parsed and how it is parsed.
   Use ON_ParseSettings::DefaultSettings for common parsing tasks.

 point_value_unit_system - [in]
   Coordinate unit system for the returned point value.  
   For example, if you want the returned point coordinates to
   be in meters, you would specify ON::LengthUnitSystem::Meters here. 
   If you want to use custom units, you must use the 
   override with the ON_UnitSystem parameter.

 point_value - [out]
   The value of the parsed point.
   
 parse_results - [out] (input pointer can be null)
   The output parse_results parameter reports what was parsed.
   
Returns:
  Number of elements of str that were parsed. A return value of
  0 indicates that str could not be parsed as a length value.
*/
ON_DECL
int ON_ParsePointExpression(
  const wchar_t* str,
  int str_count,
  ON::AngleUnitSystem default_str_angle_unit_system,
  ON::LengthUnitSystem point_value_unit_system,
  ON_3dPoint* point_value
  );

ON_DECL
int ON_ParsePointExpression(
  const wchar_t* str,
  int str_count,
  ON::AngleUnitSystem default_str_angle_unit_system,
  const ON_UnitSystem& point_value_unit_system,
  ON_3dPoint* point_value
  );

ON_DECL
int ON_ParsePointExpression(
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  ON::LengthUnitSystem point_value_unit_system,
  ON_3dPoint* point_value,
  ON_ParseSettings* parse_results
  );

ON_DECL
int ON_ParsePointExpression(
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  const ON_UnitSystem& point_value_unit_system,
  ON_3dPoint* point_value,
  ON_ParseSettings* parse_results
  );




#endif

