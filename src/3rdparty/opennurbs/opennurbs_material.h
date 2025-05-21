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

#if !defined(OPENNURBS_MATERIAL_INC_)
#define OPENNURBS_MATERIAL_INC_

class ON_PhysicallyBasedMaterial;

///////////////////////////////////////////////////////////////////////////////
//
// Class ON_Material
//
class ON_CLASS ON_Material : public ON_ModelComponent
{
  ON_OBJECT_DECLARE(ON_Material);

public:
  static const double MaxShine; // maximum value of shine exponent = 255.0

  static const ON_Material Unset;   // nil id


  static const ON_Material Default; // index = -1, persistent id

  // Default material for locked objects
  static const ON_Material DefaultLockedObject; // index = -2, persistent id

  /*
  Parameters:
    model_component_reference - [in]
    none_return_value - [in]
      value to return if ON_Material::Cast(model_component_ref.ModelComponent())
      is nullptr
  Returns:
    If ON_Material::Cast(model_component_ref.ModelComponent()) is not nullptr,
    that pointer is returned.  Otherwise, none_return_value is returned.
  */
  static const ON_Material* FromModelComponentRef(
    const class ON_ModelComponentReference& model_component_reference,
    const ON_Material* none_return_value
    );

  // compare everything except Index() value.
  static int Compare(
    const ON_Material& a,
    const ON_Material& b
    );

  // compare Id(), Name(), m_rdk_material_instance_id
  static int CompareNameAndIds(
    const ON_Material& a,
    const ON_Material& b
    );

  // Compare all settings (color, reflection, texture, plug-in id)
  // that affect the appearance.
  // Ignore Index(), Id(), Name(), m_rdk_material_instance_id.
  static int CompareAppearance(
    const ON_Material& a,
    const ON_Material& b
    );

  static int CompareColorAttributes(
    const ON_Material& a,
    const ON_Material& b
    );

  static int CompareReflectionAttributes(
    const ON_Material& a,
    const ON_Material& b
    );

  static int CompareTextureAttributes(
    const ON_Material& a,
    const ON_Material& b
  );

  static int CompareTextureAttributesAppearance(
    const ON_Material& a,
    const ON_Material& b
  );



  /*
  Parameters:
    fresnel_index_of_refraction - [in]
      ON_Material::Material::Default.m_fresnel_index_of_refraction
      is a good default
    N - [in]
      3d surface normal
    R - [in]
      3d reflection direction
  Returns:
    1.0:
      The input values were not valid or the calculation failed due to
      a divide by zero or some other numerical arithmetic failure.
    fresnel reflection coefficient
      1/2 * ((g-c)/(g+c))^2 * (1 + ( (c*(g+c) -1)/(c*(g+c) + 1) )^2)
      where
        c = N o (N-R); // c = 3d vector dot product of N and (N-R)
      and
        g = sqrt(fresnel_index_of_refraction*fresnel_index_of_refraction + c*c - 1.0).
  */
  static double FresnelReflectionCoefficient(
    double fresnel_index_of_refraction,
    const double N[3],
    const double R[3]
    );

public:
  ON_Material() ON_NOEXCEPT;
  ON_Material(const ON_Material& src);
  ~ON_Material() = default;
  ON_Material& operator=(const ON_Material& src) = default;

private:
  void Internal_CopyFrom(
    const ON_Material& src
    );

public:
  /////////////////////////////////////////////////////////////////
  // ON_Object overrides
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  void Dump(
    ON_TextLog& text_log
    ) const override;

  bool Write(
    ON_BinaryArchive& archive
    ) const override;

  bool Read(
    ON_BinaryArchive& archive
    ) override;

  ON::object_type ObjectType() const override;

  /////////////////////////////////////////////////////////////////
  // Interface

  ON_Color Ambient() const;
  ON_Color Diffuse() const;
  ON_Color Emission() const;
  ON_Color Specular() const;

  void SetAmbient(  ON_Color );
  void SetDiffuse(  ON_Color );
  void SetEmission( ON_Color );
  void SetSpecular( ON_Color );

  // Shine values are in range 0.0 to ON_Material::MaxShine
  double Shine() const;
  void SetShine( double );         // 0 to ON_Material::MaxShine

  // Transparency values are in range 0.0 = opaque to 1.0 = transparent
  double Transparency() const;
  void SetTransparency( double );  // 0.0 = opaque, 1.0 = transparent

  // Transparency values are in range 0.0 = opaque to 1.0 = transparent
  double Reflectivity() const;
  void SetReflectivity( double );  // 0.0 = opaque, 1.0 = transparent

  // ID of the last plug-in to modify this material
  ON_UUID MaterialPlugInId() const;
  void SetMaterialPlugInId(
    ON_UUID plugin_id
    );

public:
  /*
  Description:
    Get the RDK material id.
  Returns:
    The RDK material id for this material.
  Remarks:
    The RDK material id identifies a material definition managed by
    the RDK (rendering development kit).  Multiple materials in
    a Rhino or opennurbs model can reference the same RDK material.
  */
  ON_UUID RdkMaterialInstanceId() const;

  /*
  Description:
    Set this material's RDK material id.
  Parameters:
    rdk_material_id - [in]
      RDK material id value.
  Remarks:
    The RDK material id identifies a material definition managed by
    the RDK (rendering development kit).  Multiple materials in
    a Rhino or opennurbs model can reference the same RDK material.
    When setting this value, it is necessary to also set this material's
    plug-in id to ON_UniversalRenderEngineId. See SetMaterialPlugInId().
  */
  void SetRdkMaterialInstanceId(
    ON_UUID rdk_material_instance_id
    );

  bool RdkMaterialInstanceIdIsNotNil() const;
  bool RdkMaterialInstanceIdIsNil() const;

  /*
  Returns:
    True if the material can be shared.
  Remarks:
    If true, when an object using this material is copied,
    the copy references the same material.
  */
  bool Shareable() const;
  void SetShareable(
    bool bShareable
    );

  /*
  Returns:
    True if lighting is disabled.
  Remarks:
    True means render this object without
    applying any modulation based on lights.
    Basically, the diffuse, ambient, specular and
    emissive channels get combined additively, clamped,
    and then get treated as an emissive channel.
    Another way to think about it is when
    m_bDisableLighting is true, render the same way
    OpenGL does when ::glDisable( GL_LIGHTING ) is called.
  */
  bool DisableLighting() const;

  void SetDisableLighting(
    bool bDisableLighting
    );

  //If m_bUseDiffuseTextureAlphaForObjectTransparencyTexture is true, the alpha channel
  //of the texture in m_textures with m_type=bitmap_texture is used in addition to any
  //textures with m_type=transparency_texture.
  bool UseDiffuseTextureAlphaForObjectTransparencyTexture() const;
  void SetUseDiffuseTextureAlphaForObjectTransparencyTexture(
    bool bUseDiffuseTextureAlphaForObjectTransparencyTexture
    );

  //////////////////////////////////////////////////////////////
  //
  // Reflection and Refraction settings
  //

  // The bool m_bFresnelReflections enables fresnel scaling
  // of reflection contributions to the diffuse color.
  // True:
  //   The fresnel term is used to scale the reflection contribution
  //   before addition to the diffuse component.
  // False:
  //   The reflection contribution is simply added to the diffuse component.
  bool FresnelReflections() const;
  void SetFresnelReflections(
    bool bFresnelReflections
    );

  //Returns a color that can be used as a simple preview of the material in GUIs.  This is
  //the function that the layer manager uses to color the little material swatch, for example.
  ON_Color PreviewColor() const;

  //Call this function to determine if the material should be treated as Physically Based (ie - a PBR material)
  //If this function returns true, the call to PhysicallyBased will return a non-null pointer.
  //If the function returns false, use the legacy interface (Diffuse etc).  Conversion of a non-PBR material to PBR
  //is possible by calling ConvertToPhysicallyBased.
  bool IsPhysicallyBased(void) const;

  //Physically based material interface.  Use this interface to set and get PBR parameters
  //and to check if this material supports PBR.
  //Note - it is very important that the lifetime of the returned pointer is the same as the ON_Material
  //it was called on.  Once the material is deleted, this pointer is no longer valid.
  const std::shared_ptr<ON_PhysicallyBasedMaterial> PhysicallyBased(void) const;
  std::shared_ptr <ON_PhysicallyBasedMaterial> PhysicallyBased(void);

  //Convert a legacy material to a PBR material that is the best approximation of the original.
  //After calling this function, the material is guaranteed to return true to material.IsPhysicallyBased()
  void ToPhysicallyBased(void);

  //Internal use only
  static ON_UUID PhysicallyBasedUserdataId(void);

private:
  // The value of m_rdk_material_id identifies an RDK (rendering development kit)
  // material. Multiple materials in a Rhino model can refer to the same
  // RDK material id.  In V5 this value is stored in user data.  In V6 it is
  // saved in the m_rdk_material_id field.
  ON_UUID m_rdk_material_instance_id = ON_nil_uuid;

public:
  ON_Color m_ambient = ON_Color::Black;
  ON_Color m_diffuse = ON_Color::Gray126;
  ON_Color m_emission = ON_Color::Black;
  ON_Color m_specular = ON_Color::White;
  ON_Color m_reflection = ON_Color::White;
  ON_Color m_transparent = ON_Color::White;

  //The values all of the colors above do not support alpha values, and Rhino will not work correctly
  //if there is a value other than 0 in that fourth byte.  This function cleans this up.
  //https://mcneel.myjetbrains.com/youtrack/issue/RH-85216/ONMaterial-diffuse-color-is-ONColorUnsetColor
  void RemoveColorAlphaValues(void);

private:
  bool m_bShareable = false;

private:
  bool m_bDisableLighting = false;

private:
  bool m_bUseDiffuseTextureAlphaForObjectTransparencyTexture = false;

private:
  bool m_bFresnelReflections = false;

private:
  unsigned int m_reserved1 = 0;

public:
  double m_reflectivity = 0.0; // 0.0 = none, 1.0 = 100%
  double m_shine = 0.0;        // 0.0 = none to GetMaxShine()=maximum
  double m_transparency = 0.0; // 0.0 = opaque to 1.0 = transparent (1.0-alpha)

  /*
  m_reflection_glossiness:
    Default is 0.0.
    Values from 0.0 to 1.0 make sense.
    - 0.0 reflections are perfectly specular.
    - t > 0.0 permits reflection ray direction to vary
      from the specular direction by up to t*pi/2.
  */
  double m_reflection_glossiness = 0.0;

  /*
  m_refraction_glossiness:
    Default is 0.0.
    Values from 0.0 to 1.0 make sense.
    - 0.0 refractions are perfectly specular.
    - t > 0.0 permits refraction ray direction to vary
      from the specular direction by up to t*pi/2.
  */
  double m_refraction_glossiness = 0.0;

  /*
  m_index_of_refraction:
    Default is 1.0.
    Physically, the index of refraction is >= 1.0 and is
    the value (speed of light in vacuum)/(speed of light in material).
    Some rendering algorithms set m_index_of_refraction to zero or
    values < 1.0 to generate desirable effects.
  */
  double m_index_of_refraction = 1.0;

  /*
  m_fresnel_index_of_refraction:
    Default is 1.56.
    This is the value ON:Material::FresnelReflectionCoefficient() passes
    as the first parameter to ON_FresnelReflectionCoefficient().
    - Glass material types can be simulated with
      m_index_of_refraction ~ 1.56
      m_fresnel_index_of_refraction ~ 1.56
    - Thin glass can be simulated with
      m_fresnel_index_of_refraction = 1.56
      m_index_of_refraction = 0.0
    - Porcelain type materials can be simulated with
      m_fresnel_index_of_refraction = 1.56
      m_index_of_refraction = 1.0
      m_transparency = 0.0
  */
  double m_fresnel_index_of_refraction = 1.56;

  /*
  Parameters:
    N - [in]
      3d surface normal
    R - [in]
      3d reflection direction
  Returns:
    If m_bFresnelReflections is false, then 1.0 is returned.
    If m_bFresnelReflections is true, then the value of the fresnel
    reflection coefficient is returned. In typical rendering applications,
    the reflection term is multiplied by the fresnel reflection coefficient
    before it is added to the diffuse color.
    If any input is not valid or the calculation fails, then 1.0 is returned.
  Remarks:
    When m_bFresnelReflections is true, the calculation is performed by
    calling ON_FresnelReflectionCoefficient() with m_fresnel_index_of_refraction
    as the fresnel index of refraction.
  */
  double FresnelReflectionCoefficient(
    ON_3dVector N,
    ON_3dVector R
    ) const;

  /*
  Description:
    Searches for a texture with matching texture_id.
    If more than one texture matches, the first match
    is returned.
  Parameters:
    texture_id - [in]
  Returns:
    >=0 m_textures[] index of matching texture
    -1 if no match is found.
  */
  int FindTexture(
    ON_UUID texture_id
    ) const;

  /*
  Description:
    Searches for a texture with matching filename and type.
    If more than one texture matches, the first match
    is returned.
  Parameters:
    filename - [in]  If nullptr, then any filename matches.
    type - [in] If ON_Texture::no_texture_type, then
                any texture type matches.
    i0 - [in] If i0 is < 0, the search begins at
              m_textures[0], if i0 >= m_textures.Count(),
              -1 is returned, otherwise, the search begins
              at m_textures[i0+1].
  Example:
    Iterate through all the the bitmap textures on
    a material.

          ON_Material& mat = ...;
          int ti = -1;
          int bitmap_texture_count = 0;
          for(;;)
          {
            ti = mat.FindTexture(
                        nullptr,
                        ON_Texture::TYPE::bitmap_texture,
                        ti );

            if ( ti < 0 )
            {
              // no more bitmap textures
              break;
            }

            // we have a bitmap texture
            bitmap_texture_count++;
            const ON_Texture& bitmap_texture = mat.m_textures[ti];
            ...
          }

  Returns:
    >=0 m_textures[] index of matching texture
    -1 if no match is found.
  */
  int FindTexture(
    const wchar_t* filename,
    ON_Texture::TYPE type,
    int i0 = -1
    ) const;

  /*
  Description:
    If there is already a texture with the same file name and
    type, then that texture is modified, otherwise a new texture
    is added.  If tx has user data, the user data is copied
    to the m_textures[] element.
  Parameters:
    tx - [in]
  Returns:
    Index of the added texture in the m_textures[] array.
  Remarks:
    This is intended to be a quick and simple way to add
    textures to the material.  If you need to do something
    different, then just work on the m_textures[] array.
  */
  int AddTexture(
    const ON_Texture& tx
    );

  /*
  Description:
    If there is a texture with a matching type, that texture's
    filename is modified, otherwise a new texture is added.
  Parameters:
    filename - [in] new filename
    type - [in]
  Returns:
    Index of the added texture in the m_textures[] array.
  Remarks:
    This is intended to be a quick and simple way to add
    textures to the material.  If you need to do something
    different, then just work on the m_textures[] array.
  */
  int AddTexture(
    const wchar_t* filename,
    ON_Texture::TYPE type
    );

  /*
  Description:
    Deletes all textures with matching filenames and types.
  Parameters:
    filename - [in]  If nullptr, then any filename matches.
    type - [in] If ON_Texture::no_texture_type, then
                any texture type matches.
  Returns:
    Number of textures deleted.
  */
  int DeleteTexture(
    const wchar_t* filename,
    ON_Texture::TYPE type
    );

  ON_ObjectArray<ON_Texture> m_textures;

  /*
  Description:
    The m_material_channel[] array is used to provide per face rendering material support for ON_SubD and ON_Brep objects.
    ON_Mesh objects to not support per face render materials.
    The application specifies a base ON_Material for rendering the subd or brep and a way to find materials from ON_UUID values.
    ON_Material.Id() returns the id for any given material.

    ON_BrepFace::MaterialChannelIndex() and ON_SubDFace::MaterialChannelIndex()
    specify a material channel index. If this value is 0, then the base
    material is used to render the face. Otherwise the material with
    id = base.MaterialChannelIdFromIndex( face.MaterialChannelIndex() )
    is used to render the face. 
  */
  ON_SimpleArray<ON_UuidIndex> m_material_channel;

  enum : int
  {
    ///<summary>
    /// Material channel index values stored in the ON_UuidIndex.m_i field of elements in the m_material_channel[] array
    /// must be between 0 and ON_Material::MaximumMaterialChannelIndex, inclusive.
    ///</summary>
    MaximumMaterialChannelIndex = 65535
  };

  /*
  Parameters:
    material_channel_index - [in]      
  Returns:
    If material_channel_index > 0, the m_id ON_UUID value of the first element in the 
    m_material_channel[] array with material_channel_index = ON_Uuid_index.m_i is returned. 
    This id identifies an ON_Material.
    Otherwise ON_nil_uuid is returned.
  */
  const ON_UUID MaterialChannelIdFromIndex(
    int material_channel_index
  ) const;

  /*
  Parameters:
    material_channel_id - [in]
  Returns:
    If material_channel_id is not nil, the m_i index value of the first element in the
    m_material_channel[] array with material_channel_id = ON_Uuid_index.m_id is returned.
    Otherwise 0 is returned.
  */
  int MaterialChannelIndexFromId(
    ON_UUID material_channel_id
  ) const;

  /*
  Parameters:
    material_channel_id - [in]
    bAddIdIfNotPresent - [in]
  Returns:
    If material_channel_id is not nil, the m_i index value of the first element in the
    m_material_channel[] array with material_channel_id = ON_Uuid_index.m_id is returned.
    If material_channel_id is not nil an no element of the m_material_channel[] array 
    has a matching id, a new element is added with a unique channel index > 0 and that 
    index is returned.
    Otherwise 0 is returned.
  */
  int MaterialChannelIndexFromId(
    ON_UUID material_channel_id,
    bool bAddIdIfNotPresent
  );

private:
  ON_UUID m_plugin_id = ON_nil_uuid;

private:
  bool Internal_ReadV3( ON_BinaryArchive& archive, int minor_version );
  bool Internal_WriteV3( ON_BinaryArchive& archive ) const;
  bool Internal_ReadV5( ON_BinaryArchive& archive );
  bool Internal_WriteV5( ON_BinaryArchive& archive ) const;
};

ON_DECL
bool operator==(const ON_Material&, const ON_Material&);

ON_DECL
bool operator!=(const ON_Material&, const ON_Material&);

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_Material*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<const ON_Material*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_ObjectArray<ON_Material>;

// NO! // ON_DLL_TEMPLATE template class ON_CLASS ON_ClassArray<ON_Material>;
//  It is a serious error to have an ON_ClassArray<ON_Material> and crashes
//  will occur when user data back pointers are not updated.
#endif


///////////////////////////////////////////////////////////////////////////////
//
// Class ON_PhysicallyBasedMaterial
//
class ON_CLASS ON_PhysicallyBasedMaterial
{
public:
  ON_PhysicallyBasedMaterial(const ON_Material& src);
  ON_PhysicallyBasedMaterial(const ON_PhysicallyBasedMaterial& src);
  virtual ~ON_PhysicallyBasedMaterial();

  virtual bool IsValid(class ON_TextLog* text_log = nullptr) const;

  /////////////////////////////////////////////////////////////////
  // Interface
public:
  //Reflectance model to use.  Default is GGX.  Renderers do not need to support a specific
  //model, but certain material definitions may specify in the hope that a renderer will support.
  //GGX support is built into Rhino (Cycles, display)
  enum class BRDFs : int
  {
    GGX = 0,          //http://www.cs.cornell.edu/~srm/publications/EGSR07-btdf.pdf
    Ward = 1,         //https://pdfs.semanticscholar.org/330e/59117d7da6c794750730a15f9a178391b9fe.pdf
  };

  virtual BRDFs BRDF(void) const;
  virtual void SetBRDF(const BRDFs&);

  virtual ON_4fColor BaseColor(void) const;
  virtual void SetBaseColor(const ON_4fColor&);

  //Controls diffuse shape using a subsurface approximation.  If full subsurface transport is
  //implemented, acts as a mix between diffuse and SSS
  virtual double Subsurface(void) const;
  virtual void SetSubsurface(double);

  //Color for full subsurface transport if implemented
  virtual ON_4fColor SubsurfaceScatteringColor(void) const;
  virtual void SetSubsurfaceScatteringColor(const ON_4fColor&);

  //Radius for full subsurface transport if implemented
  virtual double SubsurfaceScatteringRadius(void) const;
  virtual void SetSubsurfaceScatteringRadius(double);

  //The metallic-ness (0 = dielectric, 1 = metallic). This is a linear blend between two
  //different models.The metallic model has no diffuse component and also has a tinted incident
  //specular, equal to the base color
  virtual double Metallic(void) const;
  virtual void SetMetallic(double);

  //Incident specular amount.  Linked to Ior property below.
  //specular=((ior−1)/(ior+1))2/0.08
  virtual double Specular(void) const;
  virtual void SetSpecular(double);

  //Reflective Ior - see specular amount above.  Linked to Specular property
  virtual double ReflectiveIOR(void) const;
  virtual void SetReflectiveIOR(double);

  //A concession for artistic control that tints incident specular towards the base color.
  //Grazing specular is still achromatic.
  //Tints the facing specular reflection using the base color, while glancing reflection remains white.
  //Normal dielectrics have colorless reflection, so this parameter is not technically physically correct and is provided for faking the appearance of materials with complex surface structure.
  virtual double SpecularTint(void) const;
  virtual void SetSpecularTint(double);

  //Surface roughness, controls both diffuse and specular response
  virtual double Roughness(void) const;
  virtual void SetRoughness(double);

  //Degree of anisotropy. This controls the aspect ratio of the specular highlight. (0 = isotropic, 1 = maximally anisotropic)
  virtual double Anisotropic(void) const;
  virtual void SetAnisotropic(double);

  //Rotates the direction of anisotropy, with 1.0 going full circle.
  virtual double AnisotropicRotation(void) const;
  virtual void SetAnisotropicRotation(double);

  //An additional grazing component, primarily intended for cloth.
  //Amount of soft velvet like reflection near edges, for simulating materials such as cloth.
  virtual double Sheen(void) const;
  virtual void SetSheen(double);

  //Amount to tint sheen towards base color
  virtual double SheenTint(void) const;
  virtual void SetSheenTint(double);

  //A second, special-purpose specular lobe - Extra white specular layer on top of others. This is useful for materials like car paint and the like.
  virtual double Clearcoat(void) const;
  virtual void SetClearcoat(double);

  //Controls clearcoat glossiness (0 = a “satin” appearance, 1 = a “gloss” appearance)
  virtual double ClearcoatRoughness(void) const;
  virtual void SetClearcoatRoughness(double);

  //Index of refraction for transmission.
  virtual double OpacityIOR(void) const;
  virtual void SetOpacityIOR(double);

  //Mix between fully opaque surface at zero and fully glass like transmission at one.
  virtual double Opacity(void) const;
  virtual void SetOpacity(double);

  //Controls roughness used for transmitted light.
  virtual double OpacityRoughness(void) const;
  virtual void SetOpacityRoughness(double);

  //Controls emission - uses base color.
  virtual ON_4fColor Emission(void) const;
  virtual void SetEmission(ON_4fColor);

  //Controls Alpha transparency - 1.0 is fully opaque, 0.0 is non-visible.  Use opacity for refraction - this overrides all other shading.
  /*virtual*/ double Alpha(void) const;
  /*virtual*/ void SetAlpha(double);

  //Texture access functions - exactly the same as ON_Material.  Provided for ease of use.
  virtual int FindTexture(const wchar_t* filename, ON_Texture::TYPE type, int i0 = -1) const;
  virtual int AddTexture(const ON_Texture& tx);
  virtual int AddTexture( const wchar_t* filename, ON_Texture::TYPE type);
  virtual int DeleteTexture(const wchar_t* filename, ON_Texture::TYPE type);

  //Access the referenced ON_Material.
  virtual ON_Material& Material(void);
  virtual const ON_Material& Material(void) const;

  //Call this function to set the ON_Material up to represent the PBR material as well as possible.
  virtual void SynchronizeLegacyMaterial(void);

  //Expert function to remove all PBR data from a material
  virtual void ToLegacy(void);

  //These function just route through to ON_Material - PBR materials need to support the same functionality.
  //
  //If UseBaseColorTextureAlphaForObjectAlphaTransparencyTexture returns true, the alpha channel
  //of the texture in m_textures with m_type=pbr_base_color is used in addition to any
  //textures with m_type=pbr_alpha_texture.
  bool UseBaseColorTextureAlphaForObjectAlphaTransparencyTexture() const;
  void SetUseBaseColorTextureAlphaForObjectAlphaTransparencyTexture(bool);

public:
    class ON_CLASS ParametersNames
    {
    public:
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString BaseColor(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString BRDF(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString Subsurface(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString SubsurfaceScatteringColor(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString SubsurfaceScatteringRadius(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString Specular(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString SpecularTint(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString Metallic(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString Roughness(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString Anisotropic(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString AnisotropicRotation(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString Sheen(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString SheenTint(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString Clearcoat(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString ClearcoatRoughness(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString ClearcoatBump(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString OpacityIor(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString Opacity(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString OpacityRoughness(void);
      ON_DEPRECATED_MSG("Use CRhRdkMaterial::PhysicallyBased::ParameterNames") static ON_wString Emission(void);
  };

private:
  class Impl;
  const Impl& Implementation(void) const;
  Impl& Implementation(void);

  unsigned char _impl[64];

  //Ban copying - usage should be material.PhysicallyBased().Function()
  ON_PhysicallyBasedMaterial& operator=(const ON_Material& src) = delete;
  ON_PhysicallyBasedMaterial& operator=(const ON_PhysicallyBasedMaterial& src) = delete;
  friend ON_Material;
  friend bool ON_PhysicallyBasedMaterial_Supported(const ON_PhysicallyBasedMaterial& material);
};

#endif
