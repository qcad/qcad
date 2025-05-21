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

#if !defined(ON_GROUND_PLANE_INC_)
#define ON_GROUND_PLANE_INC_

class ON_CLASS ON_GroundPlane
{
public:
  ON_GroundPlane();
  ON_GroundPlane(ON_XMLNode& model_node);
  ON_GroundPlane(const ON_GroundPlane& gp);
  virtual ~ON_GroundPlane();

  virtual const ON_GroundPlane& operator = (const ON_GroundPlane& gp);

  virtual bool operator == (const ON_GroundPlane& gp) const;
  virtual bool operator != (const ON_GroundPlane& gp) const;

  // Returns true if the ground plane is enabled, else false.
  virtual bool Enabled(void) const;

  // Returns true if ground plane backface is enabled, else false.
  virtual bool ShowUnderside(void) const;

  // Returns the altitude of the ground plane. Note that this merely returns the stored value. It does
  // not do any auto-altitude computation. Auto-altitude must be computed by a subclass (e.g., in Rhino).
  virtual double Altitude(void) const;

  // Returns true if auto-altitude is enabled.
  virtual bool AutoAltitude(void) const;

  // Returns true if the ground plane is set to shadow-only.
  virtual bool ShadowOnly(void) const;

  // Returns the instance id of the ground plane's material.
  virtual ON_UUID MaterialInstanceId(void) const;

  // Returns the texture offset of the ground plane in model units.
  virtual ON_2dVector TextureOffset(void) const;

  // Returns true if the texture offset x and y are locked together.
  virtual bool TextureOffsetLocked(void) const;

  // Returns the texture size of the ground plane in model units.
  virtual ON_2dVector TextureSize(void) const;

  // Returns true if the texture size x and y are locked together.
  virtual bool TextureSizeLocked(void) const;

  // Returns the texture rotation of the ground plane in degrees.
  virtual double TextureRotation(void) const;

  // Set the ground plane enabled state.
  virtual void SetEnabled(bool on);

  // Set if the ground plane backface is enabled.
  virtual void SetShowUnderside(bool on);

  // Set the ground plane's altitude.
  virtual void SetAltitude(double altitude);

  // Set if the ground plane is set to auto-altitude.
  virtual void SetAutoAltitude(bool on);

  // Set if the ground plane is set to shadow-only.
  virtual void SetShadowOnly(bool on);

  // Set the instance id of the ground plane's material.
  virtual void SetMaterialInstanceId(const ON_UUID& uuid);

  // Set the texture offset of the ground plane in model units.
  virtual void SetTextureOffset(const ON_2dVector& vec);

  // Set if the texture offset x and y are locked together.
  virtual void SetTextureOffsetLocked(bool locked);

  // Set the texture size of the ground plane in model units.
  virtual void SetTextureSize(const ON_2dVector& vec);

  // Set if the texture size x and y are locked together.
  virtual void SetTextureSizeLocked(bool locked);

  // Set the texture rotation of the ground plane in degrees.
  virtual void SetTextureRotation(double angle);

  // This method populates an ON_Material with default settings and returns true. This is designed
  // to be overridden by a subclass that can return a more interesting material.
  virtual bool PopulateMaterial(ON_Material& mat) const;

  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

  // For internal use only.
  virtual void OnInternalXmlChanged(const ON_GroundPlane*);

private: // For internal use only.
  friend class ON_3dmRenderSettingsPrivate;
  void SetXMLNode(ON_XMLNode& node) const;

private:
  class CImpl;
  CImpl* _impl;
};

#endif
