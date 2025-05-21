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

////////////////////////////////////////////////////////////////
//
//  Defines ON_WindowsBITMAPINFO class that is used to provide OS independent
//  serialization of Windows device independent bitmaps (BITMAPINFO) used
//  to store preview images.
//
////////////////////////////////////////////////////////////////

#if !defined(OPENNURBS_BITMAP_INC_)
#define OPENNURBS_BITMAP_INC_

class ON_CLASS ON_Bitmap : public ON_ModelComponent
{
  ON_OBJECT_DECLARE(ON_Bitmap);

public:
  ON_Bitmap()  ON_NOEXCEPT;
  ~ON_Bitmap() = default;
  ON_Bitmap(const ON_Bitmap&);
  ON_Bitmap& operator=(const ON_Bitmap&) = default;

  static const ON_Bitmap Unset;

  /*
  Parameters:
    model_component_reference - [in]
    none_return_value - [in]
      value to return if ON_Layer::Cast(model_component_ref.ModelComponent())
      is nullptr
  Returns:
    If ON_Layer::Cast(model_component_ref.ModelComponent()) is not nullptr,
    that pointer is returned.  Otherwise, none_return_value is returned. 
  */
  static const ON_Bitmap* FromModelComponentRef(
    const class ON_ModelComponentReference& model_component_reference,
    const ON_Bitmap* none_return_value
    );

  void Dump( 
    ON_TextLog& 
    ) const override;

  bool Write( class ON_BinaryArchive& ) const override;
  bool Read( class ON_BinaryArchive& ) override;  

  unsigned int SizeOf() const override;
  
  virtual
  int Width() const;

  virtual
  int Height() const; // >0 means it's a bottom-up bitmap with origin at lower right
                      // <0 means it's a top-down bitmap with origin at upper left
  virtual
  int BitsPerPixel() const; // bits per pixel

  virtual
  size_t SizeofScan() const;  // number of bytes per scan line

  virtual
  size_t SizeofImage() const; // size of current map in bytes

  virtual
  unsigned char* Bits(
    int scan_line_index
    );

  virtual
  const unsigned char* Bits(
    int scan_line_index
    ) const;

  const ON_FileReference& FileReference() const;
  void SetFileReference(
    const ON_FileReference& file_reference
    );
  void SetFileFullPath(
    const wchar_t* file_full_path,
    bool bSetContentHash
    );

private:
  ON_FileReference m_file_reference;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_Bitmap*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<const ON_Bitmap*>;
#endif

#if !defined(ON_OS_WINDOWS_GDI)

// These are the values of the Windows defines mentioned
// in the comment below.  If you're running on Windows,
// they get defined by Windows system header files.
// If you aren't running on Windows, then you don't
// need them.
//#define BI_RGB        0L
//#define BI_RLE8       1L
//#define BI_RLE4       2L
//#define BI_BITFIELDS  3L

// Windows sizeof(ON_WindowsRGBQUAD) = 4.
struct ON_WindowsRGBQUAD {
  // Mimics Windows RGBQUAD structure.
  // For details search for "RGBQUAD" at http://msdn.microsoft.com/default.asp
  unsigned char rgbBlue;      // BYTE
  unsigned char rgbGreen;     // BYTE
  unsigned char rgbRed;       // BYTE
  unsigned char rgbReserved;  // BYTE
};

// Windows packs BITMAPFILEHEADER 
#pragma pack(push,2)
struct ON_WindowsBITMAPFILEHEADER { 
  unsigned short  bfType;         // WORD  = file type, must be BM
  unsigned int    bfSize;         // DWORD = size, in bytes, of the bitmap file
  unsigned short  bfReserved1;    // WORD    Reserved; must be zero
  unsigned short  bfReserved2;    // WORD    Reserved; must be zero
  unsigned int    bfOffBits;      // DWORD = offset, in bytes, from the beginning of the BITMAPFILEHEADER structure to the bitmap bits
};
#pragma pack(pop)

// Mimics Windows BITMAPINFOHEADER structure.
// For details search for "BITMAPINFOHEADER" at http://msdn.microsoft.com/default.asp
// Windows sizeof(BITMAPINFOHEADER) = 80.
struct ON_WindowsBITMAPINFOHEADER
{
  unsigned int   biSize;          // DWORD = sizeof(BITMAPINFOHEADER)
  int            biWidth;         // LONG  = width (in pixels) of (decompressed) bitmap
  int            biHeight;        // LONG  = height (in pixels) of (decompressed) bitmap
                                  //         >0 means it's a bottom-up bitmap with origin
                                  //            in the lower left corner.
                                  //         <0 means it's a top-down bitmap with origin
                                  //            in the upper left corner.
  unsigned short biPlanes;        // WORD  = number of planes 
                                  //         (always 1 in current Windows versions)
  unsigned short biBitCount;      // WORD  = bits per pixel (0,1,4,8,16,24,32 are valid)
                                  //         1 See http://msdn.microsoft.com/default.asp  
                                  //         4 See http://msdn.microsoft.com/default.asp  
                                  //         8 The bitmap has a maximum of 256 colors, 
                                  //           and the bmiColors member contains up 
                                  //           to 256 entries. In this case, each byte
                                  //           in the array represents a single pixel. 
                                  //        16 See http://msdn.microsoft.com/default.asp  
                                  //        24 If biClrUsed=0 and biCompression=BI_RGB(0),
                                  //           then each 3-byte triplet in the bitmap 
                                  //           array represents the relative intensities
                                  //           of blue, green, and red, respectively, for
                                  //           a pixel. For other possibilities, see
                                  //           http://msdn.microsoft.com/default.asp  
                                  //        32 If biClrUsed=0 and biCompression=BI_RGB(0),
                                  //           then each 4-byte DWORD in the bitmap 
                                  //           array represents the relative intensities
                                  //           of blue, green, and red, respectively, for
                                  //           a pixel. The high byte in each DWORD is not
                                  //           used.  
                                  //           If biClrUsed=3, biCompression=BITFIELDS(3),
                                  //           biColors[0] = red mask (0x00FF0000), 
                                  //           biColors[1] = green mask (0x0000FF00), and
                                  //           biColors[2] = blue mask (0x000000FF),
                                  //           then these masks are used with each 4-byte
                                  //           DWORD in the bitmap array to determine
                                  //           the pixel's relative intensities.                                 //           
                                  //           For other possibilities, see
                                  //           http://msdn.microsoft.com/default.asp  
  unsigned int   biCompression;   // DWORD   Currently, Windows defines the following
                                  //         types of compression.
                                  //         =0  BI_RGB (no compression)
                                  //         =1  BI_RLE8 (run length encoded used for 8 bpp)
                                  //         =2  BI_RLE4 (run length encoded used for 4 bpp)
                                  //         =3  BI_BITFIELDS  Specifies that the bitmap is
                                  //             not compressed and that the color table 
                                  //             consists of three DWORD color masks that
                                  //             specify the red, green, and blue components,
                                  //             respectively, of each pixel. This is valid
                                  //             when used with 16- and 32-bit-per-pixel
                                  //             bitmaps.
                                  //         =4  BI_JPEG (not supported in Win 95/NT4)
                                  //
  unsigned int   biSizeImage;     // DWORD = bytes in image
  int            biXPelsPerMeter; // LONG
  int            biYPelsPerMeter; // LONG
  unsigned int   biClrUsed;       // DWORD = 0 or true length of bmiColors[] array.  If 0,
                                  //           then the value of biBitCount determines the
                                  //           length of the bmiColors[] array.
  unsigned int   biClrImportant;  // DWORD
};

struct ON_WindowsBITMAPINFO
{
  // Mimics Windows BITMAPINFO structure.
  // For details search for "BITMAPINFO" at http://msdn.microsoft.com/default.asp
  ON_WindowsBITMAPINFOHEADER bmiHeader;
  ON_WindowsRGBQUAD bmiColors[1]; // The "[1]" is for the compiler.  In
                                  // practice this array commonly has
                                  // length 0, 3, or 256 and a BITMAPINFO*
                                  // points to a contiguous piece of memory
                                  // that contains
                                  //
                                  //          BITMAPINFOHEADER
                                  //          RGBQUAD[length determined by flags]
                                  //          unsigned char[biSizeImage]
                                  //
                                  // See the ON_WindowsBITMAPINFOHEADER comments
                                  // and http://msdn.microsoft.com/default.asp
                                  // for more details.
};

#endif

class ON_CLASS ON_WindowsBitmap : public ON_Bitmap
{
  ON_OBJECT_DECLARE(ON_WindowsBitmap);
  // Uncompressed 8 bpp, 24 bpp, or 32 bpp Windows device 
  // independent bitmaps (DIB)
public:
  ON_WindowsBitmap() = default;
  ~ON_WindowsBitmap();
  ON_WindowsBitmap(const ON_WindowsBitmap&);
  ON_WindowsBitmap& operator=(const ON_WindowsBitmap&);

  static const ON_WindowsBitmap Unset;

  /*
  Parameters:
    width - [in]
    height - [in]
    bits_per_pixel - [in]
      1, 2, 4, 8, 16, 24, or 32
  */
  bool Create( 
         int width,
         int height,
         int bits_per_pixel
         );

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  bool IsEmpty() const;

  bool Write( ON_BinaryArchive& ) const override; // writes compressed image
  bool Read( ON_BinaryArchive& ) override;        // reads compressed image
  unsigned int SizeOf() const override;
  
public:
  bool WriteCompressed( ON_BinaryArchive& ) const;
  bool ReadCompressed( ON_BinaryArchive& );
  bool WriteUncompressed( ON_BinaryArchive& ) const;
  bool ReadUncompressed( ON_BinaryArchive& );

public:
  int Width() const override;
  int Height() const override; // >0 means it's a bottom-up bitmap with origin at lower right
                      // <0 means it's a top-down bitmap with origin at upper left

  int PaletteColorCount() const; // number of colors in palette
  int SizeofPalette() const;     // number of bytes in palette

  int BitsPerPixel() const override;
  size_t SizeofScan() const override;        // number of bytes per scan line
  size_t SizeofImage() const override;       // number of bytes in image

  unsigned char* Bits(
    int // index of scan line 
    ) override;
  const unsigned char* Bits(
    int // index of scan line 
    ) const override;

  //int PaletteIndex( ON_Color ) const; // for 8bpp bitmaps

  ON_Color Pixel( 
    int, // 0 <= i < width
    int  // 0 <= j < height
    ) const;
  ON_Color Pixel( 
    int,  // 0 <= i < width
    const unsigned char* // value of Bits( j )
    ) const;

  //bool SetColor( // sets entire map to specified color 
  //       ON_Color
  //       );

#if defined(ON_OS_WINDOWS_GDI)

  /*
  Description:
    Create an ON_WindowsBitmap from a contiguous bitmap.
    Copies src.
  Parameters:
    src - [in] contiguous Windows device independent bitmap.
  Remarks:
    If the current Windows BITMAPINFO is identical to ON_WindowsBITMAPINFO,
    then the result of this call is identical to

         int color_count = number of colors in bitmap's palette;
         ON_WindowsBitmap::Create( &src, &src.bmiColors[color_count], true ).

  See Also:
    ON_WindowsBitmap::Create    
  */
#if defined (ON_RUNTIME_WIN)
  ON_WindowsBitmap(const BITMAPINFO& src);
#else
  ON_WindowsBitmap(const ON_WindowsBITMAPINFO& src);
#endif

  /*
  Description:
    Create an ON_WindowsBitmap from a contiguous bitmap.
    Shares bitmap memory with src.
  Parameters:
    src - [in] contiguous Windows device independent bitmap.
  See Also:
    ON_WindowsBitmap::Create    
  Remarks:
    ~ON_WindowsBitmap will not delete src.
  */
#if defined (ON_RUNTIME_WIN)
  ON_WindowsBitmap(const BITMAPINFO* src);
#else
  ON_WindowsBitmap(const ON_WindowsBITMAPINFO* src);
#endif

  /*
  Description:
    Create an ON_WindowsBitmap from a contiguous bitmap.
    Copies src.
  Parameters:
    src - [in] contiguous Windows device independent bitmap.
  See Also:
    ON_WindowsBitmap::Create    
  */
#if defined (ON_RUNTIME_WIN)
  ON_WindowsBitmap& operator=(const BITMAPINFO& src);
#else
  ON_WindowsBitmap& operator=(const ON_WindowsBITMAPINFO& src);
#endif

  /*
  Description:
    Create and ON_WindowsBitmap from a Windows BITMAPINFO pointer
    and a pointer to the bits.

    This is intended to make it easy to write compressed bimaps.
    For ON_WindowsBitmap classes created with ON_WindowsBitmap::Share,
    ON_WindowsBitmap::Destroy and ~ON_WindowsBitmap will
    not free the bmi and bits memory.

  Parameters:
    bmi  - [in] valid BITMAPINFO
    bits - [in] bits for BITMAPINFO
    bCopy - [in] If true, the bmi and bits are copied into a contiguous
                 bitmap that will be deleted by ~ON_WindowsBitmap.
                 If false, the m_bmi and m_bits pointers on this class
                 are simply set to bmi and bits.  In this case,
                 ~ON_WindowsBitmap will not free the bmi or bits
                 memory.

  Example:

          ON_BinaryArchive archive = ...;
          BITMAPINFO* bmi = 0;
          unsigned char* bits = 0;
          int color_count = ...; // number of colors in palette

          int sizeof_palette = sizeof(bmi->bmiColors[0]) * color_count;

          BITMAPINFO* bmi = (LPBITMAPINFO)calloc( 1, sizeof(*bmi) + sizeof_palette );

          bmi->bmiHeader.biSize          = sizeof(bmi->bmiHeader);
          bmi->bmiHeader.biWidth         = width;
          bmi->bmiHeader.biHeight        = height;
          bmi->bmiHeader.biPlanes        = 1;
          bmi->bmiHeader.biBitCount      = (USHORT)color_depth;
          bmi->bmiHeader.biCompression   = BI_RGB;                  
          bmi->bmiHeader.biXPelsPerMeter = 0;
          bmi->bmiHeader.biYPelsPerMeter = 0;
          bmi->bmiHeader.biClrUsed       = 0;
          bmi->bmiHeader.biClrImportant  = 0;
          bmi->bmiHeader.biSizeImage     = GetStorageSize();

          // initialize palette
          ...

          HBITMAP hbm = ::CreateDIBSection( nullptr, bmi, ..., (LPVOID*)&bits, nullptr, 0);

          {
            // Use ON_WindowsBitmap to write a compressed bitmap to 
            // archive.  Does not modify bmi or bits.
            ON_WindowsBitmap onbm;
            onbm.Create(bmi,bit,false);
            onbm.Write( archive );
          }

  */
#endif


#if defined (ON_OS_WINDOWS_GDI)
  bool Create(
    const BITMAPINFO* bmi, 
    const unsigned char* bits,
    bool bCopy
    );
#else
  bool Create(
    const ON_WindowsBITMAPINFO* bmi,
    const unsigned char* bits,
    bool bCopy
  );
#endif



  /*
  Returns:
    True if m_bmi and m_bits are in a single contiguous 
    block of memory.
    False if m_bmi and m_bits are in two blocks of memory.    
  */
  bool IsContiguous() const;

#if defined(ON_OS_WINDOWS_GDI)
  BITMAPINFO* m_bmi = nullptr;
#else
  struct ON_WindowsBITMAPINFO* m_bmi = nullptr;
  
  /*
Description:
   Create an ON_WindowsBitmap from a contiguous bitmap ON_WindowsBITMAPINFO.
   Parameters:
     src - [in] 
       A contiguous Windows device independent bitmap.  This means that the
       "bits" in the bitmap begin at the memory location &m_bits->bmiColors[0].
   See Also:
   Remarks:
     ~ON_WindowsBitmap will not delete src.
   */
  bool Create (
    const struct ON_WindowsBITMAPINFO* src 
    );
#endif

  unsigned char* m_bits = nullptr;

private:
  int m_bFreeBMI = 0; // 0 m_bmi and m_bits are not freed by ON_WindowsBitmap::Destroy
                  // 1 m_bmi  memory is freed by ON_WindowsBitmap::Destroy
                  // 2 m_bits memory is freed by ON_WindowsBitmap::Destroy
                  // 3 m_bmi and m_bits memory is freed by ON_WindowsBitmap::Destroy     

private:
  bool Internal_WriteV5( ON_BinaryArchive& ) const;
  bool Internal_ReadV5( ON_BinaryArchive& );

protected:
  void Internal_Destroy();
  void Internal_Copy(
    const ON_WindowsBitmap& src
    );  
};

/*
Description:
  ON_WindowsBitmapEx is identical to ON_WindowsBitmap except that
  it's Read/Write functions save bitmap names.
*/
class ON_CLASS ON_WindowsBitmapEx : public ON_WindowsBitmap
{
  ON_OBJECT_DECLARE(ON_WindowsBitmapEx);
public:
  ON_WindowsBitmapEx() = default;
  ~ON_WindowsBitmapEx() = default;
  ON_WindowsBitmapEx(const ON_WindowsBitmapEx&) = default;
  ON_WindowsBitmapEx& operator=(const ON_WindowsBitmapEx&) = default;

  static const ON_WindowsBitmapEx Unset;
  
  bool Write( ON_BinaryArchive& ) const override; // writes compressed image
  bool Read( ON_BinaryArchive& ) override;        // reads compressed image

private:
  bool Internal_WriteV5( ON_BinaryArchive& ) const; // writes compressed image
  bool Internal_ReadV5( ON_BinaryArchive& );        // reads compressed image
};

class ON_CLASS ON_EmbeddedBitmap : public ON_Bitmap
{
  ON_OBJECT_DECLARE(ON_EmbeddedBitmap);
public:
  ON_EmbeddedBitmap() = default;
  ~ON_EmbeddedBitmap();
  ON_EmbeddedBitmap(const ON_EmbeddedBitmap&);
  ON_EmbeddedBitmap& operator=(const ON_EmbeddedBitmap&);

  static const ON_EmbeddedBitmap Unset;

  void Create( 
    size_t sizeof_buffer 
    );

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  bool Write( ON_BinaryArchive& ) const override;
  bool Read( ON_BinaryArchive& ) override;
  unsigned int SizeOf() const override;

  size_t SizeofImage() const override;
  unsigned char* Bits(int) override;
  const unsigned char* Bits(int) const override;

  const void* m_buffer = nullptr;
  size_t m_sizeof_buffer = 0;
  bool m_managed_buffer = false; // true means the ON_EmbeddedBitmap class manages m_buffer memory.
  ON__UINT32 m_buffer_crc32 = 0; // 32 bit crc from ON_CRC32

private:
  bool Internal_WriteV5( ON_BinaryArchive& ) const;
  bool Internal_ReadV5( ON_BinaryArchive& );

private:
  void Internal_Destroy();
  void Internal_Copy(
    const ON_EmbeddedBitmap& src
    );  
};

#endif
