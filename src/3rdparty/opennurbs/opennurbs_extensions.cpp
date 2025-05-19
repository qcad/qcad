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
#include "opennurbs_internal_defines.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

const ONX_ErrorCounter ONX_ErrorCounter::operator+ (
  const ONX_ErrorCounter& rhs
  )
{
  ONX_ErrorCounter sum;
  sum.m_failure_count = m_failure_count + rhs.m_failure_count;
  sum.m_error_count = m_error_count + rhs.m_error_count;
  sum.m_warning_count = m_warning_count + rhs.m_warning_count;


  sum.m_state_bit_field = m_state_bit_field | rhs.m_state_bit_field;
  sum.m_opennurbs_library_error_count
    = (m_opennurbs_library_error_count < rhs.m_opennurbs_library_error_count)
    ? rhs.m_opennurbs_library_error_count
    : m_opennurbs_library_error_count;
  sum.m_opennurbs_library_warning_count
    = (m_opennurbs_library_warning_count < rhs.m_opennurbs_library_warning_count)
    ? rhs.m_opennurbs_library_warning_count
    : m_opennurbs_library_warning_count;

  return sum;
}


const ONX_ErrorCounter ONX_ErrorCounter::operator+= (const ONX_ErrorCounter& rhs)
{
  m_failure_count += rhs.m_failure_count;
  m_error_count += rhs.m_error_count;
  m_warning_count += rhs.m_warning_count;

  m_state_bit_field |= rhs.m_state_bit_field;
  if (m_opennurbs_library_error_count < rhs.m_opennurbs_library_error_count)
    m_opennurbs_library_error_count = rhs.m_opennurbs_library_error_count;
  if (m_opennurbs_library_warning_count < rhs.m_opennurbs_library_warning_count)
    m_opennurbs_library_warning_count = rhs.m_opennurbs_library_warning_count;

  return *this;
}


unsigned int ONX_ErrorCounter::FailureCount() const
{
  return this->m_failure_count;
}

unsigned int ONX_ErrorCounter::ErrorCount() const
{
  return this->m_error_count;
}

unsigned int ONX_ErrorCounter::WarningCount() const
{
  return this->m_warning_count;
}

unsigned int ONX_ErrorCounter::TotalCount() const
{
  return FailureCount() + ErrorCount() + WarningCount();
}

unsigned int ONX_ErrorCounter::IncrementFailureCount()
{
  return ++m_failure_count; // <- Good location for a debugger breakpoint.
}

unsigned int ONX_ErrorCounter::IncrementErrorCount()
{
  return ++m_error_count; // <- Good location for a debugger breakpoint.
}

unsigned int ONX_ErrorCounter::IncrementWarningCount()
{
  return ++m_warning_count; // <- Good location for a debugger breakpoint.
}

void ONX_ErrorCounter::ClearLibraryErrors()
{
  m_opennurbs_library_error_count = ON_GetErrorCount();
  m_state_bit_field |= 1;
}

unsigned int ONX_ErrorCounter::AddLibraryErrors()
{
  const bool bActive = (0 != (1 & m_state_bit_field));
  const unsigned int count0 = m_opennurbs_library_error_count;
  ClearLibraryErrors();
  const unsigned int count
    = bActive
    ? (m_opennurbs_library_error_count - count0)
    : 0U;
  if (bActive && count > 0)
    m_error_count += count; // <- Good location for a debugger breakpoint.
  return count;
}

void ONX_ErrorCounter::ClearLibraryWarnings()
{
  m_opennurbs_library_warning_count = ON_GetWarningCount();
  m_state_bit_field |= 2;
}

unsigned int ONX_ErrorCounter::AddLibraryWarnings()
{
  const bool bActive = (0 != (2 & m_state_bit_field));
  const unsigned int count0 = m_opennurbs_library_warning_count;
  ClearLibraryWarnings();
  const unsigned int count
    = bActive
    ? (m_opennurbs_library_warning_count - count0)
    : 0U;
  if (bActive && count>0)
    m_warning_count += count; // <- Good location for a debugger breakpoint.
  return count;
}

void ONX_ErrorCounter::ClearLibraryErrorsAndWarnings()
{
  ClearLibraryErrors();
  ClearLibraryWarnings();
}

unsigned int ONX_ErrorCounter::AddLibraryErrorsAndWarnings()
{
  return AddLibraryErrors() + AddLibraryWarnings();
}

void ONX_ErrorCounter::Dump(ON_TextLog& text_log) const
{
  text_log.Print(
      "%u failures, %u errors, %u warnings",
      m_failure_count,
      m_error_count,
      m_warning_count
    );
}

#if defined(OPENNURBS_EXPORTS)

////////////////////////////////////////////////////////////////////////////////
//
// When openNURBS is used as a Microsoft Windows DLL, it is possible 
// for new/delete to allocate memory in one executable and delete
// it in another.  Because Microsoft Windows has incompatible memory 
// managers in its plethora of C libraries and the choice of which
// C library actually gets used depends on the code generation 
// options you choose,  we get lots of support questions asking
// about hard to trace crashes.
//
// If you are using openNURBS as a Windows DLL, you are sure you know
// what you are doing, and you promise never to ask for support, then
// feel free to delete these overrides.
//
//
#if defined(ON_COMPILER_MSC)
#pragma message( " --- OpenNURBS overriding ONX_Model new and delete" )
#endif

// ONX_Model_UserData new/delete

void* ONX_Model_UserData::operator new(size_t sz)
{
  // ONX_Model_UserData new
  return onmalloc(sz);
}

void ONX_Model_UserData::operator delete(void* p)
{
  // ONX_Model_UserData delete
  onfree(p);
}

void* ONX_Model_UserData::operator new[] (size_t sz)
{
  // ONX_Model_UserData array new
  return onmalloc(sz);
}

void ONX_Model_UserData::operator delete[] (void* p)
{
  // ONX_Model_UserData array delete
  onfree(p);
}

void* ONX_Model_UserData::operator new(size_t, void* p)
{
  // ONX_Model_UserData placement new
  return p;
}

void ONX_Model_UserData::operator delete(void*, void*)
{
  // ONX_Model_UserData placement delete
  return;
}

// ONX_Model new/delete

void* ONX_Model::operator new(size_t sz)
{
  // ONX_Model new
  return onmalloc(sz);
}

void ONX_Model::operator delete(void* p)
{
  // ONX_Model delete
  onfree(p);
}

void* ONX_Model::operator new[] (size_t sz)
{
  // ONX_Model array new
  return onmalloc(sz);
}

void ONX_Model::operator delete[] (void* p)
{
  // ONX_Model array delete
  onfree(p);
}

void* ONX_Model::operator new(size_t, void* p)
{
  // ONX_Model placement new
  return p;
}

void ONX_Model::operator delete(void*, void*)
{
  // ONX_Model placement delete
  return;
}

#endif

//
//
////////////////////////////////////////////////////////////////////////////////

class ONX_ModelComponentReferenceLink
{
public:
  ONX_ModelComponentReferenceLink() = default;
  ~ONX_ModelComponentReferenceLink() = default;
  ONX_ModelComponentReferenceLink(const ONX_ModelComponentReferenceLink&) = default;
  ONX_ModelComponentReferenceLink& operator=(const ONX_ModelComponentReferenceLink&) = default;

public:
  // m_mcr in this class is the "first"  std::shared_ptr<ON_ModelComponent> that manages
  // the referenced ON_ModelComponent and is what insures ON_ModelComponent alive inside
  // and ONX_Model for the duration of the model's lifetime.
  //
  // m_sn = ON_ModelComponent.RuntimeSerialNumber() so sn lookup can be safely used to find runtime pointer.
  // When m_mcr.ModelComponent() is not nullptr, then m_sn = m_mcr.ModelComponent()->RuntimeSerialNumber().
  ON_ModelComponentReference m_mcr;
  ON__UINT64 m_sn = 0;
  ONX_ModelComponentReferenceLink* m_next = nullptr;
  ONX_ModelComponentReferenceLink* m_prev = nullptr;
};

enum class RenderContentKinds { Material, Environment, Texture };

ON_3dmObjectAttributes* GetComponentAttributes(const ON_ModelComponent& component)
{
  // To have attributes, the component must be an ON_ModelGeometryComponent.
  const auto* mgc = ON_ModelGeometryComponent::Cast(&component);
  if (nullptr == mgc)
    return nullptr; // Wrong type of component.

  return mgc->ExclusiveAttributes();
}

class ONX_ModelPrivate final
{
public:
  ONX_ModelPrivate(ONX_Model& m);
  ~ONX_ModelPrivate();

  using EmbeddedFileMap = std::unordered_map<std::wstring, std::wstring>;

  bool GetRDKDocumentXML(ON_wString& xml, bool embedded_files, int archive_3dm_version) const;
  ONX_Model_UserData* GetRDKDocumentUserData(int archive_3dm_version) const;
  void PopulateDefaultRDKDocumentXML(ON_XMLRootNode& root) const;
  bool PopulateRDKComponents(int archive_3dm_version);
  bool UpdateRDKUserData(int archive_3dm_version);
  bool CreateRenderContentFromXML(class ON_XMLNode& model_node, RenderContentKinds kind);
  bool CreateXMLFromRenderContent(ON_XMLNode& model_node, RenderContentKinds kind) const;
  bool SetRDKDocumentInformation(const wchar_t* xml, ONX_Model_UserData& docud, int archive_3dm_version) const;
  ON_XMLNode* GetRenderContentSectionNode(ON_XMLNode& model_node, RenderContentKinds kind) const;
  ON_XMLNode* GetPostEffectSectionNode(ON_XMLNode& model_node, ON_PostEffect::Types type) const;
  static void RemoveAllEmbeddedFiles(ONX_Model& model);
  static bool GetEntireRDKDocument(const ONX_Model_UserData& docud, ON_wString& xml, ONX_Model* model);

public:
  ONX_Model& m_model;
  ON__UINT64 m_model_content_version_number = 0;
  ON_ClassArray<ONX_Model::ONX_ModelComponentList> m_mcr_lists;
};

ON_InternalXMLImpl::~ON_InternalXMLImpl()
{
  if (nullptr != _local_node)
  {
    delete _local_node;
    _local_node = nullptr;
  }
}

ON_XMLNode& ON_InternalXMLImpl::Node(void) const
{
  // If the model node pointer is set, return that. This is a pointer to a node owned by the ON_3dmRenderSettings
  // which contains the entire RDK document XML. This is used by objects (Ground Plane, etc.) that are owned by the
  // ON_3dmRenderSettings. In the case of Ground Plane etc, it's a pointer into the ON_3dmRenderSettings XML.
  // In the case of decals, it's a pointer into the decal collection's XML.
  if (nullptr != _model_node)
    return *_model_node;

  // Since the model node is not set, we need a local node to hold the XML. If one has not been created yet,
  // create it. The local node is owned by this object. This case occurs for free-floating copies of model
  // objects and also for free-floating copies of decals and mesh modifiers. This node only contains the XML
  // data that's relevant to the object it's for, not the entire XML, but the object's node is still a child
  // node under the same node hierarchy as if it were the entire XML.
  if (nullptr == _local_node)
    _local_node = new ON_XMLNode(NameOfRootNode());

  return *_local_node;
}

void ON_InternalXMLImpl::SetModelNode(ON_XMLNode& node)
{
  ON_ASSERT(_model_node == nullptr);

  if (nullptr != _local_node)
  {
    delete _local_node;
    _local_node = nullptr;
  }

  _model_node = &node;
}

ON_wString ON_InternalXMLImpl::NameOfRootNode(void) const
{
  return ON_XMLRootNode().TagName();
}

ON_XMLVariant ON_InternalXMLImpl::GetParameter(const wchar_t* path_to_node, const wchar_t* param_name, const ON_XMLVariant& def) const
{
  return InternalGetParameter(path_to_node, param_name, L"", def);
}

ON_XMLVariant ON_InternalXMLImpl::GetParameter_NoType(const wchar_t* path_to_node, const wchar_t* param_name, const wchar_t* default_type, const ON_XMLVariant& def) const
{
  return InternalGetParameter(path_to_node, param_name, default_type, def);
}

ON_XMLVariant ON_InternalXMLImpl::InternalGetParameter(const wchar_t* path_to_node, const wchar_t* param_name, const wchar_t* default_type, const ON_XMLVariant& def) const
{
  std::lock_guard<std::recursive_mutex> lg(_mutex);

  const ON_XMLNode* node_read = Node().GetNodeAtPath(path_to_node);
  if (nullptr == node_read)
    return def;

  ON_XMLVariant value;
  ON_XMLParameters p(*node_read);
  p.SetDefaultReadType(default_type);
  if (!p.GetParam(param_name, value))
    return def;

  return value;
}

bool ON_InternalXMLImpl::SetParameter(const wchar_t* path_to_node, const wchar_t* param_name, const ON_XMLVariant& value)
{
  return InternalSetParameter(path_to_node, param_name, true, value);
}

bool ON_InternalXMLImpl::SetParameter_NoType(const wchar_t* path_to_node, const wchar_t* param_name, const ON_XMLVariant& value)
{
  return InternalSetParameter(path_to_node, param_name, false, value);
}

bool ON_InternalXMLImpl::InternalSetParameter(const wchar_t* path_to_node, const wchar_t* param_name, bool write_type, const ON_XMLVariant& value)
{
  std::lock_guard<std::recursive_mutex> lg(_mutex);

  bool success = false;

  ON_XMLNode* node_write = Node().CreateNodeAtPath(path_to_node);
  if (nullptr != node_write)
  {
    ON_XMLParameters p(*node_write);
    p.SetWriteTypeProperty(write_type);
    if (nullptr != p.SetParam(param_name, value))
      success = true;
  }

  return success;
}

bool ON_InternalXMLImpl::RemoveParameter(const wchar_t* path_to_node, const wchar_t* param_name)
{
  std::lock_guard<std::recursive_mutex> lg(_mutex);

  bool success = false;

  ON_XMLNode* node = Node().GetNodeAtPath(path_to_node);
  if (nullptr != node)
  {
    ON_XMLNode* child = node->GetNamedChild(param_name);
    success = node->RemoveChild(child);
  }

  return success;
}

// ONX_Model

ONX_Model::ONX_Model()
{
  m_private = new ONX_ModelPrivate(*this);

  // Tell the sun in our render settings to use the earth anchor point in our settings.
  m_settings.m_RenderSettings.Sun().UseEarthAnchorPoint(m_settings.m_earth_anchor_point);
}

ONX_Model::~ONX_Model()
{
  Reset();

  delete m_private;
  m_private = nullptr;
}

void ONX_Model::Reset()
{
  m_3dm_file_version = 0;
  m_3dm_opennurbs_version = 0;
  m_sStartSectionComments = ON_String::EmptyString;
  m_properties = ON_3dmProperties::Empty;
  m_settings = ON_3dmSettings::Default;

  for (unsigned int i = 0; i < m_userdata_table.UnsignedCount(); i++)
  {
    delete m_userdata_table[i];
  }
  m_userdata_table.Destroy();

  for (int i = 0; i < m_private->m_mcr_lists.Count(); i++)
  {
    ONX_ModelComponentList& list = m_private->m_mcr_lists[i];

    ONX_ModelComponentReferenceLink* mcr_link = list.m_first_mcr_link;
    while (nullptr != mcr_link)
    {
      mcr_link->m_mcr = ON_ModelComponentReference::Empty;
      mcr_link = mcr_link->m_next;
    }

    list.m_first_mcr_link = nullptr;
    list.m_last_mcr_link = nullptr;
  }
  m_mcr_sn_map.EmptyList();
  m_mcr_link_fsp.ReturnAll();

  m_default_line_pattern = ON_ModelComponentReference::CreateConstantSystemComponentReference(ON_Linetype::Continuous);
  m_default_layer = ON_ModelComponentReference::CreateConstantSystemComponentReference(ON_Layer::Default);
  m_default_text_style = ON_ModelComponentReference::CreateConstantSystemComponentReference(ON_TextStyle::Default);
  m_default_dimension_style = ON_ModelComponentReference::CreateConstantSystemComponentReference(ON_DimStyle::Default);
  
  m_manifest.Reset();

  m_original_to_manifest_map = ON_ManifestMap::Empty;
  m_manifest_to_original_map = ON_ManifestMap::Empty;

  m_model_geometry_bbox = ON_BoundingBox::UnsetBoundingBox;
  m_render_light_bbox = ON_BoundingBox::UnsetBoundingBox;

  if (nullptr != m_model_user_string_list)
  {
    delete m_model_user_string_list;
    m_model_user_string_list = nullptr;
  }
}

void ONX_Model::Internal_ComponentTypeBoundingBox(
  const ON_ModelComponent::Type component_type,
  ON_BoundingBox& bbox
  ) const
{
  if (false == bbox.IsValid())
  {
    ON_BoundingBox local_bbox;
    for (
      const ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(component_type).m_first_mcr_link;
      nullptr != link; 
      link = link->m_next
      )
    {
      const ON_ModelComponent* model_component = link->m_mcr.ModelComponent();
      if (nullptr == model_component)
        continue;
      if (component_type != model_component->ComponentType())
        continue;
      const ON_ModelGeometryComponent* model_geometry = ON_ModelGeometryComponent::Cast(model_component);
      if (nullptr == model_geometry)
        continue;
      const ON_3dmObjectAttributes* attributes = model_geometry->Attributes(nullptr);
      if (nullptr != attributes && attributes->IsInstanceDefinitionObject())
        continue;

      const ON_Geometry* geometry = model_geometry->Geometry(nullptr);
      if (nullptr == geometry)
        continue;

      local_bbox.Union(geometry->BoundingBox());
    }
    bbox = local_bbox;
  }
  return;
}

ON_BoundingBox ONX_Model::ModelGeometryBoundingBox() const
{
  Internal_ComponentTypeBoundingBox(ON_ModelComponent::Type::ModelGeometry,m_model_geometry_bbox);
  return m_model_geometry_bbox;
}

ON_BoundingBox ONX_Model::RenderLightBoundingBox() const
{
  Internal_ComponentTypeBoundingBox(ON_ModelComponent::Type::RenderLight,m_render_light_bbox);
  return m_render_light_bbox;
}

const ON_ComponentManifest& ONX_Model::Manifest() const
{
  return m_manifest;
}

const ON_ManifestMap& ONX_Model::OriginalToModelMap() const
{
  return m_original_to_manifest_map;
}

const ON_ManifestMap& ONX_Model::ModelToOriginalMap() const
{
  return m_manifest_to_original_map;
}

bool ONX_Model::ValdateComponentIdAndName(
  ON_ModelComponent::Type component_type,
  const ON_UUID& candidate_id,
  const ON_UUID& component_parent_id,
  const wchar_t* candidate_name,
  bool bResolveIdConflict,
  bool bResolveNameConflict,
  ON_UUID& model_id,
  ON_wString& model_name
  ) const
{
  for (;;)
  {
    if (false == ON_ModelComponent::ComponentTypeIsValid(component_type))
    {
      ON_ERROR("Invalid component_type parameter.");
      break;
    }

    const bool bIndexRequired = ON_ModelComponent::IndexRequired(component_type);
    const unsigned int count = m_manifest.ComponentIndexLimit(component_type);
    if (bIndexRequired && count >= 0x7FFFFFFFU)
    {
      ON_ERROR("Unable to create model component index.");
      break;
    }
    
    const bool bIdAvailable = m_manifest.IdIsAvailable(candidate_id);
    const bool bCreateId = ON_UuidIsNil(candidate_id) || (false == bIdAvailable && bResolveIdConflict);
    if (false == bIdAvailable && false == bCreateId)
    {
      break;
    }

    ON_wString name(candidate_name);
    name.TrimLeftAndRight();
    const bool bUniqueNameReqired = ON_ModelComponent::UniqueNameRequired(component_type);
    if ( bUniqueNameReqired )
    {
      const ON_UUID name_parent_id
        = ON_ModelComponent::UniqueNameIncludesParent(component_type)
        ? component_parent_id
        : ON_nil_uuid;
      ON_NameHash name_hash = ON_NameHash::Create(name_parent_id, name);
      if (name_hash.IsInvalidNameHash())
      {
        if (false == bResolveNameConflict)
        {
          ON_ERROR("Invalid candidate_name parameter.");
          break;
        }
        name = ON_wString::EmptyString;
        name_hash = ON_NameHash::Create(name_parent_id, name);
      }

      const bool bNameIsValid = name.IsNotEmpty() && m_manifest.NameIsAvailable(component_type, name_hash);
      if (false == bNameIsValid )
      {
        // we need to create a unique and non-empty name
        if (false == bResolveNameConflict)
        {
          // not allowed to modify name
          break;
        }

        name = m_manifest.UnusedName(component_type, component_parent_id, nullptr, name, nullptr, ON_UNSET_UINT_INDEX, nullptr);
        if (name.IsEmpty())
        {
          ON_ERROR("Unable to create component name.");
          break;
        }
      }
    }

    model_id = bCreateId ? ON_CreateId() : candidate_id;
    model_name = name;
    return true;
  }

  model_id = ON_nil_uuid;
  model_name = ON_wString::EmptyString;
  return false;
}

unsigned int ONX_Model::ComponentIndexLimit(
    ON_ModelComponent::Type component_type
    ) const
{
  return m_manifest.ComponentIndexLimit(component_type);
}

unsigned int ONX_Model::ActiveAndDeletedComponentCount(
    ON_ModelComponent::Type component_type
    ) const
{
  return m_manifest.ActiveAndDeletedComponentCount(component_type);
}

unsigned int ONX_Model::ActiveComponentCount(
    ON_ModelComponent::Type component_type
    ) const
{
  return m_manifest.ActiveComponentCount(component_type);
}

unsigned int ONX_Model::DeletedComponentCount(
    ON_ModelComponent::Type component_type
    ) const
{
  return m_manifest.DeletedComponentCount(component_type);
}

ON_ModelComponentReference ONX_Model::ComponentFromIndex(
  ON_ModelComponent::Type component_type,
  int component_model_index
  ) const
{
  if (component_model_index >= 0)
  {
    return ComponentFromUnsignedIndex(component_type,(unsigned int)component_model_index);
  }
  return ON_ModelComponentReference::Empty;
}

ON_ModelComponentReference ONX_Model::ComponentFromUnsignedIndex(
  ON_ModelComponent::Type component_type,
  unsigned int component_model_index
  ) const
{
  ON__UINT64 sn = m_manifest.ItemFromIndex(component_type,component_model_index).ComponentRuntimeSerialNumber();
  ONX_ModelComponentReferenceLink* link = Internal_ModelComponentLinkFromSerialNumber(sn);
  return (nullptr != link)
    ? link->m_mcr
    : ON_ModelComponentReference::Empty;
}

ON_ModelComponentReference ONX_Model::ComponentFromId(
  ON_ModelComponent::Type component_type,
  ON_UUID component_model_id
  ) const
{
  ON__UINT64 sn = m_manifest.ItemFromId(component_type, component_model_id).ComponentRuntimeSerialNumber();
  ONX_ModelComponentReferenceLink* link = Internal_ModelComponentLinkFromSerialNumber(sn);
  return (nullptr != link)
    ? link->m_mcr
    : ON_ModelComponentReference::Empty;
}

const ON_ModelComponentReference& ONX_Model::ComponentFromRuntimeSerialNumber(
  ON__UINT64 runtime_serial_number
) const
{
  ONX_ModelComponentReferenceLink* link = Internal_ModelComponentLinkFromSerialNumber(runtime_serial_number);
  return (nullptr != link)
    ? link->m_mcr
    : ON_ModelComponentReference::Empty;
}

ON_ModelComponentReference ONX_Model::ModelGeometryFromId(
  ON_UUID model_object_id
) const
{
  return ComponentFromId(ON_ModelComponent::Type::ModelGeometry, model_object_id);
}

const ON_ModelGeometryComponent& ONX_Model::ModelGeometryComponentFromId(
  ON_UUID model_object_id
) const
{
  const ON_ModelGeometryComponent* p = ON_ModelGeometryComponent::Cast(ModelGeometryFromId(model_object_id).ModelComponent());
  return (nullptr != p) ? *p : ON_ModelGeometryComponent::Unset;
}

ON_ModelComponentReference ONX_Model::ComponentFromName(
  ON_ModelComponent::Type component_type,
  ON_UUID component_parent_id,
  const wchar_t* component_model_name
  ) const
{
  const ON_UUID name_parent_id 
    = ON_ModelComponent::UniqueNameIncludesParent(component_type)
    ? component_parent_id
    : ON_nil_uuid;
  const bool bIgnoreCase = ON_ModelComponent::UniqueNameIgnoresCase(component_type);
  const ON_NameHash component_model_name_hash = ON_NameHash::Create(name_parent_id,component_model_name,bIgnoreCase);
  return ComponentFromNameHash(component_type,component_model_name_hash);
}

ON_ModelComponentReference ONX_Model::ComponentFromNameHash(
  ON_ModelComponent::Type component_type,
  const ON_NameHash& component_model_name_hash
  ) const
{
  ON__UINT64 sn = m_manifest.ItemFromNameHash(component_type, component_model_name_hash).ComponentRuntimeSerialNumber();
  ONX_ModelComponentReferenceLink* link = Internal_ModelComponentLinkFromSerialNumber(sn);
  return (nullptr != link)
    ? link->m_mcr
    : ON_ModelComponentReference::Empty;
}


ON_ModelComponentReference ONX_Model::ImageFromIndex(
  int image_model_index
  ) const
{
  ON_ModelComponentReference cr = ComponentFromIndex(ON_ModelComponent::Type::Image, image_model_index);
  return cr;
}

ON_ModelComponentReference ONX_Model::ImageFromId(
  ON_UUID image_id
  ) const
{
  ON_ModelComponentReference cr = ComponentFromId(ON_ModelComponent::Type::Image, image_id);
  return cr;
}

ON_ModelComponentReference ONX_Model::ImageFromFileFullPath(
  const wchar_t* image_file_full_path_name
  ) const
{
  ON_FileReference file_reference;
  file_reference.SetFullPath(image_file_full_path_name,false);
  return ImageFromFileReference(file_reference);
}

ON_ModelComponentReference ONX_Model::ImageFromFileContent(
  const ON_ContentHash& image_file_content_hash
  ) const
{
  ON_FileReference file_reference;
  file_reference.SetContentHash(image_file_content_hash);
  return ImageFromFileReference(file_reference);
}

ON_ModelComponentReference ONX_Model::ImageFromFileReference(
  const ON_FileReference& file_reference
  ) const
{
  const ON_wString full_path_name(file_reference.FullPath());
  const bool bCheckFullPath = full_path_name.IsNotEmpty();

  const ON_ContentHash file_content_hash = file_reference.ContentHash();
  const bool bCheckContentHash = file_content_hash.IsSet();
  
  if (false == bCheckFullPath && false == bCheckContentHash)
    return ON_ModelComponentReference::Empty;

  ONX_ModelComponentIterator it(*this,ON_ModelComponent::Type::Image);

  for ( ON_ModelComponentReference cr = it.FirstComponentReference(); false == cr.IsEmpty(); cr = it.NextComponentReference())
  {
    const ON_Bitmap* image = ON_Bitmap::Cast(cr.ModelComponent());
    if (nullptr == image)
      continue;
    const ON_FileReference& image_file_reference = image->FileReference();

    if (bCheckFullPath)
    {
      if (false == full_path_name.EqualPath(image_file_reference.FullPath()))
        continue;
    }

    if (bCheckContentHash)
    {
      if (0 != ON_ContentHash::CompareContent(file_content_hash, image_file_reference.ContentHash()))
        continue;
    }

    return cr;
  }

  return ON_ModelComponentReference::Empty;
}


ON_ModelComponentReference ONX_Model::LinePatternFromIndex(
  int layer_model_index
  ) const
{
  ON_ModelComponentReference cr = ComponentFromIndex(ON_ModelComponent::Type::LinePattern,layer_model_index);
  return cr.IsEmpty() ? m_default_layer : cr;
}

ON_ModelComponentReference ONX_Model::LinePatternFromId(
  ON_UUID layer_model_id
  ) const
{
  ON_ModelComponentReference cr = ComponentFromId(ON_ModelComponent::Type::LinePattern,layer_model_id);
  return cr.IsEmpty() ? m_default_layer : cr;
}

ON_ModelComponentReference ONX_Model::LinePatternFromName(
  const wchar_t* line_pattern_name
  ) const
{
  ON_ModelComponentReference cr = ComponentFromName(ON_ModelComponent::Type::LinePattern,ON_nil_uuid,line_pattern_name);
  return cr.IsEmpty() ? m_default_layer : cr;
}

ON_ModelComponentReference ONX_Model::LinePatternFromNameHash(
    ON_NameHash line_pattern_model_name_hash
    ) const
{
  ON_ModelComponentReference cr = ComponentFromNameHash(ON_ModelComponent::Type::LinePattern,line_pattern_model_name_hash);
  return cr.IsEmpty() ? m_default_layer : cr;
}

ON_ModelComponentReference ONX_Model::LinePatternFromAttributes(
  const ON_3dmObjectAttributes& attributes
  ) const
{
  int line_pattern_index = ON_Linetype::Continuous.Index();

  switch ( attributes.LinetypeSource() )
  {
  case ON::linetype_from_layer:
    if (attributes.m_layer_index >= 0)
    {
      const ON_Layer* layer = ON_Layer::Cast(LayerFromIndex(attributes.m_layer_index).ModelComponent());
      if ( nullptr != layer )
        line_pattern_index = layer->LinetypeIndex();
    }
    break;
  case ON::linetype_from_object:
    line_pattern_index = attributes.m_linetype_index;
    break;
  case ON::linetype_from_parent:
    line_pattern_index = attributes.m_linetype_index;
    // TODO: if object is an instance definition, get linetype
    //       from instance references.
    break;
  }

  return LinePatternFromIndex(line_pattern_index);
}

ON_ModelComponentReference ONX_Model::LinePatternFromLayerIndex(
  int layer_index
) const
{
  ON_ModelComponentReference layer_component = LayerFromIndex(layer_index);
  const ON_Layer* layer = ON_Layer::Cast(layer_component.ModelComponent());
  if (nullptr == layer)
    layer = &ON_Layer::Default;
  return LinePatternFromIndex(layer->m_linetype_index);
}

ON_ModelComponentReference ONX_Model::LayerFromIndex(
  int layer_model_index
  ) const
{
  ON_ModelComponentReference cr = ComponentFromIndex(ON_ModelComponent::Type::Layer,layer_model_index);
  return cr.IsEmpty() ? m_default_layer : cr;
}

ON_ModelComponentReference ONX_Model::LayerFromId(
  ON_UUID layer_model_id
  ) const
{
  ON_ModelComponentReference cr = ComponentFromId(ON_ModelComponent::Type::Layer,layer_model_id);
  return cr.IsEmpty() ? m_default_layer : cr;
}

ON_ModelComponentReference ONX_Model::LayerFromName(
  ON_UUID layer_parent_id,
  const wchar_t* layer_model_name
  ) const
{
  ON_ModelComponentReference cr = ComponentFromName(ON_ModelComponent::Type::Layer,layer_parent_id,layer_model_name);
  return cr.IsEmpty() ? m_default_layer : cr;
}

ON_ModelComponentReference ONX_Model::LayerFromNameHash(
  const ON_NameHash& layer_model_name_hash
  ) const
{
  ON_ModelComponentReference cr = ComponentFromNameHash(ON_ModelComponent::Type::Layer,layer_model_name_hash);
  return cr.IsEmpty() ? m_default_layer : cr;
}

ON_ModelComponentReference ONX_Model::LayerFromAttributes( 
  const ON_3dmObjectAttributes& attributes
  ) const
{
  return LayerFromIndex(attributes.m_layer_index);
}

ON_ModelComponentReference ONX_Model::DimensionStyleFromIndex(
  int dimension_style_model_index
  ) const
{
  ON_ModelComponentReference cr = ComponentFromIndex(ON_ModelComponent::Type::DimStyle,dimension_style_model_index);
  return cr.IsEmpty() ? DefaultDimensionStyle() : cr;
}

ON_ModelComponentReference ONX_Model::DimensionStyleFromId(
  ON_UUID dimension_style_model_id
  ) const
{
  ON_ModelComponentReference cr = ComponentFromId(ON_ModelComponent::Type::DimStyle,dimension_style_model_id);
  return cr.IsEmpty() ? DefaultDimensionStyle() : cr;
}

ON_ModelComponentReference ONX_Model::DimensionStyleFromName(
  const wchar_t* dimension_style_model_name
  ) const
{
  ON_ModelComponentReference cr = ComponentFromName(ON_ModelComponent::Type::DimStyle,ON_nil_uuid,dimension_style_model_name);
  return cr.IsEmpty() ? DefaultDimensionStyle() : cr;
}

ON_ModelComponentReference ONX_Model::DimensionStyleFromNameHash(
  ON_NameHash dimension_style_model_name_hash
  ) const
{
  ON_ModelComponentReference cr = ComponentFromNameHash(ON_ModelComponent::Type::DimStyle,dimension_style_model_name_hash);
  return cr.IsEmpty() ? DefaultDimensionStyle() : cr;
}

ON_UUID ONX_Model::CurrentDimensionStyleId() const
{
  const ON_UUID id = m_settings.CurrentDimensionStyleId();
  if (ON_nil_uuid == id)
    return id;
  if (id == ON_DimStyle::SystemDimstyleFromId(id).Id())
    return id;
  const ON_ModelComponentReference cr = ComponentFromId(ON_ModelComponent::Type::DimStyle,id);
  if (false == cr.IsEmpty())
    return id;
  return ON_nil_uuid;
}

ON_ModelComponentReference ONX_Model::CurrentDimensionStyle() const
{
  return DimensionStyleFromId(CurrentDimensionStyleId());
}

bool ONX_Model::SetCurrentDimensionStyleId(
  ON_UUID dimension_style_id
)
{
  for (;;)
  {
    if (ON_nil_uuid == dimension_style_id)
      break;
    if (dimension_style_id == ON_DimStyle::SystemDimstyleFromId(dimension_style_id).Id())
      break;
    const ON_ModelComponentReference cr = ComponentFromId(ON_ModelComponent::Type::DimStyle,dimension_style_id);
    if ( nullptr != ON_DimStyle::Cast(cr.ModelComponent()) ) 
      break;
    ON_ERROR("Invalid dimension_style_id parameter.");
    return false;
  }
  m_settings.SetCurrentDimensionStyleId(dimension_style_id);
  return true;
}

ON_ModelComponentReference ONX_Model::DefaultDimensionStyle() const
{
  return m_default_dimension_style;
}

static bool Internal_DimStyleHasFont(
  const ON_ModelComponentReference& mcr,
  unsigned int managed_font_sn,
  double model_space_text_scale,
  bool bIgnoreSystemDimStyles
)
{
  for (;;)
  {
    if (0 == managed_font_sn)
      break;
    const ON_DimStyle* dim_style_component = ON_DimStyle::Cast(mcr.ModelComponent());
    if (nullptr == dim_style_component)
      break;
    if (managed_font_sn != dim_style_component->Font().ManagedFontSerialNumber())
      break; // wrong font
    if (bIgnoreSystemDimStyles && dim_style_component->IsSystemComponent())
      break; // no system components
    if (dim_style_component->ParentIdIsNotNil())
      break; // no overrides
    if (model_space_text_scale > 0.0 && !(model_space_text_scale == dim_style_component->DimScale()))
      break;
    return true;
  }
  return false;
}

ON_ModelComponentReference ONX_Model::FirstDimensionStyleFromManagedFontSerialNumber(
  unsigned int managed_font_serial_number,
  double model_space_text_scale,
  bool bIgnoreSystemDimStyles
) const
{
  if (Internal_DimStyleHasFont(m_default_dimension_style, managed_font_serial_number, model_space_text_scale, bIgnoreSystemDimStyles))
    return m_default_dimension_style;

  for (
    ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(ON_ModelComponent::Type::DimStyle).m_first_mcr_link;
    nullptr != link;
    link = link->m_next
    )
  {
    if (Internal_DimStyleHasFont(link->m_mcr, managed_font_serial_number, model_space_text_scale, bIgnoreSystemDimStyles))
      return link->m_mcr;
  }

  return ON_ModelComponentReference::Empty;
}


ON_ModelComponentReference ONX_Model::FirstDimensionStyleFromFont(
  const ON_Font* font,
  double model_space_text_scale,
  bool bIgnoreSystemDimStyles
  ) const
{
  const ON_Font* managed_font
    = (nullptr != font)
    ? font->ManagedFont()
    : nullptr;

  const unsigned int managed_font_sn
    = (nullptr != managed_font)
    ? managed_font->ManagedFontSerialNumber()
    : 0;

  if ( 0 == managed_font_sn )
  {
    ON_ERROR("Invalid font parameter");
    return ON_ModelComponentReference::Empty;
  }

  return FirstDimensionStyleFromManagedFontSerialNumber(managed_font_sn, model_space_text_scale, bIgnoreSystemDimStyles);
}

ON_ModelComponentReference ONX_Model::DimensionStyleWithFontCharacteristics(
  const ON_Font& font_characteristics,
  double model_space_text_scale
)
{
  // search for existing dimension style
  const bool bIgnoreSystemComponents = true;
  ON_ModelComponentReference existing_mcr = this->FirstDimensionStyleFromFont(&font_characteristics, model_space_text_scale, bIgnoreSystemComponents);
  const ON_DimStyle* dim_style = ON_DimStyle::Cast(existing_mcr.ModelComponent());
  if (nullptr != dim_style)
    return existing_mcr;
  
  // create new dimension style
  const ON_DimStyle* default_dim_style = ON_DimStyle::Cast(this->DimensionStyleFromId(this->m_settings.CurrentDimensionStyleId()).ModelComponent());
  ON_DimStyle* new_dim_style = ON_DimStyle::CreateFromFont(&font_characteristics, model_space_text_scale, default_dim_style, &this->Manifest(), nullptr);
  if (nullptr != new_dim_style)
  {
    const bool bResolveIdAndNameConflicts = true;
    return this->AddManagedModelComponent(new_dim_style, bResolveIdAndNameConflicts);
  }

  return ON_ModelComponentReference::Empty;
}


ON_ModelComponentReference ONX_Model::RemoveModelComponent(
  ON_ModelComponent::Type component_type,
  ON_UUID component_id
  )
{
  const ON_ComponentManifestItem item = m_manifest.ItemFromId(component_id);
  if (item.IsUnset())
  {
    ON_ERROR("Invalid component_id parameter.");
    return ON_ModelComponentReference::Empty;
  }
  if (ON_ModelComponent::Type::Unset != component_type && component_type != item.ComponentType())
  {
    ON_ERROR("Invalid model_component type.");
    return ON_ModelComponentReference::Empty;
  }
  if (!m_manifest.RemoveComponent(item.Id()))
  {
    ON_ERROR("Unable to remove component from manifest.");
    return ON_ModelComponentReference::Empty;
  }

  ONX_ModelComponentReferenceLink* mcr_link = Internal_ModelComponentLinkFromSerialNumber(item.ComponentRuntimeSerialNumber());
  if (nullptr == mcr_link)
  {
    ON_ERROR("component not in model.");
    return ON_ModelComponentReference::Empty;
  }
  ON_ModelComponentReference mcr = mcr_link->m_mcr;
  Internal_RemoveModelComponentReferenceLink(mcr_link);
  return mcr;
}


ON_ModelComponentReference ONX_Model::AddManagedModelComponent(
  class ON_ModelComponent* managed_model_component
)
{
  return AddManagedModelComponent(managed_model_component,true);
}

int ONX_Model::AddLayer(
  const wchar_t* layer_name,
  ON_Color layer_color
)
{
  ON_Layer layer;  
  const ON_wString unused_name = m_manifest.UnusedName(layer.ComponentType(), layer.ParentId(), layer_name, nullptr, nullptr, 0, nullptr);
  layer.SetName(unused_name);  
  if ( layer_color != ON_Color::UnsetColor)
    layer.SetColor(layer_color);
  const ON_ModelComponentReference mr = AddModelComponent(layer, true);
  const ON_Layer* managed_layer = ON_Layer::FromModelComponentRef(mr, nullptr);
  int layer_index = (nullptr != managed_layer) ? managed_layer->Index() : ON_UNSET_INT_INDEX;
  if ( layer_index < 0 )
  {
    ON_ERROR("failed to add layer.");
  }
  return layer_index;
}

int ONX_Model::AddDefaultLayer(
  const wchar_t* layer_name,
  ON_Color layer_color
)
{
  ON_UUID default_layer_id = m_settings.CurrentLayerId();
  int default_layer_index = m_settings.CurrentLayerIndex();
  for ( int pass = 0; pass < 2; pass++ )
  {
    if (0 == pass)
    {
      if (ON_nil_uuid == default_layer_id)
        continue;
    }
    else 
    {
      if (ON_UNSET_INT_INDEX == default_layer_index)
        continue;
    }
    ON_ModelComponentReference mcr
      = (0 == pass)
      ? LayerFromId(default_layer_id)
      : LayerFromIndex(default_layer_index);

    const ON_Layer* layer = ON_Layer::FromModelComponentRef(mcr, nullptr);
    if (nullptr == layer)
      continue;
    if (false == layer->IsSystemComponent() && layer->Index() >= 0 && layer->ParentIdIsNil() && layer->IsVisible() && false == layer->IsLocked() )
    {
      m_settings.SetCurrentLayerId(layer->Id());
      return layer->Index();
    }
    ON_Layer default_layer(*layer);
    default_layer.ClearId();
    default_layer.ClearIndex();
    default_layer.ClearParentId();
    default_layer.SetVisible(true);
    default_layer.SetLocked(false);

    if (nullptr == layer_name || 0 == layer_name[0])
      layer_name = layer->NameAsPointer();
    default_layer.SetName(m_manifest.UnusedName(default_layer.ComponentType(), ON_nil_uuid, layer_name, nullptr, nullptr, 0, nullptr) );

    if (ON_Color::UnsetColor != layer_color)
      default_layer.SetColor(layer_color);

    const ON_ModelComponentReference mr = AddModelComponent(default_layer, true);
    const ON_Layer* managed_layer = ON_Layer::FromModelComponentRef(mr, nullptr);
    if (nullptr != managed_layer && managed_layer->Index() >= 0 && false == managed_layer->IsSystemComponent())
    {
      m_settings.SetCurrentLayerId(managed_layer->Id());
      return managed_layer->Index();
    }
  }

  int layer_index = AddLayer(layer_name, layer_color);
  if (layer_index >= 0)
  {
    const ON_ModelComponentReference mr = LayerFromIndex(layer_index);
    const ON_Layer* managed_layer = ON_Layer::FromModelComponentRef(mr, nullptr);
    if (nullptr != managed_layer && managed_layer->Index() >= 0 && false == managed_layer->IsSystemComponent())
    {
      m_settings.SetCurrentLayerId(managed_layer->Id());
      return managed_layer->Index();
    }
  }

  ON_ERROR("Failed to add default layer.");
  return ON_UNSET_INT_INDEX;  
}

int ONX_Model::AddDefaultDimensionStyle(
  const wchar_t* dimension_style_name,
  ON::LengthUnitSystem length_unit_system,
  double model_tolerance
)
{
  const ON_DimStyle* source_dimstyle = nullptr;

  ON_UUID dimstyle_id = m_settings.CurrentDimensionStyleId();
  if (ON_nil_uuid != dimstyle_id)
  {
    const ON_DimStyle* dimstyle = ON_DimStyle::FromModelComponentRef(DimensionStyleFromId(dimstyle_id),nullptr);
    if ( nullptr != dimstyle && dimstyle->ParentIdIsNil() )
    {
      if ( dimstyle->Index() < 0 || dimstyle->IsSystemComponent() )
        source_dimstyle = dimstyle;
      else
        return dimstyle->Index();
    }
    else
    {
      source_dimstyle = &ON_DimStyle::SystemDimstyleFromId(dimstyle_id);
      if (dimstyle_id != source_dimstyle->Id())
        source_dimstyle = nullptr;
    }
  }

  if (nullptr == source_dimstyle)
  {
    bool bIsMetricLengthUnit = false;
    bool bIsUnitedStatesLengthUnit = false;
    for (int pass = 0; pass < 3; pass++)
    {
      if (1 == pass)
        length_unit_system = m_settings.m_ModelUnitsAndTolerances.m_unit_system.UnitSystem();
      else if (pass > 1)
        length_unit_system = ON_3dmSettings::Default.m_ModelUnitsAndTolerances.m_unit_system.UnitSystem();
      bIsMetricLengthUnit = ON::IsMetricLengthUnit(length_unit_system);
      bIsUnitedStatesLengthUnit = bIsMetricLengthUnit ? false : ON::IsUnitedStatesCustomaryLengthUnit(length_unit_system);
      if (bIsMetricLengthUnit || bIsUnitedStatesLengthUnit)
        break;
    }
    for (int pass = 0; pass < 2; pass++)
    {
      if ( model_tolerance > 0.0 )
        break;
      if (1 == pass)
        model_tolerance = m_settings.m_ModelUnitsAndTolerances.m_absolute_tolerance;
      else if (pass > 1)
        model_tolerance = ON_3dmSettings::Default.m_ModelUnitsAndTolerances.m_absolute_tolerance;
    }

    const ON_DimStyle* system_dimstyle = nullptr;
    if (bIsMetricLengthUnit)
    {
      double meters_per_unit = ON::UnitScale(length_unit_system, ON::LengthUnitSystem::Meters);
      double tolerance_mm
        = model_tolerance > 0.0
        ? model_tolerance*ON::UnitScale(length_unit_system, ON::LengthUnitSystem::Millimeters)
        : 0.0;
      system_dimstyle =
        (tolerance_mm <= 1.0 || meters_per_unit < 1.0)
        ? &ON_DimStyle::DefaultMillimeterSmall
        : &ON_DimStyle::DefaultMillimeterLarge;
    }
    else if (bIsUnitedStatesLengthUnit)
    {
      system_dimstyle =
        (ON::LengthUnitSystem::Feet == length_unit_system)
        ? &ON_DimStyle::DefaultFootInchArchitecture
        : &ON_DimStyle::DefaultInchDecimal;
    }
    else
    {
      system_dimstyle = &ON_DimStyle::Default;
    }

    source_dimstyle = system_dimstyle;
  }

  ON_DimStyle* default_dimstyle = new ON_DimStyle(*source_dimstyle);
  default_dimstyle->ClearIndex();
  default_dimstyle->ClearParentId();
  default_dimstyle->SetId();
  default_dimstyle->SetName(m_manifest.UnusedName(*default_dimstyle));

  ON_ModelComponentReference mcr = AddManagedModelComponent(default_dimstyle, true);
  const ON_DimStyle* model_dimstyle = ON_DimStyle::FromModelComponentRef(mcr,nullptr);
  if (nullptr == model_dimstyle)
  {
    ON_ERROR("Failed to add default dimstyle.");
    return ON_UNSET_INT_INDEX;
  }
  m_settings.SetCurrentDimensionStyleId(model_dimstyle->Id());
  return model_dimstyle->Index();
}

ON_ModelComponentReference ONX_Model::AddManagedModelComponent(
  class ON_ModelComponent* managed_model_component,
  bool bResolveIdAndNameConflicts
)
{
  const bool bManagedComponent = true;
  const bool bUpdateComponentIdentification = true;
  return AddModelComponentForExperts(managed_model_component, bManagedComponent, bResolveIdAndNameConflicts, bUpdateComponentIdentification);
}


ON_ModelComponentReference ONX_Model::AddModelComponent(
  const class ON_ModelComponent& model_component
)
{
  return AddModelComponent(model_component, true);
}

ON_ModelComponentReference ONX_Model::AddModelComponent(
  const class ON_ModelComponent& model_component,
  bool bResolveIdAndNameConflicts
  )
{
  const ON_ModelComponent::Type component_type = model_component.ComponentType();
  if (!ON_ModelComponent::ComponentTypeIsValidAndNotMixed(component_type))
  {
    ON_ERROR("Invalid model_component parameter.");
    return ON_ModelComponentReference::Empty;
  }

  ON_UUID id;
  ON_wString name;
  if (false == ValdateComponentIdAndName(component_type, model_component.Id(), model_component.ParentId(), model_component.Name(), bResolveIdAndNameConflicts, bResolveIdAndNameConflicts, id, name))
  {
    ON_ERROR("Invalid model_component id or name.");
    return ON_ModelComponentReference::Empty;
  }
  
  ON_ModelComponent* candidate_model_component = nullptr;
  if (ON_ModelComponent::Type::RenderLight   == component_type ||
      ON_ModelComponent::Type::ModelGeometry == component_type)
  {
    const ON_ModelGeometryComponent* model_geometry = ON_ModelGeometryComponent::Cast(&model_component);   
    if (nullptr != model_geometry)
    {
      const ON_Geometry* geometry = model_geometry->Geometry(nullptr);
      candidate_model_component = ON_ModelGeometryComponent::Create(*geometry, model_geometry->Attributes(nullptr), nullptr);
    }
  }
  else
  {
    // Something simple like ON_Layer, ON_DimStyle, ON_RenderContent, etc
    candidate_model_component = model_component.Duplicate();
  }

  bool bManagedComponent = true;
  bool bUpdateComponentIdentification = true;
  return Internal_AddModelComponent(candidate_model_component, id, model_component.ParentId(), name, bManagedComponent, bUpdateComponentIdentification);
}

ON_ModelComponentReference ONX_Model::AddModelComponentForExperts(
  ON_ModelComponent* model_component,
  bool bManagedComponent,
  bool bResolveIdAndNameConflicts,
  bool bUpdateComponentIdentification
  )
{
  if (nullptr == model_component)
  {
    ON_ERROR("model_component parameter is nullptr.");
    return ON_ModelComponentReference::Empty;
  }

  const ON_ModelComponent::Type component_type = model_component->ComponentType();
  if (!ON_ModelComponent::ComponentTypeIsValidAndNotMixed(component_type))
  {
    ON_ERROR("Invalid model_component->ComponentType() value.");
    return ON_ModelComponentReference::Empty;
  }

  const ON_UUID parent_id = model_component->ParentId();
  ON_UUID id = ON_nil_uuid;
  ON_wString name;
  if (false == ValdateComponentIdAndName(component_type, model_component->Id(), parent_id, model_component->Name(), bResolveIdAndNameConflicts, bResolveIdAndNameConflicts && bUpdateComponentIdentification, id, name))
  {
    ON_ERROR("Invalid model_component id or name.");
    return ON_ModelComponentReference::Empty;
  }

  return Internal_AddModelComponent(model_component, id, parent_id, name, bManagedComponent, bUpdateComponentIdentification);
}

ON_ModelComponentReference ONX_Model::AddModelGeometryComponentForExperts(
  bool bManageGeometry,
  class ON_Object* geometry_object,
  bool bManageAttributes,
  class ON_3dmObjectAttributes* attributes,
  bool bResolveIdAndNameConflicts
  )
{
  if ( nullptr == ON_Geometry::Cast(geometry_object) )
  {
    ON_ERROR("Invalid geometry_object parameter.");
    return ON_ModelComponentReference::Empty;
  }

  if (nullptr == attributes)
  {
    bManageAttributes = true;
    bResolveIdAndNameConflicts = true;
    ON_Light* light = ON_Light::Cast(geometry_object);
    if (nullptr != light
      && ON_nil_uuid != light->m_light_id 
      && false == m_manifest.IdIsAvailable(light->m_light_id)
      )
    {
      light->m_light_id = ON_nil_uuid;
    }
    const ON_Layer* default_layer
      = (ON_nil_uuid == this->m_settings.CurrentLayerId())
      ? nullptr
      : ON_Layer::FromModelComponentRef(LayerFromId(m_settings.CurrentLayerId()),nullptr);
    if (nullptr == default_layer)
    {
      ONX_ModelComponentIterator layer_it(*this, ON_ModelComponent::Type::Layer);
      for (const ON_Layer* layer = ON_Layer::Cast(layer_it.FirstComponent()); nullptr != layer; layer = ON_Layer::Cast(layer_it.NextComponent()) )
      {
        if (layer->IsVisible() && false == layer->IsLocked() && layer->ParentIdIsNil())
        {
          default_layer = layer;
          break;
        }
      }
    }

    attributes = new ON_3dmObjectAttributes();
    if (nullptr != light)
    {
      attributes->m_uuid = light->m_light_id;
      attributes->m_name = light->m_light_name;
    }
    attributes->m_layer_index
      = (nullptr == default_layer)
      ? ON_Layer::Default.Index()
      : default_layer->Index();
  }
  else if ( ON_nil_uuid != attributes->m_uuid && false == m_manifest.IdIsAvailable(attributes->m_uuid))
  {
    if (bResolveIdAndNameConflicts)
      attributes->m_uuid = ON_nil_uuid;
    else
    {
      ON_ERROR("attributes->m_uuid is not valid or is in use.");
      return ON_ModelComponentReference::Empty;
    }
  }

  ON_ModelGeometryComponent* model_geometry_component = ON_ModelGeometryComponent::CreateForExperts(
    bManageGeometry,
    geometry_object,
    bManageAttributes,
    attributes,
    nullptr
  );

  if ( nullptr == model_geometry_component )
    return ON_ModelComponentReference::Empty;

  ON_ModelComponentReference model_component_reference = AddManagedModelComponent(model_geometry_component, bResolveIdAndNameConflicts);

  if (model_component_reference.IsEmpty())
    delete model_geometry_component;

  return model_component_reference;
}


ON_ModelComponentReference ONX_Model::AddModelGeometryComponent(
  const class ON_Object* geometry_object,
  const class ON_3dmObjectAttributes* attributes
)
{
  return AddModelGeometryComponent(geometry_object, attributes, true);
}

ON_ModelComponentReference ONX_Model::AddModelGeometryComponent(
  const class ON_Object* geometry_object,
  const class ON_3dmObjectAttributes* attributes,
  bool bResolveIdAndNameConflicts
  )
{
  if ( nullptr == ON_Geometry::Cast(geometry_object) )
  {
    ON_ERROR("Invalid geometry_object parameter.");
    return ON_ModelComponentReference::Empty;
  }

  ON_UUID id = ON_nil_uuid;
  if (nullptr != attributes && ON_nil_uuid != attributes->m_uuid )
  {
    if (m_manifest.IdIsAvailable(attributes->m_uuid))
      id = attributes->m_uuid;
    else if (false == bResolveIdAndNameConflicts)
    {
      ON_ERROR("attributes->m_uuid is invalid or in use in this model.");
      return ON_ModelComponentReference::Empty;
    }
  }

  ON_3dmObjectAttributes* managed_attributes = nullptr;
  ON_Object* managed_geometry_object = geometry_object->Duplicate();
  if (nullptr != attributes)
  {
    managed_attributes = new ON_3dmObjectAttributes(*attributes);
    managed_attributes->m_uuid = id;
  }

  const bool bManageGeometry = true;
  const bool bManageAttributes = true;
  return AddModelGeometryComponentForExperts(
    bManageGeometry,
    managed_geometry_object,
    bManageAttributes,
    managed_attributes,
    bResolveIdAndNameConflicts
  );
}


ON_ModelComponentReference ONX_Model::AddManagedModelGeometryComponent(
  class ON_Object* managed_geometry_object,
  class ON_3dmObjectAttributes* managed_attributes
)
{
  return AddManagedModelGeometryComponent(managed_geometry_object, managed_attributes, true);
}

ON_ModelComponentReference ONX_Model::AddManagedModelGeometryComponent(
  class ON_Object* managed_geometry_object,
  class ON_3dmObjectAttributes* managed_attributes,
  bool bResolveIdAndNameConflicts
)
{
  if ( nullptr == ON_Geometry::Cast(managed_geometry_object) )
  {
    ON_ERROR("Invalid managed_geometry_object parameter.");
    return ON_ModelComponentReference::Empty;
  }
  const bool bManageGeometry = true;
  const bool bManageAttributes = true;
  return AddModelGeometryComponentForExperts(
    bManageGeometry,
    managed_geometry_object,
    bManageAttributes,
    managed_attributes,
    bResolveIdAndNameConflicts
  );
}

ONX_ModelComponentReferenceLink* ONX_Model::Internal_ModelComponentLinkFromSerialNumber(
  ON__UINT64 model_component_runtime_serial_number
  ) const
{
  const struct ON_SerialNumberMap::SN_ELEMENT* e = m_mcr_sn_map.FindSerialNumber(model_component_runtime_serial_number);
  return (ONX_ModelComponentReferenceLink*)((nullptr != e) ? e->m_value.m_u.ptr : nullptr);
}

ONX_ModelComponentReferenceLink* ONX_Model::Internal_AddModelComponentReference(
  ON_ModelComponentReference mcr
  )
{
  const ON_ModelComponent* model_component = mcr.ModelComponent();
  if (nullptr == model_component)
  {
    ON_ERROR("Invalid mcr parameter - mcr.ModelComponent() is nullptr.");
    return nullptr;
  }

  const ON_ModelComponent::Type component_type = model_component->ComponentType();
  if (ON_ModelComponent::Type::Unset == component_type || ON_ModelComponent::Type::Mixed == component_type)
  {
    ON_ERROR("Invalid component type");
    return nullptr;
  }
  
  ONX_ModelComponentReferenceLink* mcr_link = Internal_ModelComponentLinkFromSerialNumber(model_component->RuntimeSerialNumber());
  if (nullptr != mcr_link)
  {
    // This component was already added.
    return mcr_link;
  }

  struct ON_SerialNumberMap::SN_ELEMENT* e = m_mcr_sn_map.AddSerialNumber(model_component->RuntimeSerialNumber());
  if (nullptr == e)
  {
    ON_ERROR("m_mcr_sn_map.AddSerialNumber(model_component->RuntimeSerialNumber()) failed.");
    return nullptr;
  }

  if ( 0 == m_mcr_link_fsp.SizeofElement())
    m_mcr_link_fsp.Create(sizeof(*mcr_link),0,0);

  e->m_value.m_u.ptr = m_mcr_link_fsp.AllocateDirtyElement();
    
  mcr_link = new(e->m_value.m_u.ptr) ONX_ModelComponentReferenceLink();
  mcr_link->m_mcr = mcr;

  ONX_Model::ONX_ModelComponentList& list = Internal_ComponentList( component_type );
  if (component_type != list.m_component_type)
  {
    ON_ERROR("Internal_ComponentList(component_type) failed");
  }
  else
  {
    if (nullptr == list.m_first_mcr_link)
    {
      list.m_first_mcr_link = mcr_link;
      mcr_link->m_prev = nullptr;
    }
    else
    {
      mcr_link->m_prev = list.m_last_mcr_link;
      list.m_last_mcr_link->m_next = mcr_link;
    }
    mcr_link->m_next = nullptr;
    list.m_last_mcr_link = mcr_link;

    list.m_count++;
  }

  return mcr_link;
}


void ONX_Model::Internal_RemoveModelComponentReferenceLink(
class ONX_ModelComponentReferenceLink* mcr_link
  )
{
  if (nullptr == mcr_link)
    return;

  const ON_ModelComponent* model_component = mcr_link->m_mcr.ModelComponent();

  if ( nullptr == model_component )
    return;

  m_mcr_sn_map.RemoveSerialNumberAndId(model_component->ReferenceModelSerialNumber());

  mcr_link->m_mcr = ON_ModelComponentReference::Empty;

  ONX_Model::ONX_ModelComponentList& list = Internal_ComponentList(model_component->ComponentType());
  if (list.m_count > 0)
  {
    if (mcr_link->m_prev)
      mcr_link->m_prev->m_next = mcr_link->m_next;
    else
      list.m_first_mcr_link = mcr_link->m_next;
    if (mcr_link->m_next)
      mcr_link->m_next->m_prev = mcr_link->m_prev;
    else
      list.m_last_mcr_link = mcr_link->m_prev;
    list.m_count--;
  }

  mcr_link->m_prev = nullptr;
  mcr_link->m_next = nullptr;

  m_mcr_link_fsp.ReturnElement(mcr_link);
}

ONX_Model::ONX_ModelComponentList& ONX_Model::Internal_ComponentList(
  ON_ModelComponent::Type component_type
  )
{
  const int i = static_cast<unsigned int>(component_type);
  return
    (i < ONX_Model::m_private->m_mcr_lists.Count())
    ? m_private->m_mcr_lists[i]
    : m_private->m_mcr_lists[0];
}

const ONX_Model::ONX_ModelComponentList& ONX_Model::Internal_ComponentListConst(
  ON_ModelComponent::Type component_type
  ) const
{
  const int i = static_cast<unsigned int>(component_type);
  return
    (i < ONX_Model::m_private->m_mcr_lists.Count())
    ? m_private->m_mcr_lists[i]
    : m_private->m_mcr_lists[0];
}

ON_ModelComponentReference ONX_Model::Internal_AddModelComponent(
  ON_ModelComponent* model_component,
  ON_UUID id,
  ON_UUID name_parent_id,
  const ON_wString& name,
  bool bManagedComponent,
  bool bUpdateComponentIdentification
  )
{
  for (;;)
  {
    if (nullptr == model_component)
    {
      ON_ERROR("Invalid model_component parameter.");
      break;
    }

    if (model_component->IsSystemComponent())
    {
      ON_ERROR("Invalid model_component parameter.");
      break;
    }
    
    const ON_ModelComponent::Type component_type = model_component->ComponentType();
    if (!ON_ModelComponent::ComponentTypeIsValidAndNotMixed(component_type))
    {
      ON_ERROR("Invalid model_component parameter.");
      break;
    }

    const int original_index = model_component->Index();
    const ON_UUID original_id = model_component->Id();
    const bool bIsEmbeddedFileReference = (ON_ModelComponent::Type::Image == component_type);
    const ON_Bitmap* embedded_file
      = bIsEmbeddedFileReference
      ? ON_Bitmap::Cast(model_component)
      : nullptr;

    const ON_NameHash original_name_hash 
      = bIsEmbeddedFileReference
      ? (nullptr == embedded_file ? ON_NameHash::UnsetNameHash : ON_NameHash::CreateFilePathHash(embedded_file->FileReference()) )
      : model_component->NameHash();

    const ON_NameHash name_hash 
      = bIsEmbeddedFileReference
      ? original_name_hash
      : ON_NameHash::Create(name_parent_id,name,ON_ModelComponent::UniqueNameIgnoresCase(component_type));

    int manifest_item_index = ON_UNSET_INT_INDEX;
    const bool bIndexRequired = ON_ModelComponent::IndexRequired(component_type);
    if (bIndexRequired)
    {
      manifest_item_index = m_manifest.ComponentIndexLimit(component_type);
      if (manifest_item_index >= 0x7FFFFFFF && bUpdateComponentIdentification)
      {
        ON_ERROR("Unable to set model_component_index.");
        break;
      }
    }
    const bool bUpdateIndex = (bUpdateComponentIdentification && bIndexRequired && original_index != (int)manifest_item_index);
    const bool bUpdateId = (bUpdateComponentIdentification && !(original_id == id));
    const bool bUpdateName = (false == bIsEmbeddedFileReference && bUpdateComponentIdentification && original_name_hash != name_hash);

    if (bUpdateIndex && model_component->IndexIsLocked())
    {
      ON_ERROR("Unable to set component index.");
      break;
    }
    if (bUpdateId && model_component->IdIsLocked())
    {
      ON_ERROR("Unable to set component id.");
      break;
    }
    if (bUpdateName && model_component->NameIsLocked())
    {
      ON_ERROR("Unable to set component name.");
      break;
    }

    if (bUpdateIndex && false == model_component->SetIndex((int)manifest_item_index))
    {
      ON_ERROR("model_component->SetIndex(...) failed.");
      break;
    }
    if(bUpdateId && false == model_component->SetId(id) )
    {
      ON_ERROR("model_component->SetId(...) failed.");
      break;
    }
    if(bUpdateName && false == model_component->SetName(name) )
    {
      ON_ERROR("model_component->SetName(...) failed.");
      break;
    }

    if (bUpdateComponentIdentification)
    {
      ON_ModelGeometryComponent* geometry_component = ON_ModelGeometryComponent::Cast(model_component);
      if (nullptr != geometry_component)
      {
        const ON_Light* light = ON_Light::Cast(geometry_component->Geometry(nullptr));
        if (nullptr != light)
        {
          if (id != light->m_light_id)
            const_cast<ON_Light*>(light)->m_light_id = id;
          if (name != light->m_light_name)
            const_cast<ON_Light*>(light)->m_light_name = name;
        }
        const ON_3dmObjectAttributes* attributes = geometry_component->Attributes(nullptr);
        if (nullptr != attributes)
        {
          if (id != attributes->m_uuid)
            const_cast<ON_3dmObjectAttributes*>(attributes)->m_uuid = id;
          if (name != attributes->m_name)
            const_cast<ON_3dmObjectAttributes*>(attributes)->m_name = name;
        }
      }
    }

    Internal_IncrementModelContentVersionNumber();

    const class ON_ComponentManifestItem& manifest_item = m_manifest.AddComponentToManifest(
      model_component->ComponentType(),
      model_component->RuntimeSerialNumber(),
      id,
      name_hash
      );
    
    if (manifest_item.IsUnset())
    {
      ON_ERROR("Unable to update model manifest.");
      break;
    }

    ON_ManifestMapItem original_to_manifest;
    if ( original_to_manifest.SetSourceIdentification(model_component) && original_to_manifest.SetDestinationIdentification(&manifest_item))
    {
      m_original_to_manifest_map.AddMapItem(original_to_manifest);
    }

    ON_ManifestMapItem manifest_to_original;
    if ( manifest_to_original.SetSourceIdentification(&manifest_item) && manifest_to_original.SetDestinationIdentification(model_component) )
    {
      m_manifest_to_original_map.AddMapItem(manifest_to_original);
    }

    if (bIndexRequired)
    {
      if (model_component->Index() != manifest_item.Index())
      {
        ON_ERROR("Unexpected manifest_item_index value.");
        if (bUpdateIndex && false == model_component->SetIndex((int)(manifest_item_index)))
        {
          ON_ERROR("model_component->SetIndex(...) failed.");
          break;
        }
      }
    }
    else
    {
      if (ON_ComponentManifest::UnsetComponentIndex != model_component->Index() )
      {
        ON_ERROR("Unexpected model_component->Index() value.");
        if (bUpdateIndex && false == model_component->SetIndex(ON_ComponentManifest::UnsetComponentIndex))
        {
          ON_ERROR("model_component->SetIndex(...) failed.");
          break;
        }
      }
      if ( ON_UNSET_INT_INDEX != manifest_item.Index() )
      {
        ON_ERROR("Unexpected manifest_item_index value.");
      }
    }

    if (ON_ModelComponent::Type::ModelGeometry == model_component->ComponentType())
    {
      ON_ModelGeometryComponent* model_geometry = ON_ModelGeometryComponent::Cast(model_component);
      if (nullptr != model_geometry)
      {
        // TEMPORARY - until the id and name can be removed from ON_3dmObjectAttributes,
        // they need to be synchronized with the ones on ON_ModelGeometryComponent.
        ON_3dmObjectAttributes* attributes = const_cast< ON_3dmObjectAttributes* >(model_geometry->Attributes(nullptr));
        if (nullptr != attributes)
        {
          if ( bUpdateId )
            attributes->m_uuid = model_geometry->Id();
          if (bUpdateName)
            attributes->m_name = model_geometry->Name();
        }
      }
    }
    
    if (bUpdateComponentIdentification)
    {
      // continue even when UpdateReferencedComponents() returns false
      model_component->UpdateReferencedComponents(ON_ComponentManifest::Empty,m_manifest,m_original_to_manifest_map);
    }

    ON_ModelComponentReference model_component_reference = ON_ModelComponentReference::CreateForExperts(model_component,bManagedComponent);
    Internal_AddModelComponentReference(model_component_reference);
    return model_component_reference;
  }

  return ON_ModelComponentReference::Empty;
}

/* ON_DEPRECATED */ ON_ModelComponentReference ONX_Model::RenderMaterialFromAttributes(const ON_3dmObjectAttributes& attr) const
{
  return MaterialFromAttributes(attr);
}

/* ON_DEPRECATED */ ON_ModelComponentReference ONX_Model::RenderMaterialFromLayerIndex(int index) const
{
  return MaterialFromLayerIndex(index);
}

/* ON_DEPRECATED */ ON_ModelComponentReference ONX_Model::RenderMaterialFromIndex(int index) const
{
  return MaterialFromIndex(index);
}

/* ON_DEPRECATED */ ON_ModelComponentReference ONX_Model::RenderMaterialFromId(ON_UUID id) const
{
  return MaterialFromId(id);
}

ON_ModelComponentReference ONX_Model::MaterialFromAttributes(
  const ON_3dmObjectAttributes& attributes
  ) const
{
  switch ( attributes.MaterialSource() )
  {
  case ON::material_from_layer:
    return MaterialFromLayerIndex( attributes.m_layer_index );
    break;

  case ON::material_from_object:
    return MaterialFromIndex( attributes.m_material_index );
    break;

  case ON::material_from_parent:
    // TODO: If object is an idef, get material from iref attributes.
    return MaterialFromIndex( attributes.m_material_index );
    break;
  }

  return m_default_render_material;
}

ON_ModelComponentReference ONX_Model::MaterialFromLayerIndex(
  int layer_index
  ) const
{
  int material_index = ON_Layer::FromModelComponentRef(
    LayerFromIndex(layer_index),
    &ON_Layer::Default
    )->RenderMaterialIndex();
  return MaterialFromIndex(material_index);
}

ON_ModelComponentReference ONX_Model::MaterialFromIndex(
  int material_index
  ) const
{
  ON_ModelComponentReference cr = ComponentFromIndex(ON_ModelComponent::Type::Material, material_index);
  return cr.IsEmpty() ? m_default_render_material : cr;
}

ON_ModelComponentReference ONX_Model::MaterialFromId(
  ON_UUID material_id
  ) const
{
  ON_ModelComponentReference cr = ComponentFromId(ON_ModelComponent::Type::Material, material_id);
  return cr.IsEmpty() ? m_default_render_material : cr;
}

ON_Color ONX_Model::WireframeColorFromAttributes(
  const ON_3dmObjectAttributes& attributes
  ) const
{
  ON_Color color = ON_UNSET_COLOR;

  switch ( attributes.ColorSource() )
  {
  case ON::color_from_layer:
    color = ON_Layer::FromModelComponentRef( LayerFromIndex(attributes.m_layer_index), &ON_Layer::Default )->Color();
    break;

  case ON::color_from_object:
    color = attributes.m_color;
    break;

  case ON::color_from_material:
    color = ON_Material::FromModelComponentRef( MaterialFromAttributes(attributes), &ON_Material::Default)->Diffuse();
    break;

  case ON::color_from_parent:
    color = attributes.m_color;
    // TODO: if object is an instance definition, get color
    //       from instance references.
    break;
  }

  if ( color == ON_UNSET_COLOR )
    color.SetRGB(128,128,128);

  return color;
}

void ONX_Model::DumpSummary( ON_TextLog& dump ) const
{
  dump.Print("File version: %u\n",m_3dm_file_version);
  if (false == dump.IsTextHash())
  {
    dump.Print("File openNURBS version: %u\n", m_3dm_opennurbs_version);
    if (m_3dm_file_byte_count > 0)
      dump.Print("File length: %llu bytes\n", m_3dm_file_byte_count);

    if (m_sStartSectionComments.Length() > 0)
    {
      dump.Print("Start section comments:\n");
      dump.PushIndent();
      dump.PrintWrappedText(static_cast<const char*>(m_sStartSectionComments));
      dump.PopIndent();
      dump.Print("\n");
    }
  
    m_properties.Dump(dump);

    dump.Print("\n");
  }

  m_settings.Dump(dump);

  dump.Print("\n");

  dump.Print("Contents:\n");
  dump.PushIndent();
  dump.Print("%u embedded images\n",Internal_ComponentListConst(ON_ModelComponent::Type::Image).m_count);
  dump.Print("%u materials\n",Internal_ComponentListConst(ON_ModelComponent::Type::RenderMaterial).m_count);
  dump.Print("%u line patterns\n",Internal_ComponentListConst(ON_ModelComponent::Type::LinePattern).m_count);
  dump.Print("%u text styles\n",Internal_ComponentListConst(ON_ModelComponent::Type::TextStyle).m_count);
  dump.Print("%u annotation styles\n",Internal_ComponentListConst(ON_ModelComponent::Type::DimStyle).m_count);
  dump.Print("%u hatch patterns\n",Internal_ComponentListConst(ON_ModelComponent::Type::HatchPattern).m_count);
  dump.Print("%u layers\n",Internal_ComponentListConst(ON_ModelComponent::Type::Layer).m_count);
  dump.Print("%u groups\n",Internal_ComponentListConst(ON_ModelComponent::Type::Group).m_count);
  dump.Print("%u lights\n",Internal_ComponentListConst(ON_ModelComponent::Type::RenderLight).m_count);
  dump.Print("%u model geometry objects\n",Internal_ComponentListConst(ON_ModelComponent::Type::ModelGeometry).m_count);
  if (false == dump.IsTextHash())
  {
    dump.Print("%u user data objects\n", m_userdata_table.UnsignedCount());
  }
  dump.PopIndent();
}

void ONX_Model::DumpComponentList( 
  ON_ModelComponent::Type component_type,
  ON_TextLog& text_log
  ) const
{
  const ON_wString type_name_string = ON_ModelComponent::ComponentTypeToString(component_type);
  const wchar_t* type_name = static_cast<const wchar_t*>(type_name_string);
  unsigned int i = 0;
  for ( 
    const ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(component_type).m_first_mcr_link;
    nullptr != link;
    link = link->m_next
    )
  {
    text_log.Print(L"%ls %d:\n",type_name,i);
    const ON_ModelComponent* model_component = link->m_mcr.ModelComponent();
  text_log.PushIndent();
    if ( nullptr == model_component )
      text_log.Print(L"nullptr\n");
    else
      model_component->Dump(text_log);
    link->m_mcr.ModelComponent();
    text_log.PopIndent();
    i++;
  }
}

void ONX_Model::DumpUserDataTable( ON_TextLog& dump) const
{
  int i;
  for ( i = 0; i < m_userdata_table.Count(); i++ )
  {
    const ONX_Model_UserData* ud = m_userdata_table[i];
    if ( nullptr == ud)
      continue;
    dump.Print("User Data Table %d:\n",i);
    dump.PushIndent();
    dump.Print("uuid = "); dump.Print(ud->m_uuid); dump.Print("\n");
    ud->m_goo.Dump(dump);    
    dump.PopIndent();
  }
}


void ONX_Model::Dump(ON_TextLog& dump) const
{
  dump.Print("Model summary:\n");
  dump.PushIndent();
  DumpSummary(dump);
  dump.PopIndent();

  dump.PrintNewLine();
  DumpComponentLists(dump);

  if ( false == dump.IsTextHash() )
  {
    dump.Print("User data table:\n");
    dump.PushIndent();
    DumpUserDataTable(dump);
    dump.PopIndent();
    dump.PrintNewLine();
  }
}

void ONX_Model::DumpComponentLists( ON_TextLog& dump ) const
{
  const ON_ModelComponent::Type table_types[] =
  {
    ON_ModelComponent::Type::Image,
    ON_ModelComponent::Type::TextureMapping,
    ON_ModelComponent::Type::Material,
    ON_ModelComponent::Type::LinePattern,
    ON_ModelComponent::Type::Layer,
    ON_ModelComponent::Type::Group,
    ON_ModelComponent::Type::TextStyle,
    ON_ModelComponent::Type::DimStyle,
    ON_ModelComponent::Type::RenderLight,
    ON_ModelComponent::Type::HatchPattern,
    ON_ModelComponent::Type::ModelGeometry,
    ON_ModelComponent::Type::HistoryRecord,
    ON_ModelComponent::Type::RenderContent,
    ON_ModelComponent::Type::EmbeddedFile,
    //ON_ModelComponent::Type::ObsoleteValue,
    ON_ModelComponent::Type::SectionStyle,
    ON_ModelComponent::Type::Unset // list terminator
  };

  for (unsigned i = 0; ON_ModelComponent::Type::Unset != table_types[i]; i++)
  {
    ON_wString type_name = ON_ModelComponent::ComponentTypeToString(table_types[i]);
    dump.Print(L"%ls table:\n",static_cast<const wchar_t*>(type_name));
    dump.PushIndent();
    DumpComponentList(table_types[i],dump);
    dump.PopIndent();
    dump.Print("\n");
  }
}

ON_SHA1_Hash ONX_Model::ContentHash(
) const
{
  const bool bRemapIds = true;
  ON_TextHash hash_log;
  hash_log.SetIdRemap(bRemapIds);
  Dump(hash_log);
  return hash_log.Hash();
}

class ON__CIndexPair
{
public:
  static int CompareOldIndex( const ON__CIndexPair* a, const ON__CIndexPair* b );
  static int CompareOldAndNewIndex( const ON__CIndexPair* a, const ON__CIndexPair* b );
  int m_old_index;  // value in model.m_..._table[m_table_index].m_..._index; (Read from file)
  int m_new_index;  // index in model.m_..._table[] array
};

int ON__CIndexPair::CompareOldIndex( const ON__CIndexPair* a, const ON__CIndexPair* b )
{
  return (a->m_old_index - b->m_old_index);
}

int ON__CIndexPair::CompareOldAndNewIndex( const ON__CIndexPair* a, const ON__CIndexPair* b )
{
  int i;
  if ( 0 == (i = a->m_old_index - b->m_old_index) )
    i = a->m_new_index - b->m_new_index;
  return i;
}

bool ONX_Model::Read(const char* filename, ON_TextLog* error_log)
{
  bool rc = false;

  if (nullptr != filename)
  {
    FILE* fp = ON::OpenFile(filename, "rb");
    if ( 0 != fp )
    {
      ON_BinaryFile file(ON::archive_mode::read3dm,fp);
      rc = Read(file, error_log);
      ON::CloseFile(fp);
    }
  }

  return rc;
}

bool ONX_Model::Read(const wchar_t* filename, ON_TextLog* error_log)
{
  bool rc = false;

  if (nullptr != filename)
  {
    FILE* fp = ON::OpenFile(filename, L"rb");
    if ( 0 != fp )
    {
      ON_BinaryFile file(ON::archive_mode::read3dm,fp);
      rc = Read(file, error_log);
      ON::CloseFile(fp);
    }
  }

  return rc;
}

bool ONX_Model::IncrementalReadBegin( 
  ON_BinaryArchive& archive,
  bool bManageComponents,
  unsigned int table_filter,
  ON_TextLog* error_log
  )
{
  Reset();

  const bool bResolveIdAndNameConflicts = true;
  const bool bUpdateComponentIdentification = true;

  int rc;

  if ( 0 == table_filter )
    table_filter = 0xFFFFFFFF; // read everything

  // STEP 1: REQUIRED - Read start section
  if ( !archive.Read3dmStartSection( &m_3dm_file_version, m_sStartSectionComments ) )
  {
    return false;
  }

  // STEP 2: REQUIRED - Read properties section
  if ( !archive.Read3dmProperties( m_properties ) )
  {
    return false;
  }

  // version of opennurbs used to write the file.
  m_3dm_opennurbs_version = archive.ArchiveOpenNURBSVersion();

  // STEP 3: REQUIRED - Read setting section
  if ( !archive.Read3dmSettings( m_settings ) )
  {
    return false;
  }

  // STEP 4: REQUIRED - Read embedded bitmap table
  if ( archive.BeginRead3dmBitmapTable() )
  {
    if ( 0 != (static_cast<unsigned int>(ON_3dmArchiveTableType::bitmap_table) & table_filter) )
    {
      for(;;)
      {
        ON_Bitmap* bitmap = nullptr;
        rc = archive.Read3dmBitmap(&bitmap);
        if ( rc==0 )
          break; // end of bitmap table
        if (rc < 0)
          break;
        if ( AddModelComponentForExperts(bitmap,bManageComponents,bResolveIdAndNameConflicts,bUpdateComponentIdentification).IsEmpty() )
          delete bitmap;
      }
    }

    // If BeginRead3dmBitmapTable() returns true, 
    // then you MUST call EndRead3dmBitmapTable().
    if ( !archive.EndRead3dmBitmapTable() )
    {
      return false;
    }
  }

  // STEP 5: REQUIRED - Read texture mapping table
  if ( archive.BeginRead3dmTextureMappingTable() )
  {
    if ( 0 != (static_cast<unsigned int>(ON_3dmArchiveTableType::texture_mapping_table) & table_filter) )
    {
      for(;;)
      {
        ON_TextureMapping* texture_mapping = nullptr;
        rc = archive.Read3dmTextureMapping(&texture_mapping);
        if ( rc==0 )
          break; // end of texture_mapping table
        if ( rc < 0 ) 
          break;
        if (AddModelComponentForExperts(texture_mapping, bManageComponents,bResolveIdAndNameConflicts,bUpdateComponentIdentification).IsEmpty())
          delete texture_mapping;
      }
    }
    
    // If BeginRead3dmTextureMappingTable() returns true, 
    // then you MUST call EndRead3dmTextureMappingTable().
    if ( !archive.EndRead3dmTextureMappingTable() )
    {
      return false;
    }
  }


  // STEP 6: REQUIRED - Read render material table
  if ( archive.BeginRead3dmMaterialTable() )
  {
    const ON_UUID settings_current_id = m_settings.CurrentMaterialId();
    const int settings_current_index = m_settings.CurrentMaterialIndex();
    bool bSetCurrentById = !(ON_nil_uuid == settings_current_id);
    bool bSetCurrentByIndex = false == bSetCurrentById && settings_current_index >= 0;
    m_settings.SetCurrentMaterialId(ON_nil_uuid);
    
    if ( 0 != (static_cast<unsigned int>(ON_3dmArchiveTableType::material_table) & table_filter) )
    {
      for(;;)
      {
        ON_Material* material = nullptr;
        rc = archive.Read3dmMaterial(&material);
        if ( rc==0 )
          break; // end of material table
        if (rc < 0)
          break;
        // index or id might be modified by AddModelComponentForExperts()
        const bool bSetAsCurrent =
          (bSetCurrentById && settings_current_id == material->Id())
          || (bSetCurrentByIndex && settings_current_index == material->Index());
        if ( AddModelComponentForExperts(material,bManageComponents,bResolveIdAndNameConflicts,bUpdateComponentIdentification).IsEmpty() )
        {
          delete material;
        }
        else if (bSetAsCurrent)
        {
          m_settings.SetCurrentMaterialId(material->Id());
          bSetCurrentById = false;
          bSetCurrentByIndex = false;
        }
      }
    }

    // If BeginRead3dmMaterialTable() returns true, 
    // then you MUST call EndRead3dmMaterialTable().
    if ( !archive.EndRead3dmMaterialTable() )
    {
      return false;
    }
  }


  // STEP 7: REQUIRED - Read line type table
  if ( archive.BeginRead3dmLinetypeTable() )
  {
    const ON_UUID settings_current_id = m_settings.CurrentLinePatternId();
    const int settings_current_index = m_settings.CurrentLinePatternIndex();
    bool bSetCurrentById = !(ON_nil_uuid == settings_current_id);
    bool bSetCurrentByIndex = false == bSetCurrentById && settings_current_index >= 0;
    m_settings.SetCurrentLinePatternId(ON_nil_uuid);

    if ( 0 != (static_cast<unsigned int>(ON_3dmArchiveTableType::linetype_table) & table_filter) )
    {
      for(;;)
      {
        ON_Linetype* line_pattern = nullptr;
        rc = archive.Read3dmLinetype(&line_pattern);
        if ( rc==0 )
          break; // end of linetype table
        if (rc < 0)
          break;
        // index or id might be modified by AddModelComponentForExperts()
        const bool bSetAsCurrent =
          (bSetCurrentById && settings_current_id == line_pattern->Id())
          || (bSetCurrentByIndex && settings_current_index == line_pattern->Index());
        if ( AddModelComponentForExperts(line_pattern,bManageComponents,bResolveIdAndNameConflicts,bUpdateComponentIdentification).IsEmpty() )
        {
          delete line_pattern;
        }
        else if (bSetAsCurrent)
        {
          m_settings.SetCurrentLinePatternId(line_pattern->Id());
          bSetCurrentById = false;
          bSetCurrentByIndex = false;
        }
      }
    }

    // If BeginRead3dmLinetypeTable() returns true, 
    // then you MUST call EndRead3dmLinetypeTable().
    if ( !archive.EndRead3dmLinetypeTable() )
    {
      return false;
    }
  }

  // STEP 8: REQUIRED - Read layer table
  if ( archive.BeginRead3dmLayerTable() )
  {
    const ON_UUID settings_current_id = m_settings.CurrentLayerId();
    const int settings_current_index = m_settings.CurrentLayerIndex();
    bool bSetCurrentById = !(ON_nil_uuid == settings_current_id);
    bool bSetCurrentByIndex = false == bSetCurrentById && settings_current_index >= 0;
    m_settings.SetCurrentLayerId(ON_nil_uuid);

    if ( 0 != (static_cast<unsigned int>(ON_3dmArchiveTableType::layer_table) & table_filter) )
    {
      for(;;)
      {
        ON_Layer* layer = nullptr;
        rc = archive.Read3dmLayer(&layer);
        if ( rc==0 )
          break; // end of layer table
        if (rc < 0)
          break;
        // index or id might be modified by AddModelComponentForExperts()
        const bool bSetAsCurrent =
          (bSetCurrentById && settings_current_id == layer->Id())
          || (bSetCurrentByIndex && settings_current_index == layer->Index());
        if (AddModelComponentForExperts(layer, bManageComponents,bResolveIdAndNameConflicts,bUpdateComponentIdentification).IsEmpty())
        {
          delete layer;
        }
        else if (bSetAsCurrent)
        {
          m_settings.SetCurrentLayerId(layer->Id());
          bSetCurrentById = false;
          bSetCurrentByIndex = false;
        }
      }
    }

    // If BeginRead3dmLayerTable() returns true, 
    // then you MUST call EndRead3dmLayerTable().
    if ( !archive.EndRead3dmLayerTable() )
    {
      return false;
    }

    ON_UUID current_layer_id = m_settings.CurrentLayerId();
    const ON_Layer* current_layer 
      = (ON_nil_uuid == current_layer_id)
      ? nullptr
      : ON_Layer::FromModelComponentRef(LayerFromId(current_layer_id), nullptr);
    if (nullptr == current_layer)
    {
      current_layer_id = ON_nil_uuid;
      int layer_count = 0;
      ONX_ModelComponentIterator layer_it(*this, ON_ModelComponent::Type::Layer);
      for (const ON_Layer* layer = ON_Layer::Cast(layer_it.FirstComponent()); nullptr != layer; layer = ON_Layer::Cast(layer_it.NextComponent()))
      {
        layer_count++;
        if (layer->IsVisible() && false == layer->IsLocked())
        {
          current_layer = layer;
          if ( layer->ParentIdIsNil() )
            break;
        }
      }
      if (nullptr == current_layer && layer_count > 0)
      {
        current_layer = ON_Layer::Cast(layer_it.FirstComponent());
      }
      if (nullptr != current_layer)
        m_settings.SetCurrentLayerId(current_layer->Id());
      else
        AddDefaultLayer(nullptr, ON_Color::UnsetColor);
    }
  }

  // STEP 9: REQUIRED - Read group table
  if ( archive.BeginRead3dmGroupTable() )
  {
    if ( 0 != (static_cast<unsigned int>(ON_3dmArchiveTableType::group_table) & table_filter) )
    {
      for(;;)
      {
        ON_Group* group = nullptr;
        rc = archive.Read3dmGroup(&group);
        if ( rc==0 )
          break; // end of group table
        if (rc < 0)
          break;
        if (AddModelComponentForExperts(group, bManageComponents,bResolveIdAndNameConflicts,bUpdateComponentIdentification).IsEmpty())
          delete group;
      }
    }
    
    // If BeginRead3dmGroupTable() returns true, 
    // then you MUST call EndRead3dmGroupTable().
    if ( !archive.EndRead3dmGroupTable() )
    {
      return false;
    }
  }

  // STEP 11: REQUIRED - Read dimstyle table
  if ( archive.BeginRead3dmDimStyleTable() )
  {
    const ON_UUID settings_current_id = m_settings.CurrentDimensionStyleId();
    const int settings_current_index = m_settings.CurrentDimensionStyleIndex();
    bool bSetCurrentById = !(ON_nil_uuid == settings_current_id);
    bool bSetCurrentByIndex = false == bSetCurrentById && settings_current_index >= 0;
    m_settings.SetCurrentDimensionStyleId(ON_nil_uuid);

    if ( 0 != (static_cast<unsigned int>(ON_3dmArchiveTableType::dimension_style_table) & table_filter) )
    {
      for(;;)
      {
        ON_DimStyle* dimension_style = nullptr;
        rc = archive.Read3dmDimStyle(&dimension_style);
        if ( rc==0 )
          break; // end of dimstyle table
        if ( rc < 0 ) 
          break;
        // index or id might be modified by AddModelComponentForExperts()
        const bool bSetAsCurrent =
          (bSetCurrentById && settings_current_id == dimension_style->Id())
          || (bSetCurrentByIndex && settings_current_index == dimension_style->Index());
        if (AddModelComponentForExperts(dimension_style, bManageComponents,bResolveIdAndNameConflicts,bUpdateComponentIdentification).IsEmpty())
        {
          delete dimension_style;
        }
        else if (bSetAsCurrent)
        {
          m_settings.SetCurrentDimensionStyleId(dimension_style->Id());
          bSetCurrentById = false;
          bSetCurrentByIndex = false;
        }
      }
    }
    
    // If BeginRead3dmDimStyleTable() returns true, 
    // then you MUST call EndRead3dmDimStyleTable().
    if ( !archive.EndRead3dmDimStyleTable() )
    {
      return false;
    }
  }

  // STEP 12: REQUIRED - Read render lights table
  if ( archive.BeginRead3dmLightTable() )
  {
    if ( 0 != (static_cast<unsigned int>(ON_3dmArchiveTableType::light_table) & table_filter) )
    {
      for(;;)
      {
        ON_ModelGeometryComponent* model_light = nullptr;
        rc = archive.Read3dmModelLight(&model_light);
        if (rc == 0)
          break; // end of light table
        if ( rc < 0 ) 
          break;
        if (AddModelComponentForExperts(model_light, bManageComponents,bResolveIdAndNameConflicts,bUpdateComponentIdentification).IsEmpty())
          delete model_light;
      }
    }

    // If BeginRead3dmLightTable() returns true, 
    // then you MUST call EndRead3dmLightTable().
    if ( !archive.EndRead3dmLightTable() )
    {
      return false;
    }
  }

  // STEP 13 - read hatch pattern table
  if ( archive.BeginRead3dmHatchPatternTable() )
  {
    const ON_UUID settings_current_id = m_settings.CurrentHatchPatternId();
    const int settings_current_index = ON_UNSET_INT_INDEX;
    bool bSetCurrentById = !(ON_nil_uuid == settings_current_id);
    bool bSetCurrentByIndex = false;
    m_settings.SetCurrentHatchPatternId(ON_nil_uuid);

    if ( 0 != (static_cast<unsigned int>(ON_3dmArchiveTableType::hatchpattern_table) & table_filter) )
    {
      for(;;)
      {
        ON_HatchPattern* hatch_pattern = nullptr;
        rc = archive.Read3dmHatchPattern(&hatch_pattern);
        if ( rc==0 )
          break; // end of hatchpattern table
        if ( rc < 0 ) 
          break;
        // index or id might be modified by AddModelComponentForExperts()
        const bool bSetAsCurrent =
          (bSetCurrentById && settings_current_id == hatch_pattern->Id())
          || (bSetCurrentByIndex && settings_current_index == hatch_pattern->Index());
        if (AddModelComponentForExperts(hatch_pattern, bManageComponents,bResolveIdAndNameConflicts,bUpdateComponentIdentification).IsEmpty())
        {
          delete hatch_pattern;
        }
        else if (bSetAsCurrent)
        {
          m_settings.SetCurrentHatchPatternId(hatch_pattern->Id());
          bSetCurrentById = false;
          bSetCurrentByIndex = false;
        }
      }
    }
    
    // If BeginRead3dmHatchPatternTable() returns true, 
    // then you MUST call EndRead3dmHatchPatternTable().
    if ( !archive.EndRead3dmHatchPatternTable() )
    {
      return false;
    }
  }

  // STEP 14: REQUIRED - Read instance definition table
  if ( archive.BeginRead3dmInstanceDefinitionTable() )
  {
    if ( 0 != (static_cast<unsigned int>(ON_3dmArchiveTableType::instance_definition_table) & table_filter) )
    {
      for(;;)
      {
        ON_InstanceDefinition* instance_definition = nullptr;
        rc = archive.Read3dmInstanceDefinition(&instance_definition);
        if ( rc==0 )
          break; // end of instance definition table
        if ( rc < 0 ) 
          break;
        if (AddModelComponentForExperts(instance_definition, bManageComponents,bResolveIdAndNameConflicts,bUpdateComponentIdentification).IsEmpty())
          delete instance_definition;
      }
    }
    
    // If BeginRead3dmInstanceDefinitionTable() returns true, 
    // then you MUST call EndRead3dmInstanceDefinitionTable().
    if ( !archive.EndRead3dmInstanceDefinitionTable() )
    {
      return false;
    }
  }

  return (0 == archive.CriticalErrorCount());
}

bool ONX_Model::IncrementalReadModelGeometry(
  ON_BinaryArchive& archive,
  bool bManageModelGeometryComponent,
  bool bManageGeometry,
  bool bManageAttributes,
  unsigned int object_filter,
  ON_ModelComponentReference& model_component_reference
  )
{
  model_component_reference = ON_ModelComponentReference::Empty;

  ON_3dmArchiveTableType active_table = archive.Active3dmTable();
  if (ON_3dmArchiveTableType::Unset == active_table)
  {
    ON_3dmArchiveTableType previous_table = archive.Previous3dmTable();
    if (ON_3dmArchiveTableType::Unset == previous_table)
    {
      // Yokel probably forgot to call IncrementalReadBegin()
      ON_ERROR("IncrementalReadBegin() must be called before IncrementalReadModelGeometry().");
      return false;
    }
    
    if (static_cast<unsigned int>(previous_table) >= static_cast<unsigned int>(ON_3dmArchiveTableType::object_table))
    {
      // Yokel either read or skipped reading the geometry table.
      ON_ERROR("Too late to read the geometry table.");
      return false;
    }

    if (false == archive.BeginRead3dmObjectTable())
    {
      ON_ERROR("Geometry table cannot be read from archive.");
      return false;
    }
    active_table = archive.Active3dmTable();
    if (active_table != ON_3dmArchiveTableType::object_table)
    {
      ON_ERROR("Catastrophic geometry table reading error.");
      return false;
    }
  }  
  else if (active_table != ON_3dmArchiveTableType::object_table)
  {
    // Yokel is calling IncrementalReadModelGeometry() at the wrong time.
    ON_ERROR("IncrementalReadModelGeometry() cannot be called while reading another part of the 3dm archive.");
    return false;
  }

  ON_3dmArchiveTableStatus object_table_status = archive.Archive3dmTableStatus(ON_3dmArchiveTableType::object_table);
  if (ON_3dmArchiveTableType::object_table != object_table_status.m_table_type)
  {
    ON_ERROR("Catastrophic geometry table reading error.");
    return false;
  }

  switch(object_table_status.m_state)
  {
  case ON_3dmArchiveTableStatus::TableState::Started:
  case ON_3dmArchiveTableStatus::TableState::InProgress:
    break;
  case ON_3dmArchiveTableStatus::TableState::Finished:
    {
      ON_ERROR("Geometry table has already been read from archive.");
      return false;
    }
  default:
    {
      ON_ERROR("Geometry table reading error.");
      return false;
    }
  }

  for(;;)
  {
    ON_ModelGeometryComponent* model_geometry = nullptr;
    int rc = archive.Read3dmModelGeometryForExperts(bManageGeometry,bManageAttributes,&model_geometry,object_filter);
    if ( rc <= 0 )
    {
      // end of object table or error reading
      // If BeginRead3dmObjectTable() returns true, 
      // then you MUST call EndRead3dmObjectTable().
      archive.EndRead3dmObjectTable();
      return (0==rc);
    }

    if (2 == rc && 0 != object_filter)
    {
      if ( nullptr != model_geometry)
        delete model_geometry;
      continue; // item was intentionally skipped.
    }

    model_component_reference = AddModelComponentForExperts(model_geometry,bManageModelGeometryComponent,true,true);

    if (model_component_reference.IsEmpty())
      continue;

    // return the read object.
    break;
  }

  return true;
}

bool ONX_Model::IncrementalReadFinish(
    ON_BinaryArchive& archive,
    bool bManageComponents,
    unsigned int table_filter,
    ON_TextLog* error_log
    )
{
  int rc;

  const bool bResolveIdAndNameConflicts = true;
  const bool bUpdateComponentIdentification = true;

  if ( 0 == table_filter )
    table_filter = 0xFFFFFFFF; // read everything

  // STEP 16: Read history table
  if ( archive.BeginRead3dmHistoryRecordTable() )
  {
    if ( 0 != (static_cast<unsigned int>(ON_3dmArchiveTableType::historyrecord_table) & table_filter) )
    {
      for(;;) 
      {
        ON_HistoryRecord* pHistoryRecord = nullptr;
        rc = archive.Read3dmHistoryRecord(pHistoryRecord);
        if ( rc == 0 )
          break; // end of history record table
        if ( rc < 0 ) 
          break;
        if ( AddModelComponentForExperts(pHistoryRecord,bManageComponents,bResolveIdAndNameConflicts,bUpdateComponentIdentification).IsEmpty() )
        {
          delete pHistoryRecord;
          continue;
        }
      }
    }
    
    // If BeginRead3dmHistoryRecordTable() returns true, 
    // then you MUST call EndRead3dmHistoryRecordTable().
    if ( !archive.EndRead3dmHistoryRecordTable() )
    {
      return false;
    }
  }

  if (0 != archive.CriticalErrorCount())
    return false;

  // STEP 17: OPTIONAL - Read user tables as anonymous goo
  // If you develop a plug-ins or application that uses OpenNURBS files,
  // you can store anything you want in a user table.
  for(;;)
  {
    if ( archive.Archive3dmVersion() <= 1 )
    {
      // no user tables in version 1 archives.
      break;
    }

    {
      ON__UINT32 tcode = 0;
      ON__INT64 big_value = 0;
      if ( !archive.PeekAt3dmBigChunkType(&tcode,&big_value) )
        break;
      if ( TCODE_USER_TABLE != tcode )
        break;
    }
    ON_UUID plugin_id = ON_nil_uuid;
    bool bGoo = false;
    int usertable_3dm_version = 0;
    unsigned int usertable_opennurbs_version = 0;
    if ( !archive.BeginRead3dmUserTable( plugin_id, &bGoo, &usertable_3dm_version, &usertable_opennurbs_version ) )
    {
      // attempt to skip bogus user table
      const ON__UINT64 pos0 = archive.CurrentPosition();
      ON__UINT32 tcode = 0;
      ON__INT64 big_value = 0;
      if  ( !archive.BeginRead3dmBigChunk(&tcode,&big_value) )
        break;
      if ( !archive.EndRead3dmChunk() )
        break;
      const ON__UINT64 pos1 = archive.CurrentPosition();
      if (pos1 <= pos0)
        break;
      if ( TCODE_USER_TABLE != tcode )
        break;

      continue; // skip this bogus user table
    }

    if ( 
      nullptr == m_model_user_string_list
      && plugin_id == ON_CLASS_ID(ON_DocumentUserStringList) 
      )
    {
      // Read the document user strings (key-value pairs) as
      // a user table with plug-in id = ON_CLASS_ID(ON_DocumentUserStringList)
      ON_Object* p = 0;
      archive.ReadObject(&p);
      m_model_user_string_list = ON_DocumentUserStringList::Cast(p);
      if ( 0 == m_model_user_string_list )
      {
        ON_ERROR("The document user string information in the file is damaged.");
        if ( 0 != p )
          delete p;
          p = 0;
      }
    } 
    else if ( 0 != (static_cast<unsigned int>(ON_3dmArchiveTableType::user_table) & table_filter) )
    {
      // read user data tables as anonymous goo
      ONX_Model_UserData* model_ud = new ONX_Model_UserData();
      model_ud->m_uuid = plugin_id;
      model_ud->m_usertable_3dm_version = usertable_3dm_version;
      model_ud->m_usertable_opennurbs_version = usertable_opennurbs_version;
      if ( !archive.Read3dmAnonymousUserTable( usertable_3dm_version, usertable_opennurbs_version, model_ud->m_goo ) )
      {
        delete model_ud;
        break;
      }
      m_userdata_table.Append(model_ud);
    }

    // If BeginRead3dmObjectTable() returns true, 
    // then you MUST call EndRead3dmUserTable().
    if ( !archive.EndRead3dmUserTable() )
    {
      break;
    }
  }

  if (0 != archive.CriticalErrorCount())
    return false;

  // STEP 18: OPTIONAL - check for end mark
  size_t file_length = 0;
  if (!archive.Read3dmEndMark(&file_length))
  {
    if (archive.Archive3dmVersion() != 1)
    {
      // some v1 files are missing end-of-archive markers
    }
  }
  else
  {
    m_3dm_file_byte_count = file_length;
  }

  return (0 == archive.CriticalErrorCount());
}


bool ONX_Model::Read( 
    const char* filename,
    unsigned int table_filter,
    unsigned int model_object_type_filter,
    ON_TextLog* error_log
    )
{
  const ON_wString wfilename_buffer(filename);
  const wchar_t* wfilename = static_cast< const wchar_t* >(wfilename_buffer);
  return Read(wfilename,table_filter,model_object_type_filter,error_log);
}

bool ONX_Model::Read( 
    const wchar_t* filename,
    unsigned int table_filter,
    unsigned int model_object_type_filter,
    ON_TextLog* error_log
    )
{
  bool bCallReset = true;
  bool rc = false;

  if ( 0 != filename )
  {
    FILE* fp = ON::OpenFile(filename,L"rb");
    if ( 0 != fp )
    {
      bCallReset = false;
      ON_BinaryFile file(ON::archive_mode::read3dm,fp);
      rc = Read(file, table_filter, model_object_type_filter, error_log);
      ON::CloseFile(fp);
    }
  }

  if ( bCallReset )
    Reset();

  return rc;
}

bool ONX_Model::Read(ON_BinaryArchive& archive, unsigned int table_filter,
                     unsigned int model_object_type_filter, ON_TextLog* error_log)
{
  // STEPS 1 to 14: REQUIRED.
  const bool bManageComponents = true;
  IncrementalReadBegin(archive, bManageComponents, table_filter, error_log);
  if (0 != archive.CriticalErrorCount())
    return false;

  // STEP 15: REQUIRED - Read object (geometry and annotation) table.
  if (0 == (static_cast<unsigned int>(ON_3dmArchiveTableType::object_table) & table_filter))
  {
    const bool bManageGeometry = true;
    const bool bManageAttributes = true;
    for (;;)
    {
      ON_ModelComponentReference model_geometry_reference;

      if (!IncrementalReadModelGeometry(archive, bManageComponents, bManageGeometry, bManageAttributes,
        model_object_type_filter, model_geometry_reference))
      {
        // Catastrophic error.
        break; 
      }

      if (model_geometry_reference.IsEmpty())
        break; // No more geometry.
    }

    if (0 != archive.CriticalErrorCount())
      return false;
  }

  IncrementalReadFinish(archive, bManageComponents, table_filter, error_log);
  if (0 != archive.CriticalErrorCount())
    return false;

  if (0 != archive.BadCRCCount())
    return false;

  // Having read the model data, populate the RDK components.
  const int archive_3dm_version = archive.Archive3dmVersion();
  m_private->PopulateRDKComponents(archive_3dm_version);

  return true;
}

bool ONX_Model::Read(ON_BinaryArchive& archive, ON_TextLog* error_log)
{
  unsigned int table_filter = 0; // read every table
  unsigned int model_object_type_filter = 0; // read every type of object
  return Read(archive, table_filter, model_object_type_filter, error_log);
}

bool ONX_Model::Write(const char* filename, int version, ON_TextLog* error_log) const
{
  bool rc = false;

  if (nullptr != filename && 0 != filename[0])
  {
    FILE* fp = ON::OpenFile(filename, "wb");
    if (nullptr != fp)
    {
      ON_BinaryFile file(ON::archive_mode::write3dm, fp);
      const ON_wString wFileName(filename);
      file.SetArchiveFullPath(static_cast<const wchar_t*>(wFileName));
      rc = Write(file, version, error_log);
      ON::CloseFile(fp);
    }
  }

  return rc;
}

bool ONX_Model::Write(const wchar_t* filename, int version, ON_TextLog* error_log) const
{
  bool rc = false;

  if (nullptr != filename && 0 != filename[0])
  {
    FILE* fp = ON::OpenFile(filename, L"wb");
    if (nullptr != fp)
    {
      ON_BinaryFile file(ON::archive_mode::write3dm, fp);
      file.SetArchiveFullPath(filename);
      rc = Write(file, version, error_log);
      ON::CloseFile(fp);
    }
  }

  return rc;
}

bool ONX_Model::Write(ON_BinaryArchive& archive, int version, ON_TextLog* error_log) const
{
  m_private->UpdateRDKUserData(version);

  if ( 0 != version )
  {
    if (  version < 2
      ||  version > ON_BinaryArchive::CurrentArchiveVersion()
      || (version < 50 && version > ON_BinaryArchive::CurrentArchiveVersion()/10)
      || (version >= 50 && 0 != (version % 10))
      )
    {
      version = 0;
      if ( error_log) error_log->Print("ONX_Model::Write version parameter = %d; it must be 0, or >= 2 and <= %d, or a multiple of 10 >= 50 and <= %d.\n",
                      version,ON_BinaryArchive::CurrentArchiveVersion()/10,ON_BinaryArchive::CurrentArchiveVersion());
    }
  }

  if ( !archive.WriteMode() )
  {
    // You passed in a bogus archive. You must pass ON::archive_mode::write3dm to the archive constructor.
    if ( error_log) error_log->Print("ONX_Model::Write archive.Mode() is not ON::archive_mode::write3dm.\n"
                    "See ONX_Model::Write example in the header file.\n");
    return false;
  }

  bool ok;

  // START SECTION
  ok = archive.Write3dmStartSection( version, static_cast< const char* >(m_sStartSectionComments) );
  if ( !ok )
  {
    // make sure your archive was created with ON::archive_mode::write3dm mode.
    if ( error_log) error_log->Print("ONX_Model::Write archive.Write3dmStartSection() failed.\n"
                    "Your archive is not properly initialized\n"
                    "(make sure you passed ON::archive_mode::write3dm to the constructor),\n"
                    "a file is locked, a disk is locked, or something along those lines.\n");
    return false;
  }

  // PROPERTIES SECTION
  if ( m_properties.m_RevisionHistory.m_revision_count == 0 )
    const_cast<ONX_Model*>(this)->m_properties.m_RevisionHistory.NewRevision();

  ok = archive.Write3dmProperties( m_properties );
  if ( !ok )
  {
    // make sure m_properties is valid
    if ( error_log) error_log->Print("ONX_Model::Write archive.Write3dmProperties() failed.\n"
                    "Your m_properties information is not valid or basic file writing failed.\n"
                    );
    return false;
  }

  // SETTINGS SECTION
  ok = archive.Write3dmSettings( m_settings );
  if ( !ok )
  {
    // make sure m_settings is valid
    if ( error_log) error_log->Print("ONX_Model::Write archive.Write3dmSettings() failed.\n"
                    "Your m_settings information is not valid or basic file writing failed.\n");
    return false;
  }

  // BITMAP TABLE
  ok = archive.BeginWrite3dmBitmapTable();
  if ( !ok )
  {
    if ( error_log) error_log->Print("ONX_Model::Write archive.BeginWrite3dmBitmapTable() failed.\n");
    return false;
  }
  
  for( 
    class ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(ON_ModelComponent::Type::Image).m_first_mcr_link;
    nullptr != link && ok;
    link = link->m_next
    )
  {
    ok = archive.Write3dmImageComponent(link->m_mcr);
    if ( !ok )
    {
      if ( error_log) error_log->Print("ONX_Model::Write archive.Write3dmImageComponent() failed.\n");
    }
  } 

  if ( !archive.EndWrite3dmBitmapTable() )
  {
    if ( error_log) error_log->Print("ONX_Model::Write archive.EndWrite3dmBitmapTable() failed.\n");
    return false;
  }
  if (!ok)
    return false;


  // TEXTURE MAPPING TABLE
  if ( archive.Archive3dmVersion() >= 4 )
  {
    ok = archive.BeginWrite3dmTextureMappingTable();
    if ( !ok )
    {
      if ( error_log) error_log->Print("ONX_Model::Write archive.BeginWrite3dmTextureMappingTable() failed.\n");
      return false;
    }

    for( 
      class ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(ON_ModelComponent::Type::TextureMapping).m_first_mcr_link;
      nullptr != link && ok;
      link = link->m_next
      )
    {
      ok = archive.Write3dmTextureMappingComponent(link->m_mcr);
      if ( !ok )
      {
        if ( error_log) error_log->Print("ONX_Model::Write archive.TextureMapping() failed.\n");
      }
    } 

    if ( !archive.EndWrite3dmTextureMappingTable() )
    {
      if ( error_log) error_log->Print("ONX_Model::Write archive.EndWrite3dmTextureMappingTable() failed.\n");
      return false;
    }
    if (!ok)
      return false;
  }

  // MATERIAL TABLE
  ok = archive.BeginWrite3dmMaterialTable();
  if ( !ok )
  {
    if ( error_log) error_log->Print("ONX_Model::Write archive.BeginWrite3dmMaterialTable() failed.\n");
    return false;
  }

  for( 
    class ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(ON_ModelComponent::Type::RenderMaterial).m_first_mcr_link;
    nullptr != link && ok;
    link = link->m_next
    )
  {
    ok = archive.Write3dmMaterialComponent(link->m_mcr);
    if ( !ok )
    {
      if ( error_log) error_log->Print("ONX_Model::Write archive.Write3dmMaterialComponent() failed.\n");
    }
  } 

  if ( !archive.EndWrite3dmMaterialTable() )
  {
    if ( error_log) error_log->Print("ONX_Model::Write archive.EndWrite3dmMaterialTable() failed.\n");
    return false;
  }
  if (!ok)
    return false;

  // LINETYPE TABLE
  if ( archive.Archive3dmVersion() >= 4 )
  {
    ok = archive.BeginWrite3dmLinetypeTable();
    if ( !ok )
    {
      if ( error_log) error_log->Print("ONX_Model::Write archive.BeginWrite3dmLinetypeTable() failed.\n");
      return false;
    }
    for( 
      class ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(ON_ModelComponent::Type::LinePattern).m_first_mcr_link;
      nullptr != link && ok;
      link = link->m_next
      )
    {
      ok = archive.Write3dmLinePatternComponent(link->m_mcr);
      if ( !ok )
      {
        if ( error_log) error_log->Print("ONX_Model::Write archive.Write3dmLinePatternComponent() failed.\n");
      }
    }
    if ( !archive.EndWrite3dmLinetypeTable() )
    {
      if ( error_log) error_log->Print("ONX_Model::Write archive.EndWrite3dmLinetypeTable() failed.\n");
      return false;
    }
    if (!ok)
      return false;
  }

  // LAYER TABLE
  ok = archive.BeginWrite3dmLayerTable();
  if ( !ok )
  {
    // make sure m_settings is valid
    if ( error_log) error_log->Print("ONX_Model::Write archive.BeginWrite3dmLayerTable() failed.\n");
    return false;
  }
  unsigned int layer_count = 0;
  for( 
    class ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(ON_ModelComponent::Type::Layer).m_first_mcr_link;
    nullptr != link && ok;
    link = link->m_next
    )
  {
    ok = archive.Write3dmLayerComponent(link->m_mcr);
    if (!ok)
    {
      if (error_log) error_log->Print("ONX_Model::Write archive.Write3dmLayerComponent() failed.\n");
    }
    else
      layer_count++;
  }
  if (0 == layer_count && ok)
  {
    ON_Layer layer(ON_Layer::Default);
    layer.SetId();
    layer.SetIndex(0);
    ok = archive.Write3dmLayer(layer);
    if (!ok)
    {
      if (error_log) error_log->Print("ONX_Model::Write archive.Write3dmLayer() failed.\n");
    }
  }
  if ( !archive.EndWrite3dmLayerTable() )
  {
    if ( error_log) error_log->Print("ONX_Model::Write archive.EndWrite3dmLayerTable() failed.\n");
    return false;
  }
  if (!ok)
    return false;

  // GROUP TABLE
  ok = archive.BeginWrite3dmGroupTable();
  if ( !ok )
  {
    // make sure m_settings is valid
    if ( error_log) error_log->Print("ONX_Model::Write archive.BeginWrite3dmGroupTable() failed.\n");
    return false;
  }
  for( 
    class ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(ON_ModelComponent::Type::Group).m_first_mcr_link;
    nullptr != link && ok;
    link = link->m_next
    )
  {
    ok = archive.Write3dmGroupComponent(link->m_mcr);
    if ( !ok )
    {
      if ( error_log) error_log->Print("ONX_Model::Write archive.Write3dmGroupComponent() failed.\n");
    }
  } 
  if ( !archive.EndWrite3dmGroupTable() )
  {
    if ( error_log) error_log->Print("ONX_Model::Write archive.EndWrite3dmGroupTable() failed.\n");
    return false;
  }
  if (!ok)
    return false;

  // DIMSTYLE TABLE
  if ( archive.Archive3dmVersion() >= 3 )
  {
    ok = archive.BeginWrite3dmDimStyleTable();
    if ( !ok )
    {
      // make sure m_settings is valid
      if ( error_log) error_log->Print("ONX_Model::Write archive.BeginWrite3dmDimStyleTable() failed.\n");
      return false;
    }
    for( 
      class ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(ON_ModelComponent::Type::DimStyle).m_first_mcr_link;
      nullptr != link;
      link = link->m_next
      )
    {
      ok = archive.Write3dmDimStyleComponent(link->m_mcr);
      if (!ok)
      {
        if ( error_log) error_log->Print("ONX_Model::Write archive.Write3dmDimStyleComponent() failed.\n");
      }
    }
    if ( !archive.EndWrite3dmDimStyleTable() )
    {
      if ( error_log) error_log->Print("ONX_Model::Write archive.EndWrite3dmDimStyleTable() failed.\n");
      return false;
    }
    if (!ok)
      return false;
  }

  // LIGHT TABLE
  ok = archive.BeginWrite3dmLightTable();
  if ( !ok )
  {
    // make sure m_settings is valid
    if ( error_log) error_log->Print("ONX_Model::Write archive.BeginWrite3dmLightTable() failed.\n");
    return false;
  }
  for( 
    class ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(ON_ModelComponent::Type::RenderLight).m_first_mcr_link;
    nullptr != link;
    link = link->m_next
    )
  {
    ok = archive.Write3dmModelLightComponent(link->m_mcr);
    if ( !ok )
    {
      if ( error_log) error_log->Print("ONX_Model::Write archive.Write3dmModelLightComponent() failed.\n");
    }
  }
  if ( !archive.EndWrite3dmLightTable() )
  {
    if ( error_log) error_log->Print("ONX_Model::Write archive.EndWrite3dmLightTable() failed.\n");
    return false;
  }
  if (!ok)
    return false;

  // HATCH PATTERN TABLE
  if ( archive.Archive3dmVersion() >= 4 )
  {
    ok = archive.BeginWrite3dmHatchPatternTable();
    if ( !ok )
    {
      if ( error_log) error_log->Print("ONX_Model::Write archive.BeginWrite3dmHatchPatternTable() failed.\n");
      return false;
    }

    for( 
      class ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(ON_ModelComponent::Type::HatchPattern).m_first_mcr_link;
      nullptr != link;
      link = link->m_next
      )
    {
      ok = archive.Write3dmHatchPatternComponent(link->m_mcr);
      if ( !ok )
      {
        if ( error_log) error_log->Print("ONX_Model::Write archive.Write3dmHatchPatternComponent() failed.\n");
      }
    }

    if ( !archive.EndWrite3dmHatchPatternTable() )
    {
      if ( error_log) error_log->Print("ONX_Model::Write archive.EndWrite3dmHatchPatternTable() failed.\n");
      return false;
    }
    if (!ok)
      return false;
  }

  // INSTANCE DEFINITION TABLE
  if ( archive.Archive3dmVersion() >= 3 )
  {
    ok = archive.BeginWrite3dmInstanceDefinitionTable();
    if ( !ok )
    {
      // make sure m_settings is valid
      if ( error_log) error_log->Print("ONX_Model::Write archive.BeginWrite3dmInstanceDefinitionTable() failed.\n");
      return false;
    }
    for( 
      class ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(ON_ModelComponent::Type::InstanceDefinition).m_first_mcr_link;
      nullptr != link;
      link = link->m_next
      )
    {
      ok = archive.Write3dmInstanceDefinitionComponent(link->m_mcr);
      if ( !ok )
      {
        if ( error_log) error_log->Print("ONX_Model::Write archive.Write3dmInstanceDefinitionComponent() failed.\n");
      }
    }
    if ( !archive.EndWrite3dmInstanceDefinitionTable() )
    {
      if ( error_log) error_log->Print("ONX_Model::Write archive.EndWrite3dmInstanceDefinitionTable() failed.\n");
      return false;
    }
    if (!ok)
      return false;
  }

  // OBJECT TABLE
  ok = archive.BeginWrite3dmObjectTable();
  if ( !ok )
  {
    if ( error_log) error_log->Print("ONX_Model::Write archive.BeginWrite3dmObjectTable() failed.\n");
    return false;
  }
  for( 
    class ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(ON_ModelComponent::Type::ModelGeometry).m_first_mcr_link;
    nullptr != link;
    link = link->m_next
    )
  {
    ok = archive.Write3dmModelGeometryComponent(link->m_mcr);
    if ( !ok )
    {
      if ( error_log)
        error_log->Print("ONX_Model::Write archive.Write3dmModelGeometryComponent() failed.\n");
    }
  }
  if ( !archive.EndWrite3dmObjectTable() )
  {
    if ( error_log) 
      error_log->Print("ONX_Model::Write archive.EndWrite3dmObjectTable() failed.\n");
    return false;
  }
  if (!ok)
    return false;

  // HISTORY RECORD TABLE
  if ( archive.Archive3dmVersion() >= 4 )
  {
    ok = archive.BeginWrite3dmHistoryRecordTable();
    if ( !ok )
    {
      if ( error_log) error_log->Print("ONX_Model::Write archive.BeginWrite3dmHistoryRecordTable() failed.\n");
      return false;
    }

    for( 
      class ONX_ModelComponentReferenceLink* link = Internal_ComponentListConst(ON_ModelComponent::Type::HistoryRecord).m_first_mcr_link;
      nullptr != link;
      link = link->m_next
      )
    {
      ok = archive.Write3dmHistoryRecordComponent(link->m_mcr);
      if ( !ok )
      {
        if ( error_log) error_log->Print("ONX_Model::Write archive.Write3dmistoryRecordComponent() failed.\n");
      }
    }


    if( !archive.EndWrite3dmHistoryRecordTable() )
    {
      if ( error_log) error_log->Print("ONX_Model::Write archive.EndWrite3dmHistoryTable() failed.\n");
      return false;
    }
    if (!ok)
      return false;
  }

  // STEP 17: - write user tables (plug-in info, etc.)
  if (archive.ArchiveContains3dmTable(ON_3dmArchiveTableType::user_table))
  {
    if (nullptr != m_model_user_string_list && m_model_user_string_list->UserStringCount() > 0)
    {
      // Write the document user strings (key-value pairs) as
      // a user table with plug-in id = 
      ON_UUID model_user_string_plugin_id = ON_CLASS_ID(ON_DocumentUserStringList);
      if (archive.BeginWrite3dmUserTable(model_user_string_plugin_id, false, 0, 0))
      {
        archive.WriteObject(m_model_user_string_list);
        archive.EndWrite3dmUserTable();
      }
    }

    // USER DATA TABLE
    for (int i = 0; ok && i < m_userdata_table.Count(); i++)
    {
      const ONX_Model_UserData* model_ud = m_userdata_table[i];
      if (nullptr == model_ud)
        continue;
      if (ON_UuidIsNotNil(model_ud->m_uuid))
      {
        if (!archive.Write3dmAnonymousUserTableRecord(
          model_ud->m_uuid,
          model_ud->m_usertable_3dm_version,
          model_ud->m_usertable_opennurbs_version,
          model_ud->m_goo)
          )
        {
          continue;
        }
      }
    }
  }

  if ( !archive.Write3dmEndMark() )
  {
    ok = false;
    if ( error_log) error_log->Print("ONX_Model::Write archive.Write3dmEndMark() failed.\n");
  }

  return ok;
}

int ONX_Model::UsesIDef(
        const ON_InstanceRef& iref,
        ON_UUID idef_uuid
        ) const
{
  // get id of idef we are looking for
  if ( ON_UuidIsNil(idef_uuid) )
    return 0;

  // id of idef that defines iref
  ON_UUID iref_idef_uuid = iref.m_instance_definition_uuid;
  if ( 0 == ON_UuidCompare( idef_uuid, iref_idef_uuid ) )
    return 1;

  ON_ModelComponentReference idef_reference = ComponentFromId(ON_ModelComponent::Type::InstanceDefinition,iref_idef_uuid);
  const ON_InstanceDefinition* iref_idef = ON_InstanceDefinition::FromModelComponentRef(idef_reference,nullptr);

  if ( nullptr == iref_idef )
    return -1; // invalid id.


  // set iref_list[] = list of all nested instance references in iref_idef.
  ON_SimpleArray<const ON_InstanceRef*> iref_list(256);
  const ON_SimpleArray<ON_UUID>& iref_idef_object_uuid = iref_idef->InstanceGeometryIdList();
  for ( unsigned j = 0; j < iref_idef_object_uuid.UnsignedCount(); j++ )
  {
    ON_ModelComponentReference component_reference = ComponentFromId(ON_ModelComponent::Type::InstanceDefinition,iref_idef_object_uuid[j]);
    const ON_ModelGeometryComponent* model_geometry = ON_ModelGeometryComponent::Cast(component_reference.ModelComponent());
    if ( nullptr == model_geometry )
      continue;
    const ON_Geometry* geometry = model_geometry->Geometry(nullptr);
    if ( nullptr == geometry )
      continue;
    if ( geometry->ObjectType() != ON::instance_reference )
      continue;
    const ON_InstanceRef* pNestedIRef = ON_InstanceRef::Cast(geometry);
    if ( nullptr == pNestedIRef )
      continue;
    if ( 0 == ON_UuidCompare( idef_uuid, pNestedIRef->m_instance_definition_uuid ) )
      return 2;
    iref_list.Append(pNestedIRef);
  }

  // test the nested instance references to see if they use idef_index.
  unsigned int i1 = 0;
  int depth = 3;
  for ( depth=3; i1 < iref_list.UnsignedCount(); depth++ )
  {
    const unsigned int i0 = i1;
    i1 = iref_list.UnsignedCount();
    for ( unsigned int i = i0; i < i1; i++ )
    {
      const ON_InstanceRef* pNestedIRef = iref_list[i];
      if ( nullptr == pNestedIRef )
        continue;
      ON_ModelComponentReference nested_idef_reference = ComponentFromId(ON_ModelComponent::Type::InstanceDefinition,pNestedIRef->m_instance_definition_uuid);
      const ON_InstanceDefinition* nested_idef = ON_InstanceDefinition::FromModelComponentRef(nested_idef_reference,nullptr);
      if ( nullptr == nested_idef )
        continue;
      const ON_SimpleArray<ON_UUID>& nested_idef_object_uuid = nested_idef->InstanceGeometryIdList();
      for ( unsigned int j = 0; j < nested_idef_object_uuid.UnsignedCount(); j++ )
      {
        ON_ModelComponentReference component_reference = ComponentFromId(ON_ModelComponent::Type::InstanceDefinition,nested_idef_object_uuid[j]);
        const ON_ModelGeometryComponent* model_geometry = ON_ModelGeometryComponent::Cast(component_reference.ModelComponent());
        if ( nullptr == model_geometry )
          continue;
        const ON_Geometry* geometry = model_geometry->Geometry(nullptr);
        if ( nullptr == geometry )
          continue;
        if ( geometry->ObjectType() != ON::instance_reference )
          continue;
        const ON_InstanceRef* pNestedIRef_local = ON_InstanceRef::Cast(geometry);
        if ( nullptr == pNestedIRef_local )
          continue;
        if ( 0 == ON_UuidCompare( idef_uuid, pNestedIRef_local->m_instance_definition_uuid ) )
          return depth;
        iref_list.Append(pNestedIRef_local);
      }
    }
    if ( i1 > 10000 && i1 < iref_list.UnsignedCount() )
      return -2; // probably have a circular reference
  }

  return 0;
}

ON__UINT64 ONX_Model::ModelContentVersionNumber() const
{
  return m_private->m_model_content_version_number;
}

void ONX_Model::Internal_IncrementModelContentVersionNumber()
{
  m_private->m_model_content_version_number++;
}

bool ONX_Model::SetDocumentUserString( const wchar_t* key, const wchar_t* string_value )
{
  if (nullptr == key || 0 == key[0] )
    return false;
  if ( nullptr == m_model_user_string_list )
    m_model_user_string_list = new ON_DocumentUserStringList();
  return m_model_user_string_list->SetUserString(key,string_value);
}

bool ONX_Model::GetDocumentUserString( 
  const wchar_t* key,
  ON_wString& string_value 
  ) const
{
  if ( nullptr != m_model_user_string_list )
    return m_model_user_string_list->GetUserString(key,string_value);
  string_value = ON_wString::EmptyString;
  return false;
}

int ONX_Model::GetDocumentUserStrings(
  ON_ClassArray<ON_UserString>& user_strings
  ) const
{
  if ( nullptr != m_model_user_string_list )
    return m_model_user_string_list->GetUserStrings(user_strings);
  return 0;
}

ONX_ModelComponentIterator::ONX_ModelComponentIterator(
  const ONX_Model& model,
  ON_ModelComponent::Type component_type
  )
  : m_component_type(component_type)
  , m_model(&model)
{}

const ONX_Model* ONX_ModelComponentIterator::Model() const
{
  return m_model;
}

const class ONX_Model::ONX_ModelComponentList* ONX_ModelComponentIterator::Internal_List() const
{
  if (nullptr != m_list)
    return m_list;

  if ( nullptr == m_model )
    return nullptr;

  m_list = &m_model->Internal_ComponentListConst(m_component_type);
  
  return m_list;
}

void ONX_ModelComponentIterator::Internal_SetLink(
  const class ONX_ModelComponentReferenceLink* link
  ) const
{
  // m_model is never nullptr when this function is called
  m_model_content_version = m_model->ModelContentVersionNumber();
  m_link = link;
  if (nullptr == m_link)
  {
    m_current_component_sn = 0;
    m_next_component_sn = 0;
    m_prev_component_sn = 0;
    m_current_component_weak_ref = ON_ModelComponentWeakReference::Empty;
    m_model_content_version = 0;
  }
  else
  {
    m_current_component_sn = link->m_sn;
    m_next_component_sn = (nullptr != link->m_next) ? link->m_next->m_sn : 0;
    m_prev_component_sn = (nullptr != link->m_prev) ? link->m_prev->m_sn : 0;
    m_current_component_weak_ref = link->m_mcr;
  }
}

void ONX_ModelComponentIterator::Internal_SetLink(
  ON__UINT64 model_component_sn
  ) const
{
}


ON_ModelComponentReference ONX_ModelComponentIterator::FirstComponentReference()
{
  return ON_ModelComponentReference(FirstComponentWeakReference());
}

ON_ModelComponentReference ONX_ModelComponentIterator::LastComponentReference()
{
  return ON_ModelComponentReference(LastComponentWeakReference());
}

ON_ModelComponentReference ONX_ModelComponentIterator::CurrentComponentReference() const
{
  return ON_ModelComponentReference(CurrentComponentWeakReference());
}

ON_ModelComponentReference ONX_ModelComponentIterator::NextComponentReference()
{
  return ON_ModelComponentReference(NextComponentWeakReference());
}

ON_ModelComponentReference ONX_ModelComponentIterator::PreviousComponentReference()
{
  return ON_ModelComponentReference(PreviousComponentWeakReference());
}



ON_ModelComponentWeakReference ONX_ModelComponentIterator::FirstComponentWeakReference()
{
  const ONX_Model::ONX_ModelComponentList* list = Internal_List();
  Internal_SetLink((nullptr != list) ? list->m_first_mcr_link : nullptr);
  return m_current_component_weak_ref;
}

ON_ModelComponentWeakReference ONX_ModelComponentIterator::LastComponentWeakReference()
{
  const ONX_Model::ONX_ModelComponentList* list = Internal_List();
  Internal_SetLink((nullptr != list) ? list->m_last_mcr_link : nullptr);
  return m_current_component_weak_ref;
}

ON_ModelComponentWeakReference ONX_ModelComponentIterator::CurrentComponentWeakReference() const
{
  // unchanged ModelContentVersionNumber() means that m_link is safe to dereference.
  // Otherwise use sn for safe reset.
  if (m_model_content_version != m_model->ModelContentVersionNumber() )
    Internal_SetLink(m_model->Internal_ModelComponentLinkFromSerialNumber(m_current_component_sn));
  return m_current_component_weak_ref;
}

ON_ModelComponentWeakReference ONX_ModelComponentIterator::NextComponentWeakReference()
{
  if ( nullptr == m_list )
    return FirstComponentReference();

  if ( nullptr == m_link )
    return ON_ModelComponentReference::Empty;

  if (m_model_content_version == m_model->ModelContentVersionNumber() && nullptr != m_link )
  {
    // unchanged ModelContentVersionNumber() means that m_link is safe to dereference.
    m_link = m_link->m_next;
    if (nullptr == m_link)
    {
      m_prev_component_sn = m_current_component_sn;
      m_current_component_sn = 0;
      m_next_component_sn = 0;
      m_current_component_weak_ref = ON_ModelComponentWeakReference::Empty;
    }
    else
    {
      m_current_component_sn = m_link->m_sn;
      m_next_component_sn = (nullptr != m_link->m_next) ? m_link->m_next->m_sn : 0;
      m_prev_component_sn = (nullptr != m_link->m_prev) ? m_link->m_prev->m_sn : 0;
      m_current_component_weak_ref = m_link->m_mcr;
    }
  }
  else if ( 0 != m_next_component_sn )
  {
    // Otherwise m_link is not safe to dereference.
    // Use slower serial number lookup.
    Internal_SetLink(m_model->Internal_ModelComponentLinkFromSerialNumber(m_next_component_sn));
  }
  else
  {
    m_link = nullptr;
    m_current_component_sn = 0;
    m_current_component_weak_ref = ON_ModelComponentWeakReference::Empty;
  }

  return m_current_component_weak_ref;
}

ON_ModelComponentWeakReference ONX_ModelComponentIterator::PreviousComponentWeakReference()
{
  if ( nullptr == m_list )
    return LastComponentReference();

  if ( nullptr == m_link )
    return ON_ModelComponentReference::Empty;

  if (m_model_content_version == m_model->ModelContentVersionNumber() && nullptr != m_link )
  {
    m_link = m_link->m_prev;
    if (nullptr == m_link)
    {
      m_next_component_sn = m_current_component_sn;
      m_current_component_sn = 0;
      m_prev_component_sn = 0;
      m_current_component_weak_ref = ON_ModelComponentWeakReference::Empty;
    }
    else
    {
      m_current_component_sn = m_link->m_sn;
      m_next_component_sn = (nullptr != m_link->m_next) ? m_link->m_next->m_sn : 0;
      m_prev_component_sn = (nullptr != m_link->m_prev) ? m_link->m_prev->m_sn : 0;
      m_current_component_weak_ref = m_link->m_mcr;
    }
  }
  else if ( 0 != m_prev_component_sn )
  {
    Internal_SetLink(m_model->Internal_ModelComponentLinkFromSerialNumber(m_prev_component_sn));
  }
  else
  {
    m_link = nullptr;
    m_current_component_sn = 0;
    m_current_component_weak_ref = ON_ModelComponentReference::Empty;
  }

  return m_current_component_weak_ref;
}

const ON_ModelComponent* ONX_ModelComponentIterator::FirstComponent()
{
  return FirstComponentReference().ModelComponent();
}

const ON_ModelComponent* ONX_ModelComponentIterator::LastComponent()
{
  return LastComponentReference().ModelComponent();
}

const ON_ModelComponent* ONX_ModelComponentIterator::CurrentComponent() const
{
  return CurrentComponentReference().ModelComponent();
}

const ON_ModelComponent* ONX_ModelComponentIterator::NextComponent()
{
  return NextComponentReference().ModelComponent();
}

const ON_ModelComponent* ONX_ModelComponentIterator::PreviousComponent()
{
  return PreviousComponentReference().ModelComponent();
}

unsigned int ONX_ModelComponentIterator::ActiveComponentCount() const
{
  return (nullptr != m_list) ? m_list->m_count : 0;
}

class ON_TextLogNull : public ON_TextLog
{
public:
  ON_TextLogNull() = default;
  ~ON_TextLogNull() = default;

  void AppendText(const char*) override {}
  void AppendText(const wchar_t*) override {}
};

const char* ONX_ModelTest::TestTypeToString(ONX_ModelTest::Type test_type)
{
 switch (test_type)
  {
  case ONX_ModelTest::Type::Unset:
    return "Unset";
    break;
  case ONX_ModelTest::Type::Read:
    return "Read";
    break;
  case ONX_ModelTest::Type::ReadWrite:
    return "ReadWrite";
    break;
  case ONX_ModelTest::Type::ReadWriteRead:
    return "ReadWriteRead";
    break;
  case ONX_ModelTest::Type::ReadWriteReadCompare:
    return "ReadWriteReadCompare";
    break;
  default:
    break;
  }

  ON_ERROR("Invalid test_type parameter.");
  return "Invalid test_type parameter";
}


const wchar_t* ONX_ModelTest::TestTypeToWideString(ONX_ModelTest::Type test_type)
{
  switch (test_type)
  {
  case ONX_ModelTest::Type::Unset:
    return L"Unset";
    break;
  case ONX_ModelTest::Type::Read:
    return L"Read";
    break;
  case ONX_ModelTest::Type::ReadWrite:
    return L"ReadWrite";
    break;
  case ONX_ModelTest::Type::ReadWriteRead:
    return L"ReadWriteRead";
    break;
  case ONX_ModelTest::Type::ReadWriteReadCompare:
    return L"ReadWriteReadCompare";
    break;
  default:
    break;
  }

  ON_ERROR("Invalid test_type parameter.");
  return L"Invalid test_type parameter";
}

const char* ONX_ModelTest::ResultToString(ONX_ModelTest::Result result)
{
  switch (result)
  {
  case ONX_ModelTest::Result::Unset:
    return "Unset";
    break;
  case ONX_ModelTest::Result::Fail:
    return "Fail";
    break;
  case ONX_ModelTest::Result::Errors:
    return "Errors";
    break;
  case ONX_ModelTest::Result::Warnings:
    return "Warnings";
    break;
  case ONX_ModelTest::Result::Pass:
    return "Pass";
    break;
  case ONX_ModelTest::Result::Skip:
    return "Skip";
    break;
  default:
    break;
  }

  ON_ERROR("Invalid result parameter.");
  return "Invalid result parameter";
}

const wchar_t* ONX_ModelTest::ResultToWideString(ONX_ModelTest::Result result)
{
  switch (result)
  {
  case ONX_ModelTest::Result::Unset:
    return L"Unset";
    break;
  case ONX_ModelTest::Result::Fail:
    return L"Fail";
    break;
  case ONX_ModelTest::Result::Errors:
    return L"Errors";
    break;
  case ONX_ModelTest::Result::Warnings:
    return L"Warnings";
    break;
  case ONX_ModelTest::Result::Pass:
    return L"Pass";
    break;
  case ONX_ModelTest::Result::Skip:
    return L"Skip";
    break;
  default:
    break;
  }

  ON_ERROR("Invalid result parameter.");
  return L"Invalid result parameter";

}


ONX_ModelTest::Result ONX_ModelTest::WorstResult(
  ONX_ModelTest::Result a,
  ONX_ModelTest::Result b
)
{
  if (ONX_ModelTest::Result::Unset == a && ONX_ModelTest::Result::Unset != b)
    return b;
  if (ONX_ModelTest::Result::Unset != a && ONX_ModelTest::Result::Unset == b)
    return a;
  return
    (static_cast<unsigned char>(a) < static_cast<unsigned char>(b))
    ? a : b;
}

ONX_ModelTest::Result ONX_ModelTest::ResultFromErrorCounter(
  ONX_ErrorCounter error_count,
  ONX_ModelTest::Result no_errors_result
)
{
  if (error_count.FailureCount() > 0)
    return ONX_ModelTest::Result::Fail;
  if (error_count.ErrorCount() > 0)
    return ONX_ModelTest::Result::Errors;
  if (error_count.WarningCount() > 0)
    return ONX_ModelTest::Result::Warnings;
  return no_errors_result;
}


void ONX_ModelTest::Internal_BeginTest()
{
  *this = ONX_ModelTest::Unset;

  m_test_result = ONX_ModelTest::Result::Unset;
  const size_t count = sizeof(m_test_results) / sizeof(m_test_results[0]);
  for (size_t i = 0; i < count; i++)
  {
    m_test_results[i] = ONX_ModelTest::Result::Unset;
  }

  m_error_count = ONX_ErrorCounter::Zero;
  for (size_t i = 0; i < count; i++)
  {
    m_error_counts[i] = ONX_ErrorCounter::Zero;
  }
  m_error_counts[0].ClearLibraryErrorsAndWarnings();
  m_error_count.ClearLibraryErrorsAndWarnings();

  m_current_test_index = 0;

  for (int i = 0; i < 3; i++)
  {
    m_model_3dm_file_version[i] = 0;
    m_model_hash[i] = ON_SHA1_Hash::ZeroDigest;
  }
}


void ONX_ModelTest::Internal_EndCurrentTest()
{
  if (m_current_test_index > 0 && ONX_ModelTest::Result::Unset == m_test_results[m_current_test_index])
  {
    m_error_counts[m_current_test_index].AddLibraryErrorsAndWarnings();
    m_test_results[m_current_test_index] = ONX_ModelTest::WorstResult(m_test_results[m_current_test_index], ONX_ModelTest::ResultFromErrorCounter(m_error_counts[m_current_test_index], ONX_ModelTest::Result::Pass));
    m_error_counts[0].ClearLibraryErrorsAndWarnings();
  }
}

void ONX_ModelTest::Internal_BeginNextTest(
  ONX_ModelTest::Type test_type
  )
{
  m_error_counts[0].AddLibraryErrorsAndWarnings();

  //const size_t count = sizeof(m_test_results) / sizeof(m_test_results[0]);
  const unsigned int test_index = static_cast<unsigned char>(test_type);
  
  if ( test_index > m_current_test_index  )
  {
    Internal_EndCurrentTest();
    m_current_test_index = test_index;
    m_test_results[m_current_test_index] = ONX_ModelTest::Result::Unset;
    m_error_counts[m_current_test_index] = ONX_ErrorCounter::Zero;
    m_error_counts[m_current_test_index].ClearLibraryErrorsAndWarnings();
  }
}

bool ONX_ModelTest::Internal_TallyTestResults()
{
  const size_t count = sizeof(m_test_results) / sizeof(m_test_results[0]);
  m_test_results[0] = ONX_ModelTest::WorstResult(m_test_results[0], ONX_ModelTest::Result::Pass);
  for (size_t i = 0; i < count; i++)
  {
    m_test_results[i] = ONX_ModelTest::WorstResult(m_test_results[i], ONX_ModelTest::ResultFromErrorCounter(m_error_counts[i], ONX_ModelTest::Result::Unset));
    m_test_result = ONX_ModelTest::WorstResult(m_test_result, m_test_results[i]);
    m_error_count += m_error_counts[i];
  }

  m_error_count.ClearLibraryErrorsAndWarnings();

  m_test_result = ONX_ModelTest::WorstResult(m_test_result, ONX_ModelTest::ResultFromErrorCounter(m_error_count, ONX_ModelTest::Result::Unset));

  return (ONX_ModelTest::Result::Pass == m_test_result);
}

ONX_ModelTest::Type ONX_ModelTest::TestType() const
{
  return m_test_type;
}

const ON_wString ONX_ModelTest::Source3dmFilePath() const
{
  return m_source_3dm_file_path;
}

const ON_wString ONX_ModelTest::TextLogSource3dmFilePath() const
{
  return 
    m_text_log_3dm_file_path.IsNotEmpty() 
    ? m_text_log_3dm_file_path 
    : Source3dmFilePath();
}


unsigned int ONX_ModelTest::Source3dmFileVersion() const
{
  return m_model_3dm_file_version[0];
}

bool ONX_ModelTest::SkipCompare(unsigned int source_3dm_file_version)
{
  const bool bSkipCompare
    = (source_3dm_file_version >= 1 && source_3dm_file_version < 50);
  return bSkipCompare;
}

ONX_ModelTest::Result ONX_ModelTest::TestResult() const
{
  return m_test_result;
}
 
ONX_ModelTest::Result ONX_ModelTest::TestResult(
  ONX_ModelTest::Type test_type
)
{
  const unsigned int i = static_cast<unsigned char>(m_test_type);
  return m_test_results[i];
}


ONX_ErrorCounter ONX_ModelTest::ErrorCounter() const
{
  return m_error_count;
}
 

ONX_ErrorCounter ONX_ModelTest::ErrorCounter(
  ONX_ModelTest::Type test_type
) const
{
  const unsigned int i = static_cast<unsigned char>(m_test_type);
  return m_error_counts[i];
}

bool ONX_ModelTest::ReadTest(
    const char* file_path,
    ONX_ModelTest::Type test_type,
    bool bKeepModels,
    const char* text_log_file_path,
    ON_TextLog* text_log
)
{
  Internal_BeginTest();

  m_test_type = test_type;

  ON_TextLogNull devnull;
  if (nullptr == text_log)
    text_log = &ON_TextLog::Null;

  FILE* fp = nullptr;
  for (;;)
  {
    if (nullptr == file_path || 0 == file_path[0])
    {
      m_error_counts[0].IncrementFailureCount();
      text_log->Print("file_path was the empty string.");
      break;
    }

    fp = ON_FileStream::Open3dmToRead(file_path);
    if (nullptr == fp)
    {
      m_error_counts[0].IncrementFailureCount();
      text_log->Print("ON_FileStream::Open(%s, \"rb\") failed.",file_path);
      break;
    }

    ON_BinaryFile archive(ON::archive_mode::read3dm, fp);
    archive.SetArchiveFullPath(ON_wString(file_path));

    ON_wString wide_text_log_file_path(text_log_file_path);
    Internal_ReadTest(archive, test_type, bKeepModels, wide_text_log_file_path, text_log);
    break;
  }

  if (nullptr != fp)
  {
    if (0 != ON_FileStream::Close(fp))
    {
      text_log->Print("ON_FileStream::Close(%s) failed.", file_path);
      m_error_counts[0].IncrementErrorCount();
    }
  }

  return Internal_TallyTestResults();
}


bool ONX_ModelTest::ReadTest(
  const wchar_t* file_path,
  ONX_ModelTest::Type test_type,
  bool bKeepModels,
  const wchar_t* text_log_file_path,
  ON_TextLog* text_log
)
{
  Internal_BeginTest();

  ON_TextLogNull devnull;
  if (nullptr == text_log)
    text_log = &ON_TextLog::Null;

  FILE* fp = nullptr;
  for (;;)
  {
    if (nullptr == file_path || 0 == file_path[0])
    {
      m_error_counts[0].IncrementFailureCount();
      text_log->Print("file_path was the empty string.");
      break;
    }

    fp = ON_FileStream::Open3dmToRead(file_path);
    if (nullptr == fp)
    {
      m_error_counts[0].IncrementFailureCount();
      text_log->Print(L"ON_FileStream::Open(%ls, L\"rb\") failed.",file_path);
      break;
    }

    ON_BinaryFile archive(ON::archive_mode::read3dm, fp);
    archive.SetArchiveFullPath(file_path);
    Internal_ReadTest(archive, test_type, bKeepModels, text_log_file_path, text_log);
    break;
  }

  if (nullptr != fp)
  {
    if (0 != ON_FileStream::Close(fp))
    {
      text_log->Print(L"ON_FileStream::Close(%ls) failed.",file_path);
      m_error_counts[0].IncrementErrorCount();
    }
  }

  return Internal_TallyTestResults();
}

bool ONX_ModelTest::ReadTest(
  FILE* fp,
  ONX_ModelTest::Type test_type,
  bool bKeepModels,
  const wchar_t* text_log_file_path,
  ON_TextLog* text_log
)
{
  Internal_BeginTest();

  ON_TextLogNull devnull;
  if (nullptr == text_log)
    text_log = &ON_TextLog::Null;

  for (;;)
  {
    if (nullptr == fp)
    {
      m_error_counts[0].IncrementFailureCount();
      text_log->Print("fp is nullptr.");
      break;
    }

    ON_BinaryFile archive(ON::archive_mode::read3dm, fp);

    Internal_ReadTest(archive, test_type, bKeepModels, text_log_file_path, text_log);
    break;
  }

  return Internal_TallyTestResults();
}

static bool InternalCleanPass(
  ONX_ModelTest::Result result,
  ONX_ErrorCounter error_counter
)
{
  return (ONX_ModelTest::Result::Pass == result && 0 == error_counter.TotalCount());
}

static void InternalDumpResultAndErrorCount(
  ONX_ModelTest::Result result,
  ONX_ErrorCounter error_counter,
  ON_TextLog& text_log
)
{
  text_log.Print("%s", ONX_ModelTest::ResultToString(result));
  if (false == InternalCleanPass(result,error_counter))
  {
    text_log.Print(": ");
    error_counter.Dump(text_log);
  }
  text_log.PrintNewLine();
}

bool ONX_ModelTest::DumpModel(const ONX_Model* model, ON_TextLog& text_log)
{
  if (nullptr == model || model->Manifest().ActiveComponentCount(ON_ModelComponent::Type::Unset) <= 0)
    return false;

  ON_TextHash hash_log;
  hash_log.SetIdRemap(true);
  hash_log.SetOutputTextLog(&text_log);
  model->Dump(hash_log);
  const ON_SHA1_Hash dump_hash = hash_log.Hash();
  text_log.PrintNewLine();
  text_log.Print("Model Hash: ");
  dump_hash.Dump(text_log);
  text_log.PrintNewLine();

  return (false == dump_hash.IsZeroDigestOrEmptyContentHash());
}

std::shared_ptr<ONX_Model> ONX_ModelTest::SourceModel() const
{
  return m_model[0];
}

std::shared_ptr<ONX_Model> ONX_ModelTest::ReadWriteReadModel() const
{
  const auto source_model = SourceModel();
  if (nullptr != source_model)
  {
    for (int i = 1; i < 3; i++)
    {
      const ONX_Model* copy_model = m_model[i].get();
      if (nullptr == copy_model)
        continue;
      if (copy_model->m_3dm_file_version != source_model->m_3dm_file_version)
        continue;
      return m_model[i];
    }
  }
  std::shared_ptr<ONX_Model> nullsp;
  return nullsp;
}

static const ON_wString Internal_DumpModelfileName(
  const ON_wString source_3dm_file_path,
  bool bSourceModel
)
{
  ON_wString file_name_stem = ON_FileSystemPath::FileNameFromPath(source_3dm_file_path,false);
  if (file_name_stem.IsEmpty())
    return ON_wString::EmptyString;
  ON_wString text_file_path = ON_FileSystemPath::VolumeAndDirectoryFromPath(source_3dm_file_path);
  text_file_path += file_name_stem;
  text_file_path += L"_ONX_ModelTest_";
  if (bSourceModel)
    text_file_path += L"original";
  else
    text_file_path += L"copy";

#if defined(ON_RUNTIME_WIN)
#if defined(ON_64BIT_RUNTIME)
  text_file_path += L"_Win64";
#elif defined(ON_32BIT_RUNTIME)
  text_file_path += L"_Win32";
#else
  text_file_path += L"_Win";
#endif
#elif defined(ON_RUNTIME_APPLE_MACOS)
  text_file_path += L"_MacOS";
#elif defined(ON_RUNTIME_APPLE_IOS)
  text_file_path += L"_iOS";
#elif defined(ON_RUNTIME_APPLE)
  text_file_path += L"_AppleOS";
#elif defined(ON_RUNTIME_ANDROID)
  text_file_path += L"_AndroidOS";
#endif

#if defined(ON_DEBUG)
  text_file_path += L"Debug";
#else
  text_file_path += L"Release";
#endif

  text_file_path += L".txt";
  return text_file_path;
}

bool ONX_ModelTest::DumpSourceModel() const
{
  const ON_wString text_file_path = Internal_DumpModelfileName(m_source_3dm_file_path,true);
  return DumpSourceModel(text_file_path);
}

bool ONX_ModelTest::DumpSourceModel(const wchar_t* text_file_full_path) const
{
  bool rc = false;
  FILE* fp = nullptr;
  for (;;)
  {
    if (nullptr == text_file_full_path || 0 == text_file_full_path[0])
      break;
    fp = ON_FileStream::Open(text_file_full_path, L"w");
    if (nullptr == fp)
      break;
    const auto model = SourceModel();
    if (nullptr == model)
      break;
    if (model->Manifest().ActiveComponentCount(ON_ModelComponent::Type::Unset) <= 0)
      break;
    ON_TextLog text_log(fp);
    rc = DumpSourceModel(text_log);
    break;
  }
  if (nullptr != fp)
    ON_FileStream::Close(fp);
  return rc;
}

bool ONX_ModelTest::DumpSourceModel(ON_TextLog& text_log) const
{
  return ONX_ModelTest::DumpModel(SourceModel().get(), text_log);
}

bool ONX_ModelTest::DumpReadWriteReadModel() const
{
  const ON_wString text_file_path = Internal_DumpModelfileName(m_source_3dm_file_path,false);
  return DumpReadWriteReadModel(text_file_path);
}

bool ONX_ModelTest::DumpReadWriteReadModel(const wchar_t* text_file_full_path) const
{
  bool rc = false;
  FILE* fp = nullptr;
  for (;;)
  {
    if (nullptr == text_file_full_path || 0 == text_file_full_path[0])
      break;
    fp = ON_FileStream::Open(text_file_full_path, L"w");
    if (nullptr == fp)
      break;
    const auto model = ReadWriteReadModel();
    if (nullptr == model)
      break;
    if (model->Manifest().ActiveComponentCount(ON_ModelComponent::Type::Unset) <= 0)
      break;
    ON_TextLog text_log(fp);
    rc = DumpReadWriteReadModel(text_log);
    break;
  }

  if (nullptr != fp)
    ON_FileStream::Close(fp);

  return rc;
}

bool ONX_ModelTest::DumpReadWriteReadModel(ON_TextLog& text_log) const
{
  return ONX_ModelTest::DumpModel(ReadWriteReadModel().get(), text_log);
}

void ONX_ModelTest::Dump(ON_TextLog& text_log) const
{
  const ONX_ModelTest::Type test_type = TestType();

  text_log.Print("Test type: %s\n", ONX_ModelTest::TestTypeToString(test_type));

  //const ON_wString source_archive = Source3dmFilePath();
  const ON_wString test_log_source_archive = TextLogSource3dmFilePath();
  text_log.Print(L"Source 3dm file path: %ls\n", static_cast<const wchar_t*>(test_log_source_archive));
  text_log.Print(L"Source 3dm file version: %u\n", Source3dmFileVersion());

  text_log.Print("Result: ");
  InternalDumpResultAndErrorCount(m_test_result, m_error_count, text_log);

  //const int i_rwrcompare = static_cast<const unsigned char>(ONX_ModelTest::Type::ReadWriteReadCompare);
  const bool bSkipCompare
    = ONX_ModelTest::SkipCompare(Source3dmFileVersion())
    && ONX_ModelTest::Type::ReadWriteReadCompare == test_type;
  const unsigned int imax
    = bSkipCompare
    ? static_cast<const unsigned char>(ONX_ModelTest::Type::ReadWriteRead)
    : static_cast<const unsigned char>(test_type);
  bool bSkipDetails = InternalCleanPass(m_test_result, m_error_count);
  for (unsigned int i = 0; i <= imax && bSkipDetails; i++)
  {
    bSkipDetails = InternalCleanPass(m_test_results[i], m_error_counts[i]);
  }  

  if (bSkipDetails)
  {
    if (bSkipCompare)
    {
      text_log.PushIndent();
      text_log.Print("Compare test skipped because source file version is too old.\n");
      text_log.PopIndent();
    }
    return;
  }

  text_log.PushIndent();
  for(;;)
  {
    unsigned int i = 0;
    text_log.Print("Initialization: ");
    InternalDumpResultAndErrorCount(m_test_results[i], m_error_counts[i], text_log);
    if (i >= imax)
      break;

    i++;
    text_log.Print("Read source file: ");
    InternalDumpResultAndErrorCount(m_test_results[i], m_error_counts[i], text_log);
    if (i >= imax)
      break;

    i++;
    text_log.Print("Write temporary files: ");
    InternalDumpResultAndErrorCount(m_test_results[i], m_error_counts[i], text_log);
    if (i >= imax)
      break;

    i++;
    text_log.Print("Read temporary files: ");
    InternalDumpResultAndErrorCount(m_test_results[i], m_error_counts[i], text_log);
    if (i >= imax)
      break;

    i++;
    text_log.Print("Compare models from source and temporary file: ");
    InternalDumpResultAndErrorCount(m_test_results[i], m_error_counts[i], text_log);
    if (i >= imax)
      break;

    break;
  }
  text_log.PopIndent();  
}

bool ONX_ModelTest::ReadTest(
  ON_BinaryArchive& archive,
  ONX_ModelTest::Type test_type,
  bool bKeepModels,
  const wchar_t* text_log_file_path,
  ON_TextLog* text_log
)
{
  Internal_BeginTest();
  Internal_ReadTest(archive, test_type, bKeepModels, text_log_file_path, text_log);
  return Internal_TallyTestResults();
}

void ONX_ModelTest::Internal_ReadTest(
  ON_BinaryArchive& archive,
  ONX_ModelTest::Type test_type,
  bool bKeepModels,
  const wchar_t* text_log_file_path,
  ON_TextLog* text_log
)
{
  m_test_type = test_type;
  m_source_3dm_file_path = archive.ArchiveFullPath();
  m_text_log_3dm_file_path = text_log_file_path;

  const unsigned int current_3dm_file_version = (unsigned int)ON_BinaryArchive::CurrentArchiveVersion();

  ON_TextLogNull devnull;
  if (nullptr == text_log)
    text_log = &ON_TextLog::Null;

  for (;;)
  {
    Internal_BeginNextTest(ONX_ModelTest::Type::Read);

    if ( ON::archive_mode::read3dm != archive.Mode() )
    {
      m_error_counts[0].IncrementFailureCount();
      text_log->Print("archive.Mode() must be ON::archive_mode::read3dm.");
      break;
    }

    ONX_Model* model0 = new ONX_Model();
    std::shared_ptr<ONX_Model> model0_sp = std::shared_ptr<ONX_Model>(model0);
    if (bKeepModels)
      this->m_model[0] = model0_sp;

    ON_String text_log_3dm_archive_name = TextLogSource3dmFilePath();
    if (text_log_3dm_archive_name.IsEmpty())
    {
      text_log_3dm_archive_name = "archive";
    }

    const ON_String read0_description
      = ON_String::FormatToString("ONX_Model.Read(%s,...)", static_cast<const char*>(text_log_3dm_archive_name));

    // read the original file
    text_log->Print("Calling %s ...\n", static_cast<const char*>(read0_description));
    text_log->PushIndent();
    ONX_ErrorCounter read0_error_counter;
    read0_error_counter.ClearLibraryErrorsAndWarnings();
    const bool bRead0 = model0->Read(archive, text_log);
    read0_error_counter.AddLibraryErrorsAndWarnings();
    m_model_3dm_file_version[0] = model0->m_3dm_file_version;

    text_log->PopIndent();

    if (false == bRead0)
    {
      m_error_counts[m_current_test_index].IncrementFailureCount();
      text_log->Print("%s failed.\n", static_cast<const char*>(read0_description));
      break;
    }
    else
    {
      text_log->Print("... %s ", static_cast<const char*>(read0_description));
      if ( 0 == read0_error_counter.TotalCount() )
        text_log->Print("succeeded.");
      else
      {
        text_log->Print("finished. ");
        read0_error_counter.Dump(*text_log);
      }
      text_log->PrintNewLine();

    }
    text_log->PushIndent();
    text_log->Print("Source model 3dm file version: %d", model0->m_3dm_file_version);
    text_log->PrintNewLine();
    m_model_hash[0] = model0->ContentHash();
    text_log->Print("Source model hash: ");
    m_model_hash[0].Dump(*text_log);
    text_log->PrintNewLine();
    text_log->PopIndent();

    if ( ONX_ModelTest::Type::Read == test_type)
      break;
    Internal_EndCurrentTest();
    Internal_BeginNextTest(ONX_ModelTest::Type::ReadWrite);

    //const unsigned int original_model_3dm_file_version = (unsigned int)(model0->m_3dm_file_version);

    // Write original_model to a termporary archive using "buffer" for storage. 
    ON_Buffer temporary_buffer[2];
    const unsigned int temporary_buffer_3dm_version[2] = { current_3dm_file_version - 10, current_3dm_file_version };

    for (int buffer_index = 0; buffer_index < 2; buffer_index++)
    {
      ON_BinaryArchiveBuffer temporary_archive(ON::archive_mode::write3dm, &temporary_buffer[buffer_index]);

      const ON_String write1_description
        = ON_String::FormatToString(
          "ONX_Model.Write( temporary_archive version %d, ...)",
          temporary_buffer_3dm_version[buffer_index]);

      text_log->Print("Calling %s ...\n", static_cast<const char*>(write1_description));
      text_log->PushIndent();
      ONX_ErrorCounter write1_error_counter;
      write1_error_counter.ClearLibraryErrorsAndWarnings();
      bool bWrite1 = model0->Write(temporary_archive, temporary_buffer_3dm_version[buffer_index], text_log);
      write1_error_counter.AddLibraryErrorsAndWarnings();
      text_log->PopIndent();

      if (false == bWrite1)
      {
        m_error_counts[m_current_test_index].IncrementFailureCount();
        text_log->Print("%s failed.\n", static_cast<const char*>(write1_description));
        break;
      }
      else
      {
        text_log->Print("... %s ", static_cast<const char*>(write1_description));
        if ( 0 == write1_error_counter.TotalCount() )
          text_log->Print("succeeded.");
        else
        {
          text_log->Print("finished. ");
          write1_error_counter.Dump(*text_log);
        }
        text_log->PrintNewLine();
      }
    }

    // no longer need model0
    model0 = nullptr;

    if ( ONX_ModelTest::Type::ReadWrite == test_type)
      break;
    Internal_EndCurrentTest();
    Internal_BeginNextTest(ONX_ModelTest::Type::ReadWriteRead);

    // read models from the temporary archives
    for (int buffer_index = 0; buffer_index < 2; buffer_index++)
    {
      ON_BinaryArchiveBuffer temporary_archive(ON::archive_mode::read3dm, &temporary_buffer[buffer_index]);
      const ON_String read1_description
        = ON_String::FormatToString(
          "ONX_Model.Read( temporary_archive version %d, ...)",
          temporary_buffer_3dm_version[buffer_index]);

      text_log->Print("Calling %s ...\n", static_cast<const char*>(read1_description));
      text_log->PushIndent();

      ONX_Model* model1 = new ONX_Model();
      std::shared_ptr<ONX_Model> model1_sp = std::shared_ptr<ONX_Model>(model1);
      if (bKeepModels)
        this->m_model[buffer_index+1] = model1_sp;

      ONX_ErrorCounter read1_error_counter;
      read1_error_counter.ClearLibraryErrorsAndWarnings();
      const bool bRead1 = model1->Read(temporary_archive, text_log);
      read1_error_counter.AddLibraryErrorsAndWarnings();      
      m_model_3dm_file_version[buffer_index + 1] = model1->m_3dm_file_version;

      text_log->PopIndent();

      if (false == bRead1)
      {
        m_error_counts[m_current_test_index].IncrementFailureCount();
        text_log->Print("%s failed.\n", static_cast<const char*>(read1_description));
        break;
      }
      else
      {
        text_log->Print("... %s ", static_cast<const char*>(read1_description));
        if ( 0 == read1_error_counter.TotalCount())
          text_log->Print("succeeded.");
        else
        {
          text_log->Print("finished. ");
          read1_error_counter.Dump(*text_log);
        }
        text_log->PrintNewLine();
      }
      text_log->PushIndent();
      text_log->Print("Temporary model %d 3dm file version: %d",buffer_index+1,model1->m_3dm_file_version);
      text_log->PrintNewLine();
      m_model_hash[buffer_index+1] = model1->ContentHash();
      text_log->Print("Temporary model %d hash: ",buffer_index+1);
      m_model_hash[buffer_index+1].Dump(*text_log);
      text_log->PrintNewLine();
      text_log->PopIndent();
    }

    if ( ONX_ModelTest::Type::ReadWrite == test_type)
      break;
    Internal_EndCurrentTest();
    Internal_BeginNextTest(ONX_ModelTest::Type::ReadWriteReadCompare);

    bool bSkippedCompare = true;
    for (int buffer_index = 0; buffer_index < 2; buffer_index++)
    {
      if (m_model_3dm_file_version[0] != m_model_3dm_file_version[buffer_index+1])
        continue;
      if (m_model_3dm_file_version[0] != temporary_buffer_3dm_version[buffer_index])
        continue;

      bSkippedCompare = false;
      if (m_model_hash[0] != m_model_hash[buffer_index+1])
      {
        m_error_counts[m_current_test_index].IncrementFailureCount();
        text_log->Print("The source model and temporary model %d are different.\n",buffer_index+1);
        break;
      }
      else
      {
        text_log->Print("The source model and temporary model %d are identical.\n",buffer_index+1);
      }
    }

    unsigned int compare_test_index = m_current_test_index;
    if (bSkippedCompare)
      this->m_test_results[compare_test_index] = ONX_ModelTest::Result::Skip;
            
    break;
  }

  Internal_EndCurrentTest();
}

/*  +----------------------------------------------------------------------------+
    |                                                                            |
    |                   RDK version 4 document archive format                    |
    |                                                                            |
    +================+==========================+================================+
    | Type           | Usage                    | ON_BinaryArchive function      |
    +================+==========================+================================+
    | ON__INT32      | RDK document version     | ReadInt()  / WriteInt()        |
    +----------------+--------------------------+--------------------------------+
    | ON__INT32      | Length of UTF8 XML block | ReadInt()  / WriteInt()        |
    +----------------+--------------------------+--------------------------------+
    | UTF8 chars     | Entire RDK document XML  | ReadChar() / WriteChar()       |
    +----------------+--------------------------+--------------------------------+
    | ON__INT32      | Number of embedded files | ReadInt()  / WriteInt()        |
    +----------------+--------------------------+--------------------------------+

     If the number of embedded files is not zero, then for each embedded file:

    +----------------+--------------------------+--------------------------------+
    | String         | Full path to file        | ReadString() / WriteString()   |
    +----------------+--------------------------+--------------------------------+
    | Bytes          | Compressed embedded file | Read / WriteCompressedBuffer() |
    +----------------+--------------------------+--------------------------------+
*/

static const wchar_t* RenderContentKindString(RenderContentKinds kind)
{
  switch (kind)
  {
  case RenderContentKinds::Material:    return ON_KIND_MATERIAL;
  case RenderContentKinds::Environment: return ON_KIND_ENVIRONMENT;
  case RenderContentKinds::Texture:     return ON_KIND_TEXTURE;
  default: ON_ASSERT(false); return L"";
  }
}

extern int ON_ComponentManifestImpl_TableCount(void);

ON_XMLNode& ON_GetRdkDocNode(const ON_3dmRenderSettings& rs);

ONX_ModelPrivate::ONX_ModelPrivate(ONX_Model& m)
  :
  m_model(m)
{
  // The TableCount enum in opennurbs_archive_manifest.cpp should always be
  // equal to ON_ModelComponent::Type::NumOf.
  ON_ASSERT(int(ON_ModelComponent::Type::NumOf) == ON_ComponentManifestImpl_TableCount());

  for (unsigned int i = 0; i < int(ON_ModelComponent::Type::NumOf); i++)
  {
    ONX_Model::ONX_ModelComponentList& list = m_mcr_lists.AppendNew();
    list.m_component_type = ON_ModelComponent::ComponentTypeFromUnsigned(i);
  }
}

ONX_ModelPrivate::~ONX_ModelPrivate()
{
}

ONX_Model_UserData* ONX_ModelPrivate::GetRDKDocumentUserData(int archive_3dm_version) const
{
  // Try to find existing RDK document user data.
  for (int i = 0; i < m_model.m_userdata_table.Count(); i++)
  {
    auto* pUserData = m_model.m_userdata_table[i];
    if (nullptr != pUserData)
    {
      if (::IsRDKDocumentInformation(*pUserData))
        return pUserData; // Found it.
    }
  }

  // Not found, so create it.
  auto* ud = new ONX_Model_UserData;
  ud->m_goo.m_typecode = TCODE_USER_RECORD;
  ud->m_uuid = RdkPlugInId();
  ud->m_usertable_3dm_version = archive_3dm_version;
  ud->m_usertable_opennurbs_version = ON::Version();

  ON_XMLRootNode root;
  PopulateDefaultRDKDocumentXML(root);
  SetRDKDocumentInformation(root.String(), *ud, archive_3dm_version);

  m_model.m_userdata_table.Append(ud);

  return ud;
}

void ONX_ModelPrivate::PopulateDefaultRDKDocumentXML(ON_XMLRootNode& root) const
{
  // Populate default render content kinds.
  GetRenderContentSectionNode(root, RenderContentKinds::Material);
  GetRenderContentSectionNode(root, RenderContentKinds::Environment);
  GetRenderContentSectionNode(root, RenderContentKinds::Texture);
}

bool ONX_ModelPrivate::GetRDKDocumentXML(ON_wString& xml, bool embedded_files, int archive_3dm_version) const
{
  // Gets the entire RDK document XML as a string in 'xml'. If 'embedded_files' is true,
  // ON_EmbeddedFile objects are created for each embedded file.

  const ONX_Model_UserData* pUserData = GetRDKDocumentUserData(archive_3dm_version);
  if (nullptr != pUserData)
  {
    ONX_Model* model = embedded_files ? &m_model : nullptr;
    if (GetEntireRDKDocument(*pUserData, xml, model))
      return true;
  }

  return false;
}

static bool ContentIsKind(const ON_RenderContent* pContent, RenderContentKinds kind)
{
  switch (kind)
  {
  case RenderContentKinds::Material:    return nullptr != ON_RenderMaterial   ::Cast(pContent);
  case RenderContentKinds::Environment: return nullptr != ON_RenderEnvironment::Cast(pContent);
  case RenderContentKinds::Texture:     return nullptr != ON_RenderTexture    ::Cast(pContent);
  }

  return false;
}

ON_XMLNode* ONX_ModelPrivate::GetPostEffectSectionNode(ON_XMLNode& docNode, ON_PostEffect::Types type) const
{
  ON_wString s = ON_RDK_DOCUMENT  ON_XML_SLASH  ON_RDK_SETTINGS  ON_XML_SLASH  ON_RDK_POST_EFFECTS  ON_XML_SLASH;
  s += ON_PostEffectTypeString(type);

  return docNode.CreateNodeAtPath(s);
}

ON_XMLNode* ONX_ModelPrivate::GetRenderContentSectionNode(ON_XMLNode& docNode, RenderContentKinds kind) const
{
  ON_wString s = ON_RDK_DOCUMENT  ON_XML_SLASH;
  s += RenderContentKindString(kind);
  s += ON_RDK_POSTFIX_SECTION;

  return docNode.CreateNodeAtPath(s);
}

bool ONX_ModelPrivate::CreateRenderContentFromXML(ON_XMLNode& model_node, RenderContentKinds kind)
{
  const ON_XMLNode* rc_section_node = GetRenderContentSectionNode(model_node, kind);
  if (nullptr == rc_section_node)
    return false;

  auto it = rc_section_node->GetChildIterator();

  const ON_XMLNode* rc_node = it.GetNextChild();
  while (nullptr != rc_node)
  {
    ON_RenderContent* rc = NewRenderContentFromNode(*rc_node);
    if (nullptr != rc)
    {
      // The name currently in the render content came from XML. It's been corrected if it was invalid,
      // but it still might be a duplicate of another one in the model, so we have to turn it into an
      // unused name if necessary.
      const ON_wString name = m_model.m_manifest.UnusedName(rc->ComponentType(), ON_nil_uuid, rc->Name(),
                                                            nullptr, nullptr, 0, nullptr);
      rc->SetName(name);

      const auto ref = m_model.AddModelComponent(*rc);
      auto* model_rc = ON_RenderContent::Cast(ref.ModelComponent());
      if (nullptr != model_rc)
      {
        SetModel(*model_rc, m_model);
      }

      delete rc;
    }

    rc_node = it.GetNextChild();
  }

  return true;
}

bool ONX_ModelPrivate::CreateXMLFromRenderContent(ON_XMLNode& model_node, RenderContentKinds kind) const
{
  ON_XMLNode* rc_section_node = GetRenderContentSectionNode(model_node, kind);
  if (nullptr == rc_section_node)
    return false;

  rc_section_node->RemoveAllChildren();

  ONX_ModelComponentIterator it(m_model, ON_ModelComponent::Type::RenderContent);
  const ON_ModelComponent* component = it.FirstComponent();
  while (nullptr != component)
  {
    const auto* rc = ON_RenderContent::Cast(component);
    if (nullptr != rc)
    {
      if (ContentIsKind(rc, kind))
      {
        SetRenderContentNodeRecursive(*rc, *rc_section_node);
      }
    }

    component = it.NextComponent();
  }

  return true;
}

bool ONX_ModelPrivate::PopulateRDKComponents(int archive_3dm_version)
{
  // Get the entire RDK document XML. This includes not only render contents
  // but also Sun, GroundPlane and other RDK document data. Ignore embedded files.
  ON_wString xml;
  if (!GetRDKDocumentXML(xml, true, archive_3dm_version))
    return false;

  // Read the entire XML into the document node.
  ON_XMLNode& doc_node = ON_GetRdkDocNode(m_model.m_settings.m_RenderSettings);
  const auto read = doc_node.ReadFromStream(xml, false, true);
  if (ON_XMLNode::ReadError == read)
    return false;

  // Create the render contents from the relevant nodes.
  CreateRenderContentFromXML(doc_node, RenderContentKinds::Material);
  CreateRenderContentFromXML(doc_node, RenderContentKinds::Environment);
  CreateRenderContentFromXML(doc_node, RenderContentKinds::Texture);

  // Create the mesh modifiers.
  CreateMeshModifiersFromXML(m_model, archive_3dm_version);

  return true;
}

bool ONX_ModelPrivate::UpdateRDKUserData(int archive_3dm_version)
{
  if (0 == archive_3dm_version)
    archive_3dm_version = ON_BinaryArchive::CurrentArchiveVersion();

  ON_XMLNode& doc_node = ON_GetRdkDocNode(m_model.m_settings.m_RenderSettings);

  // For each kind, convert the render content hierarchy to fresh XML.
  CreateXMLFromRenderContent(doc_node, RenderContentKinds::Material);
  CreateXMLFromRenderContent(doc_node, RenderContentKinds::Environment);
  CreateXMLFromRenderContent(doc_node, RenderContentKinds::Texture);

  // Convert the mesh modifier collection to fresh XML.
  CreateXMLFromMeshModifiers(m_model, archive_3dm_version);

  // Get the RDK document user data.
  ONX_Model_UserData* pUserData = GetRDKDocumentUserData(archive_3dm_version);
  if (nullptr == pUserData)
    return false; // Shouldn't happen because we were able to get the XML earlier.

  // Get the entire document XML as a string and set it to the user data.
  ON_wString xml = doc_node.String();
  pUserData->m_usertable_3dm_version = archive_3dm_version;
  SetRDKDocumentInformation(xml, *pUserData, archive_3dm_version);

  return true;
}

bool IsRDKDocumentInformation(const ONX_Model_UserData& docud)
{
  return (0 == ON_UuidCompare(RdkPlugInId(), docud.m_uuid)) && (docud.m_goo.m_value >= 4) && (nullptr != docud.m_goo.m_goo);
}

bool ONX_Model::IsRDKDocumentInformation(const ONX_Model_UserData& docud)
{
  return ::IsRDKDocumentInformation(docud);
}

static size_t ArchiveLengthUpToEmbeddedFiles(size_t utf8_length)
{
  //                    version             utf8_length         utf8_buf
  const size_t length = sizeof(ON__INT32) + sizeof(ON__INT32) + utf8_length;
  ON_ASSERT(length <= INT_MAX);

  return length;
}

bool ONX_Model::GetRDKEmbeddedFiles(const ONX_Model_UserData& docud, ON_ClassArray<ON_wString>& paths, ON_SimpleArray<unsigned char*>& embedded_files_as_buffers)
{
  ON_SimpleArray<size_t> dummy;
  return ::GetRDKEmbeddedFiles(docud, paths, embedded_files_as_buffers, dummy);
}

bool ONX_Model::GetRDKEmbeddedFiles(const ONX_Model_UserData& docud, ON_ClassArray<ON_wString>& paths, ON_SimpleArray<unsigned char*>& embedded_files_as_buffers, ON_SimpleArray<size_t>& buffer_sizes) // Static.
{
  return ::GetRDKEmbeddedFiles(docud, paths, embedded_files_as_buffers, buffer_sizes);
}

bool ONX_Model::GetRDKDocumentInformation(const ONX_Model_UserData& docud, ON_wString& xml) // Static.
{
  return ONX_ModelPrivate::GetEntireRDKDocument(docud, xml, nullptr);
}

static int SeekArchiveToEmbeddedFiles(ON_Read3dmBufferArchive& archive, int goo_length)
{
  // Skips over the bulk of the archive to arrive at the embedded files.
  // Then reads the number of embedded files and returns it. The archive
  // is then ready to read the first embedded file.

  if (!archive.ReadMode())
    return 0;

  // Read the version number. Must be 4.
  int version = 0;
  if (!archive.ReadInt(&version) || (4 != version))
    return 0;

  // Read the UTF8 data length.
  int utf8_length = 0;
  if (!archive.ReadInt(&utf8_length))
    return 0;

  // Validate the length.
  if (utf8_length <= 0)
    return 0;

  const auto length_so_far = ArchiveLengthUpToEmbeddedFiles(utf8_length);
  if (length_so_far > size_t(goo_length))
    return 0; // Sanity check.

  // Seek past the UTF8 data.
  if (!archive.SeekForward(utf8_length))
    return 0;

  // Read the number of embedded files.
  int num_embedded_files = 0;
  if (!archive.ReadInt(&num_embedded_files))
    return 0;

  return num_embedded_files;
}

static bool SeekArchivePastCompressedBuffer(ON_BinaryArchive& archive)
{
  // WARNING: This function has intimate knowledge of how ON_BinaryArchive::WriteCompressedBuffer() works.
  // It is my opinion that this function should really be a method on ON_BinaryArchive since only that
  // class should know how its own implementation works. JohnC, 2022AD.

  if (!archive.ReadMode())
    return false;

  bool rc = false;
  unsigned int buffer_crc0 = 0;
  char method = 0;

  size_t sizeof__outbuffer;
  if (!archive.ReadCompressedBufferSize(&sizeof__outbuffer))
    return false;

  if (0 == sizeof__outbuffer)
    return true;

  if (!archive.ReadInt(&buffer_crc0)) // 32 bit crc of uncompressed buffer
    return false;

  if (!archive.ReadChar(&method))
    return false;

  if (method != 0 && method != 1)
    return false;

  switch (method)
  {
  case 0: // uncompressed
    rc = archive.SeekForward(sizeof__outbuffer);
    break;

  case 1: // compressed
  {
    ON__UINT32 tcode = 0;
    ON__INT64  big_value = 0;
    rc = archive.BeginRead3dmBigChunk(&tcode, &big_value);
    if (rc)
      rc = archive.EndRead3dmChunk();
  }
  break;
  }

  return rc;
}

static bool ReadEmbeddedFilePathsFromArchive(ON_Read3dmBufferArchive& archive, int count, ON_ClassArray<ON_wString>& paths)
{
  // Reads the embedded file paths and skips over the data for 'count' embedded files. Must be called with
  // the archive position at the start of the first embedded file, right after the count of embedded files.
  if (0 == count)
    return false;

  for (int i = 0; i < count; i++)
  {
    ON_wString sPath;
    if (!archive.ReadString(sPath))
      return false;

    paths.Append(sPath);

    SeekArchivePastCompressedBuffer(archive);
  }

  return paths.Count() > 0;
}

bool ONX_Model::GetRDKEmbeddedFilePaths(const ONX_Model_UserData& docud, ON_ClassArray<ON_wString>& paths)
{
  if (!::IsRDKDocumentInformation(docud))
    return false;

  ON_Read3dmBufferArchive archive(docud.m_goo.m_value, docud.m_goo.m_goo, false, docud.m_usertable_3dm_version, docud.m_usertable_opennurbs_version);

  const int count = SeekArchiveToEmbeddedFiles(archive, docud.m_goo.m_value);
  if (!ReadEmbeddedFilePathsFromArchive(archive, count, paths))
    return false;

  return true;
}

bool GetRDKEmbeddedFiles(const ONX_Model_UserData& docud, ON_ClassArray<ON_wString>& paths, ON_SimpleArray<unsigned char*>& embedded_files_as_buffers, ON_SimpleArray<size_t>& buffer_sizes)
{
  if (!::IsRDKDocumentInformation(docud))
    return false;

  ON_Read3dmBufferArchive a(docud.m_goo.m_value, docud.m_goo.m_goo, false, docud.m_usertable_3dm_version, docud.m_usertable_opennurbs_version);

  const int count = SeekArchiveToEmbeddedFiles(a, docud.m_goo.m_value);
  if (0 == count)
    return false;

  int unpacked = 0;

  for (int i = 0; i < count; i++)
  {
    ON_wString sPath;
    if (!a.ReadString(sPath))
      return false;

    size_t size;
    if (!a.ReadCompressedBufferSize(&size))
      return false;

    auto* buffer = new unsigned char[size];
    bool bFailedCRC = false;
    if (a.ReadCompressedBuffer(size, buffer, &bFailedCRC))
    {
      if (!bFailedCRC)
      {
        embedded_files_as_buffers.Append(buffer);
        paths.Append(sPath);
        buffer_sizes.Append(size);
        unpacked++;
      }
      else
      {
        delete[] buffer;
      }
    }
  }

  return unpacked > 0;
}

bool ONX_Model::GetRDKEmbeddedFile(const ONX_Model_UserData& docud, const wchar_t* path, ON_SimpleArray<unsigned char>& bytes)
{
  if (!::IsRDKDocumentInformation(docud))
    return false;

  ON_Read3dmBufferArchive archive(docud.m_goo.m_value, docud.m_goo.m_goo, false, docud.m_usertable_3dm_version, docud.m_usertable_opennurbs_version);

  const auto count = SeekArchiveToEmbeddedFiles(archive, docud.m_goo.m_value);
  if (0 == count)
    return false;

  bool found = false;
  for (int i = 0; i < count; i++)
  {
    ON_wString sPath;
    if (!archive.ReadString(sPath))
      break;

    if (0 == sPath.ComparePath(path))
    {
      size_t size;
      if (!archive.ReadCompressedBufferSize(&size))
        break;

      bytes.Destroy();
      bytes.Reserve(size);

      bool bFailedCRC = false;
      bool bRet = archive.ReadCompressedBuffer(size, bytes.Array(), &bFailedCRC);

      if (!bRet || bFailedCRC)
        break;

      bytes.SetCount((int)size);

      found = true;
      break;
    }
    else
    {
      SeekArchivePastCompressedBuffer(archive);
    }
  }

  return found;
}

void ONX_ModelPrivate::RemoveAllEmbeddedFiles(ONX_Model& model)
{
  ON_SimpleArray<ON_UUID> a;
  const auto type = ON_ModelComponent::Type::EmbeddedFile;

  ONX_ModelComponentIterator it(model, type);
  const ON_ModelComponent* pComponent = it.FirstComponent();
  while (nullptr != pComponent)
  {
    a.Append(pComponent->Id());

    pComponent = it.NextComponent();
  }

  for (int i = 0; i < a.Count(); i++)
  {
    model.RemoveModelComponent(type, a[i]);
  }
}

bool ONX_ModelPrivate::GetEntireRDKDocument(const ONX_Model_UserData& docud, ON_wString& xml, ONX_Model* model) // Static.
{
  if (!::IsRDKDocumentInformation(docud))
    return false;

  ON_Read3dmBufferArchive archive(docud.m_goo.m_value, docud.m_goo.m_goo, false, docud.m_usertable_3dm_version, docud.m_usertable_opennurbs_version);

  int version = 0;
  if (!archive.ReadInt(&version))
    return false;

  if (1 == version)
  {
    // Version 1 was a UTF-16 string.
    if (!archive.ReadString(xml))
      return false;
  }
  else
  if ((3 == version) || (4 == version))
  {
    // Version 4 files are exactly the same as version 3, but with the addition of embedded files.

    // Version 3 and 4 is a UTF-8 string.
    int utf8_length = 0;
    if (!archive.ReadInt(&utf8_length))
      return false;

    if (utf8_length <= 0)
      return false;

    const size_t length_so_far = ArchiveLengthUpToEmbeddedFiles(utf8_length);
    if (length_so_far > size_t(docud.m_goo.m_value))
      return false; // Sanity check.

    ON_String s;
    s.SetLength(utf8_length);
    if (!archive.ReadChar(utf8_length, s.Array()))
      return false;

    if (s.IsNotEmpty())
    {
      const char* sArray = s.Array();
      unsigned int error_status = 0;
      auto wideLength = ON_ConvertUTF8ToWideChar(false, sArray, -1, 0, 0, &error_status, 0, 0, 0);
      if ((wideLength > 0) && (0 == error_status))
      {
        xml.SetLength(wideLength);
        ON_ConvertUTF8ToWideChar(false, sArray, -1, xml.Array(), wideLength+1, &error_status, 0, 0, 0);
      }

      if (0 != error_status)
      {
        ON_ERROR("RDK xml document settings is not a valid UTF-8 string.");
      }
    }

    if (nullptr != model)
    {
      RemoveAllEmbeddedFiles(*model);

      if (4 == version)
      {
        // Read the number of embedded files.
        int num_embedded_files = 0;
        if (!archive.ReadInt(&num_embedded_files))
          return false;

        // Create an ON_EmbeddedFile object for each embedded file.
        for (int i = 0; i < num_embedded_files; i++)
        {
          // We keep the embedded file object even if it fails to load; then it will have an error flag set.
          // See ON_EmbeddedFile::Error().
          ON_EmbeddedFile ef;
          ef.Read(archive);
          model->AddModelComponent(ef);
        }
      }
    }
  }

  return xml.Length() > 0;
}

bool ONX_ModelPrivate::SetRDKDocumentInformation(const wchar_t* xml, ONX_Model_UserData& docud, int archive_3dm_version) const
{
  ON_Write3dmBufferArchive archive(0, 0, docud.m_usertable_3dm_version, docud.m_usertable_opennurbs_version);

  // Write the version.
  int version = 4; // Where do I get this from?
  if (!archive.WriteInt(version))
    return false;

  // Convert the XML to UTF8 and write it to the archive.
  unsigned int error_status = 0;
  const int utf8_length = ON_ConvertWideCharToUTF8(false, xml, -1, 0, 0, &error_status, 0, 0, 0);

  { // BEGIN UTF8
    auto utf8 = std::unique_ptr<char[]>(new char[utf8_length]);
    char* utf8_buf = utf8.get();

    ON_ConvertWideCharToUTF8(false, xml, -1, utf8_buf, utf8_length, &error_status, 0, 0, 0);

    // Write the length of the UTF8 data.
    if (!archive.WriteInt(utf8_length))
      return false;

    // Write the UTF8 data.
    if (!archive.WriteChar(size_t(utf8_length), utf8_buf))
      return false;
  } // END UTF8

  const auto length_so_far = ArchiveLengthUpToEmbeddedFiles(utf8_length);
  ON_ASSERT(archive.SizeOfArchive() == length_so_far); // Sanity check.

  // Write the number of embedded files.
  const auto num_embedded_files = int(m_model.ActiveComponentCount(ON_ModelComponent::Type::EmbeddedFile));
  if (!archive.WriteInt(num_embedded_files))
    return false;

  // Write the embedded files to the archive.
  ONX_ModelComponentIterator it(m_model, ON_ModelComponent::Type::EmbeddedFile);
  const ON_ModelComponent* pComponent = it.FirstComponent();
  while (nullptr != pComponent)
  {
    const auto* embedded_file = ON_EmbeddedFile::Cast(pComponent);
    if (nullptr != embedded_file)
    {
      embedded_file->Write(archive);
    }

    pComponent = it.NextComponent();
  }

  // Delete the old goo.
  if (nullptr != docud.m_goo.m_goo)
    onfree(docud.m_goo.m_goo);

  // Allocate the new goo and copy the archive to it.
  const auto length_goo = archive.SizeOfArchive();
  docud.m_goo.m_goo = (unsigned char*)onmalloc(length_goo);
  docud.m_goo.m_value = int(length_goo);
  memcpy(docud.m_goo.m_goo, archive.Buffer(), length_goo);

  return true;
}

// Object user data

static ON_UserData* RDKObjectUserDataHelper(const ON_UserData* objectud)
{
  if (nullptr == objectud)
      return nullptr;

  if (0 == ON_UuidCompare(objectud->m_application_uuid, RdkPlugInId()))
  {
    if (0 != ON_UuidCompare(objectud->m_userdata_uuid, ON_RdkUserData::Uuid()))
        return nullptr; // Not RDK user data.

    return const_cast<ON_UserData*>(objectud); // RDK user data -- used for decals.
  }

  return nullptr;
}

static bool IsMeshModifierObjectUserData(ON_UserData& objectud)
{
  if (0 == ON_UuidCompare(objectud.m_application_uuid, ON_MeshModifier::PlugInId()))
    return true; // User data from Displacement plug-in.

  return false;
}

bool ONX_Model::IsRDKObjectInformation(const ON_UserData& objectud) // Static.
{
  return nullptr != RDKObjectUserDataHelper(&objectud);
}

static bool CreateArchiveBufferFromXML(const ON_wString& xml, ON_Buffer& buf, int archive_3dm_version)
{
  const auto archive_opennurbs_version_number = ON::Version(); // I don't know if this is correct.

  ON_Write3dmBufferArchive archive(0, 0, archive_3dm_version, archive_opennurbs_version_number);

  int version = 2; // Not sure if this is correct.
  if (!archive.WriteInt(version))
    return false;

  const wchar_t* wsz = static_cast<const wchar_t*>(xml);

  unsigned int error_status = 0;
  const int num_chars = ON_ConvertWideCharToUTF8(false, wsz, -1, nullptr, 0, &error_status, 0, 0, nullptr);

  auto p = std::unique_ptr<char[]>(new char[size_t(num_chars) + 1]);
  char* pBuffer = p.get();
  ON_ConvertWideCharToUTF8(false, wsz, -1, pBuffer, num_chars + 1, &error_status, 0, 0, nullptr);

  if (0 != error_status)
  {
    ON_ERROR("XML is not a valid UTF-8 string.");
    return false;
  }

  int len = num_chars * sizeof(char);
  if (!archive.WriteInt(len))
    return false;

  if (!archive.WriteChar(len, pBuffer))
    return false;

  buf.Write(archive.SizeOfArchive(), archive.Buffer());
  buf.SeekFromStart(0);

  return true;
}

bool SetXMLToUserData(const ON_wString& xml, ON_UserData& ud, int archive_3dm_version)
{
  ON_Buffer buf;
  if (!CreateArchiveBufferFromXML(xml, buf, archive_3dm_version))
    return false;

  ON_BinaryArchiveBuffer arc(ON::archive_mode::read, &buf);
  ud.Read(arc);

  return true;
}

bool SetRDKObjectInformation(ON_Object& object, const ON_wString& xml, int archive_3dm_version)
{
  // Create a buffer from the XML.
  ON_Buffer buf;
  if (!CreateArchiveBufferFromXML(xml, buf, archive_3dm_version))
    return false;

  const auto archive_opennurbs_version = ON::Version(); // I don't know if this is correct.

  // Create an archive from the buffer.
  ON_BinaryArchiveBuffer archive(ON::archive_mode::read, &buf);
  archive.SetArchive3dmVersion(archive_3dm_version);
  ON_SetBinaryArchiveOpenNURBSVersion(archive, archive_opennurbs_version);

  // Try to find existing user data.
  ON_UserData* rdk_ud = nullptr;

  for (ON_UserData* ud = object.FirstUserData(); (nullptr != ud) && (nullptr == rdk_ud); ud = ud->Next())
  {
    rdk_ud = RDKObjectUserDataHelper(ud);
  }

  if (nullptr != rdk_ud)
  {
    // Found it, so read the archive into it.
    rdk_ud->Read(archive);
  }
  else
  {
    // No user data found; create a new one and read the archive into it.
    auto* ud = new ON_RdkUserData;
    ud->Read(archive);

    if (!object.AttachUserData(ud))
    {
      delete ud;
      return false;
    }
  }

  return true;
}

static bool GetRDKObjectInformation(const ON_Object& object, ON_wString& xml, int archive_3dm_version)
{
  if (0 == archive_3dm_version)
    archive_3dm_version = ON_BinaryArchive::CurrentArchiveVersion();

  xml.SetLength(0);

  const ON_UserData* rdk_ud = nullptr;
  const auto* ud = ON_UserData::Cast(&object);
  if (nullptr != ud)
  {
    rdk_ud = RDKObjectUserDataHelper(ud);
  }
  else
  {
    for (ud = object.FirstUserData(); (nullptr != ud) && (nullptr == rdk_ud); ud = ud->Next())
    {
      rdk_ud = RDKObjectUserDataHelper(ud);
    }
  }

  if (nullptr == rdk_ud)
    return false;

  ON_Buffer buf;
  ON_BinaryArchiveBuffer arc(ON::archive_mode::write, &buf);
  rdk_ud->Write(arc);

  const auto sizeof_buffer = buf.Size();

  auto p = std::unique_ptr<ON__UINT8[]>(new ON__UINT8[size_t(sizeof_buffer)]);
  ON__UINT8* buffer = p.get();
  buf.SeekFromStart(0);
  buf.Read(sizeof_buffer, buffer);

  const unsigned int archive_opennurbs_version_number = ON::Version();
  ON_Read3dmBufferArchive archive(size_t(sizeof_buffer), buffer, false, archive_3dm_version, archive_opennurbs_version_number);

  int version = 0;
  if (!archive.ReadInt(&version))
    return false;

  if (1 == version)
  {
    // Version 1 was a UTF-16 string.
    if (!archive.ReadString(xml))
      return false;
  }
  else
  if (2 == version)
  {
    // Version 2 is a UTF-8 string.
    int len = 0;
    if (!archive.ReadInt(&len))
      return false;

    if (len <= 0)
      return false;

    if (size_t(len + 4) > sizeof_buffer) // JohnC asks: What does the 4 signify?
      return false;

    ON_SimpleArray<char> s;
    s.Reserve(size_t(len) + 1);
    s.SetCount(len + 1);
    s[len] = 0;

    char* sArray = s.Array();
    if (nullptr == sArray)
      return false;

    if (!archive.ReadChar(len, sArray))
      return false;

    if (0 == sArray[0])
      return false;

    unsigned int error_status = 0;
    const int num_chars = ON_ConvertUTF8ToWideChar(false, sArray, -1, 0, 0, &error_status, 0, 0, 0);
    if ((num_chars > 0) && (0 == error_status))
    {
      xml.SetLength(size_t(num_chars) + 2);
      ON_ConvertUTF8ToWideChar(false, sArray, -1, xml.Array(), num_chars + 1, &error_status, 0, 0, 0);
      xml.SetLength(num_chars);
    }
    else
    {
      xml.SetLength(0);
      ON_ERROR("RDK xml object information is not a valid UTF-8 string.");
    }
  }

  return xml.Length() > 0;
}

bool GetEntireDecalXML(const ON_3dmObjectAttributes& attr, ON_XMLRootNode& xmlOut)
{
  // Get the entire XML off of the attributes user data. At the moment (V8) this can only contain decals.
  ON_wString xml;
  if (!GetRDKObjectInformation(attr, xml, 0))
    return false;  // No XML on attributes.

  // Read the XML into a root node.
  if (ON_XMLNode::ReadError == xmlOut.ReadFromStream(xml))
    return false; // Failed to read XML.

  return true;
}

static bool GetMeshModifierUserDataXML(ON_UserData& ud, ON_wString& xml, int archive_3dm_version)
{
  ON_Buffer buf;
  ON_BinaryArchiveBuffer arc(ON::archive_mode::write, &buf);
  ud.Write(arc);

  const ON__UINT64 sizeof_buffer = buf.Size();

  auto p = std::unique_ptr<ON__UINT8[]>(new ON__UINT8[size_t(sizeof_buffer)]);
  ON__UINT8* buffer = p.get();
  buf.SeekFromStart(0);
  buf.Read(sizeof_buffer, buffer);

  const auto archive_opennurbs_version_number = ON::Version();
  ON_Read3dmBufferArchive archive(size_t(sizeof_buffer), buffer, false, archive_3dm_version, archive_opennurbs_version_number);

  int version = 0;
  if (!archive.ReadInt(&version))
    return false;

  if (1 == version)
  {
    // Version 1 was a UTF-16 string.
    if (!archive.ReadString(xml))
      return false;
  }
  else
  if (2 == version)
  {
    // Version 2 is a UTF-8 string.
    int len = 0;
    if (!archive.ReadInt(&len))
      return false;

    if (len <= 0)
      return false;

    if (size_t(len + 4) > sizeof_buffer) // JohnC asks: What does the 4 signify?
      return false;

    ON_SimpleArray<char> s;
    s.Reserve(size_t(len) + 1);
    s.SetCount(len + 1);
    s[len] = 0;

    char* sArray = s.Array();
    if (nullptr == sArray)
      return false;

    if (!archive.ReadChar(len, sArray))
      return false;

    if (0 == sArray[0])
      return false;

    unsigned int error_status = 0;
    const int num_chars = ON_ConvertUTF8ToWideChar(false, sArray, -1, 0, 0, &error_status, 0, 0, 0);
    if ((num_chars > 0) && (0 == error_status))
    {
      xml.SetLength(size_t(num_chars) + 2);
      ON_ConvertUTF8ToWideChar(false, sArray, -1, xml.Array(), num_chars + 1, &error_status, 0, 0, 0);
      xml.SetLength(num_chars);
    }
    else
    {
      xml.SetLength(0);
      ON_ERROR("Mesh modifier xml object information is not a valid UTF-8 string.");
    }
  }

  return true;
}

bool ONX_Model::GetRDKObjectInformation(const ON_Object& object, ON_wString& xml) // Static.
{
  // Deprecated; only for backward compatibility.
  return ::GetRDKObjectInformation(object, xml, ON_BinaryArchive::CurrentArchiveVersion());
}

bool GetMeshModifierObjectInformation(const ON_Object& object, ON_wString& xml, int archive_3dm_version)
{
  xml = L"";

  // The mesh modifiers are stored in separate user data items. We must get each one's
  // XML and combine it into a single XML node containing the entire information for all
  // mesh modifiers on this object.

  ON_XMLRootNode entire;

  ON_UserData* ud = object.FirstUserData();
  while (nullptr != ud)
  {
    if (IsMeshModifierObjectUserData(*ud))
    {
      ON_wString ud_xml;
      GetMeshModifierUserDataXML(*ud, ud_xml, archive_3dm_version);

      ON_XMLRootNode root;
      root.ReadFromStream(ud_xml);
      ON_XMLNode* mm_node = root.FirstChild();
      if (nullptr != mm_node)
      {
        root.DetachChild(*mm_node);
        entire.AttachChildNode(mm_node);
      }
    }

    ud = ud->Next();
  }

  if (entire.FirstChild() == nullptr)
    return false;

  // Return the entire XML for all mesh modifiers on this object.
  xml = entire.String();

  return true;
}

static ON_UserData* GetMeshModifierUserData(ON_Object& object, const ON_UUID& uuid_mm)
{
  ON_UserData* existing_ud = object.FirstUserData();
  while (nullptr != existing_ud)
  {
    if (existing_ud->m_userdata_uuid == uuid_mm)
      return existing_ud;

    existing_ud = existing_ud->Next();
  }

  // Not found so create it.
  ON_XMLUserData* new_ud = nullptr;

       if (uuid_mm == ON_DisplacementUserData::Uuid())  new_ud = new ON_DisplacementUserData;
  else if (uuid_mm == ON_EdgeSofteningUserData::Uuid()) new_ud = new ON_EdgeSofteningUserData;
  else if (uuid_mm == ON_ThickeningUserData::Uuid())    new_ud = new ON_ThickeningUserData;
  else if (uuid_mm == ON_CurvePipingUserData::Uuid())   new_ud = new ON_CurvePipingUserData;
  else if (uuid_mm == ON_ShutLiningUserData::Uuid())    new_ud = new ON_ShutLiningUserData;
  else ON_ASSERT(false);

  if (nullptr != new_ud)
  {
    new_ud->SetToDefaults(); // This doesn't work because the XML gets overwritten by the cached XML.
    // In fact, having cached XML in this and decals is the reason why the systems are wrong.
    // NO! LIGHT BULB MOMENT says that's not why it's wrong. Something else is wrong here.
    // I'm about to fix the decals to not have cached XML and directly use the user data. NO! After
    // that I'll do the same for mesh modifiers. NO! Then, this should work because there is no longer
    // an XML cache to overwrite the new defaults in the user data's XML. NO!

    if (!object.AttachUserData(new_ud))
    {
      delete new_ud;
      new_ud = nullptr;
    }
  }

  return new_ud;
}

void SetMeshModifierObjectInformation(ON_Object& object, const ON_MeshModifier* mm, int archive_3dm_version)
{
  if (nullptr == mm)
    return; // Can't create user data for non-existent mesh modifiers.

  ON_XMLRootNode root;
  mm->AddChildXML(root);

  ON_UserData* ud = GetMeshModifierUserData(object, mm->Uuid());
  if (nullptr != ud)
  {
    SetXMLToUserData(root.String(), *ud, archive_3dm_version);
  }
}
