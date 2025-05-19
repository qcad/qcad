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

#if !defined(ON_OBJECT_HISTORY_INC_)
#define ON_OBJECT_HISTORY_INC_

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray< class ON_Value* >;
#endif

class ON_CLASS ON_CurveProxyHistory
{
public:
  // Used to save information needed to create an ON_CurveProxy
  // reference in history records.
  ON_CurveProxyHistory();
  ~ON_CurveProxyHistory();
  ON_CurveProxyHistory(const ON_CurveProxyHistory&) = default;
  ON_CurveProxyHistory& operator=(const ON_CurveProxyHistory&) = default;

  ON_ObjRef m_curve_ref;                // from ON_CurveProxy.m_real_curve
  bool      m_bReversed;                // from ON_CurveProxy.m_bReversed
  ON_Interval m_full_real_curve_domain; // from ON_CurveProxy.m_real_curve.Domain()
  ON_Interval m_sub_real_curve_domain;  // from ON_CurveProxy.m_real_curve_domain
  ON_Interval m_proxy_curve_domain;     // from ON_CurveProxy.m_this_domain

  // If these are empty intervals, they are from old files. Ignore them.
  ON_Interval m_segment_edge_domain;
  ON_Interval m_segment_trim_domain;

  void Destroy();
  bool Write( ON_BinaryArchive& ) const;
  bool Read( ON_BinaryArchive& );
  void Dump( ON_TextLog& ) const;

private:
  ON__UINT8 m_reserved[32];
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_ClassArray<ON_CurveProxyHistory>;
#endif

class ON_CLASS ON_PolyEdgeHistory
{
public:
  // Used to save information needed to create an CRhinoPolyEdge
  // reference in history records.
  ON_PolyEdgeHistory();
  ~ON_PolyEdgeHistory();

  void Destroy();
  bool Write( ON_BinaryArchive& ) const;
  bool Read( ON_BinaryArchive& );
  void Dump( ON_TextLog& ) const;

  ON_ClassArray< ON_CurveProxyHistory > m_segment;
  ON_SimpleArray<double> m_t;
  int m_evaluation_mode;
private:
  ON__UINT8 m_reserved[64];
};

class ON_CLASS ON_HistoryRecord : public ON_ModelComponent
{
  ON_OBJECT_DECLARE(ON_HistoryRecord);
public:
  static const ON_HistoryRecord Empty;

public:
  ON_HistoryRecord() ON_NOEXCEPT;
  ~ON_HistoryRecord();
  ON_HistoryRecord(const ON_HistoryRecord& src);
  ON_HistoryRecord& operator=(const ON_HistoryRecord& src);

private:
  void Internal_Destroy();
  void Internal_Copy(
    const ON_HistoryRecord& src
    );

public:
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
  void Dump( ON_TextLog& ) const override;
  bool Write(ON_BinaryArchive& binary_archive) const override;
  bool Read(ON_BinaryArchive& binary_archive) override;

private:
  bool Internal_WriteV5(ON_BinaryArchive& binary_archive) const;
private:
  bool Internal_ReadV5(ON_BinaryArchive& binary_archive);

public:
  void DestroyValue( int value_id );

  /*
  Description:
    For setting values.
  Parameters:
    value_id - [in]
      If there a value with the same input
      id exists, the old value is replaced.
    count - [in]
      Number of values
    b - [in]
      array of count bools
    i - [in]
      array of count ints
    x - [in]
      array of count doubles
    p - [in]
      array of count 3d points
    v - [in]
      array of count 3d vectors
    xform - [in]
      array of count xforms
    c - [in]
      array of count colors
    or - [in]
      array of count object references
    g - [in]
      array of count geometry pointers
    u - [in]
      array of uuids
    s - [in]
      string
  */
  bool SetBoolValue(     int value_id, bool b);
  bool SetIntValue(      int value_id, int i);
  bool SetDoubleValue(   int value_id, double x);
  bool SetPointValue(    int value_id, ON_3dPoint p);
  bool SetVectorValue(   int value_id, ON_3dVector v);
  bool SetXformValue(    int value_id, ON_Xform xform);
  bool SetColorValue(    int value_id, ON_Color c);
  bool SetObjRefValue(   int value_id, const ON_ObjRef& oref);
  bool SetPointOnObjectValue( int value_id, const ON_ObjRef& oref, ON_3dPoint point );
  bool SetUuidValue(     int value_id, ON_UUID uuid );
  bool SetStringValue(   int value_id, const wchar_t* s );
  /*
  Parameters:
    edge_chain - [in]
      edge_chain.PersistentSubDId() must be non-nil and identify the parent subd in the model.
      If the model is an ONX_Model, then the persistent id is the ON_ModelGeometryComponent.Id().
      If the model is a CRhinoDoc, then the persistent id is CRhinoObject.ModelObjectId().
  */
  bool SetSubDEdgeChainValue(int value_id, const ON_SubDEdgeChain& edge_chain);
  bool SetGeometryValue( int value_id, ON_Geometry* g);
  bool SetPolyEdgeValue( int value_id, const ON_PolyEdgeHistory& polyedge );

  /*
  Description:
    For setting values.
  Parameters:
    value_id - [in]
      If there a value with the same input
      id exists, the old value is replaced.
    count - [in]
      Number of values
    b - [in]
      array of count bools
    i - [in]
      array of count ints
    x - [in]
      array of count doubles
    P - [in]
      array of count 3d points
    V - [in]
      array of count 3d vectors
    xform - [in]
      array of count xforms
    c - [in]
      array of count colors
    or - [in]
      array of count object references
    g - [in]
      array of count geometry pointers
    u - [in]
      array of uuids
    s - [in]
      array of strings
  */
  bool SetBoolValues(     int value_id, int count, const bool* b);
  bool SetIntValues(      int value_id, int count, const int* i);
  bool SetDoubleValues(   int value_id, int count, const double* x);
  bool SetPointValues(    int value_id, int count, const ON_3dPoint* P);
  bool SetVectorValues(   int value_id, int count, const ON_3dVector* V);
  bool SetXformValues(    int value_id, int count, const ON_Xform* xform);
  bool SetColorValues(    int value_id, int count, const ON_Color* c);
  bool SetObjRefValues(   int value_id, int count, const ON_ObjRef* oref);
  bool SetUuidValues(     int value_id, int count, const ON_UUID* u );
  bool SetStringValues(   int value_id, int count, const wchar_t* const* s );
  bool SetStringValues(   int value_id, const ON_ClassArray<ON_wString>& s );
  bool SetGeometryValues( int value_id, const ON_SimpleArray<ON_Geometry*> a);
  /*
  Parameters:
    edge_chain - [in]
      edge_chain.PersistentSubDId() must be non-nil and identify the parent subd in the model.
      If the model is an ONX_Model, then the persistent id is the ON_ModelGeometryComponent.Id().
      If the model is a CRhinoDoc, then the persistent id is CRhinoObject.ModelObjectId().
  */
  bool SetSubDEdgeChainValues(int value_id, const ON_ClassArray<ON_SubDEdgeChain>& edge_chains);
  bool SetSubDEdgeChainValues(int value_id, const ON_SimpleArray<const ON_SubDEdgeChain*>& edge_chains);
  bool SetPolyEdgeValues(int value_id, int count, const ON_PolyEdgeHistory* a);

  /*
  Description:
    For retrieving values.
  */
  bool GetStringValue( int value_id, ON_wString& str ) const;
  bool GetBoolValue( int value_id, bool* b ) const;
  bool GetIntValue( int value_id, int* i ) const;
  bool GetDoubleValue( int value_id, double* number ) const;
  bool GetPointValue( int value_id, ON_3dPoint& point ) const;
  bool GetVectorValue( int value_id, ON_3dVector& point ) const;
  bool GetXformValue( int value_id, ON_Xform& point ) const;
  bool GetColorValue( int value_id, ON_Color* color ) const;
  bool GetObjRefValue( int value_id, ON_ObjRef& oref ) const;
  bool GetPointOnObjectValue( int value_id, ON_ObjRef& oref ) const;
  bool GetCurveValue( int value_id, const ON_Curve*& ) const;
  bool GetSurfaceValue( int value_id, const ON_Surface*& ) const;
  bool GetBrepValue( int value_id, const ON_Brep*& ) const;
  bool GetMeshValue( int value_id, const ON_Mesh*& ) const;
  bool GetGeometryValue( int value_id, const ON_Geometry*& ) const;
  bool GetSubDEdgeChainValue(int value_id, const ON_SubDEdgeChain*& edge_chain) const;
  bool GetUuidValue( int value_id, ON_UUID* uuid ) const;
  bool GetPolyEdgeValue( int value_id, const ON_PolyEdgeHistory*& polyedge ) const;

  int GetStringValues( int value_id, ON_ClassArray<ON_wString>& string ) const;
  int GetBoolValues( int value_id, ON_SimpleArray<bool>& ) const;
  int GetIntValues( int value_id, ON_SimpleArray<int>& ) const;
  int GetDoubleValues( int value_id, ON_SimpleArray<double>& ) const;
  int GetPointValues( int value_id, ON_SimpleArray<ON_3dPoint>& ) const;
  int GetVectorValues( int value_id, ON_SimpleArray<ON_3dVector>& ) const;
  int GetXformValues( int value_id, ON_SimpleArray<ON_Xform>& ) const;
  int GetColorValues( int value_id, ON_SimpleArray<ON_Color>& ) const;
  int GetObjRefValues( int value_id, ON_ClassArray<ON_ObjRef>& objects ) const;
  int GetGeometryValues( int value_id, ON_SimpleArray<const ON_Geometry*>& ) const;
  int GetSubDEdgeChainValues(int value_id, ON_SimpleArray<const ON_SubDEdgeChain*>& edge_chains) const;
  int GetUuidValues( int value_id, ON_SimpleArray<ON_UUID>& ) const;
  int GetPolyEdgeValues( int value_id, ON_SimpleArray<const ON_PolyEdgeHistory*>& ) const;

  /*
  Description:
    Determine if object is an antecedent (input) in this
    history record.
  Parameters:
    object_uuid - [in] 
  Returns:
    Returns true if object_uuid is the id of an input
    object.
  */
  bool IsAntecedent( ON_UUID object_uuid ) const;


  /*
  Description:
    Print a list of the values in text_log.
  Parameters:
    text_log - [in]
  Returns:
    Number of values listed.
  */
  int ValueReport( ON_TextLog& text_log ) const;

  // CRhinoCommand::CommandId() value of the command that
  // created this history record.  Each time the command
  // is run, it can create a history record.
  ON_UUID m_command_id = ON_nil_uuid;

  // A YYYYMMDDn version number that gets updated when
  // a command changes.  This version is checked so that
  // new versions of a command's ReplayHistory don't 
  // attempt to use information saved in old files.
  int m_version = 0;

  enum class RECORD_TYPE : unsigned int
  {
    history_parameters = 0, // parameters for UpdateHistory
    feature_parameters = 1  // parameters for a feature
  };

  RECORD_TYPE m_record_type = ON_HistoryRecord::RECORD_TYPE::history_parameters;

  /*
  Description:
    Convert integer into an ON_HistoryRecord::RECORD_TYPE.
  Parameters:
    i - [in]
  Returns:
    ON_HistoryRecord::RECORD_TYPE enum with same value as i.
  */
  static
  ON_HistoryRecord::RECORD_TYPE RecordType(int i);

  // List of object id values of antecedent objects that 
  // are referenced in the list of input events in m_value[].
  // These were the command's "input" objects.
  ON_UuidList m_antecedents;

  // List of object id values of descendant objects that 
  // were created.  These were the command's "output" objects 
  ON_UuidList m_descendants;

  // Information needed to update the descendant objects
  // when an antecedent object is modified.
  ON_SimpleArray< class ON_Value* > m_value;

  /*
  Description:
    This tool is used in rare situations when the object ids 
    stored in the uuid list need to be remapped.
  Parameters:
    uuid_remap - [in]
      Is it critical that uuid_remap[] be sorted with respect
      to ON_UuidPair::CompareFirstUuid.
  */
  void RemapObjectIds( const ON_SimpleArray<ON_UuidPair>& uuid_remap );

  /*
  12 May, 2015 - Lowell
  When an object is replaced and the old object has a history record with
  CopyOnReplaceObject() set to tru, then history record is copied and 
  attached to the new object.
  That allows a descendant object to continue the history linkage after 
  it is edited.  
  See http://mcneel.myjetbrains.com/youtrack/issue/RH-30399
  */
  bool CopyOnReplaceObject() const;

  void SetCopyOnReplaceObject(
    bool bCopyOnReplaceObject
    );

private:
  bool m_bValuesSorted = true;
  bool m_bCopyOnReplaceObject = false;
  ON_Value* FindValueHelper( int, int, bool ) const;
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_HistoryRecord*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<const ON_HistoryRecord*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_ObjectArray<ON_HistoryRecord>;
#endif

#endif
