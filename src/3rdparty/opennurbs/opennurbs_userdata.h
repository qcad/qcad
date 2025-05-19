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

#if !defined(OPENNURBS_USERDATA_INC_)
#define OPENNURBS_USERDATA_INC_

class ON_CLASS ON_UserData : public ON_Object
{
  ON_OBJECT_DECLARE(ON_UserData);
public:
  ON_UserData();
  ON_UserData(const ON_UserData&);
  ON_UserData& operator=(const ON_UserData&);

  //////////
  // The destructor automatically removes the user data
  // from ON_Object::m_userdata_list.
  ~ON_UserData();

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  /*
  Description:
    Overrides virtual ON_Object::Dump().
    Prints class name, description, and uuid.
  Parameters:
    text_log - [in] Information is sent to this text log.
  Remarks:
  */
  void Dump( ON_TextLog& text_log ) const override;

  /*
  Description:
    Overrides virtual ON_Object::SizeOf().
  Returns:
    Approximate number of bytes this class uses.
  */
  unsigned int SizeOf() const override;

  ////////
  // Returns object that owns the user data
  ON_Object* Owner() const;

  ////////
  // Used for traversing list of user data attached
  // to an object.
  ON_UserData* Next() const;

  ////////
  // Returns the class id which is not necessarily the 
  // same as m_userdata_uuid.
  ON_UUID UserDataClassUuid() const; 

  //////////
  // Returns true if the user data is anonymous.  This happens
  // when the user data class is not defined at the time the
  // user data is read from an archive.  For example, if a class
  // derived from ON_UserData is defined in application A
  // but is not defined in application B, then the class can be
  // defined when an archive is written by A but not exist when
  // an archive is read by B.  In this case, the
  // user data is not lost, it is just read as ON_UnknownUserData
  // by application B.  If application B saves the parent
  // object in an archive, the unknown user data is resaved in
  // a form that can be read by application A.
  bool IsUnknownUserData() const;

  /*
  Parameters:
    description - [out] description of user data shown in 
                        object properties dump.
  Returns:
    True if user data class is ready.
  */
  virtual 
  bool GetDescription( ON_wString& description );

  /*
  Description:
    If Archive() returns true, m_application_uuid is not nil, 
    and the virtual Read() and Write() are functions are overridden,
    then this user data will be written to and read from 3dm archives.

  Returns:
    true if user data should be saved in binary archives.
    false if the user data should not be saved in binary archives.

  Remarks:
    The default implementation returns false.  If you override
    ON_UserData::Archive so that it returns true, then your 
    constructor must set m_application_uuid, you must override
    the virtual ON_Object::Read and ON_Object::Write functions and
    you must CAREFULLY TEST your code.

    ON_UserData requires expert programming and testing skills.

    If you need to know more details about the archive or 
    parent object to determine if the userdata should be saved,
    then override WriteToArchive().

    YOU SHOULD READ AND UNDERSTAND EVERY COMMENT IN THIS 
    HEADER FILE IN BEFORE ATTEMPTING TO USE ON_UserData.
  */
  virtual 
  bool Archive() const; 

  /*
  Description:
    If WriteToArchive() returns true, m_application_uuid is not nil, 
    and the virtual Read() and Write() are functions are overridden,
    then this user data will be written to and read from the 
    identified archive.
    
  Parameters:
    archive - [in]
      The archive being written to. Typically, you will test
      archive.Archive3dmVersion() to determine if your userdata
      should be saved.
    parent_object - [in]
      The object managing this userdata.
  Returns:
    true if user data should be saved in the binary archives.
    false if the user data should not be saved in binary archives.

  Remarks:
    The default implementation calls the legacy Archive() function.
  */
  virtual
  bool WriteToArchive(
    const class ON_BinaryArchive& archive,
    const class ON_Object* parent_object
    ) const;

  /*
  Description:
    DeleteAfterWrite() is used when opennurbs is writing earlier 
    versions of 3dm archives that used some type of user data that
    has since become obsolete.

  Parameters:
    archive - [in]
      archive that will be written to.  
      If needed, you can inspect the version of 3dm archive this
      is being saved and other information that you may need to 
      determine the appropriate return value.
    parent_object - [in]
      If needed, you can inspect the parent object to determine 
      the appropriate return value.

  Returns:
    True if the user data should be written the next
    time the parent object is saved to a 3dm archive and
    then deleted.

  Remarks:
    Typically, DeleteAfterWrite() is used in the situation where
    1) User data was used to add information to an opennurbs class
    whose data fields could not be modified because the SDK
    was fixed at the time.
    2) Once the class data fields could be modified, the new data
    fields were added to the class and the user data from step 1
    became obsolete.
    3) The class's Write function is called and the value of
    ON_BinaryArchive::Archive3dmVersion() corresponds to
    the version of the 3dm archive that was being saved in
    step 1. The write function fills in and attaches the obsolete
    user data to the class.  When ON_BinaryArchive::WriteObject()
    writes the obsolete user data to the earlier version file,
    it then deletes it.
  */
  virtual
  bool DeleteAfterWrite(
    const class ON_BinaryArchive& archive,
    const class ON_Object* parent_object
    ) const;

  /*
  Description:
    DeleteAfterRead() is used when opennurbs is reading earlier
    versions of 3dm archives that used some type of user data that
    has since become obsolete.

  Parameters:
    archive - [in]
      archive that was read from.
      If needed, you can inspect the version of 3dm archive this
      is being saved and other information that you may need to
      determine the appropriate return value.
    parent_object - [in]
      If needed, you can inspect the parent object to determine
      the appropriate return value.

  Returns:
    True if the user data should be deleted because the 
    information it contains has been added to the parent
    object using the methods that are current.
  */
  virtual
  bool DeleteAfterRead( 
    const class ON_BinaryArchive& archive,
    class ON_Object* parent_object
    ) const;

  /*
  Description:
    If Transform() return false, then the userdata is destroyed when 
    its parent object is transformed.  The default Transform() 
    updates m_userdata_xform and returns true. 
    Carefully read the comments above m_userdata_xform
  */
  virtual 
  bool Transform( const ON_Xform& ); 

  /*
  Description:
    This uuid is the value that must be passed to 
    ON_Object::GetUserData() to retrieve 
    this piece of user data.
  */
  ON_UUID m_userdata_uuid;

  /*
  Description:
    This uuid is used to identify the application that
    created this piece of user data.  In the case of
    Rhino, this is the id of the plug-in that created
    the user data. User data with a nil application id
    will not be saved in 3dm archives.
  */
  ON_UUID m_application_uuid;

  ////////
  // If m_userdata_copycount is 0, user data is not copied when 
  // object is copied.  If > 0, user data is copied and m_copycount
  // is incremented when parent object is copied. The user data's 
  // operator=() is used to copy.  
  // The default ON_UserData::ON_UserData() constructor sets 
  // m_userdata_copycount to zero.
  unsigned int m_userdata_copycount;  

  ////////
  // Updated if user data is attached to a piece of geometry that is
  // transformed and the virtual ON_UserData::Transform() is not 
  // overridden.  If you override ON_UserData::Transform() and want
  // m_userdata_xform to be updated, then call the 
  // ON_UserData::Transform() in your override.
  // The default constructor sets m_userdata_xform to the identity.
  ON_Xform m_userdata_xform; 

private: // don't look and don't touch - these may change
  friend class ON_Object;
  friend int ON_BinaryArchive::ReadObject( ON_Object** );
  friend bool ON_BinaryArchive::WriteObject( const ON_Object& );
  friend bool ON_BinaryArchive::ReadObjectUserData( ON_Object& );
  friend bool ON_BinaryArchive::WriteObjectUserData( const ON_Object& );
  ON_Object* m_userdata_owner; 
  ON_UserData* m_userdata_next;
};

class ON_CLASS ON_UnknownUserData : public ON_UserData
{
  ON_OBJECT_DECLARE(ON_UnknownUserData);
  // used to hold user data when the application class is not loaded
  // at time data is read
public:
  ON_UnknownUserData();
  ON_UnknownUserData(const ON_UnknownUserData&);
  ~ON_UnknownUserData();
  ON_UnknownUserData& operator=(const ON_UnknownUserData&);

  // ON_Object overrides

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
  void Dump( ON_TextLog& ) const override;
  bool Write( ON_BinaryArchive& ) const override;
  bool Read( ON_BinaryArchive& ) override;

  unsigned int SizeOf() const override; // return amount of memory used by user data
  bool GetDescription( ON_wString& ) override; // description of user data
  bool Archive() const override; 

  // Convert unknown user data to actual user data.  Useful if
  // definition of actual user data is dynamically linked after
  // archive containing user data is read.
  ON_UserData* Convert() const;

  /*
  Description:
    This is the uuid of the missing class.  This uuid
    is the 3rd parameter to the ON_OBJECT_IMPLEMENT()
    macro of the missing class.
  */
  ON_UUID m_unknownclass_uuid;
  int m_sizeof_buffer;
  void* m_buffer;

  // These version numbers are set when unknown user data is read
  // from a file record the version of the 3dm archive and the 
  // version of opennurbs that were used when the plug-in wrote
  // the user data.
  //   This information was added in to V5 opennurbs 200910190.
  // For files written with earlier versions of opennurbs, these
  // values are set from the archive containing the user data. 
  // The purpose of this version information is to have it accompany
  // unknown user data so that if is is eventually read by the plug-in
  // an ON_BinaryArchive with correct version information can be
  // passed to the plug-in's reading code.  In archives, these values
  // are stored in the TCODE_USER_TABLE_RECORD_HEADER chunk.
  int m_3dm_version; // 3dm archive version (0,1,2,3,4,5,50,...)
  

  // In V5 and earlier, m_3dm_opennurbs_version had the format YYYYMMDDN
  // For V6 the unsigned int value is calculated by ON_VersionNumberConstruct()
  // and has the high bit set (it will be negative if used as a signed int).
  // When writing files in previous version formats (V5 or earlier) it is important
  // to write a YYYYMMDDN version number in the file.  Use ON_VersionNumberParse()
  // get the YYYY, MM, DD and N values from m_3dm_opennurbs_version.
  unsigned int m_3dm_opennurbs_version_number;
};

class ON_CLASS ON_ObsoleteUserData : public ON_UserData
{
  ON_OBJECT_DECLARE(ON_ObsoleteUserData);
  // used to write obsolete user data when earlier versions
  // of 3dm archives are written and the class id for the
  // earlier version of the user data is still in use
  // in the current version of opennurbs.
public:
  ON_ObsoleteUserData();
  virtual ~ON_ObsoleteUserData();
  ON_ObsoleteUserData(const ON_ObsoleteUserData&);
  ON_ObsoleteUserData& operator=(const ON_ObsoleteUserData&);

  // This is the user data class id that will be saved in the 3dm archive.
  ON_UUID m_archive_class_uuid;
};

// Do not export this class
// It is used internally to read and write 3dm archives with versions < 60.
class ON_RdkMaterialInstanceIdObsoleteUserData : public ON_ObsoleteUserData
{
  // NO ON_OBJECT_DECLARE() for classes derived from ON_ObsoleteUserData
private:
  static const ON_UUID m_archive_class_id_ctor;
  static const ON_UUID m_archive_userdata_uuid_ctor;
  static const ON_UUID m_archive_application_uuid_ctor;
  static const unsigned int m_userdata_copycount_ctor;
  static const ON_Xform m_userdata_xform_ctor;

public:
  static bool IsRdkMaterialInstanceIdUserData(
    ON_UUID class_id,
    ON_UUID userdata_id,
    ON_UUID app_id,
    ON_Object* object
    );

  ON_RdkMaterialInstanceIdObsoleteUserData();
  virtual ~ON_RdkMaterialInstanceIdObsoleteUserData();
  ON_RdkMaterialInstanceIdObsoleteUserData(const ON_RdkMaterialInstanceIdObsoleteUserData&);
  ON_RdkMaterialInstanceIdObsoleteUserData& operator=(const ON_RdkMaterialInstanceIdObsoleteUserData&);

  // virtual ON_Object override
  bool Read(
    ON_BinaryArchive&
    ) override;

  // virtual ON_Object override
  bool Write(
    ON_BinaryArchive&
    ) const override;

  // virtual ON_UserData override
  bool GetDescription(ON_wString& description) override;

  // virtual ON_UserData override
  bool WriteToArchive(
    const class ON_BinaryArchive& archive,
    const class ON_Object* parent_object
    ) const override;

  // virtual ON_UserData override
  bool DeleteAfterWrite(
    const ON_BinaryArchive& archive,
    const ON_Object* parent_object
    ) const override;

  // virtual ON_UserData override
  bool DeleteAfterRead(
    const ON_BinaryArchive& archive,
    ON_Object* parent_object
    ) const override;

  ON_UUID m_rdk_material_instance_id;
};

class ON_CLASS ON_UserStringList : public ON_UserData
{
  ON_OBJECT_DECLARE(ON_UserStringList);
public:

  ON_UserStringList();
  ~ON_UserStringList();

  static ON_UserStringList* FromObject(
    const ON_Object*
    );

  // override virtual ON_Object::Dump function
  void Dump( ON_TextLog& text_log ) const override;

  // override virtual ON_Object::SizeOf function
  unsigned int SizeOf() const override;

  // override virtual ON_Object::DataCRC function
  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const override;

  // override virtual ON_Object::Write function
  bool Write(ON_BinaryArchive& binary_archive) const override;

  // override virtual ON_Object::Read function
  bool Read(ON_BinaryArchive& binary_archive) override;

  // override virtual ON_UserData::GetDescription function
  bool GetDescription( ON_wString& description ) override;

  // override virtual ON_UserData::Archive function
  bool Archive() const override; 

  /*
  Description:
    Add, replace or remove a user string.
  Parameters:
    key - [in]
      must be a non-empty string.  If an entry with the same key
      (case insensitive compares are used) exists, the existing
      entry is updated.
    string_value - [in]
      If string_value is empty and an entry with a matching key
      exists, the entry is deleted.
  Returns:
    True if the key is valid.
  */
  bool SetUserString( const wchar_t* key, const wchar_t* string_value );

  bool GetUserString( const wchar_t* key, ON_wString& string_value ) const;

  /*
  Description:
    Append entries to the user string list
  Parameters:
    count - [in]
      number of element in us[] array
    us - [in]
      entries to append.
    bReplace - [in]
      If bReplace is true, then existing entries with the same key are
      updated with the new entry's value.  If bReplace is false, then
      existing entries are not updated.
  Returns:
    Number of entries added, deleted, or modified.
  */
  int SetUserStrings( int count, const ON_UserString* us, bool bReplace );

  ON_ClassArray<ON_UserString> m_e;
};

class ON_CLASS ON_UserDataHolder : public ON_Object
{
public:

  /*
  Description:
    Transfers the user data from source_object to "this".
    When MoveUserDataFrom() returns source_object will not 
    have any user data.  If "this" had user data when 
    MoveUserDataFrom() was called, then that user data is
    destroyed.
  Parameters:
    source_object - [in] The "const" is a lie.  It is
      there because, in practice the source object is frequently
      const and const_cast ends up being excessively used.
  Returns:
    Number of user data items that were moved from source_object to "this" ON_UserDataHolder.
  */
  unsigned int MoveUserDataFrom(
    const ON_Object& source_object
    );


  /*
  Description:
    Copies the data from source_object with copy_count > 0 to "this" ON_UserDataHolder.
  Parameters:
    source_object - [in]
      This object and it's user data are not modified.
    user_data_item_id - [in]
      If not nil, then only userdata with this item id will be coped
  Returns:
    Number of user data items that were copied from source_object to "this" ON_UserDataHolder.
  */
   unsigned int CopyUserDataFrom(
    const ON_Object& source_object,
    ON_UUID user_data_item_id
    );

  /*
  Description:
    Moves the user data on "this" ON_UserDataHolder to destination_object.
    When MoveUserDataTo() returns "this" ON_UserDataHolder will not have any user data.
  Parameters:
    destination_object - [in] The "const" is a lie.  It is
      there because, in practice the source object is generally
      const and const_cast ends up being constantly used.
    bAppend - [in]
      true:
        Existing user data on destination_object is left unchanged.
        MoveUserDataTo( destination_object, true ) is identical to calling
        MoveUserDataTo( destination_object, ON_Object::UserDataConflictResolution::destination_object).
      false:
        Existing user data on destination_object is destroyed.
  Returns:
    Number of user data items moved from "this" ON_UserDataHolder to destination_object.
  */
  unsigned int MoveUserDataTo(
    const ON_Object& destination_object,
    bool bAppend 
    );

  /*
  Description:
    Moves the user data on "this" ON_UserDataHolder to destination_object.
    When MoveUserDataTo() returns "this" ON_UserDataHolder will not have any user data.
  Parameters:
    destination_object - [in]
      The "const" is a lie.  It is there because, in practice the source object is generally
      const and const_cast ends up being constantly used.
    user_data_item_id - [in]
      If not nil, then only user data items with this id will be considered for moving.
    userdata_conflict_resolution - [in]
      If destination_object and "this" ON_UserDataHolder have the same
      type of user data item, then userdata_conflict_resolution
      is used to determine if that destination_object user data item
      is replaced with the one on "this" ON_UserDataHolder.
  Returns:
    Number of user data items moved from "this" ON_UserDataHolder to destination_object.
  */
  unsigned int MoveUserDataTo(
    const ON_Object& destination_object,
    ON_UUID user_data_item_id,
    ON_Object::UserDataConflictResolution userdata_conflict_resolution
    );


  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
};

/*
Description:
  An ON_DocumentUserStringList object is saved in the list of user
  tables.  The Rhino SetDocumentText and GetDocumentText
  commands use the ON_Object SetUserString, GetUserString,
  GetUserStrings, GetUserStringKeys functions on an 
  ON_DocumentUserStringList class to manage the tag-value pairs of 
  strings.
*/
class ON_CLASS ON_DocumentUserStringList : public ON_Object
{
  ON_OBJECT_DECLARE(ON_DocumentUserStringList);
public:
  ON_DocumentUserStringList();
  ~ON_DocumentUserStringList();

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
  void Dump( ON_TextLog& ) const override;
  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const override;
  bool Write(ON_BinaryArchive& binary_archive) const override;
  bool Read(ON_BinaryArchive& binary_archive) override;

  // Use the
  //   ON_Object::SetUserString()
  //   ON_Object::GetUserString()
  //   ON_Object::GetUserStrings()
  //   ON_Object::GetUserStringKeys()
  //   ON_Object::UserStringCount()
  // functions to access and modify user string information.
};

#endif
