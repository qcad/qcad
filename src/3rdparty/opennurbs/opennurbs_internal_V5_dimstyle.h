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

#if !defined(OPENNURBS_INTERNAL_V5_DIMSTYLE_INC_)
#define OPENNURBS_INTERNAL_V5_DIMSTYLE_INC_

#include "opennurbs_internal_defines.h"

#if defined(ON_COMPILING_OPENNURBS)

// ON_V5x_DimStyle is used to read and write version 5 and earlier archives.
// ON_DimStyle is the class for runtime dimension style.
class ON_V5x_DimStyle : public ON_ModelComponent
{
  ON_OBJECT_DECLARE(ON_V5x_DimStyle);

private:
  friend class ON_DimStyle;

public:
  enum eArrowType
  {
    // eArrowType is used for V5 and earlier dimensions
    // V6 dimensions (ON_Dimension) use   ON_Arrowhead::arrow_type
    solidtriangle = 0,    // 2:1
    dot = 1,
    tick = 2,
    shorttriangle = 3,    // 1:1
    arrow = 4,
    rectangle = 5,
    longtriangle = 6,     // 4:1
    longertriangle = 7,   // 6:1
  };

public:
  ON_V5x_DimStyle();
  ~ON_V5x_DimStyle();
  ON_V5x_DimStyle(const ON_V5x_DimStyle&) = default;
  ON_V5x_DimStyle& operator=(const ON_V5x_DimStyle&) = default;

public:
  ON_V5x_DimStyle( const class ON_3dmAnnotationSettings& src);
  ON_V5x_DimStyle(
    ON::LengthUnitSystem model_length_unit_system,
    const class ON_DimStyle& src
  );

public:
  bool CompareDimstyle(const ON_V5x_DimStyle& src) const;
  bool CompareValidFields(const ON_V5x_DimStyle& src) const;

  //////////////////////////////////////////////////////////////////////
  //
  // ON_Object overrides

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  // virtual
  void Dump( ON_TextLog& ) const override; // for debugging

  // virtual
  bool Write(
    ON_BinaryArchive&  // serialize definition to binary archive
    ) const override;

  // virtual
  bool Read(
    ON_BinaryArchive&  // restore definition from binary archive
    ) override;

  // When a V5 file is being read into v6
  // Copy the fields that were in DimstyleExtra in v5 into the v6 dimstyle
  // that now contains the fields that were in DimstyleExtra
  ///void ConsolidateDimstyleExtra();

  bool AttachDimstyleExtra();


  bool Write_v5(
    ON_BinaryArchive&  // serialize definition to binary archive
    ) const;

private:
  bool Internal_Read_v5(
    ON_BinaryArchive&  // restore definition from binary archive
    );

  //bool Write_v6(
  //  ON_BinaryArchive&  // serialize definition to binary archive
  //  ) const;

  bool Internal_Read_v6(
    ON_BinaryArchive&  // restore definition from binary archive
    );

public:
  void EmergencyDestroy();

  //////////////////////////////////////////////////////////////////////
  //
  // Interface

  void SetDefaultsNoExtension();

  double ExtExtension() const;
  void SetExtExtension( const double);

  double ExtOffset() const;
  void SetExtOffset( const double);

  double ArrowSize() const;
  void SetArrowSize( const double);

  double LeaderArrowSize() const;
  void SetLeaderArrowSize( const double);

  double CenterMark() const;
  void SetCenterMark( const double);

  ON_INTERNAL_OBSOLETE::V5_TextDisplayMode TextAlignment() const;
  void SetTextAlignment( ON_INTERNAL_OBSOLETE::V5_TextDisplayMode);

  int ArrowType() const;           // For ON_OBSOLETE_V2_Annotation & ON_OBSOLETE_V5_Annotation derived dimensions
  void SetArrowType( eArrowType);  // ON_Dimension derived dimensions use ArrowType1() and ArrowType2()

  int LeaderArrowType() const;
  void SetLeaderArrowType( eArrowType);

  int AngularUnits() const;
  void SetAngularUnits( int);

  int LengthFormat() const;
  void SetLengthFormat( int);

  int AngleFormat() const;
  void SetAngleFormat( int);

  int LengthResolution() const;
  void SetLengthResolution( int);

  int AngleResolution() const;
  void SetAngleResolution( int);

  const class ON_TextStyle& V5TextStyle() const;
  void SetV5TextStyle( 
    const class ON_TextStyle& v5_text_style
    );

  double TextGap() const;
  void SetTextGap( double gap);

  double TextHeight() const;
  void SetTextHeight( double height);

  double LengthFactor() const;
  void SetLengthFactor( double);

  bool Alternate() const;
  void SetAlternate( bool);

  double AlternateLengthFactor() const;
  void SetAlternateLengthFactor( double);

  int AlternateLengthFormat() const;
  void SetAlternateLengthFormat( int);

  int AlternateLengthResolution() const;
  void SetAlternateLengthResolution( int);

  int AlternateAngleFormat() const;
  void SetAlternateAngleFormat( int);

  int AlternateAngleResolution() const;
  void SetAlternateAngleResolution( int);
  
  void GetPrefix( ON_wString& ) const;
  const wchar_t* Prefix() const;
  void SetPrefix( const wchar_t*);
  void SetPrefix( wchar_t*);

  void GetSuffix( ON_wString& ) const;
  const wchar_t* Suffix() const;
  void SetSuffix( const wchar_t*);
  void SetSuffix( wchar_t*);

  void GetAlternatePrefix( ON_wString& ) const;
  const wchar_t* AlternatePrefix() const;
  void SetAlternatePrefix( const wchar_t*);
  void SetAlternatePrefix( wchar_t*);

  void GetAlternateSuffix( ON_wString& ) const;
  const wchar_t* AlternateSuffix() const;
  void SetAlternateSuffix( const wchar_t*);
  void SetAlternateSuffix( wchar_t*);

  bool SuppressExtension1() const;
  void SetSuppressExtension1( bool);

  bool SuppressExtension2() const;
  void SetSuppressExtension2( bool);

  // Don't change these enum values
  // They are used in file reading & writing
  enum class Field : unsigned int
  {
    fn_name                           = 0,
    fn_index                          = 1,
    fn_extextension                   = 2,
    fn_extoffset                      = 3,
    fn_arrowsize                      = 4,
    fn_centermark                     = 5,
    fn_textgap                        = 6,
    fn_textheight                     = 7,
    fn_textalign                      = 8,
    fn_arrowtype                      = 9,  // For v5 and previous ON_OBSOLETE_V2_Annotation and ON_OBSOLETE_V5_Annotation dimensions
    fn_angularunits                   = 10,
    fn_lengthformat                   = 11,
    fn_angleformat                    = 12,
    fn_angleresolution                = 13,
    fn_lengthresolution               = 14,
    fn_fontindex                      = 15,
    fn_lengthfactor                   = 16,
    fn_bAlternate                     = 17,
    fn_alternate_lengthfactor         = 18,
    fn_alternate_lengthformat         = 19, 
    fn_alternate_lengthresolution     = 20,
    fn_alternate_angleformat          = 21, 
    fn_alternate_angleresolution      = 22,
    fn_prefix                         = 23,
    fn_suffix                         = 24,
    fn_alternate_prefix               = 25,
    fn_alternate_suffix               = 26,
    fn_dimextension                   = 27,
    fn_leaderarrowsize                = 28,
    fn_leaderarrowtype                = 29,
    fn_suppressextension1             = 30,
    fn_suppressextension2             = 31,
    fn_last                           = 32, // not used - left here for sdk
                                     
  // Added for v5 - 5/01/07 LW       
  // version 1.6                     
    fn_overall_scale                  = 33,
    fn_ext_line_color_source          = 34,
    fn_dim_line_color_source          = 35,
    fn_arrow_color_source             = 36,
    fn_text_color_source              = 37,
    fn_ext_line_color                 = 38,
    fn_dim_line_color                 = 39,
    fn_arrow_color                    = 40,
    fn_text_color                     = 41,
    fn_ext_line_plot_color_source     = 42,
    fn_dim_line_plot_color_source     = 43,
    fn_arrow_plot_color_source        = 44,
    fn_text_plot_color_source         = 45,
    fn_ext_line_plot_color            = 46,
    fn_dim_line_plot_color            = 47,
    fn_arrow_plot_color               = 48,
    fn_text_plot_color                = 49,
    fn_ext_line_plot_weight_source    = 50,
    fn_dim_line_plot_weight_source    = 51,
    fn_ext_line_plot_weight_mm        = 52,
    fn_dim_line_plot_weight_mm        = 53,
    fn_tolerance_style                = 54,
    fn_tolerance_resolution           = 55,
    fn_tolerance_upper_value          = 56,
    fn_tolerance_lower_value          = 57,
    fn_tolerance_height_scale         = 58,
    fn_baseline_spacing               = 59,
                                     
  // Added for v5 - 12/15/09 LW       
  // version 1.7                     
    fn_draw_mask                      = 60,
    fn_mask_color_source              = 61,
    fn_mask_color                     = 62,
    fn_mask_border                    = 63,
                                     
  // Added for v5 - 12/17/09 LW       
  // version 1.8                     
    fn_dimscale                       = 64,
    fn_dimscale_source                = 65,

    // Added for V6 -                  
  // version 2.0
    fn_fixed_extension_len            = 66,
    fn_fixed_extension_on             = 67,
    fn_text_rotation                  = 68,
    fn_tolerance_alt_resolution       = 69,
    fn_tolerance_textheight_fraction  = 70,
    fn_suppress_arrow1                = 71,
    fn_suppress_arrow2                = 72,
    fn_textmove_leader                = 73,
    fn_arclength_sym                  = 74,
    fn_stack_textheight_fraction      = 75,
    fn_stack_format                   = 76,
    fn_alt_round                      = 77,
    fn_round                          = 78,
    fn_alt_zero_suppress              = 79,
    fn_tol_zero_suppress              = 80,
    fn_ang_zero_suppress              = 81,
    fn_zero_suppress                  = 82,
    fn_alt_below                      = 83,

    fn_dim_arrow_type1                = 84,  // For ON_Dimension derived dimensions
    fn_dim_arrow_type2                = 85,
    fn_dim_arrow_blockname1           = 86,
    fn_dim_arrow_blockname2           = 87,
                             
    FieldCount,                      
    fn_unset                          = 0xFFFE,
    fn_really_last                    = 0xFFFF
  };

  enum : unsigned int
  {
    // must be 1 + the maximum value of an ON_V5x_DimStyle::Field enum value.
    FieldCount = 88  
  };


  // Combines a field id and a field value
  // Dimensions will have an array of DimstyleField's to record 
  // dimension style overrides for individual dimensions
  class DimstyleField
  {
  public:
    DimstyleField()
      : m_next(nullptr)
      , m_field_id(ON_V5x_DimStyle::Field::fn_unset)
    {
      m_val.s_val = nullptr;
    }
    ~DimstyleField()
    {
      if (nullptr != m_next)
      {
        delete m_next;
        m_next = nullptr;
      }
      if (nullptr != m_val.s_val)
      {
        delete m_val.s_val;
        m_val.s_val = nullptr;
      }
    }

    DimstyleField* m_next;
    ON_V5x_DimStyle::Field m_field_id;
    union
    {
      bool b_val;
      int  i_val;
      unsigned char uc_val;
      double d_val;
      unsigned int c_val;
      const ON_wString* s_val;
    }  m_val;
  };
  
  // added version 1.3
  double DimExtension() const;
  void SetDimExtension( const double);

  // This section Added for v5 - 4-24-07 LW
  // version 1.6

  // Test if a specific field has been set in this dimstyle
  // and not inherited from its parent.
  bool IsFieldOverride(ON_V5x_DimStyle::Field field_id) const;
  // Set a field to be overridden or not
  // Fields that aren't overrides inherit from their parent dimstyle
  void SetFieldOverride(ON_V5x_DimStyle::Field field_id, bool bOverride);


  /*
  Clear all field overrides
  */
  void ClearAllFieldOverrides();

  // Test if the dimstyle has any field override flags set
  bool HasOverrides() const;

  // Change the fields in this dimstyle to match the fields of the 
  // source dimstyle for all of the fields that are marked overridden in the source
  // and to match the parent for all of the fields not marked overridden.
  // Returns true if any overrides were set.
  bool OverrideFields( const ON_V5x_DimStyle& source, const ON_V5x_DimStyle& parent);

  // 
  // Change the fields in this dimstyle to match the fields of the 
  // parent dimstyle for all of the fields that are not marked overridden in the 
  // target dimstyle.
  // This is the complement of OverrideFields()
  bool InheritFields( const ON_V5x_DimStyle& parent);

  // Test if this dimstyle is the child of any other dimstyle
  bool IsChildDimstyle() const;

  // Test if this dimstyle is the child of a given dimstyle
  // A dimstyle may have several child dimstyles, but only one parent
  bool IsChildOf(const ON_UUID& parent_uuid) const;

  // use ON_ModelComponent parent id - // ON_UUID ParentId() const;

  // Set the parent of this dimstyle
  // use ON_ModelComponent parent id - //void SetParentId(ON_UUID parent_uuid);

  // Tolerances
  // Tolerance style
  //  0: None
  //  1: Symmetrical
  //  2: Deviation
  //  3: Limits
  //  4: Basic
  enum eToleranceStyle
  {
    tsMin = 0,
    tsNone = 0,
    tsSymmetrical = 1,
    tsDeviation = 2,
    tsLimits = 3,
    tsBasic = 4,
    tsMax = 4
  };
  int  ToleranceStyle() const;
  int  ToleranceResolution() const;
  double ToleranceUpperValue() const;
  double ToleranceLowerValue() const;
  double ToleranceHeightScale() const;

  double BaselineSpacing() const;

  void SetToleranceStyle( int style);
  void SetToleranceResolution( int resolution);
  void SetToleranceUpperValue( double upper_value);
  void SetToleranceLowerValue( double lower_value);
  void SetToleranceHeightScale( double scale);
  
  void SetBaselineSpacing( double spacing = false);

    // Determines whether or not to draw a Text Mask
  bool DrawTextMask() const;
  void SetDrawTextMask(bool bDraw);

  // Determines where to get the color to draw a Text Mask
  // 0: Use background color of the viewport.  Initially, gradient backgrounds will not be supported
  // 1: Use the ON_Color returned by MaskColor()
  int MaskColorSource() const;
  void SetMaskColorSource(int source);

  ON_Color MaskColor() const;  // Only works right if MaskColorSource returns 1.
                               // Does not return viewport background color
  void SetMaskColor(ON_Color color);

  // Per DimStyle DimScale
  void SetDimScaleSource(int source);
  int DimScaleSource() const;          // 0: Global DimScale, 1: DimStyle DimScale
  void SetDimScale(double scale);
  double DimScale() const;

  // Offset for the border around text to the rectangle used to draw the mask
  // This number * CRhinoAnnotation::TextHeight() for the text is the offset 
  // on each side of the tight rectangle around the text characters to the mask rectangle.
  double MaskOffsetFactor() const;

  void Scale( double scale);

  // UUID of the dimstyle this was originally copied from
  // so Restore Defaults has some place to look
  void SetSourceDimstyle(ON_UUID source_uuid);
  ON_UUID SourceDimstyle() const;

  // ver 2.0 V6

  void SetExtensionLineColorSource(const ON::object_color_source src);
  ON::object_color_source ExtensionLineColorSource() const;
  void SetDimensionLineColorSource(const ON::object_color_source src);
  ON::object_color_source DimensionLineColorSource() const;
  void SetArrowColorSource(const ON::object_color_source src);
  ON::object_color_source ArrowColorSource() const;
  void SetExtensionLineColor(ON_Color c);
  ON_Color ExtensionLineColor() const;
  void SetDimensionLineColor(ON_Color c);
  ON_Color DimensionLineColor() const;
  void SetArrowColor(ON_Color c);
  ON_Color ArrowColor() const;
  void SetTextColor(ON_Color c);
  ON_Color TextColor() const;

  void SetExtensionLinePlotColorSource(const ON::plot_color_source src);
  ON::plot_color_source ExtensionLinePlotColorSource() const;
  void SetDimensionLinePlotColorSource(const ON::plot_color_source src);
  ON::plot_color_source DimensionLinePlotColorSource() const;
  void SetArrowPlotColorSource(const ON::plot_color_source src);
  ON::plot_color_source ArrowPlotColorSource() const;
  void SetExtensionLinePlotColor(ON_Color c);
  ON_Color ExtensionLinePlotColor() const;
  void SetDimensionLinePlotColor(ON_Color c);
  ON_Color DimensionLinePlotColor() const;
  void SetArrowPlotColor(ON_Color c);
  ON_Color ArrowPlotColor() const;
  void SetTextPlotColor(ON_Color c);
  ON_Color TextPlotColor() const;

  void SetExtensionLinePlotWeightSource(const ON::plot_weight_source src);
  ON::plot_weight_source ExtensionLinePlotWeightSource() const;
  void SetDimensionLinePlotWeightSource(const ON::plot_weight_source src);
  ON::plot_weight_source DimensionLinePlotWeightSource() const;
  void SetExtensionLinePlotWeight(double w);
  double ExtensionLinePlotWeight() const;
  void SetDimensionLinePlotWeight(double w);
  double DimensionLinePlotWeight() const;

  void SetFixedExtensionLen(double l);
  double FixedExtensionLen() const;
  void SetFixedExtensionLenOn(bool on);
  bool FixedExtensionLenOn() const;
  void SetTextRotation(double r);
  double TextRotation() const;
  void SetAlternateToleranceResolution(int r);
  int AlternateToleranceResolution() const;
  //void SetAlternateTolHeightFraction(double f);
  //double AltTolHeightFraction() const;
  void SetSuppressArrow1(bool s);
  bool SuppressArrow1() const;
  void SetSuppressArrow2(bool s);
  bool SuppressArrow2() const;
  void SetTextMoveLeader(int m);
  int TextMoveLeader() const;
  void SetArcLengthSymbol(int m);
  int ArcLengthSymbol() const;
  void SetStackFractionFormat(int f);
  int StackFractionFormat() const;
  void SetStackHeightFraction(double f);
  double StackHeightFraction() const;
  void SetRoundOff(double r);
  double RoundOff() const;
  void SetAlternateRoundOff(double r);
  double AlternateRoundOff() const;
  void SetZeroSuppress(int s);
  int ZeroSuppress() const;
  void SetAlternateZeroSuppress(int s);
  int AlternateZeroSuppress() const;
  void SetToleranceZeroSuppress(int s);
  int ToleranceZeroSuppress() const;
  void SetAngleZeroSuppress(int s);
  int AngleZeroSuppress() const;
  void SetAlternateBelow(bool below);
  bool AlternateBelow() const;
  void SetArrowType1(ON_Arrowhead::arrow_type);  // ON_Dimension derived dimensions
  ON_Arrowhead::arrow_type ArrowType1() const;
  void SetArrowBlockId1(ON_UUID id);
  ON_UUID ArrowBlockId1() const;
  void SetArrowType2(ON_Arrowhead::arrow_type);
  ON_Arrowhead::arrow_type ArrowType2() const;
  void SetArrowBlockId2(ON_UUID id);
  ON_UUID ArrowBlockId2() const;
  const ON_Arrowhead& Arrowhead1() const;
  const ON_Arrowhead& Arrowhead2() const;



  // Defaults for values stored in Userdata extension - needed to read and write pre-v6 files
  static int      DefaultToleranceStyle();
  static int      DefaultToleranceResolution();
  static double   DefaultToleranceUpperValue();
  static double   DefaultToleranceLowerValue();
  static double   DefaultToleranceHeightScale();
  static double   DefaultBaselineSpacing();
  static bool     DefaultDrawTextMask(); // false
  static int      DefaultMaskColorSource(); // 0;
  static ON_Color DefaultMaskColor(); // .SetRGB(255,255,255);
  static double   DefaultDimScale(); // 1.0;
  static int      DefaultDimScaleSource(); // 0;

  bool CompareFields(const ON_V5x_DimStyle& other) const;

public:
  double m_extextension = 0.5; // extension line extension
  double m_extoffset = 0.5;    // extension line offset
  double m_arrowsize = 1.0;  // length of an arrow - may mean different things to different arrows
  double m_centermark = 0.5; // size of the + at circle centers
  double m_textgap = 0.25;    // gap around the text for clipping dim line
  double m_textheight = 1.0; // model unit height of dimension text before applying dimscale
  ON_INTERNAL_OBSOLETE::V5_TextDisplayMode m_dimstyle_textalign = ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine;   // text alignment relative to the dimension line
  int m_arrowtype = 0;     // 0: filled narrow triangular arrow  - For ON_OBSOLETE_V2_Annotation & ON_OBSOLETE_V5_Annotation derived dimensnions
  // m_arrowtype = ((ON_Arrowhead::arrow_type enum value as int) - 2)
  int m_angularunits = 0;  // 0: degrees, 1: radians
  int m_lengthformat = 0;  // 0: decimal, 1: fractional, 2: feet & inches
  int m_angleformat = 0;   // 0: decimal degrees, 1:DMS, ...
  int m_angleresolution = 2;    // for decimal degrees, digits past decimal
  int m_lengthresolution = 2;   // depends on m_lengthformat
                            // for decimal, digits past the decimal point
private:
  ON_TextStyle m_v5_text_style = ON_TextStyle::Default;

public:
  // added fields version 1.2, Jan 13, 05
  double m_lengthfactor = 1.0;  // (dimlfac) model units multiplier for length display

  bool m_bAlternate = false;      // (dimalt) display alternate dimension string (or not)
                          // using m_alternate_xxx values

  double m_alternate_lengthfactor = 1.0;  // (dimaltf) model units multiplier for alternate length display
  int m_alternate_lengthformat = 0;     // 0: decimal, 1: feet, 2: feet & inches
  int m_alternate_lengthresolution = 2; // depends on m_lengthformat
                                    // for decimal, digits past the decimal point

  int m_alternate_angleformat = 0;      // 0: decimal degrees, ...
  int m_alternate_angleresolution = 2;  // for decimal degrees, digits past decimal

  ON_wString m_prefix;              // string preceding dimension value string
  ON_wString m_suffix;              // string following dimension value string
  ON_wString m_alternate_prefix;    // string preceding alternate value string
  ON_wString m_alternate_suffix;    // string following alternate value string

private:
  ///unsigned int m_valid = 0;        // Obsolete deprecated field to be removed - Do not use
public:

  // field added version 1.4, Dec 28, 05
  double m_dimextension = 0.0;  // (dimdle) dimension line extension past the "tip" location

  // fields added version 1.5 Mar 23 06
  double m_leaderarrowsize = 1.0;       // Like dimension arrow size but applies to leaders
  int    m_leaderarrowtype = 0;       // Like dimension arrow type but applies to leaders
  bool   m_bSuppressExtension1 = false;   // flag to not draw extension lines
  bool   m_bSuppressExtension2 = false;   // flag to not draw extension lines

private:
  friend class ON_DimStyleExtra;
  // 8 Apr, 2014 - The next few fields were transferred from ON_DimStyleExtra for V6
  /// Use ON_ModelComponent.ParentId() /// ON_UUID m_parent_dimstyle = ON_nil_uuid;  // ON_nil_uuid if there is no parent dimstyle
  unsigned int m_field_override_count = 0; // number of 
  bool m_field_override[ON_V5x_DimStyle::FieldCount];

public:
  int    m_tolerance_style = 0;
  int    m_tolerance_resolution = 4;
  double m_tolerance_upper_value = 0.0;   // or both upper and lower in symmetrical style
  double m_tolerance_lower_value = 0.0;
  double m_tolerance_height_scale = 1.0;  // relative to the main dimension text

  double m_baseline_spacing = 1.0;

  // Text mask - added Dec 12 2009
  bool     m_bDrawMask = false;
  int      m_mask_color_source = 0;
  ON_Color m_mask_color = ON_Color::White;

  // Per dimstyle DimScale added Dec 16, 2009
  double   m_dimscale = 1.0;
  int      m_dimscale_source = 0;

  // 19 Oct 2010 - Added uuid of source dimstyle to restore defaults
  ON_UUID  m_source_dimstyle = ON_nil_uuid;
  // End of fields that were in ON_DimStyleExtra

  // Fields added for V6, ver 2.0

  unsigned char   m_ext_line_color_source = 0;
  unsigned char   m_dim_line_color_source = 0;
  unsigned char   m_arrow_color_source = 0;
  unsigned char   m_text_color_source = 0;
  ON_Color        m_ext_line_color = ON_Color::Black;
  ON_Color        m_dim_line_color = ON_Color::Black;
  ON_Color        m_arrow_color = ON_Color::Black;
  ON_Color        m_text_color = ON_Color::Black;
  unsigned char   m_ext_line_plot_color_source = 0;
  unsigned char   m_dim_line_plot_color_source = 0;
  unsigned char   m_arrow_plot_color_source = 0;
  unsigned char   m_text_plot_color_source = 0;
  ON_Color        m_ext_line_plot_color = ON_Color::Black;
  ON_Color        m_dim_line_plot_color = ON_Color::Black;
  ON_Color        m_arrow_plot_color = ON_Color::Black;
  ON_Color        m_text_plot_color = ON_Color::Black;
  unsigned char   m_ext_line_plot_weight_source = 0;
  unsigned char   m_dim_line_plot_weight_source = 0;
  double          m_ext_line_plot_weight_mm = 0.0;
  double          m_dim_line_plot_weight_mm = 0.0;

  double          m_fixed_extension_len = 1.0;        // Fixed extension line length if m_fixed_extension_len_on is true
  bool            m_fixed_extension_len_on = false;     // true: use fixed_extension_len, false: don't use m_fixed_extension_len
  double          m_text_rotation = 0.0;              // Dimension text rotation around text point (radians)
  int             m_alt_tol_resolution = 4;         // for decimal, digits past the decimal point, fractions: 1/2^n
  double          m_tol_textheight_fraction = 1.0;    // fraction of main text height
  bool            m_suppress_arrow1 = false;            // false: dont suppress, true: suppress
  bool            m_suppress_arrow2 = false;            // false: dont suppress, true: suppress
  int             m_textmove_leader = 0;            // 0: move text anywhere, 1: add leader when moving text
  int             m_arclength_sym = 0;              // 0: symbol before dim text, 1: symbol above dim text, no symbol
  double          m_stack_textheight_fraction = 1.0;  // fraction of main text height
  int             m_stack_format = 0;               // 0: no stacking, 1: horizontal, 2: diagonal
  double          m_alt_round = 0.0;                  // rounds to nearest specified value
  double          m_round = 0.0;                     
  int             m_alt_zero_suppress = 0;          //  0: no zero suppressing
  int             m_tol_zero_suppress = 0;          //  1: suppress zero feet
  int             m_zero_suppress = 0;              //  2: suppress zero inches
  int             m_ang_zero_suppress = 0;          //  3: suppress both zero feet and 0 inches
                                                //  4: suppress leading zeros
                                                //  8: suppress trailing zeros
                                                // 12: suppress both leading and trailing zeros
  bool            m_alt_below = false;                  // true: display alternate text below main text
                                                // true: display alternate text after main text
  //ON_Arrowhead::arrow_type m_arrow_type_1;      // Arrow types for ON_Dimension derived dimensions
  //ON_Arrowhead::arrow_type m_arrow_type_2;
  //ON_wString      m_dim_arrow_block1;
  //ON_wString      m_dim_arrow_block2;

  ON_Arrowhead    m_arrow_1;
  ON_Arrowhead    m_arrow_2;
};

void ON_Internal_FixBogusDimStyleLengthFactor(
  const class ON_BinaryArchive& file,
  double& dimstyle_length_factor
);

#endif

#endif
