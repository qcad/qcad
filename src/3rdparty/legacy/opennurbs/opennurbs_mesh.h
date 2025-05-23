/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2007 Robert McNeel & Associates. All rights reserved.
// Rhinoceros is a registered trademark of Robert McNeel & Assoicates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////
*/

#if !defined(OPENNURBS_MESH_INC_)
#define OPENNURBS_MESH_INC_

class ON_Mesh;
class ON_MeshVertexRef;
class ON_MeshEdgeRef;
class ON_MeshFaceRef;
#if defined(OPENNURBS_PLUS)
class ON_MMX_POINT;
class ON_MESH_POINT;
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Class  ON_Mesh
//
class ON_CLASS ON_MeshParameters
{
  // surface meshing perameters
public:
  static
  double Tolerance( double relative_tolerance, double actual_size );

  ON_MeshParameters();
  ~ON_MeshParameters();
  // C++ default works fine // ON_MeshParameters(const ON_MeshParameters& );
  // C++ default works fine // ON_MeshParameters& operator=(const ON_MeshParameters&);
 
  bool operator!=(const ON_MeshParameters&) const;
  bool operator==(const ON_MeshParameters&) const;

  // compares with mesh's mesh parameters
  bool operator==(const ON_Mesh&) const;
  bool operator!=(const ON_Mesh&) const;
  
  void Dump( ON_TextLog& test_log ) const;

  void Default(); 

  /*
  Description:
    Tool for provding a simple slider interface.
  Parameters:
    density - [in] 0.0 <= density <= 1.0
      0 quickly creates coarse meshes.
      1 creates accurate meshes but takes lots of time.
  */
  void Set(
    double density,
    double min_edge_length = 0.0001
    );

  /*
  Description:
    Sets the meshing parameters to create "jagged and faster" 
    render meshes.
  */
  void JaggedAndFasterMeshParameters();

  /*
  Description:
    Sets the meshing parameters to create "smooth and slower" 
    render meshes.
  */
  void SmoothAndSlowerMeshParameters();

  /*
  Description:
    Sets the meshing parameters to create the default
    analysis mesh.
  */
  void DefaultAnalysisMeshParameters();

  // Compare() ignores weld and curvature settings
  // Ignores m_min_tolerance setting.
  int Compare( const ON_MeshParameters& ) const;

  bool Write( ON_BinaryArchive& ) const;
  bool Read( ON_BinaryArchive& );

  // Meshing happens in two stages.  The first stage creates a
  // rectangular grid.  The second stage refines the grid until
  // the mesh meets all meshing requirements.  The third stage
  // combines coincident vertices if the resulting mesh is a composite.
  
  bool m_bCustomSettings;    // false - if these settings were used to create
                             //         a mesh and the app settings don't match,
                             //         then remesh the object using the app
                             //         settings.
                             // true  - these settings are customized for a
                             //         particular object - ignore app mesh
                             //         settings.

  bool m_bComputeCurvature;  // false - (default) - ON_Mesh::m_K[] not computed
                             // true  - ON_Mesh::m_K[] computed

  bool m_bSimplePlanes;      // false - (default) planar surfaces are meshed
                             //          using the controls below.
                             // true   - planar surfaces are meshed using
                             //          minimal number of triangles and
                             //          aspect/edge controls are ignored.

  bool m_bRefine;            // false - skip stage 2
                             // true  - (default) do stage 2

  bool m_bJaggedSeams;       // false - (default) edges of meshes of joined 
                             //          b-rep faces match with no gaps or
                             //          "T" joints.
                             // true   - faces in b-reps are meshed independently.
                             //          This is faster but results in gaps and
                             //          "T" joints along seams between faces.

  unsigned char m_reserved1;
  unsigned char m_reserved2;
  unsigned char m_mesher;    // 0 = slow mesher, 1 = fast mesher
    
  int m_texture_range;       // 1: normalized
                             //
                             //          each face has a normalized texture range 
                             //          [0,1]x[0,1].
                             //
                             // 2: packed normalized (default)
                             //
                             //          each face in a polysurface is assigned
                             //          a texture range that is a subrectangle 
                             //          of [0,1]x[0,1].  The subrectangles are 
                             //          mutually disjoint and packed into
                             //          into [0,1]x[0,1] in a way that minimizes
                             //          distortion and maximizes the coverage
                             //          of [0,1]x[0,1].  (This texture style 
                             //          is suitable for creating texture maps 
                             //          with popular 3D painting programs.)
                           
  // These controls are used in both stages

  double m_tolerance; // maximum distance from center of edge to surface

        
  double m_relative_tolerance; // If 0 < m_relative_tolerance < 1, 
  double m_min_tolerance;      // then the maximum distance from the
                               // center of an edge to the surface will
                               // be <= T, where T is the larger of
                               // (m_min_tolerance,d*m_relative_tolerance), 
                               // where d is an esimate of the size of the
                               // object being meshed.


  double m_min_edge_length; // edges shorter than m_min_edge_length will
                            // not be split even if the do not meet other
                            // meshing requirements

  double m_max_edge_length; // edges longer than m_max_edge_length will
                            // be split even when they meet all other
                            // meshing requirements

  // These controls are used during stage 1 to generate the grid
  double m_grid_aspect_ratio;  // desired aspect ratio of quads in grid
                               // 0.0 = any aspect ratio is acceptable
                               // values >0 and < sqrt(2) are treated as sqrt(2)
  int    m_grid_min_count;     // minimum number of quads in initial grid
  int    m_grid_max_count;     // desired masimum number of quads in initial grid
  double m_grid_angle;         // (in radians) maximum angle between surface
                               // normal evaluated at adjacent vertices.
                               // 0.0 is treated as pi.
  double m_grid_amplification; // The parameters above generate a grid.
                               // If you want fewer quads, set m_grid_amplification
                               // to a value < 1.  If you want more quads,
                               // set m_grid_amplification to a value > 1.
                               // default = 1 and values <= 0 are treated as 1.

  // These controls are used during stage 2 to refine the grid
  double m_refine_angle;       // (in radians) maximum angle in radians between
                               // surface normal evaluated at adjacent vertices.

  // These controls are used during stage 3
  int     m_face_type;         // 0 = mixed triangle and quads
                               // 1 = all triangles
                               // 2 = all quads
};

class ON_CLASS ON_MeshCurvatureStats
{
public:
  ON_MeshCurvatureStats();
  ~ON_MeshCurvatureStats();
  ON_MeshCurvatureStats(const ON_MeshCurvatureStats& );
  ON_MeshCurvatureStats& operator=(const ON_MeshCurvatureStats&);

  void Destroy();
  void EmergencyDestroy();
  
  bool Set( ON::curvature_style,
            int,           // Kcount,
            const ON_SurfaceCurvature*, // K[]
            const ON_3fVector*, // N[] surface normals needed for normal sectional curvatures
            double = 0.0   // if > 0, value is used for "infinity"
            );

  bool Write( ON_BinaryArchive& ) const;
  bool Read( ON_BinaryArchive& );

  ON::curvature_style m_style;
  
  double m_infinity; // curvature values >= this are considered infinite
                     // and not used to compute the m_average or m_adev
  int    m_count_infinite; // number of "infinte" values
  int    m_count;    // count of "finite" values
  double m_mode;     // mode of "finite" values
  double m_average;  // average of "finite" values
  double m_adev;     // average deviation of "finite" values

  ON_Interval m_range;
};

///////////////////////////////////////////////////////////////////////////////
//
// Class  ON_MeshTopology
//

struct ON_MeshTopologyVertex
{
  // m_tope_count = number of topological edges that begin or 
  // end at this topological vertex.
  int m_tope_count;

  // m_topei[] is an array of length m_tope_count with the indices 
  // of the topological edges that begin or end at this topological
  // vertex.  Generally, these edges are listed in no particular
  // order.  If you want the edges listed "radially", then call
  // ON_MeshTopology::SortVertexEdges.
  const int* m_topei;

  // m_v_count = number of ON_Mesh vertices that correspond to 
  // this topological vertex.
  int m_v_count;

  // m_vi[] is an array of length m_v_count with the indices of the
  // ON_Mesh vertices that correspond to this topological vertex.
  const int* m_vi;
};

struct ON_MeshTopologyEdge
{
  // m_topvi[] = indices of the topological verteices where the 
  // edge begins and ends.
  int m_topvi[2];

  // m_topf_count = number of topological faces tat share this topological edge
  int m_topf_count;

  // m_topfi[] is an array of length m_topf_count with the indices of the
  // topological faces that share this topological edge.
  const int* m_topfi;
};

struct ON_CLASS ON_MeshTopologyFace
{
  /*
    m_topei[] = indices of the topological edges that bound the face.
    If m_topei[2] = m_topei[3], then the face is a triangle, otherwise
    the face is a quad.
 
    NOTE WELL:
      The topological edge with index m_topei[k] ENDS at the
      vertex corresponding to ON_MeshFace.vi[k]. So, ...

      If the face is a quad, (ON_MeshFace.vi[2]!=ON_MeshFace.vi[3]),
      the topological edge with index m_topei[0] STARTS at
      ON_MeshFace.vi[3] and ENDS at ON_MeshFace.vi[0],
      the topological edge with index m_topei[1] STARTS at
      ON_MeshFace.vi[0] and ENDS at ON_MeshFace.vi[1],
      the topological edge with index m_topei[2] STARTS at
      ON_MeshFace.vi[1] and ENDS at ON_MeshFace.vi[2], and
      the topological edge with index m_topei[3] STARTS at
      ON_MeshFace.vi[0] and ENDS at ON_MeshFace.vi[1],
      
      If the face is a triangle, (ON_MeshFace.vi[2]==ON_MeshFace.vi[3]),
      the topological edge with index m_topei[0] STARTS at
      ON_MeshFace.vi[2] and ENDS at ON_MeshFace.vi[0],
      the topological edge with index m_topei[1] STARTS at
      ON_MeshFace.vi[0] and ENDS at ON_MeshFace.vi[1],
      the topological edge with index m_topei[2] STARTS at
      ON_MeshFace.vi[1] and ENDS at ON_MeshFace.vi[2].
  */
  int m_topei[4];

  /*
    If m_reve[i] is 0, then the orientation of the edge matches the
    orientation of the face.  If m_reve[i] is 1, then the orientation
    of the edge is opposite that of the face.
  */
  char m_reve[4];

  /*
  Description:
    A topological mesh face is a valid triangle if m_topei[0], 
    m_topei[1], m_topei[2] are distinct edges and 
    m_topei[3]=m_topei[2].
  Returns:
    True if face is a triangle.
  */
  bool IsTriangle() const;

  /*
  Description:
    A topological mesh face is a valid quad if m_topei[0], 
    m_topei[1], m_topei[2], and m_topei[3] are distinct edges.
  Returns:
    True if face is a quad.
  */
  bool IsQuad() const;

  /*
  Description:
    A topological mesh face is valid if m_topei[0], m_topei[1], 
    and m_topei[2] are mutually distinct, and m_topei[3] is 
    either equal to m_topei[2] or mutually distinct from the
    first three indices.
  Returns:
    True if face is valid.
  */
  bool IsValid( ) const;
};

class ON_CLASS ON_MeshFace
{
public:
  int vi[4]; // vertex index - vi[2]==vi[3] for tirangles
  bool IsTriangle() const;
  bool IsQuad() const;
  bool IsValid( 
          int // number of vertices in mesh
        ) const;
  void Flip();
};

struct ON_MeshPart
{
  // ON_Mesh faces with indices fi[0] <= i < fi[1] reference
  // vertices with indices vi[0] <= j < vi[1].
  int vi[2]; // subinterval of mesh m_V[] array
  int fi[2]; // subinterval of mesh m_F[] array
  int vertex_count;   // = vi[1] - vi[0];
  int triangle_count; // tris + 2*quads >= fi[1] - fi[0]
};

#if defined(ON_DLL_TEMPLATE)
// This stuff is here because of a limitation in the way Microsoft
// handles templates and DLLs.  See Microsoft's knowledge base 
// article ID Q168958 for details.
#pragma warning( push )
#pragma warning( disable : 4231 )
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_MeshFace>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_MeshTopologyVertex>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_MeshTopologyEdge>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_MeshTopologyFace>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<struct ON_MeshPart>;
#pragma warning( pop )
#endif

class ON_CLASS ON_MeshTopology
{
  // A mesh topology class is always associated with an ON_Mesh
  // and can be retrieved by calling ON_Mesh::Topology()
public:
  ON_MeshTopology();
  ~ON_MeshTopology();

  bool IsValid() const;

  void Dump( ON_TextLog& ) const;

  //////////
  // The parent ON_Mesh geometry used to compute this mesh topology.
  const ON_Mesh* m_mesh;

  //////////
  // number of topoligical vertices (<= m_mesh.VertexCount())
  int TopVertexCount() const;

  //////////
  // number of topoligical edges
  int TopEdgeCount() const;
  
  //////////
  // number of topoligical faces (same as m_mesh.FaceCount())
  int TopFaceCount() const;

  /*
  Description:
    Get a vertex reference to a mesh vertex index.
  Parameters:
    ci - [in] component index with type mesh_vertex or meshtop_vertex.
  Returns:
    a reference to the vertex
  */
  ON_MeshVertexRef VertexRef(ON_COMPONENT_INDEX ci) const;

  ON_MeshVertexRef VertexRef(int topv_index) const;

  /*
  Description:
    Get an edge reference.
  Parameters:
    ci - [in] component index with type meshtop_edge.
  Returns:
    a reference to the edge
  */
  ON_MeshEdgeRef EdgeRef(ON_COMPONENT_INDEX ci) const;

  ON_MeshEdgeRef EdgeRef(int tope_index) const;

  /*
  Description:
    Get a face reference from a mesh face index.
  Parameters:
    ci - [in] component index with type mesh_face.
  Returns:
    a reference to the face.
  Remarks:
    The OM_Mesh.m_F[] and ON_MeshTopology.m_topf[] arrays
    are parallel arrays; corresponding faces have identical
    indices.
  */
  ON_MeshFaceRef FaceRef(ON_COMPONENT_INDEX ci) const;

  ON_MeshFaceRef FaceRef(int topf_index) const;


  /*
  Description:
    Get the 3d point location of a vertex.
  Parameters:
    topv_index - [in];
  Returns:
    Location of vertex.
  */
  ON_3fPoint TopVertexPoint(
    int topv_index
    ) const;

  /*
  Description:
    Get the 3d line along an edge.
  Parameters:
    tope_index - [in];
  Returns:
    Line along edge.  If input is not valid,
    the line.from and to are ON_UNSET_POINT
  */
  ON_Line TopEdgeLine(
    int tope_index
    ) const;

  ////////
  // returns index of edge that connects topological vertices
  // returns -1 if no edge is found.
  int TopEdge(
    int, int // ON_MeshTopology vertex topology indices
    ) const;

  ////////
  // returns ON_MeshTopology vertex topology index of a face
  // corner.  The face is triangle iv TopFaceVertex(2) = TopFaceVertex(3)
  bool GetTopFaceVertices(
    int, // ON_MeshTopology face topology index (= ON_Mesh face index)
    int[4] // ON_MeshTopology vertex indices returned here
    ) const;

  /*
  Description:
    Sort the m_topei[] list of a mesh topology vertex so that
    the edges are in radial order.  The "const" is a white
    lie to make this function easier to call.
  Parameter:
    topvi - [in] index of vertex in m_topv[] array.
  Remarks:
    A nonmanifold edge is treated as a boundary edge with respect
    to sorting.  If any boundary or nonmanifold edges end at the
    vertex, then the first edge will be a boundary or nonmanifold
    edge.
  */
  bool SortVertexEdges( int topvi ) const;

  /*
  Description:
    Sort the m_topei[] list of every mesh topology vertex so 
    that the edges are in radial order.  The "const" is a white
    lie to make this function easier to call.
  Remarks:
    Same as
    for ( int topvi = 0; topvi < m_topv.Count(); topvi++ )
      SortVertexEdges(topvi);
  */
  bool SortVertexEdges() const;

  /*
  Description:
    Returns true if the topological vertex is hidden. 
  Parameters:
    topvi - [in] mesh topology vertex index.
  Returns:
    True if mesh topology vertex is hidden.
  Remarks:
    The mesh topology vertex is hidden if and only if
    all the ON_Mesh vertices it represents is hidden.
  */
  bool TopVertexIsHidden( int topvi ) const;

  /*
  Description:
    Returns true if the topological edge is hidden. 
  Parameters:
    topei - [in] mesh topology edge index.
  Returns:
    True if mesh topology edge is hidden.
  Remarks:
    The mesh topology edge is hidden if and only if
    either of its mesh topology vertices is hidden.
  */
  bool TopEdgeIsHidden( int topei ) const;

  /*
  Description:
    Returns true if the topological face is hidden. 
  Parameters:
    topfi - [in] mesh topology face index.
  Returns:
    True if mesh topology face is hidden.
  Remarks:
    The mesh topology face is hidden if and only if
    any of its mesh topology edges are hidden.
  */
  bool TopFaceIsHidden( int topfi ) const;

  //////////
  // m_topv_map[] has length m_mesh.VertexCount() and 
  // m_topv[m_topv_map[vi]] is the topological mesh vertex that is assocated
  // the with the mesh vertex m_mesh.m_V[vi].
  ON_SimpleArray<int> m_topv_map;

  ////////////
  // Array of topological mesh vertices.  See the comments in the definition
  // of ON_MeshTopologyVertex for details.
  ON_SimpleArray<ON_MeshTopologyVertex> m_topv;

  ////////////
  // Array of topological mesh edges.  See the comments in the definition
  // of ON_MeshTopologyEdge for details.
  ON_SimpleArray<ON_MeshTopologyEdge> m_tope;

  ////////////
  // Array of topological mesh faces.  The topological face
  // m_topf[fi] corresponds to the mesh face ON_Mesh.m_F[fi].
  // See the comments in the definition of ON_MeshTopologyFace
  // for details. To get the indices of the mesh topology 
  // vertices at the face corners use 
  // topvi = m_topv_map[m_mesh.m_F[fi].vi[n]]
  ON_SimpleArray<ON_MeshTopologyFace> m_topf;

  /*
  Description:
    Expert user function for efficiently getting the
    integer arrays used by the ON_MeshTopologyVertex
    and ON_MeshTopologyEdge classes.
  Parameters:
    count - [in] number of integers in array
  Returns:
    pointer to integer array.  The array memory
    will be freed by ~ON_MeshTopology()
  */
  int* GetIntArray(int count);

private:
  friend class ON_Mesh;

  bool Create();
  void Destroy();
  void EmergencyDestroy();

  // efficient workspaces for
  struct memchunk
  {
    struct memchunk* next;
  } *m_memchunk;
  bool m_bIsValid;

private:
  // no implementation
  ON_MeshTopology(const ON_MeshTopology&);
  ON_MeshTopology& operator=(const ON_MeshTopology&);
};

struct ON_MeshNgon
{
  // Number of N-gon corners (N >= 3)
  int N;

  // N-gon vertex indices
  // An array of N indices into the mesh's m_V[] vertex array.
  // If the ON_MeshNgon is returned by the ON_MeshNgonList::AddNgon()
  // function, then the memory for vi is managed by the ON_MeshNgonList
  // class.  
  int* vi;

  // N-gon face indices
  // An array of N indices into the mesh's m_F[] face array.
  // Often, only N-2 indices are used. Unused indices are set to -1.
  // If the ON_MeshNgon is returned by the ON_MeshNgonList::AddNgon()
  // function, then the memory for fi is managed by the ON_MeshNgonList
  // class.  
  int* fi;
};

class ON_CLASS ON_MeshNgonList
{
public:
  ON_MeshNgonList();
  ~ON_MeshNgonList();
  ON_MeshNgonList(const ON_MeshNgonList&);
  ON_MeshNgonList& operator=(const ON_MeshNgonList&);


  /*
  Description:
    Add an N-gon to the list
  Parameters:
    N - [in] number of vertices ( >= 5)
    vi - [in] array of N vertex indices into the mesh's m_V[] array.
    fi - [in] array of N face indices into the mesh's m_F[] array.
              Unused indices are set to -1.  In many cases
              there are N-2 valid indices and these are triangles.
  Remarks:
    Adding an N-gon may invalidate any pointers previously
    returned by Ngon.
  */
  bool AddNgon(int N, const int* vi, const int* fi);
  struct ON_MeshNgon* AddNgon(int N);

  /*
  Returns:
    Number of Ngons
  */
  int NgonCount() const;

  /*
  Parameters:
    Ngon_index - [in] zero based index
  Returns:
    NULL or a pointer to the Ngon
  */
  ON_MeshNgon* Ngon(int Ngon_index) const;

  /*
  Description:
    If you know about how many ngons you will need,
    then use the function to reserve space for them.
  */
  bool ReserveNgonCapacity(int capacity);

  /*
  Description:
    Destroy N-gon list
  */
  void Destroy();

  /*
  Returns:
    Approximate number of bytes used by this class.
  */
  unsigned int SizeOf() const;

private:
  int m_ngons_count;
  int m_ngons_capacity;
  ON_MeshNgon* m_ngons;
  struct ON_NGON_MEMBLK* m_memblk_list;
};

class ON_CLASS ON_MeshPartition
{
public:
  ON_MeshPartition();
  ~ON_MeshPartition();

  // maximum number of vertices in a partition
  int m_partition_max_vertex_count;
  // maximum number of triangles in a partition (quads count as 2 triangles)
  int m_partition_max_triangle_count;

  // Partition i uses 
  // vertices m_V[j] where 
  //
  //   m_part[i].vi[0] <= j < m_part[i].vi[1] 
  //
  // and uses faces m_F[k] where
  //
  //    m_part[i].fi[0] <= k < m_part[i].fi[1]
  ON_SimpleArray<struct ON_MeshPart> m_part;
};



class ON_CLASS ON_MappingTag
{
public:
  ON_MappingTag();
  void Default();
  bool Write(ON_BinaryArchive&) const;
  bool Read(ON_BinaryArchive&);
  void Dump( ON_TextLog& ) const;
  void Transform( const ON_Xform& xform );
  void Set(const ON_TextureMapping& mapping);

  /*
  Description:
    Sets the tag to the value the meshes have that
    come out of ON_Brep::CreateMesh().
  */
  void SetDefaultSurfaceParameterMappingTag();

  int Compare( const ON_MappingTag& other,
               bool bCompareId = true,
               bool bCompareCRC = true,
               bool bCompareXform = true
               ) const;

  /*
  Returns:
    True if the mapping tag is set.
  */
  bool IsSet() const;

  /*
  Returns:
    True if the mapping tag is for a mapping with
    type ON_TextureMapping::srfp_mapping with
    m_uvw = identity.
  */
  bool IsDefaultSurfaceParameterMapping() const;

  // Identifies the mapping used to create the texture 
  // coordinates and records transformations applied 
  // to the mesh after the texture coordinates were
  // calculated.  If the texture mapping does not
  // change when the mesh is transformed, then set 
  // m_mesh_xform to zero so that compares will work right.
  //
  // 
  ON_UUID                 m_mapping_id;   // ON_TextureMapping::m_mapping_id
  ON_TextureMapping::TYPE m_mapping_type; // ON_TextureMapping::m_type
  ON__UINT32              m_mapping_crc;  // ON_TextureMapping::MappingCRC()
  ON_Xform                m_mesh_xform;
};

class ON_CLASS ON_TextureCoordinates
{
public:
  ON_TextureCoordinates();

  ON_MappingTag   m_tag;
  int                        m_dim; // 1, 2, or 3
  ON_SimpleArray<ON_3fPoint> m_T;   // texture coordinates
};


#if defined(ON_DLL_TEMPLATE)
// This stuff is here because of a limitation in the way Microsoft
// handles templates and DLLs.  See Microsoft's knowledge base 
// article ID Q168958 for details.
#pragma warning( push )
#pragma warning( disable : 4231 )
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_MappingTag>;
ON_DLL_TEMPLATE template class ON_CLASS ON_ClassArray<ON_TextureCoordinates>;
#pragma warning( pop )
#endif


class ON_CLASS ON_Mesh : public ON_Geometry
{
  ON_OBJECT_DECLARE(ON_Mesh);
public:
  ON_Mesh();
  ON_Mesh(
    int,  // initial face array capacity
    int,  // initial vertex array capacity
    bool, // true if mesh has vertex normals
    bool  // true if mesh has texture coordinates
    );
  ON_Mesh( const ON_Mesh& );
  ON_Mesh& operator=( const ON_Mesh& );
  ~ON_Mesh();

  // Override of virtual ON_Object::MemoryRelocate
  void MemoryRelocate();

  // virtual ON_Object::DestroyRuntimeCache override
  void DestroyRuntimeCache( bool bDelete = true );

  void Destroy();
  void EmergencyDestroy(); // Call only when memory used by this class's
                           // members will soon become invalid for reasons 
                           // beyond your control. EmergencyDestroy() zeros
                           // anything that could possibly cause
                           // ~ON_Mesh() to crash.  Calling
                           // EmergencyDestroy() under normal conditions 
                           // will result in ~ON_Mesh() leaking
                           // memory.

  const class ON_MeshTree* MeshTree() const;

  void DestroyTree( bool bDeleteTree = true );

  /////////////////////////////////////////////////////////////////
  // ON_Object overrides

  // virtual ON_Object::SizeOf override
  unsigned int SizeOf() const;

  // virtual ON_Object::DataCRC override
  ON__UINT32 DataCRC(ON__UINT32 current_remainder) const;

  /*
  Description:
    Tests an object to see if its data members are correctly
    initialized.
  Parameters:
    text_log - [in] if the object is not valid and text_log
        is not NULL, then a brief englis description of the
        reason the object is not valid is appened to the log.
        The information appended to text_log is suitable for 
        low-level debugging purposes by programmers and is 
        not intended to be useful as a high level user 
        interface tool.
  Returns:
    @untitled table
    true     object is valid
    false    object is invalid, uninitialized, etc.
  Remarks:
    Overrides virtual ON_Object::IsValid
  */
  ON_BOOL32 IsValid( ON_TextLog* text_log = NULL ) const;

  void Dump( ON_TextLog& ) const; // for debugging

  ON_BOOL32 Write( ON_BinaryArchive& ) const;

  ON_BOOL32 Read( ON_BinaryArchive& );

  ON::object_type ObjectType() const;

  /////////////////////////////////////////////////////////////////
  // ON_Geometry overrides

  int Dimension() const;

  ON_BOOL32 GetBBox( // returns true if successful
         double*,    // minimum
         double*,    // maximum
         ON_BOOL32 = false  // true means grow box
         ) const;

  /*
	Description:
    Get tight bounding box of the mesh.
	Parameters:
		tight_bbox - [in/out] tight bounding box
		bGrowBox -[in]	(default=false)			
      If true and the input tight_bbox is valid, then returned
      tight_bbox is the union of the input tight_bbox and the 
      mesh's tight bounding box.
		xform -[in] (default=NULL)
      If not NULL, the tight bounding box of the transformed
      mesh is calculated.  The mesh is not modified.
	Returns:
    True if the returned tight_bbox is set to a valid 
    bounding box.
  */
	bool GetTightBoundingBox( 
			ON_BoundingBox& tight_bbox, 
      int bGrowBox = false,
			const ON_Xform* xform = 0
      ) const;

  ON_BOOL32 Transform( 
         const ON_Xform&
         );

  // virtual ON_Geometry::IsDeformable() override
  bool IsDeformable() const;

  // virtual ON_Geometry::MakeDeformable() override
  bool MakeDeformable();

  ON_BOOL32 SwapCoordinates(
        int, int        // indices of coords to swap
        );

  // virtual ON_Geometry override
  bool Morph( const ON_SpaceMorph& morph );

  // virtual ON_Geometry override
  bool IsMorphable() const;

  // virtual ON_Geometry override
  bool EvaluatePoint( const class ON_ObjRef& objref, ON_3dPoint& P ) const;


  /////////////////////////////////////////////////////////////////
  // Interface
  // 

  // creation
  bool SetVertex(
         int,              // vertex index
         const ON_3dPoint& // vertex location
         );
  bool SetVertex(
         int,              // vertex index
         const ON_3fPoint& // vertex location
         );
  bool SetVertexNormal(
         int,               // vertex index
         const ON_3dVector& // unit normal
         );
  bool SetVertexNormal(
         int,               // vertex index
         const ON_3fVector& // unit normal
         );
  bool SetTextureCoord(
         int,               // vertex index
         double, double     // texture coordinates
         );
  bool SetTriangle(
         int, // face index
         int,int,int // vertex indices
         );
  bool SetQuad(
         int, // face index
         int,int,int,int // vertex indices
         );

  /*
  Description:
    Get a vertex reference to a mesh vertex index.
  Parameters:
    ci - [in] component index with type mesh_vertex or meshtop_vertex.
  Returns:
    a reference to the vertex
  */
  ON_MeshVertexRef VertexRef(ON_COMPONENT_INDEX ci) const;

  ON_MeshVertexRef VertexRef(int mesh_V_index) const;

  /*
  Description:
    Get an edge reference from a mesh topology edge index.
  Parameters:
    ci - [in] component index with type meshtop_edge
  Returns:
    a reference to the edge
  */
  ON_MeshEdgeRef EdgeRef(ON_COMPONENT_INDEX ci) const;

  ON_MeshEdgeRef EdgeRef(int tope_index) const;

  /*
  Description:
    Get a face reference from a mesh face index.
  Parameters:
    ci - [in] component index with type mesh_face.
  Returns:
    a reference to the face
  */
  ON_MeshFaceRef FaceRef(ON_COMPONENT_INDEX ci) const;

  ON_MeshFaceRef FaceRef(int mesh_F_index) const;

  /*
  Parameters:
   ci - [in] a component index with type mesh_vertex, meshtop_vertex,
             meshtop_edge, or mesh_face.
  Returns:
    A pointer to an ON_MeshVertexRef, ON_MeshEdgeRef, or ON_MeshFaceRef.
    The caller must delete the returned object when it is no longer
    needed.
  See Also:
    ON_Mesh::VertexRef
    ON_Mesh::EdgeRef
    ON_Mesh::FaceRef
  */
  ON_Geometry* MeshComponent( 
      ON_COMPONENT_INDEX ci
      ) const;

  // query
  int VertexCount() const;
  int FaceCount() const;
  int QuadCount() const; // number of faces that are quads
  int TriangleCount() const; // number of faces that are triangles
  bool HasVertexNormals() const; // normals at vertices
  bool HasFaceNormals() const;
  bool HasTextureCoordinates() const;
  bool HasSurfaceParameters() const;
  bool HasPrincipalCurvatures() const;
  bool HasVertexColors() const;

  /*
  Returns:
    Number of vertices that are hidden.
  */
  int HiddenVertexCount() const;

  bool GetCurvatureStats( 
         ON::curvature_style, 
         ON_MeshCurvatureStats& 
         ) const;

  void InvalidateVertexBoundingBox(); // Call if defining geometry is changed by 
                             // directly manipulating the m_V[] array.
  void InvalidateVertexNormalBoundingBox(); // Call if defining geometry is changed by 
                             // directly manipulating the m_N[] array.
  void InvalidateTextureCoordinateBoundingBox(); // Call if defining geometry is changed by 
                             // directly manipulating the m_T[] array.
  void InvalidateCurvatureStats(); // Call if defining geometry is changed by 
                             // directly manipulating the m_T[] array.
  void InvalidateBoundingBoxes(); // Invalidates all cached bounding box information.


  void Flip(); // reverses face orientations and flips vertex and face normals

  void FlipVertexNormals(); // reverses vertex normals
  void FlipFaceNormals(); // reverses face normals
  void FlipFaceOrientation(); // reverses face orientation (does nothing to normals)

  void SetMeshParameters( const ON_MeshParameters& );
  const ON_MeshParameters* MeshParameters() const;
  void DeleteMeshParameters();

  
  bool UnitizeVertexNormals();
  bool UnitizeFaceNormals();
  bool CountQuads();

  /*
  Description:
    Splits all quads along the short diagonal.
  */
  bool ConvertQuadsToTriangles();

  /*
  Description:
    Joins adjacent triangles into quads if the resulting quad
    is nice.
  Parameters:
    angle_tol_radians - [in] Used to compare adjacent
      triangles' face normals.  For two triangles to be considered,
      the angle between their face normals has to be <= angle_tol_radians.
      When in doubt use ON_PI/90.0 (2 degrees).
    min_diagonal_length_ratio - [in] ( <= 1.0) For two triangles to be
       considered the ratio of the resulting quad's diagonals
       (length of the shortest diagonal)/(length of longest diagonal).
       has to be >= min_diagonal_length_ratio.
       When in doubt us .875.
  */
  bool ConvertTrianglesToQuads(
    double angle_tol_radians,
    double min_diagonal_length_ratio
    );

  bool ComputeFaceNormals();   // compute face normals for all faces
  bool ComputeFaceNormal(int); // computes face normal of indexed face

  int CullDegenerateFaces(); // returns number of degenerate faces
  int CullUnusedVertices(); // returns number of culled vertices

  // Description:
  //   Removes any unreferenced objects from arrays, reindexes as needed,
  //   and shrinks arrays to minimum required size.
  bool Compact();

  bool ComputeVertexNormals();    // uses face normals to cook up a vertex normal
  
  //////////
  // Scales textures so the texture domains are [0,1] and
  // eliminates any texture rotations.
  bool NormalizeTextureCoordinates();

	/////////
	// Description:
	//		Transposes the texture coordinates
	//  Returns
	//			true  -  success
	bool TransposeTextureCoordinates();
	bool TransposeSurfaceParameters();
 
	/////////
	// Description:
	//		Reverse one coordinate direction of the texture coordinates, within texture domain m_tex_domain
	//	Parameters:
	//		dir  -[in]	-   dir=0  first texture coordinate is reversed
	//									  dir=1 second texture coordinate is reversed
	//  Returns
	//			true  -  success
	bool ReverseTextureCoordinates( int dir );
	bool ReverseSurfaceParameters( int dir );
 


  /*
  Description:
    Use a texture mapping function to set the m_T[] values.
  Parameters:
    mapping - [in]
    mesh_xform - [in]
      If not NULL, the mapping calculation is performed as
      if the mesh were transformed by mesh_xform; the
      location of the mesh is not changed.
    bLazy - [in]
      If true and the m_T[] values were set using the same
      mapping parameters, then no calculation is performed.
  Returns:
    True if successful.
  See Also:
    ON_TextureMapping::GetTextureCoordinates
  */
  bool SetTextureCoordinates( 
          const class ON_TextureMapping& mapping,
					const class ON_Xform* mesh_xform = 0,
          bool bLazy = true
          );

  bool HasCachedTextureCoordinates() const;

  const ON_TextureCoordinates* CachedTextureCoordinates( 
          const ON_UUID& mapping_id 
          ) const;

  const ON_TextureCoordinates* SetCachedTextureCoordinates( 
          const class ON_TextureMapping& mapping,
					const class ON_Xform* mesh_xform = 0,
          bool bLazy = true
          );

  bool EvaluateMeshGeometry( const ON_Surface& ); // evaluate surface at tcoords
                                                  // to set mesh geometry

  // finds all coincident vertices and merges them if break angle is small enough
  bool CombineCoincidentVertices( 
          ON_3fVector, // coordinate tols for considering vertices
                       // to be coincident
          double  // cosine normal angle tolerance in radians
                  // if vertices are coincident, then they are combined
                  // if NormalA o NormalB >= this value
          );

  /*
  Description:
    Combines identical vertices.
  Parameters:
    bIgnoreVertexNormals - [in] If true, then vertex normals
      are ignored when comparing vertices.
    bIgnoreTextureCoordinates - [in] If true, then vertex
      texture coordinates, colors, and principal curvatures
      are ignored when comparing vertices.
  Returns:
    True if the mesh is changed, in which case the returned
    mesh will have fewer vertices than the input mesh.
  */
  bool CombineIdenticalVertices(
          bool bIgnoreVertexNormals = false,
          bool bIgnoreTextureCoordinates = false
          );

  void Append( const ON_Mesh& ); // appends a copy of mesh to this and updates
                                 // indices of appended mesh parts

  void SetClosed(int);

  /*
  Returns:
    True if every mesh "edge" has two or more faces.
  */
  bool IsClosed() const;

  /*
  Description:
    Determine if the mesh is a manifold.
  Parameters:
    bTopologicalTest - [in]
      If true, the query treats coincident vertices as
      the same.
    pbIsOriented - [out]
      If the input pointer is not NULL, then the returned
      value of *pbIsOriented will be true if the mesh
      is a manifold and adjacent faces have compatible
      face normals.
    pbHasBoundary - [out]
      If the input pointer is not NULL, then the returned
      value of *pbHasBoundary will be true if the mesh
      is a manifold and there is at least one "edge"
      with no adjacent faces have compatible
      face normals.
  Returns:
    True if every mesh "edge" has at most two adjacent faces.
  */
  bool IsManifold(
    bool bTopologicalTest,
    bool* pbIsOriented = NULL,
    bool* pbHasBoundary = NULL
    ) const;

  /*
  Description:
    Appends a list of mesh edges that begin or end at the specified
    vertices to the edges[] array.
  Parameters:
    vcount - [in]
      number of vertices
    vertex_index - [in]
      array of vertex indices
    bNoDuplicates - [in]
      If true, then only one edges[] is added for each edge,
      the first vertex index will alwasy be less than the
      second, and the returned elements are sorted in dictionary
      order.
      If false and an edge is shared by multiple faces, then
      there will be an edges[] element added for each face and the
      order of the vertex indicies will indicate the orientation
      of the edge with respect to the face.  No sorting is performed
      in this case.
    edges - [out]
      Edges that begin or end at one of the specified vertices are
      appended to this array.  Each ON_2dex records the start and
      end vertex index.
  Returns:
    Number of ON_2dex values appended to the edges[] array.
  */
  int GetVertexEdges( 
    int vcount,
    const int* vertex_index, 
    bool bNoDuplicates,
    ON_SimpleArray<ON_2dex>& edges
    ) const;

  /*
  Description:
    Appends a list of mesh edges to the edges[] array.
  Parameters:
    edges - [out]
      Each edges[] element is a pair of vertex indices.  There
      is at least one face in the mesh with an edge running between
      the indicies.
  Returns:
    Number of ON_2dex values appended to the edges[] array.
  */
  int GetMeshEdges( 
    ON_SimpleArray<ON_2dex>& edges
    ) const;

#if defined(OPENNURBS_PLUS)

  /*
  Description:
    Get the point on the mesh that is closest to P.
  Parameters:
    P - [in] test point
    Q - [out] point on the mesh
    maximum_distance = 0.0 - [in] 
            optional upper bound on the distance 
            from P to the mesh.  If you are only 
            interested in finding a point Q on the 
            mesh when P.DistanceTo(Q) < maximum_distance, 
            then set maximum_distance to that value.
  Returns:
    True if successful.  If false, the value of Q
    is undefined.
  */
  bool GetClosestPoint(
          const ON_3dPoint& P,
          ON_MESH_POINT* Q,
          double maximum_distance = 0.0
          ) const;

  /*
  Description:
    Quickly intersect this mesh with meshB.  Ignore overlaps
    and near misses.
  Parameters:
    meshB - [in]
    lines - [out] Intersection lines are appended to
                  this list.
  Returns:
    number of lines appended to lines[] array.
  Remarks:
    The InstersectMesh function will will create a meshtree, a mesh topology 
    and face normals of this mesh and meshB. Note: if you create these in 
    multiple memory pools you run the risk of crashing or leaking memory if
    you are not careful.
  */
  int IntersectMesh( 
          const ON_Mesh& meshB,
          ON_SimpleArray<ON_Line>& lines
          ) const;

  /*
  Description:
    Carefully intersect this mesh with meshB.
  Parameters:
    meshB - [in]
    x - [out] Each element of x is a polyline of ON_MMX_POINTs.
    intersection_tolerance - [in]
    overlap_tolerance - [in]
  Returns:
    number of olylines appended to x[] array.
  Remarks:
    The InstersectMesh function will will create a meshtree, a mesh topology 
    and face normals of this mesh and meshB. Note: if you create these in 
    multiple memory pools you run the risk of crashing or leaking memory if
    you are not careful.
  */
  int IntersectMesh( 
          const ON_Mesh& meshB,
          ON_ClassArray< ON_SimpleArray< ON_MMX_POINT > >& x, 
          double intersection_tolerance = 0.0,
          double overlap_tolerance = 0.0
          ) const;

#endif

  /*
  Description:
    Compute area of the mesh.
  Parameters:
    error_estimate - [out]  if not NULL, an upper bound on the error
        in the area calculation is returned.
  Example:

            ON_Mesh mesh = ...;
            double area, error_estimate;
            area = mesh.Area(&error_estimate);
            printf("mesh area = %g (+/- %g)\n",area,error_estimate);

  Returns:
    Area of the mesh.
  */
  double Area( double* error_estimate = NULL ) const;

  /*
  Description:
    Compute area centroid of the mesh.
  Parameters:
    area - [out] it not NULL, area of the mesh
  Returns:
    Location of area centroid.
  See Also:
    ON_Mesh::AreaMassProperties
  */
  ON_3dPoint AreaCentroid( 
          double* area = NULL
          ) const;

  /*
  Description:
    Calculate area mass properties of the mesh.
  Parameters:
    mp - [out] 
    bArea - [in] true to calculate area
    bFirstMoments - [in] true to calculate area first moments,
                         area and area centroid.
    bSecondMoments - [in] true to calculate area second moments.
    bProductMoments - [in] true to calculate area product moments.
  Returns:
    True if successful.
  */
  bool AreaMassProperties(
    ON_MassProperties& mp,
    bool bArea = true,
    bool bFirstMoments = true,
    bool bSecondMoments = true,
    bool bProductMoments = true
    ) const;


  /*
  Description:
    Compute volume of the mesh.
  Parameters:
    base_point - [in] optional base point When computing the volume of
      solid defined by several meshes, pass the same base_point to each call
      to volume.  When computing the volume of a solid defined by a single
      mesh, the center of the bounding box is a good choice for base_point.
    error_estimate - [out]  if not NULL, an upper bound on the error
        in the volume calculation is returned.
  Returns:
    volume of the mesh.
  Example:

            // Assume a solid is enclosed by 3 meshes, mesh1, mesh2, and mesh3.
            // The volume of the solid can be computed as follows.
            ON_Mesh mesh1=..., mesh2=..., mesh3=...;
            // use the center of the solid's bounding box as a common base point.
            ON_BoundingBox bbox = mesh1.BoundingBox();
            mesh2.GetBoundingBox(bbox,true);
            mesh3.GetBoundingBox(bbox,true);
            ON_3dPoint base_point = bbox.Center()
            double vol1_err, vol2_err, vol3_err;
            double vol1 = mesh1.Volume(base_point,&vol1_err);
            double vol2 = mesh2.Volume(base_point,&vol2_err);
            double vol3 = mesh3.Volume(base_point,&vol3_err);
            double volume = vol1 + vol2 + vol3;
            double error_estimate = vol1_err + vol2_err + vol3_err;
            printf("mesh volumd = %g (+/- %g)\n",volume,error_estimate);
  */
  double Volume( 
              ON_3dPoint base_point = ON_origin, 
              double* error_estimate = NULL 
              ) const;


  /*
  Description:
    Compute volume centroid of the mesh.
  Parameters:
    base_point - [in] When computing the centroid of a solid
      volume defined by several meshes, pass the same base_point 
      to each call to GetVolumeCentroid() and add the answers.
      When computing the centroid of a solid defined by a single
      mesh, the center of the bounding box is a good choice for base_point.
    volume - [out] it not NULL, Volume of the mesh
  Returns:
    Location of the volume centroid.
  */
  ON_3dPoint VolumeCentroid( 
          ON_3dPoint base_point = ON_origin,
          double* volume = NULL
          ) const;

  /*
  Description:
    Calculate volume mass properties of the mesh.
  Parameters:
    base_point - [in] When computing the volume mass properties
      of a solid volume defined by several meshes, pass the same
      base_point to each call to VolumeMassProperties() and add 
      the answers.  When computing the volume mass properties of
      a solid defined by a single mesh, the center of the 
      bounding box is a good choice for base_point. If the mesh
      is closed, you can pass ON_UNSET_POINT and the
      center of the bounding box will be used.
    mp - [out] 
    bVolume - [in] true to calculate volume
    bFirstMoments - [in] true to calculate volume first moments,
                         volume, and volume centroid.
    bSecondMoments - [in] true to calculate volume second moments.
    bProductMoments - [in] true to calculate volume product moments.
    base_point - [in] 
      If the surface is closed, then pass ON_UNSET_VALUE.

      This parameter is for expert users who are computing a
      volume whose boundary is defined by several non-closed
      breps, surfaces, and meshes.

      When computing the volume, volume centroid, or volume
      first moments of a volume whose boundary is defined by 
      several breps, surfaces, and meshes, pass the same 
      base_point to each call to VolumeMassProperties.  

      When computing the volume second moments or volume product
      moments of a volume whose boundary is defined by several
      breps, surfaces, and meshes, you MUST pass the entire 
      volume's centroid as the base_point and the input mp 
      parameter must contain the results of a previous call
      to VolumeMassProperties(mp,true,true,false,false,base_point).
      In particular, in this case, you need to make two sets of
      calls; use first set to calculate the volume centroid and
      the second set calculate the second moments and product 
      moments.
  Returns:
    True if successful.
  */
  bool VolumeMassProperties(
    ON_MassProperties& mp, 
    bool bVolume = true,
    bool bFirstMoments = true,
    bool bSecondMoments = true,
    bool bProductMoments = true,
    ON_3dPoint base_point = ON_UNSET_POINT
    ) const;

  ///////////////////////////////////////////////////////////////////////
  //
  // mesh editing
  //

  /*
  Description:
    Replace a mesh edge with a vertex at its center and update
    adjacent faces as needed.
  Parameters:
    topei - [in] index of edge in MeshTopology().m_tope[] array
  Returns:
    true if successful.
  */
  bool CollapseEdge( int topei );

  /*
  Description:
    Tests a mesh edge to see if it is valid as input to
    ON_Mesh::SwapMeshEdge.
  Parameters:
    topei - [in] index of edge in MeshTopology().m_tope[] array
  Returns:
    true if edge can be swapped by ON_Mesh::SwapMeshEdge.
  See Also:
    ON_Mesh::SwapEdge
  */
  bool IsSwappableEdge( int topei );


  /*
  Description:
    If the edge is shared by two triangular face, then
    the edge is "swapped".
  Parameters:
    topei - [in] index of edge in MeshTopology().m_tope[] array
  Returns:
    true if successful
  See Also:
    ON_Mesh::IsSwappableEdge
  */
  bool SwapEdge( int topei );

  /*
  Description:
    Removes a face from a mesh and does not alter the
    geometry of the remaining mesh.
  Parameters:
    meshfi - [in] index of face in ON_Mesh.m_F[] array
  Remarks:
    This function calls DestroyTopology() and DestroyPartition().
    The caller is responsible for calling Compact() if that step
    is required.
  Returns:
    true if successful
  */
  bool DeleteFace( int meshfi );

  /*
  Description:
    Destroys the m_H[] array and sets m_hidden_count=0.
  */
  void DestroyHiddenVertexArray();

  /*
  Returns:
    If the mesh has some hidden vertices, then an array
    of length VertexCount() is returned and the i-th
    element is true if the i-th vertex is hidden.
    If no vertices are hidden, NULL is returned.
  */
  const bool* HiddenVertexArray() const;

  /*
  Description:
    Set the runtime vertex hidden flag.
  Parameters:
    meshvi - [in] mesh vertex index
    bHidden - [in] true to hide vertex
  */
  void SetVertexHiddenFlag( int meshvi, bool bHidden );

  /*
  Description:
    Returns true if the mesh vertex is hidden.  This is a runtime
    setting that is not saved in 3dm files.
  Parameters:
    meshvi - [in] mesh vertex index.
  Returns:
    True if mesh vertex is hidden.
  */
  bool VertexIsHidden( int meshvi ) const;

  /*
  Description:
    Returns true if the mesh face is hidden.  This is a runtime
    setting that is not saved in 3dm files.
  Parameters:
    meshfi - [in] mesh face index.
  Returns:
    True if mesh face is hidden.
  Remarks:
    A face is hidden if, and only if, at least one of its
    vertices is hidden.
  */
  bool FaceIsHidden( int meshvi ) const;


  ///////////////////////////////////////////////////////////////////////
  //
  // mesh topology
  //
  // In order to keep the mesh facet definition simple and make the mesh
  // definition easily used in common rendering application, if two facets
  // share a vertex location but have different normals, curvatures, 
  // textures, etc., at that common vertex location, then the vertex is
  // duplicated.  When the topology of the mesh needs to be known,
  // use Topology() to get a class that provides complete topological
  // information about the mesh.
  const ON_MeshTopology& Topology() const;

  ///////////////////////////////////////////////////////////////////////
  // If you modify the mesh in any way that may change its topology,
  // then call DestroyTopology().  Specifically if you add or remove
  // vertices or face, change vertex locations, or change the face m_vi[]
  // values, then you must call DestroyTopology().
  void DestroyTopology();

  ///////////////////////////////////////////////////////////////////////
  //
  // mesh partitions
  //
  // In ancient times, some rendering engines were only able to process
  // small batches of triangles and th CreatePartition() function was
  // provided to partition the mesh into subsets of vertices and faces
  // that those renering engines could handle.
  //
  const ON_MeshPartition* CreatePartition( 
                int, // maximum number of vertices in a partition
                int  // maximum number of triangles in a partition
                );
  const ON_MeshPartition* Partition() const;
  void DestroyPartition();

  /*
  Description:
    Extract the portion of this mesh defined by mesh_part.
  Parameters:
    mesh_part - [in]
      defines portion of the mesh to extract.
    mesh - [in] (can be null, cannot be = "this).
      If mesh is no null, the extracted mesh will be put into
      this mesh.  If mesh is null, the extracted mesh will
      be created in a mesh allocated on the heap using the
      new operator.
  Returns:
    A pointer to the submesh.  If the input mesh parameter is null,
    then the caller must delete this mesh when it is no longer needed.
    If the input is invalid, then null is returned.
  */
  ON_Mesh* MeshPart( 
    const ON_MeshPart& mesh_part,
    ON_Mesh* mesh 
    ) const;

  ///////////////////////////////////////////////////////////////////////
  //
  // mesh N-gon lists.  
  //   ON_Mesh objects support faces that are triangle or quads.
  //   When a mesh is created from a format that supports N-gons
  //   for N larger than 4, an optional N-gon list can be added 
  //   that specifies the vertices and faces that make up the N-gon.
  //

  /*
  Description:
    If the mesh has an N-gon list, return a pointer to it.
  Returns:
    A pointer to the current N-gon list or NULL.
  */
  const class ON_MeshNgonList* NgonList() const;

  /*
  Description:
    If an N-gon list exists, it is returned and can be modified.
    If no N-gon list exists, a new empty list is returned and
    it can be modified.
  Returns:
    A pointer to the N-gon list that can be modified.
  */
  class ON_MeshNgonList* ModifyNgonList();

  /*
  Description:
    Destroy any existing N-gon list.
  */
  void DestroyNgonList();


  /////////////////////////////////////////////////////////////////
  // Implementation - mesh geometry

  // m_V[] - vertex locations
  // In a case where adjacent facets share a vertex
  // location but have distinct normals or texture
  // coordinates at that location, the vertex must
  // be duplicated.
  ON_3fPointArray m_V;

  // m_F[] facets (triangles or quads)
  ON_SimpleArray<ON_MeshFace> m_F;

  // m_N[] OPTIONAL vertex unit normals
  // If m_N[] is empty or m_N.Count() != m_V.Count(), 
  // Either m_N[] has zero count or it m_N[j] is the
  // the unit vertex normal at m_V[j].
  ON_3fVectorArray m_N;

  // m_FN[] OPTIONAL face unit normals
  // If m_FN[] is empty or m_FN.Count() != m_F.Count(), 
  // then m_FN is ignored.  Otherwise m_FN[j] is the
  // unit normal for the facet m_F[j].
  ON_3fVectorArray m_FN;

  /////////////////////////////////////////////////////////////////
  // Implementation - texture coordinates
  //
  // OPTIONAL texture coordinates for each vertex

  // It would be nice if this were an ON_TextureCoordinates,
  // but that breaks lots of checked out code that assumes
  // m_T is an array of ON_2fPoints.
  ON_MappingTag m_Ttag; // OPTIONAL tag for values in m_T[]
  ON_2fPointArray m_T;  // OPTIONAL texture coordinates for each vertex

  // RUNTIME ONLY
  //   This array is used to cache texture coordinates used by
  //   rendering applications that require 1d texture coordinates,
  //   3d texture coordinates, or multiple sets of texture 
  //   coordinates (e.g. blended textures with different mappings).
  //   Users are responsible for verifying 
  //   m_TC[i].m_T.Count() = m_V.Count()
  ON_ClassArray<ON_TextureCoordinates> m_TC;  

  // If m_T.Count() == m_V.Count(), then the mesh has texture coordinates
  // and m_T[j] is the texture coordinate for vertex m_V[j].
  //
  // When opennurbs or Rhino meshes an ON_Surface or ON_Brep, the texture
  // coordinates have a "canonical" linear relationship with the surface 
  // parameters that is described in the next section.  However, various 
  // mappings, spherical, planar, cylindrical, etc., can be applied that 
  // change the values of the texture coordinates.
  //
  // If a texture mapping function was used to set the m_T[] values, 
  // then the id and serial number of the mapping function is saved
  // in m_mapping_id and m_mapping_sn. The intended use of these fields
  // is to make it easy to avoid unnecessary recalculation.  
  // If a mesh is modified, then m_mapping_id should be set to nil 
  // and m_mapping_crc should be set to 0.
  //
  /////////////////////////////////////////////////////////////////


  /////////////////////////////////////////////////////////////////
  // Implementation - surface parameters and packed texture 
  // information
  //
  // If m_S.Count() == m_V.Count(), then the mesh is a tesselation
  // of a parameteric surface and m_S[j] is the surface parameter at
  // m_V[j].  Storing values in m_S[] is OPTIONAL.
  //
  // If m_srf_scale[] has positive values, then they report
  // the world coordinate size of a rectangle that would 
  // minimize texture distortion if it were mapped to the
  // mesh using normalized surface evaluation parameters.
  // This information is used to calculate high quality 
  // packed texture coordinates.  
  ON_2dPointArray m_S;
  ON_Interval m_srf_domain[2]; // surface evaluation domain.
  double m_srf_scale[2];


  // Packed texture information.
  //
  // If either of the m_packed_tex_domain[] intervals is a 
  // proper subinterval of (0,1), then a texture packing 
  // calculation assigned this subrectangle to this mesh.

  ON_Interval m_packed_tex_domain[2];

  // The m_packed_tex_rotate setting is valid only when
  // m_S, m_srf_domain, m_packed_scale[] and 
  // m_packed_tex_domain[] are all valid and the texture
  // coordinates are based on surface evaluation parameters.
  // In this special situation, this boolean records the 
  // correspondence between the the surface parameters, (u,v),
  // and the packed texture coordinates, (s,t),
  //
  //   m_packed_tex_rotate = false:
  //     a = m_srf_domain[0].NormalizedParameterAt(u);
  //     b = m_srf_domain[1].NormalizedParameterAt(v);
  //     s = m_packed_tex_domain[0].ParameterAt(a);
  //     t = m_packed_tex_domain[1].ParameterAt(b);
  //
  //     x = m_packed_tex_domain[0].NormalizedParameterAt(s);
  //     y = m_packed_tex_domain[1].NormalizedParameterAt(t);
  //     u = m_srf_domain[0].ParameterAt(x);
  //     v = m_srf_domain[1].ParameterAt(y);
  //
  //   m_packed_tex_rotate = true:
  //     a = m_srf_domain[0].NormalizedParameterAt(u);
  //     b = m_srf_domain[1].NormalizedParameterAt(v);
  //     s = m_packed_tex_domain[0].ParameterAt(a);
  //     t = m_packed_tex_domain[1].ParameterAt(1.0-b);
  //
  //     x = m_packed_tex_domain[0].NormalizedParameterAt(s);
  //     y = m_packed_tex_domain[1].NormalizedParameterAt(t);
  //     u = m_srf_domain[0].ParameterAt(y);
  //     v = m_srf_domain[1].ParameterAt(1.0 - x);
  bool m_packed_tex_rotate;

  /*
  Returns:
    True if the m_srf_scale[] values are positive and
    the m_packed_tex_domain[] intervals are set to values
    that describe a proper subrectangle of (0,1)x(0,1).
    True does not necessarily mean the current values in
    m_T[] are packed texture coordinates.
  */
  bool HasPackedTextureRegion() const;

  /////////////////////////////////////////////////////////////////
  // Implementation - curvature

  ON_SimpleArray<ON_SurfaceCurvature> m_K;  // OPTIONAL surface curvatures
                                            // Either m_K[] has zero count or it has the same
                                            // count as m_V[], in which case m_K[j] reports
                                            // the surface curvatures at m_V[j].

  /////////////////////////////////////////////////////////////////
  // Implementation - false color
  ON_MappingTag m_Ctag; // OPTIONAL tag for values in m_C[]
  ON_SimpleArray<ON_Color> m_C;  // OPTIONAL vertex color
                                 // Either m_C[] has zero count or it has the same
                                 // count as m_V[], in which case m_C[j] reports
                                 // the color assigned to m_V[j].

  /////////////////////////////////////////////////////////////////
  // Implementation - runtime vertex visibility - not saved in 3dm files.
  ON_SimpleArray<bool> m_H; // OPTIONAL vertex visibility.
                            // If m_H.Count() = m_V.Count(), then
                            // m_H[vi] is true if the vertex m_V[vi] 
                            // is hidden.  Otherwise, all vertices are visible.
  int m_hidden_count;       // number of vertices that are hidden
                            // = number of true values in m_H[] array.

  /////////////////////////////////////////////////////////////////
  // Implementation - runtime UI information
  const ON_Object* m_parent; // runtime parent geometry (use ...::Cast() to get it)

protected:
  friend class ON_MeshVertexRef;
  friend class ON_MeshEdgeRef;
  friend class ON_MeshFaceRef;


  /////////////////////////////////////////////////////////////////
  // Implementation - mesh topology
  ON_MeshTopology m_top;

  ON_MeshParameters* m_mesh_parameters; // If mesh was created from a parametric surface,
                                        // these parameters were used to create the mesh.
  int                         m_invalid_count;
  int                         m_quad_count;
  int                         m_triangle_count;

  int m_closed; // -1=unknown 0=mesh is not closed, 1 = mesh is closed, 2 = closed with duplicate vertices

  // The bounding boxes are valid if m_?box[0][0] <= m_?box[0][1];
  float m_vbox[2][3]; // 3d bounding box of all referenced vertices
  float m_nbox[2][3]; // 3d bounding box of all referenced unit normals 
                      // (for estimation of Gauss map bounds)
  float m_tbox[2][2]; // 2d bounding box of all referenced texture coordinates
  ON_MeshCurvatureStats* m_kstat[4]; // gaussian,mean,min,max,sectionx,sectiony,sectionz

  // sub-mesh information rendering large meshes
  ON_MeshPartition* m_partition;

  class ON_MeshTree* m_mtree;

private:
  bool Write_1( ON_BinaryArchive& ) const; // uncompressed 1.x format
  bool Write_2( int, ON_BinaryArchive& ) const; // compressed 2.x format
  bool Read_1( ON_BinaryArchive& );
  bool Read_2( int, ON_BinaryArchive& );
  bool WriteFaceArray( int, int, ON_BinaryArchive& ) const;
  bool ReadFaceArray( int, int, ON_BinaryArchive& );
  bool SwapEdge_Helper( int, bool );
};

class ON_CLASS ON_MeshVertexRef : public ON_Geometry
{
  ON_OBJECT_DECLARE(ON_MeshVertexRef);
public:
  ON_MeshVertexRef();
  ~ON_MeshVertexRef();
  ON_MeshVertexRef& operator=(const ON_MeshVertexRef&);


  // parent mesh
  const ON_Mesh* m_mesh;
  
  // m_mesh->m_V[] index
  // (can be -1 when m_top_vi references a shared vertex location)
  int m_mesh_vi; 
  
  // m_mesh->m_top.m_tope[] index
  int m_top_vi; 


  /*
  Description:
    Override of the virtual ON_Geometry::ComponentIndex().
  Returns:
    A component index for the vertex.  The type of the returned
    component index can be 
    ON_COMPONENT_INDEX::mesh_vertex, 
    ON_COMPONENT_INDEX::meshtop_vertex, or
    ON_COMPONENT_INDEX::invalid_type.
  */
  ON_COMPONENT_INDEX ComponentIndex() const;

  /*
  Returns:
    The mesh topology associated with this 
    mesh vertex reference or NULL if it doesn't
    exist.
  */
  const ON_MeshTopology* MeshTopology() const;

  /*
  Returns:
    The 3d location of the mesh vertex.  Returns
    ON_UNSET_POINT is this ON_MeshVertexRef is not 
    valid.
  */
  ON_3dPoint Point() const;

  /*
  Returns:
    The mesh topology vertex associated with this 
    mesh vertex reference.
  */
  const ON_MeshTopologyVertex* MeshTopologyVertex() const;

  // overrides of virtual ON_Object functions
  ON_BOOL32 IsValid( ON_TextLog* text_log = NULL ) const;
  void Dump( ON_TextLog& ) const;
  unsigned int SizeOf() const;
  ON::object_type ObjectType() const;

  // overrides of virtual ON_Geometry functions
  int Dimension() const;
  ON_BOOL32 GetBBox(
         double* boxmin,
         double* boxmax,
         int bGrowBox = false
         ) const;
  ON_BOOL32 Transform( 
         const ON_Xform& xform
         );
};

class ON_CLASS ON_MeshEdgeRef : public ON_Geometry
{
  ON_OBJECT_DECLARE(ON_MeshEdgeRef);
public:
  ON_MeshEdgeRef();
  ~ON_MeshEdgeRef();
  ON_MeshEdgeRef& operator=(const ON_MeshEdgeRef&);

  // parent mesh
  const ON_Mesh* m_mesh;
  
  // m_mesh->m_top.m_tope[] index
  int m_top_ei; 

  /*
  Description:
    Override of the virtual ON_Geometry::ComponentIndex().
  Returns:
    A mesh component index for the edge.  The type is
    ON_COMPONENT_INDEX::meshtop_edge and the index is the
    index into the ON_MeshTopology.m_tope[] array.
  */
  ON_COMPONENT_INDEX ComponentIndex() const;

  /*
  Returns:
    The mesh topology associated with this 
    mesh edge reference or NULL if it doesn't
    exist.
  */

  const ON_MeshTopology* MeshTopology() const;
  /*
  Returns:
    The 3d location of the mesh edge.  Returns
    ON_UNSET_POINT,ON_UNSET_POINT, is this ON_MeshEdgeRef
    is not valid.
  */
  ON_Line Line() const;

  /*
  Returns:
    The mesh topology edge associated with this 
    mesh edge reference.
  */
  const ON_MeshTopologyEdge* MeshTopologyEdge() const;

  // overrides of virtual ON_Object functions
  ON_BOOL32 IsValid( ON_TextLog* text_log = NULL ) const;
  void Dump( ON_TextLog& ) const;
  unsigned int SizeOf() const;
  ON::object_type ObjectType() const;

  // overrides of virtual ON_Geometry functions
  int Dimension() const;
  ON_BOOL32 GetBBox(
         double* boxmin,
         double* boxmax,
         int bGrowBox = false
         ) const;
  ON_BOOL32 Transform( 
         const ON_Xform& xform
         );
};

class ON_CLASS ON_MeshFaceRef : public ON_Geometry
{
  ON_OBJECT_DECLARE(ON_MeshFaceRef);
public:
  ON_MeshFaceRef();
  ~ON_MeshFaceRef();
  ON_MeshFaceRef& operator=(const ON_MeshFaceRef&);

  // parent mesh
  const ON_Mesh* m_mesh;

  // m_mesh->m_F[] and m_mesh->m_top.m_tope[] index.
  int m_mesh_fi; 

  /*
  Description:
    Override of the virtual ON_Geometry::ComponentIndex().
  Returns:
    A mesh component index for the face.  The type is
    ON_COMPONENT_INDEX::mesh_face and the index is the
    index into the ON_Mesh.m_F[] array.
  */
  ON_COMPONENT_INDEX ComponentIndex() const;

  /*
  Returns:
    The mesh topology associated with this 
    mesh face reference or NULL if it doesn't
    exist.
  */
  const ON_MeshTopology* MeshTopology() const;

  /*
  Returns:
    The mesh face associated with this mesh face reference.
  */
  const ON_MeshFace* MeshFace() const;

  /*
  Returns:
    The mesh topology face associated with this 
    mesh face reference.
  */
  const ON_MeshTopologyFace* MeshTopologyFace() const;

  // overrides of virtual ON_Object functions
  ON_BOOL32 IsValid( ON_TextLog* text_log = NULL ) const;
  void Dump( ON_TextLog& ) const;
  unsigned int SizeOf() const;
  ON::object_type ObjectType() const;

  // overrides of virtual ON_Geometry functions
  int Dimension() const;
  ON_BOOL32 GetBBox(
         double* boxmin,
         double* boxmax,
         int bGrowBox = false
         ) const;
  ON_BOOL32 Transform( 
         const ON_Xform& xform
         );
};

/*
Description:
  Calculate a quick and dirty polygon mesh approximation
  of a surface.
Parameters:
  surface - [in]
  mesh_density - [in] If <= 10, this number controls
        the relative polygon count.  If > 10, this number
        specifies a target number of polygons.
  mesh - [in] if not NULL, the polygon mesh will be put
              on this mesh.
Returns:
  A polygon mesh approximation of the surface or NULL
  if the surface could not be meshed.
*/
ON_DECL
ON_Mesh* ON_MeshSurface( 
            const ON_Surface& surface, 
            int mesh_density = 0,
            ON_Mesh* mesh = 0
            );

/*
Description:
  Calculate a quick and dirty polygon mesh approximation
  of a surface.
Parameters:
  surface - [in]
  u_count - [in] >= 2 Number of "u" parameters in u[] array.
  u       - [in] u parameters
  v_count - [in] >= 2 Number of "v" parameters in v[] array.
  v       - [in] v parameters
  mesh - [in] if not NULL, the polygon mesh will be put
              on this mesh.
Returns:
  A polygon mesh approximation of the surface or NULL
  if the surface could not be meshed.
*/
ON_DECL
ON_Mesh* ON_MeshSurface( 
            const ON_Surface& surface, 
            int u_count,
            const double* u,
            int v_count,
            const double* v,
            ON_Mesh* mesh = 0
            );

/*
Description:
  Finds the barycentric coordinates of the point on a 
  triangle that is closest to P.
Parameters:
  A - [in] triangle corner
  B - [in] triangle corner
  C - [in] triangle corner
  P - [in] point to test
  a - [out] barycentric coordinate
  b - [out] barycentric coordinate
  c - [out] barycentric coordinate
        If ON_ClosestPointToTriangle() returns true, then
        (*a)*A + (*b)*B + (*c)*C is the point on the 
        triangle's plane that is closest to P.  It is 
        always the case that *a + *b + *c = 1, but this
        function will return negative barycentric 
        coordinate if the point on the plane is not
        inside the triangle.
Returns:
  True if the triangle is not degenerate.  False if the
  triangle is degenerate; in this case the returned
  closest point is the input point that is closest to P.
*/
ON_DECL
bool ON_ClosestPointToTriangle( 
        ON_3dPoint A, ON_3dPoint B, ON_3dPoint C,
        ON_3dPoint P,
        double* a, double* b, double* c
        );


/*
Description:
  Finds the barycentric coordinates of the point on a 
  triangle that is closest to P.
Parameters:
  A - [in] triangle corner
  B - [in] triangle corner
  C - [in] triangle corner
  P - [in] point to test
  a - [out] barycentric coordinate
  b - [out] barycentric coordinate
  c - [out] barycentric coordinate
        If ON_ClosestPointToTriangle() returns true, then
        (*a)*A + (*b)*B + (*c)*C is the point on the 
        triangle's plane that is closest to P.  It is 
        always the case that *a + *b + *c = 1, but this
        function will return negative barycentric 
        coordinate if the point on the plane is not
        inside the triangle.
Returns:
  True if the triangle is not degenerate.  False if the
  triangle is degenerate; in this case the returned
  closest point is the input point that is closest to P.
*/
ON_DECL
bool ON_ClosestPointToTriangleFast( 
          const ON_3dPoint& A, 
          const ON_3dPoint& B, 
          const ON_3dPoint& C, 
          ON_3dPoint P,
          double* a, double* b, double* c
          );


/*
Description:
  Calculate a mesh representation of the NURBS surface's control polygon.
Parameters:
  nurbs_surface - [in]
  bCleanMesh - [in] If true, then degenerate quads are cleaned
                    up to be triangles. Surfaces with singular
                    sides are a common source of degenerate qauds.
  input_mesh - [in] If NULL, then the returned mesh is created
       by a class to new ON_Mesh().  If not null, then this 
       mesh will be used to store the conrol polygon.
Returns:
  If successful, a pointer to a mesh.
*/
ON_DECL
ON_Mesh* ON_ControlPolygonMesh( 
          const ON_NurbsSurface& nurbs_surface, 
          bool bCleanMesh,
          ON_Mesh* input_mesh = NULL
          );

/*
Description:
  Finds the intersection between a line segment an a triangle.
Parameters:
  A - [in] triangle corner
  B - [in] triangle corner
  C - [in] triangle corner
  P - [in] start of line segment
  Q - [in] end of line segment
  abc - [out] 
     barycentric coordinates of intersection point(s)
  t - [out] line coordinate of intersection point(s)
Returns:
  0 - no intersection
  1 - one intersection point
  2 - intersection segment
*/
ON_DECL
int ON_LineTriangleIntersect(
        const ON_3dPoint& A,
        const ON_3dPoint& B,
        const ON_3dPoint& C,
        const ON_3dPoint& P,
        const ON_3dPoint& Q,
        double abc[2][3], 
        double t[2],
        double tol
        );

/*
Description:
  Finds the unit normal to the triangle
Parameters:
  A - [in] triangle corner
  B - [in] triangle corner
  C - [in] triangle corner
Returns:
  Unit normal
*/
ON_DECL
ON_3dVector ON_TriangleNormal(
        const ON_3dPoint& A,
        const ON_3dPoint& B,
        const ON_3dPoint& C
        );

/*
Description:
  Triangulate a 2D simple closed polygon.
Parameters:
  point_count - [in] number of points in polygon ( >= 3 )
  point_stride - [in]
  P - [in] 
    i-th point = (P[i*point_stride], P[i*point_stride+1])
  tri_stride - [in]
  triangle - [out]
    array of (point_count-2)*tri_stride integers
Returns:
  True if successful.  In this case, the polygon is trianglulated into 
  point_count-2 triangles.  The indices of the 3 points that are the 
  corner of the i-th (0<= i < point_count-2) triangle are
    (triangle[i*tri_stride], triangle[i*tri_stride+1], triangle[i*tri_stride+2]).
Remarks:
  Do NOT duplicate the start/end point; i.e., a triangle will have
  a point count of 3 and P will specify 3 distinct non-collinear points.
*/
ON_DECL
bool ON_Mesh2dPolygon( 
          int point_count,
          int point_stride,
          const double* P,
          int tri_stride,
          int* triangle 
          );

/*
Description:
  Fill in a 2d region with triangles.
Parameters:
  point_count - [in] number of 2d points.
  point_stride - [in] i-th point = (point[j],point[j+1]), where
                      j = i*point_stride.
  point - [in] 2d point locations.  It is ok to include points that are inside the region
               but not at the ednd of an edge.  Duplicate points are not permitted.
  edge_count - [in] number of edges (if 0, then the input list of point
                    is treated as a counterclockwise closed polyline.
  edge_stride - [in] i-th edge connects points (edge[j],edge[j+1]) where
                     j = i*edge_stride.
  edge - [in] indices of edge ends.  Edges can intersect only at shared end points.
  edge_side - [in] if NULL, the triangles are built on the left side
                   of the edges.  If not NULL, then
                   edge[i] determines which side(s) of the edge need
                   triangles.  1 = left side only, 2 = right side only, 3 = both sides
  triangles - [out]  triangles are appended to this list.  The (i,j,k) are
                     vertex indices.
Returns:
  Number of triangles appended to triangles[] array.
*/
ON_DECL
int ON_Mesh2dRegion(
          int point_count,
          int point_stride,
          const double* point,
          int edge_count,
          int edge_stride,
          const int* edge,
          const int* edge_side,
          ON_SimpleArray<ON_3dex>& triangles
          );

#endif


