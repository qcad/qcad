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

// ON_PostEffectParams

class ON_PostEffectParams::CImpl
{
public:
  CImpl() : _node(ON_RDK_PEP_PARAMS) { }
  CImpl(const ON_XMLNode& n) : _node(n) { _node.SetTagName(ON_RDK_PEP_PARAMS); }
  ~CImpl() { delete _params; _params = nullptr; }

  const ON_XMLParameters& AsXMLParameters(void) const
  {
    if (nullptr == _params)
    {
      _params = new ON_XMLParameters(_node);
    }

    return *_params;
  }

  ON_XMLNode _node;
  mutable ON_XMLParameters* _params = nullptr;
};

ON_PostEffectParams::ON_PostEffectParams()
{
  _impl = new CImpl;
}

ON_PostEffectParams::ON_PostEffectParams(const ON_XMLNode& n)
{
  _impl = new CImpl(n);
}

ON_PostEffectParams::ON_PostEffectParams(const ON_PostEffectParams& src)
{
  _impl = new CImpl;

  operator = (src);
}

ON_PostEffectParams::~ON_PostEffectParams()
{
  delete _impl;
  _impl = nullptr;
}

const ON_PostEffectParams& ON_PostEffectParams::operator = (const ON_PostEffectParams& src)
{
  _impl->_node = src._impl->_node;

  return *this;
}

bool ON_PostEffectParams::GetParam(const wchar_t* name, ON_XMLVariant& value_out) const
{
  const ON_XMLParameters p(_impl->_node);
  return p.GetParam(name, value_out);
}

bool ON_PostEffectParams::SetParam(const wchar_t* name, const ON_XMLVariant& value)
{
  ON_XMLParameters p(_impl->_node);
  p.SetParam(name, value);
  return true;
}

const ON_XMLParameters& ON_PostEffectParams::AsXMLParameters(void) const
{
  return _impl->AsXMLParameters();
}

ON__UINT32 ON_PostEffectParams::DataCRC(ON__UINT32 current_remainder) const
{
  return _impl->_node.DataCRC(current_remainder, true);
}

void* ON_PostEffectParams::EVF(const wchar_t*, void*)
{
  return nullptr;
}

// ON_PostEffect

static ON_XMLRootNode g_panic_node;

static const wchar_t* XMLPathPeps(void)
{
  return ON_RDK_DOCUMENT  ON_XML_SLASH  ON_RDK_SETTINGS  ON_XML_SLASH  ON_RDK_POST_EFFECTS;
}

static const wchar_t* PostEffectTypeString(ON_PostEffect::Types type)
{
  switch (type)
  {
    case ON_PostEffect::Types::Early:       return ON_RDK_PEP_TYPE_EARLY;
    case ON_PostEffect::Types::ToneMapping: return ON_RDK_PEP_TYPE_TONE_MAPPING;
    case ON_PostEffect::Types::Late:        return ON_RDK_PEP_TYPE_LATE;
    default: ON_ASSERT(false); return L"";
  }
}

static ON_XMLNode* GetPostEffectTypeNode(ON_XMLNode& post_effects_node, ON_PostEffect::Types type)
{
  ON_ASSERT(post_effects_node.TagName() == ON_RDK_POST_EFFECTS);

  return post_effects_node.CreateNodeAtPath(PostEffectTypeString(type));
}

const wchar_t* ON_PostEffectTypeString(ON_PostEffect::Types type)
{
  return PostEffectTypeString(type);
}

ON_XMLNode* FindPostEffectNodeForId(const ON_XMLNode& pep_section_node, const ON_UUID& id)
{
  auto it = pep_section_node.GetChildIterator();

  auto* pep_node = it.GetNextChild();
  while (nullptr != pep_node)
  {
    const auto* prop = pep_node->GetNamedProperty(ON_RDK_PEP_ID);
    if (nullptr != prop)
    {
      if (prop->GetValue().AsUuid() == id)
        return pep_node;
    }

    pep_node = it.GetNextChild();
  }

  return nullptr;
}

class ON_PostEffect::CImpl
{
public:
  CImpl(ON_PostEffects* p, const wchar_t* n, const ON_UUID& u, Types t)
    : _collection(p), _local_name(n), _id(u), _type(t) { }

 ~CImpl();

  ON_XMLNode* PepNode(void) const;
  ON_XMLVariant GetPropertyValue(const wchar_t* name) const;
  void SetPropertyValue(const wchar_t* name, const ON_XMLVariant& v) const;

public:
  ON_PostEffects* _collection;
  mutable ON_wString _local_name;
  mutable ON_XMLNode* _local_node = nullptr;
  const ON_UUID _id;
  const ON_PostEffect::Types _type;
};

ON_PostEffect::CImpl::~CImpl()
{
  if (nullptr != _local_node)
  {
    delete _local_node;
    _local_node = nullptr;
  }
}

ON_XMLNode* ON_PostEffect::CImpl::PepNode(void) const
{
  if (nullptr != _collection)
  {
    ON_XMLNode& post_effects_node = _collection->WritablePostEffectsNode();
    ON_XMLNode* pep_type_node = GetPostEffectTypeNode(post_effects_node, _type);
    if (nullptr == pep_type_node)
      return nullptr;

    ON_XMLNode* pep_node = FindPostEffectNodeForId(*pep_type_node, _id);
    if (nullptr == pep_node)
    {
      pep_node = pep_type_node->AttachChildNode(new ON_XMLNode(ON_RDK_PEP_PLUG_IN));
    }

    return pep_node;
  }

  // This post effect is not a member of a collection; it's free-floating so we need to use
  // a local node to hold its state.
  if (nullptr == _local_node)
    _local_node = new ON_XMLNode(ON_RDK_PEP_PLUG_IN);

  return _local_node;
}

ON_XMLVariant ON_PostEffect::CImpl::GetPropertyValue(const wchar_t* name) const
{
  ON_XMLVariant v;

  const auto* pep_node = PepNode();
  if (nullptr != pep_node)
  {
    const ON_XMLProperty* pProp = pep_node->GetNamedProperty(name);
    if (nullptr != pProp)
    {
      v = pProp->GetValue();
    }
  }

  return v;
}

void ON_PostEffect::CImpl::SetPropertyValue(const wchar_t* name, const ON_XMLVariant& value) const
{
  auto* pep_node = PepNode();
  if (nullptr != pep_node)
  {
    pep_node->SetProperty(ON_XMLProperty(name, value));
  }
}

ON_PostEffect::ON_PostEffect(ON_PostEffects& pe, Types type, const ON_UUID& id, const wchar_t* local_name)
{
  _impl = new CImpl(&pe, local_name, id, type);
}

ON_PostEffect::ON_PostEffect(const ON_PostEffect& pep)
{
  _impl = new CImpl(nullptr, pep.LocalName(), pep.Id(), pep.Type());
  operator = (pep);
}

ON_PostEffect::~ON_PostEffect()
{
  delete _impl;
  _impl = nullptr;
}

const ON_PostEffect& ON_PostEffect::operator = (const ON_PostEffect& other)
{
  ON_XMLNode* pep_node_dest = _impl->PepNode();
  if (nullptr != pep_node_dest)
  {
    const ON_XMLNode* pep_node_srce = other._impl->PepNode();
    if (nullptr != pep_node_srce)
    {
      *pep_node_dest = *pep_node_srce;
    }
  }

  return *this;
}

bool ON_PostEffect::operator == (const ON_PostEffect& pep) const
{
  if (_impl->_id         != pep._impl->_id)         return false;
  if (_impl->_type       != pep._impl->_type)       return false;
  if (_impl->_local_name != pep._impl->_local_name) return false;

  ON_PostEffectParams p1, p2;
  GetAllParameters(p1);
  pep.GetAllParameters(p2);

  bool equal = true;
  auto* it = p1.AsXMLParameters().NewIterator();

  ON_wString param_name;
  ON_XMLVariant param_value1, param_value2;
  while (equal && it->Next(param_name, param_value1))
  {
    if (!p2.GetParam(param_name, param_value2))
      equal = false;

    if (param_value1 != param_value2)
      equal = false;
  }

  delete it;

  return equal;
}

bool ON_PostEffect::operator != (const ON_PostEffect& pep) const
{
  return !(operator == (pep));
}

ON_PostEffect::Types ON_PostEffect::Type(void) const
{
  return _impl->_type;
}

ON_UUID ON_PostEffect::Id(void) const
{
  return _impl->_id;
}

ON_wString ON_PostEffect::LocalName(void) const
{
  return _impl->_local_name;
}

bool ON_PostEffect::On(void) const
{
  return _impl->GetPropertyValue(ON_RDK_PEP_ON).AsBool();
}

void ON_PostEffect::SetOn(bool b)
{
  _impl->SetPropertyValue(ON_RDK_PEP_ON, b);
}

bool ON_PostEffect::Shown(void) const
{
  return _impl->GetPropertyValue(ON_RDK_PEP_SHOWN).AsBool();
}

void ON_PostEffect::SetShown(bool b)
{
  _impl->SetPropertyValue(ON_RDK_PEP_SHOWN, b);
}

ON_XMLVariant ON_PostEffect::GetParameter(const wchar_t* param_name) const
{
  ON_XMLVariant value;
  value.SetNull();

  const ON_XMLNode* pep_node = _impl->PepNode();
  if (nullptr != pep_node)
  {
    const ON_XMLNode* pep_param_node = pep_node->GetNamedChild(ON_RDK_PEP_PARAMS);
    if (nullptr != pep_param_node)
    {
      ON_XMLParameters p(*pep_param_node);
      p.GetParam(param_name, value);
    }
  }

  return value;
}

bool ON_PostEffect::SetParameter(const wchar_t* param_name, const ON_XMLVariant& param_value)
{
  const ON_XMLNode* pep_node = _impl->PepNode();
  if (nullptr == pep_node)
    return false;

  ON_XMLNode* pep_param_node = pep_node->GetNamedChild(ON_RDK_PEP_PARAMS);
  if (nullptr == pep_param_node)
    return false;

  ON_XMLParameters p(*pep_param_node);

  ON_XMLVariant current_value;
  if (!p.GetParam(param_name, current_value))
    return false; // If you can't get it, you can't set it.

  if (!p.SetParam(param_name, param_value))
    return false;

  return true;
}

bool ON_PostEffect::GetAllParameters(ON_PostEffectParams& params) const
{
  const ON_XMLNode* pep_node = _impl->PepNode();
  if (nullptr == pep_node)
    return false;

  const ON_XMLNode* pep_param_node = pep_node->GetNamedChild(ON_RDK_PEP_PARAMS);
  if (nullptr == pep_param_node)
    return false;

  params = ON_PostEffectParams(*pep_param_node);

  return true;
}

bool ON_PostEffect::SetAllParameters(const ON_PostEffectParams& params)
{
  ON_XMLNode* pep_node = _impl->PepNode();
  if (nullptr == pep_node)
    return false;

  ON_XMLNode* pep_param_node = pep_node->GetNamedChild(ON_RDK_PEP_PARAMS);
  if (nullptr == pep_param_node)
      return false;

  *pep_param_node = params.AsXMLParameters().Node();

  return true;
}

ON_XMLNode& ON_PostEffect::XMLNode(void)
{
  auto* pep_node = _impl->PepNode();
  if (nullptr != pep_node)
    return *pep_node;

  // Should never get here.
  ON_ASSERT(false);
  return g_panic_node;
}

const ON_XMLNode& ON_PostEffect::XMLNode(void) const
{
  return const_cast<ON_PostEffect*>(this)->XMLNode();
}

ON__UINT32 ON_PostEffect::DataCRC(ON__UINT32 crc) const
{
  return XMLNode().DataCRC(crc, true);
}

// ON_PostEffects

class ON_PostEffects::CImpl : public ON_InternalXMLImpl
{
public:
  CImpl(ON_PostEffects& p) : _pe(p) { }
  CImpl(ON_PostEffects& p, ON_XMLNode& n) : _pe(p), ON_InternalXMLImpl(&n) { }
  ~CImpl();

  ON_XMLNode& PostEffectsNode(void) const;

        ON_SimpleArray<ON_PostEffect*>& PostEffectList(void)       { EnsurePopulated(); return _peps; }
  const ON_SimpleArray<ON_PostEffect*>& PostEffectList(void) const { EnsurePopulated(); return _peps; }

  void Clear(void);

  int IndexOfPostEffect(const ON_UUID& id) const;

private:
  void EnsurePopulated(void) const;
  void Populate(ON_PostEffect::Types type) const;

public:
  mutable ON_SimpleArray<ON_PostEffect*> _peps;
  mutable bool _is_populated = false;
  ON_PostEffects& _pe;
};
 
ON_PostEffects::CImpl::~CImpl()
{
  Clear();
}

ON_XMLNode& ON_PostEffects::CImpl::PostEffectsNode(void) const
{
  ON_XMLNode* post_effects_node = Node().CreateNodeAtPath(XMLPathPeps());
  if (nullptr != post_effects_node)
    return *post_effects_node;

  // Should never get here.
  ON_ASSERT(false);
  return g_panic_node;
}

int ON_PostEffects::CImpl::IndexOfPostEffect(const ON_UUID& id) const
{
  const auto& pel = PostEffectList();

  for (int i = 0; i < pel.Count(); i++)
  {
    ON_PostEffect* pep = pel[i];
    if (pep->Id() == id)
      return i;
  }

  return -1;
}

void ON_PostEffects::CImpl::Populate(ON_PostEffect::Types type) const
{
  const ON_XMLNode* pep_type_node = GetPostEffectTypeNode(PostEffectsNode(), type);
  if (nullptr == pep_type_node)
    return;

  auto it = pep_type_node->GetChildIterator();

  ON_XMLNode* pep_node = it.GetNextChild();
  while (nullptr != pep_node)
  {
    if (pep_node->TagName() == ON_RDK_PEP_PLUG_IN)
    {
      ON_XMLProperty* prop_name = pep_node->GetNamedProperty(ON_RDK_PEP_LOCAL_NAME);
      if (nullptr != prop_name)
      {
        const ON_wString local_name = prop_name->GetValue().AsString();

        ON_XMLProperty* prop_id = pep_node->GetNamedProperty(ON_RDK_PEP_ID);
        if (nullptr != prop_id)
        {
          const ON_UUID id = prop_id->GetValue().AsUuid();
          _peps.Append(new ON_PostEffect(_pe, type, id, local_name));
        }
      }
    }

    pep_node = it.GetNextChild();
  }
}

void ON_PostEffects::CImpl::Clear(void)
{
  if (_is_populated)
  {
    for (int i = 0; i < _peps.Count(); i++)
    {
      delete _peps[i];
    }

    _peps.Destroy();

    _is_populated = false;
  }
}

void ON_PostEffects::CImpl::EnsurePopulated(void) const
{
  if (_is_populated)
    return;

  _is_populated = true;

  Populate(ON_PostEffect::Types::Early);
  Populate(ON_PostEffect::Types::ToneMapping);
  Populate(ON_PostEffect::Types::Late);
}

ON_PostEffects::ON_PostEffects()
{
  _impl = new CImpl(*this); // Uses local node.
}

ON_PostEffects::ON_PostEffects(ON_XMLNode& model_node)
{
  _impl = new CImpl(*this, model_node);
}

ON_PostEffects::ON_PostEffects(const ON_PostEffects& pe)
{
  _impl = new CImpl(*this); // Uses local node.
  operator = (pe);
}

ON_PostEffects::~ON_PostEffects()
{
  delete _impl;
  _impl = nullptr;
}

ON_PostEffects& ON_PostEffects::operator = (const ON_PostEffects& peps)
{
  if (this != &peps)
  {
    SetPostEffectsNode(peps.PostEffectsNode());
  }

  return *this;
}

bool ON_PostEffects::operator == (const ON_PostEffects& other) const
{
  // 3rd August 2023 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH3DM-158
  // The problem is that this is called during loading, but before the PEPs are loaded. This was
  // causing them to get populated too early so once they are loaded they don't actually get populated.

  // If the incoming pep list is not yet populated, they are equal if this one is also not populated
  // but not equal if this one is populated.
  if (!other._impl->_is_populated)
    return !_impl->_is_populated;

  // We don't want to populate this list if it's not yet populated. Remember, this method is const.
  if (!_impl->_is_populated)
    return false; // The incoming list is populated but this one isn't.

  // If we get here, the both lists are already populated, so we need to check if the lists are equal.
  ON_SimpleArray<const ON_PostEffect*> a1;
  GetPostEffects(a1);

  ON_SimpleArray<const ON_PostEffect*> a2;
  other.GetPostEffects(a2);

  if (a1.Count() != a2.Count())
    return false;

  for (int i = 0; i < a1.Count(); i++)
  {
    const ON_PostEffect& pep1 = *a1[i];
    const ON_PostEffect& pep2 = *a2[i];
    if (pep1 != pep2)
      return false;
  }

  return true;
}

bool ON_PostEffects::operator != (const ON_PostEffects& p) const
{
  return !(operator == (p));
}

ON_PostEffect* ON_PostEffects::PostEffectFromId(const ON_UUID& id)
{
  const int index = _impl->IndexOfPostEffect(id);
  if (index < 0)
    return nullptr;

  return _impl->PostEffectList()[index];
}

const ON_PostEffect* ON_PostEffects::PostEffectFromId(const ON_UUID& id) const
{
  return const_cast<ON_PostEffects*>(this)->PostEffectFromId(id);
}

void ON_PostEffects::GetPostEffects(ON_PostEffect::Types type, ON_SimpleArray<ON_PostEffect*>& a)
{
  const auto& pel = _impl->PostEffectList();

  for (int i = 0; i < pel.Count(); i++)
  {
    ON_PostEffect* pep = pel[i];
    if (pep->Type() == type)
      a.Append(pep);
  }
}

void ON_PostEffects::GetPostEffects(ON_PostEffect::Types type, ON_SimpleArray<const ON_PostEffect*>& a) const
{
  ON_SimpleArray<ON_PostEffect*> pel;
  const_cast<ON_PostEffects*>(this)->GetPostEffects(type, pel);
  for (int i = 0; i < pel.Count(); i++)
  {
    a.Append(pel[i]);
  }
}

void ON_PostEffects::GetPostEffects(ON_SimpleArray<ON_PostEffect*>& a)
{
  a = _impl->PostEffectList();
}

void ON_PostEffects::GetPostEffects(ON_SimpleArray<const ON_PostEffect*>& a) const
{
  const auto& pel = _impl->PostEffectList();

  for (int i = 0; i < pel.Count(); i++)
  {
    a.Append(pel[i]);
  }
}

ON_XMLNode& ON_PostEffects::WritablePostEffectsNode(void)
{
  return _impl->PostEffectsNode();
}

const ON_XMLNode& ON_PostEffects::PostEffectsNode(void) const
{
  return _impl->PostEffectsNode();
}

void ON_PostEffects::SetPostEffectsNode(const ON_XMLNode& post_effects_node)
{
  // This is an expert function needed by the RDK (at least for now).

  // Setting the XML invalidates any existing post effect list.
  _impl->Clear();

  // Copy the incoming node and make sure its tag name is correct.
  // This is critical to ensure the correct node can be found from that name.
  ON_XMLNode node = post_effects_node;
  node.SetTagName(ON_RDK_POST_EFFECTS);

  // Copy the corrected node to the XML.
  _impl->PostEffectsNode() = node;
}

bool ON_PostEffects::AddPostEffect(ON_PostEffect::Types type, const ON_UUID& id,
                                   const wchar_t* local_name, const ON_PostEffectParams& params,
                                   bool is_listable, bool listable_on, bool listable_shown)
{
  if (ON_PostEffect::Types::Unset == type)
    return false;

  if (ON_nil_uuid == id)
    return false;

  if ((nullptr == local_name) || (0 == *local_name))
    return false;

  ON_ASSERT(nullptr == PostEffectFromId(id)); // Can't add the same id again.

  auto* pep = new ON_PostEffect(*this, type, id, local_name);
  _impl->_peps.Append(pep); // Critical.

  auto& pep_node = pep->XMLNode();

  // Write the localized name to the XML. This seems wrong at first because one would think we
  // should be writing the English name, but this is not relied on programmatically.
  // It's only written to make the XML text human-readable (assuming you can read that language).
  pep_node.SetProperty(ON_XMLProperty(ON_RDK_PEP_LOCAL_NAME, local_name));

  // Write the id to the XML.
  pep_node.SetProperty(ON_XMLProperty(ON_RDK_PEP_ID, ON_IdToString(id)));

  if (is_listable)
  {
    // Write the listable properties to the XML.
    pep_node.SetProperty(ON_XMLProperty(ON_RDK_PEP_ON, listable_on));
    pep_node.SetProperty(ON_XMLProperty(ON_RDK_PEP_SHOWN, listable_shown));
  }

  // Add the params to the XML.
  ON_XMLNode* pep_param_node = pep_node.AttachChildNode(new ON_XMLNode(L""));
  if (nullptr != pep_param_node)
  {
    *pep_param_node = params.AsXMLParameters().Node();
  }

  return true;
}

bool ON_PostEffects::MovePostEffectBefore(const ON_UUID& id_move, const ON_UUID& id_before)
{
  if (id_move == id_before)
    return false;

  const int index_move = _impl->IndexOfPostEffect(id_move);
  if (index_move < 0)
    return false;

  auto& pel = _impl->PostEffectList();

  ON_PostEffect* pep_move = pel[index_move];
  pel.Remove(index_move);

  ON_XMLNode& xml_move = pep_move->XMLNode();

  ON_XMLNode* parent = xml_move.Parent();
  if (nullptr == parent)
    return false; // Should never happen.

  if (ON_UuidIsNil(id_before))
  {
    ON_XMLNode* xml_move_detached = parent->DetachChild(xml_move);
    parent->AttachChildNode(xml_move_detached);
    pel.Append(pep_move);
  }
  else
  {
    const int index_before = _impl->IndexOfPostEffect(id_before);
    if (index_before < 0)
      return false;

    pel.Insert(index_before, pep_move);

    ON_XMLNode& xml_before = pel[index_before]->XMLNode();
    xml_move.MoveBefore(xml_before);
  }

  return true;
}

bool ON_PostEffects::GetSelectedPostEffect(ON_PostEffect::Types type, ON_UUID& id_out) const
{
  const ON_XMLNode* pep_type_node = GetPostEffectTypeNode(_impl->PostEffectsNode(), type);
  if (nullptr != pep_type_node)
  {
    ON_XMLProperty* prop = pep_type_node->GetNamedProperty(ON_RDK_PEP_SELECTION);
    if (nullptr != prop)
    {
      id_out = prop->GetValue().AsUuid();
      return true;
    }
  }

  return false;
}

void ON_PostEffects::SetSelectedPostEffect(ON_PostEffect::Types type, const ON_UUID& id)
{
  ON_XMLNode* pep_type_node = GetPostEffectTypeNode(_impl->PostEffectsNode(), type);
  if (nullptr != pep_type_node)
  {
    pep_type_node->SetProperty(ON_XMLProperty(ON_RDK_PEP_SELECTION, id));
  }
}

void* ON_PostEffects::EVF(const wchar_t*, void*)
{
  return nullptr;
}

void ON_PostEffects::OnInternalXmlChanged(const ON_PostEffects*)
{
  _impl->Clear();
}
