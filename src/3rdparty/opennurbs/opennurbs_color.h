/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2007 Robert McNeel & Associates. All rights reserved.
// Rhinoceros is a registered trademark of Robert McNeel & Assoicates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////
*/

#if !defined(OPENNURBS_COLOR_INC_)
#define OPENNURBS_COLOR_INC_

///////////////////////////////////////////////////////////////////////////////
//
// Class ON_Color
// 
class ON_CLASS ON_Color
{
public:
	// Constructors & Conversions -     also default copy and assignment	

  static const ON_Color UnsetColor; // 0xFFFFFFFF

  // Default is black
	ON_Color();

	ON_Color(
    int red,   // ( 0 to 255 )
    int green, // ( 0 to 255 )
    int blue   // ( 0 to 255 )
    );

	ON_Color(
    int red,   // ( 0 to 255 )
    int green, // ( 0 to 255 )
    int blue,  // ( 0 to 255 )
    int alpha  // ( 0 to 255 )
    );

  // Construct from COLORREF
	ON_Color(unsigned int);

	// Conversion to COLORREF
  operator unsigned int() const;	

  // < 0 if this < arg, 0 ir this==arg, > 0 if this > arg
  int Compare( const ON_Color& ) const; 

	int Red()   const; // ( 0 to 255 )
	int Green() const; // ( 0 to 255 )
	int Blue()  const; // ( 0 to 255 )
  int Alpha() const; // ( 0 to 255 )

	double FractionRed()   const; // ( 0.0 to 1.0 )
	double FractionGreen() const; // ( 0.0 to 1.0 )
	double FractionBlue()  const; // ( 0.0 to 1.0 )
	double FractionAlpha() const; // ( 0.0 to 1.0 )

  void SetRGB(
    int red,   // red in range 0 to 255
    int green, // green in range 0 to 255
    int blue   // blue in range 0 to 255
    );

  void SetFractionalRGB(
    double red,   // red in range 0.0 to 1.0
    double green, // green in range 0.0 to 1.0
    double blue   // blue in range 0.0 to 1.0
    );

  void SetAlpha(
    int alpha // alpha in range 0 to 255
    );

  void SetFractionalAlpha(
    double alpha // alpha in range 0.0 to 1.0
    );

  void SetRGBA(
    int red,   // red in range 0 to 255
    int green, // green in range 0 to 255
    int blue,  // blue in range 0 to 255
    int alpha  // alpha in range 0 to 255
    );

  // input args
  void SetFractionalRGBA(
    double red,   // red in range 0.0 to 1.0
    double green, // green in range 0.0 to 1.0
    double blue,  // blue in range 0.0 to 1.0
    double alpha  // alpha in range 0.0 to 1.0
    );

  // Hue() returns an angle in the range 0 to 2*pi 
  //
  //           0 = red, pi/3 = yellow, 2*pi/3 = green, 
  //           pi = cyan, 4*pi/3 = blue,5*pi/3 = magenta,
  //           2*pi = red
  double Hue() const;

  // Returns 0.0 (gray) to 1.0 (saturated)
  double Saturation() const;

  // Returns 0.0 (black) to 1.0 (white)
  double Value() const;

  void SetHSV( 
         double h, // hue in radians 0 to 2*pi
         double s, // satuation 0.0 = gray, 1.0 = saturated
         double v // value     
         );

private:
  // m_color is in Windows COLORREF format.
  //
  //  0x00bbggrr,  rr= red component 0-255, etc. (little endian order)
	unsigned int m_color;
};

#endif
