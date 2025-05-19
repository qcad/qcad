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

// ON_Leader class
#ifndef OPENNURBS_LEADER_H_INCLUDED
#define OPENNURBS_LEADER_H_INCLUDED


class ON_CLASS ON_Leader : public ON_Annotation
{
  ON_OBJECT_DECLARE(ON_Leader);

public:
  ON_Leader();
  ~ON_Leader();

  ON_Leader(const ON_Leader& src);
  ON_Leader& operator=(const ON_Leader& src);

  static const ON_Leader Empty;

private:
  void Internal_Destroy();
  void Internal_CopyFrom(const ON_Leader& src);

public:

  /*
  Parameters:
    dimstyle - [in]
      If you want to specify text appearance or other custom properties ...
      ON_DimStyle style = ON_DimStyle::DimStyleFromProperties( doc->DimStyleContext().CurrentDimStyle(), ... );
      style.Set...(...);
      Then pass &style

  Remarks:
    Parses text string and makes runs
  */
  bool Create(
    const wchar_t* leader_text,
    const ON_DimStyle* dimstyle,
    int point_count,
    const ON_3dPoint* points,
    const ON_Plane& plane,
    bool bWrapped,
    double rect_width
    );

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
  void Dump(ON_TextLog& log) const override;
  bool Write(ON_BinaryArchive& file) const override;
  bool Read(ON_BinaryArchive& file) override;
  ON::object_type ObjectType() const override;

  /*
  Description:
    Create a V6 leader from a V5 leader. 
    The function is used when reading V5 files.
  Parameters:
    v5_leader -[in]
    dim_style - [in]
      Dimstyle referenced by v5_leader or nullptr if not available.
    destination - [in]
      If destination is not nullptr, then the V6 leader is constructed
      in destination. If destination is nullptr, then the new V6 leader
      is allocated with a call to new ON_Leader().
  */
  static ON_Leader* CreateFromV5Leader(
    const class ON_OBSOLETE_V5_Leader& V5_leader,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_Leader* destination
  );
  
  int Dimension() const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  bool GetAnnotationBoundingBox(
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    double* boxmin,
    double* boxmax,
    bool bGrow = false
  ) const override; // ON_Annotation override

  bool Transform(const ON_Xform& xform) override;

  bool GetTextGripPoints(
    ON_2dPoint& base,
    ON_2dPoint& width,
    const ON_DimStyle* dimstyle,
    double textscale) const;

  //bool Explode(
  //  const ON_DimStyle* dimstyle,
  //  ON_SimpleArray<const ON_Geometry*> object_parts) const;

  // Transforms text from natural position at origin to 
  // 3d location as it displays in the leader
  bool GetTextXform(
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    ON_Xform& text_xform_out
  ) const override;

  bool GetTextXform(
    const ON_Xform* model_xform,
    const ON_Viewport* vp,
    const ON_DimStyle* dimstyle,
    double dimscale,
    ON_Xform& text_xform_out
  ) const;
  
  void UpdateTextAlignment(ON_2dVector angle); // Sets text to right or left justified per leader direction

  const ON_NurbsCurve* Curve(
    const ON_DimStyle* dimstyle
    ) const; // cached curve for display and picking
  void DeleteCurve() const;

  void SetPlane(ON_Plane plane);

  //// TailDirection is the tangent direction 
  //// of the end of the leader tail
  //// Returns 1,0 if there isn't a tangent
  ON_2dVector TailDirection(const ON_DimStyle* dimstyle) const;

  // These do nothing and return false if 
  // HasLanding is false
  // Otherwise, they return a line added to the 
  // tail of the leader in the direction of
  // LeaderContentAngleStyle()
  bool LandingLine2d(
    const ON_DimStyle* style,
    double dimscale,
    ON_Line& line) const;
  bool LandingLine3d(
    const ON_DimStyle* style,
    double dimscale,
    ON_Line& line) const;

  ON__UINT32 PointCount() const;
  void SetPoints2d(int count, const ON_2dPoint* points);
  void SetPoints3d(int count, const ON_3dPoint* points);
  bool SetPoint2d(int idx, ON_2dPoint point);
  bool SetPoint3d(int idx, ON_3dPoint point);
  void InsertPoint2d(int atidx, ON_2dPoint point);
  void InsertPoint3d(int atidx, ON_3dPoint point);
  void AppendPoint2d(ON_2dPoint point);
  bool AppendPoint3d(ON_3dPoint point);
  void RemovePoint(int idx);
  bool Point2d(int idx, ON_2dPoint& point) const;
  bool Point3d(int idx, ON_3dPoint& point) const;

  bool GetTextPoint2d(
    const ON_DimStyle* dimstyle, 
    double leaderscale,
    ON_2dPoint& point) const;
  //bool GetTextPoint3d(ON_3dPoint& point) const;
  ON_2dPointArray& Points2d();
  const ON_2dPointArray& Points2d() const;

  void InvalidateTextPoint();
  bool UpdateTextPosition(
    const ON_DimStyle* dimstyle,
    double leaderscale);

private:
  ON_2dPointArray         m_points;

  // runtime
  mutable ON_NurbsCurve* m_curve = nullptr;            // Deleted by ~ON_Leader()
  mutable ON_2dPoint     m_text_point = ON_2dPoint::UnsetPoint;
};



#endif

