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

ON_VIRTUAL_OBJECT_IMPLEMENT( ON_Bitmap, ON_Object, "390465E9-3721-11d4-800B-0010830122F0");

ON_OBJECT_IMPLEMENT( ON_WindowsBitmap, ON_Bitmap,  "390465EB-3721-11d4-800B-0010830122F0");

ON_OBJECT_IMPLEMENT( ON_EmbeddedBitmap, ON_Bitmap, "772E6FC1-B17B-4fc4-8F54-5FDA511D76D2");

ON_OBJECT_IMPLEMENT( ON_WindowsBitmapEx, ON_WindowsBitmap,  "203AFC17-BCC9-44fb-A07B-7F5C31BD5ED9");

const ON_Bitmap* ON_Bitmap::FromModelComponentRef(
  const class ON_ModelComponentReference& model_component_reference,
  const ON_Bitmap* none_return_value
  )
{
  const ON_Bitmap* p = ON_Bitmap::Cast(model_component_reference.ModelComponent());
  return (nullptr != p) ? p : none_return_value;
}

ON_Bitmap::ON_Bitmap() ON_NOEXCEPT
  : ON_ModelComponent(ON_ModelComponent::Type::Image)
{}

ON_Bitmap::ON_Bitmap( const ON_Bitmap& src)
  : ON_ModelComponent(ON_ModelComponent::Type::Image,src)
  , m_file_reference(src.m_file_reference)
{}

void ON_Bitmap::Dump( ON_TextLog& dump ) const
{
  ON_ModelComponent::Dump(dump);
  m_file_reference.Dump(dump);
  dump.Print("width = %d pixels\n",Width());
  dump.Print("height = %d pixels\n",Height());
  dump.Print("bits per pixel = %d\n",BitsPerPixel());
  dump.Print("size of image = %zu bytes\n",SizeofImage());
}

int ON_Bitmap::Width() const
{
  return 0;
}

int ON_Bitmap::Height() const
{
  return 0;
}

int ON_Bitmap::BitsPerPixel() const
{
  return 0;
}

size_t ON_Bitmap::SizeofScan() const
{
  return 0;
}

size_t ON_Bitmap::SizeofImage() const
{
  return 0;
}

unsigned char* ON_Bitmap::Bits(
  int scan_line_index
  )
{
  return nullptr;
}

const unsigned char* ON_Bitmap::Bits(
  int scan_line_index
  ) const
{
  return nullptr;
}

bool ON_Bitmap::Write(ON_BinaryArchive& archive) const
{
  const int major_version = 1;
  const int minor_version = 0;
  if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, major_version, minor_version))
    return false;

  bool rc = false;
  for (;;)
  {
    const unsigned int attributes_filter
      = ON_ModelComponent::Attributes::IdAttribute
      | ON_ModelComponent::Attributes::IndexAttribute
      | ON_ModelComponent::Attributes::NameAttribute
      ;
    ON_ModelComponent::WriteModelComponentAttributes(archive, attributes_filter);
    if (!m_file_reference.Write(true, archive))
      break;

    rc = true;
    break;
  }

  if (!archive.EndWrite3dmChunk())
    rc = false;

  return rc;
}

bool ON_Bitmap::Read(ON_BinaryArchive& archive)
{
  int major_version = 0;
  int minor_version = 0;
  if (!archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version))
    return false;

  bool rc = false;
  for (;;)
  {
    if (1 != major_version)
      break;
    ON_ModelComponent::ReadModelComponentAttributes(archive);
    if (!m_file_reference.Read(archive))
      break;

    rc = true;
    break;
  }

  if (!archive.EndRead3dmChunk())
    rc = false;

  return rc;
}


const ON_FileReference& ON_Bitmap::FileReference() const
{
  return m_file_reference;
}


void ON_Bitmap::SetFileReference(
  const ON_FileReference& file_reference
  )
{
  if ( 0 != ON_FileReference::Compare(m_file_reference,file_reference) )
  {
    IncrementContentVersionNumber();
    m_file_reference = file_reference;
  }
}


void ON_Bitmap::SetFileFullPath(
  const wchar_t* file_full_path,
  bool bSetContentHash
  )
{
  ON_FileReference file_reference;
  file_reference.SetFullPath(file_full_path,bSetContentHash);
  SetFileReference(file_reference);
}


static
int ON_WindowsBitmapHelper_PaletteColorCount( int bmiHeader_biClrUsed, int bmiHeader_biBitCount )
{
  int color_count = 0;
  
  if ( bmiHeader_biClrUsed )
  {
    color_count = bmiHeader_biClrUsed;
  }
  else 
  {  
    switch( bmiHeader_biBitCount )
    {
    case 1:
      color_count = 2;
      break;
    case 4:
      color_count = 16;
      break;
    case 8:
      color_count = 256;
      break;
    default:
      color_count = 0;
    }
  }  
  return color_count;
}

static
size_t ON_WindowsBitmapHelper_SizeofPalette( int bmiHeader_biClrUsed, int bmiHeader_biBitCount )
{
#if defined(ON_OS_WINDOWS_GDI)
  return ( ON_WindowsBitmapHelper_PaletteColorCount(bmiHeader_biClrUsed,bmiHeader_biBitCount) * sizeof(RGBQUAD) );
#else
  return ( ON_WindowsBitmapHelper_PaletteColorCount(bmiHeader_biClrUsed,bmiHeader_biBitCount) * sizeof(ON_WindowsRGBQUAD) );
#endif
}

ON_WindowsBitmap::ON_WindowsBitmap( const ON_WindowsBitmap& src ) 
 : ON_Bitmap(src)
{
  Internal_Copy(src);
}

ON_WindowsBitmap::~ON_WindowsBitmap()
{
  Internal_Destroy();
}

ON_WindowsBitmap& ON_WindowsBitmap::operator=( const ON_WindowsBitmap& src )
{
  if ( this != &src ) 
  {
    Internal_Destroy();
    ON_Bitmap::operator=(src);
    Internal_Copy(src);
  }
  return *this;
}

#if defined(ON_OS_WINDOWS_GDI)

static BITMAPINFO* 
ON_WindowsBitmapHelper_AllocBMI(size_t sizeof_palette, size_t sizeof_image)
{
  // In theory,
  //    sz = sizeof(BITMAPINFOHEADER) + sizeof_palette + sizeof_image;
  // should work, but BITMAPINFO is only 4 bytes bigger than BITMAPINFOHEADER
  // and the allocation below will certainly work.
  size_t sz = sizeof(BITMAPINFO) + sizeof_palette + sizeof_image;
  BITMAPINFO* bmi = (BITMAPINFO*)onmalloc(sz);
  if ( bmi )
  {
    memset(bmi,0,sizeof(*bmi));
    bmi->bmiHeader.biSize = sizeof(bmi->bmiHeader);
  }
  return bmi;
}

#else

static 
ON_WindowsBITMAPINFO* ON_WindowsBitmapHelper_AllocBMI(size_t sizeof_palette, size_t sizeof_image)
{
  size_t sz = sizeof(ON_WindowsBITMAPINFO) + sizeof_palette + sizeof_image;
  ON_WindowsBITMAPINFO* bmi = (ON_WindowsBITMAPINFO*)onmalloc(sz);
  if ( bmi )
  {
    memset(bmi,0,sizeof(*bmi));
    bmi->bmiHeader.biSize = sizeof(bmi->bmiHeader);
  }
  return bmi;
}

#endif

void ON_WindowsBitmap::Internal_Copy( const ON_WindowsBitmap& src )
{
  if ( nullptr != src.m_bmi ) 
  {
    const int sizeof_palette = src.SizeofPalette();
    const size_t sizeof_image = src.SizeofImage();
    m_bmi = ON_WindowsBitmapHelper_AllocBMI( sizeof_palette, sizeof_image );
    if ( m_bmi ) 
    {
      m_bFreeBMI = 1;
      m_bmi->bmiHeader = src.m_bmi->bmiHeader;
      if( sizeof_palette > 0 )
      {
        memcpy(&m_bmi->bmiColors[0],&src.m_bmi->bmiColors[0],sizeof_palette);
      }
      if ( sizeof_image > 0 ) 
      {
        m_bits = (unsigned char*)&m_bmi->bmiColors[PaletteColorCount()];
        if ( src.m_bits )
          memcpy( m_bits, src.m_bits, sizeof_image );
        else
          memset( m_bits, 0, sizeof_image );
      }
      else
        m_bits = nullptr;
    }
  }
}


void ON_WindowsBitmap::Internal_Destroy()
{
  if (nullptr != m_bmi) 
  {
    if ( 1 == m_bFreeBMI || 3 == m_bFreeBMI )
      onfree(m_bmi);
    m_bmi = nullptr;
  }

  if ( nullptr != m_bits )
  {
    if ( 2 == m_bFreeBMI || 3 == m_bFreeBMI )
      onfree(m_bits);
    m_bits = nullptr;
  }

  m_bFreeBMI = 0;
}

bool ON_WindowsBitmap::IsEmpty() const
{
  return ( nullptr == m_bmi || nullptr == m_bits || 0 == Width() || 0 == Height() );
}

bool ON_WindowsBitmap::IsValid( ON_TextLog* text_log ) const
{
  bool rc 
    = ( m_bmi != nullptr && m_bits != nullptr && Width() > 0 && Height() > 0) 
    ? true
    : false;

  if ( !rc && 0 != text_log )
  {
    // TODO:  add a detailed diagnostic message
    text_log->Print("ON_WindowsBitmap is not valid\n");
  }
  return rc;
}


bool ON_WindowsBitmap::Create( 
       int width,
       int height,
       int bits_per_pixel // 1, 2, 4, 8, 16, 24, or 32
       )
{
  Internal_Destroy();

  if ( width < 1 || height < 1 )
  {
    return false;
  }
  if (   bits_per_pixel != 1 && bits_per_pixel !=  2 && bits_per_pixel !=  4 
      && bits_per_pixel != 8 && bits_per_pixel != 16 && bits_per_pixel != 24 
      && bits_per_pixel != 32 )
  {
    return false;
  }

#if defined(ON_OS_WINDOWS_GDI)
  BITMAPINFOHEADER bh;
  const DWORD sizeof_RGBQUAD    = sizeof(RGBQUAD);
#else
  ON_WindowsBITMAPINFOHEADER bh;
  const unsigned int sizeof_RGBQUAD    = sizeof(ON_WindowsRGBQUAD);
#endif
  memset( &bh, 0, sizeof(bh) );
  bh.biSize = sizeof(bh);
  bh.biWidth = width;
  bh.biHeight = height;
  bh.biPlanes = 1;
  bh.biBitCount = (unsigned short)bits_per_pixel; // cast is safe
  bh.biCompression = 0; // BI_RGB
  const int sizeof_scan = (((bits_per_pixel*width) + 31) / 32) * 4;
  bh.biSizeImage = height*sizeof_scan;
  bh.biXPelsPerMeter = 0;
  bh.biYPelsPerMeter = 0;
  bh.biClrUsed = 0;
  bh.biClrImportant = 0;

  int palette_color_count = 0;
  switch ( bits_per_pixel ) {
  case 1:
    palette_color_count = 2;
    break;
  case 4:
    palette_color_count = 16;
    break;
  case 8:
    palette_color_count = 256;
    break;
  }
  const int sizeof_palette = palette_color_count*sizeof_RGBQUAD;

  m_bmi = ON_WindowsBitmapHelper_AllocBMI( sizeof_palette, bh.biSizeImage );

  bool rc = false;

  if ( m_bmi /*&& palette_color_count > 0*/) 
  {
    m_bmi->bmiHeader = bh;
    m_bits = (unsigned char*)&m_bmi->bmiColors[palette_color_count];

    // default palette is gray scale
    if ( palette_color_count > 0 )
    {
      const int rgb_delta = 256/palette_color_count;
      int i, rgb;
      for ( i = 0, rgb = 0; i < palette_color_count; i++, rgb += rgb_delta ) 
      {
        if ( rgb >= 256 ) rgb = 255;
        m_bmi->bmiColors[i].rgbBlue  = (unsigned char)rgb;
        m_bmi->bmiColors[i].rgbGreen = (unsigned char)rgb;
        m_bmi->bmiColors[i].rgbRed   = (unsigned char)rgb;
        m_bmi->bmiColors[i].rgbReserved = 0;
      }
    }
    rc = true;
  }

  return rc;
}



int ON_WindowsBitmap::Width() const
{
  return (m_bmi) ? m_bmi->bmiHeader.biWidth : 0;
}

int ON_WindowsBitmap::Height() const
{
  return (m_bmi) ? m_bmi->bmiHeader.biHeight : 0;
}

int ON_WindowsBitmap::PaletteColorCount() const
{
  return m_bmi ? ON_WindowsBitmapHelper_PaletteColorCount(m_bmi->bmiHeader.biClrUsed, m_bmi->bmiHeader.biBitCount ) : 0;
}

int ON_WindowsBitmap::SizeofPalette() const
{
  return m_bmi ? ((int)ON_WindowsBitmapHelper_SizeofPalette(m_bmi->bmiHeader.biClrUsed, m_bmi->bmiHeader.biBitCount) ) : 0;
}

size_t ON_WindowsBitmap::SizeofScan() const
{
  int scan_width = 0;
  if ( m_bmi ) {
    int bitcount = m_bmi->bmiHeader.biBitCount;
    int width = Width();
    scan_width = (((bitcount*width) + 31) / 32) * 4;
  }
  return scan_width;
}

int ON_WindowsBitmap::BitsPerPixel() const
{
  return m_bmi ? m_bmi->bmiHeader.biBitCount : 0;
}

size_t ON_WindowsBitmap::SizeofImage() const
{
  size_t sizeImage = 0;
  if ( nullptr != m_bmi ) 
  {
    sizeImage = m_bmi->bmiHeader.biSizeImage;
    if (0 == sizeImage)
    {
      const size_t w = ((((m_bmi->bmiHeader.biWidth * m_bmi->bmiHeader.biBitCount) + 31) & ~31) >> 3);
      const size_t h = m_bmi->bmiHeader.biHeight;
      sizeImage = w*h;
    }
  }
  return sizeImage;
}

unsigned char* ON_WindowsBitmap::Bits( int scan_index )
{
  const size_t sizeof_scan = SizeofScan();
  unsigned char* bits = m_bmi ? (unsigned char*)&m_bmi->bmiColors[PaletteColorCount()] : 0;
  if ( bits && sizeof_scan && scan_index >= 0 && scan_index < Height() ) {
    bits += ( sizeof_scan*scan_index );
  }
  else {
    bits = 0;
  }
  return bits;
}

const unsigned char* ON_WindowsBitmap::Bits(int scan_index) const
{
  const size_t sizeof_scan = SizeofScan();
  const unsigned char* bits = m_bmi ? (const unsigned char*)&m_bmi->bmiColors[PaletteColorCount()] : 0;
  if ( bits && sizeof_scan && scan_index >= 0 && scan_index < Height() ) {
    bits += (sizeof_scan*scan_index);
  }
  else {
    bits = 0;
  }
  return bits;
}

ON_Color ON_WindowsBitmap::Pixel( int column_index, int row_index ) const
{
  return Pixel( column_index, Bits(row_index) );
}

ON_Color ON_WindowsBitmap::Pixel( int column_index, const unsigned char* scanbits ) const
{
  int r=0,g=0,b=0,a=0;

  unsigned int palindex;
  
  if ( m_bmi && column_index >= 0 && column_index <= Width() && scanbits && !m_bmi->bmiHeader.biCompression ) {
    switch( m_bmi->bmiHeader.biBitCount ) {
    case 32:
      scanbits += (column_index*4);
      b = *scanbits++;
      g = *scanbits++;
      r = *scanbits++;
      a = *scanbits;
      break;
    
    case 24:
      scanbits += (column_index*3);
      b = *scanbits++;
      g = *scanbits++;
      r = *scanbits;
      break;
    
    case 8:
      // 256 color bitmap uses palette
      palindex = scanbits[column_index];    
      b = m_bmi->bmiColors[palindex].rgbBlue;
      g = m_bmi->bmiColors[palindex].rgbGreen;
      r = m_bmi->bmiColors[palindex].rgbRed;
      a = m_bmi->bmiColors[palindex].rgbReserved;
      break;
    
    case 4:
      {
        // 16 color bitmap uses palette
        palindex = scanbits[column_index/2];
        if ( !(column_index%2) )
          palindex >>= 4;
        palindex &= 0x0F;
        b = m_bmi->bmiColors[palindex].rgbBlue;
        g = m_bmi->bmiColors[palindex].rgbGreen;
        r = m_bmi->bmiColors[palindex].rgbRed;
        a = m_bmi->bmiColors[palindex].rgbReserved;
      }
      break;
    
    case 1:
      // monochrome bitmap has 2 color palette 
      palindex = ( scanbits[column_index/8] >> (7-(column_index%8)) ) & 0x01;
      b = m_bmi->bmiColors[palindex].rgbBlue;
      g = m_bmi->bmiColors[palindex].rgbGreen;
      r = m_bmi->bmiColors[palindex].rgbRed;
      a = m_bmi->bmiColors[palindex].rgbReserved;
      break;		
    }
  }
  
  return ON_Color(r,g,b,a);
}

bool ON_WindowsBitmap::WriteUncompressed( ON_BinaryArchive& file ) const
{
#if defined(ON_OS_WINDOWS_GDI)
  BITMAPINFOHEADER bmiHeader;
#else
  ON_WindowsBITMAPINFOHEADER bmiHeader;
#endif

  if ( m_bmi )
  {
    bmiHeader = m_bmi->bmiHeader;
    bmiHeader.biSize = sizeof(bmiHeader);
  }
  else 
  {
    memset(&bmiHeader,0,sizeof(bmiHeader));
  }
  int i;
  short s;
  i = bmiHeader.biSize;
  bool    rc = file.WriteInt(i);
  i = bmiHeader.biWidth;
  if (rc) rc = file.WriteInt(i);
  i = bmiHeader.biHeight;
  if (rc) rc = file.WriteInt(i);
  s = bmiHeader.biPlanes;
  if (rc) rc = file.WriteShort(s);
  s = bmiHeader.biBitCount;
  if (rc) rc = file.WriteShort(s);
  i = bmiHeader.biCompression;
  if (rc) rc = file.WriteInt(i);
  i = bmiHeader.biSizeImage;
  if (rc) rc = file.WriteInt(i);
  i = bmiHeader.biXPelsPerMeter;
  if (rc) rc = file.WriteInt(i);
  i = bmiHeader.biYPelsPerMeter;
  if (rc) rc = file.WriteInt(i);
  i = bmiHeader.biClrUsed;
  if (rc) rc = file.WriteInt(i);
  i = bmiHeader.biClrImportant;
  if (rc) rc = file.WriteInt(i);

  if ( rc ) 
  {
    const int color_count = PaletteColorCount();
    for (i = 0; i < color_count && rc; i++ )
    {
      if (rc) rc = file.WriteChar( m_bmi->bmiColors[i].rgbBlue );
      if (rc) rc = file.WriteChar( m_bmi->bmiColors[i].rgbGreen );
      if (rc) rc = file.WriteChar( m_bmi->bmiColors[i].rgbRed );
      if (rc) rc = file.WriteChar( m_bmi->bmiColors[i].rgbReserved );
    }
    const size_t sizeof_image = SizeofImage();
    if ( sizeof_image > 0 && rc ) 
    {
      if (rc) rc = file.WriteByte( sizeof_image, &m_bmi->bmiColors[color_count] );
    }
  }

  return rc;
}

bool ON_WindowsBitmap::ReadUncompressed( ON_BinaryArchive& file )
{
#if defined(ON_OS_WINDOWS_GDI)
  BITMAPINFOHEADER bmiHeader;
#else
  ON_WindowsBITMAPINFOHEADER bmiHeader;
#endif
  memset(&bmiHeader,0,sizeof(bmiHeader));

  Internal_Destroy();

  int i;
  short s;
  bool rc;

  for(;;)
  {
    i = 0;
    s = 0;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biSize = i;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biWidth = i;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biHeight = i;
    rc = file.ReadShort(&s); if (!rc) break; bmiHeader.biPlanes = s;
    rc = file.ReadShort(&s); if (!rc) break; bmiHeader.biBitCount = s;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biCompression = i;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biSizeImage = i;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biXPelsPerMeter = i;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biYPelsPerMeter = i;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biClrUsed = i;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biClrImportant = i;
    break;
  }

  if ( rc ) 
  {
    bmiHeader.biSize = sizeof(bmiHeader);
    const size_t sizeof_palette = ON_WindowsBitmapHelper_SizeofPalette(bmiHeader.biClrUsed, bmiHeader.biBitCount );
    const size_t sizeof_image   = bmiHeader.biSizeImage;
    
    m_bmi = ON_WindowsBitmapHelper_AllocBMI( sizeof_palette, sizeof_image );

    if ( !m_bmi )
    {
      rc = false;
    }
    else 
    {
      m_bFreeBMI = 1;
      m_bmi->bmiHeader = bmiHeader;
      const int color_count = ON_WindowsBitmapHelper_PaletteColorCount(bmiHeader.biClrUsed, bmiHeader.biBitCount );
      for (int i_for_loop = 0; i_for_loop < color_count && rc; i_for_loop++ ) 
      {
        if (rc) rc = file.ReadChar( &m_bmi->bmiColors[i_for_loop].rgbBlue );
        if (rc) rc = file.ReadChar( &m_bmi->bmiColors[i_for_loop].rgbGreen );
        if (rc) rc = file.ReadChar( &m_bmi->bmiColors[i_for_loop].rgbRed );
        if (rc) rc = file.ReadChar( &m_bmi->bmiColors[i_for_loop].rgbReserved );
      }
      if ( sizeof_image > 0 && rc ) 
      {
        m_bits = (unsigned char*)&m_bmi->bmiColors[color_count];
        if (rc) rc = file.ReadByte( sizeof_image, m_bits );
      }
    }
  }
  return rc;
}

bool ON_WindowsBitmap::Write( ON_BinaryArchive& archive ) const
{
  return Internal_WriteV5(archive);
}

bool ON_WindowsBitmap::Internal_WriteV5( ON_BinaryArchive& archive ) const
{
  return WriteCompressed(archive);
}

bool ON_WindowsBitmap::Read( ON_BinaryArchive& archive )
{
  return Internal_ReadV5(archive);
}

bool ON_WindowsBitmap::Internal_ReadV5( ON_BinaryArchive& file )
{
  bool rc = false;
  if ( file.Archive3dmVersion() == 1 )
    rc = ReadUncompressed(file);
  else
    rc = ReadCompressed(file);
  return rc;
}

bool ON_WindowsBitmapEx::Write(ON_BinaryArchive& archive) const
{
  return Internal_WriteV5(archive);
}

bool ON_WindowsBitmapEx::Read(ON_BinaryArchive& archive)
{
  return Internal_ReadV5(archive);
}

bool ON_WindowsBitmapEx::Internal_WriteV5( ON_BinaryArchive& file ) const
{
  bool rc = file.Write3dmChunkVersion(1,0);
  if (rc)
    rc = file.WriteString(FileReference().FullPath());
  if (rc)
    rc = ON_WindowsBitmap::WriteCompressed(file);
  return rc;
}

bool ON_WindowsBitmapEx::Internal_ReadV5( ON_BinaryArchive& file )
{
  Internal_Destroy();
  SetFileReference(ON_FileReference::Unset);

  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if (rc && 1 == major_version )
  {
    // Calling ON_WindowsBitmap::ReadCompressed() destroys
    // m_bitmap_filename, so we have to read it into a local
    // string and make the assignment after calling
    // ON_WindowsBitmap::ReadCompressed().
    ON_wString bitmap_filename;
    if (rc)
      rc = file.ReadString(bitmap_filename);
    if ( !rc)
      bitmap_filename.Destroy();

    if (rc)
      rc = ON_WindowsBitmap::ReadCompressed(file);

    bitmap_filename.TrimLeftAndRight();
    if (bitmap_filename.IsNotEmpty())
    {
      ON_FileReference file_reference;
      if (ON_FileSystemPath::IsRelativePath(bitmap_filename))
        file_reference.SetRelativePath(bitmap_filename);
      else
        file_reference.SetFullPath(bitmap_filename,false);
      SetFileReference(file_reference);
    }
  }
  else
    rc = false;
  return rc;
}

bool ON_WindowsBitmap::WriteCompressed( ON_BinaryArchive& file ) const
{
  int color_count = 0;
  int sizeof_palette = 0;
  size_t sizeof_image = 0;
  bool bContiguousBitmap = IsContiguous();
#if defined(ON_OS_WINDOWS_GDI)
  BITMAPINFOHEADER bmiHeader;
#else
  ON_WindowsBITMAPINFOHEADER bmiHeader;
#endif
  if ( m_bmi )
  {
    bmiHeader = m_bmi->bmiHeader;
    color_count = PaletteColorCount();
    sizeof_palette = color_count*sizeof(*m_bmi->bmiColors);
    sizeof_image = SizeofImage();
    if ( 0 == sizeof_image )
      bContiguousBitmap = true;
  }
  else 
  {
    bContiguousBitmap = true;
    color_count = 0;
    sizeof_palette = 0;
    sizeof_image = 0;
    memset(&bmiHeader,0,sizeof(bmiHeader));
  }
  int i;
  short s;
  i = bmiHeader.biSize;
  bool    rc = file.WriteInt(i);
  i = bmiHeader.biWidth;
  if (rc) rc = file.WriteInt(i);
  i = bmiHeader.biHeight;
  if (rc) rc = file.WriteInt(i);
  s = bmiHeader.biPlanes;
  if (rc) rc = file.WriteShort(s);
  s = bmiHeader.biBitCount;
  if (rc) rc = file.WriteShort(s);
  i = bmiHeader.biCompression;
  if (rc) rc = file.WriteInt(i);
  i = bmiHeader.biSizeImage;
  if (rc) rc = file.WriteInt(i);
  i = bmiHeader.biXPelsPerMeter;
  if (rc) rc = file.WriteInt(i);
  i = bmiHeader.biYPelsPerMeter;
  if (rc) rc = file.WriteInt(i);
  i = bmiHeader.biClrUsed;
  if (rc) rc = file.WriteInt(i);
  i = bmiHeader.biClrImportant;
  if (rc) rc = file.WriteInt(i);

  if ( rc ) 
  {
    if ( bContiguousBitmap )
    {
      const size_t sizeof_buffer = sizeof_palette + sizeof_image;
      // palette and bits are compressed in a single chunk
      rc = file.WriteCompressedBuffer( sizeof_buffer, (0 != m_bmi) ? m_bmi->bmiColors : 0);
    }
    else
    {
      // 28 July 2003
      //     Added support for writing non-contiguous bitmaps
      // palette 
      rc = file.WriteCompressedBuffer( sizeof_palette, m_bmi->bmiColors );
      if (rc)
      {
        // image bits
        rc = file.WriteCompressedBuffer( sizeof_image, m_bits );
      }
    }
  }

  return rc;
}

bool ON_WindowsBitmap::ReadCompressed( ON_BinaryArchive& file )
{
  Internal_Destroy();

  bool bFailedCRC = false;
#if defined(ON_OS_WINDOWS_GDI)
  BITMAPINFOHEADER bmiHeader;
#else
  ON_WindowsBITMAPINFOHEADER bmiHeader;
#endif
  memset(&bmiHeader,0,sizeof(bmiHeader));
  int i;
  short s;
  bool rc;

  for(;;)
  {
    i = 0;
    s = 0;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biSize = i;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biWidth = i;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biHeight = i;
    rc = file.ReadShort(&s); if (!rc) break; bmiHeader.biPlanes = s;
    rc = file.ReadShort(&s); if (!rc) break; bmiHeader.biBitCount = s;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biCompression = i;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biSizeImage = i;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biXPelsPerMeter = i;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biYPelsPerMeter = i;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biClrUsed = i;
    rc = file.ReadInt(&i);   if (!rc) break; bmiHeader.biClrImportant = i;
    break;
  }


  if ( rc ) 
  {
    bmiHeader.biSize = sizeof(bmiHeader);
    const size_t sizeof_palette = ON_WindowsBitmapHelper_SizeofPalette(bmiHeader.biClrUsed, bmiHeader.biBitCount );
    const size_t sizeof_image   = bmiHeader.biSizeImage;
    m_bmi = ON_WindowsBitmapHelper_AllocBMI(sizeof_palette,sizeof_image);
    if ( !m_bmi )
    {
      rc = false;
    }
    else 
    {
      m_bFreeBMI = 1;
      m_bmi->bmiHeader = bmiHeader;
      m_bmi->bmiHeader.biSize = sizeof(m_bmi->bmiHeader);
      const int color_count = ON_WindowsBitmapHelper_PaletteColorCount(bmiHeader.biClrUsed, bmiHeader.biBitCount );
      if ( sizeof_image > 0 )
        m_bits = (unsigned char*)&m_bmi->bmiColors[color_count];
      size_t sizeof_buffer = 0;
      rc = file.ReadCompressedBufferSize( &sizeof_buffer );
      if (rc)
      {
        const size_t sizeof_colors = color_count*sizeof(*m_bmi->bmiColors);
        if (    sizeof_buffer == sizeof_colors
             || sizeof_buffer == sizeof_colors + sizeof_image
           ) 
        {
          // palette and image bits are compressed into one or two chunks
          rc = file.ReadCompressedBuffer( sizeof_buffer, m_bmi->bmiColors, &bFailedCRC );
          if ( rc && sizeof_image > 0 && sizeof_buffer == sizeof_colors )
          {
            // 28 July 2003
            //     Added support for reading non-contiguous bitmaps
            sizeof_buffer = 0;
            rc = file.ReadCompressedBufferSize( &sizeof_buffer );
            if (rc)
            {
              if ( sizeof_buffer == sizeof_image )
              {
                // image bits are compressed into a separatechunk
                rc = file.ReadCompressedBuffer( sizeof_buffer, &m_bmi->bmiColors[color_count], &bFailedCRC );
              }
              else
              {
                ON_ERROR("ON_WindowsBitmap::ReadCompressed() image bits buffer size mismatch\n");
                rc = false;
              }
            }
          }
        }
        else
        {
          ON_ERROR("ON_WindowsBitmap::ReadCompressed() buffer size mismatch\n");
          rc = false;
        }
      }
    }
  }
  return rc;
}

bool ON_WindowsBitmap::IsContiguous() const
{
  bool rc = false;
  if ( 0 != m_bmi && 0 != m_bits && m_bmi->bmiHeader.biSizeImage > 0 )
  {
    // p1 points to the first byte after the color palette.
    unsigned char* p1 = (unsigned char*)&m_bmi->bmiColors[PaletteColorCount()];
    rc = ( m_bits == p1 );
  }
  return rc;
}

#if defined(ON_OS_WINDOWS_GDI)

#pragma message( " --- OpenNURBS including Windows BITMAPINFO support in ON_WindowsBitmap" )

ON_WindowsBitmap::ON_WindowsBitmap( const BITMAPINFO& src )
                 : m_bmi(0), m_bits(0), m_bFreeBMI(0)
{
  *this = src;
}

ON_WindowsBitmap& ON_WindowsBitmap::operator=( const BITMAPINFO& src )
{
  Internal_Destroy();
  ON_Bitmap::operator=(ON_Bitmap::Unset);

  int color_count = ON_WindowsBitmapHelper_PaletteColorCount(src.bmiHeader.biClrUsed, src.bmiHeader.biBitCount );
  Create(&src,(const unsigned char*)(&src.bmiColors[color_count]),true);
  return *this;
}



ON_WindowsBitmap::ON_WindowsBitmap( const BITMAPINFO* src )
{
  if ( 0 != src )
  {
    int color_count = ON_WindowsBitmapHelper_PaletteColorCount(src->bmiHeader.biClrUsed, src->bmiHeader.biBitCount );
    Create(src,(const unsigned char*)(&src->bmiColors[color_count]),false);
  }
}

#endif

#if defined ON_OS_WINDOWS_GDI
bool ON_WindowsBitmap::Create( const BITMAPINFO* bmi, const unsigned char* bits, bool bCopy )
#else
bool ON_WindowsBitmap::Create( const ON_WindowsBITMAPINFO* bmi, const unsigned char* bits, bool bCopy )
#endif
{
  Internal_Destroy();

  bool rc = false;

  m_bFreeBMI = 0;
  m_bmi = 0;
  m_bits = 0;

  if ( 0 != bmi )
  {
    if ( bCopy )
    {
      // allocate a contiguous Windows device independent bitmap
      const size_t sizeof_palette = ON_WindowsBitmapHelper_SizeofPalette(bmi->bmiHeader.biClrUsed, bmi->bmiHeader.biBitCount );
      const int sizeof_image   = bmi->bmiHeader.biSizeImage;
      m_bmi = ON_WindowsBitmapHelper_AllocBMI( sizeof_palette, (bCopy?sizeof_image:0) );
      if ( 0 != m_bmi )
      {
        rc = true;
        m_bFreeBMI = 1; // ~ON_WindowsBitmap will free the m_bmi pointer
        m_bmi->bmiHeader = bmi->bmiHeader;
        m_bmi->bmiHeader.biSize = sizeof(m_bmi->bmiHeader);
        int color_count = ON_WindowsBitmapHelper_PaletteColorCount(bmi->bmiHeader.biClrUsed, bmi->bmiHeader.biBitCount );
        if ( color_count > 0 )
        {
          memcpy( &m_bmi->bmiColors[0], &bmi->bmiColors[0], color_count*sizeof(m_bmi->bmiColors[0]) );
        }
        if ( bCopy && sizeof_image > 0 )
        {
          m_bits = (unsigned char*)(&m_bmi->bmiColors[color_count]);
          if ( 0 != bits )
            memcpy( m_bits, bits, sizeof_image );
          else
            memset( m_bits, 0, sizeof_image );
        }
      }
    }
    else
    {
      // share BITMAPINFO memory
      rc = true;
#if defined ON_OS_WINDOWS_GDI
      m_bmi = const_cast<BITMAPINFO*>(bmi);
#else
      m_bmi = const_cast<ON_WindowsBITMAPINFO*>(bmi);
#endif
      m_bits = const_cast<unsigned char*>(bits);
    }
  }

  return rc;
}

#if !defined(ON_OS_WINDOWS_GDI)
bool ON_WindowsBitmap::Create(const struct ON_WindowsBITMAPINFO* src)
{
  bool rc = false;
  *this = ON_WindowsBitmap::Unset;
  m_bFreeBMI = 0;
  m_bmi = 0;
  m_bits = 0;
  if ( 0 != src )
  {
    rc = true;
    int color_count = ON_WindowsBitmapHelper_PaletteColorCount(src->bmiHeader.biClrUsed, src->bmiHeader.biBitCount );
    m_bmi = (struct ON_WindowsBITMAPINFO*)src;
    m_bits = (unsigned char*)(&src->bmiColors[color_count]);
  }
  return rc;
}
#endif

////////////////////////////////////////////////////////////////////////////////
//
// ON_EmbeddedBitmap - used to embed bitmaps in 3dm archives
//

ON_EmbeddedBitmap::~ON_EmbeddedBitmap()
{
  Internal_Destroy();
}

ON_EmbeddedBitmap::ON_EmbeddedBitmap(const ON_EmbeddedBitmap& src)
  : ON_Bitmap(src)
{
  Internal_Copy(src);
}

ON_EmbeddedBitmap& ON_EmbeddedBitmap::operator=(const ON_EmbeddedBitmap& src)
{
  if (this != &src)
  {
    Internal_Destroy();
    ON_Bitmap::operator=(src);
    Internal_Copy(src);
  }
  return *this;
}

void ON_EmbeddedBitmap::Internal_Copy(
  const ON_EmbeddedBitmap& src
  )
{
  if (nullptr != src.m_buffer && src.m_sizeof_buffer > 0)
  {
    Create(src.m_sizeof_buffer);
    if (nullptr != m_buffer && m_sizeof_buffer == src.m_sizeof_buffer)
    {
      memcpy(const_cast<void*>(m_buffer), src.m_buffer, m_sizeof_buffer);
      m_buffer_crc32 = src.m_buffer_crc32;
    }
  }
}

void ON_EmbeddedBitmap::Internal_Destroy()
{
  void* p
    = (m_managed_buffer && m_sizeof_buffer > 0)
    ? const_cast<void*>(m_buffer)
    : nullptr;
  m_buffer = nullptr;
  m_sizeof_buffer = 0;
  m_managed_buffer = false;
  m_buffer_crc32 = 0;
  if (nullptr != p)
    onfree(p);
}


void ON_EmbeddedBitmap::Create( size_t sizeof_buffer )
{
  Internal_Destroy();
  if ( sizeof_buffer > 0 )
  {
    m_buffer = onmalloc(sizeof_buffer);
    if ( 0 != m_buffer )
    {
      m_sizeof_buffer = sizeof_buffer;
      m_managed_buffer = true;
    }
  }
}

bool ON_EmbeddedBitmap::IsValid( ON_TextLog* text_log ) const
{
  if ( 0 == m_buffer )
  {
    if ( 0 != text_log )
      text_log->Print("ON_EmbeddedBitmap m_buffer = 0\n");
    return false;
  }
  return true;
}

bool ON_EmbeddedBitmap::Write(ON_BinaryArchive& archive) const
{
  return Internal_WriteV5(archive);
}

bool ON_EmbeddedBitmap::Internal_WriteV5( ON_BinaryArchive& file ) const 
{
  bool rc = false;
  for (;;)
  {
    if (!file.Write3dmChunkVersion(1, 1))
      break;

    if (!file.WriteString( FileReference().FullPath() ) )
      break;

    if (!file.WriteInt(m_buffer_crc32))
      break;

    const int i = 1; // 1 = compressed
    if (!file.WriteInt(i))
      break;

    if (!file.WriteCompressedBuffer(m_sizeof_buffer, m_buffer))
      break;

    // version 1.1 added id and name
    if (!file.WriteUuid(Id()))
      break;
    if (!file.WriteString(Name()))
      break;

    rc = true;
    break;
  }

  return rc;
}

bool ON_EmbeddedBitmap::Read(ON_BinaryArchive& archive)
{
  return Internal_ReadV5(archive);
}

bool ON_EmbeddedBitmap::Internal_ReadV5( ON_BinaryArchive& file ) 
{
  Internal_Destroy();

  bool rc = false;
  for (;;)
  {
    int major_version = 0;
    int minor_version = 0;
    if (!file.Read3dmChunkVersion(&major_version, &minor_version))
      break;

    if (1 != major_version)
      break;

    ON_wString file_name;
    if (!file.ReadString(file_name))
      break;
    ON_FileReference file_reference;
    if (ON_FileSystemPath::IsRelativePath(file_name))
      file_reference.SetRelativePath(file_name);
    else
      file_reference.SetFullPath(file_name, false);
    SetFileReference(file_reference);

    if (!file.ReadInt(&m_buffer_crc32))
      break;

    int i = -1;
    if (!file.ReadInt(&i))
      break;
    if (0 == i)
    {
      // uncompressed
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4996)
#pragma ON_PRAGMA_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")
      if (!file.ReadSize(&m_sizeof_buffer))
        break;
#pragma ON_PRAGMA_WARNING_POP
      void* buffer = nullptr;
      if (m_sizeof_buffer > 0)
      {
        buffer = onmalloc(m_sizeof_buffer);
        m_managed_buffer = true;
      }
      if (!file.ReadByte(m_sizeof_buffer, buffer))
      {
        if (nullptr != buffer)
          onfree(buffer);
        break;
      }
      m_buffer = buffer;
    }
    else if (1 == i)
    {
      // compressed
      if (!file.ReadCompressedBufferSize(&m_sizeof_buffer))
        break;
      void* buffer = nullptr;
      if (m_sizeof_buffer > 0)
      {
        buffer = onmalloc(m_sizeof_buffer);
      }
      bool bFailedCRC = false;
      if (!file.ReadCompressedBuffer(m_sizeof_buffer, buffer, &bFailedCRC))
      {
        if (nullptr != buffer)
          onfree(buffer);
        break;
      }
      m_buffer = buffer;
      m_managed_buffer = true;
    }
    else
    {
      // invalid 
      break;
    }

    if (minor_version < 1)
    {
      rc = true;
      break;
    }    

    // version 1.1 added id and name
    ON_UUID bitmap_id = ON_nil_uuid;
    if (!file.ReadUuid(bitmap_id))
      break;
    SetId(bitmap_id);

    ON_wString bitmap_name;
    if (!file.ReadString(bitmap_name))
      break;
    SetName(bitmap_name);

    rc = true;
    break;
  }

  if (rc && IdIsNil())
    SetId(); // older formats had nil ids - modern times require unique component ids.

  return rc;
}

size_t ON_EmbeddedBitmap::SizeofImage() const
{
  return m_sizeof_buffer;
}

unsigned char* ON_EmbeddedBitmap::Bits(int scan_line_index) 
{
  return const_cast<unsigned char*>((0 == scan_line_index) ? static_cast<const unsigned char*>(m_buffer) : nullptr);
}

const unsigned char* ON_EmbeddedBitmap::Bits(int scan_line_index) const
{
  return (0 == scan_line_index) ? static_cast<const unsigned char*>(m_buffer) : nullptr;
}

unsigned int ON_Bitmap::SizeOf() const
{
  const size_t sizeof_baseclass = ON_ModelComponent::SizeOf();
  const size_t sizeof_class = sizeof(*this) - sizeof(ON_ModelComponent);
  return (unsigned int)(sizeof_baseclass + sizeof_class);
}

unsigned int ON_EmbeddedBitmap::SizeOf() const
{
  const size_t sizeof_baseclass = ON_Bitmap::SizeOf();
  const size_t sizeof_class = sizeof(*this) - sizeof(ON_Bitmap);
  return (unsigned int)(sizeof_baseclass + sizeof_class + m_sizeof_buffer);
}

unsigned int ON_WindowsBitmap::SizeOf() const
{
  const size_t sizeof_baseclass = ON_Bitmap::SizeOf();
  const size_t sizeof_class = sizeof(*this) - sizeof(ON_Bitmap);
  return (unsigned int)(sizeof_baseclass + sizeof_class + SizeofImage());
}

