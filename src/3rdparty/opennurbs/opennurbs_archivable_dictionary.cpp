#include "opennurbs.h"
#include <cstddef>
#include <map>

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

////////////////////////////////////////////////////////////////////////////////

enum class DictionaryEntryType : int
{
  // values <= 0 are considered bogus
  // each supported object type has an associated DictionaryEntryType enum value
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // NEVER EVER Change DictionaryEntryType values as this will break I/O code
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  Undefined = 0,
  
  // some basic data types
  Boolean = 1, // bool
  UInt8 = 2,   // uint8_t
  Int8 = 3,    // int8_t
  Int16 = 4,   // int16_t
  UInt16 = 5,  // uint16_t
  Int32 = 6,   // int32_t
  UInt32 = 7,  // uint32_t
  Int64 = 8,   // int64_t
  Float = 9,   // float
  Double = 10, // double
  Uuid = 11,
  String = 12,

  // array of basic data types
  BooleanArray = 13,
  UInt8Array = 14,
  Int8Array = 15,
  Int16Array = 16,
  Int32Array = 17,
  FloatArray = 18,
  DoubleArray = 19,
  UuidArray = 20,
  StringArray = 21,
  
  Color = 22,
  Point2i = 23,
  Point2f = 24,
  Rect4i = 25,
  Rect4f = 26,
  Size2i = 27,
  Size2f = 28,
  Font = 29,

  Interval = 30,
  Point2d = 31,
  Point3d = 32,
  Point4d = 33,
  Vector2d = 34,
  Vector3d = 35,
  BoundingBox = 36,
  Ray3d = 37,
  PlaneEquation = 38,
  Xform = 39,
  Plane = 40,
  Line = 41,
  Point3f = 42,
  Vector3f = 43,

  ArchivableDictionary = 44,
  Object = 45, // OBSOLETE
  MeshParameters = 46,
  Geometry = 47,
};

////////////////////////////////////////////////////////////////////////////////

class DictionaryEntry
{
public:
  static DictionaryEntry* CreateInstance(enum DictionaryEntryType item_type);
  virtual ~DictionaryEntry() = default;

  virtual enum DictionaryEntryType EntryType() const = 0;
  virtual DictionaryEntry* Duplicate() const = 0;

  virtual bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const = 0;
  virtual bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) = 0;
};

template<typename V, DictionaryEntryType T>
class DictionaryEntryT : public DictionaryEntry
{
protected:
  using value_type      = V;
  using reference       = V&;
  using const_reference = const V&;

  value_type m_value;

public:
  enum DictionaryEntryType EntryType() const override { return T; }
  static const DictionaryEntryType Type = T;

  DictionaryEntryT() : m_value() { }
  DictionaryEntryT(const_reference value) : m_value(value) { }
  virtual ~DictionaryEntryT() override = default;

  const_reference Value() const { return m_value; }
  reference Value() { return m_value; }
};

template <typename T>
class Entry;

template <typename T>
static std::unique_ptr<Entry<T>> make_entry(const T& value)
{
  return std::make_unique<Entry<T>>(value);
}

template <typename T>
static std::unique_ptr<Entry<std::shared_ptr<typename std::remove_const<T>::type>>> make_entry(const std::shared_ptr<T>& value)
{
  return std::make_unique<Entry<std::shared_ptr<typename std::remove_const<T>::type>>>
    (std::make_shared<typename std::remove_const<T>::type>(*value));
}

////////////////////////////////////////////////////////////////////////////////
class ON_ArchivableDictionaryPrivate
{
public:
  ON_ArchivableDictionaryPrivate() = default;
  ~ON_ArchivableDictionaryPrivate() = default;

  ON_ArchivableDictionaryPrivate(const ON_ArchivableDictionaryPrivate& other) :
    m_version(other.m_version),
    m_name(other.m_name)
  {
    for (const auto & item : other.m_map)
    {
      const auto& key = item.first;
      const auto& value = item.second;
      m_map[key].reset(value->Duplicate());
    }
  }

  ON_ArchivableDictionaryPrivate& operator=(const ON_ArchivableDictionaryPrivate& other)
  {
    m_version = other.m_version;
    m_name = other.m_name;

    m_map.clear();
    for (const auto & item : other.m_map)
    {
      const auto& key = item.first;
      const auto& value = item.second;
      m_map[key].reset(value->Duplicate());
    }

    return *this;
  }

  unsigned int m_version = 0;
  ON_wString m_name = ON_wString::EmptyString;

  // std::less<void> is important to enable ON_wString-wchar_t* comparison without an implicit copy.
  std::map<ON_wString, std::unique_ptr<DictionaryEntry>, std::less<void>> m_map;

  template <typename V>
  bool TrySetValue(const wchar_t* key, const V& value)
  {
    auto r = m_map.insert({ key, nullptr });
    auto& entry_ptr = r.first->second;

    if (r.second)
    {
      entry_ptr = make_entry(value);
      return true;
    }
    else if (entry_ptr->EntryType() == Entry<V>::Type)
    {
      static_cast<Entry<V>*>(entry_ptr.get())->Value() = value;
      return true;
    }

    return false;
  }

  template <typename T>
  bool TryGetValue(const wchar_t* key, T& value) const
  {
    const auto iterator = m_map.find(key);
    if (iterator == m_map.end()) return false;

    const auto entry = iterator->second.get();
    if (entry->EntryType() != Entry<T>::Type)
      return false;

    value = static_cast<const Entry<T>*>(entry)->Value();
    return true;
  }

  template<typename T>
  const T& SetValue(const wchar_t* key, const T& value)
  {
    auto r = m_map.insert({ key, nullptr });
    auto& entry_ptr = r.first->second;

    if (!r.second && entry_ptr->EntryType() == Entry<T>::Type)
    {
      return static_cast<Entry<T>*>(entry_ptr.get())->Value() = value;
    }
    else
    {
      entry_ptr = make_entry(value);
      return static_cast<Entry<T>*>(entry_ptr.get())->Value();
    }
  }

  template <typename T>
  const std::shared_ptr<typename std::remove_const<T>::type>& SetValue(const wchar_t* key, const std::shared_ptr<T>& value)
  {
    auto entry = (m_map[key] = make_entry(value)).get();
    return static_cast<Entry<std::shared_ptr<typename std::remove_const<T>::type>>*>(entry)->Value();
  }

  template <typename T>
  T GetValue(const wchar_t* key) const
  {
    T value{};
    TryGetValue(key, value);
    return value;
  }
};

typedef std::shared_ptr<ON_ArchivableDictionary> ON_ArchivableDictionaryPtr;

////////////////////////////////////////////////////////////////////////////////
// Empty
////////////////////////////////////////////////////////////////////////////////

const ON_ArchivableDictionary ON_ArchivableDictionary::Empty;

////////////////////////////////////////////////////////////////////////////////
// Default
////////////////////////////////////////////////////////////////////////////////

ON_ArchivableDictionary::ON_ArchivableDictionary() :
  m_private(new ON_ArchivableDictionaryPrivate)
{
}

ON_ArchivableDictionary::~ON_ArchivableDictionary()
{
  delete m_private;
}

////////////////////////////////////////////////////////////////////////////////
// Copy
////////////////////////////////////////////////////////////////////////////////

ON_ArchivableDictionary::ON_ArchivableDictionary(const ON_ArchivableDictionary& src) :
  m_private(new ON_ArchivableDictionaryPrivate(*src.m_private))
{
}

ON_ArchivableDictionary& ON_ArchivableDictionary::operator=(const ON_ArchivableDictionary& src)
{
  *m_private = *src.m_private;
  return *this;
}

#if defined(ON_HAS_RVALUEREF)
////////////////////////////////////////////////////////////////////////////////
// Move
////////////////////////////////////////////////////////////////////////////////

ON_ArchivableDictionary::ON_ArchivableDictionary(ON_ArchivableDictionary&& src) ON_NOEXCEPT
  : m_private(src.m_private)
{
  src.m_private = nullptr;
}

ON_ArchivableDictionary& ON_ArchivableDictionary::operator=(ON_ArchivableDictionary&& src) ON_NOEXCEPT
{
  delete m_private;
  m_private = src.m_private;
  src.m_private = nullptr;

  return *this;
}
#endif

////////////////////////////////////////////////////////////////////////////////

static const ON_UUID RhinoDotNetDictionaryId = ON_UuidFromString("21EE7933-1E2D-4047-869E-6BDBF986EA11");

bool ON_ArchivableDictionary::Write(ON_BinaryArchive& binary_archive) const
{
  if (!binary_archive.BeginWriteDictionary(RhinoDotNetDictionaryId, m_private->m_version, m_private->m_name))
    return false;

  for (const auto& item : m_private->m_map)
  {
    const auto& key = item.first;
    const auto& value = item.second;

    if (!binary_archive.BeginWriteDictionaryEntry((int) value->EntryType(), key))
      return false;

    if (!value->WriteDictionaryEntry(binary_archive))
      return false;

    if (!binary_archive.EndWriteDictionaryEntry())
      return false;
  }

  return binary_archive.EndWriteDictionary();
}

bool ON_ArchivableDictionary::Read(ON_BinaryArchive& binary_archive)
{
  ON_UUID dictionary_id = {};
  unsigned int dictionary_version = {};
  ON_wString dictionary_name;
  m_private->m_map.clear();

  if (!binary_archive.BeginReadDictionary(&dictionary_id, &dictionary_version, dictionary_name))
    return false;

  if (dictionary_id != RhinoDotNetDictionaryId)
    return false;

  while (true)
  {
    int        item_type;
    ON_wString item_name;
    auto rc = binary_archive.BeginReadDictionaryEntry(&item_type, item_name);
    if (rc == 1)
    {
      std::unique_ptr<DictionaryEntry> value(DictionaryEntry::CreateInstance((DictionaryEntryType)item_type));
      if (value)
      {
        if (!value->ReadDictionaryEntry(binary_archive))
          return false;

        m_private->m_map[item_name] = std::move(value);
      }
      else
      {
        // We skip unknown item types
        ON_WarningEx(__FILE__, __LINE__, OPENNURBS__FUNCTION__, "Uknown ArchivableDictionary item type %d.", item_type);
      }
    }
    else if (rc == 2) break;
    else              return false;

    if (!binary_archive.EndReadDictionaryEntry())
      return false;
  }

  return binary_archive.EndReadDictionary();
}

////////////////////////////////////////////////////////////////////////////////

int ON_ArchivableDictionary::Count() const
{
  return (int)m_private->m_map.size();
}

void ON_ArchivableDictionary::Clear()
{
  m_private->m_map.clear();
}

ON_ClassArray<ON_wString> ON_ArchivableDictionary::GetKeys() const
{
  ON_ClassArray<ON_wString> keys(Count());

  for (const auto & entry : m_private->m_map)
    keys.Append(entry.first);

  return keys;
}

bool ON_ArchivableDictionary::ContainsKey(const wchar_t* key) const
{
  return m_private->m_map.find(key) != m_private->m_map.cend();
}

bool ON_ArchivableDictionary::Remove(const wchar_t* key)
{
  const auto iterator = m_private->m_map.find(key);
  if (iterator == m_private->m_map.end())
    return false;
  
  m_private->m_map.erase(iterator);
  return true;
}

bool ON_ArchivableDictionary::CopyValue(const wchar_t* key, const ON_ArchivableDictionary& source, const wchar_t* source_key)
{
  if (source_key == nullptr)
    source_key = key;

  const auto iterator = source.m_private->m_map.find(source_key);
  if (iterator != source.m_private->m_map.end())
  {
    m_private->m_map[key].reset(iterator->second->Duplicate());
    return true;
  }
  
  return false;
}

void ON_ArchivableDictionary::CopyValues(const ON_ArchivableDictionary& source)
{
  if (this != &source)
  {
    for (const auto& entry : source.m_private->m_map)
      m_private->m_map[entry.first].reset(entry.second->Duplicate());
  }
}

#pragma region Getters-Setters Primitives

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<bool> : public DictionaryEntryT<bool, DictionaryEntryType::Boolean>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteBool(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadBool(&m_value); }
};

bool ON_ArchivableDictionary::TrySetBool(const wchar_t* key, bool value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetBool(const wchar_t* key, bool& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetBool(const wchar_t* key, bool value)
{
  m_private->SetValue(key, value);
}

bool ON_ArchivableDictionary::GetBool(const wchar_t* key) const
{
  return m_private->GetValue<bool>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON__UINT8> : public DictionaryEntryT<ON__UINT8, DictionaryEntryType::UInt8>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteByte(1, &m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadByte(1, &m_value); }
};

bool ON_ArchivableDictionary::TrySetUInt8(const wchar_t* key, ON__UINT8 value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetUInt8(const wchar_t* key, ON__UINT8& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetUInt8(const wchar_t* key, ON__UINT8 value)
{
  m_private->SetValue(key, value);
}

ON__UINT8 ON_ArchivableDictionary::GetUInt8(const wchar_t* key) const
{
  return m_private->GetValue<ON__UINT8>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON__INT8> : public DictionaryEntryT<ON__INT8, DictionaryEntryType::Int8>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteByte(1, &m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadByte(1, &m_value); }
};

bool ON_ArchivableDictionary::TrySetInt8(const wchar_t* key, ON__INT8 value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetInt8(const wchar_t* key, ON__INT8& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetInt8(const wchar_t* key, ON__INT8 value)
{
  m_private->SetValue(key, value);
}

ON__INT8 ON_ArchivableDictionary::GetInt8(const wchar_t* key) const
{
  return m_private->GetValue<ON__INT8>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON__INT16> : public DictionaryEntryT<ON__INT16, DictionaryEntryType::Int16>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteShort(1, &m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadShort(1, &m_value); }
};

bool ON_ArchivableDictionary::TrySetInt16(const wchar_t* key, ON__INT16 value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetInt16(const wchar_t* key, ON__INT16& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetInt16(const wchar_t* key, ON__INT16 value)
{
  m_private->SetValue(key, value);
}

ON__INT16 ON_ArchivableDictionary::GetInt16(const wchar_t* key) const
{
  return m_private->GetValue<ON__INT16>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON__UINT16> : public DictionaryEntryT<ON__UINT16, DictionaryEntryType::UInt16>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteShort(1, &m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadShort(1, &m_value); }
};

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON__INT32> : public DictionaryEntryT<ON__INT32, DictionaryEntryType::Int32>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteInt(1, &m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadInt(1, &m_value); }
};

bool ON_ArchivableDictionary::TrySetInt32(const wchar_t* key, ON__INT32 value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetInt32(const wchar_t* key, ON__INT32& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetInt32(const wchar_t* key, ON__INT32 value)
{
  m_private->SetValue(key, value);
}

ON__INT32 ON_ArchivableDictionary::GetInt32(const wchar_t* key) const
{
  return m_private->GetValue<ON__INT32>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON__UINT32> : public DictionaryEntryT<ON__UINT32, DictionaryEntryType::UInt32>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteInt(1, &m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadInt(1, &m_value); }
};

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON__INT64> : public DictionaryEntryT<ON__INT64, DictionaryEntryType::Int64>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteBigInt(1, &m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadBigInt(1, &m_value); }
};

bool ON_ArchivableDictionary::TrySetInt64(const wchar_t* key, ON__INT64 value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetInt64(const wchar_t* key, ON__INT64& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetInt64(const wchar_t* key, ON__INT64 value)
{
  m_private->SetValue(key, value);
}

ON__INT64 ON_ArchivableDictionary::GetInt64(const wchar_t* key) const
{
  return m_private->GetValue<ON__INT64>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<float> : public DictionaryEntryT<float, DictionaryEntryType::Float>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteFloat(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadFloat(&m_value); }
};

bool ON_ArchivableDictionary::TrySetFloat(const wchar_t* key, float value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetFloat(const wchar_t* key, float& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetFloat(const wchar_t* key, float value)
{
  m_private->SetValue(key, value);
}

float ON_ArchivableDictionary::GetFloat(const wchar_t* key) const
{
  return m_private->GetValue<float>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<double> : public DictionaryEntryT<double, DictionaryEntryType::Double>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteDouble(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadDouble(&m_value); }
};

bool ON_ArchivableDictionary::TrySetDouble(const wchar_t* key, double value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetDouble(const wchar_t* key, double& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetDouble(const wchar_t* key, double value)
{
  m_private->SetValue(key, value);
}

double ON_ArchivableDictionary::GetDouble(const wchar_t* key) const
{
  return m_private->GetValue<double>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_UUID> : public DictionaryEntryT<ON_UUID, DictionaryEntryType::Uuid>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteUuid(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadUuid(m_value); }
};

bool ON_ArchivableDictionary::TrySetUuid(const wchar_t* key, ON_UUID value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetUuid(const wchar_t* key, ON_UUID& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetUuid(const wchar_t* key, ON_UUID value)
{
  m_private->SetValue(key, value);
}

ON_UUID ON_ArchivableDictionary::GetUuid(const wchar_t* key) const
{
  return m_private->GetValue<ON_UUID>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_wString> : public DictionaryEntryT<ON_wString, DictionaryEntryType::String>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteString(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadString(m_value); }
};

bool ON_ArchivableDictionary::TrySetString(const wchar_t* key, const ON_wString& value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetString(const wchar_t* key, ON_wString& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetString(const wchar_t* key, const ON_wString& value)
{
  m_private->SetValue(key, value);
}

ON_wString ON_ArchivableDictionary::GetString(const wchar_t* key) const
{
  return m_private->GetValue<ON_wString>(key);
}

#pragma endregion

////////////////////////////////////////////////////////////////////////////////

#pragma region Getters-Setters Primitive Arrays

template <> class Entry<ON_SimpleArray<bool>> : public DictionaryEntryT<ON_SimpleArray<bool>, DictionaryEntryType::BooleanArray>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteArray(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadArray(m_value); }
};

bool ON_ArchivableDictionary::TrySetBoolArray(const wchar_t* key, const ON_SimpleArray<bool>& value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetBoolArray(const wchar_t* key, ON_SimpleArray<bool>& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetBoolArray(const wchar_t* key, const ON_SimpleArray<bool>& value)
{
  m_private->SetValue(key, value);
}

ON_SimpleArray<bool> ON_ArchivableDictionary::GetBoolArray(const wchar_t* key) const
{
  return m_private->GetValue<ON_SimpleArray<bool>>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_SimpleArray<ON__UINT8>> : public DictionaryEntryT<ON_SimpleArray<ON__UINT8>, DictionaryEntryType::UInt8Array>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteArray(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadArray(m_value); }
};

bool ON_ArchivableDictionary::TrySetUInt8Array(const wchar_t* key, const ON_SimpleArray<ON__UINT8>& value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetUInt8Array(const wchar_t* key, ON_SimpleArray<ON__UINT8>& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetUInt8Array(const wchar_t* key, const ON_SimpleArray<ON__UINT8>& value)
{
  m_private->SetValue(key, value);
}

ON_SimpleArray<ON__UINT8> ON_ArchivableDictionary::GetUInt8Array(const wchar_t* key) const
{
  return m_private->GetValue<ON_SimpleArray<ON__UINT8>>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_SimpleArray<ON__INT8>> : public DictionaryEntryT<ON_SimpleArray<ON__INT8>, DictionaryEntryType::Int8Array>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteArray(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadArray(m_value); }
};

bool ON_ArchivableDictionary::TrySetInt8Array(const wchar_t* key, const ON_SimpleArray<ON__INT8>& value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetInt8Array(const wchar_t* key, ON_SimpleArray<ON__INT8>& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetInt8Array(const wchar_t* key, const ON_SimpleArray<ON__INT8>& value)
{
  m_private->SetValue(key, value);
}

ON_SimpleArray<ON__INT8> ON_ArchivableDictionary::GetInt8Array(const wchar_t* key) const
{
  return m_private->GetValue<ON_SimpleArray<ON__INT8>>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_SimpleArray<ON__INT16>> : public DictionaryEntryT<ON_SimpleArray<ON__INT16>, DictionaryEntryType::Int16Array>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteArray(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadArray(m_value); }
};

bool ON_ArchivableDictionary::TrySetInt16Array(const wchar_t* key, const ON_SimpleArray<ON__INT16>& value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetInt16Array(const wchar_t* key, ON_SimpleArray<ON__INT16>& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetInt16Array(const wchar_t* key, const ON_SimpleArray<ON__INT16>& value)
{
  m_private->SetValue(key, value);
}

ON_SimpleArray<ON__INT16> ON_ArchivableDictionary::GetInt16Array(const wchar_t* key) const
{
  return m_private->GetValue<ON_SimpleArray<ON__INT16>>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_SimpleArray<ON__INT32>> : public DictionaryEntryT<ON_SimpleArray<ON__INT32>, DictionaryEntryType::Int32Array>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteArray(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadArray(m_value); }
};

bool ON_ArchivableDictionary::TrySetInt32Array(const wchar_t* key, const ON_SimpleArray<ON__INT32>& value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetInt32Array(const wchar_t* key, ON_SimpleArray<ON__INT32>& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetInt32Array(const wchar_t* key, const ON_SimpleArray<ON__INT32>& value)
{
  m_private->SetValue(key, value);
}

ON_SimpleArray<ON__INT32> ON_ArchivableDictionary::GetInt32Array(const wchar_t* key) const
{
  return m_private->GetValue<ON_SimpleArray<ON__INT32>>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_SimpleArray<float>> : public DictionaryEntryT<ON_SimpleArray<float>, DictionaryEntryType::FloatArray>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteArray(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadArray(m_value); }
};

bool ON_ArchivableDictionary::TrySetFloatArray(const wchar_t* key, const ON_SimpleArray<float>& value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetFloatArray(const wchar_t* key, ON_SimpleArray<float>& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetFloatArray(const wchar_t* key, const ON_SimpleArray<float>& value)
{
  m_private->SetValue(key, value);
}

ON_SimpleArray<float> ON_ArchivableDictionary::GetFloatArray(const wchar_t* key) const
{
  return m_private->GetValue<ON_SimpleArray<float>>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_SimpleArray<double>> : public DictionaryEntryT<ON_SimpleArray<double>, DictionaryEntryType::DoubleArray>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteArray(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadArray(m_value); }
};

bool ON_ArchivableDictionary::TrySetDoubleArray(const wchar_t* key, const ON_SimpleArray<double>& value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetDoubleArray(const wchar_t* key, ON_SimpleArray<double>& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetDoubleArray(const wchar_t* key, const ON_SimpleArray<double>& value)
{
  m_private->SetValue(key, value);
}

ON_SimpleArray<double> ON_ArchivableDictionary::GetDoubleArray(const wchar_t* key) const
{
  return m_private->GetValue<ON_SimpleArray<double>>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_SimpleArray<ON_UUID>> : public DictionaryEntryT<ON_SimpleArray<ON_UUID>, DictionaryEntryType::UuidArray>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteArray(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadArray(m_value); }
};

bool ON_ArchivableDictionary::TrySetUuidArray(const wchar_t* key, const ON_SimpleArray<ON_UUID>& value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetUuidArray(const wchar_t* key, ON_SimpleArray<ON_UUID>& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetUuidArray(const wchar_t* key, const ON_SimpleArray<ON_UUID>& value)
{
  m_private->SetValue(key, value);
}

ON_SimpleArray<ON_UUID> ON_ArchivableDictionary::GetUuidArray(const wchar_t* key) const
{
  return m_private->GetValue<ON_SimpleArray<ON_UUID>>(key);
}

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_ClassArray<ON_wString>> : public DictionaryEntryT<ON_ClassArray<ON_wString>, DictionaryEntryType::StringArray>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteArray(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadArray(m_value); }
};

bool ON_ArchivableDictionary::TrySetStringArray(const wchar_t* key, const ON_ClassArray<ON_wString>& value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetStringArray(const wchar_t* key, ON_ClassArray<ON_wString>& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetStringArray(const wchar_t* key, const ON_ClassArray<ON_wString>& value)
{
  m_private->SetValue(key, value);
}

ON_ClassArray<ON_wString> ON_ArchivableDictionary::GetStringArray(const wchar_t* key) const
{
  return m_private->GetValue<ON_ClassArray<ON_wString>>(key);
}

#pragma endregion

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_Color> : public DictionaryEntryT<ON_Color, DictionaryEntryType::Color>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteColor(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadColor(m_value); }
};

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_2iPoint> : public DictionaryEntryT<ON_2iPoint, DictionaryEntryType::Point2i>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const
  {
    return binary_archive.WriteInt(m_value.x) && binary_archive.WriteInt(m_value.y);
  }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive)
  {
    return binary_archive.ReadInt(&m_value.x) && binary_archive.ReadInt(&m_value.y);
  }
};

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_2fPoint> : public DictionaryEntryT<ON_2fPoint, DictionaryEntryType::Point2f>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const
  {
    return binary_archive.WriteFloat(m_value.x) && binary_archive.WriteFloat(m_value.y);
  }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive)
  {
    return binary_archive.ReadFloat(&m_value.x) && binary_archive.ReadFloat(&m_value.y);
  }
};

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_4iRect> : public DictionaryEntryT<ON_4iRect, DictionaryEntryType::Rect4i>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const
  {
    const int values[]{ m_value.left, m_value.top, m_value.right - m_value.left, m_value.bottom - m_value.top };
    return binary_archive.WriteInt(4, values);
  }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive)
  {
    int values[]{ 0, 0, 0, 0 };
    if (!binary_archive.ReadInt(4, values))
      return false;

    m_value.SetRect(values[0], values[1], values[0] + values[2], values[1] + values[3]);
    return true;
  }
};

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_2iSize> : public DictionaryEntryT<ON_2iSize, DictionaryEntryType::Size2i>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteInt(m_value.cx) && binary_archive.WriteInt(m_value.cy); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadInt(&m_value.cx) && binary_archive.ReadInt(&m_value.cy); }
};

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_2dPoint> : public DictionaryEntryT<ON_2dPoint, DictionaryEntryType::Point2d>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WritePoint(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadPoint(m_value); }
};

template <> class Entry<ON_3dPoint> : public DictionaryEntryT<ON_3dPoint, DictionaryEntryType::Point3d>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WritePoint(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadPoint(m_value); }
};

template <> class Entry<ON_4dPoint> : public DictionaryEntryT<ON_4dPoint, DictionaryEntryType::Point4d>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WritePoint(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadPoint(m_value); }
};

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_2dVector> : public DictionaryEntryT<ON_2dVector, DictionaryEntryType::Vector2d>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteVector(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadVector(m_value); }
};

template <> class Entry<ON_3dVector> : public DictionaryEntryT<ON_3dVector, DictionaryEntryType::Vector3d>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return binary_archive.WriteVector(m_value); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return binary_archive.ReadVector(m_value); }
};

////////////////////////////////////////////////////////////////////////////////

template <> class Entry<ON_ArchivableDictionaryPtr> : public DictionaryEntryT<ON_ArchivableDictionaryPtr, DictionaryEntryType::ArchivableDictionary>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return m_value->Write(binary_archive); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return m_value->Read(binary_archive); }
};

////////////////////////////////////////////////////////////////////////////////
template <> class Entry<ON_Object> : public DictionaryEntryT<ON_Object, DictionaryEntryType::Object>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return m_value.Write(binary_archive); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return m_value.Read(binary_archive); }
};

////////////////////////////////////////////////////////////////////////////////
template <> class Entry<ON_MeshParameters> : public DictionaryEntryT<ON_MeshParameters, DictionaryEntryType::MeshParameters>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return m_value.Write(binary_archive); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return m_value.Read(binary_archive); }
};

bool ON_ArchivableDictionary::TrySetMeshParameters(const wchar_t* key, const ON_MeshParameters& value)
{
  return m_private->TrySetValue(key, value);
}

bool ON_ArchivableDictionary::TryGetMeshParameters(const wchar_t* key, ON_MeshParameters& value) const
{
  return m_private->TryGetValue(key, value);
}

void ON_ArchivableDictionary::SetMeshParameters(const wchar_t* key, const ON_MeshParameters& value)
{
  m_private->SetValue(key, value);
}

ON_MeshParameters ON_ArchivableDictionary::GetMeshParameters(const wchar_t* key) const
{
  return m_private->GetValue<ON_MeshParameters>(key);
}


////////////////////////////////////////////////////////////////////////////////
template <> class Entry<ON_Geometry> : public DictionaryEntryT<ON_Geometry, DictionaryEntryType::Geometry>
{
public:
  Entry() = default;
  Entry(const value_type& value) : DictionaryEntryT(value) {}
  virtual DictionaryEntry* Duplicate() const { return new Entry(m_value); }

  bool WriteDictionaryEntry(ON_BinaryArchive& binary_archive) const { return m_value.Write(binary_archive); }
  bool ReadDictionaryEntry(ON_BinaryArchive& binary_archive) { return m_value.Read(binary_archive); }
};

////////////////////////////////////////////////////////////////////////////////
DictionaryEntry* DictionaryEntry::CreateInstance(enum DictionaryEntryType item_type)
{
  switch (item_type)
  {
  // some basic data types
  case Entry<bool>::Type: return new Entry<bool>;
  case Entry<std::uint8_t>::Type: return new Entry<std::uint8_t>;
  case Entry<std::int8_t>::Type: return new Entry<std::int8_t>;
  case Entry<std::int16_t>::Type: return new Entry<std::int16_t>;
  case Entry<std::uint16_t>::Type: return new Entry<std::uint16_t>;
  case Entry<std::int32_t>::Type: return new Entry<std::int32_t>;
  case Entry<std::uint32_t>::Type: return new Entry<std::uint32_t>;
  case Entry<std::int64_t>::Type: return new Entry<std::int64_t>;
  case Entry<float>::Type: return new Entry<float>;
  case Entry<double>::Type: return new Entry<double>;
  case Entry<ON_UUID>::Type: return new Entry<ON_UUID>;
  case Entry<ON_wString>::Type: return new Entry<ON_wString>;

  // array of basic data types
  case Entry<ON_SimpleArray<bool>>::Type: return new Entry<ON_SimpleArray<bool>>;
  case Entry<ON_SimpleArray<std::uint8_t>>::Type: return new Entry<ON_SimpleArray<std::uint8_t>>;
  case Entry<ON_SimpleArray<std::int8_t>>::Type: return new Entry<ON_SimpleArray<std::int8_t>>;
  case Entry<ON_SimpleArray<std::int16_t>>::Type: return new Entry<ON_SimpleArray<std::int16_t>>;
  case Entry<ON_SimpleArray<std::int32_t>>::Type: return new Entry<ON_SimpleArray<std::int32_t>>;
  case Entry<ON_SimpleArray<float>>::Type: return new Entry<ON_SimpleArray<float>>;
  case Entry<ON_SimpleArray<double>>::Type: return new Entry<ON_SimpleArray<double>>;
  case Entry<ON_SimpleArray<ON_UUID>>::Type: return new Entry<ON_SimpleArray<ON_UUID>>;
  case Entry<ON_ClassArray<ON_wString>>::Type: return new Entry<ON_ClassArray<ON_wString>>;

  case Entry<ON_Color>::Type: return new Entry<ON_Color>;
  case Entry<ON_2iPoint>::Type: return new Entry<ON_2iPoint>;
  case Entry<ON_2fPoint>::Type: return new Entry<ON_2fPoint>;
  case Entry<ON_4iRect>::Type: return new Entry<ON_4iRect>;
  //case Entry<ON_4fRect>::Type: return new Entry<ON_4fRect>;
  case Entry<ON_2iSize>::Type: return new Entry<ON_2iSize>;
  //case Entry<ON_2fSize>::Type: return new Entry<ON_2fSize>;
  //case Entry<ON_Font>::Type: return new Entry<ON_Font>;

  //case Entry<ON_Interval>::Type: return new Entry<ON_Interval>;
  case Entry<ON_2dPoint>::Type: return new Entry<ON_2dPoint>;
  case Entry<ON_3dPoint>::Type: return new Entry<ON_3dPoint>;
  case Entry<ON_4dPoint>::Type: return new Entry<ON_4dPoint>;
  case Entry<ON_2dVector>::Type: return new Entry<ON_2dVector>;
  case Entry<ON_3dVector>::Type: return new Entry<ON_3dVector>;
  //case Entry<ON_BoundingBox>::Type: return new Entry<ON_BoundingBox>;
  //case Entry<ON_3dRay>::Type: return new Entry<ON_3dRay>;
  //case Entry<ON_PlaneEquation>::Type: return new Entry<ON_PlaneEquation>;
  //case Entry<ON_Xform>::Type: return new Entry<ON_Xform>;
  //case Entry<ON_Plane>::Type: return new Entry<ON_Plane>;
  //case Entry<ON_Line>::Type: return new Entry<ON_Line>;
  //case Entry<ON_3fPoint>::Type: return new Entry<ON_3fPoint>;
  //case Entry<ON_3fVector>::Type: return new Entry<ON_3fVector>;

  case DictionaryEntryType::Object: return new Entry<ON_Object>;
  case DictionaryEntryType::MeshParameters: return new Entry<ON_MeshParameters>;
  case DictionaryEntryType::Geometry: return new Entry<ON_Geometry>;
  case DictionaryEntryType::ArchivableDictionary: return new Entry<ON_ArchivableDictionaryPtr>;
  default: return nullptr;
  }
}

////////////////////////////////////////////////////////////////////////////////
