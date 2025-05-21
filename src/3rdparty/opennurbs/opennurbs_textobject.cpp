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
////////////////////////////////////////////////////////////////

#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

ON_OBJECT_IMPLEMENT(ON_Text, ON_Annotation, "57376349-62A9-4A16-B411-A46BCD544790");

//-----------------------------------------------------------------

ON_Text::ON_Text()
  : ON_Annotation(ON::AnnotationType::Text)
{}

ON_Text::~ON_Text()
{}

// Duplicates text string and runs
ON_Text& ON_Text::operator=(const ON_Text& src)
{
  if (this != &src)
  {
    ON_Annotation::operator=(src);
  }
  return *this;
}

ON_Text::ON_Text(const ON_Text& src)
  : ON_Annotation(src)
{}

bool ON_Text::Create(
  const wchar_t* RtfString,
  const ON_DimStyle* dimstyle,
  ON_Plane plane,
  bool bWrapped,
  double rect_width,
  double text_rotation_radians
)
{
  // Parse string, create runs, find font, set plane & height
  SetPlane(plane);

  dimstyle = &ON_DimStyle::DimStyleOrDefault(dimstyle);

  SetDimensionStyleId(*dimstyle);

  ON_TextContent* text = nullptr;
  if (nullptr == RtfString || 0 == RtfString[0])
    RtfString = L"";
  if (nullptr != RtfString)
  {
    text = new ON_TextContent;
    if (!text->Create( RtfString, Type(), dimstyle, bWrapped, rect_width, text_rotation_radians))
    {
      delete text;
      text = 0;
      return false;
    }
  }
  SetText(text);
  return true;
}

bool ON_Text::Create(
  const wchar_t* RtfString,
  const ON_DimStyle* dimstyle,
  ON_Plane plane
)
{
  bool bWrapped = false;
  const double rect_width = ON_TextContent::Empty.FormattingRectangleWidth();
  const double text_rotation_radians = ON_TextContent::Empty.TextRotationRadians();
  return Create(
    RtfString,
    dimstyle,
    plane,
    bWrapped,
    rect_width,
    text_rotation_radians
  );
}

static bool ON_V6_TextObject_IsNotIsValid()
{
  return false; // <- breakpoint here to detect invalid ON_TextContent objects.
}

bool ON_Text::IsValid(ON_TextLog* text_log) const
{
  bool rc = true;
  if (!m_plane.IsValid())
    rc = ON_V6_TextObject_IsNotIsValid();
  else if (ON_nil_uuid == m_dimstyle_id)
    rc = ON_V6_TextObject_IsNotIsValid();
  else if (nullptr == m_text || !m_text->IsValid())
    rc = ON_V6_TextObject_IsNotIsValid();
  return rc;
}

// virtual
void ON_Text::Dump(ON_TextLog& text_log) const // for debugging
{}

bool ON_Text::Write(
  ON_BinaryArchive&  archive
) const
{
  const int content_version = 0;
  if (false == archive.BeginWrite3dmAnonymousChunk(content_version))
    return false;
  bool rc = false;
  for (;;)
  {
    if (false == ON_Annotation::Internal_WriteAnnotation(archive))
      break;
    rc = true;
    break;
  }
  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

bool ON_Text::Read(
  ON_BinaryArchive&  archive
)
{
  *this = ON_Text::Empty;

  int content_version = 0;
  if (false == archive.BeginRead3dmAnonymousChunk(&content_version))
    return false;

  bool rc = false;
  for (;;)
  {
    if (false == ON_Annotation::Internal_ReadAnnotation(archive))
      break;
    rc = true;
    break;
  }
  if (!archive.EndRead3dmChunk())
    rc = false;
  return rc;
}

int ON_Text::Dimension() const
{
  return 3;
}

// ON_Geometry override
bool ON_Text::GetBBox( // returns true if successful
  double* bbox_min,       // boxmin[dim]
  double* bbox_max,       // boxmax[dim]
  bool grow          // true means grow box
) const
{
  return GetAnnotationBoundingBox(nullptr, nullptr, 1.0, bbox_min, bbox_max, grow ? true : false);
}


// ON_Annotation override
bool ON_Text::GetAnnotationBoundingBox(
  const ON_Viewport* vp,
  const ON_DimStyle* dimstyle,
  double dimscale,
  double* boxmin,
  double* boxmax,
  bool bGrow
) const
{
  if (nullptr == dimstyle)
    dimstyle = &ON_DimStyle::Default;

  const ON_SHA1_Hash hash = Internal_GetBBox_InputHash(
    vp, 
    dimstyle, 
    dimscale, 
    ON_2dPoint::Origin,
    0,
    nullptr
  );

  if (Internal_GetBBox_Begin(hash, boxmin, boxmax, bGrow))
    return true;

  if (nullptr == boxmin || nullptr == boxmax)
    return false;

  ON_BoundingBox bbox;
  Internal_GetBBox_TextGlyphBox(
    vp,
    dimstyle,
    dimscale,
    bbox
  );

  // There is no other geometry on ON_Text

  return Internal_GetBBox_End(bbox, hash, boxmin, boxmax, bGrow);
}

bool ON_Text::Transform(const ON_Xform& xform, const ON_DimStyle* parent_dimstyle)
{
  ON_3dVector Y = Plane().Yaxis();
  Y.Transform(xform);
  double scale = Y.Length();
  bool rc = Transform(xform);
  if (rc && ON_ZERO_TOLERANCE < fabs(scale - 1.0))
  {
    double oldheight = TextHeight(parent_dimstyle);
    double newheight = oldheight * scale;
    SetTextHeight(parent_dimstyle, newheight);
    oldheight = MaskBorder(parent_dimstyle);
    newheight = oldheight * scale;
    SetMaskBorder(parent_dimstyle, newheight);
  }
  return rc;
}

bool ON_Text::Transform(const ON_Xform& xform)
{
  bool rc = ON_Geometry::Transform(xform);
  if (rc)
    rc = m_plane.Transform(xform);
  if (rc)
  {
    ON_TextContent* text = this->Text();
    if (nullptr != text && text->TextIsWrapped())
    {
      double w = text->FormattingRectangleWidth();
      ON_3dVector x = m_plane.xaxis;
      if (x.Unitize())
      {
        double r = text->TextRotationRadians();
        x.Rotate(r, m_plane.zaxis);
        x.Transform(xform);
        w *= x.Length();
        text->SetFormattingRectangleWidth(w);
      }
    }
  }
  return rc;
}

// returns the base point and width grip using the current alignments
bool ON_Text::GetGripPoints(ON_2dPoint& base, ON_2dPoint& width, double textscale) const
{
  const ON_TextContent* text = Text();
  if (nullptr == text)
    return false;

  ON_2dPoint p[4];
  if (!text->Get2dCorners(p))
    return false;

  ON::TextHorizontalAlignment halign;
  ON::TextVerticalAlignment valign;
  GetAlignment(halign, valign);
  base = ON_2dPoint::Origin;
  width = (p[1] + p[2]) / 2.0;
  if (ON::TextHorizontalAlignment::Right == halign)
    width = (p[0] + p[3]) / 2.0;

  width.x *= textscale;
  width.y *= textscale;
  double a = TextRotationRadians();
  width.Rotate(a, ON_2dPoint::Origin);
  return true;
}

bool ON_Text::GetTextXform(
  const ON_Viewport* vp,
  const ON_DimStyle* dimstyle,
  double dimscale,
  ON_Xform& text_xform_out
)const 
{

  return GetTextXform(nullptr, vp, dimstyle, dimscale, text_xform_out);
}

bool ON_Text::GetTextXform(
  const ON_Xform* model_xform,
  const ON_Viewport* vp,
  const ON_DimStyle* dimstyle,
  double dimscale,
  ON_Xform& text_xform_out
) const
{
  ON_3dVector view_x = nullptr == vp ? ON_3dVector::XAxis : vp->CameraX();
  ON_3dVector view_y = nullptr == vp ? ON_3dVector::YAxis : vp->CameraY();
  ON_3dVector view_z = nullptr == vp ? ON_3dVector::ZAxis : vp->CameraZ();
  ON::view_projection projection = vp ? vp->Projection() : ON::view_projection::parallel_view;
  bool bDrawForward = dimstyle == nullptr ? false : dimstyle->DrawForward();
  return GetTextXform(model_xform, view_x, view_y, view_z, projection, bDrawForward, dimstyle, dimscale, text_xform_out);
}

bool ON_Text::GetTextXform(
  const ON_Xform* model_xform,
  const ON_3dVector view_x,
  const ON_3dVector view_y,
  const ON_3dVector view_z,
  ON::view_projection projection,
  bool bDrawForward,
  const ON_DimStyle* dimstyle,
  double dimscale,
  ON_Xform& text_xform_out
) const
{
  if (nullptr == dimstyle)
    return false;
  const ON_TextContent* text = Text();
  if (nullptr == text)
    return false;

  if (DimStyleTextPositionPropertiesHash() != dimstyle->TextPositionPropertiesHash())
  {
    ON_wString rtfstr = text->RtfText();
    ON_Plane objectplane = Plane();
    const_cast<ON_TextContent*>(text)->Create(
      rtfstr, ON::AnnotationType::Text, dimstyle, 
      text->TextIsWrapped(), text->FormattingRectangleWidth(), text->TextRotationRadians());
  }

  text_xform_out = ON_Xform::IdentityTransformation;

  ON_Xform textscale_xf(ON_Xform::DiagonalTransformation(dimscale));
  ON_Xform wcs2obj_xf(ON_Xform::IdentityTransformation);           // WCS plane to leader plane rotation
  const ON_Plane& textobjectplane = Plane();
  wcs2obj_xf.Rotation(ON_Plane::World_xy, textobjectplane);    // Rotate text from starting text plane (wcs) to object plane
  ON_Xform rotation_xf(ON_Xform::IdentityTransformation);

  if ( ON::TextOrientation::InView == dimstyle->TextOrientation() )  // Draw text horizontal and flat to the screen
  {
    ON_Xform tp2sxf;        // Text point to view plane rotation
    ON_3dPoint text_point_3d = Plane().origin;
    const ON_3dVector& text_xdir = textobjectplane.xaxis;
    const ON_3dVector& text_ydir = textobjectplane.yaxis;
    const ON_3dVector& text_zdir = textobjectplane.zaxis;
    ON_3dVector view_xdir = view_x;
    ON_3dVector view_ydir = view_y;
    ON_3dVector view_zdir = view_z;
    if (nullptr != model_xform)
    {
      auto inverse = model_xform->Inverse();
      view_xdir.Transform(inverse);
      view_ydir.Transform(inverse);
      view_zdir.Transform(inverse);
    }
    rotation_xf.Rotation(text_point_3d, text_xdir, text_ydir, text_zdir, text_point_3d, view_xdir, view_ydir, view_zdir);
    text_xform_out = wcs2obj_xf * textscale_xf;
    text_xform_out = rotation_xf * text_xform_out;
    return true;
  }
  else // ON::TextOrientation::InPlane
  {
    double textrotation = TextRotationRadians();
    if (fabs(textrotation) > ON_SQRT_EPSILON)
      rotation_xf.Rotation(textrotation, ON_3dVector::ZAxis, ON_3dPoint::Origin);  // Text rotation
  
    //ON_Xform textcenter_xf(ON_Xform::IdentityTransformation);
    if (bDrawForward)
    {
      // Check if the text is right-reading by comparing
      // text plane x and y, rotated by text rotation angle,
      // to view right and up

      ON_3dPoint text_corners[4] = { ON_3dPoint::Origin, ON_3dPoint::Origin, ON_3dPoint::Origin, ON_3dPoint::Origin };
      ON_3dPoint text_center = ON_3dPoint::Origin;
      if (text->Get3dCorners(text_corners))
      {
        text_center = (text_corners[0] + text_corners[2]) / 2.0;
        ON_3dVector text_xdir = textobjectplane.xaxis;
        ON_3dVector text_ydir = textobjectplane.yaxis;
        ON_3dVector text_zdir = textobjectplane.zaxis;
        if (nullptr != model_xform)
        {
          text_xdir.Transform(*model_xform);
          text_ydir.Transform(*model_xform);
          text_zdir.Transform(*model_xform);
        }
        if (fabs(textrotation) > ON_SQRT_EPSILON)
        {
          text_xdir.Rotate(textrotation, textobjectplane.zaxis);
          text_ydir.Rotate(textrotation, textobjectplane.zaxis);
        }

        bool flip_x = false;
        bool flip_y = false;

        const double fliptol = (projection == ON::view_projection::perspective_view) ? 0.0 : cos(80.001 * ON_DEGREES_TO_RADIANS);
        CalcTextFlip(
          text_xdir, text_ydir, text_zdir,
          view_x, view_y, view_z,
          model_xform,
          fliptol,
          flip_x,
          flip_y);

        ON_Xform mxf;  // Mirror xform for backwards text to adjust DrawForward
        if (flip_x)
        {
          mxf.Mirror(text_center, ON_3dVector::XAxis);
          textscale_xf = textscale_xf * mxf;
        }
        if (flip_y)
        {
          mxf.Mirror(text_center, ON_3dVector::YAxis);
          textscale_xf = textscale_xf * mxf;
        }
      }
    }
    text_xform_out = textscale_xf;
    text_xform_out = rotation_xf * text_xform_out;
    //text_xform_out = textcenter_xf * text_xform_out;
    text_xform_out = wcs2obj_xf * text_xform_out;

    return true;
  }
}




