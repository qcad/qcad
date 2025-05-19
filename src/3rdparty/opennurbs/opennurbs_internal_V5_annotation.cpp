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

#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

// obsolete V2 and V5 annotation objects
#include "opennurbs_internal_V2_annotation.h"
#include "opennurbs_internal_V5_annotation.h"

ON_VIRTUAL_OBJECT_IMPLEMENT( ON_OBSOLETE_V2_Annotation,       ON_Geometry,   "ABAF5873-4145-11d4-800F-0010830122F0" );
ON_OBJECT_IMPLEMENT( ON_OBSOLETE_V2_DimLinear,  ON_OBSOLETE_V2_Annotation, "5DE6B20D-486B-11d4-8014-0010830122F0" );
ON_OBJECT_IMPLEMENT( ON_OBSOLETE_V2_DimRadial,  ON_OBSOLETE_V2_Annotation, "5DE6B20E-486B-11d4-8014-0010830122F0" );
ON_OBJECT_IMPLEMENT( ON_OBSOLETE_V2_DimAngular, ON_OBSOLETE_V2_Annotation, "5DE6B20F-486B-11d4-8014-0010830122F0" );
ON_OBJECT_IMPLEMENT( ON_OBSOLETE_V2_TextObject,       ON_OBSOLETE_V2_Annotation, "5DE6B210-486B-11d4-8014-0010830122F0" );
ON_OBJECT_IMPLEMENT( ON_OBSOLETE_V2_Leader,           ON_OBSOLETE_V2_Annotation, "5DE6B211-486B-11d4-8014-0010830122F0" );

#define REALLY_BIG_NUMBER 1.0e150

static const ON_3dmAnnotationSettings* sglb_asets = 0;

void ON_OBSOLETE_V2_Annotation::SetAnnotationSettings( const ON_3dmAnnotationSettings* p )
{
  sglb_asets = p;
}

const ON_3dmAnnotationSettings& ON_OBSOLETE_V2_Annotation::AnnotationSettings()
{
  static ON_3dmAnnotationSettings defaults;
  return sglb_asets ? *sglb_asets : defaults;
}

void ON_OBSOLETE_V2_Annotation::Internal_Initialize()
{
  // TODO: initialize class members assuming any member that is not a class
  // is not initialized.
  m_type = ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtNothing;
  m_plane = ON_xy_plane;
  m_points.EmergencyDestroy();
  m_usertext.EmergencyDestroy();
  m_defaulttext.EmergencyDestroy();
  m_userpositionedtext = false;
}

void ON_OBSOLETE_V2_Annotation::Destroy()
{
  m_points.Destroy();
  m_usertext.Destroy();
  m_defaulttext.Destroy();
  m_type = ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtNothing;
  m_plane = ON_xy_plane;
  m_userpositionedtext = false;
}

void ON_OBSOLETE_V2_Annotation::EmergencyDestroy()
{
  m_points.EmergencyDestroy();
  m_usertext.EmergencyDestroy();
  m_defaulttext.EmergencyDestroy();
}


ON_OBSOLETE_V2_Annotation* ON_OBSOLETE_V2_Annotation::CreateFromV6Annotation(
  const class ON_Annotation& V6_annotation,
  const class ON_3dmAnnotationContext* annotation_context
)
{
  ON_OBSOLETE_V5_Annotation* V5_annotation = ON_OBSOLETE_V5_Annotation::CreateFromV6Annotation(V6_annotation, annotation_context);
  if (nullptr == V5_annotation)
    return nullptr;
  ON_OBSOLETE_V2_Annotation* V2_annotation = ON_OBSOLETE_V2_Annotation::CreateFromV5Annotation(*V5_annotation, annotation_context);
  delete V5_annotation;
  return V2_annotation;
}

ON_OBSOLETE_V2_Annotation* ON_OBSOLETE_V2_Annotation::CreateFromV5Annotation(
  const class ON_OBSOLETE_V5_Annotation& V5_annotation,
  const class ON_3dmAnnotationContext* annotation_context
)
{
  {
    const ON_OBSOLETE_V5_DimLinear* V5_linear_dimension = ON_OBSOLETE_V5_DimLinear::Cast(&V5_annotation);
    if (nullptr != V5_linear_dimension)
      return ON_OBSOLETE_V2_DimLinear::CreateFromV5LinearDimension(*V5_linear_dimension, annotation_context, nullptr);
  }

  {
    const ON_OBSOLETE_V5_DimAngular* V5_angular_dimension = ON_OBSOLETE_V5_DimAngular::Cast(&V5_annotation);
    if (nullptr != V5_angular_dimension)
      return ON_OBSOLETE_V2_DimAngular::CreateFromV5AngularDimension(*V5_angular_dimension, annotation_context, nullptr);
  }

  {
    const ON_OBSOLETE_V5_DimRadial* V5_radial_dimension = ON_OBSOLETE_V5_DimRadial::Cast(&V5_annotation);
    if (nullptr != V5_radial_dimension)
      return ON_OBSOLETE_V2_DimRadial::CreateFromV5RadialDimension(*V5_radial_dimension, annotation_context, nullptr);
  }

  {
    const ON_OBSOLETE_V5_Leader* V5_leader = ON_OBSOLETE_V5_Leader::Cast(&V5_annotation);
    if (nullptr != V5_leader)
      return ON_OBSOLETE_V2_Leader::CreateFromV5Leader(*V5_leader, annotation_context, nullptr);
  }

  {
    const ON_OBSOLETE_V5_TextObject* V5_text_object = ON_OBSOLETE_V5_TextObject::Cast(&V5_annotation);
    if (nullptr != V5_text_object)
      return ON_OBSOLETE_V2_TextObject::CreateFromV5TextObject(*V5_text_object, annotation_context, nullptr);
  }

  return nullptr;
}

bool ON_OBSOLETE_V2_Annotation::IsText() const { return Type() == ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock; }
bool ON_OBSOLETE_V2_Annotation::IsLeader() const { return Type() == ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader; }
bool ON_OBSOLETE_V2_Annotation::IsDimension() const { if( IsText() || IsLeader()) return false; return true; }

//virtual 
double ON_OBSOLETE_V2_Annotation::NumericValue() const { return 0.0; }
//virtual 
void ON_OBSOLETE_V2_Annotation::SetTextToDefault() { SetDefaultText( L""); }

void ON_OBSOLETE_V2_Annotation::SetType( ON_INTERNAL_OBSOLETE::V5_eAnnotationType type ) { m_type = type; }
ON_INTERNAL_OBSOLETE::V5_eAnnotationType ON_OBSOLETE_V2_Annotation::Type() const { return m_type; }
void ON_OBSOLETE_V2_Annotation::SetTextDisplayMode( ON_INTERNAL_OBSOLETE::V5_TextDisplayMode mode) { m_textdisplaymode = mode; }
ON_INTERNAL_OBSOLETE::V5_TextDisplayMode ON_OBSOLETE_V2_Annotation::TextDisplayMode() const { return m_textdisplaymode; }

void ON_OBSOLETE_V2_Annotation::SetPlane( const ON_Plane& plane ) { m_plane = plane; }
ON_Plane ON_OBSOLETE_V2_Annotation::Plane() const { return m_plane; }
int ON_OBSOLETE_V2_Annotation::PointCount() const { return m_points.Count(); }
void ON_OBSOLETE_V2_Annotation::SetPoints( const ON_SimpleArray<ON_2dPoint>& points ) { m_points = points; }
const ON_SimpleArray<ON_2dPoint>& ON_OBSOLETE_V2_Annotation::Points() const { return m_points; }
void ON_OBSOLETE_V2_Annotation::SetUserText( const wchar_t* string ) {m_usertext = string; }
const ON_wString& ON_OBSOLETE_V2_Annotation::UserText() const { return m_usertext; }
void ON_OBSOLETE_V2_Annotation::SetDefaultText( const wchar_t* string ) { m_defaulttext = string; }
const ON_wString& ON_OBSOLETE_V2_Annotation::DefaultText() const { return m_defaulttext; }
void ON_OBSOLETE_V2_Annotation::SetUserPositionedText( int bUserPositionedText ) { m_userpositionedtext = (bUserPositionedText?true:false); }
bool ON_OBSOLETE_V2_Annotation::UserPositionedText() const { return m_userpositionedtext; }

bool ON_OBSOLETE_V2_Annotation::IsValid( ON_TextLog* text_log ) const
{
  // TODO: quickly inspect object and return true/false
  bool rc = true;
  if ( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtNothing == m_type  )
  {
    if ( 0 != text_log )
      text_log->Print("ON_OBSOLETE_V2_Annotation has m_type = ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtNothing.\n");
    rc = false;
  }
  return rc;
}

void ON_OBSOLETE_V2_Annotation::Dump( ON_TextLog& dump ) const
{
  // for debugging
  dump.Print("ON_OBSOLETE_V2_Annotation: ....\n");
}

bool ON_OBSOLETE_V2_Annotation::Write( ON_BinaryArchive& file ) const
{
  bool rc = file.Write3dmChunkVersion( 1, 0 );
    // TODO: use 
    //    if (rc) rc = file.WritePoint(....);
    //    if (rc) rc = file.WriteString(....);
    //    if (rc) rc = file.WriteDouble(....);
    // to write object.
  unsigned int ui = static_cast<unsigned char>(m_type);
  if (rc) 
    rc = file.WriteInt( ui );
  if (rc) 
    rc = file.WritePlane( m_plane );
  if (rc) 
    rc = file.WriteArray( m_points );
  if (rc) 
    rc = file.WriteString( m_usertext );
  if (rc) 
    rc = file.WriteString( m_defaulttext );
  int i = m_userpositionedtext ? 1 : 0;
  if( rc )
    rc = file.WriteInt( i );
  return rc;
}

bool ON_OBSOLETE_V2_Annotation::Read( ON_BinaryArchive& file )
{
  Destroy();
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if ( rc && major_version == 1 ) 
  {
    if (rc)
    {
      unsigned int ui = 0;
      rc = file.ReadInt( &ui );
      if (rc)
        m_type = ON_INTERNAL_OBSOLETE::V5AnnotationTypeFromUnsigned(ui);
    }
    if (rc)
      rc = file.ReadPlane( m_plane );
    if (rc)
      rc = file.ReadArray( m_points );
    if (rc)
      rc = file.ReadString( m_usertext );
    if (rc)
      rc = file.ReadString( m_defaulttext );
    if( rc )
    {
      int i = 0;
      rc = file.ReadInt( &i );
      if (rc)
        m_userpositionedtext = (i ? true : false);
    }
  }

  if( fabs( m_plane.origin.x) > REALLY_BIG_NUMBER || fabs( m_plane.origin.y) > REALLY_BIG_NUMBER || fabs( m_plane.origin.z) > REALLY_BIG_NUMBER)
    return false;

  for( int i = 0; i < m_points.Count(); i++)
  {
    if( fabs( m_points[i].x) > REALLY_BIG_NUMBER || fabs( m_points[i].y) > REALLY_BIG_NUMBER)
      return false;
  }


  return rc;
}

ON::object_type ON_OBSOLETE_V2_Annotation::ObjectType() const
{
  return ON::annotation_object;
}



int ON_OBSOLETE_V2_Annotation::Dimension() const
{
  return 3; 
}

bool ON_OBSOLETE_V2_Annotation::GetBBox( // returns true if successful
       double* boxmin,
       double* boxmax,
       bool bGrowBox // default = false
       ) const
{
  // TODO:
  //   If the class is not valid, return false.
  //
  //   If the class is valid and bGrowBox is false, 
  //   return the 3d bounding box of the annotation.
  //
  //   If the class is valid and bGrowBox is true, 
  //   return the union of the input box and the 3d bounding 
  //   box of the annotation.
  if( !bGrowBox )
  {
    boxmin[0] = boxmin[1] = boxmin[2] =  1e300;
    boxmax[0] = boxmax[1] = boxmax[2] = -1e300;
  }

  ON_3dPoint wpt;
  ON_Xform xform;
  GetECStoWCSXform( xform );
  for( int i = 0; i < m_points.Count(); i++ )
  {
    wpt = m_points[i];
    
    if( wpt.y < boxmin[1] )
      boxmin[1] = wpt.y;
    if( wpt.z < boxmin[2] )
      boxmin[2] = wpt.z;
    if( wpt.x > boxmax[0] )
      boxmax[0] = wpt.x;
    if( wpt.y > boxmax[1] )
      boxmax[1] = wpt.y;
    if( wpt.z > boxmax[2] )
      boxmax[2] = wpt.z;
  }
  return true;
}

bool ON_OBSOLETE_V2_Annotation::Transform( const ON_Xform& xform )
{
  // TODO: Return false if class is invalid or xform cannot be applied.
  //       Otherwise, apply xform to geometry and return true.
  TransformUserData(xform);
  return m_plane.Transform( xform );
}

// Converts 2d points in annotation to 3d WCS points 
bool ON_OBSOLETE_V2_Annotation::GetECStoWCSXform( ON_Xform& xform ) const
{
  ON_3dVector z = ON_CrossProduct( m_plane.xaxis, m_plane.yaxis );
  return xform.ChangeBasis( m_plane.origin, m_plane.xaxis, m_plane.yaxis, z, 
                            ON_3dPoint::Origin, ON_3dVector::XAxis, ON_3dVector::YAxis, ON_3dVector::ZAxis );
}

// Converts from WCS 3d points to 2d points in annotation
bool ON_OBSOLETE_V2_Annotation::GeWCStoECSXform( ON_Xform& xform ) const
{
  ON_3dVector z = ON_CrossProduct( m_plane.xaxis, m_plane.yaxis );
  return xform.ChangeBasis( ON_3dPoint::Origin, ON_3dVector::XAxis, ON_3dVector::YAxis, ON_3dVector::ZAxis,
                            m_plane.origin, m_plane.xaxis, m_plane.yaxis, z );
}

void ON_OBSOLETE_V2_Annotation::SetPoint( int idx, ON_3dPoint point )
{
  if( idx >= 0 && idx < m_points.Count() )
    m_points[idx] = point;
}
  
ON_2dPoint ON_OBSOLETE_V2_Annotation::Point( int idx ) const
{
  if( idx >= 0 && idx < m_points.Count() )
    return m_points[idx];

  return ON_2dPoint( 0.0, 0.0 );
}



//----- ON_OBSOLETE_V2_DimLinear ------------------------------------------
ON_OBSOLETE_V2_DimLinear::ON_OBSOLETE_V2_DimLinear()
{
}

ON_OBSOLETE_V2_DimLinear::ON_OBSOLETE_V2_DimLinear(const ON_OBSOLETE_V2_DimLinear& src) : ON_OBSOLETE_V2_Annotation(src)
{
}

ON_OBSOLETE_V2_DimLinear::~ON_OBSOLETE_V2_DimLinear()
{
}

ON_OBSOLETE_V2_DimLinear& ON_OBSOLETE_V2_DimLinear::operator=(const ON_OBSOLETE_V2_DimLinear& src)
{
  if ( this != &src ) {
    ON_OBSOLETE_V2_Annotation::operator=(src);
  }
  return *this;
}

void ON_OBSOLETE_V2_DimLinear::EmergencyDestroy()
{
  ON_OBSOLETE_V2_Annotation::EmergencyDestroy();
}

double ON_OBSOLETE_V2_DimLinear::NumericValue() const
{
  return (Point( 1) - Point( 3)).Length();
}
void ON_OBSOLETE_V2_DimLinear::SetTextToDefault() 
{ 
  SetUserText( L"<>"); 
}


//----- ON_OBSOLETE_V2_DimRadial ------------------------------------------
ON_OBSOLETE_V2_DimRadial::ON_OBSOLETE_V2_DimRadial()
{
}

ON_OBSOLETE_V2_DimRadial::ON_OBSOLETE_V2_DimRadial(const ON_OBSOLETE_V2_DimRadial& src) : ON_OBSOLETE_V2_Annotation(src)
{
}

ON_OBSOLETE_V2_DimRadial::~ON_OBSOLETE_V2_DimRadial()
{
}

ON_OBSOLETE_V2_DimRadial& ON_OBSOLETE_V2_DimRadial::operator=(const ON_OBSOLETE_V2_DimRadial& src)
{
  if ( this != &src ) {
    ON_OBSOLETE_V2_Annotation::operator=(src);
  }
  return *this;
}

void ON_OBSOLETE_V2_DimRadial::EmergencyDestroy()
{
  ON_OBSOLETE_V2_Annotation::EmergencyDestroy();
}

double ON_OBSOLETE_V2_DimRadial::NumericValue() const
{
  double d = (Point( 0) - Point( 1)).Length();
  if( Type() == ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter)
    d *= 2.0;
  return d;
}

void ON_OBSOLETE_V2_DimRadial::SetTextToDefault() 
{ 
  ON_wString s; 
  if( Type() == ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter) 
    s.Format( L"%c<>", ON_wString::DiameterSymbol ); 
  else 
    s.Format( L"%c<>", ON_wString::RadiusSymbol ); 
  SetUserText( static_cast< const wchar_t* >(s)); 
}

//----- ON_OBSOLETE_V2_DimAngular -----------------------------------------
ON_OBSOLETE_V2_DimAngular::ON_OBSOLETE_V2_DimAngular() : m_angle(0.0), m_radius(0.0)
{
}

ON_OBSOLETE_V2_DimAngular::ON_OBSOLETE_V2_DimAngular(const ON_OBSOLETE_V2_DimAngular& src) : ON_OBSOLETE_V2_Annotation(src)
{
  m_angle = src.m_angle;
  m_radius = src.m_radius;
}

ON_OBSOLETE_V2_DimAngular::~ON_OBSOLETE_V2_DimAngular()
{
}

ON_OBSOLETE_V2_DimAngular& ON_OBSOLETE_V2_DimAngular::operator=(const ON_OBSOLETE_V2_DimAngular& src)
{
  if ( this != &src ) {
    ON_OBSOLETE_V2_Annotation::operator=(src);
    m_angle = src.m_angle;
    m_radius = src.m_radius;
  }
  return *this;
}

void ON_OBSOLETE_V2_DimAngular::EmergencyDestroy()
{
  ON_OBSOLETE_V2_Annotation::EmergencyDestroy();
}

bool ON_OBSOLETE_V2_DimAngular::Write( ON_BinaryArchive& file ) const
{
  bool rc = ON_OBSOLETE_V2_Annotation::Write( file );
  if( rc )
    rc = file.WriteDouble( m_angle );
  if( rc )
    rc = file.WriteDouble( m_radius );
  return rc;
}

bool ON_OBSOLETE_V2_DimAngular::Read( ON_BinaryArchive& file )
{
  bool rc = ON_OBSOLETE_V2_Annotation::Read( file );
  if( rc )
    rc = file.ReadDouble( &m_angle );
  if( rc )
    rc = file.ReadDouble( &m_radius );

  if( m_angle <= 0.0 || m_angle > REALLY_BIG_NUMBER)
    return false;

  if( m_radius <= 0.0 || m_radius > REALLY_BIG_NUMBER)
    return false;

  return rc;
}

double ON_OBSOLETE_V2_DimAngular::NumericValue() const
{
  return Angle() * 180.0 / ON_PI;
}

void ON_OBSOLETE_V2_DimAngular::SetTextToDefault() 
{ 
  ON_wString s; 
  s.Format( L"<>%c", ON_wString::DegreeSymbol ); 
  SetUserText( static_cast< const wchar_t* >(s)); 
}

//----- ON_OBSOLETE_V2_TextObject -----------------------------------------------
ON_OBSOLETE_V2_TextObject::ON_OBSOLETE_V2_TextObject() : m_fontweight(400), m_height(20.0)
{
}

ON_OBSOLETE_V2_TextObject::ON_OBSOLETE_V2_TextObject(const ON_OBSOLETE_V2_TextObject& src) : ON_OBSOLETE_V2_Annotation(src)
{
  m_facename = src.m_facename;
  m_fontweight = src.m_fontweight;
  m_height = src.m_height;
}

ON_OBSOLETE_V2_TextObject::~ON_OBSOLETE_V2_TextObject()
{
  m_facename.Destroy();
}

ON_OBSOLETE_V2_TextObject& ON_OBSOLETE_V2_TextObject::operator=(const ON_OBSOLETE_V2_TextObject& src)
{
  if ( this != &src ) {
    m_facename = src.m_facename;
    m_fontweight = src.m_fontweight;
    m_height = src.m_height;
    ON_OBSOLETE_V2_Annotation::operator=(src);
  }
  return *this;
}

void ON_OBSOLETE_V2_TextObject::EmergencyDestroy()
{
  ON_OBSOLETE_V2_Annotation::EmergencyDestroy();
  m_facename.EmergencyDestroy();
}

bool ON_OBSOLETE_V2_TextObject::Write( ON_BinaryArchive& file ) const
{
  bool rc = ON_OBSOLETE_V2_Annotation::Write( file );
  if( rc )
    rc = file.WriteString( m_facename );
  if( rc )
    rc = file.WriteInt( m_fontweight );
  if( rc )
    rc = file.WriteDouble( m_height );
  return rc;
}

bool ON_OBSOLETE_V2_TextObject::Read( ON_BinaryArchive& file )
{
  bool rc = ON_OBSOLETE_V2_Annotation::Read( file );
  if( rc )
    rc = file.ReadString( m_facename );
  if( rc )
    rc = file.ReadInt( &m_fontweight );
  if( rc )
    rc = file.ReadDouble( &m_height );

  if( fabs( m_height) > REALLY_BIG_NUMBER)
    return false;


  return rc;
}

//----- ON_OBSOLETE_V2_Leader ------------------------------------------
ON_OBSOLETE_V2_Leader::ON_OBSOLETE_V2_Leader()
{
}

ON_OBSOLETE_V2_Leader::ON_OBSOLETE_V2_Leader(const ON_OBSOLETE_V2_Leader& src) : ON_OBSOLETE_V2_Annotation(src)
{
}

ON_OBSOLETE_V2_Leader::~ON_OBSOLETE_V2_Leader()
{
}

ON_OBSOLETE_V2_Leader& ON_OBSOLETE_V2_Leader::operator=(const ON_OBSOLETE_V2_Leader& src)
{
  if ( this != &src ) {
    ON_OBSOLETE_V2_Annotation::operator=(src);
  }
  return *this;
}

void ON_OBSOLETE_V2_Leader::EmergencyDestroy()
{
  ON_OBSOLETE_V2_Annotation::EmergencyDestroy();
}


ON_OBJECT_IMPLEMENT(ON_OBSOLETE_V2_TextDot,ON_Point,"8BD94E19-59E1-11d4-8018-0010830122F0");

ON_OBSOLETE_V2_TextDot::ON_OBSOLETE_V2_TextDot()
{}

ON_OBSOLETE_V2_TextDot::~ON_OBSOLETE_V2_TextDot()
{
  m_text.Destroy();
}

ON_OBSOLETE_V2_TextDot::ON_OBSOLETE_V2_TextDot(const ON_OBSOLETE_V2_TextDot& src) : ON_Point(src), m_text(src.m_text)
{}

ON_OBSOLETE_V2_TextDot& ON_OBSOLETE_V2_TextDot::operator=(const ON_OBSOLETE_V2_TextDot& src)
{
  if ( this != &src ) {
    ON_Point::operator=(src);
    m_text = src.m_text;
  }
  return *this;
}

bool ON_OBSOLETE_V2_TextDot::IsValid( ON_TextLog* text_log ) const
{
  bool rc = true;
  if ( m_text.IsEmpty() )
  {
    if ( 0 != text_log )
      text_log->Print("ON_OBSOLETE_V2_TextDot.m_text is empty\n");
    rc = false;
  }
  return rc;
}

void ON_OBSOLETE_V2_TextDot::Dump( ON_TextLog& log ) const
{
  log.Print("ON_OBSOLETE_V2_TextDot \"%ls\" at ",m_text.Array());
  log.Print(point);
  log.Print("\n");
}

bool ON_OBSOLETE_V2_TextDot::Write( ON_BinaryArchive& file ) const
{
  bool rc = file.Write3dmChunkVersion(1,0);
  if (rc) rc = file.WritePoint( point );
  if (rc) rc = file.WriteString( m_text );
  return rc;
}

bool ON_OBSOLETE_V2_TextDot::Read( ON_BinaryArchive& file )
{
  m_text.Destroy();
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if ( major_version == 1 ) {
    if (rc) rc = file.ReadPoint( point );
    if (rc) rc = file.ReadString( m_text );
  }
  else {
    rc = false;
  }
  return rc;
}

ON_OBJECT_IMPLEMENT(ON_OBSOLETE_V2_AnnotationArrow,ON_Geometry,"8BD94E1A-59E1-11d4-8018-0010830122F0");

ON_OBSOLETE_V2_AnnotationArrow::ON_OBSOLETE_V2_AnnotationArrow() : m_tail(0.0,0.0,0.0), m_head(0.0,0.0,0.0)
{}

ON_OBSOLETE_V2_AnnotationArrow::~ON_OBSOLETE_V2_AnnotationArrow()
{}

ON_OBSOLETE_V2_AnnotationArrow::ON_OBSOLETE_V2_AnnotationArrow(const ON_OBSOLETE_V2_AnnotationArrow& src) : ON_Geometry(src), m_tail(src.m_tail), m_head(src.m_head)
{}

ON_OBSOLETE_V2_AnnotationArrow& ON_OBSOLETE_V2_AnnotationArrow::operator=(const ON_OBSOLETE_V2_AnnotationArrow& src)
{
  if ( this != &src ) {
    ON_Geometry::operator=(src);
    m_tail = src.m_tail;
    m_head = src.m_head;
  }
  return *this;
}

bool ON_OBSOLETE_V2_AnnotationArrow::IsValid( ON_TextLog* text_log ) const
{
  bool rc = true;
  if (m_tail == m_head)
  {
    if ( 0 != text_log )
      text_log->Print("ON_OBSOLETE_V2_AnnotationArrow has m_head=m_tail.\n");
    rc = false;
  }
  return rc;
}

void ON_OBSOLETE_V2_AnnotationArrow::Dump( ON_TextLog& log ) const
{
  log.Print("ON_OBSOLETE_V2_AnnotationArrow: ");
  log.Print(m_tail);
  log.Print(" to ");
  log.Print(m_head);
  log.Print("\n");
}

bool ON_OBSOLETE_V2_AnnotationArrow::Write( ON_BinaryArchive& file ) const
{
  bool rc = file.Write3dmChunkVersion(1,0);
  if (rc) rc = file.WritePoint( m_tail );
  if (rc) rc = file.WritePoint( m_head );
  return rc;
}

bool ON_OBSOLETE_V2_AnnotationArrow::Read(ON_BinaryArchive& file)
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  if ( major_version == 1 ) {
    if (rc) rc = file.ReadPoint( m_tail );
    if (rc) rc = file.ReadPoint( m_head );

  }
  else {
    rc = false;
  }
  return rc;
}

ON::object_type ON_OBSOLETE_V2_AnnotationArrow::ObjectType() const
{
  return ON::annotation_object;
}

int ON_OBSOLETE_V2_AnnotationArrow::Dimension() const
{
  return 3;
}

bool ON_OBSOLETE_V2_AnnotationArrow::GetBBox( double* boxmin, double* boxmax, bool bGrowBox ) const
{
  bool rc = ON_GetPointListBoundingBox( 3, false, 1, 3, m_tail, boxmin, boxmax, bGrowBox?true:false );
  if (rc)
    rc = ON_GetPointListBoundingBox( 3, false, 1, 3, m_head, boxmin, boxmax, true );
  return rc;
}

bool ON_OBSOLETE_V2_AnnotationArrow::Transform( const ON_Xform& xform )
{
  TransformUserData(xform);
  m_tail = xform*m_tail;
  m_head = xform*m_head;
  return true;
}

ON_3dVector ON_OBSOLETE_V2_AnnotationArrow::Vector() const
{
  return (m_head-m_tail);
}

ON_3dPoint ON_OBSOLETE_V2_AnnotationArrow::Head() const
{
  return m_head;
}

ON_3dPoint ON_OBSOLETE_V2_AnnotationArrow::Tail() const
{
  return m_tail;
}


static bool ON_Internal_UseSubDMeshProxy(
  const ON_BinaryArchive& archive
)
{
  if (archive.Archive3dmVersion() != 60)
  {
    return false; // subd mesh proxy only applies when reading or writing a V6 files.
  }

  // In a WIP, used subd objects.
  const unsigned int min_subd_version =
#if defined(RHINO_COMMERCIAL_BUILD)
    // Sep 5 2017 Dale Lear RH-41113
    // Rhino 6 commercial will have SubD objects.
    // Nope. -> V6 commercial builds do not have subd objects - use proxy mesh when version < 7.
    // 7 
    6 
#else
    // V6 WIP builds and all V7 and later builds have subd objects.
    // Use proxy mesh when version < 6.
    6
#endif
    ;
  return (ON::VersionMajor() < min_subd_version);
}


/*
Description:
  In rare cases one object must be converted into another.
  Examples include reading obsolete objects and converting them into their 
  current counterpart, converting WIP objects into a proxy for a commercial build, 
  and converting a proxy object into a WIP object for a WIP build.
*/
ON_Object* ON_BinaryArchive::Internal_ConvertObject(
    const ON_Object* archive_object,
    const ON_3dmObjectAttributes* attributes
  ) const
{
  if (nullptr == archive_object)
    return nullptr;

  if (ON::object_type::annotation_object == archive_object->ObjectType())
  {
    m_annotation_context.SetViewContext((nullptr != attributes) ? attributes->m_space : ON::active_space::no_space);
    
    const ON_OBSOLETE_V2_AnnotationArrow* annotation_arrow = ON_OBSOLETE_V2_AnnotationArrow::Cast(archive_object);
    if (nullptr != annotation_arrow)
    {
      ON_LineCurve* line_curve = new ON_LineCurve(annotation_arrow->m_tail, annotation_arrow->m_head);
      //if (nullptr != pAttributes)
      //  pAttributes->m_object_decoration = ON::object_decoration::end_arrowhead;
      return line_curve;
    }

    const ON_OBSOLETE_V2_Annotation* V2_annotation = ON_OBSOLETE_V2_Annotation::Cast(archive_object);
    if (nullptr != V2_annotation)
    {
      // convert V2 annotation object to V5 annotation object
      const ON_DimStyle& dim_style = ArchiveCurrentDimStyle();
      m_annotation_context.SetReferencedDimStyle(&dim_style,nullptr,ArchiveCurrentDimStyleIndex());
      ON_Annotation* V6_annotation = ON_Annotation::CreateFromV2Annotation(*V2_annotation, &m_annotation_context);
      if (nullptr != V6_annotation)
        V6_annotation->SetDimensionStyleId(dim_style.Id());
      return V6_annotation;
    }

    const ON_OBSOLETE_V5_Annotation* V5_annotation = ON_OBSOLETE_V5_Annotation::Cast(archive_object);
    if (nullptr != V5_annotation)
    {
      // convert V5 annotation object to V6 annotation object
      int V5_dim_style_index = V5_annotation->V5_3dmArchiveDimStyleIndex();
      const ON_DimStyle* dim_style = nullptr;
      const ON_DimStyle* override_dim_style = nullptr;
      if (V5_dim_style_index >= 0 && V5_dim_style_index < m_archive_dim_style_table.Count())
        dim_style = m_archive_dim_style_table[V5_dim_style_index];
      if (nullptr != dim_style && dim_style->ParentIdIsNotNil())
      {
        if (dim_style->Id() != dim_style->ParentId())
        {
          for (int i = 0; i < this->m_archive_dim_style_table.Count(); i++)
          {
            const ON_DimStyle* archive_dim_style = m_archive_dim_style_table[i];
            if (nullptr == archive_dim_style)
              continue;
            if (archive_dim_style->ParentIdIsNotNil())
              continue;
            if (archive_dim_style->Id() == dim_style->ParentId())
            {
              override_dim_style = dim_style;
              dim_style = archive_dim_style;
              break;
            }
          }
        }
        if (nullptr == override_dim_style)
          dim_style = nullptr;
      }

      if (nullptr == dim_style)
      {
        dim_style = &ArchiveCurrentDimStyle();
        V5_dim_style_index = ArchiveCurrentDimStyleIndex();
      }

      m_annotation_context.SetReferencedDimStyle( dim_style, override_dim_style, V5_dim_style_index );
      ON_Annotation* V6_annotation = ON_Annotation::CreateFromV5Annotation( *V5_annotation, &m_annotation_context );
      if (nullptr != V6_annotation)
      {
        const ON_UUID archive_id = dim_style->Id();
        ON_UUID model_id = archive_id;
        const ON_ManifestMapItem mapitem = this->ManifestMap().MapItemFromSourceId(archive_id);
        if (ON_ModelComponent::Type::DimStyle == mapitem.ComponentType())
          model_id = mapitem.DestinationId();
        V6_annotation->SetDimensionStyleIdForExperts(model_id, true);
      }

      return V6_annotation;
    }

    return nullptr;
  }

  if (ON::object_type::point_object == archive_object->ObjectType())
  {
    const ON_OBSOLETE_V2_TextDot* v1_text_dot = ON_OBSOLETE_V2_TextDot::Cast(archive_object);
    if (nullptr != v1_text_dot)
    {
      ON_TextDot* text_dot = new ON_TextDot();
      text_dot->SetPrimaryText(v1_text_dot->m_text);
      text_dot->SetCenterPoint(v1_text_dot->point);
      text_dot->SetFontFace(ON_DimStyle::Default.Font().WindowsLogfontName());
      return text_dot;
    }
    return nullptr;
  }

  if (ON::object_type::mesh_object == archive_object->ObjectType())
  {
    const ON_Mesh* mesh = ON_Mesh::Cast(archive_object);
    if (nullptr != mesh )
    {
      if ( false == ON_Internal_UseSubDMeshProxy(*this) )
      {
        // If mesh is a subd mesh proxy, return the original subd.
        ON_SubD* subd = ON_SubDMeshProxyUserData::SubDFromMeshProxy(mesh);
        if ( nullptr != subd )
          return subd;
      }
    }
  }
  else if (ON::object_type::subd_object == archive_object->ObjectType())
  {
    const ON_SubD* subd = ON_SubD::Cast(archive_object);
    if (nullptr != subd)
    {
      ON_Mesh* mesh = nullptr;
      if ( Archive3dmVersion() < 60 )
      {
        mesh = subd->GetControlNetMesh(nullptr, ON_SubDGetControlNetMeshPriority::Geometry);
      }
      else if ( ON_Internal_UseSubDMeshProxy(*this) )
      {
        // Use a subd mesh proxy for V6 commercial builds.
        mesh = ON_SubDMeshProxyUserData::MeshProxyFromSubD(subd);
      }
      if (nullptr != mesh)
        return mesh;
    }
  }
  
  // no conversion required.
  return nullptr;
}
