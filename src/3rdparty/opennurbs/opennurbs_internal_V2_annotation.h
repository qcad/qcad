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

#if !defined(OPENNURBS_INTERNAL_V2_ANNOTATION_H_INC)
#define OPENNURBS_INTERNAL_V2_ANNOTATION_H_INC

#if defined(ON_COMPILING_OPENNURBS)

#include "opennurbs_internal_defines.h"

// Annotation classes used in version 2 .3dm archives and Rhino version 2.
// All classes in this file are obsolete. They exist so that old files can be read.

// Legacy annotation arrow is in some old .3dm files.
// Gets converted to an ON_Line with ON_3dmObjectAttributes arrow head
// ON_3dmObjectAttributes.m_object_decoration = (ON::end_arrowhead | other bits)
class ON_OBSOLETE_V2_AnnotationArrow : public ON_Geometry
{
  // 3d annotation arrow
  ON_OBJECT_DECLARE(ON_OBSOLETE_V2_AnnotationArrow);
public:
  ON_OBSOLETE_V2_AnnotationArrow();
  ~ON_OBSOLETE_V2_AnnotationArrow();
  ON_OBSOLETE_V2_AnnotationArrow(const ON_OBSOLETE_V2_AnnotationArrow&);
  ON_OBSOLETE_V2_AnnotationArrow& operator=(const ON_OBSOLETE_V2_AnnotationArrow&);

  /////////////////////////////////////////////////////////////////
  //
  // ON_Object overrides
  //
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  void Dump( ON_TextLog& ) const override; // for debugging

  bool Write(
         ON_BinaryArchive&  // serialize definition to binary archive
       ) const override;

  bool Read(
         ON_BinaryArchive&  // restore definition from binary archive
       ) override;

  ON::object_type ObjectType() const override;

  /////////////////////////////////////////////////////////////////
  //
  // ON_Geometry overrides
  //

  int Dimension() const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  bool Transform( 
         const ON_Xform&
         ) override;

  /////////////////////////////////////////////////////////////////
  //
  // Interface
  //
  ON_3dVector Vector() const;
  ON_3dPoint Head() const;
  ON_3dPoint Tail() const;

  ON_3dPoint m_tail;
  ON_3dPoint m_head;
};

class ON_OBSOLETE_V2_TextDot : public ON_Point
{
  // 3d annotation dot with text
  ON_OBJECT_DECLARE(ON_OBSOLETE_V2_TextDot);
public:
  ON_OBSOLETE_V2_TextDot();
  ~ON_OBSOLETE_V2_TextDot();
  ON_OBSOLETE_V2_TextDot(const ON_OBSOLETE_V2_TextDot&);
  ON_OBSOLETE_V2_TextDot& operator=(const ON_OBSOLETE_V2_TextDot&);

  /////////////////////////////////////////////////////////////////
  //
  // ON_Object overrides
  //

  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;
  void Dump( ON_TextLog& ) const override; // for debugging

  bool Write(
         ON_BinaryArchive&  // serialize definition to binary archive
       ) const override;

  bool Read(
         ON_BinaryArchive&  // restore definition from binary archive
       ) override;

  ON_wString m_text;
};


////////////////////////////////////////////////////////////////
//
//   ON_OBSOLETE_V2_Annotation - used to serialize definitions of annotation
//                   objects (dimensions, text blocks, etc.).
//

class ON_OBSOLETE_V2_Annotation : public ON_Geometry
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V2_Annotation);

protected:
  ON_OBSOLETE_V2_Annotation() = default;
  ON_OBSOLETE_V2_Annotation(const ON_OBSOLETE_V2_Annotation&) = default;
  ON_OBSOLETE_V2_Annotation& operator=(const ON_OBSOLETE_V2_Annotation&) = default;

public:
  virtual ~ON_OBSOLETE_V2_Annotation() = default;

protected:
  void Internal_Initialize();  // initialize class's fields assuming
                  // memory is uninitialized

public:
  static ON_OBSOLETE_V2_Annotation* CreateFromV5Annotation(
    const class ON_OBSOLETE_V5_Annotation& V5_annotation,
    const class ON_3dmAnnotationContext* annotation_context
  );

  static ON_OBSOLETE_V2_Annotation* CreateFromV6Annotation(
    const class ON_Annotation& V6_annotation,
    const class ON_3dmAnnotationContext* annotation_context
  );

protected:
  void Internal_InitializeFromV5Annotation(
    const ON_OBSOLETE_V5_Annotation& V5_annotation,
    const class ON_3dmAnnotationContext* annotation_context
  );

public:
  void Destroy();
  void EmergencyDestroy();

  /////////////////////////////////////////////////////////////////
  //
  // ON_Object overrides
  //
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  void Dump( ON_TextLog& ) const override; // for debugging

  bool Write(
         ON_BinaryArchive&  // serialize definition to binary archive
       ) const override;

  bool Read(
         ON_BinaryArchive&  // restore definition from binary archive
       ) override;

  ON::object_type ObjectType() const override;

  /////////////////////////////////////////////////////////////////
  //
  // ON_Geometry overrides
  //

  int Dimension() const override;

  // virtual ON_Geometry GetBBox override		
  bool GetBBox( double* boxmin, double* boxmax, bool bGrowBox = false ) const override;

  bool Transform( 
         const ON_Xform&
         ) override;

  /////////////////////////////////////////////////////////////////
  //
  // ON_OBSOLETE_V2_Annotation interface
  //

  // use these to get/set the current annotation settings
  static const ON_3dmAnnotationSettings& AnnotationSettings();
  static void SetAnnotationSettings( const ON_3dmAnnotationSettings* );

  bool IsText() const;
  bool IsLeader() const;
  bool IsDimension() const;

  virtual double NumericValue() const;
  virtual void SetTextToDefault();

  void SetType( ON_INTERNAL_OBSOLETE::V5_eAnnotationType type );
  ON_INTERNAL_OBSOLETE::V5_eAnnotationType Type() const;
  void SetTextDisplayMode( ON_INTERNAL_OBSOLETE::V5_TextDisplayMode mode);
  ON_INTERNAL_OBSOLETE::V5_TextDisplayMode TextDisplayMode() const;

  void SetPlane( const ON_Plane& plane );
  ON_Plane Plane() const;
  int PointCount() const;
  void SetPoints( const ON_SimpleArray<ON_2dPoint>& points );
  const ON_SimpleArray<ON_2dPoint>& Points() const;
  void SetPoint( int idx, ON_3dPoint point );
  ON_2dPoint Point( int idx ) const;
  void SetUserText( const wchar_t* string );
  const ON_wString& UserText() const;
  void SetDefaultText( const wchar_t* string );
  const ON_wString& DefaultText() const;
  void SetUserPositionedText( int bUserPositionedText );
  bool UserPositionedText() const;

  // to convert world 3d points to and from annotation 2d points
  bool GetECStoWCSXform( ON_Xform& xform ) const;
  bool GeWCStoECSXform( ON_Xform& xform ) const;

  ON_INTERNAL_OBSOLETE::V5_eAnnotationType m_type = ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtNothing;          // enum for type of annotation
                                       // DimLinear, DimRadius, etc.

  ON_INTERNAL_OBSOLETE::V5_TextDisplayMode m_textdisplaymode = ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kNormal; // how the text is displayed
                                       // Horizontal, InLine, AboveLine

  ON_Plane m_plane = ON_Plane::World_xy;                    // ECS reference plane in WCS coordinates
  ON_SimpleArray<ON_2dPoint> m_points; // Definition points for the dimension

  ON_wString m_usertext;               // "<>", or user override
  ON_wString m_defaulttext;            // The displayed text string

  bool m_userpositionedtext = false;   // true: User has positioned text 
                                       // false: use default location
};

class ON_OBSOLETE_V2_DimLinear : public ON_OBSOLETE_V2_Annotation
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V2_DimLinear);

public:
  ON_OBSOLETE_V2_DimLinear();
  ON_OBSOLETE_V2_DimLinear(const ON_OBSOLETE_V2_DimLinear&);
  ~ON_OBSOLETE_V2_DimLinear();
  ON_OBSOLETE_V2_DimLinear& operator=(const ON_OBSOLETE_V2_DimLinear&);

  double NumericValue() const override;
  void SetTextToDefault() override;
  void EmergencyDestroy();

  static ON_OBSOLETE_V2_DimLinear* CreateFromV5LinearDimension(
    const class ON_OBSOLETE_V5_DimLinear& V5_linear_dimension,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V2_DimLinear* destination
  );
};

class ON_OBSOLETE_V2_DimRadial : public ON_OBSOLETE_V2_Annotation
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V2_DimRadial);

public:
  ON_OBSOLETE_V2_DimRadial();
  ON_OBSOLETE_V2_DimRadial(const ON_OBSOLETE_V2_DimRadial&);
  ~ON_OBSOLETE_V2_DimRadial();
  ON_OBSOLETE_V2_DimRadial& operator=(const ON_OBSOLETE_V2_DimRadial&);

  double NumericValue() const override;
  void SetTextToDefault() override;

  void EmergencyDestroy();

  static ON_OBSOLETE_V2_DimRadial* CreateFromV5RadialDimension(
    const class ON_OBSOLETE_V5_DimRadial& V5_linear_dimension,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V2_DimRadial* destination
  );
};

class ON_OBSOLETE_V2_DimAngular : public ON_OBSOLETE_V2_Annotation
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V2_DimAngular);

public:
  ON_OBSOLETE_V2_DimAngular();
  ON_OBSOLETE_V2_DimAngular(const ON_OBSOLETE_V2_DimAngular&);
  ~ON_OBSOLETE_V2_DimAngular();
  ON_OBSOLETE_V2_DimAngular& operator=(const ON_OBSOLETE_V2_DimAngular&);

  static ON_OBSOLETE_V2_DimAngular* CreateFromV5AngularDimension(
    const class ON_OBSOLETE_V5_DimAngular& V5_angular_dimension,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V2_DimAngular* destination
  );

  void EmergencyDestroy();

  bool Write( ON_BinaryArchive& file ) const override;
  bool Read( ON_BinaryArchive& file ) override;

  void SetAngle( double angle ) { m_angle = angle; }
  double Angle() const { return m_angle; }
  void SetRadius( double radius ) { m_radius = radius; }
  double Radius() const { return m_radius; }

  double NumericValue() const override;
  void SetTextToDefault() override;

private:
  double m_angle;      // angle being dimensioned
  double m_radius;     // radius for dimension arc
};

class ON_OBSOLETE_V2_TextObject : public ON_OBSOLETE_V2_Annotation
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V2_TextObject);

public:
  ON_OBSOLETE_V2_TextObject();
  ON_OBSOLETE_V2_TextObject(const ON_OBSOLETE_V2_TextObject&);
  ~ON_OBSOLETE_V2_TextObject();
  ON_OBSOLETE_V2_TextObject& operator=(const ON_OBSOLETE_V2_TextObject&);

  static ON_OBSOLETE_V2_TextObject* CreateFromV5TextObject(
    const class ON_OBSOLETE_V5_TextObject& V5_text_object,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V2_TextObject* destination
  );

  void EmergencyDestroy();

  bool Write( ON_BinaryArchive& file ) const override;
  bool Read( ON_BinaryArchive& file ) override;

  void SetFaceName( ON_wString string ) { m_facename = string; }
  ON_wString FaceName() const { return m_facename; }
  void SetFontWeight( int weight ) { m_fontweight = weight; }
  int FontWeight() const { return m_fontweight; }
  void SetHeight( double height ) { m_height = height; }
  double Height() const { return m_height; }


private:
  ON_wString m_facename;
  int m_fontweight;  // windows - 400 = NORMAL )
  double m_height;   // gets multiplied by dimscale
};

class ON_OBSOLETE_V2_Leader : public ON_OBSOLETE_V2_Annotation
{
  ON_OBJECT_DECLARE(ON_OBSOLETE_V2_Leader);

public:
  ON_OBSOLETE_V2_Leader();
  ON_OBSOLETE_V2_Leader(const ON_OBSOLETE_V2_Leader&);
  ~ON_OBSOLETE_V2_Leader();
  ON_OBSOLETE_V2_Leader& operator=(const ON_OBSOLETE_V2_Leader&);

  static ON_OBSOLETE_V2_Leader* CreateFromV5Leader(
    const class ON_OBSOLETE_V5_Leader& V5_leader,
    const class ON_3dmAnnotationContext* annotation_context,
    ON_OBSOLETE_V2_Leader* destination
  );

  void EmergencyDestroy();
};

#endif
#endif

