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


#if !defined(OPENNURBS_FONT_INC_)
#define OPENNURBS_FONT_INC_


/// <summary>
/// https://monotype.github.io/panose/pan1.htm
/// </summary>  
class ON_CLASS  ON_PANOSE1
{
public:
  ON_PANOSE1() = default;
  ~ON_PANOSE1() = default;
  ON_PANOSE1(const ON_PANOSE1&) = default;
  ON_PANOSE1& operator=(const ON_PANOSE1&) = default;

  /// <summary>
  /// PANOSE 1.0 font family kind
  ///
  /// The overall genre of the alphabet or script that is being described 
  /// is signified by the Family Kind digit. This digit consists of two parts: 
  /// the script kind identifier and the genre kind identifier. 
  /// In this case, the script identifier is Latin, and the genre type is described as Text, 
  /// Hand Written, Decorative or Symbol.
  
  /// The Family Kind digit is not controlled by specific measurements, 
  /// and there has been no attempt to mathematically determine the 
  /// appropriate category for a given font design. Visual and aesthetic 
  /// classification of Latin faces that are obviously script, decorative,
  /// or symbol fonts is required.
  /// </summary>  
  enum class FamilyKind : ON__UINT8
  {
    /// <summary>"Any" means match that digit with any available digit, which allows the mapper to handle distortable typefaces. </summary>
    Any = 0,

    /// <summary>"No Fit" means that the item being classified does not fit within the PANOSE 1.0 classification system. </summary>
    NoFit = 1,

    /// <summary>
    /// To decide whether a font belongs to the Latin Text group follow the two step process below.
    ///
    /// A. Answer the following three questions. If they are all yes, then it belongs in this group.
    /// If the answer is still ambiguous, go to step B.
    ///
    ///   Does the font belong to a family that includes italic versions? 
    ///   Most fonts in this group have a variety of weights and most include italic versions.
    ///
    ///   Are the characters in the font made up of standard topologies constructed of standard parts?
    ///
    ///  Is some portion of the font suitable for composing a paragraph of text?
    ///
    /// B. As a final tie breaker, look at the second digit of the Decorative (Section 4) 
    //     and Handwritten (Section 3) families and see if there is something in them that 
    ///    fits the font in question better.
    /// https://monotype.github.io/panose/pan2.htm
    /// </summary>
    LatinText = 2,

    /// <summary>
    /// Many fonts are clearly scripts and unrelated to any book face. On occasion, 
    /// though, the distinction gets rather vague. A good rule of thumb is that if 
    /// the cursive font is part a family that includes a book face, then it should 
    /// be classified in the Latin Text group. If it is freestanding with no obvious 
    /// related book face, then it falls into the Latin Hand Written group. This can 
    /// be a bit difficult to determine, since a font house may only choose to provide
    /// the cursive from a larger family, so the classifier needs to think about the 
    /// face being processed and not do it purely by rote. 
    /// https://monotype.github.io/panose/pan3.htm
    /// </summary>
    LatinScript = 3,

    /// <summary>
    /// Latin Decorative faces are those that are designed more for impact than readability. 
    /// Usually Decoratives are used singly or in small groups, for special purposes. 
    /// Small cap fonts are also included in this group because they have become unusual 
    /// enough to be considered special purpose fonts.
    /// https://monotype.github.io/panose/pan4.htm
    /// </summary>
    LatinDecorative = 4,

    /// <summary>
    /// Latin Symbol is where all the nonalphabetic fonts reside. These are fonts that can be loaded
    /// like normal text fonts, but do not contain readable characters. Dingbats and specialized 
    /// symbol fonts are two examples.
    /// https://monotype.github.io/panose/pan5.htm
    /// </summary>
    LatinSymbol = 5
  };

  /*
Special values "Any" (0) and "No Fit" (1) exist for every category, which have specific meanings to the mapper.  
*/

  /*
  Description:
    In the rare cases when an ON_PANOSE1::Classification value must be passed
    as an unsigned int, use ON_PANOSE1::ClassificationFromUnsigned() to
    convert the unsigned value to an ON_PANOSE1::Classification value.
  Parameters:
    unsigned_panose_family_kind - [in]
  */
  static ON_PANOSE1::FamilyKind FamilyKindFromUnsigned(
    unsigned int unsigned_panose_family_kind
    );

  static const wchar_t* FamilyKindToWideString(
    ON_PANOSE1::FamilyKind family_kind
  );

  static const ON_PANOSE1 Zero; // All PANOSE 1.0 values are zero, which means (Any,Any,...,Any)

  /*
  Returns:
    True if every PANOSE 1.0 value is zero which means there is no useful
    font classification information in the instance.
  */
  bool IsZero() const;

  /*
  Returns:
    True if every PANOSE 1.0 value is zero or one which means there is no useful
    font classification information in the instance.
  */
  bool IsZeroOrOne() const;

  /*
  Returns:
    True if some PANOSE 1.0 value is not zero and not one.  This means this 
    PANOSE 1.0 information may be useful in searching for similar fonts.
  */
  bool IsSet() const;

  ON_PANOSE1::FamilyKind PANOSE1FamilyKind() const;

  /*
  Returns:
    A pointer to an array of 10 bytes of PANOSE 1 classification properties.
    The initial byte is the PANOSE 1 Classification and is identical
    to the value returned by FontClassification().
    The interpretation of the following 9 bytes depends on the
    value of the first byte. If the initial byte is 
    0 = ON_FontPANOSE1::Classification::Any (0) 
    or 1 = ON_FontPANOSE1::Classification::NoFit,
    then these 9 bytes have no meaning.    
  */
  const ON__UINT8* TenBytes() const;

  /*
  Parameters:
    classification - [in]
      PANOSE 1.0 font classification
    panose1_properties_bytes - [in]
      Array of 9 bytes of PANOSE1 properties
  */
  void SetTenBytes(const ON__UINT8* panose1_ten_bytes);

  /*
  Parameters:
    family_kind - [in]
      PANOSE 1.0 font Family kind classification
    panose1_properties_bytes - [in]
      Array of 9 bytes of PANOSE1 properties
  */
  void SetNineBytes(
    ON_PANOSE1::FamilyKind family_kind,
    const ON__UINT8* panose1_properties_bytes
  );

  void Dump(
    class ON_TextLog& text_log
  ) const;

  bool Write(
    class ON_BinaryArchive& archive
  ) const;

  bool Read(
    class ON_BinaryArchive& archive
  );

private:
  // PANOSE 1.0 properties (10 bytes)
  //  // text / script / decrorative / symbol
  ON_PANOSE1::FamilyKind m_family_kind = ON_PANOSE1::FamilyKind::Any;

  // The interpretation of the m_prop* values depends on the value of m_family_kind.
  //
  // For every classification property,
  // 0 =  "Any" and means match that digit with any available digit, which allows the mapper to handle distortable typefaces.
  // 1 = "No Fit" means that the item being classified does not fit within the PANOSE 1.0 classification system.
  // Additional values need to be 
  
  // Classification       // Latin text       / Latin script    / Latin decrorative   / Latin symbol
  ON__UINT8 m_prop1 = 0;  // serif style      / tool kind       / decorative class    / symbol kind
  ON__UINT8 m_prop2 = 0;  // weight           / weight          / weight              / weight
  ON__UINT8 m_prop3 = 0;  // proportion       / spacing         / aspect              / spacing
  ON__UINT8 m_prop4 = 0;  // contrast         / aspect ratio    / contrast            / aspect ration and contrast
  ON__UINT8 m_prop5 = 0;  // stroke variation / contrast        / serif variant       / aspect ratio 94
  ON__UINT8 m_prop6 = 0;  // arm style        / script topology / fill                / aspect ratio 119
  ON__UINT8 m_prop7 = 0;  // letter form      / script form     / lining              / aspect ratio 157
  ON__UINT8 m_prop8 = 0;  // midline          / finials         / decorative topology / aspect ratio 163
  ON__UINT8 m_prop9 = 0;  // x-height         / x-ascent        / character range     / aspect ratio 211
};

class ON_CLASS ON_FontMetrics
{
public:
  ON_FontMetrics() = default;
  ~ON_FontMetrics() = default;
  ON_FontMetrics(const ON_FontMetrics&) = default;
  ON_FontMetrics& operator=(const ON_FontMetrics&) = default;


public:
  // All properties are zero.
  static const ON_FontMetrics Unset;


  // Used when it is impossible to find normalized font metrics (missing font for example)
  // and something valid is required for a computation.
  static const ON_FontMetrics LastResortNormalizedMetrics;

  // Used when it is impossible to find font metrics (missing font for example)
  // and something valid is required for a computation.
  // Currently LastResortMetrics.UPM() is 2048 and this value is chosen because
  // it is the largest common UPM found in real fonts encountered in March 2018.
  static const ON_FontMetrics LastResortMetrics;


  /*
    ON_FontMetric::DefaultLineFeedRatio*ON_FontMetrics().AscentOfCapital()
    can be used to cook up a line space value when using the 
    ON_FontMetrics.LineSpace() value defined by the font is
    not desired.
  */
  static const double DefaultLineFeedRatio; // 1.6

  // UNICODE code point of the glyph used to determine HeightOfCapital()
  // when no reaonable value is available from the font definition.
  // Currently this is the 'I' glyph. Opennurbs has used 'I' since 2005.
  // It is possible 'H' would work as well. All other glyphs, in 
  // particular 'M' and 'W', do not work.
  static const ON__UINT32 HeightOfCapitalCodePoint; // 'I'

public:
  /*
  Returns:
    Signed distance from the baseline to highest point on a glyph outline.

  Remarks:
    If every glyph outline in the font has (0,0) on the baseline, then Ascent() 
    is the maximum glyph bounding box Y.

    Ascent typically includes internal leading, the space used for 
    diacritcial marks above capital latin letters. For this reason,
    Ascent is typically greater than AscentOfCapital.

    Windows: = DWRITE_FONT_METRICS.ascent
  */
  int Ascent() const;

  /*
  Returns:
    Signed distance from the English baseline to lowest point on a glyph outline.

  Remarks:
    This value is typically negative because glyphs for letters like 'g' and 'j'
    typically have a portion of their outline below the baseline.  However,
    some fonts have positive descent.
    If every glyph outline in the font has (0,0) on the baseline, then Descent() 
    is the minimum glyph bounding box Y.

    Windows: = -DWRITE_FONT_METRICS.descent
  */
  int Descent() const;

  /*
  Returns:
    The positive distance to move the base line when moving to a new line of text.

  Remarks:
    For almost every font used to render English text, LineSpace() > (Ascent() - Descent()).

    This metric is sometimes called "height", but that term is often confused
    with (Ascent() - Descent()). 

    For fonts designed to render horizontal lines of text, LineSpace() is a 
    vertical distance. For fonts designed to render vertical lines of text,
    LineSpace() is a horizontal distance.  Depending on the context, the 
    direction to move can be up, down, left or right.

    Windows: = DWRITE_FONT_METRICS.ascent
             + DWRITE_FONT_METRICS.descent
             + DWRITE_FONT_METRICS.lineGap;
  */
  int LineSpace() const;

  /*
  Returns:
    The "units per EM". This is the height and width of the square grid 
    where the font glyphs are designed.  
  Remarks:
    The width of the 'M' glyph in a font can be  different from UPM.
    The height of the 'M' glyph in a font is typically less than UPM.
    In TrueType fonts, UPM is often a power of two and generally 1024 or 2048.
    In OpenType fonts, UPM is often 1000.
    In PostScript fonts, UPM is often 1000.

    Windows: = DWRITE_FONT_METRICS.designUnitsPerEm
  */
  int UPM() const;

  /*
  Returns:
    AscentOfCapital()
  */
  int AscentOfI() const;

  /*
  Returns:
    The font's typographic capital height.

  Remarks:
    The primary uses of AscentOfCapital() are:
    1) 
    Calculate a scale factor to produce text with a user specified "text height".
    2) 
    To calculate insertion location for ON::TextVerticalAlignment::Middle
    and ON::TextVerticalAlignment::Top.

    From 2005-2018 opennurbs used the ascent of a capital I. 
    Beginning in 2018 this value is taken from the system font metrics
    so that fonts designed to render Asian language text, symbols, 
    and emojis will display as expected and lines of text containing 
    multiple fonts will render more clearly.

    The value (user specified text height)/AscentOfCapital() is used
    as the scale factor to render glyphs when user interface has provided 
    a "text height" value. 

    If the capial height property of a font is not
    available, the ascent of I or H can be used instead. (There are
    commonly used fonts where using other glyphs gives undesirable results.)OfI.

    Windows: = DWRITE_FONT_METRICS.capHeight
    Apple: = CTFontGetAscent(...)
  */
  int AscentOfCapital() const;
  

  /*
  Returns:
    The font's typographic x-height.

  Remarks:
    The x-height is used to help select a substitute font to use for missing glyphs.
  */
  int AscentOfx() const;


  /*
  Description:
  Parameters:
    height_of_capital - [in]
      The desired height of typical capital latin letter glyphs.
      For fonts like Arial, Helvetica, and Times Roman the 
      heights of the H and I glyphs = font's height of capital.
  Returns:
    text_height / AscentOfCapital().
  */
  double GlyphScale(double text_height) const;
  
  /*
  Returns:
    Thickness of strikeout.
  Remarks:
    The signed distance from the baseline to the bottom of the strikeout 
    is StrikeoutPosition() - StrikeoutThickness()/2.
  */
  int StrikeoutThickness() const;

  /*
  Returns:
    Signed distance from baseline to center of strikeout. 
    A positive value indicates the strikeout is above the baseline (common).
  Remarks:
    The signed distance from the baseline to the bottom of the strikeout 
    is StrikeoutPosition() - StrikeoutThickness()/2.
  */
  int StrikeoutPosition() const;


  /*
  Returns:
    Thickness of underscore
  Remarks:
    The signed distance from the baseline to the bottom of the underscore
    is UnderscorePosition() - UnderscoreThickness()/2.
  */
  int UnderscoreThickness() const;
  
  /*
  Returns:
    Signed distance from baseline to center of underscore.
    A negative value indicates the underscore is below the baseline (common).
  Remarks:
    The signed distance from the baseline to the bottom of the underscore
    is UnderscorePosition() - UnderscoreThickness()/2.
  */
  int UnderscorePosition() const; 

  static const ON_FontMetrics Scale(
    const ON_FontMetrics& font_metrics,
    double scale
  );

  static const ON_FontMetrics Normalize(
    const ON_FontMetrics& font_metrics
  );

  void SetHeights(
    int ascent,
    int descent,
    int UPM,
    int line_space
  );

  void SetAscentOfI(
    int ascent_of_capital
  );

  void SetAscentOfCapital(
    int ascent_of_capital
  );

  void SetAscentOfx(
    int ascent_of_x
  );

  void SetStrikeout(
    int strikeout_position,
    int strikeout_thickness
  );
  
  void SetUnderscore(
    int underscore_position,
    int underscore_thickness
  );

  void SetHeights(
    double ascent,
    double descent,
    double UPM,
    double line_space
  );

  void SetAscentOfCapital(
    double ascent_of_capital
  );

  void SetAscentOfx(
    double ascent_of_x
  );

  void SetStrikeout(
    double strikeout_position,
    double strikeout_thickness
  );
  
  void SetUnderscore(
    double underscore_position,
    double underscore_thickness
  );

  /*
  Returns:
    True if all of the following are true.
    UPM() > 0
    At least one of Ascent() or Descent() is not zero.
    Ascent() > Descent()
    None of UPM(), Ascent(), or Descent() is ON_UNSET_INT_INDEX or -ON_UNSET_INT_INDEX.
  */
  bool AscentDescentAndUPMAreValid() const;

  /*
  Returns:
    True if all of the following are true.
    AscentDescentAndUPMAreValid() is true
    LineSpace() >= Ascent() - Descent()
    AscentOfCapital() <= Ascent()
    AscentOfx() <= Ascent()
  */
  bool HeightsAreValid() const;

  /*
  Returns:
    True if all of the following are true.
    HeightsAreValid() is true.
    AscentOfCapital() > 0
  */
  bool IsSetAndValid() const;

  /*
  Returns true if at least one metric is not zero.
  */
  bool IsSet() const;

  /*
  Returns true if all metrics are zero
  */
  bool IsUnset() const;

  void Dump(class ON_TextLog& text_log) const;

#if defined(ON_OS_WINDOWS_GDI)
  static const ON_FontMetrics CreateFromDWriteFontMetrics(const struct DWRITE_FONT_METRICS* dwrite_font_metrics);
  static const ON_FontMetrics CreateFromDWriteFont(struct IDWriteFont* dwrite_font);
#endif
 
private:
  int m_UPM = 0;           // units per EM
  int m_ascent = 0;        // max over all glyphs in font of (highest outline point - baseline point).y
  int m_descent = 0;       // min over all glyphs in font of (lowest outline point - baseline point).y
  int m_line_space = 0;    // distance between baselines 
  ON__UINT16 m_ascent_of_capital = 0;
  ON__UINT16 m_ascent_of_x = 0; // same units as m_ascent_of_capital

  int m_strikeout_thickness = 0;      //
  int m_strikeout_position = 0;  // 

  int m_underscore_thickness = 0;     //
  int m_underscore_position = 0; //

private:
  int m_reserved1 = 0;
  double m_reserved2 = 0.0;
  double m_reserved3 = 0.0;
  ON__UINT_PTR m_reserved_ptr = 0;
};

class ON_CLASS ON_TextBox
{
public:
  ON_TextBox() = default;
  ~ON_TextBox() = default;
  ON_TextBox(const ON_TextBox&) = default;
  ON_TextBox& operator=(const ON_TextBox&) = default;

  ON_TextBox(
    ON_2dPoint bbmin,
    ON_2dPoint bbmax
  );

#if defined(ON_OS_WINDOWS_GDI)
  static const ON_TextBox CreateFromDWriteGlyphMetrics(const struct DWRITE_GLYPH_METRICS* dwrite_glyph_metrics);
#endif

  /*
  Returns:
    true if bounding box is set.
  */
  bool IsSet() const;

  static const ON_TextBox Scale(
    const ON_TextBox& text_box,
    double scale
  );

  /*
  Returns:
    A text box with m_bbmin, m_bbmax, m_max_basepoint are translated by delta.
    m_advance is not changed.
  */
  static const ON_TextBox Translate(
    const ON_TextBox& text_box,
    const ON_2dVector& delta
  );

  static const ON_TextBox Translate(
    const ON_TextBox& text_box,
    const ON_2dex& delta
  );

  /*
  Parameters:
    lhs - [in]
      lhs.m_advance is ignored
    rhs - [in]
      rhs.m_advance is ignored
  Returns:
    Returned m_bbmin, m_bbmax, m_max_basepoint are the union of the lhs and rhs bounding box.
    Returned m_advance = (0,0)
  */
  static const ON_TextBox Union(
    const ON_TextBox& lhs,
    const ON_TextBox& rhs
  );

  void Dump(class ON_TextLog& text_log) const;

public:
  static const ON_TextBox Unset;

public:
  // The use context determines the length units. Common units include font glyph design units,
  // normalized font design units, various display units.  Typically x increases to the right,
  // y increases upwards. For glyph and text run boxes, (0,0) is the horizontal base
  //
  ON_2dex m_bbmin = ON_2dex::Unset;
  ON_2dex m_bbmax = ON_2dex::Unset;

  // m_max_basepoint.i = maximum horizontal delta in any line. Increases to the right, decreases to the left.
  // m_max_basepoint.i = vertical delta to baseline of bottom line. Increases upward, decreases downward.
  ON_2dex m_max_basepoint = ON_2dex::Zero;

  // m_advance is a vector that specifies where the basepoint should be moved
  // to after the text is rendered. m_advance.i and m_advance.j are always >= 0.  
  // When glyphs are rendered right to left (Arabic and Hebrew being examples)
  // or bottom to top, the rendering code must apply the correct sign. Some
  // reasons for using positive advance values for every glyph is that left to right 
  // and right to left languages can be appear on a single line and the sign of y 
  // associated with "up" is sometimes positive and sometimes negative.
  // ON_TextBox::Translate does not modify the vector m_advance. 
  // ON_TextBox::Union ignored input advance values and returns a box with advance = (0,0).
  // 0 <= m_advance.i will be <= m_max_basepoint.i.
  ON_2dex m_advance  = ON_2dex::Zero;


  // NOTE: 
  //  When the SDK can be broken, this class needs another int = verticalOriginY.
  //  verticalOriginY is required when placing glyphs vertically.
};

class ON_CLASS ON_OutlineFigurePoint
{
public:
  ON_OutlineFigurePoint() = default;
  ~ON_OutlineFigurePoint() = default;
  ON_OutlineFigurePoint(const ON_OutlineFigurePoint&) = default;
  ON_OutlineFigurePoint& operator= (const ON_OutlineFigurePoint&) = default;

public:
  enum class Type : ON__UINT8
  {
    Unset = 0,

    //////////////////////////////////////////////////////////////////
    //
    // Beginning of a figure
    //
    // The open/closed state is unknown.
    BeginFigureUnknown = 1,

    // Marks the beginning of an open figure. (single stroke font, ...)
    BeginFigureOpen = 2,

    // Marks the beginning of a closed figure.
    BeginFigureClosed = 3,


    //////////////////////////////////////////////////////////////////
    //
    // Interior of a figure
    //

    // interior line segment point
    LineTo = 6,

    // interior quadratic bezier (degree=2, order=3) control point.
    QuadraticBezierPoint = 7,

    // interior cubic bezier (degree=3, order=4) control point.
    CubicBezierPoint = 8,

    //////////////////////////////////////////////////////////////////
    //
    // End of a figure
    //

    // End of an open figure (single stroke font, ...)
    EndFigureOpen = 11,

    // End of a closed figure.
    EndFigureClosed = 12,


    //////////////////////////////////////////////////////////////////
    //

    // Error of some sort.
    Error = 15
  };

  enum class Proximity : ON__UINT8
  {
    Unset = 0,

    // The point is the beginning or end of a line or bezier segment in the figure
    OnFigure = 1,

    // The point is a bezier control point that may be off the figure
    OffFigure = 2,

    Error = 15
  };

  /*
  Returns:
    true if point_type is one of the following:
      ON_OutlineFigurePoint::Type::BeginFigureUnknown
      ON_OutlineFigurePoint::Type::BeginFigureFilled
      ON_OutlineFigurePoint::Type::BeginFigureHollow
      ON_OutlineFigurePoint::Type::BeginFigureOpen
  */
  static bool IsBeginFigurePointType(
    ON_OutlineFigurePoint::Type point_type
  );

  /*
  Returns:
    true if point_type is one of the following:
      ON_OutlineFigurePoint::Type::MoveTo
      ON_OutlineFigurePoint::Type::LineTo
      ON_OutlineFigurePoint::Type::QuadraticBezierPoint
      ON_OutlineFigurePoint::Type::CubicBezierPoint
  */
  static bool IsInteriorFigurePointType(
    ON_OutlineFigurePoint::Type point_type
  );

  /*
  Returns:
    true if point_type is one of the following:
      ON_OutlineFigurePoint::Type::LineToCloseContour
      ON_OutlineFigurePoint::Type::EndFigureUnknown
      ON_OutlineFigurePoint::Type::EndFigureClosed
      ON_OutlineFigurePoint::Type::EndFigureOpen
  */
  static bool IsEndFigurePointType(
    ON_OutlineFigurePoint::Type point_type
  );

  static ON_OutlineFigurePoint::Type ContourPointTypeFromUnsigned(unsigned contour_point_type_as_unsigned);

  static const ON_OutlineFigurePoint Unset;
  static const ON_OutlineFigurePoint Error;


  /*
  Returns:
    true if point_type is one of the following:
      ON_OutlineFigurePoint::Type::BeginFigureUnknown
      ON_OutlineFigurePoint::Type::BeginFigureFilled
      ON_OutlineFigurePoint::Type::BeginFigureHollow
      ON_OutlineFigurePoint::Type::BeginFigureOpen
  */
  bool IsBeginFigurePoint() const;

  /*
  Returns:
    true if point_type is one of the following:
      ON_OutlineFigurePoint::Type::MoveTo
      ON_OutlineFigurePoint::Type::LineTo
      ON_OutlineFigurePoint::Type::QuadraticBezierPoint
      ON_OutlineFigurePoint::Type::CubicBezierPoint
  */
  bool IsInteriorFigurePoint() const;

  /*
  Returns:
    true if point_type is one of the following:
      ON_OutlineFigurePoint::Type::LineToCloseContour
      ON_OutlineFigurePoint::Type::EndFigureUnknown
      ON_OutlineFigurePoint::Type::EndFigureClosed
      ON_OutlineFigurePoint::Type::EndFigureOpen
  */
  bool IsEndFigurePoint() const;


  ON_OutlineFigurePoint::Type PointType() const;

  ON_OutlineFigurePoint::Proximity PointProximity() const;

  /*
  Returns:
    True if the point is on at the start or end of a line or bezier segment.
    False otherwise (the point is in interior control point in bezier segment or unset).
  */
  bool IsOnFigure() const;

  /*
  Returns:
    True if the point is in interior control point in bezier segment.
    False otherwise (the point is on at the start or end of a line or bezier segment or unset).
  */
  bool IsOffFigure() const;

  ON__UINT16 FigureIndex() const;

  const ON_2fPoint Point() const;
  const ON_2dPoint Point2d() const;

  /*
  Returns:
    Point rounded to nearest integer coordinates.
  */
  const ON_2iPoint Point2i() const;

  /*
  Returns:
    Point rounded up (ceil) to integer coordinates.
  */
  const ON_2iPoint Point2iCeil() const;

  /*
  Returns:
    Point rounded down (floor) to integer coordinates.
  */
  const ON_2iPoint Point2iFloor() const;

public:
  ON_OutlineFigurePoint::Type m_point_type = ON_OutlineFigurePoint::Type::Unset; 

  ON_OutlineFigurePoint::Proximity m_point_proximity = ON_OutlineFigurePoint::Proximity::Unset;

  // 0 = unset. The first figure in an outline has m_figure_index = 1.
  ON__UINT16 m_figure_index = 0; 

  // point location
  ON_2fPoint m_point = ON_2fPoint::NanPoint;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_OutlineFigurePoint>;
#endif

class ON_CLASS ON_OutlineFigure
{
public:
  ON_OutlineFigure() = default;
  ~ON_OutlineFigure() = default;
  ON_OutlineFigure(const ON_OutlineFigure&) = default;
  ON_OutlineFigure& operator=(const ON_OutlineFigure&) = default;

public:
  static const ON_OutlineFigure Unset;

public:

  enum class Orientation : ON__UINT8
  {
    Unset = 0,

    CounterClockwise = 1,

    Clockwise = 2,

    NotOriented = 3,

    // An error occurred in orientation calculations
    Error = 15
  };

  static const wchar_t* OrientationToWideString(
    ON_OutlineFigure::Orientation orientation
  );

  /// <summary>
  /// ON_OutlineFigure::Type identifies the structure of the figure.
  /// </summary>
  enum class Type : ON__UINT8
  {
    ///<summary>
    /// This value should be used for parameters where the type is has not
    /// been explicitly to determined.
    ///</summary>
    Unset = 0,

    ///<summary>
    /// Unknown indicates an attempt was made to determine the type,
    /// that attempt failed, and further attempts will just waste time.
    /// It is best to pass Unset when calling functions and you have 
    /// not calculated the type.
    ///</summary>
    Unknown = 1,

    ///<summary>
    /// Single stroke figures can be open or closed and are not designed to be filled.
    /// Single stroke fonts like RhSS and MecSoft have these types of figures.
    ///</summary>
    SingleStroke = 2,

    ///<summary>
    /// Double stroke figures are closed and contain no area. 
    /// They consist of a single stroke path follow by the reverse of the single stroke path.
    /// The CamBam Stick fonts have these types of figures. A double stroke figure can
    /// be converted to a single stroke figure by removing the reversed overlapping portion.
    ///</summary>
    DoubleStroke = 3,

    ///<summary>
    /// The outline figures are perimeters around non-empty areas that are typically
    /// filled or hollow depending on their orientation.
    /// The majority of TrueType, OpenType, and PostScript fonts have these types of figures.
    ///</summary>
    Perimeter = 4,

    ///<summary>
    /// The outline figure is not a perimeter around a non-empty area.
    ///</summary>
    NotPerimeter = 5,

    ///<summary>
    /// Used in a context where there are multiple figures with different types.
    ///</summary>
    Mixed = 7,
  };

  /*
  Returns:
    If the figure type is known for certain, that type is returned.
    Otherwise ON_OutlineFigure::Type::Unknown is returned.
  */
  static ON_OutlineFigure::Type FigureTypeFromFontName(
    const wchar_t* font_name
  );

  /*
  Description:
    Opennurbs searches the description saved in field 10 of the name table
    for the strings "Engraving - single stroke" / "Engraving - double stroke" / "Engraving"
    to identify fonts that are designed for engraving (and which tend to render poorly when
    used to display text devices like screens, monitors, and printers).
    The SLF (single line fonts) are examples of fonts that have Engraving in field 10.
  Parameters:
    field_10_description - [in]
      Field 10 string from the font name table.
  Returns:
    If the description contains "single stroke", returns ON_OutlineFigure::Type::SingleStroke.
    If the description contains "double stroke", returns ON_OutlineFigure::Type::DoubleStroke.
    Otherwise returns ON_OutlineFigure::Type::Unset;
  */
  static ON_OutlineFigure::Type FigureTypeFromField10Description(
    const ON_wString field_10_description
  );


  /*
  Returns:
    Figure orientation.
  */
  ON_OutlineFigure::Orientation FigureOrientation() const;

  /*
  Returns:
    Figure type.
  */
  ON_OutlineFigure::Type FigureType() const;

  /*
  Returns:
    Signed area estimate. For simple closed curves, a positive area indicates a counter-clockwise orientation.
  */
  double AreaEstimate() const;


  /*
  Returns:
    Bounding box area >= 0
  */
  double BoxArea() const;

  /*
  Description:
    Determines if this ON_OutlineFigure is inside of outer_figure.
  Parameters:
    outer_figure - [in]
      When bPerformExtraChecking is false, outer_figure->FigureOrientation() should 
      be set to what you plan on using when rendering the glyph.
      The orientation of outer_figure can be either clockwise or counterclockwise
      and, in the context of the entire glyph, outer_figure can be an inner or outer boundary.
      For example, the registered trademark glyph (UNICODE U+00AE) is an example where 
      four nested figures with alternating orientations are common.
    bPerformExtraChecking - [in]
      In general, when sorting glyph outlines as they come froma font file, set
      outer_figure->FigureOrientation() to what will be used to render the glyph
      and pass false for bPerformExtraChecking.
      Details: In the case when bounding boxes and estimated areas and spot checks of winding numbers
      all indicate that this is inside of other_f, an additional time consuming intersection
      check is performed when this->FigureOrientation() == other_f->FigureOrientation().
      When this->FigureOrientation() and other_f->FigureOrientation() are opposited,
      the additional intersection check is skipped unless bPerformExtraChecking is true.
  Returns:
    True if it is very likely that this is not empty and is inside of other_f.
    False otherwise
  Remarks:
  */
  bool IsInsideOf(
    const ON_OutlineFigure* outer_figure,
    bool bPerformExtraChecking
  ) const;

  /*
  Description:
    Get up to four distinct points on the figure.
    These are useful for winding number tests when sorting figures.
  Parameters:
    p - [out]
      the returned points will be on the figure (not bezier interior control points).
  Returns:
    Number of points.
  */
  unsigned GetUpToFourPointsOnFigure(
    ON_2fPoint p[4]
  ) const;

  ON__UINT32 UnitsPerEM() const;

  ON__UINT16 FigureIndex() const;

  unsigned int GetFigureCurves(
    double scale,
    bool b3d,
    ON_SimpleArray< ON_Curve* >& figure_curves
    ) const;

  unsigned int GetFigureCurves(
    double scale,
    bool b3d,
    ON_SimpleArray< ON_NurbsCurve* >& figure_curves
    ) const;

  bool IsValidFigure(
    bool bLogErrors
  ) const;
  
  const ON_BoundingBox BoundingBox() const;

  bool ReverseFigure();

  bool NegateY();
  
  /*
  Description:
    Get a polyline approximation of the figure.

  Parameters:
    tolerance - [in]
      If tolerance > 0, that value is used.
      Otherwise UnitsPerEM() / 256.0 is used, which gives course but 
      recognizable decent results for glyph outlines.

    PointCallbackFunc - [in]
      called once for each point in the polyline
    context - [in]
      third parameter to PointCallbackFunc()
  Returns:
    Number of points passed to PointCallbackFunc()
  */
  unsigned int GetPolyline(
    double tolerance,
    void(*PointCallbackFunc)(float x, float y, void*),
    void* context
  ) const;

  double DefaultPolylineTolerance() const;

  static double DefaultPolylineTolerance(
    double units_per_em
    );

  int WindingNumber(
    ON_2fPoint winding_point
  ) const;

  /*
  Description:
    Get a polyline approximation of the figure.
  Parameters:
    tolerance - [in]
      If tolerance > 0, that value is used.
      Otherwise UnitsPerEM() / 256.0 is used, which gives course but 
      recognizable decent results for glyph outlines.
    points - [out]
      polyline points are appended to this array.
  Returns:
    Number of points appended to oiunts[]
  */
  unsigned int GetPolyline(
    double tolerance,
    ON_SimpleArray<ON_2dPoint>& points
  ) const;

  /*
  Description:
    Get a polyline approximation of the figure.
  Parameters:
    tolerance - [in]
      If tolerance > 0, that value is used.
      Otherwise UnitsPerEM() / 256.0 is used, which gives course but 
      recognizable decent results for glyph outlines.
    points - [out]
      polyline points are appended to this array.
  Returns:
    Number of points appended to oiunts[]
  */
  unsigned int GetPolyline(
    double tolerance,
    ON_SimpleArray<ON_2fPoint>& points
  ) const;

  /*
  Description:
    Get a polyline approximation of the figure.
  Parameters:
    tolerance - [in]
      If tolerance > 0, that value is used.
      Otherwise UnitsPerEM() / 256.0 is used, which gives course but 
      recognizable decent results for glyph outlines.
    points - [out]
      polyline points are appended to this array.
  Returns:
    Number of points appended to oiunts[]
  */
  unsigned int GetPolyline(
    double tolerance,
    ON_SimpleArray<ON_3dPoint>& points
  ) const;

  /*
  Description:
    Get a polyline approximation of the figure.
  Parameters:
    tolerance - [in]
      If tolerance > 0, that value is used.
      Otherwise UnitsPerEM() / 256.0 is used, which gives course but 
      recognizable decent results for glyph outlines.
    points - [out]
      polyline points are appended to this array.
  Returns:
    Number of points appended to oiunts[]
  */
  unsigned int GetPolyline(
    double tolerance,
    ON_SimpleArray<ON_3fPoint>& points
  ) const;

private:
  friend class ON_Outline;

private:
  ON__UINT32 m_units_per_em = 0;

private:
  mutable ON_OutlineFigure::Orientation m_orientation = ON_OutlineFigure::Orientation::Unset;
  mutable ON_OutlineFigure::Type m_figure_type = ON_OutlineFigure::Type::Unset;

private:
  mutable ON__UINT8 m_bbox_status = 0; // 0 = unset, 1 = set, 7 = error
  mutable ON__UINT8 m_area_status = 0; // 0 = unset, 1 = set, 7 = error


public:
  ON__UINT16 m_figure_index = 0;

private:
  mutable ON_2fPoint m_bbox_min = ON_2fPoint::NanPoint;
  mutable ON_2fPoint m_bbox_max = ON_2fPoint::NanPoint;

  double m_short_tolerance = 0.0;
  mutable double m_area_estimate = ON_DBL_QNAN;

public:
  ON_SimpleArray<ON_OutlineFigurePoint> m_points;

private:
  ON__UINT32 Internal_FigureEndDex( bool bLogErrors ) const;

  bool Internal_HasValidEnds( bool bLogErrors ) const;
  ON__UINT32 Internal_EstimateFigureSegmentCount() const;

  static bool Internal_NegateY(ON_2fPoint&);


  unsigned int Internal_SegmentDegree(
    ON__UINT32 segment_start_dex
  ) const;

  /*
  Parameters:
    figure_end_dex - [in]
      index of the last point in the figure.
    b3dCurve - [in]
      If true the result is 3d, otherwise it is 2d.
    curve - [in]
      If not nullptr, result is stored here
  Returns:
    nurbs curve
  */
  class ON_NurbsCurve* Internal_GetFigureCurve(
    ON__UINT32 figure_end_dex,
    ON__UINT32 segment_start_dex,
    ON__UINT32* segment_end_dex,
    bool b3d,
    class ON_NurbsCurve* destination_curve
  ) const;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_ClassArray<ON_OutlineFigure>;
#endif

class ON_CLASS ON_Outline
{
public:
  ON_Outline() = default;
  ~ON_Outline() = default;
  ON_Outline(const ON_Outline&) = default;
  ON_Outline& operator=(const ON_Outline&) = default;

public:
  static const ON_Outline Unset;

  /*
  Default value for outer orientation when it is not explicitly specified.
  */
  static const ON_OutlineFigure::Orientation DefaultOuterOrientation;



  ON__UINT32 UnitsPerEM() const;

  void SetUnitsPerEM(
    ON__UINT32 units_per_em
  );

  /*
  Returns:
    Number of figures in the outline.
  */
  unsigned int FigureCount() const;

  /*
  Parameters:
    i - [in]
      0 <= i < count
  */
  const ON_OutlineFigure& Figure(
  int i
  ) const;

  const ON_ClassArray< ON_OutlineFigure >& Figures() const;

  /*
  Returns:
    Number of points in all figures in the outline.
  */
  unsigned int OutlinePointCount() const;

  /*
  Parameters:
    bLogErrors - [in]
      
  Returns:
    True if the outline and all figures are valid.
  */
  bool IsValidOutline(
    bool bLogErrors
  ) const;

  /*
  Description:
    The outline consists of one or more figures. 
    There can be zero or more closed outer figures 
    (single stroke fonts have zero, Arial I has one, Arial i has two). 
    There can be zero or more inner figures 
    (Arial I has zero, O has one, 8 has two).
  Parameters:
    scale - [in]
      If scale > 0.0, then all curves are scaled this factor with (0,0) 
      as the fixed point. Otherwise all curves are returned in font design units.
      ON_Font::ScaleFromTextHeight() is a good tool to get this value.
    b3d - [in]
      If true, then 3d curves in the world xy plane are returned.
      Otherwise 2d curves  are returned.
    figure_curves - [in]
      Results are appended to this array.
  Returns:
    Number of figures appended to outline_curves[]
  */
  unsigned int GetOutlineCurves(
    double scale,
    bool b3d,
    ON_ClassArray< ON_SimpleArray< ON_Curve* > >& outline_curves
    ) const;


  /*
  Returns:
    The bounding box of the outline curves.

  Remarks:
     The glyph metrics bounding box of the metrics can be different from the 
     figure outline bounding box.
     For example, the glyph metrics box for 1 (numeral one) often contains space beyond the
     glyph outline because 1 visually occupies the same space as a 2. The choice is up to the
     font designer and takes into account the desired font aesthetics of columns of numbers.
     */
  const ON_BoundingBox OutlineBoundingBox() const;

  /*
  Returns:
    Glyph metrics.
  Remarks:
     The glyph metrics bounding box of the metrics can be different from the 
     figure outline bounding box.
     For example, the glyph metrics box for 1 (numeral one) often contains space beyond the
     glyph outline because 1 visually occupies the same space as a 2. The choice is up to the
     font designer and takes into account the desired font aesthetics of columns of numbers.
  */
  const ON_TextBox GlyphMetrics() const;

  /*
  Description:
    The signed area estimate calculated as the sum of each figure's area estimate.
  */
  double AreaEstimate() const;
  
  /*
  Description:
    Reverse every figure.
  */
  void Reverse();

  /*
  Description:
    Sort figures so that each outer loop is followed by it's inner loops. 
  */
  void SortFigures(
    ON_OutlineFigure::Orientation outer_loop_orientation
  );

  /*
  Returns:
    ON_OutlineFigure::Orientation::Unset
      Figures are not sorted.
    ON_OutlineFigure::Orientation::CounterClockwise
      Figures are sorted and outer figures are CCW.
    ON_OutlineFigure::Orientation::Clockwise
      Figures are sorted and outer figures are CW.
    ON_OutlineFigure::Orientation::Error
      Figure sorting failed.
  */
  ON_OutlineFigure::Orientation SortedFigureOuterOrientation() const;

  /*
  Returns:
    ON_OutlineFigure::Orientation::Unset
      Figures are not sorted.
    ON_OutlineFigure::Orientation::CounterClockwise
      Figures are sorted and inner figures are CCW.
    ON_OutlineFigure::Orientation::Clockwise
      Figures are sorted and inner figures are CW.
    ON_OutlineFigure::Orientation::Error
      Figure sorting failed.
  */
  ON_OutlineFigure::Orientation SortedFigureInnerOrientation() const;

  /*
  Returns:
    Type of figures in the outline.
  */
  ON_OutlineFigure::Type FigureType() const;

public:
  ON__UINT16 AppendFigure(
    const ON_SimpleArray<ON_OutlineFigurePoint>& points
  );

  ON__UINT16 AppendFigure(
    size_t point_count,
    const ON_OutlineFigurePoint* points
  );

  void SetGlyphMetrics(
    ON_TextBox glyph_metrics
  );

private:
  friend class ON_OutlineAccumulator;
  ON__UINT32 m_units_per_em = 0;
  ON_OutlineFigure::Type m_figure_type = ON_OutlineFigure::Type::Unset;
  mutable ON__UINT8 m_bbox_status = 0; // 0 = unset, 1 = set, 7 = error

  // Unset = unsorted
  // CounterClockwise: outer figures are CCW
  // Clockwise: outer fitures are CW
  // Error: error occurred during sorting
  mutable ON_OutlineFigure::Orientation m_sorted_figure_outer_orientation = ON_OutlineFigure::Orientation::Unset;

  ON__UINT8 m_reserved1 = 0;

  double m_short_tolerance = 0.0;

  mutable ON_BoundingBox m_bbox = ON_BoundingBox::NanBoundingBox;
  ON_TextBox m_glyph_metrics = ON_TextBox::Unset;

  // unsets the bounding box, m_bSingleStroke settings, ...
  void Internal_ClearCachedValues() const;

  ON__UINT16 Internal_AppendFigure(
    size_t point_count,
    const ON_OutlineFigurePoint* points,
    double short_tolerance,
    bool bSkipPointFigures
  );
  
  ON_ClassArray< ON_OutlineFigure > m_figures;
};

class ON_CLASS ON_OutlineAccumulator
{
public:
  ON_OutlineAccumulator() = default;
  ~ON_OutlineAccumulator() = default;

private:
  ON_OutlineAccumulator(const ON_OutlineAccumulator&) = delete;
  ON_OutlineAccumulator& operator=(const ON_OutlineAccumulator&) = delete;

public:

  /*
  Parameters:
    font_units_per_em - [in]
      This is the height and width of the square font design grid.
      In TrueType fonts, font_units_per_em is often a power of two and generally 1024 or 2048.
      In OpenType fonts, font_units_per_em is often 1000.
      In PostScript fonts, font_units_per_em is often 1000.
    figure_type - [in]
      True if the glyphs are single stroke and open glyphs should not
      be closed.
    coordinate_type - [in]
      ON_OutlineAccumulator::Coordinate::Integer
        The points passed to the figure drawing methods will be ON_2iPoint values.
        The resulting outline will contain ON_2iPoint values.
      ON_OutlineAccumulator::Coordinate::Float
        The points passed to the figure drawing methods will be ON_2fPoint values.
        The resulting outline will contain ON_2fPoint values.
      ON_OutlineAccumulator::Coordinate::Float
        The points passed to the figure drawing methods will be ON_2fPoint values
        that should be rounded to the nearest integer. The resulting outline
        will contain ON_2iPoint values.
    bAccumulatePoints - [in]
      True if the points should be accumulated in the m_outline_points[]
      array.
      False if the points are not accumulated.
      In all cases, the outline bounding box is calculated.
  Remarks:
    Typically both the width and the height of the 'M' glyph 
    in the font are less than font_units_per_em.
  */
  bool BeginGlyphOutline(
    ON__UINT32 font_units_per_em,
    ON_OutlineFigure::Type figure_type,
    ON_Outline* destination_outline
  );

  void Clear();

  ON_Outline* HarvestOutline();

  /*
  Returns:
    EndOutline(false,ON_Outline::DefaultOuterOrientation);
  */
  bool EndOutline();

  /*
  Parameters:
    bNegatePointY - [in]
      If true, the y coordinate of the accumulated points is negated.
      This is done before any orientation adjustments are performed.
    outer_orientation - [in]
      If outer_orientation is ON_OutlineFigure::Orientation::Clockwise,
      or ON_OutlineFigure::Orientation::CounterClockwise, then
      the figures are oriented so that outer boundaries have
      the specified orientation.
      Otherwise this parameter is ignored.
  */
  bool EndOutline(
    bool bNegatePointY,
    ON_OutlineFigure::Orientation outer_orientation
  );
 
  ///////////////////////////////////////////////////////////
  //
  // Tools for adding figures to the outline
  //

  /*
  Description:
    Begins a figure. A glyph outline has zero or more figures.
  Parameters:
    point_type - [in] 
      One of 
        ON_OutlineFigurePoint::Type::BeginFigureUnknown
        ON_OutlineFigurePoint::Type::BeginFigureFilled
        ON_OutlineFigurePoint::Type::BeginFigureHollow
        ON_OutlineFigurePoint::Type::BeginFigureOpen
        ON_OutlineFigurePoint::Type::BeginFigureClosed
    figure_starting_point - [in]
      First point in the figure.
  */
  bool BeginFigure(
    ON_OutlineFigurePoint::Type point_type,
    ON_2fPoint figure_starting_point
  );
  
  /*
  Description:
    Appends a line segment to the current figure.
    The line segment begins at the current_point and ends at line_end_point.
  Parameters:
    line_end_point - [in]
  */
  bool AppendLine(
    ON_2fPoint line_end_point
  );  

  /*
  Description:
    Appends a quadratic (degree = 2, order = 3) bezier to the current figure.
    The quadratic bezier begins at the current_point and ends at cv2.
    The quadratic bezier has three control points
    (current point, cv1, cv2, cv3).
  Parameters:
    cv1 - [in]
    cv2 - [in]
      end of the quadratic bezier.
  */
  bool AppendQuadraticBezier(
    ON_2fPoint cv1,
    ON_2fPoint cv2
  );
  
  /*
  Description:
    Appends a cubic (degree = 3, order = 4) bezier to the current figure.
    The cubic bezier begins at the current_point and ends at cv3.
    The cubic bezier has four control points
    (current point, cv1, cv2, cv3).
  Parameters:
    cv1 - [in]
    cv2 - [in]
    cv3 - [in]
      end of the cubic bezier.
  */
  bool AppendCubicBezier(
    ON_2fPoint cv1,
    ON_2fPoint cv2,
    ON_2fPoint cv3
  );

  /*
  Description:
    Terminates a figure that was started with the previous call to 
    BeginFigure2i() or BeginFigure2f(). 
    The locations of the figure's starting and final points are always identical.
    The point_type parameter is used to indicate if a line segment from the
    starting point to the final point is included in the figure.
  Parameters:
    point_type - [in] 
      One of 
        ON_OutlineFigurePoint::Type::EndFigureUnknown
          If FigureType() is SingleStroke, this value is treated as
          if it were ON_OutlineFigurePoint::Type::EndFigureOpen.
          Otherwise, the final point in the figure will have this type.
        ON_OutlineFigurePoint::Type::EndFigureClosed
          If FigureType() is SingleStroke is true, this value is treated as
          if it were ON_OutlineFigurePoint::Type::EndFigureOpen.
          Otherwise, the final point in the figure will have this type.
        ON_OutlineFigurePoint::Type::EndFigureOpen
          The final point in the figure will have this type.   
  */
  bool EndFigure(
    ON_OutlineFigurePoint::Type point_type
  );

  void AbandonCurrentFigure();

  /*
  Returns:
    Number of points in the current figure.
  */
  unsigned int CurrentFigurePointCount() const;

  /*
  Returns:
    Number of input errors that have occurred.
  Remarks:
    When an error occurs, the current figure is terminated.
  */
  unsigned int ErrorCount() const;

  const ON_OutlineFigurePoint CurrentFigureStartPoint() const;
  
  const ON_OutlineFigurePoint CurrentFigurePreviousPoint() const;
  
  const ON_OutlineFigurePoint CurrentFigurePoint() const;

  const bool CurrentFigureAccumulating() const;

  /*
  Returns:
    Outline design units per em.
  */
  ON__UINT32 UnitsPerEM() const;

  ON_OutlineFigure::Type FigureType() const;

  bool IsInitialized() const;
  bool IsFinalized() const;
  bool IsInitializedOrFinalized() const;

private:
  // Units per EM > 0
  // This is the height and width of the square grid font design grid.
  //     The width of the 'M' glyph in a font can be  different from UPM.
  //     The height of the 'M' glyph in a font is typically less than UPM.
  //     In TrueType fonts, UPM is often a power of two and generally 1024 or 2048.
  //     In OpenType fonts, UPM is often 1000.
  //     In PostScript fonts, UPM is often 1000.
  ON__UINT32 m_units_per_em = 0;
    
  ON__UINT8 m_status = 0;      // 0 = none, 1 initialized, 2 finalized.
  ON_OutlineFigure::Type m_figure_type = ON_OutlineFigure::Type::Unset;

  // 0 = not accumulating points in a figure.
  // 1 = accumulating points in a figure.
  int m_figure_depth = 0;

  // Total number of errors
  ON__UINT32 m_error_count = 0;
  
  // current figure accumulator
  ON_OutlineFigurePoint m_figure_start = ON_OutlineFigurePoint::Unset;
  ON_OutlineFigurePoint m_figure_prev = ON_OutlineFigurePoint::Unset;
  ON_OutlineFigurePoint m_figure_current = ON_OutlineFigurePoint::Unset;
  ON_SimpleArray< ON_OutlineFigurePoint > m_point_accumulator;
  ON_Outline* m_outline = nullptr;
  ON_Outline* m_managed_outline = nullptr;

public:
  /*
    Expert user tool for getting the start point of 
    the figure currently being accumulated.
  */
  const ON_OutlineFigurePoint ActiveFigureStartPoint() const;

  /*
    Expert user tool for getting the current point of 
    the figure being accumulated.
  */
  const ON_OutlineFigurePoint ActiveFigureCurrentPoint() const;

  const ON_Outline& Outline() const;

private:
  bool Internal_InFigure() const;

  void Internal_AccumulateError(
    bool bCancelCurrentFigure
  );

  bool Internal_AccumulatePoint(
    ON_OutlineFigurePoint::Type point_type,
    ON_2fPoint point_location,
    bool bPointInBoundingBox
  );

  ON_Outline& Internal_Outline();
};


/*
  The best way to get a useful ON_FontGlyph is to call
  ON_Font.CodePointGlyph(unicode_code_point)
*/
class ON_CLASS ON_FontGlyph 
{
public:
  /*
    The best way to get a useful ON_FontGlyph is to call
    ON_Font.CodePointGlyph(unicode_code_point)
  */
  ON_FontGlyph() = default;
  ~ON_FontGlyph() = default;
  ON_FontGlyph(const ON_FontGlyph& src);
  ON_FontGlyph& operator=(const ON_FontGlyph& src);


  /*
    If the font and code point are valid, constructs an unmanaged 
    glyph with the specified font and code point.
    The glyph box is not set.
  */
  ON_FontGlyph(
    const class ON_Font* font,
    ON__UINT32 code_point
  );

public:
  static const ON_FontGlyph Unset;

  const class ON_Font* Font() const;
  
  const ON__UINT32 CodePoint() const;

  bool IsEndOfLineCodePoint() const;

  static bool IsEndOfLineCodePoint(
    ON__UINT32 unicode_code_point
  );

  static bool IsCarriageReturnAndLineFeed(
    ON__UINT32 unicode_code_point,
    ON__UINT32 next_unicode_code_point
  );

  /*
  Returns:
    Glyph box in opennurbs normalized font coordinates.
  */
  const ON_TextBox& GlyphBox() const;

  /*
  Returns:
    Font unit glyph box. 
  Remarks:
    Must be used with ON_Font::FontUnitFontMetrics() and a single font to obtain useful results.
    You are probably better of using normalized font coordinates in a ON_FontGlyph.GlyphBox().
  */
  const ON_TextBox& FontUnitGlyphBox() const;

  static int CompareCodePointAndFont(
    const ON_FontGlyph& lhs,
    const ON_FontGlyph& rhs
  );

  /*
  Parameters:
    text - [in]
      Null terminated wchar_t string.
    font - [in]
      The font used to render the glyphs.
    unicode_CRLF_code_point - [in]
      If unicode_CRLF_code_point is a valid unicode code point,
      then consecutive carriage return line feed pairs are converted
      to a single glyph with code point = unicode_CRLF_code_point.

      ON_UnicodeCodePoint::ON_LineSeparator is a good choice when you want to  
      condense carriage return line feed pairs to a single unambiguous code point.

      ON_UnicodeCodePoint::ON_InvalidCodePoint is a good choice when you want to
      preserve carriage return line feed pairs as two separate glyphs.

    glyph_list - [out]
      Note that glyph_list.Count() is often different than the 
      length of the text string or the number of unicode codepoints
      in the decoded text. 
      Adjacent carriage return and line feed codepoints are 
      converted to single a hard end of line.
      All trailing end of line code points are removed from text.
      Invalid unicode encoding sequences are replaced with
      ON_UnicodeCodePoint::ReplacementCharacter glyphs.

    text_box - [out]
      tight bounding boxt of text extents.
      text_box.m_advance.i = maximum of all line horizontal advance values..
      text_box.m_advance.j = vertical advance to baseline of last line
      If if the font height
      is ON_Font::Constants::AnnotationFontCellHeight. If you will render the font
      at a different height from ON_Font::Constants::AnnotationFontCellHeight, then
      use ON_TextBox::Scale as follows:
      ON_TextBox scaled_box 
        = ON_TextBox::Scale(
            text_box,
            (font render height)/((double)ON_Font::Constants::AnnotationFontCellHeight)
        );
  Return:
    number of lines of text or 0 if input is not valid or text is empty.
  */
  static int GetGlyphList
  (
    const wchar_t* text,
    const class ON_Font* font,
    ON__UINT32 unicode_CRLF_code_point,
    ON_SimpleArray<const ON_FontGlyph*>& glyph_list,
    ON_TextBox& text_box
  );

  static int GetGlyphList
  (
    size_t code_point_count,
    ON__UINT32* code_points,
    const class ON_Font* font,
    ON__UINT32 unicode_CRLF_code_point,
    ON_SimpleArray<const ON_FontGlyph*>& glyph_list,
    ON_TextBox& text_box
  );

  /*
  Parameters:
    font - [in]
      The font used to render the glyphs.
    text_box - [out]
      tight bounding boxt of text extents.
      text_box.m_advance.i = maximum of all line horizontal advance values..
      text_box.m_advance.j = vertical advance to baseline of last line
      If if the font height
      is ON_Font::Constants::AnnotationFontCellHeight. If you will render the font
      at a different height from ON_Font::Constants::AnnotationFontCellHeight, then
      use ON_TextBox::Scale as follows:
      ON_TextBox scaled_box 
        = ON_TextBox::Scale(
            text_box,
            (font render height)/((double)ON_Font::Constants::AnnotationFontCellHeight)
        );
  Return:
    number of lines of text or 0 if input is not valid or text is empty.
  */
  static int GetGlyphListBoundingBox
  (
    const wchar_t* text,
    const class ON_Font* font,
    ON_TextBox& text_box
  );

  static int GetGlyphListBoundingBox
  (
    size_t code_point_count,
    ON__UINT32* code_points,
    const class ON_Font* font,
    ON_TextBox& text_box
  );

  /*
  Description:
    Sets the font and code point and unsets every other property including the
    glyph box and substitute information.
  Parameters:
    font - [in]
    code_point - [in]
  */
  bool SetCodePoint(
    const class ON_Font* font,
    ON__UINT32 code_point
  );

  /*
  Returns:
    True if the unicode code point and font are set
  */
  bool CodePointIsSet() const;

  /*
  Returns: 
    true if this is a managed instance.
    Managed instances persist for the lifetime of the application
    and the pointer can be safely saved and referenced at any time.
  */
  bool IsManaged() const;

  /*
  Returns:
    If this->CodePointIsSet() is true, then a persistent pointer
    to a managed glyph with the same code point and font is returned.
    Otherwise nullptr is returned.
  */
  const ON_FontGlyph* ManagedGlyph() const;

  /*
  Parameters:
    bUseReplacementCharacter - [in]
      When this->CodePointIsSet() is true, 
      and bUseReplacementCharacter is true,
      and no reasonable glyph definition exists,
      and no substituted  is available,
      then the replacement character glyph for UNICODE code point
      ON_UnicodeCodePoint::ON_ReplacementCharacter (U+FFFD) will be returned.

  Returns:
    A managed glyph that can be used to render "this".
    If this->CodePointIsSet() is false, nullptr is returned.
    If this->CodePointIsSet() is true, the returned glyph may
    have a different font and code point when the current 
    computer requires font or glyph substitution to draw
    the glyph.  When the current platform cannot render this,
    nullptr or the replacement glyph is returned depending on
    the value of bUseReplacementCharacter.

  See Also:
    ON_FontGlyph.SubstituteGlyph().
  */
  const ON_FontGlyph* RenderGlyph(
    bool bUseReplacementCharacter
    ) const;

  /*
  Returns:
    If this is a managed glyph or a copy of a managed glyph, 
    and a substitute font or code point is used to render the glyph, 
    then the substitute is returned.
    In all other cases, nullptr is returned.
  See Also:
    ON_FontGlyph.RenderGlyph().
  */
  const ON_FontGlyph* SubstituteGlyph() const;

  /*
  Parameters:
    bIncludeCharMaps - [in]
      If true, then char information is printed.
  */
  void Dump(
    bool bIncludeCharMaps,
    ON_TextLog& text_log
  ) const;

  void Dump(
    bool bIncludeFont,
    bool bIncludeCharMaps,
    bool bIncludeSubstitute,
    bool bIncludeFontUnitTextBox,
    ON_TextLog& text_log
  ) const;

#if defined(OPENNURBS_FREETYPE_SUPPORT)
// Look in opennurbs_system_runtime.h for the correct place to define OPENNURBS_FREETYPE_SUPPORT.
// Do NOT define OPENNURBS_FREETYPE_SUPPORT here or in your project setting ("makefile").


public:
  /*
  Description:
    This is a debugging tool to test the code that starts with a font and 
    Unicode code point and and finds a glyph in the font definition for 
    that code point.
  Parameters:
    text_log - [in]
      If text_log is not nullptr, then diagnostic messages are sent to this log.
  Returns:
    True: 
      No errors were found. Every available charmap either returned the same glyph id
      that FontGlyphId() function returns or had no glyph id for this code point.
    False:
      Inconsistent results were returned from different charmaps.
  Remarks:
    If a font or charmap is known to contain a bug and that bug is
    handled by opennurbs, then true is returned and a message is printed
    to the log.
  */
  bool TestFreeTypeFaceCharMaps(
    ON_TextLog* text_log
  ) const;

public:
  /*
  Description:
    If opennurbs is built with FreeType support then
    FT_Face freetype_face = (FT_Face)glyph->FreeTypeFace()
    will return a FreeType face that can be used to render the glyph.
  Parameters:
    font - [in]
  Returns:
    A value that can be cast as a FreeType FT_Face.
  Example
    const ON_Font* font = ...;
    FT_Face freetype_face = (FT_Face)glyph->FreeTypeFace(font);
  Remarks:
    Many fonts do not have a glyph for a every UNICODE codepoint and font
    substitution is required. If you want to get the freetype face
    used for a specific UNICODE codepoint, call ON_Font::CodepointFreeTypeFace().
  */
  const ON__UINT_PTR FreeTypeFace() const;
#endif

public:
  /*
  Returns:
    Font glyph id.
  Remarks:
    The glyph id depends on the font and is assigned by the font designer.
    In particular the font glyph id for the same Unicode code point
    often varies from font to font. In a font, it is often the case that
    multiple Unicode code points map to the same glyph. For example,
    space an non-breaking space typically map to the same font glyph id.
  */
  unsigned int FontGlyphIndex() const;

  bool FontGlyphIndexIsSet() const;


  ON_DEPRECATED_MSG("Use FontGlyphIndex()")
  const ON__UINT_PTR FontGlyphId() const;

  ON_DEPRECATED_MSG("Use FontGlyphIndexIsSet()")
  bool FontGlyphIdIsSet() const;

  /*
  Description:
    Get glyph contours as NURBS curves.
  Parameters:
    bSingleStrokeFont - [in]
      If true, open contours will not be closed by adding a line segment.
    height_of_capital - [in]
      If > 0, output curves, bounding box, and advance vector are scaled 
      by height_of_capital/(font design capital height). For fonts like
      Arial, Helvetica, Times Roman, and Courier this means the height
      of H and I will be height_of_capital. 
      Otherwise, no scaling is applied to the output curves, bounding box,
      and advance vector.
      Pass 0.0 or in this->Font()->HeightOfI() to get the contours to be in opennurbs
      normalized font coordinates.
      All other values < 0 are treated as 0.0.
    glyph_contours - [out]
    glyph_bbox - [out]
      glyph bounding box.
    glyph_advance - [out]
      glyph_advance->x = horizontal advance to apply when rendering glyphs horizontally.
      A positive horizontal advance indicates advance to the right.
      glyph_advance->y = vertical advance to apply when rendering glyphs vertically.
      A positive vertical advance indicates advance downwards.
  */
  bool GetGlyphContours(
    bool bSingleStrokeFont,
    double height_of_capital,
    ON_ClassArray< ON_SimpleArray< ON_Curve* > >& glyph_contours,
    ON_BoundingBox* glyph_bbox,
    ON_3dVector* glyph_advance
  ) const;

  bool GetOutline(
    bool bSingleStrokeFont,
    class ON_Outline& outline
  ) const;


  static bool GetStringContours(
    const wchar_t* text_string,
    const class ON_Font* font,
    bool bSingleStrokeFont,
    double height_of_capital,
    double small_caps_scale,
    ON_ClassArray< ON_ClassArray< ON_SimpleArray< ON_Curve* > > >& string_contours
  );


private:
  friend class ON_GlyphMap;
  friend class ON_Font;
  
  // NOTE WELL: 
  //   The offset of m_codepoint in ON_FontGlyph must be >= 8 bytes.
  //   so the ON_FixeSizePool that manages memory for the glyph cache
  //   can efficiently iterate all active managed glyphs.
  //
  ON_TextBox m_font_unit_glyph_bbox; // values in the native font definition units (freetype FT_LOAD_NO_SCALE units)
  ON_TextBox m_normalized_glyph_bbox; // bounding box in opennurbs normalized font coordinates

  // This box is for the platform native glyph. It can be different than m_glyph_box.
  // Example:
  //  Start with a Windows LOGFONT with face = Arial, height = ON_Font::Constants::AnnotationFontCellHeight (256)
  //  Native Windows height of Arial I = 165, height of LF = ...
  //  FreeType made from the same LOGFONT on the same has height of Arial I = 184, height of LF = ...

  // When font does not contain a glyph to render  a specified unicode codepoint,
  // then one or more glyphs from one or more substitution fonts are used to
  // render the codepoint. In this case, m_substitutes points to a linked
  // list of substitute used to render the glyph.
  //
  ON__UINT32 m_code_point = ON_UnicodeCodePoint::ON_InvalidCodePoint;
 
  ON__UINT8 m_is_managed = 0; // 1 = managed glyph
  ON__UINT8 m_reserved1 = 0;
  ON__UINT16 m_reserved2 = 0;
  ON__UINT32 m_reserved3 = 0;
  ON__UINT32 m_font_glyph_index = 0;
  const class ON_Font* m_managed_font = nullptr;
  const class ON_FontGlyph* m_substitute = nullptr;


private:
  void Internal_SetFontGlyphIndex(unsigned int font_glyph_index);
  void Internal_CopyFrom(const ON_FontGlyph& src);
  static ON_FontGlyph* Internal_AllocateManagedGlyph(const ON_FontGlyph& src);
  bool Internal_GetPlatformSubstitute(
    ON_FontGlyph& substitute
  ) const;
};


#if defined(ON_OS_WINDOWS_GDI)
class ON_CLASS ON_WindowsDWriteFontInformation
{
public:
  ON_WindowsDWriteFontInformation() = default;
  ~ON_WindowsDWriteFontInformation() = default;
  ON_WindowsDWriteFontInformation(const ON_WindowsDWriteFontInformation&) = default;
  ON_WindowsDWriteFontInformation& operator=(const ON_WindowsDWriteFontInformation&) = default;

public:
  void Dump(ON_TextLog& text_log) const;

  static int CompareFamilyName(const ON_WindowsDWriteFontInformation* lhs, const ON_WindowsDWriteFontInformation* rhs);
  static int CompareFamilyNameFaceNameWeightStretchStyle(const ON_WindowsDWriteFontInformation* lhs, const ON_WindowsDWriteFontInformation* rhs);
  static int ComparePostScriptName(const ON_WindowsDWriteFontInformation* lhs, const ON_WindowsDWriteFontInformation* rhs);

public:
  // value passed to IDWriteFontCollection.GetFontFamily(m_family_index,...)
  // IDWriteFactory.GetSystemFontCollection() is used to get the IDWriteFontCollection.
  unsigned int m_family_index = 0;

  // value passed to IDWriteFontFamily.GetFont(m_family_font_index,...)
  unsigned int m_family_font_index = 0;

  struct IDWriteFont* m_dwrite_font = nullptr;

  // preferred locale used to get the localized name values. 
  // If the a parrticular string was not available in the preferred locale, 
  // then other locales are used with "en-us" being the preferred alternate locale.
  ON_wString m_prefered_locale;

  // from IDWriteFontFamily.GetFamilyNames()
  const ON_wString FamilyName() const;
  ON_wString m_loc_family_name;
  ON_wString m_en_family_name;

  // from IDWriteFont.GetFaceNames()
  const ON_wString FaceName() const;
  ON_wString m_loc_face_name;
  ON_wString m_en_face_name;

  // DWRITE_FONT_WEIGHT value from IDWriteFont.GetWeight()
  unsigned int m_weight = 0;

  // DWRITE_FONT_STRETCH value from IDWriteFont.GetStretch()
  unsigned int m_stretch = 0;

  // DWRITE_FONT_STYLE value from IDWriteFont.GetStyle()
  unsigned int m_style = 0;


  // from IDWriteFont.IsSymbolFont()
  bool m_bIsSymbolFont = false;

  // deconstructed DWRITE_FONT_SIMULATIONS value from IDWriteFont.GetSimulations()
  bool m_bSimulatedBold = false;    // DWRITE_FONT_SIMULATIONS_BOLD
  bool m_bSimulatedOblique = false; // DWRITE_FONT_SIMULATIONS_OBLIQUE
  bool m_bSimulatedOther = false;   // future DWRITE_FONT_SIMULATIONS_...

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_FULL_NAME, ... )
  ON_wString m_loc_full_name;
  ON_wString m_en_full_name;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_POSTSCRIPT_NAME, ... )
  const ON_wString PostScriptName() const;
  ON_wString m_loc_postscript_name;
  ON_wString m_en_postscript_name;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_WIN32_FAMILY_NAMES, ... )
  // == LOGFONT lfFaceName
  const ON_wString WindowsLogfontName() const;
  ON_wString m_loc_gdi_family_name;
  ON_wString m_en_gdi_family_name;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_WIN32_SUBFAMILY_NAMES, ... )
  ON_wString m_loc_gdi_subfamily_name;
  ON_wString m_en_gdi_subfamily_name;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_WEIGHT_STRETCH_STYLE_FAMILY_NAME, ... )
  ON_wString m_loc_weight_stretch_style_model_name;
  ON_wString m_en_weight_stretch_style_model_name;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_COPYRIGHT_NOTICE, ... )
  ON_wString m_loc_field_0_copyright;
  ON_wString m_en_field_0_copyright;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_VERSION_STRINGS, ... )
  ON_wString m_loc_field_5_version;
  ON_wString m_en_field_5_version;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_TRADEMARK, ... )
  ON_wString m_loc_field_7_trademark;
  ON_wString m_en_field_7_trademark;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_MANUFACTURER, ... )
  ON_wString m_loc_field_8_manufacturer;
  ON_wString m_en_field_8_manufacturer;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_DESIGNER, ... )
  ON_wString m_loc_field_9_designer;
  ON_wString m_en_field_9_designer;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_DESCRIPTION, ... )
  // Opennurbs searches the description saved in field 10 of the name table
  // for the strings "Engraving - single stroke" / "Engraving - double stroke" / "Engraving"
  // to identify fonts that are desgned for engraving (and which tend to render poorly when
  // used to display text devices like screens, monitors, and printers).
  // The SLF (single line fonts) are examples of fonts that have Engraving in field 10.
  ON_wString m_loc_field_10_description;
  ON_wString m_en_field_10_description;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_FONT_VENDOR_URL, ... )
  ON_wString m_loc_field_11_vendor_URL;
  ON_wString m_en_field_11_vendor_URL;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_DESIGNER_URL, ... )
  ON_wString m_loc_field_12_designer_URL;
  ON_wString m_en_field_12_designer_URL;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_LICENSE_DESCRIPTION, ... )
  ON_wString m_loc_field_13_license;
  ON_wString m_en_field_13_license;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_LICENSE_INFO_URL, ... )
  ON_wString m_loc_field_14_license_URL;
  ON_wString m_en_field_14_license_URL;

  // from IDWriteFont.GetInformationalStrings( DWRITE_INFORMATIONAL_STRING_POSTSCRIPT_CID_NAME, ... )
  ON_wString m_loc_field_20_postscript_cid; // NOT the same as PostScriptName
  ON_wString m_en_field_20_postscript_cid;

  // from IDWriteGdiInterop.ConvertFontToLOGFONT
  LOGFONT m_gdi_interop_logfont = {};

  // from IDWriteGdiInterop.ConvertFontToLOGFONT
  bool m_gdi_interop_logfont_bIsSystemFont = false;

  // from IDWriteFont.GetMetrics
  ON_FontMetrics m_font_metrics;

  // Sample glyph metrics from IDWriteFontFace.GetDesignGlyphMetrics

  // "standard" metric glyphs
  ON_FontGlyph m_Spacebox;
  ON_FontGlyph m_Hbox;
  ON_FontGlyph m_Ibox;
  ON_FontGlyph m_xbox;

  ON_PANOSE1 m_panose1;

  ON_OutlineFigure::Type m_outline_figure_type = ON_OutlineFigure::Type::Unset;
};
#endif

class ON_CLASS ON_FontFaceQuartet
{
public:

  enum class Member : unsigned char
  {
    Unset = 0,
    Regular = 1,
    Bold = 2,
    Italic = 3,
    BoldItalic = 4
  };

  static const ON_wString MemberToString(
    ON_FontFaceQuartet::Member member
  );

  static ON_FontFaceQuartet::Member MemberFromUnsigned(
    unsigned int member_as_unsigned
  );

  static ON_FontFaceQuartet::Member MemberFromBoldAndItalic(
    bool bMemberIsBold,
    bool bMemberIsItalic
    );

  /*
  Description:
    When an exact quartet face bold/italic match is not available, choosing
    an available quartet face that minimizes ON_FontFaceQuartet::BoldItalicDeviation()
    is one way to select which available quartet face to use.
  Returns:
    A distance between two quartet face members.
  */
  static unsigned BoldItalicDeviation(
    ON_FontFaceQuartet::Member desired_member,
    ON_FontFaceQuartet::Member available_member
  );

  ON_FontFaceQuartet() = default;
  ~ON_FontFaceQuartet() = default;
  ON_FontFaceQuartet(const ON_FontFaceQuartet&) = default;
  ON_FontFaceQuartet& operator=(const ON_FontFaceQuartet&) = default;

  ON_FontFaceQuartet(
    const wchar_t* quartet_name,
    const class ON_Font* regular,
    const class ON_Font* bold,
    const class ON_Font* italic,
    const class ON_Font* bold_italic
  );

  static int CompareQuartetName(
    const ON_FontFaceQuartet* lhs,
    const ON_FontFaceQuartet* rhs
  );

  /*
  Returns a sample rich text string demonstrating the faces in the quartet.
  */
  const ON_wString RichTextSample(
    ON::RichTextStyle rich_text_style
  ) const;

public:
  static const ON_FontFaceQuartet Empty;

public:
  bool HasRegularFace() const;
  bool HasBoldFace() const;
  bool HasItalicFace() const;
  bool HasBoldItalicFace() const;
  bool HasAllFaces() const;


  /// <returns>True if FaceCount() = 0. (The name may be empty or not empty.)</returns>
  bool IsEmpty() const;

  /// <returns>True if FaceCount() > 0. (The name may be empty or not empty.)</returns>
  bool IsNotEmpty() const;

  /// <returns>Total number of available faces (0 to 4).</returns>
  unsigned int FaceCount() const;

  /// <returns>Number of faces that are not installed on this device (0 to FaceCount()).</returns>
  unsigned int NotInstalledFaceCount() const;

  /// <returns>Number of faces that are simulated (0 to FaceCount()).</returns>
  unsigned int SimulatedFaceCount() const;

  const ON_wString QuartetName() const;
  const class ON_Font* RegularFace() const;
  const class ON_Font* BoldFace() const;
  const class ON_Font* ItalicFace() const;
  const class ON_Font* BoldItalicFace() const;

  /*
  Parameters:
    font - [in]
      Font to test
  Returns:
    If font exactly matches a quartet member, that member is identified.
    Otherwise, ON_FontFaceQuartet::Member::Unset is returned.
  */
  ON_FontFaceQuartet::Member QuartetMember(
    const ON_Font* font
  ) const;

  /*
  Parameters:
    member - [in]
  Returns:
    Specified quartet member.
  */
  const ON_Font* Face(
    ON_FontFaceQuartet::Member member
  ) const;

  /*
  Parameters:
    member - [in]
  Returns:
    Closest quartet member.
  */
  const ON_Font* ClosestFace(
    ON_FontFaceQuartet::Member member
  ) const;

  const ON_Font* Face(
    bool bBold,
    bool bItalic
  ) const;

  const ON_Font* ClosestFace(
    bool bPreferedBold,
    bool bPreferedItalic
  ) const;

  void Dump(ON_TextLog& text_log) const;

private:
  ON_wString m_quartet_name;
  const class ON_Font* m_regular = nullptr;
  const class ON_Font* m_bold = nullptr;
  const class ON_Font* m_italic = nullptr;
  const class ON_Font* m_bold_italic = nullptr;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_ClassArray<ON_FontFaceQuartet>;
#endif

/// <summary>
/// An ON_Font is a face in a font family. It corresponds to a Windows LOGFONT,
/// a .NET System.Drawing.Font or a FreeType FT_Face.
/// </summary>
class ON_CLASS ON_Font
{
public:

 #pragma region RH_C_SHARED_ENUM [ON_Font::Origin] [Rhino.DocObjects.Font.FontOrigin] [nested:byte]
  /// <summary>
  /// Platform where font originated. This information is useful when 
  /// searching for appropriate substitutes.
  /// </summary>
  enum class Origin : unsigned char
  {
    /// <summary> Not set. </summary>
    Unset = 0,

    /// <summary> Origin unknown. Changing an ON_Font characteristic like weight or style sets the origin to unknown. </summary>
    Unknown = 1,

    /// <summary> 
    /// Set from a Windows IDWriteFont by ON_Font::SetFromDWriteFont() 
    /// or a Windows LOGFONT by ON_Font::SetFromWindowsLogFont() and
    /// FaceName and WindowLogfontName match a font installed on a Windows device.
    /// </summary>
    WindowsFont = 2,

    /// <summary> 
    /// Set from an Apple CTFont. The PostScriptName() and FamilyName() match a
    /// font installed on device running MacOS or iOS. The FaceName() matches
    /// the "typeface" name shown in the MacOS FontBook app.
    /// </summary>
    AppleFont = 3
  };
#pragma endregion

#pragma region RH_C_SHARED_ENUM [ON_Font::FontType] [Rhino.DocObjects.Font.FontType] [nested:byte]
  /// <summary>
  /// An enum that reports if the font face is available on the current device.
  /// </summary>
  enum class FontType : unsigned char
  {
    /// <summary> Not set. </summary>
    Unset = 0,

    /// <summary> 
    /// In the managed font list.
    /// </summary>
    ManagedFont = 1,

    /// <summary> 
    /// In the installed font list.
    /// </summary>
    InstalledFont = 2
  };
#pragma endregion

#pragma region RH_C_SHARED_ENUM [ON_Font::Weight] [Rhino.DocObjects.Font.FontWeight] [nested:byte]
  /// <summary>
  /// Weight enum values
  /// Avoid casting these values to int.
  /// Use ON_Font::WindowsLogfontWeightFromWeight() or
  /// ON_Font::AppleWeightOfFontFromWeight() or
  /// add another converter.
  /// </summary>
  enum class Weight : unsigned char
  {
    /// <summary> Not set. </summary>
    Unset = 0,

    /// <summary> IsLight = true </summary>
    Thin = 1,

    /// <summary> IsLight = true </summary>
    Ultralight = 2,

    //ExtraLight = 2,

    /// <summary> IsLight = true </summary>
    Light = 3,

    /// <summary> Default font weight. IsNormalWeight = true  Also called Regular.</summary>
    Normal = 4,  

    //Regular    = 4,

    /// <summary> IsNormalWeight = true </summary>
    Medium = 5,
    
    /// <summary> IsBold = true </summary>
    Semibold = 6,

    //Demibold   = 6,
    //Demi       = 6,
    //Semi       = 6,
   
    /// <summary> IsBold = true </summary>
    Bold = 7,
    
    /// <summary> IsBold = true </summary>
    Ultrabold = 8,

    //ExtraBold  = 8,

    /// <summary> IsBold = true Also called Black</summary>
    Heavy      = 9

    //Black      = 9,
  };
#pragma endregion

  /*
  Returns:
    -1: weight_a is lighter, weight_b is heavier
    +1: weight_a is heavier, weight_b is lighter
     0: weight_a = weight_b
  */
  static int CompareWeight(
    ON_Font::Weight weight_a,
    ON_Font::Weight weight_b
    );

  /*
  Description:
    In the rare cases when an ON_Font::Weight value must be passed
    as an unsigned int, use ON_Font::FontWeightFromUnsigned() to
    convert the unsigned value to an ON_Font::Weight value.
  Parameters:
    unsigned_font_weight - [in]
  */
  static ON_Font::Weight FontWeightFromUnsigned(
    unsigned int unsigned_font_weight
  );

  /*
  Description:
    The correspondence between Windows LOGFONT lfWeight values and
    ON_Font::Weight enum values is
    ON_Font::Weight::Thin       = 100 LOGFONT lfWeight
    ON_Font::Weight::Ultralight = 200 LOGFONT lfWeight
    ON_Font::Weight::Light      = 300 LOGFONT lfWeight
    ON_Font::Weight::Normal     = 400 LOGFONT lfWeight
    ON_Font::Weight::Medium     = 500 LOGFONT lfWeight
    ON_Font::Weight::Semibold   = 600 LOGFONT lfWeight
    ON_Font::Weight::Bold       = 700 LOGFONT lfWeight
    ON_Font::Weight::Ultrabold  = 800 LOGFONT lfWeight
    ON_Font::Weight::Heavy      = 900 LOGFONT lfWeight
  Returns:
    The Windows LOGFONT lfWeight value that corresponds to the ON_Font::Weight enum value.
  */
  static int WindowsLogfontWeightFromWeight(
    ON_Font::Weight font_weight
    );

  /*
  Description:
    The correspondence between Apple "weight of font" values and
    ON_Font::Weight enum values is
    ON_Font::Weight::Thin       = 1
    ON_Font::Weight::Ultralight = 2
    ON_Font::Weight::Light      = 3
    ON_Font::Weight::Normal     = 4  
    ON_Font::Weight::Medium     = 5
    ON_Font::Weight::Semibold   = 6
    ON_Font::Weight::Bold       = 7
    ON_Font::Weight::Ultrabold  = 8
    ON_Font::Weight::Heavy      = 9
  Returns:
    The Apple "weight of font" value that corresponds to the ON_Font::Weight enum value.
  */  
  static int AppleWeightOfFontFromWeight(
    ON_Font::Weight font_weight
    );

  /*
  Description:
    The correspondence between Apple "font weight trait" values and
    ON_Font::Weight enum values is
    ON_Font::Weight::Thin       = -0.4    Apple font weight trait
    ON_Font::Weight::Ultralight = -0.2667 Apple font weight trait
    ON_Font::Weight::Light      = -0.1333 Apple font weight trait
    ON_Font::Weight::Normal     =  0.0    Apple font weight trait
    ON_Font::Weight::Medium     =  0.1333 Apple font weight trait
    ON_Font::Weight::Semibold   =  0.2667 Apple font weight trait
    ON_Font::Weight::Bold       =  0.4    Apple font weight trait
    ON_Font::Weight::Ultrabold  =  0.5333 Apple font weight trait
    ON_Font::Weight::Heavy      =  0.6667 Apple font weight trait
  Returns:
    The Apple "WeightTrait" value that corresponds to the ON_Font::Weight enum value.
  */  
  static double AppleFontWeightTraitFromWeight(
    ON_Font::Weight font_weight
    );

  /*
  Description:
    The correspondence between Windows LOGFONT lfWeight values and
    ON_Font::Weight enum values is

    ON_Font::Weight::Thin       = 100
    ON_Font::Weight::Ultralight = 200
    ON_Font::Weight::Light      = 300
    ON_Font::Weight::Normal     = 400
    ON_Font::Weight::Medium     = 500
    ON_Font::Weight::Semibold   = 600
    ON_Font::Weight::Bold       = 700
    ON_Font::Weight::Ultrabold  = 800
    ON_Font::Weight::Heavy      = 900
  Returns:
    The best ON_Font::Weight enum value for the Windows LOGFONT weight.
  */  

  static ON_Font::Weight WeightFromWindowsLogfontWeight(
    int windows_logfont_weight
    );

  /*
  Description:
    The correspondence between Apple "weight of font" values and
    ON_Font::Weight enum values is
    ON_Font::Weight::Thin       = 1
    ON_Font::Weight::Ultralight = 2
    ON_Font::Weight::Light      = 3
    ON_Font::Weight::Normal     = 4  
    ON_Font::Weight::Medium     = 5
    ON_Font::Weight::Semibold   = 6
    ON_Font::Weight::Bold       = 7
    ON_Font::Weight::Ultrabold  = 8
    ON_Font::Weight::Heavy      = 9
  Returns:
    The best ON_Font::Weight enum value for the Apple weight of font.
  */  
  static ON_Font::Weight WeightFromAppleWeightOfFont(
    int apple_weight_of_font
    );

  /*
  Parameters:
    apple_font_weight_trait - [in]
      Apple WeightTrait
      The valid value range is from -1.0 to 1.0. The value of 0.0 corresponds to the regular or medium font weight.
  */
  static ON_Font::Weight WeightFromAppleFontWeightTrait(
    double apple_font_weight_trait
    );

  static const wchar_t* WeightToWideString(
    ON_Font::Weight font_weight
  );

  /*
  Returns:
    True if weight is ON_Font::Weight::Semibold or heavier.
  */
  static bool IsBoldWeight(
    ON_Font::Weight weight
  );


#pragma region RH_C_SHARED_ENUM [ON_Font::Stretch] [Rhino.DocObjects.Font.FontStretch] [nested:byte]
  /// <summary>
  /// Horizontal expansion or contraction of font
  /// </summary>
  enum class Stretch : unsigned char
  {
    /// <summary> Not set. </summary>
    Unset = 0,
    /// <summary> </summary>
    Ultracondensed = 1,
    /// <summary> </summary>
    Extracondensed = 2,
    /// <summary> </summary>
    Condensed = 3,
    /// <summary> </summary>
    Semicondensed = 4,

    /// <summary> Default font stretch. </summary>
    Medium = 5,

    //Normal         = 5,

    /// <summary> </summary>
    Semiexpanded = 6,
    /// <summary> </summary>
    Expanded = 7,
    /// <summary> </summary>
    Extraexpanded = 8,
    /// <summary> </summary>
    Ultraexpanded = 9
  };
#pragma endregion

  /*
  Description:
    In the rare cases when an ON_Font::Stretch value must be passed
    as an unsigned int, use ON_Font::FontStretchFromUnsigned() to
    convert the unsigned value to an ON_Font::Stretch value.
  Parameters:
    unsigned_font_stretch - [in]
  */
  static ON_Font::Stretch FontStretchFromUnsigned(
    unsigned int unsigned_font_stretch
    );
  
  static const wchar_t* StretchToWideString(
    ON_Font::Stretch font_stretch
  );

#if defined(ON_OS_WINDOWS_GDI)
  static ON_Font::Stretch FontStretchFromDWriteStretch(
    unsigned int dwrite_stretch,
    ON_Font::Stretch undefined_result
  );
#endif



#pragma region RH_C_SHARED_ENUM [ON_Font::Style] [Rhino.DocObjects.Font.FontStyle] [nested:byte]
  /// <summary>
  /// Vertical angle of font
  /// Upright, Italic, or Oblique
  /// </summary>
  enum class Style : unsigned char
  {
    /// <summary> Not set. </summary>
    Unset = 0,

    /// <summary> Default font style. </summary>
    Upright = 1,

    //Normal = 1,
    //Roman = 1,

    /// <summary> 
    /// The face is sloped so the top is to the right of the base.
    /// Face names sometimes use the word "oblique" for italic faces.
    /// </summary>
    Italic = 2,

    /// <summary> 
    /// The face is sloped so the top is to the left of the base.
    /// This is extremely rare.
    /// NOTE WELL: Face names sometimes use the word "oblique" for italic faces.
    /// </summary>
    Oblique = 3
  };
#pragma endregion

  /*
  Description:
    In the rare cases when an ON_Font::Style value must be passed
    as an unsigned int, use ON_Font::FontStyleFromUnsigned() to
    convert the unsigned value to an ON_Font::Style value.
  Parameters:
    unsigned_font_style - [in]
  */
  static ON_Font::Style FontStyleFromUnsigned(
    unsigned int unsigned_font_style
    );

  static const wchar_t* StyleToWideString(
    ON_Font::Style font_style
  );


  /*
  Returns:
    If this font is installed or managed, the installed or mangaged font face quartet is returned.
    Otherwise ON_FontFaceQuartet::Empty is returned.
    Note that managed font quartets can be enlarged to include missing faces by calling
    ON_Font::FontFromRichTextProperties(). Installed font quartets exactly match
    what is installed on the current device.
    if this font is not a member of an installed face quartet.
  */
  const ON_FontFaceQuartet FontQuartet() const;

  /*
  Returns:
    The installed font face quartet for this font or ON_FontFaceQuartet::Empty 
    if this font is not a member of an installed face quartet.
  */
  const ON_FontFaceQuartet InstalledFontQuartet() const;

public:

  /*
  Returns:
    True if lhs an rhs are in the same font family.
  */
  static bool EqualFontFamily(
    const ON_Font* lhs,
    const ON_Font* rhs
  );

  /*
  Returns:
    True if lhs and rhs have equal family names and equal face names
    in with the name local or in English.
  */
  static bool EqualFontFamilyAndFace(
    const ON_Font* lhs,
    const ON_Font* rhs
  );

  static bool EqualWeightStretchStyle(
    const ON_Font* lhs,
    const ON_Font* rhs,
    bool bUnsetIsEqual
  );

  static bool EqualWeight(
    const ON_Font* lhs,
    const ON_Font* rhs,
    bool bUnsetIsEqual
  );

  static bool EqualStretch(
    const ON_Font* lhs,
    const ON_Font* rhs,
    bool bUnsetIsEqual
  );

  static bool EqualStyle(
    const ON_Font* lhs,
    const ON_Font* rhs,
    bool bUnsetIsEqual
  );


public:

  // ON_Font::Default depends on the platform.
  //  Arial on Windows
  //  Helvetica Neue on Mac OS
  static const ON_Font Default;

  // ON_Font::Unset has unset face name and platform font name.
  static const ON_Font Unset;

  /*
  Returns:
    Windows: "Arial"
    Apple: "Helvetica Neue"
  */
  static const wchar_t* DefaultFamilyName();

  /*
  Returns:
    Windows: "Regular"
    Apple: "Regular"
  */
  static const wchar_t* DefaultFaceName();

  /*
  Returns:
    Windows: "ArialMT"
    Apple: "HelveticaNeue"
  */
  static const wchar_t* DefaultPostScriptName();


  /*
  Returns:
    Windows: "ArialMT"
    Apple: "HelveticaNeue"
  */
  static const wchar_t* DefaultWindowsLogfontName();

  /*
  Description:
    This function is poorly designed, poorly named, named and doesn't do 
    anything very useful. Avoid it. It will be deleted when it is possible
    to break the SDK.
  Parameters:
    face_name - [in]
      Name to test
  Returns:
    False if face_name is nullptr, or face_name is the empty string, 
    or the first element in the name is < ON_wString::Space,
    or the face_name contains any of these elements:   ; " ' ` = #
    True otherwise.
  */
  static bool IsValidFaceName(
    const wchar_t* face_name
    );
    
private:
  // This private constructor is used to construct ON_Font::Default, managed fonts,
  // and installed fonts. Never make this constructor protected or public.
  ON_Font(
    ON_Font::FontType font_type,
    const ON_Font& src
    );

private:
  // Use ON_Font( const ON_Font& ) or ON_Font::operator= if you need to make a copy.
  // Never make CopyHelper protected or public.
  void Internal_CopyFrom(
    const ON_Font& src
    );

public:
  /*
  Description:
    Get a font managed by the application from the font characteristics.
    Never delete a font returned by GetManagedFont().
  Parameters:
    face_name - [in]
    font_weight - [in]
      default = ON_Font::Default.FontWeight()
    font_style - [in]
      default = ON_Font::Default.FontStyle()
    font_stretch - [in]
      default = ON_Font::Default.FontStretch()
    bUnderlined - [in]
      default = ON_Font::Default.Underlined() = false
    bStrikethrough - [in]
      default = ON_Font::Default.Strikethrough() = false
    linefeed_ratio - [in]
      default = ON_Font::Default.LinefeedRatio()
    windows_charset - [in]
      default = ON_Font::WindowsCharSet::DefaultCharSet
  */
  static const ON_Font* GetManagedFont(
    const wchar_t* face_name
    );

  static const ON_Font* GetManagedFont(
    double point_size,
    const wchar_t* face_name
    );

  static const ON_Font* GetManagedFont(
    const wchar_t* face_name,
    bool bBold
    );

  static const ON_Font* GetManagedFont(
    double point_size,
    const wchar_t* face_name,
    bool bBold
    );

  static const ON_Font* GetManagedFont(
    const wchar_t* face_name,
    bool bBold,
    bool bItalic
    );

  static const ON_Font* GetManagedFont(
    double point_size,
    const wchar_t* face_name,
    bool bBold,
    bool bItalic
    );

  static const ON_Font* GetManagedFont(
    const wchar_t* face_name, 
    ON_Font::Weight font_weight,
    ON_Font::Style font_style
    );

  static const ON_Font* GetManagedFont(
    double point_size,
    const wchar_t* face_name, 
    ON_Font::Weight font_weight,
    ON_Font::Style font_style
    );

  static const ON_Font* GetManagedFont(
    const wchar_t* face_name, 
    ON_Font::Weight font_weight,
    ON_Font::Style font_style,
    ON_Font::Stretch font_stretch,
    bool bUnderlined, 
    bool bStrikethrough,
    double linefeed_ratio,
    unsigned int logfont_charset
    );

  static const ON_Font* GetManagedFont(
    double point_size,
    const wchar_t* face_name, 
    ON_Font::Weight font_weight,
    ON_Font::Style font_style,
    ON_Font::Stretch font_stretch,
    bool bUnderlined, 
    bool bStrikethrough,
    double linefeed_ratio,
    unsigned int logfont_charset
    );

  static const ON_Font* GetManagedFontFromFontDescription(
    const wchar_t* font_description
    );

#if defined(ON_OS_WINDOWS_GDI)
  /*
  Description:
    Get a managed font from a LOGFONT
  Parameters:
    map_mode - [in]
      If map_mode is 0, then ::GetMapMode(hdc) is called to get the mapping mode.
      Otherwised, map_mode must identify a Windows mapping mode
      (MM_TEXT, MM_LOMETRIC, MM_HIMETRIC, MM_LOENGLISH, MM_HIENGLISH, M_TWIPS).
      If map_mode = MM_TEXT (1), then hdc is used as described in the hdc parameter.
    hdc - [in]
      Windows device context.
      If map_mode is set and not MM_TEXT, then hdc is ignored.
      Otherwise the device context is used to get the mapping mode ( GetMapMode(hdc) ). 
      If the mapping mode is MM_TEXT, then the additional device context values
      GetDeviceCaps(hdc, LOGPIXELSY) and conversion between device and logical pixel heights
      DPtoLP(hdc,...) and LPtoDP(hdc,...) are used.
    logfont - [in]
      These logfont properties are used to find the managed font.
        lfHeight (when dc is not zero)
        lfWeight;
        lfItalic;
        lfUnderline;
        lfStrikeOut;
        lfCharSet;
        lfFaceName[LF_FACESIZE];
        All other LOGFONT properties is ignored.
  */
  static const ON_Font* GetManagedFontFromWindowsLogfont(
    int map_mode,
    HDC hdc,
    const LOGFONT& logfont
    );

  enum : int
  {
    MAP_MODE_ZERO_ERROR_SUPPRESS = MM_MAX + 3
  };
#endif

  ON_DEPRECATED_MSG("Use ON_Font::GetManagedFontFromPostScriptName()")
  static const ON_Font* GetManagedFontFromAppleFontName(
    const char* postscript_name
    );

  ON_DEPRECATED_MSG("Use ON_Font::GetManagedFontFromPostScriptName()")
  static const ON_Font* GetManagedFontFromAppleFontName(
    const wchar_t* postscript_name
    );

  /*
  Parameters:
    postscript_name - [in]
      Windows: PostScript name = IDWriteFont.GetInformationalStrings(DWRITE_INFORMATIONAL_STRING_POSTSCRIPT_NAME,...)
      Apple: PostScript name = CTFontCopyPostScriptName() / NSFont.fontName
  */
  static const ON_Font* GetManagedFontFromPostScriptName(
    const char* postscript_name
    );

  /*
  Parameters:
    postscript_name - [in]
      Windows: PostScript name = IDWriteFont.GetInformationalStrings(DWRITE_INFORMATIONAL_STRING_POSTSCRIPT_NAME,...)
      Apple: PostScript name = CTFontCopyPostScriptName() / NSFont.fontName
  */
  static const ON_Font* GetManagedFontFromPostScriptName(
    const wchar_t* postscript_name
    );

#if defined(ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)
  static const ON_Font* GetManagedFontFromAppleCTFont(
    CTFontRef apple_font,
    bool bAnnotationFont
    );
#endif

//#if defined(ON_RUNTIME_APPLE_OBJECTIVE_C_AVAILABLE)
//  static const ON_Font* GetManagedFontFromAppleNSFont(
//    NSFont* apple_font,
//    bool bAnnotationFont
//    );
//#endif

  /*
  Returns:
    The managed font for this font. 
  Remarks:
    If this->IsManagedFont() is true, then "this" is returned.
  */
  const ON_Font* ManagedFont() const;

  /*
  Description:
    It is better to call ON_Font::FontFromRichTextProperties().
  Parameters:
    rtf_font_name - [in]
      Rich text format name. This name is not well defined and depends on
      the device and application that created the rich text. On Windows this
      is often a LOGFONT.lfFaceName. On MacOS it is often a PostScript name.

    bRtfBold - [in]
      RTF bold flag

    bRtfItalic - [in]
      RTF italic flag
  Returns:
    A managed font to use for these rich text properties.
  */
  ON_DEPRECATED_MSG("Call ON_Font::FontFromRichTextProperties()")
  static const ON_Font* ManagedFontFromRichTextProperties(
    const wchar_t* rtf_font_name,
    bool bRtfBold,
    bool bRtfItalic,
    bool bRftUnderlined,
    bool bRftStrikethrough
  );

  static const ON_wString RichTextPropertiesToString(
    bool bRtfBold,
    bool bRtfItalic,
    bool bRtfUnderlined,
    bool bRtfStrikethrough
  );

  static const ON_wString RichTextPropertiesToString(
    ON_Font::Weight rtf_weight,
    ON_Font::Style rtf_style,
    bool bRtfUnderlined,
    bool bRtfStrikethrough
  );

  static const ON_wString RichTextPropertiesToString(
    const ON_Font* font
  );

  /*
  Returns:
    The list of managed fonts in a class with lots of searching tools.
  */
  static const class ON_FontList& ManagedFontList();

  /*
  Description:
    Look for a font installed on the current device that matches this font.
    The Strikethrough, Underlined, and PointSize properties are ignored.
  Parameters:
    bAllowBestMatch - [in]
      If no exact match is available and bAllowBestMach is true and
      there are installed fonts with a matching family name,
      then the best match in the family is returned.
  Returns:
    If there is a matching installed font, it is returned.
    Otherwise, nullptr is returned.
  */
  const ON_Font* InstalledFont(
    bool bAllowBestMatch
  ) const;

  /*
  Parameters:
    desired_weight - [in]
      Pass ON_Font::Weight::Unset if you do not want to change the weight.
    desired_stretch - [in]
      Pass ON_Font::Stretch::Unset if you do not want to change the stretch.
    desired_style - [in]
      Pass ON_Font::Style::Unset if you do not want to change the style.

  Returns:
    The installed font in the same family as this with the best match
    for the desired weight, stretch, and style.
    If nothing close to suitable is available, nullptr is returned.
  */
  const ON_Font* InstalledFamilyMemberWithWeightStretchStyle(
    ON_Font::Weight desired_weight,
    ON_Font::Stretch desired_stretch,
    ON_Font::Style desired_style
  ) const;


  /*
  Parameters:
    desired_weight - [in]
      Pass ON_Font::Weight::Unset if you do not want to change the weight.
    desired_stretch - [in]
      Pass ON_Font::Stretch::Unset if you do not want to change the stretch.
    desired_style - [in]
      Pass ON_Font::Style::Unset if you do not want to change the style.
    bUnderlined - [in]
    bStrikethrough - [in]

  Returns:
    The installed font in the same family as this with the best match
    for the desired weight, stretch, and style.
    If nothing close to suitable is available, nullptr is returned.
  */
  const ON_Font* ManagedFamilyMemberWithWeightStretchStyle(
    ON_Font::Weight desired_weight,
    ON_Font::Stretch desired_stretch,
    ON_Font::Style desired_style,
    bool bUnderlined,
    bool bStrikethrough
  ) const;

  /*
  Parameters:
    bBold - [in]
      True for the rich text quartet "bold face" with is typically heavier than the "regular" face.
    bItalic - [in]
      True for the rich text quartet "italic" with is typically more slanted than the "regular" face.
    bUnderlined - [in]
      True for an underlined face
    bStrikethrough - [in]
      True for a strikethrough face
  Returns:
    ON_Font::ManagedFontFromRichTextProperties(this->RichTextName(),bBold,bItalic,bUnderlined,bStrikethrough);
  */
  const ON_Font* ManagedFamilyMemberWithRichTextProperties(
    bool bBold,
    bool bItalic,
    bool bUnderlined,
    bool bStrikethrough
  ) const;

  /*
  Returns:
    The list of installed fonts in a class with lots of searching tools.
  */
  static const class ON_FontList& InstalledFontList();

  /*
  Description:
    Tests InstalledFontList().
  Parameters:
    text_log - [in]
      Summary of the test.
      If errors are detected, they are printed in error_log.
  Returns:
    true: Test passed - no errors detected.
    false: Test failed.
  */
  static bool TestInstalledFontList(
    class ON_TextLog& text_log
  );
  
  /*
  Description:
    This is the best way to get a font from rich text properties.
  Parameters:
    rich_text_font_name - [in]
      Rich text quartet name. If you have an ON_Font, then ON_Font.RichTextName()
      gets a good choice for this name.
      * For Windows installed fonts, this is identical to the Windows LOGFONT.lfFaceName.
      * For MacOS this is an invented name and is chosen to work cross platform as well
      as possible. For Apple families with up to 4 faces that align with the rich text
      quartet "regular/bold/italic/bold-italic" faces, things tend to work as expected.
      for common Apple families like Helvetica Neue with a dozen or so faces that are
      designed to  work well for western european languages, opennurbs selects 4 faces in
      the family that tend to align with would many people expect as the rich text
      "regular/bold/italic/bold-italic" face. Things get dicier with less common
      families and fonts designed for non-western european languages.
      Basically, Apple and richt text do not play nicely together.

    bBoldQuartetMember - [in]
      True to select the heavier members of the rich text quartet.

    bItalicQuartetMember - [in]
      True to select the more slanted memmers of the rich text quartet.

    bUnderlined - [in]
      True if you want underlined text.
      (Underlining is created as a rendering effect and not a separate face.)

    bStrikethrough - [in]
      True if you want strikethrough text.
      (Strikethrough is created as a rendering effect and not a separate face.)

  Returns:
    If there is an installed font, it is returned. Otherwise a managed font
    is returned. When the managed font is not installed, the corresponding
    member of ON_Font::Default::InstalledQuartet() is used to render the font.
  */
  static const ON_Font* FontFromRichTextProperties(
    ON_wString rich_text_font_name,
    bool bBoldQuartetMember,
    bool bItalicQuartetMember,
    bool bUnderlined,
    bool bStrikethrough
  );


private:
  // this must be a managed or installed font.
  const ON_Font* Internal_DecoratedFont(
    bool bUnderlined,
    bool bStrikethrough
  ) const;

public:

  /*
  Description:
    Unless you are certain you want to restrict your choices to installed fonts,
    it is better to call ON_Font::FontFromRichTextProperties().
  Parameters:
    rtf_font_name - [in]
      Rich text quartet neame. This name is not well defined and depends on
      the device and application that created the rich text. For Windows installed
      fonts, this is identical to the Windows LOGFONT.lfFaceName. 
      On MacOS this is a name Rhino cooks up and is chosen to
      work cross platform as well as possible. Apple and richt text do not
      play nicely together.
    bRtfBold - [in]
      True to prefer the heavier memmbers of the installed rich text quartet.
    bRtfItalic - [in]
      True to prefer the more slanted memmbers of the installed rich text quartet.
  Returns:
    An installed font to use for this rich text face font or nullptr if the current
    device does not have a in installed font with for this rich text quartet.
  */
  static const ON_Font* InstalledFontFromRichTextProperties(
    const wchar_t* rtf_font_name,
    bool bRtfBold,
    bool bRtfItalic
  );

  /*
  Description:
    Returns the glyph informationh for used to render a specific code point
  Parameters:
    unicode_code_point 
      UNICODE code point value
  Returns:
    Glyph rendering information.

  Remarks:
    Typically the returned glyph uses is a single glyph in this->ManagedFont().
    In this case, glyph->SubstitueCount() is 0.

    In some cases one or more glyphs from one or more substitute fonts are required
    to render the code point.  In this case, glyph->SubstitueCount() is 0.

  Example:
    ON_Font* font = ...;
    unsigned int code_point = ...;
    const ON_FontGlyph* g = font->CodePointGlyph(code_point);
    if (nullptr != g )
    {
      if ( g->SubstituteCount() > 0 )
      {
        // complicate case - one of more substitutes must be rendered to render g
        for ( const ON_FontGlyph* gsub = g.NextSubstitute(); nullptr != gsub; gsub = gsub->NextSubstitute() )
        {
          ...
        }
      }
      else
      {
        // simple case - this computer can directly render g
        ...
      }
    }
  */
  const class ON_FontGlyph* CodePointGlyph(
    ON__UINT32 unicode_code_point
  ) const;

private:
  friend class ON_FontGlyph;
  friend class ON_FontList;
  const class ON_FontGlyph* Internal_ManagedCodePointGlyph(
    ON__UINT32 unicode_code_point,
    bool bCreateIfMissing,
    bool bFindSubstitutes
  ) const;

public:

  /*
  Description:
    When reading version 5 3dm achives, the font description can be
    a generic font description or an Apple font name. This function
    rejects certain descriptions like "Default" and "Arial" for
    use as Apple font names.
  */
  static bool IsNotAppleFontName(
    const wchar_t* font_description
    );

  static const ON_Font* GetManagedFont(
    const ON_Font& font_characteristics,
    bool bCreateIfNotFound
    );

  /*
  Returns:
    If there is a managed font with the specified serial number, it is returned.
    Otherwise, nullptr is returned.
  */
  static const ON_Font* GetManagedFontFromSerialNumber(
    unsigned int managed_font_runtime_serial_number
    );

  /*
  Parameters:
    managed_fonts - [out]
      The current list of managed fonts.
  Returns:
    Number of managed fonts.
  */
  static unsigned int GetManagedFontList(
    ON_SimpleArray< const ON_Font* >& managed_fonts
    );

  /*
  Parameters:
    installed_fonts - [out]
      A list of all fonts available on the current computer
      sorted by font family name.
  Returns:
    Number of fonts available on the current computer.
  */
  static unsigned int GetInstalledFontList(
    ON_SimpleArray< const ON_Font* >& installed_fonts
    );

  /*
  Parameters:
    font_family_name - [in]
      A font family name like Arial or Helvetica.
    bIncludePartialMatch - [in]
      If true, family names that begin with font_family_name
      will be included.
    installed_fonts - [out]
      A list of all fonts available on the current computer
      with a matching font family name.
  Returns:
    Number of fonts available on the current computer.
  */
  static unsigned int GetInstalledFontFamily(
    const wchar_t* font_family_name,
    ON_SimpleArray< const ON_Font* >& installed_fonts
    );

  /*
  Parameters:
    font_list - [in]
      Fonts to search for a match. All fonts in this list
      are tested (search time is proportional to font_list.Count()).
      If the list returned by GetInstalledFontFamily() contains
      reasonable options, it is a good choice for the font_list[] 
      parameter.
  Returns:
    A pointer to the font in font_list[] that is the best
    match to this.
  */
  const ON_Font* BestMatch(
    const ON_SimpleArray< const ON_Font* >& font_list
  ) const;

  /*
  Parameters:
    font_list - [in]
      Fonts to search for a match. All fonts in this list
      are tested (search time is proportional to font_list.Count()).
      If the list returned by GetInstalledFontFamily() contains
      reasonable options, it is a good choice for the font_list[] 
      parameter.
    font_count - [in]
      Number of elements in the font_list[] array.
  Returns:
    A pointer to the font in font_list[] that is the best
    match to this.
  */
  const ON_Font* BestMatch(
    ON_Font const*const* font_list,
    size_t font_count
  ) const;
    
  static unsigned int WeightStretchStyleDeviation(
    ON_Font::Weight prefered_weight,
    ON_Font::Stretch prefered_stretch,
    ON_Font::Style prefered_style,
    ON_Font::Weight available_weight,
    ON_Font::Stretch available_stretch,
    ON_Font::Style available_style
  );

  static unsigned int WeightStretchStyleDeviation(
    ON_Font::Weight prefered_weight,
    ON_Font::Stretch prefered_stretch,
    ON_Font::Style prefered_style,
    const ON_Font* available_font
  );

  static unsigned int WeightStretchStyleDeviation(
    const ON_Font* prefered_weight_stretch_style,
    const ON_Font* available_font
  );
    
  static unsigned int UnderlinedStrikethroughDeviation(
    bool bPreferedUnderline,
    bool bPreferedStrikethrough,
    bool bAvailableUnderline,
    bool bAvailableStrikethrough
  );

  static unsigned int UnderlinedStrikethroughDeviation(
    bool bPreferedUnderline,
    bool bPreferedStrikethrough,
    const ON_Font* available_font
  );

  static unsigned int UnderlinedStrikethroughDeviation(
    const ON_Font* prefered_underlined_strikethrough,
    const ON_Font* available_font
  );
    
  static unsigned int RichTextPropertyDeviation(
    bool bPreferedRtfBold,
    bool bPreferedItalic,
    bool bPreferedUnderline,
    bool bPreferedStrikethrough,
    bool bAvailableRtfBold,
    bool bAvailableItalic,
    bool bAvailableUnderline,
    bool bAvailableStrikethrough
  );
    
  static unsigned int RichTextPropertyDeviation(
    bool bPreferedRtfBold,
    bool bPreferedItalic,
    bool bPreferedUnderline,
    bool bPreferedStrikethrough,
    const ON_Font* available_font
  );

private:
  static const ON_Font* Internal_BestMatchWeightStretchStyle(
    ON_Font::Weight prefered_weight,
    ON_Font::Stretch prefered_stretch,
    ON_Font::Style prefered_style,
    ON_Font const*const* font_list,
    size_t font_count
  );

public:

  /*
  Returns:
    True if this font is a managed font returned by one of the
    static ON_Font::GetManagedFont(...) functions.
  Remarks:
    ON_Font::Default is managed.
  */
  bool IsManagedFont() const;

  /*
  Returns:
    True if this is a managed font and the font is installed on this device.
    False otherwise.
  Remarks:
    If this->IsManagedFont() is true, then exactly one of IsManagedInstalledFont() 
    or IsManagedSubstitutedFont() is true.
    When this->IsManagedInstalledFont() is true, this->InstalledFont() returns the installed font.
  */
  bool IsManagedInstalledFont() const;

  /*
  Returns:
    True if this font is a managed font that references a font that is not installed on this computer.
  Remarks:
    If this->IsManagedFont() is true, then exactly one of IsManagedInstalledFont()
    or IsManagedSubstitutedFont() is true.
    When this->IsManagedSubstitutedFont() is true, this->SubstituteFont() returns the installed font.
  */
  bool IsManagedSubstitutedFont() const;

  /*
  Returns:
    If this font is a managed font that references a font that is not installed on this computer,
    then a pointer to the installed font that is the substitute for the missing font is returned.
    Otherwise nullptr is returned.
  */
  const ON_Font* SubstituteFont() const;
  
  /*
  Returns:
    True if this font is a mangaged font with a face that is installed on the current device
    or this is an installed font returned by a function like ON_Font::InstalledFont(), 
    ON_Font::GetInstalledFontFamily(), or ON_Font::GetInstalledFontList(). 
    False in all other cases.
  */
  bool IsInstalledFont() const;

private:
  const ON_Font* Internal_ManagedFontToInstalledFont() const;

public:
  ON_Font();
  ~ON_Font() = default;
  ON_Font(const ON_Font& src);
  ON_Font& operator=(const ON_Font& src);

public:
  /*
  Description:
    Create a font with a specified facename and properties.
  Parameters:
    gdi_logfont_name - [in]
      Windows LOGFONT.lfFaceName.
    bBold - [in]
      True for a bold version of the font.
    bItalic - [in]
      True for an italic version of the font.
  Returns:
    True if the font characteristics were valid and set on the font.
 */
  bool SetFontCharacteristics( 
    const wchar_t* gdi_logfont_name,
    bool bBold,
    bool bItalic,
    bool bUnderlined,
    bool bStrikethrough
    );

  /*
  Description:
    Create a font with a specified facename and properties.
  Parameters:
    point_size - [in]
      If point_size > 0.0, then it specifies which size of font definition
      should be used. Otherwise the font size used for annotation text
      is used.
      For high quality fonts it is generally the case that
      different point sizes of the same font face have
      subtle differences in glyph design and are not
      simply scaled versions of a base glyph.
    face_name - [in]
      Windows LOGFONT.lfFaceName value.
    bBold - [in]
      True for a bold version of the font.
    bItalic - [in]
      True for an italic version of the font.
  Returns:
    True if the font characteristics were valid and set on the font.
 */
  bool SetFontCharacteristics( 
    double point_size,
    const wchar_t* gdi_logfont_name,
    bool bBold,
    bool bItalic,
    bool bUnderlined,
    bool bStrikethrough
    );

  /*
  Description:
    Set the font's face name and characteristics.
  Parameters:
    gdi_logfont_name - [in]
      Windows LOGFONT.lfFaceName value.
  Returns:
    True if the font characteristics were valid and set on the font.
 */  
  bool SetFontCharacteristics( 
    const wchar_t* gdi_logfont_name,
    ON_Font::Weight font_weight,
    ON_Font::Style font_style,
    ON_Font::Stretch font_stretch,
    bool bUnderlined,
    bool bStrikethrough
    );

  bool SetFontCharacteristics( 
    double point_size,
    const wchar_t* gdi_logfont_name,
    ON_Font::Weight font_weight,
    ON_Font::Style font_style,
    ON_Font::Stretch font_stretch,
    bool bUnderlined,
    bool bStrikethrough
    );

  bool SetFontCharacteristics( 
    const wchar_t* gdi_logfont_name,
    ON_Font::Weight font_weight,
    ON_Font::Style font_style,
    ON_Font::Stretch font_stretch,
    bool bUnderlined,
    bool bStrikethrough,
    double linefeed_ratio,
    unsigned int logfont_charset
    );

  bool SetFontCharacteristics(
    double point_size,
    const wchar_t* gdi_logfont_name,
    ON_Font::Weight font_weight,
    ON_Font::Style font_style,
    ON_Font::Stretch font_stretch,
    bool bUnderlined,
    bool bStrikethrough,
    double linefeed_ratio,
    unsigned int logfont_charset
  );

  bool SetFontCharacteristicsForExperts(
    double point_size,
    const ON_wString postscript_name,
    const ON_wString quartet_name,
    ON_FontFaceQuartet::Member quartet_member,
    const ON_wString family_name,
    const ON_wString face_name,
    ON_Font::Weight font_weight,
    ON_Font::Style font_style,
    ON_Font::Stretch font_stretch,
    bool bUnderlined,
    bool bStrikethrough,
    unsigned char logfont_charset,
    int windows_logfont_weight,
    double apple_font_weight_trait,
    ON_PANOSE1 panose1
  );


  /*
  Description:
    The font properties weight, style, stretch, underlined, 
    and strikethrough are encoded in the returned value.
  Remarks:
    This is a legacy value used in 3dm archive reading/writing 
    and some sorting operations.
  */
  unsigned int FontCharacteristicsAsUnsigned() const;

private:
  /*
  Description:
    All font characteristics defined by the input parameters are encoded 
    in the returned value.
  Remarks:
    Used in 3dm archive reading/writing.
  */
  static unsigned int Internal_FontCharacteristicsAsUnsigned(
    ON_Font::Weight font_weight,
    ON_Font::Style font_style,
    ON_Font::Stretch font_stretch,
    bool bUnderlined,
    bool bStrikethrough
    );
    
  /*
  Description:
    All font characteristics except facename (weight, style, stretch, 
    underlined, strikethrough, charset) are encoded in the returned
    value.
  Parameters:
    font_characteristics_as_unsigned - [in]
    Value returned from ON_Font.FontCharacteristicsAsUnsigned()
  Returns:
    True if the characteristics were set.
  Remarks:
    Used in 3dm archive reading/writing.
  */
  bool Internal_SetFontCharacteristicsFromUnsigned(
    unsigned int font_characteristics_as_unsigned
    );

  static void Internal_GetFontCharacteristicsFromUnsigned(
    unsigned int font_characteristics_as_unsigned,
    ON_Font::Weight& font_weight,
    ON_Font::Stretch& font_stretch,
    ON_Font::Style& font_style,
    bool& bUnderlined,
    bool& bStrikethrough
    );

public:
  /*
  Description:
    Returns a 32-bit crc of the font weight, style, stretch, underline, strikethrough, 
    and WIndows logfont name characteristics.

  Parameters:
    bIgnoreWindowsLogfontNameOrdinalCase - [in]
      If true, ON_wString::MapStringOrdinal() is applied to the windows logfont name
      and the returned CRC is ordinal case independent.
  */
  ON__UINT32 CRC32(
    bool bIgnoreNameOrdinalCase
    ) const;

public:
// BUSTED #pragma region RH_BUSTED_C_SHARED_ENUM [ON_Font::NameLocale] [Rhino.DocObjects.Font.NameLocale] [nested:byte]
  /// <summary>
  /// ON_Font::NameLocale selects what locale is used for font name (PostScript, family, face, LOGFONT) queries.
  /// </summary>
  enum class NameLocale : ON__UINT8
  {
    ///<summary>
    /// If the localalized name is not empty, return it. Otherwise return the en-us name.
    ///</summary>
    LocalizedFirst = 0,

    ///<summary>
    /// Localized name.
    ///</summary>
    Localized = 1,

    ///<summary>
    /// en-us name.
    ///</summary>
    English = 2
  };
// BUSTED #pragma endregion

  /*
  Returns:
    Locale for the font localized font names.
  */
  const ON_wString Locale() const;

  /*
  Returns:
    The font's PostScript name.
  Remarks:
    The PostScript name is not always unique for each face. For example,
    OpenType variable fonts like Windows 10 Bahnschrift have "Bahnschrift"
    as the PostScript name for at least 10 different Bahnschrift faces.

    Platform equivalents:
    Apple: = CTFontCopyPostScriptName(...) / NSFont.fontName
    Windows: = IDWriteFont.GetInformationalStrings(DWRITE_INFORMATIONAL_STRING_POSTSCRIPT_NAME,...)
  */
  const ON_wString PostScriptName(
    ON_Font::NameLocale name_locale
  ) const;

  /*
  Returns:
    ON_Font::PostScriptName(ON_Font::NameLocale::LocalizedFirst)
  */
  const ON_wString PostScriptName() const;
  
  /*
  Returns:
    The font's family name.
  Remarks:
    Typically a font family has many faces.

    Platform equivalents:
    Apple: = CTFontCopyFamilyName(...) / NSFont.familyName
    Windows: = IDWriteFontFamily.GetFamilyNames()

    NOTE WELL: This is NOT the Windows LOGFONT lfFaceName.
  */
  const ON_wString FamilyName(
    ON_Font::NameLocale name_locale
  ) const;

  /*
  Returns:
    ON_Font::FamilyName(ON_Font::NameLocale::LocalizedFirst)
  */
  const ON_wString FamilyName() const;
  
  /*
  Returns:
    The font's face name.
  Remarks:
    Typically a font family has many faces and the face name gives a clue about the
    weight, stretch, and style of the face.
    
    For example, Arial is a common font family that often includes faces like
    "Regular", "Bold", "Italic", "Bold Italic", 
    "Narrow", "Narrow Bold", "Narrow Italic", "Narrow Bold Italic", 
    "Black", and "Black Oblique".

    Platform equivalents:
    Apple: = not available
    Windows: = IDWriteFontFamily.GetFaceNames()

    NOTE WELL: This is NOT the Windows LOGFONT lfFaceName.
  */
  const ON_wString FaceName(
    ON_Font::NameLocale name_locale
  ) const;

  /*
  Returns:
    ON_Font::FaceName(ON_Font::NameLocale::LocalizedFirst)
  */
  const ON_wString FaceName() const;

  
  /*
  Returns:
    The font's Windows GDI LOGFONT.lfFaceName.
  Remarks:
    This name is preserved so Rhino can write early version files and
    so some old code can use Windows GDI tools. 
    Every effort should be made to avoid using Windows LOGFONT lfFaceName.
  */
  const ON_wString WindowsLogfontName(
    ON_Font::NameLocale name_locale
  ) const;

  /*
  Returns:
    ON_Font::WindowsLogfontName(ON_Font::NameLocale::LocalizedFirst)
  */
  const ON_wString WindowsLogfontName() const;

  /*
  Description:
    On non-WIndows platforms like Mac OS, iOS, and Android, this function can
    be used to generate fake windows logfont names. 
    For fonts that have at most 4 faces with the same stretch and variations
    in weight and slant, the  family_name is a good choice. 
    For fonts that have many faces, like Helvetica Neue on Mac OS,
    this function will generate names that act like a Windows LOGFONT name
    for use in archaic name + regular/bold/italic/bold-italic font selection
    user interfaces.
  Returns:
    A fake windows logfont name.
  */
  static const ON_wString FakeWindowsLogfontNameFromFamilyAndPostScriptNames(
    ON_wString family_name,
    ON_wString postscript_name
  );

  /*
  Returns:
     Name of the quartet for this font. See ON_FontFaceQuartet for more details.
  */
  const ON_wString QuartetName(
    ON_Font::NameLocale name_locale
  ) const;

  /*
  Returns:
    Name of the quartet for this font. See ON_FontFaceQuartet for more details.
  */
  const ON_wString QuartetName() const;

  /*
  Returns:
    If known, this font's quartet face (regular, bold, italic, bold-italic).
    Otherwise ON_FontFaceQuartet::Member::Unset
  Remarks:
    For Windows installed fonts, the LOGFONT partition determines the quartet face.
    On Apple platforms, opennurbs uses a table for common fonts and leaves the rest unset.
    When unset, this is the best way to determine which quartet member this font represents.
    In all cases, the absolute weight or the ON_Font.IsBold() is unreliable and should
    be avoided at all costs.
  */
  ON_FontFaceQuartet::Member QuartetFaceMember() const;

  /*
  Description:
    Get a string like "Arial (Regular)" that describes this font's quartet.
  Returns:
    quartet name + (face)
  */
  const ON_wString QuartetDescription() const;

  /*
  Returns:
    A long description that includes family, face, weight, stretch and style information. 
    Generally not useful for finding matching fonts.
  Remarks:
    Calls
    ON_Font.Description(ON_Font::NameLocale::localizeFirst, ON_wString::HyphenMinus,ON_wString::Space,true)
  */
  const ON_wString Description() const;

  const ON_wString WidthWeightSlantDescription() const;

  static const ON_wString WidthWeightSlantDescription(ON_Font::Stretch width, ON_Font::Weight weight, ON_Font::Style slant);


  /*
  Description:
    Get a text description with family weight, width (stretch), slope (style).
  Parameters:
    family_separator - [in]
      character to place after family name in the description.
      0 = no separator.
      0, ON_wSting::HyphenMinus, and ON_wString::Space are common choices.
    weight_width_slope_separator - [in]
      character to place bewtween weight, stretch, and style descriptions
      0 = no separator.
      0, ON_wSting::HyphenMinus, and ON_wString::Space are common choices.
    bIncludeUndelinedAndStrikethrough - [in]
      If true, underlined and strikethrough attributes are appended
      0 = no separator.
      0, ON_wSting::HyphenMinus, and ON_wString::Space are common choices.
  Returns:
    A font description with family name, weight, stretch, and style. 
    If present, the weight, stretch, style, underlined, and strikethrough
    descriptions begin with a  capital letter followed by lowercase letters.
  Remarks:
    A description similar to the PostScript name is returned by
    DescriptionFamilyWeightStretchStyle(ON_wString::HyphenMinus,0,false).
    However, this often differs from the actual PostScript name.
  */
  const ON_wString Description(
    ON_Font::NameLocale name_local,
    wchar_t family_separator,
    wchar_t weight_width_slope_separator,
    bool bIncludeUndelinedAndStrikethrough
  ) const;



  /*
  Description:
    Get a text description with family weight, width (stretch), slope (style).
  Parameters:
    family_separator - [in]
      character to place after family name in the description.
      0 = no separator.
      0, ON_wSting::HyphenMinus, and ON_wString::Space are common choices.
    weight_width_slope_separator - [in]
      character to place bewtween weight, stretch, and style descriptions
      0 = no separator.
      0, ON_wSting::HyphenMinus, and ON_wString::Space are common choices.
    bIncludeUndelinedAndStrikethrough - [in]
      If true, underlined and strikethrough attributes are appended
      0 = no separator.
      0, ON_wSting::HyphenMinus, and ON_wString::Space are common choices.
    bIncludeNotOnDevice - [in]
      If true and this->IsManagedSubstitutedFont() is true, then the
      returned string begins with "[Not on device]" followed by the font's
      description.
  Returns:
    A font description with family name, weight, stretch, and style.
    If present, the weight, stretch, style, underlined, and strikethrough
    descriptions begin with a  capital letter followed by lowercase letters.
  Remarks:
    A description similar to the PostScript name is returned by
    DescriptionFamilyWeightStretchStyle(ON_wString::HyphenMinus,0,false).
    However, this often differs from the actual PostScript name.
  */
  const ON_wString Description(
    ON_Font::NameLocale name_local,
    wchar_t family_separator,
    wchar_t weight_width_slope_separator,
    bool bIncludeUndelinedAndStrikethrough,
    bool bIncludeNotOnDevice
  ) const;

private:
  static const ON_wString& Internal_GetName(
    ON_Font::NameLocale name_locale,
    const ON_wString& localized_name,
    const ON_wString& english_name
  );


#if defined(ON_OS_WINDOWS_GDI)

public:
  /*
  Description:
    Get the scale factors for converting heights between 
    Windows device coordinates and Windows logical coordinates.

  Parameters:
    hdc - [in]
      Windows device context.
      The device context is used to get the conversion between device 
      and logical pixel heights. The Windows GDI functions
      DPtoLP(hdc,...) and LPtoDP(hdc,...) are used.

    device_to_logical_scale - [out]
      logical_height = device_to_logical_scale*device_height

    logical_to_device_scale - [out]
      device_height = logical_to_device_scale*logical_height
    
  Returns:
    True if successful.
    False otherwise. In the returned scale factors are set to 1.0.
  */
  static bool GetWindowsDeviceToLogicalHeightScales(
    HDC hdc,
    double* device_to_logical_scale,
    double* logical_to_device_scale
  );

  /*
  Description:
    Convert a character height in points to a Windows LOGFONT lfHeight value (negative number).

    The mapping mode determines the length unit system for the returned value.
    
    
    The Windows convention is to use negative lfHeight values to specify
    font character heights and positive height values to specify font cell heights.

    font cell height = font acsent + font descent.

    font character height = Cell height - internal leading.

  Parameters:
    map_mode - [in]
      If map_mode is 0, then ::GetMapMode(hdc) is called to get the mapping mode.
      Otherwised, map_mode must identify a Windows mapping mode
      (MM_TEXT, MM_LOMETRIC, MM_HIMETRIC, MM_LOENGLISH, MM_HIENGLISH, M_TWIPS).
      If map_mode = MM_TEXT (1), then hdc is used as described in the hdc parameter.

    hdc - [in]
      Windows device context.
      If map_mode is set and not MM_TEXT, then hdc is ignored.
      Otherwise the device context is used to get the mapping mode ( GetMapMode(hdc) ). 
      If the mapping mode is MM_TEXT, then the additional device context values
      GetDeviceCaps(hdc, LOGPIXELSY) and conversion between device and logical pixel heights
      DPtoLP(hdc,...) and LPtoDP(hdc,...) are used.

    point_size - [in]
      Font character height in points (1 point = 1/72 inch = 25.4/72 millimeters). 
      In terms of font metrics, character height = ascent + descent - internal leading.

  Returns:
    LOGFONT lfHeight value. 

    This value is always negative.

    The absolute value of the returned value
    = character height
    = ascent + descent - internal leading
    For many common fonts, the "character height" is close to the distance
    from the bottom of a lower case g to the top of an upper case M. 
    The internal leading is space reserved for diacritical marks like the
    ring above the A in the UNICODE "LATIN LETTER A WITH RING" U+00C5 glyph.
    Character height is also known as the "em height". 
    Note that the "em height" is typically larger than the height of the
    letter M because "em height" include descent.
  */
  static int WindowsLogfontCharacterHeightFromPointSize(
    int map_mode,
    HDC hdc,
    double point_size
  );

  /*
  Parameters:
    map_mode - [in]
      If map_mode is 0, then ::GetMapMode(hdc) is called to get the mapping mode.
      Otherwised, map_mode must identify a Windows mapping mode
      (MM_TEXT, MM_LOMETRIC, MM_HIMETRIC, MM_LOENGLISH, MM_HIENGLISH, M_TWIPS).
      If map_mode = MM_TEXT (1), then hdc is used as described in the hdc parameter.

    hdc - [in]
      Windows device context.
      If map_mode is set and not MM_TEXT, then hdc is ignored.
      Otherwise the device context is used to get the mapping mode ( GetMapMode(hdc) ). 
      If the mapping mode is MM_TEXT, then the additional device context values
      GetDeviceCaps(hdc, LOGPIXELSY) and conversion between device and logical pixel heights
      DPtoLP(hdc,...) and LPtoDP(hdc,...) are used.

    logfont_character_height - [in]
      This value must be a Windows LOGFONT character height in units
      determine from map_mode and hdc.  If you have a LOGFONT with positive
      lfHeight value, you must get the fonts TEXTMETRICS and subbr
    
  Returns:
    Character height in points (1 point = 1/72 inch).

   font character height = font ascent + font descent - font internal leading.

  Remarks:
    See ON_Font::PointSize() for information about point units,
    font character height, and font cell height.
  */
  static double PointSizeFromWindowsLogfontCharacterHeight(
    int map_mode,
    HDC hdc,
    int logfont_character_height
  );

  /*
  Description:
    Get a Windows LOGFONT character height 
    = -(TEXTMETRIC.tmAscent + TEXTMETRIC.tmDescent - TEXTMETRIC.tmLeading ) 
    as a negative integer.

  Parameters:
    map_mode - [in]
      The best results are obtained when map_mode = MM_TEXT and the hdc is
      correctly set for the context where the font is being rendered. Otherwise
      the loss of precision when length units system conversion scale factors 
      are applied and results are stored in int LOGFONT and TEXTMETRIC fields
      lead to discrepancies.

      If map_mode is 0, then ::GetMapMode(hdc) is called to get the mapping mode.
      Otherwised, map_mode must identify a Windows mapping mode
      (MM_TEXT, MM_LOMETRIC, MM_HIMETRIC, MM_LOENGLISH, MM_HIENGLISH, M_TWIPS).
      If map_mode = MM_TEXT (1), then hdc is used as described in the hdc parameter.

    hdc - [in]
      Windows device context.
      If map_mode is set and not MM_TEXT, then hdc is ignored.
      Otherwise the device context is used to get the mapping mode ( GetMapMode(hdc) ). 
      If the mapping mode is MM_TEXT, then the additional device context values
      GetDeviceCaps(hdc, LOGPIXELSY) and conversion between device and logical pixel heights
      DPtoLP(hdc,...) and LPtoDP(hdc,...) are used.

    logfont - [in]
      If logfont.lfHeight <= 0, then logfont.lfHeight is returned.
      If logfont.lfHeight > 0, then logfont face name, map_mode and hdc are 
      used to calculate the font's TEXTMETRICS tmInternalLeading value
      -((tm.tmAscent + tm.tmDescent) - tmInternalLeading) is returned.

  Returns:
    0: failure
    <0: Windows LOGFONT character height in units specified by map_mode and hdc.
  */
  static int WindowsLogfontCharacterHeight(
    int map_mode,
    HDC hdc,
    const LOGFONT& logfont
  );

  /*
  Description:
    Get a Windows LOGFONT cell height 
    = (TEXTMETRIC.tmAscent + TEXTMETRIC.tmDescent)
    as a positive integer.

  Parameters:
    map_mode - [in]
      The best results are obtained when map_mode = MM_TEXT and the hdc is
      correctly set for the context where the font is being rendered. Otherwise
      the loss of precision when length units system conversion scale factors 
      are applied and results are stored in int LOGFONT and TEXTMETRIC fields
      lead to discrepancies.

      If map_mode is 0, then ::GetMapMode(hdc) is called to get the mapping mode.
      Otherwised, map_mode must identify a Windows mapping mode
      (MM_TEXT, MM_LOMETRIC, MM_HIMETRIC, MM_LOENGLISH, MM_HIENGLISH, M_TWIPS).
      If map_mode = MM_TEXT (1), then hdc is used as described in the hdc parameter.

    hdc - [in]
      Windows device context.
      If map_mode is set and not MM_TEXT, then hdc is ignored.
      Otherwise the device context is used to get the mapping mode ( GetMapMode(hdc) ). 
      If the mapping mode is MM_TEXT, then the additional device context values
      GetDeviceCaps(hdc, LOGPIXELSY) and conversion between device and logical pixel heights
      DPtoLP(hdc,...) and LPtoDP(hdc,...) are used.

    logfont - [in]
      If logfont.lfHeight >= 0, then logfont.lfHeight is returned.
      If logfont.lfHeight < 0, then logfont face name, map_mode and hdc are 
      used to calculate the font's TEXTMETRIC and
      (tm.tmAscent + tm.tmDescent) is returned.

  Returns:
    0: failure
    >0: Windows LOGFONT cell height in units specified by map_mode and hdc.
  */
  static int WindowsLogfontCellHeight(
    int map_mode,
    HDC hdc,
    const LOGFONT& logfont
  );


  /*
  Description:
    Get a Windows text metrics.

  Parameters:
    map_mode - [in]
      The best results are obtained when map_mode = MM_TEXT and the hdc is
      correctly set for the context where the font is being rendered. Otherwise
      the loss of precision when length units system conversion scale factors 
      are applied and results are stored in int LOGFONT and TEXTMETRIC fields
      lead to discrepancies.

      If map_mode is 0, then ::GetMapMode(hdc) is called to get the mapping mode.
      Otherwised, map_mode must identify a Windows mapping mode
      (MM_TEXT, MM_LOMETRIC, MM_HIMETRIC, MM_LOENGLISH, MM_HIENGLISH, M_TWIPS).
      If map_mode = MM_TEXT (1), then hdc is used as described in the hdc parameter.

    hdc - [in]
      Windows device context.
      If map_mode is set and not MM_TEXT, then hdc is ignored.
      Otherwise the device context is used to get the mapping mode ( GetMapMode(hdc) ). 
      If the mapping mode is MM_TEXT, then the additional device context values
      GetDeviceCaps(hdc, LOGPIXELSY) and conversion between device and logical pixel heights
      DPtoLP(hdc,...) and LPtoDP(hdc,...) are used.

    logfont - [in]
      If logfont.lfHeight >= 0, then logfont.lfHeight is returned.
      If logfont.lfHeight < 0, then logfont face name, map_mode and hdc are 
      used to calculate the font's TEXTMETRIC and
      (tm.tmAscent + tm.tmDescent) is returned.

    textmetric - [out]

  Returns:
    0: failure
    >0: Windows LOGFONT cell height in units specified by map_mode and hdc.
  */
  static bool GetWindowsTextMetrics(
    int map_mode,
    HDC hdc,
    const LOGFONT& logfont,
    TEXTMETRIC& textmetric
  );

public:
  /*
  Example:
        HDC font_hdc = ON_Font::CreateWindowsLogfontDeviceContext();
        if ( nullptr != font_hdc )
        {
          ...
          Calls to Windows SDK font management functions needing an HDC
          ...
          ON_Font::DeleteWindowsLogfontDeviceContext(font_hdc);
        }

  Returns:
    Default HDC used for Windows GDI font management
  */
  static HDC CreateWindowsLogfontDeviceContext();

  /*
  Parameters:
    font_hdc - [in]
      HDC from call to ON_Font::CreateWindowsLogfontDeviceContext();
  */
  static void DeleteWindowsLogfontDeviceContext(
    HDC hdc
  );

public:  
  /*
  Description:
    Set ON_Font properties from a subset of the LOGFONT properties.
  Parameters:
    map_mode - [in]
      If logfont.lfHeight = 0, then map_mode is ignored. Otherwise ...
      If map_mode is 0, then ::GetMapMode(hdc) is called to get the mapping mode.
      Otherwise, map_mode must identify a Windows mapping mode
      (MM_TEXT, MM_LOMETRIC, MM_HIMETRIC, MM_LOENGLISH, MM_HIENGLISH, M_TWIPS).
      If map_mode = MM_TEXT (1), then hdc is used as described in the hdc parameter.
    hdc - [in]
      If logfont.lfHeight = 0 or map_mode is set and not MM_TEXT, then hdc is ignored.
      Otherwise the device context is used to get the mapping mode ( GetMapMode(hdc) ). 
      If the mapping mode is MM_TEXT, then the additional device context values
      GetDeviceCaps(hdc, LOGPIXELSY) and conversion between device and logical pixel heights
      DPtoLP(hdc,...) and LPtoDP(hdc,...) are used.
    logfont - [in]
      These logfont properties are used to set the ON_Font.
        lfHeight
        lfWeight
        lfItalic
        lfUnderline
        lfStrikeOut
        lfCharSet
        lfFaceName[LF_FACESIZE];
        All other LOGFONT properties are ignored.
  */
  bool SetFromWindowsLogFont(
    int map_mode,
    HDC hdc,
    const LOGFONT& logfont
    );


  /*
  Description:
    Use the Windows GDI EnumFontFamiliesEx tool to get a list of LOGFONTS.
  Parameters:
    logfont_list - [out]
  */
  static unsigned int GetInstalledWindowsLogFonts(
    ON_SimpleArray<LOGFONT>& logfont_list
  );

  /*
  Description:
    Use the Windows GDI EnumFontFamiliesEx tool to get a list of LOGFONTS.
  Parameters:
    preferedLocale - [in]
      If not empty, names from this locale will be preferred.
      If preferedLocale = L"GetUserDefaultLocaleName", then
      ::GetUserDefaultLocaleName will be used to set the preferedLocale.
    bIncludeSimulatedFontFaces - [in]
      True to include simulated font faces.
    bKeepDWriteFont - [in]
      If true, then bKeepDWriteFont.m_dwrite_font will be set and the caller
      is responsible for calling m_dwrite_font->Release().
    logfont_list - [out]
  */
  static unsigned int GetInstalledWindowsDWriteFonts(
    const wchar_t* preferedLocale,
    bool bIncludeSimulatedFontFaces,
    bool bKeepDWriteFont,
    ON_SimpleArray<ON_WindowsDWriteFontInformation>& dwrite_font_list
  );


  /*
  Parameters:
    map_mode - [in]
      If map_mode is 0, then ::GetMapMode(hdc) is called to get the mapping mode.
      Otherwised, map_mode must identify a Windows mapping mode
      (MM_TEXT, MM_LOMETRIC, MM_HIMETRIC, MM_LOENGLISH, MM_HIENGLISH, M_TWIPS).
      If map_mode = MM_TEXT (1), then hdc is used as described in the hdc parameter.
    hdc - [in]
      Windows device context.
      If map_mode is set and not MM_TEXT, then hdc is ignored.
      Otherwise the device context is used to get the mapping mode ( GetMapMode(hdc) ). 
      If the mapping mode is MM_TEXT, then the additional device context values
      GetDeviceCaps(hdc, LOGPIXELSY) and conversion between device and logical pixel heights
      DPtoLP(hdc,...) and LPtoDP(hdc,...) are used.
  Returns:
    A Windows LOGFONT with properties copied from this ON_Font.
    If WindowsLogFontIsComplete() is true, then all LOGFONT properties
    are copied from the ON_Font. 
    If WindowsLogFontIsComplete() is false, then the LOGFONT lfHeight,
    lfWidth, lfEscapement, lfOrientation, lfClipPrecision, lfQuality,
    lfPitchAndFamily, and lfOutPrecision properties are set to ON_Font
    default values.
  */
  const LOGFONT WindowsLogFont(
    int map_mode,
    HDC hdc
    ) const;

  const MAT2 WindowsFontMat2() const;

#endif


#if defined (ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)

public:
  /*
  Parameters:
    size - [in]
      If size is not > 0, then the size is set to units_per_em.
  */
  static CTFontRef AppleCTFontSetSize(
    CTFontRef original,
    CGFloat size,
    bool bReleaseOriginal
    );
    
  static unsigned int AppleCTFontUnitsPerEm(CTFontRef apple_font);
    
  bool SetFromAppleCTFont (
    CTFontRef apple_font,
    bool bAnnotationFont
    );
    
  /*
  Parameters
    bIsSubstituteFont - [out]
      true if the returned CTFontRef was a substitute automatically
      created by Mac OS.
  Returns:
    An Apple CTFontRef managed by the Apple platform.
    Do not delete this font.
  */
  CTFontRef AppleCTFont(
    bool& bIsSubstituteFont
  ) const;

  /*
  Parameters
    bIsSubstituteFont - [out]
      true if the returned CTFontRef was a substitute automatically
      created by Mac OS.
  Returns:
    An Apple CTFontRef managed by the Apple platform.
    Do not delete this font.
  */
  CTFontRef AppleCTFont(
    double point_size,
    bool& bIsSubstituteFont
  ) const;
    
  /*
  Parameters
    postscript_name - [in]
      PostScript name of the desired font
    point_size - [in]
    bIsSubstituteFont - [out]
      true if the returned CTFontRef was a substitute automatically
      created by Mac OS (failed to match postscript name).
  Returns:
    An Apple CTFontRef managed by the Apple platform.
    Do not delete this font.
  */
  static CTFontRef AppleCTFont(
    const wchar_t* postscript_name,
    double point_size,
    bool& bIsSubstituteFont
  );

    
  static const ON_wString AppleCTFontPostScriptName(
    CTFontRef apple_font
  );
    
  static const ON_wString AppleCTFontFamilyName(
    CTFontRef apple_font
  );
    

  /*
  Description:
    Apple CTFont, NSFont, and MacOS do not have "face names" as a font attribute.
    This is the "typeface" name shown in the Apple FontBook Application
    and the closest approximation to the Windows font face name.
    The value from CTFontCopyName(...,kCTFontStyleNameKey)
  */
  static const ON_wString AppleCTFontFaceName(
    CTFontRef apple_font
  );
    
  /*
  Description:
    The Apple display name is used in some Apple apps
    as a short description of the font.
    When working in MacOS, the PostScript name is most reliable
    way to uniquely identify a font.
  */
  static const ON_wString AppleCTFontDisplayName(
    CTFontRef apple_font
  );
    
  static ON_PANOSE1 AppleCTFontPANOSE1(
    CTFontRef apple_font
  );
    
#endif

#if defined (OPENNURBS_FREETYPE_SUPPORT)
public:
  /*
  Description:
    If opennurbs is built with FreeType support then
    FT_Face freetype_face = (FT_Face)ON_Font::FreeTypeFace(font)
    will return a FreeType face that can be used to render the font.
  Parameters:
    font - [in]
  Returns:
    A value that can be cast as a FreeType FT_Face.
  Example
    const ON_Font* font = ...;
    FT_Face freetype_face = (FT_Face)ON_Font::FreeTypeFace(font);
  Remarks:
    Many fonts do not have a glyph for a every UNICODE codepoint and font
    substitution is required. If you want to get the freetype face
    used for a specific UNICODE codepoint, call ON_Font::CodepointFreeTypeFace().
  */
  static ON__UINT_PTR FreeTypeFace(
    const ON_Font* font
  );
 
private:
  /*
  Description:
    Helper function used by destructor to deallocate memory used
    by FreeType face
  */
  static void DestroyFreeTypeFace(
    const ON_Font* font
  );

public:
  void DumpFreeType(
    ON_TextLog& text_log
  ) const;

public:
  static void DumpFreeTypeFace(
    ON__UINT_PTR free_type_face_ptr,
    ON_TextLog& text_log
  );
#endif

public:

  /*
  Parameters:
    postscript_name - [in]
      From CTFontCopyPostScriptName(...) / NSFont.fontName
  Remarks:
    The "Apple Font Name" is the PostScript font name in the 
    Mac OS "Font Book" application and in some other Apple documentation.
    It is CTFontCopyPostScriptName(...) / NSFont.fontName.
  */
  bool SetFromAppleFontName(
    const wchar_t* postscript_name
    );
  
  /*
  Parameters:
   postscript_name - [in]
     From CTFontCopyPostScriptName(...) / NSFont.fontName
    point_size - [in]
      Pass 0.0 for annotation fonts
  Remarks:
   The "Apple Font Name" is the PostScript font name in the
   Mac OS "Font Book" application and in some other Apple documentation.
   It is CTFontCopyPostScriptName(...) / NSFont.fontName.
  */
  bool SetFromAppleFontName(
    const wchar_t* postscript_name,
    double point_size
    );
  
  ON_DEPRECATED_MSG("Use ON_Font::PostScriptName(ON_Font::NameLocale)")
  const ON_wString& AppleFontName() const;
  
  ON_DEPRECATED_MSG("Use ON_Font::PostScriptName(ON_Font::NameLocale)")
  const wchar_t* AppleFontNameAsPointer() const;

  /*
  Returns:
    A pointer for immediate use in formatted printing as in
    FormattedPrint(L"PostScript name = \"&ls\"\n",font.PostScriptNameAsPointer());
  Remarks:
    WARNING: 
      Do not save this pointer for later use. 
      It points to memory in a dynamic string.
  */
  const wchar_t* PostScriptNameAsPointer() const;

  /*
  Description:
    Sets the ON_Font information from the platform font with the specified
    postscript_name.
  Parameters:
    postscript_name - [in]
    bAcceptPartialMatch - [in]
      If bAcceptPartialMatch is true, there is not a font on the device with a
      matching name, but there are fonts with names that have significant overlap,
      then the font with the best overlap is returned. 
      For example if "Arial-Black" is not present and "Arial-BoldMT" is present,
      then ON_Font.SetFromPostScriptName(L"Arial-Black",true) will return the
      font with PostScript name "Arial-BoldMT".
  Returns:
    True if the font was set.
  */
  bool SetFromPostScriptName(
    const wchar_t* postscript_name
  );

  /*
  Parameters:
    font_name - [in]
      A UTF-16 or UTF-32 encoded null terminated string.
    bStopAtHyphen - [in]
      If true, the hash calculation terminates at the first hyphen.
      This is useful when font_name is a PostScript name and you
      don't want to include face weight or style information in the hash.

      For example, if bStopAtHyphen is true, then the four PostScript names
      "Calibri", "Calibri-Bold", "Calibri-Italic", and "Calibri-BoldItalic" 
      have the same hash.

      There are some fonts where a hyphen is an integral part of the font face name.
      Examples include "Arial-Black", "AvenirLT-Roman", "MecSoftFont-1", "MS-Gothic",
      "MS-PGothic", "MS-UIGothic", "SLF-RHN-Architect", "SLF-RHN-Industrial", 
      "SLF-RHN-WhiteLiinen", and so on.
      These hyphens are exempt from the bStopAtHyphen check.
  Returns:
    A hash of the font_name parameter that ignores spaces, hyphens, underbars, and case.
    For example, the four names "Yu Gothic Regular", "YuGothic-Regular", 
    "YUGOTHICREGULAR", and "yugothicregular" have the same FontNameHash(). 
    The hash will be identical for UTF-16 and UTF-32 encodings.
  */
  static const ON_SHA1_Hash FontNameHash(
    const wchar_t* font_name,
    bool bStopAtHyphen
  );

  /*
  Description:
    Compare the font names ignoring hyphens, underbars, and spaces.
  Parameters:
    lhs - [in]
      font name to compare
    rhs - [in]
      font name to compare
  Returns:
    If ON_Font::FontNameHash(lsh,false) and ON_Font::FontNameHash(rsh,false) are equal,
    then 0 is returned.
    Otherwise ON_wString::CompareOrdinal(lhs,rhs,true) is returned.
  Remarks:
    Useful for sorting font names.
  */
  static int CompareFontName(
    const ON_wString& lhs,
    const ON_wString& rhs
  );

  /*
  Description:
    Compare the font names ignoring hyphens, underbars, and spaces.
  Parameters:
    lhs - [in]
      font name to compare
    rhs - [in]
      font name to compare
  Returns:
    If ON_Font::FontNameHash(lsh,false) and ON_Font::FontNameHash(rsh,false) are equal,
    then 0 is returned.
    Otherwise ON_wString::CompareOrdinal(lhs,rhs,true) is returned.
  Remarks:
    Useful for sorting font names.
  */
  static int CompareFontNameWideChar(
    const wchar_t* lhs,
    const wchar_t* rhs
  );

  /*
  Description:
    Compare the font names ignoring hyphens, underbars, and spaces.
  Parameters:
    lhs - [in]
      font name to compare
    rhs - [in]
      font name to compare
  Returns:
    If ON_Font::FontNameHash(lsh,false) and ON_Font::FontNameHash(rsh,false) are equal,
    then 0 is returned.
    Otherwise ON_wString::CompareOrdinal(lhs,rhs,true) is returned.
  Remarks:
    Useful for sorting font names.
  */
  static int CompareFontNamePointer(
    const ON_wString* lhs,
    const ON_wString* rhs
  );

  /*
  Description:
    Compare the font names ignoring hyphens, underbars, and spaces.
    Ignore portions of PostScript names after the hyphen that separates the 
    font family and font face. 
  Parameters:
    lhs - [in]
      font name to compare
    rhs - [in]
      font name to compare
  Returns:
    If ON_Font::FontNameHash(lsh,true) and ON_Font::FontNameHash(rsh,true) are equal,
    then 0 is returned.
    Otherwise ON_wString::CompareOrdinal(lhs,rhs,true) is returned.
  Remarks:
    Useful for sorting font names.
  */
  static int CompareFontNameToHyphen(
    const ON_wString& lhs,
    const ON_wString& rhs
  );

  /*
  Description:
    Compare the font names ignoring hyphens, underbars, and spaces.
    Ignore portions of PostScript names after the hyphen that separates the
    font family and font face.
  Parameters:
    lhs - [in]
      font name to compare
    rhs - [in]
      font name to compare
  Returns:
    If ON_Font::FontNameHash(lsh,true) and ON_Font::FontNameHash(rsh,true) are equal,
    then 0 is returned.
    Otherwise ON_wString::CompareOrdinal(lhs,rhs,true) is returned.
  Remarks:
    Useful for sorting font names.
  */
  static int CompareFontNameToHyphenPointer(
    const ON_wString* lhs,
    const ON_wString* rhs
  );

  /*
  Description:
    Compare the font names ignoring hyphens, underbars, and spaces.
    Ignore portions of PostScript names after the hyphen that separates the
    font family and font face.
  Parameters:
    lhs - [in]
      font name to compare
    rhs - [in]
      font name to compare
  Returns:
    If ON_Font::FontNameHash(lsh,true) and ON_Font::FontNameHash(rsh,true) are equal,
    then 0 is returned.
    Otherwise ON_wString::CompareOrdinal(lhs,rhs,true) is returned.
  Remarks:
    Useful for sorting font names.
  */
  static int CompareFontNameToHyphenWideChar(
    const wchar_t* lhs,
    const wchar_t* rhs
  );

  /*
  Parameters:
    dirty_font_name - [in]
      A UTF-16 or UTF-32 encoded null terminated string.
    map - [in]
      Map to apply
  Returns:
    The input name with all spaces and hyphens removed.
  */
  static const ON_String CleanFontName(
    const wchar_t* dirty_font_name,
    ON_StringMapOrdinalType map
  );

  /*
  Parameters:
    font - [in]
    bDefaultIfEmpty - [in]
      If true and font is nullptr or has empty names, then
      the rich text font name for ON_Font::Default is returned,
  Returns:
    Font name to use in rich text file fonttbl sections.
    {\\fonttbl...{\\fN <RichTextFontName>;}...}
  */
  static const ON_wString RichTextFontName(
    const ON_Font* font,
    bool bDefaultIfEmpty
  );

  /*
  Returns:
    ON_Font::RichTextFontName(this,false);
  Remarks:
    For Windows installed fonts, this is identical to the Windows LOGFONT name.
    For Apple platforms and rich text quartet names do not play nicely together.
  */
  const ON_wString RichTextFontName() const;

  /*
  Parameters:
    family_name - [in]
      The font family name. 
      
      This a name like "Arial".
      It is NOT a name like ArialMT, Arial-..., "Arial Black", "Arial Narrow", ...
      Generally, family names do NOT contain word that specify 
      weight (Bold, Light, Heavy, ...), 
      width (Medium, Condensed, ...), 
      or slope (Oblique, Italic, Upright).
      Generally, family names do NOT contain hyphens (like thos in PostScript names).

      Apple: = CTFontCopyFamilyName() / NSFont.familyName
      Windows: = IDWriteFontFamily.GetFamilyNames()
      NOTE WELL: GDI LOGFONT.lfFaceName is NOT a font family name.

      https://blogs.msdn.microsoft.com/text/2009/04/15/introducing-the-directwrite-font-system/
  */
  bool SetFamilyName(
    const wchar_t* family_name
  );

  /*
  Parameters:
    dirty_name - [in]
      A Windows GDI LOGFONT name or PostScript name.
  Returns:
    A family name
  */
  static const ON_wString FamilyNameFromDirtyName(
    const wchar_t* dirty_name
  );

  bool SetFromFontDescription(
    const wchar_t* font_description
    );

  bool SetFromFontDescription(
    const wchar_t* font_description,
    const wchar_t* postscript_name
    );

  /*
  Description:
    Tests an object to see if its data members are correctly
    initialized.
  Parameters:
    text_log - [in] if the object is not valid and text_log
        is not nullptr, then a brief englis description of the
        reason the object is not valid is appened to the log.
        The information appended to text_log is suitable for 
        low-level debugging purposes by programmers and is 
        not intended to be useful as a high level user 
        interface tool.
  Returns:
    @untitled table
    true     object is valid
    false    object is invalid, uninitialized, etc.
  */
  bool IsValid( ON_TextLog* text_log = nullptr ) const;

  void Dump( ON_TextLog& ) const; // for debugging

  
#if defined(ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)
  // Used to create installed fonts from Apple CTFont
  ON_Font(
    ON_Font::FontType font_type,
    const class ON_AppleCTFontInformation& apple_font_information
  );
#endif
  
  
#if defined(ON_OS_WINDOWS_GDI)
public:
  static void DumpLogfont(
    const LOGFONT* logfont,
    ON_TextLog& text_log
  );
  static void DumpTextMetric(
    const TEXTMETRIC* tm,
    ON_TextLog& text_log
  );

  bool SetFromWindowsDWriteFont (
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale
  );

private:
    ON_Font(
      ON_Font::FontType font_type,
      const class ON_WindowsDWriteFontInformation& dwrite_font_information
      );

public:

  struct IDWriteFont* WindowsDWriteFont() const;

  static const ON_wString PostScriptNameFromWindowsDWriteFont(
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale
  );

  // DWRITE_INFORMATIONAL_STRING_WEIGHT_STRETCH_STYLE_FAMILY_NAME
  static const ON_wString WeightStretchStyleModelFamilyNameFromWindowsDWriteFont(
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale
  );

  static const ON_wString Field_0_CopyrightFromWindowsDWriteFont(
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale
  );

  static const ON_wString Field_5_VersionFromWindowsDWriteFont(
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale
  );

  static const ON_wString Field_7_TrademarkFromWindowsDWriteFont(
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale
  );

  static const ON_wString Field_8_ManufacturerFromWindowsDWriteFont(
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale
  );

  static const ON_wString Field_9_DesignerFromWindowsDWriteFont(
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale
  );

  // Returns the description saved in field 10. 
  // Opennurbs searches the description saved in field 10 of the name table
  // for the strings "Engraving - single stroke" / "Engraving - double stroke" / "Engraving"
  // to identify fonts that are desgned for engraving (and which tend to render poorly when
  // used to display text devices like screens, monitors, and printers).
  // The SLF (single line fonts) are examples of fonts that have Engraving in field 10.
  static const ON_wString Field_10_DescriptionFromWindowsDWriteFont(
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale
  );

  static const ON_wString Field_11_VendorURLFromWindowsDWriteFont(
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale
  );

  static const ON_wString Field_12_DesignerURLFromWindowsDWriteFont(
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale
  );

  static const ON_wString Field_13_LicenseFromWindowsDWriteFont(
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale
  );

  static const ON_wString Field_14_LicenseURLFromWindowsDWriteFont(
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale
  );

  static const ON_wString Field_20_PostScriptCIDNameFromWindowsDWriteFont(
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale
  );

  /*
  Parameters:
    dwrite_font - [in]
    preferedLocale - [in]
      preferred local for strings (family name, font name, face name, postscript name, ...)
      A locale name often has the form "es-es", "en-us", ...
      Pass nullptr or empty string list all locales and use "en-us" as the preferred locale name.
      (Most modern fonts distributed with Windows 10 in all locales have en-us names).
      Pass "*..." if you want to list all locale names and specify a preferred locale.
      For example, "*es-es" will list all local names but use "es-es" as the preferedLocale.
    text_log - [in]
      destintion for the text description of the font.
  */
  static void DumpWindowsDWriteFont(
    struct IDWriteFont* dwrite_font,
    const wchar_t* preferedLocale,
    ON_TextLog& text_log
  );

#endif
  
#if defined (ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)
public:
  static void DumpCTFont(
    CTFontRef apple_font,
    ON_TextLog& text_log
  );
#endif

public:

  // serialize definition to binary archive
  bool Write( ON_BinaryArchive& ) const;

  // restore definition from binary archive
  bool Read( ON_BinaryArchive& );

  // V6 separated the V5 ON_Font into ON_TextStyle and ON_Font.
  bool WriteV5(
    int V5_font_index,
    ON_UUID V5_font_id,
    ON_BinaryArchive& 
    ) const;

  // V6 separated the V5 ON_Font into ON_TextStyle and ON_Font.
  bool ReadV5( 
    ON_BinaryArchive&, 
    int* V5_font_index,
    ON_UUID* V5_font_id
    );

  /*
  Returns:
        0: This is not a managed font.
        1: This is the managed font ON_Font::Default.
     >= 2: This is a managed font other than ON_Font::Default.
  Remark:
    For managed fonts other than ON_Font::Default, the value of RuntimeSerialNumber()
    typically varies between instances of the same application. 
    Different platforms and application versions may use different font faces for ON_Font::Default.
    If an ON_Font is a managed font, then RuntimeSerialNumber() and ManagedFontSerialNumber()
    are identical. If an ON_Font is not a managed font, then RuntimeSerialNumber() is zero.
  */
  unsigned int RuntimeSerialNumber() const;

  /*
  Description:
    Two ON_Font classes reference the same platform font and create identical glyphs 
    if and only if the have the same ManagedFontSerialNumber().
  Returns:
        0: This font is unset.
     >= 1: Serial number of the managed font with the same characteristics.
  Remark:
    For managed fonts other than ON_Font::Default, the value of ManagedFontSerialNumber()
    typically varies between instances of the same application. 
    Different platforms and application versions may use different font faces 
    for ON_Font::Default.
    If an ON_Font is a managed font, then RuntimeSerialNumber() and ManagedFontSerialNumber()
    are identical. If an ON_Font is not a managed font, then RuntimeSerialNumber() is zero.
  */
  unsigned int ManagedFontSerialNumber() const;

  //////////////////////////////////////////////////////////////////////
  //
  // Interface
  
  enum WindowsConstants : unsigned char
  { 
    // Values used to set Windows LOGFONT fields.
#if defined(ON_OS_WINDOWS_GDI)
    logfont_ansi_charset = ANSI_CHARSET,
    logfont_default_charset = DEFAULT_CHARSET,                // LOGFONT.lfCharSet
    logfont_symbol_charset = SYMBOL_CHARSET,                  // LOGFONT.lfCharSet
    logfont_out_precis = OUT_TT_ONLY_PRECIS,                  // LOGFONT.lfOutPrecision

    // 2017-07-27, Brian Gillespie
    // Changed ON_Font::WindowsConstants::logfont_quality from ANTIALIASED_QUALITY to DEFAULT_QUALITY.
    // This makes it so that ON_Font conversion to LOGFONT results in a good-looking font when rendered by MFC.
    // With lfQuality set to ANTIALIASED_QUALITY, the font looks crummy - probably because all the rest of the fonts
    // are being rendered today with CLEARTYPE_QUALITY. Letting Windows decide what to do is probably better.
    logfont_quality = DEFAULT_QUALITY,                        // LOGFONT.lfQuality

    logfont_pitch_and_family = (DEFAULT_PITCH | FF_DONTCARE), // LOGFONT.lfPitchAndFamily
#else
    // The values below are identical to the ones above and
    // are used to insure code compiles for Apple and other
    // platforms.  
    logfont_ansi_charset = 0,
    logfont_default_charset = 1,
    logfont_symbol_charset  = 2,
    logfont_out_precis = 7,
    logfont_quality = 4,
    logfont_pitch_and_family = 0
#endif
  }; 


  #if defined(ON_OS_WINDOWS_GDI)
  static unsigned char WindowsLogfontCharSetFromLogfont(
    const LOGFONT* logfont,
    bool bValidateSymbolFont
  );
  #endif
  /*
  Parameters:
    face_name - [in]  
      GDI LOGFONT.lfFaceName value.
      Note well: This is not the font "face name" or the font "family name". 
      It is typically a combination of the face name and "GDI sub-family" name
      and typically does not include words that identify face weight or 
      face style.
  Returns:
    If the code is running on Windows:
      The appropriate value of LOGFONT.lfCharSet for the input facename.
    If the code is not running on Windows:
      ON_Font::WindowsConstants::logfont_default_charset.
  */
  static unsigned char WindowsLogfontCharSetFromFaceName(
    const wchar_t* face_name 
    );
  
  // miscellaneous constants use to initialize Windows LOGFONT fields
  enum Constants: int
  { 
    // 1995 - 2015:
    // Windows fonts have variations in glyph size, design and kerning
    // for different point sizes. Text in Rhino is generally
    // placed around geometry and the relative spatial
    // relationships between the text and the geometry must 
    // remain constant on all devices and at all "zoom" levels.
    // We have to choose a point size and then apply appropriate
    // scaling during display, printing, and in other rendering
    // calculations.  After many experiments and 20 years of commercial use, 
    // (1995-2015) we have found 256 works best.
    // This value is used on all platforms because the calculations
    // it is used in occur on all platforms.  These calculations must return 
    // consistent results so models exchanged between platforms maintain
    // spatial relationships between text and geometry.
    //
    // 2017:
    // (switching to freetype)
    // The value ON_Font::Constants::AnnotationFontCellHeight is used to define
    // "opennurbs normalized font coordinates".  The scale
    // ((double)ON_Font::Constants::AnnotationFontCellHeight)/(font definition grid height)
    // is used to convert bounding information and outlines from a native
    // font definition to opennurbs normalized font coordinates.
    // Many TrueType fonts have font definition grid height = 2048.
    // Many PostScript fonts have font definition grid height = 1000.
    AnnotationFontCellHeight = 256,  // Windows LOGFONT.lfHeight value (NOT A POINT SIZE)

    // This value is used on Apple platforms to get fonts used for rendering annotation.
    // The size should be a power of 2. Ideally we want access to the font and glyph
    // design size returned by CTFontGetUnitsPerEm().
    AnnotationFontApplePointSize = 256,

    // ON_Font::Constants::metric_char is the unicode code point value
    // for the glyph used to calculate critical glyph metrics.
    // It must be an 'I' or 'H', but we have not tested 'H'.
    // There are problems with any other upper case latin letter in common fonts.
    // In particular, the standard 'M' does not work.
    // We have used 'I' for 22 years (1995 - 2017).
    // This value is used on all platforms because the calculations
    // it is used in occur on all platforms. These calculations must return 
    // consistent results so models exchanged between platforms maintain
    // spatial relationships between text and geometry.
    MetricsGlyphCodePoint = 'I'
  }; 

  ON_DEPRECATED_MSG("Use ON_Font::Description() or ON_Font::PostScriptName()")
  const ON_wString& FontDescription() const;

  ON_DEPRECATED_MSG("V6 ON_Font does not have a description property.")
  bool SetFontDescriptionForExperts(
    const wchar_t* ignored_parameter
  );
 
  ON_DEPRECATED_MSG("Use ON_Font::PostScriptName()")
  const wchar_t* FontDescriptionAsPointer() const;
  
  ON_DEPRECATED_MSG("Use ON_FontMetrics::DefaultLineFeedRatio")
  double LinefeedRatio() const;

  /*
  Returns:
    Normalized font metrics.

  Remarks:
    Font metric "normalized" units are comparable between different fonts.
    Normalized font metrics exist so that code that positions glyphs from 
    multiple fonts does not have to take the unit system and resolution used
    in the design of each font.
    In opennurbs, much of this code that positions glyphs is located in ON_Annotation,
    ON_TextContent, and ON_TextRun member functions and is used when rendering 
    annotation objects.

    Fonts can be designed and defined at different resolutions and
    relative scaling is necessary when text contains glyphs from 
    fonts designed at different grid resolutions.  For example, 
    TrueType font grid with and height is often 1024x1024 or 
    2048x2014, OpenType grids are often 1000x1000, and PostScript 
    grids are often 1000x1000. Opennurbs "font units" are the units
    the font was designed in.

    Long ago, opennurbs and Rhino used only Windows TrueType fonts
    and ran only in Microsoft Windows.  During this era,
    the "normalized units" were for a Windows LOGFONT created
    with lfHeight = ON_Font::Constants::AnnotationFontCellHeight.
  
    Currently opennurbs and Rhino work on Microsoft Windows and Apple
    platforms and use FreeType to access font information. When a font 
    is not "tricky", the "font design" units are the the units FreeType
    uses when a font is loaded with FT_LOAD_NO_SCALE.
  
    When working with fonts and glyhphs in opennurbs and Rhino, 
    SDK users almost always want to use normalized font and glyph metrics.
  */
  const ON_FontMetrics& FontMetrics() const;

  /*
  Description:
    This function is for expert users doing something complicated.
  Returns:
    Font metrics read directly from the font definition with no or minimal
    scaling.
  Remarks:
    See ON_Font.FontMetrics() documentation for important information
    about the difference between normalized and font unit metrics.
  */
  const ON_FontMetrics& FontUnitFontMetrics() const;

  /*
  Returns:
    scale to apply when converting from a FT_LOAD_NO_SCALE FreeType
    glyph metric or outline to normalized opennurbs font coordinates.    
  */
  double FontUnitToNormalizedScale() const;
  
  /*
  Returns:
    scale to apply when converting from a FT_LOAD_NO_SCALE FreeType
    glyph metric or outline to normalized opennurbs font coordinates.
  */
  double NormalizedToFontUnitScale() const;

  /*
  Returns:
    Font character height in points (1 point = 1/72 inch).

    See the remarks for a definition of "character height".

  Remarks:
    A "point" is a length unit system.
    1 point = 1/72 inch = 25.4/72 millimeters. 

    Typically, fonts are designed for maximum clarity when the rendered 
    character height is close to PointSize().

    font cell height = font ascent + font descent.

    font character height = font cell height - font internal leading.

    For fonts designed for languages that use latin letters, it is common for 
    the character height to be equal to or a little larger than the distance 
    from the bottom of a lower case g to the top of an upper case M. 
    The character height is also called the "em height".

    Font internal leading is the space above typical capital latin letters
    that is reserved for diacritical marks like the ring above the A in 
    the UNICODE "LATIN LETTER A WITH RING" U+00C5 glyph (Angstrom symbol).
  */
  double PointSize() const;

  /*
  Parameters:
    point_size - [in]
      font character height in point units.

  Remarks:
    See the remarks section ON_Font::PointSize() for more information
    about point units and character height.
  */
  bool SetPointSize(
    double point_size
  );

  static bool IsValidPointSize(
    double point_size
  );

  /*
  Description:
    This is a legacy function that traces it's heritage to Windows specific
    GDI LOGFONT code from 1995. Best to avoid it whenever possible. 
    Ideally, use an Windows IDWriteFont or Apple CTFont to create an ON_Font that
    references an installed font. Less ideally, use a complete LOGFONT structure.
  Parameters:
    windows_logfont_name - [in]
      GDI LOGFONT.lfFaceName value.
      Note well: 
        This is not the font "face name", not the font "family name",
        and not the font PostScript name.
        It is often a combination of the family name, an additional "GDI sub-family" name.
        Occasionally it includes some face weight and style attributes.
  Returns:
    True if the value was set.
  */  
  ON_DEPRECATED_MSG("Use ON_Font::SetFromDWriteFont(), ON_Font::SetFromAppleFont(), or ON_Font::SetFromWindowsLogFont()")
  bool SetFontFaceName( 
    const wchar_t* windows_logfont_name
    );

  /*
  Description:
    This is a legacy function that traces it's heritage to Windows specific
    GDI LOGFONT code from 1995. Best to avoid it whenever possible. 
    Ideally, use an Windows IDWriteFont or Apple CTFont to create an ON_Font that
    references an installed font. Less ideally, use a complete LOGFONT structure.
  Parameters:
    windows_logfont_name - [in]
      GDI LOGFONT.lfFaceName value.
      Note well: 
        This is not the font "face name", not the font "family name",
        and not the font PostScript name.
        It is often a combination of the family name, an additional "GDI sub-family" name.
        Occasionally it includes some face weight and style attributes.
  Returns:
    True if the value was set.
  */  
  bool SetWindowsLogfontName( 
    const wchar_t* windows_logfont_name
    );

  ON_DEPRECATED_MSG("Use ON_Font::WindowsLogfontName(ON_Font::NameLocale)")
  const wchar_t* FontFaceName() const;

  /*
  Returns:
    A pointer for immediate use in formatted printing as in
    FormattedPrint(L"Windows LOGFONT.lfFaceName[] = \"&ls\"\n",font.WindowsLogfontNameAsPointer());
  Remarks:
    WARNING: 
      Do not save this pointer for later use. 
      It points to memory in a dynamic string.
  */
  const wchar_t* WindowsLogfontNameAsPointer() const;

  ON_Font::Weight FontWeight() const;

  int WindowsLogfontWeight() const;
  int AppleWeightOfFont() const;
  double AppleFontWeightTrait() const;

  /*
  Returns:
    If the font is created from a CTFont, the weight trait,
    otherwise ON_UNSET_VALUE;
  */
  double AppleFontWeightTraitEx() const;

  /*
  Description:
    Don't use this old function.  If you have a font and want a face in
    the same famliy with a different weight, then call 
    InstalledFamilyMemberWithWeightStretchStyle(desired_weight,unset,unset).

    NOTE WELL: 
      Changing the weight requires updating the Family, Face, PostScript 
      and Windows LOGFONT names as well.
  */
  bool SetFontWeight(
    ON_Font::Weight font_weight
    );

  /*
  Description:
    Don't use this old function. Higher quality font information is created 
    by SetFromAppleFont() and SetFromWindowsDWriteFont().
    NOTE WELL: 
      Changing the weight requires updating the Family, Face, PostScript 
      and Windows LOGFONT names as well.
  */
  bool SetWindowsLogfontWeight(
    int windows_logfont_weight
  );

  /*
  Description:
    Don't use this old function. Higher quality font information is created 
    by SetFromAppleFont() and SetFromWindowsDWriteFont().
    NOTE WELL: 
      Changing the weight requires updating the Family, Face, PostScript 
      and Windows LOGFONT names as well.
  */
  bool SetAppleWeightOfFont(
    int apple_weight_of_font
  );

  /*
  Description:
    Don't use this old function. Higher quality font information is created 
    by SetFromAppleFont() and SetFromWindowsDWriteFont().
    NOTE WELL: 
      Changing the weight requires updating the Family, Face, PostScript 
      and Windows LOGFONT names as well.
  */
  bool SetAppleFontWeightTrait(
    double apple_font_weight_trait
  );

  /*
  Parameters:
    bCheckFamilyName - [in]
    bCheckPostScriptName - [in]
  Returns:
    True if any of LOGFONT face name is empty.
    True if any of weight, stretch, or style is unset.
    True if bCheckFamilyName is true and FamilyName() is empty.
    True if bCheckPostScriptName is true and PostScriptName() is empty.
    False otherwise.
  */
   bool HasUnsetProperties(
    bool bCheckFamilyName,
    bool bCheckPostScriptName
  ) const;

  /*
  Description:
    If a propery is unset in this and set in source, then it is set
    to the source value.
  Parameters:
    source - [in]
    bUpdateDescription - [in]
      When in doubt, pass true. 
      If bUpdateDescription is true and  at least one property
      is changed, then the description is also updated. 
  Returns:
    Number of changed properties.
  */
  unsigned int SetUnsetProperties(
    const ON_Font& source,
    bool bUpdateDescription
  );

private:
  bool Internal_SetFontWeightTrio(
    ON_Font::Weight font_weight,
    int windows_logfont_weight,
    double apple_font_weight_trait,
    bool bUpdateFontDescription
    );

  // Unsets origin and resets cache
  void Internal_AfterModification();

public:

  /*
  Description:
    User interfaces that want to provide a name + regular/bold/italic/bold-italic
    font finder must use IsBoldInQuartet() and IsItalicInQuartet().

    This function looks at weight the font designer assigned to the font.
    This is an unreliable way to determine if a font is "light/regular/bold"
    compared to other faces in its font family.

  Returns:
    True if FontWeight() is lighter than ON_Font::Weight::Normal
  */
  bool IsLight() const;

  /*
  Description:
    User interfaces that want to provide a name + regular/bold/italic/bold-italic
    font finder must use IsBoldInQuartet() and IsItalicInQuartet().

    This function looks at weight the font designer assigned to the font.
    This is an unreliable way to determine if a font is "light/regular/bold"
    compared to other faces in its font family.

  Returns:
    True if FontWeight() is ON_Font::Normal or ON_Font::Weight::Medium
  */
  bool IsNormalWeight() const;

  /*
  Description:
    User interfaces that want to provide a name + regular/bold/italic/bold-italic
    font finder must use IsBoldInQuartet() and IsItalicInQuartet().

    This function looks at weight the font designer assigned to the font.
    This is an unreliable way to determine if a font is "light/regular/bold"
    compared to other faces in its font family.

  Returns:
    True if heavier than ON_Font::Weight::Medium.

  Remarks:
    Just in case you didn't read the description, ON_Font.IsBold() is a terrible
    way to decide if a font is "bold" in a quartet (regular,bold,italic,bold-italic).
    Use ON_Font.QuartetFaceMember()
  */
  bool IsBold() const;

  /*
  Returns:
    True if this font is considered a bold member in its installed font ON_FontFaceQuartet.
  Remarks:
    In a traditional regular/bold/italic/bold-italic font face interfaces,
    "bold" is relative to the quartet members and cannot be determined
    by inspecting the numerical value of the font's weight. For example,
    Arial Black has a weight of 900=ON_FontWeight::Weight::Heavy,
    but the Arial Black quartet has only two faces, regular and italic.
    In quartets for fonts with a simulated bold, like AvenirLT-Roman,
    the bold member often has a LOGFONT weight of 551 < SemiBold = 600.
    The Windows AvenirLT-Roman quartet has four faces and the bold faces in
    the quartet have weights 551.
  */
  bool IsBoldInQuartet() const;

  /*
  Returns:
    True if this font is considered an italic member in its installed font ON_FontFaceQuartet.
  Remarks:
    When working with rich text you want to use IsItalicInQuartet().
    For fonts with a slanted regular face like Corsiva,
    ON_Font.FontStyle() = ON_Font::Style::Italic, ON_Font.IsItalic() = true,
    and ON_Font.IsItalicInQuartet() = false.
  */
  bool IsItalicInQuartet() const;

  /*
  Remarks:
    When working with rich text you want to use IsItalicInQuartet().
    For fonts with a slanted regular face like Corsiva,
    ON_Font.FontStyle() = ON_Font::Style::Italic, ON_Font.IsItalic() = true,
    and ON_Font.IsItalicInQuartet() = false.
  */
  ON_Font::Style FontStyle() const;

  /*
  Description:
    Don't use this old function.  If you have a font and want a face in
    the same famliy with a different style, then call 
    InstalledFamilyMemberWithWeightStretchStyle(nullptr,unset,desired_style).

    NOTE WELL: 
      Changing the style requires updating the Family, Face, PostScript 
      and Windows LOGFONT names as well.
 */
  bool SetFontStyle(
    ON_Font::Style font_style
    );

  /*
  Description:
    If is better to use IsItalicInQuartet().

  Returns:
    true if FontStyle() is ON_Font::Style::Italic.
    false if FontStyle() is ON_Font::Style::Upright or .ON_Font::Style::Oblique.
  Remarks:
    When working with rich text you want to use IsItalicInQuartet().
    For fonts with a slanted regular face like Corsiva,
    ON_Font.FontStyle() = ON_Font::Style::Italic, ON_Font.IsItalic() = true,
    and ON_Font.IsItalicInQuartet() = false.
  */
  bool IsItalic() const;

  /*
  Returns:
    true if FontStyle() is ON_Font::Style::Upright.
    false if FontStyle() is ON_Font::Style::Italic or .ON_Font::Style::Oblique.
  Remarks:
    When working with rich text you want to use IsItalicInQuartet().
    For fonts with a slanted regular face like Corsiva,
    ON_Font.FontStyle() = ON_Font::Style::Italic, ON_Font.IsItalic() = true,
    and ON_Font.IsItalicInQuartet() = false.
  */
  bool IsUpright() const;

  /*
  Returns:
    true if FontStyle() is ON_Font::Style::Italic or  is ON_Font::Style::Oblique.
    Otherwise false.
  Remarks:
    When working with rich text you want to use IsItalicInQuartet().
    For fonts with a slanted regular face like Corsiva,
    ON_Font.FontStyle() = ON_Font::Style::Italic, ON_Font.IsItalic() = true,
    and ON_Font.IsItalicInQuartet() = false.
  */
  bool IsItalicOrOblique() const;

  /*
  Returns:
    true if FontStyle() is ON_Font::Style::Oblique.
    false if FontStyle() is ON_Font::Style::Upright or .ON_Font::Style::Italic.
  Remarks:
    When working with rich text you want to use IsItalicInQuartet().
    For fonts with a slanted regular face like Corsiva,
    ON_Font.FontStyle() = ON_Font::Style::Italic, ON_Font.IsItalic() = true,
    and ON_Font.IsItalicInQuartet() = false.
  */
  bool IsOblique(); // ERROR - missing const


  ON_Font::Stretch FontStretch() const;

  double AppleFontWidthTrait() const;

  /*
  Description:
    Don't use this old function.  If you have a font and want a face in
    the same famliy with a different stretch, then call 
    InstalledFamilyMemberWithWeightStretchStyle(nullptr,desired_stretch,unset).

    NOTE WELL: 
      Changing the stretch requires updating the Family, Face, PostScript 
      and Windows LOGFONT names as well.
 */
  bool SetFontStretch(
    ON_Font::Stretch font_stretch
    );

  bool IsUnderlined() const;
  bool SetUnderlined(
    bool bUnderlined 
    );

  bool IsStrikethrough() const;
  bool SetStrikethrough( 
    bool bStrikethrough
    );

  /*
  Returns:
    True if the font is a symbol font. Typically this means
    that there is no meaningful correspondence between
    public use UNICODE codepoints and glyphs.
  Remarks:
    The Linguist's Software fonts (circa 1997) with the family names
      CityBlueprint
      CountryBlueprint
      Romantic
      Technic
    are classified as symbol fonts but have reasonable glyphs 
    for most ASCII codepoints.
  */
  bool IsSymbolFont() const;

  const ON_PANOSE1 PANOSE1() const;

  void SetPANOSE1(
    ON_PANOSE1 panose1
  );

  /*
  Returns:
    If the outline figure type is known for certain, it is returned.
    Otherwise, ON_OutlineFigure::Type::Unknown is returned.
  */
  ON_OutlineFigure::Type OutlineFigureType() const;

  /*
  Returns:
    True if this is a known single stroke font.
    False otherwise.
  See Also:
    IsEngravingFont()   
  */
  bool IsSingleStrokeFont() const;

  /*
  Returns:
    True if this is a known double stroke font.
    False otherwise.
  See Also:
    IsEngravingFont()   
  */
  bool IsDoubleStrokeFont() const;

  /*
  Returns:
    True if this is a known single stroke or double stroke font.
    False otherwise.
  See Also:
    IsEngravingFont()   
  */
  bool IsSingleStrokeOrDoubleStrokeFont() const;  

  /*
  Description:
    The outlines for an engraving font have single-stroke, double-stroke, 
    or perimeters designed for path engraving. 
    These fonts behave poorly when used for filled font rendering 
    or creating solid extrusions. 
    The OrachTech 2 line fonts are examples of engraving fonts that
    are not single or double stroke.
  Returns:
    True if the font is a known engraving font.
  */
  bool IsEngravingFont() const;

  static const ON_Font* DefaultEngravingFont();

  unsigned char LogfontCharSet() const;
  
  bool SetLogfontCharSet(
    unsigned char logfont_charset
    );

  ON_DEPRECATED_MSG("Use FontMetrics().AscentOfCapital()")
  int HeightOfI() const;

  ON_DEPRECATED_MSG("Use FontMetrics().LineSpace()")
  int HeightOfLinefeed() const;
  
  ON_DEPRECATED_MSG("Use FontMetrics().GlyphScale()")
  double HeightScale(double text_height) const;
  
  ON_DEPRECATED_MSG("Use FontMetrics().StrikeoutThickness()")
  int GetStrikeoutSize() const;

  ON_DEPRECATED_MSG("Use FontMetrics().StrikeoutPosition()")
  int GetStrikeoutPosition() const;

  ON_DEPRECATED_MSG("Use FontMetrics().UnderscoreThickness()")
  int GetUnderscoreSize() const;


  ON_DEPRECATED_MSG("Use FontMetrics().UnderscorePosition()")
  int GetUnderscorePosition() const;

  /*
  Returns:
    A SHA-1 hash of all font characteristics, including platform specific settings. 
    Two fonts have identical font characteristics, if and only if they have identical 
    FontCharacteristicsHash() values.

  Example:
        ON_Font f1 = ...
        ON_Font f2 = ...
        if ( f1.FontCharacteristicsHash() == f2.FontCharacteristicsHash() )
        {
          // f1 and f2 have identical font characteristics
        }
        else
        {
          // f1 and f2 have different font characteristics
        }
  */
  const class ON_SHA1_Hash& FontCharacteristicsHash() const;

private:

public:

  /*
  Description:
    Compares the font face name, weight, style, stretch, underline, strikethrough,
    point size, and platform specific characteristics. 
  Returns:
    -1: lhs characteristics < rhs characteristics
     0: lhs characteristics = rhs characteristics
    +1: lhs characteristics > rhs characteristics
  Remarks:
    Use FontCharacteristicsHash() when every characteristic needs to be compared.
  */
  static int CompareFontCharacteristics(
    const ON_Font& lhs,
    const ON_Font& rhs
    );


  /*
  Description:
    Compares the font weight, style, stretch, underline, strikethrough, linefeed_ratio
    and facename characteristics.
  Returns:
    0 == ON_Font::CompareFontCharacteristics(lhs,rhs).
  Remarks:
    Use FontCharacteristicsHash() when every characteristic needs to be compared.
  */
  static bool EqualFontCharacteristics(
    const ON_Font& lhs,
    const ON_Font& rhs
    );

  /*
  Description:
    Expert user tool to compares the font face name, weight, style, stretch, 
    underline, and strikethrough characteristics. Additional parameters 
    determine how unset and platform specific characteristics are compared.     

  Parameters:
    bComparePlatformSpecificCharacteristics - [in]
      If bComparePlatformSpecificCharacteristics is true, characteristics
      for the current platform are compared. Otherwise all platform specific
      characteristics are ignored.
      Platform specific characteristics include m_logfont_charset on Windows,
      and m_apple_font_name and m_apple_font_weight_trait on Mac OS.

    bIgnoreUnsetCharacteristics - [in]
      If bIgnoreUnsetCharacteristics is true, unset characteristics are 
      considered equal to any other value.  

      WARNING: 
        When bIgnoredUnsetCharacteristic is true, this compare function is not a 
        well ordering of ON_Font classes and cannot be used in sorting algorithms. 
        For example, if A, B, C are fonts with weights 
          A.FontWeight() = ON_Font::Weight::Normal, 
          B.FontWeight() = ON_Font::Weight::Bold, 
          C.FontWeight() = ON_Font::Weight::Unset, 
        and all other settings identical, then A < B and A=C and B=C. 

  Returns:
    -1: lhs characteristics < rhs characteristics
     0: lhs characteristics = rhs characteristics
    +1: lhs characteristics > rhs characteristics
  */
  static int CompareFontCharacteristicsForExperts(
    bool bComparePlatformSpecificCharacteristics,
    bool bIgnoreUnsetCharacteristics,
    const ON_Font& lhs,
    const ON_Font& rhs
    );

  /*
  Description:
    In the rare cases when an ON_Font::Weight value must be passed
    as an unsigned int, use ON_Font::FontWeightFromUnsigned() to
    convert the unsigned value to an ON_Font::Weight value.
  Parameters:
    unsigned_font_weight - [in]
  */
  static ON_Font::Origin FontOriginFromUnsigned(
    unsigned int unsigned_font_origin
    );

  /*
  Returns:
    Source of the information used to set the font characteristics.
    Unset = 0,
  */
  ON_Font::Origin FontOrigin() const;
  
  void SetFontOrigin(
    ON_Font::Origin font_origin
  );

  /*
  Returns:
    True if the font face is simulated in some way
  */
  bool IsSimulated() const;

  /*
  Returns:
    often bold from normal
  */
  bool SimulatedWeight() const;

  /*
  Returns:
    often bold from normal
  */
  bool SimulatedStretch() const;

  /*
  Returns:
    true if the style was simulated (typically italic from upright)
  */
  bool SimulatedStyle() const;

  void SetSimulated(
    bool bSimulatedWeight,
    bool bSimulatedStretch,
    bool bSimulatedStyle,
    bool bSimulatedOther
  );

private:
  friend class ON_ManagedFonts;

  //////////////////////////////////////////////////////////////////////////////////
  //
  // The "font glyph definition" parameters completely determine the appearance
  // of font glyphs.
  //
  // If all "font glyph definition" parameters have identical values, 
  // text rendered using those fonts will look identical.
  //
  // If two fonts have a "font glyph definition" parameter with different values,
  // text rendered using those fonts will not look identical.
  //
  // BEGIN "font glyph definition" parameters:
  //

  // The font ON_Font::Default has m_runtime_serial_number = 1.
  // Managed fonts have m_runtime_serial_number >= 1.
  // Unmanaged fonts have m_runtime_serial_number = 0;
  static unsigned int __runtime_serial_number_generator;
  const unsigned int m_runtime_serial_number = 0;
  
  int m_windows_logfont_weight = 400; // 100 <= m_windows_logfont_weight <= 1000
  double m_point_size = 0.0; // 0.0 indicates the annotation font size will be used.
  double m_apple_font_weight_trait = 0.0; // = Apple WeightTrait value -1.0 <= m_apple_font_weight < 1.0, 0.0 = "normal"
  ON_Font::Weight  m_font_weight = ON_Font::Weight::Normal;

  ON_Font::Style   m_font_style = ON_Font::Style::Upright;    // m_font_style corresponds to Windows LOGFONT.lfItalic field
  ON_Font::Stretch m_font_stretch = ON_Font::Stretch::Medium;
  bool             m_font_bUnderlined = false;                // Same as Windows LOGFONT.lfUnderlined
  bool             m_font_bStrikethrough = false;             // Same as Windows LOGFONT.lfStrikeOut

  // There are two permitted values for m_logfont_charset.
  //   ON_Font::WindowsConstants::logfont_default_charset = 1
  //   ON_Font::WindowsConstants::logfont_symbol_charset = 2
  unsigned char    m_logfont_charset = ON_Font::WindowsConstants::logfont_default_charset;

private:
  ON_Font::Origin m_font_origin = ON_Font::Origin::Unset;

private:
  const ON_Font::FontType m_font_type = ON_Font::FontType::Unset;

private:
  // Locale for localized m_locale_* font names.
  ON_wString m_locale_name;

  // Localized and English font PostScript name
  //  Apple: = CTFontCopyPostScriptName() / NSFont.fontName
  //  Windows: = IDWriteFont.GetInformationalStrings(DWRITE_INFORMATIONAL_STRING_POSTSCRIPT_NAME,...)
  //  NOTE WELL: 
  //    This is NOT the GDI LOGFONT.lfFaceName.
  ON_wString m_loc_postscript_name;
  ON_wString m_en_postscript_name;

  // Localized and English font family name
  //  Apple: = CTFontCopyFamilyName() / NSFont.familyName
  //  Windows: = IDWriteFontFamily.GetFamilyNames()
  //  NOTE WELL: 
  //    This is NOT the GDI LOGFONT.lfFaceName.
  ON_wString m_loc_family_name;
  ON_wString m_en_family_name;

  // Localized and English font face name
  //  Apple: = CTFontCopyName( ..., kCTFontStyleNameKey)
  //  Windows: = IDWriteFont.GetFaceNames()
  //  NOTE WELL: 
  //    This is NOT the GDI LOGFONT.lfFaceName.
  ON_wString m_loc_face_name;
  ON_wString m_en_face_name;

  // Localized and English Windows GDI LOGFONT.lfFaceName
  //  Apple: = not available
  //  Windows: = IDWriteFont.GetInformationalStrings(DWRITE_INFORMATIONAL_STRING_WIN32_FAMILY_NAMES,...)
  ON_wString m_loc_windows_logfont_name;
  ON_wString m_en_windows_logfont_name;

  void Internal_ClearAllNames();

  void Internal_ClearName(
    bool bClearFamilyName,
    bool bClearFaceName,
    bool bClearPostScriptName,
    bool bClearWindowsLogfontName
  );
  
private:
  ON__UINT8 m_simulated = 0; // bit field (&1 = some simulation, &2 simulated weight, &4 simulated stretch, &8 simulated italic)

private:
  // = 1 if this is a managed font and the face is installed on the current device.
  ON__UINT8 m_reserved1 = 0;

private:
  ON_PANOSE1 m_panose1;

private:
  // A sha1 hash of all font characteristics.
  // This value is set using lazy evaluation.
  // A zero digest indicates it is not set.
  mutable ON_SHA1_Hash m_font_characteristics_hash;

private:
  double m_apple_font_width_trait = ON_UNSET_VALUE;

private:
  ON_OutlineFigure::Type m_outline_figure_type = ON_OutlineFigure::Type::Unset;

private:
  // When then is unset, it is the best way to determine what face this font
  // corresponds to in its quartet of faces. (regular,bold,italic,bold-italic)
  // The Windows OS LOGFONT partitions specify this. On Apple we have a table
  // for common fonts and we make it up on the fly for the rest.
  // This field is not included in the font hash because it is mutable
  // and may get changed as the application adds more managed fonts.
  mutable ON_FontFaceQuartet::Member m_quartet_member = ON_FontFaceQuartet::Member::Unset;

private:
  ON__UINT16 m_reserved2 = 0;
  ON__UINT32 m_reserved3 = 0;
  double m_reserved4 = 0.0;

private:
  bool ModificationPermitted(
    const char* function_name,
    const char* file_name,
    int line_number
    ) const;

private:
  //////////////////////////////////////////////////////////////////////////////////
  //
  // BEGIN global font glyph cache interface
  //
  // There is a single font glyph cache for each managed font.
  // Fonts that are not managed use a glyph cache from a managed font.
  // This make functions like ON_Font.FindGlyph() efficient and reliable.
  //
  void DestroyFontGlyphCache();
  class ON_FontGlyphCache* FontGlyphCache(
    bool bCreateIfMissing
    ) const;
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 ) 
  // C4251: '...std::shared_ptr<class ON_FontGlyphCache>...' 
  //         needs to have dll-interface to be used by clients of class 'ON_Font'
  // m_font_glyph_cache is private and all code that manages m_font_glyph_cache is explicitly implemented in the DLL.
private:
  mutable std::shared_ptr<class ON_FontGlyphCache> m_font_glyph_cache;
#pragma ON_PRAGMA_WARNING_POP
  //
  // END global font cache interface
  //
  //////////////////////////////////////////////////////////////////////////////////

private:
  // LEGACY field. Windows opennurbs never uses freetype. 
  // In rare cases, Apple opennurbs used freetype.
  mutable class ON_FreeTypeFace* m_free_type_face = nullptr;

private:
  // If this font is a managed font, then m_managed_installed_font_and_bits encodes
  // 1. The installed font used to render this font
  // 2. If the installed font is a substituted for font not installed on this device.
  // If this font is not a managed font, then m_managed_installed_font_and_bits = 0.
  // LEGACY mutable ON__UINT8 m_managed_face_is_installed = 0; 1 = managed and installed 2 = managed and substituted
  mutable ON__UINT_PTR m_managed_installed_font_and_bits = 0;
  static void Internal_SetManagedFontInstalledFont(
    const ON_Font* managed_font,
    const ON_Font* installed_font,
    bool bInstalledFontIsASubstitute
  );

  /// <summary>
  /// 
  /// </summary>
  /// <returns>
  /// True if this is a managed font that is installed on this device. False otherwise.
  /// </returns>
  bool Internal_ManagedFontIsInstalled() const;

  /// <summary>
  /// 
  /// </summary>
  /// <returns>
  /// True if this is a managed font that is not installed on this device. False otherwise.
  /// </returns>
  bool Internal_ManagedFontIsNotInstalled() const;

public:
  /*
  Parameters:
    font_glyph - [in]
    glyph_metrics_in_font_design_units - [out]
      glyph metrics in font design units
  Returns:
    >0: Glyph index
    0: failed
  */
  typedef unsigned int (*ON_GetGlyphMetricsFuncType)(
    const class ON_FontGlyph* font_glyph,
    class ON_TextBox& glyph_metrics_in_font_design_units
    );

  /*
  Parameters:
    font - [in]
    font_metrics_in_font_design_units - [out]
      font metrics in font design units
  */
  typedef void (*ON_GetFontMetricsFuncType)(
    const class ON_Font* font,
    class ON_FontMetrics& font_metrics_in_font_design_units
    );

  typedef bool (*ON_GetGlyphOutlineFuncType)(
      const class ON_FontGlyph* glyph,
      bool bSingleStrokeFont,
      class ON_Outline& outline
    );

  static void SetCustomMeasurementFunctions(
    ON_GetGlyphMetricsFuncType measureGlyphFunc,
    ON_GetFontMetricsFuncType metricsFunction
  );

private:
  static ON_GetGlyphMetricsFuncType Internal_CustomGetGlyphMetricsFunc;
  static ON_GetFontMetricsFuncType Internal_CustomGetFontMetricsFunc;
  static ON_GetGlyphOutlineFuncType Internal_CustomGetGlyphOutlineFunc;

public:
  static void GetRunBounds(
    const ON_Font& font,
    const wchar_t* text,
    double fontSizePixels,
    ON::TextHorizontalAlignment horizontalAlignment,
    ON::TextVerticalAlignment verticalAlignment,
    ON_2dPoint& boundsMin,
    ON_2dPoint& boundsMax, 
    int& lineCount
  );
};

typedef int (*ON_FontPtrCompareFunc)(ON_Font const* const* lhs, ON_Font const* const* rhs);

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<const ON_Font*>;
#endif

class ON_CLASS ON_FontList
{
public:
  ON_FontList();

  /*
  Parameters:
    bMatchUnderlineStrikethroughAndPointSize - [in]
      False to ignore underline, strikethrough, and point size properties (installed font list)
      True to match underline, strikethrough and point size properties (managed font list)
  */
  ON_FontList(
    bool bMatchUnderlineStrikethroughAndPointSize
  );

  ~ON_FontList();

private:
  ON_FontList(const ON_FontList&) = delete;
  ON_FontList& operator=(const ON_FontList&) = delete;

public:
  /*
  Returns:
    Number of fonts in the list.
  */
  unsigned int Count() const;

  ON_Font::NameLocale NameLocale() const;

  /*
  Parameters:
    font_characteristics_hash - [in]
    bReturnFirst - [in]
      If there are multiple fonts with the same hash and bReturnFirst is true,
      then the first font with tht hash is returned.
      If there are multiple fonts with the same hash and bReturnFirst is false,
      then nullptr is returned.
      new style or unset if font style is adequate
  Returns:
    A font with the specified font characteristics hash.
  */
  const ON_Font* FromFontCharacteristicsHash(
    ON_SHA1_Hash font_characteristics_hash,
    bool bReturnFirst
  ) const;

  const ON_Font* FromPostScriptName(
    const wchar_t* postscript_name
  ) const;
  
  const ON_Font* FromPostScriptName(
    const wchar_t* postscript_name,
    ON_Font::Weight prefered_weight,
    ON_Font::Stretch prefered_stretch,
    ON_Font::Style prefered_style
  ) const;
  
  const ON_Font* FromPostScriptName(
    const wchar_t* postscript_name,
    ON_Font::Weight prefered_weight,
    ON_Font::Stretch prefered_stretch,
    ON_Font::Style prefered_style,
    bool bUnderlined,
    bool bStrikethrough
  ) const;
  
  const ON_Font* FromWindowsLogfontName(
    const wchar_t* windows_logfont_name
  ) const;
  
  const ON_Font* FromWindowsLogfontName(
    const wchar_t* windows_logfont_name,
    ON_Font::Weight prefered_weight,
    ON_Font::Stretch prefered_stretch,
    ON_Font::Style prefered_style
  ) const;
  
  const ON_Font* FromWindowsLogfontName(
    const wchar_t* windows_logfont_name,
    ON_Font::Weight prefered_weight,
    ON_Font::Stretch prefered_stretch,
    ON_Font::Style prefered_style,
    bool bUnderlined,
    bool bStrikethrough
  ) const;
  
  const ON_Font* FromFamilyName(
    const wchar_t* family_name,
    const wchar_t* prefered_face_name
  ) const;
  
  const ON_Font* FromFamilyName(
    const wchar_t* family_name,
    const wchar_t* prefered_face_name,
    ON_Font::Weight prefered_weight,
    ON_Font::Stretch prefered_stretch,
    ON_Font::Style prefered_style
  ) const;
  
  const ON_Font* FromFamilyName(
    const wchar_t* family_name,
    const wchar_t* prefered_face_name,
    ON_Font::Weight prefered_weight,
    ON_Font::Stretch prefered_stretch,
    ON_Font::Style prefered_style,
    bool bUnderlined,
    bool bStrikethrough
  ) const;

  /*
  Parameters:
    rtf_font_name - [in]
      Rich text format name. This name is not well defined and depends on
      the device and application that created the rich text. On Windows this
      is often a LOGFONT.lfFaceName. On MacOS it is often a PostScript name.

    bRtfBold - [in]
      RTF bold flag

    bRtfItalic - [in]
      RTF italic flag
  */
  ON_DEPRECATED_MSG("Use the static ON_Font::FontFromRichTextProperties()")
  const ON_Font* FromRichTextProperties(
    const wchar_t* rtf_font_name,
    bool bRtfBold,
    bool bRtfItalic,
    bool bUnderlined,
    bool bStrikethrough
  ) const;

  /*
  Parameters:
    postscript_name - [in]
    windows_logfont_name - [in]
    family_name - [in]
      The returned font will have an exact match for one
      of the three names, postscript_name, windows_logfont_name, 
      or family_name.
    
    prefered_face_name - [in]
    prefered_weight - [in]      
    prefered_stretch - [in]
    prefered_style - [in]
      Preferred font properties.

    bRequireFaceMatch - [in]
      If true and face_name is not empty, then the returned font 
      will have an exact match for either postscript_name, windows_logfont_name, 
      or the family and face name pair.

    bRequireStyleMatch - [in]
      If true and prefered_stretch is not unset, then the returned
      font will have prefered_style
  Remarks:
    Ignores underlined, strikethrough, and point size settings when looking for a match.
  */
  const ON_Font* FromNames(
    const wchar_t* postscript_name,
    const wchar_t* windows_logfont_name,
    const wchar_t* family_name,
    const wchar_t* prefered_face_name,
    ON_Font::Weight prefered_weight,
    ON_Font::Stretch prefered_stretch,
    ON_Font::Style prefered_style,
    bool bRequireFaceMatch,
    bool bRequireStyleMatch
  ) const;

  /*
  Parameters:
    postscript_name - [in]
    windows_logfont_name - [in]
    family_name - [in]
      The returned font will have an exact match for one
      of the three names, postscript_name, windows_logfont_name, 
      or family_name.
    
    prefered_face_name - [in]
    prefered_weight - [in]      
    prefered_stretch - [in]
    prefered_style - [in]
      Preferred font properties.

    bRequireFaceMatch - [in]
      If true and face_name is not empty, then the returned font 
      will have an exact match for either postscript_name, windows_logfont_name, 
      or the family and face name pair.

    bRequireStyleMatch - [in]
      If true and prefered_stretch is not unset, then the returned
      font will have prefered_style

    bUnderlined - [in]
      Exact match required.
    bStrikethrough - [in]
      Exact match required.
    point_size - [in]
      Exact match required.
  */
  const ON_Font* FromNames(
    const wchar_t* postscript_name,
    const wchar_t* windows_logfont_name,
    const wchar_t* family_name,
    const wchar_t* prefered_face_name,
    ON_Font::Weight prefered_weight,
    ON_Font::Stretch prefered_stretch,
    ON_Font::Style prefered_style,
    bool bRequireFaceMatch,
    bool bRequireStyleMatch,
    bool bUnderlined,
    bool bStrikethrough,
    double point_size
  ) const;

  const ON_Font* FromFontProperties(
    const ON_Font* font_properties,
    bool bRequireFaceMatch,
    bool bRequireStyleMatch
  ) const;

  const ON_Font* FromFontProperties(
    const ON_Font* font_properties,
    bool bRequireFaceMatch,
    bool bRequireStyleMatch,
    bool bUnderlined,
    bool bStrikethrough,
    double point_size
  ) const;

  /*
  Parameters:
    family name - [in]
    desired_weight - [in]
    desired_stretch - [in]
    desired_style - [in]
  Returns:
    A font in the same family with that comes a close as possible to matching the
    desired weight, stretch and style.
  */
  const ON_Font* FamilyMemberWithWeightStretchStyle(
    const wchar_t* family_name,
    ON_Font::Weight desired_weight,
    ON_Font::Stretch desired_stretch,
    ON_Font::Style desired_style
  ) const;  
  
  /*
  Parameters:
    font - [in]
      Used to identify the family,
    desired_weight - [in]
      new weight or unset if font weight is adequate
    desired_stretch - [in]
      new stretch or unset if font stretch is adequate
    desired_style - [in]
      new style or unset if font style is adequate
  Returns:
    A font in the same family with that comes a close as possible to matching the
    desired weight, stretch and style.
  */
  const ON_Font* FamilyMemberWithWeightStretchStyle(
    const ON_Font* font,
    ON_Font::Weight desired_weight,
    ON_Font::Stretch desired_stretch,
    ON_Font::Style desired_style
  ) const;

  /*
  Description:
    Get the subset of fonts in this list with matching names.
  */
  unsigned int FontListFromNames(
    const wchar_t* postscript_name,
    const wchar_t* windows_logfont_name,
    const wchar_t* family_name,
    const wchar_t* face_name,
    ON_SimpleArray< const ON_Font* >& font_list
  ) const;

  /*
  Returns:
    Array of fonts in the order they were added.
  */
  const ON_SimpleArray< const class ON_Font* >& ByIndex() const;

  /*
  Returns:
    Array of fonts sorted by ON_Font.PostScriptName().
  */
  const ON_SimpleArray< const class ON_Font* >& ByPostScriptName() const;

  /*
  Returns:
    Array of fonts sorted by ON_Font.WindowsLogfontName().
  */
  const ON_SimpleArray< const class ON_Font* >& ByWindowsLogfontName() const;

  /*
  Returns:
    Array of fonts sorted by ON_Font.FamilyName() and then by ON_Font.FaceName().
  */
  const ON_SimpleArray< const class ON_Font* >& ByFamilyName() const;

  /*
  Returns:
    Array of fonts sorted by ON_Font.QuartetName().
  */
  const ON_SimpleArray< const class ON_Font* >& ByQuartetName() const;

  /*
  Returns:
    Array of fonts sorted by ON_Font.yFontCharacteristicsHash().
  */
  const ON_SimpleArray< const class ON_Font* >& ByFontCharacteristicsHash() const;

  /*
  Returns:
    Array of font face quartets for this list sorted quartet name.
  Remarks:
    This is pribarily for old-fashioned font selection UI that harkens back
    to the days of LOGFONT. The UI displays a name and a bold and italic button
    that lets you select one of four related faces. The name used to be based
    on the LOGFONT name. Depending on the contents of the list, there may be 
    some faces in the list that do not appear in the QuartetList().
  */
  const ON_ClassArray< ON_FontFaceQuartet >& QuartetList() const;

  /*
  Description:
    Find a font in this list with the specified quartet properties.
  Parameters:
    quartet_name - [in]
    bBold - [in]
    bItalic - [in]
  Returns:
    font in the list with specified quartet properties or nullptr if none exists.
  */
  const ON_Font* FontFromQuartetProperties(
    const wchar_t* quartet_name,
    bool bBold,
    bool bItalic
  ) const;

  /*
  Returns:
    The quartet with the specified name or ON_FontFaceQuartet::Empty if none exists.
  */
  const ON_FontFaceQuartet QuartetFromQuartetName(
    const wchar_t* quartet_name
  ) const;

  static int CompareFontCharacteristicsHash(ON_Font const* const* lhs, ON_Font const* const* rhs);

  static int ComparePostScriptName(ON_Font const* const* lhs, ON_Font const* const* rhs);
  static int CompareFamilyName(ON_Font const* const* lhs, ON_Font const* const* rhs);
  static int CompareFamilyAndFaceName(ON_Font const* const* lhs, ON_Font const* const* rhs);
  static int CompareWindowsLogfontName(ON_Font const* const* lhs, ON_Font const* const* rhs);
  static int CompareFamilyAndWindowsLogfontName(ON_Font const* const* lhs, ON_Font const* const* rhs);

  static int CompareEnglishPostScriptName(ON_Font const* const* lhs, ON_Font const* const* rhs);
  static int CompareEnglishFamilyName(ON_Font const* const* lhs, ON_Font const* const* rhs);
  static int CompareEnglishFamilyAndFaceName(ON_Font const* const* lhs, ON_Font const* const* rhs);
  static int CompareEnglishWindowsLogfontName(ON_Font const* const* lhs, ON_Font const* const* rhs);

  static int CompareQuartetName(ON_Font const* const* lhs, ON_Font const* const* rhs);

  static int CompareWeightStretchStyle(ON_Font const* const* lhs, ON_Font const* const* rhs);
  static int CompareStretch(ON_Font const* const* lhs, ON_Font const* const* rhs);
  static int CompareUnderlinedStrikethroughPointSize(ON_Font const* const* lhs, ON_Font const* const* rhs);

  unsigned int AddFont(
    const ON_Font* font,
    bool bCheckForDuplicates
  );

  unsigned int AddFonts(
    const ON_SimpleArray< const ON_Font* >& fonts
  );
  
  unsigned int AddFonts(
    size_t font_count,
    const ON_Font * const * font_list
  );

private:
  friend class ON_ManagedFonts;

private:
  const ON_Font* Internal_FromNames(
    const wchar_t* postscript_name,
    const wchar_t* windows_logfont_name,
    const wchar_t* family_name,
    const wchar_t* prefered_face_name,
    ON_Font::Weight prefered_weight,
    ON_Font::Stretch prefered_stretch,
    ON_Font::Style prefered_style,
    bool bRequireFaceMatch,
    bool bRequireStyleMatch,
    bool bMatchUnderlineStrikethroughAndPointSize,
    bool bUnderlined,
    bool bStrikethrough,
    double point_size
  ) const;

private:
  const ON_Font::NameLocale m_name_locale = ON_Font::NameLocale::LocalizedFirst;
  bool m_bMatchUnderlineStrikethroughAndPointSize = false;

  void Internal_EmptyLists();

  // List of all added fonts in the order they were added
  ON_SimpleArray< const ON_Font* > m_by_index;

  void Internal_UpdateSortedLists() const;

  static const ON_2dex Internal_SearchSortedList(
    const ON_Font* key,
    ON_FontPtrCompareFunc compare_func,
    const ON_SimpleArray< const ON_Font* >& sorted_font_list
  );

  // List of recently added fonts unsorted
  mutable ON_SimpleArray< const ON_Font* > m_unsorted;

  // A single instance is allocated in the default constructor
  // and freed in the destructor. You may assume this point is valid.
  // ON_FontListImpl contains the sorted lists.
  class ON_FontListImpl& m_sorted;

  // this reserved block is here to keep sizeof(ON_FontList) unchanged between
  // Rhino 7.3 and Rhino 7.4 and to insure that any 3rd party code that used ON_FontList
  // in Rhino 7.3 will continue to work as expected in Rhino 7.4.
  const ON__UINT_PTR m_reserved[20] = {};

  // List of quartets sorted by quartet name.
  mutable ON_ClassArray< ON_FontFaceQuartet > m_quartet_list;
};


#if defined(ON_RUNTIME_WIN)

/*
Remarks:
  Windows GDI functions used by ON_WindowsMeasureGlyph fail when the
  UTF-16 encoding of unicode_code_point requires a surrogate pair.
*/
ON_DECL
bool ON_WindowsGetGlyphMetrics(
  const ON_Font* font,
  ON__UINT32 unicode_code_point,
  class ON_TextBox& font_unit_glyph_box
);



#endif


#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_Font*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<const ON_Font*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_ClassArray<ON_Font>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_FontGlyph*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<const ON_FontGlyph*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_FontGlyph>;
#endif

#endif


