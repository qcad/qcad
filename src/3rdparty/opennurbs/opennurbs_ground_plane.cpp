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

static const wchar_t* XMLPath(void)
{
  return ON_RDK_DOCUMENT  ON_XML_SLASH  ON_RDK_SETTINGS  ON_XML_SLASH  ON_RDK_GROUND_PLANE;
}

class ON_GroundPlane::CImpl : public ON_InternalXMLImpl
{
public:
  CImpl() { }
  CImpl(const CImpl& i) = delete;
  CImpl(ON_XMLNode& n)  : ON_InternalXMLImpl(&n) { }

  bool Enabled(void)               const { return GetParameter(XMLPath(), ON_RDK_GP_ENABLED, false).AsBool(); }
  bool ShowUnderside(void)         const { return GetParameter(XMLPath(), ON_RDK_GP_SHOW_UNDERSIDE, false).AsBool(); }
  double Altitude(void)            const { return GetParameter(XMLPath(), ON_RDK_GP_ALTITUDE, 0.0).AsDouble(); }
  bool AutoAltitude(void)          const { return GetParameter(XMLPath(), ON_RDK_GP_AUTO_ALTITUDE, false).AsBool(); }
  bool ShadowOnly(void)            const { return GetParameter(XMLPath(), ON_RDK_GP_SHADOW_ONLY, true).AsBool(); }
  bool TextureOffsetLocked(void)   const { return GetParameter(XMLPath(), ON_RDK_GP_TEXTURE_OFFSET_LOCKED, false).AsBool(); }
  bool TextureSizeLocked(void)     const { return GetParameter(XMLPath(), ON_RDK_GP_TEXTURE_SIZE_LOCKED, false).AsBool(); }
  double TextureRotation(void)     const { return GetParameter(XMLPath(), ON_RDK_GP_TEXTURE_ROTATION, false).AsDouble(); }
  ON_UUID MaterialInstanceId(void) const { return GetParameter(XMLPath(), ON_RDK_GP_MATERIAL_ID, ON_nil_uuid).AsUuid(); }
  ON_2dVector TextureOffset(void)  const { return ON_2dVector(GetParameter(XMLPath(), ON_RDK_GP_TEXTURE_OFFSET, ON_nil_uuid).As2dPoint()); }
  ON_2dVector TextureSize(void)    const { return ON_2dVector(GetParameter(XMLPath(), ON_RDK_GP_TEXTURE_SIZE, ON_nil_uuid).As2dPoint()); }

  void SetEnabled(bool v)                      { SetParameter(XMLPath(), ON_RDK_GP_ENABLED, v); }
  void SetShowUnderside(bool v)                { SetParameter(XMLPath(), ON_RDK_GP_SHOW_UNDERSIDE, v); }
  void SetAltitude(double v)                   { SetParameter(XMLPath(), ON_RDK_GP_ALTITUDE, v); }
  void SetAutoAltitude(bool v)                 { SetParameter(XMLPath(), ON_RDK_GP_AUTO_ALTITUDE, v); }
  void SetShadowOnly(bool v)                   { SetParameter(XMLPath(), ON_RDK_GP_SHADOW_ONLY, v); }
  void SetMaterialInstanceId(const ON_UUID& v) { SetParameter(XMLPath(), ON_RDK_GP_MATERIAL_ID, v); }
  void SetTextureOffsetLocked(bool v)          { SetParameter(XMLPath(), ON_RDK_GP_TEXTURE_OFFSET_LOCKED, v); }
  void SetTextureSizeLocked(bool v)            { SetParameter(XMLPath(), ON_RDK_GP_TEXTURE_SIZE_LOCKED, v); }
  void SetTextureRotation(double v)            { SetParameter(XMLPath(), ON_RDK_GP_TEXTURE_ROTATION, v); }
  void SetTextureOffset(const ON_2dVector& v)  { const ON_2dPoint p = v; SetParameter(XMLPath(), ON_RDK_GP_TEXTURE_OFFSET, p); }
  void SetTextureSize(const ON_2dVector& v)    { const ON_2dPoint p = v; SetParameter(XMLPath(), ON_RDK_GP_TEXTURE_SIZE, p); }
};

ON_GroundPlane::ON_GroundPlane()
{
  _impl = new CImpl; // Uses local node.
}

ON_GroundPlane::ON_GroundPlane(ON_XMLNode& model_node)
{
  _impl = new CImpl(model_node);
}

ON_GroundPlane::ON_GroundPlane(const ON_GroundPlane& gp)
{
  _impl = new CImpl; // Uses local node.
  operator = (gp);
}

ON_GroundPlane::~ON_GroundPlane()
{
  delete _impl;
  _impl = nullptr;
}

const ON_GroundPlane& ON_GroundPlane::operator = (const ON_GroundPlane& gp)
{
  if (this != &gp)
  {
    // When copying the object, we need to directly copy the underlying XML. So we can't allow
    // virtual overrides to execute because they might hide the real values we want to copy.
    _impl->SetEnabled            (gp._impl->Enabled());
    _impl->SetShowUnderside      (gp._impl->ShowUnderside());
    _impl->SetAltitude           (gp._impl->Altitude());
    _impl->SetAutoAltitude       (gp._impl->AutoAltitude());
    _impl->SetShadowOnly         (gp._impl->ShadowOnly());
    _impl->SetMaterialInstanceId (gp._impl->MaterialInstanceId());
    _impl->SetTextureOffset      (gp._impl->TextureOffset());
    _impl->SetTextureOffsetLocked(gp._impl->TextureOffsetLocked());
    _impl->SetTextureSize        (gp._impl->TextureSize());
    _impl->SetTextureSizeLocked  (gp._impl->TextureSizeLocked());
    _impl->SetTextureRotation    (gp._impl->TextureRotation());
  }

  return *this;
}

bool ON_GroundPlane::operator == (const ON_GroundPlane& gp) const
{
  // When checking equality, we need to directly check the underlying storage. So we can't allow
  // virtual overrides to execute because they might hide the real values we want to check.
  if (_impl->Enabled()             != gp._impl->Enabled()            ) return false;
  if (_impl->ShowUnderside()       != gp._impl->ShowUnderside()      ) return false;
  if (_impl->AutoAltitude()        != gp._impl->AutoAltitude()       ) return false;
  if (_impl->ShadowOnly()          != gp._impl->ShadowOnly()         ) return false;
  if (_impl->MaterialInstanceId()  != gp._impl->MaterialInstanceId() ) return false;
  if (_impl->TextureOffset()       != gp._impl->TextureOffset()      ) return false;
  if (_impl->TextureOffsetLocked() != gp._impl->TextureOffsetLocked()) return false;
  if (_impl->TextureSize()         != gp._impl->TextureSize()        ) return false;
  if (_impl->TextureSizeLocked()   != gp._impl->TextureSizeLocked()  ) return false;

  if (!IsDoubleEqual(_impl->Altitude(),        gp._impl->Altitude()))        return false;
  if (!IsDoubleEqual(_impl->TextureRotation(), gp._impl->TextureRotation())) return false;

  return true;
}

bool ON_GroundPlane::operator != (const ON_GroundPlane& gp) const
{
  return !(operator == (gp));
}

bool ON_GroundPlane::Enabled(void) const
{
  return _impl->Enabled();
}

bool ON_GroundPlane::ShowUnderside(void) const
{
  return _impl->ShowUnderside();
}

double ON_GroundPlane::Altitude(void) const
{
  return _impl->Altitude();
}

bool ON_GroundPlane::AutoAltitude(void) const
{
  return _impl->AutoAltitude();
}

bool ON_GroundPlane::ShadowOnly(void) const
{
  return _impl->ShadowOnly();
}

ON_UUID ON_GroundPlane::MaterialInstanceId(void) const
{
  return _impl->MaterialInstanceId();
}

ON_2dVector ON_GroundPlane::TextureOffset(void) const
{
  return _impl->TextureOffset();
}

bool ON_GroundPlane::TextureOffsetLocked(void) const
{
  return _impl->TextureOffsetLocked();
}

ON_2dVector ON_GroundPlane::TextureSize(void) const
{
  return _impl->TextureSize();
}

bool ON_GroundPlane::TextureSizeLocked(void) const
{
  return _impl->TextureSizeLocked();
}

double ON_GroundPlane::TextureRotation(void) const
{
  return _impl->TextureRotation();
}

void ON_GroundPlane::SetEnabled(bool v)
{
  _impl->SetEnabled(v);
}

void ON_GroundPlane::SetShowUnderside(bool v)
{
  _impl->SetShowUnderside(v);
}

void ON_GroundPlane::SetAltitude(double v)
{
  _impl->SetAltitude(v);
}

void ON_GroundPlane::SetAutoAltitude(bool v)
{
  _impl->SetAutoAltitude(v);
}

void ON_GroundPlane::SetShadowOnly(bool v)
{
  _impl->SetShadowOnly(v);
}

void ON_GroundPlane::SetMaterialInstanceId(const ON_UUID& v)
{
  _impl->SetMaterialInstanceId(v);
}

void ON_GroundPlane::SetTextureOffset(const ON_2dVector& v)
{
  _impl->SetTextureOffset(v);
}

void ON_GroundPlane::SetTextureOffsetLocked(bool v)
{
  _impl->SetTextureOffsetLocked(v);
}

void ON_GroundPlane::SetTextureSize(const ON_2dVector& v)
{
  _impl->SetTextureSize(v);
}

void ON_GroundPlane::SetTextureSizeLocked(bool v)
{
  _impl->SetTextureSizeLocked(v);
}

void ON_GroundPlane::SetTextureRotation(double v)
{
  _impl->SetTextureRotation(v);
}

bool ON_GroundPlane::PopulateMaterial(ON_Material& mat) const
{
  mat = ON_Material::Default;
  return true;
}

void ON_GroundPlane::SetXMLNode(ON_XMLNode& node) const
{
  _impl->SetModelNode(node);
}

void* ON_GroundPlane::EVF(const wchar_t* func, void* data)
{
  return nullptr;
}

void ON_GroundPlane::OnInternalXmlChanged(const ON_GroundPlane*)
{
}
