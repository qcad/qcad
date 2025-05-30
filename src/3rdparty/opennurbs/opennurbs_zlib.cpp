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

#include "opennurbs_zlib.h"

// RH-86025, RH3DM-179, 2025-02-14, Pierre:
// We only really need the #pragma comment(lib, "path") to work when we are using
// MSVC and the Microsoft linker, but not defining include dirs in build properties.
// Other compilers do not recognize this pragma and instead use build properties to link to libs.
// ON_CMAKE_BUILD should be renamed "ON_NOT_USING_MSVC_LINK_LIB_PRAGMA"
// This whole thing should be reworked so MSVC builds also use build properties,
// instead of this non-portable pragma.
#if defined(ON_COMPILER_MSC) && !defined(ON_CMAKE_BUILD)

#if !defined(OPENNURBS_ZLIB_LIB_DIR)

#include "opennurbs_input_libsdir.h"

#if defined(OPENNURBS_INPUT_LIBS_DIR)
// Typically, OPENNURBS_LIB_DIR is defined in opennurbs_msbuild.Cpp.props
#define OPENNURBS_ZLIB_LIB_DIR OPENNURBS_INPUT_LIBS_DIR
#else
// Define OPENNURBS_ZLIB_LIB_DIR to be the directory containing zlib.lib
#error You must define OPENNURBS_ZLIB_LIB_DIR
#endif  // defined(OPENNURBS_INPUT_LIBS_DIR)



#if defined(_LIB) && defined(_MT) && !defined(_DLL)
// using Microsoft statically linked C-runtime
#pragma message ( "Linking with zlib_mt.lib in " OPENNURBS_PP2STR(OPENNURBS_ZLIB_LIB_DIR) )
#pragma comment(lib, "\"" OPENNURBS_ZLIB_LIB_DIR "/" "zlib_mt.lib" "\"")
#else
// using Microsoft DLL C-runtime
#pragma message ( "Linking with zlib.lib in " OPENNURBS_PP2STR(OPENNURBS_ZLIB_LIB_DIR) )
#pragma comment(lib, "\"" OPENNURBS_ZLIB_LIB_DIR "/" "zlib.lib" "\"")
#endif  // defined(_LIB) && defined(_MT) && !defined(_DLL)

#endif  // !defined(OPENNURBS_ZLIB_LIB_DIR)

#endif  // defined(ON_COMPILER_MSC) && !defined(ON_CMAKE_BUILD)

// compressed buffer I/O uses zlib 1.1.3 inflate()/deflate()
class ON_CompressorImplementation
{
public:
  ON_CompressorImplementation()
    : m_mode(ON::archive_mode::unset_archive_mode)
  {
    ClearStream();
  }

  void ClearStream()
  {
    memset(&m_strm, 0, sizeof(z_stream));
  }

  ON::archive_mode m_mode; // ON::archive_mode::read = read and inflate,  ON::archive_mode::write = deflate and write
  enum 
  {
    sizeof_x_buffer = 16384
  };
  unsigned char    m_buffer[sizeof_x_buffer];
  z_stream         m_strm;
};

class ON_CompressorImplementation& ON_BinaryArchive::Compressor()
{
  if (nullptr == m_compressor)
    m_compressor = (class ON_CompressorImplementation*)oncalloc(1, sizeof(*m_compressor));
  return *m_compressor;
}


bool ON_BinaryArchive::WriteCompressedBuffer(
        size_t sizeof__inbuffer,  // sizeof uncompressed input data
        const void* inbuffer  // uncompressed input data
        )
{
  size_t compressed_size = 0;
  bool rc = false;

  if ( !WriteMode() )
    return false;
  if ( sizeof__inbuffer > 0 && 0 == inbuffer )
    return false;
  if (sizeof__inbuffer > UINT32_MAX)
    return false;

  // number of bytes of uncompressed data
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4996)
#pragma ON_PRAGMA_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")
  if (!WriteSize(sizeof__inbuffer))
    return false;
#pragma ON_PRAGMA_WARNING_POP

  if ( 0 == sizeof__inbuffer )
    return true;

  // 32 bit crc of uncompressed data
  const unsigned int buffer_crc = ON_CRC32( 0, sizeof__inbuffer, inbuffer );
  if (!WriteInt(buffer_crc))
    return false;

  unsigned char method
    = (m_bUseBufferCompression && sizeof__inbuffer > 128)
    ? 1
    : 0;

  if ( method ) {
    if ( !CompressionInit() ) {
      CompressionEnd();
      method = 0;
    }
  }
  if ( !WriteChar(method) )
    return false;

  switch ( method )
  {
  case 0: // uncompressed
    rc = WriteByte(sizeof__inbuffer, inbuffer);
    if ( rc )
    {
      compressed_size = sizeof__inbuffer;
    }
    break;

  case 1: // compressed
    compressed_size = WriteDeflate( sizeof__inbuffer, inbuffer );
    rc = ( compressed_size > 0 ) ? true : false;
    CompressionEnd();
    break;
  }


  return rc;
}

bool ON_BinaryArchive::ReadCompressedBufferSize( size_t* sizeof__outbuffer )
{
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4996)
#pragma ON_PRAGMA_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")
  return ReadSize(sizeof__outbuffer);
#pragma ON_PRAGMA_WARNING_POP
}

bool ON_BinaryArchive::ReadCompressedBuffer( // read and uncompress
  size_t sizeof__outbuffer,  // sizeof of uncompressed buffer to read
  void* outbuffer,           // uncompressed output data returned here
  bool* bFailedCRC
  )
{
  bool rc = false;
  unsigned int buffer_crc0 = 0;
  unsigned int buffer_crc1 = 0;
  char method = 0;

  if ( bFailedCRC)
    *bFailedCRC = false;
  if ( !ReadMode() )
    return false;
  if ( 0 == sizeof__outbuffer )
    return true;
  if ( 0 == outbuffer )
    return false;

  if ( !ReadInt(&buffer_crc0) ) // 32 bit crc of uncompressed buffer
    return false;

  if ( !ReadChar(&method) )
    return false;

  if ( method != 0 && method != 1 )
    return false;

  switch(method)
  {
  case 0: // uncompressed
    rc = ReadByte(sizeof__outbuffer, outbuffer);
    break;
  case 1: // compressed
    rc = CompressionInit();
    if (rc)
      rc = ReadInflate( sizeof__outbuffer, outbuffer );
    CompressionEnd();
    break;
  }

  if (rc ) 
  {
    buffer_crc1 = ON_CRC32( 0, sizeof__outbuffer, outbuffer );
    if ( buffer_crc1 != buffer_crc0 ) 
    {
      ON_ERROR("ON_BinaryArchive::ReadCompressedBuffer() crc error");
      if ( bFailedCRC )
        *bFailedCRC = true;
    }
  }

  return rc;
}

size_t ON_BinaryArchive::WriteDeflate( // returns number of bytes written
        size_t sizeof___inbuffer,  // sizeof uncompressed input data ( > 0 )
        const void* in___buffer     // uncompressed input data ( != nullptr )
        )
{
  /*
    In "standard" (in 2005) 32 bit code
    
      sizeof(int)     = 4 bytes, 
      sizeof(long)    = 4 bytes,
      sizeof(pointer) = 4 bytes, and
      sizeof(size_t)  = 4 bytes.

    Theoretically I don't need to use multiple input buffer
    chunks in case.  But I'm paranoid and I will use multiple 
    input chunks when sizeof_inbuffer > 2GB in order to dodge
    any potential zlib signed verses unsigned compare bugs or
    having a signed int i++ roll over to a negative number.

    In "standard" code that has 64 bit pointers
    
      sizeof(int)     >= 4 bytes, (it's 4 on MS VS2005) 
      sizeof(long)    >= 4 bytes, (it's 4 on MS VS2005)
      sizeof(pointer)  = 8 bytes, and
      sizeof(size_t)   = 8 bytes.

    So, I'm going to assume the ints and longs in the zlib code 
    are 4 bytes, but I could have sizeof_inbuffer > 4GB.
    This means I have to use multiple input buffer chunks.  
    In this case I still use multiple input chunks when 
    sizeof_inbuffer > 2GB in order to dodge any potential zlib
    signed verses unsigned compare bugs or having a signed
    int i++ roll over to a negative number.

    So, I set
    
       const size_t max_avail = (largest signed 4 byte integer - 15)
    
    and feed inflate and deflate buffers with size <= max_avail.


    This information below is from the zlib 1.2.3 FAQ.  

    32. Can zlib work with greater than 4 GB of data?

        Yes. inflate() and deflate() will process any amount of data correctly.
        Each call of inflate() or deflate() is limited to input and output chunks
        of the maximum value that can be stored in the compiler's "unsigned int"
        type, but there is no limit to the number of chunks. Note however that the
        strm.total_in and strm_total_out counters may be limited to 4 GB. These
        counters are provided as a convenience and are not used internally by
        inflate() or deflate(). The application can easily set up its own counters
        updated after each call of inflate() or deflate() to count beyond 4 GB.
        compress() and uncompress() may be limited to 4 GB, since they operate in a
        single call. gzseek() and gztell() may be limited to 4 GB depending on how
        zlib is compiled. See the zlibCompileFlags() function in zlib.h.

        The word "may" appears several times above since there is a 4 GB limit
        only if the compiler's "long" type is 32 bits. If the compiler's "long"
        type is 64 bits, then the limit is 16 exabytes.
  */

  const size_t max_avail = 0x7FFFFFF0;

  //  Compressed information is saved in a chunk.
  bool rc = BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,0);
  if ( !rc )
    return false;

  class ON_CompressorImplementation& m_zlib(Compressor());

  size_t out__count = 0;
  int zrc = Z_OK;

  size_t my_avail_in = sizeof___inbuffer;
  unsigned char* my_next_in = (unsigned char*)in___buffer;

  size_t d = my_avail_in;
  if ( d > max_avail )
    d = max_avail;
  m_zlib.m_strm.next_in = my_next_in;
  m_zlib.m_strm.avail_in = (unsigned int)d;
  my_avail_in -= d;
  my_next_in  += d;

  m_zlib.m_strm.next_out = m_zlib.m_buffer;
  m_zlib.m_strm.avail_out = m_zlib.sizeof_x_buffer;

  // counter guards prevents infinite loops if there is a bug in zlib return codes.
  int counter = 512; 
  int flush = Z_NO_FLUSH;

  size_t deflate_output_count = 0;

  while( rc && counter > 0 ) 
  {
    // Call zlib's deflate function.  It can either process
    // more input from m_zlib.m_strm.next_in[], create more
    // compressed output in m_zlib.m_strm.next_out[], or do both.
    if ( 0 == my_avail_in && 0 == m_zlib.m_strm.avail_in )
    {
      // no uncompressed input is left - switch to finish mode
      flush = Z_FINISH;
    }
    zrc = z_deflate(&m_zlib.m_strm, flush);
    if ( zrc < 0 ) 
    {
      // Something went haywire - bail out.
      ON_ERROR("ON_BinaryArchive::WriteDeflate - z_deflate failure");
      rc = false;
      break;
    }

    deflate_output_count = m_zlib.sizeof_x_buffer - m_zlib.m_strm.avail_out;
    if ( deflate_output_count > 0 ) 
    {
      // The last call to deflate created output.  Send
      // this output to the archive.
      rc = WriteChar( deflate_output_count, m_zlib.m_buffer );
      if ( !rc )
        break;
      out__count += deflate_output_count;
      m_zlib.m_strm.next_out = m_zlib.m_buffer;
      m_zlib.m_strm.avail_out = m_zlib.sizeof_x_buffer;
    }

    if ( Z_FINISH == flush && Z_STREAM_END == zrc )
    {
      // no input left, all pending compressing is finished,
      // and all compressed output has been returned.
      break;
    }

    if ( my_avail_in > 0 && m_zlib.m_strm.avail_in < max_avail )
    {
      // inbuffer[] had more than max_zlib_avail_in bytes in it
      // and I am feeding inbuffer[] to deflate in smaller chunks
      // that the 32 bit integers in the zlib code can handle.
      if ( 0 == m_zlib.m_strm.avail_in || 0 == m_zlib.m_strm.next_in )
      {
        // The call to deflate() used up all the input 
        // in m_zlib.m_strm.next_in[].  I can feed it another chunk
        // from inbuffer[]
        d = my_avail_in;
        if ( d > max_avail )
          d = max_avail;
        m_zlib.m_strm.next_in = my_next_in;
        m_zlib.m_strm.avail_in = (unsigned int)d; 
      }
      else
      {
        // The call to deflate left some input in m_zlib.m_strm.next_in[],
        // but I can increase m_zlib.m_strm.avail_in.
        d =  max_avail - m_zlib.m_strm.avail_in;
        if ( d > my_avail_in )
          d = my_avail_in;
        m_zlib.m_strm.avail_in += (unsigned int)d;
      }

      my_avail_in -= d;
      my_next_in  += d;
    }
    else if ( 0 == deflate_output_count )
    {
      // no buffer changes this time
      counter--;
    }

    if ( zrc != Z_OK )
    {
      break;
    }
  }

  if ( !EndWrite3dmChunk() )
  {
    rc = false;
  }

  if ( 0 == counter )
  {
    rc = false;
  }

  return (rc ? out__count : 0);
}


bool ON_BinaryArchive::ReadInflate(
        size_t sizeof___outbuffer,  // sizeof uncompressed data
        void* out___buffer          // buffer for uncompressed data
        )
{
  const size_t max_avail = 0x7FFFFFF0; // See max_avail comment in ON_BinaryArchive::WriteInflate

  size_t sizeof__inbuffer = 0;
  void* in___buffer = 0;
  bool rc = false;

  // read compressed buffer from 3dm archive
  bool bValidCompressedBuffer = false;
  {
    ON__UINT32 tcode = 0;
    ON__INT64  big_value = 0;
    rc = BeginRead3dmBigChunk(&tcode,&big_value );
    if (!rc)
    {
      if ( 0 != out___buffer && sizeof___outbuffer > 0 )
        memset(out___buffer,0,sizeof___outbuffer);
      return false;
    }
    if (   tcode == TCODE_ANONYMOUS_CHUNK 
        && big_value > 4 
        && sizeof___outbuffer > 0 
        && 0 != out___buffer )
    {
      // read compressed buffer from the archive
      sizeof__inbuffer = (size_t)(big_value-4); // the last 4 bytes in this chunk are a 32 bit crc
      in___buffer = onmalloc(sizeof__inbuffer);
      if ( !in___buffer )
      {
        rc = false;
      }
      else
      {
        rc = ReadByte( sizeof__inbuffer, in___buffer );
      }
    }
    else
    {
      // Either I have the wrong chunk, or the input
      // parameters are bogus. 
      rc = false;
    }
    unsigned int c0 = BadCRCCount();
    if ( !EndRead3dmChunk() )
    {
      rc = false;
    }
    bValidCompressedBuffer = ( BadCRCCount() > c0 )
                           ? false
                           : rc;
  }

  if ( !bValidCompressedBuffer && 0 != out___buffer && sizeof___outbuffer > 0 )
  {
    // Decompression will fail, but we might get something valid
    // at the start if the data flaw was near the end of the buffer.
    memset(out___buffer,0,sizeof___outbuffer);
  }

  if ( !rc )
  {
    if ( in___buffer )
    {
      onfree(in___buffer);
      in___buffer = 0;
    }
    return false;
  }

  class ON_CompressorImplementation& m_zlib(Compressor());

  int zrc = -1;

  // set up zlib in buffer
  unsigned char* my_next_in = (unsigned char*)in___buffer;
  size_t my_avail_in = sizeof__inbuffer;

  size_t d = my_avail_in;
  if ( d > max_avail )
    d = max_avail;
  m_zlib.m_strm.next_in  = my_next_in;
  m_zlib.m_strm.avail_in = (unsigned int)d;
  my_next_in  += d;
  my_avail_in -= d;

  // set up zlib out buffer
  unsigned char* my_next_out = (unsigned char*)out___buffer;
  size_t my_avail_out = sizeof___outbuffer;

  d = my_avail_out;
  if ( d > max_avail )
    d = max_avail;
  m_zlib.m_strm.next_out  = my_next_out;
  m_zlib.m_strm.avail_out = (unsigned int)d;
  my_next_out  += d;
  my_avail_out -= d;

  // counter guards against infinite loop if there are
  // bugs in zlib return codes
  int counter = 512;
  int flush = Z_NO_FLUSH;

  while ( rc && counter > 0 )
  {
    // Call zlib's inflate function.  It can either process
    // more input from m_zlib.m_strm.next_in[], create more
    // uncompressed output in m_zlib.m_strm.next_out[], or do both.
    if ( 0 == my_avail_in && 0 == m_zlib.m_strm.avail_in )
    {
      // no compressed input is left - switch to finish mode
      flush = Z_FINISH;
    }
    zrc = z_inflate( &m_zlib.m_strm, flush );
    if ( zrc < 0 ) 
    {
      // Something went haywire - bail out.
      ON_ERROR("ON_BinaryArchive::ReadInflate - z_inflate failure");
      rc = false;
      break;
    }

    if ( Z_FINISH == flush && Z_STREAM_END == zrc )
    {
      // no input left, all pending decompression is finished,
      // and all decompressed output has been returned.
      break;
    }

    d = 0;
    if ( my_avail_in > 0 && m_zlib.m_strm.avail_in < max_avail )
    {
      if ( 0 == m_zlib.m_strm.avail_in || 0 == m_zlib.m_strm.next_in )
      {
        // The call to inflate() used up all the input 
        // in m_zlib.m_strm.next_in[].  I can feed it another chunk
        // from inbuffer[]
        d = my_avail_in;
        if ( d > max_avail )
          d = max_avail;
        m_zlib.m_strm.next_in  = my_next_in;
        m_zlib.m_strm.avail_in = (unsigned int)d; 
      }
      else
      {
        // The call to inflate() left some input in m_zlib.m_strm.next_in[],
        // but I can increase m_zlib.m_strm.avail_in.
        d =  max_avail - m_zlib.m_strm.avail_in;
        if ( d > my_avail_in )
          d = my_avail_in;
        m_zlib.m_strm.avail_in += (unsigned int)d;
      }
      my_next_in  += d;
      my_avail_in -= d;
    }

    if ( my_avail_out > 0 && m_zlib.m_strm.avail_out < max_avail )
    {
      // increase m_zlib.m_strm.next_out[] buffer
      if ( 0 == m_zlib.m_strm.avail_out || 0 == m_zlib.m_strm.next_out )
      {
        d = my_avail_out;
        if ( d > max_avail )
          d = max_avail;
        m_zlib.m_strm.next_out  = my_next_out;
        m_zlib.m_strm.avail_out = (unsigned int)d;
      }
      else
      {
        d = max_avail - m_zlib.m_strm.avail_out;
        if ( d > my_avail_out )
          d = my_avail_out;
        m_zlib.m_strm.avail_out += ((unsigned int)d);
      }
      my_next_out  += d;
      my_avail_out -= d;
    }
    else if ( 0 == d )
    {
      // no buffer changes
      counter--;
    }
  }

  if (in___buffer )
  {
    onfree(in___buffer);
    in___buffer = 0;
  }

  if ( 0 == counter )
  {
    rc = false;
  }

  return rc;
}

bool ON_BinaryArchive::CompressionInit()
{
  // inflateInit() and deflateInit() are in zlib 1.3.3
  bool rc = false;
  if ( WriteMode() ) 
  {
    class ON_CompressorImplementation& m_zlib(Compressor());

    rc = (m_zlib.m_mode == ON::archive_mode::write) ? true : false;
    if ( !rc ) {
      CompressionEnd();
      if ( Z_OK == deflateInit( &m_zlib.m_strm, Z_BEST_COMPRESSION ) ) {
        m_zlib.m_mode = ON::archive_mode::write;
        rc = true;
      }
      else {
        memset(&m_zlib.m_strm,0,sizeof(m_zlib.m_strm));
      }
    }
  }
  else if ( ReadMode() ) 
  {
    class ON_CompressorImplementation& m_zlib(Compressor());

    rc = (m_zlib.m_mode == ON::archive_mode::read) ? true : false;
    if ( !rc ) {
      CompressionEnd();
      if ( Z_OK == inflateInit( &m_zlib.m_strm ) ) {
        m_zlib.m_mode = ON::archive_mode::read;
        rc = true;
      }
      else {
        memset(&m_zlib.m_strm,0,sizeof(m_zlib.m_strm));
      }
    }
  }
  else {
    CompressionEnd();
  }
  return rc;
}

void ON_BinaryArchive::CompressionEnd()
{
  // inflateEnd() and deflateEnd() are in zlib 1.3.3
  if (0 != m_compressor)
  {
    switch (m_compressor->m_mode)
    {
    case ON::archive_mode::read:
    case ON::archive_mode::read3dm:
      inflateEnd(&m_compressor->m_strm);
      break;
    case ON::archive_mode::write:
    case ON::archive_mode::write3dm:
      deflateEnd(&m_compressor->m_strm);
      break;
    default: // to quiet lint
      break;
    }
    m_compressor->ClearStream();
    m_compressor->m_mode = ON::archive_mode::unset_archive_mode;
  }
}



struct ON_CompressedBufferHelper
{
  int m_action; // 1 = compress, 2 = uncompress
  enum
  {
    sizeof_x_buffer = 16384
  };
  unsigned char    m_buffer[sizeof_x_buffer];
  z_stream         m_strm;
  size_t           m_buffer_compressed_capacity;
};

ON_CompressedBuffer::ON_CompressedBuffer()
                    : m_sizeof_uncompressed(0),
                      m_sizeof_compressed(0),
                      m_crc_uncompressed(0),
                      m_crc_compressed(0),
                      m_method(0),
                      m_sizeof_element(0),
                      m_buffer_compressed_capacity(0),
                      m_buffer_compressed(0)
{
}

ON_CompressedBuffer::~ON_CompressedBuffer()
{
  Destroy();
}

ON_CompressedBuffer::ON_CompressedBuffer(const ON_CompressedBuffer& src)
                    : m_sizeof_uncompressed(0),
                      m_sizeof_compressed(0),
                      m_crc_uncompressed(0),
                      m_crc_compressed(0),
                      m_method(0),
                      m_sizeof_element(0),
                      m_buffer_compressed_capacity(0),
                      m_buffer_compressed(0)
{
  *this = src;
}

ON_CompressedBuffer& ON_CompressedBuffer::operator=(const ON_CompressedBuffer& src)
{
  if ( this != &src )
  {
    Destroy();
    if( src.m_buffer_compressed && src.m_sizeof_compressed > 0 )
    {
      m_sizeof_uncompressed = src.m_sizeof_uncompressed;
      m_sizeof_compressed   = src.m_sizeof_compressed;
      m_crc_uncompressed    = src.m_crc_uncompressed;
      m_crc_compressed      = src.m_crc_compressed;
      m_method              = src.m_method;
      m_sizeof_element      = src.m_sizeof_element;

      m_buffer_compressed = onmalloc(m_sizeof_compressed);
      if( m_buffer_compressed )
      {
        m_buffer_compressed_capacity = m_sizeof_compressed;
        memcpy(m_buffer_compressed,src.m_buffer_compressed,m_sizeof_compressed);
      }
    }
  }
  return *this;
}

bool ON_CompressedBuffer::Write( ON_BinaryArchive& binary_archive ) const
{
  bool rc = binary_archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);
  if ( !rc )
    return false;

  for(;;)
  {
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4996)
#pragma ON_PRAGMA_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")
    rc = binary_archive.WriteSize(m_sizeof_uncompressed);
    if (!rc)
      break;
    rc = binary_archive.WriteSize((m_buffer_compressed && m_sizeof_compressed>0) ? m_sizeof_compressed : 0);
    if (!rc)
      break;
#pragma ON_PRAGMA_WARNING_POP
    rc = binary_archive.WriteInt(m_crc_uncompressed);
    if (!rc)
      break;
    rc = binary_archive.WriteInt(m_crc_compressed);
    if (!rc)
      break;
    rc = binary_archive.WriteInt(m_method);
    if (!rc)
      break;
    rc = binary_archive.WriteInt(m_sizeof_element);
    if (!rc)
      break;
    if ( m_buffer_compressed && m_sizeof_compressed > 0 )
    {
      rc = binary_archive.WriteByte(m_sizeof_compressed,m_buffer_compressed);
      if (!rc)
        break;
    }
    break;
  }

  if ( !binary_archive.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

bool ON_CompressedBuffer::Read( ON_BinaryArchive& binary_archive )
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = binary_archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if ( !rc )
    return false;

  for(;;)
  {
    rc = ( 1 == major_version );
    if ( !rc ) 
      break;
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC(4996)
#pragma ON_PRAGMA_WARNING_DISABLE_CLANG("-Wdeprecated-declarations")
    rc = binary_archive.ReadSize(&m_sizeof_uncompressed);
    if (!rc)
      break;
    rc = binary_archive.ReadSize(&m_sizeof_compressed);
    if (!rc)
      break;
#pragma ON_PRAGMA_WARNING_PUSH
    rc = binary_archive.ReadInt(&m_crc_uncompressed);
    if (!rc)
      break;
    rc = binary_archive.ReadInt(&m_crc_compressed);
    if (!rc)
      break;
    rc = binary_archive.ReadInt(&m_method);
    if (!rc)
      break;
    rc = binary_archive.ReadInt(&m_sizeof_element);
    if (!rc)
      break;
    if ( m_sizeof_compressed > 0 )
    {
      m_buffer_compressed = onmalloc(m_sizeof_compressed);
      if ( m_buffer_compressed )
      {
        m_buffer_compressed_capacity = m_sizeof_compressed;
        rc = binary_archive.ReadByte(m_sizeof_compressed,m_buffer_compressed);
      }
      else
      {
        m_sizeof_compressed =0;
      }
      if (!rc)
        break;
    }

    break;
  }

  if ( !binary_archive.EndRead3dmChunk() )
    rc = false;

  return rc;
}

void ON_CompressedBuffer::Destroy()
{
  if ( m_buffer_compressed )
    onfree(m_buffer_compressed);

  m_sizeof_uncompressed = 0;
  m_sizeof_compressed   = 0;
  m_crc_uncompressed    = 0;
  m_crc_compressed      = 0;
  m_method              = 0;
  m_sizeof_element      = 0;
  m_buffer_compressed   = 0;
  m_buffer_compressed_capacity = 0;
}

bool ON_CompressedBuffer::Compress(
        size_t sizeof__inbuffer,  // sizeof uncompressed input data
        const void* inbuffer,     // uncompressed input data
        int sizeof_element
        )
{
  Destroy();

  //size_t compressed_size = 0;
  bool rc = false;

  if ( sizeof__inbuffer > 0 && 0 == inbuffer )
    return false;

  if ( 0 == sizeof__inbuffer )
    return true;

  if (sizeof__inbuffer > UINT32_MAX)
    return false;

  // number of bytes of uncompressed data
  m_sizeof_uncompressed = sizeof__inbuffer;

  ON_CompressedBufferHelper helper;
  memset(&helper,0,sizeof(helper));
  helper.m_action = 1;

  bool bToggleByteOrder = false;
  switch(sizeof_element)
  {
  case 2:
  case 4:
  case 8:
    if ( 0 == (sizeof__inbuffer%sizeof_element) )
    {
      m_sizeof_element = sizeof_element;
      bToggleByteOrder = (ON::endian::big_endian == ON::Endian());
    }
    break;
  };

  if ( bToggleByteOrder ) 
  {
    ON_BinaryFile::ToggleByteOrder( 
      (int)(sizeof__inbuffer/m_sizeof_element), 
      m_sizeof_element, 
      inbuffer, 
      (void*)inbuffer
      );
  }

  m_method = (sizeof__inbuffer > 128) ? 1 : 0;
  if ( m_method ) 
  {
    if ( !CompressionInit(&helper) ) 
    {
      CompressionEnd(&helper);
      m_method = 0;
    }
    else
    {
      m_buffer_compressed = onmalloc(sizeof__inbuffer/4);
      size_t sizeof_compressed = DeflateHelper( &helper, sizeof__inbuffer, inbuffer );
      CompressionEnd(&helper);
      if ( sizeof_compressed > 0 && sizeof_compressed == m_sizeof_compressed )
      {
        rc = true;
        if ( 2*m_buffer_compressed_capacity > 3*m_sizeof_compressed )
        {
          // release memory we don't need
          m_buffer_compressed_capacity = m_sizeof_compressed;
          m_buffer_compressed = onrealloc(m_buffer_compressed,m_buffer_compressed_capacity);
        }
      }
      else
      {
        Destroy();
        m_method = 0;
      }
    }
  }

  if ( 0 ==  m_method )
  {
    // uncompressed
    m_buffer_compressed = onmalloc(sizeof__inbuffer);
    if ( m_buffer_compressed )
    {
      m_sizeof_compressed = sizeof__inbuffer;
      m_buffer_compressed_capacity = sizeof__inbuffer;
      memcpy(m_buffer_compressed,inbuffer,sizeof__inbuffer);
      rc = true;
    }
  }

  if ( bToggleByteOrder ) 
  {
    ON_BinaryFile::ToggleByteOrder( 
      (int)(sizeof__inbuffer/m_sizeof_element), 
      m_sizeof_element, 
      inbuffer, 
      (void*)inbuffer
      );
  }

  if (rc)
  {
    m_crc_uncompressed = ON_CRC32( 0, sizeof__inbuffer, inbuffer );
    m_crc_compressed   = ON_CRC32( 0, m_sizeof_compressed, m_buffer_compressed );
  }

  return rc;
}

bool ON_CompressedBuffer::Uncompress(
          void* outbuffer,
          int* bFailedCRC
          ) const
{
  bool rc = false;

  if ( bFailedCRC)
    *bFailedCRC = false;
  if ( 0 == m_sizeof_uncompressed )
    return true;
  if ( 0 == outbuffer )
    return false;

  if ( m_method != 0 && m_method != 1 )
    return false;

  ON__UINT32 compressed_crc = ON_CRC32( 0, m_sizeof_compressed, m_buffer_compressed );
  if ( compressed_crc != m_crc_compressed )
  {
    // m_buffer_compressed is corrupt - let's hope the corruption
    // is near the end and we ge something useful from the
    // beginning.
    memset(outbuffer,0,m_sizeof_uncompressed);
    if ( bFailedCRC)
      *bFailedCRC = false;
  }

  switch(m_method)
  {
  case 0: // uncompressed
    if (    m_buffer_compressed
         && m_sizeof_uncompressed == m_sizeof_compressed
         )
    {
      memcpy(outbuffer,m_buffer_compressed,m_sizeof_uncompressed);
      rc = true;
    }
    break;

  case 1: // compressed
    {
      ON_CompressedBufferHelper helper;
      memset(&helper,0,sizeof(helper));
      helper.m_action = 2;
      rc = CompressionInit(&helper);
      if (rc)
      {
        rc = InflateHelper( &helper, m_sizeof_uncompressed, outbuffer );
        CompressionEnd(&helper);
      }
    }
    break;
  }

  switch(m_sizeof_element)
  {
  case 2:
  case 4:
  case 8:
    if ( 0 == (m_sizeof_uncompressed%m_sizeof_element) )
    {
      if (ON::endian::big_endian == ON::Endian())
      {
        ON_BinaryFile::ToggleByteOrder( 
          (int)(m_sizeof_uncompressed/m_sizeof_element), 
          m_sizeof_element, 
          outbuffer, 
          outbuffer
          );
      }
    }
    break;
  };


  if (rc ) 
  {
    ON__UINT32 uncompressed_crc = ON_CRC32( 0, m_sizeof_uncompressed, outbuffer );
    if ( uncompressed_crc != m_crc_uncompressed ) 
    {
      ON_ERROR("ON_CompressedBuffer::Uncompress() crc error");
      if ( bFailedCRC )
        *bFailedCRC = true;
    }
  }

  return rc;
}

bool ON_CompressedBuffer::WriteChar( 
        size_t count, const void* buffer         
        )
{
  bool rc = true;
  if ( count > 0 && buffer )
  {
    if ( count + m_sizeof_compressed > m_buffer_compressed_capacity )
    {
      size_t delta = count + m_sizeof_compressed - m_buffer_compressed_capacity;
      if ( delta < 2048 )
        delta = 2048;
      if ( delta < m_buffer_compressed_capacity/4 )
        delta = m_buffer_compressed_capacity/4;
      m_buffer_compressed_capacity += delta;
      m_buffer_compressed = onrealloc(m_buffer_compressed,m_buffer_compressed_capacity);
      if ( !m_buffer_compressed )
      {
        m_buffer_compressed_capacity = 0;
        m_sizeof_compressed = 0;
        return false;
      }
    }
    memcpy(((char*)m_buffer_compressed)+m_sizeof_compressed,buffer,count);
    m_sizeof_compressed += count;
  }
  else
  {
    rc = (0 == count);
  }
  return rc;
}


size_t ON_CompressedBuffer::DeflateHelper( // returns number of bytes written
        ON_CompressedBufferHelper* helper,
        size_t sizeof___inbuffer,  // sizeof uncompressed input data ( > 0 )
        const void* in___buffer     // uncompressed input data ( != nullptr )
        )
{
  /*
    In "standard" (in 2005) 32 bit code
    
      sizeof(int)     = 4 bytes, 
      sizeof(long)    = 4 bytes,
      sizeof(pointer) = 4 bytes, and
      sizeof(size_t)  = 4 bytes.

    Theoretically I don't need to use multiple input buffer
    chunks in case.  But I'm paranoid and I will use multiple 
    input chunks when sizeof_inbuffer > 2GB in order to dodge
    any potential zlib signed verses unsigned compare bugs or
    having a signed int i++ roll over to a negative number.

    In "standard" code that has 64 bit pointers
    
      sizeof(int)     >= 4 bytes, (it's 4 on MS VS2005) 
      sizeof(long)    >= 4 bytes, (it's 4 on MS VS2005)
      sizeof(pointer)  = 8 bytes, and
      sizeof(size_t)   = 8 bytes.

    So, I'm going to assume the ints and longs in the zlib code 
    are 4 bytes, but I could have sizeof_inbuffer > 4GB.
    This means I have to use multiple input buffer chunks.  
    In this case I still use multiple input chunks when 
    sizeof_inbuffer > 2GB in order to dodge any potential zlib
    signed verses unsigned compare bugs or having a signed
    int i++ roll over to a negative number.

    So, I set
    
       const size_t max_avail = (largest signed 4 byte integer - 15)
    
    and feed inflate and deflate buffers with size <= max_avail.


    This information below is from the zlib 1.2.3 FAQ.  

    32. Can zlib work with greater than 4 GB of data?

        Yes. inflate() and deflate() will process any amount of data correctly.
        Each call of inflate() or deflate() is limited to input and output chunks
        of the maximum value that can be stored in the compiler's "unsigned int"
        type, but there is no limit to the number of chunks. Note however that the
        strm.total_in and strm_total_out counters may be limited to 4 GB. These
        counters are provided as a convenience and are not used internally by
        inflate() or deflate(). The application can easily set up its own counters
        updated after each call of inflate() or deflate() to count beyond 4 GB.
        compress() and uncompress() may be limited to 4 GB, since they operate in a
        single call. gzseek() and gztell() may be limited to 4 GB depending on how
        zlib is compiled. See the zlibCompileFlags() function in zlib.h.

        The word "may" appears several times above since there is a 4 GB limit
        only if the compiler's "long" type is 32 bits. If the compiler's "long"
        type is 64 bits, then the limit is 16 exabytes.
  */

  const size_t max_avail = 0x7FFFFFF0;

  //  Compressed information is saved in a chunk.
  bool rc = true;

  size_t out__count = 0;
  int zrc = Z_OK;

  size_t my_avail_in = sizeof___inbuffer;
  unsigned char* my_next_in = (unsigned char*)in___buffer;

  size_t d = my_avail_in;
  if ( d > max_avail )
    d = max_avail;

  ON_CompressedBufferHelper& m_zlib = *helper;

  m_zlib.m_strm.next_in = my_next_in;
  m_zlib.m_strm.avail_in = (unsigned int)d; 
  my_avail_in -= d;
  my_next_in  += d;

  m_zlib.m_strm.next_out = m_zlib.m_buffer;
  m_zlib.m_strm.avail_out = m_zlib.sizeof_x_buffer;

  // counter guards prevents infinite loops if there is a bug in zlib return codes.
  int counter = 512; 
  int flush = Z_NO_FLUSH;

  size_t deflate_output_count = 0;

  while( rc && counter > 0 ) 
  {
    // Call zlib's deflate function.  It can either process
    // more input from m_zlib.m_strm.next_in[], create more
    // compressed output in m_zlib.m_strm.next_out[], or do both.
    if ( 0 == my_avail_in && 0 == m_zlib.m_strm.avail_in )
    {
      // no uncompressed input is left - switch to finish mode
      flush = Z_FINISH;
    }
    zrc = z_deflate( &m_zlib.m_strm, flush ); 
    if ( zrc < 0 ) 
    {
      // Something went haywire - bail out.
      ON_ERROR("ON_CompressedBuffer::DeflateHelper - z_deflate failure");
      rc = false;
      break;
    }

    deflate_output_count = m_zlib.sizeof_x_buffer - m_zlib.m_strm.avail_out;
    if ( deflate_output_count > 0 ) 
    {
      // The last call to deflate created output.  Send
      // this output to the archive.
      rc = WriteChar( deflate_output_count, m_zlib.m_buffer );
      if ( !rc )
        break;
      out__count += deflate_output_count;
      m_zlib.m_strm.next_out  = m_zlib.m_buffer;
      m_zlib.m_strm.avail_out = m_zlib.sizeof_x_buffer;
    }

    if ( Z_FINISH == flush && Z_STREAM_END == zrc )
    {
      // no input left, all pending compressing is finished,
      // and all compressed output has been returned.
      break;
    }

    if ( my_avail_in > 0 && m_zlib.m_strm.avail_in < max_avail )
    {
      // inbuffer[] had more than max_zlib_avail_in bytes in it
      // and I am feeding inbuffer[] to deflate in smaller chunks
      // that the 32 bit integers in the zlib code can handle.
      if ( 0 == m_zlib.m_strm.avail_in || 0 == m_zlib.m_strm.next_in )
      {
        // The call to deflate() used up all the input 
        // in m_zlib.m_strm.next_in[].  I can feed it another chunk
        // from inbuffer[]
        d = my_avail_in;
        if ( d > max_avail )
          d = max_avail;
        m_zlib.m_strm.next_in = my_next_in;
        m_zlib.m_strm.avail_in = (unsigned int)d; 
      }
      else
      {
        // The call to deflate left some input in m_zlib.m_strm.next_in[],
        // but I can increase m_zlib.m_strm.avail_in.
        d =  max_avail - m_zlib.m_strm.avail_in;
        if ( d > my_avail_in )
          d = my_avail_in;
        m_zlib.m_strm.avail_in += (unsigned int)d;
      }

      my_avail_in -= d;
      my_next_in  += d;
    }
    else if ( 0 == deflate_output_count )
    {
      // no buffer changes this time
      counter--;
    }

    if ( zrc != Z_OK )
    {
      break;
    }
  }

  if ( 0 == counter )
  {
    rc = false;
  }

  return (rc ? out__count : 0);
}


bool ON_CompressedBuffer::InflateHelper(
        ON_CompressedBufferHelper* helper,
        size_t sizeof___outbuffer,  // sizeof uncompressed data
        void* out___buffer          // buffer for uncompressed data
        ) const
{
  const size_t max_avail = 0x7FFFFFF0; // See max_avail comment in ON_CompressedBuffer::InflateHelper

  bool rc = true;

  int zrc = -1;

  // set up zlib in buffer
  unsigned char* my_next_in = (unsigned char*)m_buffer_compressed;
  size_t my_avail_in = m_sizeof_compressed;

  size_t d = my_avail_in;
  if ( d > max_avail )
    d = max_avail;

  struct ON_CompressedBufferHelper& m_zlib = *helper;

  m_zlib.m_strm.next_in  = my_next_in;
  m_zlib.m_strm.avail_in = (unsigned int)d;
  my_next_in  += d;
  my_avail_in -= d;

  // set up zlib out buffer
  unsigned char* my_next_out = (unsigned char*)out___buffer;
  size_t my_avail_out = sizeof___outbuffer;

  d = my_avail_out;
  if ( d > max_avail )
    d = max_avail;
  m_zlib.m_strm.next_out  = my_next_out;
  m_zlib.m_strm.avail_out = (unsigned int)d;
  my_next_out  += d;
  my_avail_out -= d;

  // counter guards against infinite loop if there are
  // bugs in zlib return codes
  int counter = 512;
  int flush = Z_NO_FLUSH;

  while ( rc && counter > 0 )
  {
    // Call zlib's inflate function.  It can either process
    // more input from m_zlib.m_strm.next_in[], create more
    // uncompressed output in m_zlib.m_strm.next_out[], or do both.
    if ( 0 == my_avail_in && 0 == m_zlib.m_strm.avail_in )
    {
      // no compressed input is left - switch to finish mode
      flush = Z_FINISH;
    }
    zrc = z_inflate( &m_zlib.m_strm, flush );
    if ( zrc < 0 ) 
    {
      // Something went haywire - bail out.
      ON_ERROR("ON_CompressedBuffer::InflateHelper - z_inflate failure");
      rc = false;
      break;
    }

    if ( Z_FINISH == flush && Z_STREAM_END == zrc )
    {
      // no input left, all pending decompression is finished,
      // and all decompressed output has been returned.
      break;
    }

    d = 0;
    if ( my_avail_in > 0 && m_zlib.m_strm.avail_in < max_avail )
    {
      if ( 0 == m_zlib.m_strm.avail_in || 0 == m_zlib.m_strm.next_in )
      {
        // The call to inflate() used up all the input 
        // in m_zlib.m_strm.next_in[].  I can feed it another chunk
        // from inbuffer[]
        d = my_avail_in;
        if ( d > max_avail )
          d = max_avail;
        m_zlib.m_strm.next_in  = my_next_in;
        m_zlib.m_strm.avail_in = (unsigned int)d; 
      }
      else
      {
        // The call to inflate() left some input in m_zlib.m_strm.next_in[],
        // but I can increase m_zlib.m_strm.avail_in.
        d =  max_avail - m_zlib.m_strm.avail_in;
        if ( d > my_avail_in )
          d = my_avail_in;
        m_zlib.m_strm.avail_in += (unsigned int)d;
      }
      my_next_in  += d;
      my_avail_in -= d;
    }

    if ( my_avail_out > 0 && m_zlib.m_strm.avail_out < max_avail )
    {
      // increase m_zlib.m_strm.next_out[] buffer
      if ( 0 == m_zlib.m_strm.avail_out || 0 == m_zlib.m_strm.next_out )
      {
        d = my_avail_out;
        if ( d > max_avail )
          d = max_avail;
        m_zlib.m_strm.next_out  = my_next_out;
        m_zlib.m_strm.avail_out = (unsigned int)d;
      }
      else
      {
        d = max_avail - m_zlib.m_strm.avail_out;
        if ( d > my_avail_out )
          d = my_avail_out;
        m_zlib.m_strm.avail_out += ((unsigned int)d);
      }
      my_next_out  += d;
      my_avail_out -= d;
    }
    else if ( 0 == d )
    {
      // no buffer changes
      counter--;
    }
  }

  if ( 0 == counter )
  {
    rc = false;
  }

  return rc;
}

bool ON_CompressedBuffer::CompressionInit( struct ON_CompressedBufferHelper* helper ) const
{
  bool rc = false;

  if ( helper )
  {
    // inflateInit() and deflateInit() are in zlib 1.3.3
    if ( 1 == helper->m_action ) 
    {
      // begin compression using zlib's deflate tool
      if (Z_OK == deflateInit(&helper->m_strm, Z_BEST_COMPRESSION))
      {
        rc = true;
      }
      else 
      {
        memset(&helper->m_strm, 0, sizeof(helper->m_strm));
        helper->m_action = 0;
      }
    }
    else if (2 == helper->m_action)
    {
      // begin uncompression using zlib's inflate tool
      if (Z_OK == inflateInit(&helper->m_strm))
      {
        rc = true;
      }
      else 
      {
        memset(&helper->m_strm, 0, sizeof(helper->m_strm));
        helper->m_action = 0;
      }
    }
  }

  return rc;
}

bool ON_CompressedBuffer::CompressionEnd( struct ON_CompressedBufferHelper* helper ) const
{
  bool rc = false;

  if ( helper )
  {
    // inflateEnd() and deflateEnd() are in zlib 1.3.3
    if (1 == helper->m_action)
    {
      // finish compression
      deflateEnd(&helper->m_strm);
      rc = true;
    }
    else if (2 == helper->m_action)
    {
      // finish decompression
      inflateEnd(&helper->m_strm);
      rc = true;
    }
    memset(&helper->m_strm, 0, sizeof(helper->m_strm));
    helper->m_action = 0;
  }

  return rc;
}


