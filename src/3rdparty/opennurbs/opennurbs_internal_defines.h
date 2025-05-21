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

// Internal header; not in the public SDK.

#if !defined(OPENNURBS_INTERNAL_DEFINES_INC_)
#define OPENNURBS_INTERNAL_DEFINES_INC_

#if defined(ON_COMPILING_OPENNURBS)

#include <unordered_map>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#ifdef ON_RUNTIME_WIN
#define PRIVATE_CHECK(c) auto priv_has = sizeof(_PRIVATE), priv_needs = sizeof(c) + 64; \
        if (priv_has < priv_needs) { ON_wString priv; \
            priv.Format(L#c L" _PRIVATE has %u but needs %u bytes\n", priv_has, priv_needs); \
            OutputDebugString(priv); ON_ASSERT(false); }
#else
#define PRIVATE_CHECK(c) { }
#endif

#define ON_RDK_UD_ROOT       L"render-content-manager-data"

inline bool IsFloatEqual (float  f1, float  f2) { return (fabsf(f1 - f2) < 1e-6); }
inline bool IsDoubleEqual(double d1, double d2) { return (fabs (d1 - d2) < 1e-10); }

ON_UUID RdkPlugInId(void);

ON__INT64 Integerize(float dirty);
ON__INT64 Integerize(double dirty);

void SetModel(const class ON_RenderContent&, ONX_Model&);
ON_3dmObjectAttributes* GetComponentAttributes(const ON_ModelComponent& component);
ON_RenderContent* NewRenderContentFromNode(const class ON_XMLNode& node);
ON_PostEffect* NewPostEffectFromNode(ON_XMLNode& node);
void SetRenderContentNodeRecursive(const ON_RenderContent& rc, ON_XMLNode& node);
ON_XMLNode* FindPostEffectNodeForId(const ON_XMLNode& sectionNode, const ON_UUID& id);
bool SetRDKObjectInformation(ON_Object& object, const ON_wString& xml, int archive_3dm_version);
bool GetRDKEmbeddedFiles(const ONX_Model_UserData& docud, ON_ClassArray<ON_wString>& paths, ON_SimpleArray<unsigned char*>& embedded_files_as_buffers, ON_SimpleArray<size_t>& buffer_sizes);
bool GetEntireDecalXML(const ON_3dmObjectAttributes& attr, ON_XMLRootNode& xmlOut);
void CreateMeshModifiersFromXML(const ONX_Model& model, int archive_3dm_version);
void CreateXMLFromMeshModifiers(const ONX_Model& model, int archive_3dm_version);
bool GetMeshModifierObjectInformation(const ON_Object& object, ON_wString& xml, int archive_3dm_version);
void SetMeshModifierObjectInformation(ON_Object& object, const ON_MeshModifier* mm, int archive_3dm_version);
bool IsRDKDocumentInformation(const ONX_Model_UserData& docud);

template <class T> inline T Lerp(float  t, const T& l, const T& h) { return l + T(t) * (h - l); }
template <class T> inline T Lerp(double t, const T& l, const T& h) { return l + T(t) * (h - l); }

class ON_InternalXMLImpl
{
public:
  ON_InternalXMLImpl(ON_XMLNode* n=nullptr) : _model_node(n) { }
  ON_InternalXMLImpl(const ON_InternalXMLImpl&) = delete;
  virtual ~ON_InternalXMLImpl();

  const ON_InternalXMLImpl& operator = (const ON_InternalXMLImpl&) = delete;

  bool operator == (const ON_InternalXMLImpl&) const = delete;
  bool operator != (const ON_InternalXMLImpl&) const = delete;

  ON_XMLVariant GetParameter(const wchar_t* path_to_node, const wchar_t* param_name, const ON_XMLVariant& def) const;
  bool SetParameter(const wchar_t* path_to_node, const wchar_t* param_name, const ON_XMLVariant& value);

  ON_XMLVariant GetParameter(const wchar_t* param_name, const ON_XMLVariant& def) const { return GetParameter(L"", param_name, def); }
  bool SetParameter(const wchar_t* param_name, const ON_XMLVariant& value) { return SetParameter(L"", param_name, value); }

  ON_XMLVariant GetParameter_NoType(const wchar_t* path_to_node, const wchar_t* param_name, const wchar_t* default_type, const ON_XMLVariant& def) const;
  bool SetParameter_NoType(const wchar_t* path_to_node, const wchar_t* param_name, const ON_XMLVariant& value);

  bool RemoveParameter(const wchar_t* path_to_node, const wchar_t* param_name);

  ON_XMLNode& Node(void) const;

  void SetModelNode(ON_XMLNode& node);

protected:
  virtual ON_wString NameOfRootNode(void) const;

private:
  ON_XMLVariant InternalGetParameter(const wchar_t* path_to_node, const wchar_t* param_name, const wchar_t* default_type, const ON_XMLVariant& def) const;
  bool InternalSetParameter(const wchar_t* path_to_node, const wchar_t* param_name, bool write_type, const ON_XMLVariant& value);

public:
  mutable std::recursive_mutex _mutex;
  mutable ON_XMLNode* _local_node = nullptr; // Used when m_model_node is null.
  ON_XMLNode* _model_node;
};

class ON_DecalCollection final
{
public:
  ON_DecalCollection(ON_3dmObjectAttributes* a) : m_attr(a) { }
  ON_DecalCollection(const ON_DecalCollection& dc) = delete;
  ~ON_DecalCollection();

  const ON_DecalCollection& operator = (const ON_DecalCollection& dc);

  ON_Decal* AddDecal(void);
  bool RemoveDecal(const ON_Decal&);
  void RemoveAllDecals(void);
  void ClearDecalArray(void);
  const ON_SimpleArray<ON_Decal*>& GetDecalArray(void) const;

  void SetChanged(void);

  void UpdateUserData(unsigned int archive_3dm_version) const;

private:
  void Populate(void) const;
  int  FindDecalIndex(const ON_UUID& id) const;

private:
  ON_3dmObjectAttributes* m_attr;
  mutable ON_XMLRootNode m_root_node;
  mutable ON_SimpleArray<ON_Decal*> m_decals;
  mutable bool m_populated = false;
  mutable bool m_changed = false;
};

template<class T> inline void hash_combine(size_t& seed, const T& v)
{
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9E3779B9 + (seed << 6) + (seed >> 2);
}

class UuidHasher // Hasher for using ON_UUID as key with std::map
{
public:
	inline size_t operator()(const ON_UUID& uuid) const
	{
		size_t seed = 0;

		const auto* d = reinterpret_cast<const ON__UINT32*>(&uuid);
		::hash_combine(seed, d[0]);
		::hash_combine(seed, d[1]);
		::hash_combine(seed, d[2]);
		::hash_combine(seed, d[3]);

		return seed;
	}
};

class ON_EnvironmentsImpl final : public ON_InternalXMLImpl
{
public:
  ON_EnvironmentsImpl() { }
  ON_EnvironmentsImpl(ON_XMLNode& n) : ON_InternalXMLImpl(&n) { }
  ON_EnvironmentsImpl(const ON_EnvironmentsImpl&);

  ON_EnvironmentsImpl& operator = (const ON_EnvironmentsImpl&);

  bool operator == (const ON_EnvironmentsImpl&);

  ON_UUID BackgroundRenderEnvironmentId(void) const;
  void    SetBackgroundRenderEnvironmentId(const ON_UUID& id);
  bool    SkylightingRenderEnvironmentOverride(void) const;
  void    SetSkylightingRenderEnvironmentOverride(bool on);
  ON_UUID SkylightingRenderEnvironmentId(void) const;
  void    SetSkylightingRenderEnvironmentId(const ON_UUID& id);
  bool    ReflectionRenderEnvironmentOverride(void) const;
  void    SetReflectionRenderEnvironmentOverride(bool on);
  ON_UUID ReflectionRenderEnvironmentId(void) const;
  void    SetReflectionRenderEnvironmentId(const ON_UUID& id);
};

class ON_3dmRenderSettingsPrivate final
{
public:
  ON_3dmRenderSettingsPrivate();
  ON_3dmRenderSettingsPrivate(const ON_3dmRenderSettingsPrivate&);
  virtual ~ON_3dmRenderSettingsPrivate();

  const ON_3dmRenderSettingsPrivate& operator = (const ON_3dmRenderSettingsPrivate&);

  void SetToDefaults(void);

  void SpecializeGroundPlane(ON_GroundPlane& gp);
  void SpecializeLinearWorkflow(ON_LinearWorkflow& lw);
  void SpecializeSun(ON_Sun& sun);

  static ON_3dmRenderSettingsPrivate& Get(const ON_3dmRenderSettings& rs);

private:
  void CreateDocumentObjects(void);

public:
  ON_XMLRootNode _rdk_document_data;

  // Document objects. The pointers to these objects are never null because
  // they are created in every constructor. See CreateDocumentObjects().
  ON_GroundPlane* _ground_plane = nullptr;
  ON_Dithering* _dithering = nullptr;
  ON_SafeFrame* _safe_frame = nullptr;
  ON_Skylight* _skylight = nullptr;
  ON_LinearWorkflow* _linear_workflow = nullptr;
  ON_RenderChannels* _render_channels = nullptr;
  ON_Sun* _sun = nullptr;
  ON_EnvironmentsImpl* _environments = nullptr;
  ON_PostEffects* _post_effects = nullptr;
  bool _gp_specialized = false;
  bool _lw_specialized = false;
  bool _sun_specialized = false;
};

//--------------------------------------------------------------------------------------------------

class ON_INTERNAL_OBSOLETE
{
public:

  //// OBSOLETE V5 Dimension Types ///////////////////////////////////////////////////////////
  enum class V5_eAnnotationType : unsigned char
  {
    dtNothing,
    dtDimLinear,
    dtDimAligned,
    dtDimAngular,
    dtDimDiameter,
    dtDimRadius,
    dtLeader,
    dtTextBlock,
    dtDimOrdinate,
  };

  // convert integer to eAnnotationType enum
  static ON_INTERNAL_OBSOLETE::V5_eAnnotationType V5AnnotationTypeFromUnsigned(
    unsigned int v5_annotation_type_as_unsigned
  );

  //// dim text locations ///////////////////////////////////////////////////////////
  enum class V5_TextDisplayMode : unsigned char
  {
    kNormal = 0, // antique name - triggers use of current default
    kHorizontalToScreen = 1,         // Horizontal to the screen
    kAboveLine = 2,
    kInLine = 3,
    kHorizontalInCplane = 4   // horizontal in the dimension's plane 
  };

  static ON_INTERNAL_OBSOLETE::V5_TextDisplayMode V5TextDisplayModeFromUnsigned(
    unsigned int text_display_mode_as_unsigned
  );

  static ON_INTERNAL_OBSOLETE::V5_TextDisplayMode V5TextDisplayModeFromV6DimStyle(
    const ON_DimStyle& V6_dim_style
  );
  
  /// <summary>
  /// Attachment of content
  /// </summary>
  enum class V5_vertical_alignment : unsigned char
  {
    /// <summary>
    /// Text centered on dimension line (does not apply to leaders or text)
    /// </summary>
    Centered = 0,
    /// <summary>
    /// Text above dimension line (does not apply to leaders or text)
    /// </summary>
    Above = 1,
    /// <summary>
    /// Text below dimension line (does not apply to leaders or text)
    /// </summary>
    Below = 2,
    /// <summary>
    /// Leader tail at top of text  (does not apply to text or dimensions)
    /// </summary>
    Top = 3, // = TextVerticalAlignment::Top
    /// <summary>
    /// Leader tail at middle of first text line (does not apply to text or dimensions)
    /// </summary>
    FirstLine = 4, // = MiddleOfTop
    /// <summary>
    /// Leader tail at middle of text or content (does not apply to text or dimensions)
    /// </summary>
    Middle = 5, // = Middle
    /// <summary>
    /// Leader tail at middle of last text line (does not apply to text or dimensions)
    /// </summary>
    LastLine = 6, // = MiddleOfBottom
    /// <summary>
    /// Leader tail at bottom of text (does not apply to text or dimensions)
    /// </summary>
    Bottom = 7, // = Bottom
    /// <summary>
    /// Leader tail at bottom of text, text underlined (does not apply to text or dimensions)
    /// </summary>
    Underlined = 8 // Underlined

    // nothing matched BottomOfTop
  };

  static ON_INTERNAL_OBSOLETE::V5_vertical_alignment V5VerticalAlignmentFromUnsigned(
    unsigned int vertical_alignment_as_unsigned
  );

  static ON_INTERNAL_OBSOLETE::V5_vertical_alignment V5VerticalAlignmentFromV5Justification(
    unsigned int v5_justification_bits
  );

  static ON_INTERNAL_OBSOLETE::V5_vertical_alignment V5VerticalAlignmentFromV6VerticalAlignment(
    const ON::TextVerticalAlignment text_vertical_alignment
  );

  static ON::TextVerticalAlignment V6VerticalAlignmentFromV5VerticalAlignment(
    ON_INTERNAL_OBSOLETE::V5_vertical_alignment V5_vertical_alignment
  );


  enum class V5_horizontal_alignment : unsigned char
  {
    /// <summary>
    /// Left aligned
    /// </summary>
    Left = 0, // Left
    /// <summary>
    /// Centered
    /// </summary>
    Center = 1,
    /// <summary>
    /// Right aligned
    /// </summary>
    Right = 2,
    /// <summary>
    /// Determined by orientation
    /// Primarily for leaders to make
    /// text right align when tail is to the left 
    /// and left align when tail is to the right
    /// </summary>
    Auto = 3,
  };

  static ON_INTERNAL_OBSOLETE::V5_horizontal_alignment V5HorizontalAlignmentFromUnsigned(
    unsigned int horizontal_alignment_as_unsigned
  );

  static ON_INTERNAL_OBSOLETE::V5_horizontal_alignment V5HorizontalAlignmentFromV5Justification(
    unsigned int v5_justification_bits
  );

  static ON_INTERNAL_OBSOLETE::V5_horizontal_alignment V5HorizontalAlignmentFromV6HorizontalAlignment(
    const ON::TextHorizontalAlignment text_horizontal_alignment
  );

  static ON::TextHorizontalAlignment V6HorizontalAlignmentFromV5HorizontalAlignment(
    ON_INTERNAL_OBSOLETE::V5_horizontal_alignment V5_vertical_alignment
  );
};

#endif

#endif
