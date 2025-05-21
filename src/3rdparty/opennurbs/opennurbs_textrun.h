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

#ifndef OPENNURBS_TEXTRUN_H_INCLUDED
#define OPENNURBS_TEXTRUN_H_INCLUDED

class ON_CLASS ON_StackedText
{
public:
  static const ON_StackedText Empty;

public:
  ON_StackedText() = default;
  ~ON_StackedText();
  ON_StackedText(const ON_StackedText& src);

  // Sets m_parent_run = nullptr.
  // You must set m_parent_run after calling operator=().
  ON_StackedText& operator=(const ON_StackedText& src);

  class ON_TextRun*  m_top_run = nullptr;
  class ON_TextRun*  m_bottom_run = nullptr;
  const ON_TextRun*  m_parent_run = nullptr;
  wchar_t            m_separator = (wchar_t)ON_UnicodeCodePoint::ON_Slash;

  enum class StackStyle : unsigned char
  {
    kUnset = 0,
    kHorizontalToScreen = 1,
    kSlanted    = 2,
  };

  static ON_StackedText::StackStyle StackStyleFromUnsigned(
    unsigned int stack_style_as_unsigned
    );

private:
  friend class ON_TextRun;

  //bool WriteNested(
  //  unsigned int nested_depth,
  //  ON_BinaryArchive& archive
  //  ) const;

  //bool ReadNested(
  //  unsigned int nested_depth,
  //  ON_BinaryArchive& archive
  //  );
};

// A range of text with all the same attributes
class ON_CLASS ON_TextRun
{
public:
  static const ON_TextRun Empty;

  /*
  Description:
    ON_TextRun::NewTextRun() gets a text run from an efficiently managed pool.
  Returns:
    A pointer to a text run. (never nullptr).
  */
  static ON_TextRun* GetManagedTextRun();

  
  /*
  Description:
    ON_TextRun::NewTextRun() gets a text run from an efficiently managed pool
    and copies src
  Returns:
    A pointer to a text run. (never nullptr).
  */
  static ON_TextRun* GetManagedTextRun(
    const ON_TextRun& src
    );

  /*
  Description:
    Return a managed ON_TextRun.
  */
  static bool ReturnManagedTextRun(
    ON_TextRun* managed_text_run
    );

  /*
  Returns:
    True if the memory for this ON_TextRun is managed.
    It was created by calling ON_TextRun::GetManagedTextRun(). If it is active,
    then is must be deleted by calling ON_TextRun::ReturnManagedTextRun();
  */
  bool IsManagedTextRun() const;

  /*
  Returns:
    True if the memory for this ON_TextRun is managed and the text run is active.
    It was created by calling ON_TextRun::GetManagedTextRun() and should be
    deleted by calling ON_TextRun::ReturnManagedTextRun();
  */
  bool IsActiveManagedTextRun() const;

public:
  ON_TextRun() = default;
  ~ON_TextRun();
  ON_TextRun(const ON_TextRun& src);
  ON_TextRun& operator=(const ON_TextRun& src);

private:
  ON_TextRun(bool bManagedTextRun);
    
public:
  enum class RunType : unsigned char
  {
    kNone        = 0,
    kText        = 1,
    kNewline     = 2,
    kSoftreturn  = 3,
    kParagraph   = 4,
    kColumn      = 5,
    kField       = 6,
    kFieldValue  = 7,
    kFontdef     = 8,
    kHeader      = 9,
    kFonttbl     = 10,
    kColortbl    = 11,
  };

  static ON_TextRun::RunType RunTypeFromUnsigned(
    unsigned int run_type_as_unsigned
    );

  enum class Stacked : unsigned char
  {
    kNone     = 0,
    kStacked  = 1,
    kTop      = 2,
    kBottom   = 3
  };

  static ON_TextRun::Stacked StackedFromUnsigned(
    unsigned int stacked_as_unsigned
    );

  enum class RunDirection : unsigned char
  {
    kLtR      = 0,
    kRtL      = 1,
  };
  
  static ON_TextRun::RunDirection RunDirectionFromUnsigned(
    unsigned int run_direction_as_unsigned
    );

public:

  ON_SHA1_Hash TextRunContentHash() const;
  ON_SHA1_Hash TextRunContentHash(
  bool bEvaluateFields
  ) const;


  void Init(
    const class ON_Font* managed_font,
    double height,
    double stackscale,
    ON_Color color,
    bool bold,
    bool italic,
    bool underlined,
    bool strikethrough,
    bool deletedisplay = true);

  bool IsText() const;
  bool IsNewline() const;
  bool IsColumn() const;
  bool IsValid() const;
  
  RunType Type() const;
  void SetType(ON_TextRun::RunType);
  RunDirection FlowDirection() const;

  Stacked IsStacked() const;
  void SetStacked(Stacked stacked);
  void SetStackedOff();

  // Set or get the WCS model unit height of the text
  // not including any annotation scaling
  double TextHeight() const;

  void SetTextHeight(double h);

  ON_Color Color() const;
  void SetColor(ON_Color color);

  void SetFont(const ON_Font* font);
  const ON_Font* Font() const;
  
  // bbox is stored as ON_BoundingBox, but is always 2d. z=0
  const ON_BoundingBox& BoundingBox() const;
  void SetBoundingBox(ON_2dPoint pmin, ON_2dPoint pmax);

  const ON_2dVector& Offset() const;
  void SetOffset(ON_2dVector offset);

  const ON_2dVector& Advance() const;
  void SetAdvance(ON_2dVector advance);

  // This returns the scale of m_height / HeightOfI.
  // It doesn't take into account anything about annotation scaling
  // This is the scale for converting ON_TextRun bounding boxes and 
  // offsets to basic model units
  double HeightScale(const ON_Font* font) const;

  void SetStackFractionHeight(double stackscale);
  double StackHeightFraction() const;
  static double DefaultStackFractionHeight();

  //bool Write(
  //  ON_BinaryArchive&
  //  ) const;
  //bool Read(
  //  ON_BinaryArchive&
  //  );

  void Get2dCorners(ON_2dPoint corners[4]) const;

private:
  static
  void SetUnicodeString(ON__UINT32*& dest, size_t count, const ON__UINT32* cp);

public:
  void SetUnicodeString(size_t count, const ON__UINT32* cp);
  static size_t CodepointCount(const ON__UINT32* cp);

  // Returns string in m_display_string, which may be the result of parsing text fields
  void SetDisplayString(const wchar_t* str);

  // The display string is the TextString() with formulae evaluated.
  const wchar_t* DisplayString() const; 

  // Returns the string in m_text_string, which is a wchar_t version of the basic text for this run,
  // and may contain unevaluated field formulae
  const wchar_t* TextString() const;

  const ON__UINT32* UnicodeString() const;

  bool GetGlyphContours(
    const ON_Font* text_font,
    bool bSingleStrokeFont,
    const ON_Xform& text_xform,
    ON_ClassArray< ON_ClassArray< ON_SimpleArray< ON_Curve* > > >& run_contours
  ) const;

  friend class ON_TextBuilder;

  // Wrap text to a specified width in model space
  int WrapTextRun(
    int call_count,
    int start_char_offset,
    double width,
    double &y_offset,
    double& currentwidth,
    class ON_TextRunArray& newruns) const;

  const ON_Font*      m_managed_font = nullptr;   // Font used to draw, pick, or otherwise evaluate this
                                                  // ON_TextRun.  This pointer is run-time only and must be 
                                                  // set and point to a valid ON_Font for any font related 
                                                  // operations to work.

//  ON_UUID              m_Font_id = ON_nil_uuid;
private:
  ON__UINT32*          m_codepoints = nullptr;     // Parsed text as UTF32
  
  // Set from m_codepoints when required.
  // Always use TextString() to get this value
  mutable ON_wString   m_text_string = ON_wString::EmptyString; 
                                                   // Parsed text as wchar_t*
                                                   // If this string is non-empty, it is valid and can be used 
                                                   // instead of m_codepoints
                                                   // This string may have unevaluated field definitions - %<field_name>%
  
  mutable ON_wString   m_display_string = ON_wString::EmptyString;  
                                                   // Text to display when this is drawn. 
                                                   // If this text has field definitions, m_display_string will have the 
                                                   // evaluation results to display
                                                   // This string may change often if there are fields to evaluate.

  mutable ON_SHA1_Hash m_text_run_hash = ON_SHA1_Hash::ZeroDigest;
  mutable ON_SHA1_Hash m_text_run_display_hash = ON_SHA1_Hash::ZeroDigest;

  ON_TextRun::Stacked  m_text_stacked = ON_TextRun::Stacked::kNone; // 0: Normal text, 1: Run is stacked container, 2: Run is top of stacked fraction, 3: Run is bottom of stacked fraction

private:
  void Internal_ContentChanged() const;
public:
  ON_StackedText*      m_stacked_text = nullptr;    // pointers to runs for the top and bottom parts

  ON_Color             m_color = ON_Color::UnsetColor;
private:
  ON_TextRun::RunType      m_run_type = ON_TextRun::RunType::kNone;
  ON_TextRun::RunDirection m_direction = ON_TextRun::RunDirection::kLtR;

private:

  // This value of m_managed_status is not copied
  // 0: Not managed
  // 1: Managed by GetManagedTextRun() / ReturnManagedTextRun()
  const unsigned char m_managed_status = 0; 
  unsigned char m_active_status = 0; // 0: active, 1: inactive managed text_run

private:
  double               m_run_text_height = 1.0;             // (ECS) text height in model units or page units

public:
  ON_2dVector          m_offset = ON_2dVector::ZeroVector;  // (ECS) offset to lower left of bounding box from ON_TextContent plane origin

  ON_2dVector          m_advance = ON_2dVector::ZeroVector; // (ECS) distance and direction from m_offset to start of next run

private:
  ON_BoundingBox       m_bbox = ON_BoundingBox::EmptyBoundingBox; // (ECS) 3d Bounding box oriented to ON_TextContent object's plane (z == 0) with run offset already included

public:
  double               m_height_scale = -1.0;      // Font HeightOfI / text height - Converts from font units to model units or page units
  double               m_stackscale = 0.7;         // fraction for scaling textheight in stacked text

  // indent and margins are in model units or page units
                                                   // These apply to Paragraph type runs (m_type == rtParagraph)
  double               m_indent = 0.0;             // First line indentation for this paragraph
  double               m_left_margin = 0.0;        // left margin in formatting rect for this paragraph
  double               m_right_margin = 0.0;       // right margin in formatting rect for this paragraph

  int                  m_line_index = -1;          // line position in ON_TextContent

private:
  ON__UINT_PTR m_reserved=0;

private:
  friend class ON_StackedText;
  //bool WriteNested(
  //  unsigned int nested_depth,
  //  ON_BinaryArchive& archive
  //  ) const;
  //bool ReadNested(
  //  unsigned int nested_depth,
  //  ON_BinaryArchive& archive
  //  );
private:
  void Internal_Destroy();
  void Internal_CopyFrom(const ON_TextRun& src);
};


class ON_CLASS ON_TextRunArray : private ON_SimpleArray< ON_TextRun* >
{
  //ON_TextRun*& AppendNew();
  //void Append(int, ON_TextRun* const *);
  //void Append(ON_TextRun* const);

public:
  static const ON_TextRunArray EmptyArray;

  ON_TextRunArray() = default;

  // Calls Destroy(true,true)
  ~ON_TextRunArray();

  // Duplicate runs are managed text runs
  ON_TextRunArray& operator=(const ON_TextRunArray& src);

  // Duplicate runs are managed text runs
  ON_TextRunArray(const ON_TextRunArray& src);

public:

  /*
  Returns:
    A hash of the information that determines the text content with evaluated fields.
  */
  ON_SHA1_Hash TextRunArrayContentHash() const;

  /*
  Parameters:
    bEvaluateFields - [in]
      true - hash text with fields evaluated
      false - hash text with fields unevaluated
  Returns:
    A hash of the information that determines the text content
    without evaluating the fields.
  */
  ON_SHA1_Hash TextRunArrayContentHash(
    bool bEvaluateFields
  ) const;

  // Run must be a managed run or on the heap.
  // The destructor will return managed runs and delete unmanaged runs.
  void InsertRun(int i, ON_TextRun*& run);

  void RemoveRun(int i);

  // Run must be a managed run or on the heap.
  // The destructor will return managed runs and delete unmanaged runs.
  void AppendRun(ON_TextRun*& run);

  bool Get2dCorners(ON_2dPoint corners[4]) const;

  const ON_TextRun* operator[](int i) const;
  ON_TextRun* operator[](int i);
  int Count() const;
  unsigned int UnsignedCount() const;
  ON_TextRun*const* Array() const;

  /*
  Parameters:
    bReturnManagedRuns - [in]
      True: Managed runs will be returned.
      False: Caller must explicitly handle managed runs.
    bDeleteUnmanagedRuns - [in]
      True: Unmanaged runs are deleted.
      False: Caller must explicitly handle unmanaged runs.
  */
  void SetTextHeight(double height);

private:
  void Internal_Destroy();
  void Internal_CopyFrom(const ON_TextRunArray& src);
};


#endif
