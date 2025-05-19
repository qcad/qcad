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

#if !defined(ON_XML_INC_)
#define ON_XML_INC_

typedef bool (*ON_XMLRecurseChildrenCallback)(class ON_XMLNode*, void*);

#define ON_XML_SLASH  L"/"

// This is the structure of the RDK document XML.

#define ON_RDK_DOCUMENT                             L"render-content-manager-document"

  #define ON_RDK_CURRENT_CONTENT                      L"content"
  #define ON_RDK_BACKGROUND_ENVIRONMENT               L"environment"
  #define ON_RDK_DEFAULT_CONTENT_SECTION              L"default-content-section"

  #define ON_RDK_SETTINGS                             L"settings"
    #define ON_RDK_NAMED_VIEWS                          L"named-views"
    #define ON_RDK_NAMED_CPLANES                        L"named-cplanes"
    #define ON_RDK_NAMED_POSITIONS                      L"named-positions"
    #define ON_RDK_NAMED_SNAPSHOTS                      L"named-snapshots"
    #define ON_RDK_SORT_MODE                            L"sort-mode"
      #define ON_RDK_SORT_MODE_ASCENDING                  L"ascending"
      #define ON_RDK_SORT_MODE_DESCENDING                 L"descending"
      #define ON_RDK_SORT_MODE_CUSTOM                     L"custom"

    #define ON_RDK_MISCELLANEOUS                      L"miscellaneous"
      #define ON_RDK_CUSTOM_IMAGE_SIZE_IS_PRESET        L"custom-image-size-is-preset"
      #define ON_RDK_NAME_COLLISION_SUPPRESS            L"smart-merge-name-collision-suppress"
        #define ON_RDK_IMPORT                             L"import"
        #define ON_RDK_PASTE                              L"paste"

    #define ON_RDK_EXCLUDED_RENDER_ENGINES            L"excluded-render-engines"
      #define ON_RDK_UUIDS                              L"uuids"

    #define ON_RDK_FILTERS                            L"filters"
      #define ON_RDK_NAME_FILTER                        L"name-filter"
      #define ON_RDK_NAME_FILTER_INVERT                 L"name-filter-invert"
      #define ON_RDK_SHOW_UNASSIGNED                    L"show-unassigned-materials"
      #define ON_RDK_SHOW_V4                            L"show-v4-materials"
      #define ON_RDK_SHOW_HIDDEN                        L"show-hidden-materials"
      #define ON_RDK_SHOW_REFERENCE                     L"show-reference-materials"

    #define ON_RDK_POST_EFFECTS                       L"post-effects-new"
      #define ON_RDK_PEP_TYPE_EARLY                     L"early"
      #define ON_RDK_PEP_TYPE_TONE_MAPPING              L"tone-mapping"
      #define ON_RDK_PEP_TYPE_LATE                      L"late"
      #define ON_RDK_PEP_PLUG_IN                        L"plug-in"
      #define ON_RDK_PEP_LOCAL_NAME                     L"name"
      #define ON_RDK_PEP_ON                             L"on"
      #define ON_RDK_PEP_ID                             L"id"
      #define ON_RDK_PEP_SHOWN                          L"shown"
      #define ON_RDK_PEP_PARAMS                         L"state" // This should really be 'params'.
      #define ON_RDK_PEP_SELECTION                      L"selection"

    #define ON_RDK_RENDERING                          L"rendering"

      #define ON_RDK_RENDER_CHANNELS                    L"render-channels"
        #define ON_RDK_RCH_LIST                           L"list"
        #define ON_RDK_RCH_MODE                           L"mode"
          #define ON_RDK_RCH_MODE_AUTOMATIC                 L"automatic"
          #define ON_RDK_RCH_MODE_CUSTOM                    L"custom"

      #define ON_RDK_CURRENT_RENDER_PRESET              L"current-preset"
      #define ON_RDK_EMBED_SUPPORT_FILES_ON             L"embed-support-files-on"

      #define ON_RDK_DITHERING_ENABLED                  L"use-dithering"
      #define ON_RDK_DITHERING_METHOD                   L"dithering"
        #define ON_RDK_DITHERING_METHOD_FLOYD_STEINBERG   L"floyd-steinberg"
        #define ON_RDK_DITHERING_METHOD_SIMPLE_NOISE      L"simple-noise"

      #define ON_RDK_PRE_PROCESS_GAMMA_ON               L"use-linear-workflow"
      #define ON_RDK_POST_PROCESS_GAMMA_ON              L"use-post-process-gamma"
      #define ON_RDK_POST_PROCESS_GAMMA                 L"gamma" // Keep original XML tag.

      #define ON_RDK_CUSTOM_REFLECTIVE_ENVIRONMENT_ON   L"custom-env-for-refl-and-refr-on"
      #define ON_RDK_CUSTOM_REFLECTIVE_ENVIRONMENT      L"custom-env-for-refl-and-refr"

    #define ON_RDK_SUN                                L"sun"
      #define ON_RDK_SUN_ENABLE_ALLOWED                 L"enable-allowed"
      #define ON_RDK_SUN_ENABLE_ON                      L"enable-on"
      #define ON_RDK_SUN_MANUAL_CONTROL_ALLOWED         L"manual-control-allowed"
      #define ON_RDK_SUN_MANUAL_CONTROL_ON              L"manual-control-on"
      #define ON_RDK_SUN_NORTH                          L"north"
      #define ON_RDK_SUN_AZIMUTH                        L"sun-azimuth"
      #define ON_RDK_SUN_ALTITUDE                       L"sun-altitude"
      #define ON_RDK_SUN_DATE_YEAR                      L"year"
      #define ON_RDK_SUN_DATE_MONTH                     L"month"
      #define ON_RDK_SUN_DATE_DAY                       L"day"
      #define ON_RDK_SUN_TIME_HOURS                     L"time"
      #define ON_RDK_SUN_DAYLIGHT_SAVING_ON             L"daylight-saving-on"
      #define ON_RDK_SUN_DAYLIGHT_SAVING_MINUTES        L"daylight-saving-minutes"
      #define ON_RDK_SUN_OBSERVER_LATITUDE              L"observer-latitude"
      #define ON_RDK_SUN_OBSERVER_LONGITUDE             L"observer-longitude"
      #define ON_RDK_SUN_OBSERVER_TIMEZONE              L"observer-timezone"
      #define ON_RDK_SUN_SKYLIGHT_ENABLED               L"skylight-on"
      #define ON_RDK_SUN_SKYLIGHT_SHADOW_INTENSITY      L"skylight-shadow-intensity"
      #define ON_RDK_SUN_SKYLIGHT_ENVIRONMENT_OVERRIDE  L"skylight-custom-environment-on"
      #define ON_RDK_SUN_SKYLIGHT_ENVIRONMENT_ID        L"skylight-custom-environment"
      #define ON_RDK_SUN_SHADOW_INTENSITY               L"shadow-intensity"
      #define ON_RDK_SUN_INTENSITY                      L"intensity"

    #define ON_RDK_SAFE_FRAME                         L"safe-frame"
      #define ON_RDK_SF_ENABLED                         L"on"
      #define ON_RDK_SF_PERSPECTIVE_ONLY                L"perspective-only"
      #define ON_RDK_SF_4x3_FIELD_GRID_ON               L"field-display-on"
      #define ON_RDK_SF_LIVE_FRAME                      L"live-frame"
      #define ON_RDK_SF_ACTION_FRAME                    L"action-frame"
      #define ON_RDK_SF_TITLE_FRAME                     L"title-frame"
        #define ON_RDK_SFF_ON                             L"on"
        #define ON_RDK_SFF_XSCALE                         L"x-scale"
        #define ON_RDK_SFF_YSCALE                         L"y-scale"
        #define ON_RDK_SFF_LINK                           L"link"

    #define ON_RDK_GROUND_PLANE                       L"ground-plane"
     #define ON_RDK_GP_ENABLED                          L"on"
     #define ON_RDK_GP_ALTITUDE                         L"altitude"
     #define ON_RDK_GP_AUTO_ALTITUDE                    L"auto-altitude"
     #define ON_RDK_GP_SHOW_UNDERSIDE                   L"show-underside"
     #define ON_RDK_GP_SHADOW_ONLY                      L"shadow-only"
     #define ON_RDK_GP_MATERIAL_ID                      L"material"
     #define ON_RDK_GP_TEXTURE_OFFSET                   L"texture-offset"
     #define ON_RDK_GP_TEXTURE_OFFSET_LOCKED            L"offset-lock" // Keep old string.
     #define ON_RDK_GP_TEXTURE_SIZE                     L"texture-size"
     #define ON_RDK_GP_TEXTURE_SIZE_LOCKED              L"repeat-lock" // Keep old string.
     #define ON_RDK_GP_TEXTURE_ROTATION                 L"texture-rotation"

// Decals (stored in object attributes user data).

#define ON_RDK_USER_DATA_ROOT             L"render-content-manager-data"

#define ON_RDK_DECALS                       L"decals"

  #define ON_RDK_DECAL                      L"decal"

    #define ON_RDK_DECAL_CUSTOM               L"custom"
    #define ON_RDK_DECAL_CUSTOM_RENDERER      L"renderer"
    #define ON_RDK_DECAL_CUSTOM_PARAMS        L"parameters"

    #define ON_RDK_DECAL_MAPPING              L"mapping"
    //----- +++++++++++++++++++
    #define ON_RDK_DECAL_MAPPING_PLANAR       L"planar"
    #define ON_RDK_DECAL_MAPPING_CYLINDRICAL  L"cylindrical"
    #define ON_RDK_DECAL_MAPPING_SPHERICAL    L"spherical"
    #define ON_RDK_DECAL_MAPPING_UV           L"uv"
    #define ON_RDK_DECAL_MAPPING_NONE         L"none"

    #define ON_RDK_DECAL_PROJECTION           L"projection"
    //----- ++++++++++++++++++++++
    #define ON_RDK_DECAL_PROJECTION_FORWARD   L"forward"
    #define ON_RDK_DECAL_PROJECTION_BACKWARD  L"backward"
    #define ON_RDK_DECAL_PROJECTION_BOTH      L"both"
    #define ON_RDK_DECAL_PROJECTION_NONE      L"none"

    #define ON_RDK_DECAL_MAP_TO_INSIDE_ON     L"map-to-inside-on"
    #define ON_RDK_DECAL_TRANSPARENCY         L"transparency"
    #define ON_RDK_DECAL_TEXTURE_INSTANCE     L"texture-instance"
    #define ON_RDK_DECAL_HEIGHT               L"height"
    #define ON_RDK_DECAL_ORIGIN               L"origin"
    #define ON_RDK_DECAL_RADIUS               L"radius"
    #define ON_RDK_DECAL_HORZ_SWEEP_STA       L"latitude-start"
    #define ON_RDK_DECAL_HORZ_SWEEP_END       L"latitude-stop"
    #define ON_RDK_DECAL_VERT_SWEEP_STA       L"longitude-start"
    #define ON_RDK_DECAL_VERT_SWEEP_END       L"longitude-stop"
    #define ON_RDK_DECAL_VECTOR_UP            L"vector-up"
    #define ON_RDK_DECAL_VECTOR_ACROSS        L"vector-across"
    #define ON_RDK_DECAL_MIN_U                L"min-u"
    #define ON_RDK_DECAL_MIN_V                L"min-v"
    #define ON_RDK_DECAL_MAX_U                L"max-u"
    #define ON_RDK_DECAL_MAX_V                L"max-v"
    #define ON_RDK_DECAL_IS_TEMPORARY         L"is-temporary"
    #define ON_RDK_DECAL_IS_VISIBLE           L"is-visible"
    #define ON_RDK_DECAL_INSTANCE_ID          L"instance-id"

// Render Content.

#define ON_RENDER_CONTENT_TYPE_NAME               L"type-name"
#define ON_RENDER_CONTENT_TYPE_ID                 L"type-id"
#define ON_RENDER_CONTENT_INSTANCE_ID             L"instance-id"
#define ON_RENDER_CONTENT_RENDER_ENGINE_ID        L"render-engine-id"
#define ON_RENDER_CONTENT_PLUG_IN_ID              L"plug-in-id"
#define ON_RENDER_CONTENT_GROUP_ID                L"group-id"
#define ON_RENDER_CONTENT_INSTANCE_NAME           L"instance-name"
#define ON_RENDER_CONTENT_CHILD_SLOT_NAME         L"child-slot-name"
#define ON_RENDER_CONTENT_NOTES                   L"notes"
#define ON_RENDER_CONTENT_TAGS                    L"tags"
#define ON_RENDER_CONTENT_HIDDEN                  L"hidden"
#define ON_RENDER_CONTENT_REFERENCE               L"reference"
#define ON_RENDER_CONTENT_AUTO_DELETE             L"auto-delete"

#define ON_RENDER_CONTENT_PARAMETERS              L"parameters"
#define ON_RENDER_CONTENT_PARAMETERS_V8           L"parameters-v8"
#define ON_RENDER_CONTENT_SIMULATION              L"simulation"

// General parameters used by materials that simulate ON_Material.

#define ON_MATERIAL_ALPHA_TRANSPARENCY                 L"alpha-transparency"
#define ON_MATERIAL_AMBIENT                            L"ambient"
#define ON_MATERIAL_DIFFUSE                            L"diffuse"
#define ON_MATERIAL_DISABLE_LIGHTING                   L"disable-lighting"
#define ON_MATERIAL_EMISSION                           L"emission"
#define ON_MATERIAL_FLAMINGO_LIBRARY                   L"flamingo-library"
#define ON_MATERIAL_FRESNEL_ENABLED                    L"fresnel-enabled"
#define ON_MATERIAL_CLARITY_AMOUNT                     L"clarity-amount"
#define ON_MATERIAL_IOR                                L"ior"
#define ON_MATERIAL_POLISH_AMOUNT                      L"polish-amount"
#define ON_MATERIAL_SHINE                              L"shine"       // Value is 0.0..1.0, NOT ON_Material::MaxShine.
#define ON_MATERIAL_SPECULAR                           L"specular"
#define ON_MATERIAL_REFLECTIVITY_AMOUNT                L"reflectivity"
#define ON_MATERIAL_REFLECTIVITY_COLOR                 L"reflectivity-color"
#define ON_MATERIAL_TRANSPARENCY_AMOUNT                L"transparency"
#define ON_MATERIAL_TRANSPARENCY_COLOR                 L"transparency-color"
#define ON_MATERIAL_SIM_REFLECTION_COLOR               L"reflection"  // Used by simulation, not by Custom Material field.
#define ON_MATERIAL_SIM_TRANSPARENT_COLOR              L"transparent" // Used by simulation, not by Custom Material field.

#define ON_MATERIAL_IS_PHYSICALLY_BASED                L"is-physically-based"

#define ON_PBR_MATERIAL_BRDF                           L"pbr-brdf"
#define   ON_PBR_MATERIAL_BRDF_GGX                       L"ggx"
#define   ON_PBR_MATERIAL_BRDF_WARD                      L"ward"
#define ON_PBR_MATERIAL_ALPHA                          L"pbr-alpha"
#define ON_PBR_MATERIAL_ANISOTROPIC                    L"pbr-anisotropic"
#define ON_PBR_MATERIAL_ANISOTROPIC_ROTATION           L"pbr-anisotropic-rotation"
#define ON_PBR_MATERIAL_BASE_COLOR                     L"pbr-base-color"
#define ON_PBR_MATERIAL_CLEARCOAT                      L"pbr-clearcoat"
#define ON_PBR_MATERIAL_CLEARCOAT_BUMP                 L"pbr-clearcoat-bump"
#define ON_PBR_MATERIAL_CLEARCOAT_ROUGHNESS            L"pbr-clearcoat-roughness"
#define ON_PBR_MATERIAL_EMISSION_COLOR                 L"pbr-emission"
#define ON_PBR_MATERIAL_EMISSION_MULTIPLIER            L"emission-multiplier"
#define ON_PBR_MATERIAL_METALLIC                       L"pbr-metallic"
#define ON_PBR_MATERIAL_OPACITY                        L"pbr-opacity"
#define ON_PBR_MATERIAL_OPACITY_IOR                    L"pbr-opacity-ior"
#define ON_PBR_MATERIAL_OPACITY_ROUGHNESS              L"pbr-opacity-roughness"
#define ON_PBR_MATERIAL_ROUGHNESS                      L"pbr-roughness"
#define ON_PBR_MATERIAL_SHEEN                          L"pbr-sheen"
#define ON_PBR_MATERIAL_SHEEN_TINT                     L"pbr-sheen-tint"
#define ON_PBR_MATERIAL_SPECULAR                       L"pbr-specular"
#define ON_PBR_MATERIAL_SPECULAR_TINT                  L"pbr-specular-tint"
#define ON_PBR_MATERIAL_SUBSURFACE                     L"pbr-subsurface"
#define ON_PBR_MATERIAL_SUBSURFACE_SCATTERING_COLOR    L"pbr-subsurface-scattering-color"
#define ON_PBR_MATERIAL_SUBSURFACE_SCATTERING_RADIUS   L"pbr-subsurface-scattering-radius"
#define ON_PBR_MATERIAL_USE_BASE_COLOR_TEXTURE_ALPHA   L"pbr-use-base-color-texture-alpha"

#define ON_RENDER_TEXTURE_FILENAME    L"filename"

// Material's texture simulation.
#define ON_RENDER_MATERIAL_TEXTURE_SIMULATION_FORMAT    L"Texture-%u-"
#define ON_RENDER_MATERIAL_TEXTURE_SIMULATION_FILENAME  L"filename"
#define ON_RENDER_MATERIAL_TEXTURE_SIMULATION_ON        L"on"
#define ON_RENDER_MATERIAL_TEXTURE_SIMULATION_AMOUNT    L"amount"
#define ON_RENDER_MATERIAL_TEXTURE_SIMULATION_TYPE      L"type"
#define ON_RENDER_MATERIAL_TEXTURE_SIMULATION_FILTER    L"filter"
#define ON_RENDER_MATERIAL_TEXTURE_SIMULATION_MODE      L"mode"
#define ON_RENDER_MATERIAL_TEXTURE_SIMULATION_UVW       L"uvw"
#define ON_RENDER_MATERIAL_TEXTURE_SIMULATION_WRAP_U    L"wrap-u"
#define ON_RENDER_MATERIAL_TEXTURE_SIMULATION_WRAP_V    L"wrap-v"

// Environment simulation.
#define ON_ENVIRONMENT_SIMULATION_BACKGROUND_COLOR      L"background-color"
#define ON_ENVIRONMENT_SIMULATION_BACKGROUND_IMAGE      L"background-image"
#define ON_ENVIRONMENT_SIMULATION_BACKGROUND_PROJECTION L"background-projection"

// Environment projections.
#define ON_ENVIRONMENT_PROJECTION_BOX                   L"box"
#define ON_ENVIRONMENT_PROJECTION_CUBE_MAP              L"cubemap"
#define ON_ENVIRONMENT_PROJECTION_CUBE_MAP_HORZ         L"horizontal-cross-cubemap"
#define ON_ENVIRONMENT_PROJECTION_CUBE_MAP_VERT         L"vertical-cross-cubemap"
#define ON_ENVIRONMENT_PROJECTION_EMAP                  L"emap"
#define ON_ENVIRONMENT_PROJECTION_HEMISPHERICAL         L"hemispherical"
#define ON_ENVIRONMENT_PROJECTION_LIGHT_PROBE           L"lightprobe"
#define ON_ENVIRONMENT_PROJECTION_PLANAR                L"planar"
#define ON_ENVIRONMENT_PROJECTION_SPHERICAL             L"spherical"

// Texture simulation.
#define ON_TEXTURE_SIMULATION_ON                            L"on"
#define ON_TEXTURE_SIMULATION_FILENAME                      L"filename"
#define ON_TEXTURE_SIMULATION_MODE                          L"mode"
#define ON_TEXTURE_SIMULATION_TYPE                          L"type"
#define ON_TEXTURE_SIMULATION_OFFSET                        L"offset"
#define ON_TEXTURE_SIMULATION_REPEAT                        L"repeat"
#define ON_TEXTURE_SIMULATION_ROTATION                      L"rotation"
#define ON_TEXTURE_SIMULATION_MAPPING_CHANNEL               L"mapping-channel"
#define ON_TEXTURE_SIMULATION_PROJECTION_MODE               L"projection-mode"
#define ON_TEXTURE_SIMULATION_HAS_TRANSPARENT_COLOR         L"has-trans-color"
#define ON_TEXTURE_SIMULATION_MIN_FILTER                    L"min-filter"
#define ON_TEXTURE_SIMULATION_MAG_FILTER                    L"mag-filter"
#define ON_TEXTURE_SIMULATION_TRANSPARENCY_TEXTURE_ID       L"transparency-texture-id"
#define ON_TEXTURE_SIMULATION_TRANSPARENT_COLOR             L"trans-color"
#define ON_TEXTURE_SIMULATION_TRANSPARENT_COLOR_SENSITIVITY L"trans-color-sensitivity"
#define ON_TEXTURE_SIMULATION_TREAT_AS_LINEAR               L"treat-as-linear"
#define ON_TEXTURE_SIMULATION_WRAP_TYPE                     L"wrap-type"
#define ON_TEXTURE_SIMULATION_BLEND_CONSTANT_A              L"blend-constant-a"

// Strings returned by ON_RenderContent::Kind().
#define ON_KIND_MATERIAL     L"material"
#define ON_KIND_ENVIRONMENT  L"environment"
#define ON_KIND_TEXTURE      L"texture"

// Standard texture child slot names.
#define ON_TEXTURE_CHILD_SLOT_NAME_BITMAP_TEXTURE         L"bitmap-texture"
#define ON_TEXTURE_CHILD_SLOT_NAME_BUMP_TEXTURE           L"bump-texture"
#define ON_TEXTURE_CHILD_SLOT_NAME_TRANSPARENCY_TEXTURE   L"transparency-texture"
#define ON_TEXTURE_CHILD_SLOT_NAME_ENVIRONMENT_TEXTURE    L"environment-texture"

#define ON_RDK_POSTFIX_SECTION  L"-section"

class ON_CLASS ON_XMLVariant
{
public:
  enum class Types : unsigned int
  {
    Null,
    Bool, Integer, Float, Double, String,
    DoubleArray2, DoubleArray3, DoubleArray4, DoubleColor4,
    Matrix, Uuid, Time, Buffer
  };

  enum class ArrayTypes : unsigned int
  {
    Array2, Array3, Array4, Array16
  };

public:
  ON_XMLVariant(); // Creates an empty string type.
  ON_XMLVariant(bool value);
  ON_XMLVariant(int value);
  ON_XMLVariant(float value);
  ON_XMLVariant(double value);
  ON_XMLVariant(time_t time);
  ON_XMLVariant(const ON_wString& value);
  ON_XMLVariant(const ON_UUID& uuid);
  ON_XMLVariant(const ON_2dPoint& p);
  ON_XMLVariant(const ON_3dPoint& p);
  ON_XMLVariant(const ON_4fColor& c);
  ON_XMLVariant(const ON_Xform& xform);
  ON_XMLVariant(const double* point, ArrayTypes at=ArrayTypes::Array3);
  ON_XMLVariant(const float*  point, ArrayTypes at=ArrayTypes::Array3);
  ON_XMLVariant(const wchar_t* wsz);
  ON_XMLVariant(const void* buffer, size_t size);
  ON_XMLVariant(const ON_Buffer& buffer);
  ON_XMLVariant(const ON_XMLVariant& src);
  virtual ~ON_XMLVariant();

  const ON_XMLVariant& operator = (const ON_XMLVariant& src);

  bool operator == (const ON_XMLVariant& v) const;
  bool operator != (const ON_XMLVariant& v) const;

  virtual ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;

public:
  virtual Types Type(void) const;
  virtual ON_wString TypeAsString(void) const;
  virtual bool IsEmpty(void) const;
  virtual bool IsNull(void) const;

  virtual bool Varies(void) const;
  virtual void SetVaries(void);

  virtual ON::LengthUnitSystem Units(void) const;
  virtual void SetUnits(ON::LengthUnitSystem units);

  // Optimized version of ON_wString::NeedsXMLEncode(). Always use this if possible
  // because it knows from the type of the variant whether entity ref encoded output is even possible.
  virtual bool NeedsXMLEncode(void) const;

  virtual ON_Buffer& GetBuffer(void) const;
  virtual void ClearBuffers(void);

public:
  virtual void SetNull(void);
  virtual void SetValue(int v);
  virtual void SetValue(double v);
  virtual void SetValue(float v);
  virtual void SetValue(const wchar_t* s);
  virtual void SetValue(const ON_wString& s);
  virtual void SetValue(const double* p, ArrayTypes at);
  virtual void SetValue(const float* p, ArrayTypes at);
  virtual void SetValue(const ON_2dPoint& p);
  virtual void SetValue(const ON_3dPoint& p);
  virtual void SetValue(const ON_4dPoint& p);
  virtual void SetValue(const ON_4fColor& c);
  virtual void SetValue(bool b);
  virtual void SetValue(time_t time);
  virtual void SetValue(const ON_UUID& uuid);
  virtual void SetValue(const ON_Xform& xform);
  virtual void SetValue(const void* buffer, size_t size);
  virtual void SetValue(const ON_Buffer& buffer);

  virtual bool       AsBool(void) const;
  virtual int        AsInteger(void) const;
  virtual double     AsDouble(void) const;
  virtual float      AsFloat(void) const;
  virtual ON_2dPoint As2dPoint(void) const;
  virtual ON_3dPoint As3dPoint(void) const;
  virtual ON_4dPoint As4dPoint(void) const;
  virtual ON_UUID    AsUuid(void) const;
  virtual ON_Xform   AsXform(void) const;
  virtual time_t     AsTime(void) const;
  virtual ON_4fColor AsColor(void) const;
  virtual ON_Buffer  AsBuffer(void) const;
  virtual void*      AsBuffer(size_t& size_out) const;
  virtual ON_wString AsString(void) const;

  operator bool() const;
  operator double() const;
  operator float() const;
  operator int() const;
  operator ON_2dPoint() const;
  operator ON_3dPoint() const;
  operator ON_4dPoint() const;
  operator ON_4fColor() const;
  operator ON_UUID() const;
  operator time_t() const;
  operator ON_Buffer() const;
  operator ON_wString() const;

public:
  virtual bool TypePending(void) const;
  virtual void SetTypePendingFlag(bool bTypePending) const;

  // Format string as type and value. Useful for debugging.
  virtual void Format(ON_wString& s) const;

protected:
  virtual void StringToPoint(int iValues) const;

private:
  class ON_XMLVariantPrivate* _private;
  ON__UINT8 _PRIVATE[168+64];
};

class ON_CLASS ON_XMLProperty
{
public:
  ON_XMLProperty();
  ON_XMLProperty(const ON_XMLVariant& value);
  ON_XMLProperty(const ON_wString& sName, const ON_XMLVariant& value);
  ON_XMLProperty(const ON_XMLProperty& prop);
  virtual ~ON_XMLProperty();

  const ON_XMLProperty& operator = (const ON_XMLProperty& prop);

  virtual const ON_wString& Name(void) const;
  virtual void SetName(const wchar_t* name);

  virtual ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;

  virtual ON_XMLProperty* Next(void) const;

  virtual bool IsDefaultProperty(void) const;

  virtual const ON_XMLVariant& GetValue(void) const;
  virtual void SetValue(const ON_XMLVariant& value);

  bool operator < (const ON_XMLProperty& prop) const;

  virtual ON_XMLVariant& GetNonConstValue(void);

  virtual void SetHugeStringValue(const ON_wString& s);

  virtual void* EVF(const wchar_t* func, void* data);

private:
  class ON_XMLPropertyPrivate* _private;
  ON__UINT8 _PRIVATE[24+64];
  friend class ON_XMLNode;
  friend class ON_XMLNodePrivate;
  friend class ON_XMLPropertyPrivate;
};

class ON_CLASS ON_XMLSegmentedStream
{
public:
  ON_XMLSegmentedStream();
  virtual ~ON_XMLSegmentedStream();

  virtual int Count(void) const;
  virtual void Append(wchar_t* s);
  virtual wchar_t* Segment(int index) const;

protected:
  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

  ON_XMLSegmentedStream(const ON_XMLSegmentedStream&) = delete;
  const ON_XMLSegmentedStream& operator = (const ON_XMLSegmentedStream&) = delete;

private:
  class ON_XMLSegmentedStreamPrivate* _private;
};

class ON_CLASS ON_XMLNode
{
public:
  ON_XMLNode(const wchar_t* name); // Always creates empty default property.
  ON_XMLNode(const ON_XMLNode&);
  ON_XMLNode(ON_XMLNode&&) noexcept = delete;
  virtual ~ON_XMLNode();

  const ON_XMLNode& operator = (const ON_XMLNode&);

  bool operator == (const ON_XMLNode&) const;
  bool operator != (const ON_XMLNode&) const;

  virtual bool MergeFrom(const ON_XMLNode& src); // src node must have the same name

  virtual const ON_wString& TagName(void) const;
  virtual void SetTagName(const wchar_t* name);

  static bool IsValidXMLNameWithDebugging(const wchar_t* name);
  static bool IsValidXMLName(const wchar_t* name);
  static ON_wString GetNameFromTag(const wchar_t* tag);

public: // Hierarchy.
  // Get the first child of this node or null if none.
  virtual ON_XMLNode* FirstChild(void) const;

  // Get the previous sibling of this node or null if none.
  virtual ON_XMLNode* PrevSibling(void) const;

  // Get the next sibling of this node or null if none.
  virtual ON_XMLNode* NextSibling(void) const;

  // Get the parent of this node or null if none.
  virtual ON_XMLNode* Parent(void) const;

  // Get the top-level parent of this node.
  virtual const ON_XMLNode& TopLevel(void) const;

  // Recursively iterate over the children of this node, calling the supplied callback function for each child.
  // If the callback function returns false, this function will fail.
  // Returns true if successful, false on failure.
  virtual bool RecurseChildren(ON_XMLRecurseChildrenCallback callback, void* data) const;

public: // Change data.
  // Adds a node as a child of this node. Takes ownership of node.
  // Returns a pointer to node for convenience.
  virtual ON_XMLNode* AttachChildNode(ON_XMLNode* node);

  // Attaches a property directly to the node. Takes ownership of the property.
  // Any existing property with the same name is first deleted.
  // For convenience, returns a pointer to the input property.
  virtual ON_XMLProperty* AttachProperty(ON_XMLProperty* prop);

  // Sets a property on the node. The property is copied and ownership of it remains with the caller.
  // Any existing property with the same name is first deleted.
  // Returns a pointer to the copy of the property.
  virtual ON_XMLProperty* SetProperty(const ON_XMLProperty& prop);

  // Removes and deletes this node.
  virtual void Remove(void);

  // Removes and deletes the child node, if possible.
  // Returns true if successful, else false.
  virtual bool RemoveChild(ON_XMLNode* child);

  // Removes and deletes the named property, if possible.
  // Returns true if successful, else false.
  virtual bool RemoveProperty(const wchar_t* prop_name);

  // Removes the child node and passes ownership to the caller.
  // Returns the detached node or null on failure.
  virtual ON_XMLNode* DetachChild(ON_XMLNode& child);

  // Removes and deletes all child nodes.
  virtual void RemoveAllChildren(void);

  // Removes and deletes all properties and adds an empty default property.
  virtual void RemoveAllProperties(void);

  // Removes and deletes all child nodes and properties, and clears the tag name.
  virtual void Clear(void);

  // Moves this node before another node.
  virtual void MoveBefore(ON_XMLNode& other);

  // Moves this node after another node.
  virtual void MoveAfter(ON_XMLNode& other);

public: // Serialization.
  static constexpr ON__UINT32 ReadError = 0xFFFFFFFF; // Indicates ReadFromStream() failure.
  virtual ON__UINT32 ReadFromStream(const wchar_t* buf, bool warnings_as_errors=false, bool validate_tags=true);

  virtual void* LastReadBufferPointer(void) const;

  // This function is called on the top-most node during the reading process.
  virtual void OnNodeReadFromStream(const ON_XMLNode* node) const;

  virtual ON_wString String(bool include_formatting=true, bool force_long_format=false, bool sorted_props=false) const;
  operator ON_wString() const;

  // Writes the node to a wide buffer (AKA 'stream') as XML text.
  // max_chars is the maximum number of wide characters that the buffer can accommodate.
  // To find out how much space is needed without actually writing anything, pass zero.
  // When writing to the buffer, a terminator is written if there is room for it, but the
  // terminator is not included in the returned number of characters.
  virtual ON__UINT32 WriteToStream(wchar_t* stream, ON__UINT32 max_chars, bool include_formatting = true, bool force_long_format = false, bool sorted_props = false) const;

  class ON_CLASS CharacterCounts
  {
  public:
    void operator += (const CharacterCounts& cw);

    // Number of characters that would have been written if the buffer was big enough.
    // This value does not include the terminator.
    ON__UINT32 _logical = 0;

    // Number of characters that were physically written. Always zero if max_chars is zero.
    // It is otherwise usually the same as m_logical, but less when the buffer is too small.
    // This value does not include the terminator.
    ON__UINT32 _physical = 0;

    ON__UINT64 _reserved = 0;
  };

  virtual CharacterCounts WriteToStreamEx      (wchar_t* stream, ON__UINT32 max_chars, bool include_formatting = true, bool force_long_format = false, bool sorted_props = false) const;
  virtual CharacterCounts WriteHeaderToStream  (wchar_t* stream, ON__UINT32 max_chars, bool include_formatting = true, bool force_long_format = false, bool sorted_props = false) const;
  virtual CharacterCounts WriteChildrenToStream(wchar_t* stream, ON__UINT32 max_chars, bool include_formatting = true, bool force_long_format = false, bool sorted_props = false) const;
  virtual CharacterCounts WriteFooterToStream  (wchar_t* stream, ON__UINT32 max_chars, bool include_formatting = true, bool force_long_format = false) const;

  virtual bool WriteToSegmentedStream(ON_XMLSegmentedStream& stream, bool include_formatting=true, bool force_long_format=false, bool sorted_props=false) const;

public: // Utilities.
  virtual int PropertyCount(void) const;
  virtual int ChildCount(void) const;

  virtual int GetNestedDepth(void) const;

  // Get the CRC of this node.
  // Param current_remainder is the current remainder value as used by ON_CRC32.
  // Param recursive is true to process nodes recursively, false to process only this node.
  virtual ON__UINT32 DataCRC(ON__UINT32 current_remainder, bool recursive) const;

  // Use this when you are looking for a node that is only one child below - non-recursive, but fast.
  virtual ON_XMLNode* GetNamedChild(const wchar_t* name) const;

  virtual ON_XMLProperty* GetNamedProperty(const wchar_t* name) const;

  virtual ON_XMLProperty& GetDefaultProperty(void) const;

  // Returns the full path to this node.
  virtual ON_wString GetPathFromRoot(void) const;

  // Gets at nodes deep into the tree using a slash-delimited path, i.e., "child/grandchild/great-grandchild".
  // There's no checking for multiple nodes with the same name at each level of the tree, so if you use these
  // methods, you have to make sure you have unique node names at each level.

  // Gets a child node given the relative path from the current node. If the node does not exist, the method
  // returns null. The returned pointer should not be deleted by the caller. The child node is owned by its
  // immediate parent at that position in the node hierarchy.
  virtual ON_XMLNode* GetNodeAtPath(const wchar_t* path) const;

  // Gets a child node given the relative path from the current node. If the node does not exist, it is
  // created. This method should therefore never return null. The returned pointer should not be deleted
  // by the caller. The child node is owned by its immediate parent at that position in the node hierarchy.
  virtual ON_XMLNode* CreateNodeAtPath(const wchar_t* path);

protected:
  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

public: // Iteration.
  class ON_CLASS ChildIterator
  {
  public:
    ChildIterator(const ON_XMLNode* parent);
    ChildIterator(const ChildIterator& other);
    virtual ~ChildIterator();

    const ChildIterator& operator = (const ChildIterator& other);

    virtual ON_XMLNode* GetNextChild(void);
    virtual void* EVF(const wchar_t* func, void* data);

  private:
    class ON_XMLNodeChildIteratorPrivate* _private;
  };

  class ON_CLASS PropertyIterator
  {
  public:
    PropertyIterator(const ON_XMLNode* parent, bool sorted = false);
    PropertyIterator(const PropertyIterator& other);
    virtual ~PropertyIterator();

    const PropertyIterator& operator = (const PropertyIterator& other);

    virtual ON_XMLProperty* GetNextProperty(void);
    virtual void* EVF(const wchar_t* func, void* data);

  private:
    class ON_XMLNodePropertyIteratorPrivate* _private;
  };

  virtual ChildIterator GetChildIterator(void) const;
  virtual PropertyIterator GetPropertyIterator(bool alphabetized = false) const;

  static bool AutoTypePropValue(void);
  static void SetAutoTypePropValue(bool b=true);

  // For internal use only.
  virtual void SetInternalDebuggingFlags(ON__UINT64);

private:
  class ON_XMLNodePrivate* _private;
  ON__UINT8 _PRIVATE[152+64];
  friend class ON_XMLNodePrivate;
  friend class ON_XMLNodePropertyIteratorPrivate;
};

class ON_CLASS ON_XMLRootNode : public ON_XMLNode
{
public:
  ON_XMLRootNode();
  ON_XMLRootNode(const ON_XMLNode& node);
  ON_XMLRootNode(const ON_XMLRootNode& root);
  virtual ~ON_XMLRootNode();

  const ON_XMLRootNode& operator = (const ON_XMLNode& node);
  const ON_XMLRootNode& operator = (const ON_XMLRootNode& root);

  virtual const ON_XMLRootNode& NodeForRead(void) const;
  virtual ON_XMLRootNode& NodeForWrite(void);

  virtual bool ReadFromFile(const wchar_t* path, bool warnings_as_errors=false, bool validate_tags=true);
  virtual bool WriteToFile (const wchar_t* path, bool include_formatting=true, bool utf8=false, bool sorted_properties=false) const;

  virtual void Clear(void) override;

private:
  class ON_XMLRootNodePrivate* _private;
};

class ON_CLASS ON_XMLUserData : public ON_UserData
{
public:
  ON_XMLUserData();
  ON_XMLUserData(const ON_XMLUserData& ud);
  virtual ~ON_XMLUserData();

  const ON_XMLUserData& operator = (const ON_XMLUserData& ud);

  virtual const ON_XMLRootNode& XMLRootForRead(void) const;
  virtual ON_XMLRootNode& XMLRootForWrite(void) const;

  virtual ON_XMLProperty* Property(const wchar_t* xml_path, const wchar_t* prop_name) const;

  virtual ON_XMLVariant Value(const wchar_t* xml_path, const wchar_t* prop_name = L"") const;
  virtual bool SetValue(const wchar_t* xml_path, const wchar_t* prop_name, const ON_XMLVariant& value);
  virtual void SetValue(const wchar_t* xml_path, const ON_XMLVariant& value);

  virtual void Clear(void) const;

  virtual int Version(void) const;

  virtual bool Archive(void) const override;

  virtual void SetToDefaults(void) const = 0;
  virtual void ReportVersionError(void) const = 0;

  virtual bool Write(ON_BinaryArchive&) const override;
  virtual bool Read(ON_BinaryArchive&) override;

  virtual void _Dump(const wchar_t* wszFileName) const;

  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

protected:
  ON_XMLProperty* InternalProperty(const wchar_t* xml_path, const wchar_t* prop_name) const;

public:
  virtual void SetToDefaultsImpl(int) const;

private:
  class ON_XMLUserDataPrivate* _private;
  ON__UINT8 _PRIVATE[240+64];
};

class ON_CLASS ON_XMLParameters
{
public:
  ON_XMLParameters(ON_XMLNode& node);
  ON_XMLParameters(const ON_XMLNode& node);
  ON_XMLParameters(const ON_XMLParameters&) = delete;
  virtual ~ON_XMLParameters();

  const ON_XMLParameters& operator = (const ON_XMLParameters&) = delete;

  virtual void SetWriteTypeProperty(bool b);
  virtual void SetDefaultReadType(const wchar_t* type);

  virtual ON_wString AsString(void) const;
  virtual void SetAsString(const wchar_t* s);

  virtual bool GetParam(const wchar_t* param_name, ON_XMLVariant& param_value_out) const;
  virtual ON_XMLNode* SetParam(const wchar_t* param_name, const ON_XMLVariant& param_value);

  // Easy-to-use helper function. Returns 'default_value' if param is not found.
  ON_XMLVariant GetParam(const wchar_t* param_name, const ON_XMLVariant& default_value) const;

  // Expert access to the underlying XML node.
        ON_XMLNode& Node(void);
  const ON_XMLNode& Node(void) const;

  class ON_CLASS CIterator
  {
  public:
    CIterator(const ON_XMLParameters& p);
    virtual ~CIterator();

    bool Next(ON_wString& param_name_out, ON_XMLVariant& param_value_out) const;

  protected:
    virtual void* EVF(const wchar_t*, void*);

  private:
    class ON_XMLParametersIteratorPrivate* _private;
  };
  CIterator* NewIterator(void) const;

protected:
  virtual bool GetParamNode(const ON_XMLNode& node, ON_XMLVariant& param_value) const;
  virtual void* EVF(const wchar_t*, void*);
  virtual ON_XMLNode* SetParamNode(ON_XMLNode& node, const wchar_t* param_name, const ON_XMLVariant& param_value);
  virtual ON_XMLNode* ObtainChildNodeForWrite(ON_XMLNode& node, const wchar_t* param_name) const;

private:
  class ON_XMLParametersPrivate* _private;
  friend class ON_XMLParametersIteratorPrivate;
};

class ON_CLASS ON_XMLParametersV8 : public ON_XMLParameters
{
public:
  ON_XMLParametersV8(ON_XMLNode& node);
  ON_XMLParametersV8(const ON_XMLNode& node);
  ON_XMLParametersV8(const ON_XMLParametersV8&) = delete;

  const ON_XMLParametersV8& operator = (const ON_XMLParametersV8&) = delete;

  virtual bool GetParam(const wchar_t* param_name, ON_XMLVariant& param_value_out) const override;

protected:
  virtual ON_XMLNode* ObtainChildNodeForWrite(ON_XMLNode& node, const wchar_t* param_name) const override;
  virtual ON_XMLNode* FindNodeByNameProperty(const wchar_t* param_name) const;
};

// Class ON_XMLParamBlock is ON_XMLParameters with a built-in XML node.
class ON_CLASS ON_XMLParamBlock : public ON_XMLParameters
{
public:
  ON_XMLParamBlock();
  virtual ~ON_XMLParamBlock();

private:
  ON_XMLRootNode _node;
  ON__UINT64 _reserved;
};

ON_DECL bool ON_RunXMLTests(const wchar_t* test_folder);

////////////////////////////////////////////////////////////////////////////////////////////
//
// ON_RdkUserData is for internal use only and is not intended for use by SDK clients.
//
////////////////////////////////////////////////////////////////////////////////////////////

class ON_CLASS ON_RdkUserData : public ON_XMLUserData
{
private:
  ON_OBJECT_DECLARE(ON_RdkUserData);

public:
  ON_RdkUserData();
  ON_RdkUserData(const ON_RdkUserData& ud);
  virtual ~ON_RdkUserData();

  const ON_RdkUserData& operator = (const ON_RdkUserData& ud);

  static ON_UUID Uuid(void);

  virtual void SetToDefaults(void) const override;
  virtual bool GetDescription(ON_wString& s) override;
  virtual bool Read(ON_BinaryArchive&) override;
  virtual bool Write(ON_BinaryArchive&) const override;
  virtual bool DeleteAfterWrite(const ON_BinaryArchive& archive, const ON_Object* parent_object) const override;
  virtual bool DeleteAfterRead(const ON_BinaryArchive& archive, ON_Object* parent_object) const override;
  virtual bool Transform(const ON_Xform& xform) override;
  virtual void ReportVersionError(void) const override;

  typedef bool (*ReadCallback)(ON_RdkUserData& ud);
  typedef bool (*WriteCallback)(const ON_RdkUserData& ud);
  typedef bool (*TransformCallback)(ON_RdkUserData& ud, const ON_Xform& xform);

  static void SetCallbacks(ReadCallback rc, WriteCallback wc, TransformCallback tc);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
// This class is for internal RDK use only.
class ON_CLASS ON_RdkDocumentDefaults
{
public:
  enum class ValueSets { All, New };

  ON_RdkDocumentDefaults(int major_version, ValueSets vs, void* reserved=nullptr);
  ON_RdkDocumentDefaults(const ON_RdkDocumentDefaults&) = delete;
  virtual ~ON_RdkDocumentDefaults();

  const ON_RdkDocumentDefaults& operator = (const ON_RdkDocumentDefaults&) = delete;

  virtual const ON_XMLNode& Node(void) const;

  virtual void CopyDefaultsTo(ON_XMLNode& dest) const;

  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

private:
  virtual void CreateXML(void);

private:
  ON_XMLRootNode _root;
  const ValueSets _vs;
  const int _major_version;
  void* _reserved;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////

extern ON_DECL ON_UUID ON_UuidDefaultMaterialInstance;
extern ON_DECL ON_UUID ON_UuidDefaultEnvironmentInstance;

#endif
