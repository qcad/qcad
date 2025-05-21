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

#if !defined(ON_MESH_MODIFIERS_INC_)
#define ON_MESH_MODIFIERS_INC_

class ON_CLASS ON_MeshModifier
{
public:
  // Returns the plug-in id of the 'Displacement' plug-in which implements all the mesh modifiers.
  static ON_UUID PlugInId(void);

public:
  ON_MeshModifier();
  ON_MeshModifier(const ON_XMLNode& node);
  ON_MeshModifier(const ON_MeshModifier& mm) = delete;
  virtual ~ON_MeshModifier();

  const ON_MeshModifier& operator = (const ON_MeshModifier&) = delete;

  // Return the unique identifier of this mesh modifier.
  virtual ON_UUID Uuid(void) const = 0;

public: // For internal use only.
  virtual ON_XMLNode* AddChildXML(ON_XMLRootNode& root) const;

protected:
  class CImpl;
  CImpl* m_impl;
};

////////////////////////////////////////////////////////////////
//
// Displacement
//
////////////////////////////////////////////////////////////////

#define ON_DISPLACEMENT_ROOT                       L"new-displacement-object-data"
  #define ON_DISPLACEMENT_ON                         L"on"
  #define ON_DISPLACEMENT_CHANNEL                    L"channel"
  #define ON_DISPLACEMENT_BLACK_POINT                L"black-point"
  #define ON_DISPLACEMENT_WHITE_POINT                L"white-point"
  #define ON_DISPLACEMENT_SWEEP_PITCH                L"sweep-pitch"
  #define ON_DISPLACEMENT_REFINE_STEPS               L"refine-steps"
  #define ON_DISPLACEMENT_REFINE_SENSITIVITY         L"refine-sensitivity"
  #define ON_DISPLACEMENT_TEXTURE                    L"texture"
  #define ON_DISPLACEMENT_FACE_COUNT_LIMIT_ENABLED   L"face-count-limit-enabled"
  #define ON_DISPLACEMENT_FACE_COUNT_LIMIT           L"face-count-limit"
  #define ON_DISPLACEMENT_POST_WELD_ANGLE            L"post-weld-angle"
  #define ON_DISPLACEMENT_MESH_MEMORY_LIMIT          L"mesh-memory-limit"
  #define ON_DISPLACEMENT_FAIRING_ENABLED            L"fairing-enabled"
  #define ON_DISPLACEMENT_FAIRING_AMOUNT             L"fairing-amount"
  #define ON_DISPLACEMENT_SWEEP_RES_FORMULA          L"sweep-res-formula"
  #define ON_DISPLACEMENT_SUB_OBJECT_COUNT           L"sub-object-count"
  #define ON_DISPLACEMENT_SUB                        L"sub"
    #define ON_DISPLACEMENT_SUB_INDEX                  L"sub-index"
    #define ON_DISPLACEMENT_SUB_ON                     L"sub-on"
    #define ON_DISPLACEMENT_SUB_TEXTURE                L"sub-texture"
    #define ON_DISPLACEMENT_SUB_CHANNEL                L"sub-channel"
    #define ON_DISPLACEMENT_SUB_BLACK_POINT            L"sub-black-point"
    #define ON_DISPLACEMENT_SUB_WHITE_POINT            L"sub-white-point"

class ON_CLASS ON_DisplacementUserData : public ON_XMLUserData
{
private:
  ON_OBJECT_DECLARE(ON_DisplacementUserData);

public:
  ON_DisplacementUserData();
  ON_DisplacementUserData(const ON_DisplacementUserData& ud);

  static ON_UUID Uuid(void);

  const ON_DisplacementUserData& operator = (const ON_DisplacementUserData& ud);

  virtual bool GetDescription(ON_wString& s) override;
  virtual void SetToDefaults(void) const override;
  virtual void ReportVersionError(void) const override;
  virtual bool Transform(const ON_Xform& xform) override;
  virtual bool Read(ON_BinaryArchive&) override;
};

class ON_CLASS ON_Displacement : public ON_MeshModifier
{
public:
  ON_Displacement();
  ON_Displacement(const ON_XMLNode& node);
  ON_Displacement(const ON_Displacement& dsp);
  ~ON_Displacement();

  const ON_Displacement& operator = (const ON_Displacement& dsp);

  bool operator == (const ON_Displacement& dsp) const;
  bool operator != (const ON_Displacement& dsp) const;

  // Specifies whether the feature is enabled or not.
  bool On(void) const;
  void SetOn(bool b);

  // Specifies which texture is used for computing displacement amount
  ON_UUID Texture(void) const;
  void SetTexture(const ON_UUID& id);

  // Specifies which texture mapping channel is used for displacement texture
  int MappingChannel(void) const;
  void SetMappingChannel(int c);

  // Specifies the amount of displacement for the black color in the texture
  double BlackPoint(void) const;
  void SetBlackPoint(double b);

  // Specifies the amount of displacement for the white color in the texture
  double WhitePoint(void) const;
  void SetWhitePoint(double w);

  // Specifies how densely the object is initially subdivided.
  // The lower the value, the higher the resolution of the displaced mesh.
  int InitialQuality(void) const;
  void SetInitialQuality(int q);

  // Specifies whether to perform a mesh reduction as a post process to simplify the result of displacement
  bool FinalMaxFacesOn(void) const;
  void SetFinalMaxFacesOn(bool b);

  // Specifies how many faces the reduction post process should target to
  int FinalMaxFaces(void) const;
  void SetFinalMaxFaces(int f);

  // Specifies whether to perform a fairing step
  bool FairingOn(void) const;
  void SetFairingOn(bool b);

  // Specifies number of steps for fairing process. This straightens rough feature edges.
  int Fairing(void) const;
  void SetFairing(int f);

  // Specifies the maximum angle between face normals of adjacent faces
  // that will get welded together.
  double PostWeldAngle(void) const;
  void SetPostWeldAngle(double a);

  // Specifies in megabytes how much memory can be allocated for use by the displacement mesh.
  int MeshMemoryLimit(void) const;
  void SetMeshMemoryLimit(int l);

  // Specifies the number of refinement passes
  int RefineSteps(void) const;
  void SetRefineSteps(int s);

  // Specifies how sensitive the divider for contrasts is on the displacement texture.
  // Specify 1 to split all mesh edges on each refine step.
  // Specify 0.99 to make even slight contrasts on the displacement texture cause edges to be split.
  // Specifying 0.01 only splits edges where heavy contrast exists.
  double RefineSensitivity(void) const;
  void SetRefineSensitivity(double s);

  // Specifies which formula is used to calculate sweep resolution from initial quality.
  // Default = Default formula.
  // AbsoluteToleranceDependent = Formula used in Rhino 5. Dependent on absolute tolerance.
  enum class SweepResolutionFormulas : int { Default = 0, AbsoluteToleranceDependent = 1 };
  SweepResolutionFormulas SweepResolutionFormula(void) const;
  void SetSweepResolutionFormula(SweepResolutionFormulas f);

  // Sub-items can exist to override the top-level parameters for polysurface/SubD faces.
  class ON_CLASS SubItem final
  {
  public:
    SubItem(const ON_XMLNode& sub_node);
    SubItem(const SubItem&) = delete;
    ~SubItem();

    const SubItem& operator = (const SubItem& sub);

    bool operator == (const SubItem& sub) const;
    bool operator != (const SubItem& sub) const;

    // Returns the index of this sub-item.
    // When this is >= 0 it is the component index of the polysurface or SubD face.
    int FaceIndex(void) const;
    void SetFaceIndex(int i);

    // Overrides displacement 'on'.
    bool On(void) const;
    void SetOn(bool b);

    // Overrides displacement 'texture'.
    ON_UUID Texture(void) const;
    void SetTexture(const ON_UUID& id);

    // Overrides displacement 'mapping channel'.
    int MappingChannel(void) const;
    void SetMappingChannel(int c);

    // Overrides displacement 'black-point'.
    double BlackPoint(void) const;
    void SetBlackPoint(double b);

    // Overrides displacement 'white-point'.
    double WhitePoint(void) const;
    void SetWhitePoint(double w);

    // For internal use only.
    void ToXML(ON_XMLNode& node) const;

  private:
    class CImpl;
    CImpl* m_impl;
  };

  class ON_CLASS SubItemIterator final
  {
  public:
    SubItemIterator(const ON_Displacement& dsp);
    ~SubItemIterator();

    SubItem* Next(void);

  private:
    class CImpl;
    CImpl* m_impl;
  };

  SubItem& AddSubItem(void);
  void DeleteSubItem(int face_index);
  void DeleteAllSubItems(void);
  int  FindSubItemArrayIndex(int face_index) const;
  SubItem* FindSubItem(int face_index) const;
  SubItemIterator GetSubItemIterator(void) const;

  class ON_CLASS Defaults final
  {
  public:
    static int RefineStepCount(void);
    static int FairingAmount(void);
    static int FaceLimit(void);
    static int ChannelNumber(void);
    static int MeshMemoryLimit(void);
    static double BlackPoint(void);
    static double WhitePoint(void);
    static double SweepPitch(void);
    static double RefineSensitivity(void);
    static double PostWeldAngle(void);
    static double AbsoluteTolerance(void);
    static SweepResolutionFormulas SweepResolutionFormula(void);
  };

  virtual ON_UUID Uuid(void) const override;

public: // For internal use only.
  virtual ON_XMLNode* AddChildXML(ON_XMLRootNode& root) const override;

private:
  class CImplDSP;
  CImplDSP* m_impl_dsp;
};

////////////////////////////////////////////////////////////////
//
// Edge Softening
//
////////////////////////////////////////////////////////////////

#define ON_EDGE_SOFTENING_ROOT              L"edge-softening-object-data"
  #define ON_EDGE_SOFTENING_ON                L"on"
  #define ON_EDGE_SOFTENING_SOFTENING         L"softening"
  #define ON_EDGE_SOFTENING_CHAMFER           L"chamfer"
  #define ON_EDGE_SOFTENING_UNWELD            L"unweld"
  #define ON_EDGE_SOFTENING_FORCE_SOFTENING   L"force-softening"
  #define ON_EDGE_SOFTENING_EDGE_THRESHOLD    L"edge-threshold"

class ON_CLASS ON_EdgeSofteningUserData : public ON_XMLUserData
{
private:
  ON_OBJECT_DECLARE(ON_EdgeSofteningUserData);

public:
  ON_EdgeSofteningUserData();
  ON_EdgeSofteningUserData(const ON_EdgeSofteningUserData& ud);

  static ON_UUID Uuid(void);

  const ON_EdgeSofteningUserData& operator = (const ON_EdgeSofteningUserData& ud);

  virtual bool GetDescription(ON_wString& s) override;
  virtual void SetToDefaults(void) const override;
  virtual void ReportVersionError(void) const override;
};

class ON_CLASS ON_EdgeSoftening : public ON_MeshModifier
{
public:
  ON_EdgeSoftening();
  ON_EdgeSoftening(const ON_XMLNode& node);
  ON_EdgeSoftening(const ON_EdgeSoftening& es);

  const ON_EdgeSoftening& operator = (const ON_EdgeSoftening& es);

  bool operator == (const ON_EdgeSoftening& es) const;
  bool operator != (const ON_EdgeSoftening& es) const;

  // Specifies whether the feature is enabled or not.
  bool On(void) const;
  void SetOn(bool b);

  // The softening radius.
  double Softening(void) const;
  void SetSoftening(double d);

  // Specifies whether to chamfer the edges.
  bool Chamfer(void) const;
  void SetChamfer(bool b);

  // Specifies whether the edges are faceted.
  bool Faceted(void) const;
  void SetFaceted(bool b);

  // Threshold angle (in degrees) which controls whether an edge is softened or not.
  // The angle refers to the angles between the adjacent faces of an edge.
  double EdgeAngleThreshold(void) const;
  void SetEdgeAngleThreshold(double d);

  // Specifies whether to soften edges despite too large a radius.
  bool ForceSoftening(void) const;
  void SetForceSoftening(bool b);

  virtual ON_UUID Uuid(void) const override;

  class ON_CLASS Defaults final
  {
  public:
    static bool Chamfer(void);
    static bool Faceted(void);
    static bool ForceSoftening(void);
    static double Softening(void);
    static double EdgeAngleThreshold(void);
  };
};

////////////////////////////////////////////////////////////////
//
// Thickening
//
////////////////////////////////////////////////////////////////

#define ON_THICKENING_ROOT          L"thickening-object-data"
  #define ON_THICKENING_ON            L"on"
  #define ON_THICKENING_DISTANCE      L"distance"
  #define ON_THICKENING_SOLID         L"solid"
  #define ON_THICKENING_BOTH_SIDES    L"both-sides"
  #define ON_THICKENING_OFFSET_ONLY   L"offset-only"

class ON_CLASS ON_ThickeningUserData : public ON_XMLUserData
{
private:
  ON_OBJECT_DECLARE(ON_ThickeningUserData);

public:
  ON_ThickeningUserData();
  ON_ThickeningUserData(const ON_ThickeningUserData& ud);

  static ON_UUID Uuid(void);

  const ON_ThickeningUserData& operator = (const ON_ThickeningUserData& ud);

  virtual void SetToDefaults(void) const override;
  virtual bool GetDescription(ON_wString& s) override;
  virtual void ReportVersionError(void) const override;
  virtual bool Transform(const ON_Xform& xform) override;
};

class ON_CLASS ON_Thickening : public ON_MeshModifier
{
public:
  ON_Thickening();
  ON_Thickening(const ON_XMLNode& node);
  ON_Thickening(const ON_Thickening& t);

  const ON_Thickening& operator = (const ON_Thickening& t);

  bool operator == (const ON_Thickening& t) const;
  bool operator != (const ON_Thickening& t) const;

  // Specifies whether the feature is enabled or not.
  bool On(void) const;
  void SetOn(bool b);

  // Specifies how thick meshes will be made
  double Distance(void) const;
  void SetDistance(double d);

  // Specifies whether to make open meshes solid by adding walls when thickening
  bool Solid(void) const;
  void SetSolid(bool b);

  // Specifies whether to only offset the original surface
  bool OffsetOnly(void) const;
  void SetOffsetOnly(bool b);

  // Specifies whether to thicken to both sides of the surface
  bool BothSides(void) const;
  void SetBothSides(bool b);

  virtual ON_UUID Uuid(void) const override;

  class ON_CLASS Defaults final
  {
  public:
    static bool Solid(void);
    static bool BothSides(void);
    static bool OffsetOnly(void);
    static double Distance(void);
  };
};

#define ON_CURVE_PIPING_ROOT        L"curve-piping-object-data"
  #define ON_CURVE_PIPING_ON          L"on"
  #define ON_CURVE_PIPING_SEGMENTS    L"segments"
  #define ON_CURVE_PIPING_RADIUS      L"radius"
  #define ON_CURVE_PIPING_ACCURACY    L"accuracy"
  #define ON_CURVE_PIPING_WELD        L"weld"     // 'Weld' is a legacy name. The real name is 'Faceted' but this is the INVERSE of weld.
  #define ON_CURVE_PIPING_CAP_TYPE    L"cap-type"
    #define ON_CURVE_PIPING_NONE        L"none"
    #define ON_CURVE_PIPING_FLAT        L"flat"
    #define ON_CURVE_PIPING_BOX         L"box"
    #define ON_CURVE_PIPING_DOME        L"dome"

class ON_CLASS ON_CurvePipingUserData : public ON_XMLUserData
{
private:
	ON_OBJECT_DECLARE(ON_CurvePipingUserData);

public:
	ON_CurvePipingUserData();
	ON_CurvePipingUserData(const ON_CurvePipingUserData& ud);

	static ON_UUID Uuid(void);

	const ON_CurvePipingUserData& operator = (const ON_CurvePipingUserData& ud);

	virtual void SetToDefaults(void) const override;
	virtual bool GetDescription(ON_wString& s) override;
	virtual void ReportVersionError(void) const override;
	virtual bool Transform(const ON_Xform& xform) override;
};

class ON_CLASS ON_CurvePiping : public ON_MeshModifier
{
public:
  ON_CurvePiping();
  ON_CurvePiping(const ON_XMLNode& node);
  ON_CurvePiping(const ON_CurvePiping& cp);

  const ON_CurvePiping& operator = (const ON_CurvePiping& cp);

  bool operator == (const ON_CurvePiping& cp) const;
  bool operator != (const ON_CurvePiping& cp) const;

  // Specifies whether the feature is enabled or not.
  bool On(void) const;
  void SetOn(bool b);

  // Specifies the radius of the pipe (minimum value 0.0001).
  double Radius(void) const;
  void SetRadius(double d);

  // Specifies the number of segments in the pipe (minimum value 2).
  int Segments(void) const;
  void SetSegments(int s);

  // Specifies whether the pipe is faceted or not.
  bool Faceted(void) const;
  void SetFaceted(bool b);

  // Specifies the accuracy of the pipe in the range 0 to 100.
  int Accuracy(void) const;
  void SetAccuracy(int a);

  enum class CapTypes : int
  {
    None = 0, // No capping.
    Flat = 1, // A flat surface will cap the pipe.
    Box  = 2, // A simple construction will cap the pipe.
    Dome = 3, // A meridians-and-parallels hemisphere construction will cap the pipe.
  };

  // The type of cap to be created at the ends of the pipe.
  CapTypes CapType(void) const;
  void SetCapType(CapTypes ct);

  virtual ON_UUID Uuid(void) const override;

  class ON_CLASS Defaults final
  {
  public:
    static bool Faceted(void);
    static int Segments(void);
    static int Accuracy(void);
    static double Radius(void);
    static CapTypes CapType(void);
  };
};

#define ON_SHUTLINING_ROOT               L"shut-lining-object-data"
  #define ON_SHUTLINING_ON                 L"on"
  #define ON_SHUTLINING_FACETED            L"faceted"
  #define ON_SHUTLINING_AUTO_UPDATE        L"auto-update"
  #define ON_SHUTLINING_FORCE_UPDATE       L"force-update"
  #define ON_SHUTLINING_CURVE              L"curve"
    #define ON_SHUTLINING_CURVE_UUID         L"uuid"
    #define ON_SHUTLINING_CURVE_ENABLED      L"enabled"
    #define ON_SHUTLINING_CURVE_RADIUS       L"radius"
    #define ON_SHUTLINING_CURVE_PROFILE      L"profile"
    #define ON_SHUTLINING_CURVE_PULL         L"pull"
    #define ON_SHUTLINING_CURVE_IS_BUMP      L"is-bump"

class ON_CLASS ON_ShutLiningUserData : public ON_XMLUserData
{
private:
	ON_OBJECT_DECLARE(ON_ShutLiningUserData);

public:
	ON_ShutLiningUserData();
	ON_ShutLiningUserData(const ON_ShutLiningUserData& ud);

	static ON_UUID Uuid(void);

	const ON_ShutLiningUserData& operator = (const ON_ShutLiningUserData& ud);

	virtual void SetToDefaults(void) const override;
	virtual bool GetDescription(ON_wString& s) override;
	virtual void ReportVersionError(void) const override;
	virtual bool Transform(const ON_Xform& xform) override;
};

class ON_CLASS ON_ShutLining : public ON_MeshModifier
{
public:
  ON_ShutLining();
  ON_ShutLining(const ON_XMLNode& node);
  ON_ShutLining(const ON_ShutLining& sl);
  virtual ~ON_ShutLining();

  const ON_ShutLining& operator = (const ON_ShutLining& sl);

  bool operator == (const ON_ShutLining& sl) const;
  bool operator != (const ON_ShutLining& sl) const;

  // Specifies whether the feature is enabled or not.
  bool On(void) const;
  void SetOn(bool b);

  // Specifies whether the shut-lining is faceted or not.
  bool Faceted(void) const;
  void SetFaceted(bool b);

  // Specifies whether the shut-lining automatically updates or not.
  bool AutoUpdate(void) const;
  void SetAutoUpdate(bool b);

  // Specifies whether updating is forced or not.
  bool ForceUpdate(void) const;
  void SetForceUpdate(bool b);

  class ON_CLASS Curve final
  {
  public:
    Curve(const ON_XMLNode& curve_node);
    Curve(const Curve&) = delete;
    ~Curve();

    const Curve& operator = (const Curve& c);

    bool operator == (const Curve& c) const;
    bool operator != (const Curve& c) const;

    // Specifies the id of the curve object to use for a shut-line.
    ON_UUID Id(void) const;
    void SetId(const ON_UUID& id);

    // Specifies the radius of the pipe used to create the shut-line for this curve.
    double Radius(void) const;
    void SetRadius(double d);

    // Specifies the profile of the shut-line for this curve.
    int Profile(void) const;
    void SetProfile(int p);

    // Specifies whether shut-line is created for the this curve.
    bool Enabled(void) const;
    void SetEnabled(bool b);

    // Specifies whether this curve is pulled to the surface before creating the shut-line.
    bool Pull(void) const;
    void SetPull(bool b);

    // Specifies whether to create a bump instead of a dent for this curve.
    bool IsBump(void) const;
    void SetIsBump(bool b);

    class ON_CLASS Defaults final
    {
    public:
      static bool   Enabled(void);
      static bool   Pull(void);
      static bool   IsBump(void);
      static int    Profile(void);
      static double Radius(void);
    };

    // For internal use only.
    void ToXML(ON_XMLNode& node) const;

  private:
    class CImpl;
    CImpl* m_impl;
  };

  class ON_CLASS CurveIterator final
  {
  public:
    CurveIterator(const ON_ShutLining& sl);
    ~CurveIterator();

    Curve* Next(void);

  private:
    class CImpl;
    CImpl* m_impl;
  };

  // Adds a new curve to the shut-lining. The curve will have an id of ON_nil_uuid.
  // After adding a curve, you should set the id to that of a curve in the model
  // that will be used to calculate the shut-lining.
  Curve& AddCurve(void);

  // Deletes all the curves from the shut-lining.
  void DeleteAllCurves(void);

  // Finds a curve on the shut-lining by its id. Returns null if not found.
  Curve* FindCurve(const ON_UUID& id) const;

  // Gets an iterator for iterating over all the curves on the shut-lining.
  CurveIterator GetCurveIterator(void) const;

  virtual ON_UUID Uuid(void) const override;

  class ON_CLASS Defaults final
  {
  public:
    static bool Faceted(void);
    static bool AutoUpdate(void);
    static bool ForceUpdate(void);
    static double Tolerance(void);
  };

public: // For internal use only.
  virtual ON_XMLNode* AddChildXML(ON_XMLRootNode& root) const override;

private:
  class CImplSL;
  CImplSL* m_impl_sl;
};

class ON_CLASS ON_MeshModifiers final
{
public:
  ON_MeshModifiers();
  ON_MeshModifiers(const ON_MeshModifiers&) = delete;
  ~ON_MeshModifiers();

  bool operator == (const ON_MeshModifiers&) const = delete;
  bool operator != (const ON_MeshModifiers&) const = delete;

  const ON_MeshModifiers& operator = (const ON_MeshModifiers& mm);

  // Get an object that provides access to displacement information.
  // If there is no displacement information and 'allow_creation' is false, the method returns null.
  // If there is no displacement information and 'allow_creation' is true, a default displacement object is created.
  ON_Displacement* Displacement(bool allow_creation=false);

  // Get an object that provides access to edge softening information.
  // If there is no edge softening information and 'allow_creation' is false, the method returns null.
  // If there is no edge softening information and 'allow_creation' is true, a default edge softening object is created.
  ON_EdgeSoftening* EdgeSoftening(bool allow_creation=false);

  // Get an object that provides access to thickening information.
  // If there is no thickening information and 'allow_creation' is false, the method returns null.
  // If there is no thickening information and 'allow_creation' is true, a default thickening object is created.
  ON_Thickening* Thickening(bool allow_creation=false);

  // Get an object that provides access to curve piping information.
  // If there is no curve piping information and 'allow_creation' is false, the method returns null.
  // If there is no curve piping information and 'allow_creation' is true, a default curve piping object is created.
  ON_CurvePiping* CurvePiping(bool allow_creation=false);

  // Get an object that provides access to shut-lining information.
  // If there is no shut-lining information and 'allow_creation' is false, the method returns null.
  // If there is no shut-lining information and 'allow_creation' is true, a default shut-lining object is created.
  ON_ShutLining* ShutLining(bool allow_creation=false);

public: // For internal use only.
  void LoadFromXML(const ON_XMLRootNode&);

private:
  class CImpl;
  CImpl* m_impl;
};

#endif
