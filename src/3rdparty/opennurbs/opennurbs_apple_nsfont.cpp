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

#if defined(ON_RUNTIME_APPLE_CORE_TEXT_AVAILABLE)

#include "opennurbs_internal_glyph.h"
#include "opennurbs_apple_nsfont.h"

class ON_AppleCTFontInformation
{
  // "fake class" (for now)
public:
  ON_AppleCTFontInformation() = default;
  ~ON_AppleCTFontInformation() = default;
  ON_AppleCTFontInformation(const ON_AppleCTFontInformation&) = default;
  ON_AppleCTFontInformation& operator=(const ON_AppleCTFontInformation&) = default;
private:
  ON__UINT_PTR m_nothing = 0;
};

ON_Font::ON_Font(
  ON_Font::FontType font_type,
  const class ON_AppleCTFontInformation& apple_font_information
)
: m_font_type(font_type)
{}

void ON_ManagedFonts::Internal_GetAppleInstalledCTFonts(
  ON_SimpleArray<const ON_Font*>& platform_font_list
)
{
  ON_AppleCTFontInformation currently_nothing;
  
  CFDictionaryRef options = nullptr;
  CTFontCollectionRef availableFontCollection = CTFontCollectionCreateFromAvailableFonts(options);
  if (nullptr == availableFontCollection )
    return;
  CFArrayRef availableFontArray = CTFontCollectionCreateMatchingFontDescriptors(availableFontCollection);
  CFRelease(availableFontCollection);
  if (nullptr == availableFontArray)
    return;
  const CFIndex count = CFArrayGetCount(availableFontArray);
  platform_font_list.Reserve((int)count);
  for ( CFIndex idx = 0; idx < count; idx++)
  {
    CTFontDescriptorRef descriptor = (CTFontDescriptorRef)CFArrayGetValueAtIndex(availableFontArray, idx);
    if (nullptr == descriptor)
      continue;
    const CGAffineTransform *matrix = nullptr;
    CGFloat size = 1000;
    CTFontRef font = CTFontCreateWithFontDescriptor(descriptor, size, matrix);
    if (nullptr == font)
      continue;

    const unsigned int units_per_em = CTFontGetUnitsPerEm(font);
    if ( units_per_em > 0 && (CGFloat)units_per_em != size )
    {
      CFRelease(font);
      size = (CGFloat)units_per_em;
      font = CTFontCreateWithFontDescriptor(descriptor, size, matrix);
      if (nullptr == font)
        continue;
    }
    
    // It is critical that m_font_type = ON_Font::FontType::InstalledFont
    ON_Font* platform_font = new ON_Font(ON_Font::FontType::InstalledFont,currently_nothing);
    
    if (false == platform_font->SetFromAppleCTFont(font, false))
    {
      CFRelease(font);
      delete platform_font;
      continue;
    }

    CFRelease(font);
    platform_font->SetPointSize(0);
    platform_font_list.Append(platform_font);
  }
  CFRelease(availableFontArray);
}

const ON_Font* ON_Font::GetManagedFontFromAppleCTFont(
  CTFontRef apple_font,
  bool bAnnotationFont
)
{
  ON_Font font_characteristics;
  if ( false == font_characteristics.SetFromAppleCTFont(apple_font,bAnnotationFont) )
    return nullptr;
  return font_characteristics.ManagedFont();
}

unsigned int ON_Font::AppleCTFontUnitsPerEm(CTFontRef apple_font)
{
  const unsigned int units_per_em
    = (nullptr != apple_font)
    ? CTFontGetUnitsPerEm(apple_font)
    : 0;
  return units_per_em;
}


CTFontRef ON_Font::AppleCTFontSetSize(
  CTFontRef apple_font,
  CGFloat size,
  bool bReleaseOriginal
)
{
  for(;;)
  {
    if (nullptr == apple_font)
      break;
    const unsigned int units_per_em = ON_Font::AppleCTFontUnitsPerEm(apple_font);
    if ( units_per_em <= 0 )
      break;
    const CGFloat units_per_em_size = (CGFloat)units_per_em;
    if ( !(units_per_em_size > 0.0) )
      break;
    const CGFloat size0 = CTFontGetSize(apple_font);
    if ( fabs(size0 - units_per_em_size) <= 0.0001 )
      break;
    
    const CGAffineTransform *matrix = nullptr;
    CTFontDescriptorRef attributes = nullptr;
    CTFontRef apple_font1 = CTFontCreateCopyWithAttributes(apple_font, units_per_em_size, matrix, attributes);
    if ( nullptr == apple_font1)
      break;
    
    const unsigned int units_per_em1 = CTFontGetUnitsPerEm(apple_font1);
    if ( units_per_em1 != units_per_em)
    {
      CFRelease(apple_font1);
      break;
    }
    
    if (bReleaseOriginal)
      CFRelease(apple_font);
    return apple_font1;
  }
  return apple_font;
}

ON_PANOSE1 ON_Font::AppleCTFontPANOSE1(CTFontRef apple_font)
{
  ON_PANOSE1 panose1 = ON_PANOSE1::Zero;
  
  CFDataRef os2Table = nullptr;
  for(;;)
  {
    if (nullptr == apple_font)
      break;
    
    // The OS/2 table contains the PANOSE1 classification
    os2Table = CTFontCopyTable(apple_font, kCTFontTableOS2, kCTFontTableOptionNoOptions);
    
    if (nullptr == os2Table)
      break;
    
    // The PANOSE data is in bytes 32-42 of the table according to the TrueType and OpenType specs.
    if (CFDataGetLength(os2Table) < 42)
    {
      // Truncated table?
      break;
    }
    
    uint8_t panose[10] = {};
    CFDataGetBytes(os2Table, (CFRange){ 32, 10 }, panose);
    if (panose[0] > 5)
      break; // invalid PANOSE1 family kind
    
    panose1.SetTenBytes(panose);
    break;
  }
  if (nullptr != os2Table)
    CFRelease(os2Table);
  
  return panose1;
}

bool ON_Font::SetFromAppleCTFont(CTFontRef apple_font, bool bAnnotationFont)
{
  if (nullptr == apple_font)
    return false;
  
  if ( false == this->ModificationPermitted(OPENNURBS__FUNCTION__,__FILE__,__LINE__) )
    return false;
  
  *this = ON_Font::Unset;
  
  const ON_wString postscript_name = ON_Font::AppleCTFontPostScriptName(apple_font);
  const ON_wString family_name = ON_Font::AppleCTFontFamilyName(apple_font);
  const ON_wString face_name = ON_Font::AppleCTFontFaceName(apple_font);
  
  // Set Windows LOGFONT.lfFaceName to something not empty there is some hope this
  // font might work in Rhino 6/7 for Windows too.
  const ON_wString windows_logfont_name = ON_Font::FakeWindowsLogfontNameFromFamilyAndPostScriptNames(family_name, postscript_name);
  
  const bool rc = postscript_name.IsNotEmpty() || family_name.IsNotEmpty();
  if (rc)
  {
    m_loc_postscript_name = postscript_name;
    m_en_postscript_name = postscript_name;
    m_loc_family_name = family_name;
    m_en_family_name = family_name;
    m_loc_face_name = face_name;
    m_en_face_name = face_name;
    m_loc_windows_logfont_name = windows_logfont_name;
    m_en_windows_logfont_name = windows_logfont_name;
    
    // Can get font metrics from NSFontDescriptor
    // https://developer.apple.com/library/content/documentation/TextFonts/Conceptual/CocoaTextArchitecture/FontHandling/FontHandling.html
    // defaultLineHeight(for theFont: NSFont)
    // fd.xHeight, fd.ascender, fd.descender, fd.capHeight, fd.defaultLineHeightForFont
    
    // Set weight - used if this font needs sustution on another computer
    // https://mcneel.myjetbrains.com/youtrack/issue/RH-37075
    
    double apple_font_weight_trait = ON_UNSET_VALUE;
    double apple_font_width_trait = ON_UNSET_VALUE;
    double apple_font_slant_trait = ON_UNSET_VALUE;
    ON_Font::Weight weight = ON_Font::Weight::Normal;
    ON_Font::Style style = ON_Font::Style::Upright;
    ON_Font::Stretch stretch = ON_Font::Stretch::Medium;

    CTFontDescriptorRef descriptor = CTFontCopyFontDescriptor(apple_font);
    if (nullptr != descriptor)
    {
      CFDictionaryRef dict = (CFDictionaryRef)CTFontDescriptorCopyAttribute(descriptor, kCTFontTraitsAttribute);
      if (nullptr != dict)
      {
        const CFNumberRef appleSymbolicTrait = (CFNumberRef)CFDictionaryGetValue(dict, kCTFontSymbolicTrait);
        const CFNumberRef appleWeight = (CFNumberRef)CFDictionaryGetValue(dict, kCTFontWeightTrait);
        const CFNumberRef appleWidth = (CFNumberRef)CFDictionaryGetValue(dict, kCTFontWidthTrait);
        const CFNumberRef appleSlant = (CFNumberRef)CFDictionaryGetValue(dict, kCTFontSlantTrait);
        
        if (nullptr != appleSymbolicTrait)
        {
          int i=0;
          if ( CFNumberGetValue(appleSymbolicTrait, kCFNumberIntType, &i) )
          {
            // Use the kCTFontSymbolicTrait key to access the symbolic traits value from the font traits dictionary.
            // The value is returned as a CFNumberRef.
            if (0 != (kCTFontTraitItalic & i))
              style = ON_Font::Style::Italic;
            if (0 != (kCTFontTraitBold & i))
              weight = ON_Font::Weight::Bold;
            if (0 != (kCTFontTraitCondensed & i))
              stretch = ON_Font::Stretch::Condensed;
            else if (0 != (kCTFontTraitExpanded & i))
              stretch = ON_Font::Stretch::Expanded;
          }
        }
        
        if (nullptr != appleWeight)
        {
          double x = apple_font_weight_trait;
          if ( CFNumberGetValue(appleWeight, kCFNumberFloat64Type, &x) && -1.0 <= x && x <= 1.0)
          {
            // Use the kCTFontWeightTrait key to access the normalized weight trait from the font traits dictionary.
            // The value returned is a CFNumberRef representing a float value between -1.0 and 1.0 for normalized weight.
            // The value of 0.0 corresponds to the regular or medium font weight.
            apple_font_weight_trait = x;
            ON_Font::WeightFromAppleFontWeightTrait(apple_font_weight_trait);
          }
        }
        
        if (nullptr != appleWidth)
        {
          double x = apple_font_width_trait;
          if ( CFNumberGetValue(appleWidth, kCFNumberFloat64Type, &x) && -1.0 <= x && x <= 1.0 )
          {
            // Use the kCTFontWidthTrait key to access the normalized proportion trait from the font traits dictionary.
            // This value corresponds to the relative inter-glyph spacing for a given font.
            // The value returned is a CFNumberRef representing a float between -1.0 and 1.0.
            // The value of 0.0 corresponds to regular glyph spacing while negative values represent condensed glyph spacing.
            apple_font_width_trait = x;
            if (-1.0 == apple_font_width_trait)
              stretch = ON_Font::Stretch::Condensed;
            else if (1.0 == apple_font_width_trait)
              stretch = ON_Font::Stretch::Expanded;
          }
        }
        
        if (nullptr != appleSlant)
        {
          double x = apple_font_weight_trait;
          if ( CFNumberGetValue(appleSlant, kCFNumberFloat64Type, &x) && -1.0 <= x && x <= 1.0 )
          {
            // Use this key to access the normalized slant angle from the font traits dictionary.
            // The value returned is a CFNumberRef representing a float value between -1.0 and 1.0 for normalized slant angle.
            // The value or 0.0 corresponds to 0 degree clockwise rotation from the vertical and 1.0 corresponds to 30 degrees clockwise rotation.
            apple_font_slant_trait = x;
            if (1.0 == apple_font_slant_trait)
              style = ON_Font::Style::Italic;
          }
        }
        CFRelease(dict);
      }
      CFRelease(descriptor);
    }
    
    if (-1.0 <= apple_font_weight_trait && apple_font_weight_trait <= 1.0)
      SetAppleFontWeightTrait(apple_font_weight_trait);
    else
      SetFontWeight(weight);
    
    m_font_style = style;
    m_font_stretch = stretch;
    
    // Saving point size added January 2018.
    const double point_size = (double)CTFontGetSize(apple_font);
    m_point_size
    = (false == bAnnotationFont && ON_Font::IsValidPointSize(point_size) && point_size < ((double)ON_Font::AnnotationFontApplePointSize))
    ? point_size
    : 0.0; // indicates annotation size (units per em) will be used
    
    m_logfont_charset = ON_Font::WindowsConstants::logfont_default_charset;
    
    // do this again because some of the above calls can modify description
    m_loc_postscript_name = postscript_name;
    m_en_postscript_name = m_loc_postscript_name;
    m_loc_family_name = family_name;
    m_en_family_name = m_loc_family_name;
    m_loc_face_name = face_name;
    m_en_face_name = m_loc_face_name;
    m_loc_windows_logfont_name = windows_logfont_name;
    m_en_windows_logfont_name = m_loc_windows_logfont_name;
    m_panose1 = ON_Font::AppleCTFontPANOSE1(apple_font);
    
    SetFontOrigin(ON_Font::Origin::AppleFont);

    if (-1.0 <= apple_font_weight_trait && apple_font_weight_trait <= 1.0)
      m_apple_font_weight_trait = apple_font_weight_trait;

    if (-1.0 <= apple_font_width_trait && apple_font_width_trait <= 1.0)
      m_apple_font_width_trait = apple_font_width_trait;
    else
      m_apple_font_width_trait = ON_UNSET_VALUE;
  }
  
  return rc;
}

const ON_wString ON_Font::AppleCTFontPostScriptName(
  CTFontRef apple_font
)
{
  if (nullptr == apple_font)
    return ON_wString::EmptyString;
  
  CFStringRef applePostScriptName = CTFontCopyPostScriptName(apple_font);
  ON_wString postscript_name(applePostScriptName);
  if (nullptr != applePostScriptName)
    CFRelease(applePostScriptName);
  postscript_name.TrimLeftAndRight();
  return postscript_name;
}


const ON_wString ON_Font::AppleCTFontFamilyName(
  CTFontRef apple_font
)
{
  CFStringRef appleFamilyName = CTFontCopyFamilyName(apple_font);
  ON_wString family_name(appleFamilyName);
  if (nullptr != appleFamilyName)
    CFRelease(appleFamilyName);
  family_name.TrimLeftAndRight();
  return family_name;
}


const ON_wString ON_Font::AppleCTFontDisplayName(
  CTFontRef apple_font
)
{
  CFStringRef appleDisplayName = CTFontCopyDisplayName(apple_font);
  ON_wString display_name(appleDisplayName);
  if (nullptr != appleDisplayName)
    CFRelease(appleDisplayName);
  display_name.TrimLeftAndRight();
  return display_name;
}

static const ON_wString Internal_FaceNameFromAppleDisplayAndFamilyName(
 const ON_wString& appleFontDisplayName,
 const ON_wString& appleFontFamilyName
)
{
  if ( appleFontDisplayName.IsEmpty() || appleFontFamilyName.IsEmpty())
    return ON_wString::EmptyString;
  
  const wchar_t* family_and_face_str = static_cast<const wchar_t*>(appleFontDisplayName);
  const wchar_t* family_str = static_cast<const wchar_t*>(appleFontFamilyName);
  if (nullptr == family_and_face_str || nullptr == family_str)
    return ON_wString::EmptyString;
  
  // It is not always the case that the beginning of
  // appleFontDisplayName exactly matches
  // appleFontFamilyName.
  // We need to ignore spaces and hyphens.
  for (;;)
  {
    wchar_t a = *family_str;
    while (ON_wString::Space == a || ON_wString::HyphenMinus == a)
      a = *(++family_str);
    
    wchar_t b = *family_and_face_str;
    while (ON_wString::Space == b || ON_wString::HyphenMinus == b)
      b = *(++family_and_face_str);
    
    if (0 == a || 0 == b)
      break;
    a = ON_wString::MapCharacterOrdinal(ON_StringMapOrdinalType::MinimumOrdinal,a);
    b = ON_wString::MapCharacterOrdinal(ON_StringMapOrdinalType::MinimumOrdinal,b);
    if (a != b)
      break;
    family_str++;
    family_and_face_str++;
  }
  for(wchar_t c = *family_and_face_str; ON_wString::Space == c || ON_wString::HyphenMinus == c; c = *family_and_face_str )
    ++family_and_face_str;
  ON_wString face_name(family_and_face_str);
  face_name.TrimRight();
  if ( face_name.IsEmpty())
  {
    // This is what Apple MacOS uses in FontBook and other font selection UI.
    // https://developer.apple.com/documentation/appkit/nsfontmanager/1462316-availablemembersoffontfamily?language=objc
    // A more complicated approach that yields the same results is:
    // https://developer.apple.com/documentation/coretext/1511240-ctfontcopyname?language=objc
    // using kCTFontSubFamilyNameKey This retrieves the TrueType "subfamily" font name
    // TrueType names [1]=family [2]=subfamily (which we call "face"), [6] = postscript.
    // Reference: Section 6 of https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=IWS-Chapter08
    //
    // None of the approaches above is localized, so a hard coded English word works as
    // well as using the Apple SDK.
    face_name = L"Regular";
  }
  return face_name;
}

const ON_wString ON_Font::AppleCTFontFaceName(
  CTFontRef apple_font
)
{
  for(;;)
  {
    if (nullptr == apple_font)
      break;
    
    for(;;)
    {
      CFStringRef appleStyleName = CTFontCopyName(apple_font,kCTFontStyleNameKey);
      if (nullptr == appleStyleName)
        break;
      ON_wString style_name(appleStyleName);
      CFRelease(appleStyleName);
      style_name.TrimRight();
      if ( style_name.IsEmpty() )
        break;
      return style_name;
    }
    
    // Fallback - In Sep 12, 2018 tests of 603 faces, the no longer needed with the swtich to CTFont
    // Leaving this here to handle unknown buggy fonts.
    const ON_wString family_and_face_name = ON_Font::AppleCTFontDisplayName(apple_font);
    const ON_wString family_name = ON_Font::AppleCTFontFamilyName(apple_font);
    const ON_wString hack_style_name = Internal_FaceNameFromAppleDisplayAndFamilyName(family_and_face_name,family_name);
    return hack_style_name;
  }
  
  return ON_wString::EmptyString;
}

CTFontRef ON_Font::AppleCTFont(bool& bIsSubstituteFont) const
{
  // Using PointSize() added January 2018.
  bIsSubstituteFont = false;
  const double pointSize
  = ON_Font::IsValidPointSize(m_point_size)
  ? m_point_size
  : 0.0;
  return ON_Font::AppleCTFont(pointSize, bIsSubstituteFont);
}

 CTFontRef ON_Font::AppleCTFont(
   const wchar_t* postscript_name,
   double pointSize,
   bool& bIsSubstituteFont
)
{
  bIsSubstituteFont = false;
  ON_wString local_name(postscript_name);
  local_name.TrimLeftAndRight();
  if (local_name.IsEmpty())
    return nullptr;
  
  const bool bHavePointSize = ( pointSize > 0.0 );
  const CGFloat size = (CGFloat)(bHavePointSize ? pointSize : 1000.0 );
  const CGAffineTransform *matrix = nullptr;
  
  CFStringRef appleName = local_name.ToAppleCFString();
  if (nullptr == appleName)
    return nullptr;
  CTFontRef appleFont = CTFontCreateWithName(appleName, size, matrix);
  CFRelease(appleName);
  if (nullptr == appleFont)
    return nullptr;
  if (false == bHavePointSize)
    appleFont = ON_Font::AppleCTFontSetSize(appleFont, 0.0, true);
  
  if (nullptr != appleFont)
  {
    const ON_wString ctfont_postscript_name = ON_Font::AppleCTFontPostScriptName(appleFont);
    if (false == ON_wString::EqualOrdinal(ctfont_postscript_name, local_name, true))
      bIsSubstituteFont = true;
  }
  
  return appleFont;
}


CTFontRef ON_Font::AppleCTFont(double pointSize, bool& bIsSubstituteFont) const
{
  if (this->IsManagedSubstitutedFont())
  {
    // March 2021 Dale Lear
    // Fixes RH-62974 on Mac platform
    const ON_Font* sub =this->SubstituteFont();
    if (nullptr != sub &&sub->IsInstalledFont())
    {
      if (false == sub->IsManagedSubstitutedFont())
      {
        CTFontRef subref = sub->AppleCTFont( pointSize, bIsSubstituteFont);
        bIsSubstituteFont = true;
        return subref;
      }
    }
  }
  
  const bool bHavePointSize = ( pointSize > 0.0 );
  const CGFloat size = (CGFloat)(bHavePointSize ? pointSize : 1000.0 );
  
  CTFontRef appleCTFont = nullptr;
  ON_wString appleCTFontPostscriptName;
  bIsSubstituteFont = false;
  
  const ON_Font* installed_font = nullptr;
  bool bInstalledFontIsSubstitute = false;
  ON_wString tested_names[7];
  for(int name_dex = 0; name_dex < 7; name_dex++)
  {
    ON_wString name;
    if ( 2 == name_dex)
    {
      installed_font = InstalledFont(true);
      if (nullptr == installed_font)
      {
        bInstalledFontIsSubstitute = true;
        installed_font = &ON_Font::Default;
      }
    }

    switch (name_dex)
    {
      case 0:
        name = m_loc_postscript_name;
        break;
      case 1:
        name = m_en_postscript_name;
        break;
      case 2:
        name = installed_font->m_loc_postscript_name;
        break;
      case 3:
        name = installed_font->m_en_postscript_name;
        break;
      case 4:
        name = installed_font->m_loc_family_name;
        break;
      case 5:
        name = installed_font->m_en_family_name;
        break;
      case 6:
        name = installed_font->Description();
        break;
      default:
        break;
    }
    
    if ( name.IsNotEmpty() )
    {
      for ( int i = 0; i < name_dex; i++ )
      {
        if ( ON_wString::EqualOrdinal(name,tested_names[i],true) )
        {
          name = ON_wString::EmptyString;
          break;
        }
      }
    }
    if ( name.IsEmpty() )
      continue;
    tested_names[name_dex] = name;
    
    bool bCandidateIsSubstitute = false;
    CTFontRef candidate = ON_Font::AppleCTFont(name, size, bCandidateIsSubstitute);
    if (nullptr == candidate)
      continue;
    const ON_wString candidate_name = ON_Font::AppleCTFontPostScriptName(candidate);
    
    if (nullptr == appleCTFont || ON_wString::EqualOrdinal(name,candidate_name,true))
    {
      if (nullptr != appleCTFont)
        CFRelease(appleCTFont);
      appleCTFont = candidate;
      appleCTFontPostscriptName = candidate_name;
      bIsSubstituteFont = bCandidateIsSubstitute || bInstalledFontIsSubstitute;
      if (ON_wString::EqualOrdinal(name, appleCTFontPostscriptName, true))
        break;
    }
    else
      CFRelease(candidate);
  }
  
  if ( nullptr != appleCTFont && false == bHavePointSize)
  {
    // make sure size = font_units_per_em
    appleCTFont = ON_Font::AppleCTFontSetSize(appleCTFont, 0.0, true);
  }
  
  return appleCTFont;
}

static unsigned int Internal_AppleUnitsPerEm( CTFontRef appleFont, double* pointSizeToUPM )
{
  unsigned int font_design_units_per_M = CTFontGetUnitsPerEm(appleFont);
  if ( font_design_units_per_M <= 0 )
  {
    ON_ERROR("CTFontGetUnitsPerEm(appleFont) returned zero.");
    font_design_units_per_M = 1000;
  }
  
  if (nullptr != pointSizeToUPM)
  {
    const double point_size = (double)CTFontGetSize(appleFont);
    const double UPM = font_design_units_per_M;
  
    // This scaling approach recovers correct values in font design units
    // when compared with values from DWrite and FreeType.
    *pointSizeToUPM = (point_size > 0.0 && fabs(point_size-UPM) > 0.001 ) ? (UPM/point_size) : 1.0;
  }
  
  return font_design_units_per_M;
}

void ON_AppleFontGetFontMetrics(
  const ON_Font* font,
  ON_FontMetrics& font_metrics
  )
{
  for (;;)
  {
    if (nullptr == font)
      break;
    
    font = font->ManagedFont();
    if (nullptr == font)
      break;
    
    bool bIsSubstituteFont = false;
    CTFontRef appleFont = font->AppleCTFont(bIsSubstituteFont);
    if (nullptr == appleFont)
      break;
    
    double pointSizeToUPM = 1.0;
    const unsigned int font_design_units_per_M = Internal_AppleUnitsPerEm(appleFont,&pointSizeToUPM);
    
    const double UPM = font_design_units_per_M;
    
    const double leading = pointSizeToUPM*((double)CTFontGetLeading(appleFont));

    const double ascent = pointSizeToUPM * ((double)CTFontGetAscent(appleFont));

    const CGFloat ct_descent_sign = -1;
    const double descent = pointSizeToUPM * ((double)(ct_descent_sign*CTFontGetDescent(appleFont)));
    
    const double line_space1 = ascent - descent + leading;
    const double line_space2
      = (1.0 != pointSizeToUPM)
      ? (pointSizeToUPM*((double)(CTFontGetAscent(appleFont)-(ct_descent_sign*CTFontGetDescent(appleFont))+CTFontGetLeading(appleFont))))
      : line_space1;
    const double line_space = (line_space2>=line_space1) ? line_space2 : line_space1;
    
    const double ascent_of_x = pointSizeToUPM*((double)CTFontGetXHeight(appleFont));
    const double ascent_of_capital = pointSizeToUPM*((double)CTFontGetCapHeight(appleFont));
    const double underscore_position = pointSizeToUPM*((double)CTFontGetUnderlinePosition(appleFont));
    const double underscore_thickness = pointSizeToUPM*((double)CTFontGetUnderlineThickness(appleFont));
    
    CFRelease(appleFont);
    
    font_metrics = ON_FontMetrics::Unset;
    font_metrics.SetHeights(
      ascent,
      descent,
      UPM,
      line_space
      );
    if (false == font_metrics.AscentDescentAndUPMAreValid())
      break;
    
    font_metrics.SetAscentOfx(ascent_of_x);
    font_metrics.SetAscentOfCapital(ascent_of_capital);
    font_metrics.SetUnderscore(underscore_position,underscore_thickness);
    
    // Have to fake strikeout settings - not in NSFont API?
    //int strikeout_position = ...;
    //int strikeout_thickness = ...;
    double h = (ascent_of_capital > 0) ? ascent_of_capital : ascent;
    if (h > 0.0)
    {
    font_metrics.SetStrikeout(
      (0.5*h),
      (0.5*underscore_thickness)
      );
    }
    
    if (font_metrics.AscentDescentAndUPMAreValid())
      return;
    break;
  }
  
  font_metrics = ON_FontMetrics::Unset;
  return;
}

static int Internal_IntFloor(double x)
{
  double f = floor(x);
  double c = ceil(x);
  if ( (1.0 == (c-f)) && ((c-x) <= 1.0e-4 ))
    return (int)c;
  return (int)f;
}

static int Internal_IntCeil(double x)
{
  double f = floor(x);
  double c = ceil(x);
  if ( (1.0 == (c-f)) && ((x-f) <= 1.0e-4 ))
    return (int)f;
  return (int)c;
}

bool ON_AppleFontGetGlyphMetrics(
  CTFontRef appleFont,
  unsigned int glyphIndex,
  class ON_TextBox& glyph_metrics
)
{
  glyph_metrics = ON_TextBox::Unset;
  
  for(;;)
  {
    if (0 == glyphIndex)
      break;
    if (nullptr == appleFont)
      break;
    
    const CGGlyph glyphs[2] = {(CGGlyph)glyphIndex,0};
    if ( ((unsigned int)glyphs[0]) != glyphIndex )
      break; // CGGlyph is a short and glyphIndex is too large.
    const CFIndex count = 1;
    
    CGRect boundingRects[2];
    CGRect glyphRect = CTFontGetBoundingRectsForGlyphs(appleFont, kCTFontOrientationHorizontal, glyphs, boundingRects, count);
    if ( boundingRects[0].size.height != 0.0f || boundingRects[0].size.width != 0.0f  )
      glyphRect = boundingRects[0];
    
    CGSize advances[2];
    double glyphAdvanceX = CTFontGetAdvancesForGlyphs(appleFont, kCTFontOrientationHorizontal, glyphs, advances, count);
    if (advances[0].width != 0.0f)
      glyphAdvanceX = advances[0].width;

    double glyphAdvanceY = CTFontGetAdvancesForGlyphs(appleFont, kCTFontOrientationVertical, glyphs, advances, count);
    if (advances[0].width != 0.0f)
      glyphAdvanceY = advances[0].width; // width is correct - the vertical advance is returned in width.
    
    //CGSize translations[2];
    //CTFontGetVerticalTranslationsForGlyphs(appleFont, glyphs, translations, count);
    
    double pointSizeToUPM = 1.0;
    const unsigned int font_design_units_per_M = Internal_AppleUnitsPerEm(appleFont,&pointSizeToUPM);
    if (0 == font_design_units_per_M)
      pointSizeToUPM = 1.0;
    
    glyph_metrics.m_bbmin.i = Internal_IntFloor(pointSizeToUPM*glyphRect.origin.x);
    glyph_metrics.m_bbmin.j = Internal_IntFloor(pointSizeToUPM*glyphRect.origin.y);
    
    glyph_metrics.m_bbmax.i = Internal_IntCeil(pointSizeToUPM*(glyphRect.origin.x + glyphRect.size.width));
    glyph_metrics.m_bbmax.j = Internal_IntCeil(pointSizeToUPM*(glyphRect.origin.y + glyphRect.size.height));
    
    glyph_metrics.m_advance.i = Internal_IntCeil(pointSizeToUPM*glyphAdvanceX);
    glyph_metrics.m_advance.j = Internal_IntCeil(pointSizeToUPM*glyphAdvanceY);
    
    return true;
  }
  return false;
}

class ON_AppleGlyphOutlineAccumlator : public ON_OutlineAccumulator
{
public:
  ON_AppleGlyphOutlineAccumlator() = default;
  ~ON_AppleGlyphOutlineAccumlator() = default;

  static void Internal_PathApplierFunction(
    void *info, 
    const CGPathElement *element
  );
  
private:
  static const ON_2fPoint Internal_Point(CGPoint p);

private:
  ON_AppleGlyphOutlineAccumlator(const ON_AppleGlyphOutlineAccumlator&) = delete;
  ON_AppleGlyphOutlineAccumlator& operator=(const ON_AppleGlyphOutlineAccumlator&) = delete;
};

const ON_2fPoint ON_AppleGlyphOutlineAccumlator::Internal_Point(CGPoint p)
{
  return ON_2fPoint((float)p.x, (float)p.y);
}

void ON_AppleGlyphOutlineAccumlator::Internal_PathApplierFunction(
  void *info,
  const CGPathElement *element
)
{
  if (nullptr == info || nullptr == element)
    return;

  ON_AppleGlyphOutlineAccumlator* acc = (ON_AppleGlyphOutlineAccumlator*)info;

  switch (element->type)
  {
  case kCGPathElementMoveToPoint:
    if (nullptr != element->points)
    {
      acc->BeginFigure(
        ON_OutlineFigurePoint::Type::BeginFigureUnknown,
        ON_AppleGlyphOutlineAccumlator::Internal_Point(element->points[0])
      );
    }
    break;

  case kCGPathElementAddLineToPoint:
    if (nullptr != element->points)
    {
      acc->AppendLine(
        ON_AppleGlyphOutlineAccumlator::Internal_Point(element->points[0])
      );
    }
    break;

  case kCGPathElementAddQuadCurveToPoint:
    if (nullptr != element->points)
    {
      acc->AppendQuadraticBezier(
        ON_AppleGlyphOutlineAccumlator::Internal_Point(element->points[0]),
        ON_AppleGlyphOutlineAccumlator::Internal_Point(element->points[1])
      );
    }
    break;

  case kCGPathElementAddCurveToPoint: // cubic bezier
    if (nullptr != element->points)
    {
      acc->AppendCubicBezier(
        ON_AppleGlyphOutlineAccumlator::Internal_Point(element->points[0]),
        ON_AppleGlyphOutlineAccumlator::Internal_Point(element->points[1]),
        ON_AppleGlyphOutlineAccumlator::Internal_Point(element->points[2])
      );
    }
    break;

  case kCGPathElementCloseSubpath:
    acc->EndFigure(
      ON_OutlineFigurePoint::Type::EndFigureClosed
    );
    break;

  default:
    break;
  };

}

bool ON_AppleFontGetGlyphOutline(
  CTFontRef appleFont,
  unsigned int glyphIndex,
  ON_OutlineFigure::Type figure_type,
  class ON_Outline& outline
)
{
  outline = ON_Outline::Unset;
  
  if (nullptr == appleFont)
    return false;
  
  if ( glyphIndex <= 0 )
    return false;
    
  const CGGlyph appleGlyphIndex = (CGGlyph)glyphIndex;
  if (((unsigned int)appleGlyphIndex) != glyphIndex)
  {
    // glyphIndex too large - currently CGGlyph is an unsigned short.
    return false; 
  }
  
  CGPathRef applePath = CTFontCreatePathForGlyph(appleFont, appleGlyphIndex, nullptr);
  
  // NOTE WELL: applePath = nullptr for space, tab and so on.
  // We still need to get the advance for these code points.
  // NO // if (nullptr == applePath)
  // NO //   return false;

  unsigned int font_design_units_per_M = CTFontGetUnitsPerEm(appleFont);
  const CGFloat point_size = CTFontGetSize(appleFont);
  if ( false == (point_size== (CGFloat)font_design_units_per_M))
  {
    ON_WARNING("CTFontGetSize() != CTFontGetUnitsPerEm()");
    font_design_units_per_M =(unsigned int)ceil(point_size);
  }
  
  ON_AppleGlyphOutlineAccumlator acc;
  acc.BeginGlyphOutline(font_design_units_per_M, figure_type, &outline);
  if ( nullptr != applePath)
  {
    CGPathApply(applePath, &acc, ON_AppleGlyphOutlineAccumlator::Internal_PathApplierFunction);
    CGPathRelease(applePath);
  }
  acc.EndOutline();

  // Add Glyph metrics to outline
  ON_TextBox glyph_metrics_in_font_design_units;
  bool bHaveGlyphMetrics = ON_AppleFontGetGlyphMetrics(appleFont, appleGlyphIndex, glyph_metrics_in_font_design_units);
  if ( bHaveGlyphMetrics )
    outline.SetGlyphMetrics(glyph_metrics_in_font_design_units);
  else
    outline.SetGlyphMetrics(ON_TextBox::Unset);
      
  return true;
}

unsigned int ON_AppleFontGlyphIndex(
  CTFontRef appleFont,
  unsigned int unicode_code_point
)
{
  unsigned int glyphIndex = 0;

  for (;;)
  {
    if (false == ON_IsValidUnicodeCodePoint(unicode_code_point))
      break;

    ON__UINT16 utf16[3] = {};
    const int utf16_count = ON_EncodeUTF16(unicode_code_point, utf16);
    if (utf16_count < 1 || utf16_count > 2)
      break;

    // UniChar is used for Apple UTF-16 endcodings
    const UniChar apple_utf16[3] = { (UniChar)utf16[0], (UniChar)utf16[1], (UniChar)0 };

    // glyphs[] includes an element for the NULL terminator and an extra element
    // in case CTFontGetGlyphsForCharacters is buggy when handling surrogate pairs.
    CGGlyph glyphs[3] = {};  
    if (false == CTFontGetGlyphsForCharacters(appleFont, apple_utf16, glyphs, (NSInteger)utf16_count))
      break;
    if (0 == glyphs[0])
      break;
    if (0 != glyphs[1] || 0 != glyphs[2])
      break;

    glyphIndex = (unsigned int)glyphs[0];

    break;
  }

  return glyphIndex;
}


unsigned int ON_AppleFontGetGlyphMetrics(
  const ON_FontGlyph* glyph,
  ON_TextBox& glyph_metrics
)
{
  glyph_metrics = ON_TextBox::Unset;

  if (nullptr == glyph)
    return 0;

  if (false == glyph->CodePointIsSet())
    return 0;

  const ON_Font* font = glyph->Font();
  if (nullptr == font)
    return 0;

  bool bIsSubstituteFont = false;
  CTFontRef appleFont = font->AppleCTFont(bIsSubstituteFont);
  if (nullptr == appleFont)
    return 0;

  const unsigned int glyph_index = ON_AppleFontGlyphIndex(appleFont, glyph->CodePoint());
  if (0 == glyph_index)
  {
    CFRelease(appleFont);
    return 0;
  }
  
  ON_AppleFontGetGlyphMetrics(appleFont, glyph_index, glyph_metrics);
  CFRelease(appleFont);

  return glyph_index;
}

bool ON_AppleFontGetGlyphOutline(
  const ON_FontGlyph* glyph,
  ON_OutlineFigure::Type figure_type,
  class ON_Outline& outline
)
{
  outline = ON_Outline::Unset;

  if (nullptr == glyph)
    return false;

  if (false == glyph->CodePointIsSet())
    return false;

  const unsigned int glyphIndex = glyph->FontGlyphIndex();
  if (0==glyphIndex)
    return false;

  const ON_Font* font = glyph->Font();
  if (nullptr == font)
    return false;

  if (ON_OutlineFigure::Type::Unset == figure_type)
  {
    ON_OutlineFigure::Type font_figure_type = font->OutlineFigureType();
    if (ON_OutlineFigure::Type::Unset != font_figure_type)
    {
      figure_type = font_figure_type;
    }
  }

#if defined(OPENNURBS_FREETYPE_SUPPORT)
  if (
    ON_OutlineFigure::Type::SingleStroke == figure_type
    // NO // ON_OutlineFigure::Type::DoubleStroke == font_figure_type
    )
  {
    // Apple's Mac OS CTFontCreatePathForGlyph() ignores subfigures that
    // are lines. These are common in single stroke fonts. Typical results
    // with singel stroke files are things like the R is missing it's right leg, 
    // h is missing is left side line, and so on. 
    // Freetype has many bugs, but it can parse some common single stroke files. 
    // Freetype is basically a file reading utility that can parse outline 
    // information in older formats of font files. It fails on newer formats 
    // and it also commonly fails to correctly map UNICODE code points to 
    // glyph indices. Freetype should only be used as a last resort.
    const bool freetype_rc = ON_FreeTypeGetGlyphOutline(
      glyph,
      glyphIndex,
      figure_type,
      outline
    );
    if (freetype_rc)
      return true;
  }
#endif

  bool bIsSubstituteFont = false;
  CTFontRef appleFont = font->AppleCTFont(bIsSubstituteFont);
  if (nullptr == appleFont)
    return false;

  const bool rc = ON_AppleFontGetGlyphOutline(
    appleFont,
    glyphIndex,
    figure_type,
    outline
  );
  
  CFRelease(appleFont);

  return rc;
}

void ON_Font::DumpCTFont(
  CTFontRef apple_font,
  ON_TextLog& text_log
)
{
  if (nullptr == apple_font)
  {
    text_log.Print("CTFont = nullptr\n");
    return;
  }

  text_log.Print("CTFont\n");
  text_log.PushIndent();
  
  const ON_wString postscript_name = ON_Font::AppleCTFontPostScriptName(apple_font);
  text_log.Print(L"CTFont PostScriptName: \"%ls\"\n",static_cast<const wchar_t*>(postscript_name));
  
  const ON_wString display_name = ON_Font::AppleCTFontDisplayName(apple_font);
  text_log.Print(L"CTFont DisplayName: \"%ls\"\n",static_cast<const wchar_t*>(display_name));
  
  const ON_wString family_name = ON_Font::AppleCTFontFamilyName(apple_font);
  text_log.Print(L"CTFont FamilyName: \"%ls\"\n",static_cast<const wchar_t*>(family_name));
  
  // Apple NSFont and MacOS do not have "face names" as a font attribute.
  // This is the "typeface" name shown in Apple FontBook
  const ON_wString fake_face_name = ON_Font::AppleCTFontFaceName(apple_font);
  text_log.Print(L"CTFont FontBook typeface: \"%ls\"\n",static_cast<const wchar_t*>(fake_face_name));

  const unsigned int UPM = ON_Font::AppleCTFontUnitsPerEm(apple_font);
  text_log.Print("CTFont UnitsPerEm: %u\n",UPM);

  const double point_size = (double)CTFontGetSize(apple_font);
  text_log.Print("CTFont Size: %g points\n",point_size);
  
#if 0
  text_log.Print(L"CTFont Names:\n");
  text_log.PushIndent();
  
  CFStringRef keys[] =
  {
    kCTFontCopyrightNameKey,
    kCTFontFamilyNameKey,
    kCTFontSubFamilyNameKey,
    kCTFontStyleNameKey,
    kCTFontUniqueNameKey, // Apple docs say this name is not actually unique
    kCTFontFullNameKey,
    kCTFontVersionNameKey,
    kCTFontPostScriptNameKey,
    kCTFontTrademarkNameKey,
    kCTFontManufacturerNameKey,
    kCTFontDesignerNameKey,
    kCTFontDescriptionNameKey,
    kCTFontVendorURLNameKey,
    kCTFontDesignerURLNameKey,
    kCTFontLicenseNameKey,
    kCTFontLicenseURLNameKey,
    kCTFontSampleTextNameKey,
    kCTFontPostScriptCIDNameKey
  };
  
  const size_t key_count = sizeof(keys)/sizeof(keys[0]);
  text_log.Print(L"CTFont Names:\n");
  text_log.PushIndent();
  for (size_t i = 0; i < key_count; i++)
  {
    CFStringRef appleName = CTFontCopyName(apple_font,keys[i]);
    const ON_wString key(keys[i]);
    const ON_wString name(appleName);
    if (nullptr != appleName)
      CFRelease(appleName);
    if ( name.IsNotEmpty() )
    {
      text_log.Print(
        L"\"%ls\" = CTFontCopyName(...,\"%ls\")\n",
        static_cast<const wchar_t*>(name),
        static_cast<const wchar_t*>(key)
        );
    }
  }
  text_log.PopIndent();
#endif

  text_log.PopIndent();
}


#endif
