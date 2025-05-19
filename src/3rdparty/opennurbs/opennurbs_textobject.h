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

// ON_Table class
#ifndef OPENNURBS_TEXTOBJECT_H_INCLUDED
#define OPENNURBS_TEXTOBJECT_H_INCLUDED

class ON_CLASS ON_Text : public ON_Annotation
{
  ON_OBJECT_DECLARE(ON_Text);

public:
  static const ON_Text Empty;

  ON_Text();
  ~ON_Text();

  ON_Text(const ON_Text& src);
  ON_Text& operator=(const ON_Text& src);

public:

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  // Parses text string and makes runs
  bool Create(
    const wchar_t* RtfString,
    const ON_DimStyle* dimstyle,
    ON_Plane plane,
    bool bWrapped,
    double rect_width,
    double text_rotation_radians
    );

  // Parses text string and makes runs - wrapped = false, rotation = 0
  bool Create(
    const wchar_t* RtfString,
    const ON_DimStyle* dimstyle,
    ON_Plane plane
    );

  void Destroy();

  // virtual
  void Dump(ON_TextLog&) const override; // for debugging

  bool Write(
    ON_BinaryArchive&  // serialize definition to binary archive
    ) const override;

  bool Read(
    ON_BinaryArchive&  // restore definition from binary archive
    ) override;

  int Dimension() const override;

  /*
  Description:
    Create a V5 text object from a V6 text object. 
    The function is used when reading V5 files.
  Parameters:
    v5_text_object -[in]
    dimstyle - [in]
      Dimstyle referenced by v5_text_object or nullptr if not available.
    destination - [in]
      If destination is not nullptr, then the V6 text object is constructed
      in destination. If destination is nullptr, then the new V6 text object
      is allocated with a call to new ON_Text().
  */
  static ON_Text* CreateFromV5TextObject(
    const class ON_OBSOLETE_V5_TextObject& V5_text_object,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_Text* destination
  );

  //bool Explode(
  //  const ON_DimStyle* dimstyle,
  //  ON_SimpleArray<const ON_Geometry*> object_parts) const;



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

  /*
  Description:
  Transform the object by a 4x4 xform matrix and change text height
  override to accommodate scaling in the transform if necessary
  Parameters:
  [in] xform  - An ON_Xform with the transformation information
  Returns:
  true = Success
  false = Failure
  Remarks:
  The object has been transformed when the function returns
  If the scale changed because of the transform, an override for text height
  is either changed, if one already was in place, or is added.
  */
  bool Transform(const ON_Xform& xform, const ON_DimStyle* dimstyle);

  // Transforms text from natural position at origin to 
  // 3d location as it displays in the text object
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

  // returns the base point and with grip using the current alignments
  bool GetGripPoints(ON_2dPoint& base, ON_2dPoint& width, double textscale) const;

private:
  void Internal_SetObsoleteV5TextObjectInformation(
    const class ON_3dmAnnotationContext* annotation_context,
    const class ON_OBSOLETE_V5_TextObject& V5_text_object
  );
  public:
    bool GetTextXform(
      const ON_Xform* model_xform,
      const ON_3dVector view_x,
      const ON_3dVector view_y,
      const ON_3dVector view_z,
      ON::view_projection projection,
      bool bDrawForward,
      const ON_DimStyle* dimstyle,
      double dimscale,
      ON_Xform& text_xform_out
    ) const;

};

#endif

