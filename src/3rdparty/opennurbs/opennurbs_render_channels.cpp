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

#define ON_RDK_RENDER_CHANNELS        L"render-channels"
  #define ON_RDK_RCH_MODE               L"mode"
  #define   ON_RDK_RCH_MODE_AUTOMATIC     L"automatic"
  #define   ON_RDK_RCH_MODE_CUSTOM        L"custom"
  #define ON_RDK_RCH_LIST               L"list"

class ON_RenderChannels::CImpl : public ON_InternalXMLImpl
{
public:
  CImpl() { }
  CImpl(ON_XMLNode& n) : ON_InternalXMLImpl(&n) { }
};

static const wchar_t* XMLPath(void)
{
  return ON_RDK_DOCUMENT   ON_XML_SLASH  ON_RDK_SETTINGS  ON_XML_SLASH
         ON_RDK_RENDERING  ON_XML_SLASH  ON_RDK_RENDER_CHANNELS;
}

ON_RenderChannels::ON_RenderChannels()
{
  m_impl = new CImpl;
}

ON_RenderChannels::ON_RenderChannels(ON_XMLNode& model_node)
{
  m_impl = new CImpl(model_node);
}

ON_RenderChannels::ON_RenderChannels(const ON_RenderChannels& rch)
{
  m_impl = new CImpl;
  operator = (rch);
}

ON_RenderChannels::~ON_RenderChannels()
{
  delete m_impl;
  m_impl = nullptr;
}

const ON_RenderChannels& ON_RenderChannels::operator = (const ON_RenderChannels& rch)
{
  if (this != &rch)
  {
    SetMode(rch.Mode());

    ON_SimpleArray<ON_UUID> chan;
    rch.GetCustomList(chan);
    SetCustomList(chan);
  }

  return *this;
}

static ON_wString GetSortedSemicolonDelimitedString(const ON_SimpleArray<ON_UUID>& chan)
{
  ON_wString s;

  ON_ClassArray<ON_wString> a;

  for (int i = 0; i < chan.Count(); i++)
  {
    ON_UuidToString(chan[i], s);
    a.Append(s);
  }

  a.QuickSort(ON_CompareIncreasing);

  s = L"";
  for (int i = 0; i < a.Count(); i++)
  {
    s += a[i];
    if (i < (a.Count() - 1))
      s += L";";
  }

  return s;
}

static ON_wString GetSortedCustomListAsString(const ON_RenderChannels& rch)
{
  ON_SimpleArray<ON_UUID> chan;
  rch.GetCustomList(chan);

  return GetSortedSemicolonDelimitedString(chan);
}

bool ON_RenderChannels::operator == (const ON_RenderChannels& rch) const
{
  if (Mode() != rch.Mode())
    return false;

  ON_ClassArray<ON_wString> a, b;
  const ON_wString s1 = GetSortedCustomListAsString(*this);
  const ON_wString s2 = GetSortedCustomListAsString(rch);
  if (s1 != s2)
    return false;

  return true;
}

bool ON_RenderChannels::operator != (const ON_RenderChannels& rch) const
{
  return !(operator == (rch));
}

ON_RenderChannels::Modes ON_RenderChannels::Mode(void) const
{
  auto mode = Modes::Automatic;

  const ON_wString s = m_impl->GetParameter(XMLPath(), ON_RDK_RCH_MODE, ON_RDK_RCH_MODE_AUTOMATIC).AsString();
  if (ON_RDK_RCH_MODE_CUSTOM == s)
    mode = Modes::Custom;

  return mode;
}

void ON_RenderChannels::SetMode(Modes m)
{
  ON_wString s = ON_RDK_RCH_MODE_AUTOMATIC;
  if (Modes::Custom == m)
    s = ON_RDK_RCH_MODE_CUSTOM;

  m_impl->SetParameter(XMLPath(), ON_RDK_RCH_MODE, s);
}

void ON_RenderChannels::GetCustomList(ON_SimpleArray<ON_UUID>& chan) const
{
  ON_wString s = m_impl->GetParameter(XMLPath(), ON_RDK_RCH_LIST, false).AsString();
  const int len = s.Length();
  if (len == 0)
    return;

  if (s[len-1] != L';')
    s += L';';

  int pos = -1;
  while ((pos = s.Find(L";")) >= 0)
  {
    const ON_UUID uuid = ON_UuidFromString(s.Left(pos));
    chan.Append(uuid);
    s = s.Mid(pos+1);
  }
}

void ON_RenderChannels::SetCustomList(const ON_SimpleArray<ON_UUID>& chan)
{
  const ON_wString s = GetSortedSemicolonDelimitedString(chan);
  m_impl->SetParameter(XMLPath(), ON_RDK_RCH_LIST, s);
}

void* ON_RenderChannels::EVF(const wchar_t* func, void* data)
{
  return nullptr;
}

void ON_RenderChannels::OnInternalXmlChanged(const ON_RenderChannels*)
{
}
