//
// Copyright (c) 1993-2023 Robert McNeel & Associates. All rights reserved.
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

#if !defined(OPENNURBS_SECTIONSTYLE_INC_)
#define OPENNURBS_SECTIONSTYLE_INC_


//////////////////////////////////////////////////////////////////////
// class ON_SectionStyle

class ON_CLASS ON_SectionStyle : public ON_ModelComponent
{
  ON_OBJECT_DECLARE(ON_SectionStyle);

public:
  ON_SectionStyle() ON_NOEXCEPT;
  ~ON_SectionStyle();
  ON_SectionStyle(const ON_SectionStyle& other);
  ON_SectionStyle& operator=(const ON_SectionStyle& other);

  static const ON_SectionStyle Unset;   // index = ON_UNSET_INT_INDEX, id = nil

  /*
    Description:
      Tests that name is set and there is at least one non-zero length segment
  */
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  void Dump( ON_TextLog& ) const override; // for debugging

  /*
    Description:
      Write to file (serialize definition to binary archive)
  */
  bool Write(ON_BinaryArchive&) const override;

  /*
    Description:
      Read from file (restore definition from binary archive)
  */
  bool Read(ON_BinaryArchive&) override;


  /*
    Description:
      Test only the section style attributes below for equality. Does not
      perform any testing of the ON_ModelComponent fields
    Parameters:
      other: other section style to compare against this
  */
  bool SectionAttributesEqual(const ON_SectionStyle& other) const;

#pragma region RH_C_SHARED_ENUM [SectionBackgroundFillMode] [Rhino.DocObjects.SectionBackgroundFillMode] [byte]
  /// <summary>
  /// Defines how a background fill is applied to a section
  /// </summary>
  enum class SectionBackgroundFillMode : unsigned char
  {
    /// <summary>
    /// Do not fill in the background of a section
    /// </summary>
    None = 0,
    /// <summary>
    /// Use the current display mode settings to determine how to apply a fill.
    /// Wireframe will not fill while shaded and rendered will fill using colors
    /// and materials matching how the object is drawn.
    /// </summary>
    Viewport = 1,
    /// <summary>
    /// Use a solid color for a background fill. If BackgroundFillColor is set
    /// on this section style, then that color will be used. Otherwise, the item's
    /// color that this section style is associated will be used
    /// </summary>
    SolidColor = 2
  };
#pragma endregion

  // How a background fill is applied
  SectionBackgroundFillMode BackgroundFillMode() const;
  void SetBackgroundFillMode(SectionBackgroundFillMode mode);


  // Custom background fill color. If unset (default), the object's color or
  // material is used for a fill
  ON_Color BackgroundFillColor(bool print) const;
  void SetBackgroundFillColor(const ON_Color& color, bool print);

  // Should the boundary curves for a section be shown (default is true)
  bool BoundaryVisible() const;
  void SetBoundaryVisible(bool on);

  // Custom boundary color for a section. If unset (default), the object's
  // color is used
  ON_Color BoundaryColor(bool print) const;
  void SetBoundaryColor(const ON_Color& color, bool print);

  // Width scale to apply to an object's linetype for sections. Default is 3
  double BoundaryWidthScale() const;
  void SetBoundaryWidthScale(double scale);

  // When to fill/hatch the sections for an object can depend on the type of
  // object being sectioned. See ON_SectionFillRule for the choices of
  // when to generate hatches.
  ON::SectionFillRule SectionFillRule() const;
  void SetSectionFillRule(ON::SectionFillRule rule);

  // Hatch pattern index for hatch to use when drawing a closed section
  // Default is ON_UNSET_INT_INDEX which means don't draw a hatch
  int HatchIndex() const;
  void SetHatchIndex(int index);

  // Scale applied to the hatch pattern for a section
  double HatchScale() const;
  void SetHatchScale(double scale);

  // Rotation angle in radians applied to hatch pattern for a section.
  double HatchRotation() const;
  void SetHatchRotation(double rotation);

  // Custom hatch pattern color for a section. If unset (default), the object's
  // color is used
  ON_Color HatchColor(bool print) const;
  void SetHatchColor(const ON_Color& color, bool print);

  // Section styles can have custom linetypes. If null, then the linetype is retrieved
  // from the parent layer or attributes
  const ON_Linetype* BoundaryLinetype() const;
  void SetBoundaryLinetype(const ON_Linetype& linetype);
  void RemoveBoundaryLinetype();
private:
  class ON_SectionStylePrivate* m_private = nullptr;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_SectionStyle*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<const ON_SectionStyle*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_ObjectArray<ON_SectionStyle>;
#endif

#endif

