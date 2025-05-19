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

#if !defined(OPENNURBS_TOPOLOGY_INC_)
#define OPENNURBS_TOPOLOGY_INC_


class ON_CLASS ON_ComponentAttributes
{
public:

  enum : unsigned int
  {
    ///<summary> 
    /// The Damaged bit is set when an vertex, edge, or face component has a critical data structure flaw.
    ///</summary>
    Damaged = 0x80000000U
  };

#pragma region RH_C_SHARED_ENUM [ON_ComponentAttributes::EdgeAttributes] [Rhino.Geometry.EdgeAttributes] [int]

  /// <summary>
  /// <para>ON_EdgeAttributeFlags are used to report attributes of single edge objects, like
  /// ON_SubDEdge and ON_BrepEdge, and aggregate edge demographics in objects with topology
  /// like ON_SubD, ON_Mesh and ON_Brep.</para>
  /// <seealso cref="ON_BrepEdge::EdgeFlags"/>
  /// <seealso cref="ON_SubDEdge::EdgeFlags"/>
  /// <seealso cref="ON_Brep::AggregateEdgeFlags"/>
  /// <seealso cref="ON_Mesh::AggregateEdgeFlags"/>
  /// <seealso cref="ON_SubD::AggregateEdgeFlags"/>
  /// </summary>
  enum EdgeAttributes : unsigned int
  {
    ///<summary> 
    /// The Open bit is set when an edge has distinct start and end vertices.
    /// Open and Closed are mutually exclusive edge attributes.
    /// Note that an open edge can have zero length when two distinct vertices
    /// have identical locations and the edge's geometry is a zero length curve.
    ///</summary>
    Open = 1,

    ///<summary> 
    /// The Closed bit is set when an edge begins and ends at the same vertex.
    /// Open and Closed are mutually exclusive edge attributes.
    /// Note that a closed edge can have zero length or nonzero length.
    ///</summary>
    Closed = 2,

    ///<summary> 
    /// The ZeroLength edge has zero length. It can be open or closed.
    /// ZeroLength and NonzeroLength are mutually exclusive edge attributes.
    ///</summary>
    ZeroLength = 4,

    ///<summary> 
    /// The NonzeroLength edge has non zero length. It can be open or closed.
    /// ZeroLength and NonzeroLength are mutually exclusive edge attributes.
    ///</summary>
    NonzeroLength = 8,

    ///<summary> 
    /// The Wire edge has no faces.
    /// Wire, Boundary, Interior, and Nonmanifold are mutually exclusive edge attributes.
    ///</summary>
    Wire = 16,

    ///<summary> 
    /// The Boundary edge has one face.
    /// Wire, Boundary, Interior, and Nonmanifold are mutually exclusive edge attributes.
    ///</summary>
    Boundary = 32,

    ///<summary> 
    /// The Interior edge has two faces.
    /// Wire, Boundary, Interior, and Nonmanifold are mutually exclusive edge attributes.
    ///</summary>
    Interior = 64,

    ///<summary> 
    /// The Nonmanifold edge has three or more faces.
    /// Wire, Boundary, Interior, and Nonmanifold are mutually exclusive edge attributes.
    ///</summary>
    Nonmanifold = 128,

    ///<summary> 
    /// The InteriorOriented edge has two faces with compatible face orientations.
    /// InteriorOriented and InteriorNotOriented are mutually exclusive interior edge attributes.
    ///</summary>
    InteriorOriented = 256,

    ///<summary> 
    /// The InteriorNotOriented edge has two faces with opposite face orientations.
    /// InteriorOriented and InteriorNotOriented are mutually exclusive interior edge attributes.
    ///</summary>
    InteriorNotOriented = 512,

    ///<summary> 
    /// The InteriorSmooth edge has two faces with a guaranteed surface tangent continuity.
    /// InteriorSmooth and InteriorCrease are mutually exclusive interior edge attributes.
    ///</summary>
    InteriorSmooth = 1024,

    ///<summary> 
    /// The InteriorCrease edge has two faces with a possible surface tangent discontinuity
    /// InteriorSmooth and InteriorCrease are mutually exclusive interior edge attributes.
    ///</summary>
    InteriorCrease = 2048,

    ///<summary> 
    /// The InteriorTwoFaced edge has two distinct faces.
    /// InteriorTwoFaced, InteriorSeam, and InteriorSlit are mutually exclusive interior edge attributes.
    ///</summary>
    InteriorTwoFaced = 4096,

    ///<summary> 
    /// The InteriorSeam edge has two faces that are identical and the edge is on the parametric boundary of the face's surface.
    /// InteriorTwoFaced, InteriorSeam, and InteriorSlit are mutually exclusive interior edge attributes.
    ///</summary>
    ///<example> 
    /// Parametric surfaces that are cylinders are an example of a situation where seam edges occur.
    ///</example>
    InteriorSeam = 8192,

    ///<summary> 
    /// The InteriorSlit edge has two faces that are identical and the edges is not a seam.
    /// InteriorTwoFaced, InteriorSeam, and InteriorSlit are mutually exclusive interior edge attributes.
    ///</summary>
    InteriorSlit = 16384,

    ///<summary> 
    /// The InteriorSharp edge has two faces with a guaranteed surface tangent continuity.
    /// An InteriorSharp edge is an InteriorSmooth edge with added SubD sharpness.
    ///</summary>
    InteriorSharp = 32768,

    ///<summary> 
    /// ON_ComponentAttributes::EdgeAttributes::Mask can be used to isolate EdgeAttributes bits
    /// from an unsigned int bit field containing other information.
    ///</summary>
    ///<example> 
    /// Determine if two unsigned ints have identical ON_ComponentAttributes::EdgeAttributes settings.
    ///<code>
    /// unsigned int combined_flags1 = ...;
    /// unsigned int combined_flags2 = ...;
    /// unsigned int edge_flags1 = (ON_ComponentAttributes::EdgeAttributes::Mask &amp; combined_flags1);
    /// unsigned int edge_flags2 = (ON_ComponentAttributes::EdgeAttributes::Mask &amp; combined_flags2);
    /// if ( edge_flags1 == edge_flags1)
    /// {
    ///    ... edges flags are identical ...
    /// }
    ///</code>
    ///</example>
    Mask = 0xFFFF
  };

#pragma endregion


  /// <summary> 
  /// Inspects edge attributes to determine if the edge is has the attributes
  /// specified by the edge_attributes_filter.
  /// </summary> 
  static bool EdgeIsEligible(
    unsigned int edge_attributes_filter,
    const class ON_SubDEdge* edge
    );

  static bool EdgeIsEligible(
    unsigned int edge_attributes_filter,
    unsigned int edge_attributes
    );

  /// <summary> 
  /// Inspects aggregate edge demographics to determine if every edge has exactly two faces and all 
  /// the faces have a compatible orientations.
  /// </summary> 
  /// <example>  
  /// This sample shows how to determine if an ON_SubD is a solid.
  /// <code> 
  /// ON_SubD subd = ...;
  /// if (ON_ComponentAttributes::IsSolid(subd.AggregateEdgeComponentAttributes())
  /// { 
  ///   // subd is a solid
  ///   ...
  /// }
  /// </code> 
  /// </example> 
  /// <param name="aggregate_edge_component_attributes">
  ///   Value made by bitwise or of ON_ComponentAttributes::EdgeAttributes values for every edge in the object.
  /// </param>
  /// <returns>True if every edge has exactly two faces.</returns>
  /// <seealso cref="ON_Brep::EdgeDemographics"/>
  /// <seealso cref="ON_SUbD::EdgeDemographics"/>
  /// <seealso cref="ON_Mesh::EdgeDemographics"/>
  /// <seealso cref="ON_ComponentAttributes::IsSolid"/>
  /// <seealso cref="ON_ComponentAttributes::IsNotSolid"/>
  /// <seealso cref="ON_ComponentAttributes::HasBoundary"/>
  /// <seealso cref="ON_ComponentAttributes::IsOriented"/>
  /// <seealso cref="ON_ComponentAttributes::IsNotOriented"/>
  /// <seealso cref="ON_ComponentAttributes::IsManifold"/>
  /// <seealso cref="ON_ComponentAttributes::IsNotManifold"/>
  static bool IsSolid(
    unsigned int aggregate_edge_component_attributes
    );

  /// <summary> 
  /// Inspects aggregate edge demographics to determine if there is a boundary edge.
  /// </summary> 
  /// <param name="aggregate_edge_component_attributes">
  ///   Value made by bitwise or of ON_ComponentAttributes::EdgeAttributes values for every edge in the object.
  /// </param>
  /// <returns>True if there is at least one edge that has exactly one face.
  /// Otherwise, false is returned.
  ///</returns>
  static bool HasBoundary(
    unsigned int aggregate_edge_component_attributes
    );

  /// <summary> 
  /// Inspects aggregate edge demographics to determine if the faces have a compatible orientations.
  /// </summary> 
  /// <param name="aggregate_edge_demographics">
  ///   Value made by bitwise or of ON_ComponentAttributes::EdgeAttributes values for every edge in the object.
  /// </param>
  /// <returns>If for every edge edge with exactly two faces, those two faces have compatible orientations, then true is returned.
  /// Otherwise, false is returned.
  ///</returns>
  static bool IsOriented(
    unsigned int aggregate_edge_component_attributes
    );

  /// <summary> 
  /// Inspects aggregate edge demographics to determine if the faces have a compatible orientations.
  /// </summary> 
  /// <param name="aggregate_edge_component_attributes">
  ///   Value made by bitwise or of ON_ComponentAttributes::EdgeAttributes values for every edge in the object.
  /// </param>
  /// <returns>If there is an edge edge with exactly two faces and those faces have incompatible orientations,
  /// then true is returned. Otherwise, false is returned.
  ///</returns>
  static bool IsNotOriented(
    unsigned int aggregate_edge_component_attributes
    );
  
  /// <summary> 
  /// Inspects aggregate edge demographics to determine if the object is a manifold, possibly with boundary.
  /// Face orientation is ignored.
  /// </summary> 
  /// <param name="aggregate_edge_component_attributes">
  ///   Value made by bitwise or of ON_ComponentAttributes::EdgeAttributes values for every edge in the object.
  /// </param>
  /// <returns>If every edge has one or two faces, then true is returned.
  /// If bAllowBoundaryEdges is true and every edge has one or two faces, then true is returned.
  /// Otherwise, false is returned.
  ///</returns>
  static bool IsManifold(
    unsigned int aggregate_edge_component_attributes
    );

  /// <summary> 
  /// Inspects aggregate edge demographics to determine if the object is a not manifold.
  /// </summary> 
  /// <param name="aggregate_edge_component_attributes">
  ///   Value made by bitwise or of ON_ComponentAttributes::EdgeAttributes values for every edge in the object.
  /// </param>
  /// <returns>True if there is at least one edge with 3 or more faces or at least one wire edge.</returns>  
  static bool IsNotManifold(
    unsigned int aggregate_edge_component_attributes
    );
};

#endif
