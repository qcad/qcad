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

ON_OBJECT_IMPLEMENT(ON_ModelGeometryComponent,ON_ModelComponent,"29D1B827-41CE-45C1-B265-0686AA391DAE");

const ON_ModelGeometryComponent* ON_ModelGeometryComponent::FromModelComponentRef(
  const class ON_ModelComponentReference& model_component_reference,
  const ON_ModelGeometryComponent* none_return_value
  )
{
  const ON_ModelGeometryComponent* p = ON_ModelGeometryComponent::Cast(model_component_reference.ModelComponent());
  return (nullptr != p) ? p : none_return_value;
}

bool ON_ModelGeometryComponent::UpdateReferencedComponents(
  const class ON_ComponentManifest& source_manifest,
  const class ON_ComponentManifest& destination_manifest,
  const class ON_ManifestMap& manifest_map
  )
{
  bool bGeometryUpdated = false;
  for (;;)
  {
    ON_Object* geometry = m_geometry_sp.get();
    if (nullptr == geometry)
    {
      bGeometryUpdated = true;
      break;
    }
    bGeometryUpdated = geometry->UpdateReferencedComponents(source_manifest,destination_manifest,manifest_map);
    break;
  }

  bool bAttributesUpdated = false;
  for (;;)
  {
    ON_3dmObjectAttributes* attributes = m_attributes_sp.get();
    if (nullptr == attributes)
    {
      bAttributesUpdated = true;
      break;
    }
    if (&ON_3dmObjectAttributes::Unset == attributes)
      return false;
    if (&ON_3dmObjectAttributes::DefaultAttributes == attributes)
      return false;

    bAttributesUpdated = attributes->UpdateReferencedComponents(source_manifest,destination_manifest,manifest_map);
    break;
  }

  return bGeometryUpdated && bAttributesUpdated;
}


static ON_ModelComponent::Type Internal_ON_ModelGeometry_TypeFilter(ON_ModelComponent::Type type)
{
  switch (type)
  {
  case ON_ModelComponent::Type::Unset:
    return type;
    break;
  case ON_ModelComponent::Type::Image:
    break;
  case ON_ModelComponent::Type::TextureMapping:
    break;
  case ON_ModelComponent::Type::RenderMaterial:
    break;
  case ON_ModelComponent::Type::LinePattern:
    break;
  case ON_ModelComponent::Type::Layer:
    break;
  case ON_ModelComponent::Type::Group:
    break;
  case ON_ModelComponent::Type::TextStyle:
    break;
  case ON_ModelComponent::Type::DimStyle:
    break;
  case ON_ModelComponent::Type::RenderLight:
    return type;
    break;
  case ON_ModelComponent::Type::HatchPattern:
    break;
  case ON_ModelComponent::Type::InstanceDefinition:
    break;
  case ON_ModelComponent::Type::ModelGeometry:
    return type;
    break;
  case ON_ModelComponent::Type::HistoryRecord:
    break;
  case ON_ModelComponent::Type::Mixed:
    break;
  default:
    break;
  }

  ON_ERROR("Invalid ON_ModelComponent::Type for ON_ModelGeometryComponent.");
  return ON_ModelComponent::Type::Unset;
}

ON_ModelGeometryComponent::ON_ModelGeometryComponent() ON_NOEXCEPT
  : ON_ModelComponent(Internal_ON_ModelGeometry_TypeFilter(ON_ModelComponent::Type::Unset))
{}

ON_ModelGeometryComponent::ON_ModelGeometryComponent( ON_ModelComponent::Type type ) ON_NOEXCEPT
  : ON_ModelComponent(Internal_ON_ModelGeometry_TypeFilter(type))
{}

ON_ModelGeometryComponent::~ON_ModelGeometryComponent()
{
  // This destructor is explicitly implemented to insure m_geometry_sp
  // and m_attributes_sp are destroyed by the same c-runtime
  // that creates them.
}

ON_ModelGeometryComponent::ON_ModelGeometryComponent(const ON_ModelGeometryComponent& src) 
  : ON_ModelComponent(Internal_ON_ModelGeometry_TypeFilter(src.ComponentType()), src)
  , m_geometry_sp(src.m_geometry_sp)
  , m_attributes_sp(src.m_attributes_sp)
{}

ON_ModelGeometryComponent& ON_ModelGeometryComponent::operator=(const ON_ModelGeometryComponent& src)
{
  if ( this != &src )
  {
    ON_ModelComponent::operator=(src);
    m_geometry_sp.reset();
    m_geometry_sp = src.m_geometry_sp;
    m_attributes_sp.reset();
    m_attributes_sp = src.m_attributes_sp;
    SetComponentType(Internal_ON_ModelGeometry_TypeFilter(src.ComponentType()));
  }
  return *this;
}

ON_ModelGeometryComponent* ON_ModelGeometryComponent::CreateForExperts(
  bool bManageGeometry,
  ON_Object* geometry_object,
  bool bManageAttributes,
  ON_3dmObjectAttributes* attributes,
  ON_ModelGeometryComponent* model_geometry_component
  )
{
  ON_ModelComponent::Type component_type;
  ON_Geometry* geometry = ON_Geometry::Cast(geometry_object);
  ON_Light* light = ON_Light::Cast(geometry);

  if (nullptr != light)
    component_type = ON_ModelComponent::Type::RenderLight;
  else if (nullptr != geometry)
    component_type = ON_ModelComponent::Type::ModelGeometry;
  else
    component_type = ON_ModelComponent::Type::Unset;

  if (nullptr == attributes)
  {
    bManageAttributes = true;
    attributes = new ON_3dmObjectAttributes();
    if (nullptr != light)
    {
      attributes->m_uuid = light->m_light_id;
      attributes->m_name = light->m_light_name;
    }
  }

  if ( ON_nil_uuid == attributes->m_uuid )
    attributes->m_uuid = ON_CreateId();

  if (nullptr != light)
  {
    light->m_light_id = attributes->m_uuid;
    light->m_light_name = attributes->m_name;
  }

  if ( nullptr == model_geometry_component)
    model_geometry_component = new ON_ModelGeometryComponent(component_type);

  model_geometry_component->m_geometry_sp
    = bManageGeometry
    ? ON_MANAGED_SHARED_PTR(ON_Geometry,geometry)
    : ON_UNMANAGED_SHARED_PTR(ON_Geometry,geometry);


  model_geometry_component->m_attributes_sp
    = bManageAttributes
    ? ON_MANAGED_SHARED_PTR(ON_3dmObjectAttributes,attributes)
    : ON_UNMANAGED_SHARED_PTR(ON_3dmObjectAttributes,attributes);

  model_geometry_component->SetId(attributes->m_uuid);
  if ( attributes->m_name.IsNotEmpty() )
    model_geometry_component->SetName(attributes->m_name);

  return model_geometry_component;
}

ON_ModelGeometryComponent* ON_ModelGeometryComponent::Create(
  const class ON_Object& geometry_object,
  const class ON_3dmObjectAttributes* attributes,
  ON_ModelGeometryComponent* model_geometry_component
  )
{
  const bool bManageGeometry = true;
  ON_Object* managed_geometry_object = geometry_object.Duplicate();
  const bool bManageAttributes = (nullptr != attributes);
  ON_3dmObjectAttributes* managed_attributes = (nullptr != attributes) ? attributes->Duplicate() : nullptr;
  return ON_ModelGeometryComponent::CreateForExperts(bManageGeometry,managed_geometry_object,bManageAttributes,managed_attributes,model_geometry_component);
}

ON_ModelGeometryComponent* ON_ModelGeometryComponent::CreateManaged(
  ON_Object* geometry_object,
  ON_3dmObjectAttributes* object_attributes,
  ON_ModelGeometryComponent* model_geometry_component
  )
{
  bool bManageGeometry = true;
  bool bManageAttributes = true;
  return ON_ModelGeometryComponent::CreateForExperts(bManageGeometry,geometry_object,bManageAttributes,object_attributes,model_geometry_component);
}

#if defined(ON_HAS_RVALUEREF)
ON_ModelGeometryComponent::ON_ModelGeometryComponent( ON_ModelGeometryComponent&& src) ON_NOEXCEPT
  : ON_ModelComponent(std::move(src))
  , m_geometry_sp(std::move(src.m_geometry_sp))
  , m_attributes_sp(std::move(src.m_attributes_sp))
{}

ON_ModelGeometryComponent& ON_ModelGeometryComponent::operator=(ON_ModelGeometryComponent&& src)
{
  if ( this != &src )
  {
    m_geometry_sp.reset();
    m_attributes_sp.reset();
    ON_ModelComponent::operator=(std::move(src));
    m_geometry_sp = std::move(src.m_geometry_sp);
    m_attributes_sp = std::move(src.m_attributes_sp);
  }
  return *this;
}
#endif

bool ON_ModelGeometryComponent::IsEmpty() const
{
  return (nullptr == m_geometry_sp.get());
}

bool ON_ModelGeometryComponent::IsInstanceDefinitionGeometry() const
{
  if (nullptr != m_geometry_sp.get())
  {
    const ON_3dmObjectAttributes* attributes = m_attributes_sp.get();
    return (nullptr != attributes && attributes->IsInstanceDefinitionObject() );
  }
  return false;
}


const ON_Geometry* ON_ModelGeometryComponent::Geometry(
  const ON_Geometry* no_geometry_return_value
  ) const
{
  const ON_Geometry* ptr = m_geometry_sp.get();
  return (nullptr != ptr) ? ptr : no_geometry_return_value;
}

const ON_3dmObjectAttributes* ON_ModelGeometryComponent::Attributes(
  const ON_3dmObjectAttributes* no_attributes_return_value
  ) const
{
  const ON_3dmObjectAttributes* ptr = m_attributes_sp.get();
  return (nullptr != ptr) ? ptr : no_attributes_return_value;
}

ON_Geometry* ON_ModelGeometryComponent::ExclusiveGeometry() const
{
  return
    (1 == m_geometry_sp.use_count())
    ? m_geometry_sp.get()
    : nullptr;
}

ON_3dmObjectAttributes* ON_ModelGeometryComponent::ExclusiveAttributes() const
{
  return
    (1 == m_attributes_sp.use_count())
    ? m_attributes_sp.get()
    : nullptr;
}

void ON_ModelGeometryComponent::Dump( ON_TextLog& text_log ) const
{
  ON_ModelComponent::Dump(text_log);

  text_log.Print("Attributes:\n");
  text_log.PushIndent();
  const ON_3dmObjectAttributes* attributes = Attributes(nullptr);
  if (nullptr == attributes)
    text_log.Print("Unset\n");
  else
  {
    attributes->Dump(text_log);
    // attributes user data
    const ON_UserData* ud = attributes->FirstUserData();
    while (0 != ud)
    {
      text_log.Print("Attributes user data:\n");
      text_log.PushIndent();
      ud->Dump(text_log);
      text_log.PopIndent();
      ud = ud->Next();
    }
  }
  text_log.PopIndent();

  text_log.Print("Geometry:\n");
  text_log.PushIndent();
  const ON_Object* geometry = Geometry(nullptr);
  if (nullptr == geometry)
    text_log.Print("Unset\n");
  else
  {
    geometry->Dump(text_log);
    // geometry user data
    const ON_UserData* ud = geometry->FirstUserData();
    while (0 != ud)
    {
      text_log.Print("Geometry user data:\n");
      text_log.PushIndent();
      ud->Dump(text_log);
      text_log.PopIndent();
      ud = ud->Next();
    }
  }
  text_log.PopIndent();
}
