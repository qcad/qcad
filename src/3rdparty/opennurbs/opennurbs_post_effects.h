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

#if !defined(ON_POST_EFFECTS_INC_)
#define ON_POST_EFFECTS_INC_

// Class ON_PostEffectParams represents a collection of arbitrary post effect parameters.
class ON_CLASS ON_PostEffectParams
{
public:
  ON_PostEffectParams();
  ON_PostEffectParams(const ON_XMLNode&);
  ON_PostEffectParams(const ON_PostEffectParams&);
  virtual ~ON_PostEffectParams();

  const ON_PostEffectParams& operator = (const ON_PostEffectParams&);

  bool operator == (const ON_PostEffectParams&) = delete;
  bool operator != (const ON_PostEffectParams&) = delete;

  // Get a parameter from the collection by name.
  virtual bool GetParam(const wchar_t* name, ON_XMLVariant& value_out) const;

  // Set a parameter to the collection by name.
  virtual bool SetParam(const wchar_t* name, const ON_XMLVariant& value);

  // Get the parameter collection as an ON_XMLParameters object.
  virtual const ON_XMLParameters& AsXMLParameters(void) const;

  // Get a data CRC of the collection.
  virtual ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;

  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

private:
  class CImpl;
  CImpl* _impl;
};

// Class ON_PostEffect represents a single post effect.
class ON_CLASS ON_PostEffect
{
public:
  enum class Types : unsigned int
  {
    Unset,
    Early,       // Early post effects operate on HDR (float) image data.
    ToneMapping, // Tone mapping post effects convert HDR image data to LDR (8-bit) image data.
    Late         // Late post effects operate on LDR image data.
  };

  ON_PostEffect() = delete; // You can't create a post effect with no name, id or type.
  ON_PostEffect(class ON_PostEffects& peps, Types type, const ON_UUID& id, const wchar_t* local_name);
  ON_PostEffect(const ON_PostEffect& pep);
  virtual ~ON_PostEffect();

  virtual const ON_PostEffect& operator = (const ON_PostEffect& pep);

  virtual bool operator == (const ON_PostEffect& pep) const;
  virtual bool operator != (const ON_PostEffect& pep) const;

public: // Read-only properties.

  // Returns the type of this post effect. 
  virtual Types Type(void) const;

  // Returns the unique id of this post effect. 
  virtual ON_UUID Id(void) const;

  // Returns the localized name of this post effect.
  virtual ON_wString LocalName(void) const;

public: // Read/write properties.

  // Returns true if the post effect is 'on'. Only early and late post effects can be on.
  // This corresponds to the check box next to the post effect's name in the user interface.
  virtual bool On(void) const;

  // Set if the post effect is 'on'. Only early and late post effects can be on.
  // This corresponds to the check box next to the post effect's name in the user interface.
  virtual void SetOn(bool on);

  // Returns true if the post effect is shown. Only early and late post effects can be shown.
  // This corresponds to the post effect appearing in the list in the user interface.
  virtual bool Shown(void) const;

  // Set if the post effect is shown. Only early and late post effects can be shown.
  // This corresponds to the post effect appearing in the list in the user interface.
  virtual void SetShown(bool shown);

public: // Post effects can have any number of arbitrary parameters.

  // Get a parameter by its name.
  // Param 'param_name' is the name of the parameter to set.
  // Returns the value if successful or null if the parameter was not found.
  virtual ON_XMLVariant GetParameter(const wchar_t* param_name) const;

  // Set a parameter by its name.
  // Param 'param_name' is the name of the parameter to set.
  // Param 'param_value' specifies the type and value to set.
  // Returns true if successful or false if the parameter could not be set.
  virtual bool SetParameter(const wchar_t* param_name, const ON_XMLVariant& param_value);

  // Get all the parameters in one go.
  // Returns true if successful or false if the parameters could not be retrieved.
  virtual bool GetAllParameters(ON_PostEffectParams& params) const;

  // Set all the parameters in one go.
  // Returns true if successful or false if the parameters could not be set.
  virtual bool SetAllParameters(const ON_PostEffectParams& params);

public: // Other.

  // Returns the XML node that stores the state of this post effect.
  virtual       ON_XMLNode& XMLNode(void);
  virtual const ON_XMLNode& XMLNode(void) const;

  // Returns a CRC of the state of this post effect.
  virtual ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;

public:
  class CImpl;
  CImpl* _impl;
};

// Class ON_PostEffects represents a collection of post effects.
class ON_CLASS ON_PostEffects
{
public:
  ON_PostEffects();
  ON_PostEffects(ON_XMLNode& model_node);
  ON_PostEffects(const ON_PostEffects& peps);
  virtual ~ON_PostEffects();

  virtual ON_PostEffects& operator = (const ON_PostEffects& peps);

  virtual bool operator == (const ON_PostEffects& peps) const;
  virtual bool operator != (const ON_PostEffects& peps) const;

  // Find a post effect from its id.
  virtual       ON_PostEffect* PostEffectFromId(const ON_UUID& id);
  virtual const ON_PostEffect* PostEffectFromId(const ON_UUID& id) const;

  // Get an array of post effects of a certain type.
  virtual void GetPostEffects(ON_PostEffect::Types type, ON_SimpleArray<      ON_PostEffect*>& a);
  virtual void GetPostEffects(ON_PostEffect::Types type, ON_SimpleArray<const ON_PostEffect*>& a) const;

  // Get an array of all post effects.
  virtual void GetPostEffects(ON_SimpleArray<      ON_PostEffect*>& a);
  virtual void GetPostEffects(ON_SimpleArray<const ON_PostEffect*>& a) const;

  // Add a new post effect to the collection.
  virtual bool AddPostEffect(ON_PostEffect::Types type, const ON_UUID& id,
                             const wchar_t* local_name, const ON_PostEffectParams& params,
                             bool is_listable, bool listable_on, bool listable_shown);

  // Move a post effect before another post effect in the list.
  // Param 'id_move' is the id of the post effect to move.
  // Param 'id_before' is the id of a post effect before which the post effect should be moved.
  // If this is nil, the post effect is moved to the end of the list.
  // If the post effect identified by 'id_before' is not found, the method will fail.
  // Returns true if successful, else false.
  virtual bool MovePostEffectBefore(const ON_UUID& id_move, const ON_UUID& id_before);

  // Gets the selected post effect for a certain type into 'id_out'.
  // Returns true if successful or false if the selection information could not be found.
  virtual bool GetSelectedPostEffect(ON_PostEffect::Types type, ON_UUID& id_out) const;

  // Sets the selected post effect for a certain type.
  virtual void SetSelectedPostEffect(ON_PostEffect::Types type, const ON_UUID& id);

  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

public: // Expert access to the post effect XML.

  // Returns the XML node that stores the state of all the post effects (ON_RDK_POST_EFFECTS).
  const ON_XMLNode& PostEffectsNode(void) const;

  // Sets the XML node that stores the state of all the post effects (ON_RDK_POST_EFFECTS).
  void SetPostEffectsNode(const ON_XMLNode&);

  // For internal use only.
  virtual void OnInternalXmlChanged(const ON_PostEffects*);

private: // For internal use only.
  friend class ON_PostEffect;
  ON_XMLNode& WritablePostEffectsNode(void);

public:
  class CImpl;
  CImpl* _impl;
};

// Helper function to get the type of a post effect as a string.
ON_DECL const wchar_t* ON_PostEffectTypeString(ON_PostEffect::Types type);

#endif
