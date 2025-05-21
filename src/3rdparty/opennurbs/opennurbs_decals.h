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

#if !defined(ON_DECALS_INC_)
#define ON_DECALS_INC_

// Comment in this line to enable human-readable decal CRCs. One of the most difficult things about
// diagnosing decal bugs is not being able to get useful information from their CRCs. By enabling
// this feature, the decal CRC will change from being an integer to being a class with debug information
// in it. THIS BREAKS THE SDK SO ONLY USE IT FOR LOCAL DEBUGGING. NEVER CHECK THIS LINE IN WITH IT ENABLED.
//#define HUMAN_READABLE_DECAL_CRC

#ifndef _DEBUG
#ifdef HUMAN_READABLE_DECAL_CRC
#error "HUMAN_READABLE_DECAL_CRC is defined in release build"
#endif
#endif

#if (defined _DEBUG) && (defined HUMAN_READABLE_DECAL_CRC)
class ON_HumanReadableDecalCRC
{
public:
  ON_HumanReadableDecalCRC(ON__UINT32 v=0) : _value(v) { }

  void operator =  (ON__UINT32 v)              { _value =  v; }
  bool operator == (ON__UINT32 v) const { return _value == v; }
  bool operator != (ON__UINT32 v) const { return _value != v; }

  operator ON__UINT32(void) const { return _value; }

  operator const wchar_t*(void) const { return _info1; }

public:
  ON__UINT32 _value = 0;
  ON_wString _info1;
  ON_wString _info2;
};
#define ON_DECAL_CRC  ON_HumanReadableDecalCRC
#else
#define ON_DECAL_CRC  ON__UINT32
#endif

#define ON_NIL_DECAL_CRC  ON_DECAL_CRC(0) // If a decal CRC is nil, it means 'no decal'.

// ON_Decal encapsulates a rendering decal which is an image that sticks to the surface of an object
// like a real-life decal does. Decals are identified by their CRC which is a value generated from the
// decal's current state. When a property changes, the CRC will also change.
//
// Decals have a choice of mappings:
//
// - UV:          Maps a texture to (u,v) coordinates on an object.
// - Planar:      Maps a texture to a rectangle like an ordinary sticker.
// - Spherical:   Maps a texture to a spherical object like a label on a ball.
// - Cylindrical: Maps a texture to a cylinder like a label on a can.
//
// They also have a choice of projections:
//
// - Forward:  Projects the decal forward onto the object.
// - Backward: Projects the decal backward onto the object.
// - Both:     Projects the decal forward and backward onto the object.
//
// Some of the properties are only used by certain mappings:
//
// - UV bounds:        UV mapping only.
// - Transparency:     All mappings.
// - Origin:           All mappings except UV.
// - Up vector:        All mappings except UV.
// - Across vector:    All mappings except UV.
// - Height:           Cylindrical mapping only.
// - Map to inside:    Cylindrical and spherical mappings only.
// - Radius:           Cylindrical and spherical mappings only.
// - Horizontal sweep: Cylindrical and spherical mappings only.
// - Vertical sweep:   Spherical mapping only.
//
// The class stores its data as XML but it is optimized with a built-in cache. As each property is
// requested, it is read from the XML and cached. Thereafter, the cached value is returned and the XML
// for that property is never read again. On writing to a property, the cache is updated and by default
// the XML is also updated. However, it is possible to inhibit the XML update for increased performance.
// See SetCacheOnly() below.

class ON_CLASS ON_Decal
{
public:
  // Construct a decal with all properties set to defaults.
  ON_Decal();

  // Construct a decal passing the XML node to be used for its storage.
  ON_Decal(ON_XMLNode& node);

  // Construct a decal passing the const XML node to be used for its storage. This decal is read only.
  ON_Decal(const ON_XMLNode& node);

  ON_Decal(class ON_DecalCollection& coll, ON_XMLNode& node); // For internal use only.

  // Construct this decal as a copy of another decal.
  ON_Decal(const ON_Decal& other);

  virtual ~ON_Decal();

  virtual const ON_Decal& operator = (const ON_Decal& d);

  virtual bool operator == (const ON_Decal& d) const;
  virtual bool operator != (const ON_Decal& d) const;

  enum class Mappings : ON__INT32
  {
    None        = -1,
    Planar      =  0, // Planar mapping. Uses projection, origin, up and across vectors (not unitized).
    Cylindrical =  1, // Cylindrical mapping. Uses origin, up, across, height, radius, horz-sweep.
    Spherical   =  2, // Spherical mapping. Uses origin, up, across, radius, horz-sweep, vert-sweep.
    UV          =  3, // UV mapping. Uses UV bounds.
  };

  enum class Projections : ON__INT32
  {
    None     = -1,
    Forward  =  0, // Project forward.
    Backward =  1, // Project backward.
    Both     =  2, // Project forward and backward.
  };

  // Returns the decal texture's instance id.
  ON_UUID TextureInstanceId(void) const;

  // Sets the decal texture's instance id.
  void SetTextureInstanceId(const ON_UUID& id);

  // Returns the decal's mapping.
  Mappings Mapping(void) const;

  // Sets the decal's mapping.
  void SetMapping(Mappings m);

  // Returns the decal's projection. Used only when mapping is planar.
  Projections Projection(void) const;

  // Sets the decal's projection. Used only when mapping is planar.
  void SetProjection(Projections p);

  // Returns true if the texture is mapped to inside of sphere or cylinder, else false.
  // Used only when mapping is cylindrical or spherical.
  bool MapToInside(void) const;

  // Sets if the texture is mapped to inside of sphere or cylinder.
  // Used only when mapping is cylindrical or spherical.
  void SetMapToInside(bool b);

  // Returns the decal's transparency in the range 0..1.
  double Transparency(void) const;

  // Sets the decal's transparency (clamped to the range 0..1).
  void SetTransparency(double d);

  // Returns the origin of the decal in world space. Not used when the mapping is UV.
  ON_3dPoint Origin(void) const;

  // Sets the origin of the decal in world space. Not used when the mapping is UV.
  void SetOrigin(const ON_3dPoint& pt);

  // Returns the 'up' vector of the decal. For planar mapping the length of the vector is relevant.
  // Not used when the mapping is UV. For cylindrical and spherical mapping, the vector is unitized.
  ON_3dVector VectorUp(void) const;

  // Sets the 'up' vector of the decal. Not used when the mapping is UV.
  void SetVectorUp(const ON_3dVector& vec);

  // Returns the 'across' vector of the decal. For planar mapping the length of the vector is relevant.
  // Not used when the mapping is UV.
  // For cylindrical and spherical mapping, the vector is unitized.
  ON_3dVector VectorAcross(void) const;

  // Sets the 'across' vector of the decal. Not used when the mapping is UV.
  void SetVectorAcross(const ON_3dVector& vec);

  // Returns the height of the decal. Only used when mapping is cylindrical.
  double Height(void) const;

  // Sets the height of the decal. Only used when mapping is cylindrical.
  void SetHeight(double d);

  // Returns the radius of the decal. Only used when mapping is cylindrical or spherical.
  double Radius(void) const;

  // Sets the radius of the decal. Only used when mapping is cylindrical or spherical.
  void SetRadius(double d);

  // Gets the start and end angles of the decal's 'horizontal sweep' (these are angles of longitude in radians).
  // Only used when mapping is cylindrical or spherical.
  void GetHorzSweep(double& sta, double& end) const;

  // Sets the start and end angles of the decal's 'horizontal sweep' (these are angles of longitude in radians).
  // Only used when mapping is cylindrical or spherical.
  void SetHorzSweep(double sta, double end);

  // Gets the start and end angles of the decal's 'vertical sweep' (these are angles of latitude in radians).
  // Only used when mapping is spherical.
  void GetVertSweep(double& sta, double& end) const;

  // Sets the start and end angles of the decal's 'vertical sweep' (these are angles of latitude in radians).
  // Only used when mapping is spherical.
  void SetVertSweep(double sta, double end);

  // Returns the UV bounds of the decal. Only used when mapping is UV.
  void GetUVBounds(double& min_u, double& min_v, double& max_u, double& max_v) const;

  // Sets the UV bounds of the decal. Only used when mapping is UV.
  void SetUVBounds(double min_u, double min_v, double max_u, double max_v);

  // Gets a texture mapping based on the properties of this decal. Only works and returns true if
  // the decal mapping is Planar, Spherical or Cylindrical. Otherwise returns false.
  bool GetTextureMapping(ON_TextureMapping& tm) const;

  // Returns the Decal CRC of the decal.
  ON_DECAL_CRC DecalCRC(void) const;

  // Returns the Data CRC of the decal. This is not necessarily the same as the decal CRC
  // because it allows a starting current remainder.
  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;

  // Returns true if the decal is visible in the rendering.
  bool IsVisible(void) const;

  // Sets whether or not the decal is visible in the rendering.
  void SetIsVisible(bool visible);

  // Returns the unique id of the decal. This is a run-time id that is not persistent and is
  // only used for looking decals up in the model.
  ON_UUID Id(void) const;

  // Get the custom XML for the specified render engine. The format of the XML is described below.
  void GetCustomXML(const ON_UUID& renderEngineId, ON_XMLNode& custom_param_node) const;

  // Set the custom XML for the specified render engine. This XML should have the following format:
  //
  //  <parameters>
  //    <param-name type="type"></param-name>
  //    ...
  //  </parameters>
  //
  // Therefore 'custom_param_node' must have a tag name of "<parameters>". The easiest way to produce
  // such XML is by using ON_XMLParameters.
  bool SetCustomXML(const ON_UUID& renderEngineId, const ON_XMLNode& custom_param_node);

public: // For internal use only.
  static ON_DECAL_CRC ComputeDecalCRC(ON__UINT32, const ON_XMLNode&);
  void GetEntireCustomXML(ON_XMLNode&) const;
  void AppendCustomXML(const ON_XMLNode&);

private:
  class CImpl;
  CImpl* _impl;
};

// For internal use only.
ON_DECAL_CRC ON_DECL ON_DecalCRCFromNode(const ON_XMLNode& node);

#endif
