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

////////////////////////////////////////////////////////////////
//
//   Definition of subdivision surface
//
////////////////////////////////////////////////////////////////

#if !defined(OPENNURBS_SUBD_INC_)
#define OPENNURBS_SUBD_INC_

/// <summary>
/// ON_SubDGetControlNetMeshPriority specifies what type of ON_SubD information
/// is most important to transfer to the ON_Mesh.
/// </summary>
enum class ON_SubDGetControlNetMeshPriority : unsigned char
{
  ///<summary>
  /// Create a mesh that can be used to reliably transfer SubD control net geometry, 
  /// topology, and interior edge crease information. Use this option when the mesh 
  /// will be used to create a Catmull-Clark subdivision surface. SubD texture 
  /// coordinates cannot be recovered from the mesh.
  ///</summary>
  Geometry = 0,

  ///<summary>
  /// Create a mesh that has the shape of the SubD control net and
  /// includes SubD texture coordinate information.
  /// Use this option when the mesh will be used to create an image of the
  /// SubD control net that relies on texture coordinates. SubD interior edge
  /// crease information cannot be recovered from the mesh. Most applications will 
  /// not be able to use the mesh to recreate a Catmull-Clark subdivision surface.
  ///</summary>
  TextureCoordinates = 1
};


/// <summary>
/// ON_SubDTextureCoordinateType identifies the way ON_SubDMeshFragment texture coordinates are set from an ON_SubDFace.
/// </summary>
enum class ON_SubDTextureCoordinateType : unsigned char
{
  ///<summary>
  /// Texture domains are not set.
  ///</summary>
  Unset = 0,

  ///<summary>
  /// Each SubDFace uses the unit square in texture space.
  ///</summary>
  Unpacked = 1,

  ///<summary>
  /// The face's pack rect is used to set fragment texture coordinates.
  /// When possible, adjacent quads with the same ON_SubDFace::PackId() value are assigned adjacent 
  /// rectangles in texture space.
  ///</summary>
  Packed = 2,

  ///<summary>
  /// All ON_SubDMeshFragment texture coordinate values are zero.
  ///</summary>
  Zero = 3,

  ///<summary>
  /// All ON_SubDMeshFragment texture coordinate values are ON_DBL_QNAN.
  ///</summary>
  Nan = 4,

  ///<summary>
  /// All ON_SubDMeshFragment texture coordinate values are set by
  /// barycentric interpolation of ON_SubDFace.TexturePoint() values.
  ///</summary>
  FromFaceTexturePoints = 6,

  ///<summary>
  /// Texture coordinates are set from an ON_TextureMapping and transformation specified
  /// by ON_SubD::TextureMappingTag(). In all other cases, ON_SubD::TextureMappingTag()
  /// can be set, but is ignored.
  ///</summary>
  FromMapping = 7,
};

#pragma region RH_C_SHARED_ENUM [ON_SubDVertexTag] [Rhino.Geometry.SubDVertexTag] [byte]
/// <summary>
/// ON_SubDVertexTag identifies the type of subdivision vertex.  Different tags use
/// different subdivision algorithms to determine where the subdivision point and
/// limit point are located.  There are topological constraints that restrict which
/// tags can be assigned.
/// </summary>
enum class ON_SubDVertexTag : unsigned char
{
  ///<summary>
  /// Not a valid vertex tag and the default value for ON_SubDVertex.m_vertex_tag.
  /// This encourages developers to thoughtfully initialize ON_SubDVertex.m_vertex_tag
  /// or use ON_SubD.UpdateAllTagsAndSectorCoefficients() to automatically set the
  /// m_vertex_tag values at an appropriate time.
  ///</summary>
  Unset = 0,

  ///<summary>
  /// Must be an interior vertex.
  /// All edges attached to a smooth vertex must be tagged as ON_SubDEdgeTag::Smooth
  /// and must have 2 faces. 
  ///</summary>
  Smooth = 1,

  ///<summary>
  /// Can be an interior or a boundary vertex.
  /// Exactly two edges ending at a crease vertex must be tagged as ON_SubDEdgeTag::Crease and may
  /// have 1 or 2 faces. 
  /// All other edges ending at a crease must be tagged as tagON_SubD::EdgeTag::Smooth and have 2 faces.
  /// Below P = ON_SubDVertex.ControlNetPoint() and Ai = ON_SubDVertex.Edge(i)->OtherEndVertex()->ControlNetPoint().
  /// A crease vertex subdivision point is (6*P + A1 + A2)/8.
  /// A crease vertex limit surface point is (4*P + A1 + A2)/6.
  ///</summary>
  Crease = 2,

  ///<summary>
  /// Can be an interior, boundary, nonmanifold, or isolated vertex.
  /// The location of a corner vertex is fixed. 
  /// The all subdivision points and the limit point are at the initial vertex location.
  /// The edges ending at a corner vertex can be smooth or crease edges.
  /// A corner vertex subdivision point is P where P = ON_SubDVertex.ControlNetPoint().
  /// A corner vertex limit surface point is P where P = ON_SubDVertex.ControlNetPoint().
  ///</summary>
  Corner = 3,

  ///<summary>
  /// Must be an interior vertex.  
  /// Every edge attached to a dart vertex must have 2 faces.
  /// Exactly one edge attached to a dart vertex must be tagged as ON_SubDEdgeTag::Crease
  /// and every other attached edge must be tagged as ON_SubDEdgeTag::smooth.
  ///</summary>
  Dart = 4
};
#pragma endregion

#pragma region RH_C_SHARED_ENUM [ON_SubDEdgeTag] [Rhino.Geometry.SubDEdgeTag] [byte]
/// <summary>
/// ON_SubDEdgeTag identifies the type of subdivision edge.  Different tags use
/// different subdivision algorithms to calculate the subdivision point.
/// </summary>  
enum class ON_SubDEdgeTag : unsigned char
{
  ///<summary>
  /// Not a valid edge tag and the default value for ON_SubDEdge.m_edge_tag.
  /// This encourages developers to thoughtfully initialize ON_SubDEdge.m_edge_tag.
  /// or use ON_SubD.UpdateAllTagsAndSectorCoefficients() to automatically set the
  /// m_edge_tag values at an appropriate time.
  ///</summary>
  Unset = 0,

  ///<summary>
  /// At least one the edge's vertices must be tagged as ON_SubDVertexTag::Smooth.
  /// The edge must have exactly two faces.
  /// The edge's subdivision point is (A1 + A2 + S(f1) + S(f2))/4, where 
  /// Ai = ON_SubDEdge.Vertex(i)->ControlNetPoint() and
  /// S(fi) = ON_SubDEdge.Face(i)->SubdivisionPoint().
  ///</summary>
  Smooth = 1,

  ///<summary>
  /// Both of the edge's vertices must be tagged as ON_SubDVertexTag::Dart,
  /// ON_SubDVertexTag::Crease, or ON_SubDVertexTag::Corner. 
  /// (The vertex tags can be different.) The edge can have any number of faces.
  /// The edge's subdivision point is (A1+A2)/2 where Ai = ON_SubDEdge.Vertex(i)->ControlNetPoint().
  ///</summary>
  Crease = 2,

  ///<summary>
  /// This tag appears only on level 0 edges that have exactly two neighboring faces
  /// and both of the edge's vertices are tagged as ON_SubDVertexTag::Dart,
  /// ON_SubDVertexTag::Crease, or ON_SubDVertexTag::Corner.
  /// The level 1 subdivision point for a level 0 edge tagged as ON_SubDEdgeTag::SmoothX 
  /// is the standard smooth edge subdivision point.
  /// When subdivided, the new subdivision vertex will be tagged
  /// as ON_SubDVertexTag::Smooth and the subdivided edges will
  /// be tagged as ON_SubDEdgeTag::Smooth.  
  /// The tag ON_SubDEdgeTag::SmoothX can only appear on a level 0 edge.
  /// This tag exists because the ON_SubD subdivision
  /// algorithm requires any edge with both end vertices
  /// tagged as not smooth must be subdivided at its midpoint.
  /// Sector iterators treat "SmoothX" edges as smooth.
  /// Both edge m_sector_coefficient[] values must be set so the smooth subdivided edges will be valid.
  ///</summary>
  SmoothX = 4
};
#pragma endregion

#pragma region RH_C_SHARED_ENUM [ON_SubDEdgeType] [Rhino.Geometry.SubDEdgeType] [byte]
/// <summary>
/// ON_SubDEdgeType describes a subdivision edge. 
/// ON_SubDEdgeType is typically used when generating text descriptions
/// or filtering edges during selection processes. 
/// Do not confuse ON_SubDEdgeType and ON_SubDEdgeTag.
/// The unique types are single bits and suitable for use in bitwise logic.
/// </summary>  
enum class ON_SubDEdgeType : unsigned char
{
  ///<summary>
  /// Type is unset or the edge is not valid.
  ///</summary>
  Unset = 0,

  ///<summary>
  /// The edge has zero faces and the tag is ON_SubDEdgeTag::Crease.
  ///</summary>
  Wire = 1,

  ///<summary>
  /// The edge has one face and the tag is ON_SubDEdgeTag::Crease.
  ///</summary>
  Boundary = 2,

  ///<summary>
  /// The edge has two faces, 
  /// the tag is ON_SubDEdgeTag::Smooth or ON_SubDEdgeTag::SmoothX,
  /// and the edge sharpness is zero. 
  /// Note that ON_SubEdge::IsSmoothNotSharp() returns true if and only if ON_SubEdge::EdgeType() is InteriorSmooth.
  ///</summary>
  InteriorSmooth = 4,

  ///<summary>
  /// The edge has two faces, 
  /// the tag is ON_SubDEdgeTag::Smooth or ON_SubDEdgeTag::SmoothX,
  /// and the edge sharpness is nonzero.
  /// Note that ON_SubEdge::IsSharp() returns true if and only if ON_SubEdge::EdgeType() is InteriorSharp.
  ///</summary>
  InteriorSharp = 8,

  ///<summary>
  /// The edge has two faces and the tag is ON_SubDEdgeTag::Crease.
  ///</summary>
  InteriorCrease = 16,

  ///<summary>
  /// The edge has three or more faces and the tag is ON_SubDEdgeTag::Crease.
  ///</summary>
  Nonmanifold = 32,

  ///<summary>
  /// The edge has an invalid combination of face count, tag, and sharpness properties.
  ///</summary>
  Invalid = 64,

  ///<summary>
  /// A mask for all interior edge types. Interior edges have 2 faces.
  ///</summary>
  InteriorMask = 28,

  ///<summary>
  /// A mask for all valid edge types.
  ///</summary>
  ValidTypesMask = 63
};
#pragma endregion

#pragma region RH_C_SHARED_ENUM [ON_SubDHashType] [Rhino.Geometry.SubDHashType] [byte]
/// <summary>
/// ON_SubDHashType used used to specify what type of SubD information is hashed (topology or geometry).
/// </summary>
enum class ON_SubDHashType : unsigned char
{
  /// <summary>
  /// Unset indicates the hash type still needs to be selected. It is not a valid type
  /// for calculating a hash.
  /// </summary>
  Unset = 0,

  /// <summary>
  /// The Topology hash includes component ids, and all topological relationships 
  /// between vertices, edges, and faces. If two SubDs have the same topology hash,
  /// then the the have identical labeled control net topology.
  /// </summary>
  Topology = 3,

  /// <summary>
  /// The TopologyAndEdgeCreases includes all information in a Topology hash.
  /// The TopologyAndEdgeCreases adds edge crease/smooth attributes.
  /// Many contexts, including face packing and exploding, take edge creases
  /// into account when partitioning a SubD into regions.
  /// </summary>
  TopologyAndEdgeCreases = 1,

  /// <summary>
  /// A geometry hash includes all information in a TopologyAndEdgeCreases hash.
  /// The Geometry hash adds vertex tags, vertex control net points, 
  /// and nonzero subdivision displacements on vertices, edges, and faces.
  /// If two SubDs have the same geometry hash, then they have identical surface geometry.
  /// </summary>
  Geometry = 2
};
#pragma endregion

ON_DECL
ON_SubDHashType ON_SubDHashTypeFromUnsigned(
  unsigned int subd_hash_type_as_unsigned
);

ON_DECL
const ON_wString ON_SubDHashTypeToString(
  ON_SubDHashType subd_hash_type,
  bool bVerbose
);

/// <summary>
/// ON_SubDHash provides a simple way to save a SubD's vertex, edge, and face SHA1 hashes.
/// Typically it is used when a calculation needs to know if the current SubD has is geometrically
/// identical to a previous SubD. When speed is not important, comparing the current value of
/// ON_SubD::GeometryHash() to a previously save value of ON_SubD::GeometryHash() is functionally
/// identical but typically much slower when the SubDs are different.
/// </summary>
class ON_CLASS ON_SubDEdgeSharpness
{
public:
  ON_SubDEdgeSharpness() = default;
  ~ON_SubDEdgeSharpness() = default;
  ON_SubDEdgeSharpness(const ON_SubDEdgeSharpness&) = default;
  ON_SubDEdgeSharpness& operator=(const ON_SubDEdgeSharpness&) = default;

public:
  /// <summary>
  /// ON_SubDEdgeSharpness::MaximumValue = 4.
  /// SubD edge sharpness values are &lt;= ON_SubDEdgeSharpness::MaximumValue.
  /// </summary>
  static const double MaximumValue;

  /// <summary>
  /// ON_SubDEdgeSharpness::SmoothValue = 0.0.
  /// Valid SubD edge sharpness values are &lt;= ON_SubDEdgeSharpness::MaximumValue.
  /// Smooth edges have a sharpness property of ON_SubDEdgeSharpness::Smooth.
  /// </summary>
  static const double SmoothValue;

  /// <summary>
  /// ON_SubDEdgeSharpness::CreaseValue = ON_SubDEdgeSharpness::MaximumValue + 1.
  /// Valid SubD edge sharpness values are &lt;= ON_SubDEdgeSharpness::MaximumValue.
  /// This value is used when it is convenient to use and ON_SubDEdgeSharpness to
  /// indicate an edge has a crease tag. Edges with crease tags always have a 
  /// sharpness property of ON_SubDEdgeSharpness::Smooth.
  /// </summary>
  static const double CreaseValue;

  /// <summary>
  /// ON_SubDEdgeSharpness::Tolerance = 0.01
  /// If an edge has sharpness within ON_SubDEdgeSharpness::Tolerance of an integer value,
  /// the sharpness is set to that integer value.
  /// </summary>
  static const double Tolerance;

  /// <summary>
  /// An edge sharpness with constant value 0.0.
  /// </summary>
  static const ON_SubDEdgeSharpness Smooth;


  /// <summary>
  /// An edge sharpness with constant value ON_SubDEdgeSharpness::MaximumValue.
  /// This is the maximum sharpness that can be applied to an edge.
  /// </summary>
  static const ON_SubDEdgeSharpness Maximum;

  /// <summary>
  /// An edge sharpness with both end values = ON_SubDEdgeSharpness::CreaseValue.
  /// This value is not a valid sharpness value for a sharp edge 
  /// (A sharp edge a smooth edge with nonzero sharpness).
  /// When working with edges, it is sometimes convenient to have
  /// an ON_SubDEdgeSharpness value that indicated the edge is a crease. 
  /// ON_SubDEdgeSharpness::Crease is used for this purpose.
  /// </summary>
  static const ON_SubDEdgeSharpness Crease;

  /// <summary>
  /// An edge sharpness with both end values = ON_DBL_QNAN.
  /// </summary>
  static const ON_SubDEdgeSharpness Nan;

  /// <summary>
  /// Create a text string describing the sharpness as a percentage.
  /// If the sharpness is constant, and single percentage is returned.
  /// If the sharpness is variable, percentage range returned.
  /// If the sharpness is not valid, a warning sign is returned.
  /// </summary>
  /// <param name="bOrderMinToMax">
  /// If the sharpness is not constant and bOrderMinToMax is true, then
  /// the string has the format min%-max%. 
  /// If the sharpness is not constant and bOrderMinToMax is false, then
  /// the string has the format EndSharpness(0)%-EndSharpness(1)%. 
  /// </param>
  /// <returns>A string describing the sharpness as a percentage range.</returns>
  const ON_wString ToPercentageText(bool bOrderMinToMax) const;

  /// <summary>
  /// Create a text string describing the sharpness as a percentage.
  /// This is useful in user interface code that expresses sharpness in percentages.
  /// If 0 &lt;= sharpness &lt;= ON_SubDEdgeSharpness::MaximumValue,
  /// valid, a number followed by a percent sign is returned.
  /// If sharpness = ON_SubDEdgeSharpness::CreaseValue, "crease" is returned.
  /// If the sharpness is not valid, a warning sign is returned.
  /// </summary>
  /// <param name="sharpness"></param>
  /// <returns></returns>
  static const ON_wString ToPercentageText(double sharpness);

  /// <summary>
  /// Convert sharpness to a percentage from 0 to 100.0.
  /// This is useful in user interface code that experesses sharpness in percentages.
  /// </summary>
  /// <param name="sharpness"></param>
  /// <param name="crease_percentage"></param>
  /// <returns>
  /// If 0 &lt;= sharpness &lt;= ON_SubDEdgeSharpness::MaximumValue, then 100.0*sharpness/ON_SubDEdgeSharpness::MaximumValue is returned.
  /// If sharpness = ON_SubDEdgeSharpness::CreaseValue, then crease_percentage is returned.
  /// Otherwise ON_DBL_QNAN is returned.
  /// </returns>
  static double ToPercentage(double sharpness, double crease_percentage);

  /// <returns>
  /// If the sharpness value is valid and contant, returns true.
  /// Otherwise returns false.
  /// Note that ON_SubDEdgeSharpness::Crease.IsConstant() and ON_SubDEdgeSharpness::Nan.IsConstant() are both false.
  ///</returns>
  bool IsConstant() const;

  /// <param name="bCreaseResult">
  /// Value to return when this is equal to ON_SubDEdgeSharpness::Crease.
  /// </param>
  /// <returns>
  /// If this is equal to ON_SubDEdgeSharpness::Crease, returns bCreaseResult.
  /// If the sharpness value is valid and contant, returns true.
  /// Otherwise returns false.
  /// </returns>
  bool IsConstant( bool bCreaseResult ) const;

  /// <returns>
  /// If EndSharpness(0) &gt; EndSharpness(1), true is returned.
  /// Otherwise false is returned.
  /// </returns>
  bool IsIncreasing() const;

  /// <returns>
  /// If EndSharpness(0) &lt; EndSharpness(1), true is returned.
  /// Otherwise false is returned.
  /// </returns>
  bool IsDecreasing() const;

  /// <returns>
  /// True if the sharpness value is valid and variable.
  /// Note that ON_SubDEdgeSharpness::Crease.IsVariable() and ON_SubDEdgeSharpness::Nan.IsVariable() are both false.
  /// </returns>
  bool IsVariable() const;

  /// <returns>
  /// If EndSharpness(0) &lt; EndSharpness(1), +1 is returned.
  /// If EndSharpness(0) &gt; EndSharpness(1), -1 is returned.
  /// If EndSharpness(0) = EndSharpness(1), 0 is returned.
  /// Otherwise ON_UNSET_INT_INDEX is returned.
  /// </returns>
  int Trend() const;

  /// <returns>
  /// If IsValid() or IsCrease() is true, then EndSharpness(1) - EndSharpness(0) is returned.
  /// Otherwise ON_DBL_QNAN is returned.
  /// </returns>
  double Delta() const;

  /// Determine if sharpnesses have equal adjacent end sharpness values.
  /// <param name="s0"></param>
  /// <param name="s1"></param>
  /// <returns>
  /// If s0.EndSharpness(1) == s1.EndSharpness(0), then true is returned.
  /// Otherwise false is returned.
  /// </returns>
  static bool EqualEndSharpness(
    ON_SubDEdgeSharpness s0,
    ON_SubDEdgeSharpness s1
  );

  /// Determine if sharpnesses have the same trend and equal adjacent end sharpness values.
  /// <param name="s0"></param>
  /// <param name="s1"></param>
  /// <returns>
  /// If s0.Trend() = s1.Trend() and s0.EndSharpness(1) == s1.EndSharpness(0), then true is returned.
  /// Otherwise false is returned.
  /// </returns>
  static bool EqualTrend(
    ON_SubDEdgeSharpness s0,
    ON_SubDEdgeSharpness s1
  );


  /// Determine if sharpnesses have the same delta and equal adjacent end sharpness values.
  /// <param name="s0"></param>
  /// <param name="s1"></param>
  /// <returns>
  /// If s0.Delta() = s1.Delta() and s0.EndSharpness(1) == s1.EndSharpness(0), then true is returned.
  /// Otherwise false is returned.
  /// </returns>
  static bool EqualDelta(
    ON_SubDEdgeSharpness s0,
    ON_SubDEdgeSharpness s1
  );


  /// <summary>
  /// Determine if edges are adjacent and have equal adjacent sharpness values.
  /// </summary>
  /// <param name="eptr0"></param>
  /// <param name="eptr1"></param>
  /// <returns>
  /// If the edges have the same tag, eptr0.RelativeVertex(1) = eptr1.RelativeVertex(0), and
  /// then ON_SubDEdgeSharpness::EqualEndSharpness(eptr0.RelativeSharpness(),eptr1.RelativeSharpness()) is returned.
  /// Otherwise false is returned.
  /// </returns>
  static bool EqualEndSharpness(
    const class ON_SubDEdgePtr& eptr0,
    const class ON_SubDEdgePtr& eptr1
  );

  /// <summary>
  /// Determine if edges are adjacent, have the same sharpness trend, and equal adjacent sharpness values.
  /// </summary>
  /// <param name="eptr0"></param>
  /// <param name="eptr1"></param>
  /// <returns>
  /// If the edges have the same tag, eptr0.RelativeVertex(1) = eptr1.RelativeVertex(0), and
  /// then ON_SubDEdgeSharpness::EqualTrend(eptr0.RelativeSharpness(),eptr1.RelativeSharpness()) is returned.
  /// Otherwise false is returned.
  /// </returns>
  static bool EqualTrend(
    const class ON_SubDEdgePtr& eptr0,
    const class ON_SubDEdgePtr& eptr1
  );

  /// <summary>
  /// Determine if edges are adjacent, have the same sharpness trend, and equal adjacent sharpness values.
  /// </summary>
  /// <param name="eptr0"></param>
  /// <param name="eptr1"></param>
  /// <returns>
  /// If the edges have the same tag, eptr0.RelativeVertex(1) = eptr1.RelativeVertex(0), and
  /// then ON_SubDEdgeSharpness::EqualDelta(eptr0.RelativeSharpness(),eptr1.RelativeSharpness()) is returned.
  /// Otherwise false is returned.
  /// </returns>
  static bool EqualDelta(
    const class ON_SubDEdgePtr& eptr0,
    const class ON_SubDEdgePtr& eptr1
  );


  /// <summary>
  /// Determine if all the input edges have idential constant sharpeness.
  /// </summary>
  /// <param name="edges"></param>
  /// <param name="bCreaseResult">
  /// Result to return if all the edges are creases.
  /// </param>
  /// <returns>True if all edges have identical constant sharpness.</returns>
  static bool IsConstant(
    const ON_SimpleArray<ON_SubDEdgePtr>& edges,
    bool bCreaseResult
  );

  /// <summary>
  /// Determine if all the input edges have idential constant sharpeness.
  /// </summary>
  /// <param name="edge_count"></param>
  /// <param name="edges"></param>
  /// <param name="bCreaseResult">
  /// Result to return if all the edges are creases.
  /// </param>
  /// <returns>True if all edges have identical constant sharpness.</returns>
  static bool IsConstant(
    size_t edge_count,
    const ON_SubDEdgePtr* edges,
    bool bCreaseResult
  );

  /// <returns>True if the sharpness is zero.</returns>
  bool IsZero() const;

  /// <returns>
  /// If both end sharpness values are &gt;= 0 and &lt;= ON_SubDEdgeSharpness::MaximumValue
  /// and at least one end sharpness value is &gt; 0, returns true.
  /// Otherwise returns false.
  /// Note that ON_SubDEdgeSharpness::Crease.IsSharp() and ON_SubDEdgeSharpness::Nan.IsSharp() are both false;
  /// </returns>
  bool IsSharp() const;

  /// <returns>
  /// If the sharpness value is (ON_SubDEdgeSharpness::CreaseValue,ON_SubDEdgeSharpness::CreaseValue), returns true.
  /// Otherwise false is returned.
  /// In particular, ON_SubDEdgeSharpness::Crease.IsCrease() is true and all other values return false.
  /// </returns>
  bool IsCrease() const;


  /// <returns>
  /// (IsCrease() || IsSharp())
  /// </returns>
  bool IsCreaseOrSharp() const;


  /// <returns>
  /// If both end sharpness values are &gt;= 0 and &lt;= ON_SubDEdgeSharpness::MaximumValue, returns true.
  /// Note that ON_SubDEdgeSharpness::Crease.IsValid() and ON_SubDEdgeSharpness::Nan.IsValid() are both false.
  /// </returns>
  bool IsValid() const;


  /// <returns>
  /// Returns the opposite of IsValid().
  /// Note that ON_SubDEdgeSharpness::Crease.IsNotValid() and ON_SubDEdgeSharpness::Nan.IsNotValid() are both true.
  /// </returns>
  bool IsNotValid() const;

  /// <param name="bCreaseResult">
  /// Value to return when this is equal to ON_SubDEdgeSharpness::Crease.
  /// </param>
  /// <returns>
  /// If both end sharpness values are &gt;= 0 and &lt;= ON_SubDEdgeSharpness::MaximumValue, returns true.
  /// If this is equal to ON_SubDEdgeSharpness::Crease, returns bCreaseResult.
  /// Otherwise returns false.
  /// </returns>
  bool IsValid(bool bCreaseResult) const;

  /// <param name="bCreaseResult">
  /// Value to return when this is equal to ON_SubDEdgeSharpness::Crease.
  /// </param>
  /// <returns>
  /// If this is equal to ON_SubDEdgeSharpness::Crease, returns bCreaseResult.
  /// Otherwise returns the opposite of IsValid().
  /// </returns>
  bool IsNotValid(bool bCreaseResult) const;

  /// <summary>
  /// Determine if candidate_value is a valid edge end sharpness value.
  /// </summary>
  /// <param name="candidate_value">
  /// value to check
  /// </param>
  /// <param name="bCreaseResult">
  /// Value to return when ON_SubDEdgeSharpness::CreaseValue == candidate_value</param>
  /// <returns></returns>
  static bool IsValidValue(
    double candidate_value,
    bool bCreaseResult
  );

  /// <summary>
  /// Create a constant ON_SubDEdgeSharpness;
  /// </summary>
  /// <param name="sharpness">0 &lt;= sharpness &lt;= ON_SubDEdgeSharpness::MaximumValue</param>
  /// <returns>
  /// If the input values is valid, an ON_SubDEdgeSharpness 
  /// with constant value sharpness is returned. 
  /// If the input vaue is ON_SubDEdgeSharpness::CreaseValue, ON_SubDEdgeSharpness::Crease is returned.
  /// Otherwise ON_SubDEdgeSharpness::Nan is returned.
  /// </returns>
  static const ON_SubDEdgeSharpness FromConstant(double sharpness);

  /// <summary>
  /// Create a variable ON_SubDEdgeSharpness;
  /// </summary>
  /// <param name="sharpness0">0 &lt;= sharpness0 &lt;= ON_SubDEdgeSharpness::MaximumValue</param>
  /// <param name="sharpness1">0 &lt;= sharpness1 &lt;= ON_SubDEdgeSharpness::MaximumValue</param>
  /// <returns>
  /// If both input values are valid, an edge sharpness 
  /// with start value sharpness0 and end value sharpness1 is returned. 
  /// If both input values are ON_SubDEdgeSharpness::CreaseValue, ON_SubDEdgeSharpness::Crease::Crease is returned.
  /// Otherwise ON_SubDEdgeSharpness::Nan is returned.
  /// </returns>
  static const ON_SubDEdgeSharpness FromInterval(double sharpness0, double sharpness1);

  /// <summary>
  /// Create a variable ON_SubDEdgeSharpness;
  /// </summary>
  /// <param name="sharpness_interval">0 &lt;= sharpness0 &lt;= ON_SubDEdgeSharpness::MaximumValue</param>
  /// <returns>
  /// If the interval's values are valid, an edge sharpness 
  /// with start value sharpness_interval[0] and end value sharpness_interval[1] is returned. 
  /// If both sharpness_interval[] values are ON_SubDEdgeSharpness::CreaseValue, ON_SubDEdgeSharpness::Crease::Crease is returned.
  /// Otherwise ON_SubDEdgeSharpness::Nan is returned.
  /// </returns>
  static const ON_SubDEdgeSharpness FromInterval(const class ON_Interval& sharpness_interval);

  /// <summary>
  /// Return a sharpness interval that is the union of the nonzero input sharpness intervals.
  /// </summary>
  /// <param name="a"></param>
  /// <param name="b"></param>
  /// <returns>
  /// If an input parameter is ON_SubDEdgeSharpness::Smooth, ON_SubDEdgeSharpness::Crease, or ON_SubDEdgeSharpness::Nan,
  /// then that parameter it is ignored.
  /// The returned interval is the union of the nonzero valid input intervals. 
  /// If no input intervals are nonzero, then ON_SubDEdgeSharpness::Smooth is returned. 
  /// Either the returned sharpness is ON_SubDEdgeSharpness::Smooth or has 0.0 &lt; sharpness[0] &lt;= sharpness[1] &lt;= ON_SubDEdgeSharpness::MaximumValue.
  /// </returns>
  static const ON_SubDEdgeSharpness Union(
    const ON_SubDEdgeSharpness& a, 
    const ON_SubDEdgeSharpness& b 
  );

  /// <summary>
  /// Sharpness value for a subdivided edge.
  /// </summary>
  /// <param name="end_index"0 or 1.</param>
  /// <returns>Subdivided sharpness or ON_SubDEdgeSharpness::Smooth if index is out of range.</returns>
  const ON_SubDEdgeSharpness Subdivided(int end_index) const;

  const ON_SubDEdgeSharpness Reversed() const;

  /// <summary>
  /// Convert a user facing slider value to a SubD edge end sharpness value.
  /// </summary>
  /// <param name="slider_domain">Non empty slider domain. (Often ON_Interval::ZeroToOne.)</param>
  /// <param name="slider_value">A value in the slider_domain. slider_domain[0] returns 0.0. slider_domain[1] returns ON_SubDEdgeSharpness::MaximumValue.</param>
  /// <param name="invalid_input_result">Value to return if the input is not valid.</param>
  /// <returns>The slider value converted to an ON_SubDEdge sharpness value.</returns>
  static double SharpnessFromSliderValue(
    ON_Interval slider_domain,
    double slider_value,
    double invalid_input_result
  );

  /// <summary>
  /// Set chain_edge_sharpness to a sequence of evenly changing sharpnesses
  /// beginning with chain_sharpness_range[0] and ending with chain_sharpness_range[1].
  /// </summary>
  /// <param name="chain_sharpness_range">Beginning and ending sharpnesses.</param>
  /// <param name="edge_count">Number of edges in the chain.</param>
  /// <param name="chain_edge_sharpness">The list of sharpnesses is returned here.</param>
  /// <returns>
  /// If the sharpness is constant, 1 is returned.
  /// If the sharpness varies from edge to edge, edge_count is returned.
  /// Otherwise 0 is returned.
  /// </returns>
  static unsigned SetEdgeChainSharpness(
    ON_Interval chain_sharpness_range,
    unsigned edge_count,
    ON_SimpleArray<ON_SubDEdgeSharpness>& chain_edge_sharpness
  );

  /// <summary>
  /// Set chain_edge_sharpness to a sequence of evenly changing sharpnesses
  /// beginning with chain_sharpness_range[0] and ending with chain_sharpness_range[1].
  /// </summary>
  /// <param name="chain_sharpness_range">Beginning and ending sharpnesses.</param>
  /// <param name="edge_count">Number of edges in the chain.</param>
  /// <param name="chain_edge_sharpness">
  /// The list of sharpnesses is returned here.
  /// chain_edge_sharpness[] must have a capacity &gt;= edge_count.</param>
  /// <returns>
  /// If the sharpness is constant, 1 is returned.
  /// If the sharpness varies from edge to edge, edge_count is returned.
  /// Otherwise 0 is returned.
  /// </returns>
  static unsigned SetEdgeChainSharpness(
    ON_Interval chain_sharpness_range,
    unsigned edge_count,
    ON_SubDEdgeSharpness* chain_edge_sharpness
  );

  /// <summary>
  /// Convert a user facing slider value to a SubD edge end sharpness value.
  /// </summary>
  /// <param name="slider_domain">Non empty slider domain. (Often ON_Interval::ZeroToOne.)</param>
  /// <param name="normalized_slider_value">0 &lt;= normalized_slider_value &lt;= 1.</param>
  /// <param name="invalid_input_result">Value to return if the input is not valid.</param>
  /// <returns>
  /// If 0 &lt;= normalized_slider_value &lt;= 1, the normalized slider value converted to an ON_SubDEdge sharpness value
  /// from 0 to ON_SubDEdgeSharpness::MaximumValue. Otherwise, ON_DBL_QNAN is returned.
  /// </returns>
  static double SharpnessFromNormalizedValue(
    double normalized_slider_value
  );

  /// <summary>
  /// Get the edge sharpness at the start or end.
  /// </summary>
  /// <param name="end_index"0 or 1.</param>
  /// <returns>EndSharpness(end_index).</returns>
  double operator[](int end_index) const;

  /// <summary>
  /// Return the average of the sharpness interval.
  /// </summary>
  /// <returns>0.5*(sharpness[0]+sharpness[1])</returns>
  double Average() const;

  /// <summary>
  /// Return the minimum of the sharpness interval.
  /// </summary>
  /// <returns>The minimum of the sharpness interval</returns>
  double MinimumEndSharpness() const;

  /// <summary>
  /// Return the maximum of the sharpness interval.
  /// </summary>
  /// <returns>The maximum of the sharpness interval</returns>
  double MaximumEndSharpness() const;


  /// <summary>
  /// Get the sharpness at the start or end.
  /// </summary>
  /// <param name="end_index">0 or 1.</param>
  /// <returns>Sharpness or ON_DBL_QNAN if end_index is out of range.</returns>
  double EndSharpness(int end_index) const;

  ON_DEPRECATED_MSG("Use the version with an interior_crease_vertex_sharpness parameter.")
  static double VertexSharpness(
    ON_SubDVertexTag vertex_tag,
    unsigned sharp_edge_end_count,
    double maximum_edge_end_sharpness
  );


  /// <summary>
  /// Calculate the vertex sharpness from the attached sharp edge information.
  /// Note that vertices with a corner tag always have zero sharpness.
  /// </summary>
  /// <param name="vertex_tag">
  /// The vertex tag (smooth, crease, dart, corner). 
  /// For smooth, crease, and dart, this is used to determine the number of attached crease edges.
  /// COrner vertices always have sharpness = 0.
  /// </param>
  /// <param name="interior_crease_vertex_sharpness">
  /// If the original source of the vertex is an interior crease vertex 
  /// (vertex_tag = ON_SubDVertexTag::Crease, 2 sectors, EdgeCount() = FaceCount() &gt;= 2),
  /// then interior_crease_vertex_sharpness is the maximum edge sharpness at the
  /// vertex's end of all smooth edges from both sectors. 
  /// This paramter is important in special situations that occur
  /// in low level SubD evaluation code where information from only one
  /// sector is present. In all other cases, this value doesn't matter as long
  /// as interior_crease_vertex_sharpness &lt;= maximum_edge_sharpness_at_vertex.
  /// When in doubt pass 0.0 or ON_DBL_QNAN.
  /// </param>
  /// <param name="sharp_edge_end_count">
  /// Number of sharp edges attached to the vertex that have 
  /// nonzero end sharpness at the vertex.
  /// </param>
  /// <param name="maximum_edge_sharpness_at_vertex">
  /// The largest sharp edge end sharpness at the vertex.
  /// </param>
  /// <returns>
  /// The vertex sharpness value to use when subdividing the vertex.
  /// </returns>
  static double VertexSharpness(
    ON_SubDVertexTag vertex_tag,
    double interior_crease_vertex_sharpness,
    unsigned sharp_edge_end_count,
    double maximum_edge_sharpness_at_vertex
  );

  /// <summary>
  /// Verify 0 &lt;= sharpness &lt;= ON_SubDEdgeSharpness::MaximumValue and return an integer value when
  /// the input sharpenss is within ON_SubDEdgeSharpness::Tolerance of an integer.
  /// </summary>
  /// <param name="sharpness"></param>
  /// <param name="invalid_input_result">Value returned when the sharpness parameter is invalid.</param>
  /// <returns>SubD edge sharpness value that makes sense.</returns>
  static double Sanitize(
    double sharpness,
    double invalid_input_result
  );

  /// <summary>
  /// Verify 0 &lt;= sharpness &lt;= ON_SubDEdgeSharpness::MaximumValue and return an integer value when
  /// the input sharpenss is within ON_SubDEdgeSharpness::Tolerance of an integer.
  /// </summary>
  /// <param name="sharpness"></param>
  /// <returns>SubD edge sharpness value that makes sense or 0.0 if the input sharpness is invalid.</returns>
  static double Sanitize(
    double sharpness
  );

private:
  float m_edge_sharpness[2] = {};
};

ON_DECL
bool operator==(const ON_SubDEdgeSharpness& lhs, const ON_SubDEdgeSharpness& rhs);

ON_DECL
bool operator!=(const ON_SubDEdgeSharpness& lhs, const ON_SubDEdgeSharpness& rhs);

class ON_SubDVertexSharpnessCalculator
{
public:
  ON_SubDVertexSharpnessCalculator() = default;
  ~ON_SubDVertexSharpnessCalculator() = default;
  ON_SubDVertexSharpnessCalculator(const ON_SubDVertexSharpnessCalculator&) = default;
  ON_SubDVertexSharpnessCalculator& operator=(const ON_SubDVertexSharpnessCalculator&) = default;

  static const ON_SubDVertexSharpnessCalculator Unset;

  /// <summary>
  /// This constructor completely initializes the class
  /// and you may immediately call VertexSharpness() and VertexSharpPoint().
  /// </summary>
  /// <param name="vertex">
  /// Vertex where sharpness information is desired.
  /// </param>
  ON_SubDVertexSharpnessCalculator(
    const ON_SubDVertex* vertex
  );

  /// <summary>
  /// This constructor begins the initialization of the class.
  /// You must call AddEdgeSharpnessAndControlNetPoint() or
  /// AddCreaseEdgeControlNetPoint() for each edge attached to the vertex.
  /// This technique is useful when iteratove subdivision calculations 
  /// are being performed an no explicit ON_SubDVertex exists.
  /// </summary>
  /// <param name="vertex_tag"></param>
  /// <param name="vertex_control_net_point"></param>
  /// <param name="maximum_sharpness_at_interior_crease_vertex">
  /// If the vertex_tag parameter is ON_SubDVertexTag::Crease
  /// and the vertex is an interior crease (two crease sectors),  
  /// then maximum_sharpness_at_interior_crease_vertex should
  /// be the maximum value of the edge sharpnesses of all
  /// non-crease edges at this vertex. 
  /// In all other cases pass 0.0.
  /// When vertex_tag is not ON_SubDVertexTag::Crease, this
  /// parameter is always ignored.
  /// </param>
  ON_SubDVertexSharpnessCalculator(
    ON_SubDVertexTag vertex_tag,
    ON_3dPoint vertex_control_net_point,
    double maximum_sharpness_at_interior_crease_vertex
  );

  /// <summary>
  /// Completely initializes the class and you may immediately call VertexSharpness() and VertexSharpPoint().
  /// </summary>
  /// <param name="vertex">
  /// Vertex where sharpness information is desired.
  /// </param>
  bool SetVertex(
    const ON_SubDVertex* vertex
  );

  /// <summary>
  /// This constructor begins the initialization of the class.
  /// You must call AddEdgeSharpnessAndControlNetPoint() or
  /// AddCreaseEdgeControlNetPoint() for each edge attached to the vertex.
  /// This technique is useful when iteratove subdivision calculations 
  /// are being performed an no explicit ON_SubDVertex exists.
  /// </summary>
  /// <param name="vertex_tag"></param>
  /// <param name="vertex_control_net_point"></param>
  /// <param name="maximum_sharpness_at_interior_crease_vertex">
  /// If the vertex_tag parameter is ON_SubDVertexTag::Crease
  /// and the vertex is an interior crease (two crease sectors),  
  /// then maximum_sharpness_at_interior_crease_vertex should
  /// be the maximum value of the edge sharpnesses of all
  /// non-crease edges at this vertex. 
  /// In all other cases pass 0.0.
  /// When vertex_tag is not ON_SubDVertexTag::Crease, this
  /// parameter is always ignored.
  /// </param>
  /// <returns>
  /// True if successful. False otherwise.
  /// </returns>
  bool SetVertex(
    ON_SubDVertexTag vertex_tag,
    ON_3dPoint vertex_control_net_point,
    double maximum_sharpness_at_interior_crease_vertex
  );

  /// <summary>
  /// If this class was created using the constructor that has a vertex tag
  /// and that tag was ON_SubDVertexTag::Smooth or ON_SubDVertexTag::Dart,
  /// or ON_SubDVertexTag::Crease, then you you must call this function for
  /// every sharp edge connected to the vertex. 
  /// </summary>
  /// <param name="sharpness_at_vertex">
  /// If the associated edge is a crease, then pass ON_SubDEdgeSharpness::CreaseValue
  /// (or call AddCreaseEdge(other_end)).
  /// If the associated edge is smooth, then pass the edge sharpness at the
  /// the end connect to the vertex in question.
  /// </param>
  /// <param name="other_end_control_net_point">
  /// The control net point at edge's other vertex.
  /// </param>
  /// <returns>
  /// True if successful. False otherwise.
  /// </returns>
  bool AddEdgeSharpnessAndControlNetPoint(
    double sharpness_at_vertex,
    ON_3dPoint other_end_control_net_point
  );

  /// <summary>
  /// You may call this function if the edge in question
  /// is a crease edge attached to the vertex.
  /// </summary>
  /// <param name="other_end_control_net_point">
  /// The control net point at edge's other vertex.
  /// </param>
  bool AddCreaseEdgeControlNetPoint(
    ON_3dPoint other_end_control_net_point
  );

  /// <returns>
  /// If the vertex has been set, true is returned.
  /// Otherwise, false is returned.
  /// </returns>
  bool VertexIsSet() const;

  /// <returns>If the vertex has been set, the vertex's tag is returned.
  /// Otherwise, ON_SubDVertexTag::Unset is returned.
  /// </returns>
  ON_SubDVertexTag VertexTag() const;

  /// <returns>If the vertex has been set, the vertex's control net point is returned.
  /// Otherwise, ON_3dPoint::NanPoint is returned.
  /// </returns>
  const ON_3dPoint VertexControlNetPoint() const;

  /// <returns>Number of edges attached to the vertex.</returns>
  unsigned EdgeCount() const;

  /// <returns>Number of sharp edges attached to the vertex.</returns>
  unsigned SharpEdgeCount() const;

  /// <returns>Number of crease edges attached to the vertex.</returns>
  unsigned CreaseEdgeCount() const;

  /// <returns>
  /// True if the vertex has nonzero sharpness. 
  /// </returns>
  bool IsSharpVertex() const;

  /// <summary>
  /// When the vertex sharpness is &gt; 0, the vertex subdivision
  /// point is a blend of this->VertexSharpPoint() and the 
  /// Catmull-Clark subdivision point calculated as if there were no sharpness.
  /// </summary>
  /// <returns>
  /// The vertex sharpness.
  /// </returns>
  double VertexSharpness() const;

  /// <summary>
  /// 
  /// </summary>
  /// <returns>
  /// If this->VertexSharpness() &gt; 0, then this point must be blended with
  /// the Catmull-Clark subdivision point calculated as if there were no sharpness.
  /// Otherwise, 0 is returned.
  /// </returns>
  const ON_3dPoint VertexSharpPoint() const;

private:
  void Internal_SetVertex(
    ON_SubDVertexTag vertex_tag,
    ON_3dPoint vertex_control_net_point,
    double maximum_sharpness_at_interior_crease_vertex
  );

  void Internal_SetVertex(
    const ON_SubDVertex* vertex
  );

  bool Internal_SetVertexSharpnessAndSharpPoint() const;

  mutable enum class Status : unsigned char
  {
    Unset,

    /// <summary>
    /// m_vertex_tag, m_u2.m_vertex_control_net_point are set
    /// and edges can be added.
    /// </summary>
    VertexSet,

    /// <summary>
    /// m_u1.m_vertex_sharpness = VertexSharpness(),
    /// m_other_end_control_net_points[0] = VertexSharpPoint().
    /// m_other_end_control_net_points[1] = ON_3dPoint::NanPoint.
    /// </summary>
    SharpnessSet
  }
  m_status;

  ON_SubDVertexTag m_vertex_tag = ON_SubDVertexTag::Unset;

  /// <summary>
  /// Total number of edges attached to the vertex
  /// </summary>
  unsigned short m_edge_count = 0;

  /// <summary>
  /// Number of crease edges attached to the vertex.
  /// </summary>
  unsigned short m_crease_edge_count = 0;

  /// <summary>
  /// Number of sharp edges attached to the vertex.
  /// </summary>
  unsigned short m_sharp_edge_count = 0;

  ON_3dPoint m_vertex_control_net_point = {};

  mutable union
  {
    double m_max_edge_sharpness_at_vertex = 0.0;
    double m_vertex_sharpness;
  } m_u1;

  mutable
    ON_3dPoint m_other_end_control_net_points[2] = {};
};

/// <summary>
/// A ON_SubDFaceCornerDex is a value that identifies a subd face corner.
/// </summary>
class ON_WIP_CLASS ON_SubDFaceCornerDex
{
private:
  unsigned short m_corner_index = 0;
  unsigned short m_edge_count = 0;

public:  
  ON_SubDFaceCornerDex() = default;
  ~ON_SubDFaceCornerDex() = default;
  ON_SubDFaceCornerDex(const ON_SubDFaceCornerDex&) = default;
  ON_SubDFaceCornerDex& operator=(const ON_SubDFaceCornerDex&) = default;

  ON_SubDFaceCornerDex(unsigned face_corner_index, unsigned face_edge_count);

  /// <summary>
  /// ON_SubDFaceCorner::Unset has CornerIndex()=0 and EdgeCount()=0.
  /// </summary>
  static const ON_SubDFaceCornerDex Unset;

  /// <summary>
  /// Dictionary compares EdgeCount() then CornerIndex(). 
  /// Any set value &lt; any unset value.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns>
  /// -1 if lsh &lt; rhs. 
  /// 0 if lhs = rhs. 
  /// +1 if lhs &gt; rhs.
  /// </returns>
  static int CompareAll(const ON_SubDFaceCornerDex& lhs, const ON_SubDFaceCornerDex& rhs);

  /// <summary>
  /// Uses ON_SubDFaceCornerDex::CompareAll to dictionary sort nonnull inputs and safely sorts
  /// nullptr to the end.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns></returns>
  static int Compare(const ON_SubDFaceCornerDex* lhs, const ON_SubDFaceCornerDex* rhs);

  /// <returns>
  /// True if EdgeCount() &gt;= 3 and 0&lt; =CornerIndex() &lt; EdgeCount().
  /// False otherwise.
  /// </returns>
  bool IsSet() const;

  /// <returns>
  /// True if EdgeCount() &lt; 3 or CornerIndex() &gt;= EdgeCount().
  /// False otherwise.
  /// </returns>  
  bool IsNotSet() const;

  /// <param name="face"></param>
  /// <returns>
  /// True if IsSet() is true, nullptr != face, and EdgeCount() = face->EdgeCount().
  /// </returns>
  bool IsValid(const class ON_SubDFace* face) const;

  /// <returns>
  /// Zero based index identifying the corner of a subd face.
  /// </returns>
  unsigned CornerIndex() const;

  /// <returns>
  /// The number of edges in the subd face.
  ///</returns>
  unsigned EdgeCount() const;

  /// <returns>True if this is a corner of a quad face (IsSet() && 4 == EdgeCount()).</returns>
  bool IsQuadFace() const;

  /// <summary>
  /// NextCornerDex() = (this->CornerDex() + 1) % this->EdgeCount().
  /// If this is not set, then ON_SubDFaceCornerDex::Unset is returned.
  /// </summary>
  /// <returns>
  /// The next face coner in the counter-clocwise sense.
  /// </returns>
  const ON_SubDFaceCornerDex NextCornerDex() const;

  /// <summary>
  /// NextCornerDex() = (this->CornerDex() + this->EdgeCount() - 1) % this->EdgeCount().
  /// If this is not set, then ON_SubDFaceCornerDex::Unset is returned.
  /// </summary>
  /// <returns>
  /// The previous face coner in the counter-clocwise sense.
  /// </returns>
  const ON_SubDFaceCornerDex PreviousCornerDex() const;

  /// <summary>
  /// Get the vertex at the corner of the face identified by this.
  /// If this is not set, face is nullptr, or face->EdgeCount() != this->EdgeCount(),
  /// then nullptr is returned.
  /// </summary>
  /// <param name="face"></param>
  /// <returns>The vertex at the face corner</returns>
  const ON_SubDVertex* CornerVertex(const class ON_SubDFace* face) const;

  /// <summary>
  /// Get the vertex at the corner of the face identified by this->PreviousCornerDex().
  /// If this is not set, face is nullptr, or face->EdgeCount() != this->EdgeCount(),
  /// then nullptr is returned.
  /// </summary>
  /// <param name="face"></param>
  /// <returns>The vertex at the previous corner of the face</returns>
  const ON_SubDVertex* PreviousCornerVertex(const class ON_SubDFace* face) const;

  /// <summary>
  /// Get the vertex at the corner of the face identified by this->NextCornerDex().
  /// If this is not set, face is nullptr, or face->EdgeCount() != this->EdgeCount(),
  /// then nullptr is returned.
  /// </summary>
  /// <param name="face"></param>
  /// <returns>The vertex at the next corner of the face</returns>
  const ON_SubDVertex* NextCornerVertex(const class ON_SubDFace* face) const;

  /// <summary>
  /// Get the edge face->EdgePtr(this->CornerIndex()).
  /// If this is not set, face is nullptr, or face->EdgeCount() != this->EdgeCount(),
  /// then ON_SubDEdgePtr::Null is returned.
  /// </summary>
  /// <param name="face"></param>
  /// <param name="corner_edge_dex">
  /// 0=edge entering the corner = this->LeftEdgePtr(face);
  /// 1=edge leaving the corner
  /// </param>
  /// <returns></returns>
  const ON_SubDEdgePtr EdgePtr(const class ON_SubDFace* face, unsigned corner_edge_dex) const;

  /// <summary>
  /// Get the edge of face that goes from the the previous
  /// face corner to this face corner. The edge pointer 
  /// is oriented from PreviousCornerVertex() to CornerVertex().
  /// If this is not set, face is nullptr, or face->EdgeCount() != this->EdgeCount(),
  /// then ON_SubDEdgePtr::Null is returned.
  /// </summary>
  /// <param name="face"></param>
  /// <returns>face->EdgePtr(this->PreviousCornerDex().CornerIndex())</returns>
  const ON_SubDEdgePtr LeftEdgePtr(const class ON_SubDFace* face) const;

  /// <summary>
  /// Get the edge of face that goes from the this face corner
  /// to the next face corner. The edge pointer 
  /// is oriented from CornerVertex() to NextCornerVertex().
  /// If this is not set, face is nullptr, or face->EdgeCount() != this->EdgeCount(),
  /// then ON_SubDEdgePtr::Null is returned.
  /// </summary>
  /// <param name="face"></param>
  /// <returns>face->EdgePtr(this->CornerIndex())</returns>
  const ON_SubDEdgePtr RightEdgePtr(const class ON_SubDFace* face) const;
};

class ON_WIP_CLASS ON_SubDFaceParameter
{
public:
  ON_SubDFaceParameter() = default;
  ~ON_SubDFaceParameter() = default;
  ON_SubDFaceParameter(const ON_SubDFaceParameter&) = default;
  ON_SubDFaceParameter& operator=(const ON_SubDFaceParameter&) = default;


  /// <summary>
  /// Create a SubD face parameter that identifies a point on the face. 
  /// The parameters (0,0) correspond the the corner vertex cdex.Vertex(face). 
  /// The corner_s parameter runs from the corner vertex to the midpoint of cdex.RightEdge(face).
  /// The corner_t parameter runs from the corner vertex to the midpoint of cdex.LeftEdge(face).
  /// The parameters (1/2, 1/2) correspond the the center of the face.
  /// </summary>
  /// <param name="cdex">
  /// Identifies the face's corner subdivison quad.
  /// </param>
  /// <param name="corner_s">
  /// 0 &lt;= corner_s &lt;= 1/2
  /// </param>
  /// <param name="corner_t">
  /// 0 &lt;= corner_t &lt;= 1/2
  /// </param>
  ON_SubDFaceParameter(
    ON_SubDFaceCornerDex cdex,
    double corner_s,
    double corner_t
  );

  /// <summary>
  /// Create at ON_SubDFaceParameter the corresponds to the the specified quad face parameters.
  /// The quad face parameters for face.Vertex(0) are (0,0).
  /// The quad face parameters for face.Vertex(1) are (1,0).
  /// The quad face parameters for face.Vertex(2) are (1,1).
  /// The quad face parameters for face.Vertex(3) are (0,1).
  /// </summary>
  /// <param name="quad_face_s">
  /// 0 &lt;= quad_face_s &lt= 1.
  /// </param>
  /// <param name="quad_face_t">
  /// 0 &lt;= quad_face_t &lt= 1.
  /// </param>
  /// <returns>
  /// The ON_SubDFaceParameter the references the quad face point.
  /// </returns>
  static const ON_SubDFaceParameter CreateFromQuadFaceParameteters(
    double quad_face_s,
    double quad_face_t
  );


  /// <summary>
  /// ON_SubDFaceParameter::Nan has face_edge_count=0, corner_index=0, s=ON_DBL_QNAN, t=ON_DBL_QNAN.
  /// </summary>
  static const ON_SubDFaceParameter Nan;

  /// <returns>True if all values are valid.</returns>
  bool IsSet();

  /// <returns>True if all values are not valid.</returns>
  bool IsNotSet();

  /// <summary>
  /// Well ordered dictionary compare of m_cdex, m_s, and m_t using
  /// ON_SubDFaceCornerDex::CompareAll() and ON_DBL::CompareValue().
  /// Any set value &lt; any unset value.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns>
  /// -1: lhs &lt; rhs
  ///  0: lhs = rhs
  /// +1: lhs &gt; rhs
  /// </returns>
  static int CompareAll(const ON_SubDFaceParameter& lhs, const ON_SubDFaceParameter& rhs);

  /// <summary>
  /// Well ordered dictionary compare that uses ON_SubDFaceParameter::CompareAll() to
  /// compare nonnull values and safely sorts nullptr to the end.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns></returns>
  static int Compare(const ON_SubDFaceParameter* lhs, const ON_SubDFaceParameter* rhs);

  bool IsSet() const;

  bool IsNotSet() const;

  /// <summary>
  /// m_cdex identifies face's subdivision quad the s and t parameters apply to.
  /// The corner vertex is V = m_cdex.Vertex(face).
  /// The edge entering the corner is LE = m_cdex.LeftEdge(face).
  /// The edge leaving the corner is RE = m_cdex.RightEdge(face).
  /// V = LE.RelativeVertex(1) = RE.RelativeVertex(0).
  /// </summary>
  const ON_SubDFaceCornerDex FaceCornerDex() const;

  /// <summary>
  /// cdex = FaceCornerDex() identifies face's subdivision quad the s and t parameters apply to.
  /// The corner vertex is V = cdex.Vertex(face).
  /// The edge entering the corner is LE = cdex.LeftEdge(face).
  /// The edge leaving the corner is RE = cdex.RightEdge(face).
  /// V = LE.RelativeVertex(1) = RE.RelativeVertex(0).
  /// 
  /// p = FaceCornerParameters();
  /// The p.x parameter runs along half of RE from V to the midpoint of RE.
  /// 0 &lt;= p.x &lt; 1/2.
  /// The p.y parameter runs along half of LE from V to the midpoint of LE.
  /// 0 &lt;= p.y &lt; 1/2.
  /// At V, p=(0,0).
  /// At the midpoint of RE, p=(1/2,0)
  /// At the midpoint of LE, p=(0,1/2)
  /// At the center of the face, p=(1/2,1/2).
  /// </summary>
  const ON_2dPoint FaceCornerParameters() const;

  /// <summary>
  /// For quad faces, QuadFaceParameters() returns 2 normalized parameters that span the entire quad face.
  /// The 2d points (0,0), (1,0), (1,1), (0,1) corresponed to the quad face's vertices 
  /// face.Vertex(0), face.Vertex(1), face.Vertex(2), face.Vertex(3).
  /// </summary>
  /// <returns>
  /// If m_cdex.IsQUadFace() is true, then the 2 normalized quad face parameters 
  /// corresponding to this ON_SubDFaceParameter are returned.
  /// Otherwise ON_2dPoint::NanPoint is returned.
  /// </returns>
  const ON_2dPoint QuadFaceParameters() const;

  /// <summary>
  /// An evaluation point is at a SubD vertex if IsSet() is true
  /// and FaceCornerParameters() = (0,0, 0,0).
  /// </summary>
  /// <returns>
  /// True if the evaluation point is at a SubD vertex.
  /// </returns>
  const bool AtVertex() const;

  /// <summary>
  /// An evaluation point is on a subD edge if IsSet() is true and
  /// at least one of the values in FaceCornerParameters() is 0.0.
  /// </summary>
  /// <returns>
  /// True if the evaluation point is on a SubD edge.
  /// </returns>
  const bool OnEdge() const;

private:
  /// <summary>
  /// m_cdex identifies face's subdivision quad the s and t parameters apply to.
  /// The corner vertex is V = m_cdex.Vertex(face).
  /// The edge entering the corner is LE = m_cdex.LeftEdge(face).
  /// The edge leaving the corner is RE = m_cdex.RightEdge(face).
  /// V = LE.RelativeVertex(1) = RE.RelativeVertex(0).
  /// </summary>
  ON_SubDFaceCornerDex m_cdex;

  /// <summary>
  /// m_cdex identifies face's subdivision quad the s and t parameters apply to.
  /// The corner vertex is V = m_cdex.Vertex(face).
  /// The edge entering the corner is LE = m_cdex.LeftEdge(face).
  /// The edge leaving the corner is RE = m_cdex.RightEdge(face).
  /// V = LE.RelativeVertex(1) = RE.RelativeVertex(0).
  /// 
  /// The m_s parameter runs along half of RE from V to the midpoint of RE.
  /// 0 &lt;= m_s &lt; 1/2.
  /// m_s = 0 at V = RE.RelativeVertex(0) = LE.RelativeVertex(1).
  /// m_s = 1/2 at the midpoint of RE.
  /// At V, (m_s,m_t)=(0,0).
  /// At the center of the face, (m_s,m_t)=(1/2,1/2).
  /// </summary>
  double m_s = ON_DBL_QNAN;

  /// <summary>
  /// m_cdex identifies face's subdivision quad the s and t parameters apply to.
  /// The corner vertex is V = m_cdex.Vertex(face).
  /// The edge entering the corner is LE = m_cdex.LeftEdge(face).
  /// The edge leaving the corner is RE = m_cdex.RightEdge(face).
  /// V = LE.RelativeVertex(1) = RE.RelativeVertex(0).
  /// 
  /// The m_t parameter runs along half of LE from V to the midpoint of LE.
  /// 0 &lt;= m_t &lt; 1/2.
  /// m_t = 0 at V = RE.RelativeVertex(0) = LE.RelativeVertex(1).
  /// m_t = 1/2 at the midpoint of LE.
  /// At V, (m_s,m_t)=(0,0).
  /// At the center of the face, (m_s,m_t)=(1/2,1/2).
  /// </summary>
  double m_t = ON_DBL_QNAN;
};

ON_WIP_DECL
bool operator==(const ON_SubDFaceParameter& lhs, const ON_SubDFaceParameter& rhs);

ON_WIP_DECL
bool operator!=(const ON_SubDFaceParameter& lhs, const ON_SubDFaceParameter& rhs);


/// <summary>
/// ON_SubDHash provides a simple way to save a SubD's vertex, edge, and face SHA1 hashes.
/// Typically it is used when a calculation needs to know if the current SubD has is geometrically
/// identical to a previous SubD. When speed is not important, comparing the current value of
/// ON_SubD::GeometryHash() to a previously save value of ON_SubD::GeometryHash() is functionally
/// identical but typically much slower when the SubDs are different.
/// </summary>
class ON_CLASS ON_SubDHash
{
public:
  ON_SubDHash() = default;
  ~ON_SubDHash() = default;
  ON_SubDHash(const ON_SubDHash&) = default;
  ON_SubDHash& operator=(const ON_SubDHash&) = default;

public:
  /// <summary>
  /// All counts are zero and all hashes are ON_SHA1::EmptyContentHash.
  /// </summary>
  static const ON_SubDHash Empty;

  // Saves the counts and hashes of the specified type


  /// <summary>
  /// Saves the counts and hashes of the specified type.
  /// </summary>
  /// <param name="hash_type"></param>
  /// <param name="subd"></param>
  /// <returns></returns>
  static const ON_SubDHash Create(ON_SubDHashType hash_type, const class ON_SubD& subd );

  static const ON_SubDHash Create(ON_SubDHashType hash_type, const class ON_SubDimple* subdimple);

  /// <summary>
  /// Dictionary compare of VertexCount(), EdgeCount(), FaceCount(), VertexHash(), EdgeHash(), and FaceHash() in that order.
  /// 
  /// NOTE WELL:
  /// SubDRuntimeSerialNumber() and SubdGeometryContentSerialNumber() are not compared because the reason this
  /// class exists is for it to be used to see if two different SubDs have identical content.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns>
  /// -1: lhs < rhs
  /// 0: lhs == rsh
  /// 1: lhs > rhs
  /// </returns>
  static int Compare(const ON_SubDHash& lhs, const ON_SubDHash& rhs);

  /*
  Returns:
    True if vertex count is 0 or HashType is unset.
  */
  bool IsEmpty() const;

  /*
  Returns:
    True if vertex count is > 0 and HashType is geometry or toplology.
  */
  bool IsNotEmpty() const;

  ON_SubDHashType HashType() const;

  /// <summary>
  /// The runtime serial number can be used to identify the SubD that was hashed to created this ON_SubDHash.
  /// </summary>
  /// <returns>
  /// If this hash was created from an ON_SubD, then the value of subd.RuntimeSerialNumber() is returned.
  /// Otherwise, 0 is returned.
  /// </returns>
  ON__UINT64 SubDRuntimeSerialNumber() const;

  /// <summary>
  /// The geometry content serial number can be used to quickly determine if a SubD is exactly the instance used
  /// to create this ON_SubDHash. If the geometry content serial numbers are equal, then the SubD is identical
  /// to the one use to create the hash. If the geometry content serial numbers differ, the current SubD hashes 
  /// need to be checked against this to see what, if anything, changed. For example, moving a vertex will not 
  /// change a topology hash.
  /// </summary>
  /// <returns>
  /// Returns:
  ///   If this hash was created from an ON_SubD, then the value of subd.GeometryContentSerialNumber() at the
  ///   at the instant this hash was created is returned.
  ///   Otherwise, 0 is returned.
  /// </returns>
  ON__UINT64 SubDGeometryContentSerialNumber() const;

  /// <summary>
  /// Copied from the SubD when the hash is created.
  /// </summary>
  /// <returns>
  /// Number of hashed vertices.
  /// </returns>
  unsigned int VertexCount() const;

  /// <summary>
  /// Copied from the SubD when the hash is created.
  /// </summary>
  /// <returns>
  /// Number of hashed edges.
  /// </returns>
  unsigned int EdgeCount() const;

  /// <summary>
  /// Copied from the SubD when the hash is created.
  /// </summary>
  /// <returns>
  /// Number of hashed faces.
  /// </returns>
  unsigned int FaceCount() const;

  /// <summary>
  /// If two SubDs have identical VertexHash() values, 
  /// then the SubD vertex information associated with HashType() is identical.
  /// </summary>
  /// <returns>
  /// A SHA1 hash of the SubD's vertex information associated with HashType().
  /// </returns>
  const ON_SHA1_Hash VertexHash() const;

  /// <summary>
  /// If two SubDs have identical EdgeHash() values, 
  /// then the SubD edge information associated with HashType() is identical.
  /// </summary>
  /// <returns>
  /// A SHA1 hash of the SubD's edge information associated with HashType().
  /// </returns>
  const ON_SHA1_Hash EdgeHash() const;

  /// <summary>
  /// If two SubDs have identical FaceHash() values, 
  /// then the SubD face information associated with HashType() is identical.
  /// </summary>
  /// <returns>
  /// A SHA1 hash of the SubD's face information associated with HashType().
  /// </returns>
  const ON_SHA1_Hash FaceHash() const;

  /// <summary>
  /// If two SubDs have identical SubDHash() values, 
  /// then the SubD vertex, edge, and face information associated with HashType() is identical.
  /// </summary>
  /// <returns>
  /// A SHA1 hash of the SubD's vertex, edge, and face information associated with HashType().
  /// </returns>
  const ON_SHA1_Hash SubDHash() const;

  void Dump(ON_TextLog&) const;
  bool Write(class ON_BinaryArchive&) const;
  bool Read(class ON_BinaryArchive&);

private:
  friend class ON_SubDimple;
  ON_SubDHashType m_hash_type = ON_SubDHashType::Unset;
  unsigned int m_vertex_count = 0;
  unsigned int m_edge_count = 0;
  unsigned int m_face_count = 0;
  ON__UINT64 m_subd_runtime_serial_number = 0;
  ON__UINT64 m_subd_geometry_content_serial_number = 0;
  ON_SHA1_Hash m_vertex_hash = ON_SHA1_Hash::EmptyContentHash;
  ON_SHA1_Hash m_edge_hash = ON_SHA1_Hash::EmptyContentHash;
  ON_SHA1_Hash m_face_hash = ON_SHA1_Hash::EmptyContentHash;
};

bool operator==(const ON_SubDHash& lhs, const ON_SubDHash& rhs);

bool operator!=(const ON_SubDHash& lhs, const ON_SubDHash& rhs);

class ON_CLASS ON_SubDToBrepParameters
{
public:
  ON_SubDToBrepParameters() = default;
  ~ON_SubDToBrepParameters() = default;
  ON_SubDToBrepParameters(const ON_SubDToBrepParameters&) = default;
  ON_SubDToBrepParameters& operator=(const ON_SubDToBrepParameters&) = default;

  /*
  Description:
    Default ON_SubDToBrepParameters settings.
  Remarks: 
    These are the settings used by ON_SubD::BrepForm()
  */
  static const ON_SubDToBrepParameters Default;

  /*
  Description:
    Default ON_SubDToBrepParameters settings for creating an unpacked brep.
  */
  static const ON_SubDToBrepParameters DefaultUnpacked;

  /*
  Description:
    Default ON_SubDToBrepParameters settings for creating an packed brep.
  */
  static const ON_SubDToBrepParameters DefaultPacked;

  static int Compare(
    const ON_SubDToBrepParameters& lhs,
    const ON_SubDToBrepParameters& rhs
    );
  static int CompareFromPointers(
    const ON_SubDToBrepParameters* lhs,
    const ON_SubDToBrepParameters* rhs
    );

#pragma region RH_C_SHARED_ENUM [ON_SubDToBrepParameters::VertexProcess] [Rhino.Geometry.SubDToBrepOptions.ExtraordinaryVertexProcessOption] [nested:byte]
  /// <summary>
  /// ON_SubDToBrepParameters::Vertex identifies the options for post processing extraorindary vertices.
  /// </summary>
  enum class VertexProcess : unsigned char
  {
    ///<summary>
    /// The NURBS patches are used as is. 
    /// At extraordinary vertices, the brep vertex may not be G1.
    /// Typically the deviation bewtween the brep and SubD surface is smallest with this option.
    ///</summary>
    None = 0,

    ///<summary>
    /// At extraordinary vertices, the NURBS patches are modified so they are G1 at the extraordinary vertex.
    /// Typically the deviation bewtween the brep and SubD surface is larger than None and smaller than
    /// LocalG1x and LocalG2.
    ///</summary>
    LocalG1 = 1,

    ///<summary>
    /// At extraordinary vertices, the NURBS patches are modified so they are G2 at the extraordinary vertex.
    /// Typically the deviation bewtween the brep and SubD surface is larger than LocalG1 and LocalG1x.
    ///</summary>
    LocalG2 = 2,

    ///<summary>
    /// At extraordinary vertices, the NURBS patches are modified so they are G1 at the extraordinary vertex
    /// and tend to be closer to G1 along edges near the extraordinary vertex.
    /// Typically the deviation bewtween the brep and SubD surface is larger than LocalG1 and smaller than LocalG2.
    ///</summary>
    LocalG1x = 3,

    ///<summary>
    /// At extraordinary vertices, the NURBS patches are modified so they are G1 at the extraordinary vertex
    /// and G1 along edges near the extraordinary vertex.
    /// The patches will have one double knot near the extraordinary vertex.
    ///</summary>
    LocalG1xx = 4,
  };
#pragma endregion

  static ON_SubDToBrepParameters::VertexProcess VertexProcessFromUnsigned(
    unsigned int vertex_process_as_unsigned
  );

  static const ON_wString VertexProcessToString(
    ON_SubDToBrepParameters::VertexProcess vertex_process
  );

  /*
  Returns:
    Option used for post processing extraorindary vertices.
  */
  ON_SubDToBrepParameters::VertexProcess ExtraordinaryVertexProcess() const;

  /*
  Description:
    Set the ExtraordinaryVertexProcess() property.
  Parameters:
    ev_process - [in]
  */
  void SetExtraordinaryVertexProcess(
    ON_SubDToBrepParameters::VertexProcess ev_process
  );

  /*
  Returns:
    If true, then quad packs of SubD faces are returned as a single brep face.
    Otherwise each SubD face generates a brep face.
  Remarks:
    SubD n-gons with n != 4 always generate n brep faces.
  */
  bool PackFaces() const;

  /*
  Description:
    Set the PackFaces() property.
  Parameters:
    bPackFaces - [in]
  */
  void SetPackFaces(
    bool bPackFaces
  );

  const ON_wString ToString(
  bool bVerbose
  ) const;

  bool Read(ON_BinaryArchive& archive);
  
  bool Write(ON_BinaryArchive& archive) const;

private:
  bool m_bPackFaces = false;
  ON_SubDToBrepParameters::VertexProcess m_extraordinary_vertex_process = ON_SubDToBrepParameters::VertexProcess::LocalG1x;
  unsigned short m_reserved1 = 0;
  unsigned int m_reserved2 = 0;
  double m_reserved3 = 0.0;
};

bool operator==(const ON_SubDToBrepParameters& lhs, const ON_SubDToBrepParameters& rhs);
bool operator!=(const ON_SubDToBrepParameters& lhs, const ON_SubDToBrepParameters& rhs);

class ON_CLASS ON_SubDVertexPtr
{
public:
  // For performance reasons, m_ptr is not initialized and no constructors are declared
  // or implemented.  If you require initialization, then use x = ON_SubDVertexPtr::Null
  // or x = ON_SubDVertexPtr::Create(...).
  ON__UINT_PTR m_ptr;

  static const ON_SubDVertexPtr Null;

  bool IsNull() const;
  bool IsNotNull() const;

  /// <returns>
  /// If Vertex() is not nullptr, Vertex()->m_id is returned.
  /// Otherwise, 0 is returned.
  /// </returns>
  unsigned int VertexId() const;

  /// <returns>
  /// If Vertex() is not nullptr, Vertex()->m_vertex_tag is returned.
  /// Otherwise, ON_SubDVertexTag::Unset is returned.
  /// </returns>
  ON_SubDVertexTag VertexTag() const;

  /*
  Returns:
    True if this vertex is active in its parent subd or other
    relevant context.
  Remarks:
    When a component is in use, IsActive() = true. 
    If was used and then deleted, IsActive() is false.
  */
  bool IsActive() const;

  class ON_SubDVertex* Vertex() const;

  ON__UINT_PTR VertexDirection() const;

  const ON_ComponentStatus Status() const;

  static const ON_SubDVertexPtr Create(
    const class ON_SubDVertex* vertex
    );

  /*
  Parameters:
    vertex - [in]
    vertex_direction - [in]
      zero or one
  */
  static const ON_SubDVertexPtr Create(
    const class ON_SubDVertex* vertex,
    ON__UINT_PTR vertex_direction
    );

  static const ON_SubDVertexPtr Create(
    const class ON_SubDComponentPtr& vertex_component
    );

  /*
  Returns:
    The current value of the component mark ( m_status->RuntimeMark() ).
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  */
  bool Mark() const;

  /*
  Description:
    Clears (sets to false) the value of the component mark.
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool ClearMark() const;

  /*
  Description:
    Sets (sets to true) the value of the component mark.
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool SetMark() const;

  /*
  Description:
    Sets the value of the component mark to bMark.
  Parameter:
    bMark - [in]
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool SetMark(
    bool bMark
  ) const;


  ON__UINT8 MarkBits() const;

  ON__UINT8 SetMarkBits(
    ON__UINT8 mark_bits
  ) const;

  ON__UINT8 ClearMarkBits() const;

  void ClearSavedSubdivisionPoints() const;

  /*
  Description:
    Clears saved subdivision and limit surface information for this component.
  Parameters:
    bClearNeighborhood - [in]
      If true, all components attached to this component are also cleared.
  */
  void ClearSavedSubdivisionPoints(
    bool bClearNeighborhood
  ) const;

};

ON_DECL
bool operator==(ON_SubDVertexPtr lhs, ON_SubDVertexPtr rhs);

ON_DECL
bool operator!=(ON_SubDVertexPtr lhs, ON_SubDVertexPtr rhs);


#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_SubDVertexPtr>;
#endif

class ON_CLASS ON_SubDEdgePtr
{
public:
  // For performance reasons, m_ptr is not initialized and no constructors are declared
  // or implemented.  If you require initialization, then use x = ON_SubDEdgePtr::Null
  // or x = ON_SubDEdgePtr::Create(...).
  ON__UINT_PTR m_ptr;

  static const ON_SubDEdgePtr Null;

  /*
  Returns:
    True if this->Edge() is nullptr.
  */
  bool IsNull() const;

  /*
  Returns:
    True if this->Edge() is not nullptr.
  */
  bool IsNotNull() const;


  /*
  Returns:
    True if this->Edge() is not nullptr and both vertex pointers are not null as well.
  */
  bool IsNotNullAndVerticesAreNotNull() const;

  /*
  Returns:
    True if this edge is active in its parent subd or other
    relevant context.
  Remarks:
    When a component is in use, IsActive() = true. 
    If was used and then deleted, IsActive() is false.
  */
  bool IsActive() const;


  /*
  Returns:
    The ON_SubDEdge this points at.
  */
  class ON_SubDEdge* Edge() const;

  /*
  Returns:
    If Edge() is not nullptr, Edge()->m_id is returned.
    Otherwise, 0 is returned.
  */
  unsigned int EdgeId() const;
  
  /*
  Returns:
    If Edge() is not nullptr, Edge()->FaceCount() is returned.
    Otherwise, 0 is returned.
  */
  unsigned int EdgeFaceCount() const;

  /*
  Returns:
    If Edge() is not nullptr, Edge()->m_edge_tag is returned.
    Otherwise, ON_SubDEdgeTag::Unset is returned.
  */
  ON_SubDEdgeTag EdgeTag() const;

  /// <summary>
  /// EdgeType() is typically used to generate text descriptions and
  /// in selection filtering. 
  /// Do not confuse EdgeType() and EdgeTag().
  /// </summary>
  /// <returns>
  /// If Edge() is not nullptr, then Edge()->EdgeType() is returned.
  /// Otherwise, ON_SubDEdgeType::Unset is returned.
  /// </returns>
  ON_SubDEdgeType EdgeType() const;
    
  /*
  Returns:
    If Edge() is not nullptr, Edge()->IsSmooth() is returned.
    Otherwise, false is returned.
  */
  bool EdgeIsSmooth() const;
    

  /*
  Returns:
    If Edge() is not nullptr, Edge()->IsSmoothNotSharp() is returned.
    Otherwise, false is returned.
  */
  bool EdgeIsSmoothNotSharp() const;

  /*
  Returns:
    If Edge() is not nullptr, Edge()->IsSharp() is returned.
    Otherwise, false is returned.
  */
  bool EdgeIsSharp() const;

  /*
  Returns:
    If Edge() is not nullptr, Edge()->IsCreaseOrSharp() is returned.
    Otherwise, false is returned.
  */
  bool EdgeIsCreaseOrSharp() const;

  /*
  Returns:
    If Edge() is not nullptr, Edge()->IsCrease() is returned.
    Otherwise, false is returned.
  */
  bool EdgeIsCrease() const;
   

  /*
  Returns:
    If Edge() is not nullptr, Edge()->IsHardCrease() is returned.
    Otherwise, false is returned.
  */
  bool EdgeIsHardCrease() const;
   
  /*
  Returns:
    If Edge() is not nullptr, Edge()->IsDartCrease() is returned.
    Otherwise, false is returned.
  */
  bool EdgeIsDartCrease() const;

  /*
  Returns:
    If Edge() is not nullptr, Edge()->HasInteriorEdgeTopology(bRequireOppositeFaceDirections) is returned.
    Otherwise, false is returned.
  */
  bool HasInteriorEdgeTopology(
    bool bRequireOppositeFaceDirections
  ) const;

  /*
  Returns:
    0: this ON_SubDEdgePtr is oriented from Edge()->Vertex(0) to Edge()->Vertex(1).
    1: this ON_SubDEdgePtr is oriented from Edge()->Vertex(1) to Edge()->Vertex(0).
  */
  ON__UINT_PTR EdgeDirection() const;

  /*
  Parameters:
    relative_vertex_index - [in]
      0: return Edge()->Vertex(EdgeDirection())
      1: return Edge()->Vertex(1-EdgeDirection())
  Returns:
    The requested vertex with EdgeDirection() taken into account.
    nullptr if relative_vertex_index, Edge() is nullptr, or Edge()->Vertex() is nullptr.
  */
  const class ON_SubDVertex* RelativeVertex(
    int relative_vertex_index
  ) const;

  /*
  Parameters:
    relative_vertex_index - [in]
      0: return Edge()->Vertex(EdgeDirection())->m_vertex_tag
      1: return Edge()->Vertex(1-EdgeDirection())->m_vertex_tag
  Returns:
    The requested vertex with EdgeDirection() taken into account.
    If Edge() or Edge()->Vertex(EdgeDirection()) is nullptr,
    then ON_SubDVertexTag::Unset is returned.
  */
  ON_SubDVertexTag RelativeVertexTag(
    int relative_vertex_index
  ) const;

  /*
  Parameters:
    relative_vertex_index - [in]
      0: return Edge()->Vertex(EdgeDirection())
      1: return Edge()->Vertex(1-EdgeDirection())
  Returns:
    The requested id of the vertex with EdgeDirection() taken into account.
    0 if relative_vertex_index, Edge() is nullptr, or Edge()->Vertex() is nullptr.
  */
  unsigned RelativeVertexId(
    int relative_vertex_index
  ) const;

  /*
  Parameters:
    relative_vertex_index - [in]
      0: return Edge()->Vertex(EdgeDirection())
      1: return Edge()->Vertex(1-EdgeDirection())
  Returns:
    The requested vertex control net point with EdgeDirection() taken into account.
    ON_3dPoint::NanPoint if relative_vertex_index, Edge() is nullptr, or Edge()->Vertex() is nullptr.
  */
  const ON_3dPoint RelativeControlNetPoint(
    int relative_vertex_index
  ) const;


  /*
  Parameters:
    relative_vertex_index - [in]
      0: return Edge()->Vertex(EdgeDirection())->SurfacePoint()
      1: return Edge()->Vertex(1-EdgeDirection())->SurfacePoint()
  Returns:
    The requested vertex surface point with EdgeDirection() taken into account.
    ON_3dPoint::NanPoint if relative_vertex_index, Edge() is nullptr, or Edge()->Vertex() is nullptr.
  */
  const ON_3dPoint RelativeVertexSurfacePoint(
    int relative_vertex_index
  ) const;

  /*
  Parameters:
    relative_vertex_index - [in]
      0: return Edge()->Vertex(EdgeDirection())->Point(point_location)
      1: return Edge()->Vertex(1-EdgeDirection())->Point(point_location)
    point_location - [in]
      Used to select control net or limit surface point.
  Returns:
    The requested vertex point with with EdgeDirection() taken into account.
    ON_3dPoint::NanPoint if relative_vertex_index, Edge() is nullptr, or Edge()->Vertex() is nullptr.
  */
  const ON_3dPoint RelativeVertexPoint(
    int relative_vertex_index,
    ON_SubDComponentLocation point_location
  ) const;


  bool RelativeVertexMark(
    int relative_vertex_index,
    bool missing_vertex_return_value
  ) const;

  ON__UINT8 RelativeVertexMarkBits(
    int relative_vertex_index,
    ON__UINT8 missing_vertex_return_value
  ) const;

  const ON_Line RelativeControlNetLine() const;

  const ON_3dVector RelativeControlNetDirection() const;

  /*
  Description:
    The sector coefficient is a property of a smooth edge end
    that is attached to a dart, crease, or corner vertex.
    In all other cases the sector coefficient is ignored.
    The value of the sector coefficient is constant throughout subdivision.    
    Every smooth edge in a sector has the same sector coefficient at the central vertex.
  Parameters:
    relative_vertex_index - [in]
  Returns:
    If Edge() not nullptr, then
    If (relative_vertex_index = 0), returns Edge()->m_sector_coefficient(EdgeDirection())
    If (relative_vertex_index = 0), returns Edge()->m_sector_coefficient(1-EdgeDirection())
    Otherwise ON_SubDSectorType::ErrorSectorCoefficient is returned.
  Remarks:
    The name "sector coefficient" is used because is is a property of the
    vertex's sector (every edge in vertex sector has the same value at the tagged vertex).
    The sector coefficient does not change when a subdivision is applied.
  */
  double RelativeSectorCoefficient(
    int relative_vertex_index
    ) const;

  void  SetRelativeSectorCoefficientForExperts(
    int relative_vertex_index,
    double relative_sector_coefficient
  ) const;

  /// <summary>
  /// Edge sharpness oriented with respect to this ON_SubDEdgePointer's direction.
  /// </summary>
  /// <param name="bUseCreaseSharpness">
  /// If the edge is a crease and bUseCreaseSharpness is false, then ON_SubDEdgeSharpness::Smooth is returned.
  /// If the edge is a crease and bUseCreaseSharpness is true, then ON_SubDEdgeSharpness::Crease is returned.
  /// </param>
  /// <returns></returns>
  const ON_SubDEdgeSharpness RelativeSharpness( bool bUseCreaseSharpness ) const;

  void SetRelativeSharpness(ON_SubDEdgeSharpness relative_sharpness) const;

  /*
  Description:
    Get the face on the left or right side of an oriented manifold or boundary edge.
    A face is on the "left side" if this ON_SubDEdgePtr is oriented so it
    points in the same direction as the face's oriented boundary.
    A face is on the "right side" if this ON_SubDEdgePtr is oriented so it
    points in the opposite direction as the face's oriented boundary.
    If an edge is nonmanifold (3 or more faces), then nullptr is always returned.
    If an edge has two faces that do not attach to this edge with opposite orientations
    (nonoriented manifold edge), then nullptr is returned.    
  Parameters:
    relative_face_index - [in]
      0: return face on the left side of the edge with respect to EdgeOrientation().
      1: return face on the right side of the edge with respect to EdgeOrientation().
  Returns:
    The requested face.
  */
  const class ON_SubDFace* RelativeFace(
    int relative_face_index
  ) const;

  /// <summary>
  /// Get the edge's face ignoring orientation.
  /// </summary>
  /// <param name="edge_face_index">
  /// ON_SubDEdge face index.
  /// </param>
  /// <returns>
  /// If this->Edge() is not nullptr, then this->Edge()->Face(edge_face_index) is returned.
  /// Otherwise nullptr is returned.
  /// </returns>
  const class ON_SubDFace* EdgeFace(
    int edge_face_index
  ) const;


  /*
  Description:
    Return the neighboring face.
  Parameters:
    face - [in]
      A face attached to this edge.
    bStopAtCrease - [in]
      If true and if m_edge_tag = ON_SubDEdgeTag::Crease,
      then nullptr is returned.
  Returns:
    If the m_face_count = 2,
    m_edge_tag is smooth or x or passes the crease tag test,
    one of m_face2[0,1] points a face, then
    the neighboring face is returned.
    In any other case, nullptr is returned.
  */
  const ON_SubDFace* NeighborFace(
    const ON_SubDFace* face,
    bool bStopAtCrease
  ) const;

  /*
  Returns:
    this->RelativeFace(relative_face_index)->Mark();
  */
  bool RelativeFaceMark(
    int relative_face_index,
    bool missing_face_return_value
  ) const;

  /*
  Returns:
    this->RelativeFace(relative_face_index)->MarkBits();
  */
  ON__UINT8 RelativeFaceMarkBits(
    int relative_face_index,
    ON__UINT8 missing_face_return_value
  ) const;

  /*
  Returns:
    The vector from RelativeVertex(0)->ControlNetPoint() to RelativeVertex(1)->ControlNetPoint(),
    or ON_3dVector::NanVector if the relative vertex pointers are nullptr.
  */
  const ON_3dVector RelativeDirection() const;

  /*
  Returns:
    this->Edge()->m_status.
  */
  const ON_ComponentStatus Status() const;

  /*
  Returns:
    A ON_SubDEdgePtr pointing at the same edge with the direction reversed from this.
  */
  const ON_SubDEdgePtr Reversed() const;

  /// <summary>
  /// Get the SubD edge Catmull-Clark subdivision point.
  /// </summary>
  /// <returns>Catmull-Clark edge subdivision point.</returns>
  const ON_3dPoint SubdivisionPoint() const;



  void ClearSavedSubdivisionPoints() const;

  /*
  Description:
    Clears saved subdivision and limit surface information for this component.
  Parameters:
    bClearNeighborhood - [in]
      If true, all components attached to this component are also cleared.
  */
  void ClearSavedSubdivisionPoints(
    bool bClearNeighborhood
  ) const;



  /*
  Parameters:
    edge - [in]
  Returns:
    An ON_SubDEdgePtr pointing at edge with direction = 0 (not reversed).
  */
  static const ON_SubDEdgePtr Create(
    const class ON_SubDEdge* edge
    );

  /*
  Parameters:
    edge - [in]
    direction - [in]
      0: not reversed
      1: reversed
  Returns:
    An ON_SubDEdgePtr pointing at edge with the specified direction.
  */
  static const ON_SubDEdgePtr Create(
    const class ON_SubDEdge* edge,
    ON__UINT_PTR direction
    );

  /*
  Parameters:
    v0 - [in]
    v1 - [in]
  Returns:
    If there is an edge connecting v0 and v1, then an ON_SubDEdgePtr pointing to that edge 
    and oriented from v0 to v1 is returned. Otherwise ON_SubDEdgePtr::Null is returned.
  */
  static const ON_SubDEdgePtr Create(
    const class ON_SubDVertex* v0,
    const class ON_SubDVertex* v1
  );


  static const ON_SubDEdgePtr Create(
    const class ON_SubDComponentPtr& edge_component
    );

  /*
  Parameters:
    edge - [in]
    start_vertex - [in]
      One of the edge's vertices.
  Returns:
     An ON_SubDEdgePtr pointing at edge with RelativeVertex(0) = start_vertex.
  */
  static const ON_SubDEdgePtr CreateFromStartVertex(
    const class ON_SubDEdge* edge,
    const ON_SubDVertex* start_vertex
  );

  /*
  Parameters:
    edge - [in]
    end_vertex - [in]
      One of the edge's vertices.
  Returns:
     An ON_SubDEdgePtr pointing at edge with RelativeVertex(1) = end_vertex.
  */
  static const ON_SubDEdgePtr CreateFromEndVertex(
    const class ON_SubDEdge* edge,
    const ON_SubDVertex* end_vertex
  );


  /*
  Returns:
    The current value of the component mark ( m_status->RuntimeMark() ).
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  */
  bool Mark() const;

  /*
  Description:
    Clears (sets to false) the value of the component mark.
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool ClearMark() const;

  /*
  Description:
    Sets (sets to true) the value of the component mark.
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool SetMark() const;

  /*
  Description:
    Sets the value of the component mark to bMark.
  Parameter:
    bMark - [in]
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool SetMark(
    bool bMark
  ) const;

  ON__UINT8 MarkBits() const;

  ON__UINT8 SetMarkBits(
    ON__UINT8 mark_bits
  ) const;

  ON__UINT8 ClearMarkBits() const;
};

ON_DECL
bool operator==(ON_SubDEdgePtr lhs, ON_SubDEdgePtr rhs);

ON_DECL
bool operator!=(ON_SubDEdgePtr lhs, ON_SubDEdgePtr rhs);


#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_SubDEdgePtr>;
#endif

class ON_CLASS ON_SubDFacePtr
{
public:
  // For performance reasons, m_ptr is not initialized and no constructors are declared
  // or implemented.  If you require initialization, then use x = ON_SubDFacePtr::Null
  // or x = ON_SubDFacePtr::Create(...).
  ON__UINT_PTR m_ptr;

  static const ON_SubDFacePtr Null;

  bool IsNull() const;

  bool IsNotNull() const;

  /*
  Returns:
    True if this face is active in its parent subd or other
    relevant context.
  Remarks:
    When a component is in use, IsActive() = true. 
    If was used and then deleted, IsActive() is false.
  */
  bool IsActive() const;


  class ON_SubDFace* Face() const;
  
  /*
  Returns:
    If Face() is not nullptr, Face()->m_id is returned.
    Otherwise, 0 is returned.
  */
  unsigned int FaceId() const;

  /*
  Returns:
    If Face() is not nullptr, Face()->EdgeCount() is returned.
    Otherwise, 0 is returned.
  */
  unsigned int FaceEdgeCount() const;
  
  ON__UINT_PTR FaceDirection() const;

  const ON_ComponentStatus Status() const;

  /*
  Returns:
    A ON_SubDFacePtr pointing at the same face with the direction reversed from this.
  */
  const ON_SubDFacePtr Reversed() const;

  static const ON_SubDFacePtr Create(
    const class ON_SubDFace* face,
    ON__UINT_PTR direction
    );

  static const ON_SubDFacePtr Create(
    const class ON_SubDComponentPtr& face_component
    );

  static int Compare(
    const ON_SubDFacePtr* lhs,
    const ON_SubDFacePtr* rhs
  );

  static int CompareFacePointer(
    const ON_SubDFacePtr* lhs,
    const ON_SubDFacePtr* rhs
  );

  /*
  Returns:
    The current value of the component mark ( m_status->RuntimeMark() ).
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  */
  bool Mark() const;

  /*
  Description:
    Clears (sets to false) the value of the component mark.
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool ClearMark() const;

  /*
  Description:
    Sets (sets to true) the value of the component mark.
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool SetMark() const;

  /*
  Description:
    Sets the value of the component mark to bMark.
  Parameter:
    bMark - [in]
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool SetMark(
    bool bMark
  ) const;

  ON__UINT8 MarkBits() const;

  ON__UINT8 SetMarkBits(
    ON__UINT8 mark_bits
  ) const;

  ON__UINT8 ClearMarkBits() const;

  void ClearSavedSubdivisionPoints() const;

  /*
  Description:
    Clears saved subdivision and limit surface information for this component.
  Parameters:
    bClearNeighborhood - [in]
      If true, all components attached to this component are also cleared.
  */
  void ClearSavedSubdivisionPoints(
    bool bClearNeighborhood
  ) const;

  ///<summary>
  /// The SubD face Catmull-Clark subdivision point.
  ///</summary>
  const ON_3dPoint SubdivisionPoint() const;


};

ON_DECL
bool operator==(ON_SubDFacePtr lhs, ON_SubDFacePtr rhs);

ON_DECL
bool operator!=(ON_SubDFacePtr lhs, ON_SubDFacePtr rhs);

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_SubDFacePtr>;
#endif


class ON_CLASS ON_SubDComponentPtr
{
public:
  // For performance reasons, m_ptr is not initialized and no constructors are declared
  // or implemented.  If you require initialization, then use x = ON_SubDComponentPtr::Null
  // or x = ON_SubDComponentPtr::Create(...).
  ON__UINT_PTR m_ptr;

  /// <summary>
  /// nullptr, type = Unset, direction = 0
  /// </summary>
  static const ON_SubDComponentPtr Null; 

  /// <summary>
  /// nullptr, type = Vertex, direction = 0
  /// </summary>
  static const ON_SubDComponentPtr NullVertex;

  /// <summary>
  /// nullptr, type = Edge, direction = 0
  /// </summary>
  static const ON_SubDComponentPtr NullEdge;

  /// <summary>
  /// nullptr, type = Face, direction = 0
  /// </summary>
  static const ON_SubDComponentPtr NullFace;

  /// <summary>
  /// ON_SubDComponentPtr::Type identifies the type of subdivision component referenced by
  /// the ON_SubDComponentPtr.
  /// </summary>
  enum class Type : unsigned char
  {
    Unset = 0,
    Vertex = 2,
    Edge = 4,
    Face = 6
  };

  static ON_SubDComponentPtr::Type ComponentPtrTypeFromUnsigned(
    unsigned int component_pointer_type_as_unsigned
    );

   /*
   Description:
     ON_SubDComponentPtr::Type::Vertex 
     < ON_SubDComponentPtr::Type::Edge
     < ON_SubDComponentPtr::Type::Face
     < ON_SubDComponentPtr::Type::Unset
     < invalid
   */
  static int CompareComponentPtrType(
    ON_SubDComponentPtr::Type a,
    ON_SubDComponentPtr::Type b
    );

  static int CompareType(
    const ON_SubDComponentPtr* a,
    const ON_SubDComponentPtr* b
    );

  /*
  Description:
    Dictionary compares type and ComponentBase() pointer as an unsigned.
  */
  static int CompareComponent(
    const ON_SubDComponentPtr* a,
    const ON_SubDComponentPtr* b
  );

  /*
  Description:
    Dictionary compares type and ComponentBase() id.
  */
  static int CompareComponentId(
    const ON_SubDComponentPtr* a,
    const ON_SubDComponentPtr* b
  );

  /*
  Description:
    Dictionary compares type, ComponentBase() pointer as an unsigned,
    and ComponentDirection().
  */
  static int CompareComponentAndDirection(
    const ON_SubDComponentPtr* a,
    const ON_SubDComponentPtr* b
  );


  /*
  Returns:
    True if the ComponentBase() pointer is nullptr. Note that type and mark may be set.
  */
  bool IsNull() const;

  /*
  Returns:
    True if type is set and ComponentBase() pointer is not nullptr. Note that mark may be set as well.
  */
  bool IsNotNull() const;

  /*
  Returns:
    True if this component is active in its parent subd or other
    relevant context.
  Remarks:
    When a component is in use, IsActive() = true. 
    If was used and then deleted, IsActive() is false.
  */
  bool IsActive() const;

  /*
  Returns:
    True if this component is marked as a primary motif component.
  Remarks:
    You must use ON_SubD SymmetrySet member functions to get symmetry set contents.
  */
  bool IsSymmetrySetPrimaryMotif() const;

  /*
  Returns:
    True if this component is marked being in a symmetry set.
  Remarks:
    You must use ON_SubD SymmetrySet member functions to get symmetry set contents.
  */
  bool InSymmetrySet() const;

  ON_SubDComponentPtr::Type ComponentType() const;

  class ON_SubDComponentBase* ComponentBase() const;
  
  /*
  type_filter - [in]
    If is ON_SubDComponentPtr::Type::Unset, then any type of component will be returned.
    Otherwise only a component of the specified type will be returned.
  */
  class ON_SubDComponentBase* ComponentBase(ON_SubDComponentPtr::Type type_filter) const;

  class ON_SubDVertex* Vertex() const;
  class ON_SubDEdge* Edge() const;
  class ON_SubDFace* Face() const;

  const ON_SubDVertexPtr VertexPtr() const;
  const ON_SubDEdgePtr EdgePtr() const;
  const ON_SubDFacePtr FacePtr() const;

  const bool IsVertex() const;
  const bool IsEdge() const;
  const bool IsFace() const;

  void ClearSavedSubdivisionPoints() const;

  /*
  Description:
    Clears saved subdivision and limit surface information for this component.
  Parameters:
    bClearNeighborhood - [in]
      If true, all components attached to this component are also cleared.
  */
  void ClearSavedSubdivisionPoints(
    bool bClearNeighborhood
  ) const;

  unsigned int ComponentId() const;

  /// <returns>
  /// If Vertex() is not nullptr, Vertex()->m_id is returned.
  /// Otherwise, 0 is returned.
  /// </returns>
  unsigned int VertexId() const;

  /// <returns>
  /// If Edge() is not nullptr, Edge()->m_id is returned.
  /// Otherwise, 0 is returned.
  /// </returns>
  unsigned int EdgeId() const;

  /// <returns>
  /// If Face() is not nullptr, Face()->m_id is returned.
  /// Otherwise, 0 is returned.
  /// </returns>
  unsigned int FaceId() const;

  /// <returns>
  /// If Vertex() is not nullptr, Vertex()->m_vertex_tag is returned.
  /// Otherwise, ON_SubDVertexTag::Unset is returned.
  /// </returns>
  ON_SubDVertexTag VertexTag() const;

  /// <returns>
  /// If Edge() is not nullptr, Edge()->m_edge_tag is returned.
  /// Otherwise, ON_SubDEdgeTag::Unset is returned.
  /// </returns>
  ON_SubDEdgeTag EdgeTag() const;

  /// <returns>
  /// If Vertex() is not nullptr, Vertex()->m_vertex_tag is returned.
  /// Otherwise, ON_DBL_NAN is returned.
  /// </returns>
  double VertexSharpness() const;

  /// <summary>
  /// Used to get edge sharpness when the referenced component is an edge.
  /// </summary>
  /// <param name="bUseCreaseSharpness">
  /// </param>
  /// <returns>
  /// If Edge() is not nullptr, Edge()->Sharpness(bUseCreaseSharpness) is returned.
  /// Otherwise, ON_SubDEdgeTag::Nan is returned.
  /// </returns>
  const ON_SubDEdgeSharpness EdgeSharpness(bool bUseCreaseSharpness) const;

  const ON_COMPONENT_INDEX ComponentIndex() const;

  const ON_3dPoint ControlNetCenterPoint() const;
  const ON_BoundingBox ControlNetBoundingBox() const;

  /// <summary>
  /// Get the location of the component's subdivision vertex.
  /// </summary>
  /// <returns>Catmull-Clark component subdivision point.</returns>
  const ON_3dPoint SubdivisionPoint() const;


  /*
  Returns:
    A value suitable for hash table used based on the component type and id.
  */
  ON__UINT16 Hash16FromTypeAndId() const;


  /*
  Returns:
    A value suitable for hash table used based on the value of ComponentBase().
  */
  ON__UINT32 Hash32FromPointer() const;

  /*
  Returns:
    0 or 1.
    A runtime bit property on this ON_SubDComponentPtr. 
    The use of this value varies depending on the context.
    Frequently, 0 means the referenced component is being used with its
    natural orientation and 1 means the referenced component is being used
    with the reverse of its natural oreientation.
  */
  ON__UINT_PTR ComponentDirection() const;

  /*
  Returns:
    An ON_SubDComponentPtr referencing the same ON_SubDComponentBase
    with ON_SubDComponentPtr.ComponentDirection() = 0.
  */
  const ON_SubDComponentPtr ClearComponentDirection() const;

  /*
  Returns:
    An ON_SubDComponentPtr referencing the same ON_SubDComponentBase
    with ON_SubDComponentPtr.ComponentDirection() = 1.
  */
  const ON_SubDComponentPtr SetComponentDirection() const;

  /*
  Returns:
    An ON_SubDComponentPtr referencing the same ON_SubDComponentBase
    with ON_SubDComponentPtr.ComponentDirection() = 1.
  */
  const ON_SubDComponentPtr SetComponentDirection(ON__UINT_PTR dir) const;
   
  /*
  Returns:
    An ON_SubDComponentPtr referencing the same ON_SubDComponentBase
    with ComponentDirection() = 1 - this->ComponentDirection().
  */
  const ON_SubDComponentPtr Reversed() const;

  const ON_ComponentStatus Status() const;

  /*
  Returns:
    1: status changed.
    0: status not changed.
  */
  unsigned int SetStates(
    ON_ComponentStatus states_to_set
    );

  /*
  Returns:
    1: status changed.
    0: status not changed.
  */
  unsigned int ClearStates(
    ON_ComponentStatus states_to_clear
    );

  /*
  Description:
    Makes "this" an exact copy of status.
  Parameters:
    status - [in]
  Returns:
    1: status changed.
    0: status not changed.
  */
  unsigned int SetStatus(
    ON_ComponentStatus status
    );

  /*
  Returns:
    The current value of the component mark ( m_status->RuntimeMark() ).
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  */
  bool Mark() const;

  /*
  Description:
    Clears (sets to false) the value of the component mark.
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool ClearMark() const;

  /*
  Description:
    Sets (sets to true) the value of the component mark.
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool SetMark() const;

  /*
  Description:
    Sets the value of the component mark to bMark.
  Parameter:
    bMark - [in]
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool SetMark(
    bool bMark
  ) const;

  ON__UINT8 MarkBits() const;

  ON__UINT8 SetMarkBits(
    ON__UINT8 mark_bits
  ) const;

  ON__UINT8 ClearMarkBits() const;

  /*
  Parameters:
    null_component_value - [in]
      Value to return if the component is null.
  Returns:
    If this is not null, the group id of the component is returned.
    Otherwise null_component_value is returned.
  */
  unsigned int GroupId(
    unsigned int null_component_value
  ) const;

  /*
  Description:
    Sets ON_SubDComponentBase.m_group_id.
  Parameters:
    group_id - [in]
      Value to return if the component is null.
  Returns:
    True if the component is not null and the group id was set.
    False if the component is null.
  */
  bool SetGroupId(
    unsigned int group_id
  );

  static
  const ON_SubDComponentPtr CreateNull(
    ON_SubDComponentPtr::Type component_type,
    ON__UINT_PTR component_direction
    );

  static
  const ON_SubDComponentPtr Create(
    const class ON_SubDVertex* vertex
    );

  static
  const ON_SubDComponentPtr Create(
    const class ON_SubDEdge* edge
    );

  static
  const ON_SubDComponentPtr Create(
    const class ON_SubDFace* face
    );

  static
  const ON_SubDComponentPtr Create(
    const class ON_SubDVertex* vertex,
    ON__UINT_PTR vertex_direction
    );

  static
  const ON_SubDComponentPtr Create(
    const class ON_SubDEdge* edge,
    ON__UINT_PTR edge_direction
    );

  static
  const ON_SubDComponentPtr Create(
    const class ON_SubDFace* face,
    ON__UINT_PTR face_direction
    );
  
  static
  const ON_SubDComponentPtr Create(
    ON_SubDVertexPtr vertexptr
    );
  
  static
  const ON_SubDComponentPtr Create(
    ON_SubDEdgePtr edgeptr
    );

  static
  const ON_SubDComponentPtr Create(
    ON_SubDFacePtr faceptr
    );

  /// <summary>
  /// Depending on the type of this component, returns an ON_SubDComponentPtr to
  /// ON_SubDVertex::NextVertex(), ON_SubDEdge::NextEdge(), or ON_SubDFace::NextFace(). 
  /// </summary>
  /// <returns>
  /// An ON_SubDComponentPtr to the next active component of the same type in the SubD
  /// or ON_SubDComponentPtr::Null if there is no next active component.
  /// </returns>
  const ON_SubDComponentPtr NextComponent() const;

  /// <summary>
  /// Depending on the type of this component, returns an ON_SubDComponentPtr to
  /// ON_SubDVertex::PrevVertex(), ON_SubDEdge::PrevEdge(), or ON_SubDFace::PrevFace(). 
  /// </summary>
  /// <returns>
  /// An ON_SubDComponentPtr to the previous active component of the same type in the SubD
  /// or ON_SubDComponentPtr::Null if there is no previous active component.
  /// </returns>
  const ON_SubDComponentPtr PrevComponent() const;

  /// <summary>
  /// Prefix operator ++ sets this to ON_SubDComponentPtr::NextComponent() 
  /// and returns the new value of this.
  /// </summary>
  /// <returns>ON_SubDComponentPtr::NextComponent()</returns>
  const ON_SubDComponentPtr operator++();

  /// <summary>
  /// Postfix operator ++ sets this to ON_SubDComponentPtr::NextComponent() 
  /// and returns the previous value of this.
  /// </summary>
  /// <returns>*this, before increment</returns>
  const ON_SubDComponentPtr operator++(int);


  wchar_t* ToString(
    wchar_t* s,
    size_t s_capacity
  ) const;

  const ON_wString ToString() const;

};

ON_DECL
bool operator==(ON_SubDComponentPtr lhs, ON_SubDComponentPtr rhs);

ON_DECL
bool operator!=(ON_SubDComponentPtr lhs, ON_SubDComponentPtr rhs);

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_SubDComponentPtr>;
#endif

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDComponentPtrAndNumber
//

class ON_CLASS ON_SubDComponentAndNumber
{
public:
  ON_SubDComponentAndNumber() = default;
  ~ON_SubDComponentAndNumber() = default;
  ON_SubDComponentAndNumber(const ON_SubDComponentAndNumber&) = default;
  ON_SubDComponentAndNumber& operator=(const ON_SubDComponentAndNumber&) = default;

public:
  static const ON_SubDComponentAndNumber NullAndNan;
  static const ON_SubDComponentAndNumber NullAndZero;
  static const ON_SubDComponentAndNumber Create(
    ON_SubDComponentPtr cptr,
    double x
  );

  static const ON_SubDComponentAndNumber Create(
    const ON_SubDVertex* v,
    double x
  );
  static const ON_SubDComponentAndNumber Create(
    const ON_SubDEdge* e,
    double x
  );
  static const ON_SubDComponentAndNumber Create(
    const ON_SubDFace* f,
    double x
  );

  static const ON_SubDComponentAndNumber Create(
    const ON_SubDVertexPtr vptr,
    double x
  );

  static const ON_SubDComponentAndNumber Create(
    const ON_SubDEdgePtr eptr,
    double x
  );

  static const ON_SubDComponentAndNumber Create(
    const ON_SubDFacePtr fptr,
    double x
  );

public:

  /*
  Description:
    Compare Component() using ON_SubDComponentPtr::CompareComponent().
  */
  static int CompareComponent(
    const ON_SubDComponentAndNumber* a,
    const ON_SubDComponentAndNumber* b
  );

  /*
  Description:
    Compare Component() using ON_SubDComponentPtr::CompareComponentAndDirection().
  */
  static int CompareComponentAndDirection(
    const ON_SubDComponentAndNumber* a,
    const ON_SubDComponentAndNumber* b
  );


  /*
  Description:
    Compare Number() nans are treated as equal and sort last.
  */
  static int CompareNumber(
    const ON_SubDComponentAndNumber* a,
    const ON_SubDComponentAndNumber* b
  );

  /*
  Description:
    Dictionary compare Component() and Number() in that order.
  */
  static int CompareComponentAndNumber(
    const ON_SubDComponentAndNumber* a,
    const ON_SubDComponentAndNumber* b
  );

  /*
  Description:
    Dictionary compare using ON_SubDComponentAndNumber::CompareComponentAndDirection() and ON_SubDComponentAndNumber::Number() in that order.
  */
  static int CompareComponentAndDirectionAndNumber(
    const ON_SubDComponentAndNumber* a,
    const ON_SubDComponentAndNumber* b
  );


public:
  const ON_SubDComponentPtr Component() const;
  void SetComponent(ON_SubDComponentPtr cptr);

  double Number() const;
  void SetNumber(double x);

public:
  ON_SubDComponentPtr m_cptr = ON_SubDComponentPtr::Null;
  double m_x = ON_DBL_QNAN;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_SubDComponentAndNumber>;
#endif

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDComponentAndPoint
//

class ON_CLASS ON_SubDComponentAndPoint
{
public:
  ON_SubDComponentAndPoint() = default;
  ~ON_SubDComponentAndPoint() = default;
  ON_SubDComponentAndPoint(const ON_SubDComponentAndPoint&) = default;
  ON_SubDComponentAndPoint& operator=(const ON_SubDComponentAndPoint&) = default;

public:
  static const ON_SubDComponentAndPoint NullAndNan;
  static const ON_SubDComponentAndPoint NullAndOrigin;
  static const ON_SubDComponentAndPoint Create(
    ON_SubDComponentPtr cptr,
    ON_3dPoint P
  );

  static const ON_SubDComponentAndPoint Create(
    const ON_SubDVertex* v,
    ON_3dPoint P
  );
  static const ON_SubDComponentAndPoint Create(
    const ON_SubDEdge* e,
    ON_3dPoint P
  );
  static const ON_SubDComponentAndPoint Create(
    const ON_SubDFace* f,
    ON_3dPoint P
  );

  static const ON_SubDComponentAndPoint Create(
    const ON_SubDVertexPtr vptr,
    ON_3dPoint P
  );

  static const ON_SubDComponentAndPoint Create(
    const ON_SubDEdgePtr eptr,
    ON_3dPoint P
  );

  static const ON_SubDComponentAndPoint Create(
    const ON_SubDFacePtr fptr,
    ON_3dPoint P
  );

public:

  /*
  Description:
    Compare Component() using ON_SubDComponentPtr::CompareComponent().
  */
  static int CompareComponent(
    const ON_SubDComponentAndPoint* lhs,
    const ON_SubDComponentAndPoint* rhs
  );

  /*
  Description:
    Compare Component() using ON_SubDComponentPtr::CompareComponentAndDirection().
  */
  static int CompareComponentAndDirection(
    const ON_SubDComponentAndPoint* lhs,
    const ON_SubDComponentAndPoint* rhs
  );


  /*
  Description:
    Compare Point() uses ON_3dPoint::Compare() to compare lhs and rhs Point() values.
  */
  static int ComparePoint(
    const ON_SubDComponentAndPoint* lhs,
    const ON_SubDComponentAndPoint* rhs
  );

  /*
  Description:
    Dictionary compare Component() and Point() in that order.
  */
  static int CompareComponentAndPoint(
    const ON_SubDComponentAndPoint* lhs,
    const ON_SubDComponentAndPoint* rhs
  );

  /*
  Description:
    Dictionary compare using ON_SubDComponentAndPoint::CompareComponentAndDirection() and ON_SubDComponentAndPoint::Point() in that order.
  */
  static int CompareComponentAndDirectionAndPoint(
    const ON_SubDComponentAndPoint* lhs,
    const ON_SubDComponentAndPoint* rhs
  );


public:
  const ON_SubDComponentPtr Component() const;
  void SetComponent(ON_SubDComponentPtr cptr);

  const ON_3dPoint Point() const;
  void SetPoint(ON_3dPoint P);

public:
  ON_SubDComponentPtr m_cptr = ON_SubDComponentPtr::Null;
  ON_3dPoint m_P = ON_3dPoint::NanPoint;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_SubDComponentAndPoint>;
#endif

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDComponentTest
//

/*
Description:
  ON_SubDComponentTest is used in contexts where custom testing or filtering of
  SubD components is required.
*/
class ON_CLASS ON_SubDComponentTest
{
public:
  ON_SubDComponentTest() = default;
  virtual ~ON_SubDComponentTest();
  ON_SubDComponentTest(const ON_SubDComponentTest&) = default;
  ON_SubDComponentTest& operator=(const ON_SubDComponentTest&) = default;

  /*
    Sets m_ptr=ptr
  */
  ON_SubDComponentTest(ON__UINT_PTR ptr);

  /*
  Description:
    Typically, a derived class overrides this function, uses it to inspect vertex properties,
    and returns true or false.
  Parameters:
    v - [in] vertex being tested.
  Returns:
    true if the vertex "passes" the test.
    false if the vertex "fails" the text.
  Remarks:
    The default implementation returns (cptr.IsNotNull() && 0 != m_ptr);
  */
  virtual bool Passes(const ON_SubDComponentPtr cptr) const;

  /*
  Returns:
    this->Passes(nullptr != v ? v->ComponentPtr() : ON_SubDComponentPtr::Null);
  */
  bool Passes(const class ON_SubDVertex* v) const;

  /*
  Returns:
    this->Passes(nullptr != e ? e->ComponentPtr() : ON_SubDComponentPtr::Null);
  */
  bool Passes(const class ON_SubDEdge* e) const;

  /*
  Returns:
    this->Passes(nullptr != f ? f->ComponentPtr() : ON_SubDComponentPtr::Null);
  */
  bool Passes(const class ON_SubDFace* f) const;

  // Passes() returns true for every non nullptr component.
  static const ON_SubDComponentTest AllPass;

  // Passes() returns false for every component.
  static const ON_SubDComponentTest AllFail;

protected:
  // classes derived from ON_SubDVertexFilter may use m_ptr as they see fit including to completely ignore it.
  ON__UINT_PTR m_ptr = 0;
};

class ON_CLASS ON_SubDComponentId
{
public:

  // type = unset and id = 0;
  static const ON_SubDComponentId Unset;

  ON_SubDComponentId() = default;
  ~ON_SubDComponentId() = default;
  ON_SubDComponentId(const ON_SubDComponentId&) = default;
  ON_SubDComponentId& operator=(const ON_SubDComponentId&) = default;

  ON_SubDComponentId(ON_SubDComponentPtr::Type component_type, unsigned int component_id);
  ON_SubDComponentId(ON_SubDComponentPtr::Type component_type, unsigned int component_id, ON__UINT_PTR dir);
  ON_SubDComponentId(ON_SubDComponentPtr cptr);
  ON_SubDComponentId(const class ON_SubDVertex* v);
  ON_SubDComponentId(ON_SubDVertexPtr vptr);
  ON_SubDComponentId(const class ON_SubDEdge* e);
  ON_SubDComponentId(ON_SubDEdgePtr eptr);
  ON_SubDComponentId(const class ON_SubDFace* f);
  ON_SubDComponentId(ON_SubDFacePtr fptr);
  ON_SubDComponentId(const class ON_SubDFace* f, unsigned face_corner_index);
  ON_SubDComponentId(ON_SubDFacePtr fptr, unsigned face_corner_index);
  ON_SubDComponentId(unsigned face_id, ON__UINT_PTR face_dir, ON_SubDFaceCornerDex face_cdex);

  static int CompareTypeAndId(const ON_SubDComponentId& lhs, const ON_SubDComponentId& rhs);
  static int CompareTypeAndIdAndDirection(const ON_SubDComponentId& lhs, const ON_SubDComponentId& rhs);
  static int CompareTypeAndIdFromPointer(const ON_SubDComponentId* lhs, const ON_SubDComponentId* rhs);

  /// <summary>
  /// Returns a string cN where N is ComponentId() and c is v, e or f for a vertex, edge or face component.
  /// Examples:
  /// If ComponentType is vertex and ComponentId() is 17, then the string will be "v17".
  /// If ComponentType is face, ComponentId() is 49, and FaceCornerDex is not set, 
  /// the string will be "f49".
  /// If ComponentType is face, ComponentId() is 49, and FaceCornerDex() is ON_SubDFaceCornerDex(2,3), 
  /// the string will be "f49.2".
  /// </summary>
  /// <param name="bUnsetIsEmptyString">
  /// If bUnsetIsEmptyString is truen, then an unset component id returns the empty string.
  /// Otherwise and unset component id returns "unset".
  /// </param>
  /// <param name="bOrientationPrefix">
  /// If bDirectionPrefix is true, then the string begins with "+" when
  /// ComponentDirection() is 0 and "-" when ComponentDirection() is 1.
  /// </param>
  /// <returns></returns>
  const ON_wString ToString( 
    bool bUnsetIsEmptyString,
    bool bDirectionPrefix 
  ) const;

  /// <returns>
  /// The type of the referenced component.
  /// </returns>
  ON_SubDComponentPtr::Type ComponentType() const;

  /// <returns>
  /// The id of the reference component. 0 means the id is not set.
  /// </returns>
  unsigned int ComponentId() const;

  /// <returns>
  /// 0 or 1. 
  /// 1 indicates the orientation or direction of the referenced components
  /// is opposite its intrinsic orientation or direction.
  /// </returns>
  unsigned int ComponentDirection() const;

  /*
  Returns:
    true if id > 0 and type is set to vertex, edge or face.
  */
  bool IsSet() const;

  /*
  Returns:
    true if type is unset or id is 0.
  */
  bool IsNotSet() const;

  /// <returns>
  /// True if id > 0 and type = vertex.
  /// </returns>
  bool IsVertexId() const;

  /// <returns>
  /// True if id > 0 and type = edge.
  /// </returns>
  bool IsEdgeId() const;

  /// <returns>
  /// True if id > 0 and type = face.
  /// </returns>
  bool IsFaceId() const;

  /// <summary>
  /// Create an ON_SubDComponentId that references the same SubD component
  /// but with the opposite value of this->ComponentDirection().
  /// </summary>
  /// <returns>A ON_SubDComponentId with the same type, same id, and opposite direction.</returns>
  const ON_SubDComponentId Reversed() const;

  /// <summary>
  /// Get the referenced SubD component from a component id.
  /// </summary>
  /// <param name="subd">
  /// The subd containing the referenced component.
  /// </param>
  /// <returns>
  /// The referenced SubD component from subd.
  /// </returns>
  const ON_SubDComponentPtr ComponentPtr(const class ON_SubD& subd) const;

  /// <summary>
  /// Get the referenced SubD component from a component id.
  /// </summary>
  /// <param name="subd">
  /// The subd containing the referenced component.
  /// </param>
  /// <returns>
  /// The referenced SubD component from subd.
  /// </returns>
  const ON_SubDComponentPtr ComponentPtr(const class ON_SubD* subd) const;

  unsigned VertexId() const;
  const ON_SubDVertex* Vertex(const class ON_SubD& subd) const;
  const ON_SubDVertexPtr VertexPtr(const class ON_SubD& subd) const;
  const ON_SubDVertex* Vertex(const class ON_SubD* subd) const;
  const ON_SubDVertexPtr VertexPtr(const class ON_SubD* subd) const;

  unsigned EdgeId() const;
  const ON_SubDEdge* Edge(const class ON_SubD& subd) const;
  const ON_SubDEdgePtr EdgePtr(const class ON_SubD& subd) const;
  const ON_SubDEdge* Edge(const class ON_SubD* subd) const;
  const ON_SubDEdgePtr EdgePtr(const class ON_SubD* subd) const;

  unsigned FaceId() const;
  const ON_SubDFace* Face(const class ON_SubD& subd) const;
  const ON_SubDFacePtr FacePtr(const class ON_SubD& subd) const;
  const ON_SubDFace* Face(const class ON_SubD* subd) const;
  const ON_SubDFacePtr FacePtr(const class ON_SubD* subd) const;
  const ON_SubDFaceCornerDex FaceCornerDex() const;

private:
  unsigned int m_id = 0;
  
  unsigned char m_type_and_dir = 0;
  enum : unsigned char
  {
    bits_dir_mask = 0x01,
    bits_type_mask = 0x06,
    // the remaining bits may be used in the future
  };
  void Internal_SetType(ON_SubDComponentPtr::Type type);
  void Internal_SetDir(unsigned dir);

  // The "A" and "B" values are two 12 bit unsigned integer values 
  // (0 to 4095 decimal) that are encoded in the 3 bytes m_valueAB[].
  // When the referenced component is a SubD face, A = number of face edges
  // and B = face corner index.
  void Internal_SetValueA(unsigned a);
  void Internal_SetValueB(unsigned b);
  unsigned Internal_ValueA() const;
  unsigned Internal_ValueB() const;
  unsigned char m_valueAB[3] = {};
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_SubDComponentId>;
#endif

class ON_CLASS ON_SubDComponentIdList : public ON_SubDComponentTest
{
public:
  ON_SubDComponentIdList() = default;
  ~ON_SubDComponentIdList() = default;
  ON_SubDComponentIdList(const ON_SubDComponentIdList&) = default;
  ON_SubDComponentIdList& operator=(const ON_SubDComponentIdList&) = default;

  /*
  Returns:
    returns InListPassesResult() when cptr id is in the list.
    returns !InListPassesResult() when cptr id is not the list.
  Remarks:
    AddId is safe to use in multithreaded contexts.
  */
  bool Passes(const ON_SubDComponentPtr cptr) const override;

  void SetInListPassesResult(bool bInListPassesResult);

  // Value Passes(cptr) returns when cptr is in the list
  bool InListPassesResult() const;

  void AddId(ON_SubDComponentId cid);

  void AddId(ON_SubDComponentPtr cptr);

  /*
  Add all Ids in list to m_id_list. Do not sort or remove duplicates.
  Assumes list elements all pass el.IsSet().
  Parameters:
    list - in
  */
  void AddIdList(const ON_SubDComponentIdList& list);

  unsigned int UnsignedCount() const;

  ON_SubDComponentId operator[](unsigned int i) const;

  /*
  Parameters:
    cid - in
  Returns:
    true if cid is in this list.
  */
  bool InList(ON_SubDComponentId cid) const;

  /*
  Parameters:
    cptr - in
  Returns:
    true if cptr's id is in this list.
  */
  bool InList(ON_SubDComponentPtr cptr) const;

private:
  unsigned int m_reserved1 = 0;
private:
  unsigned short m_reserved2 = 0;
private:
  bool m_bInListPassesResult = true;
private:
  mutable bool m_bSorted = false;
  mutable ON_SimpleArray<ON_SubDComponentId> m_id_list;
};

class ON_CLASS ON_SubDComponentPtrPair
{
public:
  // For performance reasons, m_ptrpair is not initialized and no constructors are declared
  // or implemented.  If you require initialization, then use x = ON_SubDComponentPtrPair::Null
  // or x = ON_SubDComponentPtr::Create(first_ptr,second_ptr).
  ON_SubDComponentPtr m_pair[2];

public:
  static const ON_SubDComponentPtrPair Create(ON_SubDComponentPtr first_ptr, ON_SubDComponentPtr second_ptr);

  /*
  Description:
    Dictionary order compare using ON_SubDComponentPtr::CompareComponent() on each element.
  */
  static int CompareComponent(const ON_SubDComponentPtrPair * lhs, const ON_SubDComponentPtrPair * rhs);

  /*
  Description:
    Dictionary order compare using ON_SubDComponentPtr::CompareComponentAndDirection() on each element.
  */
  static int CompareComponentAndDirection(const ON_SubDComponentPtrPair * lhs, const ON_SubDComponentPtrPair * rhs);

  /*
  Description:
    Compare first pointer value.
  */
  static int CompareFirstPointer(const ON_SubDComponentPtrPair * lhs, const ON_SubDComponentPtrPair * rhs);

  /*
  Returns:
    A pair with components in the opposite order
  */
  const ON_SubDComponentPtrPair SwapPair() const;


  /*
  Returns:
    A pair with components reversed.
  */
  const ON_SubDComponentPtrPair ReversedPair() const;

  /*
  Returns:
    First ON_SubDComponentPt in the pair.
  */
  const ON_SubDComponentPtr First() const;

  /*
  Returns:
    Second ON_SubDComponentPt in the pair.
  */
  const ON_SubDComponentPtr Second() const;

  /*
  Returns:
    If both points have the same type, that type is returned.
    Otherwise ON_SubDComponentPtr::Type::Unset is returned.
  */
  ON_SubDComponentPtr::Type ComponentType() const;

  /*
    Returns FIrst().IsNull().
  */
  bool FirstIsNull() const;

  /*
    Returns Second().IsNull().
  */
  bool SecondIsNull() const;

  /*
    Returns First().IsNull() && Second().IsNull().
  */
  bool BothAreNull() const;
  
  /*
    Returns First().IsNotNull().
  */
  bool FirstIsNotNull() const;

  /*
    Returns Second().IsNotNull().
  */
  bool SecondIsNotNull() const;

  /*
    Returns FirstIsNotNull() && SecondIsNotNull().
  */
  bool BothAreNotNull() const;

public:
  static const ON_SubDComponentPtrPair Null;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_SubDComponentPtrPair>;
#endif

class ON_CLASS ON_SubDComponentPtrPairHashTable : ON_Hash32Table
{
public:
  ON_SubDComponentPtrPairHashTable();

  /// <summary>
  /// This is a good choice of constructor when you have a good estimate of 
  /// the number of pairs that will be in the hash table.
  /// </summary>
  /// <param name="pair_count_estimate">
  /// A good estimate of the number of pairs that will be in this hash table.
  /// </param>
  ON_SubDComponentPtrPairHashTable(size_t pair_count_estimate);


  /// <summary>
  /// This is a good choice of constructor when the hash table is used
  /// to find pairs of vertices and edges.
  /// </summary>
  /// <param name="subd">
  /// subd.VertexCount() + subd.EdgeCount() is used as the pair count estimate.
  /// </param>
  ON_SubDComponentPtrPairHashTable(const class ON_SubD& subd);

  ~ON_SubDComponentPtrPairHashTable() = default;
  
  bool AddComponentPair(
    ON_SubDComponentPtr first_component,
    ON_SubDComponentPtr second_component
  );

  bool AddVertexPair(
    const class ON_SubDVertex* first_v,
    const class ON_SubDVertex* second_v
  );

  bool AddEdgePair(
    const class ON_SubDEdge* first_e,
    const class ON_SubDEdge* second_e
  );

  bool AddEdgePair(
    const class ON_SubDEdge* first_e,
    const ON_SubDEdgePtr second_eptr
  );

  bool AddFacePair(
    const class ON_SubDFace* first_f,
    const class ON_SubDFace* second_f
  );

  const ON_SubDComponentPtrPair PairFromSecondComponentPtr(
    ON_SubDComponentPtr second_component
  );

  const ON_SubDComponentPtrPair PairFromSecondVertex(
    const class ON_SubDVertex* second_v
  );

  const ON_SubDComponentPtrPair PairFromSecondEdge(
    const class ON_SubDEdge* second_e
  );

  const ON_SubDComponentPtrPair PairFromSecondFace(
    const class ON_SubDFace* second_f
  );

private:
  ON_FixedSizePool m_pairs_fsp;

private:
  ON_SubDComponentPtrPairHashTable(const ON_SubDComponentPtrPairHashTable&) = delete;
  ON_SubDComponentPtrPairHashTable& operator=(const ON_SubDComponentPtrPairHashTable&) = delete;
};

/// <summary>
/// Simple arrays of ON_SubD_ComponentIdTypeAndTag elements are used to save 
/// original tag values so the can be retrieved after complex editing operations.
/// </summary>
class ON_CLASS ON_SubD_ComponentIdTypeAndTag
{
public:
  static const ON_SubD_ComponentIdTypeAndTag Unset;

  /*
  Returns:
    If v is no nullptr and v->m_id > 0, a ON_SubD_ComponentIdTypeAndTag with VertexTag() = v->m_vertex_tag is returned.
    Otherwise ON_SubD_ComponentIdTypeAndTag::Unset is returned.
  */
  static const ON_SubD_ComponentIdTypeAndTag CreateFromVertex(const class ON_SubDVertex* v);

  /*
  Returns:
    If vertex_id > 0, a ON_SubD_ComponentIdTypeAndTag with VertexTag() = vtag is returned.
    Otherwise ON_SubD_ComponentIdTypeAndTag::Unset is returned.
  */
  static const ON_SubD_ComponentIdTypeAndTag CreateFromVertexId(unsigned vertex_id, ON_SubDVertexTag vtag);

  /*
  Parameters:
    e - [in]
      If e->m_edge_tag is ON_SubDEdgeTag::SmoothX, the ON_SubD_ComponentIdTypeAndTag EdgeTag() will be ON_SubDEdgeTag::Smoooth.
  Returns:
    If e is not nullptr and e->m_id > 0, a ON_SubD_ComponentIdTypeAndTag with EdgeTag() = e->m_edge_tag is returned.
    Otherwise ON_SubD_ComponentIdTypeAndTag::Unset is returned.
  */
  static const ON_SubD_ComponentIdTypeAndTag CreateFromEdge(const class ON_SubDEdge* e);

  /*
  Parameters:
    eptr - [in]
      If e->m_edge_tag is ON_SubDEdgeTag::SmoothX, the ON_SubD_ComponentIdTypeAndTag EdgeTag() will be ON_SubDEdgeTag::Smoooth.
  Returns:
    If e is not nullptr and e->m_id > 0, a ON_SubD_ComponentIdTypeAndTag with EdgeTag() = e->m_edge_tag is returned.
    Otherwise ON_SubD_ComponentIdTypeAndTag::Unset is returned.
  */
  static const ON_SubD_ComponentIdTypeAndTag CreateFromEdge(const class ON_SubDEdgePtr eptr);


  /*
  Parameters:
    edge_id - [in]
    etag - [in]
      If etag is ON_SubDEdgeTag::SmoothX, the ON_SubD_ComponentIdTypeAndTag EdgeTag() will be ON_SubDEdgeTag::Smoooth.
  Returns:
    If edge_id > 0, a ON_SubD_ComponentIdTypeAndTag with EdgeTag() = etag is returned.
    Otherwise ON_SubD_ComponentIdTypeAndTag::Unset is returned.
  */
  static const ON_SubD_ComponentIdTypeAndTag CreateFromEdgeId(unsigned edge_id, ON_SubDEdgeTag etag);

  /*
  Parameters:
    edge_id - [in]
    etag - [in]
      If etag is ON_SubDEdgeTag::SmoothX, the ON_SubD_ComponentIdTypeAndTag EdgeTag() will be ON_SubDEdgeTag::Smoooth.
  Returns:
    If edge_id > 0, a ON_SubD_ComponentIdTypeAndTag with EdgeTag() = etag is returned.
    Otherwise ON_SubD_ComponentIdTypeAndTag::Unset is returned.
  */
  static const ON_SubD_ComponentIdTypeAndTag CreateFromEdgeId(unsigned edge_id, ON_SubDEdgeTag etag, ON_SubDEdgeSharpness sharpness);


  /*
  Parameters:
    f - [in]
    ftag - [in]
      Any value and the interpretation is up to the context using the ON_SubD_ComponentIdTypeAndTag.
  Returns:
    If f is no nullptr and f->m_id > 0, a ON_SubD_ComponentIdTypeAndTag with FaceTag() = ftag is returned.
    Otherwise ON_SubD_ComponentIdTypeAndTag::Unset is returned.
  Remarks:
    SubD faces do not have a tag in the sense that vertices and edges do, but in complex editing tasks
    it is sometimes useful to include faces in an array of ON_SubD_ComponentIdTypeAndTag elements.
  */
  static const ON_SubD_ComponentIdTypeAndTag CreateFromFace(const class ON_SubDFace* f, unsigned char ftag);

  /*
  Parameters:
    face_id - [in]
    ftag - [in]
      Any value from 0 to 7. The interpretation is up to the context using the ON_SubD_ComponentIdTypeAndTag.
  Returns:
    If face_id > 0, a ON_SubD_ComponentIdTypeAndTag with FaceTag() = vtag is returned.
    Otherwise ON_SubD_ComponentIdTypeAndTag::Unset is returned.
  Remarks:
    SubD faces do not have a tag in the sense that vertices and edges do, but in complex editing tasks
    it is sometimes useful to include faces in an array of ON_SubD_ComponentIdTypeAndTag elements.
  */
  static const ON_SubD_ComponentIdTypeAndTag CreateFromFaceId(unsigned face_id, unsigned char ftag);

  /*
  Description:
    Dictionary compare on ComponentType() and ComponentId() in that order.
  */
  static int CompareTypeAndId(const ON_SubD_ComponentIdTypeAndTag* lhs, const ON_SubD_ComponentIdTypeAndTag* rhs);

  /*
  Description:
    Dictionary compare on ComponentType(), ComponentId(), and tag in that order.
  */
  static int CompareTypeAndIdAndTag(const ON_SubD_ComponentIdTypeAndTag* lhs, const ON_SubD_ComponentIdTypeAndTag* rhs);

  static const ON_SubD_ComponentIdTypeAndTag FindFromTypeAndId(ON_SubDComponentPtr::Type type, unsigned id, const ON_SimpleArray< ON_SubD_ComponentIdTypeAndTag>& sorted_tags);

  /*
  Parameters:
    v - [in]
    sorted_tags[] - [in]
      Array sorted by ON_SubD_ComponentIdTypeAndTag::CompareTypeAndId().
  Returns:
    If v is in sorted_tags[], the VertexTag() from from sorted_tags[] is returned.
    Otherwise v->m_vertex_tag is returned.
  */
  static ON_SubDVertexTag OriginalVertexTag(
    const class ON_SubDVertex* v,
    const ON_SimpleArray< ON_SubD_ComponentIdTypeAndTag>& sorted_tags
  );

  /*
  Parameters:
    vertex_id - [in]
    sorted_tags[] - [in]
      Array sorted by ON_SubD_ComponentIdTypeAndTag::CompareTypeAndId().
  Returns:
    If vertex_id is in sorted_tags[], the VertexTag() from from sorted_tags[] is returned.
    Otherwise ON_SubDVertexTag::Unset is returned.
  */
  static ON_SubDVertexTag OriginalVertexTag(
    unsigned vertex_id,
    const ON_SimpleArray< ON_SubD_ComponentIdTypeAndTag>& sorted_tags
  );

  /*
  Parameters:
    e - [in]
    sorted_tags[] - [in]
      Array sorted by ON_SubD_ComponentIdTypeAndTag::CompareTypeAndId().
  Returns:
    If e is in sorted_tags[], the EdgeTag() from from sorted_tags[] is returned.
    Otherwise e->m_edge_tag is returned.
  */
  static ON_SubDEdgeTag OriginalEdgeTag(
    const class ON_SubDEdge* e,
    const ON_SimpleArray< ON_SubD_ComponentIdTypeAndTag>& sorted_tags
  );

  /*
  Parameters:
    edge_id - [in]
    sorted_tags[] - [in]
      Array sorted by ON_SubD_ComponentIdTypeAndTag::CompareTypeAndId().
  Returns:
    If edge_id is in sorted_tags[], the EdgeTag() from from sorted_tags[] is returned.
    Otherwise ON_SubDEdgeTag::Unset is returned.
  */
  static ON_SubDEdgeTag OriginalEdgeTag(
    unsigned edge_id,
    const ON_SimpleArray< ON_SubD_ComponentIdTypeAndTag>& sorted_tags
  );

  /*
  Parameters:
    f - [in]
    sorted_tags[] - [in]
      Array sorted by ON_SubD_ComponentIdTypeAndTag::CompareTypeAndId().
  Returns:
    If f is in sorted_tags[], the FaceTag() from from sorted_tags[] is returned.
    Otherwise 0 is returned.
  */
  static unsigned char OriginalFaceTag(
    const class ON_SubDFace* f,
    const ON_SimpleArray< ON_SubD_ComponentIdTypeAndTag>& sorted_tags
  );

  /*
  Parameters:
    face_id - [in]
    sorted_tags[] - [in]
      Array sorted by ON_SubD_ComponentIdTypeAndTag::CompareTypeAndId().
  Returns:
    If face_id is in sorted_tags[], the FaceTag() from from sorted_tags[] is returned.
    Otherwise ON_SubDFaceTag::Unset is returned.
  */
  static unsigned char OriginalFaceTag(
    unsigned face_id,
    const ON_SimpleArray< ON_SubD_ComponentIdTypeAndTag>& sorted_tags
  );

  ON_SubDComponentPtr::Type ComponentType() const;

  ON_SubDVertexTag VertexTag() const;

  unsigned VertexId() const;

  /*
  Returns:
    ON_SubDEdgeTag::Unset, ON_SubDEdgeTag::Smooth, or ON_SubDEdgeTag::Crease.
  */
  ON_SubDEdgeTag EdgeTag() const;

  unsigned EdgeId() const;

  const ON_SubDEdgeSharpness EdgeSharpness(bool bUseCreaseSharpness) const;
  
  const double VertexSharpness() const;
  void SetVertexSharpness(double s);

  unsigned char FaceTag() const;

  unsigned FaceId() const;

  const ON_wString ToString() const;

private:
  // Dale lear 2024 Feb 20
  // Replaced unsued 
  // ON_SubDComponentPtr m_cptr 
  // with 
  // ON_SubDEdgeSharpness m_sharpness. 
  // 8 = sizeof(ON_SubDComponentPtr) = ON_SubDEdgeSharpness(ON_SubDEdgeSharpness),
  // so this switch does not change the sizeof(ON_SubD_ComponentIdTypeAndTag)
  // and everything involved is a private member. 
  // Thus, this change does not "break the SDK."
  ON_SubDEdgeSharpness m_sharpness = ON_SubDEdgeSharpness::Smooth;
  unsigned m_id = 0;
  ON_SubDComponentPtr::Type m_type = ON_SubDComponentPtr::Type::Unset;
  // tag = (0x07 & m_tag_and_dir).
  // dir = (0x80 & dir) ? 1 : 0; 1 = reversed.
  unsigned char m_tag_and_dirx = 0;

  // returns (0x07 & m_tag_and_dir);
  unsigned char Internal_Tag() const;

  void Internal_SetTag(unsigned char tag);

  // returns (0x80 & m_tag_and_dir) != 0 ? 1 : 0;
  unsigned char Internal_Dir() const;

  void Internal_SetDir(unsigned char dir);


  unsigned short m_reserved = 0;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_SubD_ComponentIdTypeAndTag>;
#endif


//////////////////////////////////////////////////////////////////////////
//
// ON_SubDSectorId
//

class ON_CLASS ON_SubDSectorId
{
public:
  ON_SubDSectorId() = default;
  ~ON_SubDSectorId() = default;
  ON_SubDSectorId(const ON_SubDSectorId&) = default;
  ON_SubDSectorId& operator=(const ON_SubDSectorId&) = default;

public:
  // VertexId(), MinimumFaceId(), and SectorFaceCount() are all zero.
  static const ON_SubDSectorId Zero;

  // VertexId() and MinimumFaceId() are zero. SectorFaceCount() = 0xFFFFFFFF;
  static const ON_SubDSectorId Invalid;

public:
  /*
  Description:
    Dictionary compare of VertexId() and MinimumFaceId() in that order.
  */
  static int CompareVertexIdAndMinimumFaceId(ON_SubDSectorId lhs, ON_SubDSectorId rhs);

  static int CompareVertexId(ON_SubDSectorId lhs, ON_SubDSectorId rhs);
  static int CompareMinimumFaceId(ON_SubDSectorId lhs, ON_SubDSectorId rhs);

  /*
  Description:
    Dictionary compare of VertexId() and MinimumFaceId() in that order.
  */
  static int CompareVertexIdAndMinimumFaceIdFromPointers(const ON_SubDSectorId* lhs, const ON_SubDSectorId* rhs);

  static int CompareVertexIdFromPointers(const ON_SubDSectorId* lhs, const ON_SubDSectorId* rhs);
  static int CompareMinimumFaceIdFromPointers(const ON_SubDSectorId* lhs, const ON_SubDSectorId* rhs);

  /*
  Description:
    Dictionary compare of VertexId(), MinimumFaceId(), and SectorFaceCount() in that order.
  */
  static int Compare(ON_SubDSectorId lhs, ON_SubDSectorId rhs);

  /*
  Description:
    Dictionary compare of VertexId(), MinimumFaceId(), and SectorFaceCount() in that order.
  */
  static int CompareFromPointers(const ON_SubDSectorId* lhs, const ON_SubDSectorId* rhs);

  // No initialized construction for performance reasons.
  // If initialization is required, then use sector_id = ON_SubDSectorId::Zero or sector_id = ON_SubDSectorId::Create(...).

  /*
  Description:
    Create a sector id from a vertex and face in the sector. A sector id uniquely identifies
    a sector in the context of a single ON_SubD.
  Parameters:
    vertex - [in]
    face - [in]
      A face in the sector.
      If vertex->IsSingleSectorVertex() is true, then face can be nullptr.
  Returns:
    If the vertex and face are not nullptr and the face is in a sector of the vertex,
    a nonzero zector id is returned. Otherwise ON_SubDSectorId::Invalid is returned.
  */
  static const ON_SubDSectorId Create(
    const class ON_SubDVertex* vertex,
    const class ON_SubDFace* face
  );

  /*
  Description:
    This function is used to create ON_SubDSectorId values for searching or comparing
    to values from ON_SubDSectorId::Create(). Use ON_SubDSectorId::Create() for all
    other uses.
  Parameters:
    vertex - [in]
    face - [in]
      A face in the sector.
  Returns:
    A ON_SubDSectorId with the specified values for vertex_id and minimum_face_id.
    The sector face count will be zero.
  */
  static const ON_SubDSectorId CreateFromIds(
    unsigned int vertex_id,
    unsigned int minimum_face_id
  );

  /*
  Returns:
    The sector's center vertex id.
  Remarks:
    Either SectorId(), VertexId(), and MinimumFaceId() are all zero or are all nonzero.
  */
  const unsigned int VertexId() const;

  /*
  Returns:
    The sector's minimum face id.
  */
  const unsigned int MinimumFaceId() const;

  /*
  Returns:
    Number of faces in the sector.
  */
  const unsigned int SectorFaceCount() const;

  /*
  Returns:
    True if this sector id is zero.
  */
  bool IsZero() const;

  /*
  Returns:
    True if VertexId(), MinimumFaceId(), and SectorFaceCount() are all not zero.
  */
  bool IsSet() const;

  /*
  Parameters:
    bVerbose - [in]
      If true, the returned string begins with ON_SubDSectorId.
  Returns:
    "Zero", "Invalid", or "vX.fYxN" where X is VertexId(), Y is MinimumFaceId(), and N is the SectorFaceCount().
  */
  const ON_wString ToString(bool bVerbose) const;

  /*
  Parameters:
     s - [in]
       beginning of string buffer
     s_capacity
       wchar_t element capacity of the string buffer
  Returns:
    nullptr if ther is not enough room in the buffer.
    Otherwise a pointer to the null terminator of the returned string.
  Remarks
    The returned string will be "0" for a zero sector id, "X" for an invalid sector id, 
    or "vX.fYxN" where X is VertexId(), Y is MinimumFaceId(), and N is the SectorFaceCount().
  */
  wchar_t* ToString(
    wchar_t* s,
    size_t s_capacity
  ) const;

private:
  unsigned int m_vertex_id = 0;
  // minimum face id in the sector. Since a face can be in only one sector, the
  // combination of m_vertex_id and m_minimum_face_id uniquely identify a sector
  // in the context of a single ON_SubD.
  unsigned int m_minimum_face_id = 0;
  // number of faces in the sector
  unsigned int m_sector_face_count = 0;
};

ON_DECL
bool operator==(ON_SubDSectorId, ON_SubDSectorId);

ON_DECL
bool operator!=(ON_SubDSectorId, ON_SubDSectorId);

ON_DECL
bool operator>(ON_SubDSectorId, ON_SubDSectorId);

ON_DECL
bool operator<(ON_SubDSectorId, ON_SubDSectorId);

ON_DECL
bool operator>=(ON_SubDSectorId, ON_SubDSectorId);

ON_DECL
bool operator<=(ON_SubDSectorId, ON_SubDSectorId);

class ON_CLASS ON_SubDVertexSurfacePointCoefficient
{
public: 
  ON_SubDVertexSurfacePointCoefficient() = default;
  ~ON_SubDVertexSurfacePointCoefficient() = default;
  ON_SubDVertexSurfacePointCoefficient(const ON_SubDVertexSurfacePointCoefficient&) = default;
  ON_SubDVertexSurfacePointCoefficient& operator=(const ON_SubDVertexSurfacePointCoefficient&) = default;

public:

  // ON_SubDVertexSurfacePointCoefficient::Zero.m_c = 0.0
  static const ON_SubDVertexSurfacePointCoefficient Zero;

  // ON_SubDVertexSurfacePointCoefficient::Nan.m_c = ON_DBL_QNAN
  static const ON_SubDVertexSurfacePointCoefficient Nan;

  // ON_SubDVertexSurfacePointCoefficient::Unset.m_c = ON_UNSET_VALUE
  static const ON_SubDVertexSurfacePointCoefficient Unset;

  static const ON_SubDVertexSurfacePointCoefficient Create(
    const ON_SubDVertex* limit_point_vertex,
    const ON_SubDVertex* ring_vertex,
    double x
  );

public: 
  static int CompareSurfacePointVertexId(
    const ON_SubDVertexSurfacePointCoefficient* lhs,
    const ON_SubDVertexSurfacePointCoefficient* rhs
  );

  static int CompareRingVertexId(
    const ON_SubDVertexSurfacePointCoefficient* lhs,
    const ON_SubDVertexSurfacePointCoefficient* rhs
  );

  static int CompareSurfacePointAndRingVertexId(
    const ON_SubDVertexSurfacePointCoefficient* lhs,
    const ON_SubDVertexSurfacePointCoefficient* rhs
  );

  static int CompareRingAndSurfacePointVertexId(
    const ON_SubDVertexSurfacePointCoefficient* lhs,
    const ON_SubDVertexSurfacePointCoefficient* rhs
  );


public:
  const ON_SubDVertex* m_limit_point_vertex = nullptr;
  const ON_SubDVertex* m_ring_vertex = nullptr;
  // The limit point of m_limit_point_vertex
  // = sum of m_c*m_ring_vertex->ControlNetPoint()
  // for every point in the ring of m_limit_point_vertex, including m_limit_point_vertex.
  double m_c = 0.0;

public:
  unsigned int SurfacePointVertexId() const;
  unsigned int RingVertexId() const;
  double Coefficient() const;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_SubDVertexSurfacePointCoefficient>;
#endif

class ON_CLASS ON_SubDComponentRegionIndex
{
public:
  ON_SubDComponentRegionIndex() = default;
  ~ON_SubDComponentRegionIndex() = default;
  ON_SubDComponentRegionIndex(const ON_SubDComponentRegionIndex&) = default;
  ON_SubDComponentRegionIndex& operator=(const ON_SubDComponentRegionIndex&) = default;

public:
  enum : unsigned short
  {
    /// Capacity of the m_index[] array;
    IndexCapacity = 9
  };

  // All values are zero
  static const ON_SubDComponentRegionIndex Zero;

  // All values are 0xFFFF
  static const ON_SubDComponentRegionIndex Unset;

  /*
  Description:
    Compares subdivision counts. If the counts are the same, compares m_indices[].    
  */
  static int Compare(
    const ON_SubDComponentRegionIndex* lhs,
    const ON_SubDComponentRegionIndex* rhs
  );

  /*
  Description:
    Compares subdivision indices for minimum(lhs->m_subdivision_count,rhs->m_subdivision_count).
  */
  static int CompareMinimumSubregion(
    const ON_SubDComponentRegionIndex* lhs,
    const ON_SubDComponentRegionIndex* rhs
  );

  unsigned short Index(
    unsigned short i
  ) const;

  unsigned short m_subdivision_count = 0;

  // If m_subdivision_count > 0, then m_index[0], ..., m_index[m_subdivision_count-1]
  // identifies a subregion of the level 0 component.
  //
  // Faces with quad subdivision:
  //   m_index[n] is the subdivision quad for the region that contains
  //   the parent face's corner at face->m_vertex[m_index[n]].
  // Edges
  //   m_region_index[n] = 0 indicates the beginning half of the parent edge.
  //                       (begins at edge->Vertex(0))
  //   m_region_index[n] = 1 indicates the ending half of the parent edge.
  //                       (ends at edge->Vertex(1))
  //
  // When a component is created during a subdivision step, the value 0xFFFF
  // is used to mark the non-existent regions at earlier subdivision levels.
  // For example, if a level 1 edge is created by connecting 
  // a level0 edge subdivision point (middle-ish of the edge)
  // to a level0 face subdivision point (center-ish of the face),
  // then the level 1 edge would have 
  //   m_level0_component = ON_SubDComponentPtr::CreateNull(ON_SubDComponentPtr::Type::Edge, bReversed),
  //     (m_level0_component.IsNull() will be true)
  //   m_level0_component_id = ON_SubDComponentRegion::NewTransientId()
  //   m_subdivision_count = 1,
  //   m_region_index[0] = 0xFFFF.
  // 
  unsigned short m_index[ON_SubDComponentRegionIndex::IndexCapacity] = {};

  void Push(
    unsigned int region_index
  );
  
  void Pop();

  /*
  Description:
    Get a string of the form .a.b.c .a.b.c = m_index[] values.
  */
  wchar_t* ToString(
    wchar_t* s,
    size_t s_capacity
  ) const;

  const ON_wString ToString() const;

  /*
  Description:
    Encodes ON_SubDComponentRegionIndex information in 32 bits.
    (m_subdivision_count) << 24
    | (0x00FF0000 & ((m_region_index[0]) << 16))
    | (m_region_index[1] & 0x0003) << (14)
    | (m_region_index[2] & 0x0003) << (12)
    ...
    | (m_index[m_subdivision_count] & 0x0003) <<(16-(2*m_subdivision_count))
  Remarks:
    This is useful when quick compare and sorting of regions is required,
    m_subdivision_count < 256, m_index[0] < 256, m_index[1] < 4, ..., m_index[m_subdivision_count] < 4
    Regions of N-gons with N < 256 and regions of edges
    satisfy these condition when m_subdivision_count < 256 
    (which is always in real world situations).
  */
  ON__UINT32 ToCompressedRegionIndex() const;

  static const ON_SubDComponentRegionIndex FromCompressedRegionIndex(
    ON__UINT32 compressed_region_index
  );

  static ON__UINT32 ToCompressedRegionIndex(
    unsigned short subdivision_count,
    const unsigned short* region_index
  );

  /*
  Description:
    Decompress a 32-bit region.
  Parameters:
    region32 - [in]
      Value returned from To32BitRegion().
    subdivision_count - [out]
      Subdivision count
    region_index[] - out
      Region indices. The region_index[] array must have a capcity of at 
      least ON_SubDComponentRegion::region_index_capacity elements.
  */
  static void FromCompressedRegionIndex(
    ON__UINT32 compressed_region_index,
    unsigned short* subdivision_count,
    unsigned short* region_index
  );
};

class ON_CLASS ON_SubDComponentRegion
{
public:
  ON_SubDComponentRegion() = default;
  ~ON_SubDComponentRegion() = default;
  ON_SubDComponentRegion(const ON_SubDComponentRegion&) = default;
  ON_SubDComponentRegion& operator=(const ON_SubDComponentRegion&) = default;

public:
  static const ON_SubDComponentRegion Create(
    const class ON_SubDFace* level0_face
  );

  static const ON_SubDComponentRegion Create(
    unsigned int component_id,
    ON_SubDComponentPtr::Type component_type,
    bool bComponentMark
  );

  /*
  Description:
    Creates a region that can be used to identify a component
    created at a certain level of subdivision that does not
    come from dividing a component from the previous level.
    For example, Catmull Clark subdivision edges on level N+1
    that run from the level N edge subdivision point to the 
    level N face subdivision point.

    m_level0_component = ON_SubDComponentPtr::CreateNull(component_type, bComponentDirection?1:0),
       (m_level0_component.IsNull() will be true)
    m_level0_component_id = ON_SubDComponentRegion::NewTransientId()
    m_subdivision_count = subdivision_count,
     m_region_index[0, ..., (subdivision_count-1)] = 0xFFFF.
   
  */
  static const ON_SubDComponentRegion CreateSubdivisionRegion(
    ON_SubDComponentPtr::Type component_type,
    bool bComponentDirection,
    unsigned short subdivision_count,
    bool bAssignTransientId
  );

public:
  static const ON_SubDComponentRegion Empty;

public:
  ON_SubDComponentPtr m_level0_component = ON_SubDComponentPtr::Null;

  unsigned int m_level0_component_id = 0;

  unsigned short SubdivisionCount() const;

  ON_SubDComponentRegionIndex m_region_index;

  /*
  Returns:
    True if m_level0_component_id is a transient id.
  */
  bool IsTransientId() const;

  /*
  Returns:
    True if m_level0_component_id is the id of a persistent ON_SubD level 0 component.
  */
  bool IsPersistentId() const;

  /*
  Description:
    Compares 
    m_level0_component.ComponentType(), 
    m_level0_component_id,
    m_level0_component.ComponentDirection(),
    the entire sub region,
    and m_level0_component.m_ptr.
  */
  static int Compare(
    const ON_SubDComponentRegion* lhs,
    const ON_SubDComponentRegion* rhs
    );

  /*
  Descriptions:
    Compares 
    m_level0_component.ComponentType(), 
    m_level0_component_id,
    m_level0_component.ComponentDirection().
  */
  static int CompareTypeIdDirection(
    const ON_SubDComponentRegion* lhs,
    const ON_SubDComponentRegion* rhs
    );

  /*
  Description:
    Compares 
    m_level0_component.ComponentType(), 
    m_level0_component_id,
    m_level0_component.ComponentDirection(),
    and the m_region_index[] values for the 
    minimum subdivision count lhs and rhs.    
  */
  static int CompareTypeIdDirectionMinimumSubregion(
    const ON_SubDComponentRegion* lhs,
    const ON_SubDComponentRegion* rhs
    );
  
  /*
  Description:
    Compares 
    m_level0_component.ComponentType(), 
    m_level0_component_id,
    m_level0_component.ComponentDirection(),
    and the entire sub region.
  */
  static int CompareTypeIdDirectionSubregion(
    const ON_SubDComponentRegion* lhs,
    const ON_SubDComponentRegion* rhs
    );

  void SetLevel0Component(
    ON_SubDComponentPtr component_ptr
  );

  void SetLevel0Face(
    const ON_SubDFace* face
  );

  void SetLevel0EdgePtr(
    const ON_SubDEdgePtr edge_ptr
  );

  void SetLevel0Vertex(
    const ON_SubDVertex* vertex
  );

  /*
  Description:
    region_index - [in]
      If m_level0_component identifies an edge, region_index is 0 or 1,
      and the edge is reversed (1=m_level0_component.ComponentMark()),
      then PushAbsolute(1-region_index) is called.
      In every other case, PushAbsolute(region_index) is called.
  */
  void PushAdjusted(
    unsigned int region_index
  );

  /*
  Parameters:
    region_index - [in]
      If m_level0_component identifies a face, then region_index is the index of the
      corner vertex for the subdivision quad.
      If m_level0_component identifies an edge, then region_index must be 0 or 1.
  Description:
    Increments if m_subdivision_count and appends region_index to m_region_index[]
    (m_region_index[m_subdivision_count++] = region_index)
  */
  void PushAbsolute(
    unsigned int region_index
  );

  /*
  Description:
    Get a string of the form fN.a.b.c where N = m_level0_face-m_id, a.b.c = m_region_index[] values.
  */
  wchar_t* ToString(
    wchar_t* s,
    size_t s_capacity
  ) const;

  const ON_wString ToString() const;

  void Pop();

  bool IsEmptyRegion() const;

  enum : unsigned int
  {
    TransientIdBit = 0x80000000U
  };


  /*
  Returns:
    A value that can be used to identify transient subdivision components that do not
    exist in the persistent levels of a SubD.
    Transient ids always satisfy (ON_SubDComponentRegion::TransientIdBit & transient_id) is not zero and 
    (~ON_SubDComponentRegion::TransientIdBit & transient_id) is not zero.
  Remarks:
    Transient ids are used to identify subdivision components at levels that do
    not persist in the ON_SubD. They are unique within the context where they are
    being used. They generally vary with each repetition of a calcultion in that
    context.
  */
  static const unsigned int NewTransientId();

  /*
  Description:
    Resets the value used to generate transient ids.
    This is useful during debugging session so that transient id
    values are predictable. Otherwise, use of this function 
    should be avoided.
  */
  static void ResetTransientId();

  /*
  Parameters:
    id - [in]
      Value to test to see if it is a transient subd component id.
  Returns:
    True if (ON_SubDComponentRegion::TransientIdBit & id) is not zero and 
    (~ON_SubDComponentRegion::TransientIdBit & id) is not zero.
  Remarks:
    Transient ids are used to identify subdivision components at levels that do
    not persist in the ON_SubD. They are unique within the context where they are
    being used. They generally vary with each repetition of a calcultion in that
    context.
  */
  static bool IsTransientId(unsigned int id);

  /*
  Parameters:
    id - [in]
      Value to test to see if it is a transient subd component id.
  Returns:
    If the id is a transient id, then its id value is returned.
    Otherwise, 0 is returned.
  Remarks:
    Transient ids are used to identify subdivision components at levels that do
    not persist in the ON_SubD. They are unique within the context where they are
    being used. They generally vary with each repetition of a calcultion in that
    context.
  */
  static unsigned int TransientId(unsigned int id);

  /*
  Parameters:
    id - [in]
      Value to test to see if it is a persitsent subd component id.
  Returns:
    True if (ON_SubDComponentRegion::TransientIdBit & id) is not zero and 
    (~ON_SubDComponentRegion::TransientIdBit & id) is not zero.
  Remarks:
    Transient ids are used to identify subdivision components at levels that do
    not persist in the ON_SubD. They are unique within the context where they are
    being used. They generally vary with each repetition of a calcultion in that
    context.
  */
  static bool IsPersistentId(unsigned int id);
};

class ON_CLASS ON_SubDFaceRegion
{
public:
  ON_SubDFaceRegion() = default;
  ~ON_SubDFaceRegion() = default;
  ON_SubDFaceRegion(const ON_SubDFaceRegion&) = default;
  ON_SubDFaceRegion& operator=(const ON_SubDFaceRegion&) = default;

  static const ON_SubDFaceRegion Empty;

public:
  // Identifies a region of an ON_SubDFace
  ON_SubDComponentRegion m_face_region;

  const ON_SubDFace* Level0Face() const;

  // When the face region is a quad, m_edge_region[4] identifies regions of ON_SubDEdge elements.
  // When the face region is a sub-quad, these edges may be null or have null ON_SubDEdge pointers 
  // and the ids will be zero or ON_SubDComponentRegion::IsTransientId() will be true.
  // When ON_SubDComponentRegion::IsTransientId() is true, the id does not identify
  // a persistent edge in the ON_SubD.
  ON_SubDComponentRegion m_edge_region[4];

  unsigned int m_level0_edge_count = 0;

private:
  unsigned int m_reserved = 0;

public:
  /*
  Returns:
    If vertex_id > 0 and there is a unique element of m_vertex_id[] with the same value,
    the index of that element is returned (0,1,2 or 3).
    Otherwise ON_UNSET_UNINT_INDEX is returned.
  */
  unsigned int CornerIndexFromVertexId(
    unsigned int vertex_id
  ) const;


  // If set, these are the vertice ids at the region's limit surface corners.
  // m_vertex_id[] is mutable because these values appear during recursive calculations.
  // When the face region is a sub-quad, these ids will be zero or ON_SubDComponentRegion::IsTransientId()
  // will be true. 
  // When ON_SubDComponentRegion::IsTransientId() is true, the id does not identify
  // a persistent vertex in the ON_SubD.
  mutable unsigned int m_vertex_id[4] = {};

  // When a vertex is exceptional, a NURBS conversion is typically an approximation
  // of the SubD around the exceptional vertex. There are a variety of post processes
  // that can be applied in this case and the processes need to be applied 
  // sector by sector. 
  // Note well that when a level zero face is an N-gon with N != 4,
  // the face subdivision point is an exceptional smooth vertex with valence = N.
  // In this case the corresponding m_vertex_id[] value will be zero.
  mutable ON_SubDSectorId m_sector_id[4];

public:
  void Push(unsigned int quadrant_index);

  bool IsValid(
    bool bSilentError
  ) const;

  wchar_t* ToString(
    wchar_t* s,
    size_t s_capacity
  ) const;

  const ON_wString ToString() const;
};


class ON_CLASS ON_SubDFaceRegionAndNurbs
{
public:
  ON_SubDFaceRegionAndNurbs() = default;
  ~ON_SubDFaceRegionAndNurbs() = default;
  ON_SubDFaceRegionAndNurbs(const ON_SubDFaceRegionAndNurbs&) = default;
  ON_SubDFaceRegionAndNurbs& operator=(const ON_SubDFaceRegionAndNurbs&) = default;

  static const ON_SubDFaceRegionAndNurbs Empty;

public:
  ON_SubDFaceRegion m_face_region;
  // This pointer is not managed by ON_SubDFaceRegionAndNurbs
  class ON_NurbsSurface* m_nurbs_surface = nullptr;
};


//////////////////////////////////////////////////////////////////////////
//
// ON_SubDFromMeshParameters
//
class ON_CLASS ON_SubDFromSurfaceParameters
{
public:

  // Default construction is identical to ON_SubDFromMeshParameters::Smooth.
  ON_SubDFromSurfaceParameters() = default;
  ~ON_SubDFromSurfaceParameters() = default;
  ON_SubDFromSurfaceParameters(const ON_SubDFromSurfaceParameters&) = default;
  ON_SubDFromSurfaceParameters& operator=(const ON_SubDFromSurfaceParameters&) = default;

  static const ON_SubDFromSurfaceParameters Default;
  static const ON_SubDFromSurfaceParameters DefaultWithCorners;
  static const ON_SubDFromSurfaceParameters ControlNet;
  static const ON_SubDFromSurfaceParameters ControlNetWithCorners;

#pragma region RH_C_SHARED_ENUM [ON_SubDFromSurfaceParameters::Methods] [Rhino.Geometry.SubDFromSurfaceMethods] [byte]
  /// <summary>
  /// ON_SubDFromSurfaceParameters::Method are ways to create a SubD from a surface.
  /// </summary>
  enum class Methods : unsigned char
  {
    /// <summary>
    /// Used to indicate the method is not set.
    /// </summary>
    Unset = 0,

    /// <summary>
    /// The surface is approximated with a SubD friendly NURBS surface and the SubD is created
    /// to match the subd friendly nurbs surface. 
    /// If the input surface is a subd friendly NURBS surface, the subd and surface have the same geometry.
    /// </summary>
    SubDFriendlyFit = 1,

    /// <summary>
    /// The surface is converted to a NURBS surface and then a subd with one face per NURBS bispan 
    /// is created by using an appropriate subset of the NURBS surface control net.
    /// If the input surface is a subd friendly NURBS surface, the subd and surface have the same geometry.
    /// </summary>
    FromNurbsControlNet = 2
  };
#pragma endregion

  ON_SubDFromSurfaceParameters::Methods Method() const;

  void SetMethod(
    ON_SubDFromSurfaceParameters::Methods method
    );

  bool Corners() const;

  void SetCorners(
    bool bCorners
    );

private:
  ON_SubDFromSurfaceParameters::Methods m_method = ON_SubDFromSurfaceParameters::Methods::SubDFriendlyFit;
  bool m_bCorners = false;
  unsigned short m_reserved1 = 0;
  unsigned int m_reserved2 = 0;
  double m_reserved3 = 0.0;
  double m_reserved4 = 0.0;
};


#pragma region RH_C_SHARED_ENUM [ON_SubDEndCapStyle] [Rhino.Geometry.SubDEndCapStyle] [byte]
/// <summary>
/// ON_SubDEndCapStyle enumerates the type of end caps functions like ON_SubD::CreateCylinder will create.
/// Use ON_SubDEndCapStyleFromUnsigned(integer value) to convert integer values to an ON_SubDEndCapStyle.
/// Use ON_SubDEndCapStyleToString(end_cap_style) to convert ON_SubDEndCapStyle values to string descriptions.
/// </summary>
enum class ON_SubDEndCapStyle : unsigned char
{
  /// <summary>
  /// Used to indicate the end cap style is not set.
  /// </summary>
  Unset = 0,

  /// <summary>
  /// Ends are not capped.
  /// </summary>
  None = 1,

  /// <summary>
  /// Ends are capped with triangles.
  /// </summary>
  Triangles = 2,

  /// <summary>
  /// When the end has an even number of edges, is will be capped with quads. Otherwise it will be capped with triangles.
  /// </summary>
  Quads = 3,

  /// <summary>
  /// Ends are capped with a n-gon. This is a poor choice when there are a large number of edges in the end boundary.
  /// </summary>
  Ngon = 4
};
#pragma endregion


/// <summary>
/// Convert an integer value to an ON_SubDEndCapStyle enum value.
/// </summary>
/// <param name="subd_cap_style_as_unsigned"></param>
/// If subd_cap_style_as_unsigned is not valid, then ON_SubDEndCapStyle::Unset is returned.
/// <returns></returns>
ON_DECL
ON_SubDEndCapStyle ON_SubDEndCapStyleFromUnsigned(
  unsigned int subd_cap_style_as_unsigned
);

/// <summary>
/// Convert subd_cap_style to a string description.
/// </summary>
/// <param name="subd_cap_style"></param>
/// <returns></returns>
ON_DECL
const ON_wString ON_SubDEndCapStyleToString(
  ON_SubDEndCapStyle subd_cap_style
);

//////////////////////////////////////////////////////////////////////////
//
// ON_SubD
//
//// ON_WIP_SDK 
//// This class is in the WIP SDK but the [[deprecated]] tag is 
//// failing to compile in tl_precompiledheader.cpp
class ON_CLASS ON_SubDExpandEdgesParameters
{
public:
  ON_SubDExpandEdgesParameters() = default;
  ~ON_SubDExpandEdgesParameters() = default;
  ON_SubDExpandEdgesParameters(const ON_SubDExpandEdgesParameters&) = default;
  ON_SubDExpandEdgesParameters& operator=(const ON_SubDExpandEdgesParameters&) = default;

  static const ON_SubDExpandEdgesParameters Default;

  /// <summary>
  /// ON_SubDExpandEdgesParameters::Style specifies options for how faces are inserted along input edges.
  /// </summary>
  enum class Style : unsigned char
  {
    /// <summary>
    /// Indicates the variable has not be initialized.
    /// </summary>
    Unset = 0,

    /// <summary>
    /// One quad replaces each input manifold edge. Corner cases where three or more edges meet
    /// receive special handling.
    /// </summary>
    Single = 1,

    /// <summary>
    /// Two quads are added for each input manifold edge. Corner cases where three or more edges meet
    /// receive special handling.
    /// </summary>
    Double = 2,

    /// <summary>
    /// This option applies only when the the input is an array of ON_SubDEdgePtrs
    /// that form a single oriented edge chain of manifold interior edges.
    /// A single quad is added to the left of the input edges.
    /// (The left side of of an oriented interior manifold edge is the face
    /// whose natural boundary orientation is the same as with the ON_SubDEdgePtr direction.)
    /// </summary>
    HalfLeft = 3,

    /// <summary>
    /// This option applies only when the the input is an array of ON_SubDEdgePtrs
    /// that form a single oriented edge chain of manifold interior edges.
    /// A single quad is added to the right of the input edges.
    /// (The right side of of an oriented interior manifold edge is the face
    /// whose natural boundary orientation is opposite the ON_SubDEdgePtr direction.)
    /// </summary>
    HalfRight = 4,
  };

public:
  /// OffsetTolerance = 0.001
  static const double OffsetTolerance; 

  /// Minimum permitted offset value (0.05)
  static const double MinimumOffset;

  /// Maximum permitted offset value (0.95)
  static const double MaximumOffset;

  /// Small offset value (0.125)
  static const double SmallOffset;

  /// Medium offset value (0.25)
  static const double MediumOffset;

  /// Large offset value (0.5)
  static const double LargeOffset;

public:
  /// <summary>
  /// This SHA1 hash can be used to determine if sets of parameters are the same.
  /// </summary>
  /// <returns>A SHA1 hash of all parameter values.</returns>
  const ON_SHA1_Hash Hash() const;

public:
  static double CleanupOffset(double x);


  /// <summary>
  /// Normalized constant offset parameter for inserting edges parallel to an input edge.
  /// Smaller values create narrower offsets.
  /// </summary>
  /// <returns>Offset value in the range ON_SubDExpandEdgesParameters::MinimumOffset to ON_SubDExpandEdgesParameters::MaximumOffset.</returns>
  double ConstantOffset() const;

  /// <summary>
  /// Set the constant offset value. Values within OffsetTolerance of a 
  /// predefined offset value are set to the predefined offset value.
  /// </summary>
  /// <param name="offset">
  /// ON_SubDExpandEdgesParameters::MinimumOffset &lt;= offset &lt;= ON_SubDExpandEdgesParameters::MaximumOffset;
  /// </param>
  /// <returns></returns>
  void SetConstantOffset(double offset);


  /// <summary>
  /// Determine if the set of ON_SubDEdgePtrs can be sorted into a 
  /// single edge chain that supports half side offsets.
  /// </summary>
  /// <param name="edge_chain"></param>
  /// <returns>True if variable offsets can be applied to edge_chain.</returns>
  static bool IsValidForHalfOffset(
    const ON_SimpleArray<ON_SubDEdgePtr>& edges
  );

  /// <summary>
  /// Determine if the set of ON_SubDEdgePtrs can be sorted into a 
  /// single open edge chain supports variable offsets.
  /// </summary>
  /// <param name="edge_chain"></param>
  /// <returns>True if variable offsets can be applied to edge_chain.</returns>
  static bool IsValidForVariableOffset(
    const ON_SimpleArray<ON_SubDEdgePtr>& edges
  );

  /// This option applies only when the the input is an array of ON_SubDEdgePtrs
  /// that form a single oriented edge chain. You may use
  /// ON_SubDExpandEdgesParameters::IsValidForVariableOffset() to determine if an
  /// array of ON_SubDEdgePtrs meets the variable offset requirements.
  /// In all other cases, the constant Offset() is used.
  /// To apply variable offsets to several edge chains, expand them one at a time.
  const ON_Interval VariableOffset() const;

  /*
  Description:
    This option applies only when the the input is an array of ON_SubDEdgePtrs
    that form a single oriented edge chain. You may use
    ON_SubDExpandEdgesParameters::IsValidForVariableOffset() to determine if an
    array of ON_SubDEdgePtrs meets the variable offset requirements.
    In all other cases, the constant Offset() is used.
    To apply variable offsets to several edge chains, expand them one at a time.

  Parameters:
    variable_offsets - [in]
      The two values must be between 0 and 1 and differ by more than ON_SubDExpandEdgesParameters::OffsetTolerance.
  */
  void SetVariableOffset(ON_Interval variable_offsets);

  void ClearVariableOffset();

  static bool IsValidConstantOffset(
    double constant_offset_candidate
  );

  static bool IsValidVariableOffset(
    ON_Interval variable_offset_candidate
  );

  /*
  Returns:
    True if variable offsets are set.
  */
  bool IsVariableOffset() const;


  ON_SubDExpandEdgesParameters::Style FaceStyle() const;

  /// <summary>
  /// Set the style for new faces.
  /// </summary>
  /// <param name="face_style"></param>
  /// <returns>Style for new faces.</returns>
  void SetFaceStyle(ON_SubDExpandEdgesParameters::Style face_style);

  /// <returns>True if the FaceStyle() is HalfLeft of HalfRight.</returns>
  bool IsHalfFaceStyle() const;

  /// <returns>Per face color for new faces.</returns>
  const ON_Color FaceColor() const;

  /// <summary>
  /// Set the perf face color for new faces.
  /// </summary>
  /// <param name="face_color">Color for new face. Pass ON_Color::Unset for no per face color.</param>
  void SetFaceColor(ON_Color face_color);

  /// <returns>Status for new faces.</returns>
  const ON_ComponentStatus FaceStatus() const;

  /// <summary>
  /// Set the Mark(), MarkBits(), Selected(), and Highlighted() status for new faces.
  /// </summary>
  /// <param name="face_status">Status for new faces.</param>
  void SetFaceStatus(ON_ComponentStatus face_status);

private:
  double m_constant_offset = ON_SubDExpandEdgesParameters::MediumOffset;
  ON_Interval m_variable_offsets = ON_Interval::Nan;
  ON_Color m_face_color = ON_Color::UnsetColor;
  ON_ComponentStatus m_face_status;
  ON_SubDExpandEdgesParameters::Style m_face_style = ON_SubDExpandEdgesParameters::Style::Double;

private:
  unsigned char m_reserved1 = 0;

private:
  ON__UINT64 m_reserved2 = 0;
  ON__UINT64 m_reserved3 = 0;
};

bool operator==(const ON_SubDExpandEdgesParameters& lhs, const ON_SubDExpandEdgesParameters& rhs);
bool operator!=(const ON_SubDExpandEdgesParameters& lhs, const ON_SubDExpandEdgesParameters& rhs);

class ON_WIP_CLASS ON_SubDComponentParameter
{
public:
  ON_SubDComponentParameter() = default;
  ~ON_SubDComponentParameter() = default;
  ON_SubDComponentParameter(const ON_SubDComponentParameter&) = default;
  ON_SubDComponentParameter& operator=(const ON_SubDComponentParameter&) = default;


  ON_SubDComponentParameter(ON_SubDComponentId cid);
  ON_SubDComponentParameter(ON_SubDComponentPtr cptr);

  ON_SubDComponentParameter(
    ON_SubDComponentId vertex_id,
    ON_SubDComponentId active_edge_id,
    ON_SubDComponentId active_face_id
  );

  ON_SubDComponentParameter(
    const class ON_SubDVertex* v,
    const class ON_SubDEdge* active_edge,
    const class ON_SubDFace* active_face
  );

  ON_SubDComponentParameter(
    const ON_SubDVertexPtr vptr,
    const class ON_SubDEdge* active_edge,
    const class ON_SubDFace* active_face
  );

  ON_SubDComponentParameter(
    ON_SubDComponentId edge_id,
    double p,
    ON_SubDComponentId active_face_id
  );


  /// <summary>
  /// 
  /// </summary>
  /// <param name="e"></param>
  /// <param name="p">
  /// 0 &lt;= p &lt;= 1.
  /// </param>
  /// <param name="active_face">
  /// nullptr or a face attached to the edge.
  /// </param>
  ON_SubDComponentParameter(
    const class ON_SubDEdge* e,
    double p,
    const class ON_SubDFace* active_face
  );

  /// <summary>
  /// 
  /// </summary>
  /// <param name="eptr"></param>
  /// <param name="p">
  /// 0 &lt;= p &lt;= 1.
  /// NOTE WELL: p is relative to the direction of eptr.
  /// </param>  
  /// <param name="active_face">
  /// nullptr or a face attached to the edge.
  /// </param>
  ON_SubDComponentParameter(
    const ON_SubDEdgePtr eptr,
    double p,
    const class ON_SubDFace* active_face
  );

  ON_SubDComponentParameter(
    ON_SubDComponentId face_id,
    ON_SubDFaceParameter fp
  );

  ON_SubDComponentParameter(
    const ON_SubDFace* face,
    ON_SubDFaceParameter fp
  );

  ON_SubDComponentParameter(
    const ON_SubDFacePtr fptr,
    ON_SubDFaceParameter fp
  );

  ON_SubDComponentParameter(
    const class ON_SubDFace* quad_face,
    double quad_s,
    double quad_t
  );
  ON_SubDComponentParameter(
    const class ON_SubDFacePtr quad_fptr,
    double quad_s,
    double quad_t
  );


  static const ON_SubDComponentParameter Unset;

  /// <summary>
  /// Dictionary compares component type and component id.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns></returns>
  static int CompareComponentTypeAndId(const ON_SubDComponentParameter& lhs, const ON_SubDComponentParameter& rhs);

  /// <summary>
  /// Dictionary compares component type, component id, and component dir.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns></returns>
  static int CompareComponentTypeAndIdAndDirection(const ON_SubDComponentParameter& lhs, const ON_SubDComponentParameter& rhs);


  /// <summary>
  /// Dictionary compares component type, component id, component direction, first parameter, second parameter.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns>
  /// -1: lhs &lt; rhs
  ///  0: lhs = rhs
  /// +1: lhs &gt; rhs
  /// </returns>
  static int CompareAll(const ON_SubDComponentParameter& lhs, const ON_SubDComponentParameter& rhs);

  /// <summary>
  /// Dictionary compares component type, component id, component direction, first parameter, second parameter
  /// and safely sorts nullptr to end.
  /// </summary>
  /// <param name="lhs"></param>
  /// <param name="rhs"></param>
  /// <returns></returns>
  static int Compare(const ON_SubDComponentParameter* lhs, const ON_SubDComponentParameter* rhs);

  const ON_wString ToString(bool bUnsetIsEmptyString) const;

  bool IsSet() const;

  const ON_SubDComponentId ComponentIdAndType() const;
  unsigned ComponentId() const;
  ON_SubDComponentPtr::Type ComponentType() const;
  unsigned ComponentDirection() const;

  /// <returns>
  /// True if the referenced component is a vertex.
  /// </returns>
  bool IsVertexParameter() const;

  /// <returns>
  /// If IsVertexParameter() is true, then the vertex's id is returned.
  /// Otherwise 0 is returned.
  /// </returns>
  unsigned VertexId() const;

  /// <summary>
  /// If this parameter references a vertex and the subd has a vertex
  /// with this->ComponentId(), then that vertex is returned.
  /// </summary>
  /// <param name="subd"></param>
  /// <returns>
  /// The referenced vertex in subd.
  /// </returns>
  const ON_SubDVertex* Vertex(const ON_SubD* subd) const;

  /// <summary>
  /// If this parameter references a vertex and the subd has a vertex
  /// with this->ComponentId(), then that vertex is returned.
  /// </summary>
  /// <param name="subd"></param>
  /// <returns>
  /// The referenced vertex in subd along with the direction value.
  /// </returns>
  const ON_SubDVertexPtr VertexPtr(const ON_SubD* subd) const;

  /// <summary>
  /// In some cases, an edge attached to this parameter's vertex is required. 
  /// In that case, this edge is used.
  /// </summary>
  /// <returns>
  /// The prefered edge attached to this vertex.
  /// </returns>
  const ON_SubDComponentId VertexEdge() const;

  /// <summary>
  /// In some cases, a face attached to this parameter's vertex is required. 
  /// In these cases this face is used.
  /// </summary>
  /// <returns>
  /// The prefered face attached to this vertex.
  /// </returns>
  const ON_SubDComponentId VertexFace() const;

  /// <returns>
  /// True if the referenced component is an edge.
  /// </returns>
  bool IsEdgeParameter() const;

  /// <returns>
  /// If IsEdgeParameter() is true, then the edge's id is returned.
  /// Otherwise 0 is returned.
  /// </returns>
  unsigned EdgeId() const;

  /// <summary>
  /// If this parameter references an edge and the subd has an edge
  /// with this->ComponentId(), then that edge is returned.
  /// </summary>
  /// <param name="subd"></param>
  /// <returns>
  /// The referenced edge in subd.
  /// </returns>
  const ON_SubDEdge* Edge(const ON_SubD* subd) const;

  /// <summary>
  /// If this parameter references an edge and the subd has an edge
  /// with this->ComponentId(), then that edge is returned.
  /// </summary>
  /// <param name="subd"></param>
  /// <returns>
  /// The referenced edge in subd along with the direction value.
  /// </returns>
  const ON_SubDEdgePtr EdgePtr(const ON_SubD* subd) const;

  /// <summary>
  /// Returns a parameter between 0 and 1 that identifies a point on the edge.
  /// This is always an intrisic parameter; 
  /// ComponentDirection() is not taken into account. 
  /// If the reference component is not an edge, then ON_DBL_QNAN is returned.
  /// </summary>
  /// <returns>
  /// Returns a parameter between 0 and 1 identifying the point
  /// on the edge. Note that ComponentDirection() is not taken
  /// into account. If this does not reference an edge or the
  /// parameter is not set, then ON_DBL_QNAN is returned.
  /// </returns>
  double EdgeParameter() const;

  /// <summary>
  /// In some cases, a face attached to this parameter's edge is required. 
  /// In that case, this face is used.
  /// </summary>
  /// <returns>
  /// The prefered edge attached to this vertex.
  /// </returns>
  const ON_SubDComponentId EdgeFace() const;

  /// <returns>
  /// True if the referenced component is a face.
  /// </returns>
  bool IsFaceParameter() const;

  /// <returns>
  /// If IsFaceParameter() is true, then the face's id is returned.
  /// Otherwise 0 is returned.
  /// </returns>
  unsigned FaceId() const;

  /// <summary>
  /// If this parameter references a face and the subd has a face
  /// with this->ComponentId(), then that face is returned.
  /// </summary>
  /// <param name="subd"></param>
  /// <returns>
  /// The referenced face in subd.
  /// </returns>  
  const ON_SubDFace* Face(const ON_SubD* subd) const;

  /// <summary>
  /// If this parameter references a face and the subd has a face
  /// with this->ComponentId(), then that face is returned.
  /// </summary>
  /// <param name="subd"></param>
  /// <returns>
  /// The referenced face in subd along with the direction value.
  /// </returns>
  const ON_SubDFacePtr FacePtr(const ON_SubD* subd) const;

  /// <returns>
  /// If a valid face and face parameter were passed to the constructor,
  /// then that face parameter is returned.
  /// Otherwise ON_SubDFaceParameter::Nan is returned.
  /// </returns>
  const ON_SubDFaceParameter FaceParameter() const;

  /// <summary>
  /// If the subd has a component with the same type and id,
  /// then that component is returned.
  /// </summary>
  /// <param name="subd"></param>
  /// <returns>
  /// The referenced component in subd along with the direction value.
  /// </returns>
  const ON_SubDComponentPtr ComponentPtr(const class ON_SubD* subd) const;

  /// <summary>
  /// If the subd has a component with the same type and id,
  /// then that component is returned.
  /// </summary>
  /// <param name="subd"></param>
  /// <returns>
  /// The referenced component in subd along with the direction value.
  /// </returns>
  const ON_SubDComponentPtr ComponentPtr(const class ON_SubD& subd) const;

private:
  ON_SubDComponentId m_cid = ON_SubDComponentId::Unset;

  union
  {
    ON_SubDComponentId v_active_e; // vertex's active edge
    double eptr_s;         // Relative with respect to m_cid.Direction().
    double f_corner_s;     // 0 <= f_corner_s <= 1/2
  } m_p0 = {};

  union
  {
    ON_SubDComponentId v_active_f; // vertex's active face
    ON_SubDComponentId e_active_f; // edge's active face
    double f_corner_t;  // 0 <= f_corner_t <= 1/2
  } m_p1 = {};

  bool Internal_Init(ON_SubDComponentId cid);
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubD
//
class ON_CLASS ON_SubD : public ON_Geometry
{
  ON_OBJECT_DECLARE(ON_SubD);

public:
  static const ON_SubD Empty;

  enum : unsigned int
  {
    maximum_subd_level = 128        // uses as a sanity check on input parameters
  };

  /*
  Returns:
    A runtime serial number identifying this subd.
  Remarks:
    ON_SubD is a shared pointer to an implementation. As such, there can
    be multiple ON_SubD instances that reference the same implementation.
    The runtime serial number uniquely identifies a particular instance
    of an implementation.
    The empty subd has runtime serial number = 0.
  */
  ON__UINT64 RuntimeSerialNumber() const;

  /*
  Returns:
    A runtime serial number that is changed every time a the active level,
    vertex location, vertex or edge flag, or subd topology is changed.
  */
  ON__UINT64 GeometryContentSerialNumber() const;

  /*
  Returns:
    A runtime serial number that is incremented every time a component status
    (locked, hidden, selected, highlighted, ...) is changed.
  */
  ON__UINT64 ComponentStatusSerialNumber() const;

  /*
  Description:
    Change the geometry content serial number to indicate something affecting
    the geometric shape of the subd has changed. This includes topologial changes,
    vertex and edge tag changes, and changes to vertex control net locations.
  Parameters:
    bChangePreservesSymmetry - [in]
      When in doubt, pass false.
      If the change preserves global symmtery, then pass true.
      (For example, a global subdivide preserves all types of symmetry.)
      Note well:
        Transformations do not preserve symmetries that are
        set with respect to world coordinate systems.
  Returns:
    The new value of GeometryConentSerialNumber().
  Remarks:
    The value can change by any amount.
    Changing the geometry content serial number automatically changes
    the render content serial number.
  */
  ON__UINT64 ChangeGeometryContentSerialNumberForExperts(
    bool bChangePreservesSymmetry
  );

  /*
  Description:
    The render content serial number changes whenever a change the might effect
    rendered appearance changes. This includes both geometry changes and
    changes that affect rendered appeance including changes to per face colors,
    per face materials, texture coordinates, and texture mappings.
  */
  ON__UINT64 RenderContentSerialNumber() const;

  /*
  Description:
    Change the render content serial number to indicate something affecting
    only rendered appearance has changed. This includes changes to per face colors,
    per face materials, texture coordinates, and texture mappings.
  Remarks:
    Changing the geometry content serial number automatically changes
    the render content serial number. If you call ChangeGeometryContentSerialNumberForExperts(),
    there is no need to also call ChangeRenderContentSerialNumber().
  */
  ON__UINT64 ChangeRenderContentSerialNumber() const;


  /*
  Description:
    Get a hash that uniquely identifies the topology or geometry of this SubD.
  Parameters:
    hash_type - [in]
     To see what is included in the various hashes, read the documentation for the ON_SubDHashType enum.
   bForceUpdate - [in]
     When in doubt pass false.
     The SubD hashes are mutable and cached. When code properly manages GeometryContentSerialNumber(),
     then SubDHash(hash_type,false) will always return the correct answer. This is the expected behavior.
     If code directly modifies SubD components and fails to call ChangeGeometryContentSerialNumberForExperts(),
     then it is possible a stale hash will be returned. Setting bForceUpdate = true forces the SHA1
     values to be recalculated from scratch. For extremely large SubDs, this recalculation can be time consuming.
  */
  const ON_SubDHash SubDHash(
    ON_SubDHashType hash_type,
    bool bForceUpdate
  ) const;

  /*
  Description:
    If two SubDs have identical values of GeometryHash(), then they have
    identical surface geometry.
  Returns:
    this->SubDHash(ON_SubDHashType::Geometry,false).SubDHash().
  Remarks:
    If the geometry hashes are equal, the topology hashes are equal.
  */
  const ON_SHA1_Hash GeometryHash() const;

  /*
  Description:
    If two SubDs have identical values of TopologyHash(), then they have
    identical labeled control net topology. The labels are the vertex, edge,
    and face ids.
  Returns:
    this->SubDHash(ON_SubDHashType::Topology,false).SubDHash().
  Remarks:
    Two SubDs can have the same topology hash but different geometry hashes.
  */
  const ON_SHA1_Hash TopologyHash() const;

  /*
  Description:
    Get the SubD appearance (surface or control net);
  Returns:
    ON_SubDComponentLocation::Surface or ON_SubDComponentLocation::ControlNet.
  */
  ON_SubDComponentLocation SubDAppearance() const;

  /*
  Description:
    Set the SubD appearance (surface or control net).
  Parameters:
    subd_appearance - [in]
      ON_SubDComponentLocation::Surface or ON_SubDComponentLocation::ControlNet.
  Remarks:
    This makes no changes to the information that defines the SubD.
    It does not require regeneration of the ON_SubDMeshFragments.
    Application display will need to be updated.
  */
  void SetSubDAppearance(ON_SubDComponentLocation subd_appearance) const;

  /*
  Description:
    Get the SubD appearance (surface or control net);
  Returns:
    ON_SubDComponentLocation::Surface or ON_SubDComponentLocation::ControlNet.
  */
  static ON_SubDComponentLocation ToggleSubDAppearanceValue(ON_SubDComponentLocation subd_appearance);
  static const ON_SubDComponentLocation DefaultSubDAppearance; // = ON_SubDComponentLocation::Surface
  static const ON_SubDTextureCoordinateType DefaultTextureCoordinateType; // = ON_SubDTextureCoordinateType::Packed


public:
  static ON_SubD* CreateCylinder(
    const class ON_Cylinder& cylinder,
    unsigned circumference_face_count,
    unsigned height_face_count,
    ON_SubDEndCapStyle end_cap_style,
    ON_SubDEdgeTag end_cap_edge_tag,
    ON_SubDComponentLocation radius_location,
    ON_SubD* destination_subd
  );

public:
  static ON_SubDVertexTag VertexTagFromUnsigned( 
    unsigned int vertex_tag_as_unsigned
    );


  /*
  Parameters:
    vertex_tag - [in]
    bVerbose - [in]
      If verbose, the tag name is preceded with "ON_SubDVertexTag::".
  Returns:
    vertex_tag as a string.
  */
  static const ON_wString VertexTagToString(
    ON_SubDVertexTag vertex_tag,
    bool bVertose
  );

  /*
  Parameters:
    vertex_tag - [in]
  Returns:
    True if vertex_tag is Smooth, Crease, Corner, or Dart.
    False otherwise.
  */
  static bool VertexTagIsSet(
    ON_SubDVertexTag vertex_tag
  );

  static ON_SubDEdgeTag EdgeTagFromUnsigned( 
    unsigned int edge_tag_as_unsigned
    );


  /*
  Parameters:
    edge_tag - [in]
    bVerbose - [in]
      If verbose, the tag name is preceded with "ON_SubDEdgeTag::".
  Returns:
    edge_tag as a string.
  */
  static const ON_wString EdgeTagToString(
    ON_SubDEdgeTag edge_tag,
    bool bVertose
  );


  /*
  Parameters:
    edge_tag - [in]
  Returns:
    True if edge_tag is Smooth, Crease, or SmoothX.
    False otherwise.
  */
  static bool EdgeTagIsSet(
    ON_SubDEdgeTag edge_tag
  );

  
  //enum class VertexEdgeOrder : unsigned char
  //{
  //  unset = 0,
  //  radial, // The ON_SubDVertex edge and face information satisfies:
  //          // 1) m_face_count = m_edge_count or m_face_count+1 == m_edge_count
  //          // 2) m_faces[i] is between m_edges[i] and m_edges[(i+1)%m_edge_count]
  //          // 3) When 0 < i < m_edge_count-1, m_edges[i].m_edge_count = 2
  //          //    and m_edges[i].m_face2[] references m_faces[i-1] and m_faces[i]
  //          //    in an unspecified order.
  //  notradial // one of the conditions conditions for radial is not satisfied.
  //};

  //static ON_SubD::VertexEdgeOrder VertexEdgeOrderFromUnsigned( 
  //  unsigned int vertex_edge_order_as_unsigned
  //  );

#pragma region RH_C_SHARED_ENUM [ON_SubD::VertexFacetType] [Rhino.Geometry.SubDVertexFacetType] [byte]
  /// <summary>
  /// Summarizes the number of edges in faces in the whole object.
  /// </summary>
  enum class VertexFacetType : unsigned char
  {
    ///<summary>Not a valid vertex face type.</summary>
    Unset = 0,

    ///<summary>All faces are triangular.</summary>
    Tri = 3,

    ///<summary>All faces are quads.</summary>
    Quad = 4,

    ///<summary>Edge count of faces is constant and &gt; 4.</summary>
    Ngon = 5,

    ///<summary>Edge count of faces is not constant.</summary>
    Mixed = 0xFF 
  };
#pragma endregion

  static ON_SubD::VertexFacetType VertexFacetTypeFromUnsigned( 
    unsigned int vertex_facet_type_as_unsigned
    );
  
#pragma region RH_C_SHARED_ENUM [ON_SubD::ChainType] [Rhino.Geometry.SubDChainType] [byte]
  /// <summary>
  /// SubD::ChainType specifies what edge and vertex tag tests are used when creating edge chains.
  /// </summary>
  enum class ChainType : unsigned char
  {
    ///<summary>
    /// Unset.
    ///</summary>
    Unset = 0,

    ///<summary>
    /// All types of edges and vertices can be in the chain.
    ///</summary>
    MixedTag = 1,

    ///<summary>
    /// Every edge in an edge chain has the same smooth/crease property.
    ///</summary>
    EqualEdgeTag = 2,

    ///<summary>
    /// Every edge in an edge chain has the same smooth/crease edge tag 
    /// and interior vertices have the corresponding smooth/crease vertex tag.
    ///</summary>
    EqualEdgeAndVertexTag = 3,

    ///<summary>
    /// Every edge in an edge chain has the same smooth/crease property
    /// and every edge has the same number of faces.
    /// If the edges have 1 face, then interior vertices have valence = 3.
    /// If the edges have 2 faces, then interior vertices have valence = 4.
    ///</summary>
    EqualEdgeTagAndOrdinary = 4,

    ///<summary>
    /// Every edge in an edge chain has the same smooth/crease edge tag,
    /// every edge has the same number of faces,
    /// and interior vertices have the corresponding smooth/crease vertex tag.
    /// If the edges have 1 face, then interior vertices have valence = 3.
    /// If the edges have 2 faces, then interior vertices have valence = 4.
    ///</summary>
    EqualEdgeAndVertexTagAndOrdinary = 5
  };
#pragma endregion

  /*
  Parameters:
    sit - [in]
      vertex sector iterator
    component_ring - [out]
      A sorted list of ON_SubDComponentPtr values are returned in component_ring[]
      component_ring[0] is the central vertex.
      component_ring[1] and subsequent components with odd indices are sector edges.
      component_ring[2] and subsequent components with even indices are sector faces.
      For edge components (i is odd), component_ring[i].ComponentMark() is the index of
      the center vertex in ON_SubDEge.m_vertex[].
    component_ring_capacity - [in]
      capacity of component_ring[] array
      1 + center_vertex.m_edge_count + center_vertex.m_face_count
      will be large enough.
  Returns:
    Number of components set in component_ring[].
    
    0: failure

    >= 4 and even:
      component_ring[0] = center vertex
      component_ring[1] = starting crease edge
      component_ring[2] = starting face
      ... zero or more interior smooth edge, face pairs ...
      component_ring[component_count-1] = ending crease edge

    >= 5 and odd:
      component_ring[0] = vit.CenterVertex()
      component_ring[1] = first edge (smooth)
      component_ring[2] = first face
      ... zero or more smooth edge, face, pairs ...
      component_ring[component_count-2] = last edge (smooth)
      component_ring[component_count-1] = last face

  Example:
    unsigned int component_ring_count = GetVertexComponentRing(vit,component_ring);
    unsigned int N = component_ring_count/2; // number of edges in ring
    const bool bSectorHasCreaseBoundary = (0 == (component_ring_count % 2));
  */
  static unsigned int GetSectorComponentRing(
    const class ON_SubDSectorIterator& sit,
    ON_SubDComponentPtr* component_ring,
    size_t component_ring_capacity
    );

 /*
  Parameters:
    sit - [in]
      vertex sector iterator
    component_ring - [out]
      A sorted listof ON_SubDComponentPtr values are returned in component_ring[]



  Returns:
    Number of components set in component_ring[].
    
    0: failure

    >= 4 and even:
      component_ring[0] = vit.CenterVertex()
      component_ring[1] = starting crease edge
      component_ring[2] = starting face
      ... zero or more interior smooth edge, face pairs ...
      component_ring[component_count-1] = ending crease edge

    >= 5 and odd:
      component_ring[0] = center vertex
      component_ring[1] = first edge (smooth)
      component_ring[2] = first face
      ... zero or more smooth edge, face, pairs ...
      component_ring[component_count-2] = last edge (smooth)
      component_ring[component_count-1] = last face

  Example:
    unsigned int component_ring_count = GetVertexComponentRing(vit,component_ring);
    unsigned int N = component_ring_count/2; // number of edges in ring
    const bool bSectorHasCreaseBoundary = (0 == (component_ring_count % 2));
  */
  static unsigned int GetSectorComponentRing(
    const class ON_SubDSectorIterator&  sit,
    ON_SimpleArray<ON_SubDComponentPtr>& component_ring
    );

  /*
  Returns:
    Number of edges in an component ring returned by ON_SubD::GetVertexComponentRing();
  */
  static unsigned int ComponentRingEdgeCount(
    size_t component_ring_count
    );

  /*
  Returns:
    Number of faces in an component ring returned by ON_SubD::GetVertexComponentRing();
  */
  static unsigned int ComponentRingFaceCount(
    size_t component_ring_count
    );

  static bool ComponentRingIsValid(
    const ON_SubDComponentPtr* component_ring,
    size_t component_ring_count
    );

  /*
  Returns:
    Number of points in the subdivision ring or 0 if the call fails.
  */
  static unsigned int GetSectorSubdivsionPointRing(
    const ON_SubDComponentPtr* component_ring,
    size_t component_ring_count,
    double* point_ring,
    size_t point_ring_capacity,
    size_t point_ring_stride
    );

  static unsigned int GetSectorSubdivisionPointRing(
    const ON_SubDComponentPtr* component_ring,
    size_t component_ring_count,
    ON_SimpleArray<ON_3dPoint>& subd_point_ring
    );

  static unsigned int GetSectorPointRing(
    bool bSubdivideIfNeeded,
    const ON_SubDComponentPtr* component_ring,
    size_t component_ring_count,
    double* subd_point_ring,
    size_t subd_point_ring_capacity,
    size_t subd_point_ring_stride
    );

  static unsigned int GetSectorPointRing(
    bool bSubdivideIfNeeded,
    size_t component_ring_count,
    const ON_SubDComponentPtr* component_ring,
    ON_SimpleArray<ON_3dPoint>& point_ring
    );

  static unsigned int GetSectorPointRing(
    bool bSubdivideIfNeeded,
    const class ON_SubDSectorIterator& sit,
    double* point_ring,
    size_t point_ring_capacity,
    size_t point_ring_stride
  );

  static unsigned int GetSectorPointRing(
    bool bSubdivideIfNeeded,
    const class ON_SubDSectorIterator& sit,
    ON_SimpleArray<ON_3dPoint>& point_ring
  );

  static unsigned int GetSectorPointRing(
    const class ON_SubDSectorIterator& sit,
    unsigned& subdivision_count,
    double* point_ring,
    size_t point_ring_capacity,
    size_t point_ring_stride
  );

  /// <summary>
  /// Get a ring of points that can be used to calculate the subdivision and
  /// limit points of sit.CenterVertex().
  /// </summary>
  /// <param name="sit">
  /// Initialized sector iterator.
  /// </param>
  /// <param name="subdivision_count">
  /// TNumber of subdivisions performed to get point_ring[] is returned in subdivision_count.
  /// </param>
  /// <param name="point_ring">
  /// The points are returned in point_ring[]
  /// </param>
  /// <returns>
  /// Number of points in point_ring[]
  /// </returns>
  static unsigned int GetSectorPointRing(
    const class ON_SubDSectorIterator& sit,
    unsigned& subdivision_count,
    ON_SimpleArray<ON_3dPoint>& point_ring
  );

  /*
  Parameters:
    bPermitNoSubdivisions - [in]
      When in doubt, pass false.
      If bPermitNoSubdivisions is true and no extraordinary components
      are in the ring, then locations of the input component
      control net are returned. 
      Otherwise at one or more subdivisions are applied to obtain the output ring points.
    bObsoleteAndIgnoredParameter - [in]
      Obsolete and ignored parameter. Pass false.
    obsolete_and_ignored_parameter - [in]
      Obsolete and ignored parameter. Pass nullptr.
    component_ring_count - [in]
      component_ring_count specifies the number of components in the component_ring[] array.
    component_ring[] - [in]
      component_ring[0] is the central vertex,
      component_ring[1] and subsequent components with odd indices are sector edges. sorted radially.
      component_ring[2] and subsequent components with even indices are sector faces.
      The edges and faces are sorted radially (component_ring[1] and component_ring[3] are edges of component_ring[2], etc).
    point_ring_stride - [in]
    point_ring - [out]
      point locations are returned here.
  Returns:
    Number of points in the subdivision ring or 0 if the call fails.
    The number of  points is 
    1 + ON_SubD::ComponentRingEdgeCount(component_ring_count) + ON_SubD::ComponentRingFaceCount(component_ring_count).
  Remarks:
    No validation checking is performed.  This function will crash
    if the input is not valid.  Call GetSubdivisionPointRing() if
    you want a crash proof call.
  */
  static unsigned int GetQuadSectorPointRing(
    bool bPermitNoSubdivisions,
    bool bObsoleteAndIgnoredParameter,
    const class ON_SubDVertex* obsolete_and_ignored_parameter,
    const class ON_SubDComponentPtr* component_ring,
    size_t component_ring_count,
    double* point_ring,
    size_t point_ring_stride
    );

  /// <summary>
  /// Get a ring of points that can be mulitplied by subdivsion and limit point matrices 
  /// to calculate the subdivision point and limit point for the central vertex in component_ring[0].
  /// No input validation is performed. This function will crash if the input is not valid.
  /// Call GetSubdivisionPointRing() if you want a crash proof call.
  /// </summary>
  /// <param name="bPermitNoSubdivisions">
  /// When in doubt, pass false. If bPermitNoSubdivisions is true and no extraordinary components
  /// or sharp edges are in the ring, then locations of the input component_ring[] control net points 
  /// are returned. Otherwise one or more subdivisions are applied to obtain the output ring points.
  /// </param>
  /// <param name="component_ring">
  /// component_ring[0] is the central vertex.
  /// component_ring[1] and subsequent components with odd indices are sector edges.
  /// component_ring[2] and subsequent components with even indices are sector faces.
  /// The edges and faces are sorted radially(component_ring[1] and component_ring[3] are edges of component_ring[2], etc).
  /// </param>
  /// <param name="component_ring_count">
  /// Number of components in the component_ring[] array.
  /// </param>
  /// <param name="subdivision_count">
  /// The number of subdivisions used to calculate point_ring[] is returned in subdivision_count.
  /// </param>
  /// <param name="point_ring">
  /// The point ring points are returned in point_ring[]
  /// </param>
  /// <param name="point_ring_stride">
  /// Number of doubles between subsequent points in point_ring[].
  /// </param>
  /// <returns>
  /// If successful, component_ring_count is returned which is the number of points set in point_ring[].
  /// Otherwise 0 is returned.
  /// </returns>
  static unsigned int GetQuadSectorPointRing(
    bool bPermitNoSubdivisions,
    const class ON_SubDComponentPtr* component_ring,
    size_t component_ring_count,
    unsigned int& subdivision_count,
    double* point_ring,
    size_t point_ring_stride
  );

  static const class ON_SubDVertex* SubdivideSector(
    const class ON_SubDVertex* center_vertex,
    const class ON_SubDComponentPtr* component_ring,
    size_t component_ring_count,
    class ON_SubD_FixedSizeHeap& fsh
    );

  /*
  Returns:
    true if sector_edge_count is valid for the vertex type
  */
  static bool IsValidSectorEdgeCount(
    ON_SubDVertexTag vertex_tag,
    unsigned int sector_edge_count
    );  
  
  static bool IsValidSectorFaceCount(
    ON_SubDVertexTag vertex_tag,
    unsigned int sector_face_count
    );

#pragma region RH_C_SHARED_ENUM [ON_SubD::SubDFriendlyKnotType] [Rhino.Geometry.SubDFriendlyKnotType] [byte]
  /// <summary>
  /// ON_SubD::SubDFriendlyKnotType identifies the types of subd friendly NURBS knot vectors.
  /// SubD friendly NURBS curves and surfacaes are always cubic and nonrational.
  /// Any time there is a multiple knot, the 2nd derivative is zero at the corresponding parameter.
  /// SubD friendly NURBS curves are either periodic or have zero 2nd derivative at the ends.
  /// </summary>    
  enum class SubDFriendlyKnotType : unsigned char
  {
    ///<summary>
    /// Not a valid type. Used to indicate the type has not been set and to encourage developers to explicitly specify a type.
    ///</summary>
    Unset = 0,

    ///<summary>
    /// NURBS knot vector is an unclamped uniform cubic knot vector. 
    /// Every knot interval has the same length.
    /// Every knot has multiplicity 1. 
    ///</summary>
    UnclampedUniform = 1,

    ///<summary>
    /// NURBS knot vector is a clamped uniform cubic knot vector. 
    /// Every interior knot interval has the same length.
    /// End knots have multiplicity 3 and interior knots have multiplicity 1.
    ///</summary>
    ClampedUniform = 2,

    ///<summary>
    /// NURBS knot vector is a clamped piecewise uniform cubic knot vector.
    /// All nonzero knot intervals have the same length.
    /// End knots have multiplicity 3 and interior knots have multiplicity 1 or 3.
    /// Interior knots with multiplicity 3 correspond to interior SubD creases.
    ///</summary>
    ClampedPiecewiseUniform = 4,

    ///<summary>
    /// NURBS knot vector is not subd friendly.
    ///</summary>
    Unfriendly = 127
  };
 #pragma endregion

  /*
  Parameters:
    order - [in]
      NURBS knot vector order.
    cv_count - [in]
      Number of NURBS knot vector control points.
    knots - [in]
      NURBS knot vector. This is an array of (cv_count+2) knot values.
  Returns:
    SubD friendly knot vector type.
  Remarks:
    If order is not 4, cv_count is not valid, or knot is nullptr, then
    ON_SubD::SubDFriendlyKnotType::Unfriendly is returned.
  */
  static ON_SubD::SubDFriendlyKnotType NurbsKnotType(
    int order,
    int cv_count,
    const double* knots
  );

  static ON_SubD::SubDFriendlyKnotType NurbsKnotType(
    int order,
    int cv_count,
    const double* knots,
    ON_SimpleArray<double>* triple_knots
  );

  /*
  Parameters:
    point_count - [in] >= 3
      Number of control points in a regular planar SubD ngon with creased edges.
    control_point_radius - [in]
      Distance from an ngon control point to the ngon center.
  Returns:
    Distance from an ngon surface point to the ngon center.
  See Also:
    ON_SubD::SurfacePointRadiusFromControlPointRadius()
  */
  static double SurfacePointRadiusFromControlPointRadius(
    unsigned int point_count,
    double control_point_radius
  );

  /*
  Parameters:
    point_count - [in] >= 3
      Number of control points in a regular planar SubD ngon with creased edges.
    surface_radius - [in]
    Distance from an ngon surface point to the ngon center.
  Returns:
    Distance from an ngon control point to the ngon center.
  See Also:
    ON_SubD::ControlPointRadiusFromSurfacePointRadius()
  */
  static double ControlPointRadiusFromSurfacePointRadius(
    unsigned int point_count,
    double surface_point_radius
  );







  ON_SubD() ON_NOEXCEPT;
  virtual ~ON_SubD();



  /*
  Description:
    Creates an independent copy of src.
  */
  ON_SubD( const ON_SubD& src );

  /*
  Description:
    Creates an independent copy of src.
  */
  ON_SubD& operator=(const ON_SubD& src);

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_SubD( ON_SubD&& ) ON_NOEXCEPT;

  // The rvalue assignment operator calls ON_Object::operator=(ON_Object&&)
  // which could throw exceptions.  See the implementation of
  // ON_Object::operator=(ON_Object&&) for details.
  ON_SubD& operator=( ON_SubD&& );
#endif

  /*
  Description:
    The subdivision information referenced by src_subd will be shared with this
  Remarks:
    ON_Geometry base class information, like ON_UserData, is not copied or shared.
  */
  void ShareContentsFrom(
    ON_SubD& subd
    );

  static void SwapContents(
    ON_SubD& a,
    ON_SubD& b
    );

  //virtual 
  void MemoryRelocate() override;

  //virtual
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  //virtual
  void Dump(
    ON_TextLog&
    ) const override;

  //virtual
  unsigned int SizeOf() const override;

  /*
  Description:
    This is a debugging too used to study how efficiently SubDs are using memory.
  Returns:
    Total operating system heap (in bytes) used by this SubD's ON_FixedSizePools, include the mesh fragments pool.
  Remarks:
    SizeOfAllElements() = SizeOfActiveElements() + SizeOfUnusedElements().
  */
  size_t SizeOfAllElements() const;

  /*
  Description:
    This is a debugging too used to study how efficiently SubDs are using memory.
  Returns:
    Total operating system heap (in bytes) of memory in this SubD's ON_FixedSizePools
    that is currently used by active elements, including active mesh fragments.
  Remarks:
    SizeOfAllElements() = SizeOfActiveElements() + SizeOfUnusedElements().
  */
  size_t SizeOfActiveElements() const;

  /*
  Description:
    This is a debugging too used to study how efficiently SubDs are using memory.
  Returns:
    Total operating system heap (in bytes) of memory in this SubD's ON_FixedSizePools
    that is reserved but not currently used, including unused mesh fragments.
  Remarks:
    SizeOfAllElements() = SizeOfActiveElements() + SizeOfUnusedElements().
  */
  size_t SizeOfUnusedElements() const;

  /*
  Description:
    Tool for debugging mesh fragments memory use.
  Returns:
    Total operating system heap memory (in bytes) used by the mesh fragments pool.
  Remarks:
    SizeOfAllMeshFragments() = SizeOfActiveMeshFragments() + SizeOfUnusedMeshFragments().
  */
  size_t SizeOfAllMeshFragments() const;

  /*
  Description:
    Tool for debugging mesh fragments memory use.
  Returns:
    Operating system heap memory (in bytes) that are used by active mesh fragments.
  Remarks:
    SizeOfAllMeshFragments() = SizeOfActiveMeshFragments() + SizeOfUnusedMeshFragments().
  */
  size_t SizeOfActiveMeshFragments() const;


  /*
  Description:
    Tool for debugging mesh fragments memory use.
  Returns:
    Operating system heap memory (in bytes) that has been reserved for mesh fragments
    but is not currently used by active mesh fragments.
  Remarks:
    SizeOfAllMeshFragments() = SizeOfActiveMeshFragments() + SizeOfUnusedMeshFragments().
  */
  size_t SizeOfUnusedMeshFragments() const;

  //virtual
  ON__UINT32 DataCRC(
    ON__UINT32 current_remainder
    ) const override;

  //virtual
  bool Write(
         ON_BinaryArchive& archive
         ) const override;

  //virtual
  bool Read(
         ON_BinaryArchive& archive
         ) override;

  //virtual
  ON::object_type ObjectType() const override;


  //virtual
  unsigned int ClearComponentStates(
    ON_ComponentStatus states_to_clear
    ) const override;

  //virtual
  unsigned int GetComponentsWithSetStates(
    ON_ComponentStatus states_filter,
    bool bAllEqualStates,
    ON_SimpleArray< ON_COMPONENT_INDEX >& components
    ) const override;
  
  //virtual
  unsigned int SetComponentStates(
    ON_COMPONENT_INDEX component_index,
    ON_ComponentStatus states_to_set
    ) const override;

  //virtual
  unsigned int ClearComponentStates(
    ON_COMPONENT_INDEX component_index,
    ON_ComponentStatus states_to_clear
    ) const override;

  //virtual
  unsigned int SetComponentStatus(
    ON_COMPONENT_INDEX component_index,
    ON_ComponentStatus status_to_copy
    ) const override;

  //virtual
  ON_AggregateComponentStatus AggregateComponentStatus() const override;

  //virtual
  void MarkAggregateComponentStatusAsNotCurrent() const override;

  //virtual
  bool DeleteComponents(
    const ON_COMPONENT_INDEX* ci_list,
    size_t ci_count
    ) override;

  /*
  Remarks:
    For ON_SubD objects, ClearBoundingBox() and DestroyRuntimeCache()
    are identical.
  */
  //virtual
  void DestroyRuntimeCache(
    bool bDelete = true
    ) override;

  //virtual 
  int Dimension() const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;


  /*
  Description:
    Clears all saved information that depends on vertex locations,
    subdivision algorithms, vertex or edge tags, or control net topology.  
    If you modify any of the above, then call ClearBoundingBox().
  Remarks:
    For ON_SubD objects, ClearBoundingBox() and DestroyRuntimeCache()
    are identical.
  */
  //virtual
  void ClearBoundingBox() override;

  //virtual
  bool Transform( 
         const ON_Xform& xform
         ) override;

  //virtual
  bool IsDeformable() const override;

  //virtual
  bool MakeDeformable() override;

  //virtual
  bool SwapCoordinates(
        int i,
        int j
        ) override;
  
  
  //virtual
  bool HasBrepForm() const override;

  //virtual
  /*
  Returns:
    GetSurfaceBrep( ON_SubDToBrepParameters::Default, nullptr );
  */
  ON_Brep* BrepForm(
    ON_Brep* brep = nullptr
  ) const override;

  //virtual
  ON_COMPONENT_INDEX ComponentIndex() const override;

  //virtual
  bool EvaluatePoint(
    const class ON_ObjRef& objref, 
    ON_3dPoint& P
    ) const override;

  /*
  Description:
    Uses the input mesh to define the level zero control polygon.
  Parameters:
    level_zero_mesh - [in]
    from_mesh_parameters - [in]
      To get the smoothest possible result, pass nullptr 
      or ON_SubDFromMeshParameters::Smooth. To get a sub-D with interior 
      creases use other static ON_SubDFromMeshParameters values or
      create one with custom settings.
  */
  static ON_SubD* CreateFromMesh( 
    const class ON_Mesh* level_zero_mesh,
    const class ON_SubDFromMeshParameters* from_mesh_parameters,
    ON_SubD* subd
    );


public:
#pragma region RH_C_SHARED_ENUM [ON_SubD::AutomaticMeshToSubDContext] [Rhino.Geometry.SubDAutomaticMeshToSubDContext] [byte]
  /// <summary>
  /// ON_SubD::AutomaticMeshToSubDContext identifies a context where meshes can automatically
  /// be converted to subds.
  /// </summary>
  enum class AutomaticMeshToSubDContext : unsigned char
  {
    ///<summary>
    /// Indicates the context has not been initialized.
    ///</summary>
    Unset = 0,

    ///<summary>
    /// A mesh in a Rhino 5 3dm file that is a representation of a box mode T-spline.
    /// By default, these meshes are automatically converted to subds.
    ///</summary>
    Rhino5BoxModeTSpline = 1,

    ///<summary>
    /// A mesh in an FBX file that has nonzero values for either preview division levels or render division levels.
    /// Some FBX files created by Maya save subdivision objects as meshes with nonzero division level values.
    /// By default, FBX division levels are ignored.
    ///</summary>
    FBXMeshWithDivisionLevels = 2
  };
#pragma endregion

  /*
  Returns:
    true if SubDs are automatically created when an ON_Mesh is found in the specified context.
    false otherwise.
  */
  static bool AutomaticMeshToSubD(
    ON_SubD::AutomaticMeshToSubDContext context
  );

  /*
  Parameters:
    context - [in]
      Situation where an ON_Mesh can automatically be converted into a subd.
    bAutomaticallyCreateSubD - [in]
      true if SubDs are automatically created when an ON_Mesh is found in the specified context.
      false otherwise.
  */
  static void SetAutomaticMeshToSubD(
    ON_SubD::AutomaticMeshToSubDContext context,
    bool bAutomaticallyCreateSubD
    );

  /*
  Parameters:
    context - [in]
      If context is ON_SubD::AutomaticMeshToSubDContext::Unset, all defaults will be restored.
      Otherwise, the default for the specific context will be restored.
  */
  static void AutomaticMeshToSubDRestoreDefaults(
    ON_SubD::AutomaticMeshToSubDContext context
    );

private:
  static const  bool AutomaticRhino5BoxModeTSplineToSubDDefault; // = true
  static const bool AutomaticFBXMeshWithDivisionLevelsToSubDDefault; // = false
  static bool AutomaticRhino5BoxModeTSplineToSubD; // current setting
  static bool AutomaticFBXMeshWithDivisionLevelsToSubD; // current setting

private:
  static ON_SubD* Internal_CreateFromMeshWithValidNgons(
    const class ON_Mesh* level_zero_mesh_with_valid_ngons,
    const class ON_SubDFromMeshParameters* from_mesh_parameters,
    ON_SubD* subd
  );

public:

  /*
  Description:
    Creates a SubD box
  Parameters:
    corners - [in] 
      Box corners.
      The bottom quad is specified by the first 4 points
      and the top quad specified by the last 4 points.
    edge_tag - [in]
      If edge_tag = ON_SubDEdgeTag::Crease, then the box will have 
      creases and corners. Otherwise the box will be smooth.
    facecount_x - [in] Number of faces in x direction
    facecount_y - [in] Number of faces in y direction
    facecount_z - [in] Number of faces in z direction
    destination_subd [out] - 
      If destination_subd is not null, make the SubD box there
  Returns:
    Pointer to the resulting SubD if successful
    Null for error
  */
  static ON_SubD* CreateSubDBox(
    const ON_3dPoint corners[8],
    ON_SubDEdgeTag edge_tag,
    unsigned int facecount_x,
    unsigned int facecount_y,
    unsigned int facecount_z,
    ON_SubD* destination_subd
  );

  /*
  Description:
    Creates a SubD box
  Parameters:
    corners - [in]
      Box corners.
      The bottom quad is specified by the first 4 points
      and the top quad specified by the last 4 points.
    edge_sharpness - [in]
      If edge_sharpness = ON_SubDEdgeSharpness::SmoothValue, the edges where box sides meet will be smooth.
      If ON_SubDEdgeSharpness::SmoothValue &lt; edge_sharpness &lt;= ON_SubDEdgeSharpenss::MaximumValue, 
      the edges where box sides meet will have the specified sharpness.
      If edge_sharpness = ON_SubDEdgeSharpenss::CreaseValue,
      the edges where box sides meet will be creases.
    facecount_x - [in] Number of faces in x direction
    facecount_y - [in] Number of faces in y direction
    facecount_z - [in] Number of faces in z direction
    destination_subd [out] -
      If destination_subd is not null, the SubD box is saved in this instance.
  Returns:
    Pointer to the resulting SubD if successful
    Null for error
  */
  static ON_SubD* CreateSubDBox(
    const ON_3dPoint corners[8],
    double edge_sharpness,
    unsigned int facecount_x,
    unsigned int facecount_y,
    unsigned int facecount_z,
    ON_SubD* destination_subd
  );


  /*
  Description:
    Creates a SubD cylinder
  Parameters:
    box - [in]
      Location, size and orientation of the cylinder
    facecount_around - [in] Number of faces around the cylinder
    facecount_length - [in] Number of faces in the axis direction
    facecouont_z - [in] Number of faces in z direction
    destination_subd [out] -
      If destination_subd is not null, make the SubD box there
  Returns:
    Pointer to the resulting SubD if successful
    Null for error
  */
  //static ON_SubD* CreateSubDCylinder(
  //  const ON_Cylinder cylinder,
  //  ON_SubDComponentLocation vertex_location,
  //  unsigned int facecount_around,
  //  unsigned int facecount_length,
  //  ON_SubD* destination_subd);

  /*
  Description:
    Creates a SubD cone
  Parameters:
    cone - [in]
      Location, size and orientation of the cone
    facecount_around - [in] Number of faces around the cone
    facecount_length - [in] Number of faces in the axis direction
    destination_subd [out] -
      If destination_subd is not null, make the SubD cone there
  Returns:
    Pointer to the resulting SubD if successful
    Null for error
  */
  //static ON_SubD* CreateSubDCone(
  //  const ON_Cone& cone,
  //  unsigned int facecount_around,
  //  unsigned int facecount_length,
  //  ON_SubD* destination_subd);

  /*
  Description:
    Creates a SubD truncated cone
  Parameters:
    cone - [in]
      Location, size and orientation of the cone
    truncate_param - [in] 0.0 < truncate_param <= 1.0
        Normalized parameter for truncation
        0.0: Base of cone
        1.0: Tip of cone
    facecount_around - [in] Number of faces around the cone
    facecount_length - [in] Number of faces in the axis direction
    destination_subd [out] -
      If destination_subd is not null, make the SubD cone there
  Returns:
    Pointer to the resulting SubD if successful
    Null for error
  */
  //static ON_SubD* CreateSubDTruncatedCone(
  //  const ON_Cone& cone,
  //  const double truncate_param,
  //  unsigned int facecount_around,
  //  unsigned int facecount_length,
  //  ON_SubD* destination_subd);

  /*
  Description:
    Creates a SubD torus
  Parameters:
    torus - [in]
      Location, size and orientation of the torus
    major_facecount - [in] Number of faces around the major axis
    minor_facecount - [in] Number of faces around the minor axis
    destination_subd [out] -
      If destination_subd is not null, make the SubD torus there
  Returns:
    Pointer to the resulting SubD if successful
    Null for error
  */
  //static ON_SubD* CreaptSubDTorus(
  //  ON_Torus& torus,
  //  unsigned int major_facecount,
  //  unsigned int minor_facecount,
  //  ON_SubD* destination_subd);

  unsigned int DumpTopology(
    ON_TextLog&
    ) const;

  unsigned int DumpTopology(
    ON_2udex vertex_id_range,
    ON_2udex edge_id_range,
    ON_2udex face_id_range,
    ON_TextLog&
    ) const;

  /*
  Description:
    Discard all contents of this ON_SubD.
  Remarks:
    More efficient than Destroy() if this ON_SubD will be reused soon.
  */
  void Clear();

  /*
  Description:
    Delete all contents release all memory used by this ON_SubD.
  */
  void Destroy();

  /*
  Returns:
    The number of explicitly computed levels that are currently available.
    A value of 0 indicates this SubD is empty.
  */
  unsigned int LevelCount() const;

  /*
  Returns:
    If the SubD is not empty, then the index of the active level is returned. This value will be < LevelCount().
    If the SubD is empty, then ON_UNSET_UINT_INDEX is returned.
  */
  unsigned int ActiveLevelIndex() const;

  /*
  Description:
    Remove subdivision levels
  Parameters:
    max_level_index - [in] 
      Remove all levels after max_level_index
  Returns:
    Number of removed levels.
  */
  unsigned int ClearHigherSubdivisionLevels(
    unsigned int max_level_index
    );

  /*
  Description:
    Remove subdivision levels
  Parameters:
    min_level_index - [in] 
      Remove all levels before min_level_index
  Returns:
    Number of removed levels.
  */
  unsigned int ClearLowerSubdivisionLevels(
    unsigned int min_level_index
    );

  /*
  Description:
  Remove all levels except the active level.
  Returns: 
    Number of removed levels.
  */
  unsigned ClearInactiveLevels();

  bool IsEmpty() const;
  bool IsNotEmpty() const;

  /// <summary>
  /// Determine if this SubD has sharp edges. 
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <returns>True if the SubD has at lease one sharp edge.</returns>
  bool HasSharpEdges() const;

  /// <summary>
  /// Get the range of sharpness values assigned to sharp edges
  /// and return the number of sharp edges.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <param name="sharpness_range">The range of sharpness values is returned here. (0,0) is returned if there are no sharp edges.</param>
  /// <returns>Number of sharp edges.</returns>
  unsigned int SharpEdgeCount(ON_SubDEdgeSharpness& sharpness_range) const;

  /// <summary>
  /// Number of sharp edges.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <returns>Number of sharp edges.</returns>
  unsigned int SharpEdgeCount() const;

  /// <summary>
  /// Converts all sharp edges to smooth edges.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <returns>Number of sharp edges that were converted to smooth edges.</returns>
  unsigned int ClearEdgeSharpness();


  /*
  Description:
    Get aggregate edge demographics for the subd.
  Returns:
    Bitwise or of ON_ComponentAttributes::EdgeAttributes values for every edge in the subd.
  */
  unsigned int AggregateEdgeAttributes() const;
  
  /////////////////////////////////////////////////////////
  //
  // Component (Vertex, Edge, Face) access
  //
  const ON_SubDComponentPtr ComponentPtrFromComponentIndex(
    ON_COMPONENT_INDEX component_index
    ) const;

  unsigned int ComponentPtrFromComponentIndex(
    const ON_COMPONENT_INDEX* ci_list,
    size_t ci_count,
    ON_SimpleArray<ON_SubDComponentPtr>& cptr_list
  ) const;

  unsigned int ComponentPtrFromComponentIndex(
    const ON_COMPONENT_INDEX* ci_list,
    size_t ci_count,
    bool bIncludeVertices,
    bool bIncludeEdges,
    bool bIncludeFaces,
    ON_SimpleArray<ON_SubDComponentPtr>& cptr_list
  ) const;

  /////////////////////////////////////////////////////////
  //
  // Membership query
  //
  bool InSubD(const class ON_SubDVertex* vertex) const;
  bool InSubD(const class ON_SubDEdge* edge) const;
  bool InSubD(const class ON_SubDFace* face) const;


  /*
  Returns:
    ON_SubDComponentPtr::Type::Unset if b is not in this SubD.
    Otherwise the type of the component is returned.
  */
  bool InSubD(ON_SubDComponentPtr cptr) const;
  
  /*
  Returns:
    If b is in this SubD, a ON_SubDComponentPtr to b is returned.
    Otherwise ON_SubDComponentPtr::Null is returned.
  Remarks:
    This function is the slowest of the InSubD() overrides.
    When b is an unknown component type, this function can be used to
    safely determine what type of component (vertex/edge/face).
  */
  const ON_SubDComponentPtr InSubD(const class ON_SubDComponentBase* b) const;

  /// <summary>
  /// ON_SubD::FirstVertex(), ON_SubD::FirstEdge(), or ON_SubD::FirstFace() is returned,
  /// depending on the value of component_type. 
  /// </summary>
  /// <param name="component_type"></param>
  /// <returns>The first component of the specified type.</returns>
  const ON_SubDComponentPtr FirstComponent(
    ON_SubDComponentPtr::Type component_type
  ) const;


  /// <summary>
  /// ON_SubD::VertexCount(), ON_SubD::EdgeCount(), or ON_SubD::FaceCount() is returned,
  /// depending on the value of component_type. 
  /// </summary>
  /// <param name="component_type"></param>
  /// <returns>The first component of the specified type.</returns>
  unsigned ComponentCount(
    ON_SubDComponentPtr::Type component_type
  ) const;


  /////////////////////////////////////////////////////////
  //
  // Vertex access
  //

  /*
  Returns:
    Number of vertices in the active level.
  */
  unsigned int VertexCount() const;

  /*
  Parameters:
    hash_type - [in]
      All hashes include vertex id.
      Geometry hashes include vertex tag, vertex control point, and vertex displacement.
  Returns:
    A SHA1 hash of the SubD's vertices.
  */
  const ON_SHA1_Hash VertexHash( ON_SubDHashType hash_type ) const;

  const class ON_SubDVertex* FirstVertex() const;
  const class ON_SubDVertex* LastVertex() const;

  /*
  Example:
    ON_SubDVertexIterator vit = subd.VertexIterator();
    for ( const ON_SubDVertex* v = vit.FirstVertex(); nullptr != v; v = vit.NextVertex())
    {
      ...
    }
  */
  class ON_SubDVertexIterator VertexIterator() const;

  /*
  Description:
    Avoid using this class. It is more efficient to use
    an ON_SubDVertexIterator returned by VertexIterator().
  */
  class ON_SubDVertexArray VertexArray() const;

  /*
  Parameters:
    vertex_id - [in]
  Returns:
    If vertex_id identifies a valid vertex in this ON_SubD, then
    a pointer to that vertex is returned.
    Otherwise, nullptr is returned.
  */
  const class ON_SubDVertex* VertexFromId(
    unsigned int vertex_id
  ) const;

  const class ON_SubDVertex* VertexFromComponentIndex(
    ON_COMPONENT_INDEX component_index
  ) const;

  /////////////////////////////////////////////////////////
  //
  // Edge access
  //

  /*
  Returns:
    Number of edges in the active level.
  */
  unsigned int EdgeCount() const;

  /*
  Parameters:
    hash_type - [in]
      All hashes include edge id, edge vertex ids in order, the edge crease/smooth attribute.
      Geometry hashes include edge displacements.
  Returns:
    A SHA1 hash of the SubD's edges.
  */
  const ON_SHA1_Hash EdgeHash(ON_SubDHashType hash_type) const;

  const class ON_SubDEdge* FirstEdge() const;
  const class ON_SubDEdge* LastEdge() const;

  /*
  Example:
    ON_SubDEdgeIterator eit = subd.EdgeIterator();
    for ( const ON_SubDEdge* e = eit.FirstEdge(); nullptr != e; e = eit.NextEdge())
    {
      ...
    }
  */
  class ON_SubDEdgeIterator EdgeIterator() const;

  /*
  Description:
    Avoid using this class. It is more efficient to use
    an ON_SubDEdgeIterator returned by EdgeIterator().
  */
  class ON_SubDEdgeArray EdgeArray() const;

  /*
  Parameters:
    edge_id - [in]
  Returns:
    If edge_id identifies a valid edge in this ON_SubD, then
    a pointer to that edge is returned.
    Otherwise, nullptr is returned.
  */
  const class ON_SubDEdge* EdgeFromId(
    unsigned int edge_id
    ) const;

  const class ON_SubDEdge* EdgeFromComponentIndex(
    ON_COMPONENT_INDEX component_index
  ) const;

  /////////////////////////////////////////////////////////
  //
  // Face access
  //

  /*
  Returns:
    Number of faces in the active level.
  */
  unsigned int FaceCount() const;

  /*
  Parameters:
    hash_type - [in]
  Returns:
    A SHA1 hash of the SubD's faces.
  */
  const ON_SHA1_Hash FaceHash(ON_SubDHashType hash_type) const;

  const class ON_SubDFace* FirstFace() const;
  const class ON_SubDFace* LastFace() const;

  /*
  Example:
    ON_SubDFaceIterator fit = subd.FaceIterator();
    for ( const ON_SubDFace* f = fit.FirstFace(); nullptr != f; f = fit.NextFace())
    {
      ...
    }
  */
  class ON_SubDFaceIterator FaceIterator() const;

  /*
  Description:
    Avoid using this class. It is more efficient to use
    an ON_SubDFaceIterator returned by FaceIterator().
  */
  class ON_SubDFaceArray FaceArray() const;

  /*
  Parameters:
    face_id - [in]
  Returns:
    If face_id identifies a valid face in this ON_SubD, then
    a pointer to that face is returned.
    Otherwise, nullptr is returned.
  */
  const class ON_SubDFace* FaceFromId(
    unsigned int face_id
    ) const;


  const class ON_SubDFace* FaceFromComponentIndex(
    ON_COMPONENT_INDEX component_index
  ) const;

  /////////////////////////////////////////////////////////
  //
  // Component (vertex, edge, face) state ( selected, highlighted, ... ) tools
  //   NOTE: 
  //    All component status settings are mutable
  //    All are copied. 
  //    None are saved.
  //

  /*
  Parameters:
    states_filter - [in]
    bAllEqualStates - [in]
      If a state is set in states_filter, all active level components
      with the same state set will be included in the 
      components_with_set_states[] array.  
      If bAllEqualStates is true, then ON_ComponentStatus::AllEqualStates()
      is used to test for inclusion.  
      If bAllEqualStates is false, then ON_ComponentStatus::SomeEqualStates()
      is used to test for inclusion.
    components_with_set_states - [out]
  Returns:
    Number of returned components.
  */
  unsigned int GetComponentsWithSetStates(
    ON_ComponentStatus states_filter,
    bool bAllEqualStates,
    ON_SimpleArray< ON_SubDComponentPtr >& components_with_set_states
    ) const;

  
  /*
  Description:
    Set states on an individual component.
  Parameters:
    component_ptr - [in]
      The states will be set on this component.
    states_to_set - [in]
      If a state is set in the states_to_set parameter, the same
      state will be set on the component.      
  Returns:
    0: no state settings changed on the component.
    1: some state setting changed on the component.
  */
  unsigned int SetComponentStates(
    ON_SubDComponentPtr component_ptr,
    ON_ComponentStatus states_to_set
    ) const;

  /*
  Description:
    Clear states on an individual component.
  Parameters:
    component_ptr - [in]
      The states will be cleared on this component.
    states_to_clear - [in]
      If a state is set in the states_to_clear parameter, the same
      state will be cleared on the component.      
  Returns:
    0: no state settings changed on the component.
    1: some state setting changed on the component.
  */
  unsigned int ClearComponentStates(
    ON_SubDComponentPtr component_ptr,
    ON_ComponentStatus states_to_clear
    ) const;
  
  /*
  Description:
    Copy status settings to an individual component.
  Parameters:
    component_ptr - [in]
      The states will be copied to this component.
    status_to_copy - [in]
  Returns:
    1: some state settings changed on the component.
    1: some state setting changed on the component.
  */
  unsigned int SetComponentStatus(
    ON_SubDComponentPtr component_ptr,
    ON_ComponentStatus status_to_copy
    ) const;

  /*
  Description:
    Delete components in cptr_list[]. 
    If a vertex is in cptr_list[], the vertex and every edge and face attached
    to the vertex are deleted.
    If an edge is in cptr_list[], the edge and every face attached
    to the edge are deleted.
    If a face is in cptr_list[], the face is deleted.
  Parameters:
    cptr_list - [in]
    cptr_count - [in]
      length of cptr_list[] array.
    bMarkDeletedFaceEdges - [in]
      If true, surviving edges attached to delete faces 
      have their runtmime mark set.
  Returns:
    1: some state settings changed on the component.
    1: some state setting changed on the component.
  */
  bool DeleteComponents(
    const ON_SubDComponentPtr* cptr_list,
    size_t cptr_count,
    bool bMarkDeletedFaceEdges
    );

  bool DeleteComponents(
    const ON_SimpleArray<ON_SubDComponentPtr>& cptr_list,
    bool bMarkDeletedFaceEdges
  );

  bool DeleteComponentsForExperts(
    const ON_SubDComponentPtr* cptr_list,
    size_t cptr_count,
    bool bDeleteIsolatedEdges,
    bool bUpdateTagsAndCoefficients,
    bool bMarkDeletedFaceEdges
    );

  /*
  Description:
    Delete marked components.
  Parameters:
    bDeleteMarkedComponents - [in]
      If true, marked components are deleted.
      If false, unmarked components are deleted.      
    mark_bits - [in]
      A component is marked if component.m_status.IsMarked(mark_bits) is true.
  */
  bool DeleteMarkedComponents(
    bool bDeleteMarkedComponents,
    ON__UINT8 mark_bits,
    bool bMarkDeletedFaceEdges
  );

  /*
  Description:
    Delete marked components.
  Parameters:
    bDeleteMarkedComponents - [in]
      If true, marked components are deleted.
      If false, unmarked components are deleted.
    mark_bits - [in]
      A component is marked if component.m_status.IsMarked(mark_bits) is true.
  */
  bool DeleteMarkedComponentsForExperts(
    bool bDeleteMarkedComponents,
    ON__UINT8 mark_bits,
    bool bDeleteIsolatedEdges,
    bool bUpdateTagsAndCoefficients,
    bool bMarkDeletedFaceEdges
  );

public:
  /*
  Description:
    Removes all per face material channel index overrides on the active level.
  Returns:
    Number of changed faces.
  Remarks:
    Per face material channel indices are a mutable property on ON_SubDFace and are set with ON_SubDFace.SetMaterialChannelIndex().
  */
  unsigned int ClearPerFaceMaterialChannelIndices();

  /*
  Returns:
    True if one or more faces on the active level have per face material channel index overrides.
  Remarks:
    Per face material channel indices are a mutable property on ON_SubDFace and are set with ON_SubDFace.SetMaterialChannelIndex().
  */
  bool HasPerFaceMaterialChannelIndices() const;

  /*
  Description:
    Removes all per face color overrides on the active level.
  Returns:
    Number of changed faces.
  Remarks:
    Per face colors are a mutable property on ON_SubDFace and are set with ON_SubDFace.SetPerFaceColor().
  */
  unsigned int ClearPerFaceColors() const;

  /*
  Returns:
    True if one or more faces on the active level have per face color overrides.
  Remarks:
    Per face colors are a mutable property on ON_SubDFace and are set with ON_SubDFace.SetPerFaceColor().
  */
  bool HasPerFaceColors() const;

  /*
  Description:
    If a face has a nonzero PackId(), then its per face color is set to ON_Color::RandomColor(f->PackId()).
    Otherwise, its per face color is cleared.
  */
  void SetPerFaceColorsFromPackId() const;

  /*
  Returns:
    True if per face colors were set by SetPerFaceColorsFromPackId().
  */
  bool HasPerFaceColorsFromPackId() const;


  /*
  Description:
    If a SubD is symmetric and a face belongs to a symmetry set, then per face color is
    set according to the motif the face belongs to.
    Otherwise, its per face color is cleared.
  */
  void SetPerFaceColorsFromSymmetryMotif() const;

  /*
  Returns:
    True if per face colors were set by SetPerFaceColorsFromSymmetryMotif().
  */
  bool HasPerFaceColorsFromSymmetryMotif() const;

  /*
  Description:
    Sets ON_SubDComponent MarkBits() to
    0: component is not in a symmetry set motif
    n>=1: 
      The component is the the n-th element in the symmetry set
      with n=1 indicating the component in the primary motif.
  */
  void SetComponentMarkBitsFromSymmetryMotif() const;


  ///*
  //Description:
  //  The ON__INT_PTRs in the tree are const ON_SubDMeshFragment* pointers.
  //  The bounding boxes are from the surface points.
  //*/
  //ON_RTreeRef FragmentTree() const;

  ///*
  //Description:
  //  If the tree is not needed and memory resources are tight, then call ClearTree()
  //  to remove the RTree.
  //*/
  //void ClearFragmentTree();

  ///*
  //Description:
  //  The ON__INT_PTRs in the tree are const ON_SubDComponentPtrs.
  //  The bounding boxs are based on the subd
  //*/
  //ON_RTreeRef ControlNetComponentTree(
  //  bool bIncludeVertices,
  //  bool bIncludeEdges,
  //  bool bIncludeFaces
  //  ) const;

  ///*
  //Description:
  //  If the tree is not needed and memory resources are tight, then call ClearTree()
  //  to remove the RTree.
  //*/
  //void ClearControlNetComponentTree();

  /////////////////////////////////////////////////////////
  //
  // Topology Queries
  //

  /*
  Description:
    Determine solid orientation of the active level.
  Returns:
    +2     subd is a solid but orientation cannot be computed
    +1     subd is a solid with outward facing normals
    -1     subd is a solid with inward facing normals
     0     subd is not a solid
  See Also:
    ON_SubD::IsSolid
  */
 int SolidOrientation() const;

  /*
  Description:
    Test subd to see if the active level is a solid.  
    A "solid" is a closed oriented manifold.
  Returns:
    true       subd is a solid
    fals       subd is not a solid
  See Also:
    ON_SubDp::SolidOrientation
    ON_SubDp::IsManifold
  */
  bool IsSolid() const;
  
  /*
  Description:
    Test subd to see if the active level is an oriented manifold.
  Parameters:
    bIsOriented - [out]
      True if every edge that has two faces is oriented.
      Note that non-manifold edges are ignored.
    bHasBoundary - [in]
      True if there is at least one edge with a single face.
  Returns:
    True if the subd is a manifold (has at lease one face and every edge has 1 or 2 faces).
    False if the subd is not a manifold (has no faces or at least one edge with 0 or 3 or more faces)
  See Also:
    ON_SubDp::IsSolid
  */
  bool IsManifold(
    bool& bIsOriented,
    bool& bHasBoundary
    ) const;

  bool IsManifold() const;



    /*
  Description:
    Automatically get a  boundary from a seed edge.
  Parameters:
    first_edge - [in]
      An edge with FaceCount() <= 1. 
      The search for the second edge occurs and first_edge.RelativeVertex(1)
      and all edges added to boundary_edge_chain[] have FaceCount() = first_edge.Edge()->FaceCount().
    bUseEdgeMarks -[in]
      If true, only unmarked edges will be added to boundary_edge_chain[]
      and they will be marked when added to boundary_edge_chain[].
    boundary_edge_chain - [out]
      Edge chain beginning with first_edge. 
      When true is returned, boundary_edge_chain[] has 3 or more edges and is a closed loop.
      When false is returned, boundary_edge_chain[] will contain an open chain with 0 or more edges.
  Returns:
    true if boundary_edge_chain[] is a closed loop of 3 or more boundary edges.
  */
  static bool GetBoundaryEdgeChain(
    ON_SubDEdgePtr first_edge,
    bool bUseEdgeMarks,
    ON_SimpleArray< ON_SubDEdgePtr >& boundary_edge_chain
  );

  /////////////////////////////////////////////////////////
  //
  // Editing tools
  //

  unsigned int MergeColinearEdges(
    bool bMergeBoundaryEdges,
    bool bMergeInteriorCreaseEdges,
    bool bMergeInteriorSmoothEdges,
    double distance_tolerance,
    double maximum_aspect,
    double sin_angle_tolerance
    );

  /*
  Description:
    Merge consecutive edges into a single edge.
  eptr0 - [in]
    first edge (will not be deleted)
  eptr1 - [in]
    second edge (will be deleted if edges can be merged)
  Returns:
    Merged edge (eptr0) or ON_SubDEdgePtr::Null if edges could not be merged
  */
  ON_SubDEdgePtr MergeConsecutiveEdges(
    ON_SubDEdgePtr eptr0,
    ON_SubDEdgePtr eptr1
    );

  /*
  Returns:
    True if eptr0.RelativeVetex(1) == eptr1.RelativeVetex(0) and both edges
    have the same set of faces.
  */
  static bool EdgesAreConsecutive(
    ON_SubDEdgePtr eptr0,
    ON_SubDEdgePtr eptr1
    );

  // returns true if all facets are consistently oriented
  bool IsOriented() const;

  // reverses the orientation of all facets
  bool ReverseOrientation() const;

  // Attempts to orient all facet to match the first facet.
  bool Orient() const;

  /*
  Description:
    Divide an edge into two contiguous edges.
    The input edge is modified to terminate at the new vertex.
    The new edge begins at the new vertex and ends at the original edge's m_vertex[1].
  edge - [in]
    edge to split.
  vertex_location - [in]
    location of the new vertex vertex.
    If vertex_location == ON_ON_3dPoint::UnsetPoint,
    then the edge's midpoint is used.
  Returns:
    A pointer to the new edge or nullptr if the input is not valid.
  Remarks:
    After all editing operations are completed, you must call this->UpdateEdgeSectorCoefficients(true) before
    evaluation.
  */
  const class ON_SubDEdge* SplitEdge(
    class ON_SubDEdge* edge,
    ON_3dPoint vertex_location
  );

  /*
  Description:
    Divide an edge into two contiguous edges.
  edge - [in]
    edge to split.
  vertex_location - [in]
    location of the new vertex vertex.
    If vertex_location == ON_ON_3dPoint::UnsetPoint,
    then the edge's midpoint is used.
  new_edge_end - [in]
    This paratmer is 0 or 1 and dtermines where the new edge is inserted.
    Below v0 = input eptr.RelativeVertex(0), v1 = new vertex, v2 = input eptr.RelativeVertex(1),
    and new_eptr = returned edge pointer.
    If edge_end is 0, new_eptr is first: v0 = new_eptr.RelativeVertex(0), v1 = new_eptr.RelativeVertex(1)=eptr.RelativeVertex(0), v2 = eptr.RelativeVertex(1).
    If edge_end is 1, new_eptr is last: v0 = eptr.RelativeVertex(0), v1 = eptr.RelativeVertex(1)=new_eptr.RelativeVertex(0), v2 = new_eptr.RelativeVertex(1).
  Returns:
    A pointer to the new edge or ON_SubDEdgePtr::Null if the input is not valid.
  Remarks:
    After all editing operations are completed, you must clear the evaluation cache
    and call this->UpdateEdgeSectorCoefficients(true).
  */
  const ON_SubDEdgePtr SplitEdge(
    ON_SubDEdgePtr eptr,
    ON_3dPoint vertex_location,
    unsigned new_edge_end
  );
  
  /*
  Description:
    Spin an edge's endpoints around the boundary of its neighboring faces.
    In a counter-clockwise spin (looking at faces from their shared up orientation):
      The edge's start vertex is moved to the next vertex in the boundary
      of the face on the right-hand side of the edge.
      The edge's end vertex is moved to the next vertex in the boundary
      of the face on the left-hand side of the edge.
    Note that reversing the input edge does not change the result.
  Parameters:
    edge - [in]
      edge to spin.
    spin_clockwise - [in]
      false spins the edge counter-clockwise, true spins the edge clockwise
      in the adjacent faces.
  Returns:
    A pointer to the spun edge or nullptr if the input is not valid.
  */
  const class ON_SubDEdge* SpinEdge(
    class ON_SubDEdge* edge,
    bool spin_clockwise = false
  );
  
  /*
  Description:
    Spin an edge's endpoints around the boundary of its neighboring faces.
    In a counter-clockwise spin (looking at faces from their shared up orientation):
      The edge's start vertex is moved to the next vertex in the boundary
      of the face on the right-hand side of the edge.
      The edge's end vertex is moved to the next vertex in the boundary
      of the face on the left-hand side of the edge.
    Note that reversing the input edge does not change the result.
  Parameters:
    edge - [in]
      edge to spin.
    spin_clockwise - [in]
      false spins the edge counter-clockwise, true spins the edge clockwise
      in the adjacent faces.
  Returns:
    A pointer to the spun edge or nullptr if the input is not valid.
  */
  const ON_SubDEdgePtr SpinEdge(
    ON_SubDEdgePtr eptr,
    bool spin_clockwise = false
  );

  /*
  Description:
    Divide a face into two faces by inserting an edge connecting the specified vertices.
  Parameters:
    face - [in]
      A face with at least four edges.
    fvi0 - [in]
    fvi1 - [in]
      Face vertex indices of the inserted edge's ends.
  Returns:
    A pointer to the inserted edge.
    The inserted edge runs from face->Vertex(fvi0) to face->Vertex(fvi1).
    ON_SubDEdge.Face(0) is the original face and ON_SubDEdge::Face(1) is 
    the added face.
    The first edge of both faces is the inserted edge.
  */
  const class ON_SubDEdge* SplitFace(
    class ON_SubDFace* face,
    unsigned int fvi0,
    unsigned int fvi1
    );

  /*
  Description:
    Divide a face into two faces by inserting an edge connecting the specified vertices.
  Parameters:
    face - [in]
      A face with at least four edges.
    v0 - [in]
    v1 - [in]
      Face vertices of the inserted edge's ends.
  Returns:
    A pointer to the inserted edge.
    The inserted edge runs from v0 to v1.
    ON_SubDEdge.Face(0) is the original face and ON_SubDEdge::Face(1) is 
    the added face.
    The first edge of the input face remains the first edge of face.  
    The inserted edge is the first edge of the added face.
  */
  const class ON_SubDEdge* SplitFace(
    class ON_SubDFace* face,
    const class ON_SubDVertex* v0,
    const class ON_SubDVertex* v1
    );


  /*
  Description:
    Divide a face into two faces by inserting an edge connecting the specified vertices.
  Parameters:
    face - [in]
      A face with at least four edges.
    fvi0 - [in]
    fvi1 - [in]
      Face vertex indices of the inserted edge's ends.
    new_face_side - [in]
      0: The new face will be on the left side of the inserted edge.
      0: The new face will be on the right side of the inserted edge.
  Returns:
    The edge and edgeptr are both being af both oriented 
    The inserted edge and returned edge ptr runs from face->Vertex(fvi0) to face->Vertex(fvi1).
    the new face is SplitFace(...).RelativeFace(new_face_side) and the original face is SplitFace(...).RelativeFace(new_face_side).
  */
  const ON_SubDEdgePtr SplitFace(
    class ON_SubDFace* face,
    unsigned int fvi0,
    unsigned int fvi1,
    unsigned new_face_side
  );

  /*
  Description:
    Divide a face into two faces by inserting an edge connecting the specified vertices.
  Parameters:
    face - [in]
      A face with at least four edges.
    v0 - [in]
    v1 - [in]
      Face vertices of the inserted edge's ends.
    new_face_side - [in]
      0: The new face will be on the left side of the inserted edge.
      0: The new face will be on the right side of the inserted edge.
  Returns:
    The edge and edgeptr are both being af both oriented
    The inserted edge and returned edge ptr runs from face->Vertex(fvi0) to face->Vertex(fvi1).
    the new face is SplitFace(...).RelativeFace(new_face_side) and the original face is SplitFace(...).RelativeFace(new_face_side).
  */
  const ON_SubDEdgePtr SplitFace(
    class ON_SubDFace* face,
    const class ON_SubDVertex* v0,
    const class ON_SubDVertex* v1,
    unsigned new_face_side
  );

  /*
  Description:
    Replace a face with a triangle fan  by adding a single new vertex at fan_center_point 
    and adding tringle made from the face's edes to the center point.
  Parameters:
    face - [in]
      This face is replaced with a triangle fan and becomes the first triangle in the fan.
    fan_center_point - [in]
      If valid, this point is used as the fan's center.
      Otherwise the centriod of the face's vertices is used s the fan's center.
      When in doubt, pass ON_3dPoint::UnsetPoint.
    bMarkFaces - [in]
      If true, face and new triangles are marked.
      Existing marks are not modified.
  Returns:
    If successful, the new vertex at the center of the triangle fan.
    Otherwise, nullptr is returned.
  */
  const class ON_SubDVertex* ReplaceFaceWithTriangleFan(
    class ON_SubDFace* face,
    ON_3dPoint fan_center_point,
    bool bMarkFaces
    );



  /*
  Description:
    When finished editing a SubD, call this function to delete all cached evaluation
    values and update all vertex tag, edge tags, edge sector coefficients.
  Remarks:
    This function is the most reliable (and heavy handed) way to update SubD component
    information. Expert users can choose to be more selective when certain about 
    exactly what needs to be modified.
  */
  void SubDModifiedNofification();


  /*
  Description:
    Updates vertex tag, edge tag, and edge coefficient values
    on the active level.

    After completing custom editing operations that modify the
    topology of the SubD control net or changing values of
    vertex or edge tags, the tag and sector coefficients
    information on nearby components in the edited areas
    need to be updated.

  Parameters:
    bUnsetValuesOnly - [in]
      If true, the update is restricted to vertices tagged as 
      ON_SubDVertexTag::Unset and edges tagged as ON_SubDEdgeTag::Unset.

  Returns:
    Number of vertices and edges that were changed during the update.
  */
  unsigned int UpdateAllTagsAndSectorCoefficients(
    bool bUnsetValuesOnly
  );

  /*
  Description:
    This tool if for expert users writing advanced editing tools.
    After completing custom editing operations that modify the
    topology of the SubD control net or changing values of
    vertex or edge tags, the tag and sector coefficients
    information on nearby components in the edited areas
    need to be updated.
  Parameters:
    bUnsetTagsOnly - [in]
      If bUnsetTagsOnly is true, then only unset tags and
      ill be updated.
      If bUnsetTagsOnly is false, then all tags and
      will be checked and updated as needed.
  Returns:
    Number of vertices that changed during the update.
  Remarks:
    It is easiest to call UpdateAllTagsAndSectorCoefficients().
  */
  unsigned int UpdateVertexTags(
    bool bUnsetVertexTagsOnly
    );

  /*
  Description:
    This tool if for expert users writing advanced editing tools.
    After completing custom editing operations that modify the
    topology of the SubD control net or changing values of
    vertex or edge tags, the tag and sector coefficients
    information on nearby components in the edited areas
    need to be updated.
  Parameters:
    bUnsetValuesOnly - [in]
      If bUnsetValuesOnly is true, then only unset tags and
      sector coefficients will be updated.
      If bUnsetValuesOnly is false, then all tags and
      sector coefficients will be checked and updated as needed.
  Returns:
    Number of edges that had a tag value changed or sector
    coefficient set to ON_SubDSectorType::UnsetSectorCoefficient.
  Remarks:
    It is easiest to call UpdateAllTagsAndSectorCoefficients().
  */
  unsigned int UpdateEdgeTags(
    bool bUnsetEdgeTagsOnly
    );

  /*
  Description:
    This tool if for expert users writing advanced editing tools.
    After completing custom editing operations that modify the
    topology of the SubD control net or changing values of
    vertex or edge tags, the tag and sector coefficients
    information on nearby components in the edited areas
    need to be updated.
  Parameters:
    bUnsetValuesOnly - [in]
      If bUnsetValuesOnly is true, then only unset tags and
      sector coefficients will be updated.
      If bUnsetValuesOnly is false, then all tags and
      sector coefficients will be checked and updated as needed.
  Returns:
    Number of edges that had a tag value changed or sector
    coefficient set to ON_SubDSectorType::UnsetSectorCoefficient.
  Remarks:
    It is easiest to call UpdateAllTagsAndSectorCoefficients().
  */
  unsigned int UpdateEdgeSectorCoefficients(
    bool bUnsetSectorCoefficientsOnly
    ) const;


  /*
  Descripiton:
    Sets the m_group_id value to 0 for every vertex, edge and face.
  Returns:
    Number of marks that were cleared.
  */
  unsigned int ClearGroupIds() const;

  /*
  Descripiton:
    Sets the m_group_id value to 0 for every vertex.
  Returns:
    Number of group id values that were changed.
  */
  unsigned int ClearVertexGroupIds() const;

  /*
  Descripiton:
    Sets the m_group_id value to 0 for every edge.
  Returns:
    Number of group id values that were changed.
  */
  unsigned int ClearEdgeGroupIds() const;

  /*
  Descripiton:
    Sets the m_group_id value to 0 for every face.
  Returns:
    Number of group id values that were changed.
  */
  unsigned int ClearFaceGroupIds() const;

  /*
  Descripiton:
    Sets the m_group_id value to 0 for the specified components.
  Parameters:
    bClearVertexGroupIds - [in]
      If true, m_group_id for every vertex is set to zero.
    bClearEdgeGroupIds - [in]
      If true, m_group_id for every edge is set to zero.
    bClearFaceGroupIds - [in]
      If true, m_group_id for every face is set to zero.
  Returns:
    Number of group id values that were changed.
  */
  unsigned int ClearComponentGroupIds(
    bool bClearVertexGroupIds,
    bool bClearEdgeGroupIds,
    bool bClearFaceGroupIds
  ) const;


  /*
  Descripiton:
    Sets the m_status.MarkBits() value to 0 for every vertex, edge and face.
  Returns:
    Number of marks that were cleared.
  */
  unsigned int ClearMarkBits() const;

  /*
  Descripiton:
    Sets the m_status.MarkBits() value to 0 for every vertex.
  Returns:
    Number of group id values that were changed.
  */
  unsigned int ClearVertexMarkBits() const;

  /*
  Descripiton:
    Sets the m_status.MarkBits() value to 0 for every edge.
  Returns:
    Number of group id values that were changed.
  */
  unsigned int ClearEdgeMarkBits() const;

  /*
  Descripiton:
    Sets the m_status.MarkBits() value to 0 for every face.
  Returns:
    Number of group id values that were changed.
  */
  unsigned int ClearFaceMarkBits() const;

  /*
  Descripiton:
    Sets the m_status.MarkBits() value to 0 for the specified components.
  Parameters:
    bClearVertexMarkBits - [in]
      If true, m_status.MarkBits() for every vertex is set to zero.
    bClearEdgeMarkBits - [in]
      If true, m_status.MarkBits() for every edge is set to zero.
    bClearFaceMarkBits - [in]
      If true, m_status.MarkBits() for every face is set to zero.
  Returns:
    Number of group id values that were changed.
  */
  unsigned int ClearComponentMarkBits(
    bool bClearVertexMarkBits,
    bool bClearEdgeMarkBits,
    bool bClearFaceMarkBits
  ) const;

  /*
  Descripiton:
    Clears the m_status.RuntimeMark() for every vertex, edge and face.
  Returns:
    Number of marks that were cleared.
  */
  unsigned int ClearComponentMarks() const;

  /*
  Descripiton:
    Clears the m_status.RuntimeMark() for every vertex.
  Returns:
    Number of marks that were cleared.
  */
  unsigned int ClearVertexMarks() const;

  /*
  Descripiton:
    Clears the m_status.RuntimeMark() for every edge.
  Returns:
    Number of marks that were cleared.
  */
  unsigned int ClearEdgeMarks() const;

  /*
  Descripiton:
    Clears the m_status.RuntimeMark() for every face.
  Returns:
    Number of marks that were cleared.
  */
  unsigned int ClearFaceMarks() const;

  /*
  Descripiton:
    Selectively clear m_status.RuntimeMark()
  Parameters:
    bClearVertexMarks - [in]
      If true, m_status.ClearRuntimeMark() is called for every vertex.
    bClearEdgeMarks - [in]
      If true, m_status.ClearRuntimeMark() is called for every edge.
    bClearFaceMarks - [in]
      If true, m_status.ClearRuntimeMark() is called for every face.
    marked_component_list - [out]
      If not nullptr, then pointer to components that were marked 
      are returned in this marked_component_list[]
  Returns:
    Number of marks that were cleared.
  */
  unsigned int ClearComponentMarks(
    bool bClearVertexMarks,
    bool bClearEdgeMarks,
    bool bClearFaceMarks,
    ON_SimpleArray< const class ON_SubDComponentBase* >* marked_component_list
  ) const;

  unsigned int SetComponentMarks(
    bool bClearBeforeSet,
    const ON_SimpleArray< const class ON_SubDComponentBase* >& marked_component_list
  ) const;

  unsigned int GetMarkedComponents(
    bool bIncludeVertices,
    bool bIncludeEdges,
    bool bIncludeFaces,
    ON_SimpleArray< const class ON_SubDComponentBase* >& marked_component_list
  ) const;

  /*
  Parameters:
    bAddMarkedComponents - [in]
      If true, marked components are added to component_list[].
      If false, unmarked components are added to component_list[].
    mark_bits - [in]
      If mark_bits is zero, then a component is "marked" if component.Mark() is true.
      Otherwise a component is "marked" if mark_bits = component.MarkBits().
   */
   unsigned int GetMarkedComponents(
    bool bAddMarkedComponents,
    ON__UINT8 mark_bits,
    bool bIncludeVertices,
    bool bIncludeEdges,
    bool bIncludeFaces,
    ON_SimpleArray< class ON_SubDComponentPtr >& component_list
  ) const;

  unsigned int UnselectComponents(
    bool bUnselectAllVertices,
    bool bUnselectAllEdges,
    bool bUnselectAllFaces
  ) const;

  /*
  Description:
    Save the current component status of the indictated subd components.
  Parameters:
    bGetVertexStatus - [in]
    bGetEdgeStatus - [in]
    bGetFaceStatus - [in]
    bClearStatus - [in]
      If true, the bits in status_mask will also be cleared for the components.
    status_mask - [in]
      Status bits to save.
    component_list - [out]
    status_list - [out]
      component_list[] and status_list[] are parallel arrays for components with
      a matching status bit set.
  */
  unsigned int GetComponentStatus(
    bool bGetVertexStatus,
    bool bGetEdgeStatus,
    bool bGetFaceStatus,
    bool bClearStatus,
    ON_ComponentStatus status_mask,
    ON_SimpleArray< const class ON_SubDComponentBase* >& component_list,
    ON_SimpleArray< ON_ComponentStatus >& status_list
  ) const;

  unsigned int SetComponentStatus(
    ON_ComponentStatus status_mask,
    const ON_SimpleArray< const class ON_SubDComponentBase* >& component_list,
    const ON_SimpleArray< ON_ComponentStatus >& status_list
  ) const;

  /*
  Description:
    Transforms the SubD components in ci_list[].
  Parameters:
    xform - [in]
    ci_list - [in]
    ci_count - [in]
    component_location - [in]
      Select between applying the transform to the control net (faster)
      or the surface points (slower).
  Returns:
    Number of vertex locations that changed.
  */
  unsigned int TransformComponents(
    const ON_Xform& xform,
    const ON_COMPONENT_INDEX* ci_list,
    size_t ci_count,
    ON_SubDComponentLocation component_location
  );

  unsigned int TransformComponents(
    const ON_Xform& xform,
    const ON_SubDComponentPtr* cptr_list,
    size_t cptr_count,
    ON_SubDComponentLocation component_location
  );


  /*
  Description:
    Extrude entire subd bay adding a ring of faces around the boundary and moving the original subd.
  */
  unsigned int Extrude(
    const ON_Xform& xform
  );

  unsigned int ExtrudeComponents(
    const ON_Xform& xform,
    const ON_COMPONENT_INDEX* ci_list,
    size_t ci_count
  );

  unsigned int ExtrudeComponents(
    const ON_Xform& xform,
    const ON_SubDComponentPtr* cptr_list,
    size_t cptr_count
    );

  unsigned int ExtrudeComponents(
    const ON_Xform& xform,
    const ON_COMPONENT_INDEX* ci_list,
    size_t ci_count,
    bool bExtrudeBoundaries,
    bool bPermitNonManifoldEdgeCreation
  );

  unsigned int ExtrudeComponents(
    const ON_Xform& xform,
    const ON_SubDComponentPtr* cptr_list,
    size_t cptr_count,
    bool bExtrudeBoundaries,
    bool bPermitNonManifoldEdgeCreation
  );

private:
  unsigned int Internal_ExtrudeComponents(
    const ON_Xform& xform,
    const ON_SubDComponentPtr* cptr_list,
    size_t cptr_count,
    bool bExtrudeBoundaries,
    bool bPermitNonManifoldEdgeCreation
  );

public:

  /*
  Parameters:
    ci_list - [in]
      Array of ci_count ON_COMPONENT_INDEX values that identify the vertices. 
      Elements that do not identify a SubD vertex are ignored.
    ci_count - [in]
      Number of elements in the ci_list[] array.
    vertex_tag - [in]
      Desired tag. If a vertex has the desired tag or cannot accept the desired tag, 
      then that vertex is skipped. 
      If vertex_tag is ON_SubDVertexTag::Corner, then every edge touching 
      that vertex is converted to a crease.
  Returns:
    number of vertex tags that were changed.
  */
  unsigned int SetVertexTags(
    const ON_COMPONENT_INDEX* ci_list,
    size_t ci_count,
    ON_SubDVertexTag vertex_tag
  );

  /*
  Parameters:
    ci_list - [in]
      Array of ci_count ON_COMPONENT_INDEX values that identify the vertices. 
      Elements that do not identify a SubD vertex are ignored.
    ci_count - [in]
      Number of elements in the ci_list[] array.
    vertex_tag - [in]
      Desired tag. If a vertex has the desired tag or cannot accept the desired tag, 
      then that vertex is skipped.
      If vertex_tag is ON_SubDVertexTag::Corner, then every edge touching 
      that vertex is converted to a crease.
  Returns:
    number of vertex tags that were changed.
  */
  unsigned int SetVertexTags(
    const ON_SubDComponentPtr* cptr_list,
    size_t cptr_count,
    ON_SubDVertexTag vertex_tag
  );

  /*
  Returns:
    number of tags that were changed.
  */
  unsigned int SetEdgeTags(
    const ON_COMPONENT_INDEX* ci_list,
    size_t ci_count,
    ON_SubDEdgeTag edge_tag
  );

  /*
  Returns:
    number of tags that were changed.
  */
  unsigned int SetEdgeTags(
    const ON_SubDComponentPtr* cptr_list,
    size_t cptr_count,
    ON_SubDEdgeTag edge_tag
  );

  /*
  Returns:
    number of tags that were changed.
  */
  unsigned int SetEdgeTags(
    const ON_SimpleArray<ON_SubDComponentPtr>& cptr_list,
    ON_SubDEdgeTag edge_tag
  );


  /*
  Description:
    Remove all interior creases.
  Returns:
    Number of edges converted from crease to smooth.
  */
  unsigned int RemoveAllCreases();

  /*
  Description:
    Apply the Catmull-Clark subdivision algorithm and save the results
    in this ON_SubD.
  Parameters:
    level_index - [in]
      Level where subdivision starts
    count - [in] > 0
      Number of times to subdivide.
  Returns:
    Number of subdivision steps that succeeded. 
    (= count when everything works, < count when input is not valid)
  */
  bool GlobalSubdivide(
    unsigned int count
    );

  bool GlobalSubdivide();

  /// <returns>
  /// The number of quads a call to GlobalSubdivide() will create.
  ///< / returns>  
  unsigned int GlobalSubdivideQuadCount() const;

  /// <returns>
  /// The number of quads a call to GlobalSubdivide(subdivision_count) will create.
  ///< / returns>  
  unsigned int GlobalSubdivideQuadCount(unsigned int subdivision_count) const;

  /*
  Description:
    Apply the Catmull-Clark subdivision algorithm to the faces in face_list[].
  Parameters:
    face_list - [in]
      faces to subdivide
    face_count - [in]
      number of components.
  Returns:
    true if successful.
  */
  bool LocalSubdivide(
    class ON_SubDFace const*const* face_list,
    size_t face_count
  );

  bool LocalSubdivide(
    const ON_SimpleArray< const class ON_SubDFace* >& face_list
  );

  bool LocalSubdivide(
    const ON_SimpleArray<ON_COMPONENT_INDEX>& face_list
  );

  /*
  Description:
    Adds a vertex with tag = ON_SubDVertexTag::Unset.
  */
  class ON_SubDVertex* AddVertex(
    const double* P
    );

  /*
  Description:
    Adds a vertex with specified tag.
  */
  class ON_SubDVertex* AddVertex(
    ON_SubDVertexTag vertex_tag,
    const double* P
    );

  /*
  Description:
    Expert user tool to add a vertex with specified information. This function
    is useful when copying portions of an existing SubD to a new SubD.
  Parameters:
    candidate_vertex_id - [in]
      If candidate_vertex_id is > 0 and is available, 
      the returned value with have id = candidate_vertex_id.
      Otherwise a new id will be assigned.
    vertex_tag - [in]
      Pass ON_SubDVertexTag::Unset if not known.
    P - [in]
      nullptr or a 3d point.
   initial_edge_capacity - [in]
     Initial capacity of the m_edges[] array. Pass 0 if unknown.
   initial_face_capacity - [in]
     Initial capacity of the m_faces[] array. Pass 0 if unknown.
  */
  class ON_SubDVertex* AddVertexForExperts(
    unsigned int candidate_vertex_id,
    ON_SubDVertexTag vertex_tag,
    const double* P,
    unsigned int initial_edge_capacity,
    unsigned int initial_face_capacity
    );

  /*
  Parameters:
    v - [in]
      A vertex with zero edge and zero faces.
  */
  bool ReturnVertexForExperts(
    ON_SubDVertex* v
  );

  /*
  Description:
    Search for a vertex with a specified control net point.
  Parameters:
    control_net_point - [in]
      Look for a vertex with this value for ControlNetPoint().
    tolerance - [in]
      Use 0.0 when in doubt. 
      If > 0.0, then the vertex closest to control_net_point 
      will be returned if the distance from that vertex to control_net_point
      is <= distance_tolerance.
  Returns:
    An ON_SubDVertex pointer or nullptr if none exists.
  */
  const class ON_SubDVertex* FindVertex(
    const double* control_net_point,
    double distance_tolerance
  ) const;

  /*
  Description:
    Search for a vertex with a specified control net point. If one does not
    exist, add a new one.
  Parameters:
    control_net_point - [in]
      Look for a vertex with this value for ControlNetPoint().
    tolerance - [in]
      Use 0.0 when in doubt.
      If > 0.0, then the vertex closest to control_net_point
      will be returned if the distance from that vertex to control_net_point
      is <= distance_tolerance.
  Returns:
    An ON_SubDVertex pointer or nullptr if none exists.
    */
  const class ON_SubDVertex* FindOrAddVertex(
    const double* control_net_point,
    double distance_tolerance
  );

  /*
  Parameters:
    edge_face_count - [in]
      Number of faces the edge will eventually have.
      Pass 0 if the value is not known.
    v0 - [in]
      starting vertex
    v1 - [in]
      ending vertex
  Returns:
    If edge_face_count > 0x7FFFU, then ON_SubDEdgeTag::Unset is returned.

    If edge_face_count is 1 or >= 3, then ON_SubDEdgeTag::Crease is returned.

    If both vertex tags are ON_SubDVertexTag::Smooth, then ON_SubDEdgeTag::Smooth is returned.
   
    If edge_face_count is 1 and both vertex tags are ON_SubDVertexTag::Crease or ON_SubDVertexTag::Corner,
    then ON_SubDEdgeTag::Crease is returned.
   
    If edge_face_count is 2 and both vertex tags are set and both are not ON_SubDVertexTag::Smooth,
   then ON_SubDEdgeTag::SmoothX is returned.

   Otherwise, ON_SubDEdgeTag::Unset is returned.
  */
  static ON_SubDEdgeTag EdgeTagFromContext(
    unsigned int edge_face_count,
    const ON_SubDVertexTag v0_tag,
    const ON_SubDVertexTag v1_tag
  );

  static ON_SubDEdgeTag EdgeTagFromContext(
    unsigned int edge_face_count,
    const ON_SubDVertex* v0,
    const ON_SubDVertex* v1
  );

  /*
  Description:
    Add an edge with tag = ON_SubDEdgeTag::Unset to the subd.
  Parameters:
    v0 - [in]
    v1 - [in]
      The edge begins at v0 and ends at v1.
      The edge will be on the same level as the vertices.
  Returns:
    Pointer to the allocated edge.
  Remarks:
    ON_SubD::EdgeTagFromContext() can be used to determine edge
    tag values in simple situations.
  */
  class ON_SubDEdge* AddEdge(
    class ON_SubDVertex* v0,
    class ON_SubDVertex* v1
    );

  /*
  Description:
    Search for an edge connecting v0 and v1.
  Parameters:
    v0 - [in]
    v1 - [in]
      The edge begins at v0 and ends at v1.
      The edge will be on the same level as the vertices.
  Returns:
    An ON_SubDEdgePtr to a connecting edge or ON_SubDEdgePtr::Null if none exists.
  */
  const ON_SubDEdgePtr FindEdge(
    const class ON_SubDVertex* v0,
    const class ON_SubDVertex* v1
    ) const;

  /*
  Description:
    Search for an edge connecting v0 and v1. If none exists, then add one.
  Parameters:
    v0 - [in]
    v1 - [in]
      The edge begins at v0 and ends at v1.
      The edge will be on the same level as the vertices.
  Returns:
    An ON_SubDEdgePtr to a connecting edge or ON_SubDEdgePtr::Null if none exists.
  */
  const ON_SubDEdgePtr FindOrAddEdge(
    class ON_SubDVertex* v0,
    class ON_SubDVertex* v1
    );


  /*
  Description:
    Add an edge to the subd.
  Parameters:
    edge_tag - [in]
      ON_SubDEdgeTag::Unset
        Edge tag is not known at this time.
      ON_SubDEdgeTag::Smooth
        Smooth edge. If both vertices are tagged as not smooth, the
        tag on the returned edge will be ON_SubDEdgeTag::SmoothX.  This
        tag is changed to ON_SubDEdgeTag::Smooth on the first
        subdivision step.
      ON_SubDEdgeTag::Crease.
        Crease edge.  Both vertices must be tagged as not smooth.
    v0 - [in]
    v1 - [in]
      The edge begins at v0 and ends at v1.
      The edge will be on the same level as the vertices.
  Returns:
    Pointer to the allocated edge.
  Remarks:
    ON_SubD::EdgeTagFromContext() can be used to determine edge
    tag values in simple situations.
  */
  class ON_SubDEdge* AddEdge(
    ON_SubDEdgeTag edge_tag,
    class ON_SubDVertex* v0,
    class ON_SubDVertex* v1
    );

  /*
  Description:
    Add an edge to the subd.
  Parameters:
    edge_tag - [in]
      ON_SubDEdgeTag::Unset
        Edge tag is not known at this time.
      ON_SubDEdgeTag::Smooth
        Smooth edge. If both vertices are tagged as not smooth, the
        tag on the returned edge will be ON_SubDEdgeTag::SmoothX.  This
        tag is changed to ON_SubDEdgeTag::Smooth on the first
        subdivision step.
      ON_SubDEdgeTag::Crease.
        Crease edge.  Both vertices must be tagged as not smooth.
    v0 - [in]
    v1 - [in]
      The edge begins at v0 and ends at v1.
      The edge will be on the same level as the vertices.
    sharpness - [in]
      If edge_tag is ON_SubDEdge::Smooth or ON_SubDEdge::SmoothX, then
      the the edge's sharpness is set to sharpness.
      Otherwise, the sharpness parameter is ignored.
  Returns:
    Pointer to the allocated edge.
  Remarks:
    ON_SubD::EdgeTagFromContext() can be used to determine edge
    tag values in simple situations.
  */
  class ON_SubDEdge* AddEdge(
    ON_SubDEdgeTag edge_tag,
    class ON_SubDVertex* v0,
    class ON_SubDVertex* v1,
    ON_SubDEdgeSharpness sharpness
  );

  /*
  Description:
    Expert use tool to add an edge with precomputed sector coefficients.
  Parameters:
    edge_tag - [in]
      This expert user function does not automatically set the edge tag.
    v0 - [in]
      The edge begins at v0 and ends at v1.
    v0_sector_coefficient - [in]
      Pass ON_SubDSectorType::UnsetSectorCoefficient if unknown.
    v1 - [in]
      The edge begins at v0 and ends at v1.
    v1_sector_coefficient - [in]
      Pass ON_SubDSectorType::UnsetSectorCoefficient if unknown.
  */
  class ON_SubDEdge* AddEdgeWithSectorCoefficients(
    ON_SubDEdgeTag edge_tag,
    class ON_SubDVertex* v0,
    double v0_sector_coefficient,
    class ON_SubDVertex* v1,
    double v1_sector_coefficient
  );

  class ON_SubDEdge* AddEdgeWithSectorCoefficients(
    ON_SubDEdgeTag edge_tag,
    class ON_SubDVertex* v0,
    double v0_sector_coefficient,
    class ON_SubDVertex* v1,
    double v1_sector_coefficient,
    ON_SubDEdgeSharpness sharpness
  );

  /*
  Description:
    Expert user tool to add an edge with specified information. This function
    is useful when copying portions of an existing SubD to a new SubD.
  Parameters:
    candidate_edge_id - [in]
      If candidate_edge_id is > 0 and is available,
      the returned edge with have id = candidate_edge_id.
      Otherwise a new id will be assigned.
    edge_tag - [in]
      Pass ON_SubDEdgeTag::Unset if not known.
    v0 - [in]
      The edge begins at v0 and ends at v1.
    v0_sector_coefficient - [in]
      Pass ON_SubDSectorType::UnsetSectorCoefficient if unknown.
    v1 - [in]
      The edge begins at v0 and ends at v1.
    v1_sector_coefficient - [in]
      Pass ON_SubDSectorType::UnsetSectorCoefficient if unknown.
   initial_face_capacity - [in]
     Initial face capacity. Pass 0 if unknown.
  */
  class ON_SubDEdge* AddEdgeForExperts(
    unsigned int candidate_edge_id,
    ON_SubDEdgeTag edge_tag,
    class ON_SubDVertex* v0,
    double v0_sector_coefficient,
    class ON_SubDVertex* v1,
    double v1_sector_coefficient,
    unsigned int initial_face_capacity
  );

  class ON_SubDEdge* AddEdgeForExperts(
    unsigned int candidate_edge_id,
    ON_SubDEdgeTag edge_tag,
    class ON_SubDVertex* v0,
    double v0_sector_coefficient,
    class ON_SubDVertex* v1,
    double v1_sector_coefficient,
    ON_SubDEdgeSharpness sharpness,
    unsigned int initial_face_capacity
  );

  /*
  Parameters:
    e - [in]
      An edge in this subd with no vertices or faces.
  */
  bool ReturnEdgeForExperts(
    ON_SubDEdge* e
  );

  /*
  Parameters:
    edge0 - [in]
    edge1 - [in]
    edge2 - [in]
     The face will be oriented so the boundary has the edges
     in the order (edge0, edge1, edge2).
     Consecutive edges must have a single common vertex.
     The orientations of the ON_SubDEdgePtr elements in the 
     face's edge list are automatically calculated.
  Returns:
    A pointer to the added face. 
    The returned face is managed by the subd.
  */
  class ON_SubDFace* AddTriangleFace(
    class ON_SubDEdge* edge0,
    class ON_SubDEdge* edge1,
    class ON_SubDEdge* edge2
    );

  /*
  Parameters:
    edge_count - [in]
      Must be >= 3.
    edge0 - [in]
    edge1 - [in]
    edge2 - [in]
     The ON_SubDEdgePtr parameters must be oriented so that for consecutive pairs of edges, 
     edge0.RelativeVertex(1) and edges1.RelativeVertex(0) are same vertex. 
     The face will be oriented so the boundary has the edges
     in the order (edge0, edge1, edge2).
  Returns:
    A pointer to the added face. 
    The returned face is managed by the subd.
  */
  class ON_SubDFace* AddTriangleFace(
    ON_SubDEdgePtr edge0,
    ON_SubDEdgePtr edge1,
    ON_SubDEdgePtr edge2
    );

  /*
  Parameters:
    edge0 - [in]
    edge1 - [in]
    edge2 - [in]
    edge3 - [in]
     The face will be oriented so the boundary has the edges
     in the order (edge0, edge1, edge2. edge3).
     Consecutive edges must have a single common vertex.
     The orientations of the ON_SubDEdgePtr elements in the 
     face's edge list are automatically calculated.
  Returns:
    A pointer to the added face. 
    The returned face is managed by the subd.
  */
  class ON_SubDFace* AddQuadFace(
    class ON_SubDEdge* edge0,
    class ON_SubDEdge* edge1,
    class ON_SubDEdge* edge2,
    class ON_SubDEdge* edge3
    );
 
  /*
  Parameters:
    edge_count - [in]
      Must be >= 3.
    edge0 - [in]
    edge1 - [in]
    edge2 - [in]
    edge3 - [in]
     The ON_SubDEdgePtr parameters must be oriented so that for consecutive pairs of edges, 
     edge0.RelativeVertex(1) and edges1.RelativeVertex(0) are same vertex. 
     The face will be oriented so the boundary has the edges
     in the order (edge0, edge1, edge2,edge3).
  Returns:
    A pointer to the added face. 
    The returned face is managed by the subd.
  */
  class ON_SubDFace* AddQuadFace(
    ON_SubDEdgePtr edge0,
    ON_SubDEdgePtr edge1,
    ON_SubDEdgePtr edge2,
    ON_SubDEdgePtr edge3
    );

  /*
  Parameters:
    edges[] - [in]
     edges[] must have 3 or more elements.
     edges[i] and edges[(i+1)%edge_count] must have a single common vertex.
     The face will be oriented so the boundary has the edges
     in the order (edges[0], edges[1], ..., edges[edge_count-1]).
     The orientations of the ON_SubDEdgePtr elements in the 
     face's edge list are automatically calculated.
  Returns:
    A pointer to the added face. 
    The returned face is managed by the subd.
  */
  class ON_SubDFace* AddFace(
    const ON_SimpleArray<ON_SubDEdge*>& edges
    );

  /*
  Parameters:
    edges[] - [in]
     edges[] must have 3 or more elements.
     The ON_SubDEdgePtr parameters must be oriented so that
     edges[i].RelativeVertex(1) and edges[(i+1)%edge_count].RelativeVertex(0)
     are the same vertex.
     The face will be oriented so the boundary has the edges
     in the order (edges[0], edges[1], ..., edges[edge_count-1]).
  Returns:
    A pointer to the added face. 
    The returned face is managed by the subd.
  */
  class ON_SubDFace* AddFace(
    const ON_SimpleArray<ON_SubDEdgePtr>& edges
    );

  /*
  Parameters:
    edge_count - [in]
      Must be >= 3.
    edges[] - [in]
     edges[i] and edges[(i+1)%edge_count] must have a single common vertex.
     The face will be oriented so the boundary has the edges
     in the order (edges[0], edges[1], ..., edges[edge_count-1]).
     The orientations of the ON_SubDEdgePtr elements in the 
     face's edge list are automatically calculated.
  Returns:
    A pointer to the added face. 
    The returned face is managed by the subd.
  */
  class ON_SubDFace* AddFace(
    class ON_SubDEdge * const * edges,
    unsigned int edge_count
    );

  /*
  Parameters:
    edge_count - [in]
      Must be >= 3.
    edges[] - [in]
     The ON_SubDEdgePtr parameters must be oriented so that
     edges[i].RelativeVertex(1) and edges[(i+1)%edge_count].RelativeVertex(0)
     are the same vertex.
     The face will be oriented so the boundary has the edges
     in the order (edges[0], edges[1], ..., edges[edge_count-1]).
  Returns:
    A pointer to the added face. 
    The returned face is managed by the subd.
  */
  class ON_SubDFace* AddFace(
    const class ON_SubDEdgePtr* edges,
    unsigned int edge_count
    );

  /*
  Description:
    Finds an existing face or adds a new face with corners at face_vertices[].
  Parameters:
    new_edge_tag - [in]
      If an edge needs to be added, this tag is assigned to the new edge.
      When in doubt, pass ON_SubDEdgeTag::Unset and call this->UpdateAllTagsAndSectorCoefficients(true)
      after you are finished modifying the SubD.
    face_vertices - [in]
      Array of vertices at the face corners in counter-clockwise order.
    face_vertex_count - [in]
      Number of vertices in face_vertices[]
  Returns:
    If the input is not valid, nullptr is returned.
    If there is a face with the specified corners exists, then it is returned.
    Otherwise a new face is added and returned.
  */
  class ON_SubDFace* FindOrAddFace(
    ON_SubDEdgeTag new_edge_tag,
    const class ON_SubDVertex* face_vertices[],
    size_t face_vertex_count
  );

  /*
  Parameters:
    candidate_face_id - [in]
      If candidate_face_id is > 0 and is available,
      the returned face with have id = candidate_face_id.
      Otherwise a new id will be assigned.
    edge[] - [in]
      The edge[] array must be sorted and correct oriented
      (edge[i].RelativeVertex(1) == edge[(i+1)%edge_count].RelativeVertex(0)).
    edge_count - [in]
      Must be >= 3.
  */
  class ON_SubDFace* AddFaceForExperts(
    unsigned candidate_face_id,
    const class ON_SubDEdgePtr* edge,
    unsigned int edge_count
    );

  /*
  Parameters:
    f - [in]
      A face with zero edges
  */
  bool ReturnFaceForExperts(
    ON_SubDFace* f
  );

  /*
  Description:
    Add texture points to a face.
  Parameters:
    texture_points - [in]
      An array of face->EdgeCount() points.
    texture_points_count - [in]
      number of elements in texture_points[].
      Must be >= face->EdgeCount().
  Returns:
    True if texture points were set.
  Remarks:
    This function automatically handles the management of face texture point storage.
    Texture points are a mutable property on ON_SubDFace.
  */
  bool AddFaceTexturePoints(
    const class ON_SubDFace* face,
    const class ON_3dPoint* texture_points,
    size_t texture_points_count
  ) const;

  /*
  Description:
    Add texture point storage capacity to a face.
  Parameters:
    face - [in]
      The ability to store at least face->EdgeCount() texture points will be added to this face.
  Returns:
    Number of texture points that can be set (>= face->EdgeCount()).
  */
  unsigned int AllocateFaceTexturePoints(
    const class ON_SubDFace* face
  ) const;

public:

#pragma region RH_C_SHARED_ENUM [ON_SubD::PatchStyle] [Rhino.Geometry.SubDPatchStyle] [byte]
  /// <summary>
  /// SubD::PatchStyle identifies the style of patch used to fill holes.
  /// </summary>
  enum class PatchStyle : unsigned char
  {
    ///<summary>
    /// Not a valid style.
    /// This encourages developers to thoughtfully select a patch style and can 
    /// be used to indicate a UI control is not initialized.
    ///</summary>
    Unset = 0,

    ///<summary>
    /// Automatically choose a patch style that will generally create a good looking result.
    /// If a hole boundary is not convex, it is triangulated. Otherwise:
    /// If a hole has 3 edges, a single triangle face is used.
    /// If a hole has 4 edges, a single quad face is used.
    /// If a hole has 5 or more edges and an odd number of edges, a triangle fan is used. 
    /// If a hole has 6 or more edges and an even number of edges, a quad fan is used. 
    ///</summary>
    Automatic = 1, 

    ///<summary>
    /// A single face is used under all conditions.
    ///</summary>
    SingleFace = 2,

    ///<summary>
    /// A triangle fan used under all conditions. The center of the fan
    /// is the average of the hole boundary vertex control net points.
    ///</summary>
    TriangleFan = 3,

    ///<summary>
    /// If the hole boundary has an even number of edges, a quad fan is used.
    /// Otherwise a triangle fan is used. The center of the fan
    /// is the average of the hole boundary vertex control net points.
    ///</summary>
    QuadOrTriangleFan = 4,

    ///<summary>
    /// The hole boundary is triangluated.
    /// Typically this style is selected when a boundary not convex 
    /// and the other styles produce faces with overlapping regions.
    ///</summary>
    Triangulated = 5
  };
#pragma endregion


  
public:
  /*
  Description:
    Expert user tool to insert an edge in the face's edge array.
  Parameters:
    face - [in]
    edge - [in]
    edge_direction -[in]
    i - [in]
      index where the edge should be inserted.
  Returns:
    true if successful.
  Remarks:
    This tool is used during construction or editing of a SubD and the 
    connection is added even if the result is an invalid face or edge.
    It is up to the expert user to make enough changes to create a valid SubD.
  */
  bool AddFaceEdgeConnection(
    ON_SubDFace* face,
    unsigned int i,
    ON_SubDEdge* edge,
    ON__UINT_PTR edge_direction
    );

  /*
  Description:
    Expert user tool to insert an edge in the face's edge array.
  Parameters:
    face - [in]
    eptr - [in]
      direction must be set correctly
    i - [in]
      index where the edge should be inserted.
  Returns:
    true if successful.
  Remarks:
    This tool is used during construction or editing of a SubD and the 
    connection is added even if the result is an invalid face or edge.
    It is up to the expert user to make enough changes to create a valid SubD.
  */
  bool AddFaceEdgeConnection(
    ON_SubDFace* face,
    unsigned int i,
    ON_SubDEdgePtr eptr
    );


  /*
  Description:
    Expert user tool to insert an edge in the face's edge array.
  Parameters:
    face - [in]
    i - [in]
      index where the edge should be inserted.
    eptr - [in]
      direction must be set correctly
    bAddFaceToRelativeVertex0 - [in]
      If true, face is appended to the eptr.RelativeVertex(0)'s face array.
    bAddFaceToRelativeVertex1 - [in]
      If true, face is appended to the eptr.RelativeVertex(0)'s face array.
  Returns:
    true if successful.
  Remarks:
    This tool is used during construction or editing of a SubD and the
    connection is added even if the result is an invalid face or edge.
    It is up to the expert user to make enough changes to create a valid SubD.
  */
  bool AddFaceEdgeConnection(
    ON_SubDFace* face,
    unsigned int i,
    ON_SubDEdgePtr eptr,
    bool bAddbAddFaceToRelativeVertex0,
    bool bAddbAddFaceToRelativeVertex1
    );

  /*
  Description:
    Expert user tool to set a face's boundary.
  Parameters:
    face - [in]
      Face that is in the subd with no edges.
    edges - [in]
      Array of edge_count pointers that form a loop.
      Caller is responsible for insuring edges and vertices appear only
      one time in the loop.
    edge_count - [in]
      Number of edges in the boundary.      
  Returns:
    True if successful (all edge-face and vertex-face connections are set).
    False otherwise.
  Remarks:
    This tool is used during construction or editing of a SubD and the
    connection is added even if the result is an invalid face or edge.
    It is up to the expert user to make enough changes to create a valid SubD.
  */
  bool SetFaceBoundary(
    ON_SubDFace* face,
    const ON_SubDEdgePtr* edges,
    size_t edge_count
  );

  bool SetFaceBoundary(
    ON_SubDFace* face,
    const ON_SimpleArray<ON_SubDEdgePtr>& edges
  );


  /*
  Description:
    Expert user tool to insert an edge in the face's edge array.
  Parameters:
    face - [in]
    edge - [in]
      edge to remove
  Returns:
    true if successful.
  Remarks:
    This tool is used during construction or editing of a SubD and the 
    connection is removed even if the result is an invalid face or edge.
    It is up to the expert user to make enough changes to create a valid SubD.
  */
  bool RemoveFaceEdgeConnection(
    ON_SubDFace* face,
    ON_SubDEdge* edge
    );

  /*
  Description:
    Expert user tool to remove the connection between and edge and face.
  Parameters:
    face - [in]
    i - [in]
      index where the edge should be removed.
      0 <= i < face->EdgeCount()
    removed_edge - [out]
      removed edge
  Remarks:
    This tool is used during construction or editing of a SubD and the 
    connection is removed even if the result is an invalid face or edge.
    It is up to the expert user to make enough changes to create a valid SubD.
  */
  bool RemoveFaceEdgeConnection(
    ON_SubDFace* face,
    unsigned int i
    );

  /*
  Description:
    Expert user tool to remove the connection between and edge and face.
  Parameters:
    face - [in]
    i - [in]
      index where the edge should be removed.
    removed_edge - [out]
      removed edge
  Remarks:
    This tool is used during construction or editing of a SubD and the 
    connection is removed even if the result is an invalid face or edge.
    It is up to the expert user to make enough changes to create a valid SubD.
  */
  bool RemoveFaceEdgeConnection(
    ON_SubDFace* face,
    unsigned int i,
    ON_SubDEdgePtr& removed_edge
    );

  /*
  Description:
    Expert user tool to remove a connection between an edge and vertex
  Parameters:
    e - [in]
      An edge with zero attached faces.
    v - [in]
      A vertex attached to the e.
  Returns:
    If successful, true is returned.
    Otherwise false is returned.
  */
  bool RemoveEdgeVertexConnection(
    ON_SubDEdge* e,
    ON_SubDVertex* v
  );

  /*
  Description:
    Expert user tool to remove a connection between an edge and edge->vertex[evi]
  Parameters:
    e - [in]
      An edge with zero attached faces.
    evi - [in]
      0 or 1 specifying which vertex to remove.
  Returns:
    If successful, a pointer to the removed vertex is returned.
    Otherwise nullptr is returned.
  */
  ON_SubDVertex* RemoveEdgeVertexConnection(
    ON_SubDEdge* e,
    unsigned evi
  );

  /*
  Description:
    Expert user tool to remove all edge and vertex connections from a face
  Parameters:
    face - [in]
  Remarks:
    This tool is used during editing of a SubD and the 
    connections are removed even if the result is an invalid face or edge.
    It is up to the expert user to make enough changes to create a valid SubD.
  */
  bool RemoveFaceConnections(
    ON_SubDFace* face
  );

  bool GrowVertexEdgeArray(
    ON_SubDVertex* v,
    size_t capacity
    );
  bool GrowVertexFaceArray(
    ON_SubDVertex* v,
    size_t capacity
    );
  bool GrowEdgeFaceArray(
    ON_SubDEdge* e,
    size_t capacity
    );
  bool GrowFaceEdgeArray(
    ON_SubDFace* f,
    size_t capacity
    );


  /*
  Description:
    Clear all cached evaluation information (meshes, surface points, bounding boxes, ...) 
    that depends on edge tags, vertex tags, and the location of vertex control points.
  */
  void ClearEvaluationCache() const;

  /*
  Description:
    This function copies cached evaluations of component subdivision points and limit
    surface information from src to this. Typically this is done for performance critical
    situations like control point editing.
  */
  bool CopyEvaluationCacheForExperts(const ON_SubD& src);


 /*
  Description:
    Get a mesh representation of the ON_SubD control net.
  Parameters:
    mesh - [in]
      If not null, the returned mesh will be stored on
      the input class.

    priority - [in]
      Specifies what type of SubD information is most important to transfer to the mesh.
      For more details, see the comments for ON_SubDGetControlNetMeshPriority.

  Returns:
    A mesh representation of the ON_SubD control net.
  */
  class ON_Mesh* GetControlNetMesh(
    class ON_Mesh* mesh,
    ON_SubDGetControlNetMeshPriority priority
  ) const;

private:
  bool Internal_GetGeometryControlNetMesh(
    const class ON_SubDLevel& level,
    class ON_SubDLevelComponentIdIterator& vit_by_id,
    class ON_SubDLevelComponentIdIterator& fit_by_id,
    class ON_Mesh& mesh
  ) const;
  bool Internal_GetTextureCoordinatesGeometryControlNetMesh(
    const class ON_SubDLevel& level,
    class ON_Mesh& mesh
  ) const;
public:








#pragma region RH_C_SHARED_ENUM [ON_SubD::NurbsSurfaceType] [Rhino.Geometry.SubD.NurbsSurfaceType] [nested:byte]
  /// <summary>
  /// ON_SubD::NurbsSurfaceType specifies what type of NURBS surfaces are returned by ON_SubD.GetSurfaceNurbsFragments()
  /// </summary>
  enum class NurbsSurfaceType : unsigned char
  {
    ///<summary>
    /// Not a valid type. Used to indicate the type has not been set and to encourage developers to explicitly specify a type.
    /// When in doubt, specify NurbsSurfaceType::Large.
    ///</summary>
    Unset = 0,

    ///<summary>
    /// Onee NURBS surface will be generated for each SubD quad. 
    /// N NURBS surfaces will be generated for each SubD N-gon (N = 3, 5 or more). ON_Brepface may cover multiple
    /// Near extraordinary vertices, the surfaces may have lots of knots.
    ///</summary>
    Large = 1,

    ///<summary>
    /// NURBS surfaces will be as large as possible without the addition of extra knots. 
    /// Near extraordinary vertices, the surfaces may have lots of knots.
    /// This option is preferred when a user wants larger NURBS surfaces but not at the cost of additional NURBS control points.
    ///</summary>
    Medium = 2,

    ///<summary>
    /// NURBS surfaces will not be merged and will have clamped knots.
    ///</summary>
    Small = 3,

    ///<summary>
    /// NURBS surfaces will not be merged and will have unclamped uniform knots.
    /// This is useful as a starting point for customized merging and modifying
    /// continuity at extraordinary vertices.
    ///</summary>
    Unprocessed = 4
  };
#pragma endregion


  






public:
  /*
  Parameters:
    minimum_rectangle_count - [in]
      >= 1 minimum number of rectangles in texture domain
    image_width - [in]
    image_height = [in]
      If a texture image size is known, pass it here. Otherwise pass 0.0 for both parameters.
  Returns:
    Suggested way to partition a texture coordinate domain into rectangles.
    ON_2udex.i = "x" count
    ON_2udex.j = "y" count
    For example (3,2) would mean divide the 2d texture domain into 3 segments across and 2 segments vertically.
  */
  static const ON_2udex TextureDomainGridSize(
    unsigned minimum_rectangle_count,
    double image_width,
    double image_height
  );

  enum : unsigned int
  {
    /// <summary>
    /// ON_SUbDFace packing rectangle information is calculated so that there is at least 
    /// one unused pixel between adjacent packing rectangles when a texture image size is 
    /// TextureImageSuggestedMinimumSize x TextureImageSuggestedMinimumSize 
    /// pixels or larger.
    /// Core subd code assumes TextureImageSuggestedMinimumSize is a power of 2 and >= 512.
    /// </summary>
    TextureImageSuggestedMinimumSize = 1024
  };

  static ON_SubDTextureCoordinateType TextureCoordinateTypeFromUnsigned(
    unsigned int texture_coordinate_type_as_unsigned
  );

  static ON_SubDTextureCoordinateType TextureCoordinateTypeFromObsoleteTextureDomainType(
    unsigned int obsolete_texture_domain_type_as_unsigned
  );

  static  unsigned char ObsoleteTextureDomainTypeFromTextureCoordinateType(
    ON_SubDTextureCoordinateType texture_coordinate_type
  );


  static const ON_wString TextureCoordinateTypeToString(
    ON_SubDTextureCoordinateType texture_domain_type
    );

  /*
  Description:
    Set the texture coordinate type.
  Parameters:
    texture_coordinate_type - [in]
      Type of texture coordinates. 
      If ON_SubDTextureCoordinateType::Unset or ON_SubDTextureCoordinateType::Custom,
      is passed, the type setting is changed but no changes are made to texture coordinates.
  Remarks:
    Call SetTextureCoordinates() to restore them to the default values.

    If texture_coordinate_type is ON_SubDTextureCoordinateType::FromMapping, then
    the mapping this->TextureCoordinateMapping() is used. You may call
    this->SetTextureCoordinateMapping() to set the mapping.

    Calling this->SetTextureCoordinateType() does not change existing cached
    texture coordinates. At an appropriate time, call SetFragmentTextureCoordinates()
    to update texture coordinates on any cached fragments.

    SubD texture coordinate type and fragment texture coordinates are a mutable property.
    They can be changed by rendering applications as needed.
  */
  void SetTextureCoordinateType(
    ON_SubDTextureCoordinateType texture_coordinate_type
  ) const;

  ON_SubDTextureCoordinateType TextureCoordinateType() const;

  /*
  Returns:
    Number of faces with ON_SubDFace.TexturePointsAreSet() = true.
  */
  unsigned int TexturePointsAreSet() const;

  /*
  Description:
    Delete texture points from faces.
  Returns:
    Number of faces that had texture points.
  */
  unsigned int ClearTexturePoints() const;
    
  /*
  Parameters:
    bIgnoreTextureCoordinateType - [in]
      If true, the current texture mapping tag is returned.
      If false, the current texture mapping tag is returned only when ON_SubDTextureCoordinateType::FromMapping = TextureCoordinateType().
  Returns:
    The current texture mapping tag.
  Remarks:
    The texture mapping tag should be applied only when this->TextureCoordinateType()
    is ON_SubDTextureCoordinateType::FromMapping.
    SubD texture domains and coordinates are a mutable property.
    They can be changed by rendering applications as needed.
  */
  const ON_MappingTag TextureMappingTag(
    bool bIgnoreTextureCoordinateType
    ) const;

  /*
  Description:
    Set the texture mapping tag.
  Remarks:
    The texture mapping tag should be applied only when this->TextureCoordinateType()
    is ON_SubDTextureCoordinateType::FromMapping.

    Calling this->SetTextureMappingTag() does not change existing cached
    texture coordinates. At an appropriate time, call this->SetFragmentTextureCoordinates()
    to update texture coordinates on any cached fragments.

    SubD texture domains and coordinates are a mutable property.
    They can be changed by rendering applications as needed.
  */
  void SetTextureMappingTag(const class ON_MappingTag&) const;

  /*
  Returns:
    True if setting texture coordinates requires a set ON_TextureMapping mapping.
  Remarks:
    An explicit texture mapping is required when TextureCoordinateType() is
    ON_SubDTextureCoordinateType::FromMapping and TextureMappingTag()
    is set and not ON_MappingTag::SurfaceParameterMapping or an equivalent
    surface parameter mapping.
  */
  bool TextureMappingRequired() const;

  /*
  Parameters:
    texture_coordinate_type - [in]
    texture_mapping_tag - [in]
      If texture_coordinate_type is ON_SubDTextureCoordinateType::Custom, then
      then texture_mapping_tag information is included in the hash.
      Otherwise, texture_mapping_tag is ignored.
  Returns:
    A hash that uniquely identifies the information in  TextureCoordinateType() and
    TextureMappingTag() that applies to the current subd.
  */
  static const ON_SHA1_Hash TextureSettingsHash(
    ON_SubDTextureCoordinateType texture_coordinate_type,
    const class ON_MappingTag& texture_mapping_tag
  );

  /*
  Returns:
    ON_SubD::TextureSettingsHash(this->TextureCoordinateType(),this->TextureMappingTag());
  Remarks:
    Comparing with this->FragmentTextureCoordinatesTextureSettingsHash() can tell you
    if the current fragment texture coordinates were calculated using the same settings.
  */
  const ON_SHA1_Hash TextureSettingsHash() const;

   /*
  Description:
    If needed, set the fragment texture coordinates.
  Parameters:
    mapping - [in]
      If ON_SubD::TextureMappingRequired() is true, then you must
      pass a mapping with a tag that matches ON_SubDTextureMappingTag().
      Otherwise, mapping is ignored and you may pass ON_TextureMapping::Unset.
    bLazy - [in]
      If true and the m_T[] values were set using the same
      mapping parameters, then no calculation is performed.
  Returns:
    True if successful.
  Remarks:
    SubD texture domains and coordinates are a mutable property.
    They can be changed by rendering applications as needed.
    Call SetTextureCoordinatesFromFaceDomains() to restore them to the default values.
  */
  bool SetFragmentTextureCoordinates(
    const class ON_TextureMapping& mapping,
    bool bLazy
  ) const;

  /*
  Returns:
    The value of ON_SubD::TextureSettingsHash(texture_coordinate_type,texture_mapping_tag)
    for the texture_coordinate_type and texture_mapping_tag used to set the current
    fragment texture coordinates. If no fragments exist or the coordinates are not set,
    then ON_SHA1_Hash::EmptyContentHash is returned.
  */
  const ON_SHA1_Hash FragmentTextureCoordinatesTextureSettingsHash() const;

  /*
  Description:
    If a change requires existing fragment texture coordinates to be recalculated,
    then call ClearFragmentTextureCoordinatesTextureSettingsHash().
  */
  void ClearFragmentTextureCoordinatesTextureSettingsHash() const;

  /// <summary>
  /// Determing if this SubD's mesh fragments have per vertex texture coordinates.
  /// </summary>
  /// <returns>
  /// If this SubD has mesh fragments with per vertex texture coordinates, then true is returned.
  /// Otherwise false is returned.
  /// </returns>
  bool HasFragmentTextureCoordinates() const;

  /// <param name="texture_mapping_tag">
  /// This tag identifies the method and computation used to set the
  /// per vertex texture coordinates on the fragments. The tag is persistent so
  /// that the texture coordinates can be recomputed from the id in situations where
  /// fragments need to be recalculated.
  /// </param>
  /// <returns>
  /// If this SubD has mesh fragments with per vertex texture coordinates and 
  /// texture_mapping_tag = TextureMappingTag(), then true is returned.
  /// Otherwise false is returned.
  /// </returns>
  bool HasFragmentTextureCoordinates(
    ON_MappingTag texture_mapping_tag
  ) const;

  /// <param name="texture_settings_hash">
  /// This hash uniquely identifies the method and computation used to
  /// set the per vertex texture coordinates on the fragments. The hash is a runtime
  /// value that has meaning only when fragments with per vertex texture coordinates
  /// exist.
  /// </param>
  /// <returns>
  /// If this SubD has mesh fragments with per vertex texture coordinates and 
  /// texture_settings_hash = TextureSettingsHash(), then true is returned.
  /// Otherwise false is returned.
  /// </returns>
  bool HasFragmentTextureCoordinates(
    ON_SHA1_Hash texture_settings_hash
  ) const;

  /// <param name="texture_settings_hash">
  /// This hash uniquely identifies the method and computation used to
  /// set the per vertex texture coordinates on the fragments. The hash is a runtime
  /// value that has meaning only when fragments with per vertex texture coordinates
  /// exist.
  /// </param>
  /// <param name="texture_mapping_tag">
  /// This tag identifies the method and computation used to set the
  /// per vertex texture coordinates on the fragments. The tag is persistent so
  /// that the texture coordinates can be recomputed from the id in situations where
  /// fragments need to be recalculated.
  /// </param>
  /// <returns>
  /// If this SubD has mesh fragments with per vertex texture coordinates and 
  /// texture_settings_hash = TextureSettingsHash() and
  /// texture_mapping_tag = TextureMappingTag(), then true is returned.
  /// Otherwise false is returned.
  /// </returns>
  bool HasFragmentTextureCoordinates(
    ON_SHA1_Hash texture_settings_hash,
    ON_MappingTag texture_mapping_tag
  ) const;


private:
  /*
  Description:
    Unconditionally sets fragment texture coordinates when a mapping is not required or is not available.
  */
  bool Internal_SetFragmentTextureCoordinatesWithoutMapping() const;

  /*
  Description:
     Sets the value returned by FragmentTextureCoordinatesTextureSettingsHash()
  */
  void Internal_SetFragmentTextureCoordinatesTextureSettingsHash(ON_SHA1_Hash hash) const;

  ON_SubDTextureCoordinateType Internal_BestChoiceTextureCoordinateType(
    const class ON_TextureMapping& available_mapping
  ) const;

public:
  /*
  Description:
    Use a callback to set the vertex colros in m_C[].
  Parameters:
    bLazySet - [in]
      If bLazySet is true and fragment_colors_settings_hash and the current 
      FragmentColorsSettingsHash() are equal, then nothing is changed.
    fragment_colors_settings_hash - [in]
      A that uniquely identifies the method and parameters being
      used to set the fragment vertex colors. In general this hash
      should depend on the value of this->GeometryContentSerialNumber(),
      color_callback, and all values in the callback_context that
      determine vertex colors.  Under no circumstances should this
      hash depend on this->RenderContentSerialNumber().
    fragment_colors_mapping_tag - [in]
      If not applicable, pass ON_MappingTag::Unset.
      A mapping tag identifying what is setting the fragment colors.
      This is the only property that persists in SubD copies and saves in 3dm archives.
      Typically:
        m_mapping_id is an id you make up that identifies what is setting the colors (thickness, curvature, ...).
        m_mapping_type will be ON_TextureMapping::TYPE::false_colors.
        m_mapping_crc is a field from the 1990s that the SHA1 hash handles better now and setting
          m_mapping_crc = ON_CRC32(0, sizeof(fragment_colors_settings_hash), &fragment_colors_settings_hash)
          works well.
      works well.
      Typically, m_mapping_type = TYPE::false_colors.
    callback_context - [in]
      first parameter passed to color_callback()
    color_callback - [i]
      A callback function used to set the fragment vertex colors.
  */
  bool SetFragmentColorsFromCallback(
    bool bLazySet,
    ON_SHA1_Hash fragment_colors_settings_hash,
    ON_MappingTag fragment_colors_mapping_tag,
    ON__UINT_PTR callback_context,
    const ON_Color(*color_callback)(
      ON__UINT_PTR callback_context,
      const ON_MappingTag& mapping_tag,
      const ON_SubD& subd,
      ON_SubDComponentPtr cptr,
      const ON_3dPoint& P,
      const ON_3dVector& N,
      const ON_3dPoint& T,
      const ON_SurfaceCurvature& K
      )
    ) const;


  /// <summary>
  /// Determing if this SubD's mesh fragments have per vertex color settings.
  /// </summary>
  /// <returns>
  /// If this SubD has mesh fragments with per vertex colors, then true is returned.
  /// Otherwise false is returned.
  /// </returns>
  bool HasFragmentColors() const;

  /// <param name="color_mapping_tag">
  /// This tag identifies the method and computation used to set the
  /// per vertex colors on the fragments. The tag is persistent so
  /// that the colors can be recomputed from the id in situations where
  /// fragments need to be recalculated.
  /// </param>
  /// <returns>
  /// If this SubD has mesh fragments with per vertex colors and 
  /// color_tag = FragmentColorsMappingTag(), then true is returned.
  /// Otherwise false is returned.
  /// </returns>
  bool HasFragmentColors(
    ON_MappingTag color_mapping_tag
  ) const;

  /// <param name="color_settings_hash">
  /// This hash uniquely identifies the method and computation used to
  /// set the per vertex colors on the fragments. The has is a runtime
  /// value that has meaning only when fragments with per vertex colors
  /// exist.
  /// </param>
  /// <returns>
  /// If this SubD has mesh fragments with per vertex colors and 
  /// color_settings_hash = FragmentColorsSettingsHash(), then true is returned.
  /// Otherwise false is returned.
  /// </returns>
  bool HasFragmentColors(
    ON_SHA1_Hash color_settings_hash
  ) const;

  /// <param name="color_settings_hash">
  /// This hash uniquely identifies the method and computation used to
  /// set the per vertex colors on the fragments. The has is a runtime
  /// value that has meaning only when fragments with per vertex colors
  /// exist.
  /// </param>
  /// <param name="color_mapping_tag">
  /// This tag identifies the method and computation used to set the
  /// per vertex colors on the fragments. The tag is persistent so
  /// that the colors can be recomputed from the id in situations where
  /// fragments need to be recalculated.
  /// </param>
  /// <returns>
  /// If this SubD has mesh fragments with per vertex colors and 
  /// color_settings_hash = FragmentColorsSettingsHash() and
  /// color_mapping_tag = ColorsMappingTag(), then true is returned.
  /// Otherwise false is returned.
  /// </returns>
  bool HasFragmentColors(
    ON_SHA1_Hash color_settings_hash,
    ON_MappingTag color_mapping_tag
  ) const;


  /*
  Description:
    Clear all fragment vertex colors
  Parameters:
    bClearFragmentColorsMappingTag - [in]
      When in doubt, pass true.
      If true, the mapping tag and hash associated with the fragment vertex colors are unset as well.
  */
  void ClearFragmentColors(
    bool bClearFragmentColorsMappingTag
  );


  /*
  Returns:
    This mapping tag ideitifies the color mapping used to set fragment per vertex colors.
  */
  const ON_MappingTag ColorsMappingTag() const;

  /*
  Description:
    Set the colors mapping tag.
  Remarks:
    Calling this->SetColorsMappingTag() does not change existing cached
    fragment vertex colors. At an appropriate time, call this->SetFragmentColorsFromCallback()
    to update fragment vertex colors on any cached fragments.

    The color mapping tag and per vertex colors are mutable properties.
    They can be changed by rendering applications as needed.
  */
  void SetColorsMappingTag(const class ON_MappingTag&) const;


  /*
    Returns:
      hash identifying the way the fragment vertex colors were set.
  */
  const ON_SHA1_Hash FragmentColorsSettingsHash() const;

  ON_DEPRECATED_MSG("Use ON_SubD::ColorsMappingTag()")
  const ON_MappingTag FragmentColorsMappingTag() const;

  ON_DEPRECATED_MSG("Use ON_SubD::SetColorsMappingTag()")
  void SetFragmentColorsMappingTag(const class ON_MappingTag&) const;

public:
  const class ON_SubDLevel& ActiveLevel() const;

  /// <summary>
  /// If a level exists, get it
  /// </summary>
  /// <param name="level_index"></param>
  /// <returns>
  /// If the specified level exists, it is returned.
  /// Otherwise ON_SubDLevel::Empty is returned.
  /// </returns>
  const class ON_SubDLevel& LevelForExperts(unsigned int level_index) const;

public:
  /*
  Description:
    Pretend this function and ON_SubDimple do not exist.
  Returns:
    Something that you are pretending does not exist.
  Remarks:
    It is intentional that the definition of ON_SubDimple class is not
    available in the opennurbs library interface (not in a header file).
    The size and design of ON_SubDimple will change constantly.
    If you choose to hack and whack so you can dereference an
    ON_SubDimple* pointer, then your code will crash unpredictably.
  */
  const class ON_SubDimple* SubDimple() const;
  unsigned int SubDimpleUseCount() const;

  void ShareDimple(const ON_SubD&);
  void SwapDimple(ON_SubD&);

  void ShareDimple(const class ON_SubDMeshImpl&);
  void SwapDimple(class ON_SubDMeshImpl& );

private:
  class ON_SubDimple* SubDimple(bool bCreateIfNeeded);
  class ON_SubDLevel const * ActiveLevelConstPointer() const;
  class ON_SubDLevel* ActiveLevelPointer();

  void CopyHelper(const ON_SubD&);

private:
  class ON_SubDHeap* Internal_Heap() const;

public:

    /*
    Returns:
      True if every face has a nonzero PackId and a set PackRect.
    */
    bool FacesArePacked() const;

    /*
    Description:
      Validates the face packing.
      
      If a face pack contains more than one face, then all of the following are required
      for that face pack to be valid.
      - Every face in the pack is a quad.
      - The quads form a rectangular grid.
      - All faces in the rectangular grid are quads.
      - All interior edges in the rectangular grid are smooth.
      - All interior vertices in the rectangular grid are smooth and have 4 edge and 4 faces.
      - All edges on the sides of the rectangular grid are either creases or are attached to
      exactly one face in the rectangular grid.
      
    Parameters:
      bPermitWrapping - [in]
        If true, then the face pack is allowed to wrap.
        For example, if bPermitWrapping is true, then a SubD cylinder that is a regular quad grid
        can have a single face pack.
      bIfValidThenUpdateFacePackingTopologyHash - [in]
        When in doubt, pass false to test if all of the current face packing information is
        completely valid.

        If you are using an add/remove creases edit approach to modify an initially valid packing,
        then pass true. Otherwise pass false.

        If this parameter is true, the packing is valid, and this->FacePackingSubDTopologyHash()
        does not match this->SubDTopologyHash(), then this->FacePackingSubDTopologyHash() is updated
        to the current value of this->SubDTopologyHash().

        If this parameter is false and and this->FacePackingSubDTopologyHash()
        does not match this->SubDTopologyHash(), then the function returns false.
    Returns:
      True if FacesArePacked() is true, the quad grids meet all the conditions described above,
      this->FacePackingId() is not nil, and either this->FacePackingSubDTopologyHash() is equal to
      this->SubDTopologyHash() or bIfValidThenUpdateFacePackingTopologyHash is true.
    */
    bool FacePackingIsValid(
      bool bIfValidThenUpdateFacePackingTopologyHash
    ) const;

private:
    /*
    Returns:
      True if all of the following are satisfied.
      1. All quads are packed into rectangular grids.
      2. The pack id is used in those grids is not used by any other face.
      3. The rectangular grids do not have interior creases.
      4. The rectangular grids have 4 boundaries (no wrapping).
      5. Non quads have pack ids that are zero or not shared with a quad.
    */
    bool QuadPackingIsValid() const;

public:

    /// <summary>
    /// The fast and simple face packing uses topology, vertex tags, and edge tags to 
    /// group quads into rectangular grids. It does not perform geometric feature analysis.
    /// {C3D8DD54-F8C8-4455-BB0E-2A2F4988EC81}
    /// </summary>
    static const ON_UUID FastAndSimpleFacePackingId;

    /// <summary>
    /// The quad sphere face packing is used by ON_SubD::CreateSubDQuadSphere.
    /// It divides the quad sphere into two similar sets (like a baseball cover) and assigns
    /// the bottom third of texture space to the first region and the top third to 
    /// the second region. The middle third is unmapped so that texture distortion is 
    /// uniform for each quad.
    /// {9C491E5C-2B46-48AA-BD43-7B18FDC52D58}
    /// </summary>
    static const ON_UUID QuadSphereFacePackingId;

    /// <summary>
    /// The globe sphere face packing is used by ON_SubD::CreateSubDGlobeSphere.
    /// The equatorial band of quads is assigned a central horizontal strip of 
    /// texture space while the polar triangle fans are assigned horizontal strips
    /// from the bottom and top of texture space. 
    /// The heights of the horizontal strips of texture space are chosen to minimize
    /// distortion as latitude varies.
    /// {63CA2FC1-8F6C-4EFC-9A07-C6A26A8C93FB}
    /// </summary>
    static const ON_UUID GlobeSphereFacePackingId;


    /// <summary>
    /// The custom face packing is typically used when a subd creation 
    /// function sets a custom face packing different from the default.
    /// Typically this happens when there are quad packs that align
    /// well with the overall geometry or to reduce texture distortion.
    /// It is used to indicate the built-in automatic face packing
    /// was not applied.
    /// {91FD7018-8BBE-4492-8D2E-E8761C505ACF}
    /// </summary>
    static const ON_UUID CustomFacePackingId;

    // ADD NEW PackFaces ids above this comment and below FastAndSimplePackFacesId.


    /// <summary>
    /// ON_SubD::DefaultFacePackingId identifies the default face packing.
    /// Code that wants to use the built-in face packing that is currently
    /// the best option for general use, will specify ON_SubD::DefaultFacePackingId.
    /// 
    /// Currently this id is ON_SubD::FastAndSimpleFacePackingId. 
    /// In the future it may be changed to another id. Code that wants to
    /// always apply the same face packing will explicitly specify one of
    /// the built-in face pack ids defined above.
    /// </summary>
    static const ON_UUID DefaultFacePackingId;

    static bool IsBuiltInFacePackingId(
      ON_UUID candidate_id
    );

    /*
    Returns:
      An id that identifies the algorithm used to pack the faces in this subd.
    */
    const ON_UUID FacePackingId() const;

    /*
    Returns:
      The value of ON_SubDHash::Create(ON_SubDHashType::TopologyAndEdgeCrease, *this) when the faces were packed.
    */
    const ON_SubDHash FacePackingTopologyHash() const;

    /*
    Description:
      Sets the FacePackingTopologyHash() property to Empty.
      Experts may need to do this when modifying a face packing.
      After calling ClearFacePackingTopologyHashForExperts(), call
      FacePackingIsValid(true) to make sure the modified packing was
      actually valid and update the FacePackingTopologyHash().
    */
    void ClearFacePackingTopologyHashForExperts() const;

    /*
    Description:
      When a custom algorithm that is not built into ON_SubD is used to pack the
      faces, this function must be called with an id that uniquely identifies the
      custom algorithm. The present SubD geometry will be used to set the value
      of FacePackingTopologyHash().
    Returns:
      True if faces are properly packed and custom_packing_id is not nil and unique.
      Otherwise the packing is reset to the default and false is returned.
    */
    bool SetFacePackingIdForExperts(
      ON_UUID custom_packing_id
    );

    /*
    Description:
      Clear all face pack ids and related information.
    */
    void ClearFacePackIds();



private:
  friend class ON_SubDRef;
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 ) 
  // C4251: ... needs to have dll-interface to be used by clients of class ...
  // m_subdimple_sp is private and all code that manages m_subdimple_sp is explicitly implemented in the DLL.
private:
  std::shared_ptr<class ON_SubDimple> m_subdimple_sp;
#pragma ON_PRAGMA_WARNING_POP

public:
  // The ON_SubD code increments ON_SubD::ErrorCount every time something
  // unexpected happens. This is useful for debugging.
  static unsigned int ErrorCount;
}; 

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDRef
//
class ON_CLASS ON_SubDRef
{
public:
  static const ON_SubDRef Empty;

  ON_SubDRef() ON_NOEXCEPT;
  ~ON_SubDRef();
  ON_SubDRef(const ON_SubDRef& src) ON_NOEXCEPT;
  ON_SubDRef& operator=(const ON_SubDRef& src);

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_SubDRef( ON_SubDRef&& ) ON_NOEXCEPT;
  // rvalue assignment operator
  ON_SubDRef& operator=( ON_SubDRef&& );
#endif

  const class ON_SubD& SubD() const;

  /*
  Returns:
    Number of references to the managed ON_SubD, including the one by this ON_SubDRef.
  */
  unsigned int ReferenceCount() const;

  /*
  Description:
    Allocates a new empty ON_SubD and has this ON_SubDRef reference it.
  */
  class ON_SubD& NewSubD();

  /*
  Description:
    Allocates a new ON_SubD and has this ON_SubDRef reference it.
  Parameters:
    src - [in]
      The new ON_SubD managed by this ON_SubDRef will be a copy of src.SubD().
  Returns:
    A reference to the new ON_SubD managed by this ON_SubDRef.
  */
  class ON_SubD& CopySubD(
    const ON_SubDRef& src
    );

  /*
  Description:
    Allocates a new ON_SubD and has this ON_SubDRef reference it.
  Parameters:
    src - [in]
      The new ON_SubD managed by this ON_SubDRef will be a copy of src.
  Returns:
    A reference to the new ON_SubD managed by this ON_SubDRef.
  */
  class ON_SubD& CopySubD(
    const ON_SubD& src
    );

  /*
  Description:
    If ReferenceCount() > 1, then have this ON_SubDRef reference a 
    new copy. Otherwise do nothing. The result being that this will
    be the unique reference to the ON_SubD managed by this ON_SubDRef.
  Returns:
    A reference to the ON_SubD uniquely managed by this ON_SubDRef.
  */
  class ON_SubD& UniqueSubD();
  
  /*
  Description:
    Remove this reference to the managed ON_SubD. 
    If this is the last reference, then the managed ON_SubD is deleted.
  */
  void Clear();

public:
  class ON_SubDVertexIterator VertexIterator() const;
  class ON_SubDEdgeIterator EdgeIterator() const;
  class ON_SubDFaceIterator FaceIterator() const;

  /*
  Description:
    Expert user function to have this ON_SubDRef manage the lifetime of subd.
  Parameters:
    subd - [in/out]
      subd must point to an ON_SubD that was constructed on the heap using
      an operator new call with a public ON_SubD constructor.
  Returns:
    a pointer to the managed subd or nullptr subd if not valid.
  Example:
    ON_SubD* subd = new ON_SubD(...);
    ON_SubDRef subr;
    ON_SubD* managed_subd = subdr.SetSubD(subd);
    // subd = nullptr
    // managed_subd = pointer you can use
  */
  class ON_SubD* SetSubDForExperts(
    class ON_SubD*& subd
    );

  /*
  Description:
    Expert user function to have this ON_SubDRef reference the
    contents of an existing ON_SubD.
    Do not use if user data on the referenced subd needs to be accessed.
  Parameters:
    subd - [in]
      Any subd on the heap or the stack.
  Returns:
    true if successful.
  */
  static ON_SubDRef CreateReferenceForExperts(
    const ON_SubD& subd
    );

private:
 /*
  Description:
    Expert user function to have this ON_SubDRef reference the
    contents of an existing ON_SubD.
    Do not use if user data on the referenced subd needs to be accessed.
  Parameters:
    subd - [in]
      Any subd on the heap or the stack.
  */
  ON_SubDRef(
    const class ON_SubD& subd 
    );
  
private:
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 ) 
  // C4251: ... needs to have dll-interface to be used by clients of class ...
  // m_subd_sp is private and all code that manages m_subd_sp is explicitly implemented in the DLL.
private:
  std::shared_ptr<class ON_SubD> m_subd_sp;
#pragma ON_PRAGMA_WARNING_POP
};


#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_SubDComponentAndNumber>;
#endif


//////////////////////////////////////////////////////////////////////////
//
// ON_SubDComponentList
//
class ON_CLASS ON_SubDComponentList
{
public:
  ON_SubDComponentList() = default;
  ~ON_SubDComponentList() = default;
  ON_SubDComponentList(const ON_SubDComponentList&);
  ON_SubDComponentList& operator=(const ON_SubDComponentList&);

public:
  static const ON_SubDComponentList Empty;

public:
  unsigned CreateFromMarkedComponents(const ON_SubD& subd, bool bComponentInListMark);
  unsigned CreateFromMarkedVertices(const ON_SubD& subd, bool bVertexInListMark);
  unsigned CreateFromMarkedEdges(const ON_SubD& subd, bool bEdgeInListMark);
  unsigned CreateFromMarkedFaces(const ON_SubD& subd, bool bFaceInListMark);

  unsigned CreateFromComponentList(const ON_SubD& subd, const ON_SimpleArray<ON_COMPONENT_INDEX>& component_list);
  unsigned CreateFromComponentList(const ON_SubD& subd, const ON_SimpleArray<ON_SubDComponentPtr>& component_list);

  unsigned CreateFromVertexIdList(const ON_SubD& subd, const ON_SimpleArray<unsigned>& free_vertex_ids);
  unsigned CreateFromVertexList(const ON_SubD& subd, const ON_SimpleArray<ON_SubDVertexPtr>& free_vertices);
  unsigned CreateFromVertexList(const ON_SubD& subd, const ON_SimpleArray<const ON_SubDVertex*>& free_vertices);

  void Destroy();

  /*
  Returns:
    Number of removed components.
  */
  unsigned int RemoveAllComponents();

  /*
  Returns:
    Number of removed components.
  */
  unsigned int RemoveAllVertices();

  /*
  Returns:
    Number of removed components.
  */
  unsigned int RemoveAllEdges();

  /*
  Returns:
    Number of removed components.
  */
  unsigned int RemoveAllFaces();

  /*
  Returns:
    SubD runtime serial number.
  */
  ON__UINT64 SubDRuntimeSerialNumber() const;

  /*
  Returns:
    SubD content serial number when this list was created or the last
    time UpdateContentSerialNumbers() was run.
  */
  ON__UINT64 SubDGeometryContentSerialNumber() const;

  /*
  Returns:
    SubD content serial number when this list was created or the last
    time UpdateContentSerialNumbers() was run.
  */
  ON__UINT64 SubDRenderContentSerialNumber() const;

  unsigned int Count() const;

  /*
  operator[] returns ON_SubDComponentPtr::Null when index is out of bounds.
  */
  const ON_SubDComponentPtr operator[](int) const;
  const ON_SubDComponentPtr operator[](unsigned int) const;
  const ON_SubDComponentPtr operator[](ON__INT64) const;
  const ON_SubDComponentPtr operator[](ON__UINT64) const;
#if defined(ON_RUNTIME_APPLE)
  const ON_SubDComponentPtr operator[](size_t) const;
#endif

  const ON_SimpleArray< ON_SubDComponentPtr >& ComponentList() const;

  const ON_SubD& SubD() const;

  /*
  Description:
    Update the saved subd geometry and render content serial number to the current values 
    of SubD().GeometryContentSerialNumber() and SubD().RenderContentSerialNumber().
  */
  void UpdateContentSerialNumbers();

  /*
  Description:
    Change the component list to reference components in a different subd.
  Parameters:
    new_subd - [in]
      subd to replace current referenced subd
    bUpdateDeletedComponents - [in]
      false: current components that are deleted will be ignored.
      true: if the corresponding component in new_sub is not deleted, it
      will be added to the list.
  Returns:
    Number of components in list after updating.
  */
  unsigned int UpdateSubDForExperts(const ON_SubD& subd, bool bUpdateDeletedComponents);


private:
  unsigned Internal_Create(
    const ON_SubD& subd,
    bool bAddVertices,
    bool bAddEdges,
    bool bAddFaces,
    bool bComponentInListMark,
    unsigned marked_component_count
  );

  unsigned Internal_RemoveComponents(
    bool bRemoveVertices,
    bool bRemoveEdges,
    bool bRemoveFaces
  );

private:
  ON__UINT64 m_subd_runtime_serial_number = 0;
  ON__UINT64 m_subd_geometry_content_serial_number = 0;
  ON__UINT64 m_subd_render_content_serial_number = 0;

  unsigned m_subd_vertex_count = 0;
  unsigned m_subd_edge_count = 0;
  unsigned m_subd_face_count = 0;
  unsigned m_reserved = 0;

private:
  ON_SubD m_subd; // keeps subd dimple in scope while m_component_list[] is active
  ON_SimpleArray< ON_SubDComponentPtr > m_component_list;
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDComponentMarksClearAndRestore
//
class ON_SubDComponentMarksClearAndRestore
{
public:
  // Constructor saves current component RuntimeMark() settings and then clears them.
  ON_SubDComponentMarksClearAndRestore(
    const ON_SubD& subd
  );

  // Destructor restores saved marks.
  ~ON_SubDComponentMarksClearAndRestore();

  /*
  Description:
    Restore marks saved by the constructor.
  Parameters:
    bDisableFutureRestores - [in]
      If true, no additional restores, including by the destructor, will occur.
  */
  bool Restore(
    bool bDisableFutureRestores
  );

  // Call DisableRestore() to prevent the destructor from restoring saved marks.
  void DisableRestore();

  const ON_SimpleArray< const class ON_SubDComponentBase* >& ComponentList() const;

private:
  ON_SubD m_subd;

  ON_SimpleArray< const class ON_SubDComponentBase* > m_component_list;

  bool m_bRestore = true;
  unsigned char m_reserved1 = 0;
  unsigned char m_reserved2 = 0;
  unsigned char m_reserved3 = 0;
  unsigned int m_reserved4 = 0;

private:
  ON_SubDComponentMarksClearAndRestore(const ON_SubDComponentMarksClearAndRestore&) = delete;
  ON_SubDComponentMarksClearAndRestore& operator=(const ON_SubDComponentMarksClearAndRestore&) = delete;
};


//////////////////////////////////////////////////////////////////////////
//
// ON_SubDSectorType
//
class ON_CLASS ON_SubDSectorType
{
public:
  ON_SubDSectorType() = default;
  ON_SubDSectorType(const ON_SubDSectorType&) = default;
  ON_SubDSectorType& operator=(const ON_SubDSectorType&) = default;

  static const ON_SubDSectorType Empty;

  bool IsValid() const;

  unsigned int SectorTypeHash() const;

  static int Compare(const ON_SubDSectorType*, const ON_SubDSectorType*);


  /////////////////////////////////////////////////////////////////////////////////////
  //
  // Sector Coefficients
  //
  /////////////////////////////////////////////////////////////////////////////////////
  //
  //   In the comment below, 
  //   F = number of faces in the sector,
  //   E = number of edges in the sector.
  //
  //   There are five valid sector configurations of edges and faces. In all
  //   configurations, the edges have one end at the center vertex and the
  //   faces have one corner at the center vertex.
  //
  //   SMOOTH
  //     1) The center vertex is smooth.
  //     2) F >= 2
  //     3) E = F
  //     4) Every edge is smooth.
  //     5) Every edge is an edge of two different faces in the sector.
  //
  //   DART
  //     1) The center vertex is a dart.
  //     2) F >= 2
  //     3) E = F
  //     4) One edge is a crease.
  //     5) The crease edge is an edge of two geometrically adjacent sector faces.
  //
  //   DART* (The same as "DART", but the crease edge has been duplicated.)
  //     1) The center vertex is a dart.
  //     2) F >= 2
  //     3) E = F+1
  //     4) Two edges are creases that have the same end locations.
  //     5) Each crease edge is an edge of a single face in the sector,
  //        these faces are different and are geometrically adjacent.
  //
  //   BOUNDED
  //     1) The center vertex is a crease or corner vertex.
  //     2) F >= 2
  //     3) E = F+1
  //     4) Two edges are crease edges that have different vertices at their ends.
  //     5) Each crease edge is an edge of a single face in the sector,
  //        these faces are different and not geometrically adjacent.
  //
  //   BOUNDED*
  //     1) The center vertex is a crease or corner vertex.
  //     2) F = 1
  //     3) E = 2
  //     4) The edges are crease edges that have different vertices at their ends.
  //     5) The edges a edges of the face.
  //
  /////////////////////////////////////////////////////////////////////////////////////
  //
  //   The sector coefficient is used when subdividing smooth edges in sectors
  //   with a DART, DART* or BOUNDED configuration. In these cases the 
  //   sector coefficient is a value strictly between 0.0 and 1.0 that depends on
  //     1) the center vertex tag (crease, corner or dart), 
  //     2) the value of F,
  //     3) and when the center vertex is a corner, the angle between 
  //        the boundary edges.  
  //
  //   The sector coefficient is ignored when dividing smooth edges in SMOOTH sectors.
  //   The sector coefficient is ignored when subdividing crease edges.
  //
  //   For a smooth edge in a sector with a DART, DART* or BOUNDED configuration,
  //   with w = sector coefficient, C = location of the center vertex
  //   and P = location of the smooth vertex at the other end
  //   of the smooth edge, the point
  //   
  //     Q = 3/4 * (w*C + (1-w)*P) 
  //
  //   is the contribution of C and P to the edge's subdivision point.
  //   
  //   When a smooth edge has smooth vertices at both ends located
  //   at A and B, the contribution of A and B to the edge's subdivision
  //   point is 
  //
  //     Q = 3/8 * (A + B) = 3/4 * (1/2*A + 1/2*B)
  //
  //   A crease edge's subdivision point is always the edge's midpoint.
  /*
  Description:
    Calculates sector coefficient value for the sector type
    identified by this ON_SubDSectorType.
    The sector coefficient is a property of a smooth edge end
    that is attached to a dart, crease, or corner vertex.
    In all other cases the sector coefficient is ignored.
    The value of the sector coefficient is constant throughout subdivision.
    Every smooth edge in a sector has the same sector coefficient at the central vertex.
  Returns:
    w: 0.0 < w < 1.0
      w = sector coefficient value.
    ON_SubDSectorType::IgnoredCornerSectorAngle  (= 0.0)
      This value is used to set sector angles when the actual value is not needed.
    ON_SubDSectorType::ErrorSectorCoefficient
      This ON_SubDSectorType is not valid and the calculation failed.
  */
  double SectorCoefficient() const;


  unsigned int FacetEdgeCount() const;

  ON_SubDVertexTag VertexTag() const;

  /// <returns>Number of edges attached to the center vertex.</returns>
  unsigned int EdgeCount() const;

  /// <returns>Number of faces in the sector.</returns>
  unsigned int FaceCount() const;

  /*
  Returns:
   Number of points in the point ring.  
   (1 + FaceCount() + EdgeCount()).
  */
  unsigned int PointRingCount() const;

  /*
  Returns:
   1 + FaceCount() + EdgeCount()
  */
  unsigned int ComponentRingCount() const;

  /*
  Returns:
    If the sector vertex tag is ON_SubDVertexTag::Corner,
    the angle between the corner crease boundary edges is
    returned.  
    Otherwise, ON_SubDSectorType::ErrorCornerSectorAngle is returned.
  */
  double CornerSectorAngleRadians() const;

  /*
  Returns:
    a value >= 0 and <= ON_SubDSectorType::MaximumCornerAngleIndex
  */
  unsigned int CornerSectorAngleIndex() const;

  /*
  Description:
    An angle index value of ON_SubDSectorType::MaximumCornerAngleIndex indicates
    the angle is 2pi radians.
  */
  enum : unsigned int
  {
    MaximumCornerAngleIndex = 72
  };

  // ON_SubDSectorType::MinimumCornerAngleRadians = (2.0*ON_PI)/((double)(ON_SubDSectorType::MaximumCornerAngleIndex));
  static const double MinimumCornerAngleRadians;

  // ON_SubDSectorType::MaximumCornerAngleRadians = 2.0*ON_PI - ON_SubDSectorType::MinimumCornerAngleRadians;
  static const double MaximumCornerAngleRadians;

  /*
  Parameters:
    angle_radians - [in] (0.0 <= angle_radians <= 2*ON_PI)
      The angle between the bounding crease edges
  Returns:
    If angle_radians is valid input, then the value angle_index is returned.
    The value angle_index is selected so that
    (0 < angle_index < ON_SubDSectorType::MaximumCornerSectorIndex) and
    fabs(angle_index*angle_quantum - angle_radians) is as small as possible, where
    angle_quantum =  (2.0*ON_PI)/ON_SubDSectorType::MaximumCornerSectorIndex.
    Otherwise ON_UNSET_UINT_INDEX is returned.
  */
  static unsigned int CornerAngleIndexFromCornerAngleRadians(
    double angle_radians
    );

  /*
  Convert and angle index into radians
  Parameters:
    corner_angle_index - [in]
      0 to ON_SubDSectorType::MaximumCornerAngleIndex.
  Returns:
    If angle_index is valid, the corresponding angle in radians is returned.
      = (angle_index / ((double)ON_SubDSectorType::MaximumCornerAngleIndex)) * ON_2PI
    Otherwise ON_UNSET_VALUE is returned.
  */
  static double AngleRadiansFromCornerAngleIndex(
    unsigned int corner_angle_index
    );

  /*
  Returns:
    True if this is a smooth interior vertex sector
  */
  bool IsSmoothSector() const;


  /*
  Returns:
    True if this is a dart interior vertex sector
  */
  bool IsDartSector() const;


  /*
  Returns:
    True if this is a crease vertex sector
  */
  bool IsCreaseSector() const;

  /*
  Returns:
    True if this is a corner vertex sector
  */
  bool IsCornerSector() const;

  /*
  Returns:
    True if this is a convex corner vertex sector (sector angle <= pi)
  */
  bool IsConvexCornerSector() const;

  /*
  Returns:
    True if this is a concave corner vertex sector (sector angle > pi)
  */
  bool IsConcaveCornerSector() const;

  /*
  Parameters:
    sector_boundary_edge0_ptr - [in]
    sector_boundary_edge1_ptr - [in]
      Crease edges that bound the sector containing the smooth edge.
      The edge direction must identify the corner vertex.
      corner vertex = sector_boundary_edge0_ptr.RelativeVertex(0) = sector_boundary_edge1_ptr.RelativeVertex(0)
  Returns:
    tagged end angle for a smooth edge that
    1) ends at a vertex tagged on ON_SubDVertexTag::Corner
    2) has two adjacent faces.
    3) lies in a sector bounded by 2 distinct crease edges.
    The angle is convex and positive: 0 < angle <= Pi
  */
  static double CornerSectorAngleRadiansFromEdges(
    ON_SubDEdgePtr sector_boundary_edge0_ptr,
    ON_SubDEdgePtr sector_boundary_edge1_ptr
    );

  static bool IsValidCornerSectorAngleRadians(
    double corner_sector_angle_radians
    );

  static double ClampCornerSectorAngleRadians(
    double corner_sector_angle_radians
    );

  /*
  Returns:
    Number of subdivision points in a sector ring
    facet_type vertex_tag ring count
    tri        smooth     N+1
    tri        crease     N+2
    quad       smooth     2N+1
    quad       crease     2N+2
    (2 * valence + 1) for quad subds
    (valence + 1) for tri subds
  */
  static unsigned int SectorPointRingCountFromEdgeCount(
    ON_SubDVertexTag vertex_tag,
    unsigned int sector_edge_count
    );

  static unsigned int SectorPointRingCountFromFaceCount(
    ON_SubDVertexTag vertex_tag,
    unsigned int sector_face_count
    );

  static unsigned int SectorFaceCountFromEdgeCount(
    ON_SubDVertexTag vertex_tag,
    unsigned int sector_edge_count
    );

  static unsigned int SectorEdgeCountFromFaceCount(
    ON_SubDVertexTag vertex_tag,
    unsigned int sector_face_count
    );
  
  static unsigned int MinimumSectorEdgeCount(
    ON_SubDVertexTag vertex_tag
    );
  
  static unsigned int MinimumSectorFaceCount(
    ON_SubDVertexTag vertex_tag
    );

public:
  /*
  Description:
    The sector coefficient is a property of a smooth edge end
    that is attached to a dart, crease, or corner vertex.
    In all other cases the sector coefficient is ignored.
    The value of the sector coefficient is constant throughout subdivision.
    Every smooth edge in a sector has the same sector coefficient at the central vertex.
  Returns:
    ON_SubDSectorType::IgnoredSectorCoefficient
  */
  static double SmoothSectorCoefficient();
  
  /*
  Parameters:
  face_type - [in]
  sector_face_count - [in]
    number of faces in the smooth sector.
  Returns:
    0: 
      failed to calculate coefficient
    ON_SubDSectorType::UnsetSectorCoefficient:
      This typically happens when a SubD control net is being 
      created and a facet type is not specified.  
      The coefficients will be calculated at the first subdivision.
    0 < w < 1:
      1/2 + 1/3*cos(tagged end sector angle / number of faces) for quadrangle facets
  Remarks:
    This is a useful tool when calling AddEdge while a subdivision
    level is being constructed.
  */
  static double CreaseSectorCoefficient(
    unsigned int sector_face_count
    );

  static double DartSectorCoefficient(
    unsigned int sector_face_count
    );

  static double CornerSectorCoefficient(
    unsigned int sector_face_count,
    double corner_sector_angle_radians
    );

  /// <summary>
  /// Copy the sector coefficient that is currently set on the edge.
  /// The sector coefficient is a property of a smooth edge end
  /// that is attached to a dart, crease, or corner vertex.
  /// In all other cases the sector coefficient is ignored.
  /// The value of the sector coefficient is constant throughout subdivision
  /// and this function is used to copy edge sector coefficients during subdivision. 
  /// Every smooth edge in a sector has the same sector coefficient at the central vertex.
  /// </summary>
  /// <param name="edge"></param>
  /// <param name="vertex">
  /// The vertex identifies which end of the edge to query.
  /// </param>
  /// <returns>
  /// If the edge and vertex are not nullptr and attached to each other, 
  /// edge->IsSmooth() is true,
  /// and vertex->IsDartCreaseOrCorner() is true, 
  /// then the current value of edge->m_sector_coefficient[vertex index] is returned.
  /// If the edge and vertex are not nullptr and attached to each other
  /// and edge->IsCrease() is true or vertex->IsSmooth() is true, 
  /// then ON_SubDSectorType::IgnoredSectorCoefficient is returned.
  /// In all other cases error_return_value is returned.
  /// </returns>
  static double CopyEdgeSectorCoefficient(
    const class ON_SubDEdge* edge,
    const class ON_SubDVertex* vertex,
    double error_return_value
  );

  // This value is is used to set sector angles when the
  // actual value is not needed. This occurs at both ends
  // of a creased edge and when the end of a smooth edge
  // is a smooth vertex.
  static const double IgnoredCornerSectorAngle; // = 0.0;

  // This value is used to set sector coefficients that could not be
  // correctly set because something in the calculation failed.  
  // It is typically used when an invalid component in SubD object
  // was needed to calculate the coefficient.
  static const double UnsetCornerSectorAngle; // = -8881.0;

  // This value is indicate a corner sector angle calculation failed.
  static const double ErrorCornerSectorAngle; // = -9991.0;


  // This value is used for smooth sector thetas
  static const double SmoothSectorTheta; // = 0.5*ON_PI

  // This value is used to indicate a sector theta needs to be set
  static const double UnsetSectorTheta; // = -8882.0;

  // This value is used to indicate a sector theta calculation failed.
  static const double ErrorSectorTheta; // = -9992.0;


  // This value is is used to set edge sector coefficients when the
  // actual value is not needed. This occurs at both ends
  // of a creased edge and when the end of a smooth edge
  // is a smooth vertex.
  static const double IgnoredSectorCoefficient; // = 0.0;

  // This value is used to mark edge sector coefficients that need to be
  // set in the future when more information is available.
  // It is typically used when creating a subD control net
  // and the facet type is not known. Any value < 0.0 and not
  // equal to ON_UNSET_VALUE would work. The fact that the actual
  // value is -999.0 has no other significance.
  static const double UnsetSectorCoefficient; // = -8883.0;

  // This value indicates an edge sector coefficient calculation failed.
  static const double ErrorSectorCoefficient; // = -9993.0;

  static bool IsValidSectorCoefficientValue(
    double coefficient_value,
    bool bAllowUnsetTaggedEndCoefficient
    );

  /*
  Returns:
    ON_SubDSectorType::ErrorSectorCoefficient and calls debug breakpoint
  */
  static double SectorCoefficientCalculationError();

  
  /*
  Description:
    Create a ON_SubDSectorType from a ON_SubDSectorIterator.
  Parameters:
    subd_type - [in]
    vertex_tag - [in]
    sector_face_count - [in]
      Number of faces in the sector.
    corner_sector_angle_radians - [in]
      If vertex_tag is ON_SubDVertexTag::Corner, this
      parameter is the angle between the crease edges
      that bound the corner.  
      If vertex_tag is not  ON_SubDVertexTag::Corner,
      this parameter is ignored.
  Returns:
    An ON_SubDSectorType for the case the input parameters 
    identify.
  */
  static ON_SubDSectorType Create(
    ON_SubDVertexTag vertex_tag,
    unsigned int sector_face_count,
    double corner_sector_angle_radians
    );


  /*
  Description:
    Create a ON_SubDSectorType from a ON_SubDSectorIterator.
  Parameters:
    subd_type - [in]
    sit - [in]
  Returns:
    An ON_SubDSectorType for the sector identified by sit.
  */
  static ON_SubDSectorType Create(
    const ON_SubDSectorIterator& sit
    );

  /*
  Description:
    Create a ON_SubDSectorType for the sector containing the face.
  Parameters:
    subd_type - [in]
    face - [in]
    face_vertex_index - [in]
      face->Vertex(face_vertex_index) will be the sector's
      center vertex.
  Returns:
    An ON_SubDSectorType for the sector containing the face.
  */
  static ON_SubDSectorType Create(
    const class ON_SubDFace* face,
    unsigned int face_vertex_index
    );
  
  static ON_SubDSectorType Create(
    const class ON_SubDFace* face,
    const class ON_SubDVertex* vertex
    );
  
  /*
  Description:
    Create a ON_SubDSectorType for the sector containing the edge.
  Parameters:
    subd_type - [in]
    edge - [in]
    edge_vertex_index - [in]
      edge->Vertex(edge_vertex_index) will be the sector's
      center vertex.
  Returns:
    An ON_SubDSectorType for the sector containing the edge.
  */
  static ON_SubDSectorType Create(
    const class ON_SubDEdge* edge,
    unsigned int edge_vertex_index
    );

  /*
  Description:
    Create a smooth ON_SubDSectorType.
  Parameters:
    subd_type - [in]
    sector_face_count - [in]
      Number of faces in the sector.
  Returns:
    An ON_SubDSectorType for the smooth sector case specified
    by the input parameters.
  */
  static ON_SubDSectorType CreateSmoothSectorType(
    unsigned int sector_face_count
    );

  /*
  Description:
    Create a crease ON_SubDSectorType.
  Parameters:
    subd_type - [in]
    sector_face_count - [in]
      Number of faces in the sector.
  Returns:
    An ON_SubDSectorType for the crease sector case specified
    by the input parameters.
  */
  static ON_SubDSectorType CreateCreaseSectorType(
    unsigned int sector_face_count
    );

  /*
  Description:
    Create a dart ON_SubDSectorType.
  Parameters:
    subd_type - [in]
    sector_face_count - [in]
      Number of faces in the sector.
  Returns:
    An ON_SubDSectorType for the dart sector case specified
    by the input parameters.
  */
  static ON_SubDSectorType CreateDartSectorType(
    unsigned int sector_face_count
    );

  /*
  Description:
    Create a corner ON_SubDSectorType.
  Parameters:
    subd_type - [in]
    sector_face_count - [in]
      Number of faces in the sector.
    corner_sector_angle_radians - [in]
      The angle between the crease edges that bound the corner.  
  Returns:
    An ON_SubDSectorType for the corner sector case specified
    by the input parameters.
  */
  static ON_SubDSectorType CreateCornerSectorType(
    unsigned int sector_face_count,
    double sector_corner_angle_radians
    );

  static int Compare(
    const ON_SubDSectorType& a,
    const ON_SubDSectorType& b
    );


  /*
  Description:
    Get the subdivision matrix for the default subdivison algorithms 
    used by ON_SubD.

    The matrix coefficients are ordered so that the matrix acts on
    the left of the points returned by ON_SubDSectorIterator::GetVertexRing().

    For an interior vertex (smooth or dart), the coefficients are ordered
    so that one iteration of subdivision is given by:
    S*Transpose(V, E[0], F[0], E[1], F[1], ..., E[N-1], F[N-1]).
    For a dart vertex, E[0] is the point at the end of the creased edge.


    For a boundary vertex (crease or corner), the coefficients are ordered
    so that one iteration of subdivision is given by:
    S*Transpose(V, E[0], F[0], E[1], F[1], ..., F[N-2], E[N-1]).

    N = edge valence = number of edges in the sector.
    E[i] = end of i-th edge radiating from V.
    F[i] = point on the quad that is opposite V.
    The edges and faces are ordered radially so that the face for F[i]
    lies between the edges for E[i] and E[(i+1)%N].

  Parameters:
    S - [out]
      subdivision matrix
      Matrix coefficient (i,j) = S[i][j]
      0 <= i < R, 0 <= j < R, R = ON_SubDSectorType.PointRingCount()
    matrix_capacity - [in]
      S[] can store any RxR matrix with R <= matrix_capacity.

  Returns:
    R > 0: 
      R = PointRingCount() and S is the RxR subdivision matrix for the sector type.
    0: Invalid input
  */
  unsigned int GetSubdivisionMatrix(
    double** S,
    size_t matrix_capacity
    ) const;

  /*
  Parameters:
    S - [out]
      subdivision matrix. 
      Matrix coefficient (i,j) = S[i*R + j],
      0 <= i < R, 0 <= j < R, R = ON_SubDSectorType.PointRingCount()
    S_capacity - [in]
      Number of elements in S[] array
  Returns:
     0: Invalid input.
    >0: Number of rows and columns in S.
        This number is always ON_SubDSectorType.PointRingCount().
  */
  unsigned int GetSubdivisionMatrix(
    double* S,
    size_t S_capacity
    ) const;

  /*
  Description:
    All the subdivision matrices for the ON_SubD built-in
    subdivision algorithms have eigenvalues (1, lambda1, lambda2, e4, ..., eR),
    where 1 > lambda1 >= lambda2 > |e4| >= ... >= |eR| > 0.

    The subdominant eigenvalue is lambda1 and, 
    with one exception, lambda1 = lambda2.
    The exception is described in the description of 
    ON_SubDSectorType::SubdominantEigenvalueMulitiplicity().

  Returns:
    > 0.0: 
      The subdominant eigenvalue for the subdivision matrix.

    ON_UNSET_VALUE:
      This ON_SubDSectorType is not valid.
  */
  double SubdominantEigenvalue() const;

  /*
  Returns:
    0:
      The sector type is not set.

    2: 
      The subdominant eigenvalue has algebraic and geometric multiplicity = 2.
      This is the most common case.

    1: 
      The subdominant eigenvalue has algebraic and geometric multiplicity = 1.
      This occurs in Catmull-Clark subdivision at a crease vertex with 
      two crease edges and a single face.  The subdivision matrix for this
      case is
        S is a 4 x 4 matrix with rows =
           (3/4, 1/8, 0, 1/8), 
           (1/2, 1/2, 0, 0),
           (1/4, 1/4, 1/4, 1/4), 
           (1/2, 0, 0, 1/2).
        S has 4 real eigenvalues = (1, 1/2, 1/4, 1/4), all with
        geometric multiplicity = 1.
        The three eigenvectors are
           (1, 1, 1, 1), (0, -1, 0, 1), (0, 0, 1, 0).
  */
  unsigned int SubdominantEigenvalueMulitiplicity() const;

  /*
  Description:
    With one exception, which is described below,
    all the subdivision matrices for the ON_SubD built-in
    subdivision algorithms have eigenvalues (1, lambda, lambda, e4, ..., eR),
    where lambda is real, 1 > lambda > |e4| >= ... >= |eR| > 0, and the
    geometric dimension of the lambda eigenspace is 2 (there are two
    linearly independent lambda eigenvectors). 

    The subdominant eigenvalue is lambda.  This function returns an
    orthogonal basis, (E1, E2), for the subdominant eigenspace.

    An eigenvector for the dominant eigen value 1 has is (1,1,...,1).
    The domainant eignevector is orthogonal to the subdominant eigenspace.
    
    Put another way,
    0 = E1[0] + ... + E1[R-1]
    0 = E2[0] + ... + E2[R-1]
    0 = E1[0]*E2[0] + ... + E1[R-1]*E2[R-1]

    Exceptional case:
      The Catmull-Clark subdivision matrix for a crease vertex with
      two crease edges and a single face is a special case.  
      In this exceptional, this function returns
        lambda = 1/2, E1 = {0,-1,0,-1} and E2 = {1, -2, -5, -2}.
      For more information about the exceptional case, see the description of
      ON_SubDSectorType::SubdominantEigenvalueMulitiplicity().

  Parameters:
    E1_capacity - [in]
      Capacity of the E1[] array.
    E1 - [out]
    E2_capacity - [in]
      Capacity of the E2[] array.
    E2 - [out]
      When E1_capacity > 0 and E2_capacity > 0, two orthogonal eigenvectors
      spanning the subdivision matrix subdominant eigenspace are returned
      in E1[] and E2[].
      If one of E1_capacity or E2_capacity is > 0, then both must be > 0.

  Returns:
    ON_UNSET_VALUE: Invalid input.
    e > 0.0 and e < 1.0:
      subdominant eigenvalue.
  */
  double GetSubdominantEigenvectors(
    double* E1,
    size_t E1_capacity,
    double* E2,
    size_t E2_capacity
    ) const;

  /*
  Parameters:
    LPev_capacity - [in]
      Capacity of the LPev[] array.
    LPev - [out]
      When LPev_capacity > 0, then the limit surface point evaluation coefficients are
      returned in LPev[].  Otherwise LPev is ignored.
    LT0ev_capacity - [in]
      Capacity of the LPev[] array.
    LT0ev - [out]
    LT1ev_capacity - [in]
      Capacity of the LPev[] array.
    LT1ev - [out]
      When LT0ev_capacity > 0 and LT1ev_capacity > 0, then the limit surface
      tangent coefficients are returned in LT0ev[] and LT1ev[]. Otherwise,
      LT0ev[] and LT1ev[] are ignored.
      If one of LT0ev_capacity or LT1ev_capacity is > 0, then both must be > 0.
  Returns:
     0: Invalid input.
    >0: Number of evaluation coefficients in the L*ev[] arrays.
        This number is always ON_SubDSectorType.PointRingCount().
  */
  unsigned int GetSurfaceEvaluationCoefficients(
    double* LPev,
    size_t LPev_capacity,
    double* LT0ev,
    size_t LT0ev_capacity,
    double* LT1ev,
    size_t LT1ev_capacity
    ) const;

  // SurfaceNormalSign() is a debugging tool - slow and not useful in general
  double SurfaceNormalSign() const;

  bool SurfaceEvaluationCoefficientsAvailable() const;

  /*
  Parameters:
    eigenvalues_capacity - [in]
      Capacity of the eigenvalues[] array.
      Must be 0 or >= PointRingCount()
    eigenvalues - [out]
      If 0 = eigenvalues_capacity, eigenvalues must be nullptr.
      If eigenvalues_capacity > 0, is specifies the capactiy 
      of the eigenvalues[] array.
  Returns:
    R > 0: 
      A complete set of eigenvalues is available for this sector type.
      The eigenvalues are (1, lambda, lambda, e3, ..., eR), where
      1 > lambda > e3 >= ... >= eR > 0.
    0: 
      Invalid input or the eigenvalues for this sector typoe are not available.
  */
  unsigned int GetAllEigenvalues(
    double* eigenvalues,
    size_t eigenvalues_capacity
    );

  /////*
  ////Description:
  ////  The subdivision matrix for all cases is known.
  ////  A complete set of eigenvalues are available for some cases.
  ////Parameters:
  ////  facet_type - [in]
  ////  vertex_tag - [in]
  ////  sector_edge_count - [in]
  ////    The input parameters identify the subdivision case.
  ////Returns:
  ////  R > 0: Eigenvalues are known.  There subdivison matrix is R x R.
  ////  0: Eigenvalues for this case are not known.
  ////*/
  ////static unsigned int AllEigenvaluesAvailableKnown(
  ////  ON_SubDVertexTag vertex_tag,
  ////  unsigned int sector_edge_count
  ////  );

  /*
  Description:
    Create a partial subdivison sector around vertex.
    The resulting ON_SubD has an outer ring with smooth edges and vertices,
    which is not valid as a stand-alone subd.  This is typically used for
    testing.
  Parameters:
    radius - [in]
      The center vertex is located at (0,0,0),
      If radius > 0.0, then the end of the first edge is at (radius,0,0), 
      subsequent edges are in  a radial array and quad face points, if any, 
      are 2*radius from the origin.
    sector_angle_radians - [in]
      If radius > 0, 
      this->VertexTag() is ON_SubDVertexTag::Crease,
      crease_sector_angle_radians > 0.0 and 
      crease_sector_angle_radians < 2.0*ON_PI,
      then this will be the angle between the crease boundary edges.
      In all other cases, crease_sector_angle_radians is ignored.
    subd - [in]
      If subd is not null, the vertex ring is put in this
      subd.
  Returns:
    a pointer to the vertex ring
    nullptr is returned if the input is not valid.
  */
  ON_SubD* SectorRingSubD(
    double radius,
    double sector_angle_radians,
    ON_SubD* subd
    ) const;

private:
  ON_SubDVertexTag m_vertex_tag = ON_SubDVertexTag::Unset;
  unsigned char m_reserved1 = 0;
  unsigned short m_reserved2 = 0;
  unsigned int m_hash = 0; // SetHash() sets this field, SectorTypeHash() returns its value.
  unsigned int m_corner_sector_angle_index = 0; // >= 0 and <= ON_SubDSectorType::MaximumCornerAngleIndex
  unsigned int m_sector_face_count = 0;
  double m_sector_coefficient = 0.0;
  double m_sector_theta = 0.0;
  double m_corner_sector_angle_radians = 0.0;  
  
private:
  void SetHash();

  /*
  Description:
    Calculates sector theta value for the sector type
    identified by this ON_SubDSectorType.
  Returns:
    theta: 0.0 <= theta <= ON_PI
      The sector theta value.
    ON_SubDSectorType::ErrorSectorTheta
      This ON_SubDSectorType is not valid and the calculation failed.
  */
  double SectorTheta() const;

  /*
  Parameters:
    sector_face_count - [in] >= 1
      Number of faces in the crease sector.
  Returns:
    theta: 0.0 < theta <= ON_PI
      sector theta value for a crease sector with sector_face_count faces.
      theta = Pi / sector_face_count
    ON_SubDSectorType::ErrorSectorTheta
      sector_face_count is not valid and the calculation failed.
  */
  static double CreaseSectorTheta(
    unsigned int sector_face_count
    );
  
  /*
  Parameters:
    sector_face_count - [in] >= 2
      Number of faces in the dart sector.
  Returns:
    theta: 0.0 < theta <= ON_PI
      sector theta value for a dart sector with sector_face_count faces.
      theta = 2 Pi / sector_face_count
    ON_SubDSectorType::ErrorSectorTheta
      sector_face_count is not valid and the calculation failed.
  */
  static double DartSectorTheta(
    unsigned int sector_face_count
    );

  /*
  Parameters:
    sector_face_count - [in] >= 2
      Number of faces in the corner sector.
      Note the function will accept sector_face_count = 1 for consistency with the
      limit surface evaluation code but there is no valid SubD that can connect
      a smooth edge to a corner vertex with sector face count == 1.
    corner_sector_angle_radians - [in] (0.0 <= corner_sector_angle_radians <= ON_PI)
      The convex angle between the bounding crease edges
  Returns:
    theta: 0.0 < theta <= ON_PI/2
      sector theta value for the corner sector.
      theta = index_snapped[Pi/36](clamped[0,Pi](corner_sector_angle_radians)) / sector_face_count
    ON_SubDSectorType::ErrorSectorTheta
      sector_face_count or corner_sector_angle_radians were not valid
      and the calculation failed.
  */
  static double CornerSectorThetaFromCornerAngle(
    unsigned int sector_face_count,
    double corner_sector_angle_radians
    );

  /*
  Parameters:
    sector_theta - [in] 0 < sector_theta <= ON_PI
      value from one of the sector theta functions.
      ON_SubDEdge::SectorTheta()
      ON_SubDEdge::SmoothSectorTheta()
      ON_SubDEdge::CreaseSectorTheta()
      ON_SubDEdge::CornerSectorTheta()
      ON_SubDEdge::DartSectorTheta()
  Returns:
    0: 
      failed to calculate coefficient
    ON_SubDSectorType::ErrorSectorCoefficient: 
      sector_theta is not valid.
    0 < w < 1:
      The returned value is 
      1/2 + 1/3*cos(sector_theta). (1/6 <= w <= 5/6)
  Remarks:
    This is a useful tool when calling AddEdge while a subdivision
    level is being constructed.
  */
  static double SectorCoefficientFromTheta(
    double sector_theta
    );
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDMeshFragment
//
//  Meshes of ON_SubD limit surface are calculated in fragments.
//
class ON_CLASS ON_SubDMeshFragmentGrid
{
public:
  // No construction for performance reasons. 
  // use = ON_SubDMeshFragmentGrid::Empty
  // QuadGridFromSideSegmentCount(...)
  // or QuadGridFromDisplayDensity(...) to initialize.
  //
  //ON_SubDMeshFragmentGrid() = default;
  //~ON_SubDMeshFragmentGrid() = default;
  //ON_SubDMeshFragmentGrid(const ON_SubDMeshFragmentGrid&) = default;
  //ON_SubDMeshFragmentGrid& operator=(const ON_SubDMeshFragmentGrid&) = default;


  static const ON_SubDMeshFragmentGrid Empty;

  static const ON_SubDMeshFragmentGrid OneQuadGrid;

  /*
  Description:
    Get mesh facet quads that index into a grid of points.
  Parameters:
    side_segment_count - [in]
      number quads in each row and column of the quad grid.
        side_segment_count >= 1
        side_segment_count <= ON_SubDMesh::MaximumSideSegmentCount
        side_segment_count must be a power of 2

    mesh_density_reduction - [in]
      0: quad count = maximum quad count = (side_count x side_count)
      1: quad count = 1/4 maximum quad count
      1: quad count = 1/16 maximum quad count
      ...
      If 4^mesh_density_reduction > maximum quad count, then a single quad is returned.
  */
  static ON_SubDMeshFragmentGrid QuadGridFromSideSegmentCount(
    unsigned int side_segment_count,
    unsigned int mesh_density_reduction
    );

  static ON_SubDMeshFragmentGrid QuadGridFromDisplayDensity(
    unsigned int display_density,
    unsigned int mesh_density_reduction
    );

private:
  /*
  Description:
    Get mesh facet quads that index into a grid of points.
  Parameters:
    side_segment_count - [in]
      number quads in each row and column of the quad grid
      with the highest level of detail (level_of_detail = 0)
      side_count must be a power of 2
    level_of_detail - [in]
      Desired level of detail of the returned grid
        0: highest (side_count x side_count) quads
        1: 1/4 density (side_count x side_count)/4 quads
        2: 1/16 density (side_count x side_count)/16 quads
        ...
        side_count-2: 4 quads
        side_count-1: 1 quad
        >= side_count: 1 quad
  Returns:
    Number of quads in the grid.
  */
  static unsigned int SetQuads(
    unsigned int side_segment_count,
    unsigned int level_of_detail,
    unsigned int* quads,
    size_t quad_capacity,
    size_t quad_stride,
    unsigned int* sides,
    size_t side_capacity,
    size_t side_stride
    );

public:
  unsigned int SideSegmentCount() const;

  /*
  Returns:
    SideSegmentCount() + 1;
  */
  unsigned int SidePointCount() const;

  /*
  Description:
    The GridId() is persistent and unique based on the contents of the
    grid. It is intended to be used in render applications that store
    copies of ON_SubDMeshFragmentGrid settings in things like
    vertex object buffers and want a reliable way to index into them.
    The Empty grid has id = 0;
  Returns:
    0:
      when the grid is empty
    32*n + 2*lod + t:
      t = 0 for quads and 1 for tris,
      (0 <= n <= 8) m_F_count = 2^(2n), 
      (0 <= lod <= 8) m_F_level_of_detail = lod
  Remarks:
    m_F_count is always
  */
  unsigned int GridId() const;


  unsigned int GridFaceCount() const;

  /*
  Returns:
    Total number of points in the grid = SidePointCount()*SidePointCount().
  */
  unsigned int GridPointCount() const;

  /*
  Parameters:
    grid_point_index - [in]
      0 <= grid_point_index < GridPointCount().
    grid_parameters = [out]
      g2dex = Grid2dexFromPointIndex(grid_point_index).
      grid_parameters[] = {g2dex.i/SideSegmentCount(), g2dex.j/SideSegmentCount()}
  Returns:
    True if grid_point_index was valid and grid_parameters was returned.
  Remarks:
    On a SubD quad face, 
    face->Vertex(0), face->Vertex(1), face->Vertex(2), face->Vertex(3)
    are the SubD quad corners in counter-clockwise order.
    When a grid comes from a SubD quad face, the associated grid parameters are:
    grid_parameters[] = (0,0) at face->Vertex(0),
    grid_parameters[] = (1,0) at face->Vertex(1),
    grid_parameters[] = (0,1) at face->Vertex(3),
    grid_parameters[] = (1,1) at face->Vertex(2),
  */
  bool GetGridParameters(
    unsigned int grid_point_index,
    double grid_parameters[2]
    ) const;

  /*
  Parameters:
    grid_point_index - [in]
      0 <= grid_point_index < GridPointCount().
  Returns:
    Grid (i,j) for that grid_point_index.  
    0 <= i < SidePointCount()
    0 <= j < SidePointCount()
  Remarks:
    On a SubD quad face,
    face->Vertex(0), face->Vertex(1), face->Vertex(2), face->Vertex(3)
    are the SubD quad corners in counter-clockwise order.

    Set 
    n = grid->GridPointCount()-1 and 
    k = grid->SideSegmentCount() = (grid->SidePointCount()-1).
    Note that (k+1)*(k+1) = (n+1) = GridPointCount().

    When a grid comes from a SubD quad face, the associated grid point indices are

    vertex, grid point index, grid point 2dex
    face->Vertex(0), 0, (0,0)
    face->Vertex(1), k, (k,0)
    face->Vertex(2), n-k, (k,k)
    face->Vertex(3), n, (0,k)
  */
  const ON_2udex Grid2dexFromPointIndex(
    unsigned int grid_point_index
  )  const;

  /*
  Parameters:
    i - [in]
      0 <= i < SidePointCount()
    j - [in]
      0 <= j < SidePointCount()
  Returns:
    0 <= grid_point_index < GridPointCount().
  Remarks:
    On a SubD quad face,
    face->Vertex(0), face->Vertex(1), face->Vertex(2), face->Vertex(3)
    are the SubD quad corners in counter-clockwise order.

    Set
    n = grid->GridPointCount()-1 and
    k = grid->SideSegmentCount() = (grid->SidePointCount()-1).
    Note that (k+1)*(k+1) = (n+1) = GridPointCount().

    When a grid comes from a SubD quad face, the associated grid point indices are

    vertex, grid point index, grid point 2dex
    face->Vertex(0), 0, (0,0)
    face->Vertex(1), k, (k,0)
    face->Vertex(2), n-k, (k,k)
    face->Vertex(3), n, (0,k)
  */
  unsigned int PointIndexFromGrid2dex(
    unsigned int i,
    unsigned int j
  )  const;

  /*
  Returns:
    A number between 0 and 8 or ON_UNSET_INT_INDEX.
    SideSegmentCount() = 2^DisplayDensity().
  */
  unsigned int DisplayDensity() const;

  ON_DEPRECATED_MSG("Identical to DisplayDensityReduction(). Use DisplayDensityReduction() instead because its a better name.")
  unsigned int LevelOfDetail() const;

  /*
  Description
    Each grid set has grids of quads that index the identical set of points (normals, texture coordinates, ...).
    The grid in the set with the maximum number of quads has DisplayDensityReduction() = 0.
    Additional grids in the set reduce the number of quads by a factor of 4.
    The intedger on the left is the DisplayDensityReduction value. The value of the right
    is the number of quads where M = maximum quad count for that grid set. 
    All nonzero values of M are powers of 4 (4^n). The relationship between 
    P = number of points in the set and M (the maximum number of quads for the point set)
    is P = (M/2+1)*(M/2+1).
    
    DisplayDensityReduction(): number of quads
    0: M
    1: M/4
    2: M/16
    3: M/64
    4: M/256
    ...

  Returns:
    The display density reduction from the maximum display density for this grid set.
  */
  unsigned int DisplayDensityReduction() const;

private:
  unsigned char m_reserved1;

private:
  unsigned char m_reserved2;

public:
  unsigned char m_side_segment_count; // = 2^n for non-empty grids (0 <= n <= 8)

private:
   unsigned char m_reserved3;

public:
  // m_F_count = number of quads
  //           = m_side_segment_count*m_side_segment_count
  // (0,1,4,16,256,1024,4096) After 0, each permitted value is 4x previous value
  unsigned short m_F_count;

  // m_F_level_of_detail is poorly named. It should be named m_F_mesh_density_reduction.
  // 0 = no reduction (maximum level of detail)
  // 1 = number of quads reduced by 1/4
  // 2 = number of quads reduced by 1/16
  // ...
  unsigned short m_F_level_of_detail;

  unsigned short m_F_stride;

private:
  ON__UINT16 m_reserved4;
  ON__UINT32 m_reserved5;

public:
  const unsigned int* m_F;
  const unsigned int* m_S; // [4*m_side_segment_count + 1] indices that form the polyline boundary.
  const ON_SubDMeshFragmentGrid* m_prev_level_of_detail; // nullptr or the previous level with 4 times the number of quads.
  const ON_SubDMeshFragmentGrid* m_next_level_of_detail; // nullptr or the next level with 1/4 times the number of quads.
};

class ON_CLASS ON_SubDMeshFragment
{
public:
  // No construction for performance reasons. 
  // If you require initialization, use = ON_SubDMeshFragment::Empty
  //
  //ON_SubDMeshFragment() = default;
  //~ON_SubDMeshFragment() = default;
  //ON_SubDMeshFragment(const ON_SubDMeshFragment&) = default;
  //ON_SubDMeshFragment& operator=(const ON_SubDMeshFragment&) = default;

  bool CopyFrom( const ON_SubDMeshFragment& src_fragment );


  /// <summary>
  /// Clear all information except the memory management inforation.
  /// 
  /// The intent is to be able to clear and reuse the fragment at
  /// its current vertex capacity.
  /// 
  /// Secifically:
  /// 
  /// Set referenced SubDFace to nullptr.
  /// Set vertex count to zero.
  /// Set existance of textures, curvatures, and colors to false.
  /// Set control net quad values to nans.
  /// Set the grid to ON_SubDMeshFragmentGrid::Empty.
  /// Set the surface bounding box to nan.
  /// 
  /// Does not change vertex capacity or deallocate managed arrays.
  /// </summary>
  void Clear() ON_NOEXCEPT;


  /*
  Parameters:
    src_fragment - [in]
      fragment to copy
    display_density - [in]
      The desired display density of the copy.

      If display_density = ON_UNSET_UINT_INDEX, then this->m_P_capacity must
      be at least srf_fragment.m_P_count, all points are copied, and 
      this->m_grid = srf_fragment.m_grid.

      Otherwise, src_fragment must have enough points to provide 
      the specified denisity and this must have enough 
      point capacity to store the specified density.

    this - [out]
      This must have a point capacity large enough to accommodate the
      requested display density.

  */
  bool CopyFrom( 
    const ON_SubDMeshFragment& src_fragment,
    unsigned int display_density
  );
  
  // Every field of ON_SubDMeshFragment::Empty is zero.
  static const ON_SubDMeshFragment Empty;

  enum : unsigned int
  {
    MaximumSideSegmentCount = (1U << ON_SubDDisplayParameters::MaximumDensity)
  };
  
  /*
  Returns:
    side_segment_count  = 2^display_density
  */
  static unsigned int SideSegmentCountFromDisplayDensity(
    unsigned int display_density
    );
  
  /*
  Returns:
    base 2 log of side_segment_count.
  Remarks:
    side_segment_count = 2^display_density
  */
  static unsigned int DisplayDensityFromSideSegmentCount(
    unsigned int side_segment_count
    );

  /*
  Parameters:
    display_density - [in]
      >= 0
  Returns:
    total number of points in the limit mesh fragment.
  Remarks:
    The number of points is the same for quad or tri subdivision limit
    mesh fragments, even though one is a rectanglular collection of 
    quads and the other is a triangular collection of triangles.
  */
  static unsigned int PointCountFromDisplayDensity(
    unsigned int display_density
    );

  /*
  Parameters:
    display_density - [in]
      >= 0
  Returns:
    total number of faces in the limit mesh fragment.
  */
  static unsigned int FaceCountFromDisplayDensity(
    unsigned int display_density
    );

  /*
  Returns:
    true if side_segment_count is valid.
    Otherwise 0 is returned.
  */
  static bool SideSegmentCountIsValid(
    unsigned int side_segment_count
    );

  /*
  Returns:
    If side_segment_count is valid, then (side_segment_count+1) is returned.
    Otherwise 0 is returned.
  */
  static unsigned int SidePointCountFromSideCount(
    unsigned int side_segment_count
    );

  /*
  Returns:
    If side_segment_count is valid, then (side_segment_count+1)^2 is returned.
    Otherwise 0 is returned.
  */
  static unsigned int QuadGridPointCountFromSideCount(
    unsigned int side_segment_count
    );

  /*
  Returns:
    If side_segment_count is valid, then side_segment_count^2 is returned.
    Otherwise 0 is returned.
  */
  static unsigned int QuadGridQuadCountFromSideCount(
    unsigned int side_segment_count
    );

  /*
  Description:
    Copies location and optionally normal information from a side of src_fragment
    to a side of dst_fragment. This is often used for "sealing" adjacent fragments
    where the same edge is evaluated from different faces. All evaluations are as accurate
    as IEEE double precision arithmetic can produce. However there are often tiny differences
    (last few bits of the coordinate values differ) in vertext locations because we are 
    using finite precision arithmetic with operations in different orders. 
    In general, rendering, mesho topology, and edge analysis calculations perform poorly
    when tinity differences exist.

  Parameters:
    bTestNearEqual - [in]
      If true, then the copy is performed only when the points or normals are nearly
      identical. In this case if the discrepance between coordinates is too large,
      then this function returns false.
    bCopyNormals - [in]
      If true, then normal information is copied along with point information.
    src_fragment - [in] 
      source fragment
    i0, i1 - [in]
      indices for the src_fragment.m_S[] array.      
    dst_fragment - [in] 
      destination fragment
    j0, j1 - [in]
      indices for dst_fragment.m_S[] array.
      abs(j0-j1) = abs(i0-i1);
  Remarks:
    It is required that max(i0,i1) - min(i0,i1) = max(j0,j1) - min(j0,j1) and
    all indices are valid for the respective fragments.
    The src_fragment point/normal identified by src_fragment.m_S[i] 
    is copied to he dst_fragment point/normal identified by dst_fragment.m_S[j], 
    where i0->j0, i1->j1. 
  */
  static bool SealAdjacentSides(
    bool bTestNearEqual,
    bool bCopyNormals,
    const ON_SubDMeshFragment& src_fragment,
    unsigned int i0,
    unsigned int i1,
    ON_SubDMeshFragment& dst_fragment,
    unsigned int j0,
    unsigned int j1
  );

  /*
  Parameters:
    bTestNearEqual - [in]
      If true, then the copy is performed only when the points or normals are nearly
      identical. In this case if the discrepance between coordinates is too large,
      then this function returns false.
    src - [in]
    dst - [in/out]
      The 3d point (src[0],src[1],src2[2]) is copied to (dst[0],dst[1],dst[2]).
  Returns:
    True if a copy occurred.
  */
  static bool SealPoints(
    bool bTestNearEqual,
    const double* src, 
    double* dst
    );

  /*
  Parameters:
    bTestNearEqual - [in]
      If true, then the copy is performed only when the points or normals are nearly
      identical. In this case if the discrepance between coordinates is too large,
      then this function returns false.
    src - [in]
    dst - [in/out]
      The 3d point (src[0],src[1],src2[2]) is copied to (dst[0],dst[1],dst[2]).
  Returns:
    True if a copy occurred.
  */
  static bool SealNormals(
    bool bTestNearEqual,
    const double* src, 
    double* dst
    );

  /*
  Returns:
    Number of mesh quads in a full sized fragment with the specified mesh density.
  */
  static unsigned int FullFragmentMeshQuadCountFromDensity(
    unsigned int mesh_density
  );

  /*
  Returns:
    Number of mesh quads in a half sized fragment with the specified mesh density.
  */
  static unsigned int HalfFragmentMeshQuadCountFromDensity(
    unsigned int mesh_density
  );

  /*
  Returns:
    Number of mesh points in a full sized fragment with the specified mesh density.
  */
  static unsigned int FullFragmentMeshPointCountFromDensity(
    unsigned int mesh_density
  );

  /*
  Returns:
    Number of mesh points in a half sized fragment with the specified mesh density.
  */
  static unsigned int HalfFragmentMeshPointCountFromDensity(
    unsigned int mesh_density
  );

private:
  // This field overlaps with ON_FixedSizePoolElement.m_next when a fixed size pool is managing the fragments.
  // When m_reserved != 0, the framgment is uninitialized. 
  ON__UINT64 m_reserved;

public:
  const class ON_SubDFace* m_face;

  // m_face_vertex_index[] stores the information needed for the Vertex()
  // and Edge() functions to work.
  //
  // If m_face is nullptr, then m_face_vertex_index[] has no meaning.
  // If m_face is not nullptr and a corner of the grid is on a face
  // vertex, then the corresponding m_face_vertex_index[] value
  // will be <= ON_SubDFace::MaximumEdgeCount and m_face->Vertex(m_face_vertex_index[])
  // is the vertex.  Otherwise,  the corresponding m_face_vertex_index[] value
  // will be > ON_SubDFace::MaximumEdgeCount.  
  // Catmull-Clark limit meshes:
  //   When the original SubD face is a quad, a full fragment is created and
  //   m_face_vertex_index[4] = {0,1,2,3}.
  //   When the original SuD face is an N-gon with N != 4, a partial fragment 
  //   is delivered and m_face_vertex_index[2] identifies the face vertex 
  //   for that fragment.  m_face_vertex_index[0,1,3] = a value > ON_SubDFace::MaximumEdgeCount
  unsigned short m_face_vertex_index[4];

  const class ON_SubDFace* SubDFace() const;

  const bool HasValidPointAndNormalGrid() const;

  /*
  Returns:
    True if the fragment covers the entire SubD face.
  */
  bool IsFullFaceFragment() const;

  /*
  Returns:
    True if the fragment covers a corner of the SubD face.
  */
  bool IsFaceCornerFragment() const;
  
  /*
  Returns:
    If IsFaceCornerFragment() is true, then the index of the face's vertex for the corner is returned.
    Otherwise, ON_UNSET_UINT_INDEX is returned.
  */
  unsigned int FaceCornerIndex() const;

  /*
  Returns:
    Number of fragments that cover this face. 1 for quads and N>= 3 for faces with N sides when N != 4.
  */
  unsigned int FaceFragmentCount() const;

  /*
  Returns:
    First fragment for this->m_face.
  */
  const ON_SubDMeshFragment* FirstFaceFragment() const;

  /*
  Returns:
    Last fragment for this->m_face.
  */
  const ON_SubDMeshFragment* LastFaceFragment() const;

  /*
  Parameters:
    bReturnLastFromFirstFirst - in
      If false and this is the first fragment, then nullptr is returned.
      If true and this is the first fragment, then LastFaceFragment() is returned.
  Returns:
    Previous fragment for this->m_face.
  */
  const ON_SubDMeshFragment* PreviousFaceFragment(
    bool bReturnLastFromFirstFirst
  ) const;

  /*
  Parameters:
    bReturnFirstFromLast - in
      If false and this is the last fragment, then nullptr is returned.
      If true and this is the last fragment, then FirstFaceFragment() is returned.
  Returns:
    Next fragment for this->m_face.
  */
  const ON_SubDMeshFragment* NextFaceFragment(
    bool bReturnFirstFromLast
  ) const;

  /*
  Parameters:
    fragments_capacity - in
      Capacity of the fragments[] array.
    fragments[] - out
      Fragments are returned here.
  */
  unsigned int GetFaceFragments(
    const ON_SubDMeshFragment** fragments,
    size_t fragments_capacity
    ) const;

  unsigned int GetFaceFragments(
    ON_SimpleArray<const ON_SubDMeshFragment*>& fragments
  ) const;

  /*
  Parameters:
    grid2dex_i - [in]
      0 <= grid2dex_i < m_grid.SidePointCount()
    grid2dex_j - [in]
      0 <= grid2dex_j < m_grid.SidePointCount()
  Returns:
  */
  const ON_3dPoint VertexPoint(
    unsigned grid2dex_i,
    unsigned grid2dex_j
  ) const;
  const ON_3dPoint VertexPoint(
    ON_2udex grid2dex
  ) const;
  const ON_3dPoint VertexPoint(
    unsigned grid_point_index
  ) const;

  /*
  Parameters:
    grid2dex_i - [in]
      0 <= grid2dex_i < m_grid.SidePointCount()
    grid2dex_j - [in]
      0 <= grid2dex_j < m_grid.SidePointCount()
  Returns:
  */
  const ON_3dVector VertexNormal(
    unsigned grid2dex_i,
    unsigned grid2dex_j
  ) const;
  const ON_3dVector VertexNormal(
    ON_2udex grid2dex
  ) const;
  const ON_3dVector VertexNormal(
    unsigned grid_point_index
  ) const;

  /// <summary>
  /// Get the SubD face evaluation parameter for the 
  /// SubD surface point where this vertex is located.
  /// </summary>
  /// <param name="grid2dex_i">
  /// 0 &lt;= grid2dex_i &lt;= m_grid.SideSegmentCount()</param>
  /// <param name="grid2dex_j">
  /// 0 &lt;= grid2dex_j &lt;= m_grid.SideSegmentCount()</param>
  /// </param>
  /// <returns>
  /// The SubD face evaluation parameter at this grid vertex.
  /// </returns>
  const ON_SubDFaceParameter VertexSubDFaceParameter(
    unsigned grid2dex_i,
    unsigned grid2dex_j
  ) const;

  /// <summary>
  /// Get the SubD face evaluation parameter for the 
  /// SubD surface point where this vertex is located.
  /// </summary>
  /// <param name="grid2dex_i">
  /// 0 &lt;= grid2dex.i &lt;= m_grid.SideSegmentCount()</param>
  /// <param name="grid2dex_j">
  /// 0 &lt;= grid2dex.j &lt;= m_grid.SideSegmentCount()</param>
  /// </param>
  /// <returns>
  /// The SubD face evaluation parameter at this grid vertex.
  /// </returns>
  const ON_SubDFaceParameter VertexSubDFaceParameter(
    ON_2udex grid2dex
  ) const;

  /// <summary>
  /// Get the SubD face evaluation parameter for the 
  /// SubD surface point where this vertex is located.
  /// </summary>
  /// <param name="grid_point_index">
  /// 0 &lt;= grid_point_index &lt;= m_grid.GridPointCount()</param>
  /// </param>
  /// <returns>
  /// The SubD face evaluation parameter at this grid vertex.
  /// </returns>
  const ON_SubDFaceParameter VertexSubDFaceParameter(
    unsigned grid_point_index
  ) const;

  /*
  Parameters:
    grid2dex_i - [in]
      0 <= grid2dex_i < m_grid.SidePointCount()
    grid2dex_j - [in]
      0 <= grid2dex_j < m_grid.SidePointCount()
  Returns:
    The texture coordinates calculated by iterpolating the m_ctrlnetT[] values.
  */
  const ON_3dPoint VertexTextureCoordinateFromCorners(
    unsigned grid2dex_i,
    unsigned grid2dex_j
  ) const;
  const ON_3dPoint VertexTextureCoordinateFromCorners(
    ON_2udex grid2dex
  ) const;
  const ON_3dPoint VertexTextureCoordinateFromCorners(
    unsigned grid_point_index
  ) const;
  
  /*
  Description:
    Get the texture coordinate for the specified fragment grid point.
  Parameters:
    grid2dex_i - [in]
      0 <= grid2dex_i < m_grid.SidePointCount()
    grid2dex_j - [in]
      0 <= grid2dex_j < m_grid.SidePointCount()
  Returns:
    The texture coordinate for the specified fragment grid point.
    TextureCoordinateDimension() reports the number of coordinates to set.
    When it is 2, the z coordinate of the returned point is 0.0.
  */
  const ON_3dPoint VertexTextureCoordinate(
    unsigned grid2dex_i,
    unsigned grid2dex_j
  ) const;
  const ON_3dPoint VertexTextureCoordinate(
    ON_2udex grid2dex
  ) const;
  const ON_3dPoint VertexTextureCoordinate(
    unsigned grid_point_index
  ) const;

  /*
  Description:
    Set the texture coordinate for the specified fragment grid point.
  Parameters:
    grid2dex_i - [in]
      0 <= grid2dex_i < m_grid.SidePointCount()
    grid2dex_j - [in]
      0 <= grid2dex_j < m_grid.SidePointCount()
    unsigned texture_coordinate_dimension - [in]
      2 or 3
    texture_coordinate - [in]
      Texture coordinates are mutable and are often modified on an otherwise const fragment.
  Returns:
    True if input was valid and the texture coordinate was set.
  */
  bool SetVertexTextureCoordinate(
    unsigned grid2dex_i,
    unsigned grid2dex_j,
    ON_3dPoint texture_coordinate
  ) const;
  bool SetVertexTextureCoordinate(
    ON_2udex grid2dex,
    ON_3dPoint texture_coordinate
  ) const;
  bool SetVertexTextureCoordinate(
    unsigned grid_point_index,
    ON_3dPoint texture_coordinate
  ) const;


  void ClearTextureCoordinates() const;

  bool TextureCoordinatesExistForExperts() const;

  void SetTextureCoordinatesExistForExperts(bool bTextureCoordinatesExist) const;

  /*
  Parameters:
    grid_side_index - [in]
      0 to 3 for quad grids.
      0 to 2 for tri grids
  Returns:
    The subd edge that is on the identified side of the grid.
  */
  const class ON_SubDEdgePtr SubDEdgePtr(
    unsigned int grid_side_index
    ) const;
  const class ON_SubDEdge* SubDEdge(
    unsigned int grid_side_index
    ) const;

  /*
  Parameters:
    grid_corner_index - [in]
      0, 1, 2, or 3
  Remarks:
    For partial fragments (IsFaceCornerFragment() = true), grid_corner_index = 2 is the only
    corner that corresponds to a SubD vertex. 
    For partial fragments (IsFaceCornerFragment() = true), grid_side_index = 1 and grid_side_index = 2
    correspond to half of original SuD edges.
  */
  const class ON_SubDVertexPtr SubDVertexPtr(
    unsigned int grid_corner_index
    ) const;

  /*
  Parameters:
    grid_corner_index - [in]
      0, 1, 2, or 3
  Remarks:
    For partial fragments (IsFaceCornerFragment() = true), grid_corner_index = 2 is the only
    corner that corresponds to a SubD vertex. 
    For partial fragments (IsFaceCornerFragment() = true), grid_side_index = 1 and grid_side_index = 2
    correspond to half of original SuD edges.
  */
  const class ON_SubDVertex* SubDVertex(
    unsigned int grid_corner_index
    ) const;


  /*
  Parameters:
    grid_corner_index - [in]
      0, 1, 2, or 3
  Returns:
    Limit surface location at the grid corner or ON_3dPoint::NanPoint if the fragment is empty.
  Remarks:
    For partial fragments (IsFaceCornerFragment() = true), grid_corner_index = 2 is the only
    corner that corresponds to a SubD vertex. 
    For partial fragments (IsFaceCornerFragment() = true), grid_side_index = 1 and grid_side_index = 2
    correspond to half of original SuD edges.
  */
  const ON_3dPoint CornerPoint(
    unsigned int grid_corner_index
    ) const;

  /*
  Parameters:
    grid_corner_index - [in]
      0, 1, 2, or 3
  Returns:
    Limit surface normal at the grid corner or ON_3dPoint::NanPoint if the fragment is empty.
  Remarks:
    For partial fragments (IsFaceCornerFragment() = true), grid_corner_index = 2 is the only
    corner that corresponds to a SubD vertex. 
    For partial fragments (IsFaceCornerFragment() = true), grid_side_index = 1 and grid_side_index = 2
    correspond to half of original SuD edges.
  */
  const ON_3dVector CornerNormal(
    unsigned int grid_corner_index
  ) const;

  /*
  Parameters:
    grid_corner_index - [in]
      grid side N is between corner index N and corner index (N+1)%4.
  Returns:
    Limit surface frame at the grid corner or ON_3dPoint::NanPoint if the fragment is empty.
  Remarks:
    For partial fragments (IsFaceCornerFragment() = true), grid_corner_index = 2 is the only
    corner that corresponds to a SubD vertex. 
    For partial fragments (IsFaceCornerFragment() = true), grid_side_index = 1 and grid_side_index = 2
    correspond to half of original SuD edges.
  */
  const ON_Plane CornerFrame(
    unsigned int grid_corner_index
  ) const;

  /*
  Parameters:
    grid_corner_index - [in]
      0, 1, 2, or 3
  Returns:
    vertex color at the grid corner or ON_Color::UnsetColor if thre are not vertex colors.
  Remarks:
    For partial fragments (IsFaceCornerFragment() = true), grid_corner_index = 2 is the only
    corner that corresponds to a SubD vertex.
    For partial fragments (IsFaceCornerFragment() = true), grid_side_index = 1 and grid_side_index = 2
    correspond to half of original SuD edges.
  */
  const ON_Color CornerColor(
    unsigned int grid_corner_index
  ) const;

  /*
  Parameters:
    grid_corner_index - [in]
      0, 1, 2, or 3
  Returns:
    vertex surface curvature at the grid corner or ON_SurfaceCurvature::Nan if there are not vertex curvatures.
  Remarks:
    For partial fragments (IsFaceCornerFragment() = true), grid_corner_index = 2 is the only
    corner that corresponds to a SubD vertex.
    For partial fragments (IsFaceCornerFragment() = true), grid_side_index = 1 and grid_side_index = 2
    correspond to half of original SuD edges.
  */
  const ON_SurfaceCurvature CornerCurvature(
    unsigned int grid_corner_index
  ) const;


  /*
  Parameters:
    grid_side_index - [in]
      grid side N is between corner index N and corner index (N+1)%4.
  Returns:
    Limit surface location at the midde of the grid side or ON_3dPoint::NanPoint if the fragment is empty.
  Remarks:
    For partial fragments (IsFaceCornerFragment() = true), grid_corner_index = 2 is the only
    corner that corresponds to a SubD vertex. 
    For partial fragments (IsFaceCornerFragment() = true), grid_side_index = 1 and grid_side_index = 2
    correspond to half of original SuD edges.
  */
  const ON_3dPoint SidePoint(
    unsigned int grid_side_index
  ) const;

  /*
  Parameters:
    grid_side_index - [in]
      grid side N is between corner index N and corner index (N+1)%4.
  Returns:
    Limit surface normal at the grid corner or ON_3dPoint::NanPoint if the fragment is empty.
  Remarks:
    For partial fragments (IsFaceCornerFragment() = true), grid_corner_index = 2 is the only
    corner that corresponds to a SubD vertex. 
    For partial fragments (IsFaceCornerFragment() = true), grid_side_index = 1 and grid_side_index = 2
    correspond to half of original SuD edges.
  */
  const ON_3dVector SideNormal(
    unsigned int grid_side_index
  ) const;

  /*
  Parameters:
    grid_side_index - [in]
      grid side N is between corner index N and corner index (N+1)%4.
  Returns:
    Limit surface frame at the grid corner or ON_3dPoint::NanPoint if the fragment is empty.
  Remarks:
    For partial fragments (IsFaceCornerFragment() = true), grid_corner_index = 2 is the only
    corner that corresponds to a SubD vertex. 
    For partial fragments (IsFaceCornerFragment() = true), grid_side_index = 1 and grid_side_index = 2
    correspond to half of original SuD edges.
  */
  const ON_Plane SideFrame(
    unsigned int grid_side_index
  ) const;

  /*
  Parameters:
    grid_side_index - [in]
      grid side N is between corner index N and corner index (N+1)%4.
  Returns:
    Limit surface location at the center of the grid side or ON_3dPoint::NanPoint if the fragment is empty.
  Remarks:
    For partial fragments (IsFaceCornerFragment() = true), grid_corner_index = 2 is the only
    corner that corresponds to a SubD vertex. 
    For partial fragments (IsFaceCornerFragment() = true), grid_side_index = 1 and grid_side_index = 2
    correspond to half of original SuD edges.
  */
  const ON_3dPoint CenterPoint(
  ) const;

  const ON_3dVector CenterNormal() const;

  const ON_Plane CenterFrame() const;

  const ON_3dPoint CenterTextureCoordinate() const;

private:
  bool Internal_GetFrameHelper(
    unsigned int P_dex,
    unsigned int Q_dex,
    ON_Plane& frame
  ) const;

public:

  /*
  Returns:
    Status of the face.
  */
  ON_ComponentStatus Status() const;

  /// <summary>
  /// This simple version transforms the points and normals and attempts possible
  /// transformations to the curvatures, texture coordinates and colors:
  ///   - Normals are transformed with the inverse transpose of xform, then flipped
  ///     if the transformation is mirroring, and unitized if the transformation has
  ///     a scale component.
  ///   - Texture coordinates are unchanged in value,
  ///     ON_SubDimple::Transform(xform) will update the texture coordinate tag
  ///     with subdimple.m_texture_mapping_tag.Transform(xform)
  ///   - Colors are unchanged in value if xform is an isometry, deleted otherwise.
  ///     ON_SubDimple::Transform(xform) will update the colors tag
  ///      with subdimple.m_color_mapping_tag.Transform(xform)
  ///   - Curvatures are scaled by 1/det(xform), if xform is a Similarity tranformation,
  ///     deleted otherwise.
  /// 
  /// Typically lots of fragments are being transformed and the type and context
  /// of the transformation determines if and how normals, texture coordinate,
  /// curvature and color inforation should be preserved, transformed, or destroyed.
  /// It is better to determine the answers to these questions and call the version
  /// of Transform with the bKeepTextures, bKeepCurvatures and bKeepColors parameters.
  /// 
  /// For example if the transformation is an isometry and the colors are set from
  /// the curvatures, then curvatures and colors should be kept. If the transformation
  /// is a similarity, the curvatures should be scaled and the colors destroyed. If
  /// the transformation is not a similarity both colors and curvatures should be destroyed.
  /// 
  /// If the texture coordinates are set from grid location (fake surface paramaters),
  /// then the texture coordinates should be kept.
  /// If transform is not an identity and the texture coordinates come from a 
  /// world object mapping, they should generally be destroyed.
  /// </summary>
  /// <param name="xform"></param>
  /// <returns></returns>
  bool Transform(
    const ON_Xform& xform
  );

  /// <summary>
  /// This version transforms the points and normals and attempts possible
  /// transformations to the curvatures, texture coordinates and colors, if they are kept:
  ///   - Normals are transformed with the inverse transpose of xform, then flipped
  ///     if the transformation is mirroring, and unitized if the transformation has a scale component.
  ///   - Texture coordinates are unchanged in value, ON_SubDimple::Transform(xform) will update
  ///       them with subdimple.m_texture_mapping_tag.Transform(xform).
  ///       If bKeepTextures is false, texture coordinates are destroyed.
  ///   - Curvatures are either:
  ///       - scaled by 1/det(xform), if xform is a Similarity tranformation
  ///       - unchanged in value, if not.
  ///       If bKeepCurvatures is false, curvatures are destroyed.
  ///   - Colors are unchanged in value, ON_SubDimple::Transform(xform) will update
  ///       them with subdimple.m_color_mapping_tag.Transform(xform)
  ///       If bKeepColors is false, colors are destroyed.
  /// </summary>
  /// <param name="bKeepTextures"></param>
  /// <param name="bKeepCurvatures"></param>
  /// <param name="bKeepColors"></param>
  /// <param name="xform"></param>
  /// <returns></returns>
  bool Transform(
    bool bKeepTextures,
    bool bKeepCurvatures,
    bool bKeepColors,
    const ON_Xform& xform
  );

  /// <summary>
  /// This version transforms the points, normals, curvatures, texture coordinates,
  /// and colors, if they are kept.
  ///   - Normals are transformed with xformNormals.
  ///   - Texture coordinates are transformed with xformTextures.
  ///       If bKeepTextures is false, texture coordinates are destroyed.
  ///   - Curvatures are transformed with xformCurvatures.
  ///       If bKeepCurvatures is false, curvatures are destroyed.
  ///   - Colors are transformed with xformColors.
  ///       If bKeepColors is false, colors are destroyed.
  /// </summary>
  /// <param name="bKeepTextures"></param>
  /// <param name="bKeepCurvatures"></param>
  /// <param name="bKeepColors"></param>
  /// <param name="xform"></param>
  /// <param name="xformNormals"></param>
  /// <param name="xformTextures"></param>
  /// <param name="xformCurvatures"></param>
  /// <param name="xformColors"></param>
  /// <returns></returns>
  bool Transform(
    bool bKeepTextures,
    bool bKeepCurvatures,
    bool bKeepColors,
    const ON_Xform& xform,
    const ON_Xform& xformNormals,
    const ON_Xform& xformTextures,
    const ON_Xform& xformCurvatures,
    const ON_Xform& xformColors
  );

  ON_SubDMeshFragment* m_next_fragment;
  ON_SubDMeshFragment* m_prev_fragment;

  unsigned short m_face_fragment_count; // Number of fragments that will be delivered for this face.
  unsigned short m_face_fragment_index; // First fragment has index = 0. Last fragment has index = m_face_fragment_count-1.

  // The mesh fragment is a grid of quads.
  // There are m_side_count quad edges along each side of the tessellation,
  // There are a total of m_side_count X m_side_count quads, and
  // m_P_count = (m_side_count+1)*(m_side_count+1).

public:
  enum : unsigned
  {
    /// <summary>
    /// 64x64 grid of points
    /// </summary>
    MaximumVertexCount = 0x1000
  };

  /*
  Returns:
    Number of vertices in the mesh fragment grid.
    VertexCount() should be identical to m_grid.GridPointCount().
    VertexCapacity() should be >= VertexCount().
  */
  unsigned VertexCount() const;

  /*
  Description:
    Sets number of fragment vertices being used (number of elements being used in the m_P[], m_N[], and m_T[] arrays).
  Parameters:
    vertex_count - [in]
      A value no larger than ON_SubDMeshFragment::MaximumVertexCount.
  */
  bool SetVertexCount(size_t vertex_count);

  /*
  Returns:
    Capactity for vertices in the mesh fragment grid.
    VertexCapacity() should be >= VertexCount().
    VertexCount() should be identical to m_grid.PointCount().
  */
  unsigned VertexCapacity() const;

  /*
  Description:
    Sets number of fragment vertices available (number of elements available in the 
    m_P[], m_N[], m_T[], m_K[], and m_C[] arrays).
    The memory for the arrays is managed by something besides this ON_SubDMeshFragment instance.
  Parameters:
    vertex_capacity - [in]
      A value no larger than ON_SubDMeshFragment::MaximumVertexCount.
  Returns:
    True if successful
  */
  bool SetUnmanagedVertexCapacityForExperts(size_t vertex_capacity);


  /*
  Description:
    Sets number of fragment vertices available 
    (number of elements available in the m_P[], m_N[], m_T[], m_K[], and m_C[]  arrays).
    The memory for the arrays is managed by something besides this ON_SubDMeshFragment instance.
  Parameters:
    vertex_capacity - [in]
      A value no larger than ON_SubDMeshFragment::MaximumVertexCount.
  Returns:
    True if successful
  */
  bool ReserveManagedVertexCapacity(size_t vertex_capacity);


  /*
  Returns:
    True if the memory in the m_P[], m_N[],  m_T[], m_K[], and m_C[] arrays
    is managed by this ON_SubDMeshFragment instance and can be deleted by 
    calling DeleteManagedArrays().
    False if an external agent is managing the memory.
  */
  bool ManagedArrays() const;


  /*
    True if the memory in the m_P[], m_N[],  m_T[], m_K[], and m_C[] arrays
    is managed by this ON_SubDMeshFragment instance, this function deletes
    it and zeros the appropriate ponters and strides. 
    Otherwise nothing is done.
  */
  bool DeleteManagedArrays();

  /*
  Returns:
    True if the memory in the m_P[], m_N[], m_T[], m_K[], and m_C[] arrays
    is managed by something besides this ON_SubDMeshFragment instance.
  */
  bool UnmanagedArrays() const;

  // True if the memory for points, normals, textures, colors, and curvatures is interlaced.
  bool InterlacedArrays() const;

private:
  friend class ON_SubDManagedMeshFragment;
  friend class ON_SubDMeshImpl;
  friend class ON_SubDHeap;

  // Number of grid vertices and capacity of arrays in certain conditions.
  enum
  {
    /// <summary>
    /// 3 doubles for the vertex point
    /// 3 doubles for the vertex normal
    /// 3 doubles for the vertex texture coordinate
    /// 2 doubles for the vertex principal curvatures (ON_SurfaceCurvature class)
    /// 1 double (4 bytes used for vertex color and 4 bytes currently not used)
    /// </summary>
    /// <remarks>
    /// This number must be even to permit both contiguous and interlaced 
    /// values for points, normals, textures, colors, and curvature.
    /// The PNTCK array should must have a miniumum of 
    /// (ON_SubDMeshFragment::DoublesPerVertex * vertex_capacity * sizeof(double))
    /// bytes and begin on a double aligned address.
    /// </remarks>
    DoublesPerVertex = 12
  };

  /*
  Parameters:
    bManagedArray - [in]
      True if this instance of an ON_SubDMeshFragment will manage the PNTCK_array
      and PNTCK_array = new(std::nothrow) double[ON_SubDMeshFragment::DoublesPerVertex * vertex capacity].
      Otherwise an external agent is responsible for managing the PNTCK_array memory.
    vertex_capacity[] - [in]
      Maximum number of vertices this fragment can hold.
      Must be 0 or >= 4 and <= ON_SubDMeshFragment::MaximumVertexCount.
    PNTKC_array[] - [in]
      When PNTKC_array is not nullptr (typical), it is an array of
      (ON_SubDMeshFragment::DoublesPerVertex * vertex_capacity * sizeof(double))
      bytes that begins on a double aligned address. When pNTKC_array is not nullptr,
      Something besides this  particular instance of ON_SubDMeshFragment is managing the PNTKC_array.
      The array provides storage for the fragments m_P[], n_N[], m_T[], m_K[], and m_C[]
      arrays. This approach is taken to provide efficient and fast memory managment of
      large sets of fragments.

      If PNTCK_array is nullptr, then it is allocated inside Internal_LayoutArrays()
      and calling this->DeleteManagedArrays() will deallocate it. 
      This approach is used in odd situations, is uncommon, and the caller must
      call this->DeleteManagedArrays() at an appropriate time.
  */
  void Internal_LayoutArrays(
    size_t vertex_capacity,
    double* PNTKC_array
  );

  enum : unsigned short
  {
    /// <summary>
    /// Vertex count = (m_vertex_count_etc & EtcMask)
    /// Vertex capacity = (m_vertex_capacity_etc & EtcMask)
    /// These are the counts and capacities of the m_P[]/m_N[]/m_T[]/m_C[] arrays the pointer
    /// is not nullpr and the corresponding m_P_stride/m_N_stride/m_T_stride/m_C_stride > 0.
    /// </summary>
    ValueMask = 0x1FFF, // maximum vertex count and capacity

    /// <summary>
    /// The use of the 3 bits in (m_vertex_count_etc & EtcMask) and 3 bits in (m_vertex_capacity_etc & EtcMask)
    /// are described in the enum values below.
    /// </summary>
    EtcMask = 0xE000,

    /// <summary>
    /// This bit is on m_vertex_count_etc.
    /// Set means 4 m_ctrlnetP[] points are set and the m_ctrlnetT[]/m_ctrlnetC[] 
    /// are set if m_T[]/m_C[] is set. 
    /// </summary>
    EtcControlNetQuadBit = 0x8000,

    /// <summary>
    /// This bit is on m_vertex_count_etc.
    /// Set means m_T[] contains set values.
    /// </summary>
    EtcTextureCoordinatesExistBit = 0x4000,
    
    /// <summary>
    /// This bit is on m_vertex_capacity_etc.
    /// Set means m_C[] contains set values.
    /// </summary>
    EtcColorsExistBit = 0x2000,

    /// <summary>
    /// This bit is on m_vertex_capacity_etc.
    /// Set means m_K[] contains set values.
    /// </summary>
    EtcCurvaturesExistBit = 0x4000,

    /// <summary>
    /// This bit is on m_vertex_capacity_etc.
    /// Set means the memory for the m_P[], m_N[], m_T[], and m_C[] arrays is managed by this class as a single
    /// allocation.
    /// m_P = new(std::nothrow) double[ON_SubDMeshFragment::DoublesPerVertex * point capacity] and 
    /// m_N[], m_T[], m_C[], and m_K[] point into this allocation.
    /// </summary>
    EtcManagedArraysBit = 0x8000,
  };
  mutable unsigned short m_vertex_count_etc; // count value and 3 et cetera status bits
  mutable unsigned short m_vertex_capacity_etc; // capacity value and 3 et cetera status bits

  static void Internal_Set3dPointArrayToNan(double* a, size_t a_count, size_t a_stride);

private:
  // corners for control net display in grid order (counter-clockwise quad order must swap [2] and[3])
  double m_ctrlnetP[4][3];

  // Normal used for shading the control net display in grid order.
  double m_ctrlnetN[3];


public:
  /*
  Parameters:
    grid_corner_index - [in]
      grid side N is between corner index N and corner index (N+1)%4.
  Returns:
    Texture coordinate at that corner.
  Remarks:
    For partial fragments (IsFaceCornerFragment() = true), grid_corner_index = 2 is the only
    corner that corresponds to a SubD vertex.
    For partial fragments (IsFaceCornerFragment() = true), grid_side_index = 1 and grid_side_index = 2
    correspond to half of original SuD edges.
  */
  const ON_3dPoint TextureCoordinateCorner(
    unsigned int grid_corner_index
  ) const;

private:
  // The fragment's current corner texture coordinates in grid order.
  // These can be from ON_SubDFace pack rectangles, ON_SubDFace custom texture points,
  // a texture mapping, or any other values rendering code deems desirable.
  // When a texture mapping evaluatior is not involved, they are typically
  // used to generate the fragment's texture coordinates by interpolation.
  //  m_ctrlnetT[0]
  //  m_ctrlnetT[1]
  //  m_ctrlnetT[2]
  //  m_ctrlnetT[3]
  mutable double m_ctrlnetT[4][3]; 

  // Corner principal curvatures in grid order.
  mutable ON_SurfaceCurvature m_ctrlnetK[4];

  // Corner vertex colors in grid order.
  mutable ON_Color m_ctrlnetC[4];

private:
  // When an ON_SubDFace is a quad, there is a single ON_SubDMeshFragment for the face
  // and ON_SubDMeshFragment.m_pack_rect are the corners of the quad face's pack rect in
  // ON_SubDMeshFragment gid order.
  // When an ON_SubDFace is an N-gon with N !+ 4, there are N ON_SubDMeshFragments for the face
  // and ON_SubDMeshFragment.m_pack_rect are corners of a subrect of the face's pack rect
  // in ON_SubDMeshFragment gid order.
  // The m_pack_rect[] points are in grid order. If the parent ON_SubDFace pack rect is rotated,
  // then "lower/upper" and "left/right" are with the rotation applied and hence a lower/left coordinate
  // may be greater than an upper/right coordinate value.
  //  m_pack_rect[0] "lower left"
  //  m_pack_rect[1] "lower right"
  //  m_pack_rect[2] "upper left"
  //  m_pack_rect[3] "upper right"
  double m_pack_rect[4][2]; // NOT a mutable property

public:
  /*
  Parameters:
    grid_corner_index - [in]
      grid side N is between corner index N and corner index (N+1)%4.
  Returns:
    Pack rect corner point.
  Remarks:
    For partial fragments (IsFaceCornerFragment() = true), grid_corner_index = 2 is the only
    corner that corresponds to a SubD vertex.
    For partial fragments (IsFaceCornerFragment() = true), grid_side_index = 1 and grid_side_index = 2
    correspond to half of original SuD edges.
  */
  const ON_2dPoint PackRectCorner(
    unsigned int grid_corner_index
  ) const;

  const ON_2dPoint PackRectCenter() const;

  void SetPackRectCornersForExperts(
    bool bGridOrder,
    const ON_2dPoint fragment_pack_rect_corners[4]
  );

  /*
  Description:
    Clears the pack rectangle.
  Remarks:
    Does not change the value of ON_SubDFace::PackId() or ON_SubDFace::TextureCoordinateType()
    Use ON_SubDFace::ClearPackId() to clear the pack id.
  */
  void ClearPackRect();

  /*
  Description:
    This functions sets the pack rect corners on fragments used to render
    quad and 3-gon ON_SubDFaces.
    When an ON_SubDFace is a quad, it is rendered with one ON_SubDMeshFragment.
    When an ON_SubDFace is a 3-gon, it is rendered with three ON_SubDMeshFragments.
  Remarks:
    It is critical that m_face_fragment_count and m_face_fragment_index be set
    correctly before calling this function.
    A ON_SubDMeshFragment used to render a quad ON_SubDFace has
    m_face_fragment_count = 1 and m_face_fragment_index = 0.
    A ON_SubDMeshFragment used to render a 3-gon ON_SubDFace has
    m_face_fragment_count = 3 and m_face_fragment_index = 0, 1 or 2.
  */
  void SetQuadOr3gonFaceFragmentPackRectCorners(
    bool bGridOrder,
    const ON_2dPoint face_pack_rect_corners[4]
  );

  /*
  Description:
    This functions sets the pack rect corners on fragments used to render
    n-gon ON_SubDFaces when n >= 5.
    When an ON_SubDFace is an n-gon, it is rendered with n ON_SubDMeshFragments.
  Parameters:
    bGridOrder = [in]
      Order for face_pack_rect_corners[].
    face_texture_coordinate_corners - [in]
      The points returned by ON_SubDFace::PackRectCorner(bGridOrder, i)
    face_pack_rect_size - [in]
      The n-gon face's ON_SubDFace::PackRectSize() value.
    ngon_grid_size - [in]
    ngon_sub_pack_rect_size - [in]
    ngon_sub_pack_rect_delta - [in]
      These three parameters are values from ON_SubDFace::GetNgonSubPackRectSizeAndDelta().
      ngon_grid_size, ngon_sub_pack_rect_size, and ngon_sub_pack_rect_delta are identical
      for all the ON_SubDMeshFragments used to render the n-gon face. The value of
      m_face_fragment_index determines which sub pack rect is assigned to each of
      the n ON_SubDMeshFragments use to render the n-gon face.
  Remarks:
    It is critical that m_face_fragment_count and m_face_fragment_index be set
    correctly before calling this function.
    A ON_SubDMeshFragment used to render an n-gon ON_SubDFace has
    m_face_fragment_count = n and m_face_fragment_index = 0, ..., n-1.
  */
  void SetNgonFaceFragmentPackRectCorners(
    bool bGridOrder,
    const ON_2dPoint face_pack_rect_corners[4],
    ON_2dVector face_pack_rect_size,
    ON_2udex ngon_grid_size,
    ON_2dVector ngon_sub_pack_rect_size,
    ON_2dVector ngon_sub_pack_rect_delta
  );

  /*
  Description:
    This functions gets the pack rect corners on fragments used to render 3-gon ON_SubDFaces.
    When an ON_SubDFace is an 3-gon, it is rendered with 3 ON_SubDMeshFragments.
  Parameters:
    bFacePackRectGridOrder - [in]
      Order for face_pack_rect_corners[].
    face_pack_rect_corners - [in]
      The points returned by ON_SubDFace::PackRectCorner(bGridOrder, i)
    fragment_index - [in]
      0 <= ngon_fragment_index < 3
    bFragmentPackRectGridOrder - [in]
      Order for face_pack_rect_corners[].
    fragment_pack_rect_corners - [out]
  */
  static bool Get3gonFaceFragmentPackRectCorners(
    bool bFaceGridOrder,
    const ON_2dPoint face_pack_rect_corners[4],
    unsigned int fragment_index,
    bool bFragmentGridOrder,
    ON_2dPoint fragment_pack_rect_corners[4]
  );

  /*
  Description:
    This functions gets the pack rect corners for fragments used to render
    n-gon ON_SubDFaces when n >= 5.
    When an ON_SubDFace is an n-gon, it is rendered with n ON_SubDMeshFragments.
  Parameters:
    ngon_fragment_index - [in]
      0 <= ngon_fragment_index < ngon_edge_count
    bGridOrder - [in]
      Order for face_pack_rect_corners[].
    face_pack_rect_corners - [in]
      The points returned by ON_SubDFace::PackRectCorner(bGridOrder, i)
    face_pack_rect_size - [in]
      The n-gon face's ON_SubDFace::PackRectSize() value.
    ngon_grid_size - [in]
    ngon_sub_pack_rect_size - [in]
    ngon_sub_pack_rect_delta - [in]
      These three parameters are values from ON_SubDFace::GetNgonSubPackRectSizeAndDelta().
      ngon_grid_size, ngon_sub_pack_rect_size, and ngon_sub_pack_rect_delta are identical
      for all the ON_SubDMeshFragments used to render the n-gon face. The value of
      m_face_fragment_index determines which sub pack rect is assigned to each of
      the n ON_SubDMeshFragments use to render the n-gon face.
    fragment_pack_rect_corners - [out]
  */
  static bool GetNgonFaceFragmentPackRectCorners(
    unsigned int ngon_edge_count,
    unsigned int ngon_fragment_index,
    bool bGridOrder,
    const ON_2dPoint face_pack_rect_corners[4],
    ON_2dVector face_pack_rect_size,
    ON_2udex ngon_grid_size,
    ON_2dVector ngon_sub_pack_rect_size,
    ON_2dVector ngon_sub_pack_rect_delta,
    ON_2dPoint fragment_pack_rect_corners[4]
  );

public:
  ///////////////////////////////////////////////////////////////////////////////////
  //
  // 3-dimensional grid vertex points
  //
  // Depending on the strides, m_P[], m_N[], and m_T[] can be separate or interlaced.
  //
  // The stride m_P_stride and memory m_P references is managed by some other class or function.
  // Never modify m_P_stride, m_P, or the values in m_P.
  // Use m_grid functions to get point indices and quad face indices.
  double* m_P; // surface points
  size_t m_P_stride; // stride between points for m_P[] as an array of 8 byte doubles (so 0 or >= 3)
  const double* PointArray(ON_SubDComponentLocation subd_appearance)const;
  size_t PointArrayStride(ON_SubDComponentLocation subd_appearance)const;
  unsigned PointArrayCount(ON_SubDComponentLocation subd_appearance) const;

public:

  /*
  Description:
    Create a one quad fragment with 
    m_P = this->m_ctrlnetP[], m_P_stride = 3
    m_N = this->m_ctrlnetN, m_N_stride = 0
    m_T = this->m_ctrlnetT, m_T_stride = 3
    NOTE WELL: 
    1) "this" must remain in scope and unchanged while the returned value
    is used because the returned value references memory in thism_ctrlnetX[] arrays.
    2) The next/prev pointers on the returned fragment are copied from this,
    but the returned value is not reciprocally referenced by next/prev in the linked list.
  Returns:
    A control net quad fragment that can be used locally when the SubDAppearance
    is ON_SubDComponentLocation::ControlNet.
    The points, normals, and texture_coordinates of the returned fragment
    are the control net quad points, normals, and texture coordinates
    of this fragment. m_grid is a single quad grid.
  */
  const ON_SubDMeshFragment ControlNetQuadFragmentForExperts() const;

  /*
  Parameters:
    bGridOrder - [in]
      If true, then points are returned in fragment grid order.
      Otherwise, points are returned in counter-clockwise quad order.
    quad_points - [out]
    quad_normal - [out]
  */
  bool GetControlNetQuad(
    bool bGridOrder,
    ON_3dPoint quad_points[4],
    ON_3dVector& quad_normal
  ) const;

  const ON_3dPoint ControlNetQuadPoint(
    bool bGridOrder,
    unsigned point_index
  ) const;

  /*
  Parameters:
    bGridOrder - [in]
      If true, then points are returned in fragment grid order.
      Otherwise, points are returned in counter-clockwise quad order.
    quad_points - [in]
  */
  void SetControlNetQuad(
    bool bGridOrder,
    const ON_3dPoint quad_points[4],
    ON_3dVector quad_normal
  );

  ON_DEPRECATED_MSG("Use ON_SubDMeshFragment::ClearControlNetQuad()")
  void UnsetControlNetQuad();

  void ClearControlNetQuad();

  const ON_BoundingBox SurfaceBoundingBox() const;
  const ON_BoundingBox ControlNetQuadBoundingBox() const;
  const ON_BoundingBox BoundingBox(ON_SubDComponentLocation subd_appearance) const;

  void ClearSurfaceBoundingBox();


public:
  /*
  Returns:
    If grid vertex points are available, then VertexCount() is returned.
    Otherwise 0 is returned.
  */
  unsigned int PointCount() const;
  unsigned int PointCapacity() const;

  ///////////////////////////////////////////////////////////////////////////////////
  //
  // 3-dimensional grid vertex surface normals
  //
  // The m_N[] and m_P[] arrays are parallel. 
  // Depending on the strides, m_P[], m_N[], and m_T[] can be separate or interlaced.
  //
  // If m_N is not nullptr and m_N_stride>0, then m_N[] can accommodate up to m_P_capacity normals.
  // If m_N is not nullptr and m_N_stride=0, then m_N[] can accommodate a single normal (flat shaded polygon face).
  // The stride m_N_stride and memory m_N references is managed by some other class or function.
  // Never modify m_N_stride, m_N, or the values in m_N.
  // Use m_grid functions to get normal indices and quad face indices.
  // Note well: m_N_stride can be 0 when the normal is constant (control net face normal for example).
  double* m_N; // surface normals
  size_t m_N_stride; // stride between normals for m_N[] as an array of 8 byte doubles (so 0 or >= 3)
  const double* NormalArray(ON_SubDComponentLocation subd_appearance)const;
  size_t NormalArrayStride(ON_SubDComponentLocation subd_appearance)const;
  unsigned NormalArrayCount(ON_SubDComponentLocation subd_appearance) const;

public:
  /*
  Returns:
    If grid vertex surface normals are available, then VertexCount() is returned.
    Otherwise 0 is returned.
  */
  unsigned int NormalCount() const;
  unsigned int NormalCapacity() const;

  ///////////////////////////////////////////////////////////////////////////////////
  //
  // 3d vertex texture coordinates.
  //
  // Depending on the strides, m_P[], m_N[], and m_T[] can be separate or interlaced.
  //
  // If m_T is not nullptr and m_T_stride>0, then m_T[] can accommodate up to m_P_capacity textures coordinates.
  // Otherwise there are no texture coordinates.
  // Never modify m_T_stride, m_T.
  // Use m_grid functions to get texture indices and quad face indices.
  // Note well: m_T_stride can be 0 when the texture coordinate is constant (one color per face for example)
  mutable double* m_T;
  mutable size_t m_T_stride; // stride between texture points for m_T[] as an array of 8 byte doubles (so 0 or >= 3)

  const double* TextureCoordinateArray(ON_SubDComponentLocation subd_appearance)const;
  size_t TextureCoordinateArrayStride(ON_SubDComponentLocation subd_appearance)const;
  unsigned TextureCoordinateArrayCount(ON_SubDComponentLocation subd_appearance) const;   
public:
  /*
  Returns:
    If grid texture coordinates are available, then VertexCount() is returned.
    Otherwise 0 is returned.
  */
  unsigned int TextureCoordinateCount() const;
  unsigned int TextureCoordinateCapacity() const;


  /*
  Description:
    Sets the values of each fragment's m_ctrlnetT[] member.
  Parameters:
    bSetTextureCoordinates
      If true, the texture coordinate corners are used ti set the fragment's m_T[]
      values after m_ctrlnetT[] is set.
  */
  void SetTextureCoordinateCornersForExperts(
    bool bGridOrder,
    const ON_3dPoint fragment_texture_coordinate_corners[4],
    bool bSetTextureCoordinates
  ) const;

  /*
  Description:
    This functions sets the texture coordinates on fragments used to render
    quad and 3-gon ON_SubDFaces.
    A quad ON_SubDFace is rendered with one ON_SubDMeshFragment.
    A 3-gon ON_SubDFace is rendered with three ON_SubDMeshFragments.
  Remarks:
    It is critical that m_face_fragment_count and m_face_fragment_index be set
    correctly before calling this function.
    A ON_SubDMeshFragment used to render a quad ON_SubDFace has
    m_face_fragment_count = 1 and m_face_fragment_index = 0.
    A ON_SubDMeshFragment used to render a 3-gon ON_SubDFace has
    m_face_fragment_count = 3 and m_face_fragment_index = 0, 1 or 2.
  */
  void SetQuadOr3gonFaceFragmentTextureCoordinateCorners(
    bool bGridOrder,
    const ON_3dPoint face_texture_coordinate_corners[4],
    bool bSetTextureCoordinates
  ) const;

  /*
  Description:
    When an ON_SubDFace is an n-gon with n >= 5, it is rendered with n ON_SubDMeshFragments.
    This functions sets the texture coordinates on those fragments.    
  Parameters:
    bGridOrder = [in]
      Order for face_pack_rect_corners[].
    face_texture_coordinate_corners - [in]
      The points returned by ON_SubDFace::TextureCoordinateCorner(bGridOrder, i, false)
    face_pack_rect_size - [in]
      The n-gon face's ON_SubDFace::PackRectSize() value.
    ngon_grid_size - [in]
    ngon_sub_pack_rect_size - [in]
    ngon_sub_pack_rect_delta - [in]
      These three parameters are values from ON_SubDFace::GetNgonSubPackRectSizeAndDelta().
      ngon_grid_size, ngon_sub_pack_rect_size, and ngon_sub_pack_rect_delta are identical
      for all the ON_SubDMeshFragments used to render the n-gon face. The value of
      m_face_fragment_index determines which sub pack rect is assigned to each of
      the n ON_SubDMeshFragments use to render the n-gon face.
  Remarks:
    It is critical that m_face_fragment_count and m_face_fragment_index be set
    correctly before calling this function.
    A ON_SubDMeshFragment used to render an n-gon ON_SubDFace has
    m_face_fragment_count = n and m_face_fragment_index = 0, ..., n-1.
  */
  void SetNgonFaceFragmentTextureCoordinateCorners(
    bool bGridOrder,
    const ON_3dPoint face_texture_coordinate_corners[4],
    ON_2dVector face_pack_rect_size,
    ON_2udex ngon_grid_size,
    ON_2dVector ngon_sub_pack_rect_size,
    ON_2dVector ngon_sub_pack_rect_delta,
    bool bSetTextureCoordinates
  ) const;

  /*
  Description:
    Get the texture coordinate corners.
  Parameters:
    bGridOrder - [in]
      If true, then points are returned in fragment grid order.
      Otherwise, points are returned in counter-clockwise quad order.
    texture_coordinate_corners - [out]
  */
  bool GetTextureCoordinteCorners(
    bool bGridOrder,
    ON_3dPoint texture_coordinate_corners[4]
  ) const;

  /*
  Description:
    Set the texture coordinates in m_T[] from the values in m_ctrlnetT[].
  */
  void SetTextureCoordinatesFromCorners() const;

  /*
  Description:
    Set the texture coordinates in m_T[] from the values in m_pack_rect[].
  */
  void SetPackedTextureCoordinates() const;

  /*
  Description:
    Set the this fragments texture coordinates in m_T[] to cover (0,1)x(0,1)
  */
  void SetUnpackedTextureCoordinates() const;

private:
  void Internal_SetTextureCoordinatesFromCorners(
    const double* corner0,
    const double* corner1,
    const double* corner2,
    const double* corner3,
    double default_coordinate_value,
    int corner_dim
  ) const;

private:
  ///////////////////////////////////////////////////////////////////////////////////
  //
  // Principal curvatures
  //
  // If m_K is not nullptr and m_K_stride>0, then m_K[] can accommodate up to m_P_capacity
  // principal curvatures (two doubles k1, k2). Otherwise there are no principal curvatures.
  // At exceptional points, the curvature values may be nan.
  // Never modify m_K_stride and the m_K pointer.
  // Use m_grid functions to get principal curvature indices and quad face indices.
  //
  // NOTE WELL:
  //  m_K_stride is the number of ON_SurfaceCurvature elements between m_K[i] and m_K[i+1].
  //  This is different than m_P_stride, m_N_stride, and m_T_stride, which count 
  //  the number of doubles between successive 
  //  points/normals/texture points in m_P[]/m_N[]/m_T[].
  //  
  //  If m_K[] is interlaced, the number of bytes between successive elements of m_K[] must be a multiple of 
  //  sizeof(ON_SurfaceCurvature)  because m_K_stride is a ON_SurfaceCurvature element stride.
  mutable ON_SurfaceCurvature* m_K;
  mutable size_t m_K_stride; // stride for m_K[] as an array of 16 byte ON_SurfaceCurvature elements (so 0 or >= 1).

public:
  /*  
  Returns:
    If the grid has set curvatures, then VertexCount() is returned.
    Otherwise 0 is returned.
  Remarks:
    Use CurvatureCapacity() to get capacity of the m_K[] array (set or unset).
    This function return the number of set curvatures.
  */
  unsigned int CurvatureCount() const;

  /*
  Returns:
    If the grid has memory to store curvatures, then VertexCapacity() is returned.
    Otherwise 0 is returned.
  Remarks:
    Use CurvatureCount() > 0 to determine if the curvature values are actually set.
  */
  unsigned int CurvatureCapacity() const;

  /// <param name="subd_appearance">
  /// Specifies which array (surface points or control net corners)
  /// </param>
  /// <returns>If curvature are set, a pointer to the curvatures in the specified array.
  /// Otherwise, nullptr is returned.
  /// </returns>
  const ON_SurfaceCurvature* CurvatureArray(ON_SubDComponentLocation subd_appearance)const;

  /// <param name="subd_appearance">
  /// Specifies which array (surface points or control net corners)
  /// </param>
  /// <returns>If curvature are set, the number of curvatures in the specified array.
  /// Otherwise, 0 is returned.
  /// </returns>  
  unsigned CurvatureArrayCount(ON_SubDComponentLocation subd_appearance) const;


  size_t CurvatureArrayStride(ON_SubDComponentLocation subd_appearance) const;

  /*
  Description:
    Get the principal surface curvature for the specified fragment grid point.
  Parameters:
    grid2dex_i - [in]
      0 <= grid2dex_i < m_grid.SidePointCount()
    grid2dex_j - [in]
      0 <= grid2dex_j < m_grid.SidePointCount()
  Returns:
    The principal surface curvature for the specified fragment grid point.
    When curvatures are not set, ON_SurfaceCurvature::Nan is returned.
  */
  const ON_SurfaceCurvature VertexCurvature(
    unsigned grid2dex_i,
    unsigned grid2dex_j
  ) const;

  const ON_SurfaceCurvature VertexCurvature(
    ON_2udex grid2dex
  ) const;

  const ON_SurfaceCurvature VertexCurvature(
    unsigned grid_point_index
  ) const;

  /*
    Call ClearCurvatures() if the fragment points are changed and any
    existing curvature values are now invalid.
  */
  void ClearCurvatures() const;


  /*
  Returns:
    True if the curvatures exist bit is set. This bit is used for
    control net and vertex values.
  Remarks:
    Use CurvatureCount() to determine if vertices have set curvature values.
  */
  bool CurvaturesExistForExperts() const;

  /*
  Parameters:
    bSetCurvaturesExist - [in]
      True if curvatures exist.
      False vertex curvatures do not exist or are no longer valid.
      Note that SetCurvaturesExist(false) and ClearCurvatures()
      are two ways to do the same thing.
  Remarks:
    When curvatures exist, CurvatureCount() = CurvatureCapacity().
    When curvatures do not exist, CurvatureCount() = 0.
    Typically 
  */
  void SetCurvaturesExistForExperts(bool bSetCurvaturesExist) const;


  /*
  Description:
    Computes normal curvature values for this fragment. Evaluation
    points are uniformly spaced over the fragment to fill the N, Ku, Kv
    arrays.
  Parameters:
    sample_count - [in]
      How many samples to get in both directions.
    comb_count_params - [in]
      How many combs to get in both directions (+1 if get_first_comb is false).
    get_first_comb - [in]
      Wheter to skip combs at u = 0 and v = 0. The parameters at which to
      get the combs are the same when:
        - get_first_comb is true and comb_count is n
        - get_first_comb is false and comb_count is n
    getKu, getKv - [in]
      Should the curvature be computed along u-isos, v-isos, or both.
    P, Kuv - [out]
      Arrays of size (getKu + getKv) * sample_count * comb_count_arrays where
      Points and Curvatures along u-isos or along v-isos are stored.
      Sample (i, j) in u direction, on u-dir comb j at sample i is stored
      at index i + (j - get_first_comb ? 0 : 1) * sample_count.
      Sample (i, j) in v direction, on v-dir comb i at sample j is stored
      at index (getKu * sample_count * comb_count_arrays) + j + (i - get_first_comb ? 0 : 1) * sample_count.
      Direction u (indexed with i) refers to the Fragment's grid 1st index
      (from face->Vertex(0) to face->Vertex(1)).
      Direction v (indexed with j) refers to the Fragment's grid 2nd index
      (from face->Vertex(0) to face->Vertex(3)).
      comb_count_arrays = comb_count_params - get_first_comb ? 1 : 0
  Returns:
    Number of points sampled
  */
  unsigned GetNormalCurvatures(
    const unsigned sample_count,
    const unsigned comb_count_params,
    const bool get_first_comb, 
    const bool getKu,
    const bool getKv, 
    ON_SimpleArray<ON_3dPoint>* P,
    ON_SimpleArray<ON_3dVector>* Kuv
  ) const;

private:
  ///////////////////////////////////////////////////////////////////////////////////
  //
  // Per vertex colors
  //
  // Depending on the strides, m_P[], m_N[], m_T[], m_C[] and m_K[] can be separate or interlaced.
  //
  // If m_C is not nullptr and m_C_stride>0, then m_C[] can accommodate up to m_P_capacity 
  // elements.
  // Otherwise there is no per vertex false color.
  // Never modify m_C_stride, m_C.
  // Use m_grid functions to get color indices and quad face indices.
  //
  // NOTE WELL: 
  //   When m_C is interlaced with something containing doubles, m_C_stride must be 
  //   a multiple of 2 to keep the doubles 8 bytes aligned. 
  //   When m_C is not interlaced, m_C_stride is typically 1. If this is confusing,
  //   please learn more about alignment and interlacing before working on this code.
  mutable ON_Color* m_C;
  mutable size_t m_C_stride; // stride for m_C[] as an array of 4 byte ON_Color elements (so 0 or >= 1).

public:
  /*
  Returns:
    If grid vertex colors are available, then VertexCount() is returned.
    Otherwise 0 is returned.
  Remarks:
    Use ColorCapacity() to get the capacity of m_C[].
  */  /*
  Returns:
    If the grid has memory to store curvatures, then VertexCapacity() is returned.
    Otherwise 0 is returned.
  Remarks:
    Use CurvaturesExist() or CurvatureCount() to determine if the curvature values are actually set.
  */
  unsigned int ColorCount() const;

  /*
  Returns:
    If the grid has memory to store colors, then VertexCapacity() is returned.
    Otherwise 0 is returned.
  Remarks:
    Use ColorCount() > 0 to determine if the color values are actually set.
  */
  unsigned int ColorCapacity() const;

  /// <param name="subd_appearance">
  /// Specifies which array (surface points or control net corners)
  /// </param>
  /// <returns>If colors are set, the number of curvatures in the specified array.
  /// Otherwise, 0 is returned.
  /// </returns>  
  const ON_Color* ColorArray(ON_SubDComponentLocation subd_appearance)const;
  size_t ColorArrayStride(ON_SubDComponentLocation subd_appearance)const;

  /// <param name="subd_appearance">
  /// Specifies which array (surface points or control net corners)
  /// </param>
  /// <returns>If colors are set, the number of colors in the specified array.
  /// Otherwise, 0 is returned.
  /// </returns>  
  unsigned ColorArrayCount(ON_SubDComponentLocation subd_appearance) const;

  /*
  Description:
    Get the per vertex color assigned to the specified fragment grid point.
  Parameters:
    grid2dex_i - [in]
      0 <= grid2dex_i < m_grid.SidePointCount()
    grid2dex_j - [in]
      0 <= grid2dex_j < m_grid.SidePointCount()
  Returns:
    The colo for the specified fragment grid point.
    When per vertex colors are not set, ON_Color::Unset is returned.
  */
  const ON_Color VertexColor(
    unsigned grid2dex_i,
    unsigned grid2dex_j
  ) const;

  const ON_Color VertexColor(
    ON_2udex grid2dex
  ) const;

  const ON_Color VertexColor(
    unsigned grid_point_index
  ) const;

  /*
  Call ClearColors() if vertex colors do not exist or are no longer valid.
  */
  void ClearColors() const;

  /*
  Returns:
    True if vertex color exist bit is set. This bit is used
    for control net and color array setting.
  Remarks:
    Use ColorCount() to determine if vertex colors are set.
  */
  bool ColorsExistForExperts() const;

  /*
  Parameters:
    bSetColorsExist - [in]
      True if vertex colors exist.
      False vertex colors do not exist or are no longer valid.
      SetColorsExist(false) and ClearColors() are two ways
      to do the same thing.
  */
  void SetColorsExistForExperts(bool bSetColorsExist) const;

  /*
  Description:
    Set all vertex colors in m_C[] to color.
  Parameters:
    color - [in]
  */
  bool SetColors(
    ON_Color color
  ) const;

  /*
  Description:
    Set the vertex colors in m_C[] from a callback function.
  Parameters:
  */
  bool SetColorsFromCallback(
    const ON_MappingTag& fragment_colors_mapping_tag,
    const ON_SubD& subd,
    ON__UINT_PTR callback_context,
    const ON_Color(*color_callback)(
      ON__UINT_PTR callback_context,
      const ON_MappingTag& mapping_tag,
      const ON_SubD& subd,
      ON_SubDComponentPtr cptr,
      const ON_3dPoint& P,
      const ON_3dVector& N,
      const ON_3dPoint& T,
      const ON_SurfaceCurvature& K
      )
  )const;

public:

  // Normalized grid parameters useful for appling a texture to the grid are available
  // from m_grid functions.
  
  // Information to resolve m_P[], m_N[], and m_T[] into a grid of NxN quads.
  ON_SubDMeshFragmentGrid m_grid;

  const ON_SubDMeshFragmentGrid& Grid(ON_SubDComponentLocation subd_appearance) const;

  // 3d bounding box of grid vertex points.
  ON_BoundingBox m_surface_bbox;
public:
  /*
  Parameters:
    display_density - [in]
      Determines grid size
    bCurvatureArray - [in]
      true to include room for the m_K[] array.
  Returns:
    Amount of memory needed for the fragment, the m_P[], m_N[], m_T[], m_C[], and m_K[] arrays.
  */
  static size_t SizeofFragment(
    unsigned int display_density
  );

public:
  void Dump(ON_TextLog& text_log) const;
};

/// <summary>
/// ON_SubDManagedMeshFragment is a legacy class that should not be used.
/// </summary>
class ON_CLASS ON_SubDManagedMeshFragment : public ON_SubDMeshFragment
{
public:
  ON_SubDManagedMeshFragment() ON_NOEXCEPT;
  ~ON_SubDManagedMeshFragment() ON_NOEXCEPT;
  ON_SubDManagedMeshFragment(const ON_SubDManagedMeshFragment&) ON_NOEXCEPT;
  ON_SubDManagedMeshFragment& operator=(const ON_SubDManagedMeshFragment&) ON_NOEXCEPT;

  static ON_SubDManagedMeshFragment Create(const ON_SubDMeshFragment& src) ON_NOEXCEPT;

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_SubDManagedMeshFragment( ON_SubDManagedMeshFragment&& ) ON_NOEXCEPT;

  // rvalue assignment operator
  ON_SubDManagedMeshFragment& operator=( ON_SubDManagedMeshFragment&& ) ON_NOEXCEPT;
#endif

  void Clear() ON_NOEXCEPT;

  void Destroy() ON_NOEXCEPT;

  bool ReserveCapacity(
    unsigned int mesh_density
    ) ON_NOEXCEPT;

private:
  void CopyHelper(const ON_SubDMeshFragment& src);

  size_t m_obsolete1 = 0;
  ON__UINT_PTR m_obsolete2 = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDMesh
//

/// <summary>
/// ON_SubDMesh is used to store a high density traditional quad mesh
/// of a SubD surface or a mesh of a SubD control net. 
/// In general, is is better to use an ON_SubDMeshFragmentIterator(subd)
/// that iterates the ON_MeshFragments cached on the ON_SubD. 
/// </summary>
class ON_CLASS ON_SubDMesh
{
public:
  static const ON_SubDMesh Empty;

  /*
  Returns:
    A runtime number that changes if the limit mesh content changes.
    0: Empty limit mesh
  Remarks:
    This is a runtime number. It is not saved in archives and begins
    at 1 with each new runtime instance of the opennurbs library.
  */
  ON__UINT64 ContentSerialNumber() const;



  /*
  Description:
  Parameters:
    destination_mesh - [in]
      If destination_mesh is not nullptr, then the returned mesh
      will be store here. Otherwise the returned mesh will be 
      allocated with a call to new ON_Mesh().
  Returns:
    If this limit mesh is not empty, an ON_Mesh representation of this limit mesh.
    Otherwise, nullptr.
  */
  ON_Mesh* ToMesh(
    ON_Mesh* destination_mesh
  ) const;


  /*
  Description:
  Parameters:
    mesh_density - [in]
      Larger numbers return denser meshes.
    destination_mesh - [in]
      If destination_mesh is not nullptr, then the returned mesh
      will be store here. Otherwise the returned mesh will be 
      allocated with a call to new ON_Mesh().
  Returns:
    If this limit mesh is not empty, an ON_Mesh representation of this limit mesh.
    Otherwise, nullptr.
  */
  ON_Mesh* ToMesh(
    unsigned int mesh_density,
    ON_Mesh* destination_mesh
  ) const;

  /*
  Description:
  Parameters:
    frit - [in]
      A fragment iterator from an ON_SubDMesh or ON_SubD.
    mesh_density - [in]
      Larger numbers return denser meshes.
      MinimumMeshDensity() <= mesh_density <= MaximumMeshDensity()
    destination_mesh - [in]
      If destination_mesh is not nullptr, then the returned mesh
      will be store here. Otherwise the returned mesh will be 
      allocated with a call to new ON_Mesh().
  Returns:
    If this limit mesh is not empty, an ON_Mesh representation of this limit mesh.
    Otherwise, nullptr.
  */
  static ON_Mesh* ToMesh(
    class ON_SubDMeshFragmentIterator& frit,
    unsigned int mesh_density,
    ON_Mesh* destination_mesh
  );

  ON_SubDMesh() = default;
  ~ON_SubDMesh() = default;
  ON_SubDMesh(const ON_SubDMesh&) = default;
  ON_SubDMesh& operator=(const ON_SubDMesh&) = default;

  
#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_SubDMesh( ON_SubDMesh&& ) ON_NOEXCEPT;
  // rvalue assignment operator
  ON_SubDMesh& operator=( ON_SubDMesh&& );
#endif

  ON_SubDMesh Copy() const;

  ON_SubDMesh& CopyFrom(
    const ON_SubDMesh& src
    );

  static void Swap(
    ON_SubDMesh& a,
    ON_SubDMesh& b
    );

  bool Transform(
    const ON_Xform& xform
    );

  bool Transform(
    bool bKeepCurvatures,
    bool bKeepTextures,
    bool bKeepColors,
    const ON_Xform& xform,
    const ON_Xform& xformNormals,
    const ON_Xform& xformCurvatures,
    const ON_Xform& xformTextures,
    const ON_Xform& xformColors
    );

  ON_DEPRECATED_MSG("AbsoluteSubDDisplayDensity")
  unsigned int DisplayDensity() const;

  /*
  Returns:
    The absolute subd display density used to create this display mesh.
  */
  unsigned int AbsoluteSubDDisplayDensity() const;
  
  ON_SubDDisplayParameters DisplayParameters() const;

  unsigned int FragmentCount() const;
  const ON_SubDMeshFragment* FirstFragment() const; // linked list of mesh fragments

  /*
  Parameters:
    face - [in]
  Returns:
    The first fragment for this face or nullptr if none is found.
    If the face is not a quad, then there will be multiple partial
    fragments for the face and this is the first on. The others
    follow using m_next_fragment.
  */
  const ON_SubDMeshFragment* FaceFragment(
  const class ON_SubDFace* face
  ) const;

  /*
  Description:
    Get the limit surface point location and normal for 
    the face's center from the limit mesh grid.
  Parameters:
    face - [in]
    P - [out]
      P = limit surface location or ON_3dPoint::NanPoint if not available.
    N - [out]
      N = limit surface unit normal or ON_3dVector::NanVector if not available.
  Returns:
    True if the point and normal were set from the limit mesh fragment.
    False if the limit mesh fragment was not found and nan values were returned.
  */
  bool GetFaceCenterPointAndNormal(
    const class ON_SubDFace* face,
    double* P,
    double* N
  ) const;

  /*
  Description:
    Get the limit surface point location and normal for 
    the edge's midpoint from the limit mesh grid.
  Parameters:
    edge - [in]
    edge_face_index - [in]
      Index of the face to use for the normal. If the edge is a crease, then
      each attached face may have a different normal. Pass 0 when in doubt.
    P - [out]
      P = limit surface location or ON_3dPoint::NanPoint if not available.
    N - [out]
      N = limit surface unit normal or ON_3dVector::NanVector if not available.
  Returns:
    True if the point and normal were set from the limit mesh fragment.
    False if the limit mesh fragment was not found and nan values were returned.
  */
  bool GetEdgeCenterPointAndNormal(
    const class ON_SubDEdge* edge,
    unsigned int edge_face_index,
    double* P,
    double* N
  ) const;
  
  /*
  Description:
    If the subd referenced by m_subd_ref changes, then call
    Update to update the limit mesh. 
  */
  bool Update(
    bool bShareUpdate
    );

  /*
  Description:
    The ON__INT_PTRs in the tree are const ON_SubDMeshFragment* pointers.
  */
  const ON_RTree& FragmentTree() const;

  /*
  Description:
    Clears everything.
  */
  void Clear();

  /*
  Description:
    If the tree is not needed and memory resources are tight, then call ClearTree()
    to remove the RTree.
  */
  void ClearTree();

  bool IsEmpty() const;

  ON_BoundingBox BoundingBox() const;

  bool GetTightBoundingBox(
    ON_BoundingBox& bbox,
    bool bGrowBox,
    const ON_Xform* xform
    ) const;

  ON_SubDRef SubDRef() const;
  ON_SubD SubD() const;

public:
  /*
  Description:
    Pretend this function and ON_SubDMeshImpl do not exist.
  Returns:
    Something that you are pretending does not exist.
  Remarks:
    It is intentional that the definition of ON_SubDMeshImpl class is not
    available in the opennurbs library interface (not in a header file).
    The size and design of ON_SubDMeshImpl will change constantly.
    If you choose to hack and whack so you can dereference an
    ON_SubDMeshImpl* pointer, then your code will crash unpredictably.
  */
  class ON_SubDMeshImpl* SubLimple() const;
  unsigned int SubLimpleUseCount() const;

private:
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 ) 
  friend class ON_SubDMeshImpl;
  // C4251: ... needs to have dll-interface to be used by clients of class ...
  // m_impl_sp is private and all code that manages m_impl_sp is explicitly implemented in the DLL.
private:
  std::shared_ptr< class ON_SubDMeshImpl > m_impl_sp;
#pragma ON_PRAGMA_WARNING_POP

};


class ON_CLASS ON_SubDSectorSurfacePoint
{
public:
  // For performance reasons, the default the data members are
  // not initialized by the default constructor
  // Use = ON_SubDSectorSurfacePoint::Unset when initialization is required
  static const ON_SubDSectorSurfacePoint Unset; // all doubles are ON_UNSET_VALUE, all pointer are nullptr
  static const ON_SubDSectorSurfacePoint Nan;   // all doubles are ON_DBL_QNAN, all pointer are nullptr
  static const ON_SubDSectorSurfacePoint Zero;  // all doubles are 0.0, all pointer are nullptr
  
  /*
  Returns:
    true if m_limitP[0] is ON_UNSET_VALUE.
    false otherwise.
  */
  bool IsUnset() const;

  /*
  Returns:
    true if m_limitP[0] is a nan (like ON_DBL_QNAN).
    false otherwise.
  */
  bool IsNan() const;

  /*
  Returns:
    true if all coordinates are zero.
    false otherwise.
  */
  bool IsZero() const;

  /*
  Returns:
    true if all coordinates are valid doubles and the tangents and normal have at least
    one nonzero coordinate.
    false otherwise.
  */
  bool IsSet(
    bool bUndefinedNormalIsPossible
  ) const;

  bool Transform(
    const ON_Xform& xform
    );

  bool Transform(
    const ON_Xform& xform,
    const ON_Xform& xformNormals
  );

  /// <summary>
  /// Get a limit surface point.
  /// </summary>
  /// <returns>Limit surface point.</returns>
  const ON_3dPoint Point() const;

  /// <summary>
  /// Get a limit surface normal.
  /// </summary>
  /// <returns>Limit surface normal vector.</returns>
  const ON_3dVector Normal() const;

  /// <summary>
  /// Get a limit surface tangent vector.
  /// </summary>
  /// <param name="tangent_index">0 or 1</param>
  /// <returns>Limit surface tangent vector.</returns>
  const ON_3dVector Tangent(int tangent_index) const;

  // limit surface point, tangents and normal
  double m_limitP[3];  // point
  double m_limitT1[3]; // first unit tangent
  double m_limitT2[3]; // second unit tangent
  double m_limitN[3];  // unit normal (same direction as m_limitT1 x m_limitT2)

  // When an ON_SubDVertex has a single sector, (ON_SubDVertex.IsSingleSectorVertex() is true),
  // these pointers are both null.
  // When an ON_SubDVertex has a multiple sectors, 
  // m_sector_face is the "first" face in the sector and
  // m_next_sector_limit_point is used to create a linked list.
  // (The "first" face in a sector is the one ON_SubDSectorIterator.IncrementToCrease(-1) returns.)
  const class ON_SubDSectorSurfacePoint* m_next_sector_limit_point; // nullptr for vertices with one sector
  const class ON_SubDFace* m_sector_face;                         // nullptr for vertices with one sector
};

////////////////////////////////////////////////////////////////////////////
//
// ON_SubDComponentBase
//
class ON_CLASS ON_SubDComponentBase
{
public:
  static const ON_SubDComponentBase Unset;
  
  /*
  Returns:
    True if this component is active in its parent subd or other
    relevant context.
  Remarks:
    When a component is in use, IsActive() = true. 
    If was used and then deleted, IsActive() is false.
  */
  bool IsActive() const;
    
public:
  ON_SubDComponentBase() = default;
  ~ON_SubDComponentBase() = default;
  ON_SubDComponentBase(const ON_SubDComponentBase&) = default;
  ON_SubDComponentBase& operator=(const ON_SubDComponentBase&) = default;

public:
  static int CompareId(
    const ON_SubDComponentBase* lhs,
    const ON_SubDComponentBase* rhs
  );


public:
  // The audience for this comment is anybody who wants to change the data
  // fields in ON_SubDComponentBase. Everyone else should ignore this comment.
  //   ON_SubD components come from ON_FixedSizePool and ON_SubD code
  //   uses ON_FixedSizePool.ReturnElement.  The first sizeof(void*) bytes
  //   must be a data field that is not referenced in returned elements.
  //   Since a returned element cannot have a "next level vertex",
  //   m_subd_point1 is a good data member to put first.

  // m_subd_point1 points to the next level's vertex when this component
  // has been subdivided using an algorithm like Catmull-Clark or Loop-Warren.
  const class ON_SubDVertex* m_subd_point1 = nullptr;

public:
  // The audience for this comment is anybody who wants to change the data
  // fields in ON_SubDComponentBase. Everyone else should ignore this comment.
  //   It is critical that the offset of m_id in ON_SubDComponentBase be >= sizeof(void*).
  //   ON_SubD components come from ON_FixedSizePool and ON_SubD code
  //   use ON_FixedSizePool.ElementFromId and ON_FixedSizePool.ReturnElement.
  //   Once assigned, m_id is never changed and that allows ON_SubD component
  //   indices to work.

  // Id assigned to this component. NEVER MODIFY THE m_id VALUE.  
  // It is assigned by allocators and used to find the component 
  // from an ON_COMPONENT_INDEX.
  unsigned int m_id = 0;

private:
  // The m_archive_id must be immediately after the m_id field.
  // A value of ON_UNSET_UINT_INDEX indicate the component was
  // in use and then deleted. See ON_SubDHeap Return...() functions
  // for more details.
  mutable unsigned int m_archive_id = 0;  
  
public:

  /*
  Returns:
    Subdivision level (0 to 255)
  */
  unsigned const SubdivisionLevel() const;

  /*
  Parameters:
    level - [in]
      Subdivision level (0 to 255)
  */
  void SetSubdivisionLevel(unsigned level);

  
public:
  const ON_ComponentStatus Status() const;


public:
  mutable ON_ComponentStatus m_status = ON_ComponentStatus::NoneSet;

  /*
  Returns:
    The current value of the component mark ( m_status->RuntimeMark() ).
  Remarks:
    SubD components have a mutable runtime  mark that can be used
    in any context where a single thread cares about the marks.
    Any code can use Mark() at any time. You cannot assume that
    other functions including const will not change its value.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  */
  bool Mark() const;

  /*
  Description:
    Clears (sets to false) the value of the component mark.
  Remarks:
    SubD components have a mutable runtime  mark that can be used
    in any context where a single thread cares about the marks.
    Any code can use Mark() at any time. You cannot assume that
    other functions including const will not change its value.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool ClearMark() const;

  /*
  Description:
    Sets (sets to true) the value of the component mark.
  Remarks:
    SubD components have a mutable runtime  mark that can be used
    in any context where a single thread cares about the marks.
    Any code can use Mark() at any time. You cannot assume that
    other functions including const will not change its value.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool SetMark() const;

  /*
  Description:
    Sets the value of the component mark to bMark.
  Parameter:
    bMark - [in]
  Remarks:
    SubD components have a mutable runtime  mark that can be used 
    in any context where a single thread cares about the marks.
    Any code can use Mark() at any time. You cannot assume that
    other functions including const will not change its value.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.
  Returns:
    Input value of Mark().
  */
  bool SetMark(
    bool bMark
  ) const;

  /*
  Returns:
    The current value of the component mark bits ( m_status->MarkBits() ).
  Remarks:
    Mark() and MarkBits() are independent.

    SubD components have a mutable runtime mark bits that can be used
    in any context where a single thread cares about the mark bits value.
    Any code can use MarkBits() at any time. You cannot assume that
    other functions including const will not change their value.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state. 

    MarkBits() is used in more complex calculations where the single true/false
    provided by Mark() is not sufficient. Typically MarkBits() is used when
    a collecection of components needs to be partitioned into more than two 
    sets or when the value of Mark() cannot be changed.
  */
  ON__UINT8 MarkBits() const;

  /*
  Returns:
    Set the component mark bits ( m_status->SetMarkBits( mark_bits ) ).
  Remarks:
    Mark() and MarkBits() are independent.

    SubD components have a mutable runtime mark bits that can be used
    in any context where a single thread cares about the mark bits value.
    Any code can use MarkBits() at any time. You cannot assume that
    other functions including const will not change their value.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.

    MarkBits() is used in more complex calculations where the single true/false
    provided by Mark() is not sufficient. Typically MarkBits() is used when
    a collecection of components needs to be partitioned into more than two
    sets or when the value of Mark() cannot be changed.
  Returns:
    Input value of MarkBits().
  */
  ON__UINT8 SetMarkBits(
    ON__UINT8 mark_bits
  ) const;

  /*
  Returns:
    Set the component mark bits to 0 ( m_status->SetMarkBits( 0 ) ).
  Remarks:
    Mark() and MarkBits() are independent.

    SubD components have a mutable runtime mark bits that can be used
    in any context where a single thread cares about the mark bits value.
    Any code can use MarkBits() at any time. You cannot assume that
    other functions including const will not change their value.
    It is widely used in many calculations to keep track of sets of
    components that are in a certain context specific state.

    MarkBits() is used in more complex calculations where the single true/false
    provided by Mark() is not sufficient. Typically MarkBits() is used when
    a collecection of components needs to be partitioned into more than two
    sets or when the value of Mark() cannot be changed.
  Returns:
    Input value of MarkBits().
  */
  ON__UINT8 ClearMarkBits() const;


public:
  
  //////////////////////////////////////////////////////////////
  //
  // Saved subdivision point
  //
  /*
  Description:
    Set the saved subdivision point.
  Parameters:
    subdivision_point - [in]
      includes displacement if it exists
  Returns:
    true if successful
  */
  bool SetSavedSubdivisionPoint(
    const double subdivision_point[3]
    ) const;

  bool GetSavedSubdivisionPoint(
    double subdivision_point[3]
    ) const;

  /*
  Description:
    Clears saved subdivision and limit surface information for this component.
    Attached components are not modified.
  */
  void ClearSavedSubdivisionPoint() const;

  /*
  Returns:
    Saved subdivision point. If a point has not been saved,
    ON_3dPoint::NanPoint is returned.
  */
  const ON_3dPoint SavedSubdivisionPoint() const;

  /*
  Returns:
    True if the subdivision point is cached.
  */
  bool SavedSubdivisionPointIsSet() const;

  ON_DEPRECATED_MSG("Does nothing. Returns false.")
  bool SetSubdivisionDisplacement(const double*);

  ON_DEPRECATED_MSG("Does nothing. Returns false.")
  bool GetSubdivisionDisplacement(double*) const;
  
  ON_DEPRECATED_MSG("Does nothing. Returns nans.")
  const ON_3dVector SubdivisionDisplacement() const;

  ON_DEPRECATED_MSG("Does nothing. Returns false.")
  bool SubdivisionDisplacementIsNonzero() const;

  ON_DEPRECATED_MSG("Does nothing.")
  void ClearSubdivisionDisplacement() const;

protected:
  friend class ON_Internal_SubDFaceMeshFragmentAccumulator;
  friend class ON_SubDHeap;
  enum SavedPointsFlags : unsigned char
  {
    // if ( 0 != (m_saved_points_flags & SubdivisionPointBit), then m_cache_subd_P is set.
    SubdivisionPointBit = 0x40,

    // if ( 0 != (m_saved_points_flags & SurfacePointBit), then ON_SubDVertex.m_limit* values are set.
    // ON_SubDVertex: Set means one or more sector limit surface points are saved in ON_SubDVertex.m_limit_point.
    // ON_SubDEdge: Set means the limit surface NURBS curve control points are cached.
    // ON_SubDFace: Set means limit surface mesh fragments are saved in ON_SubDFace.m_surface_mesh_fragments.
    // Unset means any information in the fields identified above is invalid and must be recalculated.
    SurfacePointBit = 0x80,

    // SubdivisionPointBit | SurfacePointBit
    CachedPointMask = 0xC0
  };

  enum ModifiedFlags : unsigned char
  {
    // if ( 0 != (m_saved_points_flags & Modified1Bit), then the component has been modified and
    // cached subdivision information needs to be recalculated.
    Modified1Bit = 0x01,

    // if ( 0 != (m_saved_points_flags & Modified2Bit), then the component is adjacent to
    // a modified component and cached subdivision information needs to be recalculated.
    Modified2Bit = 0x02,

    // ModifiedFlagsMask = Modified1Bit | Modified2Bit
    // if ( 0 != (m_saved_points_flags & ModifiedFlagsMask), then any cached subdivision information
    // on that component needs to be recalculated.
    ModifiedFlagsMask = 0x03
  };

  // m_saved_points_flags is a bit field based on ON_SubDComponentBase::SavePointsFlags values.
  // GetSurfacePoint( bUseSavedSurfacePoint=true ) can change the value of m_saved_points_flags
  void Internal_SetSavedSurfacePointFlag(bool bSavedSurfacePointFlag) const;
  void Internal_SetModified1Flag() const;
  void Internal_SetModified2Flag() const;

  /*
  Returns:
    True if Modified1Bit or Modified2Bit is set.
  */
  bool Internal_Modified1IsSet() const;

  /*
  Returns:
    True if Modified1Bit or Modified2Bit is set.
  */
  bool Internal_Modified1or2IsSet() const;

  void Internal_ClearModifiedFlags() const;
  mutable unsigned char m_saved_points_flags = 0U;

  unsigned char m_level = 0U;
public:

  // All the faces with the same nonzero value of m_group_id are in the same "group".
  // SDK interface on ON_SubD will be added after we get a better idea of how this
  // feature will be used.
  mutable unsigned int m_group_id = 0U;

protected:
  /*
  Description:
    Clears the flags indicating the saved subdivision point and surface point information 
    is current.
  */
  void Internal_ClearSubdivisionPointAndSurfacePointFlags() const;

  /*
  Description:
    Clears the flag indicating the saved subdivision point is current.
  */
  void Internal_ClearSubdivisionPointFlag() const;

  /*
  Description:
    Clears the flag indicating the saved surface point information is current.
  */
  void Internal_ClearSurfacePointFlag() const;

  bool Internal_SubdivisionPointFlag() const;

  bool Internal_SurfacePointFlag() const;

  void Internal_TransformComponentBase(bool bTransformationSavedSubdivisionPoint, const class ON_Xform& xform);
  // GetSubdivisionPoint( bUseSavedSubdivisionPoint=true ) can change the value of m_cache_subd_P
  mutable double m_saved_subd_point1[3]; // saved subdivision point

private:
  // Reserved for future use for attributes that apply to all SubD components (ON_SubDVertex, ON_SubDEdge, and ON_SubDFace).
  ON__UINT64 m_reserved8bytes1;
  ON__UINT64 m_reserved8bytes2;
  ON__UINT64 m_reserved8bytes3;

public:
  /*
  Description:
    Pretend ArchiveId() and SetArchiveId() do not exist.
  Returns:
    The ArchiveId is a value set and used by ON_BinaryArchive Read() and Write()
    functions and copy constructors and operator=(). 
    A public interface is supplied because it is not practical to use friends.
  Remarks:
    A value of ON_UNSET_UINT_INDEX indicates the component is not in use.
  */
  unsigned int ArchiveId() const
  {
    return m_archive_id;
  }

  void SetArchiveId(
    unsigned int archive_id
    ) const
  {
    // m_archive_id is mutable
    if ( ON_UNSET_UINT_INDEX != archive_id )
      m_archive_id = archive_id; 
  }

protected:
  void CopyBaseFrom(
    const ON_SubDComponentBase* src,
    bool bCopySymmetrySetNext
    );

public:
  /*
  Returns:
    True if this component is marked as a primary motif component.
  Remarks:
    You must use ON_SubD SymmetrySet member functions to get symmetry set contents.
  */
  bool IsSymmetrySetPrimaryMotif() const;

  /*
  Returns:
    True if this component is marked being in a symmetry set.
  Remarks:
    You must use ON_SubD SymmetrySet member functions to get symmetry set contents.
  */
  bool InSymmetrySet() const;

private:
  // Symmetry sets are a linked loops of components order so that symmetry(component) = next component.
  // There is exactly one motif in each symmetry set.
  // The motif component is marked with 1 == m_symmetry_set_next.ComponentDirection(). 
  // The next component in the symmetry set loop is m_symmetry_set_next.Vertex()/Edge()/Face().
  // When a symmetry set is a singleton (fixed component in the symmetry), this = m_symmetry_set_next
  // and m_symmetry_set_next.ComponentDirection()= 1.
  // The only safe way query, set, and clear symmetry set information is to use
  // ON_SubD.*SymmetrySet*() functions. Any other technique is not supported and will cause crashes.
  friend class ON_SubDArchiveIdMap;
  ON_SubDComponentPtr m_symmetry_set_next;
};

////////////////////////////////////////////////////////////////////////////
//
// ON_SubDVertexEdgeProperties
//
class ON_CLASS ON_SubDVertexEdgeProperties
{
public:
  ON_SubDVertexEdgeProperties() = default;
  ~ON_SubDVertexEdgeProperties() = default;
  ON_SubDVertexEdgeProperties(const ON_SubDVertexEdgeProperties&) = default;
  ON_SubDVertexEdgeProperties& operator=(const ON_SubDVertexEdgeProperties&) = default;

public:
  static const ON_SubDVertexEdgeProperties Zero; // all member values are zero.

  /*
  Returns:
    True if there are no null edges and there are two edges with a single face and all remaining edges have two faces.
  Remarks:
    Tags are ignored.
  */
  bool HasInteriorVertexTopology() const;

  /*
  Returns:
    True if there are no null edges, exactly two boundary edges, and any other edges have two faces.
  Remarks:
    Tags are ignored.
  */
  bool HasBoundaryVertexTopology() const;

  /*
  Returns:
    HasInteriorVertexTopology() || HasBoundaryVertexTopology().
  */
  bool HasManifoldVertexTopology() const;

  /*
  Returns:
    True if there are no null edges and there is an edge with zero faces or an edge with three or more faces.
  Remarks:
    Tags are ignored.
  */
  bool HasNonmanifoldVertexTopology() const;

  /*
  Returns:
    Number of edges.
  */
  unsigned EdgeCount() const;

public:
  // Number of null edges
  unsigned short m_null_edge_count = 0;


  /////////////////////////////////////////////////////
  //
  // Vertex attached component counts
  //

  // vertex->m_edge_count 
  unsigned short m_edge_count = 0;

  // vertex->m_face_count 
  unsigned short m_face_count = 0;

  /////////////////////////////////////////////////////
  //
  // Edge tag counts
  //

  // Number of edges tags ON_SubDEdgeTag::Unset
  unsigned short m_unset_edge_count = 0;

  // Number of edges tags ON_SubDEdgeTag::Smooth or ON_SubDEdgeTag::SmoothX
  unsigned short m_smooth_edge_count = 0;

  // Number of edges tags ON_SubDEdgeTag::Crease
  unsigned short m_crease_edge_count = 0;

  /////////////////////////////////////////////////////
  //
  // Edge topology counts
  //

  // Number of wire edges (0 attached faces)
  unsigned short m_wire_edge_count = 0;

  // Number of boundary edges (1 attached face)
  unsigned short m_boundary_edge_count = 0;

  // Number of interior edges (2 attached faces)
  unsigned short m_interior_edge_count = 0;

  // Number of nonmanifold edges (3 or more attached faces)
  unsigned short m_nonmanifold_edge_count = 0;


  /////////////////////////////////////////////////////
  //
  // Edge face counts
  //

  // Minimum value of attached edges's m_face_count.
  unsigned short m_min_edge_face_count = 0;

  // Maximum value of attached edges's m_face_count.
  unsigned short m_max_edge_face_count = 0;
};

////////////////////////////////////////////////////////////////////////////
//
// ON_SubDVertex
//
class ON_CLASS ON_SubDVertex : public ON_SubDComponentBase
{
private:
  friend class ON_SubDArchiveIdMap;
  friend class ON_SubDEdge;
  friend class ON_SubDFace;

public:
  ON_SubDVertex() = default;
  ~ON_SubDVertex() = default;
  ON_SubDVertex(const ON_SubDVertex&) = default;
  ON_SubDVertex& operator=(const ON_SubDVertex&) = default;

public:
  unsigned int VertexId() const;

public:
  /*
  Description:
    Clears saved subdivision and limit surface information for this vertex.
    Attached edges and faces are not modified.
  */
  void ClearSavedSubdivisionPoints() const;  


  /*
  Description:
    Clears saved subdivision and limit surface information for this vertex.
  Parameters:
    bClearNeighborhood - [in]
      If true, all edges and faces attached to this vertex are also cleared.
  */
  void ClearSavedSubdivisionPoints(
    bool bClearNeighborhood
  ) const;

public:
  static const ON_SubDVertex Empty;  

  bool Write (
    class ON_BinaryArchive& archive
    ) const;

  static bool Read (
    class ON_BinaryArchive& archive,
    class ON_SubD& subd,
    class ON_SubDVertex*& vertex
    );

  const ON_wString ToString(
    bool bIncludeControlNetPoint,
    bool bIncludeTopology
  ) const;

  /*
  Parameters:
    bIncludeEdges - [in]
      If true, then attached edges are included.
    bIncludeFaces - [in]
      If true, then attached faces are included.
  Returns:
    A ON_ComponentStatusLogicalOr() of this vertex's status and the 
    specified attached components.
  See Also:
    ON_SubDComponentBase::Status()
  */
  const ON_ComponentStatus NeighborhoodStatusLogicalOr(
    bool bIncludeEdges,
    bool bIncludeFaces
  ) const;

  /*
  Description:
    Apply a transformation matrix to vertex geometry information.
  Parameters:
    bTransformationSavedSubdivisionPoint - [in]
      If the transformation is being applied to every vertex, edge and 
      face in every level of a subdivision object, and the transformation
      is an orientation preserving isometry (rotation, translation, ...),
      then set bTransformationSavedSubdivisionPoint = true to apply the
      transformation to saved subdivision and saved limit point information.
      In all other cases, set bTransformationSavedSubdivisionPoint = false
      and any saved subdivision points or saved limit points will be
      deleted.  When in doubt, pass false.

    xform - [in]
  */
  bool Transform(
    bool bTransformationSavedSubdivisionPoint,
    const class ON_Xform& xform
    );

  bool Transform(
    bool bTransformationSavedSubdivisionPoint,
    const class ON_Xform& xform,
    const class ON_Xform& xformNormals
    );

  bool SetControlNetPoint(
    ON_3dPoint control_net_point,
    bool bClearNeighborhoodCache
  );

  /// <summary>
  /// Sets the control net point to ON_3dPoint::NanPoint and clears
  /// saved subdivision points.
  /// </summary>
  void UnsetControlNetPoint();


  ON_BoundingBox ControlNetBoundingBox() const;

  /// <summary>
  /// Get a SHA-1 hash that is useful in detecting when a vertex's 
  /// connections to attached edges or faces have been changed.
  /// See also ON_SubDVertex::TopologyCRC32() which, in practice,
  /// is just as reliable as the hash.
  /// </summary>
  /// <param name="bIncludeSubdivisionProperties">
  /// Pass true if you want to include nontopological subdivision properties
  /// (tags, sharpnesses, control net point) 
  /// that help determine the vertex's subdivision point in the hash.
  /// </param>
  /// <returns>
  /// A SHA-1 hash of the vertex's id and the ids of the edges and faces attached to this vertex.
  /// </returns>
  const ON_SHA1_Hash TopologyHash(bool bIncludeSubdivisionProperties) const;

  /// <summary>
  /// Get a 32 bit CRC that is useful in detecting when a vertex's 
  /// connections to attached edges or faces have been changed.
  /// </summary>
  /// <param name="bIncludeSubdivisionProperties">
  /// Pass true if you want to include nontopological subdivision properties
  /// (tags, sharpnesses, control net point) 
  /// that help determine the vertex's subdivision point in the CRC.
  /// </param>
  /// <returns>
  /// A 32 bit CRC = this->TopologyHash(bIncludeSubdivisionProperties).CRC32(0).
  /// </returns>
  ON__UINT32 TopologyCRC32(bool bIncludeSubdivisionProperties) const;


public:
  const ON_COMPONENT_INDEX ComponentIndex() const;
  const ON_SubDComponentPtr ComponentPtr() const;

public:
  // m_prev_vertex, m_next_vertex must be the first data members of ON_SubDVertex
  const class ON_SubDVertex* m_prev_vertex = nullptr; // linked list of vertices on this level
  const class ON_SubDVertex* m_next_vertex = nullptr; // linked list of vertices on this level

public:
  ON_SubDVertexTag m_vertex_tag = ON_SubDVertexTag::Unset;

  
private:
  unsigned char  m_reserved1 = 0;
private:
  unsigned short  m_reserved2 = 0;

private:
  /// The level 0 interior crease vertex sharpness is the maximum edge end sharpenss
  /// at the vertex of all smooth edges in both sectors of an interior crease vertex. 
  /// It can also be set by subdividing a previous level's value.
  /// 
  /// In low level subdivision point evaluation code, a subset of the SubD containing 
  /// only the components from the sector being evaluated is used. There is one situation 
  /// where m_interior_crease_vertex_sharpness needs to be set to properly
  /// evaluate the subdivision points and limit points.
  /// 1) The vertex is an interior crease.
  /// (The vertex has a crease tag and 2 sectors. 
  /// This implies both crease edges have 2 faces and the vertex's m_edge_count = m_face_count &gt;= 2).
  /// 2) The sharp edges in the two sectors generate different vertex sharpnesses.
  /// Again, this only occurs in low level evauation code.
  /// This value should be zero or be the same as the maximum sharpness 
  /// of all smooth edge ends at this vertex in the complete SubD.
  /// The value is mutable because it is updated in the case above
  /// at appropriate times in the evaluation calculation.
  /// If per vertex sharpness is ever added, that value must be stored someplace else
  /// as, depending on the initial sharpness configuration, this value can be
  /// larger, smaller, or equal to a per vertex sharpness.
  mutable float m_interior_crease_vertex_sharpness = 0.0;
private:

#if defined(ON_COMPILING_OPENNURBS)
public:
  /// <summary>
  /// This function is used to save vertex sharpnesses at interior crease vertices
  /// so that low level evaulation code (like that in ON_SubDVertexQuadSector) will
  /// get correct subdivision and limit points for interior crease vertices that
  /// have different maximum edge end shaprness values in their two sectors.
  /// The level 0 value passed in must be calucated while the vertex is in the orginal 
  /// complete configuration with two sectors. Subsets used in low level N > 0 evaluations
  /// sometimes pass in a value calculated by subdividing the previous level's value.
  /// </summary>
  /// <param name="interior_crease_vertex_sharpness">
  /// Maximum edge end sharpness of the interior crease vertex calculated 
  /// from all level 0 smooth edges in both sectors or calculated by subdividing
  /// a previous level's value.
  /// </param>
  /// <param name="bSkipEdgeCountTest">
  /// If bSkipEdgeCountTest is false, then v must be a level 0 crease vertex
  /// with m_edge_count = m_face_count &gt;= 2 of a level N &gt; 0 vertex
  /// with m_edge_count = 1+m_face_count &gt;= 1. 
  /// If bSkipEdgeCountTest the edge count tests are skipped. The expert user
  /// is certain this vertex is being initialized before the edges and faces are
  /// attached and it's control net topology will satisify the above conditions
  /// before the vertex is used.
  /// </param>
  void Internal_SetInteriorCreaseVertexSharpnessForExperts(
    double interior_crease_vertex_sharpness,
    bool bSkipEdgeCountTest
  ) const;

  /// <summary>
  /// Unconditionally sets the interior crease vertex sharpness to zero.
  /// </summary>
  void Internal_ClearInteriorCreaseVertexSharpnessForExperts() const;


  /// <summary>
  /// This function is for use by experts in low level subdivision point 
  /// evaluations when the center vertex is an interior crease with two sectors.
  /// It exists so that low level evaluation code using information about
  /// only one of the sectors is present (like the situation that occurs in
  /// ON_SubDVertexQuadSector functions).
  /// </summary>
  /// <returns>
  /// The interior crease sector vertex sharpness. This value must be properly
  /// epertly used with other information to get the correct subdivision point.
  /// </returns>
  double Internal_InteriorCreaseVertexSharpnessForExperts() const;
#endif

public:
  unsigned short m_edge_count = 0;
  unsigned short m_face_count = 0;

  unsigned short m_edge_capacity = 0;
  unsigned short m_face_capacity = 0;

public:
  // Array of m_edge_count edges.
  //   m_edge[i].EdgeDirection() indicates which edge end is located at this vertex
  //   If m_edge_capacity > 0, m_edge_capacity is the number of elements that
  //   may be used in m_edges[].
  class ON_SubDEdgePtr* m_edges = nullptr;

  // Array of m_face_count faces.
  //   If m_face_capacity > 0, m_face_capacity is the number of elements that
  //   may be used in m_faces[].
  const class ON_SubDFace** m_faces = nullptr;

  /*
  Description:
    Expert user tool to remove an edge from the vertex's m_edges[] array.
  Remarks:
    Does not modify the edge. If the vertex is referenced by the edge,
    then the vertex must be removed from edge's m_vertex[] array.
  */
  bool RemoveEdgeFromArray(
    const class ON_SubDEdge* f
    );

  /*
  Description:
    Expert user tool to remove a face from the vertex's m_faces[] array.
  Remarks:
    Does not modify the face or any edges. The faces edges must be updated accordingly.
  */
  bool RemoveFaceFromArray(
    const class ON_SubDFace* f
    );

  /*
  Parameters:
    bApplyInputTagBias - [in]
      If bApplyInputTagBias is true, the current tag value is used
      to choose between possible output results. When in doubt, pass false.
    bReturnBestGuessWhenInvalid
      If bReturnBestGuessWhenInvalid is true and the topology and current edges
      tags do not meet the conditions for a valid vertex, then a best guess for 
      a vertex tag is returned. Otherwise ON_SubDVertexTag::Unset is returned.
      When in doubt pass false and check for unset before using.
  Returns:
    The suggested value for this vertices tag based on its current tag value and
    its current edges. Assumes the vertex and edge topology are correct and the 
    edge tags are correctly set.
  */
  ON_SubDVertexTag SuggestedVertexTag(
    bool bApplyInputTagBias,
    bool bReturnBestGuessWhenInvalid
  ) const;

public:
  double m_P[3]; // vertex control net location
  
  ///<summary>
  /// The SubD vertex control net point.
  ///</summary>
  const ON_3dPoint ControlNetPoint() const;

private:
  // Cached limit point and limit normal
  // GetSurfacePoint( bUseSavedSurfacePoint=true ) can change the value of m_limit_point.
  // If the limit point is set and vertex has a single sector, then 
  // m_limit_point.m_sector_face = nullptr and m_limit_point.m_next_sector_limit_point = nullptr.
  // If the limit point is set and vertex has a multiple sectors, then 
  // m_limit_point.m_sector_face = first face in the sector.
  // If multiple limit points are set, then they are in a linked list
  // traversed using the ON_SubDSectorSurfacePoint.m_next_sector_limit_point.
  // The second and any additional limit points are managed by a fixed size pool.
  // Calling ClearSurfacePoint() will return these to the pool.
  mutable ON_SubDSectorSurfacePoint m_limit_point = ON_SubDSectorSurfacePoint::Unset;

public:
  enum : unsigned int
  {
    MaximumEdgeCount = 0xFFF0U,
    MaximumFaceCount = 0xFFF0U
  };

  static int CompareUnorderedEdges(
    const ON_SubDVertex* a,
    const ON_SubDVertex* b
    );

  static int CompareUnorderedFaces(
    const ON_SubDVertex* a,
    const ON_SubDVertex* b
    );

  static int CompareUnorderedEdgesAndFaces(
    const ON_SubDVertex* a,
    const ON_SubDVertex* b
    );

  ///*
  //Description:
  //  Sort the m_edges[] and m_faces[] arrays so radial groups are together.
  //  After the sorting is completed, m_vertex_edge_order is set to recorded
  //  the current sorting state and its value is returned.  
  //  The sorting is done unconditionally.
  //*/
  //ON_SubD::VertexEdgeOrder SortEdges();

  unsigned int EdgeCount(
    ON_SubDEdgeTag edge_tag
    ) const;

  unsigned int EdgeCount() const;

  const class ON_SubDEdge* Edge(
    unsigned int i
    ) const;

  const ON_SubDEdgePtr EdgePtr(
    unsigned int i
    ) const;

  ON__UINT_PTR EdgeDirection(
    unsigned int i
    ) const;

  unsigned int EdgeArrayIndex(
    const ON_SubDEdge* edge
    ) const;

  /*
  Description:
    Expert user tool to replace reference to old_edge with a reference to new_edge.
  Parameters:
    old_edge = [in]      
      Cannot be nullptr.
    new_edge = [in]
      If new_edge is Null, old_edge is simply removed.
  Returns:
    If the replacement was successful, then the m_edges[] array index where old_edge/new_edge replacement occurred is returned.
    Otherwise ON_UNSET_UINT_INDEX is returned.
  Remarks:
    No modifications are made to old_edge or new_edge.
  */
  unsigned int ReplaceEdgeInArray(
    const ON_SubDEdge* old_edge,
    const ON_SubDEdgePtr new_edge
    );

  unsigned int FaceCount() const;

  const class ON_SubDFace* Face(
    unsigned int i
    ) const;

  unsigned int FaceArrayIndex(
    const ON_SubDFace* face
  ) const;

  /*
  Description:
    Expert user tool to replace reference to old_face with a reference to new_face.
  Parameters:
    old_face = [in]      
      Cannot be nullptr.
    new_face = [in]
      If new_face is nullptr, old_face is simply removed.
  Returns:
    If the replacement was successful, then the m_faces[] array index where old_face/new_face replacement occurred is returned.
    Otherwise ON_UNSET_UINT_INDEX is returned.
  Remarks:
    No modifications are made to old_face or new_face.
  */
  unsigned int ReplaceFaceInArray(
    const ON_SubDFace* old_face,
    const ON_SubDFace* new_face
    );

  /*
  Returns:
    True if m_vertex_tag is ON_SubDVertexTag::Smooth.
  */
  bool IsSmooth() const;

  /// <summary>
  /// Sharp vertices are smooth, crease or dart vertices attached to 
  /// at least one sharp edge. Note that when an edge has variable
  /// sharpness it can have zero sharpness at one end
  /// and nonzero shaprness at the other end.
  /// The bEndCheck parameter controls what type of sharpness query
  /// is performed.
  /// Note that the vertex subdivision point is affected by attached
  /// sharp edges when IsSharp(true) is is true (ON_Vertex::VertexSharpness() &gt; 0). 
  /// The vertex limit surface point is affected by edge sharpenss 
  /// when IsSharp(false) is true.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <param name="bEndCheck">
  /// When bEndCheck is false, the check looks for edges with any nonzero sharpness.
  /// When bEndCheck is true, the check looks for edges with nonzero sharpness at this vertex.
  /// </param>
  /// <returns>
  /// True if this vertex is smooth, dart, or crease and is attached 
  /// to at least one sharp edge.
  ///</returns>
  bool IsSharp( bool bEndCheck ) const;

  /// <summary>
  /// Sharp vertices are smooth, crease or dart vertices attached 
  /// to at least one sharp edge with nonzero end sharpness at the vertex.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <returns>
  /// If the vertex is smooth and and two or more attached edges have positive end sharpness
  /// at this vertex, then the maximum edge end sharpness at this vertex is returned.
  /// If the vertex is a dart or crease and and one or more attached edges have positive end sharpness
  /// at this vertex, then the maximum edge end sharpness at this vertex is returned.
  /// Otherwise 0.0 is returned.
  /// </returns>
  double VertexSharpness() const;

  /// <summary>
  /// Sharp vertices are smooth, crease or dart vertices attached to 
  /// at least one sharp edge. Note that the end sharpness at a vertex
  /// can be zero.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <param name="bUseCreaseSharpness">
  /// When bCountCreasesAsSharp is true, crease edges are counted.
  /// </param>
  /// <param name="bEndCheck">
  /// When bEndCheck is false, the check looks for edges with any nonzero sharpness.
  /// When bEndCheck is true, the check looks for edges with nonzero sharpness at this vertex.
  /// </param>
  /// <returns>
  /// If bEndCheck is false, returns the number of sharp edges attached to this vertex.
  /// If bEndCheck is true, returns the number of edges with nonzero end sharpness at this vertex.
  /// </returns>
  unsigned int SharpEdgeCount( 
    bool bCountCreasesAsSharp,
    bool bEndCheck 
  ) const;

  /// <summary>
  /// Get the range of sharpness values assigned to sharp edges 
  /// and return the number of sharp edges.
  /// Sharp vertices are smooth, crease or dart vertices attached to at least one sharp edge
  /// with nonzero sharpness at the vertex. Note that the end sharpness at a vertex
  /// can be zero.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <param name="bCountCreasesAsSharp">
  /// When bCountCreasesAsSharp is true, creases are counted and ON_SubDEdgeSharpness::CreaseValue
  /// is used as a crease edge sharpness.
  /// </param>
  /// <param name="bEndCheck">
  /// When bEndCheck is false, the check looks for edges with any nonzero sharpness.
  /// When bEndCheck is true, the check looks for edges with nonzero sharpness at this vertex.
  /// </param>
  /// <param name="sharpness_range">
  /// The range of sharpness values is returned here.
  /// If bEndCheck is false, sharpness_range is the minimum and maximum of attached_edge->MaximumEndSharpness() for any attached sharp edge.
  /// If bEndCheck is false, sharpness_range is the minimum and maximum of nonzero attached_edge->MaximumEndSharpness() for any attached sharp edge.
  /// If no sharp edges are attached, then (0,0) is returned.
  /// </param>
  /// <returns>
  /// If bEndCheck is false, returns the number of sharp edges attached to this vertex.
  /// If bEndCheck is true, returns the number of edges with nonzero end sharpness at this vertex.
  /// </returns>
  unsigned int SharpEdgeCount(
    bool bCountCreasesAsSharp,
    bool bEndCheck, 
    ON_Interval& sharpness_range
  ) const;

  /// <summary>
  /// Sharp vertices are smooth, crease or dart vertices attached to at least one sharp edge
  /// with nonzero sharpness at the vertex.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <param name="sharp_subdivision_point">If the returned sharpness is &gt; 0,
  /// then the sharp subdivision point is returned. 
  /// When the returned sharpness is &gt; 0 and &lt; 1, 
  /// the final subdivision point is a weighted average of 
  /// sharp_subdivision_point and the ordinary subdivision point.
  /// When the returned sharpness is &gt;= 1, the sharp subdivision point is used
  /// in place of the ordinary subdivision point.
  /// </param>
  /// <returns>
  /// If the vertex is smooth and and two or more attached edges have positive end sharpness
  /// at this vertex, then the maximum edge end sharpness at this vertex is returned.
  /// If the vertex is a dart or crease and and one or more attached edges have positive end sharpness
  /// at this vertex, then the maximum edge end sharpness at this vertex is returned.
  /// Otherwise 0.0 is returned.
  ///< / returns>
  double GetSharpSubdivisionPoint(ON_3dPoint& sharp_subdivision_point) const;

  /// <summary>
  /// Sharp vertices are smooth, crease or dart vertices attached to at least one sharp edge
  /// with nonzero sharpness at the vertex.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <param name="count">
  /// The returned value is 0 to 3 and is the number of output values vertices in v[] and c[].
  /// If 1 &lt;= count &lt;=3, then 
  /// sharp_subdivision_point = sum(0 &lt;= i &lt; count, c[i]*v[i]->ControlNetPoint()).
  /// Otherwise the vertex is not sharp.
  /// </param>
  /// <param name="v">
  /// Output subdivision point vertices are returned here.
  /// </param>
  /// <param name="c">
  /// Output subdivision point sum coefficients are returned here.
  /// </param>
  /// <returns>
  /// The vertex sharpness is returned ( &gt;= 0.0 ).
  /// If the returned value is &gt; 0.0, then the sharp subdivision point 
  /// = sum(0 &lt;= i &lt; count, c[i]*v[i]->ControlNetPoint())
  /// </returns>
  double GetSharpSubdivisionPoint(
    unsigned& count,
    const ON_SubDVertex* v[3],
    double c[3]
  ) const;

  /*
  Returns:
    True if m_vertex_tag is ON_SubDVertexTag::Crease.
    If the vertex is a boundary crease, there will be one sector.
    If the vertex is an interior crease, there will be two sectors.
  */
  bool IsCrease() const;

  /// <summary>
  /// There are 2 configurations a valid crease vertex can have.
  /// 
  /// 1) A crease vertex with one sector has EdgeCount() = 1+FaceCount(),
  /// two crease edges that are attached to a single face,
  /// and the other edges are smooth and are attached to two faces.
  ///
  /// 2) A crease vertex with two sectors has EdgeCount() = FaceCount(),
  /// two crease edges, and all edges are attached to two faces.
  /// 
  /// In a complete SubD (not a subset), a 1 sector crease vertex is
  /// always on the boundary of the SubD. In all cases a 2 sector crease vertex
  /// is an interior vertex.
  /// </summary>
  /// <returns>
  /// True if the vertex tag is ON_SubDVertexTag::Crease, EdgeCount() = 1+FaceCount(), 
  /// and FaceCount() &gt;= 1.
  /// </returns>
  bool IsOneSectorCrease() const;

  /// <summary>
  /// There are 2 configurations a valid crease vertex can have.
  /// 
  /// 1) A crease vertex with one sector has EdgeCount() = 1+FaceCount(),
  /// two crease edges that are attached to a single face,
  /// and the other edges are smooth and are attached to two faces.
  ///
  /// 2) A crease vertex with two sectors has EdgeCount() = FaceCount(),
  /// two crease edges, and all edges are attached to two faces.
  /// 
  /// In a complete SubD (not a subset), a 1 sector crease vertex is
  /// always on the boundary of the SubD. In all cases a 2 sector crease vertex
  /// is an interior vertex.
  /// </summary>
  /// <returns>
  /// True if the vertex tag is ON_SubDVertexTag::Crease, EdgeCount() = FaceCount(), 
  /// and FaceCount() &gt;= 2.
  /// </returns>
  bool IsTwoSectorCrease() const;

  /*
  Returns:
    True if m_vertex_tag is ON_SubDVertexTag::Corner.
  */
  bool IsCorner() const;

  /*
  Returns:
    True if m_vertex_tag is ON_SubDVertexTag::Dart.
  */
  bool IsDart() const;

  /*
  Returns:
    True if m_vertex_tag is ON_SubDVertexTag::Smooth or ON_SubDVertexTag::Crease.
  */
  bool IsSmoothOrCrease() const;

  /*
  Returns:
    True if m_vertex_tag is ON_SubDVertexTag::Crease or ON_SubDVertexTag::Corner.
  */
  bool IsCreaseOrCorner() const;

  /*
  Returns:
    True if m_vertex_tag is ON_SubDVertexTag::Dart, ON_SubDVertexTag::Crease or ON_SubDVertexTag::Corner.
  */
  bool IsDartOrCreaseOrCorner() const;


  /*
  Returns:
    True if m_vertex_tag is ON_SubDVertexTag::Dart or ON_SubDVertexTag::Crease
  */
  bool IsDartOrCrease() const;

  /*
  Returns:
    True if m_vertex_tag is ON_SubDVertexTag::Dart or ON_SubDVertexTag::Corner
  */
  bool IsDartOrCorner() const;

  /*
  Returns:
    True if m_vertex_tag is ON_SubDVertexTag::Smooth or ON_SubDVertexTag::Dart.
  */
  bool IsSmoothOrDart() const;
  /*
  Returns:
    True if m_vertex_tag is ON_SubDVertexTag::Smooth or ON_SubDVertexTag::Dart or ON_SubDVertexTag::Crease.
  */
  bool IsSmoothOrDartOrCrease() const;

  const ON_SubDVertexEdgeProperties EdgeProperties() const;

  /*
  Parameters:
    eptr0 - [out]
    eptr1 - [out]
      If a vertex has exactly two attached edges, each of which has a single attached face,
      then these edges are returned in the order the appear in the vertex's edge list. 
      (RelativeVertex(0) = this vertex). Otherwise the parameters are set to null.
  Returns:
    True if the vertex has exactly two attached edges, each of which has a single attached face.
    False otherwise.
  */
  bool GetBoundaryVertexEdges(
    ON_SubDEdgePtr* eptr0,
    ON_SubDEdgePtr* eptr1
  ) const;

  /*
  Parameters:
    vei0 - [out]
    vei1 - [out]
      If a vertex has exactly two attached edges, each of which has a single attached face,
      then the indices of those edges in the vertex's edge list are returned. 
      Otherwise ON_UNSET_UINT_INDEX is returned.
  Returns:
    True if the vertex has exactly two attached edges, each of which has a single attached face.
    False otherwise.
  */
  bool GetBoundaryVertexEdgeIndices(
    unsigned* vei0,
    unsigned* vei1
  ) const;

  /*
  Description:
    A "standard" vertex is one where the standard subdivsion matrix for that vertex
    can be used to calculate the subdivision point. 
    This function is designed to be useful for testing and debugging code when
    a certain situation is expected to exist.  It is not used for evaluation
    because it is too slow.

  Returns:
    True if the subdivison point of the vertex can be calculated using the standard
    subdivion matrix for the vertex type and face count.

  Remarks:
    If the vertex is tagged and has multiple sectors, like an interior
    crease or corner vertex, then this function will return false.
    In this situation, it is possible that the vertex, as the center of a
    sector, is standard.
  */
  bool IsStandard() const;

  /*
  Description:
    A single sector vertex is a smooth vertex, a dart vertex, or a manifold boundary
    vertex.
  Returns:
    True if the vertex has a single sector and, consequently, a single
    limit surface normal.

  */
  bool IsSingleSectorVertex() const;

  /*
  Description:
    A manifold boundary vertex is a crease or corner vertex with 2 creased edges, 
    each attached to a single face, and all other edges are smooth edges attached 
    to two faces. There is a single sector at a manifold boundary vertex.
  Returns:
    True if the vertex has a single sector and, consequently, a single
    limit surface normal.

  */
  bool IsManifoldBoundaryVertex() const;

  /*
  Description:
    A vertex has interior vertex topology if
    EdgeCount() >= 2,
    EdgeCount() == FaceCount(),
    and every attached edge has two attached faces.
  Returns:
    True if the vertex has interior vertex toplology.
  Remarks:
    Tags are ignored. This property is often used during construction
    and modification when tags are not set.
  */
  bool HasInteriorVertexTopology() const;

  /*
  Description:
    A vertex has boundary vertex topology if
    EdgeCount() >= 2,
    EdgeCount() == 1+FaceCount(),
    two attached edges are attached to one face,
    the remaining edges are attached to two faces.
  Returns:
    True if the vertex has boundary vertex toplology.
  Remarks:
    Tags are ignored. This property is often used during construction
    and modification when tags are not set.
  */
  bool HasBoundaryVertexTopology() const;

  /*
  Returns:
    If this vertex has two boundary edges, they are returned in the pair with
    BoundaryEdgePair().First().EdgePtr().RelativeVetex(0) and
    BoundaryEdgePair().Second().EdgePtr().RelativeVetex(0)
    equal to this vertex.
    Otherwise ON_SubDComponentPtrPair::Null is returned.
  */
  const ON_SubDComponentPtrPair BoundaryEdgePair() const;

  /*
  Returns:
    If this vertex has two creased edges, they are returned in the pair.
    Otherwise ON_SubDComponentPtrPair::Null is returned.
  */
  const ON_SubDComponentPtrPair CreasedEdgePair(
    bool bInteriorEdgesOnly
  ) const;


  /*
  Returns:
    If this vertex has one creased edge, it is returned.
    Otherwise ON_SubDEdgePtr::Null is returned.
  */
  const ON_SubDEdgePtr CreasedEdge(
    bool bInteriorEdgesOnly
  ) const;

  /*
  Description:
    Count creases with specified topology.
  Parameters:
    bCountInteriorCreases - [in]
      Count includes crease edges with 2 faces.
    bCountBoundaryCreases - [in]
      Count includes crease edges with 1 face.
    bCountNonmanifoldCreases - [in]
      Count includes crease edges with 3 or more faces.
    bCountWireCreases - [in]
      Count includes crease edges with 0 faces.
  Returns:
    Number of creased edges with the specified topology.
  */
  const unsigned int CreasedEdgeCount(
    bool bCountInteriorCreases,
    bool bCountBoundaryCreases,
    bool bCountNonmanifoldCreases,
    bool bCountWireCreases
    ) const;

  /*
  Returns:
    Number of creased edges.
  */
  const unsigned int CreasedEdgeCount() const;

  /*
  Parameters:
    bUseSavedSubdivisionPoint - [in]
      If there is a saved subdivision point and bUseSavedSubdivisionPoint
      is true, then the saved value is returned.
    subdivision_point - [out]
      The SubD vertex Catmull-Clark subdivision point is returned here.
  Returns:
    true if successful
  */
  bool GetSubdivisionPoint(
    double subdivision_point[3]
    ) const;

  ///<summary>
  /// The SubD vertex Catmull-Clark subdivision point.
  ///</summary>
  const ON_3dPoint SubdivisionPoint() const;

  /// <summary>
  /// Calculate the Catmull-Clark subdivision point for a crease vertex.
  /// </summary>
  /// <param name="P">crease vertex control net point.</param>
  /// <param name="vertex_sharpness">
  /// maximum value of smooth edge sharpnesses at the crease vertex.
  /// <param name="A1">control net point at the other end of one attached crease edge.</param>
  /// <param name="A2">control net point at the other end of the other attached crease edge.</param>
  /// <returns></returns>
  static const ON_3dPoint CreaseVertexSubdivisionPoint(
    const ON_3dPoint& P,
    double vertex_sharpness,
    const ON_3dPoint& A1,
    const ON_3dPoint& A2
  );


  /*
  Description:
    Evaluates the Catmull-Clark subdivision point ignoring all cached information.
    This function is typically used in testing and debugging code and 
    in ordinary cases, it is faster and better to call SubdivisionPoint() 
    or GetSubdivisionPoint().
  Parameters:
    subdivision_point - [out]
      The vertex Catmull-Clark subdivision point is returned here.
  */
  bool EvaluateCatmullClarkSubdivisionPoint(
    double subdivision_point[3]
  ) const;

  /*
  Parameters:
   sector_face - [in]
      A face in the sector of interest
    limit_point - [out]
  Returns:
    true if successful
  */
  bool GetSurfacePoint(
    const ON_SubDFace* sector_face,
    class ON_SubDSectorSurfacePoint& limit_point
    ) const;

  bool GetSurfacePoint(
    const ON_SubDFace* sector_face,
    bool bUndefinedNormalIsPossible,
    class ON_SubDSectorSurfacePoint& limit_point
    ) const;

  /*
  Description:
    If there is a saved limit surface point, then its location is returned in surface_point[].
  Parameters:
    surface_point - [out]
  Returns:
    True if a saved limit surface point is returned.
    False if there is no saved limit surface point. The input value of surface_point[] is not changed.
  */
  bool GetSavedSurfacePoint(
    double surface_point[3]
  ) const;

  bool GetSurfacePoint(
    double surface_point[3]
  ) const;

  /*
  Returns:
    The SubD surface point.
  */
  const ON_3dPoint SurfacePoint() const;

  /*
  Parameters:
    sector_face - [in]
      When the vertex is a crease or corner vertex, different sectors typically
      have different normals and you must specify a face to determine the sector.
    bUndefinedNormalPossible - [in]
      If the SubD control net is degenerate around the vertex, the normal may
      be zero. Pass true if you will accept a zero normal vector. Otherwise
      ON_3dVector::NanVector is returned when a non-zero normal cannot be calculated.
  Returns:
    The SubD surface normal.
  */
  const ON_3dVector SurfaceNormal(
    const ON_SubDFace* sector_face,
    bool bUndefinedNormalPossible
  ) const;

  const ON_SubDSectorSurfacePoint& SectorSurfacePointForExperts() const;

  /*
  Parameters:
    subd_appearance - [in]
      If ON_SubDComponentLocation::ControlNet, then this->ControlNetPoint() is returned.
      If ON_SubDComponentLocation::Surface, then this->SurfacePoint() is returned.
      Otherwise ON_3dPoint::NanPoint is returned.
  */
  const ON_3dPoint Point(ON_SubDComponentLocation subd_appearance) const;


  /*
  Description:
    Save limit surface point and limit normal for future use.
  Parameters:
    bUndefinedNormalIsPossible - [in]
      true if an undefined normal might occur
    surface_point - [in]
  Returns:
    true if successful
  Remarks:
    ClearSavedSubdivisionPoints() clears any saved limit points.
  */
  bool SetSavedSurfacePoint(
    bool bUndefinedNormalIsPossible,
    const ON_SubDSectorSurfacePoint surface_point
    ) const;

  /*
  Description:
    In general, after you modify a vertex you should call VertexModifiedNotification().

    This is an expert user function that clears any saved limit point evaluations for this vertex.
    No saved subdivision points are cleared.
    No modifications are made to attached edges or faces.
  Remarks:
    In general, you should call VertexModifiedNotification() after you modify a vertex.
    Compare with ClearSavedSubdivisionPoints() which clears any subdivision point
    limit point evaluations saved on this vertex.
  */
  void ClearSavedSurfacePoints() const;
   
  /*
  Returns:
    true
      The vertex limit point and at least one sector normal are saved for Catmull-Clark quad subdivision.
  */
  bool SurfacePointIsSet() const;


  const ON_Plane VertexFrame(
    ON_SubDComponentLocation subd_appearance
  ) const;


  /*
  Description:
    Call this function if the vertex is modified. 
    It will clear saved subdivision information on the vertex and neighboring faces and edges that needs to be recalculated.
  */
  void VertexModifiedNofification() const;
  
  /*
  Returns:
    Number of edges attached to this vertex with Edge().m_status.RuntimeMark() = true;
  */
  unsigned int MarkedEdgeCount() const;

  /*
  Description:
    Clears all marks on edges.
  Returns:
    true if all edges are not null.
    false if any edges are null.
  */
  bool ClearEdgeMarks() const;

  /*
  Returns:
    Number of faces attached to this vertex with Face().m_status.RuntimeMark() = true;
  */
  unsigned int MarkedFaceCount() const;


  /*
  Description:
    Clears all marks on faces.
  Returns:
    true if all faces are not null.
    false if any faces are null.
  */
  bool ClearFaceMarks() const;

  /*
  Returns:
    Minimum number of edges for any face attached to this vertex.
  */
  unsigned int MinimumFaceEdgeCount() const;

  /*
  Returns:
    Maximum number of edges for any face attached to this vertex.
  */
  unsigned int MaximumFaceEdgeCount() const;


  /*
  Returns:
    Minimum number of faces for any edge attached to this vertex.
  */
  unsigned int MinimumEdgeFaceCount() const;

  /*
  Returns:
    Maximum number of faces for any edge attached to this vertex.
  */
  unsigned int MaximumEdgeFaceCount() const;

  /*
  Description:
    Expert user tool to unset ON_SubEdge.m_sector_coefficent[] values for
    edges attached to this vertex.
  Parameters:
    relative_edge_end_dex - [in]
      0: unset vertex edge sector coefficient at the end where the edges
      attaches to this vertex.
      1: unset vertex edge sector coefficient at the end where the edges
      attaches to the other vertex.
      2: unset vertex edge sector coefficients at both ends of the edge.
  */
  void UnsetSectorCoefficientsForExperts(
    unsigned int relative_edge_end_dex
  ) const;

private:
  static bool Internal_GetCatmullClarkSubdivisionPoint(
    const class ON_SubDVertex* vertex, // smooth or dart
    double vertex_point[3]
    );

  static unsigned int Internal_GetFacePointSum(
    const ON_SubDFace* face,
    const ON_SubDVertex* vertex,
    double* facePsum // sum of points that are not immediately adjacent to vertex
    );


  /*
  Description:
    Used for smooth and dart vertices when there are faces 
    that use the vertex have different numbers of sides. 
    This typically happen when a quad subd control net is
    being subdivided for the first time.
  Parameters:
    vertex - [in]
    vertex_point - [out]
  Returns:
    true if successful
  */
  static bool Internal_GetGeneralQuadSubdivisionPoint(
    const class ON_SubDVertex* vertex,
    double vertex_point[3]
    );

private:
  void CopyFrom(
    const ON_SubDVertex* src,
    bool bCopyEdgeArray,
    bool bCopyFaceArray,
    bool bCopySurfacePointList,
    bool bCopySymmetrySetNext
    );
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDEdge
//
class ON_CLASS ON_SubDEdge : public ON_SubDComponentBase
{
private:
  friend class ON_Internal_SubDFaceMeshFragmentAccumulator;
  friend class ON_SubDHeap;
  friend class ON_SubDArchiveIdMap;
  friend class ON_SubDVertex;
  friend class ON_SubDFace;

public:
  ON_SubDEdge() = default;
  ~ON_SubDEdge() = default;
  ON_SubDEdge(const ON_SubDEdge&) = default;
  ON_SubDEdge& operator=(const ON_SubDEdge&) = default;

public:
  unsigned int EdgeId() const;

public:
  /*
  Description:
    Clears saved subdivision and limit surface information for this edge.
    Attached vertices and faces are not modified.
  */
  void ClearSavedSubdivisionPoints() const;  

  /*
  Description:
    Clears saved subdivision and limit surface information for this edge.
  Parameters:
    bClearNeighborhood - [in]
      If true, all vertices and faces attached to this edge are also cleared.
  */
  void ClearSavedSubdivisionPoints(
    bool bClearNeighborhood
  ) const;

public:
  static const ON_SubDEdge Empty;
  
  bool Write (
    class ON_BinaryArchive& archive
    ) const;

  static bool Read (
    class ON_BinaryArchive& archive,
    class ON_SubD& subd,
    class ON_SubDEdge*& edge
    );
  
  /*
  Parameters:
    bIncludeVertices - [in]
      If true, then attached vertices are included.
    bIncludeFaces - [in]
      If true, then attached faces are included.
  Returns:
    A ON_ComponentStatusLogicalOr() of this vertex's status and the 
    specified attached components.
  See Also:
    ON_SubDComponentBase::Status()
  */
  const ON_ComponentStatus NeighborhoodStatusLogicalOr(
    bool bIncludeVertices,
    bool bIncludeFaces
  ) const;

  /*
  Description:
    Apply a transformation matrix to edge geometry information.

  Parameters:
    bTransformationSavedSubdivisionPoint - [in]
      If the transformation is being applied to every vertex, edge and
      face in every level of a subdivision object, and the transformation
      is an orientation preserving isometry (rotation, translation, ...),
      then set bTransformationSavedSubdivisionPoint = true to apply the
      transformation to saved subdivision and saved limit point information.
      In all other cases, set bTransformationSavedSubdivisionPoint = false
      and any saved subdivision points or saved limit points will be
      deleted.  When in doubt, pass false.

    xform - [in]
  */
  bool Transform(
    bool bTransformationSavedSubdivisionPoint,
    const class ON_Xform& xform
    );

  const ON_BoundingBox ControlNetBoundingBox() const;

  /// <summary>
  /// Get a SHA-1 hash that is useful in detecting when an edge's 
  /// connections to attached vertices or faces have been changed.
  /// See also ON_SubDEdge::TopologyCRC32() which, in practice,
  /// is just as reliable as the hash.
  /// </summary>
  /// <param name="bIncludeSubdivisionProperties">
  /// Pass true if you want to include nontopological subdivision properties
  /// (tags, sharpnesses, control net points) 
  /// that help determine the edge's subdivision point in the hash.
  /// </param>
  /// <returns>
  /// A SHA-1 hash of the edge's id and the ids of the vertices and faces attached to this edge.
  /// </returns>
  const ON_SHA1_Hash TopologyHash(bool bIncludeSubdivisionProperties) const;

  /// <summary>
  /// Get a 32 bit CRC that is useful in detecting when an edge's 
  /// connections to attached vertices or faces have been changed.
  /// </summary>
  /// <param name="bIncludeSubdivisionProperties">
  /// Pass true if you want to include nontopological subdivision properties
  /// (tags, sharpnesses, control net points) 
  /// that help determine the edge's subdivision point in the CRC.
  /// </param>
  /// <returns>
  /// A 32 bit CRC = this->TopologyHash(bIncludeSubdivisionProperties).CRC32(0).
  /// </returns>
  ON__UINT32 TopologyCRC32(bool bIncludeSubdivisionProperties) const;

  const ON_Plane CenterFrame(
    ON_SubDComponentLocation subd_appearance
  ) const;



  /*
  Description:
    Call this function if the edge is modified and it will clear any
    cached subdivision information that needs to be recalculated.
  */
  void EdgeModifiedNofification() const;

  /*
  Description:
    Expert user tool to unset sector coefficients.
  */
  void UnsetSectorCoefficientsForExperts() const;

  /*
  Description:
    Expert user tool to set mutable sector coefficients.
  Returns:
    True if values were modified.
  */
  bool UpdateEdgeSectorCoefficientsForExperts(
    bool bUnsetEdgeSectorCoefficientsOnly
    ) const;

public:
  const ON_COMPONENT_INDEX ComponentIndex() const;
  const ON_SubDComponentPtr ComponentPtr() const;

public:
  // m_prev_edge, m_next_edge must be the first data members of ON_SubDEdge
  const class ON_SubDEdge* m_prev_edge = nullptr; // linked list of edges on this level
  const class ON_SubDEdge* m_next_edge = nullptr; // linked list of edges on this level

public:
  // When checking the edge tag, it is important to consider what
  // should happen in the ON_SubDEdgeTag::SmoothX case.  It is strongly
  // suggested that you use the member functions ON_SubDEdge::IsSmooth()
  // and ON_SubDEdge::IsCrease() instead of comparing m_edge_tag to 
  // ON_SubDEdgeTag values.
  ON_SubDEdgeTag m_edge_tag = ON_SubDEdgeTag::Unset;

private:
  unsigned char m_reserved1 = 0;
  unsigned short m_reserved2 = 0;

public:
  // Array of m_face_count faces.
  //
  //  The first two are in m_face2[0] and m_face2[1].
  //  When m_face_count > 3, the third and additional faces
  //  are in m_facex[0], ..., m_facex[m_face_count-3];
  //
  //  The value of ON_SubDFacePtr.FaceDirection() is 0 if the
  //  edge's natural orientation from m_vertex[0] to m_vertex[1]
  //  agrees with the face's boundary orientation.
  //
  //  The value of ON_SubDFacePtr.FaceDirection() is 1 if the
  //  edge's natural orientation from m_vertex[0] to m_vertex[1]
  //  is opposited the face's boundary orientation.
  enum : unsigned int
  {
    MaximumFaceCount = 0xFFF0U
  };
  unsigned short m_face_count = 0;
  unsigned short m_facex_capacity = 0;
  ON_SubDFacePtr m_face2[2] = {};
  ON_SubDFacePtr* m_facex = nullptr;

  // m_vertex[0] = vertex at the start of the edge.
  // m_vertex[1] = vertex at the end of the edge.
  const class ON_SubDVertex* m_vertex[2] = {};

  // NOTE:
  // The sector coefficient is a property of a smooth edge end 
  // that is constant throughout subdivision. It exists at ends of
  // smooth edges that are attached to dart, crease, or corner vertices.
  // In all other cases the sector coefficient is ignored.
  // In particular crease edges and the ends of smooth edges 
  // attached to smooth vertices do not have a sector coefficient.
  // 
  // The ON_SubDSectorType class provides three static functions that
  // calculate sector coefficients:
  // ON_SubDSectorType::DartSectorCoefficient()
  // ON_SubDSectorType::CreaseSectorCoefficient()
  // ON_SubDSectorType::CornerSectorCoefficient()
  // 
  // If the value of vertex->m_vertex_tag is not ON_SubDVertexTag::Smooth,
  // then that vertex is "tagged". 
  //
  // If the value of m_edge_tag is ON_SubDEdgeTag::Crease,
  // then m_sector_coefficient[] should be {0,0}.  
  // In any case m_sector_coefficient[] values are ignored and the
  // midpoint of the edge is the location of the edge.s subdivision point.
  // The edge's subdivision vertex will be tagged as ON_SubDVertexTag::Crease
  // and both subdivision edges will be tagged as ON_SubDEdgeTag::Crease.
  //
  // If the value of m_edge_tag is ON_SubDEdgeTag::Smooth
  // and neither end vertex is tagged, then m_sector_coefficient[] should be {0,0}.  
  // In any case m_sector_coefficient[] values are ignored on smooth edges
  // with smooth vertices at both ends.
  // The edge's subdivision vertex will be tagged as ON_SubDVertexTag::Smooth
  // and both subdivision edges will be tagged as ON_SubDEdgeTag::Smooth.
  //
  // If the value of m_edge_tag is ON_SubDEdgeTag::Smooth and
  // exactly one end vertex is tagged, then the m_sector_coefficient[]
  // value for the tagged end is calculated by ON_SubDSectorType::SectorCoefficient().
  // tagged_coefficient*tagged_vertex + (1.0 - tagged_coefficient)*untagged_vertex
  // is used when combining the edge ends.
  // The edge's subdivision vertex will be tagged as ON_SubDVertexTag::Smooth
  // and both subdivision edges will be tagged as ON_SubDEdgeTag::Smooth.
  //
  // If the value of m_edge_tag is ON_SubDEdgeTag::SmoothX, then the edge
  // must have exactly two neighboring faces,
  // both vertices must be tagged and the m_sector_coefficient[]
  // values are calculated by ON_SubDSectorType::SectorCoefficient().
  // When the edge is subdivided, the midpoint of the edge is the 
  // location of the edge.s subdivision point.
  // The edge's subdivision vertex will be tagged as ON_SubDVertexTag::Smooth
  // and both subdivision edges will be tagged as ON_SubDEdgeTag::Smooth.
  //
  // If the value of m_edge_tag is ON_SubDEdgeTag::Smooth
  // and both end vertices are tagged, that is a severe error
  // condition and the edge is subdivided at its midpoint.
  //
  // If the value of m_edge_tag is ON_SubDEdgeTag::SmoothX
  // and both end vertices are not tagged, that is a severe error
  // condition and the edge is subdivided at its midpoint.
  //
  // m_sector_coefficient[tagged_end] = 1/2 + 1/3*cos(theta_k)
  // where "theta_k" is the tagged end's "theta_k", which depends on the vertex tag (dart/crease/corner), 
  // the number of faces k in the sector, and the control net crease angle alpha when the tagged end is a corner.
  // Dart:   theta_k = 2 * Pi / k
  // Crease: theta_k = Pi / k
  // Corner: theta_k = alpha / k
  //
  // The name "sector coefficient" is used because the value is a property of the
  // vertex's sector (every smooth edge inside a vertex sector has the same value at the tagged vertex).
  // The sector coefficient does not change which a subdivision is applied.
  // 
  // ------------------------------
  // 2022-02-09, Pierre C, RH-67377
  // ------------------------------
  // Wrong values in 3dm files created by OpenNURBS 7.16 and before, fixed in 7.17.
  // 
  // Since 2015-02-20,
  // ON_SubDSectorType::CornerSectorThetaFromCornerAngle(unsigned int sector_face_count, double corner_sector_angle_radians)
  // had been incorrectly computing theta as:
  // corner_sector_theta = corner_sector_angle_radians / (2 * sector_face_count)
  // instead of:
  // corner_sector_theta = corner_sector_angle_radians / sector_face_count.
  // 
  // This is fixed as of Rhino 7.17, but 3dm files created before this version saved the incorrect value.
  // 
  // This changes the coefficients saved in the SubD edge, and in the 3dm files.
  // Rhino recomputes all m_sector_coefficients cached in the SubD edges when
  // adding a SubD to a document, so all values are now correct. This changes 
  // SubD subdivision, meshing, limit surface, and limit point editing results, 
  // for SubDs that have a smooth edge connected to a corner vertex.
  // 
  // If you are using this value from a SubD in a 3dm file created by Rhino 7.16 or earlier,
  // without adding the SubD to a Rhino document using CRhinoSubDObject::SetSubD(ON_SubDRef subd_ref),
  // you need to recompute all sector coefficients using subd->UpdateAllTagsAndSectorCoefficients(true);
  mutable double m_sector_coefficient[2] = {};

private:
  // For a smooth edge, m_sharpness is the edge's sharpness.
  // Edge sharpenss has no meaning for edges with a crease tag.
  // ON_SubDEdge::Sharpness() comments for details. 
  ON_SubDEdgeSharpness m_sharpness = ON_SubDEdgeSharpness::Smooth;

public:

  /// <summary>
  /// Gets the edge's sharp subdivision point and returns the average of the edge's sharpnesses.
  /// The final subdivision point is (sharpness &gt;= 1.0) ? sharp_subdivision_point : (1.0-sharpness)(smooth subdivsion point)+sharpness*sharp_subdivision_point.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <param name="sharp_subdivision_point">
  /// If the returned sharpness is &gt; 0,
  /// then the sharp subdivision point (=edge->ControlNetCenterPoint()) is returned. 
  /// Otherwise ON_3dPoint::NanPoint is returned.
  /// 
  /// The relationship between  
  /// 3d point C = ordinary Catmull-Clark edge subdivision point,
  /// 3d point P = sharp_subdivision_point,
  /// s = this->GetSharpSubdivisionPoint(P), and
  /// 3d point E = this->SubdivisionPoint() is
  /// E = (s >= 1.0) ? P : ((s > 0.0) ? (s*P + (1-s)*C) : C);
  /// 
  /// NOTE WELL: when the returned value is zero, S is ON_3dPoint::NanPoint and any
  /// calculation using S will results in nans.
  /// </param>
  /// <returns>
  /// If the edge is sharp, a value &gt; 0 and &lt; ON_SubDEdgeSharpness::MaximumValue is returned.
  /// Otherwise 0.0 is returned and sharp_subdivision_point = ON_3dPoint::NanPoint.
  /// </returns>
  double GetSharpSubdivisionPoint(
    ON_3dPoint& sharp_subdivision_point
  ) const;

private:
  // Cached limit curve
  // GetEdgeSurfaceCurveControlPoints( bUseSavedSurfacePoint=true ) can change the value of m_limit_curve.
  // If 0 != ON_SUBD_CACHE_LIMIT_FLAG(m_saved_points_flags), then
  // m_limit_curve is the edge's limit surface curve.
  // The memory is managed by the parent ON_SubD. 
  // If 0 == ON_SUBD_CACHE_LIMIT_FLAG(m_saved_points_flags),
  // then any information in m_limit_mesh_fragments is dirty
  // and should not be used.
  // ClearSavedSubdivisionPoints() zeros
  // the appropriate bit of m_saved_points_flags.

  mutable class ON_SubDEdgeSurfaceCurve* m_limit_curve = nullptr;

public:

  /*
  Returns:
    Number of distinct non-nullptr vertices.
    If the edge is valid, this will be 2.
  */
  unsigned int VertexCount() const;

  /*
  Parameters:
    evi - [in]
       0 or 1
  Returns:
    If evi is 0 or 1 and m_vertex[evi] is not nullptr, then m_vertex[evi]->m_id is returned. Otherwise 0 i returned.
  */
  unsigned int VertexId(
    unsigned evi
  ) const;

  /*
  Parameters:
    evi - [in]
       0 or 1
  Returns:
    If evi is 0 or 1, then m_vertex[evi] is returned. Otherwise nullptr is returned.
  */
  const class ON_SubDVertex* Vertex(
    unsigned evi
  ) const;

  unsigned int VertexArrayIndex(
    const class ON_SubDVertex* v
  ) const;


  /*
  Description:
    Return the vertex at the other end of the edge.
  Parameters:
    vertex - [in]
      A vertex referenced in the edge's m_vertex[] array.
  Returns:
    If vertex is not nullptr and exactly one of m_vertex[] is equal to vertex,
    then the other m_vertex[] pointer is returned.
    In any other case, nullptr is returned.
  See Also:
    ON_SubDEdge.NeighborFace()
  */
  const class ON_SubDVertex* OtherEndVertex(
    const class ON_SubDVertex* vertex
  ) const;


  unsigned int FaceCount() const;

  /// <summary>
  /// EdgeType() is typically used to generate text descriptions and
  /// in selection filtering. 
  /// Do not confuse EdgeType() and EdgeTag().
  /// </summary>
  /// <returns>
  /// If the edge has a valid combination of face count, tag, and sharpness properties,
  /// then the corresponding type is returned.
  /// Otherwise, ON_SubDEdgeType::Invalid is returned.
  /// </returns>
  ON_SubDEdgeType EdgeType() const;

  /*
  Parameters:
    bRequireSameFaceOrientation - [in]
      If true, the attached faces must use the edge with opposite directions (oriented manifold).
  Returns:
    True if the edge has two distinct faces.
  */
  bool HasInteriorEdgeTopology(
    bool bRequireOppositeFaceDirections
  ) const;

  /*
  Parameters:
    bRequireSameFaceOrientation - [in]
      If true, the attached faces must use the edge with opposite directions (oriented manifold).
  Returns:
    True if the edge has two distinct faces.
  */
  bool HasBoundaryEdgeTopology() const;

  const ON_SubDFacePtr FacePtr(
    unsigned int i
    ) const;

  const ON_SubDFacePtr FacePtrFromFace(
    const class ON_SubDFace* f
    ) const;

  const class ON_SubDFace* Face(
    unsigned int i
    ) const;

  ON__UINT_PTR FaceDirection(
    unsigned int i
    ) const;

  unsigned int FaceArrayIndex(
    const class ON_SubDFace* f
    ) const;

  /*
  Description:
    Expert user tool to remove a face from the edges's face array.
  Remarks:
    Does not modify the face. If the edge is referenced in the face's edge array,
    then the edge must be removed from the face's edge array.
  */
  bool RemoveFaceFromArray(
    const ON_SubDFace* f
    );

  /*
  Description:
    Expert user tool to remove a face from the edges's face array.
  Remarks:
    Does not modify the face.  If the edge is referenced in the face's edge array,
    then the edge must be removed from the face's edge array.
  */
  bool RemoveFaceFromArray(
    unsigned int i,
    ON_SubDFacePtr& removed_face
    );

  /*
  Description:
    Expert user tool to add a face from the edges's face array.
  Remarks:
    Does not modify the face.  If the edge is not referenced in the face's edge array,
    then the edge must be inserted in the correct location in the faces array.
    If you are creating a non-manifold SubD, you must first reserve m_facex[]
    capacity by calling ON_SubD::GrowEdgeFaceArray().
  */
  bool AddFaceToArray(
    ON_SubDFacePtr face_ptr
  );

  /*
  Description:
    Expert user tool to replace reference to old_face with a reference to new_face.
    Existing orientation is copied.  No changes are made to old_face and new_face and
    their edge references must be updated accordingly.
  Parameters:
    old_face = [in]
      Cannot be nullptr.
    new_face = [in]
      If new_face is nullptr, old_face is simply removed.
  Returns:
    If the replacement was successful, then the m_faces[] array index where old_face/new_face replacement occurred is returned.
    Otherwise ON_UNSET_UINT_INDEX is returned.
  Remarks:
    No modifications are made to old_face or new_face.
  */
  unsigned int ReplaceFaceInArray(
    const ON_SubDFace* old_face,
    const ON_SubDFace* new_face
  );

  /*
  Parameters:
    vertex0 - [in]
    vertex1 - [in]
    bIgnoreOrientation - [in]
      If false, then the returned edge must have vertices (vertex0, vertex1).
      If true, then the returned edge may have vertices (vertex0, vertex1) or (vertex1, vertex0).
  Returns:
    If an edge connects the input vertices, it is returned. Otherwise nullptr is returned.
  */
  static const ON_SubDEdge* FromVertices(
    const ON_SubDVertex* vertex0,
    const ON_SubDVertex* vertex1,
    bool bIgnoreOrientation
  );

  static const ON_SubDEdgePtr FromVertices(
    const ON_SubDVertex* vertex0,
    const ON_SubDVertex* vertex1
  );

  /*
  Parameters:
    i - [in]
      0 or 1.
  Returns:
    If i is 0 or 1 and vertex[i] is set, then vertex[i]->ControlNetPoint() is returned. 
    Otherwise ON_3dPoint::NanPoint is returned.
  */
  const ON_3dPoint ControlNetPoint( unsigned int i ) const;

  const ON_Line ControlNetLine() const;

  /*
  Returns:
    If vertices are set, then the vector from m_vertex[0]->ControlNetPoint() 
    to m_vertex[1]->ControlNetPoint() is returned.
    Otherwise ON_3dVector::NanVector is returned.
  */
  const ON_3dVector ControlNetDirection() const;

  /*
  Returns:
    If vertices are set and v is an end of the edge,
    then the vector from v to OtherEndVertex(v) is returned.
    Otherwise ON_3dVector::NanVector is returned.
  */
  const ON_3dVector ControlNetDirectionFrom(
    const ON_SubDVertex* v
  ) const;

  /*
  Description:
    Return the neighboring face.
  Parameters:
    face - [in]
      A face referenced in the edge's m_face2[] array.
    bStopAtCrease - [in]
      If true and if m_edge_tag = ON_SubDEdgeTag::Crease, 
      then nullptr is returned.
  Returns:
    If the m_face_count = 2,
    m_edge_tag is smooth or x or passes the crease tag test,
    one of m_face2[0,1] points a face, then
    the neighboring face is returned.
    In any other case, nullptr is returned.
  */
  const ON_SubDFace* NeighborFace(
    const ON_SubDFace* face,
    bool bStopAtCrease
    ) const;

  /*
  Description:
    Return the neighboring face.
  Parameters:
    face - [in]
      A face referenced in the edge's m_face2[] array.
    bStopAtCrease - [in]
      If true and if m_edge_tag = ON_SubDEdgeTag::Crease, 
      then nullptr is returned.
  Returns:
    If the m_face_count = 2,
    m_edge_tag is smooth or x or passes the crease tag test,
    one of m_face2[0,1] points a face, then
    the neighboring face is returned.
    In any other case, ON_SubDFacePtr::Null is returned.
  */
  const ON_SubDFacePtr NeighborFacePtr(
    const ON_SubDFace* face,
    bool bStopAtCrease
    ) const;

  /*
  Parameters:
    edge_vertex_index - [in]
      0 or 1 identifying which end of this edge to check.
    i - [in]
      Index of the face in this edge's face array.
  Returns:
    The edge adjacent to this edge in this->Face(i).
    The orientation is with respect to this->Face(i).
  */
  const ON_SubDEdgePtr AdjacentEdgePtr(
    unsigned int edge_vertex_index,
    unsigned int i
    ) const;

  const ON_SubDEdge* AdjacentEdge(
    unsigned int edge_vertex_index,
    unsigned int i
    ) const;
  /*
  Returns:
    True if m_edge_tag is ON_SubDEdgeTag::Smooth or ON_SubDEdgeTag::SmoothX.
    False in all other cases.
  */
  bool IsSmooth() const;
  
  /*
  Returns:
    True if m_edge_tag is ON_SubDEdgeTag::Smooth.
  Remarks:
    Expert user function.
    This is used in rare cases when level 0 edges tagged as ON_SubDEdgeTag::SmoothX
    need special handling in low level evaluation code. Typical SDK level functions
    and anything related to runtime user interface should call IsSmooth().
  */
  bool IsSmoothNotX() const;
  
  /*
  Returns:
    True if m_edge_tag is ON_SubDEdgeTag::SmoothX.
  Remarks:
    Expert user function.
    This is used in rare cases when level 0 edges tagged as ON_SubDEdgeTag::SmoothX
    need special handling in low level evaluation code. Typical SDK level functions
    and anything related to runtime user interface should call IsSmooth().
    An edge tagged as "X" can occur at level 0. It is subdivided as a smooth
    vertex and both of its end vertices are tagged as ON_SubDVertexTag::Crease, 
    ON_SubDVertexTag::Corner, or ON_SubDVertexTag::Dart. 
    This tag cannot appear at level N with N >= 1.
  */
  bool IsSmoothX() const;

  /// <summary>
  /// Sharp edges are a blend between smooth edges and crease edges. 
  /// The limit surface has a continuous normal along a sharp edge.
  /// A sharp edge has a smooth tag, 
  /// has sharpness &gt; 0 at at least one end, 
  /// and has sharpness &lt; ON_SubDEdgeSharpness::MaximumValue at at least one end.
  /// Sharpness has no meaning for edges with crease tags.
  /// Both sharpness values are zero for an ordinary smooth edge.
  /// Edge sharpness steadily decreases during subdivision and becomes zero after at most ON_SubDEdgeSharpness::MaximumValue subdivisions.
  /// </summary>
  /// <returns>
  /// True if the edge is tagged as smooth, 
  /// and has at least one end with sharpness &gt; 0 and &lt; ON_SubDEdgeSharpness::MaximumValue.
  /// </returns>
  bool IsSharp() const;

  /// <summary>
  /// Crease edges have tag = ON_SubDEdgeTag::Crease. Sharp edges have
  /// tag = ON_SubDEdgeTag::Smooth or ON_SubDEdgeTag::SmoothX and have
  /// nonzero sharpness.
  /// </summary>
  /// <returns>(this->IsCrease() || this->IsSharp()).</returns>
  bool IsCreaseOrSharp() const;

  /// <summary>
  /// Determine if an edge is smooth and is not sharp.
  /// </summary>
  /// <returns>(true == IsSmooth() and false == IsSharp())</returns>
  bool IsSmoothNotSharp() const;

  /// <summary>
  /// An expert user function to determine if an edge tag in ON_SubDEdgeTag::Smooth and is not sharp.
  /// </summary>
  /// <returns>(true == IsSmoothNotX() and false == IsSharp())</returns>
  bool IsSmoothNotXNotSharp() const;

  /// <summary>
  /// Get the edge's sharpness.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <param name="bUseCreaseSharpness">
  /// If the edge is a crease and bUseCreaseSharpness is false, then ON_SubDEdgeSharpness::Smooth is returned.
  /// If the edge is a crease and bUseCreaseSharpness is true, then ON_SubDEdgeSharpness::Crease is returned.
  /// </param>
  /// <returns>
  /// If the edge is smooth, then the sharpness property is returned.
  /// If the edge is a crease and bUseCreaseSharpness is true, then ON_SubDEdgeSharpness::Crease is returned.
  /// In all other cases, ON_SubDEdgeSharpness::Smooth is returned.
  /// </returns>
  const ON_SubDEdgeSharpness Sharpness(
    bool bUseCreaseSharpness
  ) const;

  /// <summary>
  /// Get the edge's sharpness at the end with the specified vertex.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <param name="v">Vertex at an end of the edge</param>
  /// <returns>
  /// If the edge is sharp, the sharpness at the end with the specified vertex is returned.
  /// If the edge is smooth or a crease, 0 is returned.
  /// Otherwise, 0.0 is returned.
  /// </returns>
  /// <returns>The sharpness at the end of the edge with the specified vertex.</returns>
  double EndSharpness(
    const class ON_SubDVertex* v
  ) const;

  /// <summary>
  /// Get the edge's sharpness at the end with the specified vertex.
  /// If the edge is a crease, ON_SubDEdgeSharpness::Smooth is returned.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <param name="evi">End index (0=start or 1=end).</param>
  /// <returns>
  /// If the edge is sharp, the sharpness at the end with the specified by evi is returned.
  /// If the edge is smooth or a crease, 0 is returned.
  /// Otherwise, 0.0 is returned.
  /// </returns>
  /// <returns>The sharpness at the end of the edge specified by evi.</returns>
  double EndSharpness(
    unsigned evi
  ) const;

  /// <summary>
  /// Get the edge's sharpness at the end with the specified vertex.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <param name="evi">End index (0=start or 1=end).</param>
  /// <param name="bUseCreaseSharpness">
  /// If the edge is a crease and bUseCreaseSharpness is false, then ON_SubDEdgeSharpness::Smooth is returned.
  /// If the edge is a crease and bUseCreaseSharpness is true, then ON_SubDEdgeSharpness::Crease is returned.
  /// </param>
  /// <returns>
  /// If the edge is sharp, the sharpness at the end with the specified by evi is returned.
  /// If the edge is smooth or a crease, 0 is returned.
  /// Otherwise, 0.0 is returned.
  /// </returns>
  /// <returns>The sharpness at the end of the edge specified by evi.</returns>
  double EndSharpness(
    unsigned evi,
    bool bUseCreaseSharpness
  ) const;

  /// <summary>
  /// Get the edge sharpenss values for the subdivided edge at the specified end of this edge.
  /// </summary>
  /// <param name="evi">Selects the subdivided edge (0 for the left subdivided edge, 1 for the right subdivided edge) </param>
  /// <param name="bReverseSharpness">Pass true if this edge and the subdividied edge will have opposite orientations. </param>
  /// <returns>Edge sharpness for the subdivided edge.</returns>
  const ON_SubDEdgeSharpness SubdivideSharpness(
    unsigned evi,
    bool bReverseSharpness
  ) const;

  /// <summary>
  /// Get the edge sharpenss values for the subdivided edge at the specified end of this edge.
  /// </summary>
  /// <param name="end_vertex">One of this edge's vertices used to select the subdivided edge.</param>
  /// <param name="bReverseSharpness">Pass true if this edge and the subdividied edge will have opposite orientations. </param>
  /// <returns>Edge sharpness for the subdivided edge.</returns>
  const ON_SubDEdgeSharpness SubdivideSharpness(
    const class ON_SubDVertex* end_vertex,
    bool bReverseSharpness
  ) const;

  /// <summary>
  /// This tool is for expert users and internal use. 
  /// A collection of ON_SubD::SetEdgeSharpness() functions provide the easiest way to
  /// set and change edge sharpness.
  /// Set the edge sharpness values to (sharpness[0],sharpness[1]).
  /// The interval values must be &gt;= 0 and &lt;= ON_SubDEdgeSharpness::MaximumValue.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <param name="sharpness">End sharpenss values.</param>
  void SetSharpnessForExperts(
    ON_SubDEdgeSharpness sharpness
  );

  /// <summary>
  /// This tool is for expert users and internal use. 
  /// Use ON_SubD::ClearEdgeSharpness() to remove all sharp edges from a SubD.
  /// Sets the edge sharpness to ON_EdgeSharpness::Zero.
  /// </summary>
  /// <returns>True if there were changes to the edge.</returns>
  bool ClearSharpnessForExperts();

  /*
  Returns:
    True if m_edge_tag is ON_SubDEdgeTag::Crease.
  */
  bool IsCrease() const;

  /*
  Returns:
    True if m_edge_tag is ON_SubDEdgeTag::Crease and both of its end vertices 
    are tagged as ON_SubDVertexTag::Crease, or ON_SubDVertexTag::Corner. 
  */
  bool IsHardCrease() const;

  /*
  Returns:
    True if m_edge_tag is ON_SubDEdgeTag::Crease and at least one of its end vertices 
    are tagged as ON_SubDVertexTag::Dart.
  */
  bool IsDartCrease() const;

  /*
  Returns:
    0: end vertices are not tagged as darts
    1: one end vertex is tagged as a dart.
    2: both end vertices are tagged as a darts.
  */
  unsigned int DartCount() const;

  /*
  Returns:
    bitwise or of applicable ON_ComponentAttributes::EdgeAttributes values.
  Remarks:
    ON_ComponentAttributes::EdgeAttributes has subsets of mutually exclusive
    edge attributes.  If the edge is valid, then exactly one bit from each 
    mutually exclusive set of properties will be set.
    If an edge is not valie, then all bits for a set may be clear. 
    For example, if the edge has nullptr values in m_vertex[] 
    or the vertex control point locations are unset or nan, 
    then neither the ON_ComponentAttributes::EdgeAttributes::Open bit
    nor ON_ComponentAttributes::EdgeAttributes::Closed bit will be set.
  */
  unsigned int EdgeAttributes() const;

  /*
  Parameters:
    subdivision_point - [out]
  Returns:
    true if successful
  */
  bool GetSubdivisionPoint(
    double subdivision_point[3]
    ) const;

  /// <summary>
  /// Get the SubD edge Catmull-Clark subdivision point.
  /// </summary>
  /// <returns>Catmull-Clark edge subdivision point.</returns>
  const ON_3dPoint SubdivisionPoint() const;


  /*
  Description:
    Evaluates the Catmull-Clark subdivision point ignoring all cached information.
    This function is typically used in testing and debugging code and
    in ordinary cases, it is faster and better to call SubdivisionPoint()
    or GetSubdivisionPoint().
  Parameters:
    subdivision_point - [out]
      The edge Catmull-Clark subdivision point is returned here.
  */
  bool EvaluateCatmullClarkSubdivisionPoint(
    double subdivision_point[3]
  ) const;

  const ON_3dPoint ControlNetCenterPoint() const;
  const ON_3dVector ControlNetCenterNormal(
    unsigned int edge_face_index
  ) const;

  bool EdgeSurfaceCurveIsSet() const;



  /*
  Parameters:
    edge_vertex_index - [in]
      0 or 1
    edge_ptr0 - [out]
    edge_ptr1 - [out]
      Crease edges that bound the sector containing this edge.
      The direction value of the edge pointer identifies the end
      of the sector boundary edge this->at m_vertex[edge_vertex_index].
  Returns:
    Number of faces in the sector.
  */
  unsigned int GetSectorBoundaryEdges(
    unsigned int edge_vertex_index,
    ON_SubDEdgePtr* edge_ptr0,
    ON_SubDEdgePtr* edge_ptr1
    ) const;

  /*
  Returns:
    Set bTagged[i] = m_vertex[0]->IsDartOrCreaseOrCorner().
    0: bTagged[0] is true and bTagged[1] is false.
    1: bTagged[0] is false and bTagged[1] is true.
    2: bTagged[0] and Tagged[1] are both true.
    3: bTagged[0] and Tagged[1] are both false.
  */
  unsigned int TaggedEndIndex() const;

  /*
  Returns:
    Number of end vertices with Vertex().m_status.RuntimeMark() = true;
  */
  unsigned int MarkedVertexCount() const;

  /*
  Returns:
    Number of faces attached to this edge with Face().m_status.RuntimeMark() = true;
  */
  unsigned int MarkedFaceCount() const;

private:
  static unsigned int GetFacePointSum(
    const ON_SubDFace* face,
    const ON_SubDEdge* edge,
    double* facePsum // sum of face vertex points not on the edge
    );

private:
  void CopyFrom(
    const ON_SubDEdge* src,
    bool bReverseEdge,
    bool bCopyVertexArray,
    bool bCopyFaceArray,
    bool bCopySymmetrySetNext
    );
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDFace
//
class ON_CLASS ON_SubDFace : public ON_SubDComponentBase
{
private:
  friend class ON_Internal_SubDFaceMeshFragmentAccumulator;
  friend class ON_SubDHeap;
  friend class ON_SubDArchiveIdMap;
  friend class ON_SubDVertex;
  friend class ON_SubDEdge;

public:
  ON_SubDFace() = default;
  ~ON_SubDFace() = default;
  ON_SubDFace(const ON_SubDFace&) = default;
  ON_SubDFace& operator=(const ON_SubDFace&) = default;

public:
  unsigned int FaceId() const;

public:
  /*
  Description:
    Clears saved subdivision and limit surface information for this face.
    Attached edges and vertices are not modified.
  */
  void ClearSavedSubdivisionPoints() const;

  /*
  Description:
    Clears saved subdivision and limit surface information for this face.
  Parameters:
    bClearNeighborhood - [in]
      If true, all vertices, edges and face attached to this face are also cleared.
  */
  void ClearSavedSubdivisionPoints(
    bool bClearNeighborhood
  ) const;

public:
  static const ON_SubDFace Empty;

  bool Write(
    class ON_BinaryArchive& archive
  ) const;

  static bool Read(
    class ON_BinaryArchive& archive,
    class ON_SubD& subd,
    class ON_SubDFace*& face
  );


  /*
  Parameters:
    bIncludeVertices - [in]
      If true, then attached vertices are included.
    bIncludeEdges - [in]
      If true, then attached edges are included.
  Returns:
    A ON_ComponentStatusLogicalOr() of this vertex's status and the
    specified attached components.
  See Also:
    ON_SubDComponentBase::Status()
  */
  const ON_ComponentStatus NeighborhoodStatusLogicalOr(
    bool bIncludeVertices,
    bool bIncludeEdges
  ) const;

  /*
  Description:
    Apply a transformation matrix to face geometry information.

  Parameters:
    bTransformationSavedSubdivisionPoint - [in]
      If the transformation is being applied to every vertex, edge and
      face in every level of a subdivision object, and the transformation
      is an orientation preserving isometry (rotation, translation, ...),
      then set bTransformationSavedSubdivisionPoint = true to apply the
      transformation to saved subdivision and saved limit point information.
      In all other cases, set bTransformationSavedSubdivisionPoint = false
      and any saved subdivision points or saved limit points will be
      deleted.  When in doubt, pass false.

    xform - [in]
  */
  bool Transform(
    bool bTransformationSavedSubdivisionPoint,
    const class ON_Xform& xform
  );

  /*
  Description:
    Apply a transformation matrix to face geometry information.
    This version transforms the points, normals, curvatures, texture coordinates,
    and colors, if they are kept.
      - Normals are transformed with xformNormals.
      - Texture coordinates are transformed with xformTextures.
          If bKeepTextures is false, texture coordinates are destroyed.
      - Curvatures are transformed with xformCurvatures.
          If bKeepCurvatures is false, curvatures are destroyed.
      - Colors are transformed with xformColors.
          If bKeepColors is false, colors are destroyed.

  Parameters:
    bTransformationSavedSubdivisionPoint - [in]
      If the transformation is being applied to every vertex, edge and
      face in every level of a subdivision object, and the transformation
      is an orientation preserving isometry (rotation, translation, ...),
      then set bTransformationSavedSubdivisionPoint = true to apply the
      transformation to saved subdivision and saved limit point information.
      In all other cases, set bTransformationSavedSubdivisionPoint = false
      and any saved subdivision points or saved limit points will be
      deleted.  When in doubt, pass false.
    bKeepTExtures - [in]
    bKeepCurvatures - [in]
    bKeepColors - [in]
    xform - [in]
    xformNormals - [in]
    xformTextures - [in]
    xformCurvatures - [in]
    xformColors - [in]
  */
  bool Transform(
    bool bTransformationSavedSubdivisionPoint,
    bool bKeepCurvatures,
    bool bKeepTextures,
    bool bKeepColors,
    const ON_Xform& xform,
    const ON_Xform& xformNormals,
    const ON_Xform& xformCurvatures,
    const ON_Xform& xformTextures,
    const ON_Xform& xformColors
  );

  const ON_BoundingBox ControlNetBoundingBox() const;

  /// <summary>
  /// Get a SHA-1 hash that is useful in detecting when a face's 
  /// connections to attached vertices or edges have been changed.
  /// See also ON_SubDFace::TopologyCRC32() which, in practice,
  /// is just as reliable as the hash.
  /// </summary>
  /// <param name="bIncludeSubdivisionProperties">
  /// Pass true if you want to include nontopological subdivision properties
  /// (control net points) 
  /// that help determine the faces's subdivision point in the hash.
  /// </param>
  /// <returns>
  /// A SHA-1 hash of the face's id the ids of the vertices and edges attached to this face.
  /// </returns>
  const ON_SHA1_Hash TopologyHash(bool bIncludeSubdivisionProperties) const;

  /// <summary>
  /// Get a 32 bit CRC that is useful in detecting when a face's 
  /// connections to attached vertices or edges have been changed.
  /// </summary>
  /// <param name="bIncludeSubdivisionProperties">
  /// Pass true if you want to include nontopological subdivision properties
  /// (control net points) 
  /// that help determine the faces's subdivision point in the hash.
  /// </param>
  /// <returns>
  /// A 32 bit CRC = this->TopologyHash(bIncludeSubdivisionProperties).CRC32(0).
  /// </returns>
  ON__UINT32 TopologyCRC32(bool bIncludeSubdivisionProperties) const;

  /*
  Parameters:
    vertex_list - [in]
      vertices in face boundary.
      vertex_list[0] can be any vertex in the face boundary and vertex_list[] can traverse the
      boundary in order or reversed.
  Return:
    If there is a face whose boundary vertex list is face_vertices[], then that face is returned and 
    ON_SubDFacePtr.FaceDirection() indicates the orientation of face_vertices[].
    Otherwise ON_SubDFacePtr::Null is returned.
  */
  static const ON_SubDFacePtr FromVertices(
    const ON_SimpleArray< const ON_SubDVertex* >& vertex_list
  );
  static const ON_SubDFacePtr FromVertices(
    const ON_SubDVertex*const* vertex_list,
    size_t face_vertices_count
  );


  const ON_COMPONENT_INDEX ComponentIndex() const;
  const ON_SubDComponentPtr ComponentPtr() const;

  /*
  Description:
    Call this function if the face is modified and it will clear any
    cached subdivision information that needs to be recalculated.
  */
  void FaceModifiedNofification() const;

public:
  // m_prev_face, m_next_face must be the first data members of ON_SubDFace
  const class ON_SubDFace* m_prev_face = nullptr;  // linked list of faces on this level
  const class ON_SubDFace* m_next_face = nullptr;  // linked list of faces on this level

private:
  unsigned int m_reserved1 = 0;

private:
  // If non zero, m_pack_id identifies the packed group of faces this faces belongs to.
  // Faces that are not quads are never in grouped with other faces.
  // When possible, quads are packed into groups that form larger rectangular regions.
  // ON_SubD::Packfaces() creates the packing information.
  // Packing information is saved in 3dm files.
  unsigned int m_pack_id = 0;

  // Location of this face's pack rectin normalized coordinates
  // Each face is assigned a unique rectangle in the unit square (0,1)x(0,1). 
  // Groups of quad faces packed together.
  // If faces are added to an existing subd, the pack rects for the entire subd must be recalculated.
  // If faces in a quad group are removed from a subd, the pack rects for the entire subd must be recalculated.
  double m_pack_rect_origin[2] = {ON_DBL_QNAN};
  double m_pack_rect_size[2] = {ON_DBL_QNAN};
  unsigned int m_reserved2 = 0; // m_packed_rect_u = 0;
  unsigned int m_reserved3 = 0; // m_packed_rect_v = 0;

  enum PackStatusBits : unsigned char
  {
    ZeroPackStatusBits = 0,

    /////////////////////////////////////////////////////////////////////
    //
    // Pack rectangle status
    //

    // 4 ways the pack rectangle can be rotated for a face when packed texture coordinates are 
    // calculated from the packing rectangle.
    // These enum values must be 0,1,2,3 because these values are used in arithmetic formulae.
    // Rotation is used to keep pac rect coordinates continuous in quad packs containing faces
    // with inconsistent topological orientations, which is the most common situation.
    PackingRotate0 = 0,
    PackingRotate90 = 1,
    PackingRotate180 = 2,
    PackingRotate270 = 3,

    // mask for the bits used to encode the packing rotation
    PackingRotateMask = 3,

    // bit used to determine if the values in m_packed_coordinate_origin[] and m_packed_coordinate_delta[]
    // are set to valid values.
    PackRectSet = 0x04U,

    PackingBitsMask = 0x07U,
    NotPackingBitsMask = 0xF8U,

    // add other non-mutable bits here
  };

  // NOT mutable on purpose
  unsigned char m_pack_status_bits = 0;

private:
  enum TextureStatusBits : unsigned char
  {
    ZeroTextureStatusBits = 0,

    // TexturePoints bits
    TexturePointsSet = 0x01U, // set when face has set custom texture coordinates
    TexturePointsBitsMask = 0x01U,
    NotTexturePointsBitsMask = 0xFEU,

    // add other mutable bits here
  };
  // mutable because rendering code frequently modifis const objects in the Rhino.
  mutable unsigned char m_texture_status_bits = 0;

public:
  /*
  Returns:
    0: unset pack id.
    > 0: set pack id.
  Remarks:
    Faces that share the same PackId() must be neighboring quad faces that form a larger
    rectangular grid of quads. Single faces that are not quads and isolated quads cannot
    share a pack id with other faces.
  */
  unsigned int PackId() const;

  /*
  Returns:
    true if the pack rect is set.
  Remarks:
    Faces that share the same PackId() must be neighboring quad faces that form a larger
    rectangular grid of quads. Single faces that are not quads and isolated quads cannot
    share a pack id with other faces.
  */
  bool PackRectIsSet() const;

  /*
  Returns
    Lower left coordinate of this face's pack rect in normalized pack rect coordinates.
  */
  const ON_2dPoint PackRectOrigin() const;

  /*
  Returns
    Size of this face's pack rect in normalized pack rect coordinates.
  */
  const ON_2dVector PackRectSize() const;

  /*
  Returns:
    0, 90, 180, or 270
  Remarks:
    This rotation is used to keep pack rect coordinates continuous in quad packs 
    containing faces with inconsistent topological orientations, which is the most
    common situation.
  */
  unsigned PackRectRotationDegrees() const;

  /*
  Returns:
    0, 0.5*ON_PI, ON_PI, or 1.5*ON_PI
  Remarks:
    This rotation is used to keep pack rect coordinates continuous in quad packs
    containing faces with inconsistent topological orientations, which is the most
    common situation.
  */
  double PackRectRotationRadians() const;

  /*
  Parameters:
    bGridOrder - [in]
      false: counter clockwise quad order.
      true: fragment grid order
    corner_index - [in]
      0, 1, 2, or 3
  Returns:
    Specified pack rectangle corner coordinates.
    The pack rect is the (x0,x0+dx) x (y0,y0+dy) rectangle inside the unit square (0,1)x(0,1)
    where (x0,y0) = PackRectOrigin() and (dx,dy) = PackRectSize().
  */
  const ON_2dPoint PackRectCorner(
    bool bGridOrder,
    int corner_index
  ) const;

  /*
  Parameters:
    bGridOrder - [in]
      false: counter clockwise quad order.
      true: fragment grid order
    mesh_fragment_pack_rect_corners - [out]
      Pack rectangle corners for the specified mesh fragment are returned here.
      face_pack_rect_corners[i] = this->PackRectCorner(bGridOrder,i);
  Returns:
    True if the input is valid and the face's pack rectangle corner coordinates were returned.
    False otherwise.
  Remarks:
    Compare with ON_SubDFace.GetMeshFragmentPackRectCorners().
  */
  bool GetFacePackRectCorners(
    bool bGridOrder,
    ON_2dPoint face_pack_rect_corners[4]
  ) const;

  /*
  Parameters:
    bGridOrder - [in]
      false: counter clockwise quad order.
      true: fragment grid order
    fragment_index - [in]
      If the face is a quad (EdgeCount() = 4), then fragment_index must be zero.
      If the face is a n-gon (EdgeCount() = n and n != 4),
      then 0 <= fragment_index < EdgeCount().
    mesh_fragment_pack_rect_corners - [out]
      Pack rectangle corners for the specified mesh fragment are returned here.
      If the face is a quad, mesh_fragment_pack_rect_corners[] are the pack rect texture points for
      the quad corners in the order specified by bGridOrder and standard linear interpolation
      between the 4 corners will produce reasonable texture mapping coordinates.
      If the face is an n-gon, mesh_fragment_pack_rect_corners[0] is the pack rect texture point
      at face->Vertex(fragment_index). For n-gons, the n fragments are assigned non-overlapping rectangular
      subsetsof the face's pack rect. Interpolating between corner values will not produce good texture
      mapping coordinates. Pack rects are create useful and optimal texture mapping results when the SubD
      is rendered from its mesh fragmantes.
  Returns:
    True if the input is valid and the pack rectangle corner coordinates for the specified mesh fragment were returned.
    False otherwise.
  Remarks:
    A quad face (EdgeCount()=4) is rendered using 1 ON_SubDMeshFragment.
    An n-gon face (EdgeCount()=n and n != 4) is rendered using n ON_SubDMeshFragments. These n fragments correspond
    the SubD quads the n-gon face would generate with one level of Catmull-Clark subdivision.
  */
  bool GetMeshFragmentPackRectCorners(
    bool bGridOrder,
    unsigned int fragment_index,
    ON_2dPoint mesh_fragment_pack_rect_corners[4]
  ) const;

  /*
  Description:
    Sets PackId() to zero.
  Remarks:
    Does not change the values of ON_SubDFace::PackRectOrigin(), ON_SubDFace::PackRectSize(), 
    ON_SubDFace::PackRectRotationDegrees(), or ON_SubDFace::TextureCoordinateType()
    Use ON_SubDFace::ClearPackRect() to clear the pack rectangle.
  */
  void ClearPackId();

  /*
  Description:
    Clears the pack rectangle.
  Remarks:
    Does not change the value of ON_SubDFace::PackId() or ON_SubDFace::TextureCoordinateType()
    Use ON_SubDFace::ClearPackId() to clear the pack id.
  */
  void ClearPackRect();

  /*
  Parameters:
    pack_rect_origin - [in]
      Lower left corner.
      Valid origins have (0 <= origin.x < 1) and (0 <= origin.y < 1)
    pack_rect_size - [in]
      vector from lower left corner to upper right corner.
      Valid deltas have (0 < delta.x, 0 < delta.y, (origin.x+delta.x) <= 1) and (origin.y+delta.y) <= 1.
    packing_rotation_degrees - [in]
      Valid packing_rotation_degrees are a multiple of 90.
  Returns:
    True if the input parameters define a valid pack rectangle.
  */
  static bool IsValidPackRect(
    ON_2dPoint pack_rect_origin,
    ON_2dVector pack_rect_size,
    int packing_rotation_degrees
  );

  /*
  Description:  
    The ON_SubD::PackFaces() function uses this function to set the value of ON_SubDFace::PackId().
    Unless you are an expert and doing something very carefully and very fancy, to not call this function. 
    You must also set the pack rectangle correctly.
  Remarks:
    Faces that share the same PackId() must be neighboring quad faces that form a larger
    rectangular grid of quads. Single faces that are not quads and isolated quads cannot 
    share a pack id with other faces.
  */
  void SetPackIdForExperts(
    unsigned int pack_id
  );

  /*
  Description:
    The ON_SubD::PackFaces() function uses this function to set the face's pack rectangle
    (ON_SubDFace::PackRectOrigin(), ON_SubDFace::PackRectSize(), ON_SubDFace::PackRectRotationDegrees()).
    Unless you are an expert and doing something very carefully and very fancy, to not call this function.
    The lower left corner will be origin, the upper right corner will be delta.
    You must also set the pack id correctly.
  Parameters:
    pack_rect_origin - [in]
      Lower left corner.
      Valid origins have (0 <= origin.x < 1) and (0 <= origin.y < 1)
    pack_rect_size - [in]
      vector from lower left corner to upper right corner.
      Valid deltas have (0 < delta.x, 0 < delta.y, (origin.x+delta.x) <= 1) and (origin.y+delta.y) <= 1.
    packing_rotation_degrees - [in]
      Valid packing_rotation_degrees are a multiple of 90.
  Return:
    True if input is valid and the pack rectangle was set.
    False if the input was not vaie and the pack rectangle coordinates were set to nan.
  */
  bool SetPackRectForExperts(
    ON_2dPoint pack_rect_origin,
    ON_2dVector pack_rect_size,
    int packing_rotation_degrees
  );

  /*
  Description:
    Calculate how a packing rectangle assigned to an ON_SubDFace will
    be subdivided into n sub packing rectangles for an ngon when n >= 5.
  Parameters:
    ngon_edge_count - [in]
      >= 5.
    ngon_face_pack_rect_size - [in]
      ngon_face_pack_rect_size.x > 0 and ngon_face_pack_rect_size.y > 0
      The width and height of the sizeof the ngon's entire packing rectangle.
      This is typically ON_SubD_Face::PackRectSize() once that property is 
      coorectly set.
    ngon_sub_pack_rect_size - [out]
      The size of sub pack rects.
      If input is not valid, then ON_2dVector::ZeroVector is returned.
    ngon_sub_pack_rect_delta - [out]
      The delta from one sub pack rect to the next.
      If input is not valid, then ON_2dVector::ZeroVector is returned.
  Returns:
    When the input is valid, ON_2udex(i,j) is returned and specifies the face's packing 
    rectangle should be divided into i X j sub packing rectangles.
    Otherwise, ON_2udex(0,0) is returned and 
  */
  static const ON_2udex GetNgonSubPackRectSizeAndDelta(
    unsigned int ngon_edge_count,
    ON_2dVector ngon_face_pack_rect_size,
    ON_2dVector& ngon_sub_pack_rect_size,
    ON_2dVector& ngon_sub_pack_rect_delta
  );

  /*
  Parameters:
    pack_rect_distance_in_pixels - [in]
      A (normalized pack rect distance) * ON_SubD::TextureImageSuggestedMinimumSize
  Returns:
    Suggested gap between adjacent pack rects for a texture images
    with width and height >= ON_SubD::TextureImageSuggestedMinimumSize.
    This value will be 0.0 when pack_rect_distance_in_pixels is too
    small to permit a gap of 1 or more pixels without visibly
    adverse effects in a texture map clarity.
  */
  static double PackRectGapInPixels(
    double pack_rect_distance_in_pixels
  );


private:
  // The application specifies a base ON_Material used to render the subd this face belongs to.
  // If m_material_channel_index > 0 AND face_material_id = base.MaterialChannelIdFromIndex(m_material_channel_index)
  // is not nil, then face_material_id identifies an override rendering material for this face.
  // Otherwise base will be used to render this face.
  mutable unsigned short m_material_channel_index = 0;

public:
  /*
  Description:
    Set the per face rendering material channel index.

  Parameters:
    material_channel_index - [in]
      A value between 0 and ON_Material::MaximumMaterialChannelIndex, inclusive.
      This value is typically 0 or the value returned from ON_Material::MaterialChannelIndexFromId().

  Remarks:
    If base_material is the ON_Material assigned to render this subd and
    ON_UUID face_material_id = base_material.MaterialChannelIdFromIndex( material_channel_index )
    is not nil, then face_material_id identifies an override rendering material for this face.
    Otherwise base_material is used to reneder this face.
  */
  void SetMaterialChannelIndex(int material_channel_index) const;

  /*
  Description:
    Remove the per face rendering material channel index.
    The face will use the material assigned to the subd object.
  */
  void ClearMaterialChannelIndex() const;

  /*
  Returns:
    This face's rendering material channel index.

    Remarks:
    If base_material is the ON_Material assigned to render this subd, MaterialChannelIndex() > 0,
    and ON_UUID face_material_id = base_material.MaterialChannelIdFromIndex( face.MaterialChannelIndex() )
    is not nil, then face_material_id identifies an override rendering material for this face.
    Otherwise base_material is used to reneder this face.
  */
  int MaterialChannelIndex() const;

private:
  // The application specifies a base ON_Material used to render the subd this face belongs to.
  // If m_material_channel_index > 0 AND face_material_id = base.MaterialChannelIdFromIndex(m_material_channel_index)
  // is not nil, then face_material_id identifies an override rendering material for this face.
  // Otherwise base will be used to render this face.
  mutable ON_Color m_per_face_color = ON_Color::UnsetColor;

public:

  /*
  Description:
    Set per face color.

  Parameters:
    color - [in]
  */
  void SetPerFaceColor(
    ON_Color color
    ) const;

  /*
  Description:
    Remove per face color setting. The face will use the color assigned to the subd object.
  */
  void ClearPerFaceColor() const;

  /*
  Returns:
    Per face color. A value of ON_Color::UnsetColor indicates the face uses the color assigned to the subd object.
  */
  const ON_Color PerFaceColor() const;

public:
  unsigned int m_level_zero_face_id = 0;   // id of level zero face

public:
  // Array of m_edge_count edges that form the boundary of the face.
  // The edges are in ordered to form a continuous loop.
  //
  //  The first four are in m_edge4[0], ..., m_edge4[3].
  //  When m_edge_count > 4, the fifth and additional edges
  //  are in m_edgex[0], ..., m_edgex[m_edge_count-5];
  //
  //  The value of ON_SubDEdgePtr.EdgeDirection() is 0 if the
  //  edge's natural orientation from m_vertex[0] to m_vertex[1]
  //  agrees with the face's boundary orientation.
  //
  //  The value of ON_SubDEdgePtr.EdgeDirection() is 1 if the
  //  edge's natural orientation from m_vertex[0] to m_vertex[1]
  //  is opposited the face's boundary orientation.
  enum : unsigned int
  {
    MaximumEdgeCount = 0xFFF0U
  };
  unsigned short m_edge_count = 0;
  unsigned short m_edgex_capacity = 0;

  ON_SubDEdgePtr m_edge4[4];
  ON_SubDEdgePtr* m_edgex = nullptr;

  /*
  Returns:
    A linked list of limit mesh fragments that cover this face.
    Nullptr if none are currently available.

    If the face is a quad, there is a single fragment. If the
    face is an n-gon with 4 != n, then the list has n fragments.
    The i-th fragment covers the subdivision quad with its 
    corner at Vertex(i).

  Remarks:
    Use the returned fragments immediately or make a 
    copies you manage for later use.

    Use ON_SubD.UpdateSurfaceMeshCache(false) or ON_SubD.UpdateSurfaceMeshCache(true)
    to create the face fragments.

    ON_SubDFace.ClearSavedSubdivisionPoints() removes any saved
    fragments and is called when the face or nearby components
    are modified.
  */
  const class ON_SubDMeshFragment* MeshFragments() const;


  /// <summary>
  /// The face's control net center point is the average of the face's
  /// vertex control net points. This is the same point as the face's
  /// subdivision point.
  /// </summary>
  /// <returns>
  /// The average of the face's vertex control net points
  /// </returns>  
  const ON_3dPoint ControlNetCenterPoint() const;

  /// <summary>
  /// When the face's control net polygon is planar, the face's
  /// control net normal is a unit vector perpindicular to the plane
  /// that points outwards. If the control net polygon is not
  /// planar, the control net normal is control net normal is a unit
  /// vector that is the average of the control polygon's corner normals.
  /// </summary>
  /// <returns>
  /// A unit vector that is normal to planar control net polygons and a good
  /// compromise for nonplanar control net polygons.
  /// </returns> 
  const ON_3dVector ControlNetCenterNormal() const;

  /// <summary>
  /// The face's control net center frame is a plane 
  /// with normal equal to this->ControlNetCenterNormal() 
  /// and origin equal to this->ControlNetCenterPoint(). 
  /// The x and y axes of the frame have no predictable relationship 
  /// to the face or SubD control net topology.
  /// </summary>
  /// <returns>
  /// A plane with unit normal equal to this->ControlNetCenterNormal() 
  /// and origin equal to this->ControlNetCenterPoint().
  /// If the face is not valid, ON_Plane::NanPlane is returned.
  /// </returns> 
  const ON_Plane ControlNetCenterFrame() const;

  /// <returns>
  /// True if the control net polygon is convex with respect to the
  /// plane this->ControlNetCenterFrame().
  /// </returns>
  bool IsConvex() const;

  /// <returns>
  /// True if the control net polygon is not convex with respect to the
  /// plane this->ControlNetCenterFrame().
  /// </returns>
  bool IsNotConvex() const;

  /// <summary>
  /// Determine if the face's control net polygon is planar.
  /// </summary>
  /// <param name="planar_tolerance"></param>
  /// <returns>
  /// True if the face's control net polygon is planar.
  /// </returns>
  bool IsPlanar(double planar_tolerance = ON_ZERO_TOLERANCE) const;

  /// <summary>
  /// Determine if the face's control net polygon is not planar.
  /// </summary>
  /// <param name="planar_tolerance"></param>
  /// <returns>
  /// True if the face's control net polygon is not planar.
  /// </returns>
  bool IsNotPlanar(double planar_tolerance = ON_ZERO_TOLERANCE) const;

public:
  /*
  Returns:
    Number of texture points that can be set on this face.
  Remarks:
    To allocate texture point storage, call ON_SubD.AddFaceTexturePointCapacity(this).
  */
  unsigned int TexturePointsCapacity() const;

  /*
  Returns:
    If texture points are set, then true is returned.
    Otherwise, false is returned.
  */
  bool TexturePointsAreSet() const;

  /*
  Description:
    Set the texture point at the specified face vertex.
  Parameters:
    i - [in]
      0 <= 0 < this->EdgeCount()
  Parameters:
    texture_point - [in]
  Returns:
    If this->TexturePointsCanBeSet() is true and i is a valid index,
    then the texture point is set and true is returned.
    Otherwise, false is returned.
  Remarks:
    To allocate texture point storage, call ON_SubD.AllocateFaceTexturePoints(this).
    Texture points are a mutable property on ON_SubDFace.
  */
  bool SetTexturePoint(
    unsigned i,
    ON_3dPoint texture_point
  ) const;

  /*
  Description:
    Remove all texture points.
  Remarks:
    Texture points are a mutable property on ON_SubDFace.
  */
  void ClearTexturePoints() const;

  /*
  Description:
    Get the texture point at the specified face vertex.
  Parameters:
    i - [in]
      0 <= 0 < this->EdgeCount()
  Returns:
    If texture
  */
  const ON_3dPoint TexturePoint(
    unsigned int i
  ) const;

  const ON_3dPoint TextureCenterPoint() const;

private:
  // If m_texture_points is not nullptr, it has capacity 4 + m_edgex_capacity.
  // Custom texture coordinates are stored in m_texture_points.
  // When texture coordinates are packed or come from a mapping,
  // m_texture_points is not used. Typically m_texture_points
  // is used when an ON_SubD is created from an ON_Mesh and the mesh
  // has custom texture coordinates. Here "custom" means
  // not from a mapping.  
  // https://mcneel.myjetbrains.com/youtrack/issue/RH-59465
  mutable ON_3dPoint* m_texture_points = nullptr;

private:
  // If 0 != ON_SUBD_CACHE_LIMIT_FLAG(m_saved_points_flags), then
  // m_mesh_fragments is a linked list of (4==m_edge_count?1:m_edge_count)
  // fragments available from MeshFragments() and managed by the parent ON_SubD. 
  // If 0 == ON_SUBD_CACHE_LIMIT_FLAG(m_saved_points_flags), then any information
  // in m_limit_mesh_fragments is dirty and should not be used.
  // ClearSavedSubdivisionPoints() zeros the appropriate bit of m_saved_points_flags.

  // Mesh fragment(s) for this face
  mutable class ON_SubDMeshFragment* m_mesh_fragments = nullptr;

private:

public:
  /*
  Description:
    Returns the number of edges and (number of vertices) in the face's boundary.
  Remarks:
    Boundaries that vist the same vertex or same edge multiple times are not permitted.
    So the number of vertices and number of edges is always the same.
  */
  unsigned int EdgeCount() const;

  /*
  Description:
    Rapidly verifies that:
    1. EdgeCount() >= 3
    2. Every edge is not null and has 2 non-null vertices.
    3. The end vertex of and edge is identical to the start vertex of the next edge.
    4. Every edge has FaceCount() >= 1.
    5. Every vertex has EdgeCount() >= 2 and FaceCount() >= 1.
    6. The first 4 edges are unique.
    6. The first 4 vertices are unique.
  Returns:
    True if the 5 conditions above are true.
  Remarks:
    The face can still be invalid, but if HasValidEdges() returns true,
    it is save to deference pointers returned by the face's Edge() and Vertex() functions.
  */
  bool HasEdges() const;

  const ON_SubDEdgePtr EdgePtr(
    unsigned int i
    ) const;

  const ON_SubDEdgePtr EdgePtrFromEdge(
    const class ON_SubDEdge* e
    ) const;

  bool EdgeMark(
    unsigned int i,
    bool bMissingEgeReturnValue
  ) const;

  ON__UINT8 EdgeMarkBits(
    unsigned int i,
    ON__UINT8 missing_edge_return_value
  ) const;


  /// <summary>
  /// Determine if this SubD face has sharp edges. 
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <returns>True if this SubD face at lease one sharp edge.</returns>
  bool HasSharpEdges() const;

  /// <summary>
  /// Get the range of sharpness values assigned to this face's sharp edges
  /// and return the number of sharp edges.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <param name="sharpness_range">The range of sharpness values is returned here. 
  /// (0,0) is returned if there are no sharp edges.
  /// </param>
  /// <returns>Number of sharp edges attached to this face.</returns>
  unsigned int SharpEdgeCount(ON_SubDEdgeSharpness& sharpness_range) const;

  /// <summary>
  /// Number of sharp edges attached to this face.
  /// See ON_SubDEdge::IsSharp() for more information about sharp edges.
  /// </summary>
  /// <returns>Number of sharp edges attached to this face.</returns>
  unsigned int SharpEdgeCount() const;

  /// <summary>
  /// Get the maximum sharpeness of the edges that form the face's boundary.
  /// (Creased edges have zero sharpness.)
  /// </summary>
  /// <returns>The maximum sharpness of the face's edges.</returns>
  double MaximumEdgeSharpness() const;


  const class ON_SubDVertex* Vertex(
    unsigned int i
    ) const;

  const ON_3dPoint ControlNetPoint(
    unsigned int i
  ) const;

  unsigned int VertexIndex(
    const ON_SubDVertex* vertex
    ) const;

  bool VertexMark(
    unsigned int i,
    bool bMissingVertexReturnValue
  ) const;

  ON__UINT8 VertexMarkBits(
    unsigned int i,
    ON__UINT8 missing_vertex_return_value
  ) const;

  /*
  Returns;
    If the vertex is in this face's boundary, pair of face boundary edges at the vertex is returned 
    with face boundary orientations, that is vertex = pair.First().EdgePtr().RelativeVertex(1)
    and vertex = pair.Second().EdgePtr().RelativeVertex(0). Otherwise, ON_SubDComponentPtrPair::Null
    is returned.
  */
  const ON_SubDComponentPtrPair VertexEdgePair(
    const ON_SubDVertex* vertex
  ) const;

  /*
  Returns;
    If the vertex is in this face's boundary, pair of face boundary edges at the vertex is returned
    with face boundary orientations, that is vertex = pair.First().EdgePtr().RelativeVertex(1)
    and vertex = pair.Second().EdgePtr().RelativeVertex(0). Otherwise, ON_SubDComponentPtrPair::Null
    is returned.
  */
  const ON_SubDComponentPtrPair VertexEdgePair(
    unsigned vertex_index
  ) const;

  const class ON_SubDEdge* Edge(
    unsigned int i
    ) const;

  ON__UINT_PTR EdgeDirection(
    unsigned int i
    ) const;

  /*
  Returns:
    If e is part of the face's boundary, then the index of the edge is returned.
    Otherwise, ON_UNSET_UINT_INDEX is returned.
  */
  unsigned int EdgeArrayIndex(
    const ON_SubDEdge* e
    ) const;

  /*
  Description:
    Expert user tool to remove an edge from the face's edge array.
  Remarks:
    Does not modify the edge.  If the face is referenced in the edge's face array,
    then the face must be removed from the edge's face array.
  */
  bool RemoveEdgeFromArray(
    const ON_SubDEdge* e
    );

  /*
  Description:
    Expert user tool to remove an edge from the face's edge array.
  Remarks:
    Does not modify the edge.  If the face is referenced in the edge's face array,
    then the face must be removed from the edge's face array.
  */
  bool RemoveEdgeFromArray(
    unsigned int i,
    ON_SubDEdgePtr& removed_edge
    );

  /*
  Description:
    Expert user tool to replace one edge with another in the face's edge array.
  Parameters:
    edge_to_remove - [in]
    edge_to_insert - [in]
     The inserted edge is assigned the same boundary orientation as the
     removed edge.
  Remarks:
    Does not modify the edge. The corresponding reference to this face must
    be removed from the first edge and added to the second edge.
  */
  bool ReplaceEdgeInArray(
    unsigned int fei0,
    ON_SubDEdge* edge_to_remove,
    ON_SubDEdge* edge_to_insert
  );

  /*
  Description:
    Expert user tool to replace one edge with another in the face's edge array.
  Parameters:
    edge_to_remove - [in]
    edgeptr_to_insert - [in]
     The inserted edge is assigned the same boundary orientation specified
     in edgeptr_to_insert.
  Remarks:
    Does not modify the edge. The corresponding reference to this face must
    be removed from the first edge and added to the second edge.
  */
  bool ReplaceEdgeInArray(
    unsigned int fei0,
    ON_SubDEdge* edge_to_remove,
    ON_SubDEdgePtr edgeptr_to_insert
  );

  /*
  Description:
    Rotates the edge array so that Edge(fei0) becomes the first edge in the edge array.
  */
  bool RotateEdgeArray(
    unsigned int fei0
  );

  const ON_SubDEdge* PrevEdge(
    const ON_SubDEdge* edge
    ) const;

  const ON_SubDEdge* NextEdge(
    const ON_SubDEdge* edge
    ) const;

  unsigned int PrevEdgeArrayIndex(
    unsigned int edge_array_index
    ) const;

  unsigned int NextEdgeArrayIndex(
    unsigned int edge_array_index
    ) const;

  /*
  Description:
    If the face is a quad, get the opposite corner vertex.
  Parameters:
    vertex - [in]
      a vertex on this face.
  Returns:
    If the face is a quad and vertex is a vertex of the face, then
    the vertex on the opposite corner is returned.
    Otherwise, nullptr is returned.
  */
  const ON_SubDVertex* QuadOppositeVertex(
    const ON_SubDVertex* vertex
    ) const;

  /*
  Description:
    If the face is a quad, get  the opposite side edge.
  Parameters:
    edge - [in]
      an edge on this face.
  Returns:
    If the face is a quad and edge is an edge of the face, then
    the edge on the opposite side is returned.
    Otherwise, nullptr is returned.
  */
  const ON_SubDEdge* QuadOppositeEdge(
    const ON_SubDEdge* edge
    ) const;

  /// <summary>
  /// Get the edges in the face's boundary that are on either side of a face corner.
  /// </summary>
  /// <param name="corner_vertex">
  /// Vertex used to identify the face corner.
  /// </param>
  /// <param name="entering_edge">
  /// The face's boundary edge ending at corner_vertex is retuned here.
  /// </param>
  /// <param name="leaving_edge">
  /// The face's boundary edge beginning at corner_vertex is retuned here.
  /// </param>
  /// <returns>
  /// If successful, the index of the vertex in the face's vertex list is returned;
  /// this value is &gt;=0 and &lt EdgeCount().
  /// Otherwise ON_UNSET_UINT_INDEX is returned.
  /// </returns>
  unsigned int GetCornerEdges(
    const ON_SubDVertex* corner_vertex,
    ON_SubDEdgePtr& entering_edge,
    ON_SubDEdgePtr& leaving_edge
  ) const;

  /*
  Parameters:
    subdivision_point - [out]
      The average of the face vertex locations.
  Returns:
    true if successful
  */
  bool GetSubdivisionPoint(
    double subdivision_point[3]
    ) const;

  ///<summary>
  /// The SubD face Catmull-Clark subdivision point.
  ///</summary>
  const ON_3dPoint SubdivisionPoint() const;

  
  /*
  Description:
    Evaluates the Catmull-Clark subdivision point ignoring all cached information.
    This function is typically used in testing and debugging code and
    in ordinary cases, it is faster and better to call SubdivisionPoint()
    or GetSubdivisionPoint().
  Parameters:
    subdivision_point - [out]
      The Catmull-Clark face subdivision point is returned here.
  */
  bool EvaluateCatmullClarkSubdivisionPoint(
    double subdivision_point[3]
  ) const;


  /*
  Description:
    Reverse the order and orientation of the edges that form
    the boundary of this face.
  */
  bool ReverseEdgeList();

  /*
  Description:
    Get the bicubic b-spline control points for the limit surface.
    The corresponding knots are uniform.
  Parameters:
    vertex - [in]
    limit_surface_cv_stride0 - [int]
    limit_surface_cv_stride1 - [out]
    limit_surface_cv - [out]
      control points for a cubic spline surface
        CV[i][j][k] = limit_surface_cv[i*limit_bspline_cv_stride0 + j*limit_bspline_cv_stride1 + k]
        0 <= i < 4, 0 <= j < 4, 0 <= k < 3
  Returns:
    true if successful
    false if the limit surface for this face is not a cubic surface
  Remarks:
    The knots for the bicubic b-spline surface are uniform.
  */
  bool GetQuadSurface(
    double* limit_surface_cv,
    size_t limit_surface_cv_stride0,
    size_t limit_surface_cv_stride1
    ) const;

  bool GetQuadSurface(
    class ON_NurbsSurface& limit_surface
    ) const;

  bool GetQuadSurface(
    class ON_BezierSurface& limit_surface
    ) const;

  /*
  Returns:
    Number of edges in the face's boundary with Edge().m_status.RuntimeMark() = true;
  */
  unsigned int MarkedEdgeCount() const;

  /*
  Returns:
    Number of vertices in the face's boundary with Vertex().m_status.RuntimeMark() = true;
  */
  unsigned int MarkedVertexCount() const;

  /*
  Description:
    Set the mark of every vertex attached to this face.
  Returns:
    Number of marks changed.
  */
  unsigned int SetVertexMarks(
    bool bMark
    ) const;

  /*
  Description:
    Set the mark of every boundary edge attached to this face.
  Returns:
    Number of marks changed.
  */
  unsigned int SetEdgeMarks(
    bool bMark
    ) const;

  /*
  Description:
    Get the face's boundary.
  Parameters:
    face_edge_array - [out]
      The boundary of the face is returned in canonical counter-clockwise order.
  Returns:
    Number of edges in the face's boundary.
  */
  unsigned int GetEdgeArray(
    ON_SimpleArray< ON_SubDEdgePtr >& face_edge_array
  ) const;

private:
  void CopyFrom(
    const ON_SubDFace* src,
    bool bCopyEdgeArray,
    bool bCopySymmetrySetNext
    );
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDVertexArray
//

/*
Description:
  Avoid using ON_SubDVertexArray. ON_SubDVertexIterator is more efficient and a better choice.
*/
class ON_CLASS ON_SubDVertexArray
{
public:
  ON_SubDVertexArray(
    const ON_SubD& subd
    );
  ON_SubDVertexArray() = default;
  ON_SubDVertexArray(const ON_SubDVertexArray&) = default;
  ON_SubDVertexArray& operator=(const ON_SubDVertexArray&) = default;

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_SubDVertexArray(ON_SubDVertexArray&&) ON_NOEXCEPT;

  // rvalue copy operator-=
  ON_SubDVertexArray& operator=(ON_SubDVertexArray&&);
#endif

  const ON_SubD& SubD() const
  {
    return m_subd;
  }

  unsigned int VertexCount() const
  {
    return m_vertex_count;
  }

  const class ON_SubDVertex* operator[](unsigned int i) const
  {
    return (i < m_vertex_count) ? m_a[i] : nullptr;
  }
  
private:
  ON_SubD m_subd;
  const class ON_SubDVertex*const* m_a = nullptr;
  unsigned int m_vertex_count = 0;

#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 )
  // C4251: ... needs to have dll-interface to be used by clients of class ...
  // m_sp is private and all code that manages m_sp is explicitly implemented in the DLL.
private:
  std::shared_ptr< const class ON_SubDVertex* > m_sp;
#pragma ON_PRAGMA_WARNING_POP
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDEdgeArray
//

/*
Description:
  Avoid using ON_SubDEdgeArray. ON_SubDEdgeIterator is more efficient and a better choice.
*/
class ON_CLASS ON_SubDEdgeArray
{
public:
  ON_SubDEdgeArray(
    const ON_SubD& subd
    );
  ON_SubDEdgeArray() = default;
  ON_SubDEdgeArray(const ON_SubDEdgeArray&) = default;
  ON_SubDEdgeArray& operator=(const ON_SubDEdgeArray&) = default;

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_SubDEdgeArray(ON_SubDEdgeArray&&) ON_NOEXCEPT;

  // rvalue copy operator-=
  ON_SubDEdgeArray& operator=(ON_SubDEdgeArray&&);
#endif

  const ON_SubD& SubD() const
  {
    return m_subd;
  }

  unsigned int EdgeCount() const
  {
    return m_edge_count;
  }

  const class ON_SubDEdge* operator[](unsigned int i) const
  {
    return (i < m_edge_count) ? m_a[i] : nullptr;
  }

private:
  ON_SubD m_subd;
  const class ON_SubDEdge*const* m_a = nullptr;
  unsigned int m_edge_count = 0;

#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 )
  // C4251: ... needs to have dll-interface to be used by clients of class ...
  // m_sp is private and all code that manages m_sp is explicitly implemented in the DLL.
private:
  std::shared_ptr< const class ON_SubDEdge* > m_sp;
#pragma ON_PRAGMA_WARNING_POP
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDFaceArray
//

/*
Description:
  Avoid using ON_SubDFaceArray. ON_SubDFaceIterator is more efficient and a better choice.
*/
class ON_CLASS ON_SubDFaceArray
{
public:
  ON_SubDFaceArray(
    const ON_SubD& subd
    );
  ON_SubDFaceArray() = default;
  ON_SubDFaceArray(const ON_SubDFaceArray&) = default;
  ON_SubDFaceArray& operator=(const ON_SubDFaceArray&) = default;

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_SubDFaceArray(ON_SubDFaceArray&&) ON_NOEXCEPT;

  // rvalue copy operator-=
  ON_SubDFaceArray& operator=(ON_SubDFaceArray&&);
#endif

  const ON_SubD& SubD() const
  {
    return m_subd;
  }

  unsigned int FaceCount() const
  {
    return m_face_count;
  }

  const class ON_SubDFace* operator[](unsigned int i) const
  {
    return (i < m_face_count) ? m_a[i] : nullptr;
  }

private:
  ON_SubD m_subd;
  const class ON_SubDFace*const* m_a = nullptr;
  unsigned int m_face_count = 0;
  
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 )
  // C4251: ... needs to have dll-interface to be used by clients of class ...
  // m_sp is private and all code that manages m_sp is explicitly implemented in the DLL.
private:
  std::shared_ptr< const class ON_SubDFace* > m_sp;
#pragma ON_PRAGMA_WARNING_POP
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDVertexIterator
//
class ON_CLASS ON_SubDVertexIterator
{
public:
  // The best way to get an ON_SubDVertexIterator is so use the ON_SubD member function
  // ON_SubDVertexIterator vit = subd.VertexIterator();
  ON_SubDVertexIterator(
    const class ON_SubD& subd
  );

  /// <summary>
  /// An expert tool to iteratate over existing vertices on a specified level.
  /// </summary>
  /// <param name="subd"></param>
  /// <param name="level_index"></param>
  ON_SubDVertexIterator(
    const class ON_SubD& subd,
    unsigned level_index
  );

  // The best way to get an ON_SubDVertexIterator is so use the ON_SubD member function
  // ON_SubDVertexIterator vit = subd.VertexIterator();
  ON_SubDVertexIterator(
    const class ON_SubDRef& subd_ref
    );

  // Construct and iterator that iterates over a single vertex.
  ON_SubDVertexIterator(
    const class ON_SubD& subd,
    const class ON_SubDVertex& vertex
    );

  // Construct and iterator that iterates over a single vertex.
  ON_SubDVertexIterator(
    const class ON_SubDRef& subd_ref,
    const class ON_SubDVertex& vertex
    );

  // Construct and iterator that iterates over the vertices of an edge.
  ON_SubDVertexIterator(
    const class ON_SubD& subd,
    const class ON_SubDEdge& edge
    );

  // Construct and iterator that iterates over the vertices of an edge.
  ON_SubDVertexIterator(
    const class ON_SubDRef& subd_ref,
    const class ON_SubDEdge& edge
    );

  // Construct and iterator that iterates over the vertices of a face.
  ON_SubDVertexIterator(
    const class ON_SubD& subd,
    const class ON_SubDFace& face
    );

  // Construct and iterator that iterates over the vertices of a face.
  ON_SubDVertexIterator(
    const class ON_SubDRef& subd_ref,
    const class ON_SubDFace& face
    );

  ON_SubDVertexIterator() = default;
  ON_SubDVertexIterator(const ON_SubDVertexIterator&) = default;
  ON_SubDVertexIterator& operator=(const ON_SubDVertexIterator&) = default;

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_SubDVertexIterator( ON_SubDVertexIterator&& ) ON_NOEXCEPT;
  // rvalue assignment operator
  ON_SubDVertexIterator& operator=( ON_SubDVertexIterator&& );
#endif

  /*
  Returns:
  The subD object for this iterator.
  */
  const class ON_SubD& SubD() const
  {
    return m_subd_ref.SubD();
  }

  const class ON_SubDRef& SubDRef() const
  {
    return m_subd_ref;
  }

  /*
  Description:
    Prefix increment the iterator.
  Returns:
    Next vertex.
  Remarks:
    operator++(void) and NextVertex() behave the same.
    In OpenNURBS 8.17 and earlier, this function was incorrectly implemented as
    a postfix increment (operator++(int)). This has been corrected in OpenNURBS 8.18.
    If you have a plugin compiled without inlining optimizations (e.g. in Debug mode),
    operator++(void) will be calling the version in opennurbs.dll distributed
    with Rhino that is used to run the plugin.
    If you have a plugin compiled with inlining optimizations (e.g. in Release mode),
    operator++(void) will behave like the version in opennurbs_subd.h distributed
    with the Rhino SDK that was used to compiled the plugin.
  */
  const class ON_SubDVertex* operator++()
  {
    return NextVertex();
  }

  /*
  Description:
    Postfix increment the iterator.
  Returns:
    Current vertex.
  Remarks:
    operator++(int) and NextVertex() behave differently.
  */
  const class ON_SubDVertex* operator++(int)
  {
    const class ON_SubDVertex* v = m_v_current;
    NextVertex();
    return v;
  }

  /*
  Return:
    Number of vertices this iterator will iterate through.
  */
  unsigned int VertexCount() const
  {
    return m_vertex_count;
  }

  /*
  Return:
    Iterator index of the current vertex.
  */
  unsigned int CurrentVertexIndex() const
  {
    return m_vertex_index;
  }

  /*
  Description:
  Set the iterator to the beginning of the vertex list.
  Returns:
  First vertex in the list.
  */
  const class ON_SubDVertex* FirstVertex()
  {
    m_vertex_index = 0;
    return (m_v_current = m_v_first);
  }

  /*
  Description:
    Pre-increment the iterator and return the new current vertex.
  Returns:
    Next vertex.
  Remarks:
    operator++(void) and NextVertex() behave the same.
    operator++(int) and NextVertex() behave differently.
  */
  const class ON_SubDVertex* NextVertex()
  {
    m_vertex_index++;
    if (m_vertex_index < m_vertex_count)
    {
      if (0 == m_component_ptr.m_ptr)
      {
        if (nullptr != m_v_current)
          m_v_current = m_v_current->m_next_vertex;
      }
      else
      {
        const ON_SubDEdge* edge = m_component_ptr.Edge();
        if (nullptr != edge)
        {
          m_v_current = edge->Vertex(m_vertex_index);
        }
        else
        {
          const ON_SubDFace* face = m_component_ptr.Face();
          if (nullptr != face)
            m_v_current = face->Vertex(m_vertex_index);
          else
            m_v_current = nullptr;
        }
      }
    }
    else
    {
      m_vertex_index = m_vertex_count;
      m_v_current = nullptr;
    }
    return m_v_current;
  }

  /*
  Returns:
  Current vertex;
  */
  const class ON_SubDVertex* CurrentVertex() const
  {
    return m_v_current;
  }

  /*
  Description:
  Set the iterator to the end of the vertex list.
  Returns:
  Last vertex in the list.
  */
  const class ON_SubDVertex* LastVertex()
  {
    m_vertex_index = (m_vertex_count > 0) ? (m_vertex_count - 1) : 0;
    return (m_v_current = m_v_last);
  }

  /*
  Description:
  Get the iterator's base component in which we are iterating, if it exists.
  Returns:
  m_component_ptr if it exists, or ON_SubDComponentPtr::Null.
  */
  ON_SubDComponentPtr BaseComponentPtr() const
  {
    return m_component_ptr.m_ptr == 0 ? ON_SubDComponentPtr::Null : m_component_ptr;
  }

  /*
  Description:
  Get the iterator's base edge in which we are iterating, if it exists.
  Returns:
  m_component_ptr.Edge() if it exists, or nullptr.
  */
  ON_SubDEdge* BaseEdge() const
  {
    if (m_component_ptr.m_ptr == 0) return nullptr;
    return m_component_ptr.IsEdge() ? m_component_ptr.Edge() : nullptr;
  }

  /*
  Description:
  Get the iterator's base edge in which we are iterating, if it exists.
  Returns:
  m_component_ptr.Face() if it exists, or nullptr.
  */
  ON_SubDFace* BaseFace() const
  {
    if (m_component_ptr.m_ptr == 0) return nullptr;
    return m_component_ptr.IsFace() ? m_component_ptr.Face() : nullptr;
  }

private:
  void Internal_Init(
    const ON_SubDRef& subd_ref,
    unsigned int vertex_count,
    const ON_SubDVertex* first,
    const ON_SubDVertex* last,
    ON_SubDComponentPtr component_ptr
  );
  ON_SubDRef m_subd_ref;
  const ON_SubDVertex* m_v_first = nullptr;
  const ON_SubDVertex* m_v_last = nullptr;
  const ON_SubDVertex* m_v_current = nullptr;
  unsigned int m_vertex_index = 0;
  unsigned int m_vertex_count = 0;
  ON_SubDComponentPtr m_component_ptr = ON_SubDComponentPtr::Null;
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDVertexIdIterator
//

class ON_CLASS ON_SubDVertexIdIterator : private ON_FixedSizePoolIterator
{
public:
  ON_SubDVertexIdIterator() = default;
  ~ON_SubDVertexIdIterator() = default;
  ON_SubDVertexIdIterator(const ON_SubDVertexIdIterator&) = default;
  ON_SubDVertexIdIterator& operator=(const ON_SubDVertexIdIterator&) = default;

public:
  ON_SubDVertexIdIterator(const ON_SubDRef& subd_ref);
  ON_SubDVertexIdIterator(const ON_SubD& subd);

public:
  /*
  Description:
    In general, you want to use a ON_SubDVertexIterator to loop through SubD vertices.
    This is a special tool for unusual sitiations when it is necessary to
    iteratate through every vertex on every level of a SubD in order
    of increasing m_id value. 
  Returns:
    The vertex with the smallest id.
  */
  const ON_SubDVertex* FirstVertex();

  const ON_SubDVertex* FirstVertexOnLevel(unsigned int level_index);


  /*
  Description:
    In general, you want to use a ON_SubDVertexIterator to loop through SubD vertices.
    This is a special tool for unusual sitiations when it is necessary to
    iteratate through every vertex on every level of a SubD in order
    of increasing m_id value. 
  Returns:
    The vertex in order of increasing id.
  */
  const ON_SubDVertex* NextVertex();

  const ON_SubDVertex* NextVertexOnLevel(unsigned int level_index);

  /*
  Returns:
    The most recently returned vertex from a call to FirstVertex() or NextVertex().
  */
  const ON_SubDVertex* CurrentVertex() const;

private:
  friend class ON_SubDHeap;
  ON_SubDRef m_subd_ref;
  void Internal_Init();
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDEdgeIterator
//
class ON_CLASS ON_SubDEdgeIterator
{
public:
  // The best way to get an ON_SubDEdgeIterator is so use the ON_SubD member function
  // ON_SubDEdgeIterator eit = subd.EdgeIterator();
  ON_SubDEdgeIterator(
    const class ON_SubD& subd
    );

  /// <summary>
  /// An expert tool to iteratate over existing edges on a specified level.
  /// </summary>
  /// <param name="subd"></param>
  /// <param name="level_index"></param>
  ON_SubDEdgeIterator(
    const class ON_SubD& subd,
    unsigned level_index
  );

  // The best way to get an ON_SubDEdgeIterator is so use the ON_SubD member function
  // ON_SubDEdgeIterator eit = subd.EdgeIterator();
  ON_SubDEdgeIterator(
    const class ON_SubDRef& subd_ref
    );

  // Construct and iterator that iterates over a single edge.
  ON_SubDEdgeIterator(
    const class ON_SubD& subd,
    const class ON_SubDEdge& edge
    );

  // Construct and iterator that iterates over a single edge.
  ON_SubDEdgeIterator(
    const class ON_SubDRef& subd_ref,
    const class ON_SubDEdge& edge
    );

  // Construct and iterator that iterates over the edges of a vertex.
  ON_SubDEdgeIterator(
    const class ON_SubD& subd,
    const class ON_SubDVertex& vertex
    );

  // Construct and iterator that iterates over the edges of a vertex.
  ON_SubDEdgeIterator(
    const class ON_SubDRef& subd_ref,
    const class ON_SubDVertex& vertex
    );

  // Construct and iterator that iterates over the edges of a face.
  ON_SubDEdgeIterator(
    const class ON_SubD& subd,
    const class ON_SubDFace& face
    );

  // Construct and iterator that iterates over the edges of a face.
  ON_SubDEdgeIterator(
    const class ON_SubDRef& subd_ref,
    const class ON_SubDFace& face
    );

  ON_SubDEdgeIterator() = default;
  ON_SubDEdgeIterator(const ON_SubDEdgeIterator&) = default;
  ON_SubDEdgeIterator& operator=(const ON_SubDEdgeIterator&) = default;

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_SubDEdgeIterator( ON_SubDEdgeIterator&& ) ON_NOEXCEPT;
  // rvalue assignment operator
  ON_SubDEdgeIterator& operator=( ON_SubDEdgeIterator&& );
#endif

  /*
  Returns:
  The subD object for this iterator.
  */
  const class ON_SubD& SubD() const
  {
    return m_subd_ref.SubD();
  }

  const class ON_SubDRef& SubDRef() const
  {
    return m_subd_ref;
  }

  /*
  Description:
    Prefix increment the iterator.
  Returns:
    Next edge.
  Remarks:
    operator++(void) and NextEdge() behave the same.
    In OpenNURBS 8.17 and earlier, this function was incorrectly implemented as
    a postfix increment (operator++(int)). This has been corrected in OpenNURBS 8.18.
    If you have a plugin compiled without inlining optimizations (e.g. in Debug mode),
    operator++(void) will be calling the version in opennurbs.dll distributed
    with Rhino that is used to run the plugin.
    If you have a plugin compiled with inlining optimizations (e.g. in Release mode),
    operator++(void) will behave like the version in opennurbs_subd.h distributed
    with the Rhino SDK that was used to compiled the plugin.
  */
  const class ON_SubDEdge* operator++()
  {
    return NextEdge();
  }

  /*
  Description:
    Postfix increment the iterator.
  Returns:
    Current edge.
  Remarks:
    operator++(int) and NextEdge() behave differently.
  */
  const class ON_SubDEdge* operator++(int)
  {
    const class ON_SubDEdge* e = m_e_current;
    NextEdge();
    return e;
  }

  /*
  Return:
    Number of edges this iterator will iterate through.
  */
  unsigned int EdgeCount() const
  {
    return m_edge_count;
  }

  /*
  Return:
    Iterator index of the current edge.
  */
  unsigned int CurrentEdgeIndex() const
  {
    return m_edge_index;
  }

  /*
  Description:
    Set the iterator to the beginning of the edge list.
  Returns:
    First edge in the list.
  */
  const class ON_SubDEdge* FirstEdge()
  {
    m_edge_index = 0;
    return m_e_current = m_e_first;
  }

  /*
  Description:
    Pre-increment the iterator and return the new current edge.
  Returns:
    Next edge.
  Remarks:
    operator++(void) and NextEdge() behave the same.
    operator++(int) and NextEdge() behave differently.
  */
  const class ON_SubDEdge* NextEdge()
  {
    m_edge_index++;
    if (m_edge_index < m_edge_count)
    {
      if (0 == m_component_ptr.m_ptr)
      {
        if (nullptr != m_e_current)
          m_e_current = m_e_current->m_next_edge;
      }
      else
      {
        const ON_SubDVertex* vertex = m_component_ptr.Vertex();
        if (nullptr != vertex)
        {
          m_e_current = vertex->Edge(m_edge_index);
        }
        else
        {
          const ON_SubDFace* face = m_component_ptr.Face();
          if (nullptr != face)
            m_e_current = face->Edge(m_edge_index);
          else
            m_e_current = nullptr;
        }
      }
    }
    else
    {
      m_edge_index = m_edge_count;
      m_e_current = nullptr;
    }
    return m_e_current;
  }

  /*
  Returns:
  Current edge;
  */
  const class ON_SubDEdge* CurrentEdge() const
  {
    return m_e_current;
  }

  /*
  Description:
  Set the iterator to the end of the edge list.
  Returns:
  Last edge in the list.
  */
  const class ON_SubDEdge* LastEdge()
  {
    m_edge_index = (m_edge_count > 0) ? (m_edge_count - 1) : 0;
    return m_e_current = m_e_last;
  }

  /*
  Description:
  Get the iterator's base component in which we are iterating, if it exists.
  Returns:
  m_component_ptr if it exists, or ON_SubDComponentPtr::Null.
  */
  ON_SubDComponentPtr BaseComponentPtr() const
  {
    return m_component_ptr.m_ptr == 0 ? ON_SubDComponentPtr::Null : m_component_ptr;
  }

  /*
  Description:
  Get the iterator's base vertex in which we are iterating, if it exists.
  Returns:
  m_component_ptr.Vertex() if it exists, or nullptr.
  */
  ON_SubDVertex* BaseVertex() const
  {
    if (m_component_ptr.m_ptr == 0) return nullptr;
    return m_component_ptr.IsVertex() ? m_component_ptr.Vertex() : nullptr;
  }

  /*
  Description:
  Get the iterator's base edge in which we are iterating, if it exists.
  Returns:
  m_component_ptr.Face() if it exists, or nullptr.
  */
  ON_SubDFace* BaseFace() const
  {
    if (m_component_ptr.m_ptr == 0) return nullptr;
    return m_component_ptr.IsFace() ? m_component_ptr.Face() : nullptr;
  }

private:
  void Internal_Init(
    const ON_SubDRef& subd_ref,
    unsigned int edge_count,
    const ON_SubDEdge* first,
    const ON_SubDEdge* last,
    ON_SubDComponentPtr component_ptr
  );
  ON_SubDRef m_subd_ref;
  const ON_SubDEdge* m_e_first = nullptr;
  const ON_SubDEdge* m_e_last = nullptr;
  const ON_SubDEdge* m_e_current = nullptr;
  unsigned int m_edge_index = 0;
  unsigned int m_edge_count = 0;
  ON_SubDComponentPtr m_component_ptr = ON_SubDComponentPtr::Null;
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDEdgeIdIterator
//

class ON_CLASS ON_SubDEdgeIdIterator : private ON_FixedSizePoolIterator
{
public:
  ON_SubDEdgeIdIterator() = default;
  ~ON_SubDEdgeIdIterator() = default;
  ON_SubDEdgeIdIterator(const ON_SubDEdgeIdIterator&) = default;
  ON_SubDEdgeIdIterator& operator=(const ON_SubDEdgeIdIterator&) = default;

public:
  ON_SubDEdgeIdIterator(const ON_SubDRef& subd_ref);
  ON_SubDEdgeIdIterator(const ON_SubD& subd);

public:
  /*
  Description:
    In general, you want to use a ON_SubDEdgeIterator to loop through SubD edges.
    This is a special tool for unusual sitiations when it is necessary to
    iteratate through every edge on every level of a SubD in order
    of increasing m_id value. 
  Returns:
    The edge with the smallest id.
  */
  const ON_SubDEdge* FirstEdge();

  const ON_SubDEdge* FirstEdgeOnLevel(unsigned int level_index);


  /*
  Description:
    In general, you want to use a ON_SubDEdgeIterator to loop through SubD edges.
    This is a special tool for unusual sitiations when it is necessary to
    iteratate through every edge on every level of a SubD in order
    of increasing m_id value. 
  Returns:
    The edge in order of increasing id.
  */
  const ON_SubDEdge* NextEdge();

  const ON_SubDEdge* NextEdgeOnLevel(unsigned int level_index);

  /*
  Returns:
    The most recently returned edge from a call to FirstEdge() or NextEdge().
  */
  const ON_SubDEdge* CurrentEdge() const;

private:
  friend class ON_SubDHeap;
  ON_SubDRef m_subd_ref;
  void Internal_Init();
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDFaceIterator
//
class ON_CLASS ON_SubDFaceIterator
{
public:
  // The best way to get an ON_SubDFaceIterator is so use the ON_SubD member function
  // ON_SubDFaceIterator fit = subd.FaceIterator();
  ON_SubDFaceIterator(
    const class ON_SubD& subd
    );

  /// <summary>
  /// An expert tool to iteratate over existing faces on a specified level.
  /// </summary>
  /// <param name="subd"></param>
  /// <param name="level_index"></param>
  ON_SubDFaceIterator(
    const class ON_SubD& subd,
    unsigned level_index
  );

  // The best way to get an ON_SubDFaceIterator is so use the ON_SubD member function
  // ON_SubDFaceIterator fit = subd.FaceIterator();
  ON_SubDFaceIterator(
    const class ON_SubDRef& subd_ref
    );

  // Construct and iterator that iterates over the single face.
  ON_SubDFaceIterator(
    const class ON_SubD& subd,
    const class ON_SubDFace& face
    );

  // Construct and iterator that iterates over the single face.
  ON_SubDFaceIterator(
    const class ON_SubDRef& subd_ref,
    const class ON_SubDFace& face
    );

  // Construct and iterator that iterates over the faces of a vertex.
  ON_SubDFaceIterator(
    const class ON_SubD& subd,
    const class ON_SubDVertex& vertex
    );

  // Construct and iterator that iterates over the faces of a vertex.
  ON_SubDFaceIterator(
    const class ON_SubDRef& subd_ref,
    const class ON_SubDVertex& vertex
    );

  // Construct and iterator that iterates over the faces of an edge.
  ON_SubDFaceIterator(
    const class ON_SubD& subd,
    const class ON_SubDEdge& edge
    );

  // Construct and iterator that iterates over the faces of an edge.
  ON_SubDFaceIterator(
    const class ON_SubDRef& subd_ref,
    const class ON_SubDEdge& edge
    );

  ON_SubDFaceIterator() = default;
  ON_SubDFaceIterator(const ON_SubDFaceIterator&) = default;
  ON_SubDFaceIterator& operator=(const ON_SubDFaceIterator&) = default;

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_SubDFaceIterator( ON_SubDFaceIterator&& ) ON_NOEXCEPT;
  // rvalue assignment operator
  ON_SubDFaceIterator& operator=( ON_SubDFaceIterator&& );
#endif

  /*
  Returns:
  The subD object for this iterator.
  */
  const class ON_SubD& SubD() const
  {
    return m_subd_ref.SubD();
  }

  const class ON_SubDRef& SubDRef() const
  {
    return m_subd_ref;
  }

  /*
  Description:
    Prefix increment the iterator.
  Returns:
    Next face.
  Remarks:
    operator++(void) and NextFace() behave the same.
    In OpenNURBS 8.17 and earlier, this function was incorrectly implemented as
    a postfix increment (operator++(int)). This has been corrected in OpenNURBS 8.18.
    If you have a plugin compiled without inlining optimizations (e.g. in Debug mode),
    operator++(void) will be calling the version in opennurbs.dll distributed
    with Rhino that is used to run the plugin.
    If you have a plugin compiled with inlining optimizations (e.g. in Release mode),
    operator++(void) will behave like the version in opennurbs_subd.h distributed
    with the Rhino SDK that was used to compiled the plugin.
  */
  const class ON_SubDFace* operator++()
  {
    return NextFace();
  }

  /*
  Description:
    Postfix increment the iterator.
  Returns:
    Current face.
  Remarks:
    operator++(int) and NextFace() behave differently.
  */
  const class ON_SubDFace* operator++(int)
  {
    const class ON_SubDFace* f = m_face_current;
    NextFace();
    return f;
  }

  /*
  Return:
    Number of faces this iterator will iterate through.
  */
  unsigned int FaceCount() const
  {
    return m_face_count;
  }

  /*
  Return:
    Iterator index of the current face.
  */
  unsigned int CurrentFaceIndex() const
  {
    return m_face_index;
  }


  /*
  Description:
    Set the iterator to the beginning of the face list.
  Returns:
    First face in the list.
  */
  const class ON_SubDFace* FirstFace()
  {
    m_face_index = 0;
    return (m_face_current = m_face_first);
  }

  /*
  Description:
    Pre-increment the iterator and return the new current face.
  Returns:
    Next face.
  Remarks:
    operator++(void) and NextFace() behave the same.
    operator++(int) and NextFace() behave differently.
  */
  const class ON_SubDFace* NextFace()
  {
    m_face_index++;
    if (m_face_index < m_face_count)
    {
      if (0 == m_component_ptr.m_ptr)
      {
        if (nullptr != m_face_current)
          m_face_current = m_face_current->m_next_face;
      }
      else
      {
        const ON_SubDVertex* vertex = m_component_ptr.Vertex();
        if (nullptr != vertex)
        {
          m_face_current = vertex->Face(m_face_index);
        }
        else
        {
          const ON_SubDEdge* edge = m_component_ptr.Edge();
          if (nullptr != edge)
            m_face_current = edge->Face(m_face_index);
          else
            m_face_current = nullptr;
        }
      }
    }
    else
    {
      m_face_index = m_face_count;
      m_face_current = nullptr;
    }
    return m_face_current;
  }

  /*
  Returns:
    Current face;
  */
  const class ON_SubDFace* CurrentFace() const
  {
    return m_face_current;
  }

  /*
  Description:
    Set the iterator to the end of the face list.
  Returns:
    Last face in the list.
  */
  const class ON_SubDFace* LastFace()
  {
    m_face_index = (m_face_count > 0) ? (m_face_count - 1) : 0;
    return (m_face_current = m_face_last);
  }

  /*
  Description:
  Get the iterator's base component in which we are iterating, if it exists.
  Returns:
  m_component_ptr if it exists, or ON_SubDComponentPtr::Null.
  */
  ON_SubDComponentPtr BaseComponentPtr() const
  {
    return m_component_ptr.m_ptr == 0 ? ON_SubDComponentPtr::Null : m_component_ptr;
  }

  /*
  Description:
  Get the iterator's base vertex in which we are iterating, if it exists.
  Returns:
  m_component_ptr.Vertex() if it exists, or nullptr.
  */
  ON_SubDVertex* BaseVertex() const
  {
    if (m_component_ptr.m_ptr == 0) return nullptr;
    return m_component_ptr.IsVertex() ? m_component_ptr.Vertex() : nullptr;
  }

  /*
  Description:
  Get the iterator's base edge in which we are iterating, if it exists.
  Returns:
  m_component_ptr.Edge() if it exists, or nullptr.
  */
  ON_SubDEdge* BaseEdge() const
  {
    if (m_component_ptr.m_ptr == 0) return nullptr;
    return m_component_ptr.IsEdge() ? m_component_ptr.Edge() : nullptr;
  }


private:
  void Internal_Init(
    const ON_SubDRef& subd_ref,
    unsigned int face_count,
    const ON_SubDFace* first,
    const ON_SubDFace* last,
    ON_SubDComponentPtr component_ptr
  );
  ON_SubDRef m_subd_ref;
  const ON_SubDFace* m_face_first = nullptr;
  const ON_SubDFace* m_face_last = nullptr;
  const ON_SubDFace* m_face_current = nullptr;
  unsigned int m_face_index = 0;
  unsigned int m_face_count = 0;
  ON_SubDComponentPtr m_component_ptr = ON_SubDComponentPtr::Null;
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDFaceIdIterator
//

class ON_CLASS ON_SubDFaceIdIterator : private ON_FixedSizePoolIterator
{
public:
  ON_SubDFaceIdIterator() = default;
  ~ON_SubDFaceIdIterator() = default;
  ON_SubDFaceIdIterator(const ON_SubDFaceIdIterator&) = default;
  ON_SubDFaceIdIterator& operator=(const ON_SubDFaceIdIterator&) = default;

public:
  ON_SubDFaceIdIterator(const ON_SubDRef& subd_ref);
  ON_SubDFaceIdIterator(const ON_SubD& subd);

public:
  /*
  Description:
    In general, you want to use a ON_SubDFaceIterator to loop through SubD faces.
    This is a special tool for unusual sitiations when it is necessary to
    iteratate through every face on every level of a SubD in order
    of increasing m_id value. 
  Returns:
    The face with the smallest id.
  */
  const ON_SubDFace* FirstFace();
  
  const ON_SubDFace* FirstFaceOnLevel(unsigned int level_index);

  /*
  Description:
    In general, you want to use a ON_SubDFaceIterator to loop through SubD faces.
    This is a special tool for unusual sitiations when it is necessary to
    iteratate through every face on every level of a SubD in order
    of increasing m_id value. 
  Returns:
    The face in order of increasing id.
  */
  const ON_SubDFace* NextFace();

  const ON_SubDFace* NextFaceOnLevel(unsigned int level_index);

  /*
  Returns:
    The most recently returned face from a call to FirstFace() or NextFace().
  */
  const ON_SubDFace* CurrentFace() const;

private:
  friend class ON_SubDHeap;
  ON_SubDRef m_subd_ref;
  void Internal_Init();
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDComponentIterator
//
class ON_CLASS ON_SubDComponentIterator
{
public:
  static const ON_SubDComponentIterator Empty;

  // The ON_SubD member function
  //   ON_SubDComponentIterator ON_SubD::ComponentIterator(subd_level_index)
  //   is the best way to get a component iterator for a subd level.
  ON_SubDComponentIterator(
    const class ON_SubD& subd
    );
  ON_SubDComponentIterator(
    const class ON_SubDRef& subd_ref
    );

  ON_SubDComponentIterator() = default;
  ON_SubDComponentIterator(const ON_SubDComponentIterator&) = default;
  ON_SubDComponentIterator& operator=(const ON_SubDComponentIterator&) = default;

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_SubDComponentIterator( ON_SubDComponentIterator&& ) ON_NOEXCEPT;
  // rvalue assignment operator
  ON_SubDComponentIterator& operator=( ON_SubDComponentIterator&& );
#endif

  /*
  Returns:
  The subD object for this iterator.
  */
  const class ON_SubD& SubD() const
  {
    return m_subd_ref.SubD();
  }

  const class ON_SubDRef& SubDRef() const
  {
    return m_subd_ref;
  }

  /*
  Returns:
  The subD level for this iterator.
  */
  unsigned int SubDLevel() const
  {
    return m_subd_level;
  }

  /*
  Description:
    Returns the current component and increment the iterator.
  Returns:
    Current component.
  Remarks:
    operator++ and NextComponent() behave differently.
  */
  const class ON_SubDComponentPtr operator++()
  {
    const class ON_SubDComponentPtr cptr = m_cptr_current;
    NextComponent();
    return cptr;
  }

  /*
  Description:
    Set the iterator to the beginning of the component list.
  Returns:
    First component in the list.
  */
  const class ON_SubDComponentPtr FirstComponent();

  /*
  Description:
    Returns the next component and increments the iterator.
  Returns:
    Next component.
  Remarks:
    operator++ and NextComponent() behave differently.
  */
  const class ON_SubDComponentPtr NextComponent();  

  /*
  Returns:
    Current component;
  */
  const class ON_SubDComponentPtr CurrentComponent() const
  {
    return m_cptr_current;
  }

  /*
  Description:
    Set the iterator to the end of the component list.
  Returns:
    Last component in the list.
  */
  const class ON_SubDComponentPtr LastComponent();

private:
  ON_SubDRef m_subd_ref;
  unsigned int m_subd_level = 0;
  const ON_SubDVertex* m_vertex_first = nullptr;
  const ON_SubDVertex* m_vertex_last = nullptr;
  const ON_SubDEdge* m_edge_first = nullptr;
  const ON_SubDEdge* m_edge_last = nullptr;
  const ON_SubDFace* m_face_first = nullptr;
  const ON_SubDFace* m_face_last = nullptr;
  ON_SubDComponentPtr m_cptr_current = ON_SubDComponentPtr::Null;
};


//////////////////////////////////////////////////////////////////////////
//
// ON_SubDMeshFragmentIterator
//

class ON_CLASS ON_SubDMeshFragmentIterator
{
public:
  ON_SubDMeshFragmentIterator() = default;
  ~ON_SubDMeshFragmentIterator() = default;
  ON_SubDMeshFragmentIterator(const ON_SubDMeshFragmentIterator&);
  ON_SubDMeshFragmentIterator& operator=(const ON_SubDMeshFragmentIterator&);

public:
  ON_SubDMeshFragmentIterator(const class ON_SubDMesh limit_mesh);
  ON_SubDMeshFragmentIterator(ON_SubDRef& subd_ref);
  ON_SubDMeshFragmentIterator(const ON_SubD& subd);
  ON_SubDMeshFragmentIterator(const ON_SubDFaceIterator& fit);

public:
  const ON_SubDMeshFragment* FirstFragment();
  const ON_SubDMeshFragment* NextFragment();
  const ON_SubDMeshFragment* CurrentFragment();

  bool IsEmpty() const;

  const ON_SubD& SubD() const;

  /*
  Returns
    ON_SubDComponentLocation::Surface or ON_SubDComponentLocation::ControlNet
  */
  ON_SubDComponentLocation SubDAppearance() const;
  
  /*
  Parameters:
    subd_appearance_override - [in]
      ON_SubDComponentLocation::Unset - appearance controlled by SubD().SubDAppearance().
      ON_SubDComponentLocation::Surface
      ON_SubDComponentLocation::ControlNet
  Returns
    ON_SubDComponentLocation::Surface or ON_SubDComponentLocation::ControlNet
  */
  void SetSubDAppearanceOverride(ON_SubDComponentLocation subd_appearance_override);


  /*
  Returns:
    Density setting used to create the fragments and the maximum mesh density
    these fragments can deliver.
  Remarks:
    0: a single mesh quad per SubD quad 
    1: 4 mesh quads per SubD quad (n mesh quads per SubD n-gon when n != 4)
    d: 4^d mesh quads per SubD quad (n*(4^(d-1)) mesh quads per SubD n-gon when n != 4)
  */
  unsigned int MaximumMeshDensity() const;

  /*
  Returns:
    Minimum mesh density that can be extracted from these fragments.
  Remarks:
    0 = all fragments are full sized.
    1 = there are half sixed fragments because the SubD has n-gons with n != 4.
  */
  unsigned int MinimumMeshDensity() const;

  enum : unsigned int
  {
    /// <summary>
    /// Rhino uses this value in MeshDensityFromMaxMeshQuadCount() to se the default level of detail.
    /// The enum will always exist but the value can change without breaking the SDK. 
    /// You code must assume this value will change with each service release of Rhino.
    /// </summary>
    DefaultMaximumMeshQuadCount = 262144
  };

  /*
  Parameters:
    candidate_mesh_density - [in]
  Returns:
    If candidate_mesh_density > MeshDensity(), then MeshDensity() is returned.
    If candidate_mesh_density < MinimumMeshDensity(), then MinimumMeshDensity() is returned.
    Otherwise, candidate_mesh_density is returned.
  */
  unsigned int ClampMeshDensity(
    unsigned int candidate_mesh_density
  ) const;

  /*
  Returns:
    Total number of fragments.
  */
  unsigned int FragmentCount() const;

  /*
  Returns:
    Total number of full sized fragments. 
  Remarks:
    A full sized fragment covers an entire quad face.
  */
  unsigned int FullSizeFragmentCount() const;

  /*
  Returns:
    Total number of half sized fragments. 
  Remarks:
    A half sized fragment covers the corner of an N-gon and are used when N != 4.
  */
  unsigned int HalfSizeFragmentCount() const;


  /*
  Parameters:
    full_size_fragment_count - [out]
      Number of full sized fragments. These cover an entire quad face.
    half_size_fragment_count - [out]
      Number of half sized fragments. These cover a corner of an N-gon
      and are used when N != 4.
  Returns:
    Total number of fragments.
  */
  unsigned int GetFragmentCounts(
    unsigned int& full_size_fragment_count,
    unsigned int& half_size_fragment_count
  ) const;

  /*
  Parameters:
    mesh_density - [in]
      MinimumMeshDensity() <= mesh_density <= MeshDensity()
  Returns:
    Total number of mesh quads in at the specified mesh density.
  */
  unsigned int TotalQuadCount(unsigned int mesh_density) const;

  /*
  Parameters:
    mesh_density - [in]
      MinimumMeshDensity() <= mesh_density <= MeshDensity()
  Returns:
    Total number of mesh points delivered at the specified mesh density.
  */
  unsigned int TotalPointCount(unsigned int mesh_density) const;

  /*
  Returns:
    Total number of mesh quads delivered at MaximumMeshDensity().
  */
  unsigned int MaximumDensityQuadCount() const;

  /*
  Parameters:
    mesh_density - [in]
      MinimumMeshDensity() <= mesh_density <= MeshDensity()
  Returns:
    Total number of mesh points delivered at MaximumMeshDensity().
  */
  unsigned int MaximumDensityPointCount() const;

  const ON_BoundingBox SurfaceBoundingBox() const;
  const ON_BoundingBox ControlNetQuadBoundingBox() const;
  /*
  Returns:
    If this->SubDAppearance() is ON_SubDComponentLocation::ControlNet, then this->ControlNetQuadBoundingBox() is returned.
    Otherwise this->SurfaceBoundingBox() returned.
  */
  const ON_BoundingBox BoundingBox() const;

private:
  void Internal_CopyFrom(const ON_SubDMeshFragmentIterator& src);

  ON_SubDMesh m_limit_mesh;
  ON_SubD m_subd;
  ON_SubDFaceIterator m_fit;
  const ON_SubDMeshFragment* m_current_fragment = nullptr;
  bool m_bFromFaceFragments = false;
  mutable bool m_bHaveCounts = false;

  // used to override the appearance of SubD().SubDApperance().
  ON_SubDComponentLocation m_subd_appearance_override = ON_SubDComponentLocation::Unset;

private:
  // Rendering density = MaximumMeshDensity() - m_density_reduction.
  unsigned char m_reserved_density_reduction = 0; // 0 = none

private:
  mutable unsigned int m_maximum_mesh_density = 0; // See MaximumMeshDensity() comment

  // full sized fragment count (for quads)
  mutable unsigned int m_full_size_fragment_count = 0;

  // half sized fragment count (for n-gons with n != 4)
  mutable unsigned int m_half_size_fragment_count = 0;
};


//////////////////////////////////////////////////////////////////////////
//
// ON_SubDSectorIterator
//

class ON_CLASS ON_SubDSectorIterator
{
public:
  static const ON_SubDSectorIterator Empty;

  ON_SubDSectorIterator() = default;
  ~ON_SubDSectorIterator() = default;
  ON_SubDSectorIterator(const ON_SubDSectorIterator&) = default;
  ON_SubDSectorIterator& operator=(const ON_SubDSectorIterator&) = default;


  /*
  Parameters:
    center_vertex - [in]
      The vertex to iterated around.
      center_vertex->Face(0) is used to select the sector.
  Returns:
    If input is valid, a pointer to the center vertex is returned.
    Otherwise, nullptr is returned.
  */
  const ON_SubDVertex* Initialize(
    const ON_SubDVertex* center_vertex
    );

  /*
  Parameters:
    initial_face - [in]
    iterator_orientation - [in]
      0: (more common) 
        "next" means counter-clockwise with respect to the orientation of initial_face
      1: (less common)
        "next" means clockwise with respect to the orientation of initial_face
    center_vertex - [in]
      The vertex on initial_face that will be iterated around.
  Returns:
    If input is valid, a pointer to the center vertex is returned.
    Otherwise, nullptr is returned.
  */
  const ON_SubDVertex* Initialize(
    const ON_SubDFace* initial_face,
    ON__UINT_PTR iterator_orientation,
    const ON_SubDVertex* center_vertex
    );

  /*
  Parameters:
    initial_face - [in]
    iterator_orientation - [in]
      0: (more common) 
        "next" means counter-clockwise with respect to the orientation of initial_face
      1: (less common)
        "next" means clockwise with respect to the orientation of initial_face
    face_vertex_index - [in]
      initial_face->Vertex(face_vertex_index) is the center vertex
      that will be iterated around.
  Returns:
    If input is valid, a pointer to the center vertex is returned.
    Otherwise, nullptr is returned.
  */
  const ON_SubDVertex* Initialize(
    const ON_SubDFace* initial_face,
    ON__UINT_PTR iterator_orientation,
    unsigned int face_vertex_index
    );

  bool InitializeToCurrentFace();

  void Initialize();

  /*
  Description:
  The current ring index reports the total increment from the
  start to the current state.  It can be positive or negative.
  */
  int CurrentRingIndex() const;

  const ON_SubDVertex* CenterVertex() const;

  const ON_SubDFace* InitialFace() const;

  unsigned int InitialFaceCenterVertexIndex() const;

  const ON_SubDFace* CurrentFace() const;

  unsigned int CurrentFaceDirection() const;

  ON_SubDFacePtr CurrentFacePtr() const;

  unsigned int CurrentFaceCenterVertexIndex() const;


  /*
  Description:

                CurrentEdge(1)
                    |
                    |
         NextFace() | CurrentFace()
                    |
                    |
                    *------------- CurrentEdge(0)
                        PrevFace()

    The asterisk (*) marks the center vertex.
    The diagram is With respect to the initial iterator orientation.

  Parameters:
    face_side_index - [in]
      CurrentEdge(0) = edge on the clockwise (PrevFace) side of the current face
      CurrentEdge(1) = edge on the counterclockwise (NextFace) side of the current face
      The directions "counterclockwise" and "clockwise" are with respect to the
      initial iterator orientation.

   Returns:
    The requested edge. The edge pointer is oriented such that 
    RelativeVertex(0) is the center vertex.
  */
  ON_SubDEdgePtr CurrentEdgePtr(
    unsigned int face_side_index
    ) const;

  /*
  Description:

                CurrentEdge(1)
                    |
                    |
         NextFace() | CurrentFace()
                    |
                    |
                    *------------- CurrentEdge(0)
                        PrevFace()

    The asterisk (*) marks the center vertex.
    The diagram is With respect to the initial iterator orientation.

  Parameters:
    face_side_index - [in]
      CurrentEdge(0) = edge on the clockwise (PrevFace) side of the current face
      CurrentEdge(1) = edge on the counterclockwise (NextFace) side of the current face
      The directions "counterclockwise" and "clockwise" are with respect to the
      initial iterator orientation.
  Returns:
    The requested edge or nullptr if the iterator is not initialized, 
    has terminated, or is not valid. 
    When the sector iterator is initialized and valid, sit.CenterVertex() = CurrentEdge(*).RelativeVertex(0).
  */
  const ON_SubDEdge* CurrentEdge(
    unsigned int face_side_index
    ) const;

  ON__UINT_PTR CurrentEdgeDirection(
    unsigned int face_side_index
    ) const;

  /*
  Returns:
    The vertex on CurrentEdge(face_side_index) that is opposite
    the central vertex.
  */
  const ON_SubDVertex* CurrentEdgeRingVertex(
    unsigned int face_side_index
    ) const;

  enum class StopAt : unsigned char
  {
    ///<summary>
    /// Sector iteration will terminate when the edge being crossed does not have two faces.
    ///</summary>
    Boundary = 0,

    ///<summary>
    /// Sector iteration will terminate when the edge being crossed does not have two faces
    /// or that edge is tagged as ON_SubDEdgeTag::Crease.
    ///</summary>
    AnyCrease = 1,

    ///<summary>
    /// Sector iteration will terminate when the edge being crossed does not have two faces
    /// or that edge is tagged as ON_SubDEdgeTag::Crease and has no dart vertices.
    ///</summary>
    HardCrease = 2,
  };

  /*
  Description:
    Advance the "current" face to the "next" face in the ring
    by crossing CurrentEdge(1).  
    
    If the current face is not reversed (1 == CurrentFaceDirection),
    then this rotation is counter-clockwise with respect to 
    the current face's orientation.
    
    If the current face is reversed (1 == CurrentFaceDirection),
    then this rotation is clockwise with respect to 
    the current face's orientation.
  Parameters:
    stop_at - [in]
      Determines that type of CurrentEdge(1) will terminate iteration.
  Returns:
    When the input CurrentEdge(1) has exactly two faces and
    is not tagged as a crease or bStopAtCrease is false, the 
    face on the other side of CurrentEdge(1) becomes the new
    current face and a pointer to this face is returned.
  Remarks:
    Identical to calling IncrementFace(+1,bStopAtCrease);
  */
  const ON_SubDFace* NextFace(
    ON_SubDSectorIterator::StopAt stop_at
    );

  /*
  Description:
    Advance the "current" face to the "previous" face in the ring
    by crossing CurrentEdge(0).  
    
    If the current face is not reversed (0 == CurrentFaceDirection),
    then this rotation is clockwise with respect to 
    the current face's orientation.
    
    If the current face is reversed (1 == CurrentFaceDirection),
    then this rotation is counter-clockwise with respect to 
    the current face's orientation.
  Parameters:
    stop_at - [in]
      Determines that type of CurrentEdge(0) will terminate iteration.
  Returns:
    When the input CurrentEdge(0) has exactly two faces and
    is not tagged as a crease or bStopAtCrease is false, the 
    face on the other side of CurrentEdge(0) becomes the new
    current face and a pointer to this face is returned.
    In all other cases, nullptr is returned
  Remarks:
    Identical to calling IncrementFace(-1,bStopAtCrease);
  */
  const ON_SubDFace* PrevFace(
    ON_SubDSectorIterator::StopAt stop_at
    );

  /*
  Description:
    Advance the "current" face by "hopping across" the edge
    CurrentEdge((increment_direction>0) ? 1 : 0).
    
    If the current face is not reversed (0 == CurrentFaceDirection),
    then increment_direction>0 rotates counter-clockwise with respect to 
    the current face's orientation.
    
    If the current face is reversed (1 == CurrentFaceDirection),
    then increment_direction>0 rotates clockwise with respect to 
    the current face's orientation.
  Parameters:
    increment_direction - [in]
      > 0 advance the "current" face to next face
      <= 0 advance the "current" face to previous face
    stop_at - [in]
      Determines that type of CurrentEdge((increment_direction>0) ? 1 : 0) will terminate iteration.
      If true and the input value of CurrentEdge((increment_direction>0) ? 1 : 0) 
      When iteration terminates at a crease, 
      CurrentFace() becomes nullptr
      CurrentEdge((increment_direction>0) ? 1 : 0) becomes nullptr
      CurrentEdge((increment_direction>0) ? 0 : 1) points at the crease
      and nullptr returned.
  Returns:
    nullptr if iteration terminates.
  */
  const ON_SubDFace* IncrementFace(
    int increment_direction,
    ON_SubDSectorIterator::StopAt stop_at
    );

  /*
  Description:
    Increment the iterator until it reaches a face with 
    a crease 
  Parameters:
    increment_direction - [in]
    > 0 advance next until CurrentEdge(1) is a crease.
    <= 0 advance previous until CurrentEdge(0) is a crease.
  Returns:
    nullptr - the sector has no creases.
    not nullptr - incremented to a crease
  */
  const ON_SubDFace* IncrementToCrease(
    int increment_direction
    );

  /*
  Description:
    Increment the iterator until it reaches a face with
    a crease
  Parameters:
    increment_direction - [in]
    > 0 advance next until CurrentEdge(1) is a crease.
    <= 0 advance previous until CurrentEdge(0) is a crease.
  Returns:
    nullptr - the sector has no creases.
    not nullptr - incremented to a crease
  */

  /// <summary>
  /// Increment the iterator until it reaches a face with a crease on the
  /// side indicated by increment_direction. 
  /// </summary>
  /// <param name="increment_direction">
  /// &gt; 0 advance next until CurrentEdge(1) is a crease.
  /// &lt;= 0 advance previous until CurrentEdge(0) is a crease.
  /// </param>
  /// <param name="increment_count">
  /// The number of inrements it took to reach a crease.
  /// </param>
  /// <returns>
  /// ON_SubDEdgeTag::Smooth:
  ///   The sector has no creases and the iterator was not changed.
  /// ON_SubDEdgeTag::Crease: 
  ///   The sector has a crease edge and this-&lt;CurrentEdge(increment_direction &gt; 0 ? 1 : 0)
  ///   is a crease.
  /// ON_SubDEdgeTag::Unset: 
  ///   This sector iterator is not valid. No changes.
  /// </returns>
  ON_SubDEdgeTag IncrementToCrease(
    int increment_direction,
    unsigned* increment_count
  );


  /*
  Description:
    Reset iterator to initial face.
  */
  const ON_SubDFace* FirstFace();

  bool IsValid() const;

private:
  const ON_SubDVertex* m_center_vertex = nullptr;
  const ON_SubDFace* m_initial_face = nullptr;
  const ON_SubDFace* m_current_face = nullptr;

  // m_current_eptr[0].Edge() = "prev" side edge
  // m_current_eptr[1].Edge() = "next" side edge
  // center vertex = m_current_eptr[i].RelativeVertex(0)
  ON_SubDEdgePtr m_current_eptr[2] = {}; // default = { ON_SubDEdgePtr::Null, ON_SubDEdgePtr::Null };

  unsigned int m_initial_fvi = 0;
  unsigned int m_current_fvi = 0;
  unsigned int m_current_fei[2] = {};  // default = { 0, 0 }; // "prev" and "next"

  // m_initial_face_dir 
  // 0: "next" means clockwise with respect to the initial face's orientation.
  // 1: "next" means counter-clockwise with respect to the initial face's orientation.
  unsigned int m_initial_face_dir = 0;

  // m_current_face_dir 
  // 0: "next" means clockwise with respect to the initial face's orientation.
  // 1: "next" means counter-clockwise with respect to the initial face's orientation.
  // When the subd faces around the center vertex are consistently oriented, 
  // m_current_face_dir is always equal to m_initial_face_dir.
  unsigned int m_current_face_dir = 0;

  int m_current_ring_index = 0;
};


//////////////////////////////////////////////////////////////////////////
//
// ON_SubDFaceEdgeIterator
//
class ON_CLASS ON_SubDFaceEdgeIterator
{
public:
  ON_SubDFaceEdgeIterator();

  /*
  Description:
    Construct an iterator for going around the edges on a face.
  Parameters:
    face - [in]
    first_edge - [in]
      starting edge for the iterator or nullptr to start at face->Edge(0).
  */
  ON_SubDFaceEdgeIterator(
    const ON_SubDFace* face
    );

  ON_SubDFaceEdgeIterator(
    const ON_SubDFace* face,
    const ON_SubDEdge* first_edge
    );


  /*
  Description:
    Initialize an iterator for going around the edges on a face.
  Parameters:
    face - [in]
    first_edge - [in]
      starting edge for the iterator or nullptr to start at face->Edge(0).
  */
  unsigned int Initialize(
    const ON_SubDFace* face
    );

  unsigned int Initialize(
    const ON_SubDFace* face,
    const ON_SubDEdge* first_edge
    );

  unsigned int EdgeCount() const;

  /*
  Returns:
    Resets the iterator and returns the first edge.
  */
  const ON_SubDEdge* FirstEdge();

  /*
  Description:
    Increments the iterator and returns the edge.
  */
  const ON_SubDEdge* NextEdge();

  /*
  Description:
    Decrements the iterator and returns the edge.
  */
  const ON_SubDEdge* PrevEdge();


  /*
  Parameters:
    bReturnNullAtFirstEdge = [in]
      If true and the next edge would be FirstEdge(), the nullptr is returned
      and CurrentEdge() is not changed.
  Description:
    Increments the iterator and returns the edge.
  */
  const ON_SubDEdge* NextEdge(
    bool bReturnNullAtFirstEdge
  );

  /*
  Parameters:
    bReturnNullAtLastEdge = [in]
      If true and the previous edge would be FirstEdge(), the nullptr is returned
      and CurrentEdge() is not changed.
  Description:
    Decrements the iterator and returns the edge.
  */
  const ON_SubDEdge* PrevEdge(
    bool bReturnNullAtFirstEdge
  );

  /*
  Returns:
  Current edge.
  */
  const ON_SubDEdge* CurrentEdge() const;

  unsigned int FirstEdgeIndex() const;

  unsigned int CurrentEdgeIndex() const;

private:
  const ON_SubDFace* m_face;
  unsigned int m_edge_count;
  unsigned int m_edge_index0;
  unsigned int m_edge_index;
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDFromMeshParameters
//
class ON_CLASS ON_SubDFromMeshParameters
{
public:

  // Default construction is identical to ON_SubDFromMeshParameters::Smooth.
  ON_SubDFromMeshParameters() = default;
  ~ON_SubDFromMeshParameters() = default;
  ON_SubDFromMeshParameters(const ON_SubDFromMeshParameters&) = default;
  ON_SubDFromMeshParameters& operator=(const ON_SubDFromMeshParameters&) = default;

  ///////////////////////////////////////////////////////////////////////////////////////
  //
  // Crease options
  //

  // No interior creases and no corners.
  static const ON_SubDFromMeshParameters Smooth;


  // Create an interior sub-D crease along all input mesh double edges.
  static const ON_SubDFromMeshParameters InteriorCreases;

  // Create an interior sub-D crease along all input mesh double edges.
  // Look for convex corners at sub-D vertices with 2 edges or fewer
  // that have an included angle <= 120 degrees.
  static const ON_SubDFromMeshParameters ConvexCornersAndInteriorCreases;

  // Create an interior sub-D crease along all input mesh double edges.
  // Look for convex corners at sub-D vertices with 2 edges or fewer
  // that have an included angle <= 120 degrees.
  // Look for concave corners at sub-D vertices with 3 edges or more
  // that have an included angle >= 240 degrees.
  static const ON_SubDFromMeshParameters ConvexAndConcaveCornersAndInteriorCreases;

  ///////////////////////////////////////////////////////////////////////////////////////
  //
  // Custom interior crease options
  //
#pragma region RH_C_SHARED_ENUM [ON_SubDFromMeshParameters::InteriorCreaseOption] [Rhino.Geometry.SubDCreationOptions.InteriorCreaseOption] [nested:byte]
  /// <summary>
  /// Specifies the test used to determine when an interior mesh edge generates an interior SubD creased edge.
  /// </summary>
  enum class InteriorCreaseOption : unsigned char
  {
    ///<summary>The interior crease test is not defined.</summary>
    Unset = 0,

    ///<summary>No interior creases.</summary>
    None = 1,

    ///<summary>An interior mesh double edge will create an interior SubD creased edge.
    /// An interior mesh double edge occurs when the sides of two mesh faces have
    /// have distinct vertex indices and identical vertex locations.
    ///</summary>
    AtMeshDoubleEdge = 2,
  };
#pragma endregion

  static ON_SubDFromMeshParameters::InteriorCreaseOption InteriorCreaseOptionFromUnsigned(
    unsigned int interior_crease_option_as_unsigned
    );

  /*
  Parameters:
    interior_crease_option - [in]
  */
  void SetInteriorCreaseOption(
    ON_SubDFromMeshParameters::InteriorCreaseOption interior_crease_option
    );

  /*
  Returns:
    The interior crease option.
  */
  ON_SubDFromMeshParameters::InteriorCreaseOption GetInteriorCreaseOption() const;

  /*
  Description:
    Copy all settings that control how interior crease edges are created.
  Parameters:
    source_options - [in]
  Returns:
    The currently selected interior crease option.
  */
  ON_SubDFromMeshParameters::InteriorCreaseOption CopyInteriorCreaseTest(
    ON_SubDFromMeshParameters source_options
    );


  ///////////////////////////////////////////////////////////////////////////////////////
  //
  // Convex corner options
  //
#pragma region RH_C_SHARED_ENUM [ON_SubDFromMeshParameters::ConvexCornerOption] [Rhino.Geometry.SubDCreationOptions.ConvexCornerOption] [nested:byte]
  /// <summary>
  /// Defines how convex corners are treated.
  /// </summary>
  enum class ConvexCornerOption : unsigned char
  {
    ///<summary>The option is not set.</summary>
    Unset = 0,

    ///<summary>No convex corners. In general,this is the best choice.</summary>
    None = 1,

    ///<summary>
    /// A convex subd corner will appear at input mesh boundary vertices 
    /// where the corner angle &lt;= MaximumConvexCornerAngleRadians() and
    /// the number of edges the end at the vertex is &lt;= MaximumConvexCornerEdgeCount().
    ///</summary>
    AtMeshCorner = 2
  };
#pragma endregion

  static ON_SubDFromMeshParameters::ConvexCornerOption ConvexCornerOptionFromUnsigned(
    unsigned int convex_corner_option_as_unsigned
    );

  /*
  Parameters:
    convex_corner_option - [in]
  */
  void SetConvexCornerOption(
    ON_SubDFromMeshParameters::ConvexCornerOption convex_corner_option
    );

  /*
  Returns:
    The currently selected convex corner option.
  */
  ON_SubDFromMeshParameters::ConvexCornerOption GetConvexCornerOption() const;

  /*
  Description:
    If ConvexCornerTest() ConvexCornerOption::at_mesh_corner, then an
    input mesh boundary vertex becomes a sub-D corner when the number of
    edges that end at the vertex is <= MaximumConvexCornerEdgeCount() edges
    and the corner angle is <= MaximumConvexCornerAngleRadians().
  Parameters:
    maximum_convex_corner_edge_count - [in]
  */
  void SetMaximumConvexCornerEdgeCount(
    unsigned int maximum_convex_corner_edge_count
    );

  /*
  Description:
    If ConvexCornerTest() ConvexCornerOption::at_mesh_corner, then an
    input mesh boundary vertex becomes a sub-D corner when the number of
    edges that end at the vertex is <= MaximumConvexCornerEdgeCount() edges
    and the corner angle is <= MaximumConvexCornerAngleRadians().
  Returns:
    The maximum number of edges at a convex corner vertex.
  */
  unsigned int MaximumConvexCornerEdgeCount() const;

  /*
  Description:
    If ConvexCornerTest() ConvexCornerOption::at_mesh_corner, then an
    input mesh boundary vertex becomes a sub-D corner when the number of
    edges that end at the vertex is <= MaximumConvexCornerEdgeCount() edges
    and the corner angle is <= MaximumConvexCornerAngleRadians().

    The default value is 2pi/3 = 120 degrees.
  Parameters:
    maximum_convex_corner_angle_radians - [in]
      > 0.0 and < ON_PI
  */
  void SetMaximumConvexCornerAngleRadians(
    double maximum_convex_corner_angle_radians
    );

  /*
  Description:
    If ConvexCornerTest() ConvexCornerOption::at_mesh_corner, then an
    input mesh boundary vertex becomes a sub-D corner when the number of
    edges that end at the vertex is <= MaximumConvexCornerEdgeCount() edges
    and the corner angle is <= MaximumConvexCornerAngleRadians().

    The default value is 2pi/3 = 120 degrees.
  Returns:
    The maximum corner angle.
  */
  double MaximumConvexCornerAngleRadians() const;
  
  /*
  Description:
    Copy all settings that control how convex corner vertices are created.
  Parameters:
    source_options - [in]
  Returns:
    The currently selected convex corner option.
  */
  ON_SubDFromMeshParameters::ConvexCornerOption CopyConvexCornerTest(
    ON_SubDFromMeshParameters source_parameters
    );


  ///////////////////////////////////////////////////////////////////////////////////////
  //
  // Concave corner options
  //
#pragma region RH_C_SHARED_ENUM [ON_SubDFromMeshParameters::ConcaveCornerOption] [Rhino.Geometry.SubDCreationOptions.ConcaveCornerOption] [nested:byte]
  /// <summary>
  /// Defines how concave corners are treated.
  /// </summary>
  enum class ConcaveCornerOption : unsigned char
  {
    ///<summary>The option is not set.</summary>
    Unset = 0,

    ///<summary>No concave corners. In general, this is the best choice.</summary>
    None = 1,

    ///<summary>
    /// A concave subd corner will appear at input mesh boundary vertices 
    /// where the corner angle &gt;= MinimumConcaveCornerAngleRadians() and
    /// the number of edges the end at the vertex is &gt;= MinimumConcaveCornerEdgeCount().
    ///</summary>
    AtMeshCorner = 2
  };
#pragma endregion

  static ON_SubDFromMeshParameters::ConcaveCornerOption ConcaveCornerOptionFromUnsigned(
    unsigned int concave_corner_option_as_unsigned
  );

  /*
  Parameters:
    concave_corner_option - [in]
  */
  void SetConcaveCornerOption(
    ON_SubDFromMeshParameters::ConcaveCornerOption concave_corner_option
  );

  /*
  Returns:
    The currently selected concave corner option.
  */
  ON_SubDFromMeshParameters::ConcaveCornerOption GetConcaveCornerOption() const;

  /*
  Description:
    If ConcaveCornerTest() = ConcaveCornerOption::AtMeshConcaveCorner, then an
    input mesh boundary vertex becomes a sub-D corner when the number of
    edges that end at the vertex is >= MinimumConcaveCornerEdgeCount() edges
    and the corner angle is >= MinimumConcaveCornerAngleRadians().
  Parameters:
    minimum_concave_corner_edge_count - [in]
  */
  void SetMinimumConcaveCornerEdgeCount(
    unsigned int minimum_concave_corner_edge_count
  );

  /*
  Description:
    If ConcaveCornerTest() ConcaveCornerOption::AtMeshConcaveCorner, then an
    input mesh boundary vertex becomes a sub-D corner when the number of
    edges that end at the vertex is >= MinimumConcaveCornerEdgeCount() edges
    and the corner angle is >= MinimumConcaveCornerAngleRadians().
  Returns:
    The minimum number of edges at a concave corner vertex.
  */
  unsigned int MinimumConcaveCornerEdgeCount() const;

  /*
  Description:
    If ConcaveCornerTest() ConcaveCornerOption::AtMeshConcaveCorner, then an
    input mesh boundary vertex becomes a sub-D corner when the number of
    edges that end at the vertex is >= MinimumConcaveCornerEdgeCount() edges
    and the corner angle is >= MinimumConcaveCornerAngleRadians().
  Parameters:
    minimum_concave_corner_angle_radians - [in]
      > ON_PI and <= ON_2PI
  */
  void SetMinimumConcaveCornerAngleRadians(
    double minimum_concave_corner_angle_radians
  );

  /*
  Description:
    If ConcaveCornerTest() ConcaveCornerOption::AtMeshConcaveCorner, then an
    input mesh boundary vertex becomes a sub-D corner when the number of
    edges that end at the vertex is >= MinimumConcaveCornerEdgeCount() edges
    and the corner angle is >= MinimumConcaveCornerAngleRadians().
  Returns:
    The minimum corner angle.
  */
  double MinimumConcaveCornerAngleRadians() const;

  /*
  Description:
    Copy all settings that control concave corner vertices are created.
  Parameters:
    source_options - [in]
  Returns:
    The currently selected concave corner option.
  */
  ON_SubDFromMeshParameters::ConcaveCornerOption CopyConcaveCornerTest(
    ON_SubDFromMeshParameters source_parameters
  );

  /*
  Returns:
    false - In ON_SubD::CreateFromMesh(), input mesh vertex locations will be used to set subd vertex control net locations.
    true - In ON_SubD::CreateFromMesh(), input mesh vertex locations will be used to set subd vertex limit surface locations.
  Remark:
    Interpolation computation is available in Rhino, Rhino compute, Rhino Inside,
    Grasshopper. Interpolation computation is not available in the opennurbs IO toolkit.
  */
  bool InterpolateMeshVertices() const;

  /*
  Parameters:
    false
      In ON_SubD::CreateFromMesh(), input mesh vertex locations will be used to set subd vertex control net locations.
      This is the fastest and most robust way to create a subd from a mesh.
    true
      In ON_SubD::CreateFromMesh(), input mesh vertex locations will be used to set subd vertex limit surface locations.
      If there are a large number of vertices, this option can require lots of computation.
  Remark:
    Interpolation computation is available in Rhino, Rhino compute, Rhino Inside,
    Grasshopper. Interpolation computation is not available in the opennurbs IO toolkit.
  */
  void SetInterpolateMeshVertices(
    bool bInterpolateMeshVertices
  );


  ///////////////////////////////////////////////////////////////////////////////////////
  //
  // Texture coordinates
  //
#pragma region RH_C_SHARED_ENUM [ON_SubDFromMeshParameters::TextureCoordinatesOption] [Rhino.Geometry.SubDCreationOptions.TextureCoordinateOption] [nested:byte]
  /// <summary>
  /// Specifies how texture coordinate information is transferred from the mesh to the SubD.
  /// </summary>
  enum class TextureCoordinatesOption : unsigned char
  {
    ///<summary>The option is not set.</summary>
    Unset = 0,

    ///<summary>No texture coordianate information is transferred from the mesh.</summary>
    None = 1,

    ///<summary>
    /// If the mesh has a mapping, then TextureCoordinatesOption::CopyMapping is used.
    /// Otherwise if the mesh has texture coordinates, then TextureCoordinatesOption::CopyCoordinates is used.
    /// Otherwise TextureCoordinatesOption::Packed is used.
    ///</summary>
    Automatic = 2,

    ///<summary>
    /// No texture coordianate information is transferred from the mesh.
    /// The SubD faces are packed.
    ///</summary>
    Packed = 3,

    ///<summary>Texture coordinates mapping information is copied from the mesh.
    /// Generally this is the best choice because common mappings, like planar, 
    /// will appear as most people expect on the SubD.
    ///</summary>
    CopyMapping = 4,

    ///<summary>
    /// If a mesh has custom texture coordinates, the custom texture coordinates 
    /// are transferred to the SubD. This requires more memory resources, 
    /// slows subdivision evaluation, often produces unattractive
    /// results on n-gons, and distorts the texture when comes from a common mapping
    /// technique, like planar. This option may be useful when the mesh contains only 
    /// triangles and quads and the custom texture coordinates are of high quality.
    ///</summary>
    CopyCoordinates = 5,
  };
#pragma endregion


  /*
  Description:
    Set the texture coordinates option.
  Parameters:
    texture_coordinates_opton - [in]
  */
  void SetTextureCoordinatesOption(
    ON_SubDFromMeshParameters::TextureCoordinatesOption texture_coordinates_opton
  );

  /*
  Returns:
    The texture coorindates option.
  */
  ON_SubDFromMeshParameters::TextureCoordinatesOption GetTextureCoordinatesOption() const;

  static ON_SubDFromMeshParameters::TextureCoordinatesOption TextureCoordinatesOptionFromUnsigned(
    unsigned int texture_coordinates_opton_as_unsigned
  );


  /*
  Returns:
    true - In ON_SubD::CreateFromMesh(), colinear boundary edges belonging to the same face are merged into a single edge.
    false - In ON_SubD::CreateFromMesh(), each mesh boundary edge becomes a SubD boundary edge.
  */
  bool MergeColinearBoundaryEdges() const;

  /*
  Parameters:
    bMergeColinearBoundaryEdges - [in]
      true 
        In ON_SubD::CreateFromMesh(), colinear boundary edges belonging to the same face are merged into a single edge.
        In general, this is the best choice and leads to the highest quality of SubD object.
      false
        In ON_SubD::CreateFromMesh(), each mesh boundary edge becomes a SubD boundary edge.
        Use this when the boundary topology of the mesh and SubD should be identical.
  */
  void SetMergeColinearBoundaryEdges(
    bool bMergeColinearBoundaryEdges
  );

  /*
  Returns:
    true - In ON_SubD::CreateFromMesh(), colinear interior edges between two faces are merged into a single edge.
    false - In ON_SubD::CreateFromMesh(), each mesh interior edge becomes a SubD interior edge.
  */
  bool MergeColinearInteriorEdges() const;

  /*
  Parameters:
  bMergeColinearInteriorEdges - [in]
    true
      In ON_SubD::CreateFromMesh(), colinear interior edges between two faces are merged into a single edge.
      In general, this is the best choice and leads to the highest quality of SubD object.
    false
      In ON_SubD::CreateFromMesh(), each mesh interior edge becomes a SubD interior edge.
      Use this when the interior topology of the mesh and SubD should be identical.
  */
  void SetMergeColinearInteriorEdges(
    bool bMergeColinearInteriorEdges
  );

  
private:
  enum : unsigned char
  {
    MergeColinearBoundaryEdgesMask = 1,
    MergeColinearInteriorEdgesMask = 2
  };
  unsigned char m_merge_edges_bits = 0; // clear bit (0) = "true, set bit (1) = "false"

  bool m_bInterpolateMeshVertices = false;

  ON_SubDFromMeshParameters::InteriorCreaseOption m_interior_crease_option = ON_SubDFromMeshParameters::InteriorCreaseOption::None;
  ON_SubDFromMeshParameters::ConvexCornerOption m_convex_corner_option = ON_SubDFromMeshParameters::ConvexCornerOption::None;
  ON_SubDFromMeshParameters::ConcaveCornerOption m_concave_corner_option = ON_SubDFromMeshParameters::ConcaveCornerOption::None;
  ON_SubDFromMeshParameters::TextureCoordinatesOption m_texture_coordinates_option = ON_SubDFromMeshParameters::TextureCoordinatesOption::None;

  unsigned short m_maximum_convex_corner_edge_count = 2U;

  unsigned short m_minimum_concave_corner_edge_count = 4U;

  unsigned short m_reserved2 = 0;
  unsigned int m_reserved3 = 0;

  double m_reserved4 = 0.0;

  // default = 2pi/3 = 120 degrees
  double m_maximum_convex_corner_angle_radians = 120.0 * ON_DEGREES_TO_RADIANS;

  // default 4pi/3 = 240 degrees
  double m_minimum_concave_corner_angle_radians = 240.0 * ON_DEGREES_TO_RADIANS;
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDComponentRef
//
//  Used when an ON_SubD vertex, edge or face needs to be sent around as
//  a piece of ON_Geometry.
//
class ON_CLASS ON_SubDComponentRef : public ON_Geometry
{
  ON_OBJECT_DECLARE(ON_SubDComponentRef);
public:
  static const ON_SubDComponentRef Empty;

  ON_SubDComponentRef() = default;
  ~ON_SubDComponentRef() = default;
  ON_SubDComponentRef(const ON_SubDComponentRef&) ON_NOEXCEPT;
  ON_SubDComponentRef& operator=(const ON_SubDComponentRef&);

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_SubDComponentRef( ON_SubDComponentRef&& ) ON_NOEXCEPT;

  // The rvalue assignment operator calls ON_Object::operator=(ON_Object&&)
  // which could throw exceptions.  See the implementation of
  // ON_Object::operator=(ON_Object&&) for details.
  ON_SubDComponentRef& operator=( ON_SubDComponentRef&& );
#endif
  
  /*
  Parameters:
    subd_ref - [in]
    component_index - [in]
    component_location - [in]
  */
  static const ON_SubDComponentRef Create(
    const ON_SubDRef& subd_ref,
    ON_COMPONENT_INDEX component_index,
    ON_SubDComponentLocation component_location,
    ON__UINT_PTR reference_id
    );

  static const ON_SubDComponentRef Create(
    const ON_SubDRef& subd_ref,
    ON_SubDComponentPtr component_ptr,
    ON_SubDComponentLocation component_location,
    ON__UINT_PTR reference_id
    );

  static const ON_SubDComponentRef Create(
    const ON_SubDRef& subd_ref,
    const class ON_SubDVertex* vertex,
    ON_SubDComponentLocation component_location,
    ON__UINT_PTR reference_id
    );

  static const ON_SubDComponentRef Create(
    const ON_SubDRef& subd_ref,
    const class ON_SubDEdge* edge,
    ON_SubDComponentLocation component_location,
    ON__UINT_PTR reference_id
    );

  static const ON_SubDComponentRef Create(
    const ON_SubDRef& subd_ref,
    const class ON_SubDFace* face,
    ON_SubDComponentLocation component_location,
    ON__UINT_PTR reference_id
    );

  void Clear();

  ON_SubDRef SubDRef() const;

  const class ON_SubD& SubD() const;

  ON_COMPONENT_INDEX ComponentIndex() const override;

  ON_SubDComponentPtr ComponentPtr() const;

  ON_SubDComponentLocation ComponentLocation() const;

  /*
  Description:
    The interpretation of this value depends on the context.
    When the context is an ON_SubDComponentRef created by
    CRhinoGetObject, ReferenceId() is the parent CRhinoSubDObject's
    runtime serial number.
  */
  ON__UINT_PTR ReferenceId() const;

  void SetReferenceId(
    ON__UINT_PTR reference_id
  );

  const class ON_SubDVertex* Vertex() const;

  const class ON_SubDEdge* Edge() const;

  const class ON_SubDFace* Face() const;

  static int Compare(const ON_SubDComponentRef* lhs, const ON_SubDComponentRef* rhs);
  static int Compare2(const ON_SubDComponentRef* const* lhs, const ON_SubDComponentRef* const* rhs);
  
private:
  ON_SubDRef m_subd_ref;
  ON_SubDComponentPtr m_component_ptr = ON_SubDComponentPtr::Null;
  ON_COMPONENT_INDEX m_component_index = ON_COMPONENT_INDEX::UnsetComponentIndex;
  ON_SubDComponentLocation m_component_location =  ON_SubDComponentLocation::Unset;
  ON__UINT_PTR m_reference_id = 0;

public:
  // overrides of virtual ON_Object functions
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
  void Dump( ON_TextLog& ) const override;
  unsigned int SizeOf() const override;
  ON::object_type ObjectType() const override;

  // overrides of virtual ON_Geometry functions
  int Dimension() const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;
};

class ON_CLASS ON_SubDComponentRefList
{
public:
  ON_SubDComponentRefList() = default;
  ~ON_SubDComponentRefList();
  ON_SubDComponentRefList(const ON_SubDComponentRefList& src);
  ON_SubDComponentRefList& operator=(const ON_SubDComponentRefList& src);

  /*
  Description:
    Append a ON_SubDComponentRef to the identified component.
  Returns;
    A pointer to the ON_SubDComponentRef managed by this class or
    nullptr if the input is not valid.
  */
  const ON_SubDComponentRef& Append(
    const ON_SubDRef& subd_ref,
    ON_COMPONENT_INDEX ci,
    ON_SubDComponentLocation component_location,
    ON__UINT_PTR reference_id
  );

  const ON_SubDComponentRef& Append(
    const ON_SubDRef& subd_ref,
    ON_SubDComponentPtr component_ptr,
    ON_SubDComponentLocation component_location,
    ON__UINT_PTR reference_id
  );

  /*
  Description:
    Appends a copy of src_ref and returns a pointer to the ON_SubDComponentRef
    managed by this class.
  */
  const ON_SubDComponentRef& Append(const ON_SubDComponentRef& src_ref);
  const ON_SubDComponentRef& Append(const ON_SubDComponentRef* src_ref);

  /*
  Description:
    Expert user function to transfer management of an ON_SubDComponentRef on the heap
    to this class.
  */
  const ON_SubDComponentRef& AppendForExperts(ON_SubDComponentRef*& ref);

  /*
  Description:
    Expert user function to append a ON_SubDComponentRef to the identified component.
    The expert user is responsible for insuring subd exists fot the lifetime of this
    class.
  */
  const ON_SubDComponentRef& AppendForExperts(
    const ON_SubD& subd,
    ON_COMPONENT_INDEX ci,
    ON_SubDComponentLocation component_location,
    ON__UINT_PTR reference_id
  );

  const ON_SubDComponentRef& AppendForExperts(
    const ON_SubD& subd,
    ON_SubDComponentPtr component_ptr,
    ON_SubDComponentLocation component_location,
    ON__UINT_PTR reference_id
  );

  /*
  Description:
    Sort by ON_SubDComponentRef::Compare2() and remove duplicates and empty elements.
  Returns:
    Length of clean list.
  */
  int Clean();


  /*
  Returns:
    Number of refs in the list.
  */
  int Count() const;
  
  void Remove(int i);

  /*
  Description:
    Transfers the ref to an expert user who is responsible for properly managing it.
  */
  ON_SubDComponentRef* TransferForExperts(int i);

  const ON_SubDComponentRef& operator[](int) const;

  /*
  Returns:
    If the list is clean, the number of subd objects in the list. Multiple components can belong to the same SubD.
    If the list is not clean, 0.
  Remarks:
    Use Clean() to get a clean list.
  */
  int SubDCount() const;

  /* 
  Returns:
    Number of vertices.
  */
  int VertexCount() const;

  /* 
  Returns:
    Number of vertices with the specified tag.
  */
  int VertexCount(ON_SubDVertexTag vertex_tag) const;

  /* 
  Returns:
    Number of edges.
  */
  int EdgeCount() const;

  /* 
  Returns:
    Number of edges with the specified tag.
  */
  int EdgeCount(ON_SubDEdgeTag edge_tag) const;


  /* 
  Returns:
    Number of faces.
  */
  int FaceCount() const;

  /*
  Returns:
    Number of components.
  */
  int ComponentCount() const;

private:
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 ) 
  // C4251: ... needs to have dll-interface to be used by clients of class ...
  // m_subdimple_sp is private and all code that manages m_subdimple_sp is explicitly implemented in the DLL.
  ON_SimpleArray< class ON_SubDComponentRef* > m_list;
#pragma ON_PRAGMA_WARNING_POP

  int m_subd_count = 0;
  int m_subd_vertex_smooth_count = 0;
  int m_subd_vertex_dart_count = 0;
  int m_subd_vertex_crease_count = 0;
  int m_subd_vertex_corner_count = 0;
  int m_subd_edge_smooth_count = 0;
  int m_subd_edge_crease_count = 0;
  int m_subd_face_count = 0;

  bool m_bIsClean = false; // true if m_list is clean.

  unsigned char m_reserved1 = 0;
  unsigned short m_reserved2 = 0;
  unsigned int m_reserved3 = 0;
  ON__UINT_PTR m_reserved4 = 0;

private:
  bool Internal_UpdateCount(const ON_SubDComponentRef& r, int delta);
  void Internal_Destroy();
  void Internal_CopyFrom(const ON_SubDComponentRefList& src);
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDComponentPoint
//
//  Used in selection tests to return a point and parameters on a component.
//
class ON_CLASS ON_SubDComponentPoint
{
public:
  static const ON_SubDComponentPoint Unset;

  ON_SubDComponentPoint() = default;
  ~ON_SubDComponentPoint() = default;
  ON_SubDComponentPoint(const ON_SubDComponentPoint&) = default;
  ON_SubDComponentPoint& operator=(const ON_SubDComponentPoint&) = default;

  /*
  Description:
    Dictionary compare of component type, component pointer, and component direction (partial).
    This function is useful for sorting arrays of ON_SubDComponentPoint values remove duplicates.
  */
  static int CompareComponentAndDirection(
    const ON_SubDComponentPoint* a,
    const ON_SubDComponentPoint* b
    );

  /*
  Description:
    Compare the pick events to determine the component the user was most likely aiming at.

  Parameters:
    pick_type - [in]
      When pick_type is ON_PickType::PointPick, several biases may be applied to favor vertices and edges.

    vertex_depth_bias - [in]
      When in doubt pass 0.0.
      A positive value increases vertex bias in some situations; otherwise vertex_depth_bias is ignored.
      When pick_type is ON_PickType::PointPick and either
      an edge and a vertex of that edge or a face and a vertex of that face are being compared,
      then then vertex_depth_bias is added to the vertex hit depth before comparing depths.
      When the pick is happening in a perspective view, it is important to choose a vertex_depth_bias
      appropriate for the depth in the view frustum.

    edge_depth_bias - [in]
      When in doubt pass 0.0.
      A positive value increases edge bias in some situations; otherwise vertex_depth_bias is ignored.
      When pick_type is ON_PickType::PointPick and a face and an edge of that face are being compared,
      then then edge_depth_bias is added to the edge hit depth before comparing depths.
      When the pick is happening in a perspective view, it is important to choose an edge_depth_bias
      appropriate for the depth in the view frustum.

    A - [in]
    B - [in]
  Returns:
    A pick point for the component the user was most likely aiming at
    with distance and depth settings that will lead to conistent improvement
    if more than two points are being compared.
  */
  static const ON_SubDComponentPoint BestPickPoint(
    ON_PickType pick_type,
    double vertex_depth_bias,
    double edge_depth_bias,
    const ON_SubDComponentPoint& A,
    const ON_SubDComponentPoint& B
  );
  
  // m_component_ptr will be face, edge or vertex
  ON_SubDComponentPtr m_component_ptr = ON_SubDComponentPtr::Null;

  //// If the point is on a a face that does not have the ordinary number of 
  //// edges for the subdivision type, then m_face_corner_index identifies the
  //// subfragment corner.
  //unsigned int m_face_corner_index = ON_UNSET_UINT_INDEX;

  //// If m_level_index is ON_UNSET_UINT_INDEX, the point is on the limit surface.
  //// Otherwise the point is on the control net at the specified level.
  //unsigned int m_level_index = ON_UNSET_UINT_INDEX;

  ON_PickPoint m_pick_point = ON_PickPoint::Unset;
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubDMatrix
//
class ON_CLASS ON_SubDMatrix
{
public:
  ON_SubDMatrix() = default;

  static const ON_SubDMatrix Empty;

  /*
  Description:
    Precise evaluation of cos(a) and cos(a) where a = i/n pi.
    These values are required for high qualitiy limit surface evaluation.
  Parameters:
    j - [in]
    n - [in]
    cos_theta - [out]
      cos(j/n pi)
    sin_theta - [out]
      sin(j/n pi)
  */
  static bool EvaluateCosAndSin(
    unsigned int j,
    unsigned int n,
    double* cos_theta,
    double* sin_theta
    );

  bool IsValid() const;

  bool IsValidPointRing(
    const double* point_ring,
    size_t point_ring_count,
    size_t point_ring_stride
    ) const;

  bool EvaluateSubdivisionPoint(
    unsigned int component_index,
    const double* point_ring,
    size_t point_ring_count,
    size_t point_ring_stride,
    double subd_point[3]
    ) const;

  bool EvaluateSurfacePoint(
    const double* point_ring,
    size_t point_ring_count,
    size_t point_ring_stride,
    bool bUndefinedNormalIsPossible,
    double limit_point[3],
    double limit_tangent1[3],
    double limit_tangent2[3],
    double limit_normal[3]
    ) const;

  bool EvaluateSurfacePoint(
    const double* point_ring,
    size_t point_ring_count,
    size_t point_ring_stride,
    bool bUndefinedNormalIsPossible,
    class ON_SubDSectorSurfacePoint& limit_point
    ) const;

  /*
  Description:
    Get the subdivision matrix information for the case specified
    by the input parameters.  This information is retrieved from
    a cache.  In some cases, it will be calculated the first time
    it is needed.  
  Parameters:
    facet_type - [in]
    vertex_tag - [in]
    valence - [in]
      The input parameters identify the subdivision case.
  Remarks:
    Every member function of ON_SubDMatrix, including this one
    is thread safe.
  */
  static const ON_SubDMatrix& FromCache(
    ON_SubDSectorType sector_type
    );

  ON_SubDSectorType m_sector_type;

  unsigned int m_R = 0; // the matrix m_S is m_R x m_R (m_R = m_sector_type.PointRingCount())

  // The term "standard vertex ring points" is used below. 
  //
  // Let "C" be an interior vertex (m_vertex_tag is smooth or dart), 
  // (E[0], ...., E[N-1]) is a radially sorted list of its edges, 
  // (F[0], ..., F[N-1]) is a radially sorted list of its faces (F[i] is between E[i] and E[(i+1)%N]),
  // (P[0], ..., P[N-1]) are the vertices on the edges opposide Cn (P[i] is on E[i].
  // 
  // C is a "standard" smooth vertex if 
  // all edges E[i] are smooth with sharpness = 0,
  // and all faces f[i] are quads.
  // 
  // C is a "standard" dart vertex if
  // edge E[0] is a crease,
  // edges E[1], ..., E[N-1] are smooth with sharpness = 0,  
  // and all faces F[i] are quads.
  //
  // If If "C" is a boundary vertex (m_vertex_tag is crease or corner), the conditions
  // listed above are satisfied except 
  // E[0] and E[N-1] are crease edges, 
  // E[1], ..., E[N-2] are smooth edges with sharpness = 0, 
  // and faces f[0], ..., F[N-2] are quads.
  // 
  // If C is a standard interior smooth or dart vertex,
  // then the "standard vertex ring" is the list of 2*N+1 points 
  // (C, P[0], Q[0], ...., P[N-1], Q[N-1]), 
  // where Q[I] is the vertex of quad F[i] diagonally across from C.
  //
  // If C is a standard boundary vertex,
  // then the "standard vertex ring" is the list of 2*N points 
  // (C, P[0], Q[0], ...., P[N-1]).

  // m_S = R x R subdivision matrix
  // If (vertexR[0], ..., vertexR[R-1]) is a list of standard vertex ring points,
  // then then the location of the subdivided ring points
  // (vertexR1[0], ..., vertexR1[R-1]) can be calculated from m_S.
  // vertexR1[i] = m_S[i][0]*vertexR[0] + ... + m_S[i][R-1]*vertexR[R-1]
  const double* const* m_S = nullptr;

  // m_LP[] = limit point evaluation vector.
  // The array m_LP[] has m_R elements.
  // If (vertexR[0], ..., vertexR[R-1]) is a list of standard vertex ring points,
  // then Limit point = m_LP[0]*vertexR[0] + ... + m_LP[R-1]*vertexR[R-1].
  // m_LP is the eigenvector of Transpose(m_S) with eigenvalue = 1.
  // Length(m_LP) = 1.
  const double* m_LP = nullptr;

  // m_L1 and m_L2 = tangent space evaluation vectors.
  // The arrays m_L1[] and m_L2[] have m_R elements.
  // If (vertexR[0], ..., vertexR[R-1]) is a list of standard vertex ring points,
  // then the two vectors 
  // V1 = m_L1[0]*vertexR[0] + ... + m_L1[R-1]*vertexR[R-1].
  // V2 = m_L2[0]*vertexR[0] + ... + m_L2[R-1]*vertexR[R-1].
  // span the tangent plane and 
  // N = V1 x V2 is perpendicular to the limit tangent plane.
  // In general and almost always in practice, V1 and V2 are not unit vectors
  // and it is best to normalize V1 and V2 before taking the cross product.
  // m_L1 and m_L2 are subdominant eigenvectors of Transpose(m_S).
  // When the subdominant eigenvalue has geometric multiplicity 2, 
  // m_L1 and m_L2 span the same space as m_E1 and m_E2. 
  // The values stored in m_L1 and m_L2 are chosen to provide accurate
  // evaluation. In come common cases m_L1 and m_L2 are equal to m_E1 and m_E2,
  // but not in all cases.
  const double* m_L1 = nullptr;
  const double* m_L2 = nullptr;

  /*
  Description:
    Set the values in this ON_SubDMatrix so the information 
    can be used to evaluate the case identified by the input
    parameters.
  Parameters:
    facet_type - [in]
    vertex_tag - [in]
    sector_edge_count - [in]
      The input parameters identify the subdivision case.
  Returns:
    R > 0: Success.  The matrix is R x R.
    0: Failure.
  */
  unsigned int SetFromSectorType(
    ON_SubDSectorType sector_type
    );

  /*
  Returns:
    ON_UNSET_VALUE - serious error
    >= 0:
      Maximum value of numbers that should be zero in and ideal world.  
      When the matrices, eigenvalues and eigenvectors are correctly calculated, 
      this returned value is in the range from 1e-16 to 5e-13 as valence goes 
      from 3 to 100.
      For valences < 100, if a value larger than 1.0e-12 occurs, there is a bug in the code.
  */
  double TestMatrix() const;

  /*
  Description:
    Run evaluation tests on this subdivision case.
  Returns:
    >= 0.0: Test passed. Maximum deviation found in any test is returned.
    ON_UNSET_VALUE: Test failed.
  */
  double TestEvaluation() const;

  /*
  Description:
    Run evaluation tests on a range of subdivision cases.
  Parameters:
    sector_type - [in]
      If ON_SubDSectorType::Empty, then all supported sector types types are tested.
    minimum_sector_face_count - [in]
      If 0, then testing begins at ON_SubDSectorType::MinimumSectorFaceCount(vertex_tag)
      when testing vertex_tag types
    maximum_sector_face_count - [in]
      If 0, then testing stops at ON_SubD::maximum_evaluation_valence.
    text_log - [out]
      If not nullptr, then a brief written report is printed for each test case.
  Returns:
    >= 0.0: Test passed.  Maximum deviation found in any test is returned.
    ON_UNSET_VALUE: Test failed.    
  */
  static double TestEvaluation(
    ON_SubDSectorType sector_type,
    unsigned int minimum_sector_face_count,
    unsigned int maximum_sector_face_count,
    ON_TextLog* text_log
    );

  double TestComponentRing(
    const ON_SubDComponentPtr* component_ring,
    size_t component_ring_count
    ) const;

  /*
  Description:
    Test cached subdivision matrix on sector identified by sit.
  Parameters:
    subd_type - [in]
    subd_recursion_count - [in]
      number of times to subdivide
    sit - [in]
      vertex to subdivide
    component_ring - [out]
    subd_points - [out]
    limit_point - [out]
    limit_tangent0 - [out]
    limit_tangent1 - [out]
    limit_normal - [out]
  */
  static double TestEvaluation(
    const unsigned int subd_recursion_count,
    ON_SubDSectorIterator sit,
    ON_SimpleArray<ON_SubDComponentPtr>& component_ring,
    ON_SimpleArray< ON_3dPoint >& subd_points,
    class ON_SubDSectorSurfacePoint& limit_point
    );

private:
  unsigned int m__max_R = 0;
  ON_Matrix m__S; // m_S matrix memory
  ON_SimpleArray<double> m__buffer; // m_LP, m_L1, m_L2, m_E1, m_E2 memory  
};

//////////////////////////////////////////////////////////////////////////
//
// ON_SubD_FixedSizeHeap
//

/*
Description:
  A ON_SubD_FixedSizeHeap is used to manage heap used for a local subdivision.
*/
class ON_CLASS ON_SubD_FixedSizeHeap
{
private:
  static unsigned int m__sn_factory;

public:
  // The serial number is used for debugging purposes.
  const unsigned int m_sn = ++m__sn_factory;

public:
  ON_SubD_FixedSizeHeap() = default;
  ~ON_SubD_FixedSizeHeap();

  /*
  Description:
    Reserve enough room to for a subdivision of a vertex sector.
  Parameters:
    sector_edge_count - [in]
      Number of edges in the sector.
  */
  bool ReserveSubDWorkspace(
    unsigned int sector_edge_count
    );

  /*
  Description:
    Reserve enough room for a local subdivide the neighborhood of center_face.
  Parameters:
    center_face0 - [in]
  */
  bool ReserveSubDWorkspace(
    const ON_SubDFace* center_face0
    );

private:
  bool Internal_ReserveSubDWorkspace(
    size_t vertex_capacity,
    size_t face_capacity,
    size_t array_capacity,
    bool bEnableHashTable
    );

  bool Internal_ReserveSubDWorkspace_HashTable();

public:

  /*
  Description:
    Reset this ON_SubD_FixedSizeHeap so it can be used again.
  */
  void Reset();

  /*
  Description:
    Deallocate all reserved heap.
  */
  void Destroy();

  bool InUse() const;

   ON_SubDVertex* AllocateVertex(
    const double vertexP[3],
    unsigned int edge_capacity
    );

  /*
  Description:
    Allocate a vertex located at the vertex0 subdivision point. 
    
  Parameters:
    vertex0 - [in]
    edge_capacity - [in]
      If the returned vertex will be interior in a local subdivision,
      then pass vertex0->EdgeCount().
      If the returned vertex will be an outer ring vertex in a local subdivision,
      then pass 3.
  */
  ON_SubDVertex* AllocateVertex(
    const ON_SubDVertex* vertex0,
    unsigned int edge_capacity
    );

  /*
  Description:
    Allocate a vertex located at the edge0 subdivision point. 
    The vertex will have an edge and face capacity of 4.
  Parameters:
    edge0 - [in]
  */
  ON_SubDVertex* AllocateVertex(
    const ON_SubDEdge* edge0
    );

  /*
  Description:
    Find or allocate a vertex located at the edge0 subdivision point. 
    The vertex will have an edge and face capacity of 4.
  Parameters:
    edge0 - [in]
  Remarks: 
    In order for FindOrAllocateVertex() to find a vertex, that vertex must 
    have been created  by an earlier call to FindOrAllocateVertex().
    Typically, AllocateVertex(edge0) is used for center face boundary edges
    and FindOrAllocateVertex(edge0) is used for ring edges.
  */
  ON_SubDVertex* FindOrAllocateVertex(
    const ON_SubDEdge* edge0
    );

  /*
  Description:
    Allocate a vertex located at the edge0 subdivision point.
    The vertex will have an edge and face capacity of 4.
  Parameters:
    edge0 - [in]
  */
  ON_SubDVertex* AllocateEdgeSubdivisionVertex(
    bool bUseFindOrAllocate,
    const ON_SubDEdge * edge0
  );

  /*
  Description:
    Find or allocate a vertex and the face subdivision point. The vertex will have an
    edge and face capacity of face0->EdgeCount().
  Parameters:
    face0 - [in]
      outer face in a local subdivision situation
  Remarks: 
    In order for FindOrAllocateVertex() to find a vertex, that vertex must 
    have been created  by an earlier call to FindOrAllocateVertex().
    Typically, AllocateVertex(edge0) is used for the center face and
    and FindOrAllocateVertex(edge0) is used for ring faces.
  */
  ON_SubDVertex* FindOrAllocateVertex(
    const ON_SubDFace* face0
    );


  /*
  Description:
    Allocate a vertex located at the sector_face0 subdivision point. 
    The vertex will have an edge and face capacity of 3.
  Parameters:
    sector_face0 - [in]
      A face in a vertex sector.
  */
  ON_SubDVertex* AllocateSectorFaceVertex(
    const ON_SubDFace* sector_face0
    );


  /*
  Parameters:
    v0 - [in]
    v0_sector_coefficient - [in]
      If v0 null or ON_SubDVertexTag::Smooth == v0->m_vertex_tag, and v1 is null or tagged,
      then m_sector_coefficient[0] is set to v0_sector_coefficient.
      In all other cases the value of v0_sector_coefficient is ignored and m_sector_coefficient[0]
      is set to ON_SubDSectorType::IgnoredSectorCoefficient.
    v1 - [in]
    v1_sector_coefficient - [in]
      If v1 null or ON_SubDVertexTag::Smooth == v1->m_vertex_tag, and v0 is null or tagged,
      then m_sector_coefficient[1] is set to v1_sector_coefficient.
      In all other cases the value of v1_sector_coefficient is ignored and m_sector_coefficient[1]
      is set to ON_SubDSectorType::IgnoredSectorCoefficient.
  Returns:
    An edge.
    The vertex parameter information is used to set the ON_SubDEdge.m_vertex[] 
    and ON_SubDEdge.m_sector_coefficient[] values.
    If v0 and v1 are not null and both are tagged, then ON_SubDEdge.m_edge_tag is 
    set to ON_SubDEdgeTag::Crease.  
    In all other cases, ON_SubDEdge.m_edge_tag is set to ON_SubDEdgeTag::Smooth.
    If v0 or v1 is not null, then ON_SubDEdge.m_level is set to the
    maximum of v0->m_level or v1->m_level.
  */
  const ON_SubDEdgePtr AllocateEdge(
    ON_SubDVertex* v0,
    double v0_sector_coefficient,
    ON_SubDVertex* v1,
    double v1_sector_coefficient
    );

  /*
  Description:
    NOTE WELL: 
    In order for FindOrAllocateEdge() to find an edge, that edge must have been created 
    by an earlier call to FindOrAllocateEdge().
  */
  const ON_SubDEdgePtr FindOrAllocateEdge(
    ON_SubDVertex* v0,
    double v0_sector_coefficient,
    ON_SubDVertex* v1,
    double v1_sector_coefficient
    );

  const ON_SubDEdgePtr AllocateEdge(
    bool bUseFindOrAllocatEdge,
    ON_SubDVertex* v0,
    double v0_sector_coefficient,
    ON_SubDVertex* v1,
    double v1_sector_coefficient
  );



  private:
  /*
  Returns:
    A face with all field values zero (same values as ON_SubDEdge::Face), except ON_SubDFace.m_id.
  */
  ON_SubDFace* Internal_AllocateFace(
    unsigned int zero_face_id,
    unsigned int parent_face_id
    );
  public:

  ON_SubDFace* AllocateQuad(
    unsigned int zero_face_id,
    unsigned int parent_face_id,
    const ON_SubDEdgePtr eptrs[4]
    );

  ON_SubDFace* AllocateQuad(
    unsigned int zero_face_id,
    unsigned int parent_face_id,
    ON_SubDEdgePtr e0,
    ON_SubDEdgePtr e1,
    ON_SubDEdgePtr e2,
    ON_SubDEdgePtr e3
    );

  /*
  Parameters:
    capacity - [in]
      desired array size
    bZeroMemory - [in]
      If true, all array element values are zero.
      If false, array element values are undefined.
  Returns:
    An array of capacity ON__UINT_PTR pointers.
  */
  ON__UINT_PTR* AllocatePtrArray(
    unsigned int capacity,
    bool bZeroMemory
    );

  /*
  Description:
    Return the most recent array obtained from AllocatePtrArray().
    so it can be reused.  
  Returns:
    True: 
      Success.
    False: 
      Failure. The array was not the most recent array obtained
      from AllocatePtrArray().
  */
  bool ReturnPtrArray(
    void* p,
    unsigned int capacity
    );

private:
  ON_SubDVertex* m_v = nullptr;
  unsigned int m_v_capacity = 0;
  unsigned int m_v_index = 0;

  ON_SubDEdge* m_e = nullptr;
  unsigned int m_e_capacity = 0;
  unsigned int m_e_index = 0;

  ON_SubDFace* m_f = nullptr;
  unsigned int m_f_capacity = 0;
  unsigned int m_f_index = 0;

  ON__UINT_PTR* m_p = nullptr;
  unsigned int m_p_capacity = 0;
  unsigned int m_p_index = 0;

private:
  // Used to find level 1 subdivision vertex from level 0 component
  class ON_SubD_FixedSizeHeap_ComponentPairHashElement** m_hash_table = nullptr;
  class ON_SubD_FixedSizeHeap_ComponentPairHashElement* m_hash_elements = nullptr;
  unsigned int m_h_capacity = 0; // m_hash_table[] capacity.
  unsigned int m_h_count = 0; // 0xFFFFFFFFU means hash is disabled
  enum : unsigned int
  {
    DisabledHashCount = 0xFFFFFFFFU
  };

  bool Internal_HashEnabled() const;
  unsigned int Internal_Hash(ON_SubDComponentPtr component0);
  class ON_SubDVertex* Internal_HashFindVertex1(unsigned int hash, ON_SubDComponentPtr component0);
  void Internal_HashAddPair(unsigned int hash, ON_SubDComponentPtr component0, class ON_SubDVertex* vertex1);

private:
  // copies not supported
  ON_SubD_FixedSizeHeap(const ON_SubD_FixedSizeHeap&) = delete;
  ON_SubD_FixedSizeHeap& operator=(const ON_SubD_FixedSizeHeap&) = delete;
};

class ON_CLASS ON_SubDEdgeChain
{
public:
  ON_SubDEdgeChain() = default;
  ~ON_SubDEdgeChain() = default;
  ON_SubDEdgeChain(const ON_SubDEdgeChain&) = default;
  ON_SubDEdgeChain& operator=(const ON_SubDEdgeChain&) = default;

public:
  static const ON_SubDEdgeChain Empty;

public:

  /////////////////////////////////////////////////////////
  //
  // Edge chain tools
  //

  /*
  Description:
    Unconditionally sort edges into chains.

  Parameters:
    unsorted_edges - [in]
      If unsorted_edges[] contains three or more edges that share a common vertex,
      no edge chain will pass through that vertex.
      To sort an array in place, pass the same array as both parameters.

    sorted_edges - [out]
      The sorted_edges[] has the edges grouped into edge chains.
      A value of ON_SubDEdgePtr::Null is at the end of every chain
      including the last chain.

      In an edge chain subsequent edges share a common vertex; i.e.
      sorted_edges[i].RelativeVertex(1) == sorted_edges[i+1].RelativeVertex(0).
  Returns:
    Number of chains in edge_chains[].
  Remarks:
    This version of SortEdgesIntoEdgeChains() uses MarkBits() on the edges
    and vertices in unsorted_edges[]. The output values of MarkBits()
    on these components are zero.
    Multiple threads may not simultaneously use any SubD tools on that rely
    on markbits on the same ON_SubD.
  */
  static unsigned int SortEdgesIntoEdgeChains(
    const ON_SimpleArray< ON_SubDEdgePtr >& unsorted_edges,
    ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
  );

  static unsigned int SortEdgesIntoEdgeChains(
    const ON_SubDEdgePtr* unsorted_edges,
    unsigned unsorted_edge_count,
    ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
  );

  /*
  Description:
    Unconditionally sort edges into chains.

  Parameters:
    unsorted_edges - [in]
      If unsorted_edges[] contains three or more edges that share a common vertex,
      no edge chain will pass through that vertex.

    sorted_edges - [out]
      The sorted_edges[] has the edges grouped into edge chains.
      A value of ON_SubDEdgePtr::Null is at the end of every chain
      including the last chain.

      In an edge chain subsequent edges share a common vertex; i.e.
      sorted_edges[i].RelativeVertex(1) == sorted_edges[i+1].RelativeVertex(0).
  Returns:
    Number of chains in edge_chains[].
  Remarks:
    This version of SortEdgesIntoEdgeChains() uses MarkBits() on the edges
    and vertices in unsorted_edges[]. The output values of MarkBits()
    on these components are zero.
    Multiple threads may not simultaneously use any SubD tools on that rely
    on markbits on the same ON_SubD.
  */
  static unsigned int SortEdgesIntoEdgeChains(
    const ON_SimpleArray< const ON_SubDEdge* >& unsorted_edges,
    ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
  );

  static unsigned int SortEdgesIntoEdgeChains(
    const ON_SubDEdge* const * unsorted_edges,
    unsigned unsorted_edge_count,
    ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
  );


  /*
  Description:
    Unconditionally sort edges into chains.

  Parameters:
    unsorted_edges - [in]
      If unsorted_edges[] contains three or more edges that share a common vertex,
      no edge chain will pass through that vertex.

    sorted_edges - [out]
      The sorted_edges[] has the edges grouped into edge chains.
      A value of ON_SubDEdgePtr::Null is at the end of every chain
      including the last chain.

      In an edge chain subsequent edges share a common vertex; i.e.
      sorted_edges[i].RelativeVertex(1) == sorted_edges[i+1].RelativeVertex(0).
  Returns:
    Number of chains in edge_chains[].
  Remarks:
    This version of SortEdgesIntoEdgeChains() uses MarkBits() on the edges
    and vertices in unsorted_edges[]. The output value of MarkBits()
    on these components is zero.
    Multiple threads may not simultaneously use any SubD tools on that rely
    on markbits on the same ON_SubD.
  */
  static unsigned int SortEdgesIntoEdgeChains(
    const ON_SimpleArray< ON_SubDComponentPtr >& unsorted_edges,
    ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
  );

  /*
  Description:
    Unconditionally sort edges into chains.

  Parameters:
    unsorted_edges - [in]
      If unsorted_edges[] contains three or more edges that share a common vertex,
      no edge chain will pass through that vertex.

    sorted_edges - [out]
      The sorted_edges[] has the edges grouped into edge chains.
      A value of ON_SubDEdgePtr::Null is at the end of every chain
      including the last chain.

      In an edge chain subsequent edges share a common vertex; i.e.
      sorted_edges[i].RelativeVertex(1) == sorted_edges[i+1].RelativeVertex(0).
  Returns:
    Number of chains in edge_chains[].
  Remarks:
    This version of SortEdgesIntoEdgeChains() uses MarkBits() on the edges
    and vertices in unsorted_edges[]. The output value of MarkBits()
    on these components is zero.
    Multiple threads may not simultaneously use any SubD tools on that rely
    on markbits on the same ON_SubD.
  */
  static unsigned int SortEdgesIntoEdgeChains(
    const ON_SubD& subd,
    const ON_SimpleArray< ON_COMPONENT_INDEX >& unsorted_edges,
    ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
  );

  /// <summary>
  /// Refine unconditional edge chains returned by the 
  /// ON_SubDEdgeChain::SortEdgesIntoEdgeChains() functions.
  /// ON_SubDEdgeChain::SortEdgesIntoEdgeChains() unconditionally sorts 
  /// the input edges into edge chains;
  /// ending at where vertices where there the number of
  /// candidates for the next edge is zero or two or more.
  /// 
  /// In many contexts, it is often necessary to further refine
  /// the unconditionally sorted edge chains.
  /// RefineEdgeChains()  refines the unconditional edge chains
  /// into chains that have homogeneous edge tags and continuous sharpness. 
  /// When bOrdinarySmoothChains is true, 
  /// the interior vertices of smooth chains will always
  /// be smooth vertices with 4 edges and faces.
  /// When bOrdinaryCreaseChains is true, 
  /// the interior vertices of crease chains will
  /// alwasys be crease vertices.
  /// 
  /// To clean edge chains in place, pass the same array as both edge chains parameters.
  /// </summary>
  /// <param name="unconditional_edge_chains">
  /// ON_SubDEdgePtr::Null elements separate the edge chains.
  /// Typically this arrary is the output from a call to
  /// ON_SubDEdgeChain::SortEdgesIntoEdgeChains().
  /// </param>
  /// <param name="bOrdinarySmoothChains"></param>
  /// <param name="bOrdinaryCreaseChains"></param>
  /// <param name="refined_edge_chains">
  /// The refined edge chains are appended to refined_edge_chains[]. 
  /// ON_SubDEdgePtr::Null elements separate the edge chains and refined_edge_chains[]
  /// ends with a ON_SubDEdgePtr::Null.
  /// </param>
  /// <returns>Number of refined edge chains appended to refined_edge_chains[].</returns>
  static unsigned RefineEdgeChains(
    const ON_SimpleArray<ON_SubDEdgePtr>& unconditional_edge_chains,
    bool bOrdinarySmoothChains,
    bool bOrdinaryCreaseChains,
    ON_SimpleArray<ON_SubDEdgePtr>& refined_edge_chains
  );


  /// <summary>
  /// Refine unconditional edge chains returned by the 
  /// ON_SubDEdgeChain::SortEdgesIntoEdgeChains() functions.
  /// ON_SubDEdgeChain::SortEdgesIntoEdgeChains() unconditionally sorts 
  /// the input edges into edge chains
  /// ending at where vertices where there the number of
  /// candidates for the next edge is zero or two or more.
  /// In particular, the unconditionally sorted chains may contain
  /// mixed edge tags and have extraordinary vertices as interior vertices.
  /// 
  /// In many contexts, it is often necessary to further refine
  /// the unconditionally sorted edge chains.
  /// The callback function is used to determine where the unconditional chain is refined.
  /// 
  /// To refine edge chains in place, pass the same array as both edge chains parameters.
  /// </summary>
  /// <param name="unconditional_edge_chains"></param>
  /// <param name="callback_context"></param>
  /// <param name="continue_chain_callback_function">
  /// The callback function 
  /// continue_chain_callback_function(callback_context,left_etpr,right_etpr) 
  /// is called with pairs of unconditionally chained edges.
  /// If the callback function return false, the unconditional chain is broken between 
  /// the edges.
  /// If continue_chain_callback_function is nullptr, 
  /// then ON_SubDEdgeChain::ContinueChainDefaultCallback() 
  /// is used and callback_context is passed as the continue_condition parameter. 
  /// <param name="refined_edge_chains">
  /// The refined edge chains are appended to refined_edge_chains[]. 
  /// ON_SubDEdgePtr::Null elements separate the edge chains and refined_edge_chains[]
  /// ends with a ON_SubDEdgePtr::Null.
  /// </param>
  /// <returns>Number of refined edge chains appended to refined_edge_chains[].</returns>
  static unsigned RefineEdgeChains(
    const ON_SimpleArray<ON_SubDEdgePtr>& unconditional_edge_chains,
    ON__UINT_PTR callback_context,
    bool (*continue_chain_callback_function)(ON__UINT_PTR,ON_SubDEdgePtr, ON_SubDEdgePtr),
    ON_SimpleArray<ON_SubDEdgePtr>& refined_edge_chains
  );

  /// <summary>
  /// Merge crossing edge chains returned by the 
  /// ON_SubDEdgeChain::SortEdgesIntoEdgeChains() 
  /// or ON_SubDEdgeChain::RefineEdgeChains() functions.
  /// ON_SubDEdgeChain::SortEdgesIntoEdgeChains() unconditionally sorts 
  /// breaks edge chains at vertices where 3 or more edges meet.
  /// 
  /// In some contexts, it is often desirable to have edge chains
  /// cross each other at 4 valent vertices.
  /// ON_SubDEdgeChain::MergeCrossingEdgeChains() search for 4 valent vertices
  /// where 4 input chains terminate and uses the call back function
  /// to determine if the chains opposite each other should be merged inot a 
  /// single chain.
  /// 
  /// To merge edge chains in place, pass the same array as both edge chains parameters.
  /// </summary>
  /// <param name="edge_chains"></param>
  /// <param name="callback_context"></param>
  /// <param name="continue_chain_callback_function">
  /// The callback function 
  /// continue_chain_callback_function(callback_context,left_etpr,right_etpr) 
  /// is called with pairs of crossing edges at the ends of input chains to see if 
  /// they should be merged into the same chain.
  /// If the callback function returns true, input chains are merged.
  /// Often times, ON_SubDEdgeChain::ContinueChainDefaultCallback can be used as the callback function.
  /// If continue_chain_callback_function is nullptr, 
  /// then ON_SubDEdgeChain::ContinueChainDefaultCallback() 
  /// is used and callback_context is passed as the continue_condition parameter. 
  /// <param name="merged_edge_chains">
  /// The merged edge chains are appended to merged_edge_chains[]. 
  /// ON_SubDEdgePtr::Null elements separate the edge chains and merged_edge_chains[]
  /// ends with a ON_SubDEdgePtr::Null.
  /// </param>
  /// <returns>Number of edge chains appended to merged_edge_chains[].</returns>
  static unsigned MergeCrossingEdgeChains(
    const ON_SimpleArray<ON_SubDEdgePtr>& edge_chains,
    ON__UINT_PTR callback_context,
    bool (*continue_chain_callback_function)(ON__UINT_PTR, ON_SubDEdgePtr, ON_SubDEdgePtr),
    ON_SimpleArray<ON_SubDEdgePtr>& merged_edge_chains
  );


  /// <summary>
  /// ON_SubDEdgeChain::ContinueChainDefaultCallback() can be used as a callback function
  /// for ON_SubDEdgeChain::RefineEdgeChains() and ON_SubDEdgeChain::MergeCrossingEdgeChains().
  /// 
  /// Edge chain topology check
  /// This check is alsways performed.
  /// If all edge and vertex pointers are not nullptr,
  /// and left_eptr.RelativeVertex(1) == right_eptr.RelativeVertex(0),
  /// and left_eptr.RelativeVertex(0), left_eptr.RelativeVertex(1, right_eptr.RelativeVertex(1) are distinct,
  /// then the edge chain topology check passes.
  /// If the chain topology check fails, then no further checks are performed.
  /// 
  /// If the valid topology check passes, the continue_condition is treated as a bitfield.
  /// Set bits cause additional checks to be performed.
  /// 
  /// bit 1: Same face count check:
  /// Passes when both edges have the same number of faces.
  /// 
  /// bit 2: Same EdgeIsSmooth() check:
  /// Passes when left_ptr.EdgeIsSmooth() == right_eptr.EdgeIsSmooth().
  /// 
  /// bit 4: Same EdgeIsSharp() check:
  /// Passes when left_ptr.EdgeIsSharp() == right_eptr.EdgeIsSharp().
  /// 
  /// bit 8: EqualEndSharpness() check:
  /// Passes when ON_SubDEdgeSharpness::EqualEndSharpness(left_eptr,right_eptr) is true.
  /// 
  /// bits 16, 32, 64, 128: Vertex tag filter check.
  /// If none of these bits are set, this check is not performed.
  /// If any of these bits are set, they specify a filter for a vertex tag check.
  /// If bit 16 is set and the common vertex tag is ON_SubDVertexTag::Smooth, the check passes.
  /// If bit 32 is set and the common vertex tag is ON_SubDVertexTag::Crease, the check passes.
  /// If bit 64 is set and the common vertex tag is ON_SubDVertexTag::Dart, the check passes.
  /// If bit 128 is set and the common vertex tag is ON_SubDVertexTag::Corner, the check passes.
  /// Otherwise the vertex tag filter check fails.
  /// 
  /// bit 256: opposite edge check
  /// If the common vertex has 4 faces and 4 edges and left_ept and right_eptr are opposite edges,
  /// the opposited edge check passes.
  /// 
  /// If the chain topology check passes and all tests specified by set bits pass, then true is returned.
  /// 
  /// 
  /// Make no modifications including Mark() and MarkBits() modifications in the callback.
  /// </summary>
  /// <param name="continue_condition"></param>
  /// <param name="left_eptr"></param>
  /// <param name="right_eptr"></param>
  /// <returns>
  /// If the chain topology check passes and all tests specified by set bits pass, then true is returned.
  /// Otherwise false is returned.
  /// </returns>
  static bool ContinueChainDefaultCallback(
    ON__UINT_PTR continue_condition,
    ON_SubDEdgePtr left_eptr,
    ON_SubDEdgePtr right_eptr
  );

  /*
  Description:
    Determine if the array of ON_SubDEdgePtrs in edges[] can be sorted
    into a single edge chain.
  Parameters:
    edges - [in]
      Set of edges to test.
    bIsClosed - [out]
      If true is returned and edges[] sorts into a closed edge chain,
      then bIsClosed is true. Otherwise bIsClosed is false.
    bIsSorted - [out]
      If true is returned and edges[] is currently sorted into an edge chain,
      then bIsSorted is true. Otherwise bIsSorted is false.
  Returns:
    If the array of edges[] can be sorted into a single edge chain
    with no self intersections, then true is returned. Otherwise false
    is returned.
  Remarks:
    This test usesthe MarkBits() values on the edges and vertices and
    restores the values to the input state.
    Multiple threads may not simultaneously use any SubD tools on that rely
    on markbits on the same ON_SubD.
  */
  static bool IsSingleEdgeChain(
    const ON_SimpleArray<ON_SubDEdgePtr>& edges,
    bool& bIsClosed,
    bool& bIsSorted
  );

  /*
  Description:
    Determine if the array of ON_SubDEdgePtrs in edges[] can be sorted
    into a single edge chain.
  Parameters:
    edges - [in]
      Set of edges to test.
  Returns:
    If the array of edges[] can be sorted into a single edge chain
    with no self intersections, then true is returned. Otherwise false
    is returned.
  Remarks:
    This test usesthe MarkBits() values on the edges and vertices and
    restores the values to the input state.
    Multiple threads may not simultaneously use any SubD tools on that rely
    on markbits on the same ON_SubD.
  */
  static bool IsSingleEdgeChain(
    const ON_SimpleArray<ON_SubDEdgePtr>& edges
  );


  /// <summary>
  /// Returns true if edges[] has 3 or more edges, the edges form a single chain,
  /// and the chain begins and ends at the same vertex.
  /// </summary>
  /// <param name="edges"></param>
  /// <returns>True if edges[] forms a closed edge chain.</returns>
  static bool IsClosed(
    const ON_SimpleArray<ON_SubDEdgePtr>& edges
  );

  /// <summary>
  /// Returns true if edges[] has 3 or more edges, the edges form a single chain,
  /// and the chain begins and ends at the same vertex.
  /// </summary>
  /// <param name="edge_count">Number of elements in the edges[] array.</param>
  /// <param name="edges"></param>
  /// <returns>True if edges[] forms a closed edge chain.</returns>
  static bool IsClosed(
    size_t edge_count,
    const ON_SubDEdgePtr* edges
  );


  /*
  Description:
    Sort edges into a chains

  Parameters:
    unsorted_edges - [in]
      To sort an array in place, pass the same array as both parameters.
      If unsorted_edges[] contains three or more edges that share a common vertex,
      then all of the edges that share that vertex are ignored.
      The edges can be from one or more SubDs.

    unsigned int minimum_chain_length - [in]
      minimum number of edges to consider for a chain.

    edge_chains - [out]
      The edge_chains[] has the edges grouped into edge chains.

      In an edge chain subsequent edges share a common vertex; i.e.
      edge_chains[i].RelativeVertex(1) == edge_chains[i+1].RelativeVertex(0).

      When edge_chains[i].RelativeVertex(1) != edge_chains[i+1].RelativeVertex(0),
      a chain ends at edge_chains[i] and another begins at edge_chains[i+1].

      Reasonable effort is made to keep the first edge in every chain with the
      same orientation as the input edge from edge_chains[]. However, this is not
      possible in every case, for example if the input is two edges sharing the
      same starting vertex.

      NB: Reasonable effort is made to keep the corner vertices on the exterior
      of the chains, however some chains will have corners in their interior,
      especially closed chains.

    bIgnoreCorners - [in]
      If true the chains are not split at corner vertices

  Returns:
    Number of chains in edge_chains[].

  Remarks:
    When the orientation of the input edges is not intentionally set,
    the versions of SortEdgesIntoEdgeChains() above without a minimum_chain_length
    variable are a better choice.
  */
  static unsigned int SortEdgesIntoEdgeChains(
    const ON_SimpleArray< ON_SubDEdgePtr >& unsorted_edges,
    unsigned int minimum_chain_length,
    ON_SimpleArray< ON_SubDEdgePtr >& edge_chains,
    const bool bIgnoreCorners
  );

  // 7.x SDK prservation - calls above with bIgnoreCorners = false
  static unsigned int SortEdgesIntoEdgeChains(
    const ON_SimpleArray< ON_SubDEdgePtr >& unsorted_edges,
    unsigned int minimum_chain_length,
    ON_SimpleArray< ON_SubDEdgePtr >& edge_chains
  );

  /*
  Description:
    Sort edges into a chains

  Parameters:
    unsorted_edges - [in]
      To sort an array in place, pass the same array as both parameters.
      If unsorted_edges[] contains three or more edges that share a common vertex,
      then all of the edges that share that vertex are ignored.
      The edges can be from one or more SubDs.

    unsigned int minimum_chain_length - [in]
      minimum number of edges to consider for a chain.

    edge_chains - [out]
      The edge_chains[] has the edges grouped into edge chains.

      In an edge chain subsequent edges share a common vertex; i.e.
      edge_chains[i].RelativeVertex(1) == edge_chains[i+1].RelativeVertex(0).

      When edge_chains[i].RelativeVertex(1) != edge_chains[i+1].RelativeVertex(0),
      a chain ends at edge_chains[i] and another begins at edge_chains[i+1].

      The first edge in every chain has the same orientation as the input edge
      from edge_chains[].

    bIgnoreCorners - [in]
      If true the chains are not split at corner vertices

  Returns:
    Number of chains in edge_chains[].

  Remarks:
    When the orientation of the input edges is not intentionally set,
    the versions of SortEdgesIntoEdgeChains() above without a minimum_chain_length
    variable are a better choice.
  */
  static unsigned int SortEdgesIntoEdgeChains(
    const ON_SimpleArray< const ON_SubDEdge* >& unsorted_edges,
    unsigned int minimum_chain_length,
    ON_SimpleArray< ON_SubDEdgePtr >& edge_chains,
    const bool bIgnoreCorners
  );

  // 7.x SDK prservation - calls above with bIgnoreCorners = false
  static unsigned int SortEdgesIntoEdgeChains(
    const ON_SimpleArray< const ON_SubDEdge* >& unsorted_edges,
    unsigned int minimum_chain_length,
    ON_SimpleArray< ON_SubDEdgePtr >& edge_chains
  );

  /*
  Description:
    Sort edges into a chains

  Parameters:
    unsorted_edges - [in]
      To sort an array in place, pass the same array as both parameters.
      If unsorted_edges[] contains three or more edges that share a common vertex,
      then all of the edges that share that vertex are ignored.
      The edges can be from one or more SubDs.

    unsigned int minimum_chain_length - [in]
      minimum number of edges to consider for a chain.

    edge_chains - [out]
      The edge_chains[] has the edges grouped into edge chains.

      In an edge chain subsequent edges share a common vertex; i.e.
      edge_chains[i].RelativeVertex(1) == edge_chains[i+1].RelativeVertex(0).

      When edge_chains[i].RelativeVertex(1) != edge_chains[i+1].RelativeVertex(0),
      a chain ends at edge_chains[i] and another begins at edge_chains[i+1].

      The first edge in every chain has the same orientation as the input edge
      from edge_chains[].

  Returns:
    Number of chains in edge_chains[].

  Remarks:
    When the orientation of the input edges is not intentionally set,
    the versions of SortEdgesIntoEdgeChains() above without a minimum_chain_length
    variable are a better choice.
  */
  static unsigned int SortEdgesIntoEdgeChains(
    const ON_SimpleArray< ON_SubDComponentPtr >& unsorted_edges,
    unsigned int minimum_chain_length,
    ON_SimpleArray< ON_SubDEdgePtr >& sorted_edges
  );

  /*
  Description:
    Sort edges into a chains

  Parameters:
    unsorted_edges - [in]
      To sort an array in place, pass the same array as both parameters.
      If unsorted_edges[] contains three or more edges that share a common vertex,
      then all of the edges that share that vertex are ignored.
      The edges can be from one or more SubDs.

    unsigned int minimum_chain_length - [in]
      minimum number of edges to consider for a chain.

    edge_chains - [out]
      The edge_chains[] has the edges grouped into edge chains.

      In an edge chain subsequent edges share a common vertex; i.e.
      edge_chains[i].RelativeVertex(1) == edge_chains[i+1].RelativeVertex(0).

      When edge_chains[i].RelativeVertex(1) != edge_chains[i+1].RelativeVertex(0),
      a chain ends at edge_chains[i] and another begins at edge_chains[i+1].

      The first edge in every chain has the same orientation as the input edge
      from edge_chains[].

  Returns:
    Number of chains in edge_chains[].

  Remarks:
    When the orientation of the input edges is not intentionally set,
    the versions of SortEdgesIntoEdgeChains() above without a minimum_chain_length
    variable are a better choice.
  */
  static unsigned int SortEdgesIntoEdgeChains(
    const ON_SubD& subd,
    const ON_SimpleArray< ON_COMPONENT_INDEX >& unsorted_edges,
    unsigned int minimum_chain_length,
    ON_SimpleArray< ON_SubDEdgePtr >& edge_chains
  );

  /*
  Description:
    Orient edges[] into edge chains preserving the order of edges[].
  Returns:
    Number of chains in edge_chains[].
  */
  static unsigned int OrientEdgesIntoEdgeChains(
    const ON_SubD& subd,
    const ON_SimpleArray< ON_COMPONENT_INDEX >& edges,
    ON_SimpleArray< ON_SubDEdgePtr >& edge_chains
  );

  /*
  Description:
    Orient edges[] into edge chains preserving the order of edges[].
  Returns:
    Number of chains in edge_chains[].
  */
  static unsigned int OrientEdgesIntoEdgeChains(
    const ON_SimpleArray< const ON_SubDEdge* >& edges,
    ON_SimpleArray< ON_SubDEdgePtr >& edge_chains
  );

  /*
  Description:
    Orient edges[] into edge chains preserving the order of edges[].
  Returns:
    Number of chains in edge_chains[].
  */
  static unsigned int OrientEdgesIntoEdgeChains(
    const ON_SimpleArray< ON_SubDComponentPtr >& edges,
    ON_SimpleArray< ON_SubDEdgePtr >& edge_chains
  );

  /*
  Returns:
    A SHA1 hash of the edge and vertex ids. 
    Useful for determining when two edge chains from different
    subds (one generally a modified copy) involve the same
    edges and vertices.
  */
  const ON_SHA1_Hash Hash() const;


  /////////////////////////////////////////////////////////
  //
  // Edge chain tools
  //

  /*
  Description:
    Get the neighboring link in an edge chain.
  Parameters:
    starting_edge - [in]
    search_direction - [in]
      ON_ChainDirection::Previous or ON_ChainDirection::Next.
      The search direction is relative to this->EdgeDirection().
    chain_type - [in]
      Determines what edge/vertex tag conditions must be satisfied by the neighbor.
  Returns:
    The next or previous edge in the chain if it exists.
    Otherwise, nullptr is returned.
  Remarks:
    When multiple edges are candidates, there is a bias to preserve smooth/crease and a bias to
    preserve face count. If the biases don't reduce the list of candidates to one or bStopAtBreak is true
    and a creaase/smooth break is encountered, then ON_SubDEdgePtr::Null is returned.
  */
  static const ON_SubDEdgePtr EdgeChainNeighbor(
    ON_SubDEdgePtr starting_edge,
    ON_ChainDirection search_direction,
    ON_SubD::ChainType chain_type
  );

  /*
  Description:
    Get the neighboring link in an edge chain.
  Parameters:
    starting_edge - [in]
    search_direction - [in]
      ON_ChainDirection::Previous or ON_ChainDirection::Next.
      The search direction is relative to this->EdgeDirection().
    chain_type - [in]
      Determines what edge/vertex tag conditions must be satisfied by the neighbor.
    bEnableStatusCheck - [in]
    status_pass - [in]
    status_fail - [in]
      If bEnableStatusFilter is false, then no status checks are performed.
      If bEnableStatusFilter is true, ON_ComponentStatus::StatusCheck(candidate_edge->m_status,status_pass,status_fail)
      must be true for candidate_edge to be returned.
  Returns:
    The next or previous edge in the chain if it exists.
    Otherwise, nullptr is returned.
  Remarks:
    When multiple edges are candidates, there is a bias to preserve smooth/crease and a bias to
    preserve face count. If the biases don't reduce the list of candidates to one or bStopAtBreak is true
    and a creaase/smooth break is encountered, then ON_SubDEdgePtr::Null is returned.
  */
  static const ON_SubDEdgePtr EdgeChainNeighbor(
    ON_SubDEdgePtr starting_edge,
    ON_ChainDirection search_direction,
    ON_SubD::ChainType chain_type,
    bool bEnableStatusCheck,
    ON_ComponentStatus status_pass,
    ON_ComponentStatus status_fail
  );

  /*
  Description:
    Reverse the orientation of the elements and the order
    of the elements in the edge_chain[] array.
  Parameters:
    edge_chain - [in/out]
  */
  static void ReverseEdgeChain(
    ON_SimpleArray< ON_SubDEdgePtr >& edge_chain
  );

  /*
  Description:
    Reverse the orientation of the elements and the order
    of the elements in the edge_chain[] array.
  Parameters:
    edge_count - [in]
      Number of elements in edge_chain[]
    edge_chain - [in/out]
  */
  static void ReverseEdgeChain(
    ON_SubDEdgePtr* edge_chain,
    size_t edge_count
    );
  
  /*
  Description:
    Checks that all edge and vertex pointers are not nullptr 
    and that adjacent edges in the list share the same vertex.
  Parameters:
    edge_chain - [in]
      Edge chain to test
    bCheckForDuplicateEdges - [in]
      If bCheckForDuplicateEdges true, then false is returned if
      there are duplicate edges or duplicate interior vertices.
  Returns:
    True if edge_chain[] is valid.
  */
  static bool IsValidEdgeChain(
    const ON_SimpleArray< ON_SubDEdgePtr >& edge_chain,
    bool bCheckForDuplicateEdges
  );

  /*
  Description:
    Checks that all edge and vertex pointers are not nullptr 
    and that adjacent edges in the list share the same vertex.
  Parameters:
    edge_count - [in]
      Number of elements in edge_chain[] to test.
    edge_chain - [in]
      Edge chain to test
    bCheckForDuplicateEdges - [in]
      If bCheckForDuplicateEdges true, then false is returned if
      there are duplicate edges or duplicate interior vertices.
  Returns:
    True if edge_chain[] is valid.
  */
  static bool IsValidEdgeChain(
    const ON_SubDEdgePtr* edge_chain,
    size_t edge_count,
    bool bCheckForDuplicateEdges
  );


  /*
  Description:
    Get the edges and faces on a specified side of the edge chain.
  Parameters:
    relative_side - [in]
      0: Get edges and faces on the ON_SubDEdgePtr::RelativeFace(0) side (left).
      1: Get edges and faces on the ON_SubDEdgePtr::RelativeFace(1) side (right).
    
    side_components - [out]
      side_components[] is a sequence of made of vertices, edges, and faces that
      record the edges and faces that are on the specified side of the edge chain.
      
      When a vertex is in side_components[], ON_SubDComponentPtr.Vertex() is not nullptr
      and the vertex is between two conscutive edges in the edge chain.
      
      When an edge is in side_components[], ON_SubDComponentPtr.EdgePtr() is not nullptr,
      the edge is on the specified side of the edge chain (not in the edge chain),
      and ON_SubDComponentPtr.EdgePtr().RelativeVertex(0) is a vertex on the edge chain.
      
      When a face is in side_components[], ON_SubDComponentPtr.Face() is not nullptr,
      then at least one vertex of f is part of the edge chain and f is on the specified
      side of the edge chain.

      If a vertex v is in side_components[], then it is preceded and followed by the same
      face (...f,v,f,...), there are consecutive edges in the edge chain (...e0,e1,...),
      and e0 and e1 are consecutive edges in f's boundary.

      If ...eptr0,f,eptr1,... is in side_components[], 
      v0 = eptr0.RelativeVertex(0),
      v1 = eptr0.RelativeVertex(0), 
      and v0 == v1,
      then eptr0 and eptr1 are consecutive edges in the boundary of f 
      and v0==v1 is a vertex in the edge chain.

      If ...eptr0,f,eptr1,... is in side_components[], 
      v0 = eptr0.RelativeVertex(0),
      v1 = eptr0.RelativeVertex(0), 
      and v0 != v1,
      then there is an edge c from v0 to v1 that is in the edge chain and
      eptr0,c,eptr1 are consecutive edges in the boundary of f.

      If ...eptr0,f,v,... is in side_components[] and v0 = eptr0.RelativeVertex(0),
      and then v0 != v, then there is an edge c from v0 to v that is in the edge chain,
      and eptr0,c are consecutive edges in the boundary of f.

      If ...v,f,eptr1,... is in side_components[] and v1 = eptr1.RelativeVertex(0),
      and then v != v1, then there is an edge c from v to v1 that is in the edge chain,
      and c,eptr1 consecutive edges in the boundary of f.

  Remarks:
    If the SubD is not an oriented manifold along the entire side of the chain,
    then there may be gaps in chain_side[]. When there are face fans at a chain
    vertex, there will be faces that do not have an edge on the chain.
  */
  bool GetSideComponents(
    unsigned relative_side,
    ON_SimpleArray<ON_SubDComponentPtr>& side_components
  ) const;

  /*
  See above.
  */
  static bool GetSideComponents(
    const ON_SimpleArray<ON_SubDEdgePtr>& edge_chain,
    unsigned relative_side,
    ON_SimpleArray<ON_SubDComponentPtr>& side_components
  );

public:
  /*
  Returns:
    Current EdgeChain
  */
  const ON_SimpleArray<ON_SubDEdgePtr>& EdgeChain() const;


  const ON_SubD& SubD() const;
  const ON_SubDRef SubDRef() const;

  bool InChain(
    const ON_SubDEdgePtr edge_ptr
  ) const;

  bool InChain(
    const ON_SubDEdge* edge
  ) const;

  bool InChain(
    const ON_SubDVertex* vertex
  ) const;

  /*
  Returns:
    True if the edge chain has 3 or more edges that form a closed loop.
  */
  bool IsClosedLoop() const;

  /*
  Parameters:
    bStrictlyConvex - [in]
      If true, then a colinear pair of edges is not considered convex.
  Returns:
    True if the edge chain has 3 or more edges that forma a convex loop.
  */
  bool IsConvexLoop(
    bool bStrictlyConvex
  ) const;


  /*
  Parameters:
    persistent_subd_id - [in]
      If this edge chain needs to persist in a 3dm archive, then persistent_subd_id
      should identify the subd in its current context.
      If that context is an ONX_Model, then the persistent id is the ON_ModelGeometryComponent.Id().
      If that context is a CRhinoDoc, then the persistent id is CRhinoObject.ModelObjectId().
      If the edge chain is being used in a runtime context and will not be saved in a 3dm archive
      or otherwise serialized, then persistent_subd_id can be ON_nil_uuid.

  */
  unsigned int BeginEdgeChain(
    ON_UUID persistent_subd_id,
    ON_SubDRef subd_ref,
    const ON_SubDEdge* initial_edge
  );

  /*
  Parameters:
    persistent_subd_id - [in]
      If this edge chain needs to persist in a 3dm archive, then persistent_subd_id
      should identify the subd in its current context.
      If that context is an ONX_Model, then the persistent id is the ON_ModelGeometryComponent.Id().
      If that context is a CRhinoDoc, then the persistent id is CRhinoObject.ModelObjectId().
      If the edge chain is being used in a runtime context and will not be saved in a 3dm archive
      or otherwise serialized, then persistent_subd_id can be ON_nil_uuid.

  */
  unsigned int BeginEdgeChain(
    ON_UUID persistent_subd_id,
    ON_SubDRef subd_ref,
    const ON_SimpleArray<const ON_SubDEdge* >& initial_edge_chain
  );

  /*
  Parameters:
    persistent_subd_id - [in]
      If this edge chain needs to persist in a 3dm archive, then persistent_subd_id
      should identify the subd in its current context.
      If that context is an ONX_Model, then the persistent id is the ON_ModelGeometryComponent.Id().
      If that context is a CRhinoDoc, then the persistent id is CRhinoObject.ModelObjectId().
      If the edge chain is being used in a runtime context and will not be saved in a 3dm archive
      or otherwise serialized, then persistent_subd_id can be ON_nil_uuid.

  */
  unsigned int BeginEdgeChain(
    ON_UUID persistent_subd_id,
    ON_SubDRef subd_ref,
    const ON_SubDEdge*const* initial_edge_chain,
    size_t edge_count
    );

  /*
  Parameters:
    persistent_subd_id - [in]
      If this edge chain needs to persist in a 3dm archive, then persistent_subd_id
      should identify the subd in its current context.
      If that context is an ONX_Model, then the persistent id is the ON_ModelGeometryComponent.Id().
      If that context is a CRhinoDoc, then the persistent id is CRhinoObject.ModelObjectId().
      If the edge chain is being used in a runtime context and will not be saved in a 3dm archive
      or otherwise serialized, then persistent_subd_id can be ON_nil_uuid.

  */
  unsigned int BeginEdgeChain(
    ON_UUID persistent_subd_id,
    ON_SubDRef subd_ref,
    ON_SubDEdgePtr initial_edge
  );

  /*
  Parameters:
    persistent_subd_id - [in]
      If this edge chain needs to persist in a 3dm archive, then persistent_subd_id
      should identify the subd in its current context.
      If that context is an ONX_Model, then the persistent id is the ON_ModelGeometryComponent.Id().
      If that context is a CRhinoDoc, then the persistent id is CRhinoObject.ModelObjectId().
      If the edge chain is being used in a runtime context and will not be saved in a 3dm archive
      or otherwise serialized, then persistent_subd_id can be ON_nil_uuid.

  */
  unsigned int BeginEdgeChain(
    ON_UUID persistent_subd_id,
    ON_SubDRef subd_ref,
    const ON_SimpleArray<ON_SubDEdgePtr>& initial_edge_chain
  );

  /*
  Parameters:
    persistent_subd_id - [in]
      If this edge chain needs to persist in a 3dm archive, then persistent_subd_id
      should identify the subd in its current context.
      If that context is an ONX_Model, then the persistent id is the ON_ModelGeometryComponent.Id().
      If that context is a CRhinoDoc, then the persistent id is CRhinoObject.ModelObjectId().
      If the edge chain is being used in a runtime context and will not be saved in a 3dm archive
      or otherwise serialized, then persistent_subd_id can be ON_nil_uuid.

  */
  unsigned int BeginEdgeChain(
    ON_UUID persistent_subd_id,
    ON_SubDRef subd_ref,
    const ON_SubDEdgePtr* initial_edge_chain,
    size_t edge_count
    );

  unsigned int EdgeCount() const;

  void SetStatusCheck(
    bool bEnableStatusCheck,
    ON_ComponentStatus status_check_pass,
    ON_ComponentStatus status_check_fail
  );

  bool StatusCheckEnabled() const;

  const ON_ComponentStatus StatusCheckPass() const;

  const ON_ComponentStatus StatusCheckFail() const;

  bool StatusCheck(
    const ON_SubDEdge* edge
  ) const;

  void Reverse();

  const ON_SubDEdgePtr FirstEdgePtr() const;
  const ON_SubDEdgePtr LastEdgePtr() const;
  const ON_SubDEdgePtr EdgePtr(int edge_index) const;

  const ON_3dPoint FirstControlNetPoint() const;
  const ON_3dPoint LastControlNetPoint() const;
  const ON_3dPoint ControlNetPoint(int vertex_index) const;

  const ON_SubDEdge* FirstEdge() const;
  const ON_SubDEdge* LastEdge() const;
  const ON_SubDEdge* Edge(int edge_index) const;

  const ON_SubDVertex* FirstVertex() const;
  const ON_SubDVertex* LastVertex() const;
  const ON_SubDVertex* Vertex(int vertex_index) const;

  unsigned int AddOneNeighbor(
    ON_ChainDirection direction,
    ON_SubD::ChainType chain_type
    );

  unsigned int AddAllNeighbors(
    ON_ChainDirection direction,
    ON_SubD::ChainType chain_type
    );

  unsigned int AddEdge(
    const ON_SubDEdge* edge
    );

  unsigned int RemoveEdges(
    const ON_SubDEdge* first_edge,
    const ON_SubDEdge* last_edge
  );

  void ClearEdgeChain();

  /*
  Returns:
    The persistent id of the parent subd object.
    If the context is an ONX_Model, then the persistent id is the ON_ModelGeometryComponent.Id().
    If the context is a CRhinoDoc, then the persistent id is CRhinoObject.ModelObjectId().
  */
  const ON_UUID PersistentSubDId() const;

  bool HasPersistentEdgeIds() const;

  bool HasRuntimeEdgePtrs() const;

  bool SetPersistentEdgeIdsFromRuntimeEdgePtrs() const;
    
  /*
  Description:
    In situations where this edge chain is being read from a 3dm archive,
    or a similar serialization context, this function uses the saved edge
    id information to initialize the runtime ON_SubDEdgePtr information.
  Parameters:
    persistent_subd_id - [in]
      This id is passed to insure it matches the saved persistent_subd_id. 
      The source of the id depends on the context of the model managing the subd.
      If that context is an ONX_Model, then the persistent id is the ON_ModelGeometryComponent.Id().
      If that context is a CRhinoDoc, then the persistent id is CRhinoObject.ModelObjectId().
  Returns:
    True if successful.
    False if not successful.
  */
  bool SetRuntimeEdgePtrsFromPersistentSubD(
    ON_UUID persistent_subd_id,
    ON_SubDRef persistent_subd_ref
  );

  bool Write(class ON_BinaryArchive& archive) const;
  bool Read(class ON_BinaryArchive& archive);
  void Dump(class ON_TextLog& text_log) const;

private:
  ON_SubDRef m_subd_ref;
  ON_SimpleArray<ON_SubDEdgePtr> m_edge_chain;


  // If m_persistent_subd_id, then the id identifies the parent subd in the model.
  // In an ONX_Model, this is the ON_ModelGeometryComponent.Id() value
  // of the corresponding ON_SubD in the ONX_Model.
  // In Rhino, this is the CRhinoObject.ModelObjectId() value
  // of the corresponding CRhinoSubDObject in the CRhinoDoc.
  ON_UUID m_persistent_subd_id = ON_nil_uuid;

  // If m_persistent_subd_id is set and m_persistent_edge_id[] is not empty,
  // m_persistent_edge_id[] is a list of edge ids and orientations.
  // unsigned id = m_persistent_edge_id[] & 0xFFFFFFFF.
  // reversed orientation = (0 != (m_persistent_edge_id[] & 0x8000000000000000)).
  // The persistent id information is saved in 3dm archives. When that archive is read,
  // the SetRuntimeEdgePtrsFromPersistentSubD() can be used to set the runtime edge chain values.
  // These mutable fields are set by Write and used by Read.
  mutable ON_SimpleArray<unsigned int> m_persistent_edge_id;
  mutable ON_SimpleArray<ON__UINT8> m_persistent_edge_orientation; // 0 = not reversed, 1 = reversed.

  ON_UniqueTester m_unique_tester;
  ON_ComponentStatus m_status_check_pass = ON_ComponentStatus::NoneSet;
  ON_ComponentStatus m_status_check_fail = ON_ComponentStatus::Selected;
  bool m_bEnableStatusCheck = false;
};

class ON_CLASS ON_SubDComponentFilter
{
public:
  ON_SubDComponentFilter() = default;
  ~ON_SubDComponentFilter() = default;
  ON_SubDComponentFilter(const ON_SubDComponentFilter&) = default;
  ON_SubDComponentFilter& operator=(const ON_SubDComponentFilter&) = default;

public:

  ///<summary>
  /// No filters are set and all components are accepted.
  ///</summary>
  static const ON_SubDComponentFilter Unset;

  ///<summary>
  /// Only vertices are accepted.
  ///</summary>
  static const ON_SubDComponentFilter OnlyVertices;

  ///<summary>
  /// Only edges are accepted.
  ///</summary>
  static const ON_SubDComponentFilter OnlyEdges;

  ///<summary>
  /// Only faces are accepted.
  ///</summary>
  static const ON_SubDComponentFilter OnlyFaces;

  /*
  Parameters:
    bAcceptVertices - [in]
      If true, all vertices are accepted. Otherwise, all vertices are rejected.
    bAcceptEdges - [in]
      If true, all edges are accepted. Otherwise all edges are rejected.
    bAcceptFaces - [in]
      If true, all faces are accepted. Otherwise all faces are rejected.
  */
  static const ON_SubDComponentFilter Create(
    bool bAcceptVertices,
    bool bAcceptEdges,
    bool bAcceptFaces
  );

public:
  ///<summary>
  /// Topology filters.
  ///</summary>
  enum class Topology : unsigned char
  {
    ///<summary>
    /// No topology filter.
    ///</summary>
    Unset = 0,

    ///<summary>
    /// A boundary vertex has a single sector bounded by two boundary edges.
    /// A boundary edge has a single face.
    /// A boundary face has at least one boundary edge.
    ///</summary>
    Boundary = 1,

    ///<summary>
    /// An interior vertex has the same number of edges and faces and all edges are interior.
    /// An interior edge has two faces.
    /// An interior face has all interior edges.
    ///</summary>
    Interior = 2,

    ///<summary>
    /// A nonmanifold vertex is a vertex that is neither boundary nor interior.
    /// A nonmanifold edge is an edge that is neither boundary nor interior.
    /// A nonmanifold face is a face that is neither boundary nor interior.
    ///</summary>
    Nonmanifold = 4,

    ///<summary>
    /// A component that is either boundary or interior.
    ///</summary>
    BoundaryOrInterior = 3,

    ///<summary>
    /// A component that is either boundary or nonmanifold.
    ///</summary>
    BoundaryOrNonmanifold = 5,

    ///<summary>
    /// A component that is either interior or nonmanifold
    ///</summary>
    InteriorOrNonmanifold = 6
  };

  bool AcceptComponent(
    const class ON_Geometry* geometry
  ) const;

  bool AcceptComponent(
    ON_COMPONENT_INDEX component_index,
    const class ON_Geometry* geometry
  ) const;

  bool AcceptComponent(
    const class ON_SubDComponentRef* cref
  ) const;

  /*
  Returns:
    True if the filter accepts the component. False otherwise.
  */
  bool AcceptComponent(ON_SubDComponentPtr cptr) const;

  /*
  Returns:
    True if the filter accepts the vertex. False otherwise.
  */
  bool AcceptVertex(ON_SubDVertexPtr vptr) const;

  /*
  Returns:
    True if the filter accepts the edge. False otherwise.
  */
  bool AcceptEdge(ON_SubDEdgePtr eptr) const;

  /*
  Returns:
    True if the filter accepts the face. False otherwise.
  */
  bool AcceptFace(ON_SubDFacePtr fptr) const;

  /*
  Returns:
    True if the filter accepts the vertex. False otherwise.
  */
  bool AcceptVertex(const ON_SubDVertex* v) const;

  /*
  Returns:
    True if the filter accepts the edge. False otherwise.
  */
  bool AcceptEdge(const ON_SubDEdge* e) const;
  
  /*
  Returns:
    True if the filter accepts the face. False otherwise.
  */
  bool AcceptFace(const ON_SubDFace* f) const;  

  void SetAcceptVertices(bool bAcceptVertices);

  bool AcceptVertices() const;

  void SetAcceptEdges(bool bAcceptEdges);

  bool AcceptEdges() const;

  void SetAcceptFaces(bool bAcceptFaces);

  bool AcceptFaces() const;

  void SetVertexTopologyFilter(ON_SubDComponentFilter::Topology vertex_topology_filter);

  void ClearVertexTopologyFilter();

  ON_SubDComponentFilter::Topology VertexTopologyFilter() const;

  void SetEdgeTopologyFilter(ON_SubDComponentFilter::Topology edge_topology_filter);

  ON_SubDComponentFilter::Topology EdgeTopologyFilter() const;

  void ClearEdgeTopologyFilter();

  void SetFaceTopologyFilter(ON_SubDComponentFilter::Topology face_topology_filter);

  ON_SubDComponentFilter::Topology FaceTopologyFilter() const;

  void ClearFaceTopologyFilter();

  bool AcceptVertexTag(ON_SubDVertexTag vertex_tag) const;

  void AddAcceptedVertexTag(ON_SubDVertexTag vertex_tag);

  void ClearVertexTagFilter();

  bool AcceptEdgeTag(ON_SubDEdgeTag edge_tag) const;

  void AddAcceptedEdgeTag(ON_SubDEdgeTag edge_tag);

  void ClearEdgeTagFilter();

  bool AcceptFaceEdgeCount(
    unsigned face_edge_count
  ) const;

  void SetFaceEdgeCountFilter(
    unsigned minimum_face_edge_count,
    unsigned maximum_face_edge_count
  );
  
  void ClearFaceEdgeCountFilter();

private:
  bool m_bRejectVertices = false;
  ON_SubDComponentFilter::Topology m_vertex_topology_filter = ON_SubDComponentFilter::Topology::Unset;
  ON_SubDVertexTag m_vertex_tag_filter[4] = {};

  bool m_bRejectEdges = false;
  ON_SubDComponentFilter::Topology m_edge_topology_filter = ON_SubDComponentFilter::Topology::Unset;
  ON_SubDEdgeTag m_edge_tag_filter[2] = {};

  bool m_bRejectFaces = false;
  ON_SubDComponentFilter::Topology m_face_topology_filter = ON_SubDComponentFilter::Topology::Unset;
  unsigned m_minimum_face_edge_count = 0U;
  unsigned m_maximum_face_edge_count = 0U;
};





class ON_SubDRTree : public ON_RTree
{
private:
  ON_SubDRTree(const ON_SubDRTree&) = delete;
  ON_SubDRTree& operator=(const ON_SubDRTree&) = delete;

public:
  ON_SubDRTree() = default;
  ~ON_SubDRTree() = default;

public:

  bool CreateSubDVertexRTree(
    const ON_SubD& subd,
    ON_SubDComponentLocation vertex_location
  );

  bool CreateSubDEmptyRTree(
    const ON_SubD& subd
  );

  bool AddVertex(
    const ON_SubDVertex* v,
    ON_SubDComponentLocation vertex_location
  );

  const ON_SubDVertex* FindVertexAtPoint(
    const ON_3dPoint P,
    const double distance_tolerance
  ) const;

  const ON_SubDVertex* FindMarkedVertexAtPoint(
    const ON_3dPoint P,
    const double distance_tolerance
  ) const;

  const ON_SubDVertex* FindUnmarkedVertexAtPoint(
    const ON_3dPoint P,
    const double distance_tolerance
  ) const;

  const ON_SubDVertex* FindVertex(
    const class ON_SubDRTreeVertexFinder& vertex_finder,
    const double distance_tolerance
  ) const;

  const ON_SubD& SubD() const;

  /*
  Description:
    CLears the reference to the SubD and removes all RTree nodes.
  */
  void Clear();

private:
  // Shares contents with the referenced subd.
  // Used to increment the reference count on the ON_SubDimple (not a real copy). 
  // This is used to insure the vertex pointers in the rtree nodes are valid.
  ON_SubD m_subd;
};

class ON_SubDRTreeVertexFinder
{
public:
  ON_SubDRTreeVertexFinder() = default;
  ~ON_SubDRTreeVertexFinder() = default;
  ON_SubDRTreeVertexFinder(const ON_SubDRTreeVertexFinder&) = default;
  ON_SubDRTreeVertexFinder& operator=(const ON_SubDRTreeVertexFinder&) = default;

  static const ON_SubDRTreeVertexFinder Unset;

public:
  static const ON_SubDRTreeVertexFinder Create(const ON_3dPoint P);

  /*
  Parameters:
    bMarkFilter - [in]
      Vertices with Mark = bMarkFilter are eligible to be found.
      Vertices with Mark != bMarkFilter are ignored.
  */
  static const ON_SubDRTreeVertexFinder Create(const ON_3dPoint P, bool bMarkFilter);

  enum class MarkBitsFilter : unsigned char
  {
    None = 0,
    Equal = 1,
    NotEqual = 2
  };

  static const ON_SubDRTreeVertexFinder Create(
    const ON_3dPoint P, 
    ON_SubDRTreeVertexFinder::MarkBitsFilter mark_bits_filter,
    ON__UINT8 mark_bits
  );


public:
  ON_3dPoint m_P = ON_3dPoint::NanPoint;
  double m_distance = ON_DBL_QNAN;
  const ON_SubDVertex* m_v = nullptr;

  // When m_bMarkFilterEnabled is true, then vertices with Mark() == m_bMarkFilter are eligible
  // to be found and vertices with Mark() != m_bMarkFilter are ignored.
  bool m_bMarkFilterEnabled = false;
  bool m_bMarkFilter = false;

public:
  ON_SubDRTreeVertexFinder::MarkBitsFilter m_mark_bits_filter = ON_SubDRTreeVertexFinder::MarkBitsFilter::None;
  ON__UINT8 m_mark_bits = 0;

private:
  unsigned int m_reserved2 = 0;

public:

  static bool Callback(void* a_context, ON__INT_PTR a_id);
 
};

#if defined(ON_COMPILING_OPENNURBS)
/*
The ON_SubDAsUserData class is used to attach a subd to it proxy mesh
when writing V6 files in commercial rhino.
*/
class ON_SubDMeshProxyUserData : public ON_UserData
{
public:
  /*
  Returns:
    A pointer to a mesh that now manages subd.
  */
  static ON_Mesh* MeshProxyFromSubD(
    const ON_SubD* subd
  );

  /*
  Returns:
    A pointer to a subd and deletes mesh.
  */
  static ON_SubD* SubDFromMeshProxy(
    const ON_Mesh* mesh
  );

  /*
  Returns:
    A pointer to a subd and deletes mesh.
  */
  static bool IsSubDMeshProxy(
    const ON_Mesh* mesh
  );

  static const ON_SubDDisplayParameters MeshProxyDisplayParameters();

private:
  ON_OBJECT_DECLARE(ON_SubDMeshProxyUserData);

public:
  ON_SubDMeshProxyUserData();
  ~ON_SubDMeshProxyUserData();
  ON_SubDMeshProxyUserData(const ON_SubDMeshProxyUserData&);
  ON_SubDMeshProxyUserData& operator=(const ON_SubDMeshProxyUserData&);
  
private:
  // ON_Object overrides
  bool Write(ON_BinaryArchive& archive) const override;
  bool Read(ON_BinaryArchive& archive) override;
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  bool ParentMeshValid() const;

private:
  // ON_UserData overrides
  bool GetDescription(ON_wString& description) override;
  bool WriteToArchive(
    const class ON_BinaryArchive& archive,
    const class ON_Object* parent_object
  ) const override;
 
private:
  // The subd
  mutable ON_SubD* m_subd = nullptr;

private:
  // information used to see if the parent mesh has been modified.
  mutable unsigned int m_mesh_face_count = 0;
  mutable unsigned int m_mesh_vertex_count = 0;
  mutable ON_SHA1_Hash m_mesh_face_array_sha1 = ON_SHA1_Hash::EmptyContentHash;
  mutable ON_SHA1_Hash m_mesh_vertex_array_sha1 = ON_SHA1_Hash::EmptyContentHash;

private:
  void Internal_CopyFrom(const ON_SubDMeshProxyUserData& src);
  void Internal_Destroy();
  static const bool Internal_MeshHasFaces(const ON_Mesh* mesh);
  static const ON_SHA1_Hash Internal_FaceSHA1(const ON_Mesh* mesh);
  static const ON_SHA1_Hash Internal_VertexSHA1(const ON_Mesh* mesh);
};
#endif

#endif
