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

ON__UINT32 ON_Hash32TableItem::Hash32FromSHA1Hash(
  const class ON_SHA1_Hash& sha1_hash
  )
{
  return *(const ON__UINT32*)&sha1_hash;
}

ON__UINT32 ON_Hash32TableItem::Hash32FromId(
  const ON_UUID& id
  )
{
  return ON_CRC32(0, sizeof(ON_UUID), &id);
}

ON__UINT32 ON_Hash32TableItem::HashTableSerialNumber() const
{
  return m_internal_hash_table_sn;
}

ON__UINT32 ON_Hash32TableItem::HashTableItemHash() const
{
  return m_internal_hash32;
}

void ON_Hash32TableItem::ClearHashTableSerialNumberForExperts()
{
  m_internal_hash_table_sn = 0;
}

//#define ON_DEBUG_ON_Hash32Table_ValidateEachTransaction

#if defined(ON_DEBUG_ON_Hash32Table_ValidateEachTransaction)
// If the message below shows up in WIP or public builds,
// then a developer forgot to comment out the line above.
// When ON_DEBUG_ON_Hash32Table_ValidateEachTransaction is defined,
// the code runs too slowly for commercial use.
#if defined(ON_COMPILER_MSC)
#pragma message("warning: It is an error to commit this file with ON_DEBUG_ON_Hash32Table_ValidateEachTransaction defined.")
#endif
#endif


ON__UINT32 ON_Hash32Table::HashTableSerialNumber() const
{
  return m_hash_table_sn;
}

bool ON_Hash32Table::IsValid() const
{
  if (0 == m_hash_table_sn)
    return ON_IsNotValid();

  if (0 == m_hash_table_capacity)
  {
    if (nullptr != m_hash_table)
      return ON_IsNotValid();
  }
  else
  {
    if (nullptr == m_hash_table)
      return ON_IsNotValid();
  }

  ON__UINT32 item_count = 0;
  for (ON__UINT32 i = 0; i < m_hash_table_capacity; i++)
  {
    for (const ON_Hash32TableItem* item = m_hash_table[i]; nullptr != item; item = item->m_internal_next)
    {
      const ON__UINT32 j = (item->m_internal_hash32 % m_hash_table_capacity);
      if ( j != i )
        return ON_IsNotValid();
      if ( item->m_internal_hash_table_sn != m_hash_table_sn)
        return ON_IsNotValid();
      item_count++;
    }
  }

  if ( m_item_count != item_count )
    return ON_IsNotValid();  

  return true;
}

static ON__UINT32 ON_Hash32Table_NewSerialNumber()
{
  static ON__UINT32 sn = 0;
  if ( 0 == sn )
    sn++;
  return sn++;
}

ON_Hash32Table::ON_Hash32Table()
  : m_hash_table_sn(ON_Hash32Table_NewSerialNumber())
{}

ON_Hash32Table::~ON_Hash32Table()
{
  if ( nullptr != m_hash_table)
    onfree(m_hash_table);
  m_hash_table_capacity = 0;
  m_item_count = 0;
  m_hash_table = nullptr;
}

void ON_Hash32Table::Internal_AdjustTableCapacity(
  ON__UINT32 item_count
  )
{
  const ON__UINT32 max_capacity = 256 * 1024;
  const ON__UINT32 target_list_length = 8;
  if (m_hash_table_capacity < max_capacity && item_count/target_list_length >= m_hash_table_capacity)
  {
    ON__UINT32 hash_table_capacity = m_hash_table_capacity;
    if (hash_table_capacity < 64)
      hash_table_capacity = 64;
    while (hash_table_capacity < max_capacity && item_count/target_list_length > hash_table_capacity)
      hash_table_capacity *= 2;

    size_t sizeof_hash_table = hash_table_capacity*sizeof(m_hash_table[0]);
    ON_Hash32TableItem** hash_table = (ON_Hash32TableItem**)onmalloc(sizeof_hash_table);
    memset(hash_table,0,sizeof_hash_table);
    if (m_item_count > 0)
    {
      for (ON__UINT32 i = 0; i < m_hash_table_capacity; i++)
      {
        ON_Hash32TableItem* item = m_hash_table[i];
        while (nullptr != item)
        {
          ON_Hash32TableItem* next = item->m_internal_next;
          const ON__UINT32 j = item->m_internal_hash32 % hash_table_capacity;
          item->m_internal_next = hash_table[j];
          hash_table[j] = item;
          item = next;
        }
      }
      onfree(m_hash_table);
    }
    m_hash_table = hash_table;
    m_hash_table_capacity = hash_table_capacity;
  }
}

bool ON_Hash32Table::AddItem(
  ON__UINT32 hash32,
  class ON_Hash32TableItem* item
  )
{
#if defined(ON_DEBUG_ON_Hash32Table_ValidateEachTransaction)
  if (false == IsValid())
  {
    ON_ERROR("ON_Hash32Table::IsValid() is false.");
  }
#endif

  if ( nullptr == item || 0 != item->m_internal_hash_table_sn )
    return false;

  item->m_internal_hash_table_sn = m_hash_table_sn;
  item->m_internal_hash32 = hash32;
  Internal_AdjustTableCapacity(m_item_count+1);
  const ON__UINT32 i = (hash32 % m_hash_table_capacity);
  item->m_internal_next = m_hash_table[i];
  m_hash_table[i] = item;
  m_item_count++;

#if defined(ON_DEBUG_ON_Hash32Table_ValidateEachTransaction)
  if (false == IsValid())
  {
    ON_ERROR("ON_Hash32Table::IsValid() is false.");
  }
#endif

  return true;
}

bool ON_Hash32Table::RemoveItem(
  ON_Hash32TableItem* item
  )
{
#if defined(ON_DEBUG_ON_Hash32Table_ValidateEachTransaction)
    if (false == IsValid())
    {
      ON_ERROR("ON_Hash32Table::IsValid() is false.");
    }
#endif
    
  if ( nullptr != item )
  {
    if (m_hash_table_sn != item->m_internal_hash_table_sn || m_item_count <= 0)
    {
      ON_ERROR("corrupt item or hash table.");
      return false;
    }

    const ON__UINT32 i = (item->m_internal_hash32 % m_hash_table_capacity);
    ON_Hash32TableItem* prev = nullptr;
    for (ON_Hash32TableItem* p = m_hash_table[i]; nullptr != p; p = p->m_internal_next)
    {
      if (item == p)
      {
        if ( nullptr == prev )
          m_hash_table[i] = p->m_internal_next;
        else
          prev->m_internal_next = p->m_internal_next;
        m_item_count--;
        item->m_internal_hash_table_sn = 0;
        item->m_internal_hash32 = 0;
        item->m_internal_next = nullptr;

#if defined(ON_DEBUG_ON_Hash32Table_ValidateEachTransaction)
        if (false == IsValid())
        {
          ON_ERROR("ON_Hash32Table::IsValid() is false.");
        }
#endif

        return true;
      }
      prev = p;
    }

    ON_ERROR("item not in hash table - corrupt item or hash table.");
    return false;
  }
  return false;
}

unsigned int ON_Hash32Table::RemoveAllItems()
{
  const unsigned int removed_item_count = m_item_count;
  m_item_count = 0;
  memset(m_hash_table, 0, m_hash_table_capacity * sizeof(m_hash_table[0]));
  return removed_item_count;
}


unsigned int ON_Hash32Table::RemoveAllItems(
  class ON_FixedSizePool& fsp
)
{
  const size_t sizeof_item = fsp.SizeofElement();
  const size_t fsp_item_count = fsp.ActiveElementCount();
  if (sizeof_item < sizeof(ON_Hash32TableItem) || fsp_item_count < (size_t)m_item_count)
  {
    ON_ERROR("Invalid fsp parameter.");
    return RemoveAllItems();
  }

  unsigned int removed_item_count = 0;
  if (m_item_count > 0)
  {
    const bool bReturnItem = (fsp_item_count == (size_t)m_item_count);
    if (false == bReturnItem)
    {
      removed_item_count = RemoveAllItems();
      fsp.ReturnAll();
    }
    else
    {
      for (ON__UINT32 i = 0; i < m_hash_table_capacity; i++)
      {
        ON_Hash32TableItem* p = m_hash_table[i];
        if (nullptr == p)
          continue;
        m_hash_table[i] = nullptr;
        while (nullptr != p)
        {
          ON_Hash32TableItem* next = p->m_internal_next;
          memset(p, 0, sizeof_item);
          fsp.ReturnElement(p);
          p = next;
          removed_item_count++;
        }
      }
    }
  }

  if (removed_item_count != m_item_count)
  {
    ON_ERROR("Corrupt hash table.");
  }
  m_item_count = 0;
  return removed_item_count;
}



ON_Hash32TableItem* ON_Hash32Table::FirstItemWithHash(
  ON__UINT32 hash32
  ) const
{
  if (m_hash_table_capacity > 0)
  {
    for (ON_Hash32TableItem* item = m_hash_table[hash32 % m_hash_table_capacity]; nullptr != item; item = item->m_internal_next)
    {
      if (hash32 == item->m_internal_hash32)
        return item;
    }
  }
  return nullptr;
}

class ON_Hash32TableItem* ON_Hash32Table::NextItemWithHash(
  const ON_Hash32TableItem* current_item
  ) const
{
  if ( nullptr == current_item || m_hash_table_sn != current_item->m_internal_hash_table_sn )
    return nullptr;
  const ON__UINT32 hash32 = current_item->m_internal_hash32;
  for (ON_Hash32TableItem* item = current_item->m_internal_next; nullptr != item; item = item->m_internal_next)
  {
    if ( m_hash_table_sn != item->m_internal_hash_table_sn )
      break;
    if (hash32 == item->m_internal_hash32)
      return item;
  }
  return nullptr;
}

ON_Hash32TableItem* ON_Hash32Table::FirstTableItem() const
{
  if (m_item_count > 0)
  {
    for (ON__UINT32 i = 0; i < m_hash_table_capacity; i++)
    {
      if (nullptr != m_hash_table[i])
        return m_hash_table[i];
    }
  }
  return nullptr;
}

ON_Hash32TableItem* ON_Hash32Table::NextTableItem(
  const ON_Hash32TableItem* item
  ) const
{
  if ( nullptr == item && m_hash_table_sn == item->m_internal_hash_table_sn && m_item_count > 0 )
  {
    if ( item->m_internal_next )
      return item->m_internal_next;
    for (ON__UINT32 i = (item->m_internal_hash32 % m_hash_table_capacity)+1; i < m_hash_table_capacity; i++)
    {
      if (nullptr != m_hash_table[i])
        return m_hash_table[i];
    }
  }
  return nullptr;
}

unsigned int ON_Hash32Table::ItemCount() const
{
  return m_item_count;
}

