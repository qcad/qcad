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

#if !defined(OPENNURBS_GROUP_INC_)
#define OPENNURBS_GROUP_INC_

class ON_CLASS ON_Group : public ON_ModelComponent
{
  ON_OBJECT_DECLARE(ON_Group);

public:
  static const ON_Group Unset;   // nil id
                                    
  /*
  Parameters:
    model_component_reference - [in]
    none_return_value - [in]
      value to return if ON_Material::Cast(model_component_ref.ModelComponent())
      is nullptr
  Returns:
    If ON_Material::Cast(model_component_ref.ModelComponent()) is not nullptr,
    that pointer is returned.  Otherwise, none_return_value is returned. 
  */
  static const ON_Group* FromModelComponentRef(
    const class ON_ModelComponentReference& model_component_reference,
    const ON_Group* none_return_value
    );

public:
  ON_Group() ON_NOEXCEPT;
  ON_Group(const ON_Group& src);
  ~ON_Group() = default;
  ON_Group& operator=(const ON_Group& src) = default;

private:
  
  //////////////////////////////////////////////////////////////////////
  //
  // ON_Object overrides
  bool IsValid( class ON_TextLog* text_log = nullptr ) const override;

  void Dump(
    ON_TextLog& text_log
    ) const override;

  bool Write(
    ON_BinaryArchive& archive
    ) const override;

  bool Read(
    ON_BinaryArchive& archive
    ) override;

private:
  bool Internal_WriteV5(
    ON_BinaryArchive& archive
    ) const;

  bool Internal_ReadV5(
    ON_BinaryArchive& archive
    );
};

#if defined(ON_DLL_TEMPLATE)
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<ON_Group*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_SimpleArray<const ON_Group*>;
ON_DLL_TEMPLATE template class ON_CLASS ON_ObjectArray<ON_Group>;
#endif

#endif
