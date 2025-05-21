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

#if !defined(OPENNURBS_LOCALE_INC_)
#define OPENNURBS_LOCALE_INC_

typedef 
#if defined(ON_RUNTIME_WIN)
  _locale_t
#elif defined(ON_RUNTIME_APPLE)
  locale_t
#elif defined(ON_RUNTIME_ANDROID)
  locale_t
#else
  ON__UINT_PTR
#endif
  ON_CRT_locale_t;

class ON_CLASS ON_Locale
{
public:

  enum WindowsLCID : unsigned int
  {
    OrdinalLCID = 0, // not a real Windows LCID

    InvariantCultureLCID = 0x0027, // 39 decimal

    // Windows LCID for languages Rhino supports

    // "cs-CZ" Czech, ???? script implied
    cs_CZ_LCID = 0x0405, //1029 decimal

    // "de-DE" German, Germany, Latn script implied
    de_DE_LCID = 0x0407, // 1031 decimal

    // "en-US" English, US, Latn script implied
    en_US_LCID = 0x0409, // 1033 decimal

    // "en-CA" English, Canada, Latn script implied
    en_CA_LCID = 0x1009, // 4105 decimal

    // "es-ES_tradnl" Spanish, Spain, Latn script implied, traditional sort
    es_ES_tradnl_LCID = 0x040A, // 1034 decimal

    // "es-ES" Spanish, Spain, Latn script implied, modern sort
    es_ES_LCID =  0x0c0a, // 3082 decimal

    // "fr-FR" French, France, Latn script implied
    fr_FR_LCID = 0x040c, // 1036 decimal

    // "it-IT" Italian, Italy, Latn script implied
    it_IT_LCID = 0x0410, // 1040 decimal

    // "ja-JP" Japanese, Japan, ???? script implied
    ja_JP_LCID = 0x0411, // 1041 decimal

    // Korean, Republic of Korea, ???? script implied
    ko_KR_LCID = 0x0412, // 1042 decimal

    // Polish, Poland, ???? script implied
    pl_PL_LCID = 0x0415, // 1045 decimal

    // Portuguese, Portugal, Latn script implied
    pt_PT_LCID = 0x0816, // 2070 decimal

    // According to https://en.wikipedia.org/wiki/Chinese_language, Chinese is a family of language
    // varieties, often mutually unintelligible.  Specifying both Script and REGION
    // (zh-Hans-CN or zh-Hant-TW) doesn't narrow things down nearly enough. 
    //
    // Basically we have to hope the string collate and mapping functions supplied by the OS and 
    // the translations supplied by our staff work well for our customers who select from the 
    // two types of "Chinese" Rhino offers.
    //

    // Standard Chinese (Mandarin), Peoples Republic of China, Hans script implied (simplified characters) 
    zh_CN_LCID = 0x0804, // 2052 decimal

    // Standard Chinese (Mandarin), Taiwan, Hant script implied (traditional characters)
    zh_TW_LCID = 0x0404 // 1028 decimal
  };

  // The ordinal locale.  
  // String compares use ordinal element values.
  // The decimal point is a period.
  static const ON_Locale Ordinal;

  // The invariant culture locale.
  // The decimal point is a period.
  static const ON_Locale InvariantCulture;

private:
  static ON_Locale m_CurrentCulture;

public:
  // Reference to ON_Locale::m_CurrentCulture.
  // The value is set by calling ON_Locale::SetCurrentCulture();
  // The default is a copy of ON_Locale::Ordinal.
  static const ON_Locale& CurrentCulture;

  /*
  Description:
    Set the current culture locale
  Parameters:
    current_culture_locale - [in]
  */
  static bool SetCurrentCulture(
    const ON_Locale& current_culture_locale
    );

  
  // Default construction creates a copy of ON_Local::Ordinal
  ON_Locale() ON_NOEXCEPT;

  ~ON_Locale() = default;
  ON_Locale(const ON_Locale&) = default;
  ON_Locale& operator=(const ON_Locale&) = default;

  // Maximum buffer capacity for any ON_Locale functions
  // that return string information in a buffer.
  enum
  {
    BUFFER_MAXIMUM_CAPACITY = 128
  };

  /*
  Description:
    Get the language id.

  Parameters:
    buffer - [out]
      A null terminated string containing the language id is returned in this buffer.
      The string has the form:

        <language>[-<Script>][-<REGION>]

        <language>
        ISO 639 language code.
        http://www.iso.org/iso/language_codes

        <Script> is optional.
        If present, it is a 4 alpha letter ISO 15924 script code
        http://www.unicode.org/iso15924/iso15924-codes.html

        <REGION>
        ISO 3166-1 country/region identifier. (2 alpha letters)
        or UN M.49 code (3 digits)
        http://www.iso.org/iso/home/standards/country_codes.htm
      
    buffer_capacity - [in]
      number of elements in the buffer.
      A capacity >= ON_Locale::BUFFER_MAXIMUM_CAPACITY will be large enough to 
      hold all possible output.

  Returns:
    If buffer_capacity is to small or buffer is nullptr, then nullptr is returned.
    Otherwise the pointer to buffer is returned.
  
  Remarks:
    The Invariant language name is the empty string "".
  */
  const char* GetBCP47LanguageTag(
    char* buffer,
    size_t buffer_capacity
    ) const;

  const wchar_t* GetBCP47LanguageTag(
    wchar_t* buffer,
    size_t buffer_capacity
    ) const;

  /*
  Parameters:
    A string of the form

      <language>[-<Script>][-<REGION>]

      <language>
      ISO 639 language code.
      http://www.iso.org/iso/language_codes

      <Script> is optional.
      If present, it is a 4 alpha letter ISO 15924 script code
      http://www.unicode.org/iso15924/iso15924-codes.html

      <REGION>
      ISO 3166-1 country/region identifier. (2 alpha letters)
      or UN M.49 code (3 digits)
      http://www.iso.org/iso/home/standards/country_codes.htm

  Remarks:
    ON_Locale::InvariantCulture.BCP47LanguageName() = "";
    ON_Locale::Ordinal.BCP47LanguageName() = "";
  */
  const char* BCP47LanguageTag() const;


  /*
  Returns:
    ISO 639 language code.
    When available, two letter codes from ISO 639-1 are preferred.
  Remarks:
    The InvariantCulture.LanguageCode() is "".
  See Also:
    http://www.iso.org/iso/language_codes
  */
  const char* LanguageCode() const;

  /*
  Returns:
    ISO 3166-1 country/region identifier (2 alpha) or UN M.49 code (3 digits)
  Remarks:
    The returned string can be "" if the no region is specified.
    The InvariantCulture.RegionCode() is "".
  See Also:
    http://www.iso.org/iso/home/standards/country_codes.htm
  */
  const char* RegionCode() const;

  /*
  Returns:
    A 4 letter ISO 15924 script code
  Remarks:
    The returned string can be "" if the no script is specified for the locale.
    The InvariantCulture.ScriptCode() is "".
  See Also:
    http://www.unicode.org/iso15924/iso15924-codes.html
  */
  const char* ScriptCode() const;


  /*
  Returns:
    Microsoft Windows LCID value
    ON_LocaleLCID::OrdinalLCID (=0)
      The locale is a copy of ON_Locale::Ordinal.
    ON_Locale::InvariantCultureLCID (=0x00000027U)
      The locale is a copy of ON_Locale::InvariantCulture.
  */
  ON__UINT32 WindowsLCID() const;

  /*
  Description:
    Get the Microsoft Windows locale id.

  Parameters:
    buffer - [out]
      A null terminated string containing the Microsoft Windows locale id is returned in this buffer.
      The string has the form:

       <language>[-<Script>][-<REGION>][_<sort_order>] (UTF-8 string encoding)

        <language>
        ISO 639 language code.
        http://www.iso.org/iso/language_codes

        <Script> is optional.
        If present, it is a 4 alpha letter ISO 15924 script code
        http://www.unicode.org/iso15924/iso15924-codes.html

        <REGION>
        ISO 3166-1 country/region identifier. (2 alpha letters)
        or UN M.49 code (3 digits)
        http://www.iso.org/iso/home/standards/country_codes.htm

        <sort_order>
        Up to six letters specifying a sort order.
        Microsoft Windows codes are used.
      
    buffer_capacity - [in]
      number of elements in the buffer.
      A capacity >= ON_Locale::BUFFER_MAXIMUM_CAPACITY will be large enough to 
      hold all possible output.

  Returns:
    If buffer_capacity is to small or buffer is nullptr, then nullptr is returned.
    Otherwise the pointer to buffer is returned.
  
  Remarks:
    The Invariant locale name is the empty string "".
  */
  const char* GetWindowsLocaleName(
    char* buffer,
    size_t buffer_capacity
    ) const;

  const wchar_t* GetWindowsLocaleName(
    wchar_t* buffer,
    size_t buffer_capacity
    ) const;

  /*
  Returns:
    Apple OS X / iOS locale name in the form
    <language>[-<Script>][_<REGION>]

    <language>
    ISO 639 language code.
    When available, two letter codes from ISO 639-1 are preferred.
    http://www.iso.org/iso/language_codes

    <Script> is optional.
    If present, it is a 4 alpha letter ISO 15924 script code
    http://www.unicode.org/iso15924/iso15924-codes.html

    <REGION>
    ISO 3166-1 country/region identifier. (2 alpha letters)
    or UN M.49 code (3 digits)
    http://www.iso.org/iso/home/standards/country_codes.htm

  Remarks:
    The Invariant locale name is the empty string "".
    Apple language names have a hyphen (-) before the region.
    Apple locale names have an underbar (_) before the region.
  */
  const char* GetAppleLocaleName(
    char* buffer,
    size_t buffer_capacity
    ) const;

  const wchar_t* GetAppleLocaleName(
    wchar_t* buffer,
    size_t buffer_capacity
    ) const;

  /*
  Returns:
    Apple OS X / iOS locale name in the form
    <language>[-<Script>][-<REGION>]

    <language>
    ISO 639 language code.
    When available, two letter codes from ISO 639-1 are preferred.
    http://www.iso.org/iso/language_codes

    <Script> is optional.
    If present, it is a 4 alpha letter ISO 15924 script code
    http://www.unicode.org/iso15924/iso15924-codes.html

    <REGION>
    ISO 3166-1 country/region identifier. (2 alpha letters)
    or UN M.49 code (3 digits)
    http://www.iso.org/iso/home/standards/country_codes.htm

  Remarks:
    The Invariant locale name is the empty string "".
    Apple language names have a hyphen (-) before the region.
    Apple locale names have an underbar (_) before the region.
  */
  const char* GetAppleLanguageName(
    char* buffer,
    size_t buffer_capacity
    ) const;

  const wchar_t* GetAppleLanguageName(
    wchar_t* buffer,
    size_t buffer_capacity
    ) const;

  /*
  Returns:
    A 6 letter locale sort order.
  Remarks:
    The returned string can be "" if the no sort order is specified for the locale.
    The InvariantCulture.WindowsSortOrder() is "".
  See Also:
    https://msdn.microsoft.com/en-us/library/windows/desktop/dd374060(v=vs.85).aspx
  */
  const char* WindowsSortOrder() const;

  /*
  Returns:
    True if the C runtime formatted printing and scanning functions
    are using the period character as the decimal point for 
    doubles and floats.
  */
  static bool PeriodIsCRuntimeDecimalPoint();

  /*
  Description:
    Use a call like setlocale(LC_NUMERIC,"C") to configure the 
    C runtime formatted printing and scanning functions to use the
    period character as the decimal point for doubles and floats.
  Returns:
    True if successful.
  */
  static bool SetPeriodAsCRuntimeDecimalPoint();


  /*
  Description:
    Use a call like setlocale(LC_NUMERIC,"C") to configure the
    C runtime formatted printing and scanning functions to use the
    period character as the decimal point for doubles and floats.
  Returns:
    0: failed
    1: success
       Currently The decimal point is a period in the C-runtime 
       formatted printing and scanning functions.
    2: success
       When called, the decimal point was not a period, but
       a call to ON_Locale::SetPeriodAsCRuntimeDecimalPoint()
       restored the default behavior.
  */
  static unsigned int EnforcePeriodAsCRuntimeDecimalPoint();


  /*
  Returns:
    True if this is ON_Locale:InvariantCulture or a copy.
  */
  bool IsInvariantCulture() const;

  /*
  Returns:
    True if this is ON_Locale:Ordinal or a copy.
  */
  bool IsOrdinal() const;

  /*
  Returns:
    True if this is ON_Locale:Ordinal, ON_Locale:InvariantCulture or a copy
    of one of them.
  */
  bool IsOrdinalOrInvariantCulture() const;

  /*
  Description:
    NumericLocalePtr() is an expert user function needed
    to call C-runtime functions that format or parse numbers.
    This locale must never be used to collate or map strings.

    The primary use for this function is in opennurbs implementations
    of ON_String and ON_wString number formatting and parsing functions.
  Example:

       // Call _sprintf_p_l
       ON_CRT_locale_t numeric_locale = ON_Locale::CurrentCulture::NumericLocalePtr();
        _sprintf_p_l(....,locale,...);

  Returns:
    A value that can be passed into C-runtime functions that take
    a locale parameter.
  */
  ON_CRT_locale_t NumericLocalePtr() const;


  /*
  Description:
    StringCollateAndMapLocalePtr() is an expert user function needed
    to call C-runtime functions that collate (compare) 
    and map (toupper/tolower) strings. This locale must never be used
    for formatting or parsing numbers.

    The primary use for this function is in opennurbs implementations
    of ON_String and ON_wString collate and map functions.
  Example:

       // Call _wcsicoll_l
       ON_CRT_locale_t coll_locale = ON_Locale::CurrentCulture::StringCollateAndMapLocalePtr();
        _wcsicoll_l(....,coll_locale);

  Returns:
    A value that can be passed into C-runtime functions that take
    a locale parameter.
  */
  ON_CRT_locale_t StringCollateAndMapLocalePtr() const;

  /*
  Description:
    Create a locale from a Windows locale id.
  
  Parameters:
    lcid - [in]
      Windows LCID value or zero for the "ordinal" locale.

  Returns:
    ON_Locale identified by lcid.
    If lcid is not valid or not supported, a copy of ON_Locale::Ordinal is returned.
  */
  static ON_Locale FromWindowsLCID(
    ON__UINT32 windows_lcid
    );
  
  /*
  Description:
    Create a locale from a BCP 47 language name.

  Parameters:
    language_name - [in]
      The language name has the form
      <language>[-<Script>][-<REGION>]
      Case is not important.

  Returns:
    ON_Locale identified by language_name.
    If locale_name is not valid or not supported, a copy of ON_Locale::Ordinal is returned.
  */
  static ON_Locale FromBCP47LanguageName(
    const char* language_name
    );

  static ON_Locale FromBCP47LanguageName(
    const wchar_t* language_name
    );
  
  /*
  Description:
    Create a locale from a Windows locale name.

  Parameters:
    windows_name - [in]
      The Windows name has the form
      <language>[-<Script>][-<REGION>][_<sort_order>]
      Case is not important.

  Returns:
    ON_Locale identified by locale_name.
    If locale_name is not valid or not supported, a copy of ON_Locale::Ordinal is returned.
  */
  static ON_Locale FromWindowsName(
    const char* windows_name
    );

  static ON_Locale FromWindowsName(
    const wchar_t* windows_name
    );
  
  /*
  Description:
    Create a locale from an Apple locale or language name
  Parameters:
    apple_name - [in]
      The Apple name has the form <language>[-<Script>][-<REGION>].
      An underbar (_) may be used in place of a hyphen (-).
      Case is not important.
  Returns:
    ON_Locale identified by locale_name.
    If locale_name is not valid or not supported, a copy of ON_Locale::Ordinal is returned.
    
  */
  static ON_Locale FromAppleName(
    const char* apple_name
    );

  static ON_Locale FromAppleName(
    const wchar_t* apple_name
    );

  /*
  Description:
    Create a locale from BCP 47 language code, script code and region code.

  Parameters:
    language_code - [in]
      ISO 639 language code.
      When available, two letter codes from ISO 639-1 are preferred.
      http://www.iso.org/iso/language_codes

    script - [in]
      nullptr, empty string, or a 4 letter ISO 15924 script code
      http://www.unicode.org/iso15924/iso15924-codes.html

    <REGION>
      nullptr, empty string, or an ISO 3166 country/region identifier.
      http://www.iso.org/iso/home/standards/country_codes.htm

 Returns:
    ON_Locale identified by the locale name.
    If the locale name is not valid or not supported, a copy of ON_Locale::Ordinal is returned.
  */
  static ON_Locale FromSubtags(
    const char* language_code,
    const char* script_code,
    const char* region_code
    );

  static ON_Locale FromSubtags(
    const wchar_t* language_code,
    const wchar_t* script_code,
    const wchar_t* region_code
    );

  /*
  Description:
    Attempt to parse a string that is a language name or locale name 
    and extract language code, extlang code script code, region code 
    and Windows sort order.

    The language name has the form  <language>[<-extlang>][-<Script>][-<REGION>]
    
    If the Microsoft [_<windows_sort_order>] appears after the language name,
    it is parsed.
    
    Apple "locale ids" of the form <language>_<REGION>" are parsed as well
    (an underbar separator instead of a hyphen before <REGION>).

  Parameters:
    locale_name - [in]
      name to parse. Case is ignored.
    locale_name_element_count - [in]
      number of elements to parse in locale_name[]
      If locale_name_element_count < 0, then a null terminator ends parsing.

    language_code - [out]
    language_code_capacity - [in]
      number of elements available in language_code[].

    extlang_code - [out]
    extlang_code_capacity - [in]
      number of elements available in extlang_code[].

    script_code - [out]
    script_code_capacity - [in]
      number of elements available in script_code[].

    region_code - [out]
    region_code_capacity - [in]
      number of elements available in region_code[].

    windows_sortorder - [out]
    windows_sortorder_capacity - [in]
      number of elements available in windows_sortorder[].

  Remarks:
    The standards for language identifiers (RFC 5646 and BCP 47) states that a hyphen
    ( Unicode U+002D ) is supposed to be the separator between subtags.
    
    ftp://ftp.isi.edu/in-notes/bcp/bcp47.txt
  */
  static bool ParseName(
    const wchar_t* locale_name,
    int locale_name_element_count,
    wchar_t* language_code,
    size_t language_code_capacity,
    wchar_t* extlang_code,
    size_t extlang_code_capacity,
    wchar_t* script_code,
    size_t script_code_capacity,
    wchar_t* region_code,
    size_t region_code_capacity,
    wchar_t* windows_sortorder,
    size_t windows_sortorder_capacity
    );

  static bool ParseName(
    const char* locale_name,
    int locale_name_element_count,
    char* language_code,
    size_t language_code_capacity,
    char* extlang_code,
    size_t extlang_code_capacity,
    char* script_code,
    size_t script_code_capacity,
    char* region_code,
    size_t region_code_capacity,
    char* windows_sortorder,
    size_t windows_sortorder_capacity
    );

private:
  ON_CRT_locale_t m_numeric_locale = 0;         // pointer to a C runtime locale type
  ON_CRT_locale_t m_string_coll_map_locale = 0; // pointer to a C runtime locale type

  char m_bcp47_language_tag[85]; // <language>-<Script>-<REGION>
  
  // RFC 4646 language identifier
  char m_language_subtag[9];   // ISO 639 code (RFC 4646 reserves 8 alpha elements)
  char m_script_subtag[5];     // ISO 15924 code
  char m_region_subtag[5];     // ISO 3166 code (2 alpha) or UN M.49 code (3 digit)

  char m_windows_sortorder[7]; // Windows sort order
  char m_reserved2[21];

  // Values needed to use Windows tools
  ON__UINT32 m_windows_lcid = 0;    // Microsoft Windows LCID values (0 = ordinal, 0x0027 = invariant culture)
  ON__UINT32 m_reserved3 = 0;

private:

  // Construct from lcid and matching name
  static ON_Locale FromWindowsLCIDAndName(
    ON__UINT32 windows_lcid,
    const char* name
    );

  // Construct from perfect input
  //ON_Locale(
  //  ON__UINT_PTR string_coll_map_locale_ptr,
  //  ON__UINT32 windows_lcid,
  //  const char* language_name,
  //  const char* language_code,
  //  const char* script_code,
  //  const char* region_code,
  //  const char* windows_sortorder
  //  );

};

#endif
