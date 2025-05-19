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

static bool IdIsNotNil(const ON_UUID* id)
{
  // This is a fast static function to check for zero ids.
  // The caller always checks that id is not null.
  const ON__UINT64* p = (const ON__UINT64*)id;
  return (p[0] != 0 || p[1] != 0);
}

static bool IdIsNil(const ON_UUID* id)
{
  // This is a fast static function to check for zero ids.
  // The caller always checks that id is not null.
  const ON__UINT64* p = (const ON__UINT64*)id;
  return (p[0] == 0 && p[1] == 0);
}

static bool IdIsEqual(const ON_UUID* a, const ON_UUID* b)
{
  // This is a fast static function to check for zero ids.
  // The caller always checks that id is not null.
  const ON__UINT64* p = (const ON__UINT64*)a;
  const ON__UINT64* q = (const ON__UINT64*)b;
  return (p[0] == q[0] && p[1] == q[1]);
}

static bool IdIsNotEqual(const ON_UUID* a, const ON_UUID* b)
{
  // This is a fast static function to check for zero ids.
  // The caller always checks that id is not null.
  const ON__UINT64* p = (const ON__UINT64*)a;
  const ON__UINT64* q = (const ON__UINT64*)b;
  return (p[0] != q[0] || p[1] != q[1]);
}

static ON__UINT32 IdCRC32(const ON_UUID* id)
{
  return ON_CRC32(0, sizeof(*id), id);
}

// 30 July 2024 S. Baer (RH-82891)
// Rhino uses serial numbers above UIN32_MAX for "system components"
// which results in a serial number map with very large numbers for m_maxsn.
// This caused a huge lag in performance when adding a large number of
// objects to the document because we were always having to do a large
// search for an element. The following class replaces m_maxsn and keeps
// a lower maximum value to help quickly determine if an added element
// exists with a lower value (rhino objects) exists in the list.
class ON_SerialNumberMapPrivate
{
public:
  ON__UINT64 MaxSn() const { return m_maxsn; }
  ON__UINT64 LowerMaxSn() const { return m_lower_maxsn; }
  void SetMaxSn(ON__UINT64 sn)
  {
    m_maxsn = sn;
    if (sn < UINT32_MAX)
      m_lower_maxsn = sn;
  }
  void SetLowerMaxSn(ON__UINT64 sn)
  {
    m_lower_maxsn = sn;
    if (m_lower_maxsn > m_maxsn)
      m_maxsn = m_lower_maxsn;
  }

private:
  ON__UINT64 m_maxsn = 0; // largest sn stored anywhere
  ON__UINT64 m_lower_maxsn = 0;
};



class ON_SN_BLOCK
{
public:
  enum : unsigned int
  {
    // These numbers are chosen so the ON_SerialNumberMap
    // will be computationally efficient for up to
    // 10 million entries.
    SN_BLOCK_CAPACITY = 8192,
    ID_HASH_BLOCK_CAPACITY = 4090
  };

  ON_SN_BLOCK() = default;
  ~ON_SN_BLOCK() = default;
  ON_SN_BLOCK(const ON_SN_BLOCK&) = default;
  ON_SN_BLOCK& operator=(const ON_SN_BLOCK&) = default;

  ON__UINT32 m_count = 0;  // used elements in m_sn[]
  ON__UINT32 m_purged = 0; // number of purged elements in m_sn[]
  ON__UINT32 m_sorted = 1; // 0 = no, 1 = yes
  ON__UINT32 m_reserved = 0;
  ON__UINT64 m_sn0 = 0; // minimum sn in m_sn[]
  ON__UINT64 m_sn1 = 0; // maximum sn in m_sn[]
  struct ON_SerialNumberMap::SN_ELEMENT m_sn[ON_SN_BLOCK::SN_BLOCK_CAPACITY];


  /*
  Returns:
    true 
      The number of purged elements is high enough that the cost of culling
      will be recovered by improved search speeds.
  */
  bool NeedsToBeCulled() const;

  void EmptyBlock();
  void CullBlockHelper();
  void SortBlockHelper();
  bool IsValidBlock(
    ON_TextLog* textlog,
    struct ON_SerialNumberMap::SN_ELEMENT*const*const* hash_table,
    ON__UINT32 hash_block_count,
    ON__UINT64* active_id_count
    ) const;
  struct ON_SerialNumberMap::SN_ELEMENT* BinarySearchBlockHelper(
    ON__UINT64 sn
    );
  static int CompareMaxSN(
    const void*,
    const void*
    );
  ON__UINT64 ActiveElementEstimate(
    ON__UINT64 sn0,
    ON__UINT64 sn1
    ) const;
  void Dump(ON_TextLog&) const;
};

void ON_SerialNumberMap::EmptyList()
{
  m_private->SetMaxSn(0);
  m_sn_count = 0;
  m_sn_purged = 0;
  m_sn_block0.EmptyBlock();
  if (m_snblk_list)
  {
    ON__UINT64 i = m_snblk_list_capacity;
    while(i--)
    {
      if ( 0 != m_snblk_list[i] )
        onfree(m_snblk_list[i]);
    }
    onfree(m_snblk_list);
    m_snblk_list = 0;
    m_snblk_list_capacity = 0;
    m_snblk_list_count = 0;
  }
  m_bHashTableIsValid = false;
  if (nullptr != m_hash_table_blocks)
  {
    // Starts at i = 1 because m_hash_table_blocks[] and m_hash_table_blocks[0] 
    // are a single allocation.
    for (ON__UINT32 i = 1; i < m_hash_block_count; i++)
      onfree(m_hash_table_blocks[i]);
    onfree(m_hash_table_blocks); // includes m_hash_table_blocks[0].
    m_hash_table_blocks = nullptr;
  }
  m_active_id_count = 0;
}
ON_SerialNumberMap::ON_SerialNumberMap()
  : m_sn_block0(*(new ON_SN_BLOCK()))
{
  m_private = new ON_SerialNumberMapPrivate();
}

ON_SerialNumberMap::~ON_SerialNumberMap()
{
  EmptyList();
  ON_SN_BLOCK* p = &m_sn_block0;
  delete p;
  delete m_private;
}

void ON_SN_BLOCK::EmptyBlock()
{
  m_count = 0;
  m_purged = 0;
  m_sorted = 1;
  m_sn0 = 0;
  m_sn1 = 0;
}

bool ON_SN_BLOCK::NeedsToBeCulled() const
{
  const ON__UINT32 purge_ratio 
    = (m_purged >= 16)
    ? 16
    : 2;
  return (m_purged > m_count / purge_ratio);
}


void ON_SN_BLOCK::CullBlockHelper()
{
  // Search the m_an[] array for elements whose m_u_type
  // value is zero and remove them from the array.
  //
  // This is a high speed helper function.  
  // The calling function must verify m_purged > 0.
  //
  // This function removes all m_sn[] elements
  // that have 0 == m_sn_active.

  ON__UINT32 i, j;
  for (i = 0; i < m_count; i++ )
  {
    if ( 0 == m_sn[i].m_sn_active )
    {
      for ( j = i+1; j < m_count; j++ )
      {
        if ( m_sn[j].m_sn_active )
        {
          m_sn[i++] = m_sn[j];
        }
      }
      if ( 0 == i )
      {
        EmptyBlock();
      }
      else
      {
        m_count = i;
        m_purged = 0;
        if ( m_sorted )
        {
          m_sn0 = m_sn[0].m_sn;
          m_sn1 = m_sn[m_count-1].m_sn;
        }
      }
      break;
    }
  }
}



/*
The defines and #include generates a fast sorting function
static void ON_qsort_SN_ELEMENT( struct ON_SerialNumberMap::SN_ELEMENT* base, size_t nel );
*/

#define ON_SORT_TEMPLATE_COMPARE compare_SN_ELEMENT_sn
#define ON_COMPILING_OPENNURBS_QSORT_FUNCTIONS
#define ON_SORT_TEMPLATE_STATIC_FUNCTION
#define ON_SORT_TEMPLATE_TYPE struct ON_SerialNumberMap::SN_ELEMENT
#define ON_QSORT_FNAME ON_qsort_SN_ELEMENT

static int ON_SORT_TEMPLATE_COMPARE(const struct ON_SerialNumberMap::SN_ELEMENT * a, const struct ON_SerialNumberMap::SN_ELEMENT * b)
{
  ON__UINT64 asn, bsn;
  return ( ( (asn = a->m_sn) < (bsn = b->m_sn) ) ? -1 : (asn > bsn) ? 1 : 0 );
}

#include "opennurbs_qsort_template.h"

#undef ON_COMPILING_OPENNURBS_QSORT_FUNCTIONS
#undef ON_SORT_TEMPLATE_STATIC_FUNCTION
#undef ON_SORT_TEMPLATE_TYPE
#undef ON_QSORT_FNAME
#undef ON_SORT_TEMPLATE_COMPARE


void ON_SN_BLOCK::SortBlockHelper()
{
  // Sort m_sn[] by serial number.
  //
  // This is a high speed helper function.  
  //
  // The calling function verify:
  //   m_sorted is zero
  //   m_purged is zero
  //   m_count > 0
  //
  // The array m_sn[] is almost always nearly sorted,
  // so the sort used here should efficiently
  // handle almost sorted arrays. In the past,
  // heap sort was the best choice, but the qsort()
  // in VS 2010 is now a better choice than heap sort.
   
  if ( m_count > 1 )
  {
#if 1
    // Quick sort
    ON_qsort_SN_ELEMENT(m_sn, (size_t)m_count);
#else
    // Heap sort
    size_t i, j, k, i_end;
    struct SN_ELEMENT e_tmp;
    struct SN_ELEMENT* e;

    e = m_sn;

    k = m_count >> 1;
    i_end = m_count-1;
    for (;;) 
    {
      if (k)
      {
        --k;
        e_tmp = e[k];
      } 
      else 
      {
        e_tmp = e[i_end];
        e[i_end] = e[0];
        if (!(--i_end)) 
        {
          e[0] = e_tmp;
          break;
        }
      }

      i = k;
      j = (k<<1) + 1;
      while (j <= i_end)
      {
        if (j < i_end && e[j].m_sn < e[j + 1].m_sn)
          j++;
        if (e_tmp.m_sn < e[j].m_sn)
        {
          e[i] = e[j];
          i = j;
          j = (j<<1) + 1;
        } 
        else 
          j = i_end + 1;
      }
      e[i] = e_tmp;
    }
#endif
    m_sn0 = m_sn[0].m_sn;
    m_sn1 = m_sn[m_count-1].m_sn;
  }
  else
  {
    m_sn0 = m_sn1 = ((1 == m_count) ? m_sn[0].m_sn : 0);
  }
  m_sorted = 1;
}


static bool ON_SerialNumberMap_IsNotValidBlock()
{
  return ON_IsNotValid();
}

bool ON_SN_BLOCK::IsValidBlock(
  ON_TextLog* textlog, 
  struct ON_SerialNumberMap::SN_ELEMENT*const*const* hash_table,
  ON__UINT32 hash_block_count,
  ON__UINT64* active_id_count
  ) const
{
  ON__UINT64 sn0, sn;
  size_t i, pc, aidcnt;

  if ( m_count > ON_SN_BLOCK::SN_BLOCK_CAPACITY )
  {
    if (textlog)
      textlog->Print("ON_SN_BLOCK m_count = %u (should be >=0 and <%u).\n",
                      m_count,ON_SN_BLOCK::SN_BLOCK_CAPACITY);
    return ON_SerialNumberMap_IsNotValidBlock();
  }

  if ( m_purged > m_count )
  {
    if (textlog)
      textlog->Print("ON_SN_BLOCK m_purged = %u (should be >0 and <=%u).\n",
                      m_purged,m_count);
    return ON_SerialNumberMap_IsNotValidBlock();
  }

  if ( m_count < 2 && 1 != m_sorted )
  {
    if (textlog)
      textlog->Print("ON_SN_BLOCK m_count = %u but m_sorted is not 1.\n",m_count);
    return ON_SerialNumberMap_IsNotValidBlock();
  }

  if ( 0 == m_count )
  {
    if ( 0 != m_sn0 )
    {
      if (textlog)
        textlog->Print("ON_SN_BLOCK m_count = 0 but m_sn0 != 0.\n");
      return ON_SerialNumberMap_IsNotValidBlock();
    }
    if ( 0 != m_sn1 )
    {
      if (textlog)
        textlog->Print("ON_SN_BLOCK m_count = 0 but m_sn1 != 0.\n");
      return ON_SerialNumberMap_IsNotValidBlock();
    }
    return true;
  }

  if ( m_sn1 < m_sn0 )
  {
    if (textlog)
      textlog->Print("ON_SN_BLOCK m_sn1 < m_sn0.\n");
    return ON_SerialNumberMap_IsNotValidBlock();
  }

  if ( m_count > m_purged )
  {
    if ( m_sn1 - m_sn0 < m_count-m_purged-1 )
    {
      if (textlog)
        textlog->Print("ON_SN_BLOCK m_sn1 < m_sn0.\n");
      return ON_SerialNumberMap_IsNotValidBlock();
    }
  }

  sn0 = 0;
  pc = 0;
  aidcnt = 0;
  for (i = 0; i < m_count; i++)
  {
    // validate m_sn_active and m_id_active flags
    if (0 == m_sn[i].m_sn_active)
    {
      // The element serial number is not active.
      // The id must also be not active.
      pc++;
      if ( 0 != m_sn[i].m_id_active )
      {
        if (textlog)
          textlog->Print("ON_SN_BLOCK m_sn[%d].m_sn_active = 0 but m_id_active != 0.\n",i);
        return ON_SerialNumberMap_IsNotValidBlock();
      }
    }
    else if ( 0 != m_sn[i].m_id_active )
    {
      // The element has active serial number and active id.
      // It must have a nonzero m_id and be in the hash table.
      aidcnt++;
      if ( IdIsNotNil(&m_sn[i].m_id) )
      {
        const ON__UINT32 id_crc32 = IdCRC32(&m_sn[i].m_id);
        if (id_crc32 != m_sn[i].m_id_crc32)
        {
          if (textlog)
            textlog->Print("ON_SN_BLOCK m_sn[%d].m_id_active != 0 and m_sn[i].m_id_crc32 != IdCRC32(&m_sn[i].m_id).\n", i);
          return ON_SerialNumberMap_IsNotValidBlock();
        }
        if (nullptr != hash_table)
        {
          const ON_SerialNumberMap::SN_ELEMENT* e = nullptr;
          for (e = hash_table[id_crc32 % hash_block_count][(id_crc32/ON_SN_BLOCK::ID_HASH_BLOCK_CAPACITY) % ON_SN_BLOCK::ID_HASH_BLOCK_CAPACITY]; 0 != e; e = e->m_next)
          {
            if (e == &m_sn[i])
            {
              // found m_sn[i] in the hash table
              break;
            }
          }
          if (nullptr == e)
          {
            // m_sn[i] is not in the hash table but m_id_active indicates
            // it should be.
            if (textlog)
              textlog->Print("ON_SN_BLOCK m_sn[%d].m_id_active != 0 but the element is not in m_hash_table[].\n", i);
            return ON_SerialNumberMap_IsNotValidBlock();
          }
        }
      }
      else 
      {
        if (textlog)
          textlog->Print("ON_SN_BLOCK m_sn[%d].m_id_active != 0 but m_id = 0.\n",i);
        return ON_SerialNumberMap_IsNotValidBlock();
      }
    }

    // verify the serial number is in the range m_sn0 to m_sn1
    sn = m_sn[i].m_sn;
    if ( sn < m_sn0 )
    {
      if (textlog)
        textlog->Print("ON_SN_BLOCK m_sn[%d] < m_sn0.\n",i);
      return ON_SerialNumberMap_IsNotValidBlock();
    }
    if ( sn > m_sn1 )
    {
      if (textlog)
        textlog->Print("ON_SN_BLOCK m_sn[%d] > m_sn1.\n",i);
      return ON_SerialNumberMap_IsNotValidBlock();
    }

    if ( m_sorted )
    {
      // Verify this sn is bigger than the previous one
      if (sn <= sn0 )
      {
        if (textlog)
          textlog->Print("ON_SN_BLOCK m_sn[%d] > m_sn[%d].\n",i,i-1);
        return ON_SerialNumberMap_IsNotValidBlock();
      }
      sn0 = sn;
    }
  }

  if ( pc != m_purged )
  {
    if (textlog)
      textlog->Print("ON_SN_BLOCK m_purged = %u (should be %u)\n",m_purged,pc);
    return ON_SerialNumberMap_IsNotValidBlock();
  }

  // Update the active id count to include
  // the active ids from this block.
  if ( 0 != active_id_count )
    *active_id_count += aidcnt;

  return true;
}

struct ON_SerialNumberMap::SN_ELEMENT* ON_SN_BLOCK::BinarySearchBlockHelper(ON__UINT64 sn)
{
  // Perform a binary search on the serial number values in the m_sn[] array.
  //
  // This is a high speed helper function.  
  //
  // The calling function verify:
  //   m_sn[] is sorted by serial number (1 == m_sorted)
  //   m_count > 0
  //   m_sn0 <= sn <= m_sn1.

  ON__UINT64 i, j;
  struct ON_SerialNumberMap::SN_ELEMENT* e;
  ON__UINT64 midsn;

  i = m_count;
  e = m_sn;
  while (i > 0 )
  {
    midsn = e[(j=i/2)].m_sn;
    if ( sn < midsn )
    {
      i = j;
    }
    else if ( sn > midsn )
    {
      j++;
      e += j;
      i -= j;
    }
    else 
    {
      return e + j;
    }
  }
  return 0;
}

void ON_SerialNumberMap::UpdateMaxSNHelper()
{
  ON__UINT64 maxsn = (m_snblk_list_count > 0) ? m_snblk_list[m_snblk_list_count-1]->m_sn1 : 0;
  if (maxsn < m_sn_block0.m_sn1 )
    maxsn = m_sn_block0.m_sn1;

  m_private->SetMaxSn(maxsn);
}

struct ON_SerialNumberMap::SN_ELEMENT* ON_SerialNumberMap::FindElementHelper(ON__UINT64 sn)
{
  class ON_SN_BLOCK** eblk_array;
  class ON_SN_BLOCK* eblk;
  size_t i, j;

  if (m_private->MaxSn() < sn )
    return 0; // happens almost every time an object is added to the doc

  if (sn < UINT32_MAX && m_private->LowerMaxSn() < sn)
    return 0;

  if ( sn <= 0 )
    return 0;

  // First check m_sn_block0. For small models this
  // is the only place we need to look.
  if ( sn <= m_sn_block0.m_sn1 && m_sn_block0.m_sn0 <= sn )
  {
    SN_ELEMENT* e;

    m_e_blk = &m_sn_block0;
    if ( !m_sn_block0.m_sorted )
    {
      // m_sn_block0.m_sn[] needs to be sorted
      //
      // This is a rare occurrence.  It only happens
      // when commands add new objects in an order that
      // is different from that in which the CRhinoObject
      // class constructor was called.  In testing,
      // I could not find a real command that did this
      // and had to write TestAddBackwards to test this code.
      if ( m_sn_block0.m_purged > 0 )
      {
        // memory location for specific elements will be changed.
        // This will make the hash table invalid.
        Internal_HashTableInvalidate();
        m_sn_count -= m_sn_block0.m_purged;
        m_sn_purged -= m_sn_block0.m_purged;
        m_sn_block0.CullBlockHelper();
        UpdateMaxSNHelper();
      }
      if ( m_sn_block0.m_count > 0 )
      {
        // memory location for specific elements will be changed.
        // This will make the hash table invalid.
        Internal_HashTableInvalidate();
        m_sn_block0.SortBlockHelper();
      }
      e = ( sn <= m_sn_block0.m_sn1 && m_sn_block0.m_sn0 <= sn )
        ? m_sn_block0.BinarySearchBlockHelper(sn)
        : 0;
    }
    else if ( m_sn_block0.NeedsToBeCulled() )
    {
      // memory location for specific elements will be changed.
      // This will make the hash table invalid.
      Internal_HashTableInvalidate();
      m_sn_count -= m_sn_block0.m_purged;
      m_sn_purged -= m_sn_block0.m_purged;
      m_sn_block0.CullBlockHelper();
      UpdateMaxSNHelper();
      e = ( sn <= m_sn_block0.m_sn1 && m_sn_block0.m_sn0 <= sn )
        ? m_sn_block0.BinarySearchBlockHelper(sn)
        : 0;
    }
    else
    {
      e = m_sn_block0.BinarySearchBlockHelper(sn);
    }
    if (e)
      return e;
  }

  // look in the blocks kept in the m_sn_list[] array.
  // The m_sn[] arrays in these blocks are always sorted.
  // In addition the blocks are disjoint and stored in
  // the m_sn_list[] array in sorted order.
  if ( 0 == (i = (size_t)m_snblk_list_count) )
  {
    return 0;
  }
  eblk_array = m_snblk_list;
  while (i > 0 )
  {
    eblk = eblk_array[(j=i/2)];

    // The culling code is here rather than
    // in the binary search clause so the
    // entire ON_SerialNumberMap tends to
    // be tidy.
    if ( eblk->NeedsToBeCulled() )
    {
      // cull purged items from eblk

      // memory location for specific elements will be changed.
      // This will make the hash table invalid.
      Internal_HashTableInvalidate();

      m_sn_count -= eblk->m_purged;
      m_sn_purged -= eblk->m_purged;
      eblk->CullBlockHelper();
      if ( 0 == eblk->m_count )
      {
        // put empty block at the end of the list
        for( j += ((eblk_array-m_snblk_list)+1); j < m_snblk_list_count; j++ )
        {
          m_snblk_list[j-1] = m_snblk_list[j];
        }
        m_snblk_list_count--;
        m_snblk_list[m_snblk_list_count] = eblk;
        i--;
        UpdateMaxSNHelper();
        continue;
      }
      UpdateMaxSNHelper();
    }

    if ( sn < eblk->m_sn0 )
    {
      i = j;
    }
    else if ( sn > eblk->m_sn1 )
    {
      j++;
      eblk_array += j;
      i -= j;
    }
    else 
    {
      m_e_blk = eblk;
      return eblk->BinarySearchBlockHelper(sn);
    }
  }

  return 0;
}

ON__UINT64 ON_SerialNumberMap::ActiveSerialNumberCount() const
{
  return m_sn_count - m_sn_purged;
}

ON__UINT64 ON_SerialNumberMap::ActiveIdCount() const
{
  return m_active_id_count;
}

// 10 March 2024 S. Baer (RH-80748)
// The VS2022 compiler crashes in a release build when compiling the
// following function. Disable optimizations for this specific compile.
#if defined(ON_RUNTIME_WIN) && defined(_MSC_VER) && !defined(ON_DEBUG)
// Visual Studio 2022 initial release is 1930
#if _MSC_VER >= 1930
#define ON_VS2022_COMPILER_CRASH
#endif
#endif

#if defined(ON_VS2022_COMPILER_CRASH)
#pragma optimize("", off)
#endif
ON_SerialNumberMap::SN_ELEMENT* ON_SerialNumberMap::FirstElement() const
{
  SN_ELEMENT* e=nullptr;

  // The first element is likely to be m_snblk_list[0]->m_sn[0]
  // so start looking there.
  // The nullptr==e test isn't necessary. It is there to keep
  // the VisualC++ 2022 compiler from crashing.
  for(size_t i = 0; i < m_snblk_list_count && nullptr==e; i++)
  {
    if ( m_snblk_list[i]->m_count > m_snblk_list[i]->m_purged )
    {
      for (size_t j = 0; j < m_snblk_list[i]->m_count; j++ )
      {
        if ( m_snblk_list[i]->m_sn[j].m_sn_active )
        {
          e = &m_snblk_list[i]->m_sn[j];
          break;
        }
      }
      break;
    }
  }

  if ( m_sn_block0.m_count > m_sn_block0.m_purged 
       && (!e || m_sn_block0.m_sn0 < e->m_sn) 
     )
  {
    // It's possible the element is in m_sn_block0.
    if ( m_sn_block0.m_purged > 0 )
    {
      // remove purged elements from m_sn_block0.

      // memory location for specific elements will be changed.
      // This will make the hash table invalid.
      const_cast<ON_SerialNumberMap*>(this)->Internal_HashTableInvalidate();

      const_cast<ON_SerialNumberMap*>(this)->m_sn_count -= m_sn_block0.m_purged;
      const_cast<ON_SerialNumberMap*>(this)->m_sn_purged -= m_sn_block0.m_purged;
      const_cast<ON_SerialNumberMap*>(this)->m_sn_block0.CullBlockHelper();
    }
    if ( !m_sn_block0.m_sorted )
    {
      // sort elements in m_sn_block0.

      // memory location for specific elements will be changed.
      // This will make the hash table invalid.
      const_cast<ON_SerialNumberMap*>(this)->Internal_HashTableInvalidate();

      const_cast<ON_SerialNumberMap*>(this)->m_sn_block0.SortBlockHelper();      
    }
    if ( !e || m_sn_block0.m_sn0 <  e->m_sn )
    {
      // first element in m_sn_block0 is the
      // one with the smallest serial number.
      e = const_cast<struct SN_ELEMENT*>(&m_sn_block0.m_sn[0]);
    }
  }
  return e;
}
#if defined(ON_VS2022_COMPILER_CRASH)
#pragma optimize("", on)
#endif


struct ON_SerialNumberMap::SN_ELEMENT* ON_SerialNumberMap::LastElement() const
{
  struct SN_ELEMENT* e=0;
  ON__UINT64 i,j;

  // Last element is likely to be m_sn_block0.m_sn[m_sn_block0.m_count-1]
  // so start looking there.
  if ( m_sn_block0.m_count > m_sn_block0.m_purged )
  {
    if ( m_sn_block0.m_purged > 0 )
    {
      // remove purged elements from m_sn_block0

      // memory location for specific elements will be changed.
      // This will make the hash table invalid.
      const_cast<ON_SerialNumberMap*>(this)->Internal_HashTableInvalidate();

      const_cast<ON_SerialNumberMap*>(this)->m_sn_count -= m_sn_block0.m_purged;
      const_cast<ON_SerialNumberMap*>(this)->m_sn_purged -= m_sn_block0.m_purged;
      const_cast<ON_SerialNumberMap*>(this)->m_sn_block0.CullBlockHelper();
    }
    if ( !m_sn_block0.m_sorted )
    {
      // sort m_sn_block0
      // memory location for specific elements will be changed.
      // This will make the hash table invalid.
      const_cast<ON_SerialNumberMap*>(this)->Internal_HashTableInvalidate();

      const_cast<ON_SerialNumberMap*>(this)->m_sn_block0.SortBlockHelper();      
    }
    e = const_cast<struct SN_ELEMENT*>(&m_sn_block0.m_sn[m_sn_block0.m_count-1]);
  }

  i = (ON__UINT64)m_snblk_list_count;
  while(i--)
  {
    if ( m_snblk_list[i]->m_count > m_snblk_list[i]->m_purged )
    {
      if (e && e->m_sn > m_snblk_list[i]->m_sn1 )
        break;
      j = m_snblk_list[i]->m_count;
      while(j--)
      {
        if ( m_snblk_list[i]->m_sn[j].m_sn_active )
        {
          e = &m_snblk_list[i]->m_sn[j];
          break;
        }
      }
      break;
    }
  }

  return e;
}

struct ON_SerialNumberMap::SN_ELEMENT* ON_SerialNumberMap::FindSerialNumber(ON__UINT64 sn) const
{
  struct SN_ELEMENT* e = const_cast<ON_SerialNumberMap*>(this)->FindElementHelper(sn);
  return ( (e && e->m_sn_active) ? e : 0);
}

struct ON_SerialNumberMap::SN_ELEMENT* ON_SerialNumberMap::FindId(ON_UUID id) const
{
  if ( m_active_id_count > 0 && IdIsNotNil(&id) && IdIsNotEqual(&id,&m_inactive_id) )
    return Internal_HashTableFindId(id, IdCRC32(&id),true);

  return nullptr;
}

ON__UINT64 ON_SerialNumberMap::GetElements(
  ON__UINT64 sn0,
  ON__UINT64 sn1, 
  ON__UINT64 max_count,
  ON_SimpleArray<SN_ELEMENT>& elements
  ) const
{
  ON__UINT64 i,j,k,c;
  const SN_ELEMENT *ei, *ek;

  const int elements_count0 = elements.Count();

  if ( sn1 < sn0 || max_count <= 0 || m_sn_count <= m_sn_purged )
    return 0;

  if ( sn0+3 <= sn1 )
  {
    elements.Reserve(elements_count0+3);
    while ( sn0 <= sn1 )
    {
      ei = const_cast<ON_SerialNumberMap*>(this)->FindElementHelper(sn0++);
      if ( ei && ei->m_sn_active )
        elements.Append(*ei);
    }
    return (elements.Count() - elements_count0); 
  }

  ek = 0;
  k = 0;
  for ( j = 0; j < m_snblk_list_count; j++ )
  {
    if ( m_snblk_list[j]->m_sn1 < sn0 )
      continue;
    if ( sn1 < m_snblk_list[j]->m_sn0 )
      break;

    k = m_snblk_list[j]->m_count; // always > 0
    ek = &m_snblk_list[j]->m_sn[0];
    while ( ek->m_sn < sn0 || !ek->m_sn_active )
    {
      if ( --k )
      {
        if ((++ek)->m_sn > sn1)
        {
          ek = 0;
          break;
        }
      }
      else if ( ++j < m_snblk_list_count && m_snblk_list[j]->m_sn0 <= sn1 )
      {
        k = m_snblk_list[j]->m_count; // always > 0
        ek = &m_snblk_list[j]->m_sn[0];
      }
      else
      {
        ek = 0;
        break;
      }
    }
    if ( ek && ek->m_sn > sn1 )
      ek = 0;
    break;
  }

  // set c = estimate of number of items in m_snblk_list[]
  if ( ek )
  {
    c = m_snblk_list[j]->ActiveElementEstimate(ek->m_sn,sn1);
    for ( i = j+1; i < m_snblk_list_count && m_snblk_list[i]->m_sn0 <= sn1; i++ )
    {
      c += m_snblk_list[j]->ActiveElementEstimate(ek->m_sn,sn1);
    }
  }
  else
    c = 0;

  // determine where to begin searching in m_sn_block0
  i = 0;
  ei = 0;
  if (    m_sn_block0.m_count > m_sn_block0.m_purged
       && sn1 >= m_sn_block0.m_sn0
       && sn0 <= m_sn_block0.m_sn1
       && !m_sn_block0.m_sorted
     )
  {
    if ( !m_sn_block0.m_sorted )
    {
      if ( m_sn_block0.m_purged > 0 )
      {
        // memory location for specific elements will be changed.
        // This will make the hash table invalid.
        const_cast<ON_SerialNumberMap*>(this)->Internal_HashTableInvalidate();
        const_cast<ON_SerialNumberMap*>(this)->m_sn_count -= m_sn_block0.m_purged;
        const_cast<ON_SerialNumberMap*>(this)->m_sn_purged -= m_sn_block0.m_purged;
        const_cast<ON_SerialNumberMap*>(this)->m_sn_block0.CullBlockHelper();
        const_cast<ON_SerialNumberMap*>(this)->UpdateMaxSNHelper();
      }
      if ( m_sn_block0.m_count > 0 )
      {
        // memory location for specific elements will be changed.
        // This will make the hash table invalid.
        const_cast<ON_SerialNumberMap*>(this)->Internal_HashTableInvalidate();
        const_cast<ON_SerialNumberMap*>(this)->m_sn_block0.SortBlockHelper();
        if ( sn1 >= m_sn_block0.m_sn0 && sn0 <= m_sn_block0.m_sn1 )
        {
          i = m_sn_block0.m_count;
          ei = &m_sn_block0.m_sn[0];
        }
      }
    }
    else
    {
      i = m_sn_block0.m_count;
      ei = &m_sn_block0.m_sn[0];
      while ( ei->m_sn < sn0 || !ei->m_sn_active )
      {
        if ( --i )
          ei++;
        else
        {
          ei = 0;
          break;
        }
      }
      if ( ei && ei->m_sn > sn1 )
      {
        ei = 0;
      }
    }
  }

  // adjust c = estimate of number of items in m_snblk_list[]
  if ( ei )
    c += m_sn_block0.ActiveElementEstimate(ei->m_sn,sn1);
  if (c > (sn1-sn0+1) )
    c = (sn1-sn0+1);
  if ( c > 2*4096 )
    c = 2*4096;

  // reserve room for elements so we don't thrash memory
  // while growing a large dynamic array.
  elements.Reserve(elements.Count()+((int)c));

  // Add appropriate elements to elements[] array.
  while (ei || ek)
  {
    if (ei && (!ek || ei->m_sn < ek->m_sn) )
    {
      if ( ei->m_sn_active )
        elements.Append(*ei);
      if ( --i )
      {
        if ( (++ei)->m_sn > sn1 )
        {
          ei = 0;
        }
      }
      else
      {
        ei = 0;
      }
    }
    else 
    {
      if ( ek->m_sn_active )
        elements.Append(*ek);
      if ( --k )
      {
        if ( (++ek)->m_sn > sn1 )
        {
          ek = 0;
        }
      }
      else if (++j < m_snblk_list_count && sn1 <= m_snblk_list[j]->m_sn0 )
      {
        k = m_snblk_list[j]->m_count; // always > 0
        ek = &m_snblk_list[j]->m_sn[0];
      }
      else 
      {
        ek = 0;
      }
    }
  }
  
  return (elements.Count() - elements_count0);
}

ON_SerialNumberMap::SN_ELEMENT* ON_SerialNumberMap::Internal_HashTableRemoveElement(
  struct SN_ELEMENT* e,
  bool bRemoveFromHashBlock
  )
{
  if ( nullptr == e || 0 == e->m_id_active )
    return nullptr;

  e->m_id_active = 0;
  if ( m_active_id_count > 0 )
  {
    m_active_id_count--;
    // save this id.  When objects are replaced, this id will
    // be added back and saving it in m_inactive_id will 
    // prevent having to check for it in the hash table.
    m_inactive_id = e->m_id;
  }
  else
  {
    ON_ERROR("ON_SerialNumberMap - m_active_id_count corruption");
    m_inactive_id = ON_nil_uuid;
  }

  if ( m_bHashTableIsValid && bRemoveFromHashBlock )
  {
    // Hash table is valid - remove the element from the table
    struct SN_ELEMENT** hash_table_block = Internal_HashTableBlock(e->m_id_crc32);
    const ON__UINT32 hash_i = ON_SerialNumberMap::Internal_HashTableBlockRowIndex(e->m_id_crc32);
    struct SN_ELEMENT* prev = nullptr;
    struct SN_ELEMENT* h;
    for ( h = hash_table_block[hash_i]; h; h = h->m_next )
    {
      if (h == e)
      {
        if ( prev )
          prev->m_next = h->m_next;
        else
          hash_table_block[hash_i] = h->m_next;
        break;
      }
      prev = h;
    }
    if (nullptr == h)
    {
      ON_ERROR("id not found in hash table.");
    }
  }

  e->m_next = nullptr;
  return e;
}

struct ON_SerialNumberMap::SN_ELEMENT* 
ON_SerialNumberMap::RemoveSerialNumberAndId(ON__UINT64 sn)
{
  struct SN_ELEMENT* e = FindElementHelper(sn);
  if ( e && e->m_sn_active )
  {
    Internal_HashTableRemoveElement(e,true);

    e->m_sn_active = 0;
    m_sn_purged++;
    if ( m_e_blk->m_count == ++m_e_blk->m_purged )
    {
      // every item in the block is purged
      if ( m_e_blk == &m_sn_block0 )
      {
        // Every element in m_sn_block0 is purged.
        // Empty m_sn_block0.
        m_sn_count -= m_sn_block0.m_count;
        m_sn_purged -= m_sn_block0.m_count;
        m_sn_block0.EmptyBlock();
      }
      else if ( m_e_blk->m_count > 1 )
      {
        // m_e_blk is in m_sn_list[] and every element
        // in m_e_blk is purged. Remove all but
        // except one of these elements.
        // Note: We cannot empty blocks in the m_sn_list[] because
        //       this class has code that assumes the blocks
        //       in m_sn_list[] have m_count >= 1.  This makes
        //       the class generally faster.  There is code in 
        //       FindElementHelper() the keeps the m_sn_list[]
        //       blocks relatively tidy.
        m_sn_count  -= (m_e_blk->m_count-1);
        m_sn_purged -= (m_e_blk->m_count-1);
        m_e_blk->m_count = 1;
        m_e_blk->m_purged = 1;
        m_e_blk->m_sn0 = m_e_blk->m_sn1 = m_e_blk->m_sn[0].m_sn;
      }
    }
    return e;
  }

  return 0;
}

struct ON_SerialNumberMap::SN_ELEMENT* 
ON_SerialNumberMap::RemoveId(ON__UINT64 sn, ON_UUID id)
{
  if ( m_active_id_count > 0 && IdIsNotNil(&id) && IdIsNotEqual(&id,&m_inactive_id))
  {
    struct SN_ELEMENT* e;
    if ( false == m_bHashTableIsValid )
    {
      if (sn > 0)
      {
        // We can avoid rebuilding the hash table.
        // Use the serial number to find the element.
        e = FindSerialNumber(sn);
        if (nullptr != e)
          return Internal_HashTableRemoveElement(e,true);
      }
      else
      {
        // check most recently added elements
        e = Internal_HashTableFindId(id, 0, false);
        if (nullptr != e)
        {
          // got lucky
          return Internal_HashTableRemoveElement(e,true);
        }
      }
      
      // have to build hash table (expensive)
      Internal_HashTableBuild();
    }

    const ON__UINT32 id_crc32 = IdCRC32(&id);
    struct SN_ELEMENT** hash_table_block = Internal_HashTableBlock(id_crc32);
    const ON__UINT32 hash_i = ON_SerialNumberMap::Internal_HashTableBlockRowIndex(id_crc32);
    struct SN_ELEMENT* prev = nullptr;
    for (e = hash_table_block[hash_i]; nullptr != e; e = e->m_next)
    {
      if ( IdIsEqual(&e->m_id,&id) )
      {
        if (nullptr != prev)
          prev->m_next = e->m_next;
        else
          hash_table_block[hash_i] = e->m_next;
        return Internal_HashTableRemoveElement(e,false);
      }
      prev = e;
    }
  }

  return nullptr;
}


int ON_SN_BLOCK::CompareMaxSN(const void* a, const void* b)
{
  const ON__UINT64 sna = (*((const ON_SN_BLOCK*const*)a))->m_sn1;
  const ON__UINT64 snb = (*((const ON_SN_BLOCK*const*)b))->m_sn1;
  if ( sna < snb )
  {
    return (0 == sna) ? 1 : -1;
  }
  if ( snb < sna )
  {
    return (0 == snb) ? -1 : 1;
  }
  return 0;
}

ON__UINT64 ON_SN_BLOCK::ActiveElementEstimate(ON__UINT64 sn0, ON__UINT64 sn1) const
{
  ON__UINT64 c = m_count-m_purged;
  if ( c > 0 )
  {
    if ( sn0 < m_sn0 )
      sn0 = m_sn0;
    if ( sn1 > m_sn1 )
      sn1 = m_sn1;
    sn1 -= sn0;
    sn1++;
    if (c > sn1)
      c = sn1;
  }
  return c;
}

static bool ON_SerialNumberMap_IsNotValid()
{
  return ON_IsNotValid();
}

bool ON_SerialNumberMap::IsValid(
   bool bBuildHashTable,
   ON_TextLog* textlog
   ) const
{
  ON__UINT64 i, c, pc, aic;

  aic = 0;

  const bool bTestHashTable = (m_active_id_count > 0 && (bBuildHashTable || m_bHashTableIsValid));
  if (bTestHashTable && false == m_bHashTableIsValid)
  {
    const_cast<ON_SerialNumberMap*>(this)->Internal_HashTableBuild();
    if (false == m_bHashTableIsValid || nullptr == m_hash_table_blocks || m_hash_block_count <= 0)
    {
      if ( textlog )
        textlog->Print("Unable to build hash table.\n");
      return ON_SerialNumberMap_IsNotValid();
    }
  }

  if ( !m_sn_block0.IsValidBlock(
    textlog,
    bTestHashTable ? m_hash_table_blocks : nullptr,
    bTestHashTable ? m_hash_block_count : 0,
    &aic) 
    )
  {
    if ( textlog )
      textlog->Print("m_sn_block0 is not valid\n");
    return ON_SerialNumberMap_IsNotValid();
  }

  c = m_sn_block0.m_count;
  pc = m_sn_block0.m_purged;

  for ( i = 0; i < m_snblk_list_count; i++ )
  {
    if ( 0 == m_snblk_list[i]->m_count )
    {
      if ( textlog )
        textlog->Print("m_snblk_list[%d] is empty\n",i);
      return ON_SerialNumberMap_IsNotValid();
    }
    if ( 1 != m_snblk_list[i]->m_sorted )
    {
      if ( textlog )
        textlog->Print("m_snblk_list[%d] is not sorted\n",i);
      return ON_SerialNumberMap_IsNotValid();
    }
    if ( !m_snblk_list[i]->IsValidBlock(
      textlog,
      bTestHashTable ? m_hash_table_blocks : nullptr,
      bTestHashTable ? m_hash_block_count : 0,
      &aic) 
      )
    {
      if ( textlog )
        textlog->Print("m_snblk_list[%d] is not valid\n",i);
      return ON_SerialNumberMap_IsNotValid();
    }
    c += m_snblk_list[i]->m_count;
    pc += m_snblk_list[i]->m_purged;
    if ( i>0 && m_snblk_list[i]->m_sn0 <= m_snblk_list[i-1]->m_sn1 )
    {
      if ( textlog )
        textlog->Print("m_snblk_list[%d]->m_sn0 <= m_snblk_list[%d]->m_sn1\n",i,i-1);
      return ON_SerialNumberMap_IsNotValid();
    }
  }

  if ( c != m_sn_count )
  {
    if ( textlog )
      textlog->Print("m_sn_count=%d (should be %d) is not correct\n",m_sn_count,c);
    return ON_SerialNumberMap_IsNotValid();
  }

  if ( pc != m_sn_purged )
  {
    if ( textlog )
      textlog->Print("m_sn_purged=%d (should be %d) is not correct\n",m_sn_purged,pc);
    return ON_SerialNumberMap_IsNotValid();
  }

  if ( m_active_id_count != aic )
  {
    if ( textlog )
      textlog->Print("m_active_id_count=%d (should be %d) is not correct\n",m_active_id_count,aic);
    return ON_SerialNumberMap_IsNotValid();
  }

  if ( m_active_id_count + m_sn_purged > m_sn_count )
  {
    if ( textlog )
      textlog->Print("m_active_id_count=%d > %d = (m_sn_count-m_sn_purged)\n",m_active_id_count,m_sn_count-m_sn_purged);
    return ON_SerialNumberMap_IsNotValid();
  }

  if (bTestHashTable)
  {
    c = 0;
    for (ON__UINT32 hash_block_index = 0; hash_block_index < m_hash_block_count; hash_block_index++)
    {
      const SN_ELEMENT*const* hash_table_block = m_hash_table_blocks[hash_block_index];
      for (ON__UINT32 hash_i = 0; hash_i < ON_SN_BLOCK::ID_HASH_BLOCK_CAPACITY; hash_i++)
      {
        for (const SN_ELEMENT* e = hash_table_block[hash_i]; nullptr != e && c <= m_active_id_count; e = e->m_next)
        {
          if (
            hash_block_index != Internal_HashTableBlockIndex(e->m_id_crc32)
            || hash_i != ON_SerialNumberMap::Internal_HashTableBlockRowIndex(e->m_id_crc32)
            )
          {
            if (textlog)
              textlog->Print("m_hash_table linked lists are corrupt.\n");
            return ON_SerialNumberMap_IsNotValid();
          }
          c++;
        }
      }
    }

    if (c > m_active_id_count)
    {
      if (textlog)
        textlog->Print("m_hash_table[] linked lists have too many elements.\n");
      return ON_SerialNumberMap_IsNotValid();
    }
  }

  return true;
}

ON__UINT64 ON_SerialNumberMap::GarbageCollectMoveHelper(ON_SN_BLOCK* dst,ON_SN_BLOCK* src)
{
  // This helper is used by GarbageCollectHelper and moves
  // as many entries as possible from src to dst.  
  // Returns: the number of entries transferred.
  ON__UINT32 i,j,n;
  if ( src && dst )
  {
    n = ON_SN_BLOCK::SN_BLOCK_CAPACITY - dst->m_count;
    if ( src->m_count < n )
      n = src->m_count;
    if ( n > 0 )
    {
      if ( 0 == dst->m_count )
      {
        dst->EmptyBlock();
      }
      if ( 0 == src->m_sorted )
      {
        dst->m_sorted = 0;
        if ( 0 == dst->m_count )
        {
          dst->m_sn0 = src->m_sn0;
          dst->m_sn1 = src->m_sn1;
        }
      }
      memcpy(&dst->m_sn[dst->m_count],&src->m_sn[0],(size_t)(n*sizeof(src->m_sn[0])));
      dst->m_count += n;
      if ( dst->m_sorted )
      {
        dst->m_sn0 = dst->m_sn[0].m_sn; // set m_sn0 because input dst could have count 0
        dst->m_sn1 = dst->m_sn[dst->m_count-1].m_sn;
      }
      else 
      {
        if ( dst->m_sn0 > src->m_sn0 )
          dst->m_sn0 = src->m_sn0;
        if ( dst->m_sn1 < src->m_sn1 )
          dst->m_sn1 = src->m_sn1;
      }
      i = 0; j = n;
      while ( j < src->m_count )
      {
        src->m_sn[i++] = src->m_sn[j++];
      }
      src->m_count = i;
      if ( src->m_count > 0 )
      {
        if ( src->m_sorted )
          src->m_sn0 = src->m_sn[0].m_sn;
      }
      else
      {
        src->EmptyBlock();
      }
    }
  }
  else
  {
    n = 0;
  }
  return n;
}

void ON_SerialNumberMap::GarbageCollectHelper()
{
  ON__UINT64 i,m;
  ON__UINT32 j,k,n;

  // This is a helper function.  The caller
  // should check that ON_SN_BLOCK::SN_BLOCK_CAPACITY == m_sn_block0.m_count
  // before calling it.

  // memory location for specific elements will be changed.
  // This will make the hash table invalid.
  Internal_HashTableInvalidate();

  if ( m_sn_block0.m_purged > 0 )
  {
    m_sn_count -= m_sn_block0.m_purged;
    m_sn_purged -= m_sn_block0.m_purged;
    m_sn_block0.CullBlockHelper();
    if ( !m_sn_block0.m_sorted )
      m_sn_block0.SortBlockHelper();
    if ( 0 == m_snblk_list_count )
      m_private->SetMaxSn(m_sn_block0.m_sn1);
    if ( m_sn_block0.m_count < 7*(ON_SN_BLOCK::SN_BLOCK_CAPACITY/8) )
      return;
  }
  else if ( !m_sn_block0.m_sorted )
  {
    m_sn_block0.SortBlockHelper();
    if ( 0 == m_snblk_list_count )
      m_private->SetMaxSn(m_sn_block0.m_sn1);
  }

  // Remove all purged serial numbers from every block
  // and make sure every block is sorted.
  m_sn_purged = 0;
  m_sn_count = m_sn_block0.m_count;
  i = m_snblk_list_count;
  while (i--)
  {
    if ( m_snblk_list[i]->m_purged > 0 )
    {
      // The next call may empty m_snblk_list[i].
      m_snblk_list[i]->CullBlockHelper();
    }
    m_sn_count += m_snblk_list[i]->m_count;
  }

  // Put empty blocks at the end of the list
  for ( i = 0; i < m_snblk_list_count; i++ )
  {
    if ( 0 == m_snblk_list[i]->m_count )
    {
      // m_snblk_list[i] is empty ...
      for(m = i+1; m < m_snblk_list_count; m++ )
      {
        if ( m_snblk_list[m]->m_count > 0 )
        {
          // ... and m_snblk_list[m] is not empty
          ON_qsort(m_snblk_list+i,(size_t)(m_snblk_list_count-i),sizeof(*m_snblk_list),ON_SN_BLOCK::CompareMaxSN);
          break;
        }
      }
      while ( m_snblk_list_count > 0 && 0 == m_snblk_list[m_snblk_list_count-1]->m_count )
        m_snblk_list_count--;
      break;
    }
  }

  if (    m_snblk_list_count > 0 
       && m_snblk_list[m_snblk_list_count-1]->m_sn1 > m_sn_block0.m_sn0 
     )
  {
    // Merge the serial number lists so the blocks in m_sn_list[]
    // have the lowest serial numbers and m_sn_block0.m_sn[] contains
    // the largest.
    ON__UINT32 snarray_count = 0;
    struct SN_ELEMENT* snarray = (struct SN_ELEMENT*)onmalloc(2*ON_SN_BLOCK::SN_BLOCK_CAPACITY*sizeof(snarray[0]));
    for ( i = 0; i < m_snblk_list_count && m_sn_block0.m_count > 0; i++ )
    {
      if ( m_snblk_list[i]->m_sn1 < m_sn_block0.m_sn0 )
        continue;

      // Move some entries in m_sn_block0.m_sn[] 
      // to m_snblk_list[i]->m_sn[].
      ON_SN_BLOCK* blk = m_snblk_list[i];
      const ON__UINT64 sn1 = (i < m_snblk_list_count-1) 
                             ? m_snblk_list[i+1]->m_sn0 
                             : (m_sn_block0.m_sn1+1);
      snarray_count = j = k = 0;
      while(j < blk->m_count && k < m_sn_block0.m_count )
      {
        if ( blk->m_sn[j].m_sn < m_sn_block0.m_sn[k].m_sn )
        {
          snarray[snarray_count++] = blk->m_sn[j++];
        }
        else if ( m_sn_block0.m_sn[k].m_sn < sn1 )
        {
          snarray[snarray_count++] = m_sn_block0.m_sn[k++];
        }
        else
        {
          // If m_sn_block0.m_sn[m_sn_block0.m_count-1].m_sn is the largest
          // value, then we should get j == blk->m_count exit.
          // If blk->m_sn[blk->m_count-1].m_sn is the largest value,
          // then we should get k == m_sn_block0.m_count and exit.
          ON_ERROR("Bogus information - should never get here");
          break;
        }
      }
      n = blk->m_count-j;
      if ( n > 0 )
      {
        memcpy(&snarray[snarray_count],&blk->m_sn[j],(size_t)(n*sizeof(snarray[0])));
        snarray_count += n;
      }
      else
      {
        while ( k < m_sn_block0.m_count && m_sn_block0.m_sn[k].m_sn < sn1 )
          snarray[snarray_count++] = m_sn_block0.m_sn[k++];
      }
      n = (snarray_count > ON_SN_BLOCK::SN_BLOCK_CAPACITY) 
        ? ON_SN_BLOCK::SN_BLOCK_CAPACITY 
        : snarray_count;
      if ( k < m_sn_block0.m_count )
      {
        memcpy(&snarray[snarray_count],
               &m_sn_block0.m_sn[k],
               (size_t)((m_sn_block0.m_count-k)*sizeof(snarray[0]))
               );
        snarray_count += (m_sn_block0.m_count-k);
      }
      blk->m_count = n;
      memcpy(&blk->m_sn[0],snarray,(size_t)(blk->m_count*sizeof(blk->m_sn[0])));
      blk->m_sn0 = blk->m_sn[0].m_sn;
      blk->m_sn1 = blk->m_sn[blk->m_count-1].m_sn;
      if ( snarray_count > n )
      {
        // put the end of snarray[] (the largest serial numbers)
        // in m_sn_block0.m_sn[].
        m_sn_block0.m_count = (snarray_count-n);
        memcpy(&m_sn_block0.m_sn[0],
               &snarray[n],
               (size_t)(m_sn_block0.m_count*sizeof(m_sn_block0.m_sn[0]))
               );
        m_sn_block0.m_sn0 = m_sn_block0.m_sn[0].m_sn;
        m_sn_block0.m_sn1 = m_sn_block0.m_sn[m_sn_block0.m_count-1].m_sn;
      }
      else
      {
        m_sn_block0.EmptyBlock();
      }
    }
    onfree(snarray);
    snarray = 0;
  }

  // Compact the blocks in m_sn_list[]
  for ( i = 0; i < m_snblk_list_count; i++ )
  {
    for ( m = i+1; m < m_snblk_list_count; m++ )
    {
      if ( m_snblk_list[i]->m_count >= ON_SN_BLOCK::SN_BLOCK_CAPACITY )
        break;
      GarbageCollectMoveHelper(m_snblk_list[i],m_snblk_list[m]);
    }
  }
  while ( m_snblk_list_count > 0 && 0 == m_snblk_list[m_snblk_list_count-1]->m_count )
  {
    m_snblk_list_count--;
  }

  // Make sure m_sn_block0.m_an[] is has plenty of room
  if ( m_sn_block0.m_count > ON_SN_BLOCK::SN_BLOCK_CAPACITY/4 )
  {
    if ( m_snblk_list_count > 0 )
    {
      GarbageCollectMoveHelper(m_snblk_list[m_snblk_list_count-1],&m_sn_block0);
    }
    if ( m_sn_block0.m_count > ON_SN_BLOCK::SN_BLOCK_CAPACITY/2 )
    {
      // Need to add a new block to m_snblk_list[]
      if ( m_snblk_list_count == m_snblk_list_capacity )
      {
        // Add room to store more pointers to blocks in the m_sn_list[]
        i = m_snblk_list_capacity;
        m_snblk_list_capacity += 32;
        m = m_snblk_list_capacity*sizeof(m_snblk_list[0]);
        m_snblk_list = (ON_SN_BLOCK**)((0 == m_snblk_list)
                     ? onmalloc((size_t)m)
                     : onrealloc(m_snblk_list,(size_t)m));
        while ( i < m_snblk_list_capacity )
          m_snblk_list[i++] = 0;
      }
      if ( 0 == m_snblk_list[m_snblk_list_count] )
      {
        // add room to store at more serial numbers
        m_snblk_list[m_snblk_list_count] = (ON_SN_BLOCK*)onmalloc(sizeof(*(m_snblk_list[m_snblk_list_count])));
      }
      *m_snblk_list[m_snblk_list_count++] = m_sn_block0;
      m_sn_block0.EmptyBlock();
    }
  }
}

struct ON_SerialNumberMap::SN_ELEMENT* ON_SerialNumberMap::AddSerialNumber(ON__UINT64 sn)
{
  if ( sn <= 0 )
    return 0;
  struct SN_ELEMENT* e = FindElementHelper(sn);
  if ( e )
  {
    if ( 0 == e->m_sn_active )
    {
      m_sn_purged--;
      m_e_blk->m_purged--;
      memset(e,0,sizeof(*e));
      e->m_sn = sn;
      e->m_sn_active = 1;
    }
  }
  else
  {
    if ( ON_SN_BLOCK::SN_BLOCK_CAPACITY == m_sn_block0.m_count )
    {
      // make room in m_sn_block0 for the new serial number
      GarbageCollectHelper();    
    }

    if ( 0 == m_sn_block0.m_count )
    {
      m_sn_block0.m_sn0 = m_sn_block0.m_sn1 = sn;
      m_sn_block0.m_sorted = 1;
    }
    else
    {
      if ( sn > m_sn_block0.m_sn1 )
      {
        m_sn_block0.m_sn1 = sn;
      }
      else
      {
        if ( sn < m_sn_block0.m_sn0 )
          m_sn_block0.m_sn0 = sn;
        m_sn_block0.m_sorted = 0;
      }        
    }
    if ( sn > m_private->MaxSn() )
      m_private->SetMaxSn(sn);
    if (sn < UINT32_MAX && sn > m_private->LowerMaxSn())
      m_private->SetLowerMaxSn(sn);

    m_sn_count++;
    e = &m_sn_block0.m_sn[m_sn_block0.m_count++];
    memset(e,0,sizeof(*e));
    e->m_sn = sn;
    e->m_sn_active = 1;
  }

  return e;
}

struct ON_SerialNumberMap::SN_ELEMENT* ON_SerialNumberMap::Internal_HashTableFindId(
  ON_UUID id,
  ON__UINT32 id_crc32,
  bool bBuildTableIfNeeded
  ) const
{
  // Caller checks that m_active_id_count > 0 && id != nil && id != m_inactive_id

  if (false == m_bHashTableIsValid)
  {
    for (ON__UINT32 i = 0; i < 8 && i < m_sn_block0.m_count; i++)
    {
      if ( IdIsEqual(&id,&m_sn_block0.m_sn[i].m_id) )
      {
        ON_SerialNumberMap::SN_ELEMENT* e = const_cast<ON_SerialNumberMap::SN_ELEMENT*>(&m_sn_block0.m_sn[i]);
        if ( 0 != e->m_id_active )
          return e;
      }
    }
    if ( false == bBuildTableIfNeeded )
      return nullptr;

    // expensive
    Internal_HashTableBuild();
    if ( false == m_bHashTableIsValid )
      return nullptr;
  }

  for (
    ON_SerialNumberMap::SN_ELEMENT* e = m_hash_table_blocks[id_crc32 % m_hash_block_count][(id_crc32 / ON_SN_BLOCK::ID_HASH_BLOCK_CAPACITY) % ON_SN_BLOCK::ID_HASH_BLOCK_CAPACITY];
    nullptr != e;
    e = e->m_next
    )
  {
    if ( IdIsEqual(&id,&e->m_id) )
      return e;
  }

  return nullptr;
}


struct ON_SerialNumberMap::SN_ELEMENT* ON_SerialNumberMap::AddSerialNumberAndId(ON__UINT64 sn,ON_UUID id)
{
  struct SN_ELEMENT* e = AddSerialNumber(sn);

  if (nullptr == e || 0 != e->m_id_active)
  {
    // There was an active element with serial number = sn
    return e;
  }
  
  ON__UINT32 id_crc32 = 0;

  bool bNewId = IdIsNil(&id);
  if ( false == bNewId )
  {
    id_crc32 = IdCRC32(&id);
    if (IdIsEqual(&m_inactive_id, &id))
    {
      // This id was recently removed and is now being added back
      // (which turns out to be a common occurrence - go figure).
      // No need to check for duplicates.
      m_inactive_id = ON_nil_uuid;
    }
    else if (m_active_id_count > 0)
    {
      if (nullptr != Internal_HashTableFindId(id, id_crc32, true))
        bNewId = true; // id is in use - make a new one
    }
  }

  if ( bNewId )
  {
    // The input id is nil or in use. Create a new id. No need to check for duplicates
    id = ON_CreateId();
    id_crc32 = IdCRC32(&id);
  }

  if (m_bHashTableIsValid)
  {
    // Growing must happen vefore e->m_id* values are set.
    Internal_HashTableGrow();

    // Add id to hash table
    struct SN_ELEMENT** hash_table_block = Internal_HashTableBlock(id_crc32);
    const ON__UINT32 hash_i = ON_SerialNumberMap::Internal_HashTableBlockRowIndex(id_crc32);
    e->m_next = hash_table_block[hash_i];
    hash_table_block[hash_i] = e;
  }
  
  // e->m_id and related setting must be initialized after any
  // possible calls to Internal_HashTableGrow() to prevent add
  // e twice.
  e->m_id = id;
  e->m_id_active = 1;
  e->m_id_crc32 = id_crc32;
  m_active_id_count++;

  return e;
}


void ON_SerialNumberMap::Internal_HashTableInvalidate()
{
  // This helper function is called when the memory
  // locations of SN_ELEMENTs are going to change.
  // and the pointers saved in m_hash_table[] and
  // SN_ELEMENT::next may become invalid. When a
  // valid m_hash_table[] is needed at a later time,
  // BuildHashTableHelper() will restore it.
  if ( m_bHashTableIsValid )
  {
    m_bHashTableIsValid = false;
  }
}

bool ON_SerialNumberMap::Internal_HashTableRemoveSerialNumberBlock(const ON_SN_BLOCK* blk)
{
  // quickly remove every id in the block from the hash table.
  // This is done when the block is small compared to the
  // size of the hash table and removing the elements from
  // the hash table, rearranging the block, and then adding
  // the elements back into the hash table is faster than
  // simply rebuilding the hash table.
  //
  // The 128 multiplier is determined as follows:
  // - C = average number of elements with the same hash index
  //     = m_active_id_count/m_hash_capacity.
  // - D = cost of destroying hash table = time to memset the table
  //       to zero.
  // - H = cost of calculating the hash table index of an id.
  // - A = The cost of adding an element to the hash table is
  //       H + two pointer assignments with is essentially H.
  // - F = The average cost of finding an element in the hash
  //       table is H plus going through half the linked list
  //       of elements at that hash index (C/2 pointer dereferences).
  // - B = number of elements in a block.
  // - I = (number times a valid hash table is destroyed)/
  //       (number of times the hash table is rebuilt).
  // - R = rebuild cost = A*m_active_id_count.
  // - Keeping the the has table up to date only makes sense if
  //   R > I*(A+F)*active_id_count
  //   it is needed often enough to justify ...
  bool rc = false;
  if ( m_bHashTableIsValid && m_active_id_count > 128*blk->m_count )
  {
    const SN_ELEMENT* e;
    struct SN_ELEMENT** hash_table_block;
    SN_ELEMENT* h;
    SN_ELEMENT* prev;
    ON__UINT32 i;
    rc = true;
    for (e = blk->m_sn, i = blk->m_count; i--; e++)
    {
      if ( 0 == e->m_id_active )
        continue;
      hash_table_block = Internal_HashTableBlock(e->m_id_crc32);
      ON__UINT32 hash_i = Internal_HashTableBlockRowIndex(e->m_id_crc32);
      prev = 0;
      for ( h = hash_table_block[hash_i]; nullptr !=  h; h = h->m_next )
      {
        if (h == e)
        {
          // Do not change value of SN_ELEMENT's m_id_active.
          // This value is needed by AddBlockToHashTableHelper()
          // when it add the element back in.
          m_active_id_count--;
          if (prev)
            prev->m_next = h->m_next;
          else
            hash_table_block[hash_i] = h->m_next;
          break;
        }
        prev = h;
      }
    }
  }
  return rc;
}

ON__UINT64 ON_SerialNumberMap::Internal_HashTableAddSerialNumberBlock( ON_SN_BLOCK* blk) const
{
  ON__UINT32 active_id_count = 0; // 4 bytes is enough for a single block

  if ( m_bHashTableIsValid && nullptr != blk && blk->m_purged < blk->m_count )
  {
    SN_ELEMENT* e = blk->m_sn;
    SN_ELEMENT* e1 = e + blk->m_count;
    struct SN_ELEMENT** hash_table_block;
    ON__UINT32 hash_i;
    if (1 == m_hash_block_count)
    {
      hash_table_block = m_hash_table_blocks[0];
      for (/* empty init */; e < e1; e++)
      {
        if (0 == e->m_id_active)
        {
          e->m_next = nullptr;
          continue;
        }
        hash_i = ON_SerialNumberMap::Internal_HashTableBlockRowIndex(e->m_id_crc32);
        e->m_next = hash_table_block[hash_i];
        hash_table_block[hash_i] = e;
        active_id_count++;
      }
    }
    else
    {
      for (/* empty init */; e < e1; e++)
      {
        if (0 == e->m_id_active)
        {
          e->m_next = nullptr;
          continue;
        }
        hash_table_block = Internal_HashTableBlock(e->m_id_crc32);
        hash_i = ON_SerialNumberMap::Internal_HashTableBlockRowIndex(e->m_id_crc32);
        e->m_next = hash_table_block[hash_i];
        hash_table_block[hash_i] = e;
        active_id_count++;
      }
    }
  }

  return (ON__UINT64)active_id_count; // entire map may contain many blocks and more than 2^32 entries.
}


ON__UINT32 ON_SerialNumberMap::Internal_HashTableBlockIndex(
  ON__UINT32 id_crc32
  ) const
{
  return (id_crc32 % m_hash_block_count);
}

ON__UINT32 ON_SerialNumberMap::Internal_HashTableBlockRowIndex(
  ON__UINT32 id_crc32
  )
{
  return (id_crc32/ON_SN_BLOCK::ID_HASH_BLOCK_CAPACITY) % ON_SN_BLOCK::ID_HASH_BLOCK_CAPACITY;
}

ON_SerialNumberMap::SN_ELEMENT** ON_SerialNumberMap::Internal_HashTableBlock(
  ON__UINT32 id_crc32
  ) const
{
  return m_hash_table_blocks[id_crc32 % m_hash_block_count];
}

void ON_SerialNumberMap::Internal_HashTableGrow() const
{
  if (m_active_id_count >= m_hash_capacity && m_hash_block_count < ON_SN_BLOCK::ID_HASH_BLOCK_CAPACITY)
  {
    // Add capacity to the hash table.

    ON__UINT64 sz = (2U*m_hash_block_count);
    const ON__UINT32 target_linked_list_length = 4U;
    while (sz*((ON__UINT64)(target_linked_list_length*ON_SN_BLOCK::ID_HASH_BLOCK_CAPACITY)) <= m_active_id_count)
      sz++;
    const ON__UINT64 max_hash_block_count = (ON__UINT64)ON_SN_BLOCK::ID_HASH_BLOCK_CAPACITY;
    ON__UINT32 hash_block_count = (ON__UINT32)((sz < max_hash_block_count) ? sz : max_hash_block_count);
    if ( 0 == hash_block_count )
      hash_block_count = 1;
    if (m_hash_block_count < hash_block_count )
    {
      const size_t sizeof_hash_table_block = ON_SN_BLOCK::ID_HASH_BLOCK_CAPACITY*sizeof(m_hash_table_blocks[0][0]);
      if (0 == m_hash_block_count)
      {
        m_hash_table_blocks = (SN_ELEMENT***)onmalloc(2 * sizeof_hash_table_block);
        m_hash_table_blocks[0] = (SN_ELEMENT**)(m_hash_table_blocks + ON_SN_BLOCK::ID_HASH_BLOCK_CAPACITY);
        m_hash_block_count = 1;
      }
      while (m_hash_block_count < hash_block_count)
      {
        m_hash_table_blocks[m_hash_block_count] = (SN_ELEMENT**)onmalloc(sizeof_hash_table_block);
        if (nullptr == m_hash_table_blocks[m_hash_block_count])
          break;
        m_hash_block_count++;
      }

      m_hash_capacity = target_linked_list_length*ON_SN_BLOCK::ID_HASH_BLOCK_CAPACITY;
      m_hash_capacity *= m_hash_block_count;
      if (m_bHashTableIsValid || 0 == m_active_id_count)
      {
        // Invalidate() is necessary in order for Initialize()
        // to rebuild the has information.
        const_cast<ON_SerialNumberMap*>(this)->Internal_HashTableInvalidate();
        Internal_HashTableInitialize();
      }
    }
  }
}

void ON_SerialNumberMap::Internal_HashTableInitialize() const
{
  // This function is called when code requires
  // m_hash_table[] to be valid so an id can be looked up.
  if (false == m_bHashTableIsValid && m_hash_block_count > 0)
  {
    for (ON__UINT32 i = 0; i < m_hash_block_count; i++)
      memset(m_hash_table_blocks[i], 0, ON_SN_BLOCK::ID_HASH_BLOCK_CAPACITY*sizeof(m_hash_table_blocks[0][0]));

    // m_bHashTableIsValid must be true
    // before calling Internal_HashTableAddSerialNumberBlock()
    m_bHashTableIsValid = true;

    ON__UINT64 active_id_count = 0;
    for (ON__UINT64 snblk_i = 0; snblk_i < m_snblk_list_count; snblk_i++)
      active_id_count += Internal_HashTableAddSerialNumberBlock(m_snblk_list[snblk_i]);

    // Add most recent entries last so they appear at the beginning of the 
    // hash table linked lists.
    active_id_count += Internal_HashTableAddSerialNumberBlock(const_cast<ON_SN_BLOCK*>(&m_sn_block0));

    if (active_id_count != m_active_id_count)
    {
      ON_ERROR("m_active_id_count was corrupt and had to be fixed.");
      const_cast<ON_SerialNumberMap*>(this)->m_active_id_count = active_id_count;
    }

  }
}

void ON_SerialNumberMap::Internal_HashTableBuild() const
{
  // This function is called when code requires
  // m_hash_table[] to be valid so an id can be looked up.
  if ( false == m_bHashTableIsValid && m_active_id_count > 0 )
  {
    // The hash table is dirty because elements
    // have moved in memory.  Rebuild it putting
    // the newest elements first.
    Internal_HashTableGrow();
    Internal_HashTableInitialize();
  }
}


void ON_SerialNumberMap::SN_ELEMENT::Dump(ON_TextLog& text_log) const
{
  text_log.Print("m_id = ");
  text_log.Print(m_id);
  text_log.Print("\nm_sn = %d\n",m_sn);
  text_log.Print("m_sn_active = %d\n",m_sn_active);
  text_log.Print("m_id_active = %d\n",m_id_active);
}


void ON_SN_BLOCK::Dump(ON_TextLog& text_log) const
{
  text_log.Print("m_count = %d\n",m_count);
  text_log.Print("m_purged = %d\n",m_purged);
  text_log.Print("m_sorted = %d\n",m_sorted);
  text_log.Print("m_sn0 = %d\n",m_sn0);
  text_log.Print("m_sn1 = %d\n",m_sn1);
  if ( m_count > 0 )
  {
    text_log.Print("m_sn[0]\n");
    text_log.PushIndent();
    m_sn[0].Dump(text_log);
    text_log.PopIndent();
    if ( m_count > 1 )
    {
      text_log.Print("m_sn[%d]\n",m_count-1);
      text_log.PushIndent();
      m_sn[m_count-1].Dump(text_log);
      text_log.PopIndent();
    }
  }
}

void ON_SerialNumberMap::Dump(ON_TextLog& text_log) const
{
  text_log.Print("m_maxsn = %d\n", m_private->MaxSn());
  text_log.Print("m_sn_count = %d\n",m_sn_count);
  text_log.Print("m_sn_purged = %d\n",m_sn_purged);
  text_log.Print("m_active_id_count = %d\n",m_sn_purged);
  text_log.Print("m_bHashTableIsValid = %d\n",m_bHashTableIsValid);
  text_log.Print("m_snblk_list_capacity = %d\n",m_snblk_list_capacity);
  text_log.Print("m_snblk_list_count = %d\n",m_snblk_list_count);
  
  text_log.Print("m_sn_block0\n");
  text_log.PushIndent();
  m_sn_block0.Dump(text_log);
  text_log.PopIndent();

  for ( size_t i = 0; i < m_snblk_list_count; i++ )
  {
    text_log.Print("m_snblk_list[%d]\n",i);
    text_log.PushIndent();
    m_snblk_list[i]->Dump(text_log);
    text_log.PopIndent();
  }
}
