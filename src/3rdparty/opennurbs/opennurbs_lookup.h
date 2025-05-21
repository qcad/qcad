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

#if !defined(OPENNURBS_MAP_INC_)
#define OPENNURBS_MAP_INC_

/*
Description:
  ON_SerialNumberMap provides a way to map set of unique 
  serial number - uuid pairs to application defined values
  so that adding, finding and removing serial numbers is 
  fast and efficient.  The class is designed to handle
  several millions of unique serial numbers.  There are no
  restrictions on what order numbers are added and removed.
  The minimum memory footprint is less than 150KB and doesn't
  increase until you have more than 8000 serial numbers.
  It is possible to have an active serial number and an
  inactive id.
*/
class ON_CLASS ON_SerialNumberMap
{
public:
  ON_SerialNumberMap();
  ~ON_SerialNumberMap();

  struct MAP_VALUE
  {
    ON__UINT32 m_u_type;
    ON__UINT32 m_u32;
    union
    {
      ON__UINT64 u64;
      ON__INT64 i64;
      void* ptr;
      ON__UINT32 ui[2];
      ON__INT32 i[2];
    } m_u;
  };

  struct SN_ELEMENT
  {
    ////////////////////////////////////////////////////////////
    //
    // ID
    //
    ON_UUID m_id;

    ////////////////////////////////////////////////////////////
    //
    // Serial number:
    //
    ON__UINT64 m_sn;

    ////////////////////////////////////////////////////////////
    //
    // Status flags:
    //
    // If m_id_active is 1, then m_sn_active must be 1.
    // If m_sn_active = 1, then m_id_active can be 0 or 1.
    ON__UINT8 m_sn_active; // 1 = serial number is active
    ON__UINT8 m_id_active; // 1 = id is active
    ON__UINT8 m_reserved1;
    ON__UINT8 m_reserved2;

    ON__UINT32 m_id_crc32; // id hash = IdCRC(id)

    struct SN_ELEMENT* m_next; // id hash table linked list

    ////////////////////////////////////////////////////////////
    //
    // User information:
    //
    //   ON_SerialNumberMap does not use the m_value field.
    //   When a new element is added, m_value is memset to
    //   zero.  Other than that, m_value is not changed by
    //   this class.  The location of m_value in memory,
    //   (&m_value) may change at any time.
    struct MAP_VALUE m_value;

    void Dump(ON_TextLog&) const;
  };

  /*
  Returns:
    Number of active serial numbers in the list.
  */
  ON__UINT64 ActiveSerialNumberCount() const;

  /*
  Returns:
    Number of active ids in the list.  This number
    is less than or equal to ActiveSerialNumberCount().
  */
  ON__UINT64 ActiveIdCount() const;

  /*
  Returns:
    The active element with the smallest serial number, 
    or null if the list is empty.
  Restrictions:
    The returned pointer may become invalid after any
    subsequent calls to any function in this class.  
    If you need to save information in the returned
    SN_ELEMENT for future use, you must copy the 
    information into storage you are managing.

    You may change the value of the SN_ELEMENT's m_value
    field.  You must NEVER change any other SN_ELEMENT
    fields or you will break searching and possibly cause
    crashes.
  */
  struct SN_ELEMENT* FirstElement() const;

  /*
  Returns:
    The active element with the biggest serial number,
    or null if the list is empty.
  Restrictions:
    The returned pointer may become invalid after any
    subsequent calls to any function in this class.  
    If you need to save information in the returned
    SN_ELEMENT for future use, you must copy the 
    information into storage you are managing.

    You may change the value of the SN_ELEMENT's m_value
    field.  You must NEVER change any other SN_ELEMENT
    fields or you will break searching and possibly cause
    crashes.
  */
  struct SN_ELEMENT* LastElement() const;

  /*
  Parameters:
    sn - [in] serial number to search for.
  Returns:
    If the serial number is active, a pointer to
    its element is returned.
  Restrictions:
    The returned pointer may become invalid after any
    subsequent calls to any function in this class.  
    If you need to save information in the returned
    SN_ELEMENT for future use, you must copy the 
    information into storage you are managing.

    You may change the value of the SN_ELEMENT's m_value
    field.  You must NEVER change any other SN_ELEMENT
    fields or you will break searching and possibly cause
    crashes.
  */
  struct SN_ELEMENT* FindSerialNumber(ON__UINT64 sn) const;

  /*
  Parameters:
    id - [in] id number to search for.
  Returns:
    If the id is active, a pointer to
    its element is returned.
  Restrictions:
    The returned pointer may become invalid after any
    subsequent calls to any function in this class.  
    If you need to save information in the returned
    SN_ELEMENT for future use, you must copy the 
    information into storage you are managing.

    You may change the value of the SN_ELEMENT's m_value
    field.  You must NEVER change any other SN_ELEMENT
    fields or you will break searching and possibly cause
    crashes.
  */
  struct SN_ELEMENT* FindId(ON_UUID) const;

  /*
  Description:
    Add a serial number to the map.
  Parameters:
    sn - [in] serial number to add.
  Returns:
    If the serial number is valid (>0), a pointer to its
    element is returned.  When a new element is added, 
    every byte of the m_value field is set to 0.
    If the serial number was already active, its element is
    also returned.  If you need to distinguish between new
    and previously existing elements, then set an 
    m_value field to something besides 0 after you add
    a new serial number.  The id associated with this
    serial number will be zero and cannot be found using
    FindId().
  Restrictions:
    The returned pointer may become invalid after any
    subsequent calls to any function in this class.  
    If you need to save information in the returned
    SN_ELEMENT for future use, you must copy the 
    information into storage you are managing.

    You may change the value of the SN_ELEMENT's m_value
    field.  You must NEVER change any other SN_ELEMENT
    fields or you will break searching and possibly cause
    crashes.
  */
  struct SN_ELEMENT* AddSerialNumber(ON__UINT64 sn);

  /*
  Parameters:
    sn - [in] serial number to add.
    id - [in] suggested id to add. If id is zero or
              already in use, another id will be assigned
              to the element.
  Returns:
    If the serial number is valid (>0), a pointer to its
    element is returned.  When a new element is added, 
    every byte of the m_value field is set to 0.
    If the serial number was already active, its element is
    also returned.  If you need to distinguish between new
    and previously existing elements, then set an 
    m_value field to something besides 0 after you add
    a new serial number. 
    If the id parameter is nil, then a new uuid is created
    and added. If the id parameter is not nil but is active
    on another element, a new uuid is created and added.
    You can inspect the value of m_id on the returned element
    to determine the id AddSerialNumberAndId() assigned to
    the element.

  Restrictions:
    The returned pointer may become invalid after any
    subsequent calls to any function in this class.  
    If you need to save information in the returned
    SN_ELEMENT for future use, you must copy the 
    information into storage you are managing.

    You may change the value of the SN_ELEMENT's m_value
    field.  You must NEVER change any other SN_ELEMENT
    fields or you will break searching and possibly cause
    crashes.
  */
  struct SN_ELEMENT* AddSerialNumberAndId(ON__UINT64 sn, ON_UUID id);

  /*
  Parameters:
    sn - [in] serial number of the element to remove.
  Returns:
    If the serial number was active, it is removed
    and a pointer to its element is returned.  If
    the element's id was active, the id is also removed.
  Restrictions:
    The returned pointer may become invalid after any
    subsequent calls to any function in this class.  
    If you need to save information in the returned
    SN_ELEMENT for future use, you must copy the 
    information into storage you are managing.

    You may change the value of the SN_ELEMENT's m_value
    field.  You must NEVER change any other SN_ELEMENT
    fields or you will break searching and possibly cause
    crashes.
  */
  struct SN_ELEMENT* RemoveSerialNumberAndId(ON__UINT64 sn);

  /*
  Parameters:
    sn - [in] If > 0, this is the serial number
              of the element with the id. If 0, the
              field is ignored.
    id - [in] id to search for.
  Returns:
    If the id was active, it is removed and a pointer
    to its element is returned.  The element's serial
    remains active. To remove both the id and serial number,
    use RemoveSerialNumberAndId().
  Restrictions:
    The returned pointer may become invalid after any
    subsequent calls to any function in this class.  
    If you need to save information in the returned
    SN_ELEMENT for future use, you must copy the 
    information into storage you are managing.

    You may change the value of the SN_ELEMENT's m_value
    field.  You must NEVER change any other SN_ELEMENT
    fields or you will break searching and possibly cause
    crashes.
  */
  struct SN_ELEMENT* RemoveId(ON__UINT64 sn, ON_UUID id);

  /*
  Description:
    Finds all the elements whose serial numbers are
    in the range sn0 <= sn <= sn1 and appends them
    to the elements[] array.  If max_count > 0, it
    specifies the maximum number of elements to append.
  Parameters:
    sn0 - [in]
      Minimum serial number.
    sn1 - [in]
      Maximum serial number
    max_count - [in]
      If max_count > 0, this parameter specifies the
      maximum number of elements to append.
    elements - [out]
      Elements are appended to this array
  Returns:
    Number of elements appended to elements[] array.
  Remarks:
    When many elements are returned, GetElements() can be
    substantially faster than repeated calls to FindElement().
  */
  ON__UINT64 GetElements(
          ON__UINT64 sn0,
          ON__UINT64 sn1, 
          ON__UINT64 max_count,
          ON_SimpleArray<SN_ELEMENT>& elements
          ) const;

  /*
  Description:
    Empties the list.
  */
  void EmptyList();

  /*
  Description:
    Returns true if the map is valid.  Returns false if the
    map is not valid.  If an error is found and textlog
    is not null, then a description of the problem is sent
    to textlog.
  Returns:
    true if the list if valid.
  */
  bool IsValid(
    bool bBuildHashTable,
    ON_TextLog* textlog
    ) const;

  void Dump(ON_TextLog& text_log) const;

private:
  // prohibit copy construction and operator=
  // no implementation
  ON_SerialNumberMap(const ON_SerialNumberMap&) = delete;
  ON_SerialNumberMap& operator=(const ON_SerialNumberMap&) = delete;

private:
  class ON_SerialNumberMapPrivate* m_private = nullptr;

  // Serial Number list counts
  ON__UINT64 m_sn_count = 0;   // total number of elements                       
  ON__UINT64 m_sn_purged = 0;  // total number of purged elements

  // The blocks in m_sn_list[] are always sorted, disjoint,
  // and in increasing order.  m_sn_list is used when
  // m_sn_block0.m_sn[] is not large enough.
  // The sn list is partitioned into blocks to avoid
  // requiring large amounts of contiguous memory for
  // situations with millions of serial numbers.
  ON__UINT64 m_snblk_list_capacity = 0; // capacity of m_blk_list[]
  ON__UINT64 m_snblk_list_count = 0;    // used elements in m_snblk_list[]
  class ON_SN_BLOCK** m_snblk_list = nullptr;

  // If FindElementHelper() returns a non-null pointer
  // to an element, then m_e_blk points to the ON_SN_BLOCK
  // that contains the returned element.  In all other
  // situations the value in m_e_blk is undefined and
  // m_e_blk must not be dereferenced.
  class ON_SN_BLOCK* m_e_blk = nullptr;

private:
  class ON_SN_BLOCK& m_sn_block0;

private:
  struct SN_ELEMENT* FindElementHelper(ON__UINT64 sn);
  void UpdateMaxSNHelper();
  void GarbageCollectHelper();
  ON__UINT64 GarbageCollectMoveHelper(ON_SN_BLOCK* dst,ON_SN_BLOCK* src);

  ON__UINT8 m_reserved1 = 0;
  ON__UINT8 m_reserved2 = 0;
  ON__UINT8 m_reserved3 = 0;

  // When m_bHashTableIsValid == 1, the id hash table is valid.
  // Otherwise it is not built or out of date.
  // When m_bHashTableIsValid and nullptr != m_hash_table, 
  // then m_hash1_count > 0 and m_hash_table[i][j] is a 
  // linked list of elements whose id satisfies 
  // i = e->m_id_crc32 % m_hash_block_count
  // j = (e->m_id_crc32/ID_HASH_BLOCK_CAPACITY) % ID_HASH_BLOCK_CAPACITY
  mutable ON__UINT8 m_bHashTableIsValid = 0;

  mutable ON__UINT32 m_hash_block_count = 0; // number of blocks in m_hash_tableX[] 
  mutable ON__UINT64 m_hash_capacity = 0; // == m_hash_block_count*ID_HASH_BLOCK_CAPACITY
                                  // ideally, m_active_id_count/m_hash_capacity is close to 4
  mutable struct SN_ELEMENT*** m_hash_table_blocks = nullptr;

  // ID hash table counts (all ids in the hash table are active)
  ON__UINT64 m_active_id_count = 0; // number of active ids in the hash table
  ON_UUID m_inactive_id = ON_nil_uuid; // frequently an id is removed and
                            // then added back.  m_inactive_id
                            // records the most recently removed
                            // id so we don't have to waste time
                            // searching the hash table for
                            // an id that is not there.

  void Internal_HashTableInvalidate(); // marks table as dirty
  
  bool Internal_HashTableRemoveSerialNumberBlock(
    const class ON_SN_BLOCK* blk
    );
  
  /*
  Returns:
    Number of active ids added to hash table.
  */
  ON__UINT64 Internal_HashTableAddSerialNumberBlock(
    class ON_SN_BLOCK* blk
    ) const;

  void Internal_HashTableBuild() const;      // prepares table for use

  struct SN_ELEMENT** Internal_HashTableBlock(
    ON__UINT32 id_crc32
    ) const;

  ON__UINT32 Internal_HashTableBlockIndex(
    ON__UINT32 id_crc32
    ) const;

  static ON__UINT32 Internal_HashTableBlockRowIndex(
    ON__UINT32 id_crc32
    );

  struct SN_ELEMENT* Internal_HashTableFindId(
    ON_UUID id,
    ON__UINT32 id_crc32,
    bool bBuildTableIfNeeded
    ) const;

  struct SN_ELEMENT* Internal_HashTableRemoveElement(
    struct SN_ELEMENT* e,
    bool bRemoveFromHashBlock
    );

  void Internal_HashTableGrow() const;

  void Internal_HashTableInitialize() const;

};


#endif
