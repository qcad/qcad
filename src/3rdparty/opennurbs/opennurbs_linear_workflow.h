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

#if !defined(ON_LINEAR_WORKFLOW_INC_)
#define ON_LINEAR_WORKFLOW_INC_

class ON_CLASS ON_LinearWorkflow
{
public:
  ON_LinearWorkflow();
  ON_LinearWorkflow(ON_XMLNode& model_node);
  ON_LinearWorkflow(const ON_LinearWorkflow& lw);
  virtual ~ON_LinearWorkflow();

  virtual const ON_LinearWorkflow& operator = (const ON_LinearWorkflow& lw);

  virtual bool operator == (const ON_LinearWorkflow& lw) const;
  virtual bool operator != (const ON_LinearWorkflow& lw) const;

  // Returns the linear workflow (pre-process) active state for textures.
  virtual bool PreProcessTexturesOn(void) const;

  // Sets the linear workflow (pre-process) active state for textures.
  virtual void SetPreProcessTexturesOn(bool b);

  // Returns the linear workflow active state for individual colors.
  virtual bool PreProcessColorsOn(void) const;

  // Sets the linear workflow (pre-process) active state for individual colors.
  virtual void SetPreProcessColorsOn(bool b);

  // Get post-process frame buffer enabled state.
  virtual bool PostProcessFrameBufferOn(void) const;

  // Set post-process frame buffer enabled state.
  virtual void SetPostProcessFrameBufferOn(bool on);

  // Get pre-process gamma enabled state. This is the same as 'use linear workflow'.
  virtual bool PreProcessGammaOn(void) const;

  // Set pre-process gamma enabled state. This is the same as 'use linear workflow'.
  virtual void SetPreProcessGammaOn(bool on);

  // Get the pre-process gamma for input textures and colors. This is currently the same as the post-process gamma value.
  virtual float PreProcessGamma(void) const;

  // Set the pre-process gamma for input textures and colors. This is currently the same as the post-process gamma value.
  virtual void SetPreProcessGamma(float gamma);

  // Get post-process gamma enabled state.
  virtual bool PostProcessGammaOn(void) const;

  // Set post-process gamma enabled state.
  virtual void SetPostProcessGammaOn(bool on);

  // Get the post-process gamma for the frame buffer.
  virtual float PostProcessGamma(void) const;

  // Set the post-process gamma for the frame buffer.
  virtual void SetPostProcessGamma(float gamma);

  // Applies pre-process gamma correction to a color if linear workflow is active.
  // for_texture is true if the color is part of a texture. */
  virtual void ApplyPreProcessGamma(ON_4fColor& col, bool for_texture) const;

  // Returns the CRC of gamma and linear workflow active state.
  virtual ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;

  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

  // For internal use only.
  virtual void OnInternalXmlChanged(const ON_LinearWorkflow*);

private: // For internal use only.
  friend class ON_3dmRenderSettingsPrivate;
  void SetXMLNode(ON_XMLNode& node) const;

private:
  class CImpl;
  CImpl* _impl;
};

#endif
