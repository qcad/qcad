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

static void DisableCompoundUnitParsingStuff(
  ON_ParseSettings& parse_settings
  )
{
  parse_settings.SetParseFeetInches(false);
  parse_settings.SetParseArcDegreesMinutesSeconds(false);
}

static void DisableStartAndExpressionParsingStuff(
  ON_ParseSettings& parse_settings
  )
{
  // parsing of things that have multiple numbers like
  // feet and inches, arc degrees minutes seconds,
  // integer-fraction and rational numbers uses
  // this helper to prevent "fancy" stuff when parsing
  // the "additional" numbers.
  parse_settings.SetParseLeadingWhiteSpace(false);
  parse_settings.SetParseUnaryMinus(false);
  parse_settings.SetParseUnaryPlus(false);
  parse_settings.SetAllExpressionSettingsToFalse();
  DisableCompoundUnitParsingStuff(parse_settings);
}

static int GetExplicitFormulaEndIndex(
  const wchar_t* str,
  int str_index,
  int str_count,
  const ON_ParseSettings& input_parse_settings,
  int& formula_index0,
  int& formula_index1
  )
{
  formula_index0 = 0;
  formula_index1 = 0;
  if ( !input_parse_settings.ParseExplicitFormulaExpression() )
    return 0;

  if ( str_index+2 >= str_count )
    return 0;
  if ( '=' != str[str_index] )
    return 0;
  if ( '(' != str[str_index+1] )
    return 0;

  str_index += 2;

  while ( str_index < str_count 
          && input_parse_settings.IsLeadingWhiteSpace(str[str_index]) 
        )
  {
    str_index++;
  }

  formula_index0 = str_index;

  int paren_count = 1;
  while (    str_index < str_count
          && 0 != str[str_index]
          && paren_count > 0
        )
  {
    switch( str[str_index] )
    {
    case '(':
      paren_count++;
      break;
    case ')':
      paren_count--;
      if ( 0 == paren_count )
        formula_index1 = str_index;
      break;
    default:
      break;
    }
    str_index++;
  }

  if ( 0 != paren_count )
    return 0;

  while (    formula_index1 > formula_index0
          && input_parse_settings.IsInteriorWhiteSpace(str[formula_index1])
        )
  {
    formula_index1--;
  }

  if ( formula_index1 <= formula_index0 )
    return 0;

  // str[formula_index0]...str[formula_index1-1] 
  // is what was parsed by the old parsing code.

  return str_index;
}


static int ParseExplicitFormulaHelper(
  const wchar_t* str,
  int str_index,
  int str_count,
  ON_ParseSettings& input_parse_settings,
  ON_ParseSettings* parse_results,
  double* value
  )
{
  // Support for old V5 =( ... ) syntax
  const int str_index0 = str_index;
  int str_index1 = 0;
  int formula_index0 = 0;
  int formula_index1 = 0;
  str_index = 0;

  for(;;)
  {
    str_index1 = GetExplicitFormulaEndIndex(
      str,str_index0,str_count,input_parse_settings,
      formula_index0,formula_index1
      );
    if ( str_index1 <= 0 )
      break;
    if ( formula_index1 <= formula_index0 )
      break;
    if ( formula_index0 < str_index0+2 )
      break;
    if ( formula_index1+1 > str_index1 )
      break;
    if ( str_index1 < str_index0+3+formula_index1-formula_index0)
      break;
    input_parse_settings.SetParseExplicitFormulaExpression(false);
    input_parse_settings.SetParseIntegerDashFraction(false);
    double x = ON_UNSET_VALUE;
    ON_ParseSettings pr(ON_ParseSettings::FalseSettings);
    int formula_count = formula_index1-formula_index0;
    int parsed_formula_count = ON_ParseNumberExpression(
      str+formula_index0,
      formula_count,
      input_parse_settings,
      &pr,
      &x
      );
    if ( parsed_formula_count <= 0 )
      break;
    if ( parsed_formula_count <= 0 )
      break;
    if ( !ON_IsValid(x) )
      break;
    pr.SetParseExplicitFormulaExpression(true);

    str_index = str_index1;

    if ( parse_results )
      *parse_results = pr;
    if ( value )
      *value = x;
    break;
  }

  return str_index;
}

static int ON_ParsePiHelper( 
  const wchar_t* str,
  int str_index,
  int str_count,
  const ON_ParseSettings& input_parse_settings,
  ON_ParseSettings& pr,
  double* value
  )
{

  if (    input_parse_settings.ParsePi() 
       && str_index >= 0 
       && 0 != str
       && str_index < str_count 
     )
  {
    int pi_str_count = 0;

    switch(str[str_index])
    {
    case 0x03A0: // UNICODE GREEK CAPITAL LETTER PI
    case 0x03C0: // UNICODE GREEK SMALL LETTER PI
      pi_str_count = 1;
      break;

    case 'P':
    case 'p':
      if ( -1 == str_count || str_index+1 < str_count )
      {
        if ('I' == str[str_index+1] || 'i' == str[str_index+1] )
          pi_str_count = 2;
      }
      break;
    }

    if ( pi_str_count > 0 )
    {
      *value = ON_PI;
      pr.SetParsePi(true);
      str_index += pi_str_count;
      return str_index;
    }
  }

  return 0;
}

static int ON_ParseDoubleExponentHelper(
  const wchar_t* str,
  int str_index,
  int str_count,
  const ON_ParseSettings& input_parse_settings,
  char* buffer,
  unsigned int& buffer_count,
  unsigned int buffer_capacity
  )
{
  char c;
  if ( str_index + 1 >= str_count )
    return 0;

  if ( !input_parse_settings.ParseScientificENotation() )
    return 0;

  if ( !input_parse_settings.IsDecimalExponentSymbol(str[str_index]) )
    return 0;


  unsigned int buffer_index = buffer_count;

  if ( buffer_index >= buffer_capacity )
    return 0;
  
  buffer[buffer_index++] = 'e';
  
  const unsigned int buffer_exponent_index = buffer_index;
  str_index++;
  if ( str_index < str_count )
  {
    if ( input_parse_settings.IsUnaryMinus(str[str_index]) )
    {
      if ( buffer_index >= buffer_capacity )
        return 0;
      buffer[buffer_index++] = '-';
      str_index++;
    }
    else if ( input_parse_settings.IsUnaryPlus(str[str_index]) )
    {
      str_index++;
    }
    if ( str_index < str_count && 0 != (c = input_parse_settings.IsDigit(str[str_index])) )
    {
      if ( buffer_index >= buffer_capacity )
        return 0;
      bool bExponentIsZero = ('0' == c);
      buffer[buffer_index++] = c;
      str_index++;
      while ( str_index < str_count 
              && 0 != (c = input_parse_settings.IsDigit(str[str_index])) 
            )
      {
        str_index++;
        if ( bExponentIsZero )
        {
          if ('0' == c )
            continue;
          bExponentIsZero = false;
          buffer_index--;
        }
        if ( buffer_index >= buffer_capacity )
          return 0;
        buffer[buffer_index++] = c;
      }
      if ( bExponentIsZero )
      {
        buffer_index = buffer_exponent_index;
        buffer[buffer_index++] = '0';
      }
      buffer_count = buffer_index;
      return str_index;
    }
  }

  return 0;
}



static int ON_ParseDoubleHelper( 
  const wchar_t* str,
  int str_index,
  int str_count,
  const ON_ParseSettings& input_parse_settings,
  ON_ParseSettings& pr,
  double* value
  )
{
  // Please discuss any changes with Dale Lear.
  char buffer[256]; // must have room for end of line junk
  const unsigned int buffer_capacity = sizeof(buffer)/sizeof(buffer[0]);
  unsigned int buffer_count = 0;
  char c = 0;

  bool bHaveSignificand = false;
  bool bHaveSignificandDecimalPoint = false;
  if ( str_index < str_count )
  {
    bool bIntegerPartIsNotZero = false;
    const bool bParseDigitSeparators = input_parse_settings.ParseSignificandDigitSeparators();
    bool bParseSignificandIntegerPart =  input_parse_settings.ParseSignificandIntegerPart() 
                                      || input_parse_settings.ParseIntegerDashFraction()
                                      || input_parse_settings.ParseRationalNumber()
                                      ;
    if (   bParseSignificandIntegerPart
         && 0 != (c = input_parse_settings.IsDigit(str[str_index])) 
       )
    {
      if ( buffer_count >= buffer_capacity )
        return 0;
      if ( bIntegerPartIsNotZero || '0' != c )
      {
        bIntegerPartIsNotZero = true;
        buffer[buffer_count++] = c;
      }
      bHaveSignificand = true;
      pr.SetParseSignificandIntegerPart(true);
      for( str_index++; str_index < str_count; str_index++ )
      {
        c = input_parse_settings.IsDigit(str[str_index]);
        if ( 0 != c )
        {
          if ( buffer_count >= buffer_capacity )
            return 0;
          if ( bIntegerPartIsNotZero || '0' != c )
          {
            bIntegerPartIsNotZero = true;
            buffer[buffer_count++] = c;
          }
          continue;
        }
        
        if (    bParseDigitSeparators 
             && str_index+1 < str_count
             && input_parse_settings.IsDigitSeparator(str[str_index]) 
             && 0 != input_parse_settings.IsDigit(str[str_index+1]) 
           )
        {
          pr.SetParseSignificandDigitSeparators(true);
          continue;
        }

        break;
      }
    }

    if ( bHaveSignificand && 0 == buffer_count )
    {
      buffer[0] = '0';
      buffer[1] = 0;
      buffer_count = 1;
    }

    if (    str_index < str_count
         && input_parse_settings.ParseSignificandDecimalPoint() 
         && input_parse_settings.IsDecimalPoint(str[str_index])
       )
    {
      bHaveSignificandDecimalPoint = true;
      str_index++;
      pr.SetParseSignificandDecimalPoint(true);

      if (   input_parse_settings.ParseSignificandFractionalPart() 
           && 0 != (c = input_parse_settings.IsDigit(str[str_index])) 
         )
      {
        if ( buffer_count+1 >= buffer_capacity )
          return 0;
        buffer[buffer_count++] = '.';
        buffer[buffer_count++] = c;
        const unsigned int buffer_hundredths_index = buffer_count;

        bHaveSignificand = true;
        pr.SetParseSignificandFractionalPart(true);
        for( str_index++; str_index < str_count; str_index++ )
        {
          c = input_parse_settings.IsDigit(str[str_index]);
          if ( 0 != c )
          {
            if ( buffer_count+1 >= buffer_capacity )
              return 0;
            buffer[buffer_count++] = c;
            continue;
          }
        
          if (    bParseDigitSeparators 
               && str_index+1 < str_count
               && input_parse_settings.IsDigitSeparator(str[str_index]) 
               && input_parse_settings.IsDigit(str[str_index+1]) 
             )
          {
            pr.SetParseSignificandDigitSeparators(true);
            continue;
          }

          break;
        }
        while ( buffer_count > buffer_hundredths_index && '0' == buffer[buffer_count-1] )
          buffer_count--;
      }
    }
  }

  if ( !bHaveSignificand )
    return 0;

  bool bHaveExponent = false;
  int end_of_exponent_index = ON_ParseDoubleExponentHelper(str,str_index,str_count,input_parse_settings,
                                                  buffer,buffer_count,buffer_capacity
                                                  );
  if ( end_of_exponent_index > str_index )
  {
    bHaveExponent = true;
    pr.SetParseScientificENotation(true);
    str_index = end_of_exponent_index;
  }

  if ( buffer_count <= 0 || buffer_count >= buffer_capacity )
    return 0;
  
  buffer[buffer_count] = 0;
  double x = ON_UNSET_VALUE;
  if ( nullptr == ON_String::ToNumber(buffer,ON_DBL_QNAN,&x) )
    return 0;
  if ( 0 != value )
    *value = x;

  return str_index;
}


int ON_ParseNumber( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  ON_ParseSettings* parse_results,
  double* value
  )
{
  const ON_ParseSettings input_parse_settings(parse_settings);
  double x = ON_UNSET_VALUE;
  ON_ParseSettings pr = ON_ParseSettings::FalseSettings;
  if ( 0 != value )
    *value = ON_UNSET_VALUE;
  if ( 0 != parse_results )
    *parse_results = pr;

  if ( -1 == str_count )
  {
    // parse up to non number element (null, ...)
    str_count = ON_ParseSettings::max_number_str_count; 
  }

  if ( 0 == str || str_count <= 0 || 0 == str[0] )
    return 0;

  int str_index = 0;

  if (    str_index < str_count
       && input_parse_settings.ParseLeadingWhiteSpace() 
       && input_parse_settings.IsLeadingWhiteSpace(str[str_index])
     )
  {
    // skip over leading white space
    pr.SetParseLeadingWhiteSpace(true);
    while ( str_index < str_count && input_parse_settings.IsLeadingWhiteSpace(str[str_index]) )
    {
      str_index++;
    }
  }

  bool bIsNegative = false;
  if ( str_index < str_count )
  {
    if ( input_parse_settings.ParseUnaryMinus() && input_parse_settings.IsUnaryMinus(str[str_index] ) )
    {
      bIsNegative = true;
      pr.SetParseUnaryMinus(true);
      str_index++;
    }
    else if ( input_parse_settings.ParseUnaryPlus() && input_parse_settings.IsUnaryPlus(str[str_index] ) )
    {
      pr.SetParseUnaryPlus(true);
      str_index++;
    }
  }

  const int str_index0 = str_index;
  for(;;)
  {
    str_index = ON_ParsePiHelper(
      str, str_index0, str_count,
      input_parse_settings, pr, &x
      );
    if ( str_index > str_index0 )
    {
      break; // got pi
    }

    str_index = ON_ParseDoubleHelper(
      str, str_index0, str_count,
      input_parse_settings, pr, &x
      );
    
    if ( str_index <= str_index0 )
      break;

    if (    !ON_IsValid(x) 
         || !(x == floor(x)) 
         || !pr.ParseSignificandIntegerPart()
         || pr.ParseSignificandDecimalPoint()
         || pr.ParseSignificandFractionalPart()
         || pr.ParseScientificENotation()
         )
    {
      // The number we parsed was not an integer
      break;
    }

    if ( str_index+1 >= str_count )
      break;

    const bool bIsNumberDash = input_parse_settings.IsNumberDash(str[str_index]);
    const bool bIsFractionBar = !bIsNumberDash && input_parse_settings.IsRationalNumberFractionBar(str[str_index]);

    if ( !bIsNumberDash && !bIsFractionBar )
      break;

    if ( bIsNumberDash && !input_parse_settings.ParseIntegerDashFraction() )
      break;

    if ( bIsFractionBar && !input_parse_settings.ParseRationalNumber() )
      break;

    ON_ParseSettings parse_int = ON_ParseSettings::IntegerNumberSettings;
    parse_int.SetParseLeadingWhiteSpace(false);
    parse_int.SetParseUnaryPlus(false);
    parse_int.SetParseUnaryMinus(false);

    // Need another integer value;
    double x1 = ON_UNSET_VALUE;
    ON_ParseSettings pr1(ON_ParseSettings::FalseSettings);
    int str_index1 = ON_ParseDoubleHelper(
      str, str_index+1, str_count,
      parse_int, pr1, &x1
      );

    if ( str_index1 <= str_index+1 )
    {
      break;
    }

    if ( !ON_IsValid(x1) || x1 != floor(x1) )
    {
      break;
    }

    if ( bIsFractionBar )
    {
      if ( 0.0 == x1 )
        break;
      x /= x1;
      pr |= pr1;
      pr.SetParseRationalNumber(true);
      str_index = str_index1;
      break;
    }

    // At this point we are parsing integer-dash-fraction in the form I-N/D.
    // I, N and D must be integers, N > 0 and D > N.
    // If a symbol follows D, it cannot be an arithmetic operator

    if ( !bIsNumberDash )
    {
      // With the code as of 6 SWep 2013, this never happens.
      // It is here to prevent future changes from breaking this code.
      break;
    }

    if ( !(x1 > 0.0) )
      break;

    if ( str_index1+1 >= str_count )
      break;

    if ( !input_parse_settings.IsRationalNumberFractionBar(str[str_index1]) )
      break;

    // Need another integer value for the denominator "D" in value = I-N/D
    double x2 = ON_UNSET_VALUE;
    ON_ParseSettings pr2(ON_ParseSettings::FalseSettings);
    int str_index2 = ON_ParseDoubleHelper(
      str, str_index1+1, str_count,
      parse_int, pr2, &x2
      );

    if ( str_index2 <= str_index1+1 )
    {
      break;
    }

    if ( !ON_IsValid(x2) || x2 != floor(x2) || !(x2 > x1) )
    {
      break;
    }

    if ( (str_index2 < str_count || -1 == str_count )
         && parse_settings.ParseArithmeticExpression() 
       )
    {
      // c = symbol after the last digit of D in I-N/D
      const wchar_t c = str[str_index2];
      if (    parse_settings.IsAdditionSymbol(c) 
           && parse_settings.ParseAddition()
         )
        break;
      if ( parse_settings.IsSubtractionSymbol(c) 
           && parse_settings.ParseSubtraction()
         )
        break;
      if ( parse_settings.IsMultiplicationSymbol(c) 
           && parse_settings.ParseMultiplication()
         )
        break;
      if ( parse_settings.IsDivisionSymbol(c) 
           && parse_settings.ParseDivision() 
         )
        break;
      if (    parse_settings.IsDecimalPoint(c) 
           && parse_settings.ParseSignificandDecimalPoint()
         )
        break;
      if ( parse_settings.IsRationalNumberFractionBar(c) )
        break;
      if ( parse_settings.IsNumberDash(c) )
        break;
    }

    // We have I-N/D where I,N,D are integers and D > N > 0.
    //
    // (I*D+N)/D is more accurate than I + N/D because the double precision calculation (I*D+N) is typically mathematically exact in the ranges we with.
    //x += (x1/x2); // x = I + (N/D)
    x = (x*x2 + x1) / x2; // x = (I*D + N)/D 
    pr |= pr1;
    pr |= pr2;
    pr.SetParseIntegerDashFraction(true);
    str_index = str_index2;

    break;   
  }

  if ( str_index > str_index0 )
  {
    if ( bIsNegative && x > 0.0 )
      x = -x;
  }
  else
  {
    // parse number failed
    str_index = 0;
  }

  if ( value )
    *value = x;

  if ( 0 != parse_results )
    *parse_results = pr;

  return str_index;
}

static void SetParseExpressionError(
  const ON_ArithmeticCalculator& calculator,
  ON_ParseSettings* parse_results
  )
{
  if ( 0 != parse_results )
  {
    switch ( calculator.ErrorCondition() )
    {
    case ON_ArithmeticCalculator::no_error:
      break;
    case ON_ArithmeticCalculator::invalid_expression_error:
      parse_results->SetParseInvalidExpressionError(true);
      break;
    case ON_ArithmeticCalculator::divide_by_zero_error:
      parse_results->SetParseDivideByZeroError(true);
      break;
    case ON_ArithmeticCalculator::overflow_error:
      parse_results->SetParseOverflowError(true);
      break;
    default:
      break;
    }
  }
}

#define ON_PARSE_FUNCTIONS
#if defined(ON_PARSE_FUNCTIONS)
static bool IsFunctionNameFirstSymbol(wchar_t c)
{
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

class tagFUNCTION
{
public:
  const wchar_t* m_function_name;
  bool (*m_function)(const double*,double*);
  unsigned int m_function_parameter_count;
  bool m_bRadiansParameter;

  static int CompareFunctionName(
    const wchar_t* a,
    int a_count,
    const wchar_t* b
    )
  {
    wchar_t c, d=0;
    for ( int a_index = 0; a_index < a_count; a_index++ )
    {
      c = a[a_index];
      d = *b++;
      if ( c >= 'A' && c <= 'Z' )
        c += 'a'-'A';
      if ( c < d )
        return -1;
      if ( c > d )
        return 1;
      if ( 0 == c )
        return 0;
    }
    d = *b++;
    if ( 0 < d )
      return -1;
    if ( 0 > d )
      return 1;
    return 0;
  }
};



static bool atan2_function(const double* a,double* x)
{
  if ( 0.0 == a[0] && 0.0 == a[1] )
    return false;
  *x = atan2(a[0],a[1]);
  return true;
}

static bool cos_function(const double* a, double* x)
{
  *x = cos(a[0]);
  return true;
}

static bool sin_function(const double* a, double* x)
{
  *x = sin(a[0]);
  return true;
}

static bool tan_function(const double* a, double* x)
{
  *x = tan(a[0]);
  return true;
}

static bool ln_function(const double* a, double* x)
{
  if ( !(a[0] > 0.0) )
    return false;
  *x = log(a[0]);
  return true;
}

static bool log10_function(const double* a, double* x)
{
  if ( !(a[0] > 0.0) )
    return false;
  *x = log10(a[0]);
  return true;
}

static bool sqrt_function(const double* a, double* x)
{
  if ( !(a[0] >= 0.0) )
    return false;
  *x = sqrt(a[0]);
  return true;
}

static bool acos_function(const double* a, double* x)
{
  if ( !(a[0] >= -1.0 && a[0] <= 1.0) )
    return false;
  *x = acos(a[0]);
  return true;
}

static bool asin_function(const double* a, double* x)
{
  if ( !(a[0] >= -1.0 && a[0] <= 1.0) )
    return false;
  *x = asin(a[0]);
  return true;
}

static bool atan_function(const double* a, double* x)
{
  *x = atan(a[0]);
  return true;
}

static bool exp_function(const double* a, double* x)
{
  if ( !(a[0] < 709.7827) )
    return false; // exp(709.7827) > max double
  *x = exp(a[0]);
  return true;
}

static bool pow_function(const double* a, double* x)
{
  if ( 0.0 == a[0] && a[1] < 0.0 )
    return false;
  *x = pow(a[0],a[1]);
  return true;
}

static bool sinh_function(const double* a, double* x)
{
  if ( !(a[0] < 710.4760) )
    return false;
  *x = sinh(a[0]);
  return true;
}

static bool cosh_function(const double* a, double* x)
{
  if ( !(a[0] < 710.4760) )
    return false;
  *x = cosh(a[0]);
  return true;
}

static bool tanh_function(const double* a, double* x)
{
  *x = tanh(a[0]);
  return true;
}

static class tagFUNCTION* GetFunction(
  const wchar_t* function_name,
  int function_name_count
  )
{
  static bool bAngleRadiansParameter = true;
  static tagFUNCTION f[] = 
  {
    {0,0,0},
    {L"acos",acos_function,1,false},
    {L"asin",asin_function,1,false},
    {L"atan",atan_function,1,false},
    {L"atan2",atan2_function,2,false},
    {L"cos",cos_function,1,bAngleRadiansParameter},
    {L"cosh",cosh_function,1,false},
    {L"exp",exp_function,1,false},
    {L"ln",ln_function,1,false},
    //{L"log",ln_function,1,true},
    {L"log10",log10_function,1,false},
    {L"pow",pow_function,2,false},
    {L"sin",sin_function,1,bAngleRadiansParameter},
    {L"sinh",sinh_function,1,false},
    {L"sqrt",sqrt_function,1,false},
    {L"tan",tan_function,1,bAngleRadiansParameter},
    {L"tanh",tanh_function,1,false},
  };

  int i0 = 1;
  int i1 = (int)(sizeof(f)/sizeof(f[0]));
  while ( i0 < i1 )
  {
    int i = (i0+i1)/2;
    int j = tagFUNCTION::CompareFunctionName( function_name, function_name_count, f[i].m_function_name );
    if ( j < 0 )
      i1 = i;
    else if ( j > 0 )
      i0 = i+1;
    else
      return &f[i];
  }

  return 0;
}


static int ON_ParseFunctionHelper( 
  const wchar_t* str,
  int str_count,
  const ON_ParseSettings& input_parse_settings,
  ON_ParseSettings& pr,
  double* value
  )
{
  // Please discuss any changes with Dale Lear.
  double f_parameters[16];
  unsigned int f_parameter_count = 0;
  unsigned int f_parameter_capacity = (unsigned int)(sizeof(f_parameters)/sizeof(f_parameters[0]));
  tagFUNCTION* f = 0;
  double f_value = ON_UNSET_VALUE;

  int str_index = 0;

  if ( !input_parse_settings.ParseArithmeticExpression() )
    return false;

  if ( !input_parse_settings.ParseMathFunctions() )
    return false;

  for(;;)
  {
    if ( str_index >= str_count )
      break;

    int str_index1;
    for ( str_index1 = 0; str_index1 < str_count; str_index1++ )
    {
      if ( !IsFunctionNameFirstSymbol(str[str_index1]) )
        break;
    }

    if ( str_index1 <= 0 )
      break;

    while ( str_index1 < str_count && str[str_index1] >= '0' && str[str_index1] <= '9' )
    {
      str_index1++;
    }

    if ( str_index1+1 >= str_count )
      break;

    if ( !input_parse_settings.IsLeftParenthesisSymbol(str[str_index1]) )
      break;

    f = GetFunction(str,str_index1);
    if ( 0 == f )
      break;
    if ( f->m_function_parameter_count <= 0 )
      break;
    if ( f_parameter_capacity < f->m_function_parameter_count )
      break;

    // The angle parameters passed to trig functions always have
    // an "implicit" angle system of radians. It is intentional that
    // this cannot be changed by parse settings.  The reason is
    // to insure that the same script will create the same values
    // on all computers.  The implicit angle units are radians
    // because that is what all trig functions use by default
    // in C, C++, C#, and python.  Please discuss any changes
    // with Dale Lear.
    ON_ParseSettings psRadiansParameter(input_parse_settings);
    psRadiansParameter.SetDefaultAngleUnitSystem(ON::AngleUnitSystem::Radians);

    str_index1++;
    for ( f_parameter_count = 0;
          f_parameter_count < f->m_function_parameter_count; 
          f_parameter_count++)
    {
      ON_ParseSettings pr1(ON_ParseSettings::FalseSettings);
      f_parameters[f_parameter_count] = ON_UNSET_VALUE;
      int str_index2 = f->m_bRadiansParameter
        ? ON_ParseAngleExpression(str + str_index1, str_count - str_index1 - 1, psRadiansParameter, ON::AngleUnitSystem::Radians, &f_parameters[f_parameter_count], &pr1, 0)
        : ON_ParseNumberExpression(str+str_index1,str_count-str_index1-1,input_parse_settings,&pr1,&f_parameters[f_parameter_count]);
      pr |= pr1;
      if ( str_index2 <= 0 )
        break;
      if ( pr1.ParseError() )
        break;
      if ( !ON_IsValid(f_parameters[f_parameter_count]) )
        break;
      str_index1 += str_index2;
      if ( str_index1+1 >= str_count )
        break;
      if ( f_parameter_count+1 < f->m_function_parameter_count )
      {
        if ( ',' != str[str_index1] )
          break;
      }
      else if ( !input_parse_settings.IsRightParenthesisSymbol(str[str_index1]) )
        break;
      str_index1++;
    }

    if ( f_parameter_count != f->m_function_parameter_count )
      break;
    if ( !f->m_function(f_parameters,&f_value) )
    {
      f_value = ON_UNSET_VALUE;
      break;
    }

    str_index += str_index1;

    break;
  }

  if ( value )
    *value = f_value;

  return str_index;
}
#endif


int ON_ParseNumberExpression( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  ON_ParseSettings* parse_results,
  double* value
  )
{
  // Please discuss changes with Dale Lear.
  // Do not make this function recursive.
  // This function support parsing limited arithmetic expressions.
  ON_ParseSettings input_parse_settings(parse_settings);
  
  ON_ParseSettings pr = ON_ParseSettings::FalseSettings;
  if ( 0 != value )
    *value = ON_UNSET_VALUE;
  if ( 0 != parse_results )
    *parse_results = pr;

  if ( -1 == str_count )
  {
    // parse up to non-parsing element (null, ...)
    str_count = ON_ParseSettings::max_expression_str_count; 
  }

  if ( 0 == str || str_count <= 0 || 0 == str[0] )
    return 0;

  int str_index = 0;

  if (    str_index < str_count
       && input_parse_settings.ParseLeadingWhiteSpace() 
       && input_parse_settings.IsLeadingWhiteSpace(str[str_index])
     )
  {
    // skip over leading white space
    pr.SetParseLeadingWhiteSpace(true);
    while ( str_index < str_count && input_parse_settings.IsLeadingWhiteSpace(str[str_index]) )
    {
      str_index++;
    }
  }

  if ( str_index+2 < str_count // room for =(...)
       && '=' == str[str_index] 
       && '(' == str[str_index+1] 
     )
  {
    // Support for old V5 =( ... ) syntax
    str_index = ParseExplicitFormulaHelper(
      str,str_index,str_count,
      input_parse_settings,
      parse_results,
      value
      );
    return str_index;
  }
  
  input_parse_settings.SetParseLeadingWhiteSpace(false);

  ON_ArithmeticCalculator calculator;

  unsigned int parenthesis_depth = 0;

  const bool bParseArithmeticExpression = parse_settings.ParseArithmeticExpression();
  const bool bParseExplicitMultiplication = bParseArithmeticExpression && parse_settings.ParseMultiplication();
  const bool bParseExplicitDivision = bParseArithmeticExpression && parse_settings.ParseDivision();
  const bool bParseExplicitAddition = bParseArithmeticExpression && parse_settings.ParseAddition();
  const bool bParseExplicitSubtraction = bParseArithmeticExpression && parse_settings.ParseSubtraction();
  const bool bParsePairedParenthises = bParseArithmeticExpression && parse_settings.ParsePairedParentheses();

  if ( bParseExplicitDivision && input_parse_settings.ParseRationalNumber() )
  {
    // This adjustment  necessary so expressions where like
    // (a+b)/c/d with "c" and "d" being integer values 
    // will be parsed correctly as ((a+b)/c)/d instead of
    // being parsed as (a+b)/rational_number_value(c/d).
    // Note that disabling rational number parsing does
    // not disable integer-hyphen-fraction parsing.
    // When integer-hyphen-fraction parsing is enabled,
    // 3/1-1/2 will be parsed as 3/1.5 = 2.
    input_parse_settings.SetParseRationalNumber(false);
  }

  while( str_index < str_count && 0 != str[str_index] )
  {
    if ( input_parse_settings.ParseUnaryMinus() && input_parse_settings.IsUnaryMinus(str[str_index] ) )
    {
      if ( !calculator.UnaryMinus() )
      {
        SetParseExpressionError(calculator,parse_results);
        return 0;
      }
      pr.SetParseUnaryMinus(true);
      str_index++;
    }
    else if ( input_parse_settings.ParseUnaryPlus() && input_parse_settings.IsUnaryPlus(str[str_index] ) )
    {
      pr.SetParseUnaryPlus(true);
      str_index++;
    }

    if ( bParsePairedParenthises && input_parse_settings.IsLeftParenthesisSymbol(str[str_index]) )
    {
      if ( !calculator.LeftParenthesis() )
      {
        SetParseExpressionError(calculator,parse_results);
        return 0;
      }
      str_index++;
      parenthesis_depth++;
      pr.SetParseArithmeticExpression(true);
      continue;
    }

    double x1 = ON_UNSET_VALUE;
    ON_ParseSettings pr1(ON_ParseSettings::FalseSettings);
    int str_index1 = ON_ParseNumber(str+str_index,str_count-str_index,input_parse_settings,&pr1,&x1);

    #if defined(ON_PARSE_FUNCTIONS)
    if ( str_index1 == 0 )
    {
      ON_ParseSettings pr2(ON_ParseSettings::FalseSettings);
      str_index1 = ON_ParseFunctionHelper(
      str+str_index, str_count-str_index,
      input_parse_settings, pr2, &x1
      );
      if ( str_index1 > 0 )
        pr1 = pr2;
    }
    #endif

    if ( str_index1 <= 0 )
      break;

    if ( str_index + str_index1 > str_count )
      break;

    if ( pr1.ParsePi() )
    {
      if ( !calculator.Number(x1) )
      {
        SetParseExpressionError(calculator,parse_results);
        return 0;
      }
    }
    else
    {
      if ( !calculator.SimpleNumber(x1) )
      {
        SetParseExpressionError(calculator,parse_results);
        return 0;
      }
    }

    pr |= pr1;
    str_index += str_index1;
    if ( str_index >= str_count )
      break;

    while (    parenthesis_depth > 0
            && str_index < str_count 
            && bParsePairedParenthises
            && input_parse_settings.IsRightParenthesisSymbol(str[str_index]) 
          )
    {
      if ( !calculator.RightParenthesis() )
      {
        SetParseExpressionError(calculator,parse_results);
        return 0;
      }
      str_index++;
      parenthesis_depth--;
      pr.SetParseArithmeticExpression(true);
      pr.SetParsePairedParentheses(true);
    }

    if ( str_index >= str_count )
      break;

    if (  bParseExplicitMultiplication
          && input_parse_settings.IsMultiplicationSymbol(str[str_index]) 
        )
    {
      if ( !calculator.Multiply() )
      {
        SetParseExpressionError(calculator,parse_results);
        return 0;
      }
      str_index++;
      pr.SetParseArithmeticExpression(true);
      pr.SetParseMultiplication(true);
      continue;
    }

    if (  bParseExplicitDivision
          && input_parse_settings.IsDivisionSymbol(str[str_index]) 
        )
    {
      if ( !calculator.Divide() )
      {
        SetParseExpressionError(calculator,parse_results);
        return 0;
      }
      str_index++;
      pr.SetParseArithmeticExpression(true);
      pr.SetParseDivision(true);
      continue;
    }

    if (  bParseExplicitAddition
          && input_parse_settings.IsAdditionSymbol(str[str_index]) 
        )
    {
      if ( !calculator.Add() )
      {
        SetParseExpressionError(calculator,parse_results);
        return 0;
      }
      str_index++;
      pr.SetParseArithmeticExpression(true);
      pr.SetParseAddition(true);
      continue;
    }

    if (  bParseExplicitSubtraction
          && input_parse_settings.IsSubtractionSymbol(str[str_index]) 
        )
    {
      if ( !calculator.Subtract() )
      {
        SetParseExpressionError(calculator,parse_results);
        return 0;
      }
      str_index++;
      pr.SetParseArithmeticExpression(true);
      pr.SetParseSubtraction(true);
      continue;
    }

    if ( calculator.PendingImpliedMultiplication() )
      continue;

    break;
  }

  if ( str_index <= 0 || str_index > str_count )
    return 0;

  double x = ON_UNSET_VALUE;
  if ( !calculator.Evaluate(&x) )
  {
    x = ON_UNSET_VALUE;
    str_index = 0;
    pr = ON_ParseSettings::FalseSettings;
    SetParseExpressionError(calculator,&pr);
  }

  if ( value )
    *value = x;

  if ( 0 != parse_results )
    *parse_results = pr;

  return str_index;
}

int ON_ParseLengthExpression( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  double* length_value,
  ON_ParseSettings* parse_results,
  ON::LengthUnitSystem* str_length_unit_system
  )
{
  double x = ON_UNSET_VALUE;
  ON::LengthUnitSystem length_us = ON::LengthUnitSystem::None;
  const ON_ParseSettings input_parse_settings(parse_settings);
  ON_ParseSettings pr = ON_ParseSettings::FalseSettings;
  if ( 0 != length_value )
    *length_value = ON_UNSET_VALUE;
  if ( 0 != str_length_unit_system )
    *str_length_unit_system = length_us;
  if ( 0 != parse_results )
    *parse_results = pr;

  int str_index = ON_ParseNumberExpression(str,str_count,input_parse_settings,&pr,&x);
  if ( str_index <= 0 )
    return 0;

  if ( -1 != str_count )
  {
    if (str_index > str_count )
      return 0;
    str_count -= str_index;
  }

  const bool bParseWhiteSpaceBetweenValueAndUnitSystem
    = (str_index < str_count || -1 == str_count)
    && input_parse_settings.ParseWhiteSpaceBetweenValueAndUnitSystem()
    && input_parse_settings.IsInteriorWhiteSpace(str[str_index]);
  ON_ParseSettings parse_unit_name_settings(input_parse_settings);
  parse_unit_name_settings.SetParseLeadingWhiteSpace(false);
  parse_unit_name_settings.SetParseWhiteSpaceBetweenValueAndUnitSystem(bParseWhiteSpaceBetweenValueAndUnitSystem);
  
  const int end_of_unit_index = ON_ParseLengthUnitName(
    str+str_index,
    str_count,
    parse_unit_name_settings,
    &length_us
  );

  if ( end_of_unit_index > 0 )
  {
    if ( -1 != str_count )
    {
      if (end_of_unit_index > str_count )
        return 0;
      str_count -= end_of_unit_index;
    }
    str_index += end_of_unit_index;

    pr.SetParseWhiteSpaceBetweenValueAndUnitSystem(bParseWhiteSpaceBetweenValueAndUnitSystem);

    if ( -1 == str_count || str_count > 0 )
    {
      if ( ON::LengthUnitSystem::Feet == length_us 
           && floor(x) == x
           && input_parse_settings.ParseFeetInches() 
           && false == pr.ParseSignificandDecimalPoint()
           && false == pr.ParseScientificENotation()
           && false == pr.ParseRationalNumber()
           && false == pr.ParseMultiplication()
           && false == pr.ParseDivision()
           && false == pr.ParsePi()
           && false == pr.ParseIntegerDashFraction()
         )
      {
        // parse inches part or feet and inches
        int inches_index0 = str_index;
        ON_ParseSettings parse_inches = input_parse_settings;
        DisableStartAndExpressionParsingStuff(parse_inches);
        parse_inches.SetParsePi(false);
        parse_inches.SetParseFeetInches(false);

        double inches_value = ON_UNSET_VALUE;
        ON::LengthUnitSystem inches_us = ON::LengthUnitSystem::None;
        ON_ParseSettings inches_pr = ON_ParseSettings::FalseSettings;


        // Dale Lear 9 April 2014 - fix RH-23095 
        //  Checking for a number dash is required to parse 1'-1-1/2" as 13.5 inches.
        int number_dash_count = 0;
        if ( input_parse_settings.IsNumberDash(str[inches_index0]) )
        {
          // It is intentional that the "number dash" between feet and inches
          // cannot have leading or trailing interior space.
          if (-1 == str_count || str_count >= 3)
          {
            if ( input_parse_settings.IsDigit(str[inches_index0 + 1]) )
              number_dash_count = 1;
            if (-1 != str_count)
              str_count--;
          }
        }


        // June 10, 2016 Dale Lear
        // http://mcneel.myjetbrains.com/youtrack/issue/RH-34577
        //  Allow embedded interior white space between the feet and inches.
        //  Example <1' 3"> should parse as 15 inches.
        bool bParseWhiteSpaceBetweenFeetAndInches = false;
        if (0 == number_dash_count)
        {
          if (-1 == str_count || str_count >= 3)
          {
            bParseWhiteSpaceBetweenFeetAndInches
              = (str_index < str_count || -1 == str_count)
              && input_parse_settings.ParseWhiteSpaceBetweenFeetAndInches()
              && input_parse_settings.IsInteriorWhiteSpace(str[inches_index0]);
            parse_inches.SetParseLeadingWhiteSpace(bParseWhiteSpaceBetweenFeetAndInches);
          }
        }

        int end_of_inches_index = ON_ParseLengthExpression(
          str + inches_index0 + number_dash_count,
          str_count,
          parse_inches,&inches_value,&inches_pr,&inches_us);

        if (
          end_of_inches_index > 0
          && ON::LengthUnitSystem::None == inches_us
          && inches_value >= 0.0
          && inches_value < 12.0
          && str[inches_index0 + number_dash_count] >= '0'
          && str[inches_index0 + number_dash_count] <= '9'
          )
        {
          // "lazy" inches format 1'6 is parsed as 1'6"
          inches_us = ON::LengthUnitSystem::Inches;
        }

        if ( end_of_inches_index > 0 
             && ON::LengthUnitSystem::Inches == inches_us
             && inches_value >= 0.0 // Dale Lear: 1'0" parses as 12 inches http://mcneel.myjetbrains.com/youtrack/issue/RH-34577
             && inches_value < 12.0
           )
        {
          // result of correctly adjusting str_count is never used.
          //if ( -1 != str_count)
          //  str_count -= end_of_inches_index;
          str_index = inches_index0 + end_of_inches_index + number_dash_count;
          if ( x < 0.0 && inches_value > 0.0 )
            x = x*12.0 - inches_value;
          else
            x = x*12.0 + inches_value;
          length_us = ON::LengthUnitSystem::Inches;
          pr.SetParseFeetInches(true);
          inches_pr.SetParseLeadingWhiteSpace(false);
          pr |= inches_pr;
          pr.SetParseWhiteSpaceBetweenFeetAndInches(bParseWhiteSpaceBetweenFeetAndInches);
        }
      }
    }
  }
  else
  {
    length_us = ON::LengthUnitSystem::None;
  }

  if ( length_value )
    *length_value = x;
  if ( 0 != parse_results )
    *parse_results = pr;
  if ( 0 != str_length_unit_system )
    *str_length_unit_system = length_us;

  return str_index;
}

static bool Internal_IsInteger(
  const wchar_t* str,
  int str_count
)
{
  if (nullptr == str || str_count < 1)
    return false;
  for (int i = 0; i < str_count; ++i)
  {
    if (str[i] >= '0' && str[i] <= '9')
      continue;
    return false;
  }
  return true;
}

static bool Internal_IsNegativeInteger(
  const ON_ParseSettings& parse_settings,
  const wchar_t* str,
  int str_count
)
{
  if (nullptr == str || str_count < 2 || false == parse_settings.ParseUnaryMinus())
    return false;
  if (false == parse_settings.IsUnaryMinus(str[0]))
    return false;
  return Internal_IsInteger(str + 1, str_count - 1);
}

int ON_ParseAngleExpression( 
  const wchar_t* str,
  int str_count,
  ON_ParseSettings parse_settings,
  double* angle_value,
  ON_ParseSettings* parse_results,
  ON::AngleUnitSystem* str_angle_unit_system
  )
{
  double x = ON_UNSET_VALUE;
  ON::AngleUnitSystem angle_us = ON::AngleUnitSystem::None;
  ON_ParseSettings input_parse_settings(parse_settings);
  ON_ParseSettings pr = ON_ParseSettings::FalseSettings;
  if ( 0 != angle_value )
    *angle_value = ON_UNSET_VALUE;
  if ( 0 != str_angle_unit_system )
    *str_angle_unit_system = angle_us;
  if ( 0 != parse_results )
    *parse_results = pr;

  bool bNegativeDegreesMinutesSecondsIsPossible = false;
  int str_index = 0;
  ON__UINT32 cSurveyorsNotationNS = 0;
  ON__UINT32 cSurveyorsNotationEW = 0;
  if ( input_parse_settings.ParseSurveyorsNotation() )
  {
    if (    (str_index < str_count || -1 == str_count)
         && input_parse_settings.ParseLeadingWhiteSpace() 
         && input_parse_settings.IsLeadingWhiteSpace(str[str_index])
       )
    {
      // skip over leading white space
      pr.SetParseLeadingWhiteSpace(true);
      while ( str_index < str_count && input_parse_settings.IsLeadingWhiteSpace(str[str_index]) )
      {
        str_index++;
      }
    }

    input_parse_settings.SetParseLeadingWhiteSpace(false);

    if ( ((str_index+3 <= str_count) || -1 == str_count) )
    {
      // Do not localize "N" or "n" or "S" or "s".  
      // These letters are specified by Surveyor's notation specification.
      // [TODO - Reference needed].
      switch(str[str_index])
      {
      case 'N': // Do not localize this letter
      case 'n': // Do not localize this letter
        str_index++;
        cSurveyorsNotationNS = 'N';
        break;
      case 'S': // Do not localize this letter
      case 's': // Do not localize this letter
        str_index++;
        cSurveyorsNotationNS = 'S';
        break;
      }
    }

    if ( 0 != cSurveyorsNotationNS )
    {
      input_parse_settings.SetParseIntegerDashFraction(false);
    }

    const int str_number_count = (str_count > 0 ? str_count-str_index : str_count);
    ON_ParseSettings pr1(ON_ParseSettings::FalseSettings);
    int str_number_index = ON_ParseNumberExpression(str+str_index,str_number_count,input_parse_settings,&pr1,&x);
    if ( str_number_index > 0 )
    {
      if (0 == cSurveyorsNotationNS && x <= 0.0 && Internal_IsNegativeInteger(input_parse_settings, str + str_index, str_number_index - str_index))
        bNegativeDegreesMinutesSecondsIsPossible = true;
      pr |= pr1;
    }
    else
    {
      if ( input_parse_settings.ParseScientificENotation() )
      {
        // It may be that the string looked like N15.23E and the number parser failed
        // because 15.23E is an invalid attempt at using scientific E notation.
        input_parse_settings.SetParseScientificENotation(false);
        str_number_index = ON_ParseNumberExpression(str+str_index,str_number_count,input_parse_settings,&pr,&x);
        if ( str_number_index <= 0 )
          return 0;
        if ( 'E' != str[str_number_index] && 'e' != str[str_number_index] )
          return 0;
      }
    }
    str_index += str_number_index;
  }
  else
  {
    str_index = ON_ParseNumberExpression(str,str_count,input_parse_settings,&pr,&x);
    if ( str_index <= 0 )
      return 0;
    if (0 == cSurveyorsNotationNS && x <= 0.0 && Internal_IsNegativeInteger(input_parse_settings, str, str_index))
      bNegativeDegreesMinutesSecondsIsPossible = true;
  }

  if ( str_count > 0 )
  {
    if (str_index > str_count )
      return 0;
    str_count -= str_index;
  }

  int end_of_unit_index = ON_ParseAngleUnitName(str+str_index,str_count,parse_settings.PreferedLocaleId(),&angle_us);

  if (bNegativeDegreesMinutesSecondsIsPossible && ON::AngleUnitSystem::Degrees != angle_us)
    bNegativeDegreesMinutesSecondsIsPossible = false;

  if ( end_of_unit_index > 0 )
  {
    if ( str_count > 0 )
    {
      if (end_of_unit_index > str_count )
        return 0;
      str_count -= end_of_unit_index;
    }
    str_index += end_of_unit_index;

    if ( -1 == str_count || str_index+1 < str_count )
    {
      if ( ON::AngleUnitSystem::Degrees == angle_us 
           && floor(x) == x
           && input_parse_settings.ParseArcDegreesMinutesSeconds() 
           && false == pr.ParseSignificandDecimalPoint()
           && false == pr.ParseScientificENotation()
           && false == pr.ParseRationalNumber()
           && false == pr.ParsePi()
           && false == pr.ParseDivision()
           && false == pr.ParseMultiplication()
           && false == pr.ParseIntegerDashFraction()
         )
      {
        // parse arc minutes
        ON_ParseSettings next_parse_settings = input_parse_settings;
        DisableStartAndExpressionParsingStuff(next_parse_settings);
        next_parse_settings.SetParseSignificandDigitSeparators(false);
        next_parse_settings.SetParseIntegerDashFraction(false);
        next_parse_settings.SetParseRationalNumber(false);
        next_parse_settings.SetParsePi(false);
        next_parse_settings.SetParseSurveyorsNotation(false);
        next_parse_settings.SetParseUnaryMinus(false);
        next_parse_settings.SetParseUnaryPlus(false);

        double arc_minutes_value = 0.0;
        double arc_seconds_value = 0.0;

        for ( int next_value_pass = 0; next_value_pass < 2; next_value_pass++ )
        {
          double next_value = ON_UNSET_VALUE;
          ON::AngleUnitSystem next_us(ON::AngleUnitSystem::None);
          ON_ParseSettings next_pr(ON_ParseSettings::FalseSettings);
          int next_str_index = ON_ParseAngleExpression(
            str+str_index,
            ((-1 == str_count) ? str_count : (str_count-str_index-1)),
            next_parse_settings,&next_value,&next_pr,&next_us);

          if ( next_str_index <= 0 )
            break;

          if (!(next_value >= 0.0 && next_value < 60.0))
          {
            bNegativeDegreesMinutesSecondsIsPossible = false;
            break;
          }

          if ( 0 == next_value_pass )
          {
            if ( ON::AngleUnitSystem::Minutes != next_us )
            {
              if ( ON::AngleUnitSystem::Seconds == next_us && 0 == next_value_pass )
                next_value_pass = 1;
              else
              {
                bNegativeDegreesMinutesSecondsIsPossible = false;
                break;
              }
            }
          }
          else if ( 1 == next_value_pass )
          {
            if (ON::AngleUnitSystem::Seconds != next_us)
            {
              bNegativeDegreesMinutesSecondsIsPossible = false;              
              break;
            }
          }

          if (ON::AngleUnitSystem::Minutes == next_us)
            arc_minutes_value = next_value;
          else if (ON::AngleUnitSystem::Seconds == next_us)
            arc_seconds_value = next_value;
          else
            bNegativeDegreesMinutesSecondsIsPossible = false;

          str_index += next_str_index;
          pr.SetParseArcDegreesMinutesSeconds(true);
          pr |= next_pr;
        }

        if (
          bNegativeDegreesMinutesSecondsIsPossible
          && x <= 0.0 
          && arc_minutes_value >= 0.0 
          && arc_seconds_value >= 0.0
          )
        {
          // parsing something like -90d40'30"
          if (arc_minutes_value > 0.0)
            arc_minutes_value = -arc_minutes_value;
          if (arc_seconds_value > 0.0)
            arc_seconds_value = -arc_seconds_value;
        }

        if ( 0 != arc_seconds_value )
        {
          x = 60.0*(60.0*x + arc_minutes_value) + arc_seconds_value;
          angle_us = ON::AngleUnitSystem::Seconds;
        }
        else if ( 0 != arc_minutes_value )
        {
          x = 60.0*x + arc_minutes_value;
          angle_us = ON::AngleUnitSystem::Minutes;
        }
      }
    }
  }
  else
  {
    bNegativeDegreesMinutesSecondsIsPossible = false;
    angle_us = parse_settings.DefaultAngleUnitSystem();
  }

  if ( str_index > 0 && 0 != cSurveyorsNotationNS )
  {
    if ( str_count > 0 )
    {
      if (str_index+1 > str_count )
        return 0;
    }

    // Do not localize "E" or "e" or "W" or "w".  
    // These letters are specified by Surveyor's notation specification.
    // [TODO - Reference needed].
    switch(str[str_index])
    {
    case 'E': // Do not localize this letter
    case 'e': // Do not localize this letter
      str_index++;
      cSurveyorsNotationEW = 'E';
      break;
    case 'W': // Do not localize this letter
    case 'w': // Do not localize this letter
      str_index++;
      cSurveyorsNotationEW = 'W';
      break;
    default:
      cSurveyorsNotationEW = 0;
      break;
    }

    if (0 == cSurveyorsNotationEW )
      return 0;

    if ( ON::AngleUnitSystem::None == angle_us )
    {
      // Surveyor's notation implies degrees when no angle unit
      // is explicitly supplied.  This is done because it is
      // difficult for many users to enter a degree symbol
      // when typing input and Surveyor's notation is almost
      // always in degrees. [TODO cite reference].
      angle_us = ON::AngleUnitSystem::Degrees;
    }

    // The value of right_angle is calculated this way because it will
    // yield the most precise result in all angle unit systems since
    // IEEE double multiplication by 0.25 is exact and the value
    // returned by ON::AngleUnitScale(ON::turns,angle_us) is exact 
    // for all supported angle units except radians where pi rounded
    // because the IEEE double must approximate the value of pi.
    const double right_angle = 0.25*ON::AngleUnitScale(ON::AngleUnitSystem::Turns,angle_us);

    switch(cSurveyorsNotationNS)
    {
    case 'N':
      switch(cSurveyorsNotationEW)
      {
      case 'E': // N<angle>E
        x = right_angle - x;
        break;
      case 'W': // N<angle>W
        x = right_angle + x;
        break;
      default:
        return 0;
      }
      break;
    case 'S':
      switch(cSurveyorsNotationEW)
      {
      case 'E': // S<angle>E
        x =  -(right_angle - x);
        break;
      case 'W': // S<angle>W
        x =  -(right_angle + x);
        break;
      default:
        return 0;
      }
      break;
    default:
      return 0;
    }
  }

  if ( angle_value )
    *angle_value = x;
  if ( 0 != parse_results )
    *parse_results = pr;
  if ( 0 != str_angle_unit_system )
    *str_angle_unit_system = angle_us;

  return str_index;
}

