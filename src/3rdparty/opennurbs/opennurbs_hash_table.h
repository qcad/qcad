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
//   defines ON_Hash32Table
//
////////////////////////////////////////////////////////////////

#if !defined(OPENNURBS_HASH_TABLE_INC_)
#define OPENNURBS_HASH_TABLE_INC_

class ON_CLASS ON_Hash32TableItem
{
public:
  ON_Hash32TableItem() = default;
  ~ON_Hash32TableItem() = default;
  ON_Hash32TableItem(const ON_Hash32TableItem&) = default;
  ON_Hash32TableItem& operator=(const ON_Hash32TableItem&) = default;

public:
  ON__UINT32 HashTableSerialNumber() const;

  static ON__UINT32 Hash32FromSHA1Hash(
    const class ON_SHA1_Hash& sha1_hash
    );

  static ON__UINT32 Hash32FromId(
    const ON_UUID& id
    );

  /*
  Returns:
    If this item has been added to an ON_Hash32Table.AddItem(hash32,item pointer) then the 
    value of hash3d passed as the first argument to ON_Hash32Table.AddItem(hash32,item pointer)
    is returned. This is the value the ON_Hash32Table uses for this item.
    Otherwise 0 is returned.
  Remarks:
    This function is useful when copying hash tables.

    count = src_hash_table.ItemCount();
    MyHashTableItems src_items[count]; // items added to src_hash_table 

    // copy src_hash_table
    MyHashTableItems copied_items[count];
    copied_items = src_items;
    for (unsigned i = 0; i < count; ++i)
    {
      ON_SubDSurfaceInterpolatortHash32TableItem& hitem = copied_items[i];
      hitem.ClearHashTableSerialNumberForExperts();
      m_htable.AddItem(hitem.HashTableItemHash(), &hitem);
    }
  */
  ON__UINT32 HashTableItemHash() const;

  /*
  Description:
    Useful when copying hash tables to remove the hash table reference from
    a copied hash item. Never remove the hash table reference from an item
    that is still in a hash table.
  */
  void ClearHashTableSerialNumberForExperts();
private:
  friend class ON_Hash32Table;
  mutable ON_Hash32TableItem* m_internal_next = nullptr;
  mutable ON__UINT32 m_internal_hash32 = 0;
  mutable ON__UINT32 m_internal_hash_table_sn = 0;
};

/*
Description:
  A hash table designed to be used for items with high quality 32-bit hash values.
*/
class ON_CLASS ON_Hash32Table
{
public:
  ON_Hash32Table();
  ~ON_Hash32Table();

private:
  ON_Hash32Table(const ON_Hash32Table&) = delete;
  ON_Hash32Table& operator=(const ON_Hash32Table&) = delete;

public:
  ON__UINT32 HashTableSerialNumber() const;

  /*
  Description:
    Adds an item to the hash table.
  Parameters:
    hash32 - [in]
    item - [in/out]
  Returns:
    The added item.
  */
  bool AddItem(
    ON__UINT32 hash32,
    class ON_Hash32TableItem* item
    );

  /*
  Returns:
    The first item in the hash table with hash = hash32.
  Parameters:
    hash32 - [in]
  Remarks:
    This function is used to find the first element in the hash table with the
    specified hash32 failure. Use ON_Hash32TableItem.NextItemWithSameHash() to get
    the next item in the has table with the same hash value.
  */
  class ON_Hash32TableItem* FirstItemWithHash(
    ON__UINT32 hash32
    ) const;

  class ON_Hash32TableItem* NextItemWithHash(
    const class ON_Hash32TableItem* current_item
    ) const;

  /*
  Returns:
    The first item in the hash table.
  Remarks:
    This function is used for iterating throughout every element in the hash table.
  */
  class ON_Hash32TableItem* FirstTableItem(
    ) const;

  /*
  Returns:
    The next item in the hash table.
  Remarks:
    This function is used for iterating throughout every element in the hash table.
  */
  class ON_Hash32TableItem* NextTableItem(
    const ON_Hash32TableItem* item
    ) const;

  /*
  Description:
    Remove an item from the hash table. Caller is responsible for managing item memory.
  Parameters:
    item - [in/out]
      If the item is removed, the has table serial number is set to zero.
  Returns:
    The true if the item was removed.
  */
  bool RemoveItem(
    class ON_Hash32TableItem* item
    );

  /*
  Description:
    Removes all hash table items. Caller is responsible for managing the item memory.
  */
  unsigned int RemoveAllItems();

  /*
  Description:
    Removes all hash table items.
    For each item memset(item,0,fsp.SizeofElement()) and fsp.ReturnElement(item) are called.
  */
  unsigned int RemoveAllItems(
    class ON_FixedSizePool& fsp
    );

  /*
  Returns:
    Number of items in the hash table
  */
  unsigned int ItemCount() const;

  bool IsValid() const;

private:
  const ON__UINT32 m_hash_table_sn;
  ON__UINT32 m_reserved = 0;
  mutable ON__UINT32 m_hash_table_capacity = 0;
  ON__UINT32 m_item_count = 0;
  mutable class ON_Hash32TableItem** m_hash_table = nullptr;

  void Internal_AdjustTableCapacity(
    ON__UINT32 item_count
    );
};


#endif
