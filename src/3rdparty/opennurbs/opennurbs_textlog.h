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

#if !defined(ON_TEXTLOG_INC_)
#define ON_TEXTLOG_INC_

class ON_CLASS ON_TextLog
{
public:
  /*
  Description:
    Create a text log that dumps to the virtual function
    void ON_TextLog::AppendText().
  */
  ON_TextLog();

  /*
  Description:
    Create a text log that dumps to an ASCII file.
  Parameters:
    fp - [in] Pointer to an open ASCII text file.  The file
              pointer must remain valid as long as the text
              log is in use.
  */
  ON_TextLog( FILE* fp); // dump to open ASCII text file

  /*
  Description:
    Create a text log that dumps to a string.
  Parameters:
    s - [in] String that must exist as long as
             the text log is in use.
  */
  ON_TextLog( ON_wString& s );


  //////////////////////////////////////////////////////////////
  //
  // Level of detail interface
  //

  /// <summary>
  /// ON_TextLog::LevelOfDetail determines ow much detail is printed. Functions that have an ON_TextLog
  /// parameter, like the Dump() functions, may use the level of detail to tailor their output.
  /// may use the level of detail to tailor their output.
  /// </summary>
  enum class LevelOfDetail : unsigned char
  {
    /// <summary>
    /// A brief summary or synopsis.
    /// </summary>
    Minimum = 0,

    /// <summary>
    /// The default level of detail.
    /// </summary>
    Medium = 1,

    /// <summary>
    /// A verbose description that may be so long it obscures the important points.
    /// </summary>
    Maximum = 2
  };

  static ON_TextLog::LevelOfDetail LevelOfDetailFromUnsigned(
    unsigned int level_of_detail
  );

  /*
  Description:
    Set the level of detail to print.
  Parameters:
    level_of_detail - [in]
      (default = ON_TextLog::LevelOfDetail::Medium)
  */
  void SetLevelOfDetail(ON_TextLog::LevelOfDetail level_of_detail);

  /*
  Returns:
    Level of detail to print
    0 = minimum level of detail
    4 = maximum level of detail
  */
  ON_TextLog::LevelOfDetail GetLevelOfDetail() const;

  /// <summary>
  /// Increase the level of detail.
  /// </summary>
  /// <returns>
  /// Level of detail to restore when this scope of increased detail is finished.
  /// </returns>
  ON_TextLog::LevelOfDetail IncreaseLevelOfDetail();

  /// <summary>
  /// Decrease the level of detail.
  /// </summary>
  /// <returns>
  /// Level of detail to restore when this scope of decreased detail is finished.
  /// </returns>
  ON_TextLog::LevelOfDetail DecreaseLevelOfDetail();


  /*
  Parameter:
    level_of_detail - [in]
  Returns:
    True if this text log's level of detail the same or more detailed than
    the amount specified by level_of_detail.
  */
  bool LevelOfDetailIsAtLeast(ON_TextLog::LevelOfDetail level_of_detail);

  /*
  Description:
    ON_TextLog::Null is a silent text log and can be used when no output
    is desired but an ON_TextLog parameter is required.
  */
  static ON_TextLog Null;

  /*
  Returns:
    True if this is ON_TextLog::Null.
  */
  bool IsNull() const;

  /*
  Returns:
    True if the text is being used to calculate a geometric content SHA1 hash
    and non-geometry information that varies based on time, computer, or user 
    should not be printed.
  */
  bool IsTextHash() const;

public:
  virtual ~ON_TextLog();

  void SetDoubleFormat( const char* ); // default is %g
  void GetDoubleFormat( ON_String& ) const;

  void SetFloatFormat( const char* ); // default is %g
  void GetFloatFormat( ON_String& ) const;

  void SetColorFormat(ON_Color::TextFormat color_format);
  ON_Color::TextFormat GetColorFormat();

  /*
  Description:
    Returns color format to the default ON_Color::TextFormat::DecimalRGBa
  */
  void ClearColorFormat();

  void PushIndent();
  void PopIndent();
  int IndentSize() const; //  0: one tab per indent
                          // >0: number of spaces per indent
  void SetIndentSize(int);

  /*
  Returns:
    Current indentation count
  */
  int IndentCount();
  /*
  Description:
    Set indentation count.
  */
  void SetIndentCount(
    int indent_count
  );
  
  void PrintWrappedText( const char*, int = 60 );    // last arg is maximum line length
  void PrintWrappedText( const wchar_t*, int = 60 ); // last arg is maximum line length

  /*
  Description:
    Print a formatted ASCII string of up to 2000 characters.
  Parameters:
    format - [in] nullptr terminated format control string 
  Remarks:
    To print strings longer than 2000 characters, you must
    use ON_TextLog::PrintString.
  See Also:
    ON_TextLog::PrintString
  */
  void ON_VARGS_FUNC_CDECL Print(const char* format, ...);

  /*
  Description:
    Print a formatted UNICODE string of up to 2000 characters.
  Parameters:
    format - [in] nullptr terminated format control string 
  Remarks:
    To print strings longer than 2000 characters, you must
    use ON_TextLog::PrintString.
  See Also:
    ON_TextLog::PrintString
  */
  void ON_VARGS_FUNC_CDECL Print(const wchar_t* format, ...);

  void Print( float );
  void Print( double );
  void Print( const ON_2dPoint& );
  void Print( const ON_3dPoint& );
  void Print( const ON_4dPoint& );
  void Print( const ON_2dVector& );
  void Print( const ON_3dVector& );
  void Print( const ON_Xform& );
  void Print( const ON_UUID& );
  void Print( const ON_COMPONENT_INDEX& );

  /*
  Description:
    Print an unformatted wide char string of any length.
  Parameters:
    string - [in]
  */
  void Print( const ON_wString& string );

  /*
  Description:
    Print an unformatted UTF-8 string of any length.
  Parameters:
    string - [in]
  */
  void Print( const ON_String& string );

  void Print( const ON_3dPointArray&, const char* = nullptr );
  void Print( 
         const ON_Matrix&, 
         const char* = nullptr, // optional preamble
         int = 0             // optional number precision
    );

  // printing utilities
  /*
  Description:
    Same as calling Print("\n");
  */
  void PrintNewLine();

  /*
  Description:
    Same as calling Print(" ");
  */
  void PrintSpace();

  /*
  Description:
    Same as calling Print("\t");
  */
  void PrintTab();

  /*
  Description:
    Print an unformatted UTF-8 encoded null terminated string.
  Parameters:
    s - [in] UTF-8 encoded null terminated string.
  */
  void PrintString( const char* s );

  void PrintString(ON_String s);
  
  /*
  Description:
    Print an unformatted UTF-16 or UTF-32 encoded null terminated string.
  Parameters:
    s - [in] UTF-16 or UTF-32 encoded null terminated string.
  */
  void PrintString( const wchar_t* s );
  
  void PrintString(ON_wString s);

  /*
  Description:
    Print color using the format ON_Color::TextFormat::DecimalRGB.
  */
  void PrintRGB( const ON_Color& color);

  /*
  Description:
    Print color using ON_Color::ToText(this->GetColorFormat(),0,true,*this);
  */
  void PrintColor(const ON_Color& color);

  /*
  Description:
    Prints the time in the t parameter as Universal Coordinated Time in English.
    weekday month date::hour::min::sec year
  Parameters:
    t - [in]
  */
  void PrintTime( 
    const struct tm& t 
  );

  /*
  Description:
    Prints the current Universal Coordinated Time returned by the gmtime() function in English.
    weekday month date::hour::min::sec year
  */
  void PrintCurrentTime();

  void PrintPointList( 
    int,               // dim
    bool,              // true for rational points
    int,               // count
    int,               // stride
    const double*,     // point[] array
    const char* = nullptr // optional preamble
    );

  void PrintPointGrid( 
    int,               // dim
    bool,              // true for rational points
    int, int,          // point_count0, point_count1
    int, int,          // point_stride0, point_stride1
    const double*,     // point[] array
    const char* = nullptr // optional preamble
    );
    
  void PrintKnotVector( 
    int,             // order
    int,             // cv_count
    const double*    // knot[] array
    );

  ON_TextLog& operator<<( const char* );
  ON_TextLog& operator<<( char );
  ON_TextLog& operator<<( short );
  ON_TextLog& operator<<( int );
  ON_TextLog& operator<<( float );
  ON_TextLog& operator<<( double );
  ON_TextLog& operator<<( const ON_2dPoint& );
  ON_TextLog& operator<<( const ON_3dPoint& );
  ON_TextLog& operator<<( const ON_4dPoint& );
  ON_TextLog& operator<<( const ON_2dVector& );
  ON_TextLog& operator<<( const ON_3dVector& );
  ON_TextLog& operator<<( const ON_Xform& );

protected:
  friend class ON_TextHash;

  FILE* m_pFile = nullptr;
  ON_wString* m_pString = nullptr;
  
  /*
  Description:
    If the ON_TextLog(ON_wString& wstr) constructor was used, the
    default appends s to wstr.  If the ON_TextLog(FILE* fp) 
    constructor was used, the default calls fputs( fp, s).
    In all other cases, the default calls printf("%s",s).
  Parameters:
    s - [in];
  */
  virtual
  void AppendText(
        const char* s
        );

  /*
  Description:
    If the ON_TextLog(ON_wString& wstr) constructor was used, the
    default appends s to wstr.  In all other cases, the default 
    converts the string to an ON_String and calls the ASCII
    version AppendText(const char*).
  Parameters:
    s - [in];
  */
  virtual
  void AppendText(
        const wchar_t* s
        );
                  
private:
  ON_String m_indent;
  ON_String m_double_format;
  ON_String m_double2_format;
  ON_String m_double3_format;
  ON_String m_double4_format;
  ON_String m_float_format;
  ON_String m_float2_format;
  ON_String m_float3_format;
  ON_String m_float4_format;

  ON_String m_line;

  int m_beginning_of_line = 1;

  // size of a single indentation
  int m_indent_size = 0;       // 0 use tabs, > 0 = number of spaces per indent level

  // Number of indentations at the start of a new line
  int m_indent_count = 0;

  const bool m_bNullTextLog = false;
  ON_TextLog::LevelOfDetail m_level_of_detail = ON_TextLog::LevelOfDetail::Medium;
  ON_Color::TextFormat m_color_format = ON_Color::TextFormat::DecimalRGBa;
  ON__UINT8 m_reserved1 = 0;

private:
  ON_TextLog( const ON_TextLog& ) = delete;
  ON_TextLog& operator=( const ON_TextLog& ) = delete;
};

/*
Description:
  ON_TextLogIndent is a class used with ON_TextLog to
  push and pop indentation.
*/
class ON_CLASS ON_TextLogIndent
{
public:
    // The constructor calls text_log.PushIndent()
    // and the destructor calls text_log.PopIndent()
  ON_TextLogIndent(
    class ON_TextLog& text_log
    );

    // If bEnabled is true, the constructor calls text_log.PushIndent()
    // and the destructor calls text_log.PopIndent()
    ON_TextLogIndent(
      class ON_TextLog& text_log,
      bool bEnabled
    );

  ~ON_TextLogIndent();

private:
  class ON_TextLog& m_text_log;
  bool m_bEnabled;

  // prevent use of copy construction and operator=
  // (no implementations)
  ON_TextLogIndent(const ON_TextLogIndent&) = delete;
  ON_TextLogIndent& operator=(const ON_TextLogIndent&) = delete;
};


/*
Description:
  ON_TextLogLevelOfDetail is a class used with ON_TextLog to push and pop level of detail.
*/
class ON_CLASS ON_TextLogLevelOfDetail
{
public:

  // The constructor saves the current level of detail and then sets the level of detail to level_of_detail.
  ON_TextLogLevelOfDetail(
    class ON_TextLog& text_log,
    ON_TextLog::LevelOfDetail level_of_detail
  );

  /// <summary>
  /// 
  /// </summary>
  /// <param name="text_log"></param>
  /// <param name="delta_lod">
  /// Amount to change the level of detail.
  /// +1 increases the level of detail by a single level.
  /// -1 decreases the level of detail by a single level.
  /// </param>
  ON_TextLogLevelOfDetail(
    class ON_TextLog& text_log,
    int delta_lod
  );

  // The destructor restores the level ot detail the saved value.
  ~ON_TextLogLevelOfDetail();

  /*
  Returns:
    Level of detail the text log had when the constructor was called.
  */
  ON_TextLog::LevelOfDetail SavedLevelOfDetail() const;

private:
  ON_TextLogLevelOfDetail() = delete;
  ON_TextLogLevelOfDetail(const ON_TextLogLevelOfDetail&) = delete;
  ON_TextLogLevelOfDetail& operator=(const ON_TextLogLevelOfDetail&) = delete;

private:
  class ON_TextLog& m_text_log;
  const ON_TextLog::LevelOfDetail m_saved_level_of_detail;
};

class ON_CLASS ON_TextHash : public ON_TextLog
{
public:
  ON_TextHash() = default;
  ~ON_TextHash() = default;

private:
  ON_TextHash(const ON_TextHash&) = delete;
  ON_TextHash& operator= (const ON_TextHash&) = delete;

public:

  ON_StringMapType StringMapType() const;

  const class ON_Locale& StringMapLocale() const;

  void SetStringMap(
    const class ON_Locale& locale,
    ON_StringMapType map_type
  );

  void SetStringMap(
    ON_StringMapOrdinalType map_type
  );

  /*
  Parameters:
    bEnableIdRemap - [in]
    if bEnableIdRemap is true, the sequences of
    code points that match the format
    XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
    where X is a hexadecimal digit (0-9, a-f, or A-F)
    and the hyphen is literal.
    will be replaced with an id created by 
    ON_NextNotUniqueId(). 
    This is used for comparing code that generates streams
    containing new uuids.
  */
  void SetIdRemap(
    bool bEnableIdRemap
  );

  /*
  Returns:
    True if id remap is available.
  */
  bool IdRemap() const;

  /*
  Description:
    In some testing situations, the output text log can be set 
    when it is necessary to see the text used to compute the 
    SHA-1 hash. The has can be calculate which no output text
    log.

  Parameters:
    output_text_log - [in]
      Destination text log for the mtext used to calculate the hash.
  */
  void SetOutputTextLog(
    ON_TextLog* output_text_log
  );

  ON_TextLog* OutputTextLog() const;

  /*
  Returns:
    Total number of bytes that have passed through this text log.
  */
  ON__UINT64 ByteCount() const;

  /*
  Returns:
    SHA-1 hash value of the text sent to this text log.
  */
  ON_SHA1_Hash Hash() const;

private:
  void AppendText(const char* s) override;
  void AppendText(const wchar_t* s) override;

private:
  bool m_bApplyStringMap = false;
  bool m_bApplyIdRemap = false;
  
  ON_UUID m_remap_id = ON_nil_uuid;
  ON_UuidPairList2 m_remap_id_list;

  ON_StringMapType m_string_map_type = ON_StringMapType::Identity;
  ON_StringMapOrdinalType m_string_map_ordinal_type = ON_StringMapOrdinalType::Identity;
  ON_Locale m_string_map_local = ON_Locale::InvariantCulture;

  ON_TextLog* m_output_text_log = nullptr;

  static const char* Internal_ParseId(
    const char* s,
    ON_UUID* id
  );

  static bool Internal_IsHexDigit(char c);

  ON_SHA1 m_sha1;
};


#endif
