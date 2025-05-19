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

class ON_Dithering::CImpl : public ON_InternalXMLImpl
{
public:
  CImpl() { }
  CImpl(ON_XMLNode& n) : ON_InternalXMLImpl(&n) { }
};

static const wchar_t* XMLPathDit(void)
{
  return ON_RDK_DOCUMENT  ON_XML_SLASH  ON_RDK_SETTINGS  ON_XML_SLASH  ON_RDK_RENDERING;
}

ON_Dithering::ON_Dithering()
{
  m_impl = new CImpl;
}

ON_Dithering::ON_Dithering(ON_XMLNode& model_node)
{
  m_impl = new CImpl(model_node);
}

ON_Dithering::ON_Dithering(const ON_Dithering& dit)
{
  m_impl = new CImpl;
  operator = (dit);
}

ON_Dithering::~ON_Dithering()
{
  delete m_impl;
  m_impl = nullptr;
}

const ON_Dithering& ON_Dithering::operator = (const ON_Dithering& dit)
{
  if (this != &dit)
  {
    SetEnabled(dit.Enabled());
    SetMethod (dit.Method());
  }

  return *this;
}

bool ON_Dithering::operator == (const ON_Dithering& dit) const
{
  if (Enabled() != dit.Enabled()) return false;
  if (Method()  != dit.Method())  return false;

  return true;
}

bool ON_Dithering::operator != (const ON_Dithering& dit) const
{
  return !(operator == (dit));
}

bool ON_Dithering::Enabled(void) const
{
  return m_impl->GetParameter(XMLPathDit(), ON_RDK_DITHERING_ENABLED, false);
}

void ON_Dithering::SetEnabled(bool b)
{
  m_impl->SetParameter(XMLPathDit(), ON_RDK_DITHERING_ENABLED, b);
}

ON_Dithering::Methods ON_Dithering::Method(void) const
{
  const ON_wString s = m_impl->GetParameter(XMLPathDit(), ON_RDK_DITHERING_METHOD, L"").AsString();
  if (ON_RDK_DITHERING_METHOD_FLOYD_STEINBERG == s)
    return Methods::FloydSteinberg;

  return Methods::SimpleNoise;
}

void ON_Dithering::SetMethod(Methods m)
{
  const wchar_t* wsz = ON_RDK_DITHERING_METHOD_SIMPLE_NOISE;
  if (Methods::FloydSteinberg == m)
    wsz = ON_RDK_DITHERING_METHOD_FLOYD_STEINBERG;

  m_impl->SetParameter(XMLPathDit(), ON_RDK_DITHERING_METHOD, wsz);
}

ON__UINT32 ON_Dithering::DataCRC(ON__UINT32 crc) const
{
  const bool b = Enabled();
  crc = ON_CRC32(crc, sizeof(b), &b);

  const auto m = Method();
  crc = ON_CRC32(crc, sizeof(m), &m);

  return crc;
}

void* ON_Dithering::EVF(const wchar_t* func, void* data)
{
 return nullptr;
}

void ON_Dithering::OnInternalXmlChanged(const ON_Dithering*)
{
}
