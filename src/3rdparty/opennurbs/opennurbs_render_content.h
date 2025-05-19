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

#if !defined(ON_RENDER_CONTENT_INC_)
#define ON_RENDER_CONTENT_INC_

// ON_Environment

class ON_CLASS ON_Environment : public ON_Object
{
  ON_OBJECT_DECLARE(ON_Environment);

public:
  ON_Environment();
  ON_Environment(const ON_Environment& src);
  virtual ~ON_Environment();

  virtual const ON_Environment& operator = (const ON_Environment& src);

  virtual bool operator == (const ON_Environment& src) const;
  virtual bool operator != (const ON_Environment& src) const;

  enum class BackgroundProjections : unsigned int
  {
    Planar = 0,
    Spherical = 1, // Equirectangular projection.
    Emap = 2,      // Mirror ball.
    Box = 3,
    Automatic = 4,
    LightProbe = 5,
    CubeMap = 6,
    VerticalCrossCubeMap = 7,
    HorizontalCrossCubeMap = 8,
    Hemispherical = 9,
  };

  virtual ON_Color BackgroundColor(void) const;
  virtual void SetBackgroundColor(const ON_Color& col);

  virtual const ON_Texture& BackgroundImage(void) const;
  virtual void SetBackgroundImage(const ON_Texture& tex);

  virtual BackgroundProjections BackgroundProjection(void) const;
  virtual void SetBackgroundProjection(BackgroundProjections proj);

  static BackgroundProjections ProjectionFromString(const wchar_t* proj);
  static const wchar_t* StringFromProjection(BackgroundProjections proj);

protected:
  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* wszFunc, void* pvData);

private:
  class CImpl;
  CImpl* m_impl;
};

class ON_CLASS ON_RenderContent : public ON_ModelComponent
{
  ON_OBJECT_DECLARE(ON_RenderContent);

public:
  ON_RenderContent(const wchar_t* kind);
  ON_RenderContent(const ON_RenderContent&);
  virtual ~ON_RenderContent();

  virtual const ON_RenderContent& operator = (const ON_RenderContent&);

  // Returns: The internal name of the content type.
  virtual ON_wString TypeName(void) const;

  // Set the content's type name.
  virtual void SetTypeName(const wchar_t* name);

  // Returns: The unique id of the content type.
  virtual ON_UUID TypeId(void) const;

  // Set the content's type id.
  virtual void SetTypeId(const ON_UUID& uuid);

  // Returns: The content's render-engine id.
  virtual ON_UUID RenderEngineId(void) const;

  // Set the content's render-engine id.
  virtual void SetRenderEngineId(const ON_UUID& uuid);

  // Returns: The content's plug-in id.
  virtual ON_UUID PlugInId(void) const;

  // Set the content's plug-in id.
  virtual void SetPlugInId(const ON_UUID& uuid);

  // Returns: The content's notes.
  virtual ON_wString Notes(void) const;

  // Sets the content's notes.
  virtual void SetNotes(const wchar_t* notes);

  // Returns: The content's tags.
  virtual ON_wString Tags(void) const;

  // Sets the content's tags.
  virtual void SetTags(const wchar_t* tags);

  // Returns: The content's group id.
  virtual ON_UUID GroupId(void) const;

  // Sets the content's group id.
  virtual void SetGroupId(const ON_UUID& group);

  // Returns: True if the content is hidden.
  virtual bool Hidden(void) const;

  // Sets whether or not the content is hidden.
  virtual void SetHidden(bool hidden);

  // Returns: True if the content is a reference content.
  virtual bool Reference(void) const;

  // Sets whether or not the content is a reference content.
  virtual void SetReference(bool ref);

  // Returns: True if the content is automatically deleted when not in use.
  virtual bool AutoDelete(void) const;

  // Sets whether or not the content is automatically deleted when not in use.
  virtual void SetAutoDelete(bool autodel);

  // Gets a variant giving the type and value of the parameter, if found.
  // If the parameter is not found, the function returns a null variant.
  virtual ON_XMLVariant GetParameter(const wchar_t* name) const;

  // Sets the value of a named parameter.
  // Returns: True if successful, else false.
  virtual bool SetParameter(const wchar_t* name, const ON_XMLVariant& value);

  class ON_CLASS ChildIterator
  {
  public:
    ChildIterator(const ON_RenderContent* parent);
    virtual ~ChildIterator();

    virtual ON_RenderContent* GetNextChild(void);

  protected:
    // Emergency virtual function for future expansion.
    virtual void* EVF(const wchar_t* func, void* data);

  private:
    class ON_RenderContentChildIteratorPrivate* _private;
  };

  // Returns: An iterator for iterating over the content's children.
  virtual ChildIterator GetChildIterator(void) const;

  // Returns: The parent content or null if this is the top level object.
  virtual       ON_RenderContent* Parent(void);
  virtual const ON_RenderContent* Parent(void) const;

  // Returns: The first child of this content or null if none.
  virtual       ON_RenderContent* FirstChild(void);
  virtual const ON_RenderContent* FirstChild(void) const;

  // Returns: The first sibling of this content or null if none.
  virtual       ON_RenderContent* NextSibling(void);
  virtual const ON_RenderContent* NextSibling(void) const;

  // Returns: The top level parent of this content.
  virtual       ON_RenderContent& TopLevel(void);
  virtual const ON_RenderContent& TopLevel(void) const;

  // Returns: True if this is a top-level content (i.e., has no parent; is not a child).
  virtual bool IsTopLevel(void) const;

  // Returns: True if this is a child content (i.e., has a parent; is not top-level).
  virtual bool IsChild(void) const;

  // Sets another content as a child of this content.
  // Param child is the content to set as a child of this content. This content is copied and the
  // copy is attached to the model. If the child is already attached to a model the function will fail.
  // If the child is already a child of this or another content, the function will fail.
  // Param childSlotName is the child slot name that will be assigned to this child.
  // The child slot name cannot be an empty string. If it is, the function will fail.
  // Returns: True if successful, else false.
  virtual bool SetChild(const ON_RenderContent& child, const wchar_t* child_slot_name);

  // Returns: The content's child-slot name.
  virtual ON_wString ChildSlotName(void) const;

  // Sets the content's child-slot name.
  virtual void SetChildSlotName(const wchar_t* child_slot_name);

  // Returns true if the child slot with the specified child slot name is turned on, else false.
  // Also returns false if there is no child with the specified child slot name.
  virtual bool ChildSlotOn(const wchar_t* child_slot_name) const;

  // Turns the child slot with the specified child slot name on or off.
  // Returns: True if successful, else false.
  virtual bool SetChildSlotOn(bool on, const wchar_t* child_slot_name);

  // Returns the blend amount of the texture with the specified child slot name.
  // The returned value is typically in the range 0..100 but it can be any positive or negative value.
  // If there is no child with the specified child slot name, the method returns 'default_value'.
  virtual double ChildSlotAmount(const wchar_t* child_slot_name, double default_value=ON_UNSET_VALUE) const;

  // Sets the blend amount of the texture with the specified child slot name.
  // Param amount is typically in the range 0..100 but it can be any positive or negative value.
  // Returns: True if successful, else false.
  virtual bool SetChildSlotAmount(double amount, const wchar_t* child_slot_name);

  // Deletes any existing child with the specified child slot name.
  // Returns: True if successful, else false.
  virtual bool DeleteChild(const wchar_t* child_slot_name);

  // Returns: The child with the specified child slot name, or null if no such child exists.
  virtual       ON_RenderContent* FindChild(const wchar_t* child_slot_name);
  virtual const ON_RenderContent* FindChild(const wchar_t* child_slot_name) const;

  // Get the render content's state as an XML string.
  virtual ON_wString XML(bool recursive) const;

  // Set the render content's state from an XML string.
  virtual bool SetXML(const wchar_t* xml);

  // Returns the XML node that stores the state of this render content. Note that this does not include
  // any children of the render content. An ON_RenderContent only stores its own XML.
  virtual const ON_XMLNode& XMLNode(void) const;

  // Returns the kind of render content as a string.
  virtual ON_wString Kind(void) const;

  virtual ON_RenderContent* NewRenderContent(void) const = 0;

  // If ON_RenderContent::Cast(ref.ModelComponent()) is not null,
  // that pointer is returned. Otherwise, none_return_value is returned.
  static const ON_RenderContent* FromModelComponentRef(const ON_ModelComponentReference& ref,
                                                       const ON_RenderContent* none_return_value);

protected:
  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

protected:
  class ON_RenderContentPrivate* _private;
  friend class ON_RenderContentPrivate;
  friend class ON_RenderTexture;

private:
  ON__UINT8 _PRIVATE[360+64];
};

class ON_CLASS ON_RenderMaterial : public ON_RenderContent
{
  ON_OBJECT_DECLARE(ON_RenderMaterial);

public:
  ON_RenderMaterial();
  ON_RenderMaterial(const ON_RenderMaterial& m);
  virtual ~ON_RenderMaterial();

  virtual const ON_RenderContent&  operator = (const ON_RenderContent&) override;
  virtual const ON_RenderMaterial& operator = (const ON_RenderMaterial&);

  virtual ON_Material ToOnMaterial(void) const;
  virtual ON_RenderContent* NewRenderContent(void) const override;
};

class ON_CLASS ON_RenderEnvironment : public ON_RenderContent
{
  ON_OBJECT_DECLARE(ON_RenderEnvironment);

public:
  ON_RenderEnvironment();
  ON_RenderEnvironment(const ON_RenderEnvironment& e);
  virtual ~ON_RenderEnvironment();

  virtual const ON_RenderContent& operator = (const ON_RenderContent&) override;
  virtual const ON_RenderEnvironment& operator = (const ON_RenderEnvironment&);

  virtual ON_Environment ToOnEnvironment(void) const;
  virtual ON_RenderContent* NewRenderContent(void) const override;
};

class ON_CLASS ON_RenderTexture : public ON_RenderContent
{
  ON_OBJECT_DECLARE(ON_RenderTexture);

public:
  ON_RenderTexture();
  ON_RenderTexture(const ON_RenderTexture& t);
  virtual ~ON_RenderTexture();

  virtual const ON_RenderContent& operator = (const ON_RenderContent&) override;
  virtual const ON_RenderTexture& operator = (const ON_RenderTexture&);

  // Get an ON_Texture from this render texture.
  virtual ON_Texture ToOnTexture(void) const;

  // If the texture has a file name, returns that file name. Otherwise returns an empty string.
  virtual ON_wString Filename(void) const;

  // Set the texture's file name (if possible). If the texture does not have a file name (e.g., a
  // procedural texture), the method returns false.
  virtual bool SetFilename(const wchar_t*);

  virtual ON_RenderContent* NewRenderContent(void) const override;
};

// Universal render engine id. Set as ON_Material plug-in id when using ON_RenderContentType_*
// ids in ON_Material::SetRdkMaterialInstanceId().
extern ON_DECL ON_UUID ON_UniversalRenderEngineId;

// Render materials.
extern ON_DECL ON_UUID ON_RenderContentType_BlendMaterial;
extern ON_DECL ON_UUID ON_RenderContentType_BlendMaterial_V8;
extern ON_DECL ON_UUID ON_RenderContentType_CompositeMaterial;
extern ON_DECL ON_UUID ON_RenderContentType_CustomMaterial;
extern ON_DECL ON_UUID ON_RenderContentType_DefaultMaterial;
extern ON_DECL ON_UUID ON_RenderContentType_DisplayAttributeMaterial;
extern ON_DECL ON_UUID ON_RenderContentType_DoubleSidedMaterial;
extern ON_DECL ON_UUID ON_RenderContentType_EmissionMaterial;
extern ON_DECL ON_UUID ON_RenderContentType_GemMaterial;
extern ON_DECL ON_UUID ON_RenderContentType_GlassMaterial;
extern ON_DECL ON_UUID ON_RenderContentType_MetalMaterial;
extern ON_DECL ON_UUID ON_RenderContentType_PaintMaterial;
extern ON_DECL ON_UUID ON_RenderContentType_PhysicallyBasedMaterial;
extern ON_DECL ON_UUID ON_RenderContentType_PictureMaterial;
extern ON_DECL ON_UUID ON_RenderContentType_PlasterMaterial;
extern ON_DECL ON_UUID ON_RenderContentType_PlasticMaterial;

// Display material used to support front and back materials for realtime rendering in the viewport.
extern ON_DECL ON_UUID ON_RenderContentType_RealtimeDisplayMaterial;

// Render environments.
extern ON_DECL ON_UUID ON_RenderContentType_BasicEnvironment;
extern ON_DECL ON_UUID ON_RenderContentType_DefaultEnvironment;

// Render textures.
extern ON_DECL ON_UUID ON_RenderContentType_2DCheckerTexture;
extern ON_DECL ON_UUID ON_RenderContentType_3DCheckerTexture;
extern ON_DECL ON_UUID ON_RenderContentType_AddTexture;
extern ON_DECL ON_UUID ON_RenderContentType_AdvancedDotTexture;
extern ON_DECL ON_UUID ON_RenderContentType_BitmapTexture;
extern ON_DECL ON_UUID ON_RenderContentType_BlendTexture;
extern ON_DECL ON_UUID ON_RenderContentType_CubeMapTexture;
extern ON_DECL ON_UUID ON_RenderContentType_ExposureTexture;
extern ON_DECL ON_UUID ON_RenderContentType_FBmTexture;
extern ON_DECL ON_UUID ON_RenderContentType_GradientTexture;
extern ON_DECL ON_UUID ON_RenderContentType_GraniteTexture;
extern ON_DECL ON_UUID ON_RenderContentType_GridTexture;
extern ON_DECL ON_UUID ON_RenderContentType_HDRTexture;
extern ON_DECL ON_UUID ON_RenderContentType_MarbleTexture;
extern ON_DECL ON_UUID ON_RenderContentType_MaskTexture;
extern ON_DECL ON_UUID ON_RenderContentType_MultiplyTexture;
extern ON_DECL ON_UUID ON_RenderContentType_NoiseTexture;
extern ON_DECL ON_UUID ON_RenderContentType_PerlinMarbleTexture;
extern ON_DECL ON_UUID ON_RenderContentType_PerturbingTexture;
extern ON_DECL ON_UUID ON_RenderContentType_PhysicalSkyTexture;
extern ON_DECL ON_UUID ON_RenderContentType_ProjectionChangerTexture;
extern ON_DECL ON_UUID ON_RenderContentType_ResampleTexture;
extern ON_DECL ON_UUID ON_RenderContentType_SimpleBitmapTexture;
extern ON_DECL ON_UUID ON_RenderContentType_SingleColorTexture;
extern ON_DECL ON_UUID ON_RenderContentType_StuccoTexture;
extern ON_DECL ON_UUID ON_RenderContentType_TextureAdjustmentTexture;
extern ON_DECL ON_UUID ON_RenderContentType_TileTexture;
extern ON_DECL ON_UUID ON_RenderContentType_TurbulenceTexture;
extern ON_DECL ON_UUID ON_RenderContentType_WavesTexture;
extern ON_DECL ON_UUID ON_RenderContentType_WoodTexture;

// Simple bump textures.
extern ON_DECL ON_UUID ON_RenderContentType_CrossHatchBumpTexture;
extern ON_DECL ON_UUID ON_RenderContentType_DotBumpTexture;
extern ON_DECL ON_UUID ON_RenderContentType_GritBumpTexture;
extern ON_DECL ON_UUID ON_RenderContentType_HatchBumpTexture;
extern ON_DECL ON_UUID ON_RenderContentType_LeatherBumpTexture;
extern ON_DECL ON_UUID ON_RenderContentType_SpeckleBumpTexture;
extern ON_DECL ON_UUID ON_RenderContentType_WoodBumpTexture;

#endif
