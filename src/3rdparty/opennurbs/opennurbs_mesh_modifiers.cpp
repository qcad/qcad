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

ON_UUID ON_MeshModifier::PlugInId(void) // Static.
{
  static const ON_UUID uuid =
  {
    // {f293de5c-d1ff-467a-9bd1-cac8ec4b2e6b}
    0xf293de5c, 0xd1ff, 0x467a, {0x9b, 0xd1, 0xca, 0xc8, 0xec, 0x4b, 0x2e, 0x6b}
  };

  return uuid;
}

class ON_MeshModifier::CImpl : public ON_InternalXMLImpl
{
public:
  CImpl() { }
  CImpl(const ON_XMLNode& n) { Node() = n; }
};

ON_MeshModifier::ON_MeshModifier()
{
  m_impl = new CImpl;
}

ON_MeshModifier::ON_MeshModifier(const ON_XMLNode& node)
{
  m_impl = new CImpl(node);
}

ON_MeshModifier::~ON_MeshModifier()
{
  delete m_impl;
  m_impl = nullptr;
}

ON_XMLNode* ON_MeshModifier::AddChildXML(ON_XMLRootNode& root) const
{
  ON_XMLNode* mm_node = root.AttachChildNode(new ON_XMLNode(L""));
  if (nullptr != mm_node)
  {
    *mm_node = m_impl->Node();
  }

  return mm_node;
}

////////////////////////////////////////////////////////////////
//
// Displacement
//
////////////////////////////////////////////////////////////////

ON_OBJECT_IMPLEMENT(ON_DisplacementUserData, ON_UserData, "B8C04604-B4EF-43b7-8C26-1AFB8F1C54EB");

ON_UUID ON_DisplacementUserData::Uuid(void)
{
  static const ON_UUID uuid = { 0x8224a7c4, 0x5590, 0x4ac4, { 0xa3, 0x2c, 0xde, 0x85, 0xdc, 0x2f, 0xfd, 0xae } };
  return uuid;
}

ON_DisplacementUserData::ON_DisplacementUserData()
{
  m_userdata_uuid = Uuid();

  m_application_uuid = ON_MeshModifier::PlugInId();

  SetToDefaults();
}

ON_DisplacementUserData::ON_DisplacementUserData(const ON_DisplacementUserData& ud)
  :
  ON_XMLUserData(ud) // CRITICAL - Be sure to call base class.
{
  m_userdata_uuid = Uuid();

  m_application_uuid = ON_MeshModifier::PlugInId();

  // DO NOT SET OTHER ON_UserData fields
  // In particular, do not set m_userdata_copycount
  *this = ud;
}

const ON_DisplacementUserData& ON_DisplacementUserData::operator = (const ON_DisplacementUserData& ud)
{
  if (this != &ud)
    ON_XMLUserData::operator = (ud);

  return *this;
}

bool ON_DisplacementUserData::GetDescription(ON_wString& s)
{
  s = L"Displacement object data";
  return true;
}

void ON_DisplacementUserData::SetToDefaults(void) const
{
  auto& ud = const_cast<ON_DisplacementUserData&>(*this);
  ud.Clear();

  ON_Displacement::Defaults d;

  ON_XMLNode* root = ud.XMLRootForWrite().AttachChildNode(new ON_XMLNode(ON_DISPLACEMENT_ROOT));

  ON_XMLParameters p(*root);
  p.SetParam(ON_DISPLACEMENT_ON, false);
  p.SetParam(ON_DISPLACEMENT_CHANNEL, d.ChannelNumber());
  p.SetParam(ON_DISPLACEMENT_BLACK_POINT, d.BlackPoint());
  p.SetParam(ON_DISPLACEMENT_WHITE_POINT, d.WhitePoint());
  p.SetParam(ON_DISPLACEMENT_SWEEP_PITCH, d.SweepPitch());
  p.SetParam(ON_DISPLACEMENT_REFINE_STEPS, d.RefineStepCount());
  p.SetParam(ON_DISPLACEMENT_REFINE_SENSITIVITY, d.RefineSensitivity());
  p.SetParam(ON_DISPLACEMENT_TEXTURE, ON_nil_uuid);
  p.SetParam(ON_DISPLACEMENT_FACE_COUNT_LIMIT_ENABLED, false);
  p.SetParam(ON_DISPLACEMENT_FACE_COUNT_LIMIT, d.FaceLimit());
  p.SetParam(ON_DISPLACEMENT_POST_WELD_ANGLE, d.PostWeldAngle());
  p.SetParam(ON_DISPLACEMENT_MESH_MEMORY_LIMIT, d.MeshMemoryLimit());
  p.SetParam(ON_DISPLACEMENT_FAIRING_ENABLED, false);
  p.SetParam(ON_DISPLACEMENT_FAIRING_AMOUNT, d.FairingAmount());
  p.SetParam(ON_DISPLACEMENT_SUB_OBJECT_COUNT, 0);
  p.SetParam(ON_DISPLACEMENT_SWEEP_RES_FORMULA, int(d.SweepResolutionFormula()));

  ON_XMLNode* sub_node = new ON_XMLNode(ON_DISPLACEMENT_SUB);
  root->AttachChildNode(sub_node);

  ON_XMLParameters psub(*sub_node);
  psub.SetParam(ON_DISPLACEMENT_SUB_INDEX, -1);
  psub.SetParam(ON_DISPLACEMENT_SUB_ON, false);
  psub.SetParam(ON_DISPLACEMENT_SUB_TEXTURE, ON_nil_uuid);
  psub.SetParam(ON_DISPLACEMENT_SUB_CHANNEL, d.ChannelNumber());
  psub.SetParam(ON_DISPLACEMENT_SUB_BLACK_POINT, d.BlackPoint());
  psub.SetParam(ON_DISPLACEMENT_SUB_WHITE_POINT, d.WhitePoint());
}

void ON_DisplacementUserData::ReportVersionError(void) const
{
  ON_ERROR("ON_DisplacementUserData: version error");
}

bool ON_DisplacementUserData::Transform(const ON_Xform& xform)
{
  return ON_XMLUserData::Transform(xform);
}

bool ON_DisplacementUserData::Read(ON_BinaryArchive& archive)
{
  if (!ON_XMLUserData::Read(archive))
    return false;

  const int archive3dmVersion = archive.Archive3dmVersion();
  if (archive3dmVersion < 60)
  {
    ON_XMLNode* root = XMLRootForWrite().GetNamedChild(ON_DISPLACEMENT_ROOT);
    if (root != nullptr)
    {
      ON_XMLParameters p(*root);
      ON_XMLVariant v;
      if (!p.GetParam(ON_DISPLACEMENT_SWEEP_RES_FORMULA, v))
      {
        p.SetParam(ON_DISPLACEMENT_SWEEP_RES_FORMULA, 1);
      }
    }
  }

  return true;
}

class ON_Displacement::CImplDSP
{
public:
  ON_SimpleArray<SubItem*> m_subs;
};

ON_Displacement::ON_Displacement()
  :
  ON_MeshModifier(ON_XMLNode(ON_DISPLACEMENT_ROOT))
{
  m_impl_dsp = new CImplDSP;
}

ON_Displacement::ON_Displacement(const ON_XMLNode& dsp_node)
{
  m_impl_dsp = new CImplDSP;

  // Iterate over the displacement node looking at each child node's name. If the child
  // node is a sub-item node, create a sub-item object to hold the sub-item XML. Otherwise add
  // a copy of the child node to a new displacement node.
  ON_XMLNode new_dsp_node(dsp_node.TagName());

  auto it = dsp_node.GetChildIterator();
  while (ON_XMLNode* child_node = it.GetNextChild())
  {
    if (ON_DISPLACEMENT_SUB == child_node->TagName())
    {
      m_impl_dsp->m_subs.Append(new SubItem(*child_node));
    }
    else
    {
      new_dsp_node.AttachChildNode(new ON_XMLNode(*child_node));
    }
  }

  // Copy the new displacement node to our node. It only contains displacement XML with no sub-item nodes.
  m_impl->Node() = new_dsp_node;
}

ON_Displacement::ON_Displacement(const ON_Displacement& dsp)
{
  m_impl_dsp = new CImplDSP;
  operator = (dsp);
}

ON_Displacement::~ON_Displacement()
{
  DeleteAllSubItems();

  delete m_impl_dsp;
  m_impl_dsp = nullptr;
}

const ON_Displacement& ON_Displacement::operator = (const ON_Displacement& dsp)
{
  if (this != &dsp)
  {
    SetOn                    (dsp.On());
    SetTexture               (dsp.Texture());
    SetMappingChannel        (dsp.MappingChannel());
    SetBlackPoint            (dsp.BlackPoint());
    SetWhitePoint            (dsp.WhitePoint());
    SetInitialQuality        (dsp.InitialQuality());
    SetFinalMaxFacesOn       (dsp.FinalMaxFacesOn());
    SetFinalMaxFaces         (dsp.FinalMaxFaces());
    SetFairingOn             (dsp.FairingOn());
    SetFairing               (dsp.Fairing());
    SetPostWeldAngle         (dsp.PostWeldAngle());
    SetMeshMemoryLimit       (dsp.MeshMemoryLimit());
    SetRefineSteps           (dsp.RefineSteps());
    SetRefineSensitivity     (dsp.RefineSensitivity());
    SetSweepResolutionFormula(dsp.SweepResolutionFormula());
  }

  return *this;
}

bool ON_Displacement::operator == (const ON_Displacement& dsp) const
{
  if (On()                     != dsp.On())                     return false;
  if (Texture()                != dsp.Texture())                return false;
  if (MappingChannel()         != dsp.MappingChannel())         return false;
  if (BlackPoint()             != dsp.BlackPoint())             return false;
  if (WhitePoint()             != dsp.WhitePoint())             return false;
  if (InitialQuality()         != dsp.InitialQuality())         return false;
  if (FinalMaxFacesOn()        != dsp.FinalMaxFacesOn())        return false;
  if (FinalMaxFaces()          != dsp.FinalMaxFaces())          return false;
  if (FairingOn()              != dsp.FairingOn())              return false;
  if (Fairing()                != dsp.Fairing())                return false;
  if (PostWeldAngle()          != dsp.PostWeldAngle())          return false;
  if (MeshMemoryLimit()        != dsp.MeshMemoryLimit())        return false;
  if (RefineSteps()            != dsp.RefineSteps())            return false;
  if (RefineSensitivity()      != dsp.RefineSensitivity())      return false;
  if (SweepResolutionFormula() != dsp.SweepResolutionFormula()) return false;

  return true;
}

bool ON_Displacement::operator != (const ON_Displacement& dsp) const
{
  return !(operator == (dsp));
}

ON_XMLNode* ON_Displacement::AddChildXML(ON_XMLRootNode& root) const
{
  ON_XMLNode* dsp_node = ON_MeshModifier::AddChildXML(root);
  if (nullptr != dsp_node)
  {
    auto it = GetSubItemIterator();
    SubItem* sub_item = nullptr;
    while (nullptr != (sub_item = it.Next()))
    {
      ON_XMLNode* sub_node = dsp_node->AttachChildNode(new ON_XMLNode(L""));
      sub_item->ToXML(*sub_node);
    }
  }

  return dsp_node;
}

bool ON_Displacement::On(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_ON, false).AsBool();
}

void ON_Displacement::SetOn(bool b)
{
  m_impl->SetParameter(ON_DISPLACEMENT_ON, b);
}

ON_UUID ON_Displacement::Texture(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_TEXTURE, ON_nil_uuid).AsUuid();
}

void ON_Displacement::SetTexture(const ON_UUID& id)
{
  m_impl->SetParameter(ON_DISPLACEMENT_TEXTURE, id);
}

int ON_Displacement::MappingChannel(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_CHANNEL, 0).AsInteger();
}

void ON_Displacement::SetMappingChannel(int c)
{
  m_impl->SetParameter(ON_DISPLACEMENT_CHANNEL, c);
}

double ON_Displacement::BlackPoint(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_BLACK_POINT, 0.0).AsDouble();
}

void ON_Displacement::SetBlackPoint(double b)
{
  m_impl->SetParameter(ON_DISPLACEMENT_BLACK_POINT, b);
}

double ON_Displacement::WhitePoint(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_WHITE_POINT, 1.0).AsDouble();
}

void ON_Displacement::SetWhitePoint(double w)
{
  m_impl->SetParameter(ON_DISPLACEMENT_WHITE_POINT, w);
}

int ON_Displacement::InitialQuality(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_SWEEP_PITCH, 1000).AsInteger();
}

void ON_Displacement::SetInitialQuality(int q)
{
  m_impl->SetParameter(ON_DISPLACEMENT_SWEEP_PITCH, q);
}

bool ON_Displacement::FinalMaxFacesOn(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_FACE_COUNT_LIMIT_ENABLED, false).AsBool();
}

void ON_Displacement::SetFinalMaxFacesOn(bool b)
{
  m_impl->SetParameter(ON_DISPLACEMENT_FACE_COUNT_LIMIT_ENABLED, b);
}

int ON_Displacement::FinalMaxFaces(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_FACE_COUNT_LIMIT, 10000).AsInteger();
}

void ON_Displacement::SetFinalMaxFaces(int f)
{
  m_impl->SetParameter(ON_DISPLACEMENT_FACE_COUNT_LIMIT, f);
}

bool ON_Displacement::FairingOn(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_FAIRING_ENABLED, false).AsBool();
}

void ON_Displacement::SetFairingOn(bool b)
{
  m_impl->SetParameter(ON_DISPLACEMENT_FAIRING_ENABLED, b);
}

int ON_Displacement::Fairing(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_FAIRING_AMOUNT, 4).AsInteger();
}

void ON_Displacement::SetFairing(int f)
{
  m_impl->SetParameter(ON_DISPLACEMENT_FAIRING_AMOUNT, f);
}

double ON_Displacement::PostWeldAngle(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_POST_WELD_ANGLE, 40.0).AsDouble();
}

void ON_Displacement::SetPostWeldAngle(double a)
{
  m_impl->SetParameter(ON_DISPLACEMENT_POST_WELD_ANGLE, a);
}

int ON_Displacement::MeshMemoryLimit(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_MESH_MEMORY_LIMIT, 512).AsInteger();
}

void ON_Displacement::SetMeshMemoryLimit(int l)
{
  m_impl->SetParameter(ON_DISPLACEMENT_MESH_MEMORY_LIMIT, l);
}

int ON_Displacement::RefineSteps(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_REFINE_STEPS, 1).AsInteger();
}

void ON_Displacement::SetRefineSteps(int s)
{
  m_impl->SetParameter(ON_DISPLACEMENT_REFINE_STEPS, s);
}

double ON_Displacement::RefineSensitivity(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_REFINE_SENSITIVITY, 0.5).AsDouble();
}

void ON_Displacement::SetRefineSensitivity(double s)
{
  m_impl->SetParameter(ON_DISPLACEMENT_REFINE_SENSITIVITY, s);
}

ON_Displacement::SweepResolutionFormulas ON_Displacement::SweepResolutionFormula(void) const
{
  const auto def = SweepResolutionFormulas::Default;
  const int v = m_impl->GetParameter(ON_DISPLACEMENT_SWEEP_RES_FORMULA, int(def)).AsInteger();
  return SweepResolutionFormulas(v);
}

void ON_Displacement::SetSweepResolutionFormula(SweepResolutionFormulas f)
{
  m_impl->SetParameter(ON_DISPLACEMENT_SWEEP_RES_FORMULA, int(f));
}

ON_Displacement::SubItemIterator ON_Displacement::GetSubItemIterator(void) const
{
  return SubItemIterator(*this);
}

ON_Displacement::SubItem& ON_Displacement::AddSubItem(void)
{
  ON_XMLNode node(ON_DISPLACEMENT_SUB);
  auto* sub = new SubItem(node);
  m_impl_dsp->m_subs.Append(sub);

  return *sub;
}

void ON_Displacement::DeleteSubItem(int face_index)
{
  const int index = FindSubItemArrayIndex(face_index);
  if (index >= 0)
  {
    delete m_impl_dsp->m_subs[index];
    m_impl_dsp->m_subs.Remove(index);
  }
}

void ON_Displacement::DeleteAllSubItems(void)
{
  for (int i = 0; i < m_impl_dsp->m_subs.Count(); i++)
  {
    delete m_impl_dsp->m_subs[i];
  }

  m_impl_dsp->m_subs.Destroy();
}

int ON_Displacement::FindSubItemArrayIndex(int face_index) const
{
  for (int i = 0; i < m_impl_dsp->m_subs.Count(); i++)
  {
    const auto* sub = m_impl_dsp->m_subs[i];
    if (sub->FaceIndex() == face_index)
      return i;
  }

  return -1;
}

ON_Displacement::SubItem* ON_Displacement::FindSubItem(int face_index) const
{
  const int index = FindSubItemArrayIndex(face_index);
  if (index < 0)
    return nullptr;

  return m_impl_dsp->m_subs[index];
}

class ON_Displacement::SubItem::CImpl : public ON_InternalXMLImpl
{
public:
  CImpl(const ON_XMLNode& sub_node) { Node() = sub_node; }
};

ON_Displacement::SubItem::SubItem(const ON_XMLNode& sub_node)
{
  m_impl = new CImpl(sub_node);
}

ON_Displacement::SubItem::~SubItem()
{
  delete m_impl;
  m_impl = nullptr;
}

const ON_Displacement::SubItem& ON_Displacement::SubItem::operator = (const SubItem& sub)
{
  if (this != &sub)
  {
    SetOn             (sub.On());
    SetFaceIndex      (sub.FaceIndex());
    SetTexture        (sub.Texture());
    SetMappingChannel (sub.MappingChannel());
    SetBlackPoint     (sub.BlackPoint());
    SetWhitePoint     (sub.WhitePoint());
  }

  return *this;
}

bool ON_Displacement::SubItem::operator == (const SubItem& sub) const
{
  if (On()             != sub.On())             return false;
  if (FaceIndex()      != sub.FaceIndex())      return false;
  if (Texture()        != sub.Texture())        return false;
  if (MappingChannel() != sub.MappingChannel()) return false;
  if (BlackPoint()     != sub.BlackPoint())     return false;
  if (WhitePoint()     != sub.WhitePoint())     return false;

  return true;
}

bool ON_Displacement::SubItem::operator != (const SubItem& c) const
{
  return !(operator == (c));
}

int ON_Displacement::SubItem::FaceIndex(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_SUB_INDEX, -1).AsInteger();
}

void ON_Displacement::SubItem::SetFaceIndex(int i)
{
  m_impl->SetParameter(ON_DISPLACEMENT_SUB_INDEX, i);
}

bool ON_Displacement::SubItem::On(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_SUB_ON, false).AsBool();
}

void ON_Displacement::SubItem::SetOn(bool b)
{
  m_impl->SetParameter(ON_DISPLACEMENT_SUB_ON, b);
}

ON_UUID ON_Displacement::SubItem::Texture(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_SUB_TEXTURE, false).AsUuid();
}

void ON_Displacement::SubItem::SetTexture(const ON_UUID& id)
{
  m_impl->SetParameter(ON_DISPLACEMENT_SUB_TEXTURE, id);
}

int ON_Displacement::SubItem::MappingChannel(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_SUB_CHANNEL, 0).AsInteger();
}

void ON_Displacement::SubItem::SetMappingChannel(int c)
{
  m_impl->SetParameter(ON_DISPLACEMENT_SUB_CHANNEL, c);
}

double ON_Displacement::SubItem::BlackPoint(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_SUB_BLACK_POINT, 0.0).AsDouble();
}

void ON_Displacement::SubItem::SetBlackPoint(double b)
{
  m_impl->SetParameter(ON_DISPLACEMENT_SUB_BLACK_POINT, b);
}

double ON_Displacement::SubItem::WhitePoint(void) const
{
  return m_impl->GetParameter(ON_DISPLACEMENT_SUB_WHITE_POINT, 1.0).AsDouble();
}

void ON_Displacement::SubItem::SetWhitePoint(double w)
{
  m_impl->SetParameter(ON_DISPLACEMENT_SUB_WHITE_POINT, w);
}

void ON_Displacement::SubItem::ToXML(ON_XMLNode& node) const
{
  node = m_impl->Node();
}

class ON_Displacement::SubItemIterator::CImpl
{
public:
  CImpl(const ON_Displacement& dsp) : m_dsp(dsp) { }

  SubItem* Next(void)
  {
    if (m_index >= m_dsp.m_impl_dsp->m_subs.Count())
      return nullptr;

    return m_dsp.m_impl_dsp->m_subs[m_index++];
  }

  const ON_Displacement& m_dsp;
  int m_index = 0;
};

ON_Displacement::SubItemIterator::SubItemIterator(const ON_Displacement& dsp)
{
  m_impl = new CImpl(dsp);
}

ON_Displacement::SubItemIterator::~SubItemIterator()
{
  delete m_impl;
  m_impl = nullptr;
}

ON_Displacement::SubItem* ON_Displacement::SubItemIterator::Next(void)
{
  return m_impl->Next();
}

ON_UUID ON_Displacement::Uuid(void) const
{
  // The unique id of the mesh modifier is the same as the id of its user data.
  return ON_DisplacementUserData::Uuid();
}

int    ON_Displacement::Defaults::RefineStepCount(void)   { return 1; }
int    ON_Displacement::Defaults::FairingAmount(void)     { return 4; }
int    ON_Displacement::Defaults::FaceLimit(void)         { return 10000; }
int    ON_Displacement::Defaults::ChannelNumber(void)     { return 1; }
int    ON_Displacement::Defaults::MeshMemoryLimit(void)   { return 512; }
double ON_Displacement::Defaults::BlackPoint(void)        { return 0.0; }
double ON_Displacement::Defaults::WhitePoint(void)        { return 1.0; }
double ON_Displacement::Defaults::SweepPitch(void)        { return 1000.0; }
double ON_Displacement::Defaults::RefineSensitivity(void) { return 0.5; }
double ON_Displacement::Defaults::PostWeldAngle(void)     { return 40.0; }
double ON_Displacement::Defaults::AbsoluteTolerance(void) { return 0.001; }

ON_Displacement::SweepResolutionFormulas ON_Displacement::Defaults::SweepResolutionFormula(void)
{
  return SweepResolutionFormulas::Default;
}

////////////////////////////////////////////////////////////////
//
// Edge Softening
//
////////////////////////////////////////////////////////////////

ON_OBJECT_IMPLEMENT(ON_EdgeSofteningUserData, ON_UserData, "CB5EB395-BF1B-4112-8F2F-F728FCE8169C");

ON_UUID ON_EdgeSofteningUserData::Uuid(void)
{
  static const ON_UUID uuid = { 0x8cbe6160, 0x5cbd, 0x4b4d, { 0x8c, 0xd2, 0x7c, 0xe0, 0xa7, 0xc8, 0xc2, 0xd8 } };
  return uuid;
}

ON_EdgeSofteningUserData::ON_EdgeSofteningUserData()
{
  m_userdata_uuid = Uuid();

  m_application_uuid = ON_MeshModifier::PlugInId();

  SetToDefaults();
}

ON_EdgeSofteningUserData::ON_EdgeSofteningUserData(const ON_EdgeSofteningUserData& ud)
  :
  ON_XMLUserData(ud) // CRITICAL - Be sure to call base class.
{
  m_userdata_uuid = Uuid();

  m_application_uuid = ON_MeshModifier::PlugInId();

  // DO NOT SET OTHER ON_UserData fields
  // In particular, do not set m_userdata_copycount
  *this = ud;
}

bool ON_EdgeSofteningUserData::GetDescription(ON_wString& s)
{
  s = L"EdgeSoftening object data";
  return true;
}

const ON_EdgeSofteningUserData& ON_EdgeSofteningUserData::operator = (const ON_EdgeSofteningUserData& ud)
{
  if (this != &ud)
    ON_XMLUserData::operator = (ud);

  return *this;
}

void ON_EdgeSofteningUserData::SetToDefaults(void) const
{
  auto& ud = const_cast<ON_EdgeSofteningUserData&>(*this);
  ud.Clear();

  ON_XMLProperty prop;
  ON_XMLNode* root = ud.XMLRootForWrite().AttachChildNode(new ON_XMLNode(ON_EDGE_SOFTENING_ROOT));

  ON_EdgeSoftening::Defaults d;

  ON_XMLParameters p(*root);
  p.SetParam(ON_EDGE_SOFTENING_ON, false);
  p.SetParam(ON_EDGE_SOFTENING_SOFTENING, d.Softening());
  p.SetParam(ON_EDGE_SOFTENING_CHAMFER, d.Chamfer());
  p.SetParam(ON_EDGE_SOFTENING_UNWELD, d.Faceted());
  p.SetParam(ON_EDGE_SOFTENING_FORCE_SOFTENING, d.ForceSoftening());
  p.SetParam(ON_EDGE_SOFTENING_EDGE_THRESHOLD, d.EdgeAngleThreshold());
}

void ON_EdgeSofteningUserData::ReportVersionError(void) const
{
  ON_ERROR("ON_EdgeSofteningUserData: version error");
}

ON_EdgeSoftening::ON_EdgeSoftening()
  :
  ON_MeshModifier(ON_XMLNode(ON_EDGE_SOFTENING_ROOT))
{
}

ON_EdgeSoftening::ON_EdgeSoftening(const ON_XMLNode& node)
  :
  ON_MeshModifier(node)
{
}

ON_EdgeSoftening::ON_EdgeSoftening(const ON_EdgeSoftening& es)
{
  operator = (es);
}

const ON_EdgeSoftening& ON_EdgeSoftening::operator = (const ON_EdgeSoftening& es)
{
  if (this != &es)
  {
    SetOn                (es.On());
    SetSoftening         (es.Softening());
    SetChamfer           (es.Chamfer());
    SetFaceted           (es.Faceted());
    SetForceSoftening    (es.ForceSoftening());
    SetEdgeAngleThreshold(es.EdgeAngleThreshold());
  }

  return *this;
}

bool ON_EdgeSoftening::operator == (const ON_EdgeSoftening& es) const
{
  if (On()                 != es.On())                 return false;
  if (Softening()          != es.Softening())          return false;
  if (Chamfer()            != es.Chamfer())            return false;
  if (Faceted()            != es.Faceted())            return false;
  if (ForceSoftening()     != es.ForceSoftening())     return false;
  if (EdgeAngleThreshold() != es.EdgeAngleThreshold()) return false;

  return true;
}

bool ON_EdgeSoftening::operator != (const ON_EdgeSoftening& es) const
{
  return !(operator == (es));
}

bool ON_EdgeSoftening::On(void) const
{
  return m_impl->GetParameter(ON_EDGE_SOFTENING_ON, false).AsBool();
}

void ON_EdgeSoftening::SetOn(bool b)
{
  m_impl->SetParameter(ON_EDGE_SOFTENING_ON, b);
}

double ON_EdgeSoftening::Softening(void) const
{
  return m_impl->GetParameter(ON_EDGE_SOFTENING_SOFTENING, 0.1).AsDouble();
}

void ON_EdgeSoftening::SetSoftening(double d)
{
  m_impl->SetParameter(ON_EDGE_SOFTENING_SOFTENING, d);
}

bool ON_EdgeSoftening::Chamfer(void) const
{
  return m_impl->GetParameter(ON_EDGE_SOFTENING_CHAMFER, false).AsBool();
}

void ON_EdgeSoftening::SetChamfer(bool b)
{
  m_impl->SetParameter(ON_EDGE_SOFTENING_CHAMFER, b);
}

bool ON_EdgeSoftening::Faceted(void) const
{
  return m_impl->GetParameter(ON_EDGE_SOFTENING_UNWELD, false).AsBool();
}

void ON_EdgeSoftening::SetFaceted(bool b)
{
  m_impl->SetParameter(ON_EDGE_SOFTENING_UNWELD, b);
}

double ON_EdgeSoftening::EdgeAngleThreshold(void) const
{
  return m_impl->GetParameter(ON_EDGE_SOFTENING_EDGE_THRESHOLD, 5.0).AsDouble();
}

void ON_EdgeSoftening::SetEdgeAngleThreshold(double d)
{
  m_impl->SetParameter(ON_EDGE_SOFTENING_EDGE_THRESHOLD, d);
}

bool ON_EdgeSoftening::ForceSoftening(void) const
{
  return m_impl->GetParameter(ON_EDGE_SOFTENING_FORCE_SOFTENING, false).AsBool();
}

void ON_EdgeSoftening::SetForceSoftening(bool b)
{
  m_impl->SetParameter(ON_EDGE_SOFTENING_FORCE_SOFTENING, b);
}

ON_UUID ON_EdgeSoftening::Uuid(void) const
{
  // The unique id of the mesh modifier is the same as the id of its user data.
  return ON_EdgeSofteningUserData::Uuid();
}

bool   ON_EdgeSoftening::Defaults::Chamfer(void)            { return false; }
bool   ON_EdgeSoftening::Defaults::Faceted(void)            { return false; }
bool   ON_EdgeSoftening::Defaults::ForceSoftening(void)     { return false; }
double ON_EdgeSoftening::Defaults::Softening(void)          { return 0.1; }
double ON_EdgeSoftening::Defaults::EdgeAngleThreshold(void) { return 5.0; }

////////////////////////////////////////////////////////////////
//
// Thickening
//
////////////////////////////////////////////////////////////////

ON_OBJECT_IMPLEMENT(ON_ThickeningUserData, ON_UserData, "AA03D9C3-4CCF-4431-A06E-25F38CF3913F");

ON_UUID ON_ThickeningUserData::Uuid(void)
{
  static const ON_UUID uuid = { 0x6aa7ccc3, 0x2721, 0x410f, { 0xaa, 0x56, 0xe8, 0xab, 0x4f, 0x3e, 0xce, 0x67 } };
  return uuid;
}

ON_ThickeningUserData::ON_ThickeningUserData()
{
  m_userdata_uuid = Uuid();

  m_application_uuid = ON_MeshModifier::PlugInId();

  SetToDefaults();
}

ON_ThickeningUserData::ON_ThickeningUserData(const ON_ThickeningUserData& ud)
  :
  ON_XMLUserData(ud) // CRITICAL - Be sure to call base class.
{
  m_userdata_uuid = Uuid();

  m_application_uuid = ON_MeshModifier::PlugInId();

  // DO NOT SET OTHER ON_UserData fields
  // In particular, do not set m_userdata_copycount
  *this = ud;
}

const ON_ThickeningUserData& ON_ThickeningUserData::operator = (const ON_ThickeningUserData& ud)
{
  if (this != &ud)
    ON_XMLUserData::operator = (ud);

  return *this;
}

void ON_ThickeningUserData::SetToDefaults(void) const
{
  auto& ud = const_cast<ON_ThickeningUserData&>(*this);
  ud.Clear();

  ON_XMLProperty prop;
  ON_XMLNode* root = ud.XMLRootForWrite().AttachChildNode(new ON_XMLNode(ON_THICKENING_ROOT));

  ON_Thickening::Defaults d;

  ON_XMLParameters p(*root);
  p.SetParam(ON_THICKENING_ON, false);
  p.SetParam(ON_THICKENING_SOLID, d.Solid());
  p.SetParam(ON_THICKENING_BOTH_SIDES, d.BothSides());
  p.SetParam(ON_THICKENING_OFFSET_ONLY, d.OffsetOnly());
  p.SetParam(ON_THICKENING_DISTANCE, d.Distance());
}

bool ON_ThickeningUserData::GetDescription(ON_wString& s)
{
  s = L"Thickness object data";
  return true;
}

void ON_ThickeningUserData::ReportVersionError(void) const
{
  ON_ERROR("ON_ThickeningUserData: version error");
}

bool ON_ThickeningUserData::Transform(const ON_Xform& xform)
{
  return ON_XMLUserData::Transform(xform);
}

ON_Thickening::ON_Thickening()
  :
  ON_MeshModifier(ON_XMLNode(ON_THICKENING_ROOT))
{
}

ON_Thickening::ON_Thickening(const ON_XMLNode& node)
  :
  ON_MeshModifier(node)
{
}

ON_Thickening::ON_Thickening(const ON_Thickening& t)
{
  operator = (t);
}

const ON_Thickening& ON_Thickening::operator = (const ON_Thickening& t)
{
  if (this != &t)
  {
    SetOn        (t.On());
    SetDistance  (t.Distance());
    SetSolid     (t.Solid());
    SetOffsetOnly(t.OffsetOnly());
    SetBothSides (t.BothSides());
  }

  return *this;
}

bool ON_Thickening::operator == (const ON_Thickening& t) const
{
  if (On()         != t.On())         return false;
  if (Distance()   != t.Distance())   return false;
  if (Solid()      != t.Solid())      return false;
  if (OffsetOnly() != t.OffsetOnly()) return false;
  if (BothSides()  != t.BothSides())  return false;

  return true;
}

bool ON_Thickening::operator != (const ON_Thickening& t) const
{
  return !(operator == (t));
}

bool ON_Thickening::On(void) const
{
  return m_impl->GetParameter(ON_THICKENING_ON, false).AsBool();
}

void ON_Thickening::SetOn(bool b)
{
  m_impl->SetParameter(ON_THICKENING_ON, b);
}

double ON_Thickening::Distance(void) const
{
  return m_impl->GetParameter(ON_THICKENING_DISTANCE, 0.1).AsDouble();
}

void ON_Thickening::SetDistance(double d)
{
  m_impl->SetParameter(ON_THICKENING_DISTANCE, d);
}

bool ON_Thickening::Solid(void) const
{
  return m_impl->GetParameter(ON_THICKENING_SOLID, true).AsBool();
}

void ON_Thickening::SetSolid(bool b)
{
  m_impl->SetParameter(ON_THICKENING_SOLID, b);
}

bool ON_Thickening::OffsetOnly(void) const
{
  return m_impl->GetParameter(ON_THICKENING_OFFSET_ONLY, false).AsBool();
}

void ON_Thickening::SetOffsetOnly(bool b)
{
  m_impl->SetParameter(ON_THICKENING_OFFSET_ONLY, b);
}

bool ON_Thickening::BothSides(void) const
{
  return m_impl->GetParameter(ON_THICKENING_BOTH_SIDES, false).AsBool();
}

void ON_Thickening::SetBothSides(bool b)
{
  m_impl->SetParameter(ON_THICKENING_BOTH_SIDES, b);
}

ON_UUID ON_Thickening::Uuid(void) const
{
  // The unique id of the mesh modifier is the same as the id of its user data.
  return ON_ThickeningUserData::Uuid();
}

bool   ON_Thickening::Defaults::Solid(void)      { return true; }
bool   ON_Thickening::Defaults::BothSides(void)  { return false; }
bool   ON_Thickening::Defaults::OffsetOnly(void) { return false; }
double ON_Thickening::Defaults::Distance(void)   { return 0.1; }

////////////////////////////////////////////////////////////////
//
// CurvePiping
//
////////////////////////////////////////////////////////////////

ON_OBJECT_IMPLEMENT(ON_CurvePipingUserData, ON_UserData, "2D5AFEA9-F458-4079-992F-C2D405D9383B");

ON_UUID ON_CurvePipingUserData::Uuid(void)
{
  static const ON_UUID uuid = { 0x2b1a758e, 0x7cb1, 0x45ab, { 0xa5, 0xbf, 0xdf, 0xcd, 0x6d, 0x3d, 0x13, 0x6d } };
  return uuid;
}

ON_CurvePipingUserData::ON_CurvePipingUserData()
{
  m_userdata_uuid = Uuid();

  m_application_uuid = ON_MeshModifier::PlugInId();

  SetToDefaults();
}

ON_CurvePipingUserData::ON_CurvePipingUserData(const ON_CurvePipingUserData& ud)
  :
  ON_XMLUserData(ud) // CRITICAL - Be sure to call base class.
{
  m_userdata_uuid = Uuid();

  m_application_uuid = ON_MeshModifier::PlugInId();

  // DO NOT SET OTHER ON_UserData fields
  // In particular, do not set m_userdata_copycount
  *this = ud;
}

const ON_CurvePipingUserData& ON_CurvePipingUserData::operator = (const ON_CurvePipingUserData& ud)
{
  if (this != &ud)
    ON_XMLUserData::operator = (ud);

  return *this;
}

void ON_CurvePipingUserData::SetToDefaults(void) const
{
  auto& ud = const_cast<ON_CurvePipingUserData&>(*this);
  ud.Clear();

  ON_XMLProperty prop;
  ON_XMLNode* root = ud.XMLRootForWrite().AttachChildNode(new ON_XMLNode(ON_CURVE_PIPING_ROOT));

  ON_CurvePiping::Defaults d;

  ON_XMLParameters p(*root);
  p.SetParam(ON_CURVE_PIPING_ON, false);
  p.SetParam(ON_CURVE_PIPING_RADIUS, d.Radius());
  p.SetParam(ON_CURVE_PIPING_SEGMENTS, d.Segments());
  p.SetParam(ON_CURVE_PIPING_ACCURACY, d.Accuracy());
  p.SetParam(ON_CURVE_PIPING_WELD, !d.Faceted()); // 'Weld' is the inverse of 'Faceted'.
  p.SetParam(ON_CURVE_PIPING_CAP_TYPE, L"dome");
}

bool ON_CurvePipingUserData::GetDescription(ON_wString& s)
{
  s = L"CurvePiping object data";
  return true;
}

void ON_CurvePipingUserData::ReportVersionError(void) const
{
  ON_ERROR("ON_CurvePipingUserData: version error");
}

bool ON_CurvePipingUserData::Transform(const ON_Xform& xform)
{
  return ON_XMLUserData::Transform(xform);
}

ON_CurvePiping::ON_CurvePiping()
  :
  ON_MeshModifier(ON_XMLNode(ON_CURVE_PIPING_ROOT))
{
}

ON_CurvePiping::ON_CurvePiping(const ON_XMLNode& node)
  :
  ON_MeshModifier(node)
{
}

ON_CurvePiping::ON_CurvePiping(const ON_CurvePiping& cp)
{
  operator = (cp);
}

const ON_CurvePiping& ON_CurvePiping::operator = (const ON_CurvePiping& cp)
{
  if (this != &cp)
  {
    SetRadius  (cp.Radius());
    SetSegments(cp.Segments());
    SetFaceted (cp.Faceted());
    SetAccuracy(cp.Accuracy());
    SetCapType (cp.CapType());
  }

  return *this;
}

bool ON_CurvePiping::operator == (const ON_CurvePiping& cp) const
{
  if (Radius()   != cp.Radius())   return false;
  if (Segments() != cp.Segments()) return false;
  if (Faceted()  != cp.Faceted())  return false;
  if (Accuracy() != cp.Accuracy()) return false;
  if (CapType()  != cp.CapType())  return false;

  return true;
}

bool ON_CurvePiping::operator != (const ON_CurvePiping& cp) const
{
  return !(operator == (cp));
}

bool ON_CurvePiping::On(void) const
{
  return m_impl->GetParameter(ON_CURVE_PIPING_ON, false).AsBool();
}

void ON_CurvePiping::SetOn(bool b)
{
  m_impl->SetParameter(ON_CURVE_PIPING_ON, b);
}

double ON_CurvePiping::Radius(void) const
{
  return m_impl->GetParameter(ON_CURVE_PIPING_RADIUS, 1.0).AsDouble();
}

void ON_CurvePiping::SetRadius(double d)
{
  m_impl->SetParameter(ON_CURVE_PIPING_RADIUS, d);
}

int ON_CurvePiping::Segments(void) const
{
  return m_impl->GetParameter(ON_CURVE_PIPING_SEGMENTS, 16).AsInteger();
}

void ON_CurvePiping::SetSegments(int s)
{
  m_impl->SetParameter(ON_CURVE_PIPING_SEGMENTS, s);
}

bool ON_CurvePiping::Faceted(void) const
{
  // 'Weld' is the inverse of 'Faceted'.
  return !m_impl->GetParameter(ON_CURVE_PIPING_WELD, true).AsBool();
}

void ON_CurvePiping::SetFaceted(bool b)
{
  // 'Weld' is the inverse of 'Faceted'.
  m_impl->SetParameter(ON_CURVE_PIPING_WELD, !b);
}

int ON_CurvePiping::Accuracy(void) const
{
  return m_impl->GetParameter(ON_CURVE_PIPING_ACCURACY, 50).AsInteger();
}

void ON_CurvePiping::SetAccuracy(int a)
{
  m_impl->SetParameter(ON_CURVE_PIPING_ACCURACY, std::min(100, std::max(0, a)));
}

static const wchar_t* CapTypeToString(ON_CurvePiping::CapTypes ct)
{
  switch (ct)
  {
    case ON_CurvePiping::CapTypes::Flat:
      return ON_CURVE_PIPING_FLAT;
    case ON_CurvePiping::CapTypes::Box:
      return ON_CURVE_PIPING_BOX;
    case ON_CurvePiping::CapTypes::Dome:
      return ON_CURVE_PIPING_DOME;
    case ON_CurvePiping::CapTypes::None:
      return ON_CURVE_PIPING_NONE;
  }

  return ON_CURVE_PIPING_NONE;
}

ON_CurvePiping::CapTypes ON_CurvePiping::CapType(void) const
{
  const ON_wString s = m_impl->GetParameter(ON_CURVE_PIPING_CAP_TYPE, L"").AsString();

  if (s == ON_CURVE_PIPING_FLAT) return ON_CurvePiping::CapTypes::Flat;
  if (s == ON_CURVE_PIPING_BOX)  return ON_CurvePiping::CapTypes::Box;
  if (s == ON_CURVE_PIPING_DOME) return ON_CurvePiping::CapTypes::Dome;

  return ON_CurvePiping::CapTypes::None;
}

void ON_CurvePiping::SetCapType(CapTypes ct)
{
  const wchar_t* s = CapTypeToString(ct);
  m_impl->SetParameter(ON_CURVE_PIPING_CAP_TYPE, s);
}

ON_UUID ON_CurvePiping::Uuid(void) const
{
  // The unique id of the mesh modifier is the same as the id of its user data.
  return ON_CurvePipingUserData::Uuid();
}

bool   ON_CurvePiping::Defaults::Faceted(void)  { return false; }
int    ON_CurvePiping::Defaults::Segments(void) { return 16; }
int    ON_CurvePiping::Defaults::Accuracy(void) { return 50; }
double ON_CurvePiping::Defaults::Radius(void)   { return 1.0; }

ON_CurvePiping::CapTypes ON_CurvePiping::Defaults::CapType(void)
{
  return CapTypes::Dome;
}

////////////////////////////////////////////////////////////////
//
// Shut-lining
//
////////////////////////////////////////////////////////////////

ON_OBJECT_IMPLEMENT(ON_ShutLiningUserData, ON_UserData, "429DCD06-5643-4254-BDE8-C0557F8FD083");

ON_UUID ON_ShutLiningUserData::Uuid(void)
{
  static const ON_UUID uuid = { 0x7506ebe, 0x1d69, 0x4345, { 0x9f, 0xd, 0x2b, 0x9a, 0xa1, 0x90, 0x6e, 0xef } };
  return uuid;
}

ON_ShutLiningUserData::ON_ShutLiningUserData()
{
  m_userdata_uuid = Uuid();

  m_application_uuid = ON_MeshModifier::PlugInId();

  SetToDefaults();
}

ON_ShutLiningUserData::ON_ShutLiningUserData(const ON_ShutLiningUserData& ud)
  :
  ON_XMLUserData(ud) // CRITICAL - Be sure to call base class.
{
  m_userdata_uuid = Uuid();

  m_application_uuid = ON_MeshModifier::PlugInId();

  // DO NOT SET OTHER ON_UserData fields
  // In particular, do not set m_userdata_copycount
  *this = ud;
}

const ON_ShutLiningUserData& ON_ShutLiningUserData::operator = (const ON_ShutLiningUserData& ud)
{
  if (this != &ud)
    ON_XMLUserData::operator = (ud);

  return *this;
}

void ON_ShutLiningUserData::SetToDefaults(void) const
{
  auto& ud = const_cast<ON_ShutLiningUserData&>(*this);
  ud.Clear();

  ON_XMLProperty prop;
  ON_XMLNode* root = ud.XMLRootForWrite().AttachChildNode(new ON_XMLNode(ON_SHUTLINING_ROOT));

  ON_XMLParameters p(*root);
  p.SetParam(ON_SHUTLINING_ON, false);
  p.SetParam(ON_SHUTLINING_FACETED, ON_ShutLining::Defaults::Faceted());
  p.SetParam(ON_SHUTLINING_AUTO_UPDATE, ON_ShutLining::Defaults::AutoUpdate());
  p.SetParam(ON_SHUTLINING_FORCE_UPDATE, ON_ShutLining::Defaults::ForceUpdate());
}

bool ON_ShutLiningUserData::GetDescription(ON_wString& s)
{
  s = L"ShutLining object data";
  return true;
}

void ON_ShutLiningUserData::ReportVersionError(void) const
{
  ON_ERROR("ON_ShutLiningUserData: version error");
}

bool ON_ShutLiningUserData::Transform(const ON_Xform& xform)
{
  return ON_XMLUserData::Transform(xform);
}

class ON_ShutLining::CImplSL
{
public:
  ON_SimpleArray<Curve*> m_curves;
};

ON_ShutLining::ON_ShutLining()
  :
  ON_MeshModifier(ON_XMLNode(ON_SHUTLINING_ROOT))
{
  m_impl_sl = new CImplSL;
}

ON_ShutLining::ON_ShutLining(const ON_XMLNode& sl_node)
{
  m_impl_sl = new CImplSL;

  // Iterate over the shut-lining node looking at each child node's name. If the child
  // node is a curve node, create a curve object to hold the curve XML. Otherwise add
  // a copy of the child node to a new shut-lining node.
  ON_XMLNode new_sl_node(sl_node.TagName());

  auto it = sl_node.GetChildIterator();
  while (ON_XMLNode* child_node = it.GetNextChild())
  {
    if (ON_SHUTLINING_CURVE == child_node->TagName())
    {
      m_impl_sl->m_curves.Append(new Curve(*child_node));
    }
    else
    {
      new_sl_node.AttachChildNode(new ON_XMLNode(*child_node));
    }
  }

  // Copy the new shut-lining node to our node. It only contains shut-lining XML with no curve nodes.
  m_impl->Node() = new_sl_node;
}

ON_ShutLining::ON_ShutLining(const ON_ShutLining& sl)
{
  m_impl_sl = new CImplSL;
  operator = (sl);
}

ON_ShutLining::~ON_ShutLining()
{
  DeleteAllCurves();

  delete m_impl_sl;
  m_impl_sl = nullptr;
}

const ON_ShutLining& ON_ShutLining::operator = (const ON_ShutLining& sl)
{
  if (this != &sl)
  {
    // Copy basic parameters.
    SetOn(sl.On());
    SetFaceted(sl.Faceted());
    SetAutoUpdate(sl.AutoUpdate());
    SetForceUpdate(sl.ForceUpdate());

    // Copy curves.
    DeleteAllCurves();
    auto it = sl.GetCurveIterator();
    while (Curve* sl_curve = it.Next())
    {
      Curve& new_curve = AddCurve();
      new_curve = *sl_curve;
    }
  }

  return *this;
}

ON_ShutLining::Curve* ON_ShutLining::FindCurve(const ON_UUID& id) const
{
  auto it = GetCurveIterator();
  while (Curve* curve = it.Next())
  {
    if (curve->Id() == id)
      return curve;
  }

  return nullptr;
}

bool ON_ShutLining::operator == (const ON_ShutLining& sl) const
{
  if (On()          != sl.On())          return false;
  if (Faceted()     != sl.Faceted())     return false;
  if (AutoUpdate()  != sl.AutoUpdate())  return false;
  if (ForceUpdate() != sl.ForceUpdate()) return false;

  auto it1 = GetCurveIterator();
  while (Curve* curve = it1.Next())
  {
    const Curve* sl_curve = sl.FindCurve(curve->Id());
    if (nullptr == sl_curve)
      return false;
  }

  auto it2 = sl.GetCurveIterator();
  while (Curve* sl_curve = it2.Next())
  {
    const Curve* curve = FindCurve(sl_curve->Id());
    if ((nullptr == curve) || (*curve != *sl_curve))
      return false;
  }

  return true;
}

bool ON_ShutLining::operator != (const ON_ShutLining& sl) const
{
  return !(operator == (sl));
}

bool ON_ShutLining::On(void) const
{
  return m_impl->GetParameter(ON_SHUTLINING_ON, false).AsBool();
}

void ON_ShutLining::SetOn(bool b)
{
  m_impl->SetParameter(ON_SHUTLINING_ON, b);
}

bool ON_ShutLining::Faceted(void) const
{
  return m_impl->GetParameter(ON_SHUTLINING_FACETED, false).AsBool();
}

void ON_ShutLining::SetFaceted(bool b)
{
  m_impl->SetParameter(ON_SHUTLINING_FACETED, b);
}

bool ON_ShutLining::AutoUpdate(void) const
{
  return m_impl->GetParameter(ON_SHUTLINING_AUTO_UPDATE, false).AsBool();
}

void ON_ShutLining::SetAutoUpdate(bool b)
{
  m_impl->SetParameter(ON_SHUTLINING_AUTO_UPDATE, b);
}

bool ON_ShutLining::ForceUpdate(void) const
{
  return m_impl->GetParameter(ON_SHUTLINING_FORCE_UPDATE, false).AsBool();
}

void ON_ShutLining::SetForceUpdate(bool b)
{
  m_impl->SetParameter(ON_SHUTLINING_FORCE_UPDATE, b);
}

ON_ShutLining::CurveIterator ON_ShutLining::GetCurveIterator(void) const
{
  return CurveIterator(*this);
}

ON_ShutLining::Curve& ON_ShutLining::AddCurve(void)
{
  ON_XMLNode* curve_node = m_impl->Node().AttachChildNode(new ON_XMLNode(ON_SHUTLINING_CURVE));
  Curve* curve = new Curve(*curve_node);
  m_impl_sl->m_curves.Append(curve);

  return *curve;
}

void ON_ShutLining::DeleteAllCurves(void)
{
  for (int i = 0; i < m_impl_sl->m_curves.Count(); i++)
  {
    delete m_impl_sl->m_curves[i];
  }

  m_impl_sl->m_curves.Destroy();
}

ON_XMLNode* ON_ShutLining::AddChildXML(ON_XMLRootNode& root) const
{
  ON_XMLNode* sl_node = ON_MeshModifier::AddChildXML(root);

  for (int i = 0; i < m_impl_sl->m_curves.Count(); i++)
  {
    ON_XMLNode* curve_node = sl_node->AttachChildNode(new ON_XMLNode(L""));
    m_impl_sl->m_curves[i]->ToXML(*curve_node);
  }

  return sl_node;
}

ON_UUID ON_ShutLining::Uuid(void) const
{
  // The unique id of the mesh modifier is the same as the id of its user data.
  return ON_ShutLiningUserData::Uuid();
}

bool   ON_ShutLining::Defaults::Faceted(void)     { return false; }
bool   ON_ShutLining::Defaults::AutoUpdate(void)  { return false; }
bool   ON_ShutLining::Defaults::ForceUpdate(void) { return false; }
double ON_ShutLining::Defaults::Tolerance(void)   { return 0.001; }

class ON_ShutLining::Curve::CImpl final
{
public:
  CImpl(const ON_XMLNode& n) : m_node(n) { }

  ON_XMLVariant GetParam(const wchar_t* param_name, const ON_XMLVariant& def) const
  {
    const ON_XMLNode* child_node = m_node.GetNamedChild(param_name);
    if (nullptr != child_node)
      return child_node->GetDefaultProperty().GetValue();

    return def;
  }

  void SetParam(const wchar_t* param_name, const ON_XMLVariant& v)
  {
    const ON_XMLNode* child_node = m_node.CreateNodeAtPath(param_name);
    child_node->GetDefaultProperty().SetValue(v);
  }

public:
  ON_XMLNode m_node;
};

ON_ShutLining::Curve::Curve(const ON_XMLNode& curve_node)
{
  m_impl = new CImpl(curve_node);
}

ON_ShutLining::Curve::~Curve()
{
  delete m_impl;
  m_impl = nullptr;
}

const ON_ShutLining::Curve& ON_ShutLining::Curve::operator = (const ON_ShutLining::Curve& c)
{
  if (this != &c)
  {
    SetId     (c.Id());
    SetEnabled(c.Enabled());
    SetRadius (c.Radius());
    SetProfile(c.Profile());
    SetPull   (c.Pull());
    SetIsBump (c.IsBump());
  }

  return *this;
}

bool ON_ShutLining::Curve::operator == (const Curve& c) const
{
  if (Id()      != c.Id())      return false;
  if (Enabled() != c.Enabled()) return false;
  if (Radius()  != c.Radius())  return false;
  if (Profile() != c.Profile()) return false;
  if (Pull()    != c.Pull())    return false;
  if (IsBump()  != c.IsBump())  return false;

  return true;
}

bool ON_ShutLining::Curve::operator != (const Curve& c) const
{
  return !(operator == (c));
}

ON_UUID ON_ShutLining::Curve::Id(void) const
{
  return m_impl->GetParam(ON_SHUTLINING_CURVE_UUID, ON_nil_uuid);
}

void ON_ShutLining::Curve::SetId(const ON_UUID& id)
{
  m_impl->SetParam(ON_SHUTLINING_CURVE_UUID, id);
}

double ON_ShutLining::Curve::Radius(void) const
{
  return m_impl->GetParam(ON_SHUTLINING_CURVE_RADIUS, 1.0);
}

void ON_ShutLining::Curve::SetRadius(double d)
{
  m_impl->SetParam(ON_SHUTLINING_CURVE_RADIUS, d);
}

int ON_ShutLining::Curve::Profile(void) const
{
  return m_impl->GetParam(ON_SHUTLINING_CURVE_PROFILE, 0);
}

void ON_ShutLining::Curve::SetProfile(int p)
{
  m_impl->SetParam(ON_SHUTLINING_CURVE_PROFILE, p);
}

bool ON_ShutLining::Curve::Enabled(void) const
{
  return m_impl->GetParam(ON_SHUTLINING_CURVE_ENABLED, false);
}

void ON_ShutLining::Curve::SetEnabled(bool b)
{
  m_impl->SetParam(ON_SHUTLINING_CURVE_ENABLED, b);
}

bool ON_ShutLining::Curve::Pull(void) const
{
  return m_impl->GetParam(ON_SHUTLINING_CURVE_PULL, false);
}

void ON_ShutLining::Curve::SetPull(bool b)
{
  m_impl->SetParam(ON_SHUTLINING_CURVE_PULL, b);
}

bool ON_ShutLining::Curve::IsBump(void) const
{
  return m_impl->GetParam(ON_SHUTLINING_CURVE_IS_BUMP, false);
}

void ON_ShutLining::Curve::SetIsBump(bool b)
{
  m_impl->SetParam(ON_SHUTLINING_CURVE_IS_BUMP, b);
}

void ON_ShutLining::Curve::ToXML(ON_XMLNode& node) const
{
  node = m_impl->m_node;
}

bool   ON_ShutLining::Curve::Defaults::Enabled(void) { return true; }
bool   ON_ShutLining::Curve::Defaults::Pull(void)    { return true; }
bool   ON_ShutLining::Curve::Defaults::IsBump(void)  { return false; }
int    ON_ShutLining::Curve::Defaults::Profile(void) { return 1; }
double ON_ShutLining::Curve::Defaults::Radius(void)  { return 0.1; }

class ON_ShutLining::CurveIterator::CImpl
{
public:
  CImpl(const ON_ShutLining& sl) : m_sl(sl) { }

  Curve* Next(void)
  {
    if (m_index >= m_sl.m_impl_sl->m_curves.Count())
      return nullptr;

    return m_sl.m_impl_sl->m_curves[m_index++];
  }

  const ON_ShutLining& m_sl;
  int m_index = 0;
};

ON_ShutLining::CurveIterator::CurveIterator(const ON_ShutLining& sl)
{
  m_impl = new CImpl(sl);
}

ON_ShutLining::CurveIterator::~CurveIterator()
{
  delete m_impl;
  m_impl = nullptr;
}

ON_ShutLining::Curve* ON_ShutLining::CurveIterator::Next(void)
{
  return m_impl->Next();
}

// ON_MeshModifiers

class ON_MeshModifiers::CImpl
{
public:
  ~CImpl();

  void LoadFromXML(const ON_XMLRootNode& root);

  void DeleteAll(void);

  ON_Displacement * m_displacement   = nullptr;
  ON_EdgeSoftening* m_edge_softening = nullptr;
  ON_Thickening   * m_thickening     = nullptr;
  ON_CurvePiping  * m_curve_piping   = nullptr;
  ON_ShutLining   * m_shut_lining    = nullptr;
};

void ON_MeshModifiers::CImpl::LoadFromXML(const ON_XMLRootNode& root)
{
  auto it = root.GetChildIterator();
  while (ON_XMLNode* child_node = it.GetNextChild())
  {
    const ON_wString& s = child_node->TagName();

    if (ON_DISPLACEMENT_ROOT == s)
    {
      m_displacement = new ON_Displacement(*child_node);
    }
    else
    if (ON_EDGE_SOFTENING_ROOT == s)
    {
      m_edge_softening = new ON_EdgeSoftening(*child_node);
    }
    else
    if (ON_THICKENING_ROOT == s)
    {
      m_thickening = new ON_Thickening(*child_node);
    }
    else
    if (ON_CURVE_PIPING_ROOT == s)
    {
      m_curve_piping = new ON_CurvePiping(*child_node);
    }
    else
    if (ON_SHUTLINING_ROOT == s)
    {
      m_shut_lining = new ON_ShutLining(*child_node);
    }
  }
}

ON_MeshModifiers::CImpl::~CImpl()
{
  DeleteAll();
}

void ON_MeshModifiers::CImpl::DeleteAll(void)
{
  if (nullptr != m_displacement)
  {
    delete m_displacement;
    m_displacement = nullptr;
  }

  if (nullptr != m_edge_softening)
  {
    delete m_edge_softening;
    m_edge_softening = nullptr;
  }

  if (nullptr != m_thickening)
  {
    delete m_thickening;
    m_thickening = nullptr;
  }

  if (nullptr != m_curve_piping)
  {
    delete m_curve_piping;
    m_curve_piping = nullptr;
  }

  if (nullptr != m_shut_lining)
  {
    delete m_shut_lining;
    m_shut_lining = nullptr;
  }
}

ON_MeshModifiers::ON_MeshModifiers()
{
  m_impl = new CImpl;
}

ON_MeshModifiers::~ON_MeshModifiers()
{
  delete m_impl;
  m_impl = nullptr;
}

void ON_MeshModifiers::LoadFromXML(const ON_XMLRootNode& node)
{
  m_impl->LoadFromXML(node);
}

const ON_MeshModifiers& ON_MeshModifiers::operator = (const ON_MeshModifiers& mm)
{
  m_impl->DeleteAll();

  if (nullptr != mm.m_impl->m_displacement)
    m_impl->m_displacement = new ON_Displacement(*mm.m_impl->m_displacement);

  if (nullptr != mm.m_impl->m_edge_softening)
    m_impl->m_edge_softening = new ON_EdgeSoftening(*mm.m_impl->m_edge_softening);

  if (nullptr != mm.m_impl->m_thickening)
    m_impl->m_thickening = new ON_Thickening(*mm.m_impl->m_thickening);

  if (nullptr != mm.m_impl->m_curve_piping)
    m_impl->m_curve_piping = new ON_CurvePiping(*mm.m_impl->m_curve_piping);

  if (nullptr != mm.m_impl->m_shut_lining)
    m_impl->m_shut_lining = new ON_ShutLining(*mm.m_impl->m_shut_lining);

  return *this;
}

ON_Displacement* ON_MeshModifiers::Displacement(bool allow_creation)
{
  if ((nullptr == m_impl->m_displacement) && allow_creation)
    m_impl->m_displacement = new ON_Displacement;

  return m_impl->m_displacement;
}

ON_EdgeSoftening* ON_MeshModifiers::EdgeSoftening(bool allow_creation)
{
  if ((nullptr == m_impl->m_edge_softening) && allow_creation)
    m_impl->m_edge_softening = new ON_EdgeSoftening;

  return m_impl->m_edge_softening;
}

ON_Thickening* ON_MeshModifiers::Thickening(bool allow_creation)
{
  if ((nullptr == m_impl->m_thickening) && allow_creation)
    m_impl->m_thickening = new ON_Thickening;

  return m_impl->m_thickening;
}

ON_CurvePiping* ON_MeshModifiers::CurvePiping(bool allow_creation)
{
  if ((nullptr == m_impl->m_curve_piping) && allow_creation)
    m_impl->m_curve_piping = new ON_CurvePiping;

  return m_impl->m_curve_piping;
}

ON_ShutLining* ON_MeshModifiers::ShutLining(bool allow_creation)
{
  if ((nullptr == m_impl->m_shut_lining) && allow_creation)
    m_impl->m_shut_lining = new ON_ShutLining;

  return m_impl->m_shut_lining;
}

void CreateMeshModifiersFromXML(const ONX_Model& model, int archive_3dm_version)
{
  ONX_ModelComponentIterator cit(model, ON_ModelComponent::Type::ModelGeometry);

  for (const ON_ModelComponent* component = cit.FirstComponent(); nullptr != component; component = cit.NextComponent())
  {
    ON_3dmObjectAttributes* attr = GetComponentAttributes(*component);
    if (nullptr == attr)
      continue; // No attributes on component.

    // Get the entire XML off of the attributes user data.
    ON_wString xml;
    ::GetMeshModifierObjectInformation(*attr, xml, archive_3dm_version);
    if (xml.IsEmpty())
      continue; // No XML found on the component's attributes.

    ON_XMLRootNode root;
    if (ON_XMLRootNode::ReadError != root.ReadFromStream(xml))
    {
      attr->MeshModifiers().LoadFromXML(root);
    }
  }
}

void CreateXMLFromMeshModifiers(const ONX_Model& model, int archive_3dm_version)
{
  ONX_ModelComponentIterator cit(model, ON_ModelComponent::Type::ModelGeometry);

  for (const ON_ModelComponent* component = cit.FirstComponent(); nullptr != component; component = cit.NextComponent())
  {
    ON_3dmObjectAttributes* attr = GetComponentAttributes(*component);
    if (nullptr == attr)
      continue; // No attributes on component.

    ON_MeshModifiers& mm = attr->MeshModifiers();
    SetMeshModifierObjectInformation(*attr, mm.Displacement(),  archive_3dm_version);
    SetMeshModifierObjectInformation(*attr, mm.EdgeSoftening(), archive_3dm_version);
    SetMeshModifierObjectInformation(*attr, mm.Thickening(),    archive_3dm_version);
    SetMeshModifierObjectInformation(*attr, mm.CurvePiping(),   archive_3dm_version);
    SetMeshModifierObjectInformation(*attr, mm.ShutLining(),    archive_3dm_version);
  }
}
