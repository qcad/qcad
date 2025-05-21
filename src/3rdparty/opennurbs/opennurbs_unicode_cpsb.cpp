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

//
// Multiple platform support for converting 
// MSSBCP Microsoft single byte code page encodings to Unicode.
// Needed to parse RTF in ON_textContent and to use freetype
// font cmaps when the unicode cmaps are missing or damaged.
//

const ON__UINT32* ON_MSSBCP_0x80_0xFF_Unicode(
  ON__UINT32 code_page
  )
{
  // 1252: Windows Latin 1 (ANSI)
  // Verified using Windows 10 Dec 2017
  static const ON__UINT32 code_page_1252_0x80_to_0xFF[128] =
  {
    /* cp1252 0x80 */ 0x20ac, // Euro Sign
    /* cp1252 0x81 */ 0x81,
    /* cp1252 0x82 */ 0x201a, // Single Low-9 Quotation Mark
    /* cp1252 0x83 */ 0x0192, // Latin Small Letter F With Hook
    /* cp1252 0x84 */ 0x201e, // Double Low-9 Quotation Mark
    /* cp1252 0x85 */ 0x2026, // Horizontal Ellipsis
    /* cp1252 0x86 */ 0x2020, // Dagger
    /* cp1252 0x87 */ 0x2021, // Double Dagger
    /* cp1252 0x88 */ 0x02c6, // Modifier Letter Circumflex Accent
    /* cp1252 0x89 */ 0x2030, // Per Mille Sign
    /* cp1252 0x8a */ 0x0160, // Latin Capital Letter S With Caron
    /* cp1252 0x8b */ 0x2039, // Single Left-Pointing Angle Quotation Mark
    /* cp1252 0x8c */ 0x0152, // Latin Capital Ligature Oe
    /* cp1252 0x8d */ 0x8d, // ON_UnicodeCodePoint::ON_ReplacementCharacter,
    /* cp1252 0x8e */ 0x017d, // Latin Capital Letter Z With Caron
    /* cp1252 0x8f */ 0x8f,
    /* cp1252 0x90 */ 0x90,
    /* cp1252 0x91 */ 0x2018, // Left Single Quotation Mark
    /* cp1252 0x92 */ 0x2019, // Right Single Quotation Mark
    /* cp1252 0x93 */ 0x201c, // Left Double Quotation Mark
    /* cp1252 0x94 */ 0x201d, // Right Double Quotation Mark
    /* cp1252 0x95 */ 0x2022, // Bullet
    /* cp1252 0x96 */ 0x2013, // En Dash
    /* cp1252 0x97 */ 0x2014, // Em Dash
    /* cp1252 0x98 */ 0x02dc, // Small Tilde
    /* cp1252 0x99 */ 0x2122, // Trade Mark Sign
    /* cp1252 0x9a */ 0x0161, // Latin Small Letter S With Caron
    /* cp1252 0x9b */ 0x203a, // Single Right-Pointing Angle Quotation Mark
    /* cp1252 0x9c */ 0x0153, // Latin Small Ligature Oe
    /* cp1252 0x9d */ 0x9d, 
    /* cp1252 0x9e */ 0x017e, // Latin Small Letter Z With Caron
    /* cp1252 0x9f */ 0x0178, // Latin Capital Letter Y With Diaeresis
    /* cp1252 0xa0 */ 0x00a0, // No-Break Space
    /* cp1252 0xa1 */ 0x00a1, // Inverted Exclamation Mark
    /* cp1252 0xa2 */ 0x00a2, // Cent Sign
    /* cp1252 0xa3 */ 0x00a3, // Pound Sign
    /* cp1252 0xa4 */ 0x00a4, // Currency Sign
    /* cp1252 0xa5 */ 0x00a5, // Yen Sign
    /* cp1252 0xa6 */ 0x00a6, // Broken Bar
    /* cp1252 0xa7 */ 0x00a7, // Section Sign
    /* cp1252 0xa8 */ 0x00a8, // Diaeresis
    /* cp1252 0xa9 */ 0x00a9, // Copyright Sign
    /* cp1252 0xaa */ 0x00aa, // Feminine Ordinal Indicator
    /* cp1252 0xab */ 0x00ab, // Left-Pointing Double Angle Quotation Mark
    /* cp1252 0xac */ 0x00ac, // Not Sign
    /* cp1252 0xad */ 0x00ad, // Soft Hyphen
    /* cp1252 0xae */ 0x00ae, // Registered Sign
    /* cp1252 0xaf */ 0x00af, // Macron
    /* cp1252 0xb0 */ 0x00b0, // Degree Sign
    /* cp1252 0xb1 */ 0x00b1, // Plus-Minus Sign
    /* cp1252 0xb2 */ 0x00b2, // Superscript Two
    /* cp1252 0xb3 */ 0x00b3, // Superscript Three
    /* cp1252 0xb4 */ 0x00b4, // Acute Accent
    /* cp1252 0xb5 */ 0x00b5, // Micro Sign
    /* cp1252 0xb6 */ 0x00b6, // Pilcrow Sign
    /* cp1252 0xb7 */ 0x00b7, // Middle Dot
    /* cp1252 0xb8 */ 0x00b8, // Cedilla
    /* cp1252 0xb9 */ 0x00b9, // Superscript One
    /* cp1252 0xba */ 0x00ba, // Masculine Ordinal Indicator
    /* cp1252 0xbb */ 0x00bb, // Right-Pointing Double Angle Quotation Mark
    /* cp1252 0xbc */ 0x00bc, // Vulgar Fraction One Quarter
    /* cp1252 0xbd */ 0x00bd, // Vulgar Fraction One Half
    /* cp1252 0xbe */ 0x00be, // Vulgar Fraction Three Quarters
    /* cp1252 0xbf */ 0x00bf, // Inverted Question Mark
    /* cp1252 0xc0 */ 0x00c0, // Latin Capital Letter A With Grave
    /* cp1252 0xc1 */ 0x00c1, // Latin Capital Letter A With Acute
    /* cp1252 0xc2 */ 0x00c2, // Latin Capital Letter A With Circumflex
    /* cp1252 0xc3 */ 0x00c3, // Latin Capital Letter A With Tilde
    /* cp1252 0xc4 */ 0x00c4, // Latin Capital Letter A With Diaeresis
    /* cp1252 0xc5 */ 0x00c5, // Latin Capital Letter A With Ring Above
    /* cp1252 0xc6 */ 0x00c6, // Latin Capital Ligature Ae
    /* cp1252 0xc7 */ 0x00c7, // Latin Capital Letter C With Cedilla
    /* cp1252 0xc8 */ 0x00c8, // Latin Capital Letter E With Grave
    /* cp1252 0xc9 */ 0x00c9, // Latin Capital Letter E With Acute
    /* cp1252 0xca */ 0x00ca, // Latin Capital Letter E With Circumflex
    /* cp1252 0xcb */ 0x00cb, // Latin Capital Letter E With Diaeresis
    /* cp1252 0xcc */ 0x00cc, // Latin Capital Letter I With Grave
    /* cp1252 0xcd */ 0x00cd, // Latin Capital Letter I With Acute
    /* cp1252 0xce */ 0x00ce, // Latin Capital Letter I With Circumflex
    /* cp1252 0xcf */ 0x00cf, // Latin Capital Letter I With Diaeresis
    /* cp1252 0xd0 */ 0x00d0, // Latin Capital Letter Eth
    /* cp1252 0xd1 */ 0x00d1, // Latin Capital Letter N With Tilde
    /* cp1252 0xd2 */ 0x00d2, // Latin Capital Letter O With Grave
    /* cp1252 0xd3 */ 0x00d3, // Latin Capital Letter O With Acute
    /* cp1252 0xd4 */ 0x00d4, // Latin Capital Letter O With Circumflex
    /* cp1252 0xd5 */ 0x00d5, // Latin Capital Letter O With Tilde
    /* cp1252 0xd6 */ 0x00d6, // Latin Capital Letter O With Diaeresis
    /* cp1252 0xd7 */ 0x00d7, // Multiplication Sign
    /* cp1252 0xd8 */ 0x00d8, // Latin Capital Letter O With Stroke
    /* cp1252 0xd9 */ 0x00d9, // Latin Capital Letter U With Grave
    /* cp1252 0xda */ 0x00da, // Latin Capital Letter U With Acute
    /* cp1252 0xdb */ 0x00db, // Latin Capital Letter U With Circumflex
    /* cp1252 0xdc */ 0x00dc, // Latin Capital Letter U With Diaeresis
    /* cp1252 0xdd */ 0x00dd, // Latin Capital Letter Y With Acute
    /* cp1252 0xde */ 0x00de, // Latin Capital Letter Thorn
    /* cp1252 0xdf */ 0x00df, // Latin Small Letter Sharp S
    /* cp1252 0xe0 */ 0x00e0, // Latin Small Letter A With Grave
    /* cp1252 0xe1 */ 0x00e1, // Latin Small Letter A With Acute
    /* cp1252 0xe2 */ 0x00e2, // Latin Small Letter A With Circumflex
    /* cp1252 0xe3 */ 0x00e3, // Latin Small Letter A With Tilde
    /* cp1252 0xe4 */ 0x00e4, // Latin Small Letter A With Diaeresis
    /* cp1252 0xe5 */ 0x00e5, // Latin Small Letter A With Ring Above
    /* cp1252 0xe6 */ 0x00e6, // Latin Small Ligature Ae
    /* cp1252 0xe7 */ 0x00e7, // Latin Small Letter C With Cedilla
    /* cp1252 0xe8 */ 0x00e8, // Latin Small Letter E With Grave
    /* cp1252 0xe9 */ 0x00e9, // Latin Small Letter E With Acute
    /* cp1252 0xea */ 0x00ea, // Latin Small Letter E With Circumflex
    /* cp1252 0xeb */ 0x00eb, // Latin Small Letter E With Diaeresis
    /* cp1252 0xec */ 0x00ec, // Latin Small Letter I With Grave
    /* cp1252 0xed */ 0x00ed, // Latin Small Letter I With Acute
    /* cp1252 0xee */ 0x00ee, // Latin Small Letter I With Circumflex
    /* cp1252 0xef */ 0x00ef, // Latin Small Letter I With Diaeresis
    /* cp1252 0xf0 */ 0x00f0, // Latin Small Letter Eth
    /* cp1252 0xf1 */ 0x00f1, // Latin Small Letter N With Tilde
    /* cp1252 0xf2 */ 0x00f2, // Latin Small Letter O With Grave
    /* cp1252 0xf3 */ 0x00f3, // Latin Small Letter O With Acute
    /* cp1252 0xf4 */ 0x00f4, // Latin Small Letter O With Circumflex
    /* cp1252 0xf5 */ 0x00f5, // Latin Small Letter O With Tilde
    /* cp1252 0xf6 */ 0x00f6, // Latin Small Letter O With Diaeresis
    /* cp1252 0xf7 */ 0x00f7, // Division Sign
    /* cp1252 0xf8 */ 0x00f8, // Latin Small Letter O With Stroke
    /* cp1252 0xf9 */ 0x00f9, // Latin Small Letter U With Grave
    /* cp1252 0xfa */ 0x00fa, // Latin Small Letter U With Acute
    /* cp1252 0xfb */ 0x00fb, // Latin Small Letter U With Circumflex
    /* cp1252 0xfc */ 0x00fc, // Latin Small Letter U With Diaeresis
    /* cp1252 0xfd */ 0x00fd, // Latin Small Letter Y With Acute
    /* cp1252 0xfe */ 0x00fe, // Latin Small Letter Thorn
    /* cp1252 0xff */ 0x00ff, // Latin Small Letter Y With Diaeresis
  };

  // 10000: Macintosh Roman
  // Verified using Windows 10 Dec 2017
  static const ON__UINT32 code_page_10000_0x80_to_0xFF[128] =
  {
    /* 0x80*/ 0x00C4, // LATIN CAPITAL LETTER A WITH DIAERESIS
    /* 0x81*/ 0x00C5, // LATIN CAPITAL LETTER A WITH RING ABOVE
    /* 0x82*/ 0x00C7, // LATIN CAPITAL LETTER C WITH CEDILLA
    /* 0x83*/ 0x00C9, // LATIN CAPITAL LETTER E WITH ACUTE
    /* 0x84*/ 0x00D1, // LATIN CAPITAL LETTER N WITH TILDE
    /* 0x85*/ 0x00D6, // LATIN CAPITAL LETTER O WITH DIAERESIS
    /* 0x86*/ 0x00DC, // LATIN CAPITAL LETTER U WITH DIAERESIS
    /* 0x87*/ 0x00E1, // LATIN SMALL LETTER A WITH ACUTE
    /* 0x88*/ 0x00E0, // LATIN SMALL LETTER A WITH GRAVE
    /* 0x89*/ 0x00E2, // LATIN SMALL LETTER A WITH CIRCUMFLEX
    /* 0x8A*/ 0x00E4, // LATIN SMALL LETTER A WITH DIAERESIS
    /* 0x8B*/ 0x00E3, // LATIN SMALL LETTER A WITH TILDE
    /* 0x8C*/ 0x00E5, // LATIN SMALL LETTER A WITH RING ABOVE
    /* 0x8D*/ 0x00E7, // LATIN SMALL LETTER C WITH CEDILLA
    /* 0x8E*/ 0x00E9, // LATIN SMALL LETTER E WITH ACUTE
    /* 0x8F*/ 0x00E8, // LATIN SMALL LETTER E WITH GRAVE
    /* 0x90*/ 0x00EA, // LATIN SMALL LETTER E WITH CIRCUMFLEX
    /* 0x91*/ 0x00EB, // LATIN SMALL LETTER E WITH DIAERESIS
    /* 0x92*/ 0x00ED, // LATIN SMALL LETTER I WITH ACUTE
    /* 0x93*/ 0x00EC, // LATIN SMALL LETTER I WITH GRAVE
    /* 0x94*/ 0x00EE, // LATIN SMALL LETTER I WITH CIRCUMFLEX
    /* 0x95*/ 0x00EF, // LATIN SMALL LETTER I WITH DIAERESIS
    /* 0x96*/ 0x00F1, // LATIN SMALL LETTER N WITH TILDE
    /* 0x97*/ 0x00F3, // LATIN SMALL LETTER O WITH ACUTE
    /* 0x98*/ 0x00F2, // LATIN SMALL LETTER O WITH GRAVE
    /* 0x99*/ 0x00F4, // LATIN SMALL LETTER O WITH CIRCUMFLEX
    /* 0x9A*/ 0x00F6, // LATIN SMALL LETTER O WITH DIAERESIS
    /* 0x9B*/ 0x00F5, // LATIN SMALL LETTER O WITH TILDE
    /* 0x9C*/ 0x00FA, // LATIN SMALL LETTER U WITH ACUTE
    /* 0x9D*/ 0x00F9, // LATIN SMALL LETTER U WITH GRAVE
    /* 0x9E*/ 0x00FB, // LATIN SMALL LETTER U WITH CIRCUMFLEX
    /* 0x9F*/ 0x00FC, // LATIN SMALL LETTER U WITH DIAERESIS
    /* 0xA0*/ 0x2020, // DAGGER
    /* 0xA1*/ 0x00B0, // DEGREE SIGN
    /* 0xA2*/ 0x00A2, // CENT SIGN
    /* 0xA3*/ 0x00A3, // POUND SIGN
    /* 0xA4*/ 0x00A7, // SECTION SIGN
    /* 0xA5*/ 0x2022, // BULLET
    /* 0xA6*/ 0x00B6, // PILCROW SIGN
    /* 0xA7*/ 0x00DF, // LATIN SMALL LETTER SHARP S
    /* 0xA8*/ 0x00AE, // REGISTERED SIGN
    /* 0xA9*/ 0x00A9, // COPYRIGHT SIGN
    /* 0xAA*/ 0x2122, // TRADE MARK SIGN
    /* 0xAB*/ 0x00B4, // ACUTE ACCENT
    /* 0xAC*/ 0x00A8, // DIAERESIS
    /* 0xAD*/ 0x2260, // NOT EQUAL TO
    /* 0xAE*/ 0x00C6, // LATIN CAPITAL LETTER AE
    /* 0xAF*/ 0x00D8, // LATIN CAPITAL LETTER O WITH STROKE
    /* 0xB0*/ 0x221E, // INFINITY
    /* 0xB1*/ 0x00B1, // PLUS-MINUS SIGN
    /* 0xB2*/ 0x2264, // LESS-THAN OR EQUAL TO
    /* 0xB3*/ 0x2265, // GREATER-THAN OR EQUAL TO
    /* 0xB4*/ 0x00A5, // YEN SIGN
    /* 0xB5*/ 0x00B5, // MICRO SIGN
    /* 0xB6*/ 0x2202, // PARTIAL DIFFERENTIAL
    /* 0xB7*/ 0x2211, // N-ARY SUMMATION
    /* 0xB8*/ 0x220F, // N-ARY PRODUCT
    /* 0xB9*/ 0x03C0, // GREEK SMALL LETTER PI
    /* 0xBA*/ 0x222B, // INTEGRAL
    /* 0xBB*/ 0x00AA, // FEMININE ORDINAL INDICATOR
    /* 0xBC*/ 0x00BA, // MASCULINE ORDINAL INDICATOR

    // Microsoft code page 10000 maps 0xBC to U+2126 need to test current OS X
    /* 0xBD*/ 0x2126, // OHM SIGN // 0x03A9, // GREEK CAPITAL LETTER OMEGA)

    /* 0xBE*/ 0x00E6, // LATIN SMALL LETTER AE
    /* 0xBF*/ 0x00F8, // LATIN SMALL LETTER O WITH STROKE
    /* 0xC0*/ 0x00BF, // INVERTED QUESTION MARK
    /* 0xC1*/ 0x00A1, // INVERTED EXCLAMATION MARK
    /* 0xC2*/ 0x00AC, // NOT SIGN
    /* 0xC3*/ 0x221A, // SQUARE ROOT
    /* 0xC4*/ 0x0192, // LATIN SMALL LETTER F WITH HOOK
    /* 0xC5*/ 0x2248, // ALMOST EQUAL TO
    /* 0xC6*/ 0x2206, // INCREMENT
    /* 0xC7*/ 0x00AB, // LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
    /* 0xC8*/ 0x00BB, // RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
    /* 0xC9*/ 0x2026, // HORIZONTAL ELLIPSIS
    /* 0xCA*/ 0x00A0, // NO-BREAK SPACE
    /* 0xCB*/ 0x00C0, // LATIN CAPITAL LETTER A WITH GRAVE
    /* 0xCC*/ 0x00C3, // LATIN CAPITAL LETTER A WITH TILDE
    /* 0xCD*/ 0x00D5, // LATIN CAPITAL LETTER O WITH TILDE
    /* 0xCE*/ 0x0152, // LATIN CAPITAL LIGATURE OE
    /* 0xCF*/ 0x0153, // LATIN SMALL LIGATURE OE
    /* 0xD0*/ 0x2013, // EN DASH
    /* 0xD1*/ 0x2014, // EM DASH
    /* 0xD2*/ 0x201C, // LEFT DOUBLE QUOTATION MARK
    /* 0xD3*/ 0x201D, // RIGHT DOUBLE QUOTATION MARK
    /* 0xD4*/ 0x2018, // LEFT SINGLE QUOTATION MARK
    /* 0xD5*/ 0x2019, // RIGHT SINGLE QUOTATION MARK
    /* 0xD6*/ 0x00F7, // DIVISION SIGN
    /* 0xD7*/ 0x25CA, // LOZENGE
    /* 0xD8*/ 0x00FF, // LATIN SMALL LETTER Y WITH DIAERESIS
    /* 0xD9*/ 0x0178, // LATIN CAPITAL LETTER Y WITH DIAERESIS
    /* 0xDA*/ 0x2044, // FRACTION SLASH
    /* 0xDB*/ 0x20AC, // EURO SIGN
    /* 0xDC*/ 0x2039, // SINGLE LEFT-POINTING ANGLE QUOTATION MARK
    /* 0xDD*/ 0x203A, // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
    /* 0xDE*/ 0xFB01, // LATIN SMALL LIGATURE FI
    /* 0xDF*/ 0xFB02, // LATIN SMALL LIGATURE FL
    /* 0xE0*/ 0x2021, // DOUBLE DAGGER
    /* 0xE1*/ 0x00B7, // MIDDLE DOT
    /* 0xE2*/ 0x201A, // SINGLE LOW-9 QUOTATION MARK
    /* 0xE3*/ 0x201E, // DOUBLE LOW-9 QUOTATION MARK
    /* 0xE4*/ 0x2030, // PER MILLE SIGN
    /* 0xE5*/ 0x00C2, // LATIN CAPITAL LETTER A WITH CIRCUMFLEX
    /* 0xE6*/ 0x00CA, // LATIN CAPITAL LETTER E WITH CIRCUMFLEX
    /* 0xE7*/ 0x00C1, // LATIN CAPITAL LETTER A WITH ACUTE
    /* 0xE8*/ 0x00CB, // LATIN CAPITAL LETTER E WITH DIAERESIS
    /* 0xE9*/ 0x00C8, // LATIN CAPITAL LETTER E WITH GRAVE
    /* 0xEA*/ 0x00CD, // LATIN CAPITAL LETTER I WITH ACUTE
    /* 0xEB*/ 0x00CE, // LATIN CAPITAL LETTER I WITH CIRCUMFLEX
    /* 0xEC*/ 0x00CF, // LATIN CAPITAL LETTER I WITH DIAERESIS
    /* 0xED*/ 0x00CC, // LATIN CAPITAL LETTER I WITH GRAVE
    /* 0xEE*/ 0x00D3, // LATIN CAPITAL LETTER O WITH ACUTE
    /* 0xEF*/ 0x00D4, // LATIN CAPITAL LETTER O WITH CIRCUMFLEX
    /* 0xF0*/ 0xF8FF, // Apple logo
    /* 0xF1*/ 0x00D2, // LATIN CAPITAL LETTER O WITH GRAVE
    /* 0xF2*/ 0x00DA, // LATIN CAPITAL LETTER U WITH ACUTE
    /* 0xF3*/ 0x00DB, // LATIN CAPITAL LETTER U WITH CIRCUMFLEX
    /* 0xF4*/ 0x00D9, // LATIN CAPITAL LETTER U WITH GRAVE
    /* 0xF5*/ 0x0131, // LATIN SMALL LETTER DOTLESS I
    /* 0xF6*/ 0x02C6, // MODIFIER LETTER CIRCUMFLEX ACCENT
    /* 0xF7*/ 0x02DC, // SMALL TILDE
    /* 0xF8*/ 0x00AF, // MACRON
    /* 0xF9*/ 0x02D8, // BREVE
    /* 0xFA*/ 0x02D9, // DOT ABOVE
    /* 0xFB*/ 0x02DA, // RING ABOVE
    /* 0xFC*/ 0x00B8, // CEDILLA
    /* 0xFD*/ 0x02DD, // DOUBLE ACUTE ACCENT
    /* 0xFE*/ 0x02DB, // OGONEK
    /* 0xFF*/ 0x02C7  // CARON
  };

  // 874 Thai - OEM ANSI
  // Verified using Windows 10 Dec 2017
  // 1161 (subset of 1162 except 0xDE maps to euro sign)
  // 1162 extension of 874
  static const ON__UINT32 code_page_874_0x80_to_0xFF[128] =
  {
    /* 0x80 */ 0x20ac, // code page 1162 extension of code page 874 // Euro Sign
    /* 0x81 */ 0x0081,
    /* 0x82 */ 0x0082,
    /* 0x83 */ 0x0083,
    /* 0x84 */ 0x0084,
    /* 0x85 */ 0x2026, // code page 1162 extension of code page 874 // Horizontal Ellipsis
    /* 0x86 */ 0x0086,
    /* 0x87 */ 0x0087,
    /* 0x88 */ 0x0088,
    /* 0x89 */ 0x0089,
    /* 0x8a */ 0x008a,
    /* 0x8b */ 0x008b,
    /* 0x8c */ 0x008c,
    /* 0x8d */ 0x008d,
    /* 0x8e */ 0x008e,
    /* 0x8f */ 0x008f,
    /* 0x90 */ 0x0090,
    /* 0x91 */ 0x2018, // code page 1162 extension of code page 874 // Single Turned Comma Quotation Mark
    /* 0x92 */ 0x2019, // code page 1162 extension of code page 874 // Single Comma Quotation Mark
    /* 0x93 */ 0x201c, // code page 1162 extension of code page 874 // Double Turned Comma Quotation Mark
    /* 0x94 */ 0x201d, // code page 1162 extension of code page 874 // Double Comma Quotation Mark
    /* 0x95 */ 0x2022, // code page 1162 extension of code page 874 // Bullet
    /* 0x96 */ 0x2013, // code page 1162 extension of code page 874 // En Dash
    /* 0x97 */ 0x2014, // code page 1162 extension of code page 874 // Em Dash
    /* 0x98 */ 0x0098,
    /* 0x99 */ 0x0099,
    /* 0x9a */ 0x009a,
    /* 0x9b */ 0x009b,
    /* 0x9c */ 0x009c,
    /* 0x9d */ 0x009d,
    /* 0x9e */ 0x009e,
    /* 0x9f */ 0x009f,
    /* 0xa0 */ 0x00a0, // Non-Breaking Space
    /* 0xa1 */ 0x0e01, // Thai Letter Ko Kai
    /* 0xa2 */ 0x0e02, // Thai Letter Kho Khai
    /* 0xa3 */ 0x0e03, // Thai Letter Kho Khuat
    /* 0xa4 */ 0x0e04, // Thai Letter Kho Khwai
    /* 0xa5 */ 0x0e05, // Thai Letter Kho Khon
    /* 0xa6 */ 0x0e06, // Thai Letter Kho Rakhang
    /* 0xa7 */ 0x0e07, // Thai Letter Ngo Ngu
    /* 0xa8 */ 0x0e08, // Thai Letter Cho Chan
    /* 0xa9 */ 0x0e09, // Thai Letter Cho Ching
    /* 0xaa */ 0x0e0a, // Thai Letter Cho Chang
    /* 0xab */ 0x0e0b, // Thai Letter So So
    /* 0xac */ 0x0e0c, // Thai Letter Cho Choe
    /* 0xad */ 0x0e0d, // Thai Letter Yo Ying
    /* 0xae */ 0x0e0e, // Thai Letter Do Chada
    /* 0xaf */ 0x0e0f, // Thai Letter To Patak
    /* 0xb0 */ 0x0e10, // Thai Letter Tho Than
    /* 0xb1 */ 0x0e11, // Thai Letter Tho Nangmontho
    /* 0xb2 */ 0x0e12, // Thai Letter Tho Phuthao
    /* 0xb3 */ 0x0e13, // Thai Letter No Nen
    /* 0xb4 */ 0x0e14, // Thai Letter Do Dek
    /* 0xb5 */ 0x0e15, // Thai Letter To Tao
    /* 0xb6 */ 0x0e16, // Thai Letter Tho Thung
    /* 0xb7 */ 0x0e17, // Thai Letter Tho Thahan
    /* 0xb8 */ 0x0e18, // Thai Letter Tho Thong
    /* 0xb9 */ 0x0e19, // Thai Letter No Nu
    /* 0xba */ 0x0e1a, // Thai Letter Bo Baimai
    /* 0xbb */ 0x0e1b, // Thai Letter Po Pla
    /* 0xbc */ 0x0e1c, // Thai Letter Pho Phung
    /* 0xbd */ 0x0e1d, // Thai Letter Fo Fa
    /* 0xbe */ 0x0e1e, // Thai Letter Pho Phan
    /* 0xbf */ 0x0e1f, // Thai Letter Fo Fan
    /* 0xc0 */ 0x0e20, // Thai Letter Pho Samphao
    /* 0xc1 */ 0x0e21, // Thai Letter Mo Ma
    /* 0xc2 */ 0x0e22, // Thai Letter Yo Yak
    /* 0xc3 */ 0x0e23, // Thai Letter Ro Rua
    /* 0xc4 */ 0x0e24, // Thai Letter Ru
    /* 0xc5 */ 0x0e25, // Thai Letter Lo Ling
    /* 0xc6 */ 0x0e26, // Thai Letter Lu
    /* 0xc7 */ 0x0e27, // Thai Letter Wo Waen
    /* 0xc8 */ 0x0e28, // Thai Letter So Sala
    /* 0xc9 */ 0x0e29, // Thai Letter So Rusi
    /* 0xca */ 0x0e2a, // Thai Letter So Sua
    /* 0xcb */ 0x0e2b, // Thai Letter Ho Hip
    /* 0xcc */ 0x0e2c, // Thai Letter Lo Chula
    /* 0xcd */ 0x0e2d, // Thai Letter O Ang
    /* 0xce */ 0x0e2e, // Thai Letter Ho Nok Huk
    /* 0xcf */ 0x0e2f, // Thai Pai Yan Noi
    /* 0xd0 */ 0x0e30, // Thai Vowel Sign Sara A
    /* 0xd1 */ 0x0e31, // Thai Vowel Sign Mai Han-Akat
    /* 0xd2 */ 0x0e32, // Thai Vowel Sign Sara Aa
    /* 0xd3 */ 0x0e33, // Thai Vowel Sign Sara Am
    /* 0xd4 */ 0x0e34, // Thai Vowel Sign Sara I
    /* 0xd5 */ 0x0e35, // Thai Vowel Sign Sara Ii
    /* 0xd6 */ 0x0e36, // Thai Vowel Sign Sara Ue
    /* 0xd7 */ 0x0e37, // Thai Vowel Sign Sara Uee
    /* 0xd8 */ 0x0e38, // Thai Vowel Sign Sara U
    /* 0xd9 */ 0x0e39, // Thai Vowel Sign Sara Uu
    /* 0xda */ 0x0e3a, // Thai Vowel Sign Phinthu
    /* 0xdb */ 0xf8c1, // Undefined -> EUDC
    /* 0xdc */ 0xf8c2, // Undefined -> EUDC
    /* 0xdd */ 0xf8c3, // Undefined -> EUDC
    /* 0xde */ 0xf8c4, // Undefined -> EUDC
    /* 0xdf */ 0x0e3f, // Thai Baht Sign
    /* 0xe0 */ 0x0e40, // Thai Vowel Sign Sara E
    /* 0xe1 */ 0x0e41, // Thai Vowel Sign Sara Ae
    /* 0xe2 */ 0x0e42, // Thai Vowel Sign Sara O
    /* 0xe3 */ 0x0e43, // Thai Vowel Sign Sara Mai Muan
    /* 0xe4 */ 0x0e44, // Thai Vowel Sign Sara Mai Malai
    /* 0xe5 */ 0x0e45, // Thai Lak Khang Yao
    /* 0xe6 */ 0x0e46, // Thai Mai Yamok
    /* 0xe7 */ 0x0e47, // Thai Vowel Sign Mai Tai Khu
    /* 0xe8 */ 0x0e48, // Thai Tone Mai Ek
    /* 0xe9 */ 0x0e49, // Thai Tone Mai Tho
    /* 0xea */ 0x0e4a, // Thai Tone Mai Tri
    /* 0xeb */ 0x0e4b, // Thai Tone Mai Chattawa
    /* 0xec */ 0x0e4c, // Thai Thanthakhat
    /* 0xed */ 0x0e4d, // Thai Nikkhahit
    /* 0xee */ 0x0e4e, // Thai Yamakkan
    /* 0xef */ 0x0e4f, // Thai Fongman
    /* 0xf0 */ 0x0e50, // Thai Digit 0
    /* 0xf1 */ 0x0e51, // Thai Digit 1
    /* 0xf2 */ 0x0e52, // Thai Digit 2
    /* 0xf3 */ 0x0e53, // Thai Digit 3
    /* 0xf4 */ 0x0e54, // Thai Digit 4
    /* 0xf5 */ 0x0e55, // Thai Digit 5
    /* 0xf6 */ 0x0e56, // Thai Digit 6
    /* 0xf7 */ 0x0e57, // Thai Digit 7
    /* 0xf8 */ 0x0e58, // Thai Digit 8
    /* 0xf9 */ 0x0e59, // Thai Digit 9
    /* 0xfa */ 0x0e5a, // Thai Angkhankhu
    /* 0xfb */ 0x0e5b, // Thai Khomut
    /* 0xfc */ 0xf8c5, // Undefined -> EUDC
    /* 0xfd */ 0xf8c6, // Undefined -> EUDC
    /* 0xfe */ 0xf8c7, // Undefined -> EUDC
    /* 0xff */ 0xf8c8 // Undefined -> EUDC
 };

  // 1250: Eastern Europe - ANSI
  // Verified using Windows 10 Dec 2017
  static const ON__UINT32 code_page_1250_0x80_to_0xFF[128] =
  {
    /* 0x80 */ 0x20ac, // Euro Sign
    /* 0x81 */ 0x0081,
    /* 0x82 */ 0x201a, // Single Low-9 Quotation Mark
    /* 0x83 */ 0x0083,
    /* 0x84 */ 0x201e, // Double Low-9 Quotation Mark
    /* 0x85 */ 0x2026, // Horizontal Ellipsis
    /* 0x86 */ 0x2020, // Dagger
    /* 0x87 */ 0x2021, // Double Dagger
    /* 0x88 */ 0x0088,
    /* 0x89 */ 0x2030, // Per Mille Sign
    /* 0x8a */ 0x0160, // Latin Capital Letter S With Caron
    /* 0x8b */ 0x2039, // Single Left-Pointing Angle Quotation Mark
    /* 0x8c */ 0x015a, // Latin Capital Letter S With Acute
    /* 0x8d */ 0x0164, // Latin Capital Letter T With Caron
    /* 0x8e */ 0x017d, // Latin Capital Letter Z With Caron
    /* 0x8f */ 0x0179, // Latin Capital Letter Z With Acute
    /* 0x90 */ 0x0090,
    /* 0x91 */ 0x2018, // Left Single Quotation Mark
    /* 0x92 */ 0x2019, // Right Single Quotation Mark
    /* 0x93 */ 0x201c, // Left Double Quotation Mark
    /* 0x94 */ 0x201d, // Right Double Quotation Mark
    /* 0x95 */ 0x2022, // Bullet
    /* 0x96 */ 0x2013, // En Dash
    /* 0x97 */ 0x2014, // Em Dash
    /* 0x98 */ 0x0098,
    /* 0x99 */ 0x2122, // Trade Mark Sign
    /* 0x9a */ 0x0161, // Latin Small Letter S With Caron
    /* 0x9b */ 0x203a, // Single Right-Pointing Angle Quotation Mark
    /* 0x9c */ 0x015b, // Latin Small Letter S With Acute
    /* 0x9d */ 0x0165, // Latin Small Letter T With Caron
    /* 0x9e */ 0x017e, // Latin Small Letter Z With Caron
    /* 0x9f */ 0x017a, // Latin Small Letter Z With Acute
    /* 0xa0 */ 0x00a0, // No-Break Space
    /* 0xa1 */ 0x02c7, // Caron
    /* 0xa2 */ 0x02d8, // Breve
    /* 0xa3 */ 0x0141, // Latin Capital Letter L With Stroke
    /* 0xa4 */ 0x00a4, // Currency Sign
    /* 0xa5 */ 0x0104, // Latin Capital Letter A With Ogonek
    /* 0xa6 */ 0x00a6, // Broken Bar
    /* 0xa7 */ 0x00a7, // Section Sign
    /* 0xa8 */ 0x00a8, // Diaeresis
    /* 0xa9 */ 0x00a9, // Copyright Sign
    /* 0xaa */ 0x015e, // Latin Capital Letter S With Cedilla
    /* 0xab */ 0x00ab, // Left-Pointing Double Angle Quotation Mark
    /* 0xac */ 0x00ac, // Not Sign
    /* 0xad */ 0x00ad, // Soft Hyphen
    /* 0xae */ 0x00ae, // Registered Sign
    /* 0xaf */ 0x017b, // Latin Capital Letter Z With Dot Above
    /* 0xb0 */ 0x00b0, // Degree Sign
    /* 0xb1 */ 0x00b1, // Plus-Minus Sign
    /* 0xb2 */ 0x02db, // Ogonek
    /* 0xb3 */ 0x0142, // Latin Small Letter L With Stroke
    /* 0xb4 */ 0x00b4, // Acute Accent
    /* 0xb5 */ 0x00b5, // Micro Sign
    /* 0xb6 */ 0x00b6, // Pilcrow Sign
    /* 0xb7 */ 0x00b7, // Middle Dot
    /* 0xb8 */ 0x00b8, // Cedilla
    /* 0xb9 */ 0x0105, // Latin Small Letter A With Ogonek
    /* 0xba */ 0x015f, // Latin Small Letter S With Cedilla
    /* 0xbb */ 0x00bb, // Right-Pointing Double Angle Quotation Mark
    /* 0xbc */ 0x013d, // Latin Capital Letter L With Caron
    /* 0xbd */ 0x02dd, // Double Acute Accent
    /* 0xbe */ 0x013e, // Latin Small Letter L With Caron
    /* 0xbf */ 0x017c, // Latin Small Letter Z With Dot Above
    /* 0xc0 */ 0x0154, // Latin Capital Letter R With Acute
    /* 0xc1 */ 0x00c1, // Latin Capital Letter A With Acute
    /* 0xc2 */ 0x00c2, // Latin Capital Letter A With Circumflex
    /* 0xc3 */ 0x0102, // Latin Capital Letter A With Breve
    /* 0xc4 */ 0x00c4, // Latin Capital Letter A With Diaeresis
    /* 0xc5 */ 0x0139, // Latin Capital Letter L With Acute
    /* 0xc6 */ 0x0106, // Latin Capital Letter C With Acute
    /* 0xc7 */ 0x00c7, // Latin Capital Letter C With Cedilla
    /* 0xc8 */ 0x010c, // Latin Capital Letter C With Caron
    /* 0xc9 */ 0x00c9, // Latin Capital Letter E With Acute
    /* 0xca */ 0x0118, // Latin Capital Letter E With Ogonek
    /* 0xcb */ 0x00cb, // Latin Capital Letter E With Diaeresis
    /* 0xcc */ 0x011a, // Latin Capital Letter E With Caron
    /* 0xcd */ 0x00cd, // Latin Capital Letter I With Acute
    /* 0xce */ 0x00ce, // Latin Capital Letter I With Circumflex
    /* 0xcf */ 0x010e, // Latin Capital Letter D With Caron
    /* 0xd0 */ 0x0110, // Latin Capital Letter D With Stroke
    /* 0xd1 */ 0x0143, // Latin Capital Letter N With Acute
    /* 0xd2 */ 0x0147, // Latin Capital Letter N With Caron
    /* 0xd3 */ 0x00d3, // Latin Capital Letter O With Acute
    /* 0xd4 */ 0x00d4, // Latin Capital Letter O With Circumflex
    /* 0xd5 */ 0x0150, // Latin Capital Letter O With Double Acute
    /* 0xd6 */ 0x00d6, // Latin Capital Letter O With Diaeresis
    /* 0xd7 */ 0x00d7, // Multiplication Sign
    /* 0xd8 */ 0x0158, // Latin Capital Letter R With Caron
    /* 0xd9 */ 0x016e, // Latin Capital Letter U With Ring Above
    /* 0xda */ 0x00da, // Latin Capital Letter U With Acute
    /* 0xdb */ 0x0170, // Latin Capital Letter U With Double Acute
    /* 0xdc */ 0x00dc, // Latin Capital Letter U With Diaeresis
    /* 0xdd */ 0x00dd, // Latin Capital Letter Y With Acute
    /* 0xde */ 0x0162, // Latin Capital Letter T With Cedilla
    /* 0xdf */ 0x00df, // Latin Small Letter Sharp S
    /* 0xe0 */ 0x0155, // Latin Small Letter R With Acute
    /* 0xe1 */ 0x00e1, // Latin Small Letter A With Acute
    /* 0xe2 */ 0x00e2, // Latin Small Letter A With Circumflex
    /* 0xe3 */ 0x0103, // Latin Small Letter A With Breve
    /* 0xe4 */ 0x00e4, // Latin Small Letter A With Diaeresis
    /* 0xe5 */ 0x013a, // Latin Small Letter L With Acute
    /* 0xe6 */ 0x0107, // Latin Small Letter C With Acute
    /* 0xe7 */ 0x00e7, // Latin Small Letter C With Cedilla
    /* 0xe8 */ 0x010d, // Latin Small Letter C With Caron
    /* 0xe9 */ 0x00e9, // Latin Small Letter E With Acute
    /* 0xea */ 0x0119, // Latin Small Letter E With Ogonek
    /* 0xeb */ 0x00eb, // Latin Small Letter E With Diaeresis
    /* 0xec */ 0x011b, // Latin Small Letter E With Caron
    /* 0xed */ 0x00ed, // Latin Small Letter I With Acute
    /* 0xee */ 0x00ee, // Latin Small Letter I With Circumflex
    /* 0xef */ 0x010f, // Latin Small Letter D With Caron
    /* 0xf0 */ 0x0111, // Latin Small Letter D With Stroke
    /* 0xf1 */ 0x0144, // Latin Small Letter N With Acute
    /* 0xf2 */ 0x0148, // Latin Small Letter N With Caron
    /* 0xf3 */ 0x00f3, // Latin Small Letter O With Acute
    /* 0xf4 */ 0x00f4, // Latin Small Letter O With Circumflex
    /* 0xf5 */ 0x0151, // Latin Small Letter O With Double Acute
    /* 0xf6 */ 0x00f6, // Latin Small Letter O With Diaeresis
    /* 0xf7 */ 0x00f7, // Division Sign
    /* 0xf8 */ 0x0159, // Latin Small Letter R With Caron
    /* 0xf9 */ 0x016f, // Latin Small Letter U With Ring Above
    /* 0xfa */ 0x00fa, // Latin Small Letter U With Acute
    /* 0xfb */ 0x0171, // Latin Small Letter U With Double Acute
    /* 0xfc */ 0x00fc, // Latin Small Letter U With Diaeresis
    /* 0xfd */ 0x00fd, // Latin Small Letter Y With Acute
    /* 0xfe */ 0x0163, // Latin Small Letter T With Cedilla
    /* 0xff */ 0x02d9	  // Dot Above
  };

  // 1251: Cyrillic - ANSI
  // Verified using Windows 10 Dec 2017
  static const ON__UINT32 code_page_1251_0x80_to_0xFF[128] =
  {
    /* 0x80 */ 0x0402, // Cyrillic Capital Letter Dje
    /* 0x81 */ 0x0403, // Cyrillic Capital Letter Gje
    /* 0x82 */ 0x201a, // Single Low-9 Quotation Mark
    /* 0x83 */ 0x0453, // Cyrillic Small Letter Gje
    /* 0x84 */ 0x201e, // Double Low-9 Quotation Mark
    /* 0x85 */ 0x2026, // Horizontal Ellipsis
    /* 0x86 */ 0x2020, // Dagger
    /* 0x87 */ 0x2021, // Double Dagger
    /* 0x88 */ 0x20ac, // Euro Sign
    /* 0x89 */ 0x2030, // Per Mille Sign
    /* 0x8a */ 0x0409, // Cyrillic Capital Letter Lje
    /* 0x8b */ 0x2039, // Single Left-Pointing Angle Quotation Mark
    /* 0x8c */ 0x040a, // Cyrillic Capital Letter Nje
    /* 0x8d */ 0x040c, // Cyrillic Capital Letter Kje
    /* 0x8e */ 0x040b, // Cyrillic Capital Letter Tshe
    /* 0x8f */ 0x040f, // Cyrillic Capital Letter Dzhe
    /* 0x90 */ 0x0452, // Cyrillic Small Letter Dje
    /* 0x91 */ 0x2018, // Left Single Quotation Mark
    /* 0x92 */ 0x2019, // Right Single Quotation Mark
    /* 0x93 */ 0x201c, // Left Double Quotation Mark
    /* 0x94 */ 0x201d, // Right Double Quotation Mark
    /* 0x95 */ 0x2022, // Bullet
    /* 0x96 */ 0x2013, // En Dash
    /* 0x97 */ 0x2014, // Em Dash
    /* 0x98 */ 0x0098,
    /* 0x99 */ 0x2122, // Trade Mark Sign
    /* 0x9a */ 0x0459, // Cyrillic Small Letter Lje
    /* 0x9b */ 0x203a, // Single Right-Pointing Angle Quotation Mark
    /* 0x9c */ 0x045a, // Cyrillic Small Letter Nje
    /* 0x9d */ 0x045c, // Cyrillic Small Letter Kje
    /* 0x9e */ 0x045b, // Cyrillic Small Letter Tshe
    /* 0x9f */ 0x045f, // Cyrillic Small Letter Dzhe
    /* 0xa0 */ 0x00a0, // No-Break Space
    /* 0xa1 */ 0x040e, // Cyrillic Capital Letter Short U
    /* 0xa2 */ 0x045e, // Cyrillic Small Letter Short U
    /* 0xa3 */ 0x0408, // Cyrillic Capital Letter Je
    /* 0xa4 */ 0x00a4, // Currency Sign
    /* 0xa5 */ 0x0490, // Cyrillic Capital Letter Ghe With Upturn
    /* 0xa6 */ 0x00a6, // Broken Bar
    /* 0xa7 */ 0x00a7, // Section Sign
    /* 0xa8 */ 0x0401, // Cyrillic Capital Letter Io
    /* 0xa9 */ 0x00a9, // Copyright Sign
    /* 0xaa */ 0x0404, // Cyrillic Capital Letter Ukrainian Ie
    /* 0xab */ 0x00ab, // Left-Pointing Double Angle Quotation Mark
    /* 0xac */ 0x00ac, // Not Sign
    /* 0xad */ 0x00ad, // Soft Hyphen
    /* 0xae */ 0x00ae, // Registered Sign
    /* 0xaf */ 0x0407, // Cyrillic Capital Letter Yi
    /* 0xb0 */ 0x00b0, // Degree Sign
    /* 0xb1 */ 0x00b1, // Plus-Minus Sign
    /* 0xb2 */ 0x0406, // Cyrillic Capital Letter Byelorussian-Ukrainian I
    /* 0xb3 */ 0x0456, // Cyrillic Small Letter Byelorussian-Ukrainian I
    /* 0xb4 */ 0x0491, // Cyrillic Small Letter Ghe With Upturn
    /* 0xb5 */ 0x00b5, // Micro Sign
    /* 0xb6 */ 0x00b6, // Pilcrow Sign
    /* 0xb7 */ 0x00b7, // Middle Dot
    /* 0xb8 */ 0x0451, // Cyrillic Small Letter Io
    /* 0xb9 */ 0x2116, // Numero Sign
    /* 0xba */ 0x0454, // Cyrillic Small Letter Ukrainian Ie
    /* 0xbb */ 0x00bb, // Right-Pointing Double Angle Quotation Mark
    /* 0xbc */ 0x0458, // Cyrillic Small Letter Je
    /* 0xbd */ 0x0405, // Cyrillic Capital Letter Dze
    /* 0xbe */ 0x0455, // Cyrillic Small Letter Dze
    /* 0xbf */ 0x0457, // Cyrillic Small Letter Yi
    /* 0xc0 */ 0x0410, // Cyrillic Capital Letter A
    /* 0xc1 */ 0x0411, // Cyrillic Capital Letter Be
    /* 0xc2 */ 0x0412, // Cyrillic Capital Letter Ve
    /* 0xc3 */ 0x0413, // Cyrillic Capital Letter Ghe
    /* 0xc4 */ 0x0414, // Cyrillic Capital Letter De
    /* 0xc5 */ 0x0415, // Cyrillic Capital Letter Ie
    /* 0xc6 */ 0x0416, // Cyrillic Capital Letter Zhe
    /* 0xc7 */ 0x0417, // Cyrillic Capital Letter Ze
    /* 0xc8 */ 0x0418, // Cyrillic Capital Letter I
    /* 0xc9 */ 0x0419, // Cyrillic Capital Letter Short I
    /* 0xca */ 0x041a, // Cyrillic Capital Letter Ka
    /* 0xcb */ 0x041b, // Cyrillic Capital Letter El
    /* 0xcc */ 0x041c, // Cyrillic Capital Letter Em
    /* 0xcd */ 0x041d, // Cyrillic Capital Letter En
    /* 0xce */ 0x041e, // Cyrillic Capital Letter O
    /* 0xcf */ 0x041f, // Cyrillic Capital Letter Pe
    /* 0xd0 */ 0x0420, // Cyrillic Capital Letter Er
    /* 0xd1 */ 0x0421, // Cyrillic Capital Letter Es
    /* 0xd2 */ 0x0422, // Cyrillic Capital Letter Te
    /* 0xd3 */ 0x0423, // Cyrillic Capital Letter U
    /* 0xd4 */ 0x0424, // Cyrillic Capital Letter Ef
    /* 0xd5 */ 0x0425, // Cyrillic Capital Letter Ha
    /* 0xd6 */ 0x0426, // Cyrillic Capital Letter Tse
    /* 0xd7 */ 0x0427, // Cyrillic Capital Letter Che
    /* 0xd8 */ 0x0428, // Cyrillic Capital Letter Sha
    /* 0xd9 */ 0x0429, // Cyrillic Capital Letter Shcha
    /* 0xda */ 0x042a, // Cyrillic Capital Letter Hard Sign
    /* 0xdb */ 0x042b, // Cyrillic Capital Letter Yeru
    /* 0xdc */ 0x042c, // Cyrillic Capital Letter Soft Sign
    /* 0xdd */ 0x042d, // Cyrillic Capital Letter E
    /* 0xde */ 0x042e, // Cyrillic Capital Letter Yu
    /* 0xdf */ 0x042f, // Cyrillic Capital Letter Ya
    /* 0xe0 */ 0x0430, // Cyrillic Small Letter A
    /* 0xe1 */ 0x0431, // Cyrillic Small Letter Be
    /* 0xe2 */ 0x0432, // Cyrillic Small Letter Ve
    /* 0xe3 */ 0x0433, // Cyrillic Small Letter Ghe
    /* 0xe4 */ 0x0434, // Cyrillic Small Letter De
    /* 0xe5 */ 0x0435, // Cyrillic Small Letter Ie
    /* 0xe6 */ 0x0436, // Cyrillic Small Letter Zhe
    /* 0xe7 */ 0x0437, // Cyrillic Small Letter Ze
    /* 0xe8 */ 0x0438, // Cyrillic Small Letter I
    /* 0xe9 */ 0x0439, // Cyrillic Small Letter Short I
    /* 0xea */ 0x043a, // Cyrillic Small Letter Ka
    /* 0xeb */ 0x043b, // Cyrillic Small Letter El
    /* 0xec */ 0x043c, // Cyrillic Small Letter Em
    /* 0xed */ 0x043d, // Cyrillic Small Letter En
    /* 0xee */ 0x043e, // Cyrillic Small Letter O
    /* 0xef */ 0x043f, // Cyrillic Small Letter Pe
    /* 0xf0 */ 0x0440, // Cyrillic Small Letter Er
    /* 0xf1 */ 0x0441, // Cyrillic Small Letter Es
    /* 0xf2 */ 0x0442, // Cyrillic Small Letter Te
    /* 0xf3 */ 0x0443, // Cyrillic Small Letter U
    /* 0xf4 */ 0x0444, // Cyrillic Small Letter Ef
    /* 0xf5 */ 0x0445, // Cyrillic Small Letter Ha
    /* 0xf6 */ 0x0446, // Cyrillic Small Letter Tse
    /* 0xf7 */ 0x0447, // Cyrillic Small Letter Che
    /* 0xf8 */ 0x0448, // Cyrillic Small Letter Sha
    /* 0xf9 */ 0x0449, // Cyrillic Small Letter Shcha
    /* 0xfa */ 0x044a, // Cyrillic Small Letter Hard Sign
    /* 0xfb */ 0x044b, // Cyrillic Small Letter Yeru
    /* 0xfc */ 0x044c, // Cyrillic Small Letter Soft Sign
    /* 0xfd */ 0x044d, // Cyrillic Small Letter E
    /* 0xfe */ 0x044e, // Cyrillic Small Letter Yu
    /* 0xff */ 0x044f	 // Cyrillic Small Letter Ya
  };

  // 1253: Greek - ANSI
  // Verified using Windows 10 Dec 2017
    static const ON__UINT32 code_page_1253_0x80_to_0xFF[128] =
  {
    /* 0x80 */ 0x20ac, // Euro Sign
    /* 0x81 */ 0x0081,
    /* 0x82 */ 0x201a, // Single Low-9 Quotation Mark
    /* 0x83 */ 0x0192, // Latin Small Letter F With Hook
    /* 0x84 */ 0x201e, // Double Low-9 Quotation Mark
    /* 0x85 */ 0x2026, // Horizontal Ellipsis
    /* 0x86 */ 0x2020, // Dagger
    /* 0x87 */ 0x2021, // Double Dagger
    /* 0x88 */ 0x0088,
    /* 0x89 */ 0x2030, // Per Mille Sign
    /* 0x8a */ 0x008a,
    /* 0x8b */ 0x2039, // Single Left-Pointing Angle Quotation Mark
    /* 0x8c */ 0x008c,
    /* 0x8d */ 0x008d,
    /* 0x8e */ 0x008e,
    /* 0x8f */ 0x008f,
    /* 0x90 */ 0x0090,
    /* 0x91 */ 0x2018, // Left Single Quotation Mark
    /* 0x92 */ 0x2019, // Right Single Quotation Mark
    /* 0x93 */ 0x201c, // Left Double Quotation Mark
    /* 0x94 */ 0x201d, // Right Double Quotation Mark
    /* 0x95 */ 0x2022, // Bullet
    /* 0x96 */ 0x2013, // En Dash
    /* 0x97 */ 0x2014, // Em Dash
    /* 0x98 */ 0x0098,
    /* 0x99 */ 0x2122, // Trade Mark Sign
    /* 0x9a */ 0x009a,
    /* 0x9b */ 0x203a, // Single Right-Pointing Angle Quotation Mark
    /* 0x9c */ 0x009c,
    /* 0x9d */ 0x009d,
    /* 0x9e */ 0x009e,
    /* 0x9f */ 0x009f,
    /* 0xa0 */ 0x00a0, // No-Break Space
    /* 0xa1 */ 0x0385, // Greek Dialytika Tonos
    /* 0xa2 */ 0x0386, // Greek Capital Letter Alpha With Tonos
    /* 0xa3 */ 0x00a3, // Pound Sign
    /* 0xa4 */ 0x00a4, // Currency Sign
    /* 0xa5 */ 0x00a5, // Yen Sign
    /* 0xa6 */ 0x00a6, // Broken Bar
    /* 0xa7 */ 0x00a7, // Section Sign
    /* 0xa8 */ 0x00a8, // Diaeresis
    /* 0xa9 */ 0x00a9, // Copyright Sign
    /* 0xaa */ 0xf8f9, // Undefined -> EUDC
    /* 0xab */ 0x00ab, // Left-Pointing Double Angle Quotation Mark
    /* 0xac */ 0x00ac, // Not Sign
    /* 0xad */ 0x00ad, // Soft Hyphen
    /* 0xae */ 0x00ae, // Registered Sign
    /* 0xaf */ 0x2015, // Horizontal Bar
    /* 0xb0 */ 0x00b0, // Degree Sign
    /* 0xb1 */ 0x00b1, // Plus-Minus Sign
    /* 0xb2 */ 0x00b2, // Superscript Two
    /* 0xb3 */ 0x00b3, // Superscript Three
    /* 0xb4 */ 0x0384, // Greek Tonos
    /* 0xb5 */ 0x00b5, // Micro Sign
    /* 0xb6 */ 0x00b6, // Pilcrow Sign
    /* 0xb7 */ 0x00b7, // Middle Dot
    /* 0xb8 */ 0x0388, // Greek Capital Letter Epsilon With Tonos
    /* 0xb9 */ 0x0389, // Greek Capital Letter Eta With Tonos
    /* 0xba */ 0x038a, // Greek Capital Letter Iota With Tonos
    /* 0xbb */ 0x00bb, // Right-Pointing Double Angle Quotation Mark
    /* 0xbc */ 0x038c, // Greek Capital Letter Omicron With Tonos
    /* 0xbd */ 0x00bd, // Vulgar Fraction One Half
    /* 0xbe */ 0x038e, // Greek Capital Letter Upsilon With Tonos
    /* 0xbf */ 0x038f, // Greek Capital Letter Omega With Tonos
    /* 0xc0 */ 0x0390, // Greek Small Letter Iota With Dialytika And Tonos
    /* 0xc1 */ 0x0391, // Greek Capital Letter Alpha
    /* 0xc2 */ 0x0392, // Greek Capital Letter Beta
    /* 0xc3 */ 0x0393, // Greek Capital Letter Gamma
    /* 0xc4 */ 0x0394, // Greek Capital Letter Delta
    /* 0xc5 */ 0x0395, // Greek Capital Letter Epsilon
    /* 0xc6 */ 0x0396, // Greek Capital Letter Zeta
    /* 0xc7 */ 0x0397, // Greek Capital Letter Eta
    /* 0xc8 */ 0x0398, // Greek Capital Letter Theta
    /* 0xc9 */ 0x0399, // Greek Capital Letter Iota
    /* 0xca */ 0x039a, // Greek Capital Letter Kappa
    /* 0xcb */ 0x039b, // Greek Capital Letter Lamda
    /* 0xcc */ 0x039c, // Greek Capital Letter Mu
    /* 0xcd */ 0x039d, // Greek Capital Letter Nu
    /* 0xce */ 0x039e, // Greek Capital Letter Xi
    /* 0xcf */ 0x039f, // Greek Capital Letter Omicron
    /* 0xd0 */ 0x03a0, // Greek Capital Letter Pi
    /* 0xd1 */ 0x03a1, // Greek Capital Letter Rho
    /* 0xd2 */ 0xf8fa, // Undefined -> EUDC
    /* 0xd3 */ 0x03a3, // Greek Capital Letter Sigma
    /* 0xd4 */ 0x03a4, // Greek Capital Letter Tau
    /* 0xd5 */ 0x03a5, // Greek Capital Letter Upsilon
    /* 0xd6 */ 0x03a6, // Greek Capital Letter Phi
    /* 0xd7 */ 0x03a7, // Greek Capital Letter Chi
    /* 0xd8 */ 0x03a8, // Greek Capital Letter Psi
    /* 0xd9 */ 0x03a9, // Greek Capital Letter Omega
    /* 0xda */ 0x03aa, // Greek Capital Letter Iota With Dialytika
    /* 0xdb */ 0x03ab, // Greek Capital Letter Upsilon With Dialytika
    /* 0xdc */ 0x03ac, // Greek Small Letter Alpha With Tonos
    /* 0xdd */ 0x03ad, // Greek Small Letter Epsilon With Tonos
    /* 0xde */ 0x03ae, // Greek Small Letter Eta With Tonos
    /* 0xdf */ 0x03af, // Greek Small Letter Iota With Tonos
    /* 0xe0 */ 0x03b0, // Greek Small Letter Upsilon With Dialytika And Tonos
    /* 0xe1 */ 0x03b1, // Greek Small Letter Alpha
    /* 0xe2 */ 0x03b2, // Greek Small Letter Beta
    /* 0xe3 */ 0x03b3, // Greek Small Letter Gamma
    /* 0xe4 */ 0x03b4, // Greek Small Letter Delta
    /* 0xe5 */ 0x03b5, // Greek Small Letter Epsilon
    /* 0xe6 */ 0x03b6, // Greek Small Letter Zeta
    /* 0xe7 */ 0x03b7, // Greek Small Letter Eta
    /* 0xe8 */ 0x03b8, // Greek Small Letter Theta
    /* 0xe9 */ 0x03b9, // Greek Small Letter Iota
    /* 0xea */ 0x03ba, // Greek Small Letter Kappa
    /* 0xeb */ 0x03bb, // Greek Small Letter Lamda
    /* 0xec */ 0x03bc, // Greek Small Letter Mu
    /* 0xed */ 0x03bd, // Greek Small Letter Nu
    /* 0xee */ 0x03be, // Greek Small Letter Xi
    /* 0xef */ 0x03bf, // Greek Small Letter Omicron
    /* 0xf0 */ 0x03c0, // Greek Small Letter Pi
    /* 0xf1 */ 0x03c1, // Greek Small Letter Rho
    /* 0xf2 */ 0x03c2, // Greek Small Letter Final Sigma
    /* 0xf3 */ 0x03c3, // Greek Small Letter Sigma
    /* 0xf4 */ 0x03c4, // Greek Small Letter Tau
    /* 0xf5 */ 0x03c5, // Greek Small Letter Upsilon
    /* 0xf6 */ 0x03c6, // Greek Small Letter Phi
    /* 0xf7 */ 0x03c7, // Greek Small Letter Chi
    /* 0xf8 */ 0x03c8, // Greek Small Letter Psi
    /* 0xf9 */ 0x03c9, // Greek Small Letter Omega
    /* 0xfa */ 0x03ca, // Greek Small Letter Iota With Dialytika
    /* 0xfb */ 0x03cb, // Greek Small Letter Upsilon With Dialytika
    /* 0xfc */ 0x03cc, // Greek Small Letter Omicron With Tonos
    /* 0xfd */ 0x03cd, // Greek Small Letter Upsilon With Tonos
    /* 0xfe */ 0x03ce, // Greek Small Letter Omega With Tonos
    /* 0xff */ 0xf8fb	 // Undefined -> EUDC
  };

  // 1254: Turkish - ANSI
  // Verified using Windows 10 Dec 2017
  static const ON__UINT32 code_page_1254_0x80_to_0xFF[128] =
  {
    /* 0x80 */ 0x20ac, // Euro Sign
    /* 0x81 */ 0x0081,
    /* 0x82 */ 0x201a, // Single Low-9 Quotation Mark
    /* 0x83 */ 0x0192, // Latin Small Letter F With Hook
    /* 0x84 */ 0x201e, // Double Low-9 Quotation Mark
    /* 0x85 */ 0x2026, // Horizontal Ellipsis
    /* 0x86 */ 0x2020, // Dagger
    /* 0x87 */ 0x2021, // Double Dagger
    /* 0x88 */ 0x02c6, // Modifier Letter Circumflex Accent
    /* 0x89 */ 0x2030, // Per Mille Sign
    /* 0x8a */ 0x0160, // Latin Capital Letter S With Caron
    /* 0x8b */ 0x2039, // Single Left-Pointing Angle Quotation Mark
    /* 0x8c */ 0x0152, // Latin Capital Ligature Oe
    /* 0x8d */ 0x008d,
    /* 0x8e */ 0x008e,
    /* 0x8f */ 0x008f,
    /* 0x90 */ 0x0090,
    /* 0x91 */ 0x2018, // Left Single Quotation Mark
    /* 0x92 */ 0x2019, // Right Single Quotation Mark
    /* 0x93 */ 0x201c, // Left Double Quotation Mark
    /* 0x94 */ 0x201d, // Right Double Quotation Mark
    /* 0x95 */ 0x2022, // Bullet
    /* 0x96 */ 0x2013, // En Dash
    /* 0x97 */ 0x2014, // Em Dash
    /* 0x98 */ 0x02dc, // Small Tilde
    /* 0x99 */ 0x2122, // Trade Mark Sign
    /* 0x9a */ 0x0161, // Latin Small Letter S With Caron
    /* 0x9b */ 0x203a, // Single Right-Pointing Angle Quotation Mark
    /* 0x9c */ 0x0153, // Latin Small Ligature Oe
    /* 0x9d */ 0x009d,
    /* 0x9e */ 0x009e,
    /* 0x9f */ 0x0178, // Latin Capital Letter Y With Diaeresis
    /* 0xa0 */ 0x00a0, // No-Break Space
    /* 0xa1 */ 0x00a1, // Inverted Exclamation Mark
    /* 0xa2 */ 0x00a2, // Cent Sign
    /* 0xa3 */ 0x00a3, // Pound Sign
    /* 0xa4 */ 0x00a4, // Currency Sign
    /* 0xa5 */ 0x00a5, // Yen Sign
    /* 0xa6 */ 0x00a6, // Broken Bar
    /* 0xa7 */ 0x00a7, // Section Sign
    /* 0xa8 */ 0x00a8, // Diaeresis
    /* 0xa9 */ 0x00a9, // Copyright Sign
    /* 0xaa */ 0x00aa, // Feminine Ordinal Indicator
    /* 0xab */ 0x00ab, // Left-Pointing Double Angle Quotation Mark
    /* 0xac */ 0x00ac, // Not Sign
    /* 0xad */ 0x00ad, // Soft Hyphen
    /* 0xae */ 0x00ae, // Registered Sign
    /* 0xaf */ 0x00af, // Macron
    /* 0xb0 */ 0x00b0, // Degree Sign
    /* 0xb1 */ 0x00b1, // Plus-Minus Sign
    /* 0xb2 */ 0x00b2, // Superscript Two
    /* 0xb3 */ 0x00b3, // Superscript Three
    /* 0xb4 */ 0x00b4, // Acute Accent
    /* 0xb5 */ 0x00b5, // Micro Sign
    /* 0xb6 */ 0x00b6, // Pilcrow Sign
    /* 0xb7 */ 0x00b7, // Middle Dot
    /* 0xb8 */ 0x00b8, // Cedilla
    /* 0xb9 */ 0x00b9, // Superscript One
    /* 0xba */ 0x00ba, // Masculine Ordinal Indicator
    /* 0xbb */ 0x00bb, // Right-Pointing Double Angle Quotation Mark
    /* 0xbc */ 0x00bc, // Vulgar Fraction One Quarter
    /* 0xbd */ 0x00bd, // Vulgar Fraction One Half
    /* 0xbe */ 0x00be, // Vulgar Fraction Three Quarters
    /* 0xbf */ 0x00bf, // Inverted Question Mark
    /* 0xc0 */ 0x00c0, // Latin Capital Letter A With Grave
    /* 0xc1 */ 0x00c1, // Latin Capital Letter A With Acute
    /* 0xc2 */ 0x00c2, // Latin Capital Letter A With Circumflex
    /* 0xc3 */ 0x00c3, // Latin Capital Letter A With Tilde
    /* 0xc4 */ 0x00c4, // Latin Capital Letter A With Diaeresis
    /* 0xc5 */ 0x00c5, // Latin Capital Letter A With Ring Above
    /* 0xc6 */ 0x00c6, // Latin Capital Ligature Ae
    /* 0xc7 */ 0x00c7, // Latin Capital Letter C With Cedilla
    /* 0xc8 */ 0x00c8, // Latin Capital Letter E With Grave
    /* 0xc9 */ 0x00c9, // Latin Capital Letter E With Acute
    /* 0xca */ 0x00ca, // Latin Capital Letter E With Circumflex
    /* 0xcb */ 0x00cb, // Latin Capital Letter E With Diaeresis
    /* 0xcc */ 0x00cc, // Latin Capital Letter I With Grave
    /* 0xcd */ 0x00cd, // Latin Capital Letter I With Acute
    /* 0xce */ 0x00ce, // Latin Capital Letter I With Circumflex
    /* 0xcf */ 0x00cf, // Latin Capital Letter I With Diaeresis
    /* 0xd0 */ 0x011e, // Latin Capital Letter G With Breve
    /* 0xd1 */ 0x00d1, // Latin Capital Letter N With Tilde
    /* 0xd2 */ 0x00d2, // Latin Capital Letter O With Grave
    /* 0xd3 */ 0x00d3, // Latin Capital Letter O With Acute
    /* 0xd4 */ 0x00d4, // Latin Capital Letter O With Circumflex
    /* 0xd5 */ 0x00d5, // Latin Capital Letter O With Tilde
    /* 0xd6 */ 0x00d6, // Latin Capital Letter O With Diaeresis
    /* 0xd7 */ 0x00d7, // Multiplication Sign
    /* 0xd8 */ 0x00d8, // Latin Capital Letter O With Stroke
    /* 0xd9 */ 0x00d9, // Latin Capital Letter U With Grave
    /* 0xda */ 0x00da, // Latin Capital Letter U With Acute
    /* 0xdb */ 0x00db, // Latin Capital Letter U With Circumflex
    /* 0xdc */ 0x00dc, // Latin Capital Letter U With Diaeresis
    /* 0xdd */ 0x0130, // Latin Capital Letter I With Dot Above
    /* 0xde */ 0x015e, // Latin Capital Letter S With Cedilla
    /* 0xdf */ 0x00df, // Latin Small Letter Sharp S
    /* 0xe0 */ 0x00e0, // Latin Small Letter A With Grave
    /* 0xe1 */ 0x00e1, // Latin Small Letter A With Acute
    /* 0xe2 */ 0x00e2, // Latin Small Letter A With Circumflex
    /* 0xe3 */ 0x00e3, // Latin Small Letter A With Tilde
    /* 0xe4 */ 0x00e4, // Latin Small Letter A With Diaeresis
    /* 0xe5 */ 0x00e5, // Latin Small Letter A With Ring Above
    /* 0xe6 */ 0x00e6, // Latin Small Ligature Ae
    /* 0xe7 */ 0x00e7, // Latin Small Letter C With Cedilla
    /* 0xe8 */ 0x00e8, // Latin Small Letter E With Grave
    /* 0xe9 */ 0x00e9, // Latin Small Letter E With Acute
    /* 0xea */ 0x00ea, // Latin Small Letter E With Circumflex
    /* 0xeb */ 0x00eb, // Latin Small Letter E With Diaeresis
    /* 0xec */ 0x00ec, // Latin Small Letter I With Grave
    /* 0xed */ 0x00ed, // Latin Small Letter I With Acute
    /* 0xee */ 0x00ee, // Latin Small Letter I With Circumflex
    /* 0xef */ 0x00ef, // Latin Small Letter I With Diaeresis
    /* 0xf0 */ 0x011f, // Latin Small Letter G With Breve
    /* 0xf1 */ 0x00f1, // Latin Small Letter N With Tilde
    /* 0xf2 */ 0x00f2, // Latin Small Letter O With Grave
    /* 0xf3 */ 0x00f3, // Latin Small Letter O With Acute
    /* 0xf4 */ 0x00f4, // Latin Small Letter O With Circumflex
    /* 0xf5 */ 0x00f5, // Latin Small Letter O With Tilde
    /* 0xf6 */ 0x00f6, // Latin Small Letter O With Diaeresis
    /* 0xf7 */ 0x00f7, // Division Sign
    /* 0xf8 */ 0x00f8, // Latin Small Letter O With Stroke
    /* 0xf9 */ 0x00f9, // Latin Small Letter U With Grave
    /* 0xfa */ 0x00fa, // Latin Small Letter U With Acute
    /* 0xfb */ 0x00fb, // Latin Small Letter U With Circumflex
    /* 0xfc */ 0x00fc, // Latin Small Letter U With Diaeresis
    /* 0xfd */ 0x0131, // Latin Small Letter Dotless I
    /* 0xfe */ 0x015f, // Latin Small Letter S With Cedilla
    /* 0xff */ 0x00ff  // Latin Small Letter Y With Diaeresis
  };

  // 1255: Hebrew - ANSI
  // Verified using Windows 10 Dec 2017
  static const ON__UINT32 code_page_1255_0x80_to_0xFF[128] =
  {
    /* 0x80 */ 0x20ac, // Euro Sign
    /* 0x81 */ 0x0081, // Undefined -> Control
    /* 0x82 */ 0x201a, // Low Single Comma Quotation Mark
    /* 0x83 */ 0x0192, // Latin Small Letter Script F
    /* 0x84 */ 0x201e, // Low Double Comma Quotation Mark
    /* 0x85 */ 0x2026, // Horizontal Ellipsis
    /* 0x86 */ 0x2020, // Dagger
    /* 0x87 */ 0x2021, // Double Dagger
    /* 0x88 */ 0x02c6, // Modifier Letter Circumflex
    /* 0x89 */ 0x2030, // Per Mille Sign
    /* 0x8a */ 0x008a, // Undefined -> Control
    /* 0x8b */ 0x2039, // Left Pointing Single Guillemet
    /* 0x8c */ 0x008c, // Undefined -> Control
    /* 0x8d */ 0x008d, // Undefined -> Control
    /* 0x8e */ 0x008e, // Undefined -> Control
    /* 0x8f */ 0x008f, // Undefined -> Control
    /* 0x90 */ 0x0090, // Undefined -> Control
    /* 0x91 */ 0x2018, // Single Turned Comma Quotation Mark
    /* 0x92 */ 0x2019, // Single Comma Quotation Mark
    /* 0x93 */ 0x201c, // Double Turned Comma Quotation Mark
    /* 0x94 */ 0x201d, // Double Comma Quotation Mark
    /* 0x95 */ 0x2022, // Bullet
    /* 0x96 */ 0x2013, // En Dash
    /* 0x97 */ 0x2014, // Em Dash
    /* 0x98 */ 0x02dc, // Spacing Tilde
    /* 0x99 */ 0x2122, // Trademark
    /* 0x9a */ 0x009a, // Undefined -> Control
    /* 0x9b */ 0x203a, // Right Pointing Single Guillemet
    /* 0x9c */ 0x009c, // Undefined -> Control
    /* 0x9d */ 0x009d, // Undefined -> Control
    /* 0x9e */ 0x009e, // Undefined -> Control
    /* 0x9f */ 0x009f, // Undefined -> Control
    /* 0xa0 */ 0x00a0, // Non-Breaking Space
    /* 0xa1 */ 0x00a1, // Inverted Exclamation Mark
    /* 0xa2 */ 0x00a2, // Cent Sign
    /* 0xa3 */ 0x00a3, // Pound Sign
    /* 0xa4 */ 0x20aa, // New Sheqel Sign
    /* 0xa5 */ 0x00a5, // Yen Sign
    /* 0xa6 */ 0x00a6, // Broken Vertical Bar
    /* 0xa7 */ 0x00a7, // Section Sign
    /* 0xa8 */ 0x00a8, // Spacing Diaeresis
    /* 0xa9 */ 0x00a9, // Copyright Sign
    /* 0xaa */ 0x00d7, // Multiplication Sign
    /* 0xab */ 0x00ab, // Left Pointing Guillemet
    /* 0xac */ 0x00ac, // Not Sign
    /* 0xad */ 0x00ad, // Soft Hyphen
    /* 0xae */ 0x00ae, // Registered Trade Mark Sign
    /* 0xaf */ 0x00af, // Spacing Macron
    /* 0xb0 */ 0x00b0, // Degree Sign
    /* 0xb1 */ 0x00b1, // Plus-Or-Minus Sign
    /* 0xb2 */ 0x00b2, // Superscript Digit Two
    /* 0xb3 */ 0x00b3, // Superscript Digit Three
    /* 0xb4 */ 0x00b4, // Spacing Acute
    /* 0xb5 */ 0x00b5, // Micro Sign
    /* 0xb6 */ 0x00b6, // Paragraph Sign
    /* 0xb7 */ 0x00b7, // Middle Dot
    /* 0xb8 */ 0x00b8, // Spacing Cedilla
    /* 0xb9 */ 0x00b9, // Superscript Digit One
    /* 0xba */ 0x00f7, // Division Sign
    /* 0xbb */ 0x00bb, // Right Pointing Guillemet
    /* 0xbc */ 0x00bc, // Fraction One Quarter
    /* 0xbd */ 0x00bd, // Fraction One Half
    /* 0xbe */ 0x00be, // Fraction Three Quarters
    /* 0xbf */ 0x00bf, // Inverted Question Mark
    /* 0xc0 */ 0x05b0, // Hebrew Point Sheva
    /* 0xc1 */ 0x05b1, // Hebrew Point Hataf Segol
    /* 0xc2 */ 0x05b2, // Hebrew Point Hataf Patah
    /* 0xc3 */ 0x05b3, // Hebrew Point Hataf Qamats
    /* 0xc4 */ 0x05b4, // Hebrew Point Hiriq
    /* 0xc5 */ 0x05b5, // Hebrew Point Tsere
    /* 0xc6 */ 0x05b6, // Hebrew Point Segol
    /* 0xc7 */ 0x05b7, // Hebrew Point Patah
    /* 0xc8 */ 0x05b8, // Hebrew Point Qamats
    /* 0xc9 */ 0x05b9, // Hebrew Point Holam
    /* 0xca */ 0x05ba, // Hebrew Point ????
    /* 0xcb */ 0x05bb, // Hebrew Point Qubuts
    /* 0xcc */ 0x05bc, // Hebrew Point Dagesh
    /* 0xcd */ 0x05bd, // Hebrew Point Meteg
    /* 0xce */ 0x05be, // Hebrew Punctuation Maqaf
    /* 0xcf */ 0x05bf, // Hebrew Point Rafe
    /* 0xd0 */ 0x05c0, // Hebrew Point Paseq
    /* 0xd1 */ 0x05c1, // Hebrew Point Shin Dot
    /* 0xd2 */ 0x05c2, // Hebrew Point Sin Dot
    /* 0xd3 */ 0x05c3, // Hebrew Punctuation Sof Pasuq
    /* 0xd4 */ 0x05f0, // Hebrew Ligature Yiddish Double Vav
    /* 0xd5 */ 0x05f1, // Hebrew Ligature Yiddish Vav Yod
    /* 0xd6 */ 0x05f2, // Hebrew Ligature Yiddish Double Yod
    /* 0xd7 */ 0x05f3, // Hebrew Punctuation Geresh
    /* 0xd8 */ 0x05f4, // Hebrew Punctuation Gershayim
    /* 0xd9 */ 0xf88d, // Undefined -> EUDC
    /* 0xda */ 0xf88e, // Undefined -> EUDC
    /* 0xdb */ 0xf88f, // Undefined -> EUDC
    /* 0xdc */ 0xf890, // Undefined -> EUDC
    /* 0xdd */ 0xf891, // Undefined -> EUDC
    /* 0xde */ 0xf892, // Undefined -> EUDC
    /* 0xdf */ 0xf893, // Undefined -> EUDC
    /* 0xe0 */ 0x05d0, // Hebrew Letter Alef
    /* 0xe1 */ 0x05d1, // Hebrew Letter Bet
    /* 0xe2 */ 0x05d2, // Hebrew Letter Gimel
    /* 0xe3 */ 0x05d3, // Hebrew Letter Dalet
    /* 0xe4 */ 0x05d4, // Hebrew Letter He
    /* 0xe5 */ 0x05d5, // Hebrew Letter Vav
    /* 0xe6 */ 0x05d6, // Hebrew Letter Zayin
    /* 0xe7 */ 0x05d7, // Hebrew Letter Het
    /* 0xe8 */ 0x05d8, // Hebrew Letter Tet
    /* 0xe9 */ 0x05d9, // Hebrew Letter Yod
    /* 0xea */ 0x05da, // Hebrew Letter Final Kaf
    /* 0xeb */ 0x05db, // Hebrew Letter Kaf
    /* 0xec */ 0x05dc, // Hebrew Letter Lamed
    /* 0xed */ 0x05dd, // Hebrew Letter Final Mem
    /* 0xee */ 0x05de, // Hebrew Letter Mem
    /* 0xef */ 0x05df, // Hebrew Letter Final Nun
    /* 0xf0 */ 0x05e0, // Hebrew Letter Nun
    /* 0xf1 */ 0x05e1, // Hebrew Letter Samekh
    /* 0xf2 */ 0x05e2, // Hebrew Letter Ayin
    /* 0xf3 */ 0x05e3, // Hebrew Letter Final Pe
    /* 0xf4 */ 0x05e4, // Hebrew Letter Pe
    /* 0xf5 */ 0x05e5, // Hebrew Letter Final Tsadi
    /* 0xf6 */ 0x05e6, // Hebrew Letter Tsadi
    /* 0xf7 */ 0x05e7, // Hebrew Letter Qof
    /* 0xf8 */ 0x05e8, // Hebrew Letter Resh
    /* 0xf9 */ 0x05e9, // Hebrew Letter Shin
    /* 0xfa */ 0x05ea, // Hebrew Letter Tav
    /* 0xfb */ 0xf894, // Undefined -> EUDC
    /* 0xfc */ 0xf895, // Undefined -> EUDC
    /* 0xfd */ 0x200e, // Left-To-Right Mark
    /* 0xfe */ 0x200f, // Right-To-Left Mark
    /* 0xff */ 0xf896	 // Undefined -> EUDC
  };

  // 1256: Arabic - ANSI
  // Verified using Windows 10 Dec 2017
  static const ON__UINT32 code_page_1256_0x80_to_0xFF[128] =
  {
    /* 0x80 */ 0x20ac	, // Euro Sign
    /* 0x81 */ 0x067e	, // Arabic Taa with Three Dots Below
    /* 0x82 */ 0x201a	, // Low Single Comma Quotation Mark
    /* 0x83 */ 0x0192	, // Latin Small Letter Script F
    /* 0x84 */ 0x201e	, // Low Double Comma Quotation Mark
    /* 0x85 */ 0x2026	, // Horizontal Ellipsis
    /* 0x86 */ 0x2020	, // Dagger
    /* 0x87 */ 0x2021	, // Double Dagger
    /* 0x88 */ 0x02c6	, // Modifier Letter Circumflex
    /* 0x89 */ 0x2030	, // Per Mille Sign
    /* 0x8a */ 0x0679	, // Arabic Letter Tteh
    /* 0x8b */ 0x2039	, // Left Pointing Single Guillemet
    /* 0x8c */ 0x0152	, // Latin Capital Letter O E
    /* 0x8d */ 0x0686	, // Arabic Haa with Middle Three Dots Downward
    /* 0x8e */ 0x0698	, // Arabic Ra with Three Dots Above
    /* 0x8f */ 0x0688	, // Arabic Letter Ddal
    /* 0x90 */ 0x06af	, // Arabic Gaf
    /* 0x91 */ 0x2018	, // Single Turned Comma Quotation Mark
    /* 0x92 */ 0x2019	, // Single Comma Quotation Mark
    /* 0x93 */ 0x201c	, // Double Turned Comma Quotation Mark
    /* 0x94 */ 0x201d	, // Double Comma Quotation Mark
    /* 0x95 */ 0x2022	, // Bullet
    /* 0x96 */ 0x2013	, // En Dash
    /* 0x97 */ 0x2014	, // Em Dash
    /* 0x98 */ 0x06a9	, // Arabic Letter Keheh
    /* 0x99 */ 0x2122	, // Trademark
    /* 0x9a */ 0x0691	, // Arabic Letter Rreh
    /* 0x9b */ 0x203a	, // Right Pointing Single Guillemet
    /* 0x9c */ 0x0153	, // Latin Small Letter O E
    /* 0x9d */ 0x200c	, // Zero Width Non-Joiner
    /* 0x9e */ 0x200d	, // Zero Width Joiner
    /* 0x9f */ 0x06ba	, // Arabic Letter Noon Ghunna
    /* 0xa0 */ 0x00a0	, // Non-Breaking Space
    /* 0xa1 */ 0x060c	, // Arabic Comma
    /* 0xa2 */ 0x00a2	, // Cent Sign
    /* 0xa3 */ 0x00a3	, // Pound Sign
    /* 0xa4 */ 0x00a4	, // Currency Sign
    /* 0xa5 */ 0x00a5	, // Yen Sign
    /* 0xa6 */ 0x00a6	, // Broken Vertical Bar
    /* 0xa7 */ 0x00a7	, // Section Sign
    /* 0xa8 */ 0x00a8	, // Spacing Diaeresis
    /* 0xa9 */ 0x00a9	, // Copyright Sign
    /* 0xaa */ 0x06be	, // Arabic Letter Heh Doachashmee
    /* 0xab */ 0x00ab	, // Left Pointing Guillemet
    /* 0xac */ 0x00ac	, // Not Sign
    /* 0xad */ 0x00ad	, // Soft Hyphen
    /* 0xae */ 0x00ae	, // Registered Trade Mark Sign
    /* 0xaf */ 0x00af	, // Spacing Macron
    /* 0xb0 */ 0x00b0	, // Degree Sign
    /* 0xb1 */ 0x00b1	, // Plus-Or-Minus Sign
    /* 0xb2 */ 0x00b2	, // Superscript Digit Two
    /* 0xb3 */ 0x00b3	, // Superscript Digit Three
    /* 0xb4 */ 0x00b4	, // Spacing Acute
    /* 0xb5 */ 0x00b5	, // Micro Sign
    /* 0xb6 */ 0x00b6	, // Paragraph Sign
    /* 0xb7 */ 0x00b7	, // Middle Dot
    /* 0xb8 */ 0x00b8	, // Spacing Cedilla
    /* 0xb9 */ 0x00b9	, // Superscript Digit One
    /* 0xba */ 0x061b	, // Arabic Semicolon
    /* 0xbb */ 0x00bb	, // Right Pointing Guillemet
    /* 0xbc */ 0x00bc	, // Fraction One Quarter
    /* 0xbd */ 0x00bd	, // Fraction One Half
    /* 0xbe */ 0x00be	, // Fraction Three Quarters
    /* 0xbf */ 0x061f	, // Arabic Question Mark
    /* 0xc0 */ 0x06c1	, // Arabic Letter Heh Goal
    /* 0xc1 */ 0x0621	, // Arabic Letter Hamzah
    /* 0xc2 */ 0x0622	, // Arabic Letter Maddah On Alef
    /* 0xc3 */ 0x0623	, // Arabic Letter Hamzah On Alef
    /* 0xc4 */ 0x0624	, // Arabic Letter Hamzah On Waw
    /* 0xc5 */ 0x0625	, // Arabic Letter Hamzah Under Alef
    /* 0xc6 */ 0x0626	, // Arabic Letter Hamzah On Ya
    /* 0xc7 */ 0x0627	, // Arabic Letter Alef
    /* 0xc8 */ 0x0628	, // Arabic Letter Baa
    /* 0xc9 */ 0x0629	, // Arabic Letter Taa Marbutah
    /* 0xca */ 0x062a	, // Arabic Letter Taa
    /* 0xcb */ 0x062b	, // Arabic Letter Thaa
    /* 0xcc */ 0x062c	, // Arabic Letter Jeem
    /* 0xcd */ 0x062d	, // Arabic Letter Haa
    /* 0xce */ 0x062e	, // Arabic Letter Khaa
    /* 0xcf */ 0x062f	, // Arabic Letter Dal
    /* 0xd0 */ 0x0630	, // Arabic Letter Thal
    /* 0xd1 */ 0x0631	, // Arabic Letter Ra
    /* 0xd2 */ 0x0632	, // Arabic Letter Zain
    /* 0xd3 */ 0x0633	, // Arabic Letter Seen
    /* 0xd4 */ 0x0634	, // Arabic Letter Sheen
    /* 0xd5 */ 0x0635	, // Arabic Letter Sad
    /* 0xd6 */ 0x0636	, // Arabic Letter Dad
    /* 0xd7 */ 0x00d7	, // Multiplication Sign
    /* 0xd8 */ 0x0637	, // Arabic Letter Tah
    /* 0xd9 */ 0x0638	, // Arabic Letter Dhah
    /* 0xda */ 0x0639	, // Arabic Letter Ain
    /* 0xdb */ 0x063a	, // Arabic Letter Ghain
    /* 0xdc */ 0x0640	, // Arabic Tatweel
    /* 0xdd */ 0x0641	, // Arabic Letter Fa
    /* 0xde */ 0x0642	, // Arabic Letter Qaf
    /* 0xdf */ 0x0643	, // Arabic Letter Caf
    /* 0xe0 */ 0x00e0	, // Latin Small Letter A Grave
    /* 0xe1 */ 0x0644	, // Arabic Letter Lam
    /* 0xe2 */ 0x00e2	, // Latin Small Letter A Circumflex
    /* 0xe3 */ 0x0645	, // Arabic Letter Meem
    /* 0xe4 */ 0x0646	, // Arabic Letter Noon
    /* 0xe5 */ 0x0647	, // Arabic Letter Ha
    /* 0xe6 */ 0x0648	, // Arabic Letter Waw
    /* 0xe7 */ 0x00e7	, // Latin Small Letter C Cedilla
    /* 0xe8 */ 0x00e8	, // Latin Small Letter E Grave
    /* 0xe9 */ 0x00e9	, // Latin Small Letter E Acute
    /* 0xea */ 0x00ea	, // Latin Small Letter E Circumflex
    /* 0xeb */ 0x00eb	, // Latin Small Letter E Diaeresis
    /* 0xec */ 0x0649	, // Arabic Letter Alef Maqsurah
    /* 0xed */ 0x064a	, // Arabic Letter Ya
    /* 0xee */ 0x00ee	, // Latin Small Letter I Circumflex
    /* 0xef */ 0x00ef	, // Latin Small Letter I Diaeresis
    /* 0xf0 */ 0x064b	, // Arabic Fathatan
    /* 0xf1 */ 0x064c	, // Arabic Dammatan
    /* 0xf2 */ 0x064d	, // Arabic Kasratan
    /* 0xf3 */ 0x064e	, // Arabic Fathah
    /* 0xf4 */ 0x00f4	, // Latin Small Letter O Circumflex
    /* 0xf5 */ 0x064f	, // Arabic Dammah
    /* 0xf6 */ 0x0650	, // Arabic Kasrah
    /* 0xf7 */ 0x00f7	, // Division Sign
    /* 0xf8 */ 0x0651	, // Arabic Shaddah
    /* 0xf9 */ 0x00f9	, // Latin Small Letter U Grave
    /* 0xfa */ 0x0652	, // Arabic Sukun
    /* 0xfb */ 0x00fb	, // Latin Small Letter U Circumflex
    /* 0xfc */ 0x00fc	, // Latin Small Letter U Diaeresis
    /* 0xfd */ 0x200e	, // Left-To-Right Mark
    /* 0xfe */ 0x200f	, // Right-To-Left Mark
    /* 0xff */ 0x06d2	 // Arabic Letter Yeh Barree
  };

  // 1257: Baltic - ANSI
  // Verified using Windows 10 Dec 2017
  static const ON__UINT32 code_page_1257_0x80_to_0xFF[128] =
  {
    /* 80 */ 0x20ac, // Euro Sign
    /* 81 */ 0x0081,
    /* 82 */ 0x201a, // Low Single Comma Quotation Mark
    /* 83 */ 0x0083,
    /* 84 */ 0x201e, // Low Double Comma Quotation Mark
    /* 85 */ 0x2026, // Horizontal Ellipsis
    /* 86 */ 0x2020, // Dagger
    /* 87 */ 0x2021, // Double Dagger
    /* 88 */ 0x0088,
    /* 89 */ 0x2030, // Per Mille Sign
    /* 8a */ 0x008a,
    /* 8b */ 0x2039, // Left Pointing Single Guillement
    /* 8c */ 0x008c,
    /* 8d */ 0x00a8, // Diaeresis
    /* 8e */ 0x02c7, // CARON
    /* 8f */ 0x00b8, // Cedilla
    /* 90 */ 0x0090,
    /* 91 */ 0x2018, // Left Single Quotation Mark
    /* 92 */ 0x2019, // Right Single Quotation Mark
    /* 93 */ 0x201c, // Left Double Quotation Mark
    /* 94 */ 0x201d, // Right Double Quotation Mark
    /* 95 */ 0x2022, // Bullet
    /* 96 */ 0x2013, // En Dash
    /* 97 */ 0x2014, // Em Dash
    /* 98 */ 0x0098,
    /* 99 */ 0x2122, // Trade Mark Sign
    /* 9a */ 0x009a,
    /* 9b */ 0x203a, // Right Pointing Single Guillement
    /* 9c */ 0x009c,
    /* 9d */ 0x00af, // Macron
    /* 9e */ 0x02db, // Ogonek
    /* 9f */ 0x009f,
    /* a0 */ 0x00a0, // No-Break Space
    /* a1 */ 0xf8fc,
    /* a2 */ 0x00a2, // Cent Sign
    /* a3 */ 0x00a3, // Pound Sign
    /* a4 */ 0x00a4, // Currency Sign
    /* a5 */ 0xf8fd, // Undefined -> EUDC
    /* a6 */ 0x00a6, // Broken Bar
    /* a7 */ 0x00a7, // Section Sign
    /* a8 */ 0x00d8, // O Stroke
    /* a9 */ 0x00a9, // Copyright Sign
    /* aa */ 0x0156, // R Cedilla
    /* ab */ 0x00ab, // Left Pointing Guillement
    /* ac */ 0x00ac, // Not Sign
    /* ad */ 0x00ad, // Soft Hyphen
    /* ae */ 0x00ae, // Registered Sign
    /* af */ 0x00c6, // AE
    /* b0 */ 0x00b0, // Degree Sign
    /* b1 */ 0x00b1, // Plus-Minus Sign
    /* b2 */ 0x00b2, // Superscript 2
    /* b3 */ 0x00b3, // Superscript 3
    /* b4 */ 0x00b4, // Acute
    /* b5 */ 0x00b5, // Micro Sign
    /* b6 */ 0x00b6, // Pilcrow Sign
    /* b7 */ 0x00b7, // Middle Dot
    /* b8 */ 0x00f8, // o Stroke
    /* b9 */ 0x00b9, // Superscript 1
    /* ba */ 0x0157, // r Cedilla
    /* bb */ 0x00bb, // Right Pointing Guillement
    /* bc */ 0x00bc, // Fraction 1/4
    /* bd */ 0x00bd, // Fraction 1/2
    /* be */ 0x00be, // Fraction 3/4
    /* bf */ 0x00e6, // ae
    /* c0 */ 0x0104, // A Ogonek
    /* c1 */ 0x012e, // I Ogonek
    /* c2 */ 0x0100, // A Macron
    /* c3 */ 0x0106, // C Acute
    /* c4 */ 0x00c4, // A Diaeresis
    /* c5 */ 0x00c5, // A Ring Above
    /* c6 */ 0x0118, // E Ogonek
    /* c7 */ 0x0112, // E Macron
    /* c8 */ 0x010c, // C Hacek
    /* c9 */ 0x00c9, // E Acute
    /* ca */ 0x0179, // Z Acute
    /* cb */ 0x0116, // E Dot Above
    /* cc */ 0x0122, // G Cedilla
    /* cd */ 0x0136, // K Cedilla
    /* ce */ 0x012a, // I Macron
    /* cf */ 0x013b, // L Cedilla
    /* d0 */ 0x0160, // S Hacek
    /* d1 */ 0x0143, // N Acute
    /* d2 */ 0x0145, // N Cedilla
    /* d3 */ 0x00d3, // O Acute
    /* d4 */ 0x014c, // O Macron
    /* d5 */ 0x00d5, // O Tilde
    /* d6 */ 0x00d6, // O Diaeresis
    /* d7 */ 0x00d7, // Multiplication Sign
    /* d8 */ 0x0172, // U Ogonek
    /* d9 */ 0x0141, // L Stroke
    /* da */ 0x015a, // S Acute
    /* db */ 0x016a, // U Macron
    /* dc */ 0x00dc, // U Diaeresis
    /* dd */ 0x017b, // Z Dot Above
    /* de */ 0x017d, // Z Hacek
    /* df */ 0x00df, // Sharp ss
    /* e0 */ 0x0105, // a Ogonek
    /* e1 */ 0x012f, // i Ogonek
    /* e2 */ 0x0101, // a Macron
    /* e3 */ 0x0107, // c Acute
    /* e4 */ 0x00e4, // a Diaeresis
    /* e5 */ 0x00e5, // a Ring Above
    /* e6 */ 0x0119, // e Ogonek
    /* e7 */ 0x0113, // e Macron
    /* e8 */ 0x010d, // c Hacek
    /* e9 */ 0x00e9, // e Acute
    /* ea */ 0x017a, // z Acute
    /* eb */ 0x0117, // e Dot Above
    /* ec */ 0x0123, // g Cedilla
    /* ed */ 0x0137, // k Cedilla
    /* ee */ 0x012b, // i Macron
    /* ef */ 0x013c, // l Cedilla
    /* f0 */ 0x0161, // s Hacek
    /* f1 */ 0x0144, // n Acute
    /* f2 */ 0x0146, // n Cedilla
    /* f3 */ 0x00f3, // o Acute
    /* f4 */ 0x014d, // o Macron
    /* f5 */ 0x00f5, // o Tilde
    /* f6 */ 0x00f6, // o Diaeresis
    /* f7 */ 0x00f7, // Division Sign
    /* f8 */ 0x0173, // u Ogonek
    /* f9 */ 0x0142, // l Stroke
    /* fa */ 0x015b, // s Acute
    /* fb */ 0x016b, // u Macron
    /* fc */ 0x00fc, // u Diaeresis
    /* fd */ 0x017c, // z Dot Above
    /* fe */ 0x017e, // z Hacek
    /* ff */ 0x02d9  // Dot Above
  };

  // 1258: Viet Nam - ANSI
  // Verified using Windows 10 Dec 2017
  static const ON__UINT32 code_page_1258_0x80_to_0xFF[128] =
  {
    /* 0x80 */ 0x20ac	, // Euro Sign
    /* 0x81 */ 0x0081	, // Undefined -> Control
    /* 0x82 */ 0x201a	, // Single Low-9 Quotation Mark
    /* 0x83 */ 0x0192	, // Latin Small Letter F With Hook
    /* 0x84 */ 0x201e	, // Double Low-9 Quotation Mark
    /* 0x85 */ 0x2026	, // Horizontal Ellipsis
    /* 0x86 */ 0x2020	, // Dagger
    /* 0x87 */ 0x2021	, // Double Dagger
    /* 0x88 */ 0x02c6	, // Modifier Letter Circumflex Accent
    /* 0x89 */ 0x2030	, // Per Mille Sign
    /* 0x8a */ 0x008a	, // Undefined -> Control
    /* 0x8b */ 0x2039	, // Single Left-Pointing Angle Quotation Mark
    /* 0x8c */ 0x0152	, // Latin Capital Ligature Oe
    /* 0x8d */ 0x008d	, // Undefined -> Control
    /* 0x8e */ 0x008e	, // Undefined -> Control
    /* 0x8f */ 0x008f	, // Undefined -> Control
    /* 0x90 */ 0x0090	, // Undefined -> Control
    /* 0x91 */ 0x2018	, // Left Single Quotation Mark
    /* 0x92 */ 0x2019	, // Right Single Quotation Mark
    /* 0x93 */ 0x201c	, // Left Double Quotation Mark
    /* 0x94 */ 0x201d	, // Right Double Quotation Mark
    /* 0x95 */ 0x2022	, // Bullet
    /* 0x96 */ 0x2013	, // En Dash
    /* 0x97 */ 0x2014	, // Em Dash
    /* 0x98 */ 0x02dc	, // Small Tilde
    /* 0x99 */ 0x2122	, // Trade Mark Sign
    /* 0x9a */ 0x009a	, // Undefined -> Control
    /* 0x9b */ 0x203a	, // Single Right-Pointing Angle Quotation Mark
    /* 0x9c */ 0x0153	, // Latin Small Ligature Oe
    /* 0x9d */ 0x009d	, // Undefined -> Control
    /* 0x9e */ 0x009e	, // Undefined -> Control
    /* 0x9f */ 0x0178	, // Latin Capital Letter Y With Diaeresis
    /* 0xa0 */ 0x00a0	, // No-Break Space
    /* 0xa1 */ 0x00a1	, // Inverted Exclamation Mark
    /* 0xa2 */ 0x00a2	, // Cent Sign
    /* 0xa3 */ 0x00a3	, // Pound Sign
    /* 0xa4 */ 0x00a4	, // Currency Sign
    /* 0xa5 */ 0x00a5	, // Yen Sign
    /* 0xa6 */ 0x00a6	, // Broken Bar
    /* 0xa7 */ 0x00a7	, // Section Sign
    /* 0xa8 */ 0x00a8	, // Diaeresis
    /* 0xa9 */ 0x00a9	, // Copyright Sign
    /* 0xaa */ 0x00aa	, // Feminine Ordinal Indicator
    /* 0xab */ 0x00ab	, // Left-Pointing Double Angle Quotation Mark
    /* 0xac */ 0x00ac	, // Not Sign
    /* 0xad */ 0x00ad	, // Soft Hyphen
    /* 0xae */ 0x00ae	, // Registered Sign
    /* 0xaf */ 0x00af	, // Macron
    /* 0xb0 */ 0x00b0	, // Degree Sign
    /* 0xb1 */ 0x00b1	, // Plus-Minus Sign
    /* 0xb2 */ 0x00b2	, // Superscript Two
    /* 0xb3 */ 0x00b3	, // Superscript Three
    /* 0xb4 */ 0x00b4	, // Acute Accent
    /* 0xb5 */ 0x00b5	, // Micro Sign
    /* 0xb6 */ 0x00b6	, // Pilcrow Sign
    /* 0xb7 */ 0x00b7	, // Middle Dot
    /* 0xb8 */ 0x00b8	, // Cedilla
    /* 0xb9 */ 0x00b9	, // Superscript One
    /* 0xba */ 0x00ba	, // Masculine Ordinal Indicator
    /* 0xbb */ 0x00bb	, // Right-Pointing Double Angle Quotation Mark
    /* 0xbc */ 0x00bc	, // Vulgar Fraction One Quarter
    /* 0xbd */ 0x00bd	, // Vulgar Fraction One Half
    /* 0xbe */ 0x00be	, // Vulgar Fraction Three Quarters
    /* 0xbf */ 0x00bf	, // Inverted Question Mark
    /* 0xc0 */ 0x00c0	, // Latin Capital Letter A With Grave
    /* 0xc1 */ 0x00c1	, // Latin Capital Letter A With Acute
    /* 0xc2 */ 0x00c2	, // Latin Capital Letter A With Circumflex
    /* 0xc3 */ 0x0102	, // Latin Capital Letter A With Breve
    /* 0xc4 */ 0x00c4	, // Latin Capital Letter A With Diaeresis
    /* 0xc5 */ 0x00c5	, // Latin Capital Letter A With Ring Above
    /* 0xc6 */ 0x00c6	, // Latin Capital Ligature Ae
    /* 0xc7 */ 0x00c7	, // Latin Capital Letter C With Cedilla
    /* 0xc8 */ 0x00c8	, // Latin Capital Letter E With Grave
    /* 0xc9 */ 0x00c9	, // Latin Capital Letter E With Acute
    /* 0xca */ 0x00ca	, // Latin Capital Letter E With Circumflex
    /* 0xcb */ 0x00cb	, // Latin Capital Letter E With Diaeresis
    /* 0xcc */ 0x0300	, // Combining Grave Accent
    /* 0xcd */ 0x00cd	, // Latin Capital Letter I With Acute
    /* 0xce */ 0x00ce	, // Latin Capital Letter I With Circumflex
    /* 0xcf */ 0x00cf	, // Latin Capital Letter I With Diaeresis
    /* 0xd0 */ 0x0110	, // Latin Capital Letter D Bar
    /* 0xd1 */ 0x00d1	, // Latin Capital Letter N With Tilde
    /* 0xd2 */ 0x0309	, // Combining Hook Above
    /* 0xd3 */ 0x00d3	, // Latin Capital Letter O With Acute
    /* 0xd4 */ 0x00d4	, // Latin Capital Letter O With Circumflex
    /* 0xd5 */ 0x01a0	, // Latin Capital Letter O With Horn
    /* 0xd6 */ 0x00d6	, // Latin Capital Letter O With Diaeresis
    /* 0xd7 */ 0x00d7	, // Multiplication Sign
    /* 0xd8 */ 0x00d8	, // Latin Capital Letter O With Stroke
    /* 0xd9 */ 0x00d9	, // Latin Capital Letter U With Grave
    /* 0xda */ 0x00da	, // Latin Capital Letter U With Acute
    /* 0xdb */ 0x00db	, // Latin Capital Letter U With Circumflex
    /* 0xdc */ 0x00dc	, // Latin Capital Letter U With Diaeresis
    /* 0xdd */ 0x01af	, // Latin Capital Letter U With Horn
    /* 0xde */ 0x0303	, // Combining Tilde
    /* 0xdf */ 0x00df	, // Latin Small Letter Sharp S
    /* 0xe0 */ 0x00e0	, // Latin Small Letter A With Grave
    /* 0xe1 */ 0x00e1	, // Latin Small Letter A With Acute
    /* 0xe2 */ 0x00e2	, // Latin Small Letter A With Circumflex
    /* 0xe3 */ 0x0103	, // Latin Small Letter A With Breve
    /* 0xe4 */ 0x00e4	, // Latin Small Letter A With Diaeresis
    /* 0xe5 */ 0x00e5	, // Latin Small Letter A With Ring Above
    /* 0xe6 */ 0x00e6	, // Latin Small Ligature Ae
    /* 0xe7 */ 0x00e7	, // Latin Small Letter C With Cedilla
    /* 0xe8 */ 0x00e8	, // Latin Small Letter E With Grave
    /* 0xe9 */ 0x00e9	, // Latin Small Letter E With Acute
    /* 0xea */ 0x00ea	, // Latin Small Letter E With Circumflex
    /* 0xeb */ 0x00eb	, // Latin Small Letter E With Diaeresis
    /* 0xec */ 0x0301	, // Combining Acute Accent
    /* 0xed */ 0x00ed	, // Latin Small Letter I With Acute
    /* 0xee */ 0x00ee	, // Latin Small Letter I With Circumflex
    /* 0xef */ 0x00ef	, // Latin Small Letter I With Diaeresis
    /* 0xf0 */ 0x0111	, // Latin Small Letter D Bar
    /* 0xf1 */ 0x00f1	, // Latin Small Letter N With Tilde
    /* 0xf2 */ 0x0323	, // Combining Dot Below
    /* 0xf3 */ 0x00f3	, // Latin Small Letter O With Acute
    /* 0xf4 */ 0x00f4	, // Latin Small Letter O With Circumflex
    /* 0xf5 */ 0x01a1	, // Latin Small Letter O With Horn
    /* 0xf6 */ 0x00f6	, // Latin Small Letter O With Diaeresis
    /* 0xf7 */ 0x00f7	, // Division Sign
    /* 0xf8 */ 0x00f8	, // Latin Small Letter O With Stroke
    /* 0xf9 */ 0x00f9	, // Latin Small Letter U With Grave
    /* 0xfa */ 0x00fa	, // Latin Small Letter U With Acute
    /* 0xfb */ 0x00fb	, // Latin Small Letter U With Circumflex
    /* 0xfc */ 0x00fc	, // Latin Small Letter U With Diaeresis
    /* 0xfd */ 0x01b0	, // Latin Small Letter U With Horn
    /* 0xfe */ 0x20ab	, // Dong Sign
    /* 0xff */ 0x00ff	 // Latin Small Letter Y With Diaeresis
  };
  
  const ON__UINT32* a;
  switch (code_page)
  {
  case 874:  // subset of 1162
  case 1161: // subset of 1162 except 0xDE maps to euro sign is in 
  case 1162:
    a = code_page_874_0x80_to_0xFF; 
    break;
  case 1250: 
    a = code_page_1250_0x80_to_0xFF;
    break;
  case 1251: 
    a = code_page_1251_0x80_to_0xFF;
    break;
  case 1252: 
    a = code_page_1252_0x80_to_0xFF;
    break;
  case 1253: 
    a = code_page_1253_0x80_to_0xFF;
    break;
  case 1254: 
    a = code_page_1254_0x80_to_0xFF;
    break;
  case 1255: 
    a = code_page_1255_0x80_to_0xFF;
    break;
  case 1256: 
    a = code_page_1256_0x80_to_0xFF;
    break;
  case 1257: 
    a = code_page_1257_0x80_to_0xFF;
    break;
  case 1258: 
    a = code_page_1258_0x80_to_0xFF;
    break;
  case 10000: 
    a = code_page_10000_0x80_to_0xFF;
    break;
  default:
    a = nullptr;
    break;
  }
  return a;
};

class CodePageEncodingUnicodeCodePoint
{
public:
  CodePageEncodingUnicodeCodePoint() = default;
  ~CodePageEncodingUnicodeCodePoint() = default;
  CodePageEncodingUnicodeCodePoint(const CodePageEncodingUnicodeCodePoint&) = default;
  CodePageEncodingUnicodeCodePoint& operator=(const CodePageEncodingUnicodeCodePoint&) = default;

  static int CompareUnicodeCodePoint(
    const void* lhs,
    const void* rhs
  );

public:
  ON__UINT32 m_cp_encoding = 0;
  ON__UINT32 m_unicode_code_point = 0;
};

int CodePageEncodingUnicodeCodePoint::CompareUnicodeCodePoint(
  const void* lhs,
  const void* rhs
)
{
  const ON__UINT32 lhs_code_point = (nullptr != lhs) ? ((const class CodePageEncodingUnicodeCodePoint*)lhs)->m_unicode_code_point : 0xFFFFFFFF;
  const ON__UINT32 rhs_code_point = (nullptr != rhs) ? ((const class CodePageEncodingUnicodeCodePoint*)rhs)->m_unicode_code_point : 0xFFFFFFFF;
  if (lhs_code_point < rhs_code_point)
    return -1;
  if (lhs_code_point > rhs_code_point)
    return 1;
  return 0;
}

class InternalUnicodeToCodePage
{
public:
  ~InternalUnicodeToCodePage()
  {
    if (nullptr != m_unicode_to_cp)
    {
      onfree(m_unicode_to_cp);
    }
  }

  static InternalUnicodeToCodePage* Create(
    ON__UINT32 code_page
  );

  ON__UINT32 CodePage() const
  {
    return m_code_page;
  }

  ON__UINT32 MapUnicodeToWindowsSingleByteCodePage(
    ON__UINT32 unicode_code_point
  ) const
  {
    for (;;)
    {
      if (
        nullptr == m_unicode_to_cp
        || m_unicode_to_cp_count <= 0
        || unicode_code_point < m_unicode_to_cp[0].m_unicode_code_point
        || unicode_code_point > m_unicode_to_cp[m_unicode_to_cp_count - 1].m_unicode_code_point
        )
      {
        break;
      }
      CodePageEncodingUnicodeCodePoint key;
      key.m_unicode_code_point = unicode_code_point;
      const CodePageEncodingUnicodeCodePoint* e = (const CodePageEncodingUnicodeCodePoint*)bsearch(&key, m_unicode_to_cp, m_unicode_to_cp_count, sizeof(key), CodePageEncodingUnicodeCodePoint::CompareUnicodeCodePoint);
      if (nullptr == e)
        break;
      return e->m_cp_encoding;
    }
    return 0xFFFFFFFF;
  }

private:
  const ON__UINT32 m_code_page = 0;
  const ON__UINT32 m_unicode_to_cp_count = 0;
  CodePageEncodingUnicodeCodePoint* m_unicode_to_cp = nullptr;

private:
  InternalUnicodeToCodePage(
    ON__UINT32 code_page,
    const ON__UINT32 unicode_to_cp_count,
    CodePageEncodingUnicodeCodePoint* unicode_to_cp
  )
    : m_code_page(code_page)
    , m_unicode_to_cp_count(unicode_to_cp_count)
    , m_unicode_to_cp(unicode_to_cp)
  {};
  InternalUnicodeToCodePage() = delete;
  InternalUnicodeToCodePage(const InternalUnicodeToCodePage&) = delete;
  InternalUnicodeToCodePage& operator=(const InternalUnicodeToCodePage&) = delete;
};

InternalUnicodeToCodePage* InternalUnicodeToCodePage::Create(
  ON__UINT32 code_page
)
{
  for (;;)
  {
    const ON__UINT32* cp_to_unicode = ON_MSSBCP_0x80_0xFF_Unicode(code_page);
    if (nullptr == cp_to_unicode)
      break;
    CodePageEncodingUnicodeCodePoint* a = (CodePageEncodingUnicodeCodePoint*)onmalloc(128 * sizeof(a[0]));
    ON__UINT32 a_count = 0;
    for (ON__UINT32 i = 0; i < 128; i++)
    {
      if (cp_to_unicode[i] < 0x80 )
        continue;
      if (ON_UnicodeCodePoint::ON_ReplacementCharacter == cp_to_unicode[i])
        continue;
      if (0 == ON_IsValidUnicodeCodePoint(cp_to_unicode[i]))
        continue;
      a[a_count].m_cp_encoding = i + 0x80;
      a[a_count].m_unicode_code_point = cp_to_unicode[i];
      a_count++;
    }
    if (0 == a_count)
    {
      onfree(a);
      break;
    }
    ON_qsort(a, a_count, sizeof(a[0]), CodePageEncodingUnicodeCodePoint::CompareUnicodeCodePoint);
    return new InternalUnicodeToCodePage(code_page,a_count,a);
  }
  return nullptr;
}

ON__UINT32 ON_MapUnicodeToMSSBCP(
  ON__UINT32 code_page,
  ON__UINT32 unicode_code_point
)
{
  if (unicode_code_point < 0x80)
    return unicode_code_point;

  for (;;)
  {
    if (ON_UnicodeCodePoint::ON_ReplacementCharacter == unicode_code_point )
      break;

    if (false == ON_IsValidUnicodeCodePoint(unicode_code_point))
      break;

    const InternalUnicodeToCodePage* utocp;
    switch (code_page)
    {
    case 874:
    case 1161:
    case 1162:
      {
        static const InternalUnicodeToCodePage* utocp1162 = nullptr;
        if (nullptr == utocp1162)
          utocp1162 = InternalUnicodeToCodePage::Create(1162);
        utocp = utocp1162;
        break;
      }      

    case 1250:
      {
        static const InternalUnicodeToCodePage* utocp_LOCAL = nullptr;
        if (nullptr == utocp_LOCAL)
          utocp_LOCAL = InternalUnicodeToCodePage::Create(code_page);
        utocp = utocp_LOCAL;
        break;
      }      

    case 1251:
      {
        static const InternalUnicodeToCodePage* utocp_LOCAL = nullptr;
        if (nullptr == utocp_LOCAL)
          utocp_LOCAL = InternalUnicodeToCodePage::Create(code_page);
        utocp = utocp_LOCAL;
        break;
      }      

    case 1252: // Windows Latin I
      {
        static const InternalUnicodeToCodePage* utocp1252 = nullptr;
        if (nullptr == utocp1252)
          utocp1252 = InternalUnicodeToCodePage::Create(code_page);
        utocp = utocp1252;
        break;
      }      

    case 1253:
      {
        static const InternalUnicodeToCodePage* utocp_LOCAL = nullptr;
        if (nullptr == utocp_LOCAL)
          utocp_LOCAL = InternalUnicodeToCodePage::Create(code_page);
        utocp = utocp_LOCAL;
        break;
      }      

    case 1254:
      {
        static const InternalUnicodeToCodePage* utocp_LOCAL = nullptr;
        if (nullptr == utocp_LOCAL)
          utocp_LOCAL = InternalUnicodeToCodePage::Create(code_page);
        utocp = utocp_LOCAL;
        break;
      }      

    case 1255:
      {
        static const InternalUnicodeToCodePage* utocp_LOCAL = nullptr;
        if (nullptr == utocp_LOCAL)
          utocp_LOCAL = InternalUnicodeToCodePage::Create(code_page);
        utocp = utocp_LOCAL;
        break;
      }      

    case 1256:
      {
        static const InternalUnicodeToCodePage* utocp_LOCAL = nullptr;
        if (nullptr == utocp_LOCAL)
          utocp_LOCAL = InternalUnicodeToCodePage::Create(code_page);
        utocp = utocp_LOCAL;
        break;
      }      

    case 1257:
      {
        static const InternalUnicodeToCodePage* utocp_LOCAL = nullptr;
        if (nullptr == utocp_LOCAL)
          utocp_LOCAL = InternalUnicodeToCodePage::Create(code_page);
        utocp = utocp_LOCAL;
        break;
      }      

    case 1258:
      {
        static const InternalUnicodeToCodePage* utocp_LOCAL = nullptr;
        if (nullptr == utocp_LOCAL)
          utocp_LOCAL = InternalUnicodeToCodePage::Create(code_page);
        utocp = utocp_LOCAL;
        break;
      }    

    case 10000: // Apple Roman
      {
        static const InternalUnicodeToCodePage* utocp10000 = nullptr;
        if (nullptr == utocp10000)
          utocp10000 = InternalUnicodeToCodePage::Create(code_page);
        utocp = utocp10000;
        break;
      }      

    default: // uncommon or not supported
      // add some type of binary search for the appropriate InternalUnicodeToCodePage
      // if we ever end up adding "uncommon" support.
      utocp = nullptr;
      break;
    }

    if (nullptr == utocp)
      break;

    return utocp->MapUnicodeToWindowsSingleByteCodePage(unicode_code_point);
  }


  return 0xFFFFFFFF;
}

ON__UINT32 ON_MapMSSBCPToUnicode(
  ON__UINT32 code_page,
  ON__UINT32 code_page_single_byte_encoding
)
{
  ON__UINT32 code_point;
  if (code_page_single_byte_encoding < 0x0080)
  {
    // Values in the range 0x00 to 0x7F have identity mapping to UNICODE code point.
    code_point = code_page_single_byte_encoding;
  }
  else
  {
    const ON__UINT32* a
      = (code_page_single_byte_encoding <= 0xFF)
      ? ON_MSSBCP_0x80_0xFF_Unicode(code_page)
      : nullptr;
    code_point
      = (nullptr != a)
      ? a[code_page_single_byte_encoding - 0x80]
      : ON_UnicodeCodePoint::ON_ReplacementCharacter;
  }
  return code_point;
}


ON__UINT32 ON_Test_MSSBCP(
  const ON__UINT32 code_page,
  const ON__UINT32 char_encoding,
  bool bWindowsAPITest,
  ON_TextLog& text_log
)
{
  int rc = 0;
  if (char_encoding > 0xFF)
  {
    // invalid single byte encoding
    ON_ERROR("Invalid char_encoding parameter.");
    return 0;
  }

  const ON__UINT32 unicode_code_point = ON_MapMSSBCPToUnicode(code_page, char_encoding);
  if (ON_UnicodeCodePoint::ON_ReplacementCharacter == unicode_code_point)
  {
    rc = 2;
  }
  else
  {
    const ON__UINT32 c = ON_MapUnicodeToMSSBCP(code_page, unicode_code_point);
    if (c == char_encoding)
    {
      rc = 1;
    }
    else
    {
      rc = 0;
      text_log.Print("Code page %u char %02x U+%04X ON_MapUnicodeToMSSBCP() = %02x\n",
            code_page,
            char_encoding,
            unicode_code_point,
            c
          );
    }
  }

#if defined(ON_RUNTIME_WIN)
  while (bWindowsAPITest)
  {
    const char mbcs[2] = { (char)char_encoding,0 };
    wchar_t w[16] = {};
    ON__UINT32 ucp = ON_UnicodeCodePoint::ON_InvalidCodePoint;
    const int w_count = ::MultiByteToWideChar(code_page, 0, mbcs, 1, w, 15);
    if (w_count <= 0)
    {
      if (IsValidCodePage(code_page))
      {
        text_log.Print("Code page %u char %02x U+%04X MultiByteToWideChar() failed.\n",
          code_page,
          char_encoding,
          unicode_code_point
        );
        rc = 0;
      }
      break;
    }

    struct ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::FailOnErrors;
    const int decode_count = ON_DecodeWideChar(w, w_count, &e, &ucp);
    if (unicode_code_point != ucp || decode_count != w_count || 0 != e.m_error_status)
    {
      text_log.Print("Code page %u char %02x U+%04X MultiByteToWideChar() = U+%04X.\n",
        code_page,
        char_encoding,
        unicode_code_point,
        ucp
      );
      rc = 0;
      break;
    }

    char mbcs2[16] = {};
    BOOL bUsedDefaultChar = 0;
    const char mbcs2_default[2] = { 0,0 };
    const int mbcs2_count = WideCharToMultiByte(code_page, 0, w, w_count, mbcs2, 15, mbcs2_default, &bUsedDefaultChar);
    if (mbcs2_count <= 0)
    {
      text_log.Print("Code page %u char %02x U+%04X WideCharToMultiByte() failed.\n",
        code_page,
        char_encoding,
        unicode_code_point
      );
      rc = 0;
      break;
    }

    if (1 != mbcs2_count || mbcs[0] != mbcs2[0] || bUsedDefaultChar)
    {
      text_log.Print("Code page %u char %02x U+%04X WideCharToMultiByte() = {",
        code_page,
        char_encoding,
        unicode_code_point
      );
      for (int i = 0; i < mbcs2_count; i++)
      {
        if ( i > 0)
          text_log.Print(", %02x", mbcs2[i]);
        else
          text_log.Print(" %02x", mbcs2[i]);
      }
      text_log.Print("}\n");
      rc = 0;
      break;
    }

    // successful test
    break;
  }
#endif

  return rc;
}
static bool ON_InternalIsDoubleByteCodePage(
  const ON__UINT32 code_page
)
{
  bool rc;
  switch (code_page)
  {
  case 932: // ANSI/OEM Japanese; Japanese (Shift-JIS)
  case 936: // ANSI/OEM Simplified Chinese (PRC, Singapore); Chinese Simplified (GB2312)
  case 949: // ANSI/OEM Korean (Unified Hangul Code)
  case 950: // ANSI/OEM Traditional Chinese (Taiwan; Hong Kong SAR, PRC); Chinese Traditional (Big5)
    rc = true;
    break;
  default:
    rc = false;
    break;
  }
  return rc;
}

bool ON_Test_MSSBCP(
  const ON__UINT32 code_page,
  bool bWindowsAPITest,
  ON_TextLog& text_log
)
{
  unsigned int pass_count = 0;
  unsigned int fail_count = 0;
  unsigned int not_mapped_count = 0;
#if defined(ON_RUNTIME_WIN)
  if (bWindowsAPITest)
  {
    if (0 == ::IsValidCodePage(code_page))
    {
      text_log.Print("Code page %u not installed on this computer.\n", code_page);
      bWindowsAPITest = false;
    }
  }
#else
  bWindowsAPITest = false;
#endif
  const ON__UINT32 char_encoding_max
    = ON_InternalIsDoubleByteCodePage(code_page)
    ? 0x7F  // veriy identity map for values 0x00 to 0x7E
    : 0xFF;
  for (ON__UINT32 char_encoding = 0; char_encoding <= char_encoding_max; char_encoding++)
  {
    switch (ON_Test_MSSBCP(code_page, char_encoding, bWindowsAPITest, text_log))
    {
    case 0:
      fail_count++;
      break;
    case 1:
      pass_count++;
      break;
    case 2:
      not_mapped_count++;
      break;
    }
  }

  text_log.Print(
    "Tested %u single byte encodings. %u passed, %u failed (%u not mapped).\n",
    pass_count+fail_count+not_mapped_count,
    pass_count+not_mapped_count,
    fail_count,
    not_mapped_count
  );
  

  return (0 == fail_count);
}

bool ON_Test_MSSBCP(
  bool bWindowsAPITest,
  ON_TextLog& text_log
)
{
  const ON__UINT32 code_pages[] =
  {
  // double byte encodings - testing ANSI/OEM mapping portion 0x00 to 0x7F.
  932, // ANSI/OEM Japanese; Japanese (Shift-JIS)
  936, // ANSI/OEM Simplified Chinese (PRC, Singapore); Chinese Simplified (GB2312)
  949, // ANSI/OEM Korean (Unified Hangul Code)
  950, // ANSI/OEM Traditional Chinese (Taiwan; Hong Kong SAR, PRC); Chinese Traditional (Big5)
  //
  // single byte encodings below
  //
  874,
  1161,
  1162,
  1250,
  1251,
  1252,
  1253,
  1254,
  1255,
  1256,
  1257,
  1258,
  10000,
  //
  // list terminator below
  //
  0xFFFFFFFF
  };

  unsigned int pass_count = 0;
  unsigned int fail_count = 0;
  for (size_t i = 0; 0xFFFFFFFF != code_pages[i]; i++)
  {
    const ON__UINT32 code_page = code_pages[i];
    text_log.Print(
      "Testing code page %u:\n",
      code_page
    );
    text_log.PushIndent();
    if (ON_Test_MSSBCP(code_page,bWindowsAPITest,text_log))
    {
      pass_count++;
      text_log.Print("Passed.\n");
    }
    else
    {
      text_log.Print("FAILED.\n");
      fail_count++;
    }
    text_log.PopIndent();
  }

  text_log.PrintNewLine();
  text_log.Print(
    "Tested %u code pages. % u passed. % u failed.\n", 
    pass_count + fail_count, 
    pass_count,
    fail_count
  );

  return (0 == fail_count);
}


bool ON_Test_PrintPlatformMSSBCPToUnicodeTable(
  const ON__UINT32 code_page,
  ON__UINT32 char_encoding0,
  ON__UINT32 char_encoding1,
  ON_TextLog& text_log
)
{
#if defined(ON_RUNTIME_WIN)
  if (false == IsValidCodePage(code_page))
  {
    text_log.Print(
      "// Microsoft code page %u is not installed.\n",
      code_page
    );
    return false;
  }

  if (char_encoding1 > 0xFF)
    char_encoding1 = 0xFF;
  if (char_encoding0 > char_encoding1)
    return false;

  text_log.Print(
    "// Microsoft code page %u encoding %02x to %02x Unicode code points\n",
    code_page,
    char_encoding0,
    char_encoding1
    );

  ON__UINT32 error_count = 0;
  text_log.Print(
    "const ON__UINT32 mssb_code_page_%u_0x%02x_0x%02x_unicode[%u] =\n",
    code_page,
    char_encoding0,
    char_encoding1, 
    char_encoding1 - char_encoding0 + 1
  );
  text_log.Print("{\n");
  text_log.PushIndent();
  for (ON__UINT32 char_encoding = char_encoding0; char_encoding <= char_encoding1; char_encoding++)
  {
    ON__UINT32 unicode_code_point = ON_UnicodeCodePoint::ON_InvalidCodePoint;
    for (;;)
    {
      const char mbcs[2] = { (char)char_encoding,0 };
      wchar_t w[16] = {};
      const int w_count = ::MultiByteToWideChar(code_page, 0, mbcs, 1, w, 15);
      if (w_count <= 0)
        break;

      struct ON_UnicodeErrorParameters e = ON_UnicodeErrorParameters::FailOnErrors;
      ON__UINT32 u = ON_UnicodeCodePoint::ON_InvalidCodePoint;
      const int decode_count = ON_DecodeWideChar(w, w_count, &e, &u);
      if (false == ON_IsValidUnicodeCodePoint(u))
        break;
      if (decode_count != w_count)
        break;
      if (0 != e.m_error_status)
        break;
      unicode_code_point = u;
      break;
    }
    if (ON_UnicodeCodePoint::ON_InvalidCodePoint == unicode_code_point)
    {
      text_log.Print("#error 0x%02x failed to map to a valid Unicode code point.\n", char_encoding);
      error_count++;
    }
    else
    {
      text_log.Print("0x%04X", unicode_code_point);
      if (char_encoding < char_encoding1)
        text_log.Print(",");
      else
        text_log.Print(" ");
      text_log.Print(" // 0x%02x -> U+%04X\n", char_encoding, unicode_code_point);
    }
  }
  text_log.PopIndent();
  text_log.Print("};\n");

  return (0 == error_count);
#else
  ON_ERROR("Platform not supported.");
  return false;
#endif
}

