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

class ON_SafeFrame::CImpl : public ON_InternalXMLImpl
{
public:
  CImpl() { }
  CImpl(ON_XMLNode& n) : ON_InternalXMLImpl(&n) { }

  ON_XMLVariant GetBaseParameter(const wchar_t* param_name, const ON_XMLVariant& def) const;
  bool SetBaseParameter(const wchar_t* param_name, const ON_XMLVariant& value);

  ON_XMLVariant GetFrameParameter(const wchar_t* frame_name, const wchar_t* param_name, const ON_XMLVariant& def) const;
  bool SetFrameParameter(const wchar_t* frame_name, const wchar_t* param_name, const ON_XMLVariant& value);
};

static const wchar_t* XMLPathBase(void)
{
  return ON_RDK_DOCUMENT  ON_XML_SLASH  ON_RDK_SETTINGS  ON_XML_SLASH  ON_RDK_SAFE_FRAME;
}

static ON_wString XMLPath(const ON_wString& section_name)
{
  ON_wString s = XMLPathBase();
  ON_ASSERT(section_name.IsNotEmpty());
  s += ON_XML_SLASH;
  s += section_name;

  return s;
}

ON_XMLVariant ON_SafeFrame::CImpl::GetBaseParameter(const wchar_t* param_name, const ON_XMLVariant& def) const
{
  return GetParameter(XMLPathBase(), param_name, def);
}

bool ON_SafeFrame::CImpl::SetBaseParameter(const wchar_t* param_name, const ON_XMLVariant& value)
{
  return SetParameter(XMLPathBase(), param_name, value);
}

ON_XMLVariant ON_SafeFrame::CImpl::GetFrameParameter(const wchar_t* frame_name, const wchar_t* param_name, const ON_XMLVariant& def) const
{
  return GetParameter(XMLPath(frame_name), param_name, def);
}

bool ON_SafeFrame::CImpl::SetFrameParameter(const wchar_t* frame_name, const wchar_t* param_name, const ON_XMLVariant& value)
{
  return SetParameter(XMLPath(frame_name), param_name, value);
}

ON_SafeFrame::ON_SafeFrame()
{
  m_impl = new CImpl;
}

ON_SafeFrame::ON_SafeFrame(ON_XMLNode& model_node)
{
  m_impl = new CImpl(model_node);
}

ON_SafeFrame::ON_SafeFrame(const ON_SafeFrame& sf)
{
  m_impl = new CImpl;
  operator = (sf);
}

ON_SafeFrame::~ON_SafeFrame()
{
  delete m_impl;
  m_impl = nullptr;
}

const ON_SafeFrame& ON_SafeFrame::operator = (const ON_SafeFrame& sf)
{
  if (this != &sf)
  {
    SetEnabled          (sf.Enabled());
    SetPerspectiveOnly  (sf.PerspectiveOnly());
    SetFieldGridOn      (sf.FieldGridOn());
    SetLiveFrameOn      (sf.LiveFrameOn());
    SetActionFrameOn    (sf.ActionFrameOn());
    SetActionFrameLinked(sf.ActionFrameLinked());
    SetTitleFrameOn     (sf.TitleFrameOn());
    SetTitleFrameLinked (sf.TitleFrameLinked());
    SetActionFrameXScale(sf.ActionFrameXScale());
    SetActionFrameYScale(sf.ActionFrameYScale());
    SetTitleFrameXScale (sf.TitleFrameXScale());
    SetTitleFrameYScale (sf.TitleFrameYScale());
  }

  return *this;
}

bool ON_SafeFrame::operator == (const ON_SafeFrame& sf) const
{
  if (Enabled()           != sf.Enabled())           return false;
  if (PerspectiveOnly()   != sf.PerspectiveOnly())   return false;
  if (FieldGridOn()       != sf.FieldGridOn())       return false;
  if (LiveFrameOn()       != sf.LiveFrameOn())       return false;
  if (ActionFrameOn()     != sf.ActionFrameOn())     return false;
  if (ActionFrameLinked() != sf.ActionFrameLinked()) return false;
  if (TitleFrameOn()      != sf.TitleFrameOn())      return false;
  if (TitleFrameLinked()  != sf.TitleFrameLinked())  return false;

  if (!IsDoubleEqual(ActionFrameXScale(), sf.ActionFrameXScale())) return false;
  if (!IsDoubleEqual(ActionFrameYScale(), sf.ActionFrameYScale())) return false;
  if (!IsDoubleEqual(TitleFrameXScale() , sf.TitleFrameXScale())) return false;
  if (!IsDoubleEqual(TitleFrameYScale() , sf.TitleFrameYScale())) return false;

  return true;
}

bool ON_SafeFrame::operator != (const ON_SafeFrame& sf) const
{
  return !(operator == (sf));
}

bool ON_SafeFrame::Enabled(void) const
{
  return m_impl->GetBaseParameter(ON_RDK_SF_ENABLED, false).AsBool();
}

void ON_SafeFrame::SetEnabled(bool b)
{
  m_impl->SetBaseParameter(ON_RDK_SF_ENABLED, b);
}

bool ON_SafeFrame::PerspectiveOnly(void) const
{
  return m_impl->GetBaseParameter(ON_RDK_SF_PERSPECTIVE_ONLY, false).AsBool();
}

void ON_SafeFrame::SetPerspectiveOnly(bool b)
{
  m_impl->SetBaseParameter(ON_RDK_SF_PERSPECTIVE_ONLY, b);
}

bool ON_SafeFrame::FieldGridOn(void) const
{
  return m_impl->GetBaseParameter(ON_RDK_SF_4x3_FIELD_GRID_ON, false).AsBool();
}

void ON_SafeFrame::SetFieldGridOn(bool b)
{
  m_impl->SetBaseParameter(ON_RDK_SF_4x3_FIELD_GRID_ON, b);
}

bool ON_SafeFrame::LiveFrameOn(void) const
{
  return m_impl->GetFrameParameter(ON_RDK_SF_LIVE_FRAME, ON_RDK_SFF_ON, false).AsBool();
}

void ON_SafeFrame::SetLiveFrameOn(bool b)
{
  m_impl->SetFrameParameter(ON_RDK_SF_LIVE_FRAME, ON_RDK_SFF_ON, b);
}

bool ON_SafeFrame::ActionFrameOn(void) const
{
  return m_impl->GetFrameParameter(ON_RDK_SF_ACTION_FRAME, ON_RDK_SFF_ON, false).AsBool();
}

void ON_SafeFrame::SetActionFrameOn(bool b)
{
  m_impl->SetFrameParameter(ON_RDK_SF_ACTION_FRAME, ON_RDK_SFF_ON, b);
}

bool ON_SafeFrame::ActionFrameLinked(void) const
{
  return m_impl->GetFrameParameter(ON_RDK_SF_ACTION_FRAME, ON_RDK_SFF_LINK, false).AsBool();
}

void ON_SafeFrame::SetActionFrameLinked(bool b)
{
  m_impl->SetFrameParameter(ON_RDK_SF_ACTION_FRAME, ON_RDK_SFF_LINK, b);
}

double ON_SafeFrame::ActionFrameXScale(void) const
{
  return m_impl->GetFrameParameter(ON_RDK_SF_ACTION_FRAME, ON_RDK_SFF_XSCALE, 0.9).AsDouble();
}

void ON_SafeFrame::SetActionFrameXScale(double d)
{
  m_impl->SetFrameParameter(ON_RDK_SF_ACTION_FRAME, ON_RDK_SFF_XSCALE, d);
}

double ON_SafeFrame::ActionFrameYScale(void) const
{
  return m_impl->GetFrameParameter(ON_RDK_SF_ACTION_FRAME, ON_RDK_SFF_YSCALE, 0.9).AsDouble();
}

void ON_SafeFrame::SetActionFrameYScale(double d)
{
  m_impl->SetFrameParameter(ON_RDK_SF_ACTION_FRAME, ON_RDK_SFF_YSCALE, d);
}

bool ON_SafeFrame::TitleFrameOn(void) const
{
  return m_impl->GetFrameParameter(ON_RDK_SF_TITLE_FRAME, ON_RDK_SFF_ON, false).AsBool();
}

void ON_SafeFrame::SetTitleFrameOn(bool b)
{
  m_impl->SetFrameParameter(ON_RDK_SF_TITLE_FRAME, ON_RDK_SFF_ON, b);
}

bool ON_SafeFrame::TitleFrameLinked(void) const
{
  return m_impl->GetFrameParameter(ON_RDK_SF_TITLE_FRAME, ON_RDK_SFF_LINK, false).AsBool();
}

void ON_SafeFrame::SetTitleFrameLinked(bool b)
{
  m_impl->SetFrameParameter(ON_RDK_SF_TITLE_FRAME, ON_RDK_SFF_LINK, b);
}

double ON_SafeFrame::TitleFrameXScale(void) const
{
  return m_impl->GetFrameParameter(ON_RDK_SF_TITLE_FRAME, ON_RDK_SFF_XSCALE, 0.8).AsDouble();
}

void ON_SafeFrame::SetTitleFrameXScale(double d)
{
  m_impl->SetFrameParameter(ON_RDK_SF_TITLE_FRAME, ON_RDK_SFF_XSCALE, d);
}

double ON_SafeFrame::TitleFrameYScale(void) const
{
  return m_impl->GetFrameParameter(ON_RDK_SF_TITLE_FRAME, ON_RDK_SFF_YSCALE, 0.8).AsDouble();
}

void ON_SafeFrame::SetTitleFrameYScale(double d)
{
  m_impl->SetFrameParameter(ON_RDK_SF_TITLE_FRAME, ON_RDK_SFF_YSCALE, d);
}

void* ON_SafeFrame::EVF(const wchar_t* func, void* data)
{
  return nullptr;
}

void ON_SafeFrame::OnInternalXmlChanged(const ON_SafeFrame*)
{
}
