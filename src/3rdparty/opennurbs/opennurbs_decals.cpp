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
#include "opennurbs_internal_defines.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

// ON_Decal

static ON_4dPoint UNSET_4D_POINT = ON_4dPoint(ON_UNSET_VALUE, ON_UNSET_VALUE, ON_UNSET_VALUE, ON_UNSET_VALUE);

ON_DECAL_CRC ON_DecalCRCFromNode(const ON_XMLNode& node)
{
	return ON_Decal::ComputeDecalCRC(0, node);
}

class ON_Decal::CImpl : public ON_InternalXMLImpl
{
public:
  CImpl();
  CImpl(ON_DecalCollection* dc,       ON_XMLNode& node);
  CImpl(ON_DecalCollection* dc, const ON_XMLNode& node);

  ON_UUID TextureInstanceId(void) const;
  void SetTextureInstanceId(const ON_UUID& id);
  Mappings Mapping(void) const;
  void SetMapping(Mappings v);
  Projections Projection(void) const;
  void SetProjection(Projections v);
  bool MapToInside(void) const;
  void SetMapToInside(bool v);
  double Transparency(void) const;
  void SetTransparency(double v);
  ON_3dPoint Origin(void) const;
  void SetOrigin(const ON_3dPoint& v);
  ON_3dVector VectorUp(void) const;
  void SetVectorUp(const ON_3dVector& v);
  ON_3dVector VectorAcross(void) const;
  void SetVectorAcross(const ON_3dVector& v);
  double Height(void) const;
  void SetHeight(double d);
  double Radius(void) const;
  void SetRadius(double d);
  bool IsVisible(void) const;
  void SetIsVisible(bool b);
  void GetHorzSweep(double& sta, double& end) const;
  void SetHorzSweep(double sta, double end);
  void GetVertSweep(double& sta, double& end) const;
  void SetVertSweep(double sta, double end);
  void GetUVBounds(double& min_u, double& min_v, double& max_u, double& max_v) const;
  void SetUVBounds(double min_u, double min_v, double max_u, double max_v);

  ON_UUID Id(void) const { return _decal_id; }
  ON_XMLVariant GetParameter(const wchar_t* param_name, const ON_XMLVariant& def) const;
  void SetParameter(const wchar_t* param_name, const ON_XMLVariant& value);
  ON_XMLNode* FindCustomNodeForRenderEngine(const ON_UUID& renderEngineId) const;
  virtual ON_wString NameOfRootNode(void) const override { return ON_RDK_DECAL; }

  static const int unset_bool = 2;
  mutable struct Cache
  {
    double radius       = ON_UNSET_VALUE;
    double height       = ON_UNSET_VALUE;
    double transparency = ON_UNSET_VALUE;
    ON_UUID texture_instance_id = ON_nil_uuid;
    ON_3dPoint origin = ON_3dPoint::UnsetPoint;
    ON_3dVector vector_up = ON_3dVector::UnsetVector;
    ON_3dVector vector_across = ON_3dVector::UnsetVector;
    ON_2dPoint horz_sweep  = ON_2dPoint::UnsetPoint;
    ON_2dPoint vert_sweep  = ON_2dPoint::UnsetPoint;
    ON_4dPoint uv_bounds   = UNSET_4D_POINT;
    Mappings mapping = Mappings::None;
    Projections projection = Projections::None;
    bool texture_instance_id_set = false;
    int visible = unset_bool;
    int map_to_inside = unset_bool;
  }
  _cache;

private:
  ON_DecalCollection* _collection = nullptr;
  ON_UUID _decal_id;
};

static ON_Decal::Mappings MappingFromString(const ON_wString& s)
{
       if (s == ON_RDK_DECAL_MAPPING_PLANAR)      return ON_Decal::Mappings::Planar;
  else if (s == ON_RDK_DECAL_MAPPING_SPHERICAL)   return ON_Decal::Mappings::Spherical;
  else if (s == ON_RDK_DECAL_MAPPING_CYLINDRICAL) return ON_Decal::Mappings::Cylindrical;
  else if (s == ON_RDK_DECAL_MAPPING_UV)          return ON_Decal::Mappings::UV;
  else if (s == ON_RDK_DECAL_MAPPING_NONE)        return ON_Decal::Mappings::None;

  ON_ASSERT(false);
  return ON_Decal::Mappings::None;
}

ON_Decal::CImpl::CImpl()
{
  ON_CreateUuid(_decal_id);
}

ON_Decal::CImpl::CImpl(ON_DecalCollection* dc, ON_XMLNode& node)
  :
  _collection(dc),
  ON_InternalXMLImpl(&node)
{
  ON_CreateUuid(_decal_id);
}

ON_Decal::CImpl::CImpl(ON_DecalCollection* dc, const ON_XMLNode& node)
  :
  _collection(dc),
  ON_InternalXMLImpl(&const_cast<ON_XMLNode&>(node))
{
  ON_CreateUuid(_decal_id);
}

ON_XMLVariant ON_Decal::CImpl::GetParameter(const wchar_t* param_name, const ON_XMLVariant& def) const
{
  return ON_InternalXMLImpl::GetParameter(L"", param_name, def);
}

void ON_Decal::CImpl::SetParameter(const wchar_t* param_name, const ON_XMLVariant& value)
{
  if (nullptr != _collection)
    _collection->SetChanged();

  ON_InternalXMLImpl::SetParameter(L"", param_name, value);
}

ON_UUID ON_Decal::CImpl::TextureInstanceId(void) const
{
  if (!_cache.texture_instance_id_set)
  {
    _cache.texture_instance_id = GetParameter(ON_RDK_DECAL_TEXTURE_INSTANCE, ON_nil_uuid).AsUuid();
    _cache.texture_instance_id_set = true;
  }

  return _cache.texture_instance_id;
}

void ON_Decal::CImpl::SetTextureInstanceId(const ON_UUID& id)
{
  if (!_cache.texture_instance_id_set || (_cache.texture_instance_id != id))
  {
    _cache.texture_instance_id = id;
    _cache.texture_instance_id_set = true;
    SetParameter(ON_RDK_DECAL_TEXTURE_INSTANCE, id);
  }
}

ON_Decal::Mappings ON_Decal::CImpl::Mapping(void) const
{
  if (Mappings::None == _cache.mapping)
  {
    const ON_wString s = GetParameter(ON_RDK_DECAL_MAPPING, ON_RDK_DECAL_MAPPING_UV).AsString();
    _cache.mapping = MappingFromString(s);
  }

  return _cache.mapping;
}

void ON_Decal::CImpl::SetMapping(Mappings m)
{
  if (_cache.mapping != m)
  {
    _cache.mapping = m;

    const wchar_t* s = L"";
    switch (m)
    {
    default: ON_ASSERT(false);
    case Mappings::None:        s = ON_RDK_DECAL_MAPPING_NONE;        break;
    case Mappings::Planar:      s = ON_RDK_DECAL_MAPPING_PLANAR;      break;
    case Mappings::Spherical:   s = ON_RDK_DECAL_MAPPING_SPHERICAL;   break;
    case Mappings::Cylindrical: s = ON_RDK_DECAL_MAPPING_CYLINDRICAL; break;
    case Mappings::UV:          s = ON_RDK_DECAL_MAPPING_UV;          break;
    }

    SetParameter(ON_RDK_DECAL_MAPPING, s);
  }
}

ON_Decal::Projections ON_Decal::CImpl::Projection(void) const
{
  if (Projections::None == _cache.projection)
  {
    const ON_wString s = GetParameter(ON_RDK_DECAL_PROJECTION, ON_RDK_DECAL_PROJECTION_NONE).AsString();
         if (s == ON_RDK_DECAL_PROJECTION_FORWARD)  _cache.projection = ON_Decal::Projections::Forward;
    else if (s == ON_RDK_DECAL_PROJECTION_BACKWARD) _cache.projection = ON_Decal::Projections::Backward;
    else if (s == ON_RDK_DECAL_PROJECTION_BOTH)     _cache.projection = ON_Decal::Projections::Both;
    else if (s == ON_RDK_DECAL_PROJECTION_NONE)     _cache.projection = ON_Decal::Projections::None;
    else ON_ASSERT(false);
  }

  return _cache.projection;
}

void ON_Decal::CImpl::SetProjection(Projections v)
{
  if (_cache.projection != v)
  {
    _cache.projection = v;

    const wchar_t* s = L"";
    switch (v)
    {
    default: ON_ASSERT(false);
    case ON_Decal::Projections::None:     s = ON_RDK_DECAL_PROJECTION_NONE;     break;
    case ON_Decal::Projections::Forward:  s = ON_RDK_DECAL_PROJECTION_FORWARD;  break;
    case ON_Decal::Projections::Backward: s = ON_RDK_DECAL_PROJECTION_BACKWARD; break;
    case ON_Decal::Projections::Both:     s = ON_RDK_DECAL_PROJECTION_BOTH;     break;
    }

    SetParameter(ON_RDK_DECAL_PROJECTION, s);
  }
}

bool ON_Decal::CImpl::MapToInside(void) const
{
  if (unset_bool == _cache.map_to_inside)
  {
    _cache.map_to_inside = GetParameter(ON_RDK_DECAL_MAP_TO_INSIDE_ON, false).AsBool() ? 1 : 0;
  }

  return 0 != _cache.map_to_inside;
}

void ON_Decal::CImpl::SetMapToInside(bool b)
{
  const int i = b ? 1 : 0;
  if (_cache.map_to_inside != i)
  {
    _cache.map_to_inside = i;
    SetParameter(ON_RDK_DECAL_MAP_TO_INSIDE_ON, b);
  }
}

double ON_Decal::CImpl::Transparency(void) const
{
  if (ON_UNSET_VALUE == _cache.transparency)
  {
    _cache.transparency = GetParameter(ON_RDK_DECAL_TRANSPARENCY, 0.0).AsDouble();
  }

  return _cache.transparency;
}

void ON_Decal::CImpl::SetTransparency(double v)
{
  if (_cache.transparency != v)
  {
    _cache.transparency = v;
    SetParameter(ON_RDK_DECAL_TRANSPARENCY, v);
  }
}

ON_3dPoint ON_Decal::CImpl::Origin(void) const
{
  if (ON_3dPoint::UnsetPoint == _cache.origin)
  {
    _cache.origin = GetParameter(ON_RDK_DECAL_ORIGIN, ON_3dPoint::Origin).As3dPoint();
  }

  return _cache.origin;
}

void ON_Decal::CImpl::SetOrigin(const ON_3dPoint& pt)
{
  if (_cache.origin != pt)
  {
    _cache.origin = pt;
    SetParameter(ON_RDK_DECAL_ORIGIN, pt);
  }
}

ON_3dVector ON_Decal::CImpl::VectorUp(void) const
{
  if (ON_3dVector::UnsetVector == _cache.vector_up)
  {
     _cache.vector_up = GetParameter(ON_RDK_DECAL_VECTOR_UP, ON_3dPoint::Origin).As3dPoint();
  }

  return _cache.vector_up;
}

void ON_Decal::CImpl::SetVectorUp(const ON_3dVector& v)
{
  if (_cache.vector_up != v)
  {
    _cache.vector_up = v;
    SetParameter(ON_RDK_DECAL_VECTOR_UP, ON_3dPoint(v));
  }
}

ON_3dVector ON_Decal::CImpl::VectorAcross(void) const
{
  if (ON_3dVector::UnsetVector == _cache.vector_across)
  {
     _cache.vector_across = GetParameter(ON_RDK_DECAL_VECTOR_ACROSS, ON_3dPoint::Origin).As3dPoint();
  }

  return _cache.vector_across;
}

void ON_Decal::CImpl::SetVectorAcross(const ON_3dVector& v)
{
  if (_cache.vector_across != v)
  {
    _cache.vector_across = v;
    SetParameter(ON_RDK_DECAL_VECTOR_ACROSS, ON_3dPoint(v));
  }
}

double ON_Decal::CImpl::Height(void) const
{
  if (ON_UNSET_VALUE == _cache.height)
  {
    _cache.height = GetParameter(ON_RDK_DECAL_HEIGHT, 1.0).AsDouble();
  }

  return _cache.height;
}

void ON_Decal::CImpl::SetHeight(double v)
{
  if (_cache.height != v)
  {
    _cache.height = v;
    SetParameter(ON_RDK_DECAL_HEIGHT, v);
  }
}

double ON_Decal::CImpl::Radius(void) const
{
  if (ON_UNSET_VALUE == _cache.radius)
  {
    _cache.radius = GetParameter(ON_RDK_DECAL_RADIUS, 1.0).AsDouble();
  }

  return _cache.radius;
}

void ON_Decal::CImpl::SetRadius(double v)
{
  if (_cache.radius != v)
  {
    _cache.radius = v;
    SetParameter(ON_RDK_DECAL_RADIUS, v);
  }
}

bool ON_Decal::CImpl::IsVisible(void) const
{
  if (unset_bool == _cache.visible)
  {
    _cache.visible = GetParameter(ON_RDK_DECAL_IS_VISIBLE, true).AsBool();
  }

  return 0 != _cache.visible;
}

void ON_Decal::CImpl::SetIsVisible(bool b)
{
  const int i = b ? 1 : 0;
  if (_cache.visible != i)
  {
    _cache.visible = i;
    SetParameter(ON_RDK_DECAL_IS_VISIBLE, b);
  }
}

void ON_Decal::CImpl::GetHorzSweep(double& sta, double& end) const
{
  if (ON_2dPoint::UnsetPoint == _cache.horz_sweep)
  {
    _cache.horz_sweep.x = GetParameter(ON_RDK_DECAL_HORZ_SWEEP_STA, 0.0).AsDouble();
    _cache.horz_sweep.y = GetParameter(ON_RDK_DECAL_HORZ_SWEEP_END, 0.0).AsDouble();
  }

  sta = _cache.horz_sweep.x;
  end = _cache.horz_sweep.y;
}

void ON_Decal::CImpl::SetHorzSweep(double sta, double end)
{
  const auto sweep = ON_2dPoint(sta, end);
  if (_cache.horz_sweep != sweep)
  {
    _cache.horz_sweep = sweep;
    SetParameter(ON_RDK_DECAL_HORZ_SWEEP_STA, sta);
    SetParameter(ON_RDK_DECAL_HORZ_SWEEP_END, end);
  }
}

void ON_Decal::CImpl::GetVertSweep(double& sta, double& end) const
{
  if (ON_2dPoint::UnsetPoint == _cache.vert_sweep)
  {
    _cache.vert_sweep.x = GetParameter(ON_RDK_DECAL_VERT_SWEEP_STA, 0.0).AsDouble();
    _cache.vert_sweep.y = GetParameter(ON_RDK_DECAL_VERT_SWEEP_END, 0.0).AsDouble();
  }

  sta = _cache.vert_sweep.x;
  end = _cache.vert_sweep.y;
}

void ON_Decal::CImpl::SetVertSweep(double sta, double end)
{
  const auto sweep = ON_2dPoint(sta, end);
  if (_cache.vert_sweep != sweep)
  {
    _cache.vert_sweep = sweep;
    SetParameter(ON_RDK_DECAL_VERT_SWEEP_STA, sta);
    SetParameter(ON_RDK_DECAL_VERT_SWEEP_END, end);
  }
}

void ON_Decal::CImpl::GetUVBounds(double& min_u, double& min_v, double& max_u, double& max_v) const
{
  if (UNSET_4D_POINT == _cache.uv_bounds)
  {
    _cache.uv_bounds.x = GetParameter(ON_RDK_DECAL_MIN_U, 0.0).AsDouble();
    _cache.uv_bounds.y = GetParameter(ON_RDK_DECAL_MIN_V, 0.0).AsDouble();
    _cache.uv_bounds.z = GetParameter(ON_RDK_DECAL_MAX_U, 1.0).AsDouble();
    _cache.uv_bounds.w = GetParameter(ON_RDK_DECAL_MAX_V, 1.0).AsDouble();
  }

  min_u = _cache.uv_bounds.x;
  min_v = _cache.uv_bounds.y;
  max_u = _cache.uv_bounds.z;
  max_v = _cache.uv_bounds.w;
}

void ON_Decal::CImpl::SetUVBounds(double min_u, double min_v, double max_u, double max_v)
{
  const auto bounds = ON_4dPoint(min_u, min_v, max_u, max_v);
  if (_cache.uv_bounds != bounds)
  {
    _cache.uv_bounds = bounds;
    SetParameter(ON_RDK_DECAL_MIN_U, min_u);
    SetParameter(ON_RDK_DECAL_MIN_V, min_v);
    SetParameter(ON_RDK_DECAL_MAX_U, max_u);
    SetParameter(ON_RDK_DECAL_MAX_V, max_v);
  }
}

ON_XMLNode* ON_Decal::CImpl::FindCustomNodeForRenderEngine(const ON_UUID& renderEngineId) const
{
  ON_XMLNode* child_node = nullptr;
  auto it = Node().GetChildIterator();
  while (nullptr != (child_node = it.GetNextChild()))
  {
    if (child_node->TagName() == ON_RDK_DECAL_CUSTOM)
    {
      const ON_XMLProperty* prop = child_node->GetNamedProperty(ON_RDK_DECAL_CUSTOM_RENDERER);
      if ((nullptr != prop) && (prop->GetValue().AsUuid() == renderEngineId))
        return child_node;
    }
  }

  return nullptr;
}

ON_Decal::ON_Decal()
{
  _impl = new CImpl;
}

ON_Decal::ON_Decal(ON_XMLNode& node)
{
  ON_ASSERT(node.TagName() == ON_RDK_DECAL);

  _impl = new CImpl(nullptr, node);
}

ON_Decal::ON_Decal(const ON_XMLNode& node)
{
  ON_ASSERT(node.TagName() == ON_RDK_DECAL);

  _impl = new CImpl(nullptr, node);
}

ON_Decal::ON_Decal(ON_DecalCollection& dc, ON_XMLNode& node)
{
  ON_ASSERT(node.TagName() == ON_RDK_DECAL);

  _impl = new CImpl(&dc, node);
}

ON_Decal::ON_Decal(const ON_Decal& d)
{
  _impl = new CImpl;
  operator = (d);
}

ON_Decal::~ON_Decal()
{
  delete _impl;
  _impl = nullptr;
}

const ON_Decal& ON_Decal::operator = (const ON_Decal& d)
{
  if (this != &d)
  {
    _impl->Node() = d._impl->Node();
  }

  return *this;
}

bool ON_Decal::operator == (const ON_Decal& d) const
{
  // This only checks if the basic parameters are equal. It ignores any custom data.

  if (TextureInstanceId() != d.TextureInstanceId()) return false;
  if (Mapping()           != d.Mapping())           return false;
  if (Projection()        != d.Projection())        return false;
  if (MapToInside()       != d.MapToInside())       return false;
  if (Transparency()      != d.Transparency())      return false;
  if (Origin()            != d.Origin())            return false;
  if (VectorUp()          != d.VectorUp())          return false;
  if (VectorAcross()      != d.VectorAcross())      return false;
  if (Height()            != d.Height())            return false;
  if (Radius()            != d.Radius())            return false;

  double sta1 = 0.0, end1 = 0.0, sta2 = 0.0, end2 = 0.0;
    GetHorzSweep(sta1, end1);
  d.GetHorzSweep(sta2, end2);
  if (!IsDoubleEqual(sta1, sta2)) return false;
  if (!IsDoubleEqual(end1, end2)) return false;

    GetVertSweep(sta1, end1);
  d.GetVertSweep(sta2, end2);
  if (!IsDoubleEqual(sta1, sta2)) return false;
  if (!IsDoubleEqual(end1, end2)) return false;

  double min_u1 = 0.0, min_v1 = 0.0, max_u1 = 0.0, max_v1 = 0.0;
  double min_u2 = 0.0, min_v2 = 0.0, max_u2 = 0.0, max_v2 = 0.0;
    GetUVBounds(min_u1, min_v1, max_u1, max_v1);
  d.GetUVBounds(min_u2, min_v2, max_u2, max_v2);
  if (!IsDoubleEqual(min_u1, min_u2)) return false;
  if (!IsDoubleEqual(min_v1, min_v2)) return false;
  if (!IsDoubleEqual(max_u1, max_u2)) return false;
  if (!IsDoubleEqual(max_v1, max_v2)) return false;

  return true;
}

bool ON_Decal::operator != (const ON_Decal& d) const
{
  return !(operator == (d));
}

ON_UUID ON_Decal::TextureInstanceId(void) const
{
  return _impl->TextureInstanceId();
}

void ON_Decal::SetTextureInstanceId(const ON_UUID& id)
{
  _impl->SetTextureInstanceId(id);
}

ON_Decal::Mappings ON_Decal::Mapping(void) const
{
  return _impl->Mapping();
}

void ON_Decal::SetMapping(Mappings m)
{
  _impl->SetMapping(m);
}

ON_Decal::Projections ON_Decal::Projection(void) const
{
  return _impl->Projection();
}

void ON_Decal::SetProjection(Projections p)
{
  _impl->SetProjection(p);
}

bool ON_Decal::MapToInside(void) const
{
  return _impl->MapToInside();
}

void ON_Decal::SetMapToInside(bool b)
{
  _impl->SetMapToInside(b);
}

double ON_Decal::Transparency(void) const
{
  return _impl->Transparency();
}

void ON_Decal::SetTransparency(double d)
{
  _impl->SetTransparency(d);
}

ON_3dPoint ON_Decal::Origin(void) const
{
  return _impl->Origin();
}

void ON_Decal::SetOrigin(const ON_3dPoint& pt)
{
  _impl->SetOrigin(pt);
}

ON_3dVector ON_Decal::VectorUp(void) const
{
  return _impl->VectorUp();
}

void ON_Decal::SetVectorUp(const ON_3dVector& vec)
{
  _impl->SetVectorUp(vec);
}

ON_3dVector ON_Decal::VectorAcross(void) const
{
  return _impl->VectorAcross();
}

void ON_Decal::SetVectorAcross(const ON_3dVector& vec)
{
  _impl->SetVectorAcross(vec);
}

double ON_Decal::Height(void) const
{
  return _impl->Height();
}

void ON_Decal::SetHeight(double d)
{
  _impl->SetHeight(d);
}

double ON_Decal::Radius(void) const
{
  return _impl->Radius();
}

void ON_Decal::SetRadius(double d)
{
  _impl->SetRadius(d);
}

void ON_Decal::GetHorzSweep(double& sta, double& end) const
{
  _impl->GetHorzSweep(sta, end);
}

void ON_Decal::SetHorzSweep(double sta, double end)
{
  _impl->SetHorzSweep(sta, end);
}

void ON_Decal::GetVertSweep(double& sta, double& end) const
{
  _impl->GetVertSweep(sta, end);
}

void ON_Decal::SetVertSweep(double sta, double end)
{
  _impl->SetVertSweep(sta, end);
}

void ON_Decal::GetUVBounds(double& min_u, double& min_v, double& max_u, double& max_v) const
{
  _impl->GetUVBounds(min_u, min_v, max_u, max_v);
}

void ON_Decal::SetUVBounds(double min_u, double min_v, double max_u, double max_v)
{
  _impl->SetUVBounds(min_u, min_v, max_u, max_v);
}

bool ON_Decal::IsVisible(void) const
{
  return _impl->IsVisible();
}

void ON_Decal::SetIsVisible(bool b)
{
  _impl->SetIsVisible(b);
}

ON_UUID ON_Decal::Id(void) const
{
  return _impl->Id();
}

ON_DECAL_CRC ON_Decal::DecalCRC(void) const
{
  return ComputeDecalCRC(0, _impl->Node());
}

ON__UINT32 ON_Decal::DataCRC(ON__UINT32 current_remainder) const
{
  return ComputeDecalCRC(current_remainder, _impl->Node());
}

void ON_Decal::GetCustomXML(const ON_UUID& renderEngineId, ON_XMLNode& custom_param_node) const
{
  custom_param_node.Clear();
  custom_param_node.SetTagName(ON_RDK_DECAL_CUSTOM_PARAMS);

  // Find the node for 'renderEngineId'.
  const ON_XMLNode* custom_node = _impl->FindCustomNodeForRenderEngine(renderEngineId);
  if (nullptr != custom_node)
  {
    // Get the parameter node and copy it to 'custom_param_node'.
    const ON_XMLNode* param_node = custom_node->GetNamedChild(ON_RDK_DECAL_CUSTOM_PARAMS);
    if (nullptr != param_node)
    {
      custom_param_node = *param_node;
    }
  }
}

bool ON_Decal::SetCustomXML(const ON_UUID& renderEngineId, const ON_XMLNode& custom_param_node)
{
  if (custom_param_node.TagName() != ON_RDK_DECAL_CUSTOM_PARAMS)
    return false;

  // If there is already a custom node for 'renderEngineId' then delete it.
  ON_XMLNode* custom_node = _impl->FindCustomNodeForRenderEngine(renderEngineId);
  if (nullptr != custom_node)
  {
    ON_XMLNode* parent = custom_node->Parent();
    if (nullptr != parent)
    {
      delete parent->DetachChild(*custom_node);
    }
  }

  // Attach the new custom node and set its 'renderer' property to be the render engine id.
  custom_node = _impl->Node().AttachChildNode(new ON_XMLNode(ON_RDK_DECAL_CUSTOM));
  ON_XMLProperty prop(ON_RDK_DECAL_CUSTOM_RENDERER, renderEngineId);
  custom_node->SetProperty(prop);

  // Attach a copy of the custom param node to the custom node.
  custom_node->AttachChildNode(new ON_XMLNode(custom_param_node));

  return true;
}

void ON_Decal::AppendCustomXML(const ON_XMLNode& custom_node)
{
  // This function only exists to support the RDK.

  ON_ASSERT(custom_node.TagName() == L"entire-custom-xml");

  ON_XMLNode* child = custom_node.FirstChild();
  while (nullptr != child)
  {
    _impl->Node().AttachChildNode(new ON_XMLNode(*child));

    child = custom_node.NextSibling();
  }
}

// Copied from IRhRdkDecal::GetTextureMapping -- TODO: Refactor. [JOHN-DECAL-FIX]
bool ON_Decal::GetTextureMapping(ON_TextureMapping& mappingOut) const
{
  const auto& decal = *this;
  using M = ON_Decal::Mappings;

  switch (decal.Mapping())
  {
  case M::Cylindrical:
    {
    // Orthogonal vectors in the end plane of cylinder.
    const auto vecPlaneXAxis = decal.VectorAcross();
    const auto vecPlaneYAxis = ON_CrossProduct(decal.VectorAcross(), -decal.VectorUp());

    // Center for the end of the cylinder.
    const auto ptCylinderEndCenter = decal.Origin() - decal.VectorUp() * decal.Height() * 0.5;

    // Plane for the end of the cylinder.
    ON_Plane plane(ptCylinderEndCenter, vecPlaneXAxis, vecPlaneYAxis);

    // Circle for the end of the cylinder.
    ON_Circle circle(plane, decal.Radius());

    // The cylinder itself..
    ON_Cylinder cylinder(circle, decal.Height());

    // Cylindrical mapping without caps.
    mappingOut.SetCylinderMapping(cylinder, false);

    return true;
    }

  case M::Spherical:
    {
    // Orthogonal vectors in the equatorial plane.
    const auto vecPlaneXAxis = decal.VectorAcross();
    const auto vecPlaneYAxis = ON_CrossProduct(decal.VectorAcross(), -decal.VectorUp());

    // Equatorial plane.
    ON_Plane plane(decal.Origin(), vecPlaneXAxis, vecPlaneYAxis);

    // The sphere itself.
    ON_Sphere sphere;
    sphere.plane = plane;
    sphere.radius = decal.Radius();

    // Spherical mapping.
    mappingOut.SetSphereMapping(sphere);

    return true;
    }

  case M::Planar:
    {
    const auto vecAcross = decal.VectorAcross();
    const auto vecUp = decal.VectorUp();
    const ON_Plane plane(decal.Origin(), vecAcross, vecUp);
    const ON_Interval xInterval(0.0, vecAcross.Length());
    const ON_Interval yInterval(0.0, vecUp.Length());
    const ON_Interval zInterval(0.0, 1.0);
    mappingOut.SetPlaneMapping(plane, xInterval, yInterval, zInterval);

    return true;
    }

  default: break;
  }

  return false;
}

/* Class ON_DecalNodeReader

   This object encapsulates the reading of all decal properties from XML nodes.
   It is used by the decal CRC calculation in ComputeDecalCRC().

   TODO: It could also be used by the ON_Decal XML node access (for Rhino 9).

*/
class ON_DecalNodeReader
{
public:
  ON_DecalNodeReader(const ON_XMLNode* decal_node);

  ON_XMLVariant Mapping(void) const           { return Value(ON_RDK_DECAL_MAPPING, ON_RDK_DECAL_MAPPING_NONE); }
  ON_XMLVariant Projection(void) const        { return Value(ON_RDK_DECAL_PROJECTION, ON_RDK_DECAL_PROJECTION_NONE); }
  ON_XMLVariant MapToInside(void) const       { return Value(ON_RDK_DECAL_MAP_TO_INSIDE_ON, _def.MapToInside()); } 
  ON_XMLVariant Transparency(void) const      { return Value(ON_RDK_DECAL_TRANSPARENCY    , _def.Transparency()); }
  ON_XMLVariant TextureInstanceId(void) const { return Value(ON_RDK_DECAL_TEXTURE_INSTANCE, _def.TextureInstanceId()); }
  ON_XMLVariant Height(void) const            { return Value(ON_RDK_DECAL_HEIGHT          , _def.Height()); }
  ON_XMLVariant Radius(void) const            { return Value(ON_RDK_DECAL_RADIUS          , _def.Radius()); }
  ON_XMLVariant Origin(void) const            { return Value(ON_RDK_DECAL_ORIGIN          , _def.Origin()); }
  ON_XMLVariant VectorUp(void) const          { return Value(ON_RDK_DECAL_VECTOR_UP       , ON_3dPoint(_def.VectorUp())); }
  ON_XMLVariant VectorAcross(void) const      { return Value(ON_RDK_DECAL_VECTOR_ACROSS   , ON_3dPoint(_def.VectorAcross())); }
  ON_XMLVariant HorzSweepSta(void) const      { return Value(ON_RDK_DECAL_HORZ_SWEEP_STA  , DefaultHorzSweepSta()); }
  ON_XMLVariant HorzSweepEnd(void) const      { return Value(ON_RDK_DECAL_HORZ_SWEEP_END  , DefaultHorzSweepEnd()); }
  ON_XMLVariant VertSweepSta(void) const      { return Value(ON_RDK_DECAL_VERT_SWEEP_STA  , DefaultVertSweepSta()); }
  ON_XMLVariant VertSweepEnd(void) const      { return Value(ON_RDK_DECAL_VERT_SWEEP_END  , DefaultVertSweepEnd()); }
  ON_XMLVariant MinU(void) const              { return Value(ON_RDK_DECAL_MIN_U           , DefaultMinU()); }
  ON_XMLVariant MinV(void) const              { return Value(ON_RDK_DECAL_MIN_V           , DefaultMinV()); }
  ON_XMLVariant MaxU(void) const              { return Value(ON_RDK_DECAL_MAX_U           , DefaultMaxU()); }
  ON_XMLVariant MaxV(void) const              { return Value(ON_RDK_DECAL_MAX_V           , DefaultMaxV()); }
  ON_XMLVariant IsTemporary(void) const       { return Value(ON_RDK_DECAL_IS_TEMPORARY    , false); }
  ON_XMLVariant IsVisible(void) const         { return Value(ON_RDK_DECAL_IS_VISIBLE      , _def.IsVisible()); }
  ON_XMLVariant InstanceId(void) const        { return Value(ON_RDK_DECAL_INSTANCE_ID     , _def.Id()); }

private:
  ON_XMLVariant Value(const wchar_t* wszName, const ON_XMLVariant& vDefault) const;

  double DefaultHorzSweepSta(void) const { double a, b; _def.GetHorzSweep(a, b); return a; }
  double DefaultHorzSweepEnd(void) const { double a, b; _def.GetHorzSweep(a, b); return b; }
  double DefaultVertSweepSta(void) const { double a, b; _def.GetVertSweep(a, b); return a; }
  double DefaultVertSweepEnd(void) const { double a, b; _def.GetVertSweep(a, b); return b; }

  double DefaultMinU(void) const { double a, b, c, d; _def.GetUVBounds(a, b, c, d); return a; }
  double DefaultMinV(void) const { double a, b, c, d; _def.GetUVBounds(a, b, c, d); return b; }
  double DefaultMaxU(void) const { double a, b, c, d; _def.GetUVBounds(a, b, c, d); return c; }
  double DefaultMaxV(void) const { double a, b, c, d; _def.GetUVBounds(a, b, c, d); return d; }

private:
  const ON_XMLNode* _decal_node;
  const ON_Decal _def;
};

ON_DecalNodeReader::ON_DecalNodeReader(const ON_XMLNode* decal_node)
  :
  _decal_node(decal_node)
{
  ON_ASSERT(_decal_node && (_decal_node->TagName() == ON_RDK_DECAL));
}

ON_XMLVariant ON_DecalNodeReader::Value(const wchar_t* wszName, const ON_XMLVariant& vDefault) const
{
  ON_XMLVariant vValue = vDefault;

  if (nullptr != _decal_node)
  {
    const ON_XMLParameters p(*_decal_node);
    p.GetParam(wszName, vValue);
  }

  return vValue;
}

#if (defined _DEBUG) && (defined HUMAN_READABLE_DECAL_CRC)
#define ON_DECAL_PROP_NAME(s) , s
static void DecalUpdateCRC(ON_DECAL_CRC& crc, const ON_XMLVariant value, const wchar_t* name)
{
  crc = value.DataCRC(crc);
  crc._info1 += ON_wString(name) + L"=" + value.AsString() + ON_wString(L" ");
  crc._info2 += ON_wString(name) + L"=" + value.AsString() + ON_wString(L"\n");
}
#else
#define ON_DECAL_PROP_NAME(s)
static void DecalUpdateCRC(ON_DECAL_CRC& crc, const ON_XMLVariant& value)
{
  crc = value.DataCRC(crc);
}
#endif

static void DecalUpdateCRC_Custom(const ON_XMLNode& decal_node, ON_DECAL_CRC& crc)
{
  // Look for custom data nodes and for each one, find the parameter node and then iterate over its
  // children and CRC the properties. For now, we will have to rely on the raw XML. A better solution
  // would be to have the plug-in that created this XML calculate the CRC itself.

  const ON_wString custom = L"[CUSTOM] ";

  auto it = decal_node.GetChildIterator();
  ON_XMLNode* pChildNode = nullptr;
  while (nullptr != (pChildNode = it.GetNextChild()))
  {
    if (pChildNode->TagName() != ON_RDK_DECAL_CUSTOM)
      continue; // Not a custom data node.

    const ON__UINT32 crc_before_custom_params = crc;

    // Find the custom parameter node.
    const ON_XMLNode* pParamNode = pChildNode->GetNamedChild(ON_RDK_DECAL_CUSTOM_PARAMS);
    if (nullptr != pParamNode)
    {
      // Iterate over the nodes inside the custom parameter node.
      const ON_XMLParameters p(*pParamNode);
      auto* iterator = p.NewIterator();
      if (nullptr != iterator)
      {
        ON_wString sParamName;
        ON_XMLVariant vParamValue;
        while (iterator->Next(sParamName, vParamValue))
        {
          DecalUpdateCRC(crc, vParamValue ON_DECAL_PROP_NAME(custom + sParamName));
        }

        delete iterator;
      }

      if (crc != crc_before_custom_params)
      {
        // 20th January 2025 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-71351
        // Since the crc has changed, there must be some custom params, so only now do we include the render
        // engine id. Prior to this, the render engine id was getting included even when there were no custom
        // params. This caused the UI to overlook decals which were programatically created by clients.
        const ON_XMLProperty* prop = pChildNode->GetNamedProperty(ON_RDK_DECAL_CUSTOM_RENDERER);
        if (nullptr != prop)
        {
          // Include the render engine id.
          const ON_UUID uuid = prop->GetValue().AsUuid();
          DecalUpdateCRC(crc, uuid ON_DECAL_PROP_NAME(custom + L"render_engine_id"));
        }
      }
    }
  }
}

ON_DECAL_CRC ON_Decal::ComputeDecalCRC(ON__UINT32 current_remainder, const ON_XMLNode& decal_node) // Static.
{
  // The CRC of a decal is a unique value based on its state. It's created by CRC-ing all the decal properties
  // that affect the decal's appearance. We do not include the 'IsTemporary' property in the CRC because whether
  // or not a decal is temporary has nothing to do with what it looks like. We do however, include the 'IsVisible'
  // property because a decal being visible or invisible actually affects its appearance. Also, the RDK change
  // queue relies on the CRC to update the viewport so including the visibility is critical. Furthermore, the
  // CRC only includes the properties that are relevant for the decal's mapping type.

  ON_DECAL_CRC crc = current_remainder;

  if (decal_node.TagName() == ON_RDK_DECAL)
  {
    const ON_DecalNodeReader d(&decal_node);

    DecalUpdateCRC(crc, d.Mapping()            ON_DECAL_PROP_NAME(L"mapping"));
    DecalUpdateCRC(crc, d.IsVisible()          ON_DECAL_PROP_NAME(L"visible"));
    DecalUpdateCRC(crc, d.Transparency()       ON_DECAL_PROP_NAME(L"transparency"));
    DecalUpdateCRC(crc, d.TextureInstanceId()  ON_DECAL_PROP_NAME(L"texture_id"));

    const ON_Decal::Mappings mapping = MappingFromString(d.Mapping().AsString());

    if (Mappings::UV == mapping)
    {
      DecalUpdateCRC(crc, d.MinU()             ON_DECAL_PROP_NAME(L"min_u"));
      DecalUpdateCRC(crc, d.MinV()             ON_DECAL_PROP_NAME(L"min_v"));
      DecalUpdateCRC(crc, d.MaxU()             ON_DECAL_PROP_NAME(L"max_u"));
      DecalUpdateCRC(crc, d.MaxV()             ON_DECAL_PROP_NAME(L"max_v"));
    }
    else
    {
      DecalUpdateCRC(crc, d.Origin()           ON_DECAL_PROP_NAME(L"origin"));
      DecalUpdateCRC(crc, d.VectorUp()         ON_DECAL_PROP_NAME(L"up"));
      DecalUpdateCRC(crc, d.VectorAcross()     ON_DECAL_PROP_NAME(L"across"));

      if ((Mappings::Cylindrical == mapping) || (Mappings::Spherical == mapping))
      {
        DecalUpdateCRC(crc, d.MapToInside()    ON_DECAL_PROP_NAME(L"map_to_inside"));
        DecalUpdateCRC(crc, d.Radius()         ON_DECAL_PROP_NAME(L"radius"));
        DecalUpdateCRC(crc, d.HorzSweepSta()   ON_DECAL_PROP_NAME(L"horz_sweep_sta"));
        DecalUpdateCRC(crc, d.HorzSweepEnd()   ON_DECAL_PROP_NAME(L"horz_sweep_end"));

        if (Mappings::Cylindrical == mapping)
        {
          DecalUpdateCRC(crc, d.Height()       ON_DECAL_PROP_NAME(L"height"));
        }
        else
        if (Mappings::Spherical == mapping)
        {
          DecalUpdateCRC(crc, d.VertSweepSta() ON_DECAL_PROP_NAME(L"vert_sweep_sta"));
          DecalUpdateCRC(crc, d.VertSweepEnd() ON_DECAL_PROP_NAME(L"vert_sweep_end"));
        }
      }
      else
      if (Mappings::Planar == mapping)
      {
        DecalUpdateCRC(crc, d.Projection()     ON_DECAL_PROP_NAME(L"projection"));
      }
    }

    DecalUpdateCRC_Custom(decal_node, crc);

    // Make sure it's not nil.
    if (crc == ON_NIL_DECAL_CRC)
      crc = 0xFFFFFFFF;
  }

  return crc;
}

// ON_DecalCollection

ON_DecalCollection::~ON_DecalCollection()
{
  ClearDecalArray();
}

int ON_DecalCollection::FindDecalIndex(const ON_UUID& id) const
{
  for (int i = 0; i < m_decals.Count(); i++)
  {
    if (m_decals[i]->Id() == id)
      return i;
  }

  return -1;
}

ON_Decal* ON_DecalCollection::AddDecal(void)
{
  // Ensure the array is populated before adding a new decal.
  GetDecalArray();

  ON_Decal* decal = nullptr;

  ON_XMLNode* decals_node = m_root_node.CreateNodeAtPath(ON_RDK_UD_ROOT  ON_XML_SLASH  ON_RDK_DECALS);
  if (nullptr != decals_node)
  {
    // Add an XML node for the new decal.
    auto* decal_node = new ON_XMLNode(ON_RDK_DECAL);
    decals_node->AttachChildNode(decal_node);

    // Add the new decal. It stores a pointer to the new XML node. This is safe because
    // the decals have the same lifetime as the root node that owns the XML nodes.
    decal = new ON_Decal(*this, *decal_node);
    m_decals.Append(decal);

    SetChanged();
  }

  return decal;
}

bool ON_DecalCollection::RemoveDecal(const ON_Decal& decal)
{
  // Ensure the array is populated before deleting a decal.
  GetDecalArray();

  // Remove the decal from the XML by finding the XML node with the same decal CRC
  // and then deleting that node.
  const ON__UINT32 decal_crc = decal.DecalCRC();

  const wchar_t* path = ON_RDK_UD_ROOT  ON_XML_SLASH  ON_RDK_DECALS;
  ON_XMLNode* decals_node = m_root_node.GetNodeAtPath(path);
  if (nullptr != decals_node)
  {
    auto it = decals_node->GetChildIterator();
    ON_XMLNode* child_node = nullptr;
    while (nullptr != (child_node = it.GetNextChild()))
    {
      if (ON_DecalCRCFromNode(*child_node) == decal_crc)
      {
        child_node->Remove();
        break;
      }
    }
  }

  // Find the decal in the array.
  const int index = FindDecalIndex(decal.Id());
  if (index < 0)
    return false;

  // Delete it.
  delete m_decals[index];
  m_decals.Remove(index);

  return true;
}

void ON_DecalCollection::RemoveAllDecals(void)
{
  m_root_node.Clear();
  m_root_node.CreateNodeAtPath(ON_RDK_UD_ROOT);

  ClearDecalArray();
}

void ON_DecalCollection::ClearDecalArray(void)
{
  // 12th July 2023 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-75697
  // Only call SetChanged() if a decal is actually deleted.
  const int count = m_decals.Count();
  if (count > 0)
  {
    for (int i = 0; i < count; i++)
    {
      delete m_decals[i];
    }

    m_decals.Destroy();

    SetChanged();
  }

  m_populated = false;
}

const ON_DecalCollection& ON_DecalCollection::operator = (const ON_DecalCollection& dc)
{
  ClearDecalArray();

  for (int i = 0; i < dc.m_decals.Count(); i++)
  {
    ON_Decal* decal = dc.m_decals[i];
    if (nullptr != decal)
    {
      m_decals.Append(new ON_Decal(*decal));
    }
  }

  m_populated = dc.m_populated;

  return *this;
}

const ON_SimpleArray<ON_Decal*>& ON_DecalCollection::GetDecalArray(void) const
{
  // 19th February 2025 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-86089
  // The m_populated flag is an optimization designed to make sure we only populate the array when something
  // changes. Unfortunately, in Rhino 8, I forgot to add code to detect when a decal changes externally to this
  // class, and the array (which is essentially a cache) becomes invalid. This is fixed in Rhino 9 but the fix
  // is too complicated to backport to Rhino 8, so to get around this I'm just going to remove the optimization.

//if (!m_populated) // Always repopulate the array.
  {
    for (int i = 0; i < m_decals.Count(); i++)
    {
      delete m_decals[i];
    }

    m_decals.Destroy();

    Populate();

    m_populated = true;
  }

  return m_decals;
}

void ON_DecalCollection::Populate(void) const
{
  if (nullptr == m_attr)
    return;

  if (GetEntireDecalXML(*m_attr, m_root_node))
  {
    const wchar_t* path = ON_RDK_UD_ROOT  ON_XML_SLASH  ON_RDK_DECALS;
    ON_XMLNode* decals_node = m_root_node.GetNodeAtPath(path);
    if (nullptr != decals_node)
    {
      // Iterate over the decals under the decals node adding a new decal for each one.
      ON_ASSERT(m_decals.Count() == 0);
      auto it = decals_node->GetChildIterator();
      ON_XMLNode* child_node = nullptr;
      while (nullptr != (child_node = it.GetNextChild()))
      {
        auto* decal = new ON_Decal(*const_cast<ON_DecalCollection*>(this), *child_node);
        m_decals.Append(decal);
      }
    }
  }
}

void ON_DecalCollection::SetChanged(void)
{
  m_changed = true;
}

void ON_DecalCollection::UpdateUserData(unsigned int archive_3dm_version) const
{
  if (m_changed)
  {
    // 12th July 2023 John Croudy, https://mcneel.myjetbrains.com/youtrack/issue/RH-75697
    // For there to be something useful in the XML, the root node must have at least one child node.
    if (m_root_node.ChildCount() > 0)
    {
      SetRDKObjectInformation(*m_attr, m_root_node.String(), archive_3dm_version);
    }

    m_changed = false;
  }
}
