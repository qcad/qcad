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

ON_OBJECT_IMPLEMENT(ON_Environment, ON_Object, "94BCA4D5-0FC7-435E-95F9-22F3927F9B2E");

class ON_Environment::CImpl
{
public:
  CImpl();
  CImpl(const CImpl& src);

public:
  ON_Color m_back_col;
  ON_Texture m_back_image;
  BackgroundProjections m_back_proj = BackgroundProjections::Planar;
};

ON_Environment::CImpl::CImpl()
  :
  m_back_col(ON_Color(160, 160, 160))
{
}

ON_Environment::CImpl::CImpl(const CImpl& src)
{
  m_back_col   = src.m_back_col;
  m_back_proj  = src.m_back_proj;
  m_back_image = src.m_back_image;
}

ON_Environment::ON_Environment()
{
  m_impl = new CImpl;
}

ON_Environment::ON_Environment(const ON_Environment& src)
{
  m_impl = new CImpl(*src.m_impl);
}

ON_Environment::~ON_Environment()
{
  delete m_impl;
  m_impl = nullptr;
}

static ON__UINT32 CRCOnlyRGB(ON__UINT32 current_remainder, const ON_Color& c)
{
  const auto x = (unsigned int)c & 0x00FFFFFF;
  return ON_CRC32(current_remainder, sizeof(x), &x);
}

ON__UINT32 ON_Texture_CRC(const ON_Texture& tex)
{
  ON_wString file(tex.m_image_file_reference.FullPath());
#ifdef ON_RUNTIME_WIN
  file.MakeLower();
#endif
  ON__UINT32 crc = file.DataCRC(0);

  crc = ON_CRC32(crc, sizeof(tex.m_mapping_channel_id), &tex.m_mapping_channel_id);

  crc = ON_CRC32(crc, sizeof(tex.m_bOn),       &tex.m_bOn);
  crc = ON_CRC32(crc, sizeof(tex.m_type),      &tex.m_type);
  crc = ON_CRC32(crc, sizeof(tex.m_minfilter), &tex.m_minfilter);
  crc = ON_CRC32(crc, sizeof(tex.m_magfilter), &tex.m_magfilter);
  crc = ON_CRC32(crc, sizeof(tex.m_wrapu),     &tex.m_wrapu);
  crc = ON_CRC32(crc, sizeof(tex.m_wrapv),     &tex.m_wrapv);
  crc = ON_CRC32(crc, sizeof(tex.m_wrapw),     &tex.m_wrapw);

  crc = CRCOnlyRGB(crc, tex.m_border_color);
  crc = CRCOnlyRGB(crc, tex.m_transparent_color);
  crc = CRCOnlyRGB(crc, tex.m_blend_constant_RGB);

  crc = ON_CRC32(crc, sizeof(tex.m_blend_order), &tex.m_blend_order);

  const double amount = int(tex.m_blend_constant_A * 100.0) / 100.0;
  crc = ON_CRC32(crc, sizeof(amount), &amount);

  crc = ON_CRC32(crc, sizeof(tex.m_bump_scale), &tex.m_bump_scale);
  crc = ON_CRC32(crc, sizeof(tex.m_uvw),        &tex.m_uvw);

  crc = ON_CRC32(crc, sizeof(tex.m_blend_A0),   &tex.m_blend_A0);
  crc = ON_CRC32(crc, sizeof(tex.m_blend_RGB0), &tex.m_blend_RGB0);
  crc = ON_CRC32(crc, sizeof(tex.m_blend_A1),   &tex.m_blend_A1);
  crc = ON_CRC32(crc, sizeof(tex.m_blend_RGB1), &tex.m_blend_RGB1);
  crc = ON_CRC32(crc, sizeof(tex.m_blend_A2),   &tex.m_blend_A2);
  crc = ON_CRC32(crc, sizeof(tex.m_blend_RGB2), &tex.m_blend_RGB2);
  crc = ON_CRC32(crc, sizeof(tex.m_blend_A3),   &tex.m_blend_A3);
  crc = ON_CRC32(crc, sizeof(tex.m_blend_RGB3), &tex.m_blend_RGB3);

  crc = ON_CRC32(crc, sizeof(tex.m_bTreatAsLinear), &tex.m_bTreatAsLinear);

	return crc;
}

bool ON_Environment::operator == (const ON_Environment& env) const
{
  if (m_impl->m_back_col < env.m_impl->m_back_col)
    return false;

  if (m_impl->m_back_col > env.m_impl->m_back_col)
    return false;

  if (m_impl->m_back_proj != env.m_impl->m_back_proj)
    return false;

  if (ON_Texture_CRC(m_impl->m_back_image) != ON_Texture_CRC(env.m_impl->m_back_image))
    return false;

  return true;
}

bool ON_Environment::operator != (const ON_Environment& env) const
{
  return !(operator == (env));
}

const ON_Environment& ON_Environment::operator = (const ON_Environment& src)
{
  if (this != &src)
  {
    delete m_impl;
    m_impl = new CImpl(*src.m_impl);
  }

  return *this;
}

ON_Color ON_Environment::BackgroundColor(void) const
{
  return m_impl->m_back_col;
}

void ON_Environment::SetBackgroundColor(const ON_Color& col)
{
  m_impl->m_back_col = col;
}

const ON_Texture& ON_Environment::BackgroundImage(void) const
{
  return m_impl->m_back_image;
}

void ON_Environment::SetBackgroundImage(const ON_Texture& tex)
{
  m_impl->m_back_image = tex;
}

ON_Environment::BackgroundProjections ON_Environment::BackgroundProjection(void) const
{
  return m_impl->m_back_proj;
}

void ON_Environment::SetBackgroundProjection(ON_Environment::BackgroundProjections proj)
{
  m_impl->m_back_proj = proj;
}

ON_Environment::BackgroundProjections ON_Environment::ProjectionFromString(const wchar_t* wsz) // Static.
{
  if (0 == on_wcsicmp(ON_ENVIRONMENT_PROJECTION_PLANAR, wsz))        return BackgroundProjections::Planar;
  if (0 == on_wcsicmp(ON_ENVIRONMENT_PROJECTION_SPHERICAL, wsz))     return BackgroundProjections::Spherical;
  if (0 == on_wcsicmp(ON_ENVIRONMENT_PROJECTION_EMAP, wsz))          return BackgroundProjections::Emap;
  if (0 == on_wcsicmp(ON_ENVIRONMENT_PROJECTION_BOX, wsz))           return BackgroundProjections::Box;
  if (0 == on_wcsicmp(ON_ENVIRONMENT_PROJECTION_LIGHT_PROBE, wsz))   return BackgroundProjections::LightProbe;
  if (0 == on_wcsicmp(ON_ENVIRONMENT_PROJECTION_CUBE_MAP, wsz))      return BackgroundProjections::CubeMap;
  if (0 == on_wcsicmp(ON_ENVIRONMENT_PROJECTION_CUBE_MAP_VERT, wsz)) return BackgroundProjections::VerticalCrossCubeMap;
  if (0 == on_wcsicmp(ON_ENVIRONMENT_PROJECTION_CUBE_MAP_HORZ, wsz)) return BackgroundProjections::HorizontalCrossCubeMap;
  if (0 == on_wcsicmp(ON_ENVIRONMENT_PROJECTION_HEMISPHERICAL, wsz)) return BackgroundProjections::Hemispherical;

  ON_ASSERT(false);
  return BackgroundProjections::Planar;
}

const wchar_t* ON_Environment::StringFromProjection(BackgroundProjections proj) // Static.
{
  switch (proj)
  {
  case BackgroundProjections::Planar:                 return ON_ENVIRONMENT_PROJECTION_PLANAR;
  case BackgroundProjections::Spherical:              return ON_ENVIRONMENT_PROJECTION_SPHERICAL;
  case BackgroundProjections::Emap:                   return ON_ENVIRONMENT_PROJECTION_EMAP;
  case BackgroundProjections::Box:                    return ON_ENVIRONMENT_PROJECTION_BOX;
  case BackgroundProjections::LightProbe:             return ON_ENVIRONMENT_PROJECTION_LIGHT_PROBE;
  case BackgroundProjections::CubeMap:                return ON_ENVIRONMENT_PROJECTION_CUBE_MAP;
  case BackgroundProjections::VerticalCrossCubeMap:   return ON_ENVIRONMENT_PROJECTION_CUBE_MAP_VERT;
  case BackgroundProjections::HorizontalCrossCubeMap: return ON_ENVIRONMENT_PROJECTION_CUBE_MAP_HORZ;
  case BackgroundProjections::Hemispherical:          return ON_ENVIRONMENT_PROJECTION_HEMISPHERICAL;
  default: break;
  }

  ON_ASSERT(false);
  return ON_ENVIRONMENT_PROJECTION_PLANAR;
}

void* ON_Environment::EVF(const wchar_t* wszFunc, void* pvData)
{
  return nullptr;
}

ON_UUID RdkPlugInId(void)
{
  static ON_UUID uuid = { 0x16592D58, 0x4A2F, 0x401D, { 0xBF, 0x5E, 0x3B, 0x87, 0x74, 0x1C, 0x1B, 0x1B } };
  return uuid;
}

class ON_RenderContentPrivate
{
public:
  ON_RenderContentPrivate(ON_RenderContent& rc, const wchar_t* kind);
  virtual ~ON_RenderContentPrivate();

  void SetXMLNode(const ON_XMLNode& node);

  const ON_XMLNode* XMLNode_Simulation(void) const;

  ON_RenderContent& TopLevel(void);

  bool AddChild(ON_RenderContent& rc);
  void DeleteAllChildren(void);

  ON_XMLVariant GetPropertyValue(const wchar_t* name) const;
  void SetPropertyValue(const wchar_t* name, const ON_XMLVariant& value);

  ON_RenderContent* FindChild(const wchar_t* child_slot_name) const;
  bool SetChild(ON_RenderContent* child, const wchar_t* child_slot_name);
  bool ChangeChild(ON_RenderContent* old_child, ON_RenderContent* new_child);

public:
  void InternalSetPropertyValue(const wchar_t* name, const ON_XMLVariant& value);

  static void SetRenderContentNodeRecursive(const ON_RenderContent& rc, ON_XMLNode& node);
  static void BuildXMLHierarchy(const ON_RenderContent& rc, ON_XMLNode& node);
  static ON_XMLNode* NewXMLNodeRecursive(const ON_RenderContent& rc);
  static void SetModel(const ON_RenderContent& rc, ONX_Model& model);
  static ON_RenderContent* NewRenderContentFromNode(const ON_XMLNode& node);

private:
  ON_RenderContent* FindLastChild(void) const;
  ON_RenderContent* FindPrevSibling(ON_RenderContent* child) const;

public:
  ONX_Model* m_model = nullptr;
  ON_XMLNode m_node;
  ON_RenderContent& m_render_content;
  ON_RenderContent* m_parent = nullptr;
  ON_RenderContent* m_first_child = nullptr;
  ON_RenderContent* m_next_sibling = nullptr;
  mutable std::recursive_mutex m_mutex;
};

ON_RenderContentPrivate::ON_RenderContentPrivate(ON_RenderContent& rc, const wchar_t* kind)
  :
  m_node(kind),
  m_render_content(rc)
{
}

ON_RenderContentPrivate::~ON_RenderContentPrivate()
{
  DeleteAllChildren();
}

const ON_XMLNode* ON_RenderContentPrivate::XMLNode_Simulation(void) const
{
  return m_node.GetNamedChild(ON_RENDER_CONTENT_SIMULATION);
}

ON_XMLVariant ON_RenderContentPrivate::GetPropertyValue(const wchar_t* name) const
{
  // Gets a property from the content node. This is one of:
  //
  // - the material node <material... >
  // - the environment node <environment... >
  // - the texture node <texture... >

  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  ON_XMLVariant v;

  const ON_XMLProperty* pProp = m_node.GetNamedProperty(name);
  if (nullptr != pProp)
  {
    v = pProp->GetValue();
  }

  return v;
}

void ON_RenderContentPrivate::SetPropertyValue(const wchar_t* name, const ON_XMLVariant& value)
{
  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  InternalSetPropertyValue(name, value);
}

void ON_RenderContentPrivate::InternalSetPropertyValue(const wchar_t* name, const ON_XMLVariant& value)
{
  // Sets a property on the content node. This is one of:
  //
  // - the material node <material... >
  // - the environment node <environment... >
  // - the texture node <texture... >

  ON_XMLProperty* pProp = m_node.GetNamedProperty(name);
  if (nullptr != pProp)
  {
    pProp->SetValue(value);
  }
  else
  {
    pProp = m_node.AttachProperty(new ON_XMLProperty(name, value));
  }
}

static void EnsureNameValid(ON_wString& name)
{
  // 29th November 2023 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-78603
  // Component names cannot begin with '(', ')', '[', ']', '{', '}' or ' '.
  // Component names should not be multiline.
  // I'm also going to disallow ':' because that has a special meaning in the name and
  // render content does not use that feature.

  ON_wString name_copy = name;
  name = L"";

  bool first = true;
  const int len = name_copy.Length();
  for (int i = 0; i < len; i++)
  {
    wchar_t c = name_copy[i];
    if (first)
    {
      if ( c == L' '                ) continue;
      if ((c == L'(') || (c == L')')) continue;
      if ((c == L'[') || (c == L']')) continue;
      if ((c == L'{') || (c == L'}')) continue;

      first = false;
    }

    // Replace control codes with a space. Includes CR/LF.
    if (c < L' ')
      c = L' ';

    name += c;
  }

  // 2024-08-27 : kike@mcneel.com
  // `ON_ModelComponent::IsValidComponentName` allows ':'.
  // The hole point of https://mcneel.myjetbrains.com/youtrack/issue/RH-78603
  // is to ensure all type names has same restrictions.
  // 
  //// Also disallow ':' inside the name.
  //name.Replace(':', ' ');

  name.TrimLeftAndRight();
}

void ON_RenderContentPrivate::SetXMLNode(const ON_XMLNode& node)
{
  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  // Copy the incoming XML node. The render content will only store a copy of its own XML, so
  // we will have to prune this copy as we find children and create render content children
  // for all the XML children.
  ON_XMLNode node_copy = node;

  // Iterate over the child nodes of the XML node being set to this content.
  auto it = node_copy.GetChildIterator();
  ON_XMLNode* child_node = nullptr;
  while (nullptr != (child_node = it.GetNextChild()))
  {
    // See if the child node is a content node.
    const ON_wString& name = child_node->TagName();
    if ((ON_KIND_MATERIAL == name) || (ON_KIND_ENVIRONMENT == name) || (ON_KIND_TEXTURE == name))
    {
      // Yes, so we are going to add a new render content to this hierarchy (recursively)
      // and remove this child node from the copy of the XML node.
      ON_RenderContent* child_rc = NewRenderContentFromNode(*child_node);
      if (nullptr != child_rc)
      {
        // Add the new content as a child of this content.
        AddChild(*child_rc);
      }

      delete node_copy.DetachChild(*child_node);
    }
  }

  // Copy the pruned copy of the XML node. This node does not have any child content nodes.
  m_node = node_copy;

  // Copy the XML instance name to the component name after validating it.
  ON_wString name = GetPropertyValue(ON_RENDER_CONTENT_INSTANCE_NAME).AsString();

  // 29th November 2023 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-78603
  if (!ON_ModelComponent::IsValidComponentName(name))
  {
    EnsureNameValid(name);
  }

  m_render_content.SetName(name);

  // Copy the XML instance id to the component id.
  m_render_content.SetId(GetPropertyValue(ON_RENDER_CONTENT_INSTANCE_ID).AsUuid());
}

bool ON_RenderContentPrivate::AddChild(ON_RenderContent& child)
{
  if ((nullptr != child._private->m_model) || (nullptr != child._private->m_parent) || (nullptr != child._private->m_next_sibling))
    return false;

  if (nullptr == m_first_child)
  {
    m_first_child = &child;
  }
  else
  {
    ON_RenderContent* last_child = FindLastChild();
    if (nullptr == last_child)
      return false;

    last_child->_private->m_next_sibling = &child;
  }

  child._private->m_next_sibling = nullptr;
  child._private->m_parent = &m_render_content;

  return true;
}

void ON_RenderContentPrivate::DeleteAllChildren(void)
{
  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  if (nullptr == m_first_child)
    return;

  ON_RenderContent* child_rc = m_first_child;
  while (nullptr != child_rc)
  {
    auto* delete_rc = child_rc;
    child_rc = child_rc->_private->m_next_sibling;
    delete delete_rc;
  }

  m_first_child = nullptr;
}

ON_RenderContent* ON_RenderContentPrivate::FindLastChild(void) const
{
  ON_RenderContent* result = nullptr;

  ON_RenderContent* candidate = m_first_child;
  while (nullptr != candidate)
  {
    result = candidate;
    candidate = candidate->_private->m_next_sibling;
  }

  return result;
}

ON_RenderContent* ON_RenderContentPrivate::FindPrevSibling(ON_RenderContent* child) const
{
  if (child != m_first_child)
  {
    ON_RenderContent* candidate = m_first_child;
    while (nullptr != candidate)
    {
      if (child == candidate->_private->m_next_sibling)
        return candidate;

      candidate = candidate->_private->m_next_sibling;
    }
  }

  return nullptr;
}

ON_RenderContent& ON_RenderContentPrivate::TopLevel(void)
{
  if (nullptr != m_parent)
  {
    return m_parent->_private->TopLevel();
  }

  return m_render_content;
}

bool ON_RenderContentPrivate::ChangeChild(ON_RenderContent* old_child, ON_RenderContent* new_child)
{
  if (nullptr == old_child)
    return false;

  if (old_child == m_first_child)
  {
    if (nullptr != new_child)
    {
      m_first_child = new_child;
    }
    else
    {
      m_first_child = old_child->_private->m_next_sibling;
    }
  }
  else
  {
    const ON_RenderContent* prev_sibling = FindPrevSibling(old_child);
    if (nullptr == prev_sibling)
      return false;

    if (nullptr != new_child)
    {
      prev_sibling->_private->m_next_sibling = new_child;
    }
    else
    {
      prev_sibling->_private->m_next_sibling = old_child->_private->m_next_sibling;
    }
  }

  if (nullptr != new_child)
  {
    new_child->_private->m_next_sibling = old_child->_private->m_next_sibling;
    new_child->_private->m_parent = old_child->_private->m_parent;
  }

  delete old_child;

  return true;
}

ON_RenderContent* ON_RenderContentPrivate::FindChild(const wchar_t* child_slot_name) const
{
  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  ON_RenderContent* child_rc = m_first_child;
  while (nullptr != child_rc)
  {
    if (child_rc->ChildSlotName() == child_slot_name)
      return child_rc;

    child_rc = child_rc->_private->m_next_sibling;
  }

  return nullptr;
}

bool ON_RenderContentPrivate::SetChild(ON_RenderContent* child, const wchar_t* child_slot_name)
{
  std::lock_guard<std::recursive_mutex> lg(m_mutex);

  if (nullptr != child)
  {
    if (nullptr != child->_private->m_model)
      return false;

    if (nullptr != child->_private->m_parent)
      return false;

    if ((nullptr == child_slot_name) || (0 == child_slot_name[0]))
      return false;

    child->_private->SetPropertyValue(ON_RENDER_CONTENT_CHILD_SLOT_NAME, child_slot_name);
  }

  // Get any existing child with the same child slot name (may be null).
  auto* existing_child = FindChild(child_slot_name);
  if (nullptr != existing_child)
  {
    // There is an existing child with the same child slot name; replace it.
    if (!ChangeChild(existing_child, child)) // Deletes existing_child.
      return false;
  }
  else
  {
    // No existing child; just add the new one.
    if (nullptr != child)
    {
      if (!AddChild(*child))
        return false;
    }
  }

  if (nullptr != child)
  {
    auto* pModel = TopLevel()._private->m_model;
    child->_private->m_model = pModel;
  }

  return true;
}

void ON_RenderContentPrivate::SetRenderContentNodeRecursive(const ON_RenderContent& rc, ON_XMLNode& node) // Static.
{
  // Copy the component name to the XML instance name.
  rc._private->SetPropertyValue(ON_RENDER_CONTENT_INSTANCE_NAME, rc.Name());

  // Copy the component id to the XML instance id.
  rc._private->SetPropertyValue(ON_RENDER_CONTENT_INSTANCE_ID, rc.Id());

  auto* child_node = new ON_XMLNode(rc.XMLNode());
  node.AttachChildNode(child_node);

  auto it = rc.GetChildIterator();
  ON_RenderContent* child_rc;
  while (nullptr != (child_rc = it.GetNextChild()))
  {
    SetRenderContentNodeRecursive(*child_rc, *child_node);
  }
}

void ON_RenderContentPrivate::BuildXMLHierarchy(const ON_RenderContent& rc, ON_XMLNode& node) // Static.
{
  // Recursively builds 'node' from the tree structure of the XML nodes in 'rc' and its children.

  node = rc._private->m_node;

  auto* child_rc = rc._private->m_first_child;
  while (nullptr != child_rc)
  {
    auto* child_node = new ON_XMLNode(L"");
    BuildXMLHierarchy(*child_rc, *child_node);
    node.AttachChildNode(child_node);

    child_rc = child_rc->_private->m_next_sibling;
  }
}

ON_XMLNode* ON_RenderContentPrivate::NewXMLNodeRecursive(const ON_RenderContent& rc) // Static.
{
  ON_XMLNode* node = new ON_XMLNode(rc._private->m_node);

  ON_RenderContent* child_rc = rc._private->m_first_child;
  while (nullptr != child_rc)
  {
    ON_XMLNode* child_node = NewXMLNodeRecursive(*child_rc);
    if (nullptr != child_node)
    {
      node->AttachChildNode(child_node);
    }

    child_rc = child_rc->_private->m_next_sibling;
  }

  return node;
}

void ON_RenderContentPrivate::SetModel(const ON_RenderContent& rc, ONX_Model& model) // Static.
{
  rc._private->m_model = &model;

  auto it = rc.GetChildIterator();
  ON_RenderContent* child_rc = nullptr;
  while (nullptr != (child_rc = it.GetNextChild()))
  {
    SetModel(*child_rc, model);
  }
}

ON_RenderContent* ON_RenderContentPrivate::NewRenderContentFromNode(const ON_XMLNode& node) // Static.
{
  ON_RenderContent* rc = nullptr;

  const ON_wString& kind = node.TagName();

  if (ON_KIND_MATERIAL == kind)
    rc = new ON_RenderMaterial;
  else
  if (ON_KIND_ENVIRONMENT == kind)
    rc = new ON_RenderEnvironment;
  else
  if (ON_KIND_TEXTURE == kind)
    rc = new ON_RenderTexture;

  if (nullptr != rc)
  {
    rc->_private->SetXMLNode(node);
  }

  return rc;
}

ON_VIRTUAL_OBJECT_IMPLEMENT(ON_RenderContent, ON_ModelComponent, "A98DEDDA-E4FA-4E1E-9BD3-2A0695C6D4E9");

ON_RenderContent::ON_RenderContent(const wchar_t* kind)
  :
  ON_ModelComponent(ON_ModelComponent::Type::RenderContent)
{
  _private = new (_PRIVATE) ON_RenderContentPrivate(*this, kind); PRIVATE_CHECK(ON_RenderContentPrivate);

  // Set a unique instance id.
  ON_UUID uuid;
  ON_CreateUuid(uuid);
  SetId(uuid);

  // Set the plug-in id to the RDK plug-in id.
  _private->InternalSetPropertyValue(ON_RENDER_CONTENT_PLUG_IN_ID, RdkPlugInId());

  // Set the render engine id to 'universal'.
  _private->InternalSetPropertyValue(ON_RENDER_CONTENT_RENDER_ENGINE_ID, ON_UniversalRenderEngineId);
}

ON_RenderContent::ON_RenderContent(const ON_RenderContent& rc)
  :
  ON_ModelComponent(ON_ModelComponent::Type::RenderContent, rc)
{
  _private = new (_PRIVATE) ON_RenderContentPrivate(*this, L""); PRIVATE_CHECK(ON_RenderContentPrivate);
  operator = (rc);
}

ON_RenderContent::~ON_RenderContent()
{
  _private->~ON_RenderContentPrivate();
  _private = nullptr;
}

const ON_RenderContent& ON_RenderContent::operator = (const ON_RenderContent& rc)
{
  if (this != &rc)
  {
    ON_XMLRootNode root;
    ON_RenderContentPrivate::BuildXMLHierarchy(rc, root);
    _private->SetXMLNode(root);
  }

  return *this;
}

ON_wString ON_RenderContent::TypeName(void) const
{
  return _private->GetPropertyValue(ON_RENDER_CONTENT_TYPE_NAME).AsString();
}

void ON_RenderContent::SetTypeName(const wchar_t* name)
{
  _private->SetPropertyValue(ON_RENDER_CONTENT_TYPE_NAME, name);
}

ON_wString ON_RenderContent::Notes(void) const
{
  return _private->GetPropertyValue(ON_RENDER_CONTENT_NOTES).AsString();
}

void ON_RenderContent::SetNotes(const wchar_t* notes)
{
  _private->SetPropertyValue(ON_RENDER_CONTENT_NOTES, notes);
}

ON_wString ON_RenderContent::Tags(void) const
{
  return _private->GetPropertyValue(ON_RENDER_CONTENT_TAGS).AsString();
}

void ON_RenderContent::SetTags(const wchar_t* tags)
{
  _private->SetPropertyValue(ON_RENDER_CONTENT_TAGS, tags);
}

ON_UUID ON_RenderContent::TypeId(void) const
{
  return _private->GetPropertyValue(ON_RENDER_CONTENT_TYPE_ID).AsUuid();
}

void ON_RenderContent::SetTypeId(const ON_UUID& uuid)
{
  _private->SetPropertyValue(ON_RENDER_CONTENT_TYPE_ID, uuid);
}

ON_UUID ON_RenderContent::RenderEngineId(void) const
{
  return _private->GetPropertyValue(ON_RENDER_CONTENT_RENDER_ENGINE_ID).AsUuid();
}

void ON_RenderContent::SetRenderEngineId(const ON_UUID& uuid)
{
  _private->SetPropertyValue(ON_RENDER_CONTENT_RENDER_ENGINE_ID, uuid);
}

ON_UUID ON_RenderContent::PlugInId(void) const
{
  return _private->GetPropertyValue(ON_RENDER_CONTENT_PLUG_IN_ID).AsUuid();
}

void ON_RenderContent::SetPlugInId(const ON_UUID& uuid)
{
  _private->SetPropertyValue(ON_RENDER_CONTENT_PLUG_IN_ID, uuid);
}

ON_UUID ON_RenderContent::GroupId(void) const
{
  return _private->GetPropertyValue(ON_RENDER_CONTENT_GROUP_ID).AsUuid();
}

void ON_RenderContent::SetGroupId(const ON_UUID& group)
{
  _private->SetPropertyValue(ON_RENDER_CONTENT_GROUP_ID, group);
}

bool ON_RenderContent::Hidden(void) const
{
  return _private->GetPropertyValue(ON_RENDER_CONTENT_HIDDEN).AsBool();
}

void ON_RenderContent::SetHidden(bool hidden)
{
  _private->SetPropertyValue(ON_RENDER_CONTENT_HIDDEN, hidden);
}

bool ON_RenderContent::Reference(void) const
{
  return _private->GetPropertyValue(ON_RENDER_CONTENT_REFERENCE).AsBool();
}

void ON_RenderContent::SetReference(bool ref)
{
  _private->SetPropertyValue(ON_RENDER_CONTENT_REFERENCE, ref);
}

bool ON_RenderContent::AutoDelete(void) const
{
  return _private->GetPropertyValue(ON_RENDER_CONTENT_AUTO_DELETE).AsBool();
}

void ON_RenderContent::SetAutoDelete(bool autodel)
{
  _private->SetPropertyValue(ON_RENDER_CONTENT_AUTO_DELETE, autodel);
}

ON_XMLVariant ON_RenderContent::GetParameter(const wchar_t* name) const
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  ON_XMLVariant value;
  value.SetNull();

  // Try to get the new V8 parameter section.
  const ON_XMLNode* node = _private->m_node.GetNamedChild(ON_RENDER_CONTENT_PARAMETERS_V8);
  if (nullptr != node)
  {
    // Got it, so use the new ON_XMLParametersV8 to get the parameter's value.
    ON_XMLParametersV8 p(*node);
    p.GetParam(name, value);
  }
  else
  {
    // Either no V8 section was found or the parameter isn't there yet.
    // Try to get the legacy parameter section. This should not fail.
    node = _private->m_node.GetNamedChild(ON_RENDER_CONTENT_PARAMETERS);
    if (nullptr != node)
    {
      // Got it, so use the legacy ON_XMLParameters to get the parameter's value.
      ON_XMLParameters p(*node);
      p.GetParam(name, value);
    }
  }

  return value;
}

bool ON_RenderContent::SetParameter(const wchar_t* name, const ON_XMLVariant& value)
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  bool success = false;

  // Create / get the new V8 parameter section.
  auto* node = _private->m_node.CreateNodeAtPath(ON_RENDER_CONTENT_PARAMETERS_V8);
  if (nullptr != node)
  {
    // Use the new ON_XMLParametersV8 to write the parameter's value.
    ON_XMLParametersV8 p(*node);
    if (nullptr != p.SetParam(name, value))
      success = true;
  }

  // Create / get the legacy parameter section.
  node = _private->m_node.CreateNodeAtPath(ON_RENDER_CONTENT_PARAMETERS);
  if (nullptr != node)
  {
    // Use the legacy ON_XMLParameters to write the parameter's value.
    ON_XMLParameters p(*node);
    if (nullptr != p.SetParam(name, value))
      success = true;
  }

  return success;
}

ON_RenderContent::ChildIterator ON_RenderContent::GetChildIterator(void) const
{
  return ChildIterator(this);
}

ON_RenderContent* ON_RenderContent::Parent(void)
{
  return _private->m_parent;
}

const ON_RenderContent* ON_RenderContent::Parent(void) const
{
  return _private->m_parent;
}

ON_RenderContent* ON_RenderContent::FirstChild(void)
{
  return _private->m_first_child;
}

const ON_RenderContent* ON_RenderContent::FirstChild(void) const
{
  return _private->m_first_child;
}

ON_RenderContent* ON_RenderContent::NextSibling(void)
{
  return _private->m_next_sibling;
}

const ON_RenderContent* ON_RenderContent::NextSibling(void) const
{
  return _private->m_next_sibling;
}

ON_RenderContent& ON_RenderContent::TopLevel(void)
{
  return _private->TopLevel();
}

const ON_RenderContent& ON_RenderContent::TopLevel(void) const
{
  return _private->TopLevel();
}

bool ON_RenderContent::IsTopLevel(void) const
{
	return nullptr == _private->m_parent;
}

bool ON_RenderContent::IsChild(void) const
{
	return nullptr != _private->m_parent;
}

bool ON_RenderContent::SetChild(const ON_RenderContent& child, const wchar_t* child_slot_name)
{
  return _private->SetChild(child.Duplicate(), child_slot_name);
}

bool ON_RenderContent::DeleteChild(const wchar_t* child_slot_name)
{
  return _private->SetChild(nullptr, child_slot_name);
}

ON_wString ON_RenderContent::ChildSlotName(void) const
{
  return _private->GetPropertyValue(ON_RENDER_CONTENT_CHILD_SLOT_NAME).AsString();
}

void ON_RenderContent::SetChildSlotName(const wchar_t* csn)
{
  _private->SetPropertyValue(ON_RENDER_CONTENT_CHILD_SLOT_NAME, csn);
}

#define MAT_POSTFIX_ON            L"on"
#define MAT_POSTFIX_AMOUNT        L"amount"
#define MAT_POSTFIX_DOUBLE_AMOUNT L"double-amount"
#define MAT_POSTFIX_FILTER_ON     L"filter-on"

bool ON_RenderContent::ChildSlotOn(const wchar_t* child_slot_name) const
{
  const auto s = ON_wString(child_slot_name) + L"-" MAT_POSTFIX_ON;
  return GetParameter(s).AsBool();
}

bool ON_RenderContent::SetChildSlotOn(bool on, const wchar_t* child_slot_name)
{
  const auto s = ON_wString(child_slot_name) + L"-" MAT_POSTFIX_ON;
  return SetParameter(s, on);
}

double ON_RenderContent::ChildSlotAmount(const wchar_t* child_slot_name, double default_value) const
{
  // This is complicated. See https://mcneel.myjetbrains.com/youtrack/issue/RH-58417

  // Try to get the new double amount value in the range 0..1.
  auto s = ON_wString(child_slot_name) + L"-" MAT_POSTFIX_DOUBLE_AMOUNT;
  auto v = GetParameter(s);
  if (!v.IsNull())
  {
    // Got it, so return it in the range 0..100.
    return v.AsDouble() * 100.0;
  }

  // Couldn't get it so get the legacy amount value. This value is problematic (which is why we added
  // the new double amount). The reason is that originally, the value was supposed to be in the range
  // 0..100, and the Physically Based material is an example of a material that does this. But due to
  // an oversight, the Custom Material saved this in the range 0..1. This means that here, in generic
  // code that doesn't know which class saved the data, we have to figure out what range it's in by
  // looking at the variant's type.
  s = ON_wString(child_slot_name) + L"-" MAT_POSTFIX_AMOUNT;
  v = GetParameter(s);
  if (!v.IsNull())
  {
    if (v.Type() == ON_XMLVariant::Types::Integer)
    {
      // Got it as an integer so it's already in the range 0..100.
      return double(v.AsInteger());
    }
    else
    {
      // The double value is in the range 0..1. Return it in the range 0..100.
      return v.AsDouble() * 100.0;
    }
  }

  return default_value;
}

bool ON_RenderContent::SetChildSlotAmount(double amount, const wchar_t* child_slot_name)
{
  const auto s = ON_wString(child_slot_name) + L"-" MAT_POSTFIX_DOUBLE_AMOUNT;

  return SetParameter(s, amount / 100.0);
}

ON_RenderContent* ON_RenderContent::FindChild(const wchar_t* child_slot_name)
{
  return _private->FindChild(child_slot_name);
}

const ON_RenderContent* ON_RenderContent::FindChild(const wchar_t* child_slot_name) const
{
  return _private->FindChild(child_slot_name);
}

ON_wString ON_RenderContent::XML(bool recursive) const
{
  ON_XMLNode* node = &_private->m_node;

  if (recursive)
  {
    node = ON_RenderContentPrivate::NewXMLNodeRecursive(*this);
  }

  const ON__UINT32 logical_count = node->WriteToStream(nullptr, 0);
  auto* stream = new wchar_t[size_t(logical_count) + 1];
  node->WriteToStream(stream, logical_count);
  stream[logical_count] = 0;
  const ON_wString xml = stream;
  delete[] stream;

  if (recursive)
    delete node;

  return xml;
}

bool ON_RenderContent::SetXML(const wchar_t* xml)
{
  ON_XMLRootNode node;
  if (ON_XMLNode::ReadError == node.ReadFromStream(xml))
    return false;

  _private->SetXMLNode(node);

  return true;
}

const ON_XMLNode& ON_RenderContent::XMLNode(void) const
{
  return _private->m_node;
}

ON_wString ON_RenderContent::Kind(void) const
{
  return _private->m_node.TagName();
}

const ON_RenderContent* ON_RenderContent::FromModelComponentRef(const ON_ModelComponentReference& ref,
                                                                const ON_RenderContent* none_return_value) // Static.
{
  const auto* rc = ON_RenderContent::Cast(ref.ModelComponent());
  if (nullptr != rc)
    return rc;

  return none_return_value;
}

void* ON_RenderContent::EVF(const wchar_t* func, void* data)
{
  return nullptr;
}

// ON_RenderContent::ChildIterator

class ON_RenderContentChildIteratorPrivate final
{
public:
  ON_RenderContent* _current = nullptr;
};

ON_RenderContent::ChildIterator::ChildIterator(const ON_RenderContent* parent_rc)
{
  _private = new ON_RenderContentChildIteratorPrivate;

  if (nullptr != parent_rc)
  {
    _private->_current = parent_rc->_private->m_first_child;
  }
}

ON_RenderContent::ChildIterator::~ChildIterator()
{
  delete _private;
}

ON_RenderContent* ON_RenderContent::ChildIterator::GetNextChild(void)
{
  ON_RenderContent* rc = _private->_current;
  if (nullptr != rc)
  {
    _private->_current = rc->_private->m_next_sibling;
  }

  return rc;
}

void* ON_RenderContent::ChildIterator::EVF(const wchar_t*, void*)
{
  return nullptr;
}

void SetModel(const ON_RenderContent& rc, ONX_Model& model)
{
  ON_RenderContentPrivate::SetModel(rc, model);
}

ON_RenderContent* NewRenderContentFromNode(const ON_XMLNode& node)
{
  return ON_RenderContentPrivate::NewRenderContentFromNode(node);
}

void SetRenderContentNodeRecursive(const ON_RenderContent& rc, ON_XMLNode& node)
{
  ON_RenderContentPrivate::SetRenderContentNodeRecursive(rc, node);
}

// ON_RenderMaterial

ON_OBJECT_IMPLEMENT(ON_RenderMaterial, ON_RenderContent, "493E6601-F95B-4A5D-BB6F-2F6633076907");

ON_RenderMaterial::ON_RenderMaterial()
  :
  ON_RenderContent(ON_KIND_MATERIAL)
{
}

ON_RenderMaterial::ON_RenderMaterial(const ON_RenderMaterial& mat)
  :
  ON_RenderContent(mat)
{
}

ON_RenderMaterial::~ON_RenderMaterial()
{
}

const ON_RenderContent& ON_RenderMaterial::operator = (const ON_RenderContent& c)
{
  ON_RenderContent::operator = (c);
  return *this;
}

const ON_RenderMaterial& ON_RenderMaterial::operator = (const ON_RenderMaterial& mat)
{
  ON_RenderContent::operator = (mat);
  return *this;
}

ON_XMLVariant ParamHelper(const ON_XMLParameters& p, const wchar_t* name)
{
  ON_XMLVariant value;
  if (!p.GetParam(name, value))
    value = L"";

  return value;
}

ON_Material ON_RenderMaterial::ToOnMaterial(void) const
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  ON_Material mat;

  const ON_XMLNode* sim_node = _private->XMLNode_Simulation();
  if (nullptr != sim_node)
  {
    ON_XMLParameters p(*sim_node);

    mat.m_ambient               =       ParamHelper(p, ON_MATERIAL_AMBIENT              ).AsColor();
    mat.m_diffuse               =       ParamHelper(p, ON_MATERIAL_DIFFUSE              ).AsColor();
    mat.m_emission              =       ParamHelper(p, ON_MATERIAL_EMISSION             ).AsColor();
    mat.m_specular              =       ParamHelper(p, ON_MATERIAL_SPECULAR             ).AsColor();
    mat.m_shine                 =       ParamHelper(p, ON_MATERIAL_SHINE                ).AsDouble() * ON_Material::MaxShine;
    mat.m_reflection            =       ParamHelper(p, ON_MATERIAL_SIM_REFLECTION_COLOR ).AsColor();
    mat.m_reflectivity          =       ParamHelper(p, ON_MATERIAL_REFLECTIVITY_AMOUNT  ).AsDouble();
    mat.m_transparency          =       ParamHelper(p, ON_MATERIAL_TRANSPARENCY_AMOUNT  ).AsDouble();
    mat.m_transparent           =       ParamHelper(p, ON_MATERIAL_SIM_TRANSPARENT_COLOR).AsColor();
    mat.m_index_of_refraction   =       ParamHelper(p, ON_MATERIAL_IOR                  ).AsDouble();
    mat.m_reflection_glossiness = 1.0 - ParamHelper(p, ON_MATERIAL_POLISH_AMOUNT        ).AsDouble();
    mat.m_refraction_glossiness = 1.0 - ParamHelper(p, ON_MATERIAL_CLARITY_AMOUNT       ).AsDouble();
    mat.SetFresnelReflections   (       ParamHelper(p, ON_MATERIAL_FRESNEL_ENABLED      ).AsBool());
    mat.SetDisableLighting      (       ParamHelper(p, ON_MATERIAL_DISABLE_LIGHTING     ).AsBool());

    mat.m_fresnel_index_of_refraction = 1.56;

    if (ParamHelper(p, ON_MATERIAL_IS_PHYSICALLY_BASED).AsBool())
    {
      mat.ToPhysicallyBased();

      auto pbm = mat.PhysicallyBased();

      auto brdf = ON_PhysicallyBasedMaterial::BRDFs::GGX;
      const ON_wString s = ParamHelper(p, ON_PBR_MATERIAL_BRDF).AsString();
      if (s == ON_PBR_MATERIAL_BRDF_WARD)
        brdf = ON_PhysicallyBasedMaterial::BRDFs::Ward;
      pbm->SetBRDF(brdf);

      pbm->SetBaseColor                 (ParamHelper(p, ON_PBR_MATERIAL_BASE_COLOR).AsColor());
      pbm->SetSubsurface                (ParamHelper(p, ON_PBR_MATERIAL_SUBSURFACE).AsDouble());
      pbm->SetSubsurfaceScatteringColor (ParamHelper(p, ON_PBR_MATERIAL_SUBSURFACE_SCATTERING_COLOR).AsColor());
      pbm->SetSubsurfaceScatteringRadius(ParamHelper(p, ON_PBR_MATERIAL_SUBSURFACE_SCATTERING_RADIUS).AsDouble());
      pbm->SetSpecular                  (ParamHelper(p, ON_PBR_MATERIAL_SPECULAR).AsDouble());
      pbm->SetSpecularTint              (ParamHelper(p, ON_PBR_MATERIAL_SPECULAR_TINT).AsDouble());
      pbm->SetMetallic                  (ParamHelper(p, ON_PBR_MATERIAL_METALLIC).AsDouble());
      pbm->SetRoughness                 (ParamHelper(p, ON_PBR_MATERIAL_ROUGHNESS).AsDouble());
      pbm->SetAnisotropic               (ParamHelper(p, ON_PBR_MATERIAL_ANISOTROPIC).AsDouble());
      pbm->SetAnisotropicRotation       (ParamHelper(p, ON_PBR_MATERIAL_ANISOTROPIC_ROTATION).AsDouble());
      pbm->SetSheen                     (ParamHelper(p, ON_PBR_MATERIAL_SHEEN).AsDouble());
      pbm->SetSheenTint                 (ParamHelper(p, ON_PBR_MATERIAL_SHEEN_TINT).AsDouble());
      pbm->SetClearcoat                 (ParamHelper(p, ON_PBR_MATERIAL_CLEARCOAT).AsDouble());
      pbm->SetClearcoatRoughness        (ParamHelper(p, ON_PBR_MATERIAL_CLEARCOAT_ROUGHNESS).AsDouble());
      pbm->SetOpacity                   (ParamHelper(p, ON_PBR_MATERIAL_OPACITY).AsDouble());
      pbm->SetOpacityIOR                (ParamHelper(p, ON_PBR_MATERIAL_OPACITY_IOR).AsDouble());
      pbm->SetOpacityRoughness          (ParamHelper(p, ON_PBR_MATERIAL_OPACITY_ROUGHNESS).AsDouble());
      pbm->SetEmission                  (ParamHelper(p, ON_PBR_MATERIAL_EMISSION_COLOR).AsColor());
      pbm->SetAlpha                     (ParamHelper(p, ON_PBR_MATERIAL_ALPHA).AsDouble());
      pbm->SetUseBaseColorTextureAlphaForObjectAlphaTransparencyTexture(ParamHelper(p, ON_PBR_MATERIAL_USE_BASE_COLOR_TEXTURE_ALPHA).AsBool());
    }

    mat.SetName(Name());

    mat.m_textures.Destroy();

    // Iterate over the children.
    int count = 1;
    while (true)
    {
      ON_Texture tex;
      ON_XMLVariant v;

      ON_wString s;
      s.Format(ON_RENDER_MATERIAL_TEXTURE_SIMULATION_FORMAT, count);

      if (!p.GetParam(s + ON_RENDER_MATERIAL_TEXTURE_SIMULATION_FILENAME, v))
        break; // Not ideal.

      tex.m_image_file_reference.SetFullPath(v.AsString(), false);

      if (p.GetParam(s + ON_RENDER_MATERIAL_TEXTURE_SIMULATION_ON, v))
        tex.m_bOn = v;

      if (p.GetParam(s + ON_RENDER_MATERIAL_TEXTURE_SIMULATION_AMOUNT, v))
        tex.m_blend_constant_A = v;

      if (p.GetParam(s + ON_RENDER_MATERIAL_TEXTURE_SIMULATION_TYPE, v))
        tex.m_type = ON_Texture::TYPE(v.AsInteger());

      if (p.GetParam(s + ON_RENDER_MATERIAL_TEXTURE_SIMULATION_FILTER, v))
        tex.m_minfilter = tex.m_magfilter = ON_Texture::FILTER(v.AsInteger());

      if (p.GetParam(s + ON_RENDER_MATERIAL_TEXTURE_SIMULATION_MODE, v))
        tex.m_mode = ON_Texture::MODE(v.AsInteger());

      if (p.GetParam(s + ON_RENDER_MATERIAL_TEXTURE_SIMULATION_UVW, v))
        tex.m_uvw = v.AsXform();

      if (p.GetParam(s + ON_RENDER_MATERIAL_TEXTURE_SIMULATION_WRAP_U, v))
        tex.m_wrapu = ON_Texture::WRAP(v.AsInteger());

      if (p.GetParam(s + ON_RENDER_MATERIAL_TEXTURE_SIMULATION_WRAP_V, v))
        tex.m_wrapv = ON_Texture::WRAP(v.AsInteger());

      mat.m_textures.Append(tex);
      count++;
    }
  }

  return mat;
}

ON_RenderContent* ON_RenderMaterial::NewRenderContent(void) const
{
  return new ON_RenderMaterial;
}

// This usage enum was copied from the RDK but the values are not important because
// this is only used internally to ON_RenderTexture::ToOnTexture().
enum class ChildSlotUsage : unsigned int
{
  None                             = 0x0000000,
  Diffuse                          = 0x0000001,
  Transparency                     = 0x0000002,
  Bump                             = 0x0000004,
  Environment                      = 0x0000008,
  PBR_base_color                   = Diffuse,
  PBR_opacity                      = Transparency,
  PBR_bump                         = Bump,
  PBR_subsurface                   = 0x0000020,
  PBR_subsurface_scattering_color  = 0x0000040,
  PBR_subsurface_scattering_radius = 0x0000080,
  PBR_metallic                     = 0x0000100,
  PBR_specular                     = 0x0000200,
  PBR_specular_tint                = 0x0000400,
  PBR_roughness                    = 0x0000800,
  PBR_anisotropic                  = 0x0001000,
  PBR_anisotropic_rotation         = 0x0002000,
  PBR_sheen                        = 0x0004000,
  PBR_sheen_tint                   = 0x0008000,
  PBR_clearcoat                    = 0x0010000,
  PBR_clearcoat_roughness          = 0x0020000,
  PBR_opacity_ior                  = 0x0040000,
  PBR_opacity_roughness            = 0x0080000,
  PBR_emission                     = 0x0100000,
  PBR_ambient_occlusion            = 0x0200000,
  PBR_displacement                 = 0x0800000,
  PBR_clearcoat_bump               = 0x1000000,
  PBR_alpha                        = 0x2000000,
};

static ChildSlotUsage PBR_ChildSlotNameToUsage(const wchar_t* csn)
{
  using U = ChildSlotUsage;

  // Most of the child slot names have equivalent parameter names. Some do not and are hard-coded here.

  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_ALPHA))                        return U::PBR_alpha;
  if (0 == on_wcsicmp(csn, L"pbr-ambient-occlusion"))                     return U::PBR_ambient_occlusion;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_ANISOTROPIC))                  return U::PBR_anisotropic;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_ANISOTROPIC_ROTATION))         return U::PBR_anisotropic_rotation;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_BASE_COLOR))                   return U::PBR_base_color;
  if (0 == on_wcsicmp(csn, L"pbr-bump"))                                  return U::PBR_bump;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_CLEARCOAT))                    return U::PBR_clearcoat;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_CLEARCOAT_BUMP))               return U::PBR_clearcoat_bump;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_CLEARCOAT_ROUGHNESS))          return U::PBR_clearcoat_roughness;
  if (0 == on_wcsicmp(csn, L"pbr-displacement"))                          return U::PBR_displacement;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_EMISSION_COLOR))               return U::PBR_emission;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_METALLIC))                     return U::PBR_metallic;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_OPACITY))                      return U::PBR_opacity;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_OPACITY_IOR))                  return U::PBR_opacity_ior;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_OPACITY_ROUGHNESS))            return U::PBR_opacity_roughness;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_ROUGHNESS))                    return U::PBR_roughness;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_SHEEN))                        return U::PBR_sheen;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_SHEEN_TINT))                   return U::PBR_sheen_tint;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_SPECULAR))                     return U::PBR_specular;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_SPECULAR_TINT))                return U::PBR_specular_tint;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_SUBSURFACE))                   return U::PBR_subsurface;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_SUBSURFACE_SCATTERING_COLOR))  return U::PBR_subsurface_scattering_color;
  if (0 == on_wcsicmp(csn, ON_PBR_MATERIAL_SUBSURFACE_SCATTERING_RADIUS)) return U::PBR_subsurface_scattering_radius;

  return U::None;
}

static ON_wString PBR_ChildSlotNameFromUsage(ChildSlotUsage usage)
{
  using U = ChildSlotUsage;

  // Most of the child slot names have equivalent parameter names. Some do not and are hard-coded here.

  switch (usage)
  {
  case U::PBR_alpha:                        return ON_PBR_MATERIAL_ALPHA;
  case U::PBR_ambient_occlusion:            return L"pbr-ambient-occlusion";
  case U::PBR_anisotropic:                  return ON_PBR_MATERIAL_ANISOTROPIC;
  case U::PBR_anisotropic_rotation:         return ON_PBR_MATERIAL_ANISOTROPIC_ROTATION;
  case U::PBR_base_color:                   return ON_PBR_MATERIAL_BASE_COLOR;
  case U::PBR_bump:                         return L"pbr-bump";
  case U::PBR_clearcoat:                    return ON_PBR_MATERIAL_CLEARCOAT;
  case U::PBR_clearcoat_bump:               return ON_PBR_MATERIAL_CLEARCOAT_BUMP;
  case U::PBR_clearcoat_roughness:          return ON_PBR_MATERIAL_CLEARCOAT_ROUGHNESS;
  case U::PBR_displacement:                 return L"pbr-displacement";
  case U::PBR_emission:                     return ON_PBR_MATERIAL_EMISSION_COLOR;
  case U::PBR_metallic:                     return ON_PBR_MATERIAL_METALLIC;
  case U::PBR_opacity:                      return ON_PBR_MATERIAL_OPACITY;
  case U::PBR_opacity_ior:                  return ON_PBR_MATERIAL_OPACITY_IOR;
  case U::PBR_opacity_roughness:            return ON_PBR_MATERIAL_OPACITY_ROUGHNESS;
  case U::PBR_roughness:                    return ON_PBR_MATERIAL_ROUGHNESS;
  case U::PBR_sheen:                        return ON_PBR_MATERIAL_SHEEN;
  case U::PBR_sheen_tint:                   return ON_PBR_MATERIAL_SHEEN_TINT;
  case U::PBR_specular:                     return ON_PBR_MATERIAL_SPECULAR;
  case U::PBR_specular_tint:                return ON_PBR_MATERIAL_SPECULAR_TINT;
  case U::PBR_subsurface:                   return ON_PBR_MATERIAL_SUBSURFACE;
  case U::PBR_subsurface_scattering_color:  return ON_PBR_MATERIAL_SUBSURFACE_SCATTERING_COLOR;
  case U::PBR_subsurface_scattering_radius: return ON_PBR_MATERIAL_SUBSURFACE_SCATTERING_RADIUS;
  case U::Environment:                      return L""; // PBR materials do not support Environment.
  default: ON_ASSERT(false);                return L"";
  }
}

static ON_Texture::TYPE PreJuly2023_TextureTypeFromUsage(ChildSlotUsage u)
{
  using U = ChildSlotUsage;
  using T = ON_Texture::TYPE;

  switch (u)
  {
  case U::Diffuse:                          return T::diffuse_texture; // Also handles PBR_base_color.
  case U::Transparency:                     return T::opacity_texture; // Also handles PBR_opacity.
  case U::Bump:                             return T::bump_texture;    // Also handles PBR_bump.
  case U::Environment:                      return T::emap_texture;
  case U::PBR_alpha:                        return T::pbr_alpha_texture;
  case U::PBR_ambient_occlusion:            return T::pbr_ambient_occlusion_texture;
  case U::PBR_anisotropic:                  return T::pbr_anisotropic_texture;
  case U::PBR_anisotropic_rotation:         return T::pbr_anisotropic_rotation_texture;
  case U::PBR_clearcoat:                    return T::pbr_clearcoat_texture;
  case U::PBR_clearcoat_bump:               return T::pbr_clearcoat_bump_texture;
  case U::PBR_clearcoat_roughness:          return T::pbr_clearcoat_roughness_texture;
  case U::PBR_displacement:                 return T::pbr_displacement_texture;
  case U::PBR_emission:                     return T::pbr_emission_texture;
  case U::PBR_metallic:                     return T::pbr_metallic_texture;
  case U::PBR_opacity_ior:                  return T::pbr_opacity_ior_texture;
  case U::PBR_opacity_roughness:            return T::pbr_opacity_roughness_texture;
  case U::PBR_roughness:                    return T::pbr_roughness_texture;
  case U::PBR_sheen:                        return T::pbr_sheen_texture;
  case U::PBR_sheen_tint:                   return T::pbr_sheen_tint_texture;
  case U::PBR_specular:                     return T::pbr_specular_texture;
  case U::PBR_specular_tint:                return T::pbr_specular_tint_texture;
  case U::PBR_subsurface:                   return T::pbr_subsurface_texture;
  case U::PBR_subsurface_scattering_color:  return T::pbr_subsurface_scattering_texture;
  case U::PBR_subsurface_scattering_radius: return T::pbr_subsurface_scattering_radius_texture;
  default: ON_ASSERT(false);                return T::no_texture_type;
  }
}

static ON_wString PreJuly2023_TextureChildSlotName(const ON_RenderMaterial& rm, ChildSlotUsage usage)
{
  if (rm.ToOnMaterial().IsPhysicallyBased())
    return PBR_ChildSlotNameFromUsage(usage);

  switch (usage)
  {
  case ChildSlotUsage::Diffuse:      return ON_TEXTURE_CHILD_SLOT_NAME_BITMAP_TEXTURE;
  case ChildSlotUsage::Bump:         return ON_TEXTURE_CHILD_SLOT_NAME_BUMP_TEXTURE;
  case ChildSlotUsage::Transparency: return ON_TEXTURE_CHILD_SLOT_NAME_TRANSPARENCY_TEXTURE;
  case ChildSlotUsage::Environment:  return ON_TEXTURE_CHILD_SLOT_NAME_ENVIRONMENT_TEXTURE;
  default: return L"";
  }
}

static ChildSlotUsage PreJuly2023_TextureUsage(const ON_RenderMaterial& rm, const wchar_t* child_slot_name)
{
  if (rm.ToOnMaterial().IsPhysicallyBased())
    return PBR_ChildSlotNameToUsage(child_slot_name);

  if (0 == PreJuly2023_TextureChildSlotName(rm, ChildSlotUsage::Diffuse).CompareNoCase(child_slot_name))
    return ChildSlotUsage::Diffuse;

  if (0 == PreJuly2023_TextureChildSlotName(rm, ChildSlotUsage::Transparency).CompareNoCase(child_slot_name))
    return ChildSlotUsage::Transparency;

  if (0 == PreJuly2023_TextureChildSlotName(rm, ChildSlotUsage::Bump).CompareNoCase(child_slot_name))
    return ChildSlotUsage::Bump;

  if (0 == PreJuly2023_TextureChildSlotName(rm, ChildSlotUsage::Environment).CompareNoCase(child_slot_name))
    return ChildSlotUsage::Environment;

  return ChildSlotUsage::None;
}

// ON_RenderEnvironment

ON_OBJECT_IMPLEMENT(ON_RenderEnvironment, ON_RenderContent, "A0AB8EF9-5FD4-4320-BBDA-A1200D1846E4");

ON_RenderEnvironment::ON_RenderEnvironment()
  :
  ON_RenderContent(ON_KIND_ENVIRONMENT)
{
}

ON_RenderEnvironment::ON_RenderEnvironment(const ON_RenderEnvironment& env)
  :
  ON_RenderContent(env)
{
}

ON_RenderEnvironment::~ON_RenderEnvironment()
{
}

const ON_RenderContent& ON_RenderEnvironment::operator = (const ON_RenderContent& c)
{
  ON_RenderContent::operator = (c);
  return *this;
}

const ON_RenderEnvironment& ON_RenderEnvironment::operator = (const ON_RenderEnvironment& env)
{
  ON_RenderContent::operator = (env);
  return *this;
}

ON_Environment ON_RenderEnvironment::ToOnEnvironment(void) const
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  ON_Environment env;

  const ON_XMLNode* sim_node = _private->XMLNode_Simulation();
  if (nullptr != sim_node)
  {
    ON_XMLVariant v;
    ON_XMLParameters p(*sim_node);

    if (p.GetParam(ON_ENVIRONMENT_SIMULATION_BACKGROUND_COLOR, v))
      env.SetBackgroundColor(v.AsColor());

    if (p.GetParam(ON_ENVIRONMENT_SIMULATION_BACKGROUND_IMAGE, v))
    {
      ON_Texture tex;
      tex.m_image_file_reference.SetFullPath(v.AsString(), false);
      env.SetBackgroundImage(tex);

      // TODO: More? Andy is thinking about this.
    }

    if (p.GetParam(ON_ENVIRONMENT_SIMULATION_BACKGROUND_PROJECTION, v))
    {
      const auto proj = ON_Environment::ProjectionFromString(v.AsString());
      env.SetBackgroundProjection(proj);
    }
  }

  return env;
}

ON_RenderContent* ON_RenderEnvironment::NewRenderContent(void) const
{
  return new ON_RenderEnvironment;
}

// ON_RenderTexture

ON_OBJECT_IMPLEMENT(ON_RenderTexture, ON_RenderContent, "677D9905-CC8C-41E6-A7AD-2409DDE68ED0");

ON_RenderTexture::ON_RenderTexture()
  :
  ON_RenderContent(ON_KIND_TEXTURE)
{
}

ON_RenderTexture::ON_RenderTexture(const ON_RenderTexture& tex)
  :
  ON_RenderContent(tex)
{
}

ON_RenderTexture::~ON_RenderTexture()
{
}

const ON_RenderContent& ON_RenderTexture::operator = (const ON_RenderContent& c)
{
  ON_RenderContent::operator = (c);
  return *this;
}

const ON_RenderTexture& ON_RenderTexture::operator = (const ON_RenderTexture& tex)
{
  ON_RenderContent::operator = (tex);
  return *this;
}

ON_Texture ON_RenderTexture::ToOnTexture(void) const
{
  std::lock_guard<std::recursive_mutex> lg(_private->m_mutex);

  // The following simulation values are new in V8:
  //
  // - ON_TEXTURE_SIMULATION_ON
  // - ON_TEXTURE_SIMULATION_TYPE
  // - ON_TEXTURE_SIMULATION_MODE
  // - ON_TEXTURE_SIMULATION_TREAT_AS_LINEAR
  // - ON_TEXTURE_SIMULATION_BLEND_CONSTANT_A
  // - ON_TEXTURE_SIMULATION_TRANSPARENCY_TEXTURE_ID
  // - ON_TEXTURE_SIMULATION_MIN_FILTER
  // - ON_TEXTURE_SIMULATION_MAG_FILTER
  //
  // This data was not saved in the texture simulation XML prior to 20th July 2023 so these values
  // won't exist in old documents. If one value exists, we can assume they all do, so we use 'on'
  // to determine if they exist or not. If they don't exist, we either leave the default in place
  // or use a hacky method to get the value from the parent content.

  ON_Texture tex;
  ON_XMLVariant v;

  const ON_XMLNode* sim_node = _private->XMLNode_Simulation();
  if (nullptr != sim_node)
  {
    ON_XMLParameters p(*sim_node);

    if (p.GetParam(ON_TEXTURE_SIMULATION_ON, v))
    {
      // Since the 'on' value was found, this must be a document created on or after 20th July 2023.
      // We can also get all the other new values and won't be needing the parent hack.
      tex.m_bOn = v.AsBool();

      if (p.GetParam(ON_TEXTURE_SIMULATION_TYPE, v))
        tex.m_type = ON_Texture::TYPE(v.AsInteger());

      if (p.GetParam(ON_TEXTURE_SIMULATION_MODE, v))
        tex.m_mode = ON_Texture::MODE(v.AsInteger());

      if (p.GetParam(ON_TEXTURE_SIMULATION_TREAT_AS_LINEAR, v))
        tex.m_bTreatAsLinear = v.AsBool();

      if (p.GetParam(ON_TEXTURE_SIMULATION_BLEND_CONSTANT_A, v))
        tex.m_blend_constant_A = v.AsDouble();

      if (p.GetParam(ON_TEXTURE_SIMULATION_TRANSPARENCY_TEXTURE_ID, v))
        tex.m_transparency_texture_id = v.AsUuid();

      if (p.GetParam(ON_TEXTURE_SIMULATION_MIN_FILTER, v))
        tex.m_minfilter = ON_Texture::FILTER(v.AsInteger());

      if (p.GetParam(ON_TEXTURE_SIMULATION_MAG_FILTER, v))
        tex.m_magfilter = ON_Texture::FILTER(v.AsInteger());
    }
    else
    {
      // Since the new 'on' value was not found, this must be an old document. Use the various defaults and hacks.
      v = GetParameter(L"filter");
      if (!v.IsNull())
      {
        tex.m_minfilter =
        tex.m_magfilter = v.AsBool() ? ON_Texture::FILTER::linear_filter
                                     : ON_Texture::FILTER::nearest_filter;
      }

      const ON_wString child_slot_name = ChildSlotName();
      const auto* parent = Parent();
      if (nullptr != parent)
      {
        auto* parent_material = dynamic_cast<const ON_RenderMaterial*>(parent);
        if (nullptr != parent_material)
        {
          const auto usage = PreJuly2023_TextureUsage(*parent_material, child_slot_name);
          tex.m_type = PreJuly2023_TextureTypeFromUsage(usage);
        }

        tex.m_bOn = parent->ChildSlotOn(child_slot_name);
        tex.m_blend_constant_A = parent->ChildSlotAmount(child_slot_name, 100.0) / 100.0;

        v = parent->GetParameter(L"treat-as-linear");
        if (!v.IsNull())
        {
          tex.m_bTreatAsLinear = v.AsBool();
        }
      }
    }

    if (p.GetParam(ON_TEXTURE_SIMULATION_FILENAME, v))
    {
      tex.m_image_file_reference.SetFullPath(v.AsString(), false);
    }

    if (p.GetParam(ON_TEXTURE_SIMULATION_OFFSET, v))
    {
      ON_3dVector offset, repeat, rotation;
      tex.m_uvw.DecomposeTextureMapping(offset, repeat, rotation);
      const auto pt = v.As2dPoint();
      offset.x = pt[0];
      offset.y = pt[1];
      tex.m_uvw = ON_Xform::TextureMapping(offset, repeat, rotation);
    }

    if (p.GetParam(ON_TEXTURE_SIMULATION_REPEAT, v))
    {
      ON_3dVector offset, repeat, rotation;
      tex.m_uvw.DecomposeTextureMapping(offset, repeat, rotation);
      const auto pt = v.As2dPoint();
      repeat.x = pt[0];
      repeat.y = pt[1];
      tex.m_uvw = ON_Xform::TextureMapping(offset, repeat, rotation);
    }

    if (p.GetParam(ON_TEXTURE_SIMULATION_ROTATION, v))
    {
      ON_3dVector offset, repeat, rotation;
      tex.m_uvw.DecomposeTextureMapping(offset, repeat, rotation);
      const auto angle = v.AsDouble(); // 'angle' is in degrees.
      rotation.z = angle * ON_DEGREES_TO_RADIANS;
      tex.m_uvw = ON_Xform::TextureMapping(offset, repeat, rotation);
    }

    if (p.GetParam(ON_TEXTURE_SIMULATION_WRAP_TYPE, v))
    {
      const auto wt = ON_Texture::WRAP(v.AsInteger());
      tex.m_wrapu = wt;
      tex.m_wrapv = wt;
      tex.m_wrapw = wt;
    }

    if (p.GetParam(ON_TEXTURE_SIMULATION_MAPPING_CHANNEL, v))
    {
      tex.m_mapping_channel_id = v.AsInteger();
    }

    if (p.GetParam(ON_TEXTURE_SIMULATION_TRANSPARENT_COLOR, v))
    {
      tex.m_transparent_color = v.AsColor();
    }
  }

  return tex;
}

ON_wString ON_RenderTexture::Filename(void) const
{
  const ON_XMLVariant v = GetParameter(ON_RENDER_TEXTURE_FILENAME);
  if (v.IsNull())
    return L"";

  return v.AsString();
}

bool ON_RenderTexture::SetFilename(const wchar_t* f)
{
  return SetParameter(ON_RENDER_TEXTURE_FILENAME, f);
}

ON_RenderContent* ON_RenderTexture::NewRenderContent(void) const
{
  return new ON_RenderTexture;
}

int ONX_Model::AddRenderMaterial(const wchar_t* candidate_name)
{
  if (!ON_ModelComponent::IsValidComponentName(candidate_name))
    return ON_UNSET_INT_INDEX;

  ON_RenderMaterial mat;
  mat.SetTypeId(ON_RenderContentType_PhysicallyBasedMaterial);

  const ON_wString mat_name = m_manifest.UnusedName(mat.ComponentType(), ON_nil_uuid, candidate_name,
                                                    nullptr, nullptr, 0, nullptr);
  mat.SetName(mat_name);

  const ON_ModelComponentReference mcr = AddModelComponent(mat, true);
  const auto* model_mat = ON_RenderMaterial::Cast(mcr.ModelComponent());
  if (nullptr == model_mat)
  {
    ON_ERROR("Failed to add render material; AddModelComponent() failed");
    return ON_UNSET_INT_INDEX;
  }

  return model_mat->Index();
}

int ONX_Model::AddRenderEnvironment(const wchar_t* candidate_name)
{
  if (!ON_ModelComponent::IsValidComponentName(candidate_name))
    return ON_UNSET_INT_INDEX;

  ON_RenderEnvironment env;
  env.SetTypeId(ON_RenderContentType_BasicEnvironment);

  const ON_wString env_name = m_manifest.UnusedName(env.ComponentType(), ON_nil_uuid, candidate_name,
                                                    nullptr, nullptr, 0, nullptr);
  env.SetName(env_name);

  const ON_ModelComponentReference mcr = AddModelComponent(env, true);
  const auto* model_env = ON_RenderEnvironment::Cast(mcr.ModelComponent());
  if (nullptr == model_env)
  {
    ON_ERROR("Failed to add render environment; AddModelComponent() failed");
    return ON_UNSET_INT_INDEX;
  }

  return model_env->Index();
}

int ONX_Model::AddRenderTexture(const wchar_t* filename)
{
  const ON_wString clean_filename = ON_FileSystemPath::CleanPath(filename);

  if (!ON_FileSystem::PathExists(clean_filename))
  {
    ON_ERROR("Failed to add render texture; file does not exist");
    return ON_UNSET_INT_INDEX;
  }

  ON_RenderTexture tex;
  tex.SetTypeId(ON_RenderContentType_BitmapTexture);
  tex.SetParameter(ON_RENDER_TEXTURE_FILENAME, clean_filename);

  const ON_wString candidate_name = ON_FileSystemPath::FileNameFromPath(clean_filename, false);
  const ON_wString tex_name = m_manifest.UnusedName(tex.ComponentType(), ON_nil_uuid, candidate_name,
                                                    nullptr, nullptr, 0, nullptr);
  tex.SetName(tex_name);

  const ON_ModelComponentReference mcr = AddModelComponent(tex, true);
  const ON_RenderTexture* model_tex = ON_RenderTexture::Cast(mcr.ModelComponent());
  if (nullptr == model_tex)
  {
    ON_ERROR("Failed to add render texture; AddModelComponent() failed");

    return ON_UNSET_INT_INDEX;
  }

  return model_tex->Index();
}

ON_DECL void ON_EnsureNameValid(ON_wString& name)
{
  EnsureNameValid(name);
}

ON_UUID ON_UniversalRenderEngineId = { 0x99999999, 0x9999, 0x9999, { 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99 } };

ON_UUID ON_RenderContentType_2DCheckerTexture         = { 0xfd60c44e, 0x080c, 0x4967, { 0x92, 0xaa, 0x41, 0x0e, 0x8a, 0xa9, 0x5a, 0x0f } };
ON_UUID ON_RenderContentType_3DCheckerTexture         = { 0x6cdbb011, 0x3e2a, 0x4769, { 0x87, 0x2f, 0xe3, 0x89, 0x65, 0x63, 0xea, 0x3a } };
ON_UUID ON_RenderContentType_AddTexture               = { 0xdbfae616, 0x1ffb, 0x4b75, { 0xa6, 0x46, 0x1c, 0x7f, 0xa8, 0x9a, 0xa9, 0xb3 } };
ON_UUID ON_RenderContentType_AdvancedDotTexture       = { 0x9b654648, 0x5799, 0x41bf, { 0x82, 0x3c, 0x48, 0x31, 0x4d, 0x1e, 0xb6, 0xaa } };
ON_UUID ON_RenderContentType_BasicEnvironment         = { 0xba51ce00, 0xba51, 0xce00, { 0xba, 0x51, 0xce, 0xba, 0x51, 0xce, 0x00, 0x00 } };
ON_UUID ON_RenderContentType_BitmapTexture            = { 0x57e0ed08, 0x1907, 0x4529, { 0xb0, 0x1b, 0x0c, 0x4a, 0x24, 0x24, 0x55, 0xfd } };
ON_UUID ON_RenderContentType_BlendMaterial            = { 0xb1e4d000, 0xb1e4, 0xd000, { 0xb1, 0xe4, 0xd0, 0xb1, 0xe4, 0xd0, 0x07, 0x09 } };
ON_UUID ON_RenderContentType_BlendMaterial_V8         = { 0x0322370f, 0xa9af, 0x4264, { 0xa5, 0x7c, 0x58, 0xff, 0x8e, 0x43, 0x45, 0xdd } };
ON_UUID ON_RenderContentType_BlendTexture             = { 0x3fa30f00, 0x4c3f, 0x4afe, { 0x88, 0xab, 0xd7, 0x13, 0xb0, 0xbe, 0x2f, 0xd8 } };
ON_UUID ON_RenderContentType_CompositeMaterial        = { 0x4eb8c64d, 0xde99, 0x45cb, { 0xb3, 0x7e, 0x68, 0x85, 0xb4, 0x07, 0x2a, 0x4d } };
ON_UUID ON_RenderContentType_CustomMaterial           = { 0xba51c000, 0xba51, 0xc000, { 0xba, 0x51, 0xc0, 0xba, 0x51, 0xc0, 0x00, 0x00 } };
ON_UUID ON_RenderContentType_DefaultMaterial          = { 0xdefadefa, 0xdefa, 0xdefa, { 0xde, 0xfa, 0xde, 0xfa, 0xde, 0xfa, 0xde, 0xfa } };
ON_UUID ON_RenderContentType_DefaultEnvironment       = { 0xdefaeeee, 0xdefa, 0xeeee, { 0xde, 0xfa, 0xee, 0xee, 0xde, 0xfa, 0xee, 0xee } };
ON_UUID ON_RenderContentType_CrossHatchBumpTexture    = { 0x6e9c1863, 0x9015, 0x44a4, { 0xaf, 0x6c, 0xc4, 0x27, 0x21, 0x0e, 0xa8, 0xde } };
ON_UUID ON_RenderContentType_CubeMapTexture           = { 0x956c41fa, 0xa03b, 0x4733, { 0xaf, 0xe7, 0x23, 0x44, 0xaa, 0x00, 0x82, 0xdd } };
ON_UUID ON_RenderContentType_DisplayAttributeMaterial = { 0xc85d18a8, 0x68dd, 0x49fd, { 0xae, 0x3e, 0x72, 0xa3, 0x79, 0xc8, 0xc4, 0x86 } };
ON_UUID ON_RenderContentType_DotBumpTexture           = { 0xfee0999d, 0x26f1, 0x4aea, { 0x81, 0xfe, 0x85, 0x70, 0x28, 0x6a, 0xe9, 0x64 } };
ON_UUID ON_RenderContentType_DoubleSidedMaterial      = { 0xe6cd1973, 0xb739, 0x496e, { 0xab, 0x69, 0x32, 0x95, 0x7f, 0xa4, 0x84, 0x92 } };
ON_UUID ON_RenderContentType_EmissionMaterial         = { 0x94bb5698, 0xb0cd, 0x4d6e, { 0x84, 0xd7, 0xd2, 0x6f, 0x79, 0x81, 0x7d, 0x6e } };
ON_UUID ON_RenderContentType_ExposureTexture          = { 0x0f2f3b9b, 0xa330, 0x418c, { 0x83, 0x71, 0xf9, 0xf4, 0xe7, 0x61, 0xbe, 0x3c } };
ON_UUID ON_RenderContentType_FBmTexture               = { 0x8edbb011, 0x4e2a, 0x5769, { 0x87, 0x2f, 0xe3, 0x89, 0x65, 0x63, 0xea, 0x3b } };
ON_UUID ON_RenderContentType_GemMaterial              = { 0x5386a427, 0x85bb, 0x48a8, { 0x82, 0xa8, 0x10, 0x9f, 0xf0, 0x19, 0x27, 0xc3 } };
ON_UUID ON_RenderContentType_GlassMaterial            = { 0x51b4af08, 0x9dec, 0x4744, { 0x86, 0xf9, 0x54, 0x6f, 0xba, 0xcb, 0x80, 0x0d } };
ON_UUID ON_RenderContentType_GradientTexture          = { 0x8edbb013, 0x1e2b, 0x2669, { 0x87, 0x2f, 0xe3, 0x89, 0x65, 0x63, 0xea, 0x3b } };
ON_UUID ON_RenderContentType_GraniteTexture           = { 0x56587545, 0xb6de, 0x4f1f, { 0x8c, 0x60, 0x46, 0x39, 0xa2, 0x13, 0x8d, 0x8c } };
ON_UUID ON_RenderContentType_GridTexture              = { 0x809acd47, 0x00c8, 0x4c2f, { 0xae, 0x38, 0xaa, 0x5e, 0x3d, 0x8b, 0xea, 0xc7 } };
ON_UUID ON_RenderContentType_GritBumpTexture          = { 0x1b762bb6, 0x8b95, 0x4c1b, { 0xb3, 0x38, 0x45, 0x93, 0xc3, 0x3f, 0xfb, 0x65 } };
ON_UUID ON_RenderContentType_HatchBumpTexture         = { 0xb4e3a0dd, 0x6b65, 0x4612, { 0x84, 0xb3, 0xcc, 0x64, 0xdd, 0xda, 0x49, 0x6e } };
ON_UUID ON_RenderContentType_HDRTexture               = { 0xf28c2d86, 0x0466, 0x40d4, { 0x89, 0xee, 0xa5, 0x4b, 0x6c, 0x5e, 0x92, 0x88 } };
ON_UUID ON_RenderContentType_LeatherBumpTexture       = { 0x5dfb43e6, 0x2f03, 0x432f, { 0xbe, 0xcf, 0x9f, 0x9a, 0xb3, 0x0c, 0x89, 0x41 } };
ON_UUID ON_RenderContentType_MarbleTexture            = { 0xa6cae674, 0xb2cd, 0x4585, { 0xa2, 0xbe, 0x9a, 0xb2, 0xe5, 0x0d, 0x35, 0x76 } };
ON_UUID ON_RenderContentType_MaskTexture              = { 0xb047bd26, 0x32eb, 0x43f7, { 0x9a, 0x4e, 0x6a, 0x82, 0x8c, 0x22, 0x67, 0xd1 } };
ON_UUID ON_RenderContentType_MetalMaterial            = { 0x037469d6, 0x0b9a, 0x4e5f, { 0xaf, 0x10, 0xe4, 0x83, 0xc9, 0x92, 0x99, 0x3a } };
ON_UUID ON_RenderContentType_MultiplyTexture          = { 0x95bf2b4a, 0xc79b, 0x48e8, { 0x97, 0xd0, 0x25, 0x84, 0xf2, 0xe8, 0xe5, 0x2b } };
ON_UUID ON_RenderContentType_NoiseTexture             = { 0x9b787367, 0xebbc, 0x4865, { 0xaf, 0x18, 0xfd, 0x9d, 0xab, 0x7e, 0xb1, 0x77 } };
ON_UUID ON_RenderContentType_PaintMaterial            = { 0x492fafa5, 0x0e48, 0x4c8e, { 0x89, 0xa0, 0x08, 0xd3, 0xa1, 0x9b, 0xfe, 0x89 } };
ON_UUID ON_RenderContentType_PerlinMarbleTexture      = { 0x113245f5, 0x2f12, 0x4e26, { 0x8d, 0xec, 0xb1, 0x18, 0x30, 0x40, 0x2c, 0x47 } };
ON_UUID ON_RenderContentType_PerturbingTexture        = { 0xe26c301a, 0xcad4, 0x4420, { 0x9e, 0xe6, 0xc4, 0x05, 0x62, 0xa2, 0xc9, 0xdd } };
ON_UUID ON_RenderContentType_PhysicallyBasedMaterial  = { 0x5a8d7b9b, 0xcdc9, 0x49de, { 0x8c, 0x16, 0x2e, 0xf6, 0x4f, 0xb0, 0x97, 0xab } };
ON_UUID ON_RenderContentType_PhysicalSkyTexture       = { 0xfd8913b1, 0x1654, 0x47c5, { 0x8f, 0xd2, 0xe1, 0xf0, 0x29, 0xdd, 0x4a, 0xb4 } };
ON_UUID ON_RenderContentType_PictureMaterial          = { 0xa7e351be, 0x9546, 0x42dc, { 0x89, 0x40, 0x88, 0x67, 0xf2, 0x82, 0x90, 0x31 } };
ON_UUID ON_RenderContentType_PlasterMaterial          = { 0x6736887e, 0x11dd, 0x4782, { 0x8c, 0xc9, 0xd5, 0x0e, 0x41, 0xff, 0x45, 0xb0 } };
ON_UUID ON_RenderContentType_PlasticMaterial          = { 0xab3f2653, 0x4d79, 0x459d, { 0x90, 0x03, 0x1a, 0x63, 0xd9, 0x65, 0x06, 0x2d } };
ON_UUID ON_RenderContentType_ProjectionChangerTexture = { 0x103da058, 0x9de8, 0x4270, { 0xb9, 0x20, 0xbc, 0xac, 0xe5, 0xa6, 0xc7, 0xd9 } };
ON_UUID ON_RenderContentType_RealtimeDisplayMaterial  = ON_RenderContentType_DoubleSidedMaterial;
ON_UUID ON_RenderContentType_ResampleTexture          = { 0x71d5feef, 0x4144, 0x4133, { 0x8c, 0x38, 0x1e, 0xef, 0x2b, 0xc8, 0x51, 0xf1 } };
ON_UUID ON_RenderContentType_SimpleBitmapTexture      = { 0xcfb368a4, 0xffb2, 0x404a, { 0xbb, 0xa9, 0x49, 0x72, 0x03, 0xb5, 0x05, 0x3a } };
ON_UUID ON_RenderContentType_SingleColorTexture       = { 0xb9368b92, 0x9f02, 0x45fb, { 0xb6, 0xcf, 0x09, 0x5e, 0xf8, 0x46, 0x35, 0x50 } };
ON_UUID ON_RenderContentType_SpeckleBumpTexture       = { 0xf1bf487d, 0xe84d, 0x4693, { 0xaf, 0xfc, 0x3f, 0x39, 0xf2, 0x39, 0xc2, 0x6c } };
ON_UUID ON_RenderContentType_StuccoTexture            = { 0x9d5173c5, 0x5f01, 0x4832, { 0xa4, 0x51, 0xa0, 0x22, 0x07, 0x4b, 0xa2, 0x08 } };
ON_UUID ON_RenderContentType_TextureAdjustmentTexture = { 0x79c30c49, 0xed60, 0x4c14, { 0xab, 0x9b, 0x02, 0x24, 0x3f, 0x5c, 0xaf, 0x7f } };
ON_UUID ON_RenderContentType_TileTexture              = { 0x7edbb011, 0x4e2a, 0x5769, { 0x87, 0x2f, 0xe3, 0x89, 0x65, 0x63, 0xea, 0x3a } };
ON_UUID ON_RenderContentType_TurbulenceTexture        = { 0x9edbb011, 0x4e2a, 0x5769, { 0x87, 0x2f, 0xe3, 0x89, 0x65, 0x63, 0xea, 0x3c } };
ON_UUID ON_RenderContentType_WavesTexture             = { 0xbbb53de4, 0x265e, 0x416c, { 0xa2, 0x19, 0x6c, 0x98, 0x2e, 0x70, 0x03, 0x5f } };
ON_UUID ON_RenderContentType_WoodBumpTexture          = { 0x757ca668, 0x47c9, 0x43b2, { 0xbb, 0x58, 0x19, 0x03, 0xce, 0x9a, 0x7a, 0x72 } };
ON_UUID ON_RenderContentType_WoodTexture              = { 0x11700849, 0xa326, 0x4538, { 0xbd, 0x44, 0x11, 0x86, 0x46, 0x90, 0xda, 0x68 } };
