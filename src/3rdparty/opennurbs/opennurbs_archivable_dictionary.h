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

#if !defined(OPENNURBS_ARCHIVABLE_DICTIONARY_INC_)
#define OPENNURBS_ARCHIVABLE_DICTIONARY_INC_

class ON_CLASS ON_ArchivableDictionary
{
public:
  static const ON_ArchivableDictionary Empty;

  ON_ArchivableDictionary();
  virtual ~ON_ArchivableDictionary();

  ON_ArchivableDictionary(const ON_ArchivableDictionary& src);
  ON_ArchivableDictionary& operator=(const ON_ArchivableDictionary& src);

#if defined(ON_HAS_RVALUEREF)
  ON_ArchivableDictionary(ON_ArchivableDictionary&& src) ON_NOEXCEPT;
  ON_ArchivableDictionary& operator=(ON_ArchivableDictionary&& src) ON_NOEXCEPT;
#endif

  virtual bool Write(ON_BinaryArchive& binary_archive) const;
  virtual bool Read(ON_BinaryArchive& binary_archive);

  int Count() const;      // Number of elements in dictionary.
  void Clear();           // Sets count to 0.

  ON_ClassArray<ON_wString> GetKeys() const;
  bool ContainsKey(const wchar_t* key) const;
  bool Remove(const wchar_t* key);

  bool CopyValue(const wchar_t* key, const ON_ArchivableDictionary& source, const wchar_t* source_key = nullptr);
  void CopyValues(const ON_ArchivableDictionary& source);

#pragma region Getters-Setters Primitives

  bool TrySetBool(const wchar_t* key, bool value);
  bool TryGetBool(const wchar_t* key, bool& value) const;
  void SetBool(const wchar_t* key, bool value);
  bool GetBool(const wchar_t* key) const;

  bool TrySetUInt8(const wchar_t* key, ON__UINT8 value);
  bool TryGetUInt8(const wchar_t* key, ON__UINT8& value) const;
  void SetUInt8(const wchar_t* key, ON__UINT8 value);
  ON__UINT8 GetUInt8(const wchar_t* key) const;

  bool TrySetInt8(const wchar_t* key, ON__INT8 value);
  bool TryGetInt8(const wchar_t* key, ON__INT8& value) const;
  void SetInt8(const wchar_t* key, ON__INT8 value);
  ON__INT8 GetInt8(const wchar_t* key) const;

  bool TrySetInt16(const wchar_t* key, ON__INT16 value);
  bool TryGetInt16(const wchar_t* key, ON__INT16& value) const;
  void SetInt16(const wchar_t* key, ON__INT16 value);
  ON__INT16 GetInt16(const wchar_t* key) const;

  bool TrySetInt32(const wchar_t* key, ON__INT32 value);
  bool TryGetInt32(const wchar_t* key, ON__INT32& value) const;
  void SetInt32(const wchar_t* key, ON__INT32 value);
  ON__INT32 GetInt32(const wchar_t* key) const;

  bool TrySetInt64(const wchar_t* key, ON__INT64 value);
  bool TryGetInt64(const wchar_t* key, ON__INT64& value) const;
  void SetInt64(const wchar_t* key, ON__INT64 value);
  ON__INT64 GetInt64(const wchar_t* key) const;

  bool TrySetFloat(const wchar_t* key, float value);
  bool TryGetFloat(const wchar_t* key, float& value) const;
  void SetFloat(const wchar_t* key, float value);
  float GetFloat(const wchar_t* key) const;

  bool TrySetDouble(const wchar_t* key, double value);
  bool TryGetDouble(const wchar_t* key, double& value) const;
  void SetDouble(const wchar_t* key, double value);
  double GetDouble(const wchar_t* key) const;

  bool TrySetUuid(const wchar_t* key, ON_UUID value);
  bool TryGetUuid(const wchar_t* key, ON_UUID& value) const;
  void SetUuid(const wchar_t* key, ON_UUID value);
  ON_UUID GetUuid(const wchar_t* key) const;

  bool TrySetString(const wchar_t* key, const ON_wString& value);
  bool TryGetString(const wchar_t* key, ON_wString& value) const;
  void SetString(const wchar_t* key, const ON_wString& value);
  ON_wString GetString(const wchar_t* key) const;

#pragma endregion

#pragma region Getters-Setters Primitive Arrays

  bool TrySetBoolArray(const wchar_t* key, const ON_SimpleArray<bool>& value);
  bool TryGetBoolArray(const wchar_t* key, ON_SimpleArray<bool>& value) const;
  void SetBoolArray(const wchar_t* key, const ON_SimpleArray<bool>& value);
  ON_SimpleArray<bool> GetBoolArray(const wchar_t* key) const;

  bool TrySetUInt8Array(const wchar_t* key, const ON_SimpleArray<ON__UINT8>& value);
  bool TryGetUInt8Array(const wchar_t* key, ON_SimpleArray<ON__UINT8>& value) const;
  void SetUInt8Array(const wchar_t* key, const ON_SimpleArray<ON__UINT8>& value);
  ON_SimpleArray<ON__UINT8> GetUInt8Array(const wchar_t* key) const;

  bool TrySetInt8Array(const wchar_t* key, const ON_SimpleArray<ON__INT8>& value);
  bool TryGetInt8Array(const wchar_t* key, ON_SimpleArray<ON__INT8>& value) const;
  void SetInt8Array(const wchar_t* key, const ON_SimpleArray<ON__INT8>& value);
  ON_SimpleArray<ON__INT8> GetInt8Array(const wchar_t* key) const;

  bool TrySetInt16Array(const wchar_t* key, const ON_SimpleArray<ON__INT16>& value);
  bool TryGetInt16Array(const wchar_t* key, ON_SimpleArray<ON__INT16>& value) const;
  void SetInt16Array(const wchar_t* key, const ON_SimpleArray<ON__INT16>& value);
  ON_SimpleArray<ON__INT16> GetInt16Array(const wchar_t* key) const;

  bool TrySetInt32Array(const wchar_t* key, const ON_SimpleArray<ON__INT32>& value);
  bool TryGetInt32Array(const wchar_t* key, ON_SimpleArray<ON__INT32>& value) const;
  void SetInt32Array(const wchar_t* key, const ON_SimpleArray<ON__INT32>& value);
  ON_SimpleArray<ON__INT32> GetInt32Array(const wchar_t* key) const;

  bool TrySetFloatArray(const wchar_t* key, const ON_SimpleArray<float>& value);
  bool TryGetFloatArray(const wchar_t* key, ON_SimpleArray<float>& value) const;
  void SetFloatArray(const wchar_t* key, const ON_SimpleArray<float>& value);
  ON_SimpleArray<float> GetFloatArray(const wchar_t* key) const;

  bool TrySetDoubleArray(const wchar_t* key, const ON_SimpleArray<double>& value);
  bool TryGetDoubleArray(const wchar_t* key, ON_SimpleArray<double>& value) const;
  void SetDoubleArray(const wchar_t* key, const ON_SimpleArray<double>& value);
  ON_SimpleArray<double> GetDoubleArray(const wchar_t* key) const;

  bool TrySetUuidArray(const wchar_t* key, const ON_SimpleArray<ON_UUID>& value);
  bool TryGetUuidArray(const wchar_t* key, ON_SimpleArray<ON_UUID>& value) const;
  void SetUuidArray(const wchar_t* key, const ON_SimpleArray<ON_UUID>& value);
  ON_SimpleArray<ON_UUID> GetUuidArray(const wchar_t* key) const;

  bool TrySetStringArray(const wchar_t* key, const ON_ClassArray<ON_wString>& value);
  bool TryGetStringArray(const wchar_t* key, ON_ClassArray<ON_wString>& value) const;
  void SetStringArray(const wchar_t* key, const ON_ClassArray<ON_wString>& value);
  ON_ClassArray<ON_wString> GetStringArray(const wchar_t* key) const;

#pragma endregion

#pragma region Getters-Setters Geometry

  bool TrySetMeshParameters(const wchar_t* key, const ON_MeshParameters& value);
  bool TryGetMeshParameters(const wchar_t* key, ON_MeshParameters& value) const;
  void SetMeshParameters(const wchar_t* key, const ON_MeshParameters& value);
  ON_MeshParameters GetMeshParameters(const wchar_t* key) const;

#pragma endregion

private:
  class ON_ArchivableDictionaryPrivate* m_private = nullptr;
  ON__UINT_PTR m_reserved = 0;
};

////////////////////////////////////////////////////////////////

#endif
