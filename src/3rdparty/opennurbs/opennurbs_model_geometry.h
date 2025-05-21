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

#if !defined(ON_MODEL_GEOMETRY_INC_)
#define ON_MODEL_GEOMETRY_INC_

/*
Description:
  Used to store geometry table object definition and attributes in an ONX_Model.
*/
class ON_CLASS ON_ModelGeometryComponent : public ON_ModelComponent
{
  ON_OBJECT_DECLARE(ON_ModelGeometryComponent);

public:
  static const ON_ModelGeometryComponent Unset;

  static const ON_ModelGeometryComponent* FromModelComponentRef(
    const class ON_ModelComponentReference& model_component_reference,
    const ON_ModelGeometryComponent* none_return_value
    );

  bool UpdateReferencedComponents(
    const class ON_ComponentManifest& source_manifest,
    const class ON_ComponentManifest& destination_manifest,
    const class ON_ManifestMap& manifest_map
    ) override;
  
  bool IsEmpty() const;

  bool IsInstanceDefinitionGeometry() const;

private:

public:
  ON_ModelGeometryComponent()  ON_NOEXCEPT;

  ON_ModelGeometryComponent(
    ON_ModelComponent::Type type
  ) ON_NOEXCEPT;

  ~ON_ModelGeometryComponent();
  ON_ModelGeometryComponent(const ON_ModelGeometryComponent&);
  ON_ModelGeometryComponent& operator=(const ON_ModelGeometryComponent&);

#if defined(ON_HAS_RVALUEREF)
  // rvalue copy constructor
  ON_ModelGeometryComponent( ON_ModelGeometryComponent&& ) ON_NOEXCEPT;
  // rvalue assignment operator
  ON_ModelGeometryComponent& operator=( ON_ModelGeometryComponent&& );
#endif

  void Dump(
    ON_TextLog& text_log
    ) const override;

  /*
  Parameters:
    geometry - [in]
      ON_Curve, ON_Surface, ON_Brep, ON_Mesh, ON_Light, annotation, detail, ...
      A new copy of the geometry is managed by the ON_ModelGeometryComponent class.
    attributes - [in]
      nullptr if not available.
      A new copy of the attributes is managed by the ON_ModelGeometryComponent class.
    model_geometry_component - [in]
      If not nullptr, this class is set. Otherwise operator new allocates
      an ON_ModelGeometryComponent class.
  Remarks:
    The returned ON_ModelGeometryComponent manages geometry and attributes and will
    eventually delete them.
  */
  static ON_ModelGeometryComponent* Create(
    const class ON_Object& model_geometry,
    const class ON_3dmObjectAttributes* attributes,
    ON_ModelGeometryComponent* model_geometry_component
    );

  /*
  Parameters:
    geometry_object - [in]
      ON_Curve, ON_Surface, ON_Brep, ON_Mesh, ON_Light, annotation, detail, ...
      geometry_object was created on the heap using operator new and 
      the ON_ModelGeometryComponent destructor will delete geometry_object.
    attributes - [in]
      attributes is nullptr or was created on the heap using operator new
      and the ON_ModelGeometryComponent destructor will delete attributes.
    model_geometry - [in]
      If not nullptr, this class is set. Otherwise operator new allocates
      an ON_ModelGeometryComponent class.
  Remarks:
    The returned ON_ModelGeometryComponent manages geometry_object and attributes and will
    eventually delete them.
  */
  static ON_ModelGeometryComponent* CreateManaged(
    class ON_Object* geometry_object,
    class ON_3dmObjectAttributes* attributes,
    ON_ModelGeometryComponent* model_geometry_component
    );

  /*
  Parameters:
    bManageGeometry - [in]
      If true, geometry_object was created on the heap using operator new and 
      the ON_ModelGeometryComponent destructor will delete geometry_object. Otherwise
      the expert caller is carefully managing the geometry_object instance and memory.
    geometry_object - [in]
      ON_Curve, ON_Surface, ON_Brep, ON_Mesh, ON_Light, annotation, detail, ...
    bManageAttributes - [in]
      If true, attributes is nullptr or was created on the heap using operator new
      and the ON_ModelGeometryComponent destructor will delete attributes. Otherwise
      the expert caller is carefully managing the attributes instance and memory.
    attributes - [in]
      nullptr if not available
    model_geometry_component - [in]
      If not nullptr, this class is set. Otherwise operator new allocates
      an ON_ModelGeometryComponent class.
  */
  static ON_ModelGeometryComponent* CreateForExperts(
    bool bManageGeometry,
    class ON_Object* geometry_object,
    bool bManageAttributes,
    class ON_3dmObjectAttributes* attributes,
    ON_ModelGeometryComponent* model_geometry_component
    );

  /*
  Description:
    Get a pointer to geometry. The returned pointer may be shared
    and should not be used to modify the geometry.
  Parameters:
    no_geometry_return_value - [in]
      This value is returned if no geometric object has been set.
      A good choices for this parameter's value depends on the context.
      Common options are nullptr.
  Returns:
    The curve, surface, annotation, detail, light, ... geometry, 
    or no_geometry_return_value if the geometry has not been set.    
    If the geometry is a light, then ComponentType() will return ON_ModelComponent::Type::RenderLight.    
    If the geometry is set and something besides light, then ComponentType() 
    will return ON_ModelComponent::Type::ModelGeometry.
    Otherwise, ComponentType() will return ON_ModelComponent::Type::ModelGeometry::Unset.
  See Also:
    ON_ModelGeometryComponent::Attributes()
    ON_ModelGeometryComponent::Geometry()
    ON_ModelGeometryComponent::ExclusiveAttributes()
    ON_ModelGeometryComponent::ExclusiveGeometry();
    ON_ModelComponentRef::ExclusiveModelComponent();
    ONX_Model::ComponentFromRuntimeSerialNumber()
  */
  const class ON_Geometry* Geometry(
    const class ON_Geometry* no_geometry_return_value
    ) const;

  /*
  Description:
    Get a pointer to geometry that can be used to modify the geometry.
    The returned pointer is not shared at the time it is returned
    and will not be shared until a copy of this ON_ModelGeometryComponent
    is created.
  Returns:
    If this ON_ModelGeometryComponent is the only reference to the geometry, 
    then a pointer to the geometry is returned.
    Otherwise, nullptr is returned.
  See Also:
    ON_ModelGeometryComponent::Attributes()
    ON_ModelGeometryComponent::Geometry()
    ON_ModelGeometryComponent::ExclusiveAttributes()
    ON_ModelGeometryComponent::ExclusiveGeometry();
    ON_ModelComponentRef::ExclusiveModelComponent();
    ONX_Model::ComponentFromRuntimeSerialNumber()
  */
  class ON_Geometry* ExclusiveGeometry() const;

  /*
  Description:
    Get a pointer to attributes. The returned pointer may be shared
    and should not be used to modify the attributes.
  Parameters:
    no_attributes_return_value - [in]
      This value is returned if no attributes have been set.
      A good choices for this parameter's value depends on the context.
      Common options are nullptr, &ON_3dmObjectAttributes::Unset,
      &ON_3dmObjectAttributes::Default, or the model's current default attributes. 
  Returns:
    The layer, rendering and other attributes for this element, 
    or no_attributes_return_value if the attributes have not been set.
  See Also:
    ON_ModelGeometryComponent::Attributes()
    ON_ModelGeometryComponent::Geometry()
    ON_ModelGeometryComponent::ExclusiveAttributes()
    ON_ModelGeometryComponent::ExclusiveGeometry();
    ON_ModelComponentRef::ExclusiveModelComponent();
    ONX_Model::ComponentFromRuntimeSerialNumber()
  */
  const ON_3dmObjectAttributes* Attributes(
    const ON_3dmObjectAttributes* no_attributes_return_value
    ) const;

  /*
  Description:
    Get a pointer to attributes that can be used to modify the attributes.
    The returned pointer is not shared at the time it is returned
    and will not be shared until a copy of this ON_ModelGeometryComponent
    is created.
  Returns:
    If this ON_ModelGeometryComponent is the only reference to the attributes, 
    then a pointer to the attributes is returned.
    Otherwise, nullptr is returned.
  See Also:
    ON_ModelGeometryComponent::Attributes()
    ON_ModelGeometryComponent::Geometry()
    ON_ModelGeometryComponent::ExclusiveAttributes()
    ON_ModelGeometryComponent::ExclusiveGeometry();
    ON_ModelComponentRef::ExclusiveModelComponent();
    ONX_Model::ComponentFromRuntimeSerialNumber()
  */
  class ON_3dmObjectAttributes* ExclusiveAttributes() const;

private:

#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4251 ) 
  // C4251: ... needs to have dll-interface to be used by clients of class ...
  // m_geometry_sp is private and all code that manages m_sp is explicitly implemented in the DLL.
  // m_attributes_sp is private and all code that manages m_sp is explicitly implemented in the DLL.
private:
  std::shared_ptr<ON_Geometry> m_geometry_sp;
private:
  std::shared_ptr<ON_3dmObjectAttributes> m_attributes_sp;
#pragma ON_PRAGMA_WARNING_POP
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_ModelGeometryComponent*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<const ON_ModelGeometryComponent*>;
#endif

#endif
