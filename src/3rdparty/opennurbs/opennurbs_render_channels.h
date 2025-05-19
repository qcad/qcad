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

#if !defined(ON_RENDER_CHANNELS_INC_)
#define ON_RENDER_CHANNELS_INC_

class ON_CLASS ON_RenderChannels
{
public:
  ON_RenderChannels();
  ON_RenderChannels(ON_XMLNode& model_node);
  ON_RenderChannels(const ON_RenderChannels& rch);
  virtual ~ON_RenderChannels();

  virtual const ON_RenderChannels& operator = (const ON_RenderChannels& rch);

  virtual bool operator == (const ON_RenderChannels& rch) const;
  virtual bool operator != (const ON_RenderChannels& rch) const;

  enum class Modes : unsigned int
  {
    Automatic,
    Custom,
  };

  // Get the mode.
  virtual Modes Mode(void) const;

  // Set the mode.
  virtual void SetMode(Modes m);

  // Get the list of channels to render when in 'custom' mode.
  // - 'chan' accepts the channel ids. */
  virtual void GetCustomList(ON_SimpleArray<ON_UUID>& chan) const;

  // Set the list of channels to render when in 'custom' mode.
  // - 'chan' contains the channel ids.
  virtual void SetCustomList(const ON_SimpleArray<ON_UUID>& chan);

  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

  // For internal use only.
  virtual void OnInternalXmlChanged(const ON_RenderChannels*);

private:
  class CImpl;
  CImpl* m_impl;
};

#endif
