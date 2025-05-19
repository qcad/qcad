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

class ON_LinearWorkflow::CImpl : public ON_InternalXMLImpl
{
public:
  CImpl() { }
  CImpl(ON_XMLNode& n) : ON_InternalXMLImpl(&n) { }
};

static const wchar_t* XMLPath(void)
{
  return ON_RDK_DOCUMENT  ON_XML_SLASH  ON_RDK_SETTINGS  ON_XML_SLASH  ON_RDK_RENDERING;
}

ON_LinearWorkflow::ON_LinearWorkflow()
{
  _impl = new CImpl;
}

ON_LinearWorkflow::ON_LinearWorkflow(ON_XMLNode& model_node)
{
  _impl = new CImpl(model_node);
}

ON_LinearWorkflow::ON_LinearWorkflow(const ON_LinearWorkflow& lw)
{
  _impl = new CImpl;
  operator = (lw);
}

ON_LinearWorkflow::~ON_LinearWorkflow()
{
  delete _impl;
  _impl = nullptr;
}

const ON_LinearWorkflow& ON_LinearWorkflow::operator = (const ON_LinearWorkflow& lw)
{
  if (this != &lw)
  {
    // When copying the object, we need to directly copy the underlying XML. So we can't allow
    // virtual overrides to execute because they might hide the real values we want to copy.
    using LW = ON_LinearWorkflow;
    LW::SetPreProcessTexturesOn    (lw.LW::PreProcessTexturesOn());
    LW::SetPreProcessColorsOn      (lw.LW::PreProcessColorsOn());
    LW::SetPostProcessFrameBufferOn(lw.LW::PostProcessFrameBufferOn());
    LW::SetPreProcessGammaOn       (lw.LW::PreProcessGammaOn());
    LW::SetPostProcessGammaOn      (lw.LW::PostProcessGammaOn());
    LW::SetPreProcessGamma         (lw.LW::PreProcessGamma());
    LW::SetPostProcessGamma        (lw.LW::PostProcessGamma());
  }

  return *this;
}

bool ON_LinearWorkflow::operator == (const ON_LinearWorkflow& lw) const
{
  // When checking equality, we need to directly check the underlying storage. So we can't allow
  // virtual overrides to execute because they might hide the real values we want to check.
  using LW = ON_LinearWorkflow;
  if (LW::PreProcessTexturesOn()         != lw.LW::PreProcessTexturesOn())     return false;
  if (LW::PreProcessColorsOn()           != lw.LW::PreProcessColorsOn())       return false;
  if (LW::PostProcessFrameBufferOn()     != lw.LW::PostProcessFrameBufferOn()) return false;
  if (LW::PreProcessGammaOn()            != lw.LW::PreProcessGammaOn())        return false;
  if (LW::PostProcessGammaOn()           != lw.LW::PostProcessGammaOn())       return false;
  if (!IsFloatEqual(LW::PreProcessGamma(),  lw.LW::PreProcessGamma()))         return false;
  if (!IsFloatEqual(LW::PostProcessGamma(), lw.LW::PostProcessGamma()))        return false;

  return true;
}

bool ON_LinearWorkflow::operator != (const ON_LinearWorkflow& lw) const
{
  return !(operator == (lw));
}

bool ON_LinearWorkflow::PreProcessTexturesOn(void) const
{
	return _impl->GetParameter(XMLPath(), ON_RDK_PRE_PROCESS_GAMMA_ON, false);
}

void ON_LinearWorkflow::SetPreProcessTexturesOn(bool b)
{
		_impl->SetParameter(XMLPath(), ON_RDK_PRE_PROCESS_GAMMA_ON, b);
}

bool ON_LinearWorkflow::PreProcessColorsOn(void) const
{
	return _impl->GetParameter(XMLPath(), ON_RDK_PRE_PROCESS_GAMMA_ON, false);
}

void ON_LinearWorkflow::SetPreProcessColorsOn(bool b)
{
		_impl->SetParameter(XMLPath(), ON_RDK_PRE_PROCESS_GAMMA_ON, b);
}

bool ON_LinearWorkflow::PreProcessGammaOn(void) const
{
	return _impl->GetParameter(XMLPath(), ON_RDK_PRE_PROCESS_GAMMA_ON, true);
}

void ON_LinearWorkflow::SetPreProcessGammaOn(bool on)
{
	_impl->SetParameter(XMLPath(), ON_RDK_PRE_PROCESS_GAMMA_ON, on);
}

bool ON_LinearWorkflow::PostProcessGammaOn(void) const
{
	return _impl->GetParameter(XMLPath(), ON_RDK_POST_PROCESS_GAMMA_ON, true);
}

void ON_LinearWorkflow::SetPostProcessGammaOn(bool on)
{
	_impl->SetParameter(XMLPath(), ON_RDK_POST_PROCESS_GAMMA_ON, on);
}

bool ON_LinearWorkflow::PostProcessFrameBufferOn(void) const
{
  return true; // Always on. For possible future use.
}

void ON_LinearWorkflow::SetPostProcessFrameBufferOn(bool)
{
	// Always on. Ignore the call.
}

static float ClampGamma(float f) { return std::min(5.0f, std::max(0.2f, f)); }

float ON_LinearWorkflow::PreProcessGamma(void) const
{
  return ON_LinearWorkflow::PostProcessGamma();
}

void ON_LinearWorkflow::SetPreProcessGamma(float gamma)
{
  ON_LinearWorkflow::SetPostProcessGamma(gamma);
}

float ON_LinearWorkflow::PostProcessGamma(void) const
{
  return ClampGamma(_impl->GetParameter(XMLPath(), ON_RDK_POST_PROCESS_GAMMA, 2.2f));
}

void ON_LinearWorkflow::SetPostProcessGamma(float gamma)
{
  _impl->SetParameter(XMLPath(), ON_RDK_POST_PROCESS_GAMMA, ClampGamma(gamma));
}

void ON_LinearWorkflow::ApplyPreProcessGamma(ON_4fColor& col, bool for_texture) const
{
  const bool check = for_texture ? PreProcessTexturesOn() : PreProcessColorsOn();
  if (!check)
    return;

  const float gamma = PreProcessGamma();
  if (!IsFloatEqual(gamma, 1.0f))
  {
    float* f = col.FloatArray();

    ON_ASSERT((f[0] >= 0.0) && (f[1] >= 0.0) && (f[2] >= 0.0));

    if (f[0] > 0.0) f[0] = powf(f[0], gamma);
    if (f[1] > 0.0) f[1] = powf(f[1], gamma);
    if (f[2] > 0.0) f[2] = powf(f[2], gamma);
  }
}

ON__UINT32 ON_LinearWorkflow::DataCRC(ON__UINT32 crc) const
{
  bool b[] = { PreProcessTexturesOn(), PreProcessColorsOn(), PostProcessFrameBufferOn(), PostProcessGammaOn() };
  crc = ON_CRC32(crc, sizeof(b), b);

  ON__INT64 f[] = { Integerize(PreProcessGamma()), Integerize(PostProcessGamma()) };
  crc = ON_CRC32(crc, sizeof(f), f);

  return crc;
}

void ON_LinearWorkflow::SetXMLNode(ON_XMLNode& node) const
{
  _impl->SetModelNode(node);
}

void* ON_LinearWorkflow::EVF(const wchar_t* func, void* data)
{
  return nullptr;
}

void ON_LinearWorkflow::OnInternalXmlChanged(const ON_LinearWorkflow*)
{
}
