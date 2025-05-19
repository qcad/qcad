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

#if !defined(ON_EMBEDDED_FILE_INC_)
#define ON_EMBEDDED_FILE_INC_

class ON_CLASS ON_EmbeddedFile : public ON_ModelComponent
{
  ON_OBJECT_DECLARE(ON_EmbeddedFile);

public:
  ON_EmbeddedFile();
  ON_EmbeddedFile(const ON_EmbeddedFile&);
  virtual ~ON_EmbeddedFile();

  virtual const ON_EmbeddedFile& operator = (const ON_EmbeddedFile&);

  // Returns the fully-qualified filename of the embedded file. This filename may or may not refer to a
  // local file depending on the way the embedded file was loaded. For example, if it was loaded from an
  // archive, the filename could be that of a file on a different computer.
  virtual ON_wString Filename(void) const;

  // Sets the fully-qualified filename of the embedded file. This can be used to set a filename initially
  // when none has been loaded, or to change the filename prior to saving to an archive.
  virtual void SetFilename(const wchar_t* filename);

  // Loads the embedded file from a local file. This also sets the filename. Returns true if successful, else false.
  virtual bool LoadFromFile(const wchar_t* filename);

  // Saves the embedded file to a local file. The embedded file must have been loaded by a call to
  // one of either LoadFromFile(), LoadFromBuffer() or Read() prior to calling this method.
  // Returns true if successful, else false.
  virtual bool SaveToFile(const wchar_t* filename) const;

  // Loads the embedded file from a buffer. This does not set the filename; it merely loads the contents
  // of the buffer into the embedded file object. If you intend to call Write() after this, you may need
  // to call SetFilename() first. Returns true if successful, else false.
  virtual bool LoadFromBuffer(ON_Buffer& buf);

  // Saves the embedded file to a buffer. The embedded file must have been loaded by a call to
  // one of either LoadFromFile(), LoadFromBuffer() or Read() prior to calling this method.
  // This does not save the filename to the buffer, it only saves the file contents.
  // Returns true if successful, else false.
  virtual bool SaveToBuffer(ON_Buffer& buf) const;

  // Reads an embedded file from an archive. The archive must be positioned at the start of suitable data
  // as created by the Write() method. It first loads the filename from the archive and then loads the file
  // contents. This method is an expert user tool. Incorrect use will have undefined results.
  // Returns true if successful, else false.
  virtual bool Read(ON_BinaryArchive& archive) override;

  // Writes the embedded file to an archive. The embedded file must have been loaded by a call to
  // one of either LoadFromFile(), LoadFromBuffer() or Read() prior to calling this method.
  // This writes both the filename and the file contents to the archive.
  // Returns true if successful, else false.
  virtual bool Write(ON_BinaryArchive& archive) const override;

  // Returns the length of the loaded data. If the object is not loaded, this method returns zero.
  virtual size_t Length(void) const;

  // Returns the compressed length of the data loaded by Read(). If the object is not loaded or was
  // loaded by LoadFromFile() or LoadFromBuffer(), this method returns zero.
  virtual size_t CompressedLength(void) const;

  // Returns true if the embedded file was loaded, but the load failed. This should only happen
  // if a buffer or archive being loaded is corrupted.
  bool Error(void) const;

  // Clears the embedded file data. Returns true if successful, else false.
  virtual bool Clear(void);

  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

  // If ON_EmbeddedFile::Cast(ref.ModelComponent()) is not null,
  // that pointer is returned. Otherwise, none_return_value is returned.
  static const ON_EmbeddedFile* FromModelComponentRef(const ON_ModelComponentReference& ref,
                                                      const ON_EmbeddedFile* none_return_value);

private:
  class CImpl;
  CImpl* m_impl;
};

#endif
