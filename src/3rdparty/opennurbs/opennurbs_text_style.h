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


#if !defined(OPENNURBS_TEXT_STYLE_INC_)
#define OPENNURBS_TEXT_STYLE_INC_


class ON_CLASS ON_TextStyle : public ON_ModelComponent
{
  ON_OBJECT_DECLARE(ON_TextStyle);

public:
  static const ON_TextStyle Unset;    // All values not set
  static const ON_TextStyle Default;  // index = -1, font set
  static const ON_TextStyle ByLayer;  // index = -2, no font
  static const ON_TextStyle ByParent; // index = -3, no font

  /*
  Parameters:
    model_component_reference - [in]
    none_return_value - [in]
      value to return if ON_TextStyle::Cast(model_component_ref.ModelComponent())
      is nullptr
  Returns:
    If ON_TextStyle::Cast(model_component_ref.ModelComponent()) is not nullptr,
    that pointer is returned.  Otherwise, none_return_value is returned. 
  */
  static const ON_TextStyle* FromModelComponentRef(
    const class ON_ModelComponentReference& model_component_reference,
    const ON_TextStyle* none_return_value
    );

  ON_TextStyle();
  ~ON_TextStyle() = default;
  ON_TextStyle(const ON_TextStyle&);
  ON_TextStyle& operator=(const ON_TextStyle&);

private:
  void Internal_Copy(
    const ON_TextStyle& src 
    );

public:
  /*
  Returns:
    The managed font for this text style.
    Returns ON_Font::Default if the font is not set.
  */
  const ON_Font& Font() const;

  const ON_wString& FontDescription() const;

  const wchar_t* FontDescriptionAsPointer() const;

  const ON_wString& AppleFontName() const;

  const wchar_t* AppleFontNameAsPointer() const;

  /*
  Parameters:
    font_characteristics - [in]
  */
  void SetFont(
    const ON_Font* font_characteristics
    );
  void SetFont(
    const ON_Font& font_characteristics
    );

  /*
  Parameters:
    font_description - [in]
      If font_description is an empty string, then SetFont( alternate_font ) 
      is called.
    alternate_font - [in]
      Font to use if the current runtime environment does not have a
      font with a matching font description.
      When alternate_font is nullptr, ON_Font::Default will be used as
      the alternate font.
  */
  void SetFontFromDescription(
    const wchar_t* font_description,
    const wchar_t* apple_font_name,
    const ON_Font* alternate_font
    );

  void ClearFont();

  bool FontIsSet() const;

  void LockFont();
  bool FontIsLocked() const;

  /*
  Description:
    Get a string with the text style name and font description.
  Parameters:
    sSeparator - [in]
      string that separates the text style name and the font description.
      For example, if sSeparator = " - ", then 
      name_and_font_description = "<text style name> - <font description>".
    name_and_font_description - [out]
  Returns:
    A pointer to the string in name_and_font_description.  This pointer is never
    nullptr.    
  */
  const wchar_t* GetNameAndFontDescription(
    const wchar_t* sSeparator,
    ON_wString& name_and_font_description
    ) const;

  static bool EqualTextStyleFontAndName(
    const ON_TextStyle& a,
    const ON_TextStyle& b
    );

private:  
  // V5 files had a single string used for different purposes
  // on Windows and Apple platforms. These two strings are runtime
  // information.
  ON_wString m_font_description;

  ON_wString m_apple_font_name;

  // m_managed_font points to a managed ON_Font and is the font returned by Font().
  const ON_Font* m_managed_font = nullptr;
 
  enum : unsigned char {
    font_bit = 1
  };

  unsigned char m_is_set_bits = 0;
  unsigned char m_is_locked_bits = 0;

  unsigned char m_reserved1 = 0;
  unsigned int m_reserved2 = 0;
  ON__UINT_PTR m_reserved_ptr_1 = 0;
  ON__UINT_PTR m_reserved_ptr_2 = 0;
  double m_reserved_double_0 = 0.0;
  double m_reserved_double_1 = 0.0;

public:
  // overrides virtual ON_Object::IsValid
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  // overrides virtual ON_Object::IsValid
  void Dump( ON_TextLog& ) const override;

  // On September 16, 2015 the "V5" ON_Font was split into
  //   ON_TextStyle (a document object) and
  //   ON_Font (a current runtime resource)
  //   = ON_VersionNumberConstruct(6, 0, 2015, 9, 16, 0)
  //   Versions of opennurbs before binary_archive_opennurbs_version
  //   serialized ON_TextStyle information in the V5 ON_Font format.
  static const unsigned int binary_archive_opennurbs_version;

  // overrides virtual ON_Object::Write
  bool Write( ON_BinaryArchive& ) const override;

  // overrides virtual ON_Object::Read
  bool Read( ON_BinaryArchive& ) override;

};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_TextStyle*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_ObjectArray<ON_TextStyle>;
#endif

#endif
