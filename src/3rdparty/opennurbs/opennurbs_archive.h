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

#if !defined(ON_ARCHIVE_INC_)
#define ON_ARCHIVE_INC_


/////////////////////////////////////////////////////////////////////
//
// ON_Buffer 
//

typedef void (*ON_Buffer_ErrorHandler)(class ON_Buffer*);

class ON_CLASS ON_Buffer
{
public:
  ON_Buffer();
  ~ON_Buffer();

  ON_Buffer(const ON_Buffer& src);
  ON_Buffer& operator=(const ON_Buffer& src);

  /*
  Description:
    Compare contents of buffers.
  Parameters:
    a - [in]
    b - [in]
  Returns:
    -1: a < b
     0: a == b
     1: a > b
  */
  static int Compare( const ON_Buffer& a, const ON_Buffer& b );

  void Destroy();
  void EmergencyDestroy();

  /*
  Returns:
    True if Size() == CurrentPosition().
  Remarks:
    It is possible to seek beyond the end of the buffer.
    In this case, the current position will be past the end
    of the buffer and AtEnd() will return false.
  */
  bool AtEnd() const;

  /*
  Returns:
    Number of bytes currently in the buffer.
  Remarks:
    It is possible to seek beyond the end of the buffer.
    In this case, the current position will be past the end
    of the buffer and CurrentPosition() will be greater than
    Size().
  */
  ON__UINT64 Size() const;

  /*
  Returns:
    32-bit CRC of the buffer contents.
  Remarks:
    
  */
  ON__UINT32 CRC32( ON__UINT32 current_remainder ) const;


  /*
  Returns:
    Current position in the buffer.
  Remarks:
    It is possible to seek beyond the end of the buffer.
    In this case, the current position will be past the end
    of the buffer and CurrentPosition() will be greater than
    Size().
  */
  ON__UINT64 CurrentPosition() const;
  
  /*
  Parameters:
    size - [in]
      number of bytes to write.
    buffer - [in]
      values to write.
  Returns:
    Number of bytes written buffer.
  */
  ON__UINT64 Write( ON__UINT64 size, const void* buffer );

  /*
  Parameters:
    size - [in]
      number of bytes to read.
    buffer - [out]
      read values are returned in buffer.
  Returns:
    Number of bytes read into buffer. For example, 
    if CurrentPosition() <= Size() and 
    size > (Size() - CurrentPosition()) and
    buffer is not null, then the value
    (Size() - CurrentPosition()) is returned.
  Remarks:
    If the size parameter is zero, then nothing is done.
    When CurrentPosition() <= Size(), attempts to read more 
    than (Size() - CurrentPosition()) bytes do not generate 
    an error. When CurrentPosition() > Size(), any attempt
    to read generates an error.
  */
  ON__UINT64 Read( ON__UINT64 size, void* buffer );

  enum
  {
    seek_from_beginning_of_file = 0,
    seek_from_current_position = 1,
    seek_from_end_of_file = 2
  };

  /*
  Parameters:
    offset - [in]
      number of bytes to seek from origin
    origin - [in]
      initial position.
        0 (SEEK_SET) Seek from beginning of file.
        1 (SEEK_CUR) Seek from current position.
        2 (SEEK_END) Seek from end of file.
  Returns:
    True if successful.
    False if the seek would result in a file position
    before the beginning of the file. If false is
    returned, the current position is not changed.
  Remarks:
    Seeking beyond the end of the buffer is succeeds.
    Seeking before the beginning of the buffer fails.
  */
  bool Seek( 
    ON__INT64 offset, 
    int origin 
    );

  /*
  Parameters:
    offset - [in] (>= 0)
      number of bytes to seek from the start of the buffer.
  Returns:
    True if successful.
    False if the seek would result in a file position
    before the beginning of the file. If false is
    returned, the current position is not changed.
  Remarks:
    Seeking beyond the end of the buffer is succeeds.
    Seeking before the beginning of the buffer fails.
  */
  bool SeekFromStart( ON__INT64 offset ); 

  /*
  Parameters:
    offset - [in]
      number of bytes to seek from the current position.
  Returns:
    True if successful.
    False if the seek would result in a file position
    before the beginning of the file. If false is
    returned, the current position is not changed.
  Remarks:
    Seeking beyond the end of the buffer is succeeds.
    Seeking before the beginning of the buffer fails.
  */
  bool SeekFromCurrentPosition( ON__INT64 offset ); 

  /*
  Parameters:
    offset - [in]
      number of bytes to seek from the end fo the buffer.
  Returns:
    True if successful.
    False if the seek would result in a file position
    before the beginning of the file. If false is
    returned, the current position is not changed.
  Remarks:
    Seeking beyond the end of the buffer is succeeds.
    Seeking before the beginning of the buffer fails.
  */
  bool SeekFromEnd( ON__INT64 offset ); 

  /*
  Parameters:
    buffer_size - [in]
      new size of buffer.
  Returns:
    True if successful.    
  Remarks:
    The current position is not changed and may be beyond the
    end of the file. Use Seek to set the current position after
    calling ChangeSize().
  */
  bool ChangeSize( ON__UINT64 buffer_size );

  /*
  Description:
    Return unused memory to heap.
  Remarks:
    Call this function after creating an ON_Buffer that will persist for
    and extended amount of time. There are never more than 16 pages of
    unused memory (16*4096 bytes on most computers) in an ON_Buffer.
    Compact() can be called at any time, but calling Compact() the then
    writing at the end of the buffer is not an efficient use of time
    or memory.
  */
  bool Compact();

  /*
  Returns
    True if the ON_Buffer is valid.
  */
  bool IsValid( const ON_TextLog* text_log ) const;

  /*
  Returns:
    Value that identifies most recent error.
    0: no error
    1: attempt to seek to a negative position
  */
  ON__UINT32 LastError() const;
  
  void ClearLastError();

  ON_Buffer_ErrorHandler ErrorHandler() const;
  
  void SetErrorHandler(ON_Buffer_ErrorHandler error_handler);

  /*
  Description:
    Use WriteToBinaryArchive() to save an entire ON_Buffer inside
    a binary archive.  Use ReadFromBinaryArchive() to retrieve
    the ON_Buffer from the ON_BinaryArchive.
  */
  bool WriteToBinaryArchive( ON_BinaryArchive& ) const;

  /*
  Description:
    Use ReadFromBinaryArchive() to retrieve an entire ON_Buffer
    that was written using WriteToBinaryArchive().
  */
  bool ReadFromBinaryArchive( ON_BinaryArchive& );

  /*
  Description:
    Compress this buffer

  Parameters:
    compressed_buffer - [out]
      (The reference can be *this)
  
  Example:

        // compress a buffer in place
        ON_Buffer buffer;
        buffer = ...;
        if ( !buffer.Compress(buffer) )
        {
           // compression failed
        }
        else
        {
           // buffer is now compressed
        }

  Returns:
    True if successful.  False if failed.
  */
  bool Compress( ON_Buffer& compressed_buffer ) const;

  /*
  Description:
    Uncompress this buffer which must have been compressed using
    ON_Buffer::Compress().

  Parameters:
    uncompressed_buffer - [out]
      (The reference can be *this)

  Example:
        // silly example that compresses and then uncompresses a buffer in place
        // to show how to call the functions.
        ON_Buffer buffer;
        buffer = ...; // buffer is in it uncompressed form
        if ( buffer.Compress(buffer) )
        {
           // buffer is now compressed
           if ( buffer.Uncompress(buffer) )
           {
              // buffer is uncompressed again.
           }
        }

  Returns:
    True if successful.  False if failed.
  */
  bool Uncompress( ON_Buffer& uncompressed_buffer ) const;

private:

  ON__UINT64 m_buffer_size; // total number of bytes in the buffer
  ON__UINT64 m_current_position;

  struct ON_BUFFER_SEGMENT* m_first_segment;
  struct ON_BUFFER_SEGMENT* m_last_segment;
  struct ON_BUFFER_SEGMENT* m_current_segment;
  bool SetCurrentSegment(bool);
  void Copy( const ON_Buffer& );

  ON_Buffer_ErrorHandler m_error_handler;

  ON__UINT32 m_last_error;
  unsigned char m_reserved[12];
};

/////////////////////////////////////////////////////////////////////
//
// ON_BinaryArchive 
//      virtual class for CPU independent serialization
//
// ON_BinaryFile
//      simple class for CPU independent binary file I/O
//      includes optional CRC support
//

struct ON_3DM_CHUNK
{
  size_t m_offset; // In read or write_using_fseek mode, this is the
                   // file position of first byte after chunk's length.
                   // In write_using_buffer mode, this of the m_buffer[]
                   // position of first byte after chunk's length.
  unsigned int m_typecode;
  int m_value;
  int m_do_length; // true if chunk is a long chunk with length
  ON__UINT16 m_do_crc16; // 16 bit CRC using CCITT polynomial
  ON__UINT16 m_crc16;
  ON__UINT32 m_do_crc32; // 32 bit CRC
  ON__UINT32 m_crc32;
};

class ON_CLASS ON_3DM_BIG_CHUNK
{
public:
  ON_3DM_BIG_CHUNK() = default;
  ~ON_3DM_BIG_CHUNK() = default;
  ON_3DM_BIG_CHUNK(const ON_3DM_BIG_CHUNK&) = default;
  ON_3DM_BIG_CHUNK& operator=(const ON_3DM_BIG_CHUNK&) = default;

public:
  ON__UINT64 m_start_offset=0; // When reading or writing 3dm archives, this is the
                             // archive offset (file position) of first byte of 
                             // chunk information content.
  
  ON__UINT64 m_end_offset=0; // When writing 3dm archives, this is the archive 
                           // offset (file position) of the byte immediately after
                           // the farthest successful write. 
                           // When reading 3dm archives, this the archive offset
                           // of the first byte after the chunk's information content.
                           // When reading, a 16 bit or 32 bit CRC can follow the chunk
                           // information content.
                           // During ordinary reading and writing, valid seek target 
                           // positions satisfy 
                           // m_start_offset <= seek target pos <= m_end_offset.

  /*
  Returns:
    Number of bytes in the chunk, including bytes used to store CRC values.
    0 for short chunks.
    0 for chunks currently being written.
  Remarks:
    For chunks being read,
     m_start_offset + Length() = m_end_offset + SizeofCRC().
  */
  ON__UINT64 Length() const;

  /*
  Parameters:
    current_position - [in]
      Value of ON_BinaryArchive.CurrentPosition()

  Returns:
    Number of bytes that can be read when ON_BinaryArchive ReadMode() is true.
  */
  ON__UINT64 LengthRemaining(
    ON__UINT64 current_position
  ) const;

  /*
  Returns:
    0: no CRC
    4: 32 bit CRC (4 bytes)
    2: 16 bit CRC (2 bytes)
  */
  ON__UINT64 SizeofCRC() const;

  ON__INT64 m_big_value=0;
  ON__UINT32 m_typecode=0;  
  ON__UINT8 m_bLongChunk=0; // true if chunk is a long chunk and m_big_value is a length.

private:
  ON__UINT8 m_reserved1=0;
  ON__UINT8 m_reserved2=0;
  ON__UINT8 m_reserved3=0;

public:
  // CRC settings
  ON__UINT8 m_do_crc16=0; // true (1) if we are calculating 16 bit CRC
  ON__UINT8 m_do_crc32=0; // true (1) if we are calculating 32 bit CRC
  ON__UINT16 m_crc16=0; // current 16 bit CRC value
  ON__UINT32 m_crc32=0; // current 32 bit CRC value
};

bool ON_IsLongChunkTypecode(ON__UINT32 typecode);

bool ON_IsShortChunkTypecode(ON__UINT32 typecode);

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_3DM_CHUNK>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_3DM_BIG_CHUNK>;
#endif

// Used int ON_3dmProperties::Read() to set ON_BinaryArchive.m_3dm_opennurbs_version
// Do not call directly. 
void ON_SetBinaryArchiveOpenNURBSVersion(class ON_BinaryArchive&,unsigned int);

class ON_CLASS ON_UserDataItemFilter
{
public:
  ON_UserDataItemFilter();

  ON_UserDataItemFilter(
    ON_UUID application_id,
    bool bSerialize
    );

  ON_UserDataItemFilter(
    ON_UUID application_id,
    ON_UUID item_id,
    bool bSerialize
    );

  static int Compare(
    const class ON_UserDataItemFilter*,
    const class ON_UserDataItemFilter*
    );

  // The application id can be the id for a plug-in, Rhino or opennurbs
  ON_UUID m_application_id;

  // The item id for object user data is the value of ON_UserData.m_userdata_uuid.
  // The item id for user table is the application id.
  // A nil item id indicates the setting is applied to all object user data 
  // and user table information for the specified application.
  ON_UUID m_item_id;

  // If application id and item id match and m_bSerializeEnabled,
  // does not match, then the ON_UserDataItemFilter with the
  // largest value of m_precedence is used.
  unsigned int m_precedence;

  // bSerializationEnabled is true if reading and writing are permitted.
  // bSerializationEnabled is false if reading and writing are prevented.
  bool m_bSerialize;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_UserDataItemFilter>;
#endif

class ON_CLASS ON_ComponentManifest
{
public:
  // The default constructor would work prfectly,
  // except there is a bug in Apple's CLANG that
  // requires either an explicitly implemented constructor
  // or an explicitly implemented copy constructor together
  // with a hack to initialize the static ON_ComponentManifest::Empty.
  // Apple CLANG BUG // ON_ComponentManifest() = default;
  ON_ComponentManifest() ON_NOEXCEPT;

  ~ON_ComponentManifest();

  static const ON_ComponentManifest Empty;

  void Reset();

  enum : int
  {
    UnsetComponentIndex = ON_UNSET_INT_INDEX
  };

private:
  ON_ComponentManifest(const ON_ComponentManifest&) = delete;
  ON_ComponentManifest& operator=(const ON_ComponentManifest&) = delete;

public:

  /*
    Total number of items in the manifest, including items referencing system components and deleted items.
  */
  unsigned int ItemCount() const;

  /*
  Parameters:
    component_type - [in]
      If component_type is ON_ModelComponent::Type::Unset or ON_ModelComponent::Type::Mixed,
      then the every explicit component type is counted.
  Returns:
    Total number of model components of the specified type in this manifest. 
  Remarks:
    The count includes active, deleted, and system components.
  */
  unsigned int TotalComponentCount(
    ON_ModelComponent::Type component_type
    ) const;

  /*
  Parameters:
    component_type - [in]
      If component_type is ON_ModelComponent::Type::Unset or ON_ModelComponent::Type::Mixed,
      then the every explicit component type is counted.
  Returns:
    Number of model components of the specified type in this manifest. 
  Remarks:
    The count includes active and deleted components.
    The count does not include system components (those added by calling AddSystemComponentToManifest()).
  */
  unsigned int ActiveAndDeletedComponentCount(
    ON_ModelComponent::Type component_type
    ) const;

  /*
  Parameters:
    component_type - [in]
      If component_type is ON_ModelComponent::Type::Unset or ON_ModelComponent::Type::Mixed,
      then the every explicit component type is counted.
  Returns:
    Number of active model components of the specified type in this manifest. 
  Remarks:
    The count does not include deleted components (IsDeleted() = true).
    The count does not include system components (those added by calling AddSystemComponentToManifest()).
  */
  unsigned int ActiveComponentCount(
    ON_ModelComponent::Type component_type
    ) const;

  /*
  Parameters:
    component_type - [in]
      If component_type is ON_ModelComponent::Type::Unset or ON_ModelComponent::Type::Mixed,
      then the every explicit component type is counted.
  Returns:
    Number of model components of the specified type in this manifest that have IsDeleted() = true.
  Remarks:
    System components cannot be deleted.
  */
  unsigned int DeletedComponentCount(
    ON_ModelComponent::Type component_type
    ) const;

  unsigned int SystemComponentCount(
    ON_ModelComponent::Type component_type
    ) const;

  /*
  Parameters:
    component_type - [in]
  Returns:
    If the component type is indexed, then all current manifest indices
    for the component_type are >= 0 and < ComponentIndexLimit().
    Otherwise 0 is returned.
  */
  int ComponentIndexLimit(
    ON_ModelComponent::Type component_type
    ) const;

  /*
  Description:
    Add a component to this manifest.
    If the id is not set or not unique, the component will not be added.
    If a unique name is required and the name is not set or not unique,
    the component will not be added.
  Parameters:
    component - [in]
      If you want to update the component id, index and name values to 
      match the ones assigned in the manifest, then call 
      component.SetIdentification(manifest_item),
      where manifest_item is the information returned by this function.
    bResolveIdAndNameCollisions - [in]
      If false, then the component parameter id must not be used in the
      manifest and, when required, the name must be set and unique.
      If true and a new id or name is required, one will be assigned.
      Note that the component parameter is const and its id and name
      are not modified.
    assigned_name - [out]
      If not null, the assigned name is returned here.
  Returns:
    If an item is added to this manifest, then the assigned
    identification information is returned. 
    Otherwise ON_ComponentManifestItem::Unset is returned.
    Note the manifest index is generally different from component.Index().
  Remarks:
    Use 
  */
  const class ON_ComponentManifestItem& AddComponentToManifest(
    const class ON_ModelComponent& component,
    bool bResolveIdAndNameCollisions,
    ON_wString* assigned_name
    );

  const class ON_ComponentManifestItem& AddSystemComponentToManifest(
    const class ON_ModelComponent& component
    );


  /*
  Description:
    Add a component to this manifest.
  Parameters:
    component_type - [in]
      Type of component.
    component_serial_number - [in]
      0 or the component's unique runtime serial number (ON_ModelComponent::RuntimeSerialNumber()).
    component_id - [in]
    component_name_hash - [in]
      If the the component type requires a unique name and the name
      is not valid or in use, the component will not be added.
  Returns:
    If an item is added to this manifest, then the identification
    information is returned.
    Otherwise ON_ComponentManifestItem::Unset is returned.
    Note: 
    The manifest index is assigned to components that require an index.
  */
  const class ON_ComponentManifestItem& AddComponentToManifest(
    ON_ModelComponent::Type component_type,
    ON__UINT64 component_serial_number,
    ON_UUID component_id,
    const ON_NameHash& component_name_hash
    );

  /*
  Description:
    Add a component to this manifest.  
    If the id is not set or in use, then a new one will be assigned.
    If the component type requires a unique name and the name is not set or in use,
    then a new one will be assigned.
  Parameters:
    component_type - [in]
      Type of component.
    component_serial_number - [in]
      0 or the component's unique runtime serial number (ON_ModelComponent::RuntimeSerialNumber()).
    component_id - [in]
      If the id is nil or in use, a new id will be assigned.
    component_name_hash - [in]
      If the the component type requires a unique name and the name
      is not valid or in use, the component will not be added.
    original_name - [in/out]
      If a new name needs to be assigned, the input value will be used
      as a candidate and then as the root. Passing in the current name
      is a good choice. The output value is the final assigned name.
  Returns:
    If an item is added to this manifest, then the identification
    information is returned.
    Otherwise ON_ComponentManifestItem::Unset is returned.
  */
  const class ON_ComponentManifestItem& AddComponentToManifest(
    ON_ModelComponent::Type component_type,
    ON__UINT64 component_serial_number,
    ON_UUID component_parent_id,
    ON_UUID component_id,
    const ON_NameHash& component_name_hash,
    const wchar_t* candidate_name,
    ON_wString& assigned_name
    );

  const class ON_ComponentManifestItem& AddComponentToManifest(
    ON_ModelComponent::Type component_type,
    ON__UINT64 component_serial_number,
    ON_UUID component_parent_id,
    ON_UUID component_id,
    const wchar_t* original_name,
    ON_wString& assigned_name
    );


  /*
  Description:
    Modify a manifest items's component name
  Parameters:
    item_id - [in]
      Identifies the manifest item to modify.
    component_parent_id - [in]
      ON_ModelComponent.ParentId() value.
      When ON_ModelComponent::UniqueNameIncludesParent(component_type) is true,
      it is critical that component_parent_id be set correctly.
    name - [in]
      new name
  Returns:
    True if name was modified.
  */
  const class ON_ComponentManifestItem& ChangeComponentName(
    ON_UUID item_id,
    ON_ModelComponent::Type component_type,
    ON_UUID component_parent_id,
    const wchar_t* component_name
    );

  /*
  Description:
    Modify a manifest items's component name
  Parameters:
    component - [in]
      The component that is in the manifest with the new name set.
  Returns:
    True if name was modified.
  */
  const class ON_ComponentManifestItem& ChangeComponentName(
    const class ON_ModelComponent& component
    );

  /*
  Description:
    A function for expert users to directly set the
    component's name hash. Generally, it is better
    to use the ChangeComponentName() functions.
  Parameters:
    item_id - [in]
      Identifies the manifest item to modify.
    component_name_hash - [in]
      new name hash
  */
  const class ON_ComponentManifestItem& ChangeComponentNameHash(
    ON_UUID item_id,
    const ON_NameHash& component_name_hash
    );

  /*
  Description:
    Modify a manifest items's component m_component_runtime_serial_number,
    m_original_index, m_original_id, and m_name_hash values.
  Parameters:
    manifest_id - [in]
      identifies the manifest item to modify
    component_runtime_serial_number - [in]      
  */
  const class ON_ComponentManifestItem& ChangeComponentRuntimeSerialNumber(
    ON_UUID item_id,
    ON__UINT64 component_runtime_serial_number
    );

  /*
  Description:
    Set a component's status to deleted.
  */
  const class ON_ComponentManifestItem& DeleteComponent(
    ON_UUID item_id
    );

  const class ON_ComponentManifestItem& DeleteComponent(
    ON__UINT64 component_runtime_serial_number
    );

  /*
  Description:
    Undelete a previously deleted component.
  */
  const class ON_ComponentManifestItem& UndeleteComponent(
    ON_UUID item_id,
    ON_UUID parent_id,
    const wchar_t* candidate_name,
    ON_wString& assigned_name
    );

  /*
  Description:
    Undelete a previously deleted component with the same id and
    change the serial number to new_component_runtime_serial_number.
  Remarks:
    Often when an object is modified, the original and new
    object have the same id but different serial numbers. The original is
    deleted. When the item is undeleted for the object, the runtime
    serial number needs to be udated.
  */
  const class ON_ComponentManifestItem& UndeleteComponentAndChangeRuntimeSerialNumber(
    ON_UUID item_id,
    ON_UUID parent_id,
    ON__UINT64 new_component_runtime_serial_number,
    const wchar_t* candidate_name,
    ON_wString& assigned_name
    );

  bool RemoveComponent(
    const ON_ModelComponent& component
    );

  bool RemoveComponent(
    ON__UINT64 component_runtime_serial_number
    );

  bool RemoveComponent(
    ON_UUID item_id
    );

  bool RemoveIndexedComponent(
    ON_ModelComponent::Type component_type,
    int item_index
    );

  bool RemoveAllComponents(
    ON_ModelComponent::Type component_type,
    bool bResetManifestIndex
    );
  
  /*
  Description:
    Get a name that is currently not used in this manifest as either a component
    or manifest name.
  Parameters:
    component_type - [in]
      ON_ModelComponent::ComponentTypeIsValidAndNotMixed(component_type) must be true.
    component_parent_id - [in]
      If ON_ModelComponent::UniqueNameIncludesParent(component_type) is true and
      candidate_name is not empty, then the component parent id must be accurate.
      This is the case for ON_Layer names. 
      Otherwise, you may pass ON_nil_uuid.
    candidate_name - [in]
      If candidate_name is a valid and not it use,
      then unused_component_name = candidate_name.
      If ON_ModelComponent::UniqueNameIncludesParent(component_type) is true and
      candidate_name is not empty, then component_parent_id must be accurate.
      This is the case for ON_Layer names.
    base_name - [in]
      If base_name is empty or not valid, 
      then ON_ModelComponent::ComponentTypeToString(component_type) is used as base_name
    suffix_separator - [in]
      empty or the string to place between base_name and the suffix when searching for an
      unused name.
    suffix0 - [in]
      If a suffix needs to be appended, the search for a 
      unused name begins with the suffix values suffix0+1.
    suffix_value - [out]
      If nullptr != suffix_value, the value used to generate the 
      unique name suffix is returned.
  Returns:
    An component name that is not used in this manifest.
  Remarks:
    If candidate_name could not be used, then it has the form 
    base_name + suffix_separator + X, where X is an integer > suffix0.
  */
  const ON_wString UnusedName(
    ON_ModelComponent::Type component_type,
    ON_UUID component_parent_id,
    const wchar_t* candidate_name,
    const wchar_t* base_name,
    const wchar_t* suffix_separator,
    unsigned int suffix0,
    unsigned int* suffix_value
    ) const;

  /*
  Description:
    Get a name that is currently not used in this manifest as either a component
    or manifest name.
  Parameters:
    model_component - [in]
      The component type, id, parent id, and candidate name parameters for the
      more complicated version of UnusedName() are taken from this parameter.
  Returns:
    An component name that is not used in this manifest.
  Remarks:
    If candidate_name could not be used, then it has the form 
    base_name + suffix_separator + X, where X is an integer > suffix0.
  */
  const ON_wString UnusedName(
    const ON_ModelComponent& model_component
    ) const;

  /*
  Parameters:
    component_type - [in]
      ON_ModelComponent::ComponentTypeIsValidAndNotMixed(component_type)
      must be true or false will be returned.
    candidate_name_hash - [in]
      candidate_name_hash.IsValidAndNotEmpty()
      must be true or false will be returned.
  Returns:
    True if the candidate_name_hash a hash of a valid, non-empty name and the
    name is currently not used as either a component or manifest name value.
  */
  bool NameIsAvailable(
    ON_ModelComponent::Type component_type,
    const ON_NameHash& candidate_name_hash
    ) const;

  /*
  Description:
    Get an id that is not currently used in this manifest
  Parameters:
    component_type - [in]
      ON_ModelComponent::ComponentTypeIsValidAndNotMixed(component_type) must be true.
    candidate_id
      If candidate_id is valid component id and not in use,
      then its value is returned.
  Returns:
    An id that is valid and currently not used in this ON_Manifest as 
    either a component or a manifest id value.
  Remarks:
    If candidate_id cannot be used, then ON_CreateId() is used to create a new id.
  */
  ON_UUID UnusedId(
    ON_UUID candidate_id
    ) const;

  /*
  Returns:
    True if the id is valid and currently not used in this ON_Manifest as 
    either a component or a manifest id value.
  */
  bool IdIsAvailable(
    ON_UUID id
    ) const;
  
  //////////////////////////////////////////////////////////////////
  //
  // Query tools to get item identificaion information
  //
  //    
  const class ON_ComponentManifestItem& ItemFromId(
    ON_UUID item_id
    ) const;

  const class ON_ComponentManifestItem& ItemFromComponentRuntimeSerialNumber(
    ON__UINT64 component_runtime_serial_number
    ) const;

  /*
  Description:
    Returns the item if it has the required component type and id.
  Remarks:
    Every item has a unique manifest id.  The component_type
    parameter is provided if an additional check needs to be
    made on component type.
  */
  const class ON_ComponentManifestItem& ItemFromId(
    ON_ModelComponent::Type component_type,
    ON_UUID item_id
    ) const;

  /*
  Parameters:
    component_type - [in]
    model_component - [in]
      The value of ON_ModelComponent::UniqueNameIgnoresCase(component_type) must be used
      when creating the name hash (group names are case sensitive).
  */
  const class ON_ComponentManifestItem& ItemFromName(
    const class ON_ModelComponent* model_component
    ) const;

  /*
  Parameters:
    component_type - [in]
    parent_id - [in]
      If  ON_ModelComponent::UniqueNameIncludesParent(component_type) is true, 
      then the parent_id must be used to calculate the name hash 
      (layer names require parent ids).
  */
  const class ON_ComponentManifestItem& ItemFromName(
    ON_ModelComponent::Type component_type,
    ON_UUID parent_id,
    const wchar_t* name
    ) const;

  /*
  Parameters:
    component_type - [in]
    component_name_hash - [in]
      The value of ON_ModelComponent::UniqueNameIgnoresCase(component_type) must be used
      when creating the name hash (group names are case sensitive).

      If  ON_ModelComponent::UniqueNameIncludesParent(component_type) is true, 
      then the parent_id must be used to calculate the name hash 
      (layer names require parent ids).
  */
  const class ON_ComponentManifestItem& ItemFromNameHash(
    ON_ModelComponent::Type component_type,
    const ON_NameHash& component_name_hash
    ) const;

  const class ON_ComponentManifestItem& ItemFromIndex(
    ON_ModelComponent::Type component_type,
    int item_index
    ) const;

  const class ON_ComponentManifestItem& ItemFromUnsignedIndex(
    ON_ModelComponent::Type component_type,
    unsigned int unsigned_item_index
    ) const;

  const class ON_ComponentManifestItem& SystemItemFromNameHash(
    ON_ModelComponent::Type component_type,
    const ON_NameHash& system_item_name_hash
    ) const;

  const class ON_ComponentManifestItem& SystemItemFromIndex(
    ON_ModelComponent::Type component_type,
    int system_item_index
    ) const;

  const class ON_ComponentManifestItem* FirstItem(
    ON_ModelComponent::Type component_type
    ) const;

  const class ON_ComponentManifestItem* LastItem(
    ON_ModelComponent::Type component_type
    ) const;

  /*
  Returns:
    Next item in the manifest with the same component type.
  */
  const class ON_ComponentManifestItem* NextItem(
    const class ON_ComponentManifestItem* item
    ) const;

  /*
  Returns:
    Previous item in the manifest with the same component type.
  */
  const class ON_ComponentManifestItem* PreviousItem(
    const class ON_ComponentManifestItem* item
    ) const;

  /*
  Returns:
    Next item in the manifest with the same component type.
  */
  const class ON_ComponentManifestItem* NextItem(
    ON_UUID manifest_item_id
    ) const;

  /*
  Returns:
    Previous item in the manifest with the same component type.
  */
  const class ON_ComponentManifestItem* PreviousItem(
    ON_UUID manifest_item_id
    ) const;

  /*
  Description:
    This number is incremented every time the manifest changes.
  */
  ON__UINT64 ManifestContentVersionNumber() const;

private:
  const class ON_ComponentManifestItem* Internal_AddItem(
    class ON_ComponentManifestItem& item,
    ON_UUID component_parent_id,
    bool bResolveIdAndNameCollisions,
    const wchar_t* candidate_name,
    ON_wString* assigned_name
    );

private:
  class ON_ComponentManifestImpl* Impl() const;
  mutable class ON_ComponentManifestImpl* m_impl = nullptr;
};

class ON_CLASS ON_ComponentManifestItem
{
public:
  static const ON_ComponentManifestItem UnsetItem;

  static int CompareComponentType(
    const ON_ComponentManifestItem* a, 
    const ON_ComponentManifestItem* b
    );

  static int CompareId(
    const ON_ComponentManifestItem*const* a, 
    const ON_ComponentManifestItem*const* b
    );

  static int CompareNameHash(
    const ON_ComponentManifestItem*const* a,
    const ON_ComponentManifestItem*const* b
    );

  static int CompareIndex(
    const ON_ComponentManifestItem*const* a, 
    const ON_ComponentManifestItem*const* b
    );

public:
  // Assigns component type, index, id and name hash
  ON_ComponentManifestItem(
    const class ON_ModelComponent& component
    );

  ON_ComponentManifestItem(
    const class ON_ModelComponent& component,
    const ON_UUID& manifest_id,
    const class ON_NameHash& manifest_name_hash
    );

  ON_ComponentManifestItem(
    ON_ModelComponent::Type component_type,
    ON__UINT64 m_component_runtime_serial_number,
    const ON_UUID& manifest_id,
    const class ON_NameHash& manifest_name_hash
    );

  ON_ComponentManifestItem(
    const class ON_ModelComponent& component,
    int manifest_index,
    const ON_UUID& manifest_id,
    const class ON_NameHash& manifest_name_hash
    );

  ON_ComponentManifestItem(
    ON_ModelComponent::Type component_type,
    ON__UINT64 m_component_runtime_serial_number,
    int manifest_index,
    const ON_UUID& manifest_id,
    const class ON_NameHash& manifest_name_hash
    );

  ON_ComponentManifestItem() = default;
  ~ON_ComponentManifestItem() = default;
  ON_ComponentManifestItem(const ON_ComponentManifestItem&) = default;
  ON_ComponentManifestItem& operator=(const ON_ComponentManifestItem&) = default;

public:
  /*
  Returns:
    true if m_component_type is not ON_ModelComponent::Type::Unset
    and the m_manifest_id is not nil.
  */
  bool IsValid() const;

  /*
  Returns:
    true if m_component_type is ON_ModelComponent::Type::Unset
    or the m_manifest_id is nil.
  */
  bool IsUnset() const;
  
  /*
  Returns:
    true if the item is in a deleted state.
    Name is erased. 
    The component can be found by component serial number, id, or index.
  */
  bool IsDeleted() const;

  /*
  Returns:
    true if the item is a constant system component.
  */
  bool IsSystemComponent() const;

public:
  /*
  Return:
    item component type. ON_ModelComponent::Type::Unset if it is not set.
  */
  ON_ModelComponent::Type ComponentType() const;

  void SetComponentType(
    ON_ModelComponent::Type component_type
  );

public:
  /*
  Return:
    item id. ON_nil_uuid if is not set.
  */
  ON_UUID Id() const;

  void SetId(
    ON_UUID id
  );

public:
  /*
  Return:
    item component runtime serial number. 0 if it is not set.
  */
  ON__UINT64 ComponentRuntimeSerialNumber() const;

  void SetComponentRuntimeSerialNumber(
    ON__UINT64 component_runtime_serial_number
  );

public:
  /*
  Return:
    item name hash. ON_NameHash::UnsetNameHash if is not set.
  */
  const ON_NameHash& NameHash() const;

  void SetNameHash(
    const ON_NameHash& name_hash
  );

public:
  /*
  Return:
    item index. ON_UNSET_INT_INDEX if it is not set.
  */
  int Index() const;

  void SetIndex(
    int index
  );

private:
  friend class ON_ComponentManifestImpl;

  void Internal_SetDeletedState(
    bool bDeleted
    );

private:
  ON__UINT32 m_status_bits = 0;
  ON_ModelComponent::Type m_component_type = ON_ModelComponent::Type::Unset;
  ON__UINT8 m_reserved1 = 0;
  ON__UINT16 m_reserved2 = 0;
  ON__UINT32 m_reserved3 = 0;
  int m_index = ON_UNSET_INT_INDEX;
  ON__UINT64 m_component_runtime_serial_number = 0;
  ON_UUID m_id = ON_nil_uuid;
  ON_NameHash m_name_hash = ON_NameHash::UnsetNameHash;
};

class ON_CLASS ON_ManifestMapItem
{
public:
  ON_ManifestMapItem() = default;
  ~ON_ManifestMapItem() = default;
  ON_ManifestMapItem(const ON_ManifestMapItem&) = default;
  ON_ManifestMapItem& operator=(const ON_ManifestMapItem&) = default;

public:
  static const ON_ManifestMapItem Unset;
  
  /*
  Description:
    Compares type, indices and ids.
  */
  static int Compare(
    const ON_ManifestMapItem& a,
    const ON_ManifestMapItem& b
  );

  static int CompareTypeAndSourceId(
    const ON_ManifestMapItem& a,
    const ON_ManifestMapItem& b
  );

  static int CompareTypeAndDestinationId(
    const ON_ManifestMapItem& a,
    const ON_ManifestMapItem& b
  );

  static int CompareTypeAndSourceIdAndIndex(
    const ON_ManifestMapItem& a,
    const ON_ManifestMapItem& b
  );

  static int CompareTypeAndDestinationIdAndIndex(
    const ON_ManifestMapItem& a,
    const ON_ManifestMapItem& b
  );

  static int CompareTypeAndSourceIndex(
    const ON_ManifestMapItem& a,
    const ON_ManifestMapItem& b
  );

  static int CompareTypeAndDestinationIndex(
    const ON_ManifestMapItem& a,
    const ON_ManifestMapItem& b
  );

  /*
  Description:
    32-bit hash for use in source id hash tables
  */
  static ON__UINT32 SourceIdHash32(
    const ON_UUID& source_component_id
  );

  /*
  Description:
    32-bit hash for use in source index hash tables
  */
  static ON__UINT32 SourceIndexHash32(
    ON_ModelComponent::Type component_type,
    int source_component_index
  );

  /*
  Returns:
    True if 
    m_component_type is not ON_ModelComponent::Type::Unset
    and m_source_component_id is not nil
    and m_destination_component_id is not nil
    and no index is required or m_source_component_index and m_destination_component_index
    are not ON_UNSET_INT_INDEX.
  */
  bool SourceAndDestinationAreSet() const;

  bool SourceOrDestinationIsUnset() const;

  /*
  Returns:
    True if 
    m_component_type is not ON_ModelComponent::Type::Unset
    and m_source_component_id is not nil
    and no index is required or m_source_component_index is not ON_UNSET_INT_INDEX.
  */
  bool SourceIsSet() const;

  bool SourceIsUnset() const;

  /*
  Returns:
    True if 
    m_component_type is not ON_ModelComponent::Type::Unset
    and m_destination_component_id is not nil
    and no index is required or m_destination_component_index is not ON_UNSET_INT_INDEX.
  */  
  bool DestinationIsSet() const;

  bool DestinationIsUnset() const;

  /*
  Returns:
    True if destination_manifest contains a manifest item that matches
    m_component_type, m_destination_component_id, and m_destination_component_index.
  */
  bool DestinationInManifest(
    const ON_ComponentManifest& destination_manifest
    ) const;

  /*
  Returns:
    True if destination_manifest contains a manifest item that matches
    m_component_type, m_source_component_id, and m_source_component_index.
  */
  bool SourceInManifest(
    const ON_ComponentManifest& source_manifest
    ) const;

  ON_ManifestMapItem SwapSourceAndDestiation() const;

  ON_ModelComponent::Type ComponentType() const;
  const ON_UUID& SourceId() const;
  const ON_UUID& DestinationId() const;
  int SourceIndex() const;
  int DestinationIndex() const;
  
  bool ClearSourceIdentification();

  bool ClearDestinationIdentification();

  /*
  Description:
    Set type and source identification.
  Parameters:
    component_type - [in]
    source_id - [in]
    source_index - [in]
  Returns:
    True if set.
    False destination type is set and different from component_type.
  */
  bool SetSourceIdentification(
    ON_ModelComponent::Type component_type,
    ON_UUID source_id,
    int source_index
    );

  /*
  Description:
    Set type and destination identification.
  Parameters:
    component_type - [in]
    source_id - [in]
    source_index - [in]
  Returns:
    True if set.
    False destination type is set and different from component_type.
  */  
  bool SetDestinationIdentification(
    ON_ModelComponent::Type component_type,
    ON_UUID destination_id,
    int destination_index
    );

  /*
  Description:
    Set type and source identification to model_component identification.
  Parameters:
    model_component - [in]
  Returns:
    True if set.
    False destination type is set and different from model_component->ComponentType().
  */
  bool SetSourceIdentification(
    const class ON_ModelComponent* model_component
    );

  /*
  Description:
    Set type and destination identification to model_component identification.
  Parameters:
    model_component - [in]
  Returns:
    True if set.
    False source type is set and different from model_component->ComponentType().
  */
  bool SetDestinationIdentification(
    const class ON_ModelComponent* model_component
    );

  /*
  Description:
    Set type and source identification to manifest_item identification.
  Parameters:
    manifest_item - [in]
  Returns:
    True if set.
    False destination type is set and different from manifest_item->ComponentType().
  */

  bool SetSourceIdentification(
    const class ON_ComponentManifestItem* manifest_item
    );

  /*
  Description:
    Set type and destination identification to manifest_item identification.
  Parameters:
    manifest_item - [in]
  Returns:
    True if set.
    False source type is set and different from manifest_item->ComponentType().
  */
  bool SetDestinationIdentification(
    const class ON_ComponentManifestItem* manifest_item
    );

  /*
  Description:
    Copy type and source identification from map_item.
  Parameters:
    map_item - [in]
  Returns:
    True if set.
    False destination type is set and different from map_item->ComponentType().
  */
  bool SetSourceIdentification(
    const class ON_ManifestMapItem* map_item
    );

  /*
  Description:
    Copy type and destination identification from map_item.
  Parameters:
    map_item - [in]
  Returns:
    True if set.
    False source type is set and different from map_item->ComponentType().
  */
  bool SetDestinationIdentification(
    const class ON_ManifestMapItem* map_item
    );

private:
  bool Internal_SetSourceOrDestinationIdentification(
    unsigned int which_identification, // 0 = source, 1 = destination
    ON_ModelComponent::Type component_type,
    ON_UUID id,
    int index
  );

private:
  ON_ModelComponent::Type m_component_type = ON_ModelComponent::Type::Unset;
private:
  unsigned int m_reserved = 0;
private:
  int m_source_index = ON_UNSET_INT_INDEX;
  int m_destination_index = ON_UNSET_INT_INDEX;
private:
  ON_UUID m_source_id = ON_nil_uuid;
  ON_UUID m_destination_id = ON_nil_uuid;
};

ON_DECL
bool operator==(const ON_ManifestMapItem& lhs,const ON_ManifestMapItem& rhs);

ON_DECL
bool operator!=(const ON_ManifestMapItem& lhs,const ON_ManifestMapItem& rhs);


/*
Description:
  ON_ManifestIdentificationMap is used to record a map from
  a source manifest to a destination manifest when the index or id
  values change. This is common when reading and writing archives
  and when merging models.
*/
class ON_CLASS ON_ManifestMap
{
public:
  // The default constructor would work prfectly,
  // except there is a bug in Apple's CLANG that
  // requires either an explicitly implemented constructor
  // or an explicitly implemented copy constructor together
  // with a hack to initialize the static ON_ComponentManifest::Empty.
  // Apple CLANG BUG // ON_ManifestMap() = default;
  ON_ManifestMap() ON_NOEXCEPT;

  ~ON_ManifestMap();
  ON_ManifestMap(const ON_ManifestMap&);
  ON_ManifestMap& operator=(const ON_ManifestMap&);

public:
  static const ON_ManifestMap Empty;
    
public:
  bool AddMapItem(
    const class ON_ManifestMapItem& map_item
    );

  /*
  Parameters:
    map_item - [in]
      The source settings must exactly match source settings of an existing map.
      The destination settings are the new values to assign.
  Return:
    True if a mapping was successfully updated (even when the destation settings did not change).
  */
  bool UpdatetMapItemDestination(
    const class ON_ManifestMapItem& map_item
    );

  /*
  Parameters:
    map_item - [in]
      The source settings must exactly match source settings of an existing map.
      The destination settings are the new values to assign.
    bIgnoreSourceIndex - [in]
      If true, the value of map_item.SourceIndex() is ignored.
      Otherwise, it must exactly match the source index setting of an existing map.
  Return:
    True if a mapping was successfully updated (even when the destation settings did not change).
  */
  bool UpdatetMapItemDestination(
    const class ON_ManifestMapItem& map_item,
    bool bIgnoreSourceIndex
    );

  const class ON_ManifestMapItem& MapItemFromSourceId(
    const ON_UUID& source_item_id
    ) const;

  const class ON_ManifestMapItem& MapItemFromSourceIndex(
    ON_ModelComponent::Type component_type,
    int source_component_index
    ) const;

  bool GetAndValidateDestinationIndex(
    ON_ModelComponent::Type component_type,
    int source_component_index,
    const ON_ComponentManifest& destination_manifest,
    int* destination_component_index
    ) const;

  bool GetAndValidateDestinationIndex(
    ON_ModelComponent::Type component_type,
    const ON_UUID& source_component_id,
    const ON_ComponentManifest& destination_manifest,
    int* destination_component_index
    ) const;

  bool GetAndValidateDestinationId(
    ON_ModelComponent::Type component_type,
    const ON_UUID& source_component_id,
    const ON_ComponentManifest& destination_manifest,
    ON_UUID* destination_component_id
    ) const;

  /*
  Returns:
    True if there are no ON_ManifestMapItem elements.
  */
  bool IsEmpty() const;

  /*
  Returns:
    True if there is at least one ON_ManifestMapItem element.
  */
  bool IsNotEmpty() const;

  /*
  Returns:
    Number of map items.
  Remarks:
    Some of these items may not change id or index.
  */
  unsigned int MapItemCount() const;

private:
  class ON_ManifestMapImpl* Impl();
  class ON_ManifestMapImpl* m_impl = nullptr;
};


enum class ON_3dmArchiveTableType : unsigned int
{
  // The values of the table_type enums must increase in the order 
  // the corresponding tables appear in well formed 3dm archives
  // and the bitwise or of distinct values must be zero because
  // bitfield filters are used in some reading operations.

  Unset                     = 0,

  // First section in any 3dm archive.
  start_section             = 0x00000001U,

  properties_table          = 0x00000002U,
  settings_table            = 0x00000004U,
  bitmap_table              = 0x00000008U,
  texture_mapping_table     = 0x00000010U,
  material_table            = 0x00000020U,
  linetype_table            = 0x00000040U,
  layer_table               = 0x00000080U,
  group_table               = 0x00000100U,
  text_style_table          = 0x00000200U,
  leader_style_table        = 0x00000400U,
  dimension_style_table     = 0x00000800U,
  light_table               = 0x00001000U,
  hatchpattern_table        = 0x00002000U,
  instance_definition_table = 0x00004000U,
  object_table              = 0x00008000U, 
  historyrecord_table       = 0x00010000U,
  user_table                = 0x00020000U,

  // Last section in any 3dm archive.
  end_mark                  = 0x40000000U
};


/*
Description:
  Context for an annotation object. This context is required when
  converting current annotation objects to and from formats used
  in earlier versions and is typically used when reading and 
  writing 3dm archives.
*/
class ON_CLASS ON_3dmAnnotationContext
{
public:
  ON_3dmAnnotationContext() = default;
  ~ON_3dmAnnotationContext();
  ON_3dmAnnotationContext(const ON_3dmAnnotationContext&);
  ON_3dmAnnotationContext& operator=(const ON_3dmAnnotationContext&);

public:
  static const ON_3dmAnnotationContext Default;

public:
  ON::active_space ViewContext() const;
  
  void SetViewContext(
    ON::active_space
  );

  ON::LengthUnitSystem ModelLengthUnitSystem() const;
  
  void SetModelLengthUnitSystem(
    ON::LengthUnitSystem model_length_unit_system
  );

  ON::LengthUnitSystem PageLengthUnitSystem() const;
  
  void SetPageLengthUnitSystem(
    ON::LengthUnitSystem page_length_unit_system
  );

  const class ON_3dmAnnotationSettings& AnnotationSettings() const;

  /*
  Parameters:
    annotation_settings - [in]
      Annotation settings that are externally managed and will exist
      during the lifetime of the ON_3dmAnnotationContext class instance.
  */
  void SetReferencedAnnotationSettings(
    const class ON_3dmAnnotationSettings* annotation_settings
  );

  /*
  Parameters:
    annotation_settings - [in]
      A copy of annotation_settings is stored and manged by the ON_3dmAnnotationContext class instance.
  */
  void SetManagedAnnotationSettings(
    const class ON_3dmAnnotationSettings& annotation_settings
  );

  /*
  Returns:
    True if the annotation settings have been explicitly set.
  */
  bool AnnotationSettingsAreSet() const;

  /*
  This is the dimstyle the annotation object is question is using.
  It can be a "base" dimstyle from the dimstyle table or an
  "override" style attached used by a single instance of an annnotation
  object.
  */
  const class ON_DimStyle& DimStyle() const;
  
  const class ON_DimStyle& ParentDimStyle() const;

  /*
  Parameters:
    dim_style - [in]
      A dimension style that is externally managed and will exist
      during the lifetime of the ON_3dmAnnotationContext class instance.
  */
  void SetReferencedDimStyle(
    const class ON_DimStyle* parent_dim_style,
    const class ON_DimStyle* override_dim_style,
    int V5_3dm_archive_index
  );

  /*
  Parameters:
    dim_style - [in]
      A copy of a dim_style is stored and manged by the ON_3dmAnnotationContext class instance.
  */
  void SetManagedDimStyle(
    const class ON_DimStyle& parent_dim_style,
    const class ON_DimStyle* override_dim_style,
    int V5_3dm_archive_index
  );

  void UpdateReferencedDimStyle(
    const class ON_DimStyle* old_pointer,
    const class ON_DimStyle* new_pointer
  );

  /*
  Returns:
    True if the dimension style has been explicitly set.
  */
  bool DimStyleIsSet() const;
  
  /*
  Returns:
    If the dimstyle is not set or it has a nil parent id, then DimStyleId() is returned.
    Otherwise the parent id is returned.
  */
  ON_UUID ParentDimStyleId() const;

  /*
  Returns:
    3dm archive dimension style table index to use when writing a V5 3dm archive.
    This is often different from DimStyle().Index().
  */
  int V5_ArchiveDimStyleIndex() const;

  /*
  Parameters:
    bRequireSetOverrides - [in]
      true if explicit overrides are required.
  Returns:
    true if the context dim style is an override style (parent id is not nil) and
    it has overrides or bRequireSetOverrides is false.
  */
  bool IsOverrideDimStyle() const;

  const class ON_BinaryArchive* BinaryArchive() const;
  
  /*
  Parameters:
    binary_archive - [in]
      Binary archive that is externally managed and will exist
      during the lifetime of the ON_3dmAnnotationContext class instance.
  */
  void SetReferencedBinaryArchive(
    const class ON_BinaryArchive* binary_archive
  );
  
  /*
  Returns:
    True if the the target binary archive is set.
  */
  bool BinaryArchiveIsSet() const;
  
private:
  const class ON_BinaryArchive* m_binary_archive = nullptr;

  // V6 table dimstyle. If an override dimstyle is in use,
  // this is the "parent dimstyle" referenced by the override.
  const class ON_DimStyle* m_parent_dim_style = nullptr;
  class ON_DimStyle* m_managed_parent_dim_style = nullptr;

  const class ON_DimStyle* m_override_dim_style = nullptr;
  class ON_DimStyle* m_managed_override_dim_style = nullptr;

  const class ON_3dmAnnotationSettings* m_annotation_settings = nullptr;
  class ON_3dmAnnotationSettings* m_managed_annotation_settings = nullptr;
  ON::active_space  m_view_context = ON::active_space::no_space;
  ON::LengthUnitSystem m_model_length_unit_system = ON::LengthUnitSystem::None;
  ON::LengthUnitSystem m_page_length_unit_system = ON::LengthUnitSystem::None;

  // V5 archive dim style index
  int m_V5_3dm_archive_dim_style_index = ON_UNSET_INT_INDEX;

private:
  void Internal_CopyFrom(const ON_3dmAnnotationContext& src);
  void Internal_Destroy();
};


class ON_CLASS ON_3dmArchiveTableStatus
{
public:
  ON_3dmArchiveTableStatus() = default;
  ~ON_3dmArchiveTableStatus() = default;
  ON_3dmArchiveTableStatus(const ON_3dmArchiveTableStatus&) = default;
  ON_3dmArchiveTableStatus& operator=(const ON_3dmArchiveTableStatus&) = default;

  static const ON_3dmArchiveTableStatus Unset;

  ON_3dmArchiveTableType m_table_type = ON_3dmArchiveTableType::Unset;

  // number of table items
  unsigned int m_item_count = 0; 

  // Number of crc errors found during archive reading.
  // If > 0, then the archive is corrupt. See the table 
  // status information below to determine where the 
  // errors occurred.
  unsigned int m_crc_error_count = 0;

  // Number of other types of serious errors found during archive reading
  // or writing.
  // If > 0, then the archive is corrupt. See the table status information
  // below to determine where the errors occurred.
  unsigned int m_critical_error_count = 0;

  // Number of other types of serious errors found during archive reading.
  // If > 0, then the archive is corrupt. See the table status information
  // below to determine where the errors occurred.
  unsigned int m_recoverable_error_count = 0;
  
  enum class TableState : unsigned int 
  {
    Unset      = 0U,
    Started    = 1U, // began to read the table
    InProgress = 2U,
    Finished   = 3U, // finished reading the table
    NotFound   = 4U  // the table could not be located during reading
  };

  ON_3dmArchiveTableStatus::TableState m_state = ON_3dmArchiveTableStatus::TableState::Unset;
};

class ON_CLASS ON_BinaryArchive // use for generic serialization of binary data
{
public:
  /*
  *  You might want to initialize this class before using it
  *  by calling SetArchive3dmVersion with
  *  ON_BinaryArchive::CurrentArchiveVersion() and
  *  SetOpenNURBS3dmVersion with ON::Version().
  */
  ON_BinaryArchive( ON::archive_mode );
  virtual ~ON_BinaryArchive();

protected:
  virtual
  ON__UINT64 Internal_CurrentPositionOverride( // current offset (in bytes) into archive ( like ftell() )
    ) const = 0;

  virtual
  bool Internal_SeekFromCurrentPositionOverride( // seek from current position ( like fseek( ,SEEK_CUR) )
      int // byte offset ( >= -CurrentPostion() )
    ) = 0;

  virtual
  bool Internal_SeekToStartOverride(  // seek from current position ( like fseek(0 ,SEEK_SET) )
    ) = 0;

public:
  /*
  Returns:
    True if current position is at the end of the archive.
  */
  virtual
  bool AtEnd() const = 0;

public:
  /*
  Returns:
    Number of bytes from start of archive to the current position.
  */
  ON__UINT64 CurrentPosition() const;

  /*
  Description:
    Set current position to bytes_from_start many bytes from the start of the archive.
  Parameters:
    bytes_from_start - [in]
  Returns:
    True: successful
    False: failure
  Remarks:
    Similar to fseek( ,SEEK_SET)
  */
  bool SeekFromStart(
      ON__UINT64 bytes_from_start
    );
  
  /*
  Description:
    Increase the archive's current position by bytes_forward from the current position.
  Parameters:
    bytes_forward - [in]
  Returns:
    True: successful
    False: failure
  */
  bool SeekForward(
    ON__UINT64 bytes_forward
  );

  /*
  Description:
    Decrease the archive's current position by bytes_backward from the current position.
  Parameters:
    bytes_backward - [in]
  Returns:
    True: successful
    False: failure
  */
  bool SeekBackward(
    ON__UINT64 bytes_backward
  );

private:
  bool Internal_SeekCur(
    bool bFowrard,
    ON__UINT64 offset
  );

public:

  /*
  Description:
    Tool for swapping bytes when doing I/O on
    using big endian CPUs.
  Remarks:
    3dm files are always saved with little endian byte order.
  See Also:
    ON_BinaryArchive::Endian
  */
  static
  bool ToggleByteOrder(
    size_t, // number of elements
    size_t, // size of element (2,4, or 8)
    const void*,  // source buffer
    void*         // destination buffer (can be same a source buffer)
    );

  static
  const char* TypecodeName( unsigned int tcode );

  static
  char* ON_TypecodeParse( unsigned int tcode, char* typecode_name, size_t max_length );
  
  /*
  Returns:
     Endian-ness of the cpu reading this file.
  Remarks:
    3dm files are always saved with little endian byte order.
  */
  ON::endian Endian() const; // endian-ness of cpu

  bool ReadByte( size_t, void* ); // must fail if mode is not read or readwrite

  bool WriteByte( size_t, const void* ); // must fail if mode is not write or readwrite

  /*
  Description:
    Expert user function that uses Read() to load a buffer.
  Parameters:
    sizeof_buffer - [in] number of bytes to attempt to read.
    buffer - [out] read bytes are stored in this buffer
  Returns:
    Number of bytes actually read, which may be less than
    sizeof_buffer if the end of file is encountered.
  */
  ON__UINT64 ReadBuffer( ON__UINT64 sizeof_buffer, void* buffer );

  /*
  Description:
    Expert user function to control CRC calculation while reading and writing.
    Typically this is used when seeking around and reading/writing information
    in non-serial order.
  Parameters:
    bEnable  - [in]
  Returns:
    Current state of CRC calculation.  Use the returned value to restore the
    CRC calculation setting after you are finished doing your fancy pants
    expert IO.
  */
  bool EnableCRCCalculation( bool bEnable );

  // ReadCompressedBuffer()/WriteCompressedBuffer() use zlib 1.1.3
  // to inflate/deflate the data buffer.
  // Care must be used to get an endian independent file.  
  // See ON_Mesh::Read()/ON_Mesh::Write() for an example of an endian
  // independent use of compression. See also ToggleByteOrder() and Endian().
  //
  // To read data archived by WriteCompressedBuffer( sizeof_buffer, buffer )
  // do something like:
  //
  //   size_t sizeof_buffer = 0;
  //   ReadCompressedBufferSize(&sizeof_buffer);
  //   buffer = something with sizeof_buffer bytes.
  //   int bFailedCRC = false;
  //   bool ok = ReadCompressedBuffer( sizeof_buffer, buffer, &bFailedCRC );
  //


  /*
  Description:
    Red the size of a compressed buffer.
  Parameters:
    sizeof__outbuffer - [out] size of the uncompressed buffer in bytes
  Returns:
    True if read was successful.
  */
  bool ReadCompressedBufferSize( size_t* sizeof__outbuffer );

  /*
  Description:
    Read compressed information from an archive and uncompress it.
  Parameters:
    sizeof__outbuffer - [in] size of the uncompressed buffer in bytes
    outbuffer - [out] uncompressed buffer returned here
    bFailedCRC - [out] true if cyclic redundancy check fails
                      on uncompressed buffer

  Example:

          size_t sizeof_buffer = 0;
          ReadCompressedBufferSize(&sizeof_buffer);
          buffer = ...; // something with sizeof_buffer bytes.
          int bFailedCRC = false;
          bool ok = ReadCompressedBuffer( sizeof_buffer, buffer, &bFailedCRC );

  Returns:
    True if read was successful.  You need to check the value
    of bFailedCRC to see if the information that was read is valid.
  Remarks:
    Write your archive write/read code as if compression is always enabled.
    Do not vary what get written or read based on the value of UseBufferCompression().
  */
  bool ReadCompressedBuffer(
          size_t sizeof__outbuffer,
          void* outbuffer,
          bool* bFailedCRC
          );

  /*
  Description:
    Compress buffer and write the compressed information to the archive.
  Parameters:
    sizeof__inbuffer - [in] size of the uncompressed buffer in bytes
    inbuffer - [in] uncompressed buffer
  Returns:
    True if write was successful.
  Remarks:
    Write your archive write/read code as if compression is always enabled.
    Do not vary what get written or read based on the value of UseBufferCompression().
  */
  bool WriteCompressedBuffer(
    size_t sizeof__inbuffer,
    const void* inbuffer
    );

  bool ReadBool( bool* );

	bool ReadChar(    // Read an array of 8 bit chars
			size_t,       // number of chars to read
			char*    
			);  
	bool ReadChar(    // Read a single 8 bit char
			char*    
			);  

  bool ReadChar(    // Read an array of 8 bit signed chars
			size_t,       // number of chars to read
			ON__INT8*    
			);  
	bool ReadChar(    // Read an array of 8 bit unsigned chars
			size_t,       // number of unsigned chars to read
			ON__UINT8*    
			);  
	bool ReadChar(    // Read a single 8 bit signed char
			ON__INT8*    
			);  
	bool ReadChar(    // Read a single 8 bit unsigned char
			ON__UINT8*    
			);  

	bool ReadShort(   // Read an array of 16 bit shorts
			size_t,       // number of shorts to read
			ON__INT16*    
			);  
	bool ReadShort(   // Read an array of 16 bit unsigned shorts
			size_t,       // number of shorts to read
			ON__UINT16*    
			);  
	bool ReadShort(   // Read a single 16 bit short
			ON__INT16*    
			);  
	bool ReadShort(   // Read a single 16 bit unsigned short
			ON__UINT16*    
			);  

	bool ReadInt( // Read an array of 32 bit integers
			size_t,	      // number of ints to read
			ON__INT32*      
			); 
	bool ReadInt( // Read an array of 32 bit integers
			size_t,	      // number of ints to read
			ON__UINT32*      
			); 
	bool ReadInt( // Read a single 32 bit integer
			ON__INT32*      
			); 
	bool ReadInt( // Read a single 32 bit unsigned integer
			ON__UINT32*      
			); 

	bool ReadBigInt( // Read an array of 64 bit integers
			size_t,	      // number of ints to read
			ON__INT64*      
			); 
	bool ReadBigInt( // Read an array of 64 bit integers
			size_t,	      // number of ints to read
			ON__UINT64*      
			); 
	bool ReadBigInt( // Read a single 64 bit integer
			ON__INT64*      
			); 
	bool ReadBigInt( // Read a single 64 bit unsigned integer
			ON__UINT64*      
			); 


  ON_DEPRECATED_MSG("Please use ON_BinaryArchive::ReadInt")
	bool ReadLong( // Read an array of 32 bit integers
			size_t,	      // number of ints to read
			long*      
			); 
  ON_DEPRECATED_MSG("Please use ON_BinaryArchive::ReadInt")
	bool ReadLong( // Read an array of 32 bit integers
			size_t,	      // number of ints to read
			unsigned long*      
			); 
  ON_DEPRECATED_MSG("Please use ON_BinaryArchive::ReadInt")
	bool ReadLong( // Read a single 32 bit integer
			long*      
			); 
  ON_DEPRECATED_MSG("Please use ON_BinaryArchive::ReadInt")
	bool ReadLong( // Read a single 32 bit unsigned integer
			unsigned long*      
			); 

  ON_DEPRECATED_MSG
  (
    "ON_BinaryArchive::ReadSize is deprecated because it truncates to 32-bits.\n"
    " - If you are updating existing code use 'ReadInt' instead.\n"
    " - Else if you need to write a 64-bit size_t please call 'ReadBigSize'"
  )
  bool ReadSize( // Read a single 32 bit size_t
			size_t*
			); 

  bool ReadBigSize( size_t* ); // 64 bits
  
  bool ReadBigTime( time_t* ); // UCT seconds since 1 January 1970 (64 bits)


	bool ReadFloat(   // Read an array of floats
			size_t,       // number of floats
			float*
			);
	bool ReadFloat(   // Read a single float
			float*
			);
	bool ReadDouble(  // Read an array of IEEE doubles
			size_t,       // number of doubles
			double*
			);
	bool ReadDouble(  // Read a single double
			double*
			);

  bool ReadColor(
    ON_Color&
    );

  bool ReadColor(
    ON_4fColor&
  );

  bool ReadPoint (
    ON_2dPoint&
    );
  bool ReadPoint (
    ON_3dPoint&
    );
  bool ReadPoint (
    ON_4dPoint&
    );
  bool ReadVector (
    ON_2dVector&
    );
  bool ReadVector (
    ON_3dVector&
    );

  bool ReadBoundingBox(ON_BoundingBox&);

  bool ReadXform(ON_Xform&);

  bool ReadPlaneEquation(ON_PlaneEquation&);

  bool ReadPlane(ON_Plane&);

  bool ReadLine(ON_Line&);

  bool ReadArc(ON_Arc&);

  bool ReadCircle(ON_Circle&);

  bool ReadInterval( ON_Interval& );

  bool ReadUuid( ON_UUID& );

  bool ReadDisplayMaterialRef( ON_DisplayMaterialRef& );

  bool ReadLinetypeSegment( ON_LinetypeSegment& );

  // All times are stored in coordinated universal time
  // ( a.k.a GMT, UTC ).  Use ANSI C time() and gmtime() calls.
  bool ReadTime( struct tm& );

  /*
  Parameters:
    str_array_count - [out]
      Number of elements in the string array. All ON_BinaryArchive string
      WriteString() functions write a null terminator to the file and
      the null terminator is included in the count. This means that
      if a string has a non-zero element, then str_array_count >= 2.
  Remarks:
    Modify your code to use ReadStringUTF8ElementCount() when reading
    UTF-8 encoded strings and ReadStringUTF16ElementCount()
    when reading UTF-16 encoded strings.
  */
  ON_DEPRECATED_MSG("Use either ReadStringUTF8ElementCount() or ReadStringUTF16ElementCount()")
  bool ReadStringSize(
      size_t* str_array_count
      );

  /*
  Parameters:
    string_utf8_element_count - [out]
      Number of bytes in the string array. All ON_BinaryArchive string
      WriteString() functions write a null terminator to the file and
      the null terminator is included in string_element_count. This means
      that if opennurbs wrote the string, either string_element_count = 0
      or string_element_count >= 2.
  */
  bool ReadStringUTF8ElementCount(
    size_t* string_utf8_element_count
    );

  /*
  Parameters:
    string_utf16_element_count - [out]
      Number of elements in the string array. All ON_BinaryArchive string
      WriteString() functions write a null terminator to the file and
      the null terminator is included in string_element_count. This means
      that if opennurbs wrote the string, either string_element_count = 0
      or string_element_count >= 2.
  */
  bool ReadStringUTF16ElementCount(
    size_t* string_utf16_element_count
    );


  /*
  Parameters:
    str_array_count - [in]
      Number of char elements in str_array[], including the null
      terminator.  The value of str_array_count is returned by
      ReadCharStringElementCount().
    str_array - [in/out]
      Pass in an array with at least str_array_count elements.
      If true is returned and str_array_count > 0,
      then str_array[str_array_count-1] = 0. All strings with
      char elements written by Rhino are UTF-8 encoded
      unicode strings.
  */
  bool ReadString(
      size_t str_array_count,
      char* str_array
      );

  /*
  Parameters:
    str_array_count - [in]
      Number of unsigned char elements in str_array[], including
      the null terminator. The value of str_array_count is returned
      by ReadCharStringElementCount().
    str_array - [in/out]
      Pass in an array with at least str_array_count elements.
      If true is returned and str_array_count > 0,
      then str_array[str_array_count-1] = 0. All strings with
      unsigned char elements written by Rhino are UTF-8 encoded 
      unicode strings.
  */
  bool ReadString(
      size_t str_array_count,
      unsigned char* str_array
      );

  /*
  Parameters:
    str_array_count - [in]
      Number of unsigned short elements in str_array[],
      including the null terminator. The value of 
      str_array_count is returned by ReadWideCharStringElementCount().
    str_array - [in/out]
      Pass in an array with at least str_array_count elements.
      If true is returned and str_array_count > 0,
      then str_array[str_array_count-1] = 0. All strings with
      unsigned short elements written by Rhino are UTF-16 encoded
      unicode strings.
  */
  bool ReadString(
      size_t str_array_count,
      unsigned short*  str_array
      );

  bool ReadString( ON_String& sUTF8 );

  bool ReadString( ON_wString& s );

  bool ReadComponentIndex( ON_COMPONENT_INDEX& );

  bool ReadArray( ON_SimpleArray<bool>& );
  bool ReadArray( ON_SimpleArray<char>&);

  bool ReadArray( ON_SimpleArray<ON__INT8>&);
  bool ReadArray( ON_SimpleArray<ON__INT16>&);
  bool ReadArray( ON_SimpleArray<ON__INT32>&);
  bool ReadArray( ON_SimpleArray<ON__UINT8>&);
  bool ReadArray( ON_SimpleArray<ON__UINT16>&);
  bool ReadArray( ON_SimpleArray<ON__UINT32>&);
  bool ReadArray( ON_SimpleArray<float>& );
  bool ReadArray( ON_SimpleArray<double>& );

  bool ReadArray( ON_SimpleArray<ON_Color>& );
  bool ReadArray( ON_SimpleArray<ON_2dPoint>& );
  bool ReadArray( ON_SimpleArray<ON_3dPoint>& );
  bool ReadArray( ON_SimpleArray<ON_4dPoint>& );
  bool ReadArray( ON_SimpleArray<ON_2dVector>& );
  bool ReadArray( ON_SimpleArray<ON_3dVector>& );
  bool ReadArray( ON_SimpleArray<ON_Xform>& );
  bool ReadArray( ON_SimpleArray<ON_2fPoint>& );
  bool ReadArray( ON_SimpleArray<ON_3fPoint>& );
  bool ReadArray( ON_SimpleArray<ON_4fPoint>& );
  bool ReadArray( ON_SimpleArray<ON_2fVector>& );
  bool ReadArray( ON_SimpleArray<ON_3fVector>& );
  bool ReadArray( ON_SimpleArray<ON_UUID>& );
  bool ReadArray( ON_SimpleArray<ON_UuidIndex>& );
  bool ReadArray( ON_SimpleArray<ON_UuidPtr>& );
  bool ReadArray( ON_SimpleArray<ON_SurfaceCurvature>& );
  bool ReadArray( ON_ClassArray<ON_String>& );
  bool ReadArray( ON_ClassArray<ON_wString>& );
  bool ReadArray( ON_SimpleArray<ON_DisplayMaterialRef>& );
  bool ReadArray( ON_SimpleArray<ON_LinetypeSegment>& );  
  bool ReadArray( ON_SimpleArray<ON_MappingChannel>& );
  bool ReadArray( ON_ClassArray<ON_MaterialRef>& );
  bool ReadArray( ON_ClassArray<ON_MappingRef>& );
  bool ReadArray( ON_ClassArray<class ON_ObjRef>& );
  bool ReadArray( ON_SimpleArray<class ON_ObjRef_IRefID>& );
  bool ReadArray( ON_SimpleArray<class ON_ClippingPlaneInfo>& );
  bool ReadArray( ON_ObjectArray<class ON_Layer>& );
  bool ReadArray( ON_SimpleArray<class ON_Layer*>& );

  bool WriteBool( bool );

#if defined(ON_COMPILER_MSC) && defined(NDEBUG)
  // Work around Release build optimization bug in Visual Studio 2017.
  __declspec(noinline)
#endif
  bool WriteBoolTrue();

#if defined(ON_COMPILER_MSC) && defined(NDEBUG)
  // Work around Release build optimization bug in Visual Studio 2017.
  __declspec(noinline)
#endif
  bool WriteBoolFalse();

  bool WriteChar(    // Write an array of 8 bit chars
			size_t,       // number of chars to write
			const char*    
			);  
	bool WriteChar(    // Write a single 8 bit char
			char
			);  

  bool WriteChar(    // Write an array of 8 bit signed chars
			size_t,       // number of chars to write
			const ON__INT8*
			);  
	bool WriteChar(    // Write an array of 8 bit unsigned chars
			size_t,       // number of unsigned chars to write
			const ON__UINT8*
			);  
	bool WriteChar(    // Write a single 8 bit signed char
			ON__INT8
			);  
	bool WriteChar(    // Write a single 8 bit unsigned char
			ON__UINT8
			);  

	bool WriteShort(   // Write an array of 16 bit shorts
			size_t,       // number of shorts to write
			const ON__INT16*
			);  
	bool WriteShort(   // Write an array of 16 bit unsigned shorts
			size_t,       // number of shorts to write
			const ON__UINT16*
			);  
	bool WriteShort(   // Write a single 16 bit short
			ON__INT16
			);  
	bool WriteShort(   // Write a single 16 bit unsigned short
			ON__UINT16
			);  

	bool WriteInt( // Write an array of 32 bit integers
			size_t,	      // number of ints to write
			const ON__INT32*
			); 
	bool WriteInt( // Write an array of 32 bit integers
			size_t,	      // number of ints to write
			const ON__UINT32*
			); 
	bool WriteInt( // Write a single 32 bit integer
			ON__INT32    
			); 
	bool WriteInt( // Write a single 32 bit unsigned integer
			ON__UINT32
			); 

	bool WriteBigInt( // Write an array of 64 bit integers
			size_t,	      // number of ints to write
			const ON__INT64*      
			); 
	bool WriteBigInt( // Write an array of 64 bit integers
			size_t,	      // number of ints to write
			const ON__UINT64*      
			); 
	bool WriteBigInt( // Write a single 64 bit integer
			ON__INT64    
			); 
	bool WriteBigInt( // Write a single 64 bit unsigned integer
			ON__UINT64
			); 

  ON_DEPRECATED_MSG("Please use ON_BinaryArchive::WriteInt")
	bool WriteLong( // Write an array of 32 bit integers
			size_t,	      // number of ints to write
			const long*      
			); 
  ON_DEPRECATED_MSG("Please use ON_BinaryArchive::WriteInt")
	bool WriteLong( // Write an array of 32 bit integers
			size_t,	      // number of ints to write
			const unsigned long*      
			); 
  ON_DEPRECATED_MSG("Please use ON_BinaryArchive::WriteInt")
	bool WriteLong( // Write a single 32 bit integer
			long    
			); 
  ON_DEPRECATED_MSG("Please use ON_BinaryArchive::WriteInt")
	bool WriteLong( // Write a single 32 bit unsigned integer
			unsigned long
			); 

  ON_DEPRECATED_MSG
  (
    "ON_BinaryArchive::WriteSize is deprecated because it truncates to 32-bits.\n"
    " - If you are updating existing code use 'WriteInt' instead.\n"
    " - Else if you need to write a 64-bit size_t please call 'WriteBigSize'"
  )
	bool WriteSize( // Write a single 32 bit size_t
			size_t
			); 

  bool WriteBigSize( size_t ); // 64 bits 
  
  bool WriteBigTime( time_t ); // UCT seconds since 1 January 1970 (64 bits)

	bool WriteFloat(   // Write a number of IEEE floats
			size_t,       // number of doubles
			const float*
			);
	bool WriteFloat(   // Write a single float
			float
			);
	bool WriteDouble(  // Write a single double
      size_t,
			const double*
			);
	bool WriteDouble(  // Write a single double
			double
			);

  bool WriteColor (
    const ON_Color&
    );

  bool WriteColor(
    const ON_4fColor&
  );

  bool WritePoint (
    const ON_2dPoint&
    );
  bool WritePoint (
    const ON_3dPoint&
    );
  bool WritePoint (
    const ON_4dPoint&
    );
  bool WriteVector (
    const ON_2dVector&
    );
  bool WriteVector (
    const ON_3dVector&
    );

  bool WriteBoundingBox(const ON_BoundingBox&);

  bool WriteXform(const ON_Xform&);

  bool WritePlaneEquation(const ON_PlaneEquation&);

  bool WritePlane(const ON_Plane&);

  bool WriteLine(const ON_Line&);

  bool WriteArc(const ON_Arc&);

  bool WriteCircle(const ON_Circle&);

  bool WriteInterval( const ON_Interval& );

  bool WriteUuid( const ON_UUID& );

  bool WriteDisplayMaterialRef( const ON_DisplayMaterialRef& );

  bool WriteLinetypeSegment( const ON_LinetypeSegment& );

  // All times are stored in universal coordinated time
  // ( a.k.a GMT, UCT ).  Use ANSI C time() and gmtime() calls.
  bool WriteTime( const struct tm& );

  /*
  Parameters:
    sUTF8 - [in]
      A null terminated UTF-8 encoded unicode string.
  Remarks:
    To read a string written with WriteString(const char*),
    call ReadStringUTF8ElementCount(&string_utf8_element_count)
    to get the number of char elements written in the file,
    obtain a buffer with at least string_utf8_element_count
    char elements and then call 
    ReadString(string_utf8_element_count,buffer) to read the
    char elements.

    If 0 == sUTF8 or 0 == SUTF8[0], a 4 byte int with
    value = 0 is written, otherwise a 4 byte int with
    value = strlen + 1 is written, followed by the string,
    followed by the null terminator.
  */
  bool WriteString(
      const char* sUTF8         
      );

  /*
  Parameters:
    sUTF8 - [in]
      A null terminated UTF-8 encoded unicode string.
  Remarks:
    To read a string written with WriteString(const unsigned char*),
    call ReadStringUTF8ElementCount(&string_utf8_element_count) to
    get the number of unsigned char elements written in the file,
    obtain a buffer with at least string_utf8_element_count
    unsigned char elements and then call 
    ReadString(string_utf8_element_count,buffer) to read the 
    unsigned charelements.

    If 0 == sUTF8 or 0 == SUTF8[0], a 4 byte int with
    value = 0 is written, otherwise a 4 byte int with
    value = strlen + 1 is written, followed by the string,
    followed by the null terminator.
  */
  bool WriteString(
      const unsigned char* sUTF8
      );

  /*
  Parameters:
    sUTF16 - [in]
      A null terminated UTF-16 encoded unicode string.
  Remarks:
    To read a string written with WriteString(const unsigned short*),
    call ReadStringUTF16ElementCount(&string_utf16_element_count) to
    get the number of unsigned short elements written in the file,
    obtain a buffer with at least string_utf16_element_count
    unsigned short elements and then call 
    ReadString(string_utf16_element_count,buffer) to read the
    unsigned short elements.

    If 0 == sUTF8 or 0 == SUTF8[0], a 4 byte int with
    value = 0 is written, otherwise a 4 byte int with
    value = strlen + 1 is written, followed by the string,
    followed by the null terminator.
  */
  bool WriteUTF16String(
      const unsigned short* sUTF16
      );

  /*
  Description:
    Write a wide string as a UTF-8 encoded string.
  */
  bool WriteWideString(
    const wchar_t* sWideChar,
    int sWideChar_count
    );
  
  /*
  Description:
    Write a wide string as a UTF-8 encoded string.
  */
  bool WriteWideString(
    const ON_wString& wide_string
    );
  
  /*
  Description:
    Read a wide string written with the WriteWideString() function.
  */
  bool ReadWideString(
    ON_wString& wide_string
    );
  
  bool WriteString( const ON_String& sUTF8 );

  bool WriteString( const ON_wString& s);

  bool WriteComponentIndex( const ON_COMPONENT_INDEX& );

  bool WriteArray( const ON_SimpleArray<bool>& );
  bool WriteArray( const ON_SimpleArray<char>& );
  
  bool WriteArray( const ON_SimpleArray<ON__INT8>& );
  bool WriteArray( const ON_SimpleArray<ON__INT16>& );
  bool WriteArray( const ON_SimpleArray<ON__INT32>& );
  bool WriteArray(const ON_SimpleArray<ON__UINT8>&);
  bool WriteArray(const ON_SimpleArray<ON__UINT16>&);
  bool WriteArray(const ON_SimpleArray<ON__UINT32>&);

  bool WriteArray( const ON_SimpleArray<float>& );
  bool WriteArray( const ON_SimpleArray<double>& );

  bool WriteArray( const ON_SimpleArray<ON_Color>& );

  bool WriteArray( const ON_SimpleArray<ON_2dPoint>& );
  bool WriteArray( const ON_SimpleArray<ON_3dPoint>& );
  bool WriteArray( const ON_SimpleArray<ON_4dPoint>& );
  bool WriteArray( const ON_SimpleArray<ON_2dVector>& );
  bool WriteArray( const ON_SimpleArray<ON_3dVector>& );

  bool WriteArray( const ON_SimpleArray<ON_2fPoint>& );
  bool WriteArray( const ON_SimpleArray<ON_3fPoint>& );
  bool WriteArray( const ON_SimpleArray<ON_4fPoint>& );
  bool WriteArray( const ON_SimpleArray<ON_2fVector>& );
  bool WriteArray( const ON_SimpleArray<ON_3fVector>& );
  bool WriteArray( const ON_SimpleArray<ON_Xform>& );
  bool WriteArray( const ON_SimpleArray<ON_UUID>& );
  bool WriteArray( const ON_SimpleArray<ON_UuidIndex>& );
  bool WriteArray( const ON_SimpleArray<ON_UuidPtr>& );
  bool WriteArray( const ON_SimpleArray<ON_SurfaceCurvature>& );
  bool WriteArray( const ON_ClassArray<ON_String>& );
  bool WriteArray( const ON_ClassArray<ON_wString>& );
  bool WriteArray( const ON_SimpleArray<ON_DisplayMaterialRef>& );
  bool WriteArray( const ON_SimpleArray<ON_LinetypeSegment>& );  
  bool WriteArray( const ON_SimpleArray<ON_MappingChannel>& );
  bool WriteArray( const ON_ClassArray<ON_MaterialRef>& );
  bool WriteArray( const ON_ClassArray<ON_MappingRef>& );
  bool WriteArray( const ON_ClassArray<class ON_ObjRef>& );
  bool WriteArray( const ON_SimpleArray<class ON_ObjRef_IRefID>& );
  bool WriteArray( const ON_SimpleArray<class ON_ClippingPlaneInfo>& );
  bool WriteArray( int count, const class ON_Layer* );
  bool WriteArray( int count, const class ON_Layer*const* );

  /////////////////////////////////////////////////////
  //
  // Read/Write classes derived from ON_Object
  //

  /*
  Description:
    Reads and object from a 3dm archive;
  Parameters:
    ppObject - [out]  object is allocated and a pointer to the
                      allocated object is returned as *ppObject;
  Returns:
    0: failure - unable to read object because of file IO problems
    1: success
    3: unable to read object because it's UUID is not registered
       this could happen in cases where old code is attempting to read
       new objects.
  */
  int ReadObject( 
         ON_Object** ppObject
         );


  /*
  Description:
    Reads and object from a 3dm archive.
  Parameters:
    object - [in] The value of object.ON_ClassId()->Uuid() must
                  exactly match the class uuid in of the next
                  object in the archive.
  Returns:
    0: failure - unable to read object because of file IO problems.
    1: success
    2: unable to read object because the class id in the archive
       did not match pObject->ClassId.
  */
  int ReadObject( 
         ON_Object& object
         );

  bool WriteObject( const ON_Object* ); // writes object definition
  bool WriteObject( const ON_Object& ); // writes object definition

private:
  bool Internal_WriteObject(
    const ON_Object& model_object
  );
  bool Internal_WriteV5AnnotationObject(
    const class ON_Annotation& V6_annotation,
    const class ON_3dmAnnotationContext* annotation_context
  );
  bool Internal_WriteV2AnnotationObject(
    const class ON_OBSOLETE_V5_Annotation& V5_annotation,
    const class ON_3dmAnnotationContext* annotation_context
  );
public:


  ///////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  //
  // 3DM Interface - ignore if not reading/writing a 3DM file
  //                 this is here so that the infrastructure
  //                 for writing 3dm archives is available for
  //                 any type of serialization device.
  //

  /*
  Description:
    Specify which types of objects (ON_Brep, ON_Extrusion, ON_SubD, ...)
    save render meshes in the 3dm file.

  Parameters:
    object_type_flags - [in]
      The bits in object_type_flags correspond to ON::object_type values
      and identify the object types the setting will be applied to.

  Remarks:
    Saving render meshes increases file size, sometimes dramatically.

    Creating ON_Brep analysis meshes is often slow. 
    Disable saving ON_Brep analysis meshes when IO speed or file size is 
    a critical issue, the time expense of recreating the ON_Brep meshes
    when the file is read is acceptable, and the file will be read by Rhino. 
    Enable when the file size is not an issue or the file will be used by other 
    applications that may not be able to create meshes.

    Creating ON_Extrusion meshes is fast. Disable when IO speed or file size
    is an issue and the file will be read by Rhino.  Enable when the file
    will be used by other applications that may not be able to create meshes.

    Creating ON_SubD meshes is fast. Disable when IO speed or file size
    is an issue and the file will be read by Rhino.  Enable when the file
    will be used by other applications that may not be able to create meshes.
  */
  void EnableSave3dmRenderMeshes( 
    unsigned int object_type_flags,
    bool bSave3dmRenderMeshes 
    );

  /*
  Description:
    Specify which types of objects (ON_Brep, ON_Extrusion, ON_SubD, ...)
    save render meshes in the 3dm file.
  Returns:
    The bits in the return value correspond to ON::object_type values
    and identify the object types save analysis meshes in the 3dm file.
  */  
  unsigned int Save3dmRenderMeshObjectTypeFlags() const;

  /*
  Parameters:
    object_type - [in]
  Returns:
    true if render meshes for the specified object type will be 
    saved in the .3dm file.
  */  
  bool Save3dmRenderMesh(
    ON::object_type object_type
    ) const;

  /*
  Description:
    Specify which types of objects (ON_Brep, ON_Extrusion, ON_SubD, ...)
    save analysis meshes in the 3dm file.
  
  Parameters:
    object_type_flags - [in]
      The bits in object_type_flags correspond to ON::object_type values
      and identify the object types the setting will be applied to.

  Remarks:
    Saving analysis meshes increases file size, sometimes dramatically.

    Creating ON_Brep analysis meshes is often slow. 
    Disable saving ON_Brep analysis meshes when IO speed or file size is 
    a critical issue, the time expense of recreating the ON_Brep meshes
    when the file is read is acceptable, and the file will be read by Rhino. 
    Enable when the file size is not an issue or the file will be used by other 
    applications that may not be able to create meshes.

    Creating ON_Extrusion meshes is fast. Disable when IO speed or file size
    is an issue and the file will be read by Rhino.  Enable when the file
    will be used by other applications that may not be able to create meshes.

    Creating ON_SubD meshes is fast. Disable when IO speed or file size
    is an issue and the file will be read by Rhino.  Enable when the file
    will be used by other applications that may not be able to create meshes.
  */
  void EnableSave3dmAnalysisMeshes(
    unsigned int object_type_flags,
    bool bSave3dmAnalysisMeshes 
    );
  
  void SetSave3dmPreviewImage(
    bool bSave3dmPreviewImage
  );
  
  /*
  Returns:
    true: (default)
      If a preview image is included in the ON_3dmProperties information, it will be saved.
    false: 
      A preview imae, if it exists, will not be saved in the 3dm archive.
      This reduces archive size. 
      When Save3dmPreviewImage() is false, generating a preview image can be skipped.
  */
  bool Save3dmPreviewImage() const;

  /*
  Description:
    Control when some information, like preview images and mesh information, is
    compressed when writing 3dm archives. The default is true. 
    In special situations when the storage media is extremely fast and large file size
    is not a concern, disabling buffer compression can reduce file write time.
  Parameters:
    bUseBufferCompression - [in]
  Remarks:
    The default is true.
  */
  void SetUseBufferCompression(
    bool bUseBufferCompression
  );

  /*
  Returns:
    true: (default)
      Some information, including preview images and mesh information is compressed when
      writing 3dm archives. This reduces, sometimes dramatically, the size
      of the 3dm archive.
    false: 
      No compression is performed. This increases, sometimes dramatically, the size
      of the 3dm archive.
      In special situations when the storage media is extremely fast and large file size
      is not a concern, disabling buffer compression can reduce file write time.
  */
  bool UseBufferCompression() const;


  /*
  Description:
    Specify which types of objects (ON_Brep, ON_Extrusion, ON_SubD, ...)
    save analysis meshes in the 3dm file.
  Returns:
    The bits in the return value correspond to ON::object_type values
    and identify the object types save analysis meshes in the 3dm file.
  */  
  unsigned int Save3dmAnalysisMeshObjectTypeFlags() const;

  /*
  Parameters:
    object_type - [in]
  Returns:
    true if analysis meshes for the specified object type will be 
    saved in the .3dm file.
  */  
  bool Save3dmAnalysisMesh(
    ON::object_type object_type
    ) const;


  /*
  Returns:
    True if all user data and user tables should be read or written.
    False if some or no user data or user tables should be read or written.
  Remarks:
    AllUserDataSerializationIsEnabled() = (false == ShouldSerializeNoUserData() && false == ShouldSerializeSomeUserData())
  */
  bool ShouldSerializeAllUserData() const;

  /*
  Returns:
    True if no user data and user tables should be read or written.
    False if some or all user data or user tables should be read or written.
  Remarks:
    SerializeNoUserData() = (false == ShouldSerializeAllUserData() && false == ShouldSerializeSomeUserData())
  */
  bool ShouldSerializeNoUserData() const;

  /*
  Returns:
    True if some but not all user data or user tables should be
    read or written.
    False if all user data or no user data should be read or written.
  Remarks:
    SerializeSomeUserData() = (false == ShouldSerializeAllUserData() && false == ShouldSerializeNoUserData())

    Use ShouldSerializeUserDataItem(application_id,item_id) to
    determine if a specific object user data or user table should 
    be read or written.    
  */
  bool ShouldSerializeSomeUserData() const;

  /*
  Description:
    Determine if an application's (plug-in's) object user data 
    or user table should be read or written.
  Parameters:
    application_id - [in]
      The application id (often a plug-in id) for the object user data
      or user table.
    item_id - [in]
      item_id identifies which user data items should be read or written.
      - To determine if a specific type of object user data should
        be read or written, pass the value of ON_UserData.m_userdata_uuid.
      - To determine if the user table for the application should
        be read or written, pass application_id.
      - To determine if all object user data and the user table
        for the application should be read or written, pass nil.
  Returns:
    True if the identified user data or user table should be read or written.
  */
  bool ShouldSerializeUserDataItem(
    ON_UUID application_id,
    ON_UUID item_id
    ) const;

  /*
  Description:
    Specify the serialization option for object user data and user tables 
    that are not explicitly set by SetShouldSerializeUserDataItem().
  Parameters:
    bSerialize - [in]
  Remarks:
    If no setting is specified, all user data is read and written.
  */
  bool SetShouldSerializeUserDataDefault(
    bool bSerialize
    );

  bool ShouldSerializeUserDataDefault() const;


  /*
  Description:
    Specify if an application's (plug-in's) object user data
    or user table should be read or written.
  Parameters:
    application_id - [in]
      The application id (often a plug-in id) for the object user data
      or user table.
    item_id - [in]
      item_id identifies which user data items should be read or written.
      - To determine if a specific type of object user data should
        be read or written, pass the value of ON_UserData.m_userdata_uuid.
      - To determine if the user table for the application should
        be read or written, pass application_id.
      - To determine if all object user data and the user table
        for the application should be read or written, pass nil.
    bSerializeUserDataItem - [in]
      True to enable reading and writing of the specified item. 
      False to disable reading and writing of the specified item. 
  Returns:
    True if the input was valid and the setting was applied. 
    This function will not apply any settings after reading 
    or writing begins.
  */
  bool SetShouldSerializeUserDataItem(
    ON_UUID application_id,
    ON_UUID item_id,
    bool bSerializeUserDataItem
    );

  /*
  Description:
    Determine if an object has user data that should be written.
  Parameters:
    object - [in]
  Returns:
    True if object has user data that should be written.
  */
  bool ObjectHasUserDataToWrite(
    const class ON_Object* object
    ) const;

  bool ShouldWriteUserDataItem(
    const class ON_Object* object,
    const class ON_UserData* object_user_data
    ) const;

  /*
  Remarks:
    In a stable commercially released Rhino version N, CurrentArchiveVersion() = 10*N.
    In "early" Rhino N WIP, CurrentArchiveVersion() = 10*(N-1).
    In "later" Rhino N WIP, CurrentArchiveVersion() = 10*N.
  Returns:
    The current 3dm archive version that is saved by Rhino.
  */
  static int CurrentArchiveVersion();

  /*
  Description:
    As time passes, more tables have been added to 3dm archives.
  Parameters:
    table - [in]
  Returns:
    True if this archive has the specified table
  */
  bool ArchiveContains3dmTable(
    ON_3dmArchiveTableType table
    ) const;

  /*
  Parameters:
    archive_3dm_version - [in]
      1,2,3,4,5,50,60,70,...
    opennurbs_library_version - [in]
      a number > 100000000
  */
  static bool ArchiveContains3dmTable(
    ON_3dmArchiveTableType table,
    unsigned int archive_3dm_version,
    unsigned int opennurbs_library_version
    );

  bool WriteModelComponentName(
    const ON_ModelComponent& model_component
  );

  ///////////////////////////////////////////////////////////////////
  // Step 1: REQUIRED - Write/Read Start Section
  //

  
  /*
  Description:
    In rare cases, experts testing handling of corrupt 3dm files need to
    write a 3dm archive that is corrupt. In this rare testing situation,
    those experts should call IntentionallyWriteCorrupt3dmStartSectionForExpertTesting()
    exactly one time before they begin writing the file. The 32 byte identifier will
    replace the 1st 3 spaces with a capital X to mimic a file that became corrupt
    while residing on storage media.
  */
  void IntentionallyWriteCorrupt3dmStartSectionForExpertTesting();

  /*
  Parameters:
    version - [in]
       0, 2, 3, 4, 5, 50 or 60 (5 is treated as 50)
       
       If version is 0, then the value of ON_BinaryArchive::CurrentArchiveVersion()
       is used.

       Use either 0 or the value of ON_BinaryArchive::CurrentArchiveVersion()
       for the version parameter when you want your code to write the most 
       up to date file version. 

    sStartSectionComment - [in]
      nullptr or a UTF-8 encoded string with application name, et cetera.
      This information is primarily used when debugging files
      that contain problems.  McNeel and Associates stores
      application name, application version, compile date, 
      and the OS in use when file was written.
  */
  bool Write3dmStartSection( 
    int version,
    const char* sStartSectionComment
    );

  /*
  Parameters:
    version - [out]
       .3dm file version (2, 3, 4, 5, 50, 60)
    sStartSectionComment - [out]
      UTF-8 encoded string passed to Write3dmStartSection()
    destination_manifest - [in]
      manifest of the destination model
  */
  bool Read3dmStartSection( 
    int* version,
    ON_String& sStartSectionComment
    );

  /*
  Returns:
    A copy of the start section comment written to or read from the archive.
    If this function is called before Write3dmStartSection() or Read3dmStartSection(),
    it returns ON_String:EmptyString;
  */
  const ON_String& Archive3dmStartSectionComment() const;

  ///////////////////////////////////////////////////////////////////
  // Step 2: REQUIRED - Write/Read properties table
  //
  bool Write3dmProperties(
        const class ON_3dmProperties&
        );
  bool Read3dmProperties(
        class ON_3dmProperties&
        );

  /*
  Returns:
    A copy of the ON_3dmProperties information written to or read from the archive.
    If this function is called before Write3dmProperties() or Read3dmProperties(),
    it returns ON_3dmProperties:Empty;
  */
  const class ON_3dmProperties& Archive3dmProperties() const;

  ///////////////////////////////////////////////////////////////////
  // Step 3: REQUIRED - Write/Read settings table
  //
  bool Write3dmSettings(
        const class ON_3dmSettings&
        );
  bool Read3dmSettings(
        class ON_3dmSettings&
        );
  
  /*
  Returns:
    A copy of the ON_3dmSettings information written to or read from the archive.
    If this function is called before Write3dmSettings() or Read3dmSettings(),
    it returns ON_3dmSettings:Default;
  */
  const class ON_3dmSettings& Archive3dmSettings() const;

  ///////////////////////////////////////////////////////////////////
  // Step 4: REQUIRED - Write/Read bitmap table (it can be empty)
  //
  bool BeginWrite3dmBitmapTable();
  bool Write3dmImageComponent( 
    const class ON_ModelComponentReference& model_component_reference
    );
  bool Write3dmImageComponent( 
    const class ON_ModelComponent* model_component 
    );
  bool Write3dmBitmap( const class ON_Bitmap& );
  bool EndWrite3dmBitmapTable();

  bool BeginRead3dmBitmapTable();
  int  Read3dmBitmap(   // returns 0 at end of bitmap table
                        //         1 bitmap successfully read
            class ON_Bitmap** // bitmap returned here
            );
  bool EndRead3dmBitmapTable();

  ///////////////////////////////////////////////////////////////////
  // Step 5: REQUIRED - Write/Read texture mapping table (it can be empty)
  //
  bool BeginWrite3dmTextureMappingTable();
  bool Write3dmTextureMappingComponent( 
    const class ON_ModelComponentReference& model_component_reference
    );
  bool Write3dmTextureMappingComponent( 
    const class ON_ModelComponent* model_component 
    );
  bool Write3dmTextureMapping( const class ON_TextureMapping& );
  bool EndWrite3dmTextureMappingTable();

  bool BeginRead3dmTextureMappingTable();
  int  Read3dmTextureMapping( // returns 0 at end of table
            class ON_TextureMapping** // testuremapping returned here
            );
  bool EndRead3dmTextureMappingTable();

  ///////////////////////////////////////////////////////////////////
  // Step 6: REQUIRED - Write/Read render material table (it can be empty)
  //
  bool BeginWrite3dmMaterialTable();
  bool Write3dmMaterialComponent( 
    const class ON_ModelComponentReference& model_component_reference
    );
  bool Write3dmMaterialComponent( 
    const class ON_ModelComponent* model_component 
    );
  bool Write3dmMaterial( const class ON_Material& );
  bool EndWrite3dmMaterialTable();

  bool BeginRead3dmMaterialTable();
  int  Read3dmMaterial( // returns 0 at end of table
            class ON_Material** // material returned here
            );
  bool EndRead3dmMaterialTable();

  ///////////////////////////////////////////////////////////////////
  // Step 7: REQUIRED - Write/Read linetype table (it can be empty)
  //
  bool BeginWrite3dmLinetypeTable();
  bool Write3dmLinePatternComponent( 
    const class ON_ModelComponentReference& model_component_reference
    );
  bool Write3dmLinePatternComponent( 
    const class ON_ModelComponent* model_component 
    );
  bool Write3dmLinetype( 
    const class ON_Linetype& line_pattern
    );
  bool EndWrite3dmLinetypeTable();

  bool BeginRead3dmLinetypeTable();
  int  Read3dmLinetype(
  class ON_Linetype**
    );
  bool EndRead3dmLinetypeTable();

  ///////////////////////////////////////////////////////////////////
  // Step 8: REQUIRED - Write/Read layer table (it can be empty)
  //
  bool BeginWrite3dmLayerTable();
  bool Write3dmLayerComponent( 
    const class ON_ModelComponentReference& model_component_reference
    );
  bool Write3dmLayerComponent( 
    const class ON_ModelComponent* model_component 
    );
  bool Write3dmLayer( const ON_Layer& );
  bool EndWrite3dmLayerTable();

  bool BeginRead3dmLayerTable();
  int  Read3dmLayer( // returns 0 at end of table
            ON_Layer** // layer returned here
            );
  bool EndRead3dmLayerTable();

  ///////////////////////////////////////////////////////////////////
  // Step 9: REQUIRED - Write/Read group table (it can be empty)
  //
  bool BeginWrite3dmGroupTable();
  bool Write3dmGroupComponent( 
    const class ON_ModelComponentReference& model_component_reference
    );
  bool Write3dmGroupComponent( 
    const class ON_ModelComponent* model_component 
    );
  bool Write3dmGroup( const class ON_Group& );
  bool EndWrite3dmGroupTable();

  bool BeginRead3dmGroupTable();

  // Description:
  //   Reads groups from group table.  If the group definition is
  //   read, a group is created by calling new ON_Group(),
  //   initialized with values stored in the archive, and 
  //   returned.
  //
  // Parameters:
  //   ppGroup - If the group definition is
  //   read, a group is created by calling new ON_Group(),
  //   initialized with values stored in the archive, and 
  //   a pointer to the new group is returned in *ppGroup.
  //
  // Returns:
  //
  //   @untitled table
  //   0     at the end of the group table
  //   1     group definition was successfully read
  //   -1    archive is corrupt at this point
  //
  // Example:
  //   Calls to Read3dmGroup need to be bracketed by calls
  //   to BeginRead3dmGroupTable() / EndRead3dmGroupTable().
  //
  //           archive.BeginRead3dmGroupTable();
  //           ON_Group* pGroup;
  //           int rc = 1;
  //           while(rc==1)
  //           { //
  //             pGroup = 0;
  //             archive.Read3dmGroup(&pGroup);
  //             if ( pGroup )
  //               do something with pGroup
  //           } //
  //           archive.EndRead3dmGroupTable();
  //      
  int  Read3dmGroup(
            class ON_Group** // ppGroup
            );

  bool EndRead3dmGroupTable();


  ///////////////////////////////////////////////////////////////////////
  ////// Step 10: REQUIRED - Write/Read text_style table (it can be empty)
  //////
  ////ON_DEPRECATED_MSG("remove call. Text style information is now part of ON_DimStyle.")
  ////bool BeginWrite3dmTextStyleTable();
  ////////bool Write3dmTextStyleComponent( 
  ////////  const class ON_ModelComponentReference& model_component_reference
  ////////  );
  ////////bool Write3dmTextStyleComponent( 
  ////////  const class ON_ModelComponent* model_component 
  ////////  );
  ////ON_DEPRECATED_MSG("remove call. Text style information is now part of ON_DimStyle.")
  ////bool Write3dmTextStyle( 
  ////  const class ON_TextStyle& 
  ////  );
  ////ON_DEPRECATED_MSG("remove call. Text style information is now part of ON_DimStyle.")
  ////bool EndWrite3dmTextStyleTable();

private:
  ////bool Internal_BeginWrite3dmTextStyleTable();
  bool Internal_Write3dmTextStyle( 
    const class ON_TextStyle& 
    );
  /////bool Internal_EndWrite3dmTextStyleTable();

public:

  //////ON_DEPRECATED_MSG("remove call. Text style information is now part of ON_DimStyle.")
  //////bool BeginRead3dmTextStyleTable();

  //////ON_DEPRECATED_MSG("remove call. Text style information is now part of ON_DimStyle.")
  //////int Read3dmTextStyle(
  //////          class ON_TextStyle** // ppTextStyle
  //////          );

  //////ON_DEPRECATED_MSG("remove call. Text style information is now part of ON_DimStyle.")
  //////bool EndRead3dmTextStyleTable();

private:
  int Internal_Read3dmTextStyle(
    class ON_TextStyle** // ppTextStyle
  );
public:

  ///////////////////////////////////////////////////////////////////
  // Step 11: REQUIRED - Write/Read dimstyle table (it can be empty)
  //
  bool BeginWrite3dmDimStyleTable();
  
  bool Write3dmDimStyleComponent( 
    const class ON_ModelComponentReference& model_component_reference
    );
  bool Write3dmDimStyleComponent( 
    const class ON_ModelComponent* model_component 
    );
  bool Write3dmDimStyle( const class ON_DimStyle& );

  bool EndWrite3dmDimStyleTable();

private:
  bool Internal_Write3dmDimStyle( const class ON_DimStyle&, bool bUpdateManifest );
public:

  bool BeginRead3dmDimStyleTable();

  // Description:
  //   Reads annotation dimension styles from dimension style table.
  //   If the dimension style definition is read, 
  //   a dimension style is created by calling new ON_DimStyle(),
  //   initialized with values stored in the archive, and 
  //   returned.
  //
  // Parameters:
  //   ppDimStyle - If the dimstyle definition is
  //   read, a dimstyle is created by calling new ON_DimStyle(),
  //   initialized with values stored in the archive, and 
  //   a pointer to the new dimstyle is returned in *ppDimStyle.
  //
  // Returns:
  //
  //   @untitled table
  //   0     at the end of the dimension style table
  //   1     dimension style definition was successfully read
  //   -1    archive is corrupt at this point
  //
  // Example:
  //   Calls to Read3dmDimStyle need to be bracketed by calls
  //   to BeginRead3dmDimStyleTable() / EndRead3dmDimStyleTable().
  //
  //           archive.BeginRead3dmDimStyleTable();
  //           int rc = 1;
  //           ON_DimStyle* pDimStyle;
  //           while(rc==1)
  //           { //
  //             pDimStyle = 0;
  //             archive.Read3dmDimStyle(&pDimStyle);
  //             if ( pDimStyle )
  //               do something with pDimStyle
  //           } //
  //           archive.EndRead3dmDimStyleTable();
  //      
  int Read3dmDimStyle(
    class ON_DimStyle** ppDimStyle
    );

private:
  int Internal_Read3dmDimStyle(
    class ON_DimStyle** ppDimStyle
    );

  void Internal_ConvertTextStylesToDimStyles();

  double Internal_ArchiveModelSpaceTextScale() const;

  const ON_DimStyle* Internal_ArchiveCurrentDimStyle();

public:
  bool EndRead3dmDimStyleTable();

  /*
    Internal_Read3dmDimStyleOverrides() is a public function on ON_BinaryArchive because 
    it must be called from ON_Annotation::Internal_ReadAnnotation().
    There is no other reason to call this function.
  */
public:
  bool Internal_Read3dmDimStyleOverrides(
    class ON_Annotation& annotation,
    bool bFromDimStyleTable
  );

  /*
    Internal_Write3dmDimStyleOverrides() is a public function on ON_BinaryArchive because 
    it must be called from ON_Annotation::Internal_WriteAnnotation().
    There is no other reason to call this function.
  */
public:
  bool Internal_Write3dmDimStyleOverrides(
    const class ON_Annotation& annotation,
    const class ON_DimStyle* dim_style_overrides
  );

public:
  ///////////////////////////////////////////////////////////////////
  // Step 12: REQUIRED - Write/Read render light table (it can be empty)
  //
  bool BeginWrite3dmLightTable();
  bool Write3dmModelLightComponent( 
    const class ON_ModelComponentReference& model_component_reference
    );
  bool Write3dmModelLightComponent( 
    const class ON_ModelGeometryComponent* model_light
    );
  bool Write3dmLight(
    const class ON_Light&,
    const class ON_3dmObjectAttributes* // can be nullptr
    );
  bool EndWrite3dmLightTable();

  bool BeginRead3dmLightTable();

  // Call either Read3dmModelLight or Read3dmLight
  /*
  Parameters:
    model_light - [out]
      ON_ModelGeometryComponent returned here.
      nullptr returned at end of the table.
    object_filter - [in]
      optional filter made by setting ON::object_type bits
  Returns:
     0 at end of object table
     1 if object is read
     2 if object is skipped because it does not match filter
    -1 if file is corrupt
  */
  int Read3dmModelLight(
    class ON_ModelGeometryComponent** model_light
    );

  int  Read3dmLight(
    class ON_Light** light,
    class ON_3dmObjectAttributes* attributes
    );

  bool EndRead3dmLightTable();


  ///////////////////////////////////////////////////////////////////
  // Step 13: REQUIRED - Write/Read hatch pattern table (it can be empty)
  //
  bool BeginWrite3dmHatchPatternTable();
  bool Write3dmHatchPatternComponent( 
    const class ON_ModelComponentReference& model_component_reference
    );
  bool Write3dmHatchPatternComponent( 
    const class ON_ModelComponent* model_component 
    );
  bool Write3dmHatchPattern( const class ON_HatchPattern&);
  bool EndWrite3dmHatchPatternTable();

  bool BeginRead3dmHatchPatternTable();
  int  Read3dmHatchPattern(class ON_HatchPattern**);
  bool EndRead3dmHatchPatternTable();

  ///////////////////////////////////////////////////////////////////
  // Step 14: REQUIRED - Write/Read instance definition table (it can be empty)
  //
  bool BeginWrite3dmInstanceDefinitionTable();
  bool Write3dmInstanceDefinitionComponent( 
    const class ON_ModelComponentReference& model_component_reference
    );
  bool Write3dmInstanceDefinitionComponent( 
    const class ON_ModelComponent* model_component 
    );
  bool Write3dmInstanceDefinition( const class ON_InstanceDefinition& );
  bool EndWrite3dmInstanceDefinitionTable();

  bool BeginRead3dmInstanceDefinitionTable();

  /*
   Description:
     Reads instance definitions from instance definition table.
  
   Parameters:
     ppInstanceDefinition - If an instance definition is
     read, an instance definition is created by calling new 
     ON_InstanceDefinition(), initialized with values stored
     in the archive, and a pointer to the new instance definition
     is returned in *ppInstanceDefinition.
  
   Returns:
  
     @untitled table
     0     at the end of the instance definition table
     1     instance definition was successfully read
     -1    archive is corrupt at this point
  
   Example:
     Calls to Read3dmInstanceDefinition need to be bracketed by calls
     to BeginRead3dmInstanceDefinitionTable() / EndRead3dmInstanceDefinitionTable().
  
             archive.BeginRead3dmInstanceDefinitionTable();
             int rc = 1;
             ON_InstanceDefinition* pInstanceDefinition;
             while(rc==1)
             { 
               pInstanceDefinition = 0;
               archive.Read3dmInstanceDefinition(&pInstanceDefinition);
               if ( pInstanceDefinition )
                 do something with pInstanceDefinition
             } 
             archive.EndRead3dmInstanceDefinitionTable();
  */      
  int Read3dmInstanceDefinition(
    class ON_InstanceDefinition** // ppInstanceDefinition
    );

  bool EndRead3dmInstanceDefinitionTable();

  ///////////////////////////////////////////////////////////////////
  // Step 15: REQUIRED - Write/Read geometry and annotation table (it can be empty)
  //
  bool BeginWrite3dmObjectTable();
  bool Write3dmModelGeometryComponent( 
    const class ON_ModelComponentReference& model_component_reference
    );
  bool Write3dmModelGeometryComponent( 
    const class ON_ModelGeometryComponent* model_geometry
    );
  bool Write3dmObject( 
         const ON_Object&,
         const ON_3dmObjectAttributes* // optional
         );
  bool EndWrite3dmObjectTable();

  bool BeginRead3dmObjectTable();

  // Call either Read3dmModelGeometry or Read3dmObject
  /*
  Parameters:
    model_geometry - [out]
      ON_ModelGeometryComponent returned here.
      nullptr returned at end of the table.
    object_filter - [in]
      optional filter made by setting ON::object_type bits
  Returns:
     0 at end of object table
     1 if object is read
     2 if object is skipped because it does not match filter
    -1 if file is corrupt
  */
  int Read3dmModelGeometry(
    class ON_ModelGeometryComponent** model_geometry,
    unsigned int object_filter = 0
    );

  /*
  Parameters:
    bManageGeometry - [in]
      true: model_geometry will reference count and delete the ON_Geometry pointer.
      false: The caller must delete the ON_Geometry pointer.
    bManageAttributes - [in]
      true: model_geometry will reference count and delete the ON_3dmObjectAttributes pointer.
      false: The caller must delete the ON_3dmObjectAttributes pointer.
    model_geometry - [out]
      ON_ModelGeometryComponent returned here.
      nullptr returned at end of the table.
    object_filter - [in]
      optional filter made by setting ON::object_type bits
      0 = no filter.
  Returns:
     0 at end of object table
     1 if object is read
     2 if object is skipped because it does not match filter
    -1 if file is corrupt
  */
  int Read3dmModelGeometryForExperts(
    bool bManageGeometry,
    bool bManageAttributes,
    class ON_ModelGeometryComponent** model_geometry,
    unsigned int object_filter
    );

  /*
  Parameters:
    model_object - [out]
      nullptr returned at end of the table.
    attributes - [out]
      If not nullptr, then attributes are returned here
    object_filter - [in]
      optional filter made by setting ON::object_type bits
  Returns:
     0 at end of object table
     1 if object is read
     2 if object is skipped because it does not match filter
    -1 if file is corrupt
  */
  int Read3dmObject(
    ON_Object** model_object,
    ON_3dmObjectAttributes* attributes,
    unsigned int object_filter = 0
    );

private:
  /*
  Description:
    In rare cases one object must be converted into another.
    Examples include reading obsolete objects and converting them into their 
    current counterpart, converting WIP objects into a proxy for a commercial build, 
    and converting a proxy object into a WIP object for a WIP build.
  */
  ON_Object* Internal_ConvertObject(
    const ON_Object* archive_object,
    const ON_3dmObjectAttributes* attributes
  ) const;

public:

  bool EndRead3dmObjectTable();

  ///////////////////////////////////////////////////////////////////
  // Step 16: REQUIRED - Write/Read history record table (it can be empty)
  //
  bool BeginWrite3dmHistoryRecordTable();
  bool Write3dmHistoryRecordComponent( 
    const class ON_ModelComponentReference& model_component_reference
    );
  bool Write3dmHistoryRecordComponent( 
    const class ON_ModelComponent* model_component 
    );
  bool Write3dmHistoryRecord( 
         const class ON_HistoryRecord&
         );
  bool EndWrite3dmHistoryRecordTable();

  bool BeginRead3dmHistoryRecordTable();

  /*
  Returns:
           0 at end of object table
           1 if object is read
          -1 if file is corrupt
  */
  int  Read3dmHistoryRecord(
          class ON_HistoryRecord*&
          );
  bool EndRead3dmHistoryRecordTable();

  ///////////////////////////////////////////////////////////////////
  // Step 17: OPTIONAL - Write/Read 0 or more user tables
  //

  /*
  Description:
    Write the user table header information that must precede
    the user table information written by a plug-in.
  Parameters:
    plugin_id - [in]
    bSavingGoo - [in]
      Set to false if a plug-in will be used to write
      the user table.  Set to true if a user table written by
      a missing plug-in is being resaved. In this case,
      goo_3dm_version and goo_opennurbs_version must also be
      set.  In practice, you should use Write3dmAnonymousUserTableRecord()
      to handle writing "goo" and use this function only when
      the plug-in in present.
    goo_3dm_version - [in]
      If bSavingGoo is false, this parameter must be zero and
      ON_BinaryArchive::Archive3dmVersion() will be used.
      If bSavingGoo is true, this parameter must be the version of 
      the 3dm archive (1,2,3,4,5,50,...) the plug-in code used to 
      write the user table.
    goo_opennurbs_version - [in]
      If bSavingGoo is false, this parameter must be zero and
      ON_BinaryArchive::ArchiveOpenNURBSVersion() will be used.
      If bSavingGoo is true, this parameter must be the version
      of the opennurbs the plug-in code used to write the 
      user table.
  Returns:
    True if the the user information can be written.
    False if user information should not be written.
  */
  bool BeginWrite3dmUserTable(
    ON_UUID plugin_id,
    bool bSavingGoo,
    int goo_3dm_version,
    unsigned int goo_opennurbs_version
    );

  bool EndWrite3dmUserTable();

  /*
  Description:
    If Read3dmAnaonymousUserTable() was used to read ON_3dmGoo because a 
    plug-in was not present, then use Write3dmAnonymousUserTableRecord()
    to put than information back into the archive.
    Write3dmAnonymousUserTableRecord() writes the entire record.
    Do NOT call BeginWrite3dmUserTable() / EndWrite3dmUserTable() when
    using Write3dmAnonymousUserTableRecord().
  Parameters:
    plugin_id - [in]
    goo_version - [in]
      The version of the archive (1,2,3,4,5,50,...) that was used when
      the plug-in wrote the user table.
    goo_opennurbs_version - [in]
      The version of opennurbs ( YYYMMDDN ) that was used when the 
      plug-in wrote the user table.
    goo - [in]
  Returns:
    True if the goo was written.
    False if skipped because it could not be robustly saved.
  */
  bool Write3dmAnonymousUserTableRecord( 
    ON_UUID plugin_id,
    int goo_3dm_version,
    unsigned int goo_opennurbs_version,
    const class ON_3dmGoo& goo
    );

  ON_DEPRECATED_MSG("use BeginWrite3dmUserTable(plugin_id, bSavingGoo, 3dm_version, opennurbs_version)")
  bool BeginWrite3dmUserTable( const ON_UUID& );

  ON_DEPRECATED_MSG("use Write3dmAnonymousUserTableRecord(plugin_id, ..., goo)")
  bool Write3dmAnonymousUserTable( const class ON_3dmGoo& );

  /*
  Parameters:
    plugin_id - [out] 
      id of plug-in that wrote the user table
    bLastSavedAsGoo - [out] 
      True if this table was saved into this archive as goo because
      the plug-in was not present at the time of the save.
    archive_3dm_version - [out]
      Version of the archive the plug-in wrote to.  When bLastSavedAsGoo
      is true, this number can be different from Archive3dmVersion().
    archive_opennurbs_version - [out]
      Version of opennurbs the plug-in used to write the archive.  
      When bLastSavedAsGoo is true, this number can be different 
      from ArchiveOpenNURBSVersion().     
  Returns:
    False when there are no more user tables or an IO error occurs.
  */
  bool BeginRead3dmUserTable(
    ON_UUID& plugin_id,
    bool* bLastSavedAsGoo,
    int* archive_3dm_version,
    unsigned int* archive_opennurbs_version
    );

  /*
  Description:
    If the plug-in that wrote the user table is not present and you need
    to read and resave the user table, then use Read3dmAnonymousUserTable()
    to load the information into "goo".
    If you do not need to resave the information, then simply call EndRead3dmUserTable()
    to skip over this table.
  */
  bool Read3dmAnonymousUserTable( 
    int archive_3dm_version,
    unsigned int archive_opennurbs_version,
    ON_3dmGoo& goo
    );

  bool EndRead3dmUserTable();

  ///////////////////////////////////////////////////////////////////
  // Step 18: REQUIRED when writing / OPTIONAL when reading
  //         Write end of file marker.  This information is primarily
  //         used when debugging files to make sure the end of the file
  //         hasn't been cut off.
  //

  // Description:
  //   Writes a TCODE_ENDOFFILE chunk that contains the number
  //   of bytes in the archive.
  //
  // Returns:
  //   true if successful, false if unable to write to archive.
  bool Write3dmEndMark();

  // Description:
  //   Checks for a TCODE_ENDOFFILE chunk at the current position.
  //   If it finds one, it reads it and returns the number
  //   of bytes in the archive.  Comparing this number with
  //   the current file position can help detect files that
  //   have been damaged by losing sections.
  //
  // Parameters:
  //   sizeof_archive - [out] number of bytes written to archive
  //
  // Returns:
  //   true if successful, false if unable to find or read
  //   a TCODE_ENDOFFILE chunk.
  bool Read3dmEndMark( 
           size_t* // sizeof_archive
           );

  ///////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  // Low level tools to  Write/Read chunks. See opennurbs_3dm.h for details
  // about the structure of chunks.  Every chunk must begin with a
  // call to BeginWrite/ReadChunk().
  // If BeginWriteChunk()/BeginReadChunk() returns true, then
  // you must call EndWrite/ReadChunk() or cease using the archive.

  // Description:
  //   Writes a chunk header containing 4 byte typecode and value.
  //
  // Parameters:
  //   typecode - [in] a TCODE_* number from opennurbs_3dm.h
  //   value    - [in] if (typecode&TCODE_SHORT) is nonzero, then
  //              this is the value to be saved.  Otherwise, pass
  //              a zero and the EndWrite3dmChunk() call will
  //              store the length of the chunk.
  //
  // Returns:
  //   true if write was successful.
  bool BeginWrite3dmChunk(
        unsigned int, // typecode
        int // value
        );

  bool BeginWrite3dmBigChunk(
        ON__UINT32 typecode,
        ON__INT64 value
        );

  /*
  Description:
    Begins writing a chunk.
  Parameters:
    tcode - [in] chunk's typecode from opennurbs_3dm.h.  This cannot be a short tcode.
    major_version - [in] ( >= 1)
    minor_version - [in] ( >= 0 )
  Returns:
    True if input was valid and chunk was started.  In this case
    You must call EndWrite3dmChunk(), even if something goes wrong
    while you attempt to write the contents of the chunk.
    False if input was not valid or the write failed.
  */
  bool BeginWrite3dmChunk(
        unsigned int tcode,
        int major_version,
        int minor_version
        );

  /*
  Description:
    If version >= 0, calls BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,version).
  */
  bool BeginWrite3dmAnonymousChunk(
    int version
    );


  // updates length in chunk header
  bool EndWrite3dmChunk();

  bool Write3dmGoo( const ON_3dmGoo& ); // call to write "goo"

  //ON_DEPRECATED_MSG("use BeginRead3dmBigChunk")
  //bool BeginRead3dmChunk(
  //      unsigned int*,   // typecode from opennurbs_3dm.h
  //      int*             // value
  //      );

  // When the end of the 3dm file is reached, BeginReadChunk() will
  // return true with a typecode of TCODE_ENDOFFILE.
  bool BeginRead3dmBigChunk(
        unsigned int*,   // typecode from opennurbs_3dm.h
        ON__INT64*       // value
        );
  /*
  Description:
    Begins reading a chunk that must be in the archive at this location.
  Parameters:
    expected_tcode - [in] chunk's typecode from opennurbs_3dm.h
    major_version - [out] 
    minor_version - [out] 
  Returns:
    True if beginning of the chunk was read.  In this case
    You must call EndRead3dmChunk(), even if something goes wrong
    while you attempt to read the interior of the chunk.
    False if the chunk did not exist at the current location in the file.
  */
  bool BeginRead3dmChunk(
        unsigned int expected_tcode,
        int* major_version,
        int* minor_version
        );

  /*
  Description:
    Calls BeginWRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version),
    checks that 1 == major_version, minor_version >= 0 and returns the value
    of minor_version as version.
  Parameters:
    version - [out]
  */
  bool BeginRead3dmAnonymousChunk(
    int* version
    );

  /*
  Description:
    Calling this will skip rest of stuff in chunk if it was only partially read.
  Parameters:
    bSupressPartiallyReadChunkWarning - [in]
      Generally, a call to ON_WARNING is made when a chunk is partially
      read.  If bSupressPartiallyReadChunkWarning is true, then
      no warning is issued for partially read chunks.
  */
  bool EndRead3dmChunk(); 
  bool EndRead3dmChunk(bool bSupressPartiallyReadChunkWarning); 


  ///////////////////////////////////////////////////////////////////
  //
  // Tools for dictionary IO (used in .NET)
  //

  /*
  Description:
    Begins writing a dictionary.
  Parameters:
    dictionary_id - [in]
    version - [in]
      It is suggested that you use ON_VersionNumberConstruct() to create
      a version number.
    dictionary_name - [in]
      You may pass nullptr.
  Remarks:
    Begins a new chunk with tcode TCODE_DICTIONARY and then writes
    a TCODE_DICTIONARY_ID chunk containing the id, version and name.
    After calling this function, you may either write entries by
    calling
      BeginWriteDictionaryEntry(); 
      write entry definition...
      EndWriteDictionaryEntry();
    or you may finish writing the dictionary by calling
      EndWriteDictionary();
  */
  bool BeginWriteDictionary(
          ON_UUID dictionary_id,
          unsigned int version,
          const wchar_t* dictionary_name
          );
  /*
  Description:
    Begins writing a dictionary entry.
  Parameters:
    de_type - [in]
    entry_name - [in]
  Returns:
    true 
      Entry header was written and you must call EndWriteDictionary()
      after writing the entry data.
    false 
      Failed to write entry header.  Do not call EndWriteDictionary().
  Remarks:
    Begins a new chunk with tcode TCODE_DICTIONARY_ENTRY,
    then writes the int, and then writes the string.
  */
  bool EndWriteDictionary();

  /*
  Description:
    Begins writing a dictionary entry.
  Parameters:
    de_type - [in]
    entry_name - [in]
  Returns:
    true 
      Entry header was written and you must call EndWriteDictionary()
      after writing the entry data.
    false 
      Failed to write entry header.  Do not call EndWriteDictionary().
  Remarks:
    Begins a new chunk with tcode TCODE_DICTIONARY_ENTRY,
    then writes the int, and then writes the string.
  */
  bool BeginWriteDictionaryEntry(
          int de_type, 
          const wchar_t* entry_name
          );
  bool EndWriteDictionaryEntry();

  bool BeginReadDictionary(
          ON_UUID* dictionary_id,
          unsigned int* version,
          ON_wString& dictionary_name
          );
  bool EndReadDictionary();

  /*
  Description:
    Begin reading a dictionary entry.
  Parameters:
    de_type - [out]
    entry_name - [out]
  Returns:
    0: serious IO error
    1: success
        read information and then call EndReadDictionaryEntry()
    2: at end of dictionary
  */
  int BeginReadDictionaryEntry(
          int* de_type, 
          ON_wString& entry_name
          );
  bool EndReadDictionaryEntry();

  bool Read3dmGoo( ON_3dmGoo& ); // Call to read "goo"

  ON_DEPRECATED_MSG("use PeekAt3dmBigChunkType")
  bool PeekAt3dmChunkType( // does not change file position
        unsigned int*,   // typecode from opennurbs_3dm.h
        int*             // value
        );

  bool PeekAt3dmBigChunkType( // does not change file position
        ON__UINT32* typecode,
        ON__INT64* big_value
        );

  bool Seek3dmChunkFromStart( 
        // beginning at the start of the active chunk, search portion of
        // archive included in active chunk for the start of a subchunk 
        // with the specified type.
        // if true is returned, then the position is set so the next call to
        // BeginRead3dmChunk() will read a chunk with the specified typecode
        unsigned int    // typecode from opennurbs_3dm.h
        );
  bool Seek3dmChunkFromCurrentPosition( 
        // beginning at the current position, search portion of archive
        // included in active chunk for the start of a subchunk with the
        // specified type.
        // if true is returned, then the position is set so the next call to
        // BeginRead3dmChunk() will read a chunk with the specified typecode
        unsigned int    // typecode from opennurbs_3dm.h
        );

  // A chunk version is a single byte that encodes a major.minor 
  // version number.  Useful when creating I/O code for 3dm chunks
  // that may change in the future.  Increment the minor version 
  // number if new information is added to the end of the chunk. 
  // Increment the major version if the format of the chunk changes
  // in some other way.
  bool Write3dmChunkVersion(
    int, // major // 0 to 15
    int  // minor // 0 to 16
    );
  bool Read3dmChunkVersion(
    int*, // major // 0 to 15
    int*  // minor // 0 to 16
    );

  /*
  Description:
    Low level tool to writes user data attached to the 
    object.  This function should never be called
    directly.
  Parameters:
    object - [in]
  Returns:
    True if successful.
  */
  bool WriteObjectUserData( const ON_Object& object );

  /*
  Description:
    Low level tool to read user data and attach it to
    the object.  This function should never be called
    directly.
  Parameters:
    object - [in/out]
  Returns:
    True if successful.
  */
  bool ReadObjectUserData( ON_Object& object );

  /*
  Description:
    If a 3dm archive is being read or written, then this is the
    version of the 3dm archive format (1, 2, 3, 4, 5, 50, 60, ...).
  Returns:
    @untitle table
    0     a 3dm archive is not being read/written
    1     a version 1 3dm archive is being read/written
    2     a version 2 3dm archive is being read/written
    3     a version 3 3dm archive is being read/written
    4     a version 4 3dm archive is being read/written
    5     an old version 5 3dm archive is being read
    50    a version 5 3dm archive is being read/written
    60    a version 6 3dm archive is being read/written
    70    a version 7 3dm archive is being read/written
    ...
  See Also:
    ON_BinaryArchive::ArchiveOpenNURBSVersion
  */
  int Archive3dmVersion() const;

  /*
  Description:
    If a 3dm archive is being read, then this is the version
    of openNURBS that was used to write the archive.  This value
    is only available after ON_BinaryArchive::Read3dmProperties
    is called.
  See Also:
    ON_BinaryArchive::Archive3dmVersion
    ON_BinaryArchive::Read3dmProperties
  Returns:
    Version of openNURBS used to write the archive.  The openNURBS
    version is the value returned by ON::Version.
  See Also:
    ON::Version
    ON_BinaryArchive::Read3dmProperties
    ON_BinaryArchive::Archive3dmVersion
  Remarks:
    This value is rarely needed.  You probably want to
    use ON_BinaryArchive::Archive3dmVersion.
  */
  unsigned int ArchiveOpenNURBSVersion() const;
  
  /*
  Returns:
    The runtime environment where the archive was created.
  Remarks:
    When reading an archive, compare the values of 
    ON_BinaryArchive::ArchiveRuntimeEnvironment()
    and 
    ON::CurrentRuntimeEnvironment() 
    to determine if adjustments need to be made to resources provided
    by runtime environments, like fonts.
  */
  ON::RuntimeEnvironment ArchiveRuntimeEnvironment() const;

  const ON_DimStyle& ArchiveCurrentDimStyle() const;
  const int ArchiveCurrentDimStyleIndex() const;
  const ON_UUID ArchiveCurrentDimStyleId() const;

  /*
  Description:
    If a 3dm archive is being written to a version 2,3,4 or 50 format,
    then new format opennurbs version numbers need to be saved in the
    old YYYYMMDDN format.  This function returns the value that should
    be written in the file.
  Parameters:
    archive_3dm_version - [in]
      Version of the file that is being written (2, 3, 4, 50, 60, ...)
    opennurbs_version - [in]
      opennurbs version number
  Returns:
    Value to save in the file.
  */
  static unsigned int ArchiveOpenNURBSVersionToWrite(
    unsigned int archive_3dm_version,
    unsigned int opennurbs_version
    );

  /*
  Description:
    When a 3dm archive is saved from an MFC application that
    supports Windows linking/embedding, the first 5kb to 1mb
    of the file contains information that is put there by MFC.
    ArchiveStartOffset() returns the offset into the file where
    the 3dm archive actually begins. The call to 
    ON_BinaryArchive::Read3dmStartSection() calculates this
    offset and stores the value in m_3dm_start_section_offset.
  Returns:
    Offset into the binary "file" where the actual 3dm archive
    begins.
  Remarks:
    Generally, this value can be ignored. This function is
    a diagnostice tool that is used to analyzed damaged files.
  */
  size_t ArchiveStartOffset() const;

  /*
  Description:
    Expert user function for reading damaged files.
  Parameters:
    chunk - [out] current chunk.
  Returns:
    Level of the chunk or 0 if there is no current
    chunk.
  */
  int GetCurrentChunk(ON_3DM_CHUNK& chunk) const;
  int GetCurrentChunk(ON_3DM_BIG_CHUNK& big_chunk) const;

  /*
  Description:
    Expert user function for reading damaged files.  The search starts
    at the beginning of the file.
  Parameters:
    tcode_table - [in] typecode of the table
    tcode_record - [in] typecode of the record
    class_uuid - [in] id of the opennurbs class in the record
    min_length_data - [in] minimum size of the opennurbs class data
  Returns:
    True if the table start is found.  In this case the current
    position of the archive is at the start of the table and
    the standared BeginRead3dm...Table() function can be used.
    False if the table start is not found.
  */
  bool FindTableInDamagedArchive(
          unsigned int tcode_table,
          unsigned int tcode_record,
          ON_UUID class_uuid,
          int min_length_data
          );

  /*
  Description:
    Expert user function for studying contents of a file.
    The primary use is as an aid to help dig through files
    that have been damaged (bad disks, transmission errors, etc.)
    If an error is found, a line that begins with the word
    "ERROR" is printed.
  Parameters:
    text_log - [in] place to print information
    recursion_depth - [in] simply a counter
        to aid in debugging.
  Returns:
    0 if something went wrong, otherwise the typecode
    of the chunk that was just studied.
  */
  unsigned int 
  Dump3dmChunk(
        ON_TextLog& text_log, 
        int recursion_depth = 0
        );

  enum class eStorageDeviceError : unsigned int
  {
    None = 0,
    
    // values from 1 through 0xFFFFFFF0 are used for IO device 
    // specific exceptions that terminate reading or writing.

    WriteFailed = 0xFFFFFFF1, // writing to device failed
    SeekFailedDuringWriting = 0xFFFFFFF2, // virtual Seek() failed during writing
    ReadFailed = 0xFFFFFFF8,  // reading from device failed
    SeekFailedDuringReading = 0xFFFFFFF9,  // virtual Seek() failed during reading
    UnknownDeviceError = 0xFFFFFFFFU
  };

  static ON_BinaryArchive::eStorageDeviceError StorageDeviceErrorFromUnsigned(
    unsigned int storage_device_error_as_unsigned
    );

  /*
  Description:
    An error terminated reading or writing
  Returns:
    0: no error terminiated reading or writing
    !=0: See the ON_BinaryArchive::DeviceErrorType for values
  */
  unsigned int StorageDeviceError() const;

private:
  /*
  Description:
    Works like the C runtrim fread().
  Returns:
    actual number of bytes read (like fread())
  */
  size_t Read(size_t, void*);

protected:
  /*
  Remarks:
    In some unusual situations when reading old or damaged files, a read may fail.
    Call MaskReadError( ON__UINT64 sizeof_request, ON__UINT64 sizeof_read )
    before calling ON_ERROR().
  */
  virtual size_t Internal_ReadOverride( size_t, void* ) = 0; 

private:
  /*
  Description:
    Works like the C runtrim fwrite().
  Returns:
    actual number of bytes written (like fwrite())
  */
  size_t Write( size_t, const void* );
protected:
  virtual size_t Internal_WriteOverride( size_t, const void* ) = 0;

public:
  /*
  Description:
    Force Write() to flush any buffered data to physical archive.
  Returns:
    True if successful or if there is nothing to flush.  False if
    information could not be flushed.
  */
  virtual bool Flush() = 0;

  /*
  Description:
    When ON_BinaryArchive::ReadObject() encounters userdata and
    the user data class id is not present,  LoadUserDataApplication
    is called to load the application that created user data.
  Returns:
    0 - could not load the application
    1 - successfully loaded the application
    2 - the application was already loaded
  */
  virtual
  int LoadUserDataApplication( 
    ON_UUID application_id 
    );

  bool SetArchive3dmVersion(int);
  bool SetOpenNURBS3dmVersion(unsigned int v);

  /*
  Description:
    A non-zero storage device error terminates reading or writing.
    See the ON_BinaryArchive::eStorageDeviceError for values.
  Parameter:
    storage_device_error - [in]
      A non-zero code that identifies an error the terminates 
      reading or writing.  
      See ON_BinaryArchive::CriticalErrorCodes for values
  Remarks:
    Once set, the storage_device_error value cannot be changed.
  */
  void SetStorageDeviceError(
    ON_BinaryArchive::eStorageDeviceError storage_device_error
    );
  void SetStorageDeviceError(
    unsigned int storage_device_error
    );

private:
  // 16 bit integer IO
  bool WriteInt8( size_t, const ON__INT8* );
  bool ReadInt8( size_t, ON__INT8* );

  // 16 bit integer IO
  bool WriteInt16( size_t, const ON__INT16* );
  bool ReadInt16( size_t, ON__INT16* );

  // 32 bit integer IO
  bool WriteInt32( size_t, const ON__INT32* );
  bool ReadInt32( size_t, ON__INT32* );

  // 64 bit integer IO
  bool WriteInt64( size_t, const ON__INT64* );
  bool ReadInt64(  size_t, ON__INT64* );

  bool BeginWrite3dmTable( 
    unsigned int // tcode
    );
  bool EndWrite3dmTable( 
    unsigned int // tcode
    );
  bool BeginRead3dmTable( 
    unsigned int // tcode
    );
  bool EndRead3dmTable( 
    unsigned int // tcode
    );
  
  bool Read3dmV1Layer( ON_Layer*& );
  int  Read3dmV1Light(  // returns 0 at end of light table
                      //         1 light successfully read
                      //        -1 if file is corrupt
            ON_Light**, // light returned here
            ON_3dmObjectAttributes* // optional - if NOT nullptr, object attributes are
                                    //            returned here
            );
  int Read3dmV1Material( ON_Material** );
  int  Read3dmV1Object( // returns 0 at end of object table
                      //         1 if object is read
                      //         2 if object is skipped because it does not match filter
                      //        -1 if file is corrupt
          ON_Object**, // object returned here (nullptr if skipped)
          ON_3dmObjectAttributes*, // optional - if NOT nullptr, object attributes are
                                   //            returned here
          unsigned int = 0 // optional filter made by setting ON::object_type bits
          );  // returns nullptr at end of object table

  bool Read3dmV1AttributesOrMaterial( 
            ON_3dmObjectAttributes*,    // attributes,
            ON_Material*,      // material,
            bool&,             // bHaveMat
            unsigned int,      // end_mark_tcode 
            class ON__3dmV1_XDATA* = 0 // v1 "xdata"
            );
  bool Read3dmV1String( ON_String& );
  int  Read3dmV1LayerIndex( const char* ) const;

public:
  // helpers for reading V1 objects
  bool ReadV1_TCODE_RH_POINT(ON_Object**,ON_3dmObjectAttributes*);
  bool ReadV1_TCODE_MESH_OBJECT(ON_Object**,ON_3dmObjectAttributes*);
  bool ReadV1_TCODE_LEGACY_CRV(ON_Object**,ON_3dmObjectAttributes*);
  bool ReadV1_TCODE_LEGACY_FAC(ON_Object**,ON_3dmObjectAttributes*);
  bool ReadV1_TCODE_LEGACY_SHL(ON_Object**,ON_3dmObjectAttributes*);
  bool ReadV1_TCODE_RHINOIO_OBJECT_NURBS_CURVE(ON_Object**,ON_3dmObjectAttributes*);
  bool ReadV1_TCODE_RHINOIO_OBJECT_NURBS_SURFACE(ON_Object**,ON_3dmObjectAttributes*);
  bool ReadV1_TCODE_RHINOIO_OBJECT_BREP(ON_Object**,ON_3dmObjectAttributes*);
  bool ReadV1_TCODE_ANNOTATION(unsigned int,ON_Object**,ON_3dmObjectAttributes*);

private:
  void UpdateCRC( size_t, const void* );
  int ReadObjectHelper(ON_Object**);

  int m_3dm_version = 0; // 1,2,3,4,5 (obsolete 32-bit chunk sizes)
                         // 50,60,70,... (64-bit chunk sizes)

  int m_3dm_v1_layer_index = 0;
  int m_3dm_v1_material_index = 0;

  


protected:
  unsigned int ErrorMessageMask() const;
  /*
  Parameters:
    sizeof_request - [in] 
      value of count parameter passed to virtual Read() function.
    sizeof_read - [in]
      number of bytes actually read by the virtual Read() function.
  Returns:
    True if a call to Read() is permitted to ask for more bytes
    than are left in the file.  This value varies as the file
    is read and must be checked at each failure.
  */
  bool MaskReadError( ON__UINT64 sizeof_request, ON__UINT64 sizeof_read ) const;

private:


  // When a 3DM archive is read, m_3dm_opennurbs_version records the version of
  // OpenNURBS used to create the archive.  Otherwise, m_3dm_opennurbs_version
  // is zero.
  //
  // Read3dmProperties() sets this to the version of OpenNURBS that was
  // used to write file file.  If the file was created using a version
  // of OpenNURBS before 200012210, this number will be zero.
  //
  // Write3dmProperties() stores the value returned by ON::Version() in
  // the archive's properties table.
  friend void ON_SetBinaryArchiveOpenNURBSVersion(ON_BinaryArchive&,unsigned int);
  unsigned int m_3dm_opennurbs_version = 0;

  ON::RuntimeEnvironment m_archive_runtime_environment = ON::RuntimeEnvironment::Unset;

  // When a 3dm archive is saved from an MFC application that supports
  // Windows linking/embedding, the first 5kb to 1mb of the file contains
  // information that is put there by MFC.  m_3dm_start_section_offset
  // records the offset into the file where the 3dm archive actually begins.
  size_t m_3dm_start_section_offset = 0;

  /*Read3dmTableRecordBegin
  m_3dm_previous_table = 3dm archive table that was most recently read/written.
  m_3dm_active_table = 3dm archive table currently being read/written
  */
  ON_3dmArchiveTableType m_3dm_previous_table = ON_3dmArchiveTableType::Unset;
  ON_3dmArchiveTableType m_3dm_active_table = ON_3dmArchiveTableType::Unset;
  // If reading/writing a table fails, m_3dm_failed_table identifies the first failure.
  ON_3dmArchiveTableType m_3dm_first_failed_table = ON_3dmArchiveTableType::Unset;

  int m_user_data_depth = 0; // > 0 when user data is being read or written

  // 3dm archive status information
  class ON_3dmTableStatusLink* m_3dm_table_status_list = nullptr;

private:
  bool Internal_Write3dmUpdateManifest(
    const ON_ModelComponent& model_component
    );
  bool Internal_Write3dmLightOrGeometryUpdateManifest(
    ON_ModelComponent::Type component_type,
    ON_UUID component_id,
    int component_index,
    const ON_wString & component_name
    );
  bool Internal_Read3dmUpdateManifest(
    ON_ModelComponent& model_component
    );
  bool Internal_Read3dmLightOrGeometryUpdateManifest(
    ON_ModelComponent::Type component_type,
    ON_UUID component_id,
    int component_index,
    const ON_wString & component_name
    );

private:
  bool Internal_IncrementCurrentPosition(
    ON__UINT64 delta
  );
  bool Internal_DecrementCurrentPosition(
    ON__UINT64 delta
  );
  ON__UINT64 m_current_positionX = 0;

  /*
  Description:
    Increments m_crc_error_count and active table m_crc_error_count.
  */
  void Internal_ReportCRCError();
  
  unsigned int m_crc_error_count = 0; // number of chunks that have a bad crc
  
  /*
  Description:
    Increments m_critical_error_count and active table m_critical_error_count.
  */
  void Internal_ReportCriticalError();

  // Number of critical errors.  These errors are more serious than a CRC error.
  // If a critical error occurs, the information being read or written is 
  // so corrupted that chunk accounting is failing or the calling code is deeply flawed. 
  unsigned int m_critical_error_count = 0;

  // ON_BinaryArchive::eStorageDeviceError values are used to set
  // m_storage_device_error.
  // ON_BinaryArchive::StorageDeviceError() returns the value.
  unsigned int m_storage_device_error = 0;

  // The bits in m_error_message_mask are used to mask errors
  // when we know we are doing something that may generate an
  // error.
  //
  // bit 0x00000001
  //   Setting this bit masks an error when attempting to read 4 bytes
  //   at the end of a file.
  //   V1 files do not have a table structure and are read using
  //   multiple passes and there are valid situations where a 
  //   4 byte read is attempted at the end of a file.
  //   This situation also occurs when a damaged file is missing a table
  //   or contains tables in the wrong order and the table must be searched
  //   for by typecode.
  //
  // bit 0x00000002
  //   Some v1 files do not have an end mark.  When reading
  //   these v1 files bit 0x02 is set.
  //
  // bit 0x00000004
  //   Requested read may go beyond end of file.
  //   One situation where this happens is when a table is not at the 
  //   expected location in a file, 
  unsigned int m_error_message_mask = 0;


    
  ON__UINT64 m_3dm_end_mark_length = 0;
  
  bool Begin3dmTable(
    ON::archive_mode expected_mode,
    ON_3dmArchiveTableType table
    );
  bool End3dmTable(
    ON_3dmArchiveTableType table,
    bool bSuccess
    );
  void Internal_Increment3dmTableItemCount();
  bool Read3dmTableRecord(
    ON_3dmArchiveTableType table,
    void** ptr
    );
  bool Internal_Begin3dmTableRecord(
    ON_3dmArchiveTableType table
    );

public:
  /*
  Returns:
    Archive read/write mode
  */
  ON::archive_mode Mode() const;

  /*
  Returns:
    True if Mode() is an archive reading mode.
  */
  bool ReadMode() const;

  /*
  Returns:
    True if Mode() is an archive writing mode.
  */
  bool WriteMode() const;

  /*
  Returns:
    True if Mode() is not set to a valid read or write mode.
  */
  bool UnsetMode() const;

  /*
  Returns:
    If a 3dm archive is being read or written, the value of the archive 
    section (table) being read is returned.
    ON_3dmArchiveTableType::Unset is returned if a table is
    not actively being read or written.
  Remarks:
    Use ON_BinaryArchive::Mode() to determine if a binary archive is being
    read or written.
    Use ON_BinaryArchive::Previous3dmTable() to determine the most recent
    table that was successfully read and finished.
  */
  ON_3dmArchiveTableType Active3dmTable() const;

  static ON_ModelComponent::Type TableComponentType(
    ON_3dmArchiveTableType table_type
  );

  /*
  Returns:
    If a 3dm archive is being read or written, the value of the most
    recently read or written archive section (table) is returned.
  Remarks:
    Use ON_BinaryArchive::Mode() to determine if a binary archive is being
    read or written.
  */
  ON_3dmArchiveTableType Previous3dmTable() const;

  /*
  Returns:
    If a 3dm archive is being read or written and a failure occurs,
    the first archive section (table) that failed to read or write
    is returned.
  */
  ON_3dmArchiveTableType FirstFailed3dmTable() const;

  /*
  Returns:
    Number of chunks read with a bad CRC
  */
  unsigned int BadCRCCount() const;

  /*
  Returns:
    Number of critical errors
  */
  unsigned int CriticalErrorCount() const;

  const ON_3dmArchiveTableStatus Archive3dmTableStatus(
    ON_3dmArchiveTableType table_type
    );

private:

  ON_3dmArchiveTableType TableTypeFromTypecode( unsigned int ); // table type from tcode

  ON_SimpleArray<ON_3DM_BIG_CHUNK> m_chunk;

  // stack of chunks
  bool PushBigChunk( ON__UINT32 typecode, ON__INT64 value );

  bool WriteChunkTypecode( ON__UINT32 );
  bool ReadChunkTypecode( ON__UINT32* );
  bool WriteChunkValue( ON__UINT32 typecode, ON__INT64 );
  bool WriteChunkLength( ON__UINT64 );
  bool ReadChunkValue( ON__UINT32 typecode, ON__INT64* value64 );
  bool FindMisplacedTable( 
        ON__UINT64 filelength,
        const ON__UINT32 table_tocde,
        const ON__UINT32 table_record_record,
        const ON_UUID class_uuid,
        const ON__UINT64 min_length_data
        );

  bool ReadObjectUserDataAnonymousChunk(
          const ON__UINT64 length_TCODE_ANONYMOUS_CHUNK,
          const int archive_3dm_version,
          const unsigned int archive_opennurbs_version,
          class ON_UserData* ud );

public:
  size_t SizeofChunkLength() const;

private:
  bool WriteEOFSizeOfFile( ON__UINT64 );
  bool ReadEOFSizeOfFile( ON__UINT64* );

  bool m_bDoChunkCRC = false; // true if active chunk crc status should be checked
                      // and updated.
  bool m_bChunkBoundaryCheck = false;

public:
  /*
  Returns:
    true:
      All read, write, and seek operations check to make sure they stay within
      the current chunk boundary.
  */
  bool ChunkBoundaryCheck() const;

  /*
  Parameters:
    bChunkBoundaryCheck - [in]
      true:
        All read, write, and seek operations check to make sure they stay within
        the current chunk boundary.
  */
  void SetChunkBoundaryCheck(
    bool bChunkBoundaryCheck
  );

  
private:
  class ON_CompressorImplementation* m_compressor = nullptr;
  class ON_CompressorImplementation& Compressor();

  // returns number of bytes written
  size_t WriteDeflate(
        size_t,         // sizeof uncompressed input data
        const void*  // uncompressed input data
        );
  bool ReadInflate(
        size_t,  // sizeof uncompressed input data
        void* // buffer to hold uncompressed data
        );
  bool CompressionInit();
  void CompressionEnd();

private:
  // endian-ness of the cpu reading this file.
  // 3dm files are always saved with little endian byte order.
  const ON::endian m_endian = ON::Endian();

  const ON::archive_mode m_mode = ON::archive_mode::unset_archive_mode;

  // user data and user table reading and writing filter
  // If m_user_data_filter is empty, then all user data and user tables are read/written.
  // If m_user_data_filter is not empty, then the first element has both ids=nil, precedence=0,
  // and m_bSerialize = default setting. If there are any elements after the first element,
  // the must have m_application_id != nil and the value of m_bSerialize overrides the 
  // default setting.  If there are multiple elements with the same application and item id,
  // the most recently added element is used.
  ON_SimpleArray< ON_UserDataItemFilter > m_user_data_filter;
  
  /*
  Description:
    Sorts m_user_data_filter so items are ordered by 
    application id (nil is first) and precedence (low to high)
  */
  void SortUserDataFilter();

private:
  // 3dm write options

  // bits corresponded to ON::object_type flags.
  // If the bit is set, then the mesh will be saved in the 3dm file.
  // (RhinoCommon: if default is changed, sync with File3dmWriteOptions.RenderMeshesFlags)
  ON__UINT32 m_save_3dm_render_mesh_flags = 0xFFFFFFFFU;
  ON__UINT32 m_save_3dm_analysis_mesh_flags = 0xFFFFFFFFU;

  bool m_bSave3dmPreviewImage = true;

  bool m_bUseBufferCompression = true;

  bool m_bReservedA = false;
  bool m_bReservedB = false;
  bool m_bReservedC = false;
  bool m_bReservedD = false;
  bool m_bReservedE = false;
  bool m_bReservedF = false;

public:
  /*
  Description:
    Specify model serial number attributes to assign to ON_ModelComponent
    classes when they are read.
  */
  void SetModelSerialNumber(
    unsigned int model_serial_number,
    unsigned int reference_model_serial_number,
    unsigned int instance_definition_model_serial_number
    );

  /*
  Description:
    Clear() information set by SetModelSerialNumber() do not modify
    ON_ModelComponent model serial number information when the classes
    are read.
  */  
  void ClearModelSerialNumber();

  /*
  Parameters:
    bCheckForRemappedIds - [in]
      true if the archive is reading in a situation where component ids may get remapped.
  */
  void SetCheckForRemappedIds(
    bool bCheckForRemappedIds
  );

  /*
  Returns:
    True if the archive is reading in a situation where component ids may get remapped.
  */
  bool CheckForRemappedIds() const;

  unsigned int ModelSerialNumber() const;
  unsigned int ReferenceModelSerialNumber() const;
  unsigned int InstanceDefinitionModelSerialNumber() const;
  
  /*
  Description:
    Writes the attributes identified by the component_filter parameter.
  Parameters:
    model_component - [in]
    attributes_filter - [in]
      A bitfield that determines which attributes will be written.
  Returns:
    false: critical failure.
    true: writing can continue.
  */
  bool WriteModelComponentAttributes(
    const class ON_ModelComponent& model_component,
    unsigned int attributes_filter
    );

  /*
  Description:
    Reads the attributes the Write() function writes.
  Parameters:
    model_component - [in/out]
    component_filter - [out]
      A bitfield that reports which attributes were read.
      If the corresponding component on model_component is locked,
      the read value is discarded.
  Returns:
    false: critical failure.
    true: reading can continue.  
  Remarks:
    If locked attributes are read, thire values are ignored.
  */
  bool ReadModelComponentAttributes(
    ON_ModelComponent& model_component,
    unsigned int* attributes_filter
    );

  /*
  Description:
    When writing archives, the index of the component in the model is
    often different than the index of the component in the archive.
    WriteComponentIndex converts the model id or index into 
    an archive index and writes the archive index value.
  Remarks:
    During writing, the m_manifest member stores 
    the model id and index as the "Component" value and
    the 3dm archive id index as the "Manifest" value.
  */
  bool Write3dmReferencedComponentIndex(
    ON_ModelComponent::Type component_type,
    int model_component_index
    );

  /*
  Description:
    When writing archives, the index of the component in the model is
    often different than the index of the component in the archive.
    WriteComponentIndex converts the model id or index into 
    an archive index and writes the archive index value.
  Remarks:
    During writing, the m_manifest member stores 
    the model id and index as the "Component" value and
    the 3dm archive id index as the "Manifest" value.
  */
  bool Write3dmReferencedComponentIndex(
    ON_ModelComponent::Type component_type,
    ON_UUID model_component_id
    );

  /*
  Description:
    When writing archives, the index of the component in the model is
    often different than the index of the component in the archive.
    WriteComponentIndex converts the model id or index into 
    an archive index and writes the archive index value.
  Remarks:
    During writing, the m_manifest member stores 
    the model id and index as the "Component" value and
    the 3dm archive id index as the "Manifest" value.
  */
  bool Write3dmReferencedComponentIndex(
    const ON_ModelComponent& model_component
    );

  /*
  Description:
    When reading 3dm archives, model component indexes in the archive and
    in the destination model are typically different.
    This function basically reads and reverses the steps that WriteArchiveComponentIndex()
    uses to adjust and write a model component index.
  Parameters:
    component_type - [in]
      Type of the referenced component.
    component_index - [out]
      component reference index
  Returns:
    false - catestrophic read failure.
  */
  bool Read3dmReferencedComponentIndex(
    ON_ModelComponent::Type component_type,
    int* component_index
    );

  bool Read3dmReferencedComponentIndexArray(
    ON_ModelComponent::Type component_type,
    ON_SimpleArray<int>& component_index_array
    );

  /*
  Returns:
    True: (default state)
      Read3dmReferencedComponentIndex() and Write3dmReferencedComponentIndex() will automatically
      adjust components index references so they are valid.
    False: (uncommon)
      Read3dmReferencedComponentIndex() and Write3dmReferencedComponentIndex() will not
      adjust components index references so they are valid.
  */
  bool ReferencedComponentIndexMapping() const;

  /*
  Description:
    Set the archive's ReferencedComponentIndexMapping() state.
  Parameters:
    bEnableReferenceComponentIndexMapping - [in]
    True: (default state)
      Read3dmReferencedComponentIndex() and Write3dmReferencedComponentIndex() will automatically
      adjust components index references so they are valid.
    False: (uncommon)
      Read3dmReferencedComponentIndex() and Write3dmReferencedComponentIndex() will not
      adjust components index references so they are valid. This is only used with the
      component being read or written is not the model but is a copy of one
      in a different model (linked instance definitions being the common situation).
  */
  void SetReferencedComponentIndexMapping(
    bool bEnableReferenceComponentIndexMapping
    );

  /*
  Description:
    WriteComponentId converts the model ID into 
    an archive ID and writes the archive Id value.
    Generally, the ID of the component in the model is 
    identical to the ID of the component in the archive.
    In rare situations this is not the case.
  Remarks:
    During writing, the m_manifest member stores 
    the model ID as the "Component" value and
    the 3dm archive ID as the "Manifest" value.
  */
  bool Write3dmReferencedComponentId(
    ON_ModelComponent::Type component_type,
    ON_UUID model_component_id
    );

  bool Write3dmReferencedComponentId(
    const ON_ModelComponent& model_component
    );

  /*
  Description:
    When reading 3dm archives, the model component ID in the archive
    and in the destination model are often identical, but sometimes
    different. For example, the when the same template is used
    to create multiple models and files and the models from those files
    are merged into a single file, there will be ID collisions.
    For components that are identified by name, like layers and dimension styles,
    this is not a problem. For components like instance definitions that have
    a more complicated set of merging rules, it is critical that
    references to instance definition ids be updated from values in the archive
    to values in the model.
    uses to adjust and write a model component Id.
  Parameters:
    component_type - [in]
      Type of the referenced component.
    component_id - [out]
      component reference ID
  Returns:
    false - catestrophic read failure.
  */
  bool Read3dmReferencedComponentId(
    ON_ModelComponent::Type component_type,
    ON_UUID* component_id
    );

  /*
  Returns:
    True: (default state)
      Read3dmReferencedComponentId() and Write3dmReferencedComponentId() will automatically
      adjust components Id references so they are valid.
    False: (uncommon)
      Read3dmReferencedComponentId() and Write3dmReferencedComponentId() will not
      adjust components Id references so they are valid.
  */
  bool ReferencedComponentIdMapping() const;

  /*
  Description:
    Set the archive's ReferencedComponentIdMapping() state.
  Parameters:
    bEnableReferenceComponentIdMapping - [in]
    True: (default state)
      Read3dmReferencedComponentId() and Write3dmReferencedComponentId() will automatically
      adjust components Id references so they are valid.
    False: (uncommon)
      Read3dmReferencedComponentId() and Write3dmReferencedComponentId() will not
      adjust components Id references so they are valid. This is only used with the
      component being read or written is not the model but is a copy of one
      in a different model (linked instance definitions being the common situation).
  */
  void SetReferencedComponentIdMapping(
    bool bEnableReferenceComponentIdMapping
    );


public:
  // Reading and writing operations fill in the manifest.
  // ON_ComponentManifest query tools can be used to look up
  // model and archive index and id information.
  //
  // The component and manifest id values are always identical
  // during reading and writing.
  //
  // When writing, the component indices are model indices
  // and the manifest indices are the archive indices that
  // were written in the file.
  //
  // When reading, the component indices are "index" values read
  // from the archive and the manifest indices are the order they
  // were read. When files are valid, these indices are the same.
  //
  // After reading is complete, the application can use 
  // ON_ComponentManifest::UpdateManifestItem() to convert
  // the component index and id values to model index and
  // id values.
  const class ON_ComponentManifest& Manifest() const;
  const class ON_ManifestMap& ManifestMap() const;
  bool AddManifestMapItem(
    const class ON_ManifestMapItem& map_item
    );

  /*
  Description:
    When an application is reading an archive and changes the
    index or id of a model component as it is added to the model,
    then it needs to update the manifest map item destination settings.
  Parameters:
    map_item - [in]
      The source type, index and id match what was read from the 3dm archive.
      The destination index and id are the values assigned by the
      application reading the 3dm archive.
  */
  bool UpdateManifestMapItemDestination(
    const class ON_ManifestMapItem& map_item
    );

private:
  // Reading:
  //   m_manifest is a list of what has been read from the 3dm archive.
  //   m_manifest_map is a map from the 3dm archive index and id to the
  //   model index and id. The map is maintained by the application
  //   reading the file calling AddManifestMapItem() when read items
  //   are added to the model.
  // Writing:
  //   m_manifest is a list of what has been written to the 3dm archive.
  //   m_manifest_map maps model index and id to 3dm archive index and id.
  //   m_manifest_map is automatically maintained by the ON_BinaryArchive
  //   writing code because the index and id changes happen internally
  //   in 3dm archive writing functions.
  ON_ComponentManifest m_manifest;
  ON_ManifestMap m_manifest_map;

  // True: (default state)
  //  Read3dmReferencedComponentIndex() and Write3dmReferencedComponentIndex() will automatically
  //  adjust component index references so they are valid.
  // False: (uncommon)
  //  Read3dmReferencedComponentIndex() and Write3dmReferencedComponentIndex() will not
  //  adjust component index references so they are valid.
  bool m_bReferencedComponentIndexMapping = true;

  // True: (default state)
  //  Read3dmReferencedComponentId() and Write3dmReferencedComponentId() will automatically
  //  adjust component id references so they are valid.
  // False: (uncommon)
  //  Read3dmReferencedComponentId() and Write3dmReferencedComponentId() will not
  //  adjust component id references so they are valid.
  bool m_bReferencedComponentIdMapping = true;

private:
  // If the archive is a file system item (file), then
  // these strings specify the name of the file
  ON_wString m_archive_file_name;
  ON_wString m_archive_directory_name;
  ON_wString m_archive_full_path; // = archive_directory_name + path separator + archive_file_name

  // If the archive is being read, this is the name
  // of the file where it was written.
  // If false = ON_wString::EqualPath(m_archive_full_path,m_archive_saved_as_full_path),
  // then file has been moved or copied since it was saved.
  // When reading a file, this value is set by ON_BinaryArchive::Read3dmProperties()
  // When writing a file, this value is set by SetArchiveFullPath().
  ON_wString m_archive_saved_as_full_path;

  /*
    ON_BinaryArchive::Read3dmProperties() sets m_bArchiveMoved to true if
    the 3dm archive being read is not in the same file system location as where
    it was written.  This piece of information is useful when attempting to find
    referenced files that are not where they were when the 3dm archive was saved.
  */
  bool m_b3dmArchiveMoved = false;

public:
  const ON_wString& ArchiveFileName() const;
  const ON_wString& ArchiveDirectoryName() const;
  const ON_wString& ArchiveFullPath() const;
  const ON_wString& ArchiveSavedAsFullPath() const;

  const wchar_t* ArchiveFileNameAsPointer() const;
  const wchar_t* ArchiveDirectoryNameAsPointer() const;
  const wchar_t* ArchiveFullPathAsPointer() const;
  const wchar_t* ArchiveSavedAsFullPathPointer() const;

  /*
  Returns:
    true if the 3dm archive being read is not in the same file system 
    location as where is was saved.
  */
  bool ArchiveFileMoved() const;

  /*
  Parameters:
    archive_full_path - [in]
      full path to file being read or written
  */
  void SetArchiveFullPath(
    const wchar_t* archive_full_path
    );

  /*
  Parameters:
    archive_directory_name - [in]
      full path file being written
    archive_file_name - [in]
      name of file being written
  */
  void SetArchiveFullPath(
    const wchar_t* archive_directory_name,
    const wchar_t* archive_file_name
    );

private:
  bool m_SetModelComponentSerialNumbers = false;
  bool m_bCheckForRemappedIds = false;
  // Expert testers who need to create a corrupt 3dm file
  // call IntentionallyWriteCorrupt3dmStartSectionForExpertTesting() before writing
  // the 3dm file.
  unsigned char m_IntentionallyWriteCorrupt3dmStartSection = 0;
  bool m_reservedB = false;
  unsigned int m_model_serial_number = 0;
  unsigned int m_reference_model_serial_number = 0;
  unsigned int m_instance_definition_model_serial_number = 0;
  unsigned int m_reserved1 = 0;
  ON__UINT_PTR m_reserved2 = 0;

private:
  // ids of plug-ins that support saving older (V3) versions
  // of user data.  This information is filled in from the
  // list of plug-ins passed in whenteh settings are saved.
  ON_SimpleArray<ON_UUID> m_V3_plugin_id_list;

  struct ON__3dmV1LayerIndex* m_V1_layer_list = nullptr;

private:
  // m_archive_text_style_table and m_archive_dim_style_table are private and not used by inline functions.
  // No DLL interface is required.

  mutable ON_3dmAnnotationContext m_annotation_context;

#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 )
  // The m_archive_text_style_table[] array is used when reading archives.
  // It contains the text styles read from the archive
  ON_SimpleArray< ON_TextStyle* > m_archive_text_style_table;

  // The m_dim_style_index_text_style_index[] is used when reading archives.
  // ON_2dex.i = text style archive index.
  // ON_2dex.j = dimension style archive index.
  ON_SimpleArray< ON_2dex > m_text_style_to_dim_style_archive_index_map;

  // This m_archive_dim_style_table[] array is used when reading
  // and writing archives. This information is required when reading
  // and writing archives from previous versions.
  // - When writing, the dimstyles are copies of the model dimstyles
  //   and have model ids and indices.
  // - When reading, the dimstyles are copies of the archive dimstyles
  //   and have archive ids and indices.
  ON_SimpleArray< ON_DimStyle* > m_archive_dim_style_table;
  ON_SimpleArray< ON_DimStyle* > m_DELETE_ME_archive_dim_style_overrides;
  bool m_bLegacyOverrideDimStylesInArchive = false;

  const ON_DimStyle* m_archive_current_dim_style = nullptr;

  // m_archive_dim_style_table_status values:
  // READING:
  // 0 = not started
  //   1 = BeginWrite3dmDimStyle() has been called, 
  //       m_archive_text_style_table[] is valid, 
  //       and Read3dmDimStyle() can be called.
  //   2 = All entries of m_archive_text_style_table[] have been read by Read3dmDimStyle().
  //   3 = EndRead3dmDimStyle() has been called.
  // WRITING:
  //   0 = not started
  //   1 = BeginWrite3dmDimStyle() has been called and Write3dmDimStyle() can be called.
  //   2 = Write3dmDimStyle() has saved at least one dimstyle
  //   3 = EndWrite3dmDimStyle() has been called.
  unsigned int m_archive_dim_style_table_status = 0;

  // index in m_archive_text_style_table[] where Read3dmDimStyle() should
  // begin searching for the next dimstyle to "read".
  unsigned int m_archive_dim_style_table_read_index = ON_UNSET_UINT_INDEX;

#pragma ON_PRAGMA_WARNING_POP

public:
  /*
  Description:
    When reading version 5 and earlier files that contain a text style
    table, this function can be used to get the archive text style from
    the archive text style index. This function is used when reading
    V5 and pre August 2016 V6 ON_DimStyle information.
  */
  const ON_TextStyle* ArchiveTextStyleFromArchiveTextStyleIndex(
    int archive_text_style_index
  ) const;

private:
  ON_String m_archive_3dm_start_section_comment = ON_String::EmptyString;
  class ON_3dmProperties* m_archive_3dm_properties = nullptr;
  class ON_3dmSettings* m_archive_3dm_settings = nullptr;

private:
  // prohibit default construction, copy construction, and operator=
  ON_BinaryArchive() = delete;
  ON_BinaryArchive( const ON_BinaryArchive& ) = delete; // no implementation
  ON_BinaryArchive& operator=( const ON_BinaryArchive& ) = delete; // no implementation
};

class ON_CLASS ON_3dmGoo
{
  // used to store goo
public:
  ON_3dmGoo();
  ~ON_3dmGoo();
  ON_3dmGoo( const ON_3dmGoo& );
  ON_3dmGoo& operator=( const ON_3dmGoo& );

  void Dump(ON_TextLog&) const;

  unsigned int m_typecode;
  int m_value;
  unsigned char* m_goo;
  ON_3dmGoo* m_next_goo;
  ON_3dmGoo* m_prev_goo;
};


class ON_CLASS ON_BinaryFile : public ON_BinaryArchive
{
public:
  ON_BinaryFile( 
    ON::archive_mode archive_mode 
    );

  /*
  Description:
    Create an ON_BinaryArchive that reads/writes from an ordinary file.
  Parameters:
    archive_mode - [in]
    fp - [in]
      If a file is being read, fp is the pointer returned 
      from ON_FileStream::Open(...,"rb").
      If a file is being written, fp is the pointer returned 
      from ON_FileStream::Open(...,"wb").
  */
  ON_BinaryFile( 
    ON::archive_mode archive_mode, 
    FILE* fp
    );

  /*
  Description:
    Create an ON_BinaryArchive that reads/writes from an ordinary file.
  Parameters:
    archive_mode - [in]
    file_system_path - [in]
      path to file being read or written.
  */
  ON_BinaryFile(
    ON::archive_mode archive_mode, 
    const wchar_t* file_system_path
    );

  /*
  Description:
    Create an ON_BinaryArchive that reads/writes from an ordinary file.
  Parameters:
    archive_mode - [in]
    file_system_path - [in]
      path to file being read or written.
  */
  ON_BinaryFile(
    ON::archive_mode archive_mode, 
    const char* file_system_path
    );

  ~ON_BinaryFile();

protected:
  // ON_BinaryArchive overrides
  ON__UINT64 Internal_CurrentPositionOverride() const override;
  bool Internal_SeekFromCurrentPositionOverride(int byte_offset) override;
  bool Internal_SeekToStartOverride() override;

public:
  // ON_BinaryArchive overrides
  bool AtEnd() const override;

protected:
  // ON_BinaryArchive overrides
  size_t Internal_ReadOverride( size_t, void* ) override; // return actual number of bytes read (like fread())
  size_t Internal_WriteOverride( size_t, const void* ) override;
  bool Flush() override;

public:

  //// fseek from end (since the file has an end)
  //bool SeekFromEnd( int ); 

  //////////
  // To use custom memory buffering instead of relying
  // on fread()/fwrite()'s build in buffering, call
  // EnableMemoryBuffer() with the buffer size immediately
  // after constructing the ON_BinaryFile.  There appear
  // to be enough bugs in existing Windows NT/2000 NETWORK
  // I/O that using this hack will speed up I/O by factors
  // of 10 to 100.
  void EnableMemoryBuffer(
         int=16384 // capacity of memory buffer
         );

  /*
  Returns:
    True if a file stream is open (nullptr != m_fp).
  */
  bool FileIsOpen() const;

  void CloseFile();

private:
  // Implementation
  FILE* m_fp = nullptr;
  bool m_bCloseFileInDestructor = false;

  // if m_memory_buffer_capacity is zero, then Write() uses
  // fwrite() directly.  If m_memory_buffer_capacity is
  // greater than zero, then Write() buffers its results
  // into m_memory_buffer.  This is provided to work around
  // bugs in some networks that result in extremely slow
  // performance when seeking is used.
  size_t m_memory_buffer_capacity = 0;
  size_t m_memory_buffer_size = 0;
  size_t m_memory_buffer_ptr = 0;
  unsigned char* m_memory_buffer = nullptr;

private:
  // prohibit default construction, copy construction, and operator=
  ON_BinaryFile() = delete;
  ON_BinaryFile(const ON_BinaryFile&) = delete;
  ON_BinaryFile& operator=(const ON_BinaryFile&) = delete;
};

class ON_CLASS ON_BinaryArchiveBuffer : public ON_BinaryArchive
{
public:
  /*
  Description:
    Create an ON_BinaryArchive that reads/writes from an ON_Buffer.
  Parameters:
    mode - [in]
    buffer - [in]
  Remarks:
    If a non-null buffer is specified, then do not call SetBuffer()
  */
  ON_BinaryArchiveBuffer( ON::archive_mode, ON_Buffer* buffer );

  virtual ~ON_BinaryArchiveBuffer();

  /*
  Description:
    If the ON_BinaryArchiveBuffer class is created with the constructor
    that has a single "mode" parameter, then use SetBuffer()
    to specify the buffer to read/write from before using
    the ON_BinaryArchiveBuffer.
  Parameters:
    buffer - [in]
  Returns:
    True if the buffer is set.  Once the buffer is set it
    cannot be changed.
  */
  bool SetBuffer( ON_Buffer* buffer );

  /*
  Returns:
    Buffer being read/written. 
  */
  ON_Buffer* Buffer() const;

protected:
  // ON_BinaryArchive overrides
  ON__UINT64 Internal_CurrentPositionOverride() const override;
  bool Internal_SeekFromCurrentPositionOverride(int byte_offset) override;
  bool Internal_SeekToStartOverride() override;

public:
  // ON_BinaryArchive overrides
  bool AtEnd() const override;

protected:
  // ON_BinaryArchive overrides
  size_t Internal_ReadOverride( size_t, void* ) override; // return actual number of bytes read (like fread())
  size_t Internal_WriteOverride( size_t, const void* ) override;
  bool Flush() override;

private:
  // Buffer being read/written.
  ON_Buffer* m_buffer;

private:
  // prohibit use - you should specify a buffer.
  ON_BinaryArchiveBuffer( ON::archive_mode );
private:
  // prohibit default construction, copy construction, and operator=
  ON_BinaryArchiveBuffer( ); // no implementation
  ON_BinaryArchiveBuffer( const ON_BinaryArchiveBuffer& ); // no implementation
  ON_BinaryArchiveBuffer& operator=( const ON_BinaryArchiveBuffer& ); // no implementation
};


class ON_CLASS ON_Read3dmBufferArchive : public ON_BinaryArchive
{
public:

  /*
  Description:
    Construct an ON_BinaryArchive for reading information from a memory buffer.
  Parameters:
    sizeof_buffer - [in] size of buffer in bytes (>0)
    buffer - [in] memory buffer containing binary archive
    bCopyBuffer - [in]
      true - copy the input buffer.  
          Useful when the buffer may be destroyed while this class is still in use.
      false - Do not copy the input buffer.  
          In this case you are responsible for making certain the input buffer 
          is valid while this class is in use.
    archive_3dm_version  - [in] (1,2,3,4,5,50,60,70,...)
    archive_opennurbs_version - [in] 
  */
  ON_Read3dmBufferArchive( 
    size_t sizeof_buffer, 
    const void* buffer,
    bool bCopyBuffer,
    int archive_3dm_version,
    unsigned int archive_opennurbs_version
    );

  ~ON_Read3dmBufferArchive();

  /*
  Returns: 
     value of m_sizeof_buffer
  */
  size_t SizeOfBuffer() const;

  /*
  Returns: 
     value of m_buffer
  */
  const void* Buffer() const;

protected:
  // ON_BinaryArchive overrides
  ON__UINT64 Internal_CurrentPositionOverride() const override;
  bool Internal_SeekFromCurrentPositionOverride(int byte_offset) override;
  bool Internal_SeekToStartOverride() override;

public:
  // ON_BinaryArchive overrides
  bool AtEnd() const override;

protected:
  // ON_BinaryArchive overrides
  size_t Internal_ReadOverride( size_t, void* ) override; // return actual number of bytes read (like fread())
  size_t Internal_WriteOverride( size_t, const void* ) override;
  bool Flush() override;

private:
  void* m_p;
  const unsigned char* m_buffer;
  size_t m_sizeof_buffer;
  size_t m_buffer_position;
  ON__INT_PTR m_reserved1;
  ON__INT_PTR m_reserved2;
  ON__INT_PTR m_reserved3;
  ON__INT_PTR m_reserved4;

private:
  // prohibit use - no implementation
  ON_Read3dmBufferArchive(); 
  ON_Read3dmBufferArchive( const ON_Read3dmBufferArchive& );
  ON_Read3dmBufferArchive& operator=(const ON_Read3dmBufferArchive&);
};

class ON_CLASS ON_Write3dmBufferArchive : public ON_BinaryArchive
{
public:

  /*
  Description:
    Construct an ON_BinaryArchive for writing information to a memory buffer.
  Parameters:
    initial_sizeof_buffer - [in] 
      initial size of buffer in bytes (>=0)
      If you are unable to estimate the size you will need, pass in zero.
    max_sizeof_buffer - [in] 
      maximum size of buffer in bytes (>=0)
      If max_sizeof_buffer > 0 and the amount of information saved 
      requires a buffer larger than this size, then writing fails. 
      If max_sizeof_buffer <= 0, then no buffer size limits are enforced.
    archive_3dm_version  - [in] (0, ,2,3,4,5,50,60,70,...)
      Pass 0 or ON_BinaryArchive::CurrentArchiveVersion() to write the
      version of opennurbs archives used by lastest version of Rhino.
    archive_opennurbs_version - [in]
  */
  ON_Write3dmBufferArchive( 
    size_t initial_sizeof_buffer, 
    size_t max_sizeof_buffer, 
    int archive_3dm_version,
    unsigned int archive_opennurbs_version
    );

  ~ON_Write3dmBufferArchive();

  /*
  Returns: 
     Size of the archive in bytes.
  */
  size_t SizeOfArchive() const;

  /*
  Returns: 
     value of m_sizeof_buffer
  */
  size_t SizeOfBuffer() const;

  /*
  Returns: 
     value of m_buffer.
     SizeOfArchive() reports the number of bytes
     written to this buffer.
     SizeOfBuffer() reports the number of bytes
     allocated in this buffer.
     
  */
  const void* Buffer() const;

  /*
  Returns:
    The pointer to the buffer and sets all 
    members on this archive back to zero.
    The caller is responsible for calling onfree() on
    the pointer when finished with the buffer.
  */
  void* HarvestBuffer();

protected:
  // ON_BinaryArchive overrides
  ON__UINT64 Internal_CurrentPositionOverride() const override;
  bool Internal_SeekFromCurrentPositionOverride(int byte_offset) override;
  bool Internal_SeekToStartOverride() override;

public:
  // ON_BinaryArchive overrides
  bool AtEnd() const override;

protected:
  // ON_BinaryArchive overrides
  size_t Internal_ReadOverride( size_t, void* ) override; // return actual number of bytes read (like fread())
  size_t Internal_WriteOverride( size_t, const void* ) override;
  bool Flush() override;

private:
  void AllocBuffer(size_t);
  void* m_p;
  unsigned char* m_buffer;
  size_t m_sizeof_buffer;
  const size_t m_max_sizeof_buffer;
  size_t m_sizeof_archive;
  size_t m_buffer_position;
  ON__INT_PTR m_reserved1;
  ON__INT_PTR m_reserved2;
  ON__INT_PTR m_reserved3;
  ON__INT_PTR m_reserved4;

private:
  // prohibit use - no implementation
  ON_Write3dmBufferArchive(); 
  ON_Write3dmBufferArchive( const ON_Write3dmBufferArchive& );
  ON_Write3dmBufferArchive& operator=(const ON_Write3dmBufferArchive&);
};

/*
Description:
  Create a simple archive that contains a single or multiple  geometric object(s).
Parameters:
  archive - [in] destination archive.
  version - [in] (0, 2, 3, 4,50,60,70,...) format version.archive version number.
      Version 2 format can be read by Rhino 2 and Rhino 3.  Version
      3 format can be read by Rhino 3.
      Pass 0 or ON_BinaryArchive::CurrentArchiveVersion() to write
      the latest version of archives supported by Rhino.
  object - [in] object to be saved in the archive's object table.
      This is typically some type of ON_Curve, ON_Surface, ON_Mesh,
      or ON_Brep.
	object_list - [in] objects to be saved in the archive's object table.
      These are typically some type of ON_Curve, ON_Surface, ON_Mesh,
      or ON_Brep.
	object_list_count - [in] explicit count of number of objects in object_list.
Returns:
  @untitled table
  true     archive successfully written.
  false    archive not successfully written.
Example:

          const char* filename = "myfile.3dm";
          FILE* fp = ON::OpenFile( filename, "wb" );
          ON_BinaryFile file( fp, ON::archive_mode::write3dm );
          bool ok = ON_WriteArchive( archive, geometry );
          ON::CloseFile( fp );

Remarks:
  For ON_WriteOneObjectArchive the  object table in the archive will contain a single
  object.
*/
ON_DECL
bool ON_WriteOneObjectArchive( 
  ON_BinaryArchive& archive,
  int version,
  const ON_Object& object
  );

ON_DECL
bool ON_WriteOneObjectArchive( 
  const wchar_t* filename,
  const ON_Object& object
  );

ON_DECL
bool ON_WriteMultipleObjectArchive( 
  ON_BinaryArchive& archive,
  int version,
  const ON_SimpleArray<const ON_Object* >& object_list
  );

ON_DECL
bool ON_WriteMultipleObjectArchive( 
  ON_BinaryArchive& archive,
  int version,
  size_t object_list_count,
  const ON_Object* const* object_list
  );

bool ON_WriteMultipleObjectArchive( 
  const wchar_t* filename,
  int version,
  size_t object_list_count,
  const ON_Object* const* object_list
  );


/*
Opens a debug archive file 
	Uses directory set by ON_SetDebugWriteObjectDirectory(const wchar_t* ).
	creates a file named "debug_file_nnnn.3dm"
Example:
	ON_DebugWriteArchive debug;
	if(debug.m_Archive)
		 ON_WriteArchive( *debug.m_Archive, geometry );

*/
class ON_CLASS ON_DebugWriteArchive
{
public:
  /*
    Creates a file in N_DebugWriteObjectDirectory() and allocates archive to write to
    that file.
  */
  ON_DebugWriteArchive();
	~ON_DebugWriteArchive();

  // check for nullptr before using
  // Destructor closes archive and deletes it.

  ON_BinaryArchive* Archive() const;

  // Name of the archive file.
  // = .../debug_file_NNNNN.3dm where N = Number().
  const ON_wString& FilePath() const;

  // the number of the archive or 0 
  unsigned int Number() const;

private:
  ON_BinaryArchive* m_archive = nullptr; 
	FILE* m_fp = nullptr;
  unsigned int m_N = 0;
  ON_wString m_file_path;

private:
  ON_DebugWriteArchive(const ON_DebugWriteArchive&) = delete;
  ON_DebugWriteArchive& operator=(const ON_DebugWriteArchive&) = delete;
};

#endif
