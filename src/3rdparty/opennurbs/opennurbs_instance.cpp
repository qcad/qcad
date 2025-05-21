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

ON_OBJECT_IMPLEMENT( ON_InstanceDefinition, ON_ModelComponent, "26F8BFF6-2618-417f-A158-153D64A94989" );

class /*NEVER EXPORT THIS CLASS DEFINITION*/ ON_ReferencedComponentSettingsImpl
{
public:
  ON_ReferencedComponentSettingsImpl() = default;
  ~ON_ReferencedComponentSettingsImpl()
  {
    InternalDestroyHelper();
  }
  ON_ReferencedComponentSettingsImpl(const ON_ReferencedComponentSettingsImpl& src)
  {
    InternalCopyHelper(src);
  }
  ON_ReferencedComponentSettingsImpl& operator=(const ON_ReferencedComponentSettingsImpl& src)
  {
    if (&src != this)
    {
      InternalDestroyHelper();
      InternalCopyHelper(src);
    }
    return *this;
  }

  bool ReadImpl( 
    ON_BinaryArchive& binary_archive 
    );

  bool WriteImpl( 
    ON_BinaryArchive& binary_archive 
    ) const;

  bool IsNotEmptyImpl() const
  {
    return HasLayerInformationImpl();
  }

  bool HasLayerInformationImpl() const
  {
    return (HasLayerTableInformationImpl() || HasParentLayerInformationImpl());
  }

  bool HasLayerTableInformationImpl() const
  {
    return (m_layer_referenced_file_copy.Count() > 0);
  }

  bool HasParentLayerInformationImpl() const
  {
    return (m_bHasReferenceLayerTableParentLayer || nullptr != m_layer_table_parent_layer);
  }
  
  /*
  See ON_ReferencedComponentSettings::AfterReferenceLayerTableRead comment.
  */
  void AfterReferenceLayerTableReadImpl(
    const class ON_ComponentManifest& source_archive_manifest,
    const class ON_ComponentManifest& model_manifest,
    const class ON_ManifestMap& archive_to_model_map,
    ON_Layer* linked_definition_parent_layer,
    unsigned int layer_count,
    ON_Layer** layers
  );

  /*
  See ON_ReferencedComponentSettings::AfterLayerTableAddedToModel comment.
  */
  void AfterLayerTableAddedToModelImpl(
    const class ON_ComponentManifest& source_archive_manifest,
    const class ON_ComponentManifest& model_manifest,
    const class ON_ManifestMap& archive_to_model_map
    );

  /*
  See ON_ReferencedComponentSettings::BeforeLinkedDefinitionWrite comment.
  */
  void BeforeLinkedDefinitionWriteImpl(
    const class ON_ComponentManifest& model_manifest,
    const class ON_ComponentManifest& destination_archive_manifest,
    const class ON_ManifestMap& model_to_archive_map,
    const ON_Layer* linked_definition_parent_layer,
    void* context,
    const ON_Layer*(*ModelLayerFromIdFunc)(void* context, const ON_UUID&)
    );

private:
  /*
  Parameters:
    previous_referenced_file_layer - [in]
      A copy of the layer the last time the reference file was read
        Differences between reference_file_layer and referenced_file_layer_copy
        indicate that setting changed in the reference file since the last time
        the model refreshed the linked instance definition or worksession reference.
    reference_file_layer - [in]
      Layer read from the referenced file
    previous_model_layer - [in]
      A copy of the corresponding model layer the last time the model (not the referenced file) was saved.
        Differences between model_layer_copy and referenced_file_layer_copy
        indicate that setting was modified in the model the last time the
        model refreshed or saved the linked instance definition or worksession
    model_layer - [out]
      Layer used in the model.
      To update a layer "in-place", pass the same layer as reference_file_layer and model_layer
  Remarks:
    NOTE WELL: 
      The "model" contains the linked instance definition or worksession.
      The reference file is not what is read to create the model.
      The reference file is read to import the contents of the linked instance definition.
  */
  static bool Internal_UpdateLayer(
    const ON_Layer& previous_referenced_file_layer,
    const ON_Layer& reference_file_layer,
    const ON_Layer& previous_model_layer,
    ON_Layer& model_layer
    );

  /*
  Parameters:
    layer - [in/out]
      input layer = values read from referenced file
      output layer = values to use in model
      (name, index and id are not changed)
  */
  bool Internal_UpdateLayer(
    ON_Layer& layer
    ) const;

  /*
  Returns:
    bool setting state to use in current model
  */
  static bool Internal_UpdateBool(
    bool bPreviousReferenceFileState,
    bool bCurrentReferenceFileState,
    bool bPreviousModelState
  );

  /*
  Returns:
    color to use in current model
  */
  static ON_Color Internal_UpdateColor(
    ON_Color previous_reference_file_color,
    ON_Color current_reference_file_color,
    ON_Color previous_model_color
  );

  /*
  Returns:
    double value to use in current model
  */
  static double Internal_UpdateDouble(
    double previous_reference_file_value,
    double current_reference_file_value,
    double previous_model_value
  );


  // These m_layer_referenced_file_copy[] and m_layer_model_copy[]
  // are parallel arrays when read and written. Shortly after
  // reading/writing, m_layer_model_copy[] is destroyed because
  // it has no use except during reading/writing.

  // m_referenced_file_copy_layers[] contains copies of the last 
  // layer values read from the referenced file when a linked instance
  // definition is inserted into the model.
private:
  ON_SimpleArray<ON_Layer*> m_layer_referenced_file_copy; 

  // m_model_settings_layers[] contains copies of the most
  // recent settings used in the model. 
  //
  // The  m_model_settings_layers[] identification values 
  // (name, index, and id) are meaningless when read from the file.
  // They are runtime values that often change each time a linked 
  // instance definition is loaded.
  //
  // When some other attribute, (visibility, color, plot weight, ...)
  // is different between m_ref_file_copy_layers[] and m_model_settings_layers[],
  // it indicates the model setting has been changed from the file setting. 
private:
  ON_SimpleArray<ON_Layer*> m_layer_model_copy; 

  // Settings for the layer that is the
  // parent of the layers in the linked
  // file's layer table.  This layer is
  // not in the linked file and is not
  // saved in the layer table of active model containing
  // the idef.  If null, it is created.
private:
  bool m_bHasReferenceLayerTableParentLayer = false;
  ON_Layer* m_layer_table_parent_layer = nullptr;

private:
  // When a component (layer, material, ...) from a linked file is inserted in the 
  // active model and a component id collision occurs, the active model id of the
  // component has to be changed. This list keeps track of the changes so we can 
  // determine which runtime component corresponds to a component in the linked file.
  // The first id in the pair is component id in the linked reference file.
  // The second id in the pair is the component id in the runtime model.
  //
  // This information is created in AfterLayerTableAddedToModelImpl()
  // and used in BeforeLinkedDefinitionWriteImpl().
  // It has no other use and is not saved in files because the
  // 2nd id is a runtime value that can change every time a file is read.
  ON_UuidPairList2 m_runtime_layer_id_map;

private:
  static void InternalDestroyLayerArray(
    ON_SimpleArray<ON_Layer*>& a
  )
  {
    int count = a.Count();
    for (int i = 0; i < count; i++)
    {
      ON_Layer* layer = a[i];
      if (nullptr == layer)
        continue;
      a[i] = nullptr;
      delete layer;
    }
    a.SetCount(0);
    a.Destroy();
  }

private:
  void InternalCopyHelper(const ON_ReferencedComponentSettingsImpl& src)
  {
    int count = src.m_layer_referenced_file_copy.Count();
    if (count != src.m_layer_model_copy.Count())
      count = 0;

    m_layer_referenced_file_copy.Reserve(count);
    m_layer_model_copy.Reserve(count);
    for ( int i = 0; i < count; i++ )
    {
      const ON_Layer* src_ref_layer = src.m_layer_referenced_file_copy[i];
      if (nullptr == src_ref_layer)
        continue;
      const ON_Layer* src_model_layer = src.m_layer_model_copy[i];
      if (nullptr == src_model_layer)
        continue;
      m_layer_referenced_file_copy.Append(new ON_Layer(*src_ref_layer));
      m_layer_model_copy.Append(new ON_Layer(*src_model_layer));
    }
    
    m_bHasReferenceLayerTableParentLayer = src.m_bHasReferenceLayerTableParentLayer;
    if ( nullptr != src.m_layer_table_parent_layer )
    {
      m_layer_table_parent_layer = new ON_Layer( *src.m_layer_table_parent_layer );
      m_bHasReferenceLayerTableParentLayer = true;
    }

    m_runtime_layer_id_map = src.m_runtime_layer_id_map;
    m_runtime_layer_id_map.ImproveSearchSpeed();
  }

private:
 void InternalDestroyListsHelper()
  {
    ON_ReferencedComponentSettingsImpl::InternalDestroyLayerArray(m_layer_referenced_file_copy);
    ON_ReferencedComponentSettingsImpl::InternalDestroyLayerArray(m_layer_model_copy);
    m_runtime_layer_id_map.Empty();
  }

private:
  void InternalDestroyHelper()
  {
    m_bHasReferenceLayerTableParentLayer = false;
    if ( 0 != m_layer_table_parent_layer )
    {
      delete m_layer_table_parent_layer;
      m_layer_table_parent_layer = nullptr;
    }

    InternalDestroyListsHelper();
  }
};

ON_ReferencedComponentSettings::~ON_ReferencedComponentSettings()
{
  if (nullptr != m_impl)
    delete m_impl;
}

ON_ReferencedComponentSettings::ON_ReferencedComponentSettings(const ON_ReferencedComponentSettings& src)
{
  if (nullptr != src.m_impl)
    m_impl = new ON_ReferencedComponentSettingsImpl(*src.m_impl);
}

ON_ReferencedComponentSettings& ON_ReferencedComponentSettings::operator=(const ON_ReferencedComponentSettings& src)
{
  if (m_impl != src.m_impl)
  {
    if (nullptr != m_impl)
      delete m_impl;
    if (nullptr != src.m_impl)
      m_impl = new ON_ReferencedComponentSettingsImpl(*src.m_impl);
  }
  return *this;
}

bool ON_ReferencedComponentSettings::Read(
  ON_BinaryArchive& archive
  )
{
  if (nullptr != m_impl)
  {
    delete m_impl;
    m_impl = nullptr;
  }
  
  int major_version = 0;
  int minor_version = 0;
  if (!archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version))
    return false;

  bool bSuppressPartiallyReadChunkWarning = false;
  
  bool rc = false;
  for (;;)
  {
    if (1 != major_version)
      break;

    bool bHaveImpl = false;
    if (!archive.ReadBool(&bHaveImpl))
      break;
    if (bHaveImpl)
    {
      ON_ReferencedComponentSettingsImpl* impl = new ON_ReferencedComponentSettingsImpl();
      if (!impl->ReadImpl(archive))
      {
        delete impl;
        break;
      }
      m_impl = impl;
    }
    
    // end of 1.0 chunk contents

    
    // increment this when Write's minor_version increases
    // Settint bSuppressPartiallyReadChunkWarning suppresses warnings when old code reads new files.
    const int max_supported_minor_version = 0; 
    if (minor_version > max_supported_minor_version)
      bSuppressPartiallyReadChunkWarning = true;
    rc = true;
    break;
  }

  if (!archive.EndRead3dmChunk(bSuppressPartiallyReadChunkWarning))
    rc = false;
  return rc;
}

bool ON_ReferencedComponentSettings::Write(
  ON_BinaryArchive& archive
) const
{
  int major_version = 1;
  int minor_version = 0;
  if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, major_version, minor_version))
    return false;
  
  bool rc = false;
  for (;;)
  {
    const bool bHaveImpl 
      = archive.Archive3dmVersion() >= 60
      && nullptr != m_impl 
      && m_impl->IsNotEmptyImpl();
    if (!archive.WriteBool(bHaveImpl))
      break;

    if (bHaveImpl && !m_impl->WriteImpl(archive))
      break;

    rc = true;
    break;
  }

  if (!archive.EndWrite3dmChunk())
    rc = false;
  return rc;
}

bool ON_ReferencedComponentSettings::IsEmpty() const
{
  return (false == IsNotEmpty());
}

bool ON_ReferencedComponentSettings::IsNotEmpty() const
{
  return (nullptr != m_impl && m_impl->IsNotEmptyImpl());
}

bool ON_ReferencedComponentSettings::HasLayerInformation() const
{
  return (nullptr != m_impl && m_impl->HasLayerInformationImpl());
}

bool ON_ReferencedComponentSettings::HasLayerTableInformation() const
{
  return (nullptr != m_impl && m_impl->HasLayerTableInformationImpl());
}

bool ON_ReferencedComponentSettings::HasParentLayerInformation() const
{
  return (nullptr != m_impl && m_impl->HasParentLayerInformationImpl());
}

class ON_ReferencedComponentSettingsImpl* ON_ReferencedComponentSettings::Impl(
  bool bCreateIfNull
)
{
  if (nullptr == m_impl && bCreateIfNull)
    m_impl = new ON_ReferencedComponentSettingsImpl();
  return m_impl;
}

void ON_ReferencedComponentSettings::AfterReferenceLayerTableRead(
  const class ON_ComponentManifest& source_archive_manifest,
  const class ON_ComponentManifest& model_manifest,
  const class ON_ManifestMap& archive_to_model_map,
  ON_Layer* linked_definition_parent_layer,
  unsigned int layer_count,
  ON_Layer** layers
)
{
  if (layer_count <= 0 || nullptr == layers)
    return;
  Impl(true)->AfterReferenceLayerTableReadImpl(source_archive_manifest,model_manifest,archive_to_model_map,linked_definition_parent_layer,layer_count, layers);
}

void ON_ReferencedComponentSettings::AfterLayerTableAddedToModel(
    const class ON_ComponentManifest& source_archive_manifest,
    const class ON_ComponentManifest& model_manifest,
    const class ON_ManifestMap& archive_to_model_map
  )
{
  if (m_impl)
    m_impl->AfterLayerTableAddedToModelImpl(source_archive_manifest, model_manifest, archive_to_model_map);
}

void ON_ReferencedComponentSettings::BeforeLinkedDefinitionWrite(
  const class ON_ComponentManifest& model_manifest,
  const class ON_ComponentManifest& destination_archive_manifest,
  const class ON_ManifestMap& model_to_archive_map,
  const ON_Layer* linked_definition_parent_layer,
  void* context,
  const ON_Layer*(*ModelLayerFromIdFunc)(void* context, const ON_UUID&)
)
{
  if (m_impl)
    m_impl->BeforeLinkedDefinitionWriteImpl(model_manifest,destination_archive_manifest,model_to_archive_map,linked_definition_parent_layer,context,ModelLayerFromIdFunc);
}


void ON_ReferencedComponentSettingsImpl::AfterReferenceLayerTableReadImpl(
  const class ON_ComponentManifest& source_archive_manifest,
  const class ON_ComponentManifest& model_manifest,
  const class ON_ManifestMap& archive_to_model_map,
  ON_Layer* linked_definition_parent_layer,
  unsigned int layer_count,
  ON_Layer** layers
)
{
  ON_SimpleArray<ON_Layer*> updated_reference_copy(layer_count);
  if (m_layer_referenced_file_copy.Count() != m_layer_model_copy.Count())
    InternalDestroyListsHelper();
  //const int old_count = m_layer_referenced_file_copy.Count();
  for (unsigned int i = 0; i < layer_count; i++)
  {
    ON_Layer* layer = layers[i];
    if (nullptr == layer)
      continue;
    updated_reference_copy.Append(new ON_Layer(*layer));
    Internal_UpdateLayer(*layer);
  }
  InternalDestroyListsHelper();
  m_layer_referenced_file_copy = updated_reference_copy;
  updated_reference_copy.Destroy();
  if (nullptr != linked_definition_parent_layer)
  {
    if (nullptr != m_layer_table_parent_layer)
    {
      ON_ReferencedComponentSettingsImpl::Internal_UpdateLayer(*m_layer_table_parent_layer, *m_layer_table_parent_layer, *m_layer_table_parent_layer, *linked_definition_parent_layer);
    }
  }
}

void ON_ReferencedComponentSettingsImpl::AfterLayerTableAddedToModelImpl(
  const class ON_ComponentManifest& source_archive_manifest,
  const class ON_ComponentManifest& model_manifest,
  const class ON_ManifestMap& archive_to_model_map
)
{
  InternalDestroyLayerArray(m_layer_model_copy);
  m_runtime_layer_id_map.Empty();
  int count = 0;
  for (int i = 0; i < m_layer_referenced_file_copy.Count(); i++)
  {
    ON_Layer* layer = m_layer_referenced_file_copy[i];
    if (nullptr == layer)
      continue;
    m_layer_referenced_file_copy[i] = nullptr;
    ON_ManifestMapItem map_item = archive_to_model_map.MapItemFromSourceId(layer->Id());
    if (ON_ModelComponent::Type::Layer != map_item.ComponentType() || ON_nil_uuid == map_item.DestinationId())
    {
      delete layer;
      continue;
    }
    if (false == m_runtime_layer_id_map.AddPair(map_item.SourceId(),map_item.DestinationId()))
    {
      delete layer;
      continue;
    }
    // If this layer came from reading a non-.3dm file,
    // it might have per viewport settings that apply to 
    // the viewports in the reference file.
    // These viewports are not in the current model and
    // any reference file per viewport settings should be deleted.
    layer->DeletePerViewportSettings(ON_nil_uuid);

    m_layer_referenced_file_copy[count++] = layer;
  }
  m_layer_referenced_file_copy.SetCount(count);
  m_runtime_layer_id_map.ImproveSearchSpeed();
}

void ON_ReferencedComponentSettingsImpl::BeforeLinkedDefinitionWriteImpl(
  const class ON_ComponentManifest& model_manifest,
  const class ON_ComponentManifest& destination_archive_manifest,
  const class ON_ManifestMap& model_to_archive_map,
  const ON_Layer* linked_definition_parent_layer,
  void* context,
  const ON_Layer*(*ModelLayerFromIdFunc)(void* context, const ON_UUID&)
 )
{
  InternalDestroyLayerArray(m_layer_model_copy);
  const int count0 = m_layer_referenced_file_copy.Count();
  m_layer_model_copy.Reserve(count0);
  int count1 = 0;
  for (int i = 0; i < count0; i++)
  {
    ON_Layer* layer_referenced_file_copy = m_layer_referenced_file_copy[i];
    if (nullptr == layer_referenced_file_copy)
      continue;
    m_layer_referenced_file_copy[i] = nullptr;
    ON_UUID model_layer_id = ON_nil_uuid;
    if (!m_runtime_layer_id_map.FindId1(layer_referenced_file_copy->Id(), &model_layer_id))
    {
      delete layer_referenced_file_copy;
      continue;
    }
    if (ON_nil_uuid == model_layer_id)
    {
      delete layer_referenced_file_copy;
      continue;
    }
    const ON_Layer* model_layer = ModelLayerFromIdFunc(context, model_layer_id);
    if (nullptr == model_layer)
    {
      delete layer_referenced_file_copy;
      continue;
    }
    if (model_layer_id != model_layer->Id())
    {
      delete layer_referenced_file_copy;
      continue;
    }

    // We found the corresponding runtime model layer
    m_layer_referenced_file_copy[count1++] = layer_referenced_file_copy;

    ON_Layer* ref_model_layer_copy = new ON_Layer(*model_layer);
    // The runtime index and id commonly change every time the file is read,
    // so saving this variable runtime identification information
    // leads to confusion.
    ref_model_layer_copy->ClearName();
    ref_model_layer_copy->ClearIndex();
    ref_model_layer_copy->ClearId();
    ref_model_layer_copy->ClearModelSerialNumber();

    m_layer_model_copy.Append(ref_model_layer_copy);
  }

  if (
    count1 > 0
    && count1 <= count0
    && count1 == m_layer_referenced_file_copy.Count()
    && count1 == m_layer_model_copy.Count()
    )
  {
    if (count1 != count0)
    {
      m_layer_referenced_file_copy.SetCount(count1);
      m_runtime_layer_id_map.Empty();
      for (int i = 0; i < count1; i++)
      {
        m_runtime_layer_id_map.AddPair(
          m_layer_referenced_file_copy[i]->Id(),
          m_layer_model_copy[i]->Id()
        );
      }
      m_runtime_layer_id_map.ImproveSearchSpeed();
    }
  }
  else
  {
    InternalDestroyHelper();
  }
}

bool ON_ReferencedComponentSettingsImpl::Internal_UpdateBool(
  bool bPreviousReferenceFileState,
  bool bCurrentReferenceFileState,
  bool bPreviousModelState
)
{
  return
    (bPreviousReferenceFileState == bCurrentReferenceFileState)
    ? bPreviousModelState
    : bCurrentReferenceFileState;
}

ON_Color ON_ReferencedComponentSettingsImpl::Internal_UpdateColor(
  ON_Color previous_reference_file_color,
  ON_Color current_reference_file_color,
  ON_Color previous_model_color
)
{
  return
    (previous_reference_file_color == current_reference_file_color)
    ? previous_model_color
    : current_reference_file_color;
}

double ON_ReferencedComponentSettingsImpl::Internal_UpdateDouble(
  double previous_reference_file_value,
  double current_reference_file_value,
  double previous_model_value
)
{
  return
    (previous_reference_file_value == current_reference_file_value)
    ? previous_model_value
    : current_reference_file_value;
}

bool ON_ReferencedComponentSettingsImpl::Internal_UpdateLayer(
  const ON_Layer& previous_referenced_file_layer,
  const ON_Layer& reference_file_layer,
  const ON_Layer& previous_model_layer,
  ON_Layer& model_layer
  )
{
  // NOTES:
  //
  // 1) 
  // It is critical that model_layer identification information (name, index, id)
  // do not change.
  //
  // 2) 
  // model_layer is generally the same layer as reference_file_layer and may be 
  // same layer as referenced_file_layer_copy or model_layer_copy,
  // so it must be initialized AFTER the final settings are determined.
  //
  // Any per view settings on previous_referenced_file_layer or
  // reference_file_layer should have been removed. 
  // In any case they have no meaning in the current context
  // since the views from the reference_file are not imported.
  //
  // There may be per view settings on previous_model_layer or model_layer
  // and these need to be handled appropriately.
  // See RH-37183 for more details and an example.
  // 

  // Layer visibility
  const bool bIsVisible = ON_ReferencedComponentSettingsImpl::Internal_UpdateBool(
    previous_referenced_file_layer.IsVisible(),
    reference_file_layer.IsVisible(),
    previous_model_layer.IsVisible()
  );
  model_layer.SetVisible(bIsVisible);

  // Layer locked
  const bool bIsLocked = ON_ReferencedComponentSettingsImpl::Internal_UpdateBool(
    previous_referenced_file_layer.IsLocked(),
    reference_file_layer.IsLocked(),
    previous_model_layer.IsLocked()
  );
  model_layer.SetLocked(bIsLocked);

  // Layer color
  const ON_Color color = ON_ReferencedComponentSettingsImpl::Internal_UpdateColor(
    previous_referenced_file_layer.Color(),
    reference_file_layer.Color(),
    previous_model_layer.Color()
  );
  model_layer.SetColor(color);

  // Layer plot color
  const ON_Color plot_color = ON_ReferencedComponentSettingsImpl::Internal_UpdateColor(
    previous_referenced_file_layer.PlotColor(),
    reference_file_layer.PlotColor(),
    previous_model_layer.PlotColor()
  );
  model_layer.SetPlotColor(plot_color);

  // Layer plot weight
  double plot_weight = ON_ReferencedComponentSettingsImpl::Internal_UpdateDouble(
    previous_referenced_file_layer.PlotWeight(),
    reference_file_layer.PlotWeight(),
    previous_model_layer.PlotWeight()
  );
  model_layer.SetPlotWeight(plot_weight);

  // Add more settings here without breaking anything

  // Dale Lear August 2017 - RH-39457
  // Saved PerViewport settings need to be applied to model_layer
  //
  // Per view settings from the reference file have no meaning because the
  // views they apply to are in the reference file and those views are
  // not merge into the active model.  
  // The per view settings are simply copied from previous_model_layer to model_layer
  // because the previous_model_layer is the only place to persistently 
  // store per viewport settings in the current' model's archive.
  model_layer.DeletePerViewportSettings(ON_nil_uuid);
  model_layer.CopyPerViewportSettings(
    previous_model_layer,
    ON_nil_uuid,
    ON_Layer::PER_VIEWPORT_SETTINGS::per_viewport_all_settings
  );

  return true;
}

bool ON_ReferencedComponentSettingsImpl::Internal_UpdateLayer(
  ON_Layer& layer
  ) const
{
  for (;;)
  {
    // input layer has values read from reference file,
    // so layer->Id() = reference file layer id
    const ON_UUID reference_file_layer_id = layer.Id();
    if (ON_nil_uuid == reference_file_layer_id)
      break;

    const int count = m_layer_referenced_file_copy.Count();
    if (count <= 0)
      break;
    if (count != m_layer_model_copy.Count())
      break;
    for (int i = 0; i < count; i++)
    {
      if (nullptr == m_layer_referenced_file_copy[i])
        continue;
      if (reference_file_layer_id != m_layer_referenced_file_copy[i]->Id())
        continue;
      if (nullptr == m_layer_model_copy[i])
        continue;
      return ON_ReferencedComponentSettingsImpl::Internal_UpdateLayer(
        *m_layer_referenced_file_copy[i],
        layer,
        *m_layer_model_copy[i],
        layer
        );
    }
    break;
  }

  return false;
}

ON_InstanceDefinition::ON_InstanceDefinition() ON_NOEXCEPT
  : ON_ModelComponent(ON_ModelComponent::Type::InstanceDefinition)
{}

ON_InstanceDefinition::~ON_InstanceDefinition()
{
  Internal_Destroy();
}

ON_InstanceDefinition::ON_InstanceDefinition(const ON_InstanceDefinition& src)
  : ON_ModelComponent(ON_ModelComponent::Type::InstanceDefinition,src)
{
  Internal_Copy(src);
}

ON_InstanceDefinition& ON_InstanceDefinition::operator=(const ON_InstanceDefinition& src)
{
  if ( this != &src ) 
  {
    Internal_Destroy();
    ON_ModelComponent::operator=(src);
    Internal_Copy(src);
  }
  return *this;
}

void ON_InstanceDefinition::Internal_Destroy()
{
  if (nullptr != m_linked_idef_component_settings)
  {
    delete m_linked_idef_component_settings;
    m_linked_idef_component_settings = nullptr;
  }
}

void ON_InstanceDefinition::Internal_Copy(const ON_InstanceDefinition& src)
{
  m_description = src.m_description;
  m_url = src.m_url;
  m_url_tag = src.m_url_tag;
  m_bbox = src.m_bbox;
  m_us = src.m_us;
  m_idef_update_type = src.m_idef_update_type;
  m_bSkipNestedLinkedDefinitions = src.m_bSkipNestedLinkedDefinitions;
  m_linked_file_reference = src.m_linked_file_reference;
  m_linked_file_V5_checksum = src.m_linked_file_V5_checksum;
  m_linked_component_appearance = src.m_linked_component_appearance;
  if (nullptr != src.m_linked_idef_component_settings)
    m_linked_idef_component_settings = new ON_ReferencedComponentSettings(*src.m_linked_idef_component_settings);

  //This omission was causing part of https://mcneel.myjetbrains.com/youtrack/issue/RH-47128
  m_object_uuid = src.m_object_uuid;
}


const ON_InstanceDefinition* ON_InstanceDefinition::FromModelComponentRef(
  const class ON_ModelComponentReference& model_component_reference,
  const ON_InstanceDefinition* none_return_value
  )
{
  const ON_InstanceDefinition* p = ON_InstanceDefinition::Cast(model_component_reference.ModelComponent());
  return (nullptr != p) ? p : none_return_value;
}

void ON_InstanceDefinition::Dump( ON_TextLog& text_log ) const
{
  text_log.Print("Instance Definition\n");
  text_log.PushIndent();

  ON_ModelComponent::Dump(text_log);

  text_log.Print("Type: ");
  switch( InstanceDefinitionType() )
  {
  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset:
    text_log.Print("Unset");
    break;
  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static:
    text_log.Print("Static");
    break;
  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded:
    text_log.Print("LinkedAndEmbedded");
    break;

  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked:
    switch (LinkedComponentAppearance())
    {
    case ON_InstanceDefinition::eLinkedComponentAppearance::Active:
      text_log.Print("Linked - active layer style");
      break;
    case ON_InstanceDefinition::eLinkedComponentAppearance::Reference:
      text_log.Print("Linked - reference layer style");
      break;
    default:
      text_log.Print("Linked");
      break;
    }
    break;

  default:
    text_log.Print("not valid");
    break;
  }
  text_log.Print("\n");


  
  const wchar_t* wsDescription = static_cast< const wchar_t* >(m_description);
  if ( 0 != wsDescription && 0 != wsDescription[0]) 
    text_log.Print("Description: \"%ls\"\n",wsDescription);

  const wchar_t* wsURL = static_cast< const wchar_t* >(m_url);
  if ( 0 != wsURL && 0 != wsURL[0]) 
    text_log.Print("URL: \"%ls\"\n",wsURL);

  const wchar_t* wsTag = static_cast< const wchar_t* >(m_url_tag);
  if ( 0 != wsTag && 0 != wsTag[0]) 
    text_log.Print("URL tag: \"%ls\"\n",wsTag);

  m_us.Dump(text_log);

  if (m_linked_file_reference.IsSet())
  {
    text_log.Print("Linked definition file path: ");
    m_linked_file_reference.Dump(text_log);
  }

  const int id_count = m_object_uuid.Count();
  text_log.Print("Contains: %d objects\n",id_count);

  if ( id_count > 0 )
  {
    text_log.PushIndent();

    text_log.Print(m_object_uuid[0]); 
    text_log.Print("\n");

    if ( id_count > 4 )
    {
      text_log.Print("...\n");
    }
    else
    {
      for ( int i = 1; i < id_count; i++ )
      {
        text_log.Print(m_object_uuid[i]);
        text_log.Print("\n");
      }
    }

    text_log.PopIndent();
  }

  m_bbox.Dump(text_log);

  text_log.PopIndent();
}

bool ON_InstanceDefinition::IsValid( ON_TextLog* text_log ) const
{
  if (false == ON_ModelComponent::IsValid(text_log))
    return false;

  if ( IdIsNil() )
  {
    if (text_log)
    {
      text_log->Print("ON_InstanceDefinition has nil uuid.\n");
    }
    return false;
  }
  if ( !m_bbox.IsValid() )
  {
    if (text_log)
    {
      text_log->Print("ON_InstanceDefinition has invalid bounding box.\n");
    }
    return false;
  }

  switch( InstanceDefinitionType() )
  {
  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static:
      // no source archive information should be present
      if ( m_linked_file_reference.IsSet() )
      {
        if (text_log)
        {
          text_log->Print("ON_InstanceDefinition is static but m_linked_file_path is not empty.\n");
        }
        return false;
      }

      if ( ON_InstanceDefinition::eLinkedComponentAppearance::Unset != LinkedComponentAppearance() )
      {
        if (text_log)
        {
          text_log->Print("ON_InstanceDefinition type is Static but LinkedComponentAppearance() is not ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset.\n");
        }
        return false;
      }
      break;

  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded:
  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked:
      // source archive information is required
      if( false == m_linked_file_reference.IsSet() )
      {
        if (text_log)
        {
          text_log->Print("ON_InstanceDefinition is linked or embedded but m_linked_file_path is empty.\n");
        }
        return false;
      }
      if( !m_linked_file_reference.ContentHash().IsSet() && !m_linked_file_V5_checksum.IsSet())
      {
        // one of these should be set, even if the file is currently missing.
        if (text_log)
        {
          text_log->Print("ON_InstanceDefinition is linked or embedded but m_linked_file_reference.ContentHash() and m_V5_linked_defintion_checksum are not set.\n");
        }
        return false;
      }

      if ( ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked == InstanceDefinitionType() )
      {
        if ( ON_InstanceDefinition::eLinkedComponentAppearance::Active != LinkedComponentAppearance() && ON_InstanceDefinition::eLinkedComponentAppearance::Reference != LinkedComponentAppearance() )
        {
          if (text_log)
          {
            text_log->Print("ON_InstanceDefinition is Linked but LinkedComponentAppearance() is not Embed or Reference.\n");
          }
          return false;
        }
      }
      else
      {
        if ( ON_InstanceDefinition::eLinkedComponentAppearance::Unset != LinkedComponentAppearance() )
        {
          if (text_log)
          {
            text_log->Print("ON_InstanceDefinition type is LinkedAndEmbedded but LinkedComponentAppearance() is not ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset.\n");
          }
          return false;
        }
      }

      break;

    default:
      if ( text_log )
      {
        text_log->Print("ON_InstanceDefinition.m_idef_update_type value is invalid.\n");
      }
      return false;
      break;
  }

  // TODO
  return true;
}


unsigned int ON_InstanceDefinition::SizeOf() const
{
  unsigned int sz = sizeof(*this) - sizeof(ON_Geometry);
  sz += ON_ModelComponent::SizeOf();
  sz += this->m_object_uuid.SizeOfArray();
  sz += this->m_description.SizeOf();
  sz += this->m_url.SizeOf();
  sz += this->m_url_tag.SizeOf();
  sz += this->m_linked_file_reference.SizeOf();
  return sz;
}

ON_InstanceDefinition::IDEF_UPDATE_TYPE ON_InstanceDefinition::IdefUpdateType() const
{
  return InstanceDefinitionType();
}


ON_InstanceDefinition::IDEF_UPDATE_TYPE ON_InstanceDefinition::InstanceDefinitionType() const
{
  return m_idef_update_type;
}


bool ON_InstanceDefinition::IsLinkedType() const
{
  switch (InstanceDefinitionType())
  {
    case ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded:
    case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked:
      return true;
    case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static:
    case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset:
      return false;
  }
  return false;
}

bool ON_InstanceDefinition::SkipNestedLinkedDefinitions() const
{
  return m_bSkipNestedLinkedDefinitions;
}

void ON_InstanceDefinition::SetSkipNestedLinkedDefinitions(
  bool bSkipNestedLinkedDefinitions
)
{
  const bool b = bSkipNestedLinkedDefinitions ? true : false;
  if (b != m_bSkipNestedLinkedDefinitions)
  {
    m_bSkipNestedLinkedDefinitions = b;
    Internal_ContentChanged();
  }
}

ON_InstanceDefinition::IDEF_UPDATE_TYPE ON_InstanceDefinition::InstanceDefinitionTypeFromUnsigned(
  unsigned int idef_type_as_unsigned
  )
{
  switch (idef_type_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked);
  }
  ON_ERROR("Invalid idef_type_as_unsigned value.");
  return ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset;
}

ON_InstanceDefinition::eLinkedComponentAppearance ON_InstanceDefinition::LinkedComponentAppearanceFromUnsigned(
  unsigned int linked_component_style_as_unsigned
  )
{
  switch (linked_component_style_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_InstanceDefinition::eLinkedComponentAppearance::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_InstanceDefinition::eLinkedComponentAppearance::Active);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_InstanceDefinition::eLinkedComponentAppearance::Reference);
  }
  ON_ERROR("Invalid linked_component_style_as_unsigned parameter.");
  return ON_InstanceDefinition::eLinkedComponentAppearance::Unset;
}

ON_InstanceDefinition::eLinkedComponentAppearance ON_InstanceDefinition::LinkedComponentAppearance() const
{
  return m_linked_component_appearance;
}

bool ON_InstanceDefinition::SetLinkedComponentAppearance(
  ON_InstanceDefinition::eLinkedComponentAppearance linked_component_appearance
  )
{
  if (linked_component_appearance != ON_InstanceDefinition::LinkedComponentAppearanceFromUnsigned(static_cast<unsigned char>(linked_component_appearance)))
  {
    ON_ERROR("Invalid linked_component_style parameter.");
    return false;
  }

  switch (InstanceDefinitionType())
  {
  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset:
  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static:
  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded:
    if (ON_InstanceDefinition::eLinkedComponentAppearance::Unset == linked_component_appearance)
    {
      if (m_linked_component_appearance != linked_component_appearance)
      {
        IncrementContentVersionNumber();
        m_linked_component_appearance = linked_component_appearance;
      }
      return true;
    }
    break;

  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked:
    if (ON_InstanceDefinition::eLinkedComponentAppearance::Active == linked_component_appearance 
      || ON_InstanceDefinition::eLinkedComponentAppearance::Reference == linked_component_appearance
      )
    {
      if (m_linked_component_appearance != linked_component_appearance)
      {
        IncrementContentVersionNumber();
        m_linked_component_appearance = linked_component_appearance;
      }
      return true;
    }
    break;

  default:
    break;
  }
  
  ON_ERROR("Invalid linked_component_style parameter for this type of instance definition.");
  return false;
}


ON::object_type ON_InstanceDefinition::ObjectType() const
{
  return ON::instance_definition;
}

const ON_BoundingBox ON_InstanceDefinition::BoundingBox() const
{
  return m_bbox;
}

void ON_InstanceDefinition::SetBoundingBox(
  ON_BoundingBox bbox
  )
{
  if (m_bbox.m_min == bbox.m_min &&  m_bbox.m_max == bbox.m_max)
    return;
  m_bbox = bbox;
  Internal_ContentChanged();
}


void ON_InstanceDefinition::ClearBoundingBox()
{
  if (m_bbox == ON_BoundingBox::EmptyBoundingBox)
    return;
  m_bbox = ON_BoundingBox::EmptyBoundingBox;
  Internal_ContentChanged();
}


const ON_wString ON_InstanceDefinition::URL() const
{
  return m_url;
}

void ON_InstanceDefinition::SetURL( const wchar_t* url )
{
  ON_wString s(url);
  s.TrimLeftAndRight();
  if (s == m_url)
    return;

  if ( s.IsEmpty() )
    m_url = ON_wString::EmptyString;
  else
    m_url = s;
  Internal_ContentChanged();
}

const ON_wString ON_InstanceDefinition::URL_Tag() const
{
  return m_url_tag;
}

void ON_InstanceDefinition::SetURL_Tag( const wchar_t* url_tag )
{
  ON_wString s(url_tag);
  s.TrimLeftAndRight();
  if (s == m_url_tag)
    return;


  if (s.IsEmpty())
    m_url_tag = ON_wString::EmptyString;
  else
    m_url_tag = s;
  Internal_ContentChanged();
}

const ON_SimpleArray<ON_UUID>& ON_InstanceDefinition::InstanceGeometryIdList() const
{
  return m_object_uuid;
}

void ON_InstanceDefinition::SetInstanceGeometryIdList(
  const  ON_SimpleArray<ON_UUID>& instance_geometry_id_list
)
{
  if (&instance_geometry_id_list == &m_object_uuid)
    return; // lists are identical

  if (m_object_uuid.UnsignedCount() == instance_geometry_id_list.UnsignedCount())
  {
    if (0 == m_object_uuid.UnsignedCount())
      return; // nothing in either list
    if (0 == memcmp(instance_geometry_id_list.Array(), m_object_uuid.Array(), m_object_uuid.UnsignedCount() * sizeof(ON_UUID)) )
      return; // lists are identical
  }

  // Change m_object_uuid[].
  m_object_uuid = instance_geometry_id_list;

  Internal_ContentChanged();
}


void ON_InstanceDefinition::ClearInstanceGeometryIdList()
{
  if (0 == m_object_uuid.Count())
    return;
  m_object_uuid.Destroy();
  Internal_ContentChanged();
}

int ON_InstanceDefinition::Internal_InstanceGeometryIdIndex(
    ON_UUID id
) const
{
  if (ON_nil_uuid == id || m_object_uuid.Count() <= 0 )
    return false;
  for (int i = 0; i < m_object_uuid.Count(); i++)
  {
    if (m_object_uuid[i] == id)
      return i;
  }
  return ON_UNSET_INT_INDEX;
}


bool ON_InstanceDefinition::IsInstanceGeometryId(ON_UUID id) const
{
  return Internal_InstanceGeometryIdIndex(id) >= 0;
}

bool ON_InstanceDefinition::RemoveInstanceGeometryId(ON_UUID id)
{
  if (ON_nil_uuid == id)
    return false;
 int i = Internal_InstanceGeometryIdIndex(id);
 if ( i >= 0 && i < m_object_uuid.Count() && id == m_object_uuid[i])
 {
    m_object_uuid.Remove(i);
    Internal_ContentChanged();
    return true;
  }
  return false;
}

bool ON_InstanceDefinition::RemoveInstanceGeometryId(
  int id_index
)
{
  if (id_index >= 0 && id_index < m_object_uuid.Count())
  {
    m_object_uuid.Remove(id_index);
    Internal_ContentChanged();
    return true;
  }
  return false;
}

bool ON_InstanceDefinition::AddInstanceGeometryId(ON_UUID id)
{
  if (ON_nil_uuid == id)
    return false;

  m_object_uuid.Append(id);
  Internal_ContentChanged();
  return true;
}

void ON_InstanceDefinition::Internal_AccumulateHash() const
{
  if (ON_SHA1_Hash::ZeroDigest == m_content_hash)
  {
    ON_SHA1 sha1;
    
    sha1.AccumulateUnsigned32(static_cast<unsigned int>(m_idef_update_type));

    if ( 
      (ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static == m_idef_update_type  
        || ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded == m_idef_update_type)
      && m_object_uuid.Count() > 0
      )
    {
      for (int i = 0; i < m_object_uuid.Count(); i++)
      {
        sha1.AccumulateId(m_object_uuid[i]);
      }
      sha1.AccumulateBoundingBox(m_bbox);
      sha1.AccumulateUnitSystem(m_us);
    }

    if ( IsLinkedType() && m_linked_file_reference.IsSet() )
    {
      sha1.AccumulateString(m_linked_file_reference.FullPath());
      if (ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked == m_idef_update_type)
      {
        sha1.AccumulateUnsigned8(static_cast<unsigned char>(m_linked_component_appearance));
      }
      sha1.AccumulateBool(m_bSkipNestedLinkedDefinitions);
    }

    m_geometry_content_hash = sha1.Hash();

    sha1.AccumulateString(m_description);
    sha1.AccumulateString(m_url);
    sha1.AccumulateString(m_url_tag);

    m_content_hash = sha1.Hash();
  }
}


const ON_SHA1_Hash ON_InstanceDefinition::GeometryContentHash() const
{
  Internal_AccumulateHash();
  return m_geometry_content_hash;
}

const ON_SHA1_Hash ON_InstanceDefinition::ContentHash() const
{
  Internal_AccumulateHash();
  return m_content_hash;
}

const ON_wString ON_InstanceDefinition::Description() const
{
  return m_description;
}

void ON_InstanceDefinition::SetDescription( const wchar_t* description )
{
  ON_wString s(description);
  s.TrimLeftAndRight();
  if (s == m_description)
    return;

  if ( s.IsEmpty() )
    m_description = ON_wString::EmptyString;
  else
    m_description = s;
  Internal_ContentChanged();
}

void ON_InstanceDefinition::Internal_ContentChanged()
{
  IncrementContentVersionNumber();
  m_geometry_content_hash = ON_SHA1_Hash::ZeroDigest;
  m_content_hash = ON_SHA1_Hash::ZeroDigest;
}

const ON_FileReference ON_InstanceDefinition::LinkedFileReference() const
{
  return m_linked_file_reference;
}

const ON_wString& ON_InstanceDefinition::LinkedFilePath() const
{
  return m_linked_file_reference.FullPath();
}

bool ON_InstanceDefinition::SetLinkedFileReference(
  ON_InstanceDefinition::IDEF_UPDATE_TYPE linked_definition_type,
  ON_FileReference linked_file_reference
  )
{
  return Internal_SetLinkedFileReference(linked_definition_type,linked_file_reference,ON_CheckSum::UnsetCheckSum);
}

bool ON_InstanceDefinition::SetLinkedFileReference(
  ON_InstanceDefinition::IDEF_UPDATE_TYPE linked_definition_type,
  const wchar_t* linked_file_full_path
  )
{
  ON_FileReference linked_file_reference;
  linked_file_reference.SetFullPath(linked_file_full_path, false);
  if (ON_FileSystem::IsFile(linked_file_full_path))
    linked_file_reference.SetFullPathStatus(ON_FileReference::Status::FullPathValid);
  return SetLinkedFileReference(linked_definition_type,linked_file_reference);
}


bool ON_InstanceDefinition::SetInstanceDefinitionType(
  IDEF_UPDATE_TYPE instance_definition_type
  )
{
  if ( instance_definition_type == InstanceDefinitionType() )
    return true;

  bool rc;
  bool bChanged = false;

  switch (instance_definition_type)
  {
  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset:
  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static:
    if ( m_idef_update_type != instance_definition_type )
      bChanged = true;
    ClearLinkedFileReference();
    m_idef_update_type = instance_definition_type;
    SetLinkedComponentAppearance(ON_InstanceDefinition::eLinkedComponentAppearance::Unset);
    rc = true;
    break;

  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded:
    if (ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked == InstanceDefinitionType() )
    {
      if ( m_idef_update_type != instance_definition_type )
        bChanged = true;
      m_idef_update_type = instance_definition_type;
      SetLinkedComponentAppearance(ON_InstanceDefinition::eLinkedComponentAppearance::Unset);
      rc = true;
    }
    else
    {
      ON_ERROR("Invalid instance_definition_type parameter. Use SetLinkedFilePath() to create linked instance defintions.");
      rc = false;
    }
    break;

  case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked:
    if (ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded == InstanceDefinitionType() )
    {
      if ( m_idef_update_type != instance_definition_type )
        bChanged = true;
      m_idef_update_type = instance_definition_type;
      SetLinkedComponentAppearance(ON_InstanceDefinition::eLinkedComponentAppearance::Active);
      rc = true;
    }
    else
    {
      ON_ERROR("Invalid instance_definition_type parameter. Use SetLinkedFilePath() to create linked instance defintions.");
      rc = false;
    }
    break;

  default:
    ON_ERROR("Invalid instance_definition_type parameter");
    rc = false;
    break;
  }

  if ( bChanged)
    Internal_ContentChanged();

  return rc;
}

bool ON_InstanceDefinition::Internal_SetLinkedFileReference(
  ON_InstanceDefinition::IDEF_UPDATE_TYPE linked_definition_type,
  const ON_FileReference& linked_file_reference,
  ON_CheckSum V5_checksum
  )
{
  bool bInvalidFullPath = false;
  bool bInvalidRelativePath = false;
  bool rc = false;
  linked_definition_type = ON_InstanceDefinition::InstanceDefinitionTypeFromUnsigned(static_cast<unsigned int>(linked_definition_type));
  bool bIsLinkedIdefType
    = ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked == linked_definition_type
    || ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded == linked_definition_type;
  ON_wString full_path;
  ON_wString relative_path;
  if (bIsLinkedIdefType)
  {
    full_path = linked_file_reference.FullPath();
    full_path.TrimLeftAndRight();
    relative_path = linked_file_reference.RelativePath();
    relative_path.TrimLeftAndRight();

    if (full_path.IsNotEmpty())
    {
      // Use local path in case drive, dir, fname or ext are being reused.
      const wchar_t* v = nullptr;
      const wchar_t* d = nullptr;
      const wchar_t* f = nullptr;
      const wchar_t* e = nullptr;
      on_wsplitpath(static_cast<const wchar_t*>(full_path), &v, &d, &f, &e);
      if (nullptr == f || nullptr == d || f <= d || '.' == d[0])
      {
        if (relative_path.IsEmpty() && nullptr != f && (nullptr == d || (f > d && '.' == d[0])))
        {
          relative_path = full_path;
          full_path = ON_wString::EmptyString;
        }
        else
        {
          ON_ERROR("Invalid full path.");
          full_path = ON_wString::EmptyString;
          bInvalidRelativePath = true;
        }
      }
    }

    if (relative_path.IsNotEmpty())
    {
      // Use local path in case drive, dir, fname or ext are being reused.
      const wchar_t* v = nullptr;
      const wchar_t* d = nullptr;
      const wchar_t* f = nullptr;
      const wchar_t* e = nullptr;
      on_wsplitpath(static_cast<const wchar_t*>(relative_path), &v, &d, &f, &e);
      if (nullptr == f || (nullptr != d && '.' != d[0]))
      {
        if (full_path.IsEmpty() && nullptr != f && nullptr != d && f > d && ON_FileSystemPath::IsDirectorySeparator(d[0], true))
        {
          full_path = relative_path;
          relative_path = ON_wString::EmptyString;
        }
        else
        {
          ON_ERROR("Invalid relative path.");
          relative_path = ON_wString::EmptyString;
          bInvalidRelativePath = true;
        }
      }
    }
  }

  if ( false == bIsLinkedIdefType || (full_path.IsEmpty() && relative_path.IsEmpty()) )
  {
    if (bIsLinkedIdefType)
    {
      ON_ERROR("A valid file name must be specified for linked instance definitions.");
    }
    ClearLinkedFileReference();
    if ( m_idef_update_type != linked_definition_type )
      Internal_ContentChanged();
    rc = true;
  }
  else
  {
    if ( m_linked_file_reference.FullPath() != full_path 
      || m_linked_file_reference.RelativePath() != relative_path
      || ON_ContentHash::DifferentContent(m_linked_file_reference.ContentHash(),linked_file_reference.ContentHash())
      || m_idef_update_type != linked_definition_type
      )
      Internal_ContentChanged();

    const ON_FileReference::Status file_status 
      = ON_FileSystem::IsFile(full_path)
      ? ON_FileReference::Status::FullPathValid
      : (full_path.IsEmpty() ? ON_FileReference::Status::Unknown : ON_FileReference::Status::FileNotFound)
      ;

    m_linked_file_reference = linked_file_reference;
    m_linked_file_reference.SetFullPath(full_path,false);
    if ( ON_FileReference::Status::FullPathValid == file_status )
      m_linked_file_reference.ClearRelativePath();
    else
      m_linked_file_reference.SetRelativePath(relative_path);
    m_linked_file_reference.SetContentHash(linked_file_reference.ContentHash());
    m_linked_file_reference.SetFullPathStatus(file_status);
    m_linked_file_reference.SetEmbeddedFileId(linked_file_reference.EmbeddedFileId());

    m_linked_file_V5_checksum = V5_checksum;
    m_idef_update_type = linked_definition_type;
    if ( ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked != m_idef_update_type )
      rc = SetLinkedComponentAppearance(ON_InstanceDefinition::eLinkedComponentAppearance::Unset);
    else if (
      ON_InstanceDefinition::eLinkedComponentAppearance::Active != LinkedComponentAppearance() 
      && ON_InstanceDefinition::eLinkedComponentAppearance::Reference != LinkedComponentAppearance() 
      )
      rc = SetLinkedComponentAppearance(ON_InstanceDefinition::eLinkedComponentAppearance::Reference);
    else
      rc = true;

    if (bInvalidFullPath || bInvalidRelativePath)
      rc = false;
  }
  return rc;
}


void ON_InstanceDefinition::ClearLinkedFileReference()
{
  bool bChanged = false;
  if (ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset != m_idef_update_type)
  {
    if ( m_idef_update_type != ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static )
      bChanged = true;
    m_idef_update_type = ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static;
  }
  if ( m_linked_file_reference.IsSet()  || m_bSkipNestedLinkedDefinitions)
    bChanged = true;
  m_linked_file_reference = ON_FileReference::Unset;
  m_linked_file_V5_checksum = ON_CheckSum::UnsetCheckSum;
  SetLinkedComponentAppearance(ON_InstanceDefinition::eLinkedComponentAppearance::Unset);
  m_bSkipNestedLinkedDefinitions = false;
  if ( bChanged )
    Internal_ContentChanged();
}

void ON_InstanceDefinition::ClearLinkedFileContentHash()
{
  m_linked_file_reference.ClearContentHash();
  m_linked_file_V5_checksum = ON_CheckSum::UnsetCheckSum;
}

void ON_InstanceDefinition::ClearLinkedFileRelativePath()
{
  if (m_linked_file_reference.RelativePath().IsEmpty())
    return;
  m_linked_file_reference.ClearRelativePath();
  Internal_ContentChanged();
}

const ON_UnitSystem& ON_InstanceDefinition::UnitSystem() const
{
  return m_us;
}

void ON_InstanceDefinition::SetUnitSystem( ON::LengthUnitSystem us )
{
  // make sure we are not getting garbage cast as an ON::LengthUnitSystem
  if ( us == ON::LengthUnitSystemFromUnsigned(static_cast<unsigned int>(us)) 
    && ON::LengthUnitSystem::CustomUnits != us
    )
  {
    if (m_us.UnitSystem() != us)
    {
      m_us.SetUnitSystem(us);
      Internal_ContentChanged();
    }
  }
}

void ON_InstanceDefinition::SetUnitSystem( const ON_UnitSystem& us )
{
  // make sure we are not getting garbage cast as an ON::LengthUnitSystem
  if ( us.IsValid() && !(us == m_us) )
  {
    m_us = us;
    Internal_ContentChanged();
  }
}

ON_OBJECT_IMPLEMENT( ON_InstanceRef, ON_Geometry, "F9CFB638-B9D4-4340-87E3-C56E7865D96A" );

const double ON_InstanceRef::SingularTransformationTolerance = 1.0e-6;

bool ON_InstanceRef::IsValid( ON_TextLog* text_log ) const
{
  if ( 0 == ON_UuidCompare( m_instance_definition_uuid, ON_nil_uuid) )
  {
    if ( text_log )
      text_log->Print("ON_InstanceRef has nil m_instance_definition_uuid.\n");
    return false;
  }

  ON_Xform tmp = m_xform.Inverse()*m_xform;
  if ( !tmp.IsIdentity( ON_InstanceRef::SingularTransformationTolerance) )
  {
    if ( text_log )
      text_log->Print("ON_InstanceRef has singular m_xform.\n");
    return false;
  }
  return true;
}

bool ON_InstanceRef::Write(
       ON_BinaryArchive& binary_archive
     ) const
{
  bool rc = binary_archive.Write3dmChunkVersion(1,0);
  if ( rc )
    rc = binary_archive.WriteUuid( m_instance_definition_uuid );
  if ( rc )
    rc = binary_archive.WriteXform( m_xform );
  if ( rc )
    rc = binary_archive.WriteBoundingBox( m_bbox );
  return rc;
}

bool ON_InstanceRef::Read(
       ON_BinaryArchive& binary_archive
     )
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = binary_archive.Read3dmChunkVersion(&major_version,&minor_version);
  if ( rc )
  {
    if ( major_version != 1 )
      rc = false;
    if (rc )
      rc = binary_archive.Read3dmReferencedComponentId( ON_ModelComponent::Type::InstanceDefinition, &m_instance_definition_uuid );
    if ( rc )
      rc = binary_archive.ReadXform( m_xform );
    if ( rc )
      rc = binary_archive.ReadBoundingBox( m_bbox );
  }
  return rc;
}

ON::object_type ON_InstanceRef::ObjectType() const
{
  return ON::instance_reference;
}


// virtual ON_Geometry overrides
int ON_InstanceRef::Dimension() const
{
  return 3;
}

bool ON_InstanceRef::GetBBox(
       double* boxmin,
       double* boxmax,
       bool bGrowBox
       ) const
{
  if ( !boxmin || !boxmax )
  {
    bGrowBox = false;
  }
  else if ( bGrowBox )
  {
    bGrowBox = ON_BoundingBox(ON_3dPoint(boxmin),ON_3dPoint(boxmax)).IsValid();
  }

  if( m_bbox.IsValid() )
  {
    if( bGrowBox )
    {
      if( boxmin[0] > m_bbox.m_min.x ) boxmin[0] = m_bbox.m_min.x;
      if( boxmin[1] > m_bbox.m_min.y ) boxmin[1] = m_bbox.m_min.y;
      if( boxmin[2] > m_bbox.m_min.z ) boxmin[2] = m_bbox.m_min.z;

      if( boxmax[0] < m_bbox.m_max.x ) boxmax[0] = m_bbox.m_max.x;
      if( boxmax[1] < m_bbox.m_max.y ) boxmax[1] = m_bbox.m_max.y;
      if( boxmax[2] < m_bbox.m_max.z ) boxmax[2] = m_bbox.m_max.z;
    }
    else
    {
      if( boxmin )
      {
        boxmin[0] = m_bbox.m_min.x;
        boxmin[1] = m_bbox.m_min.y;
        boxmin[2] = m_bbox.m_min.z;
      }
      if( boxmax )
      {
        boxmax[0] = m_bbox.m_max.x;
        boxmax[1] = m_bbox.m_max.y;
        boxmax[2] = m_bbox.m_max.z;
      }
      bGrowBox = true;
    }
  }

  return bGrowBox;
}

bool ON_InstanceRef::Transform( 
       const ON_Xform& xform
       )
{
  ON_Geometry::Transform(xform);
  m_xform = xform*m_xform;
  m_bbox.Transform(xform);
  return true;
}

bool ON_InstanceRef::IsDeformable() const
{
  // 25 Feb 2006 Dale Lear - this seems wrong to me.
  return true;
}

bool ON_InstanceRef::MakeDeformable()
{
  // 25 Feb 2006 Dale Lear - this seems wrong to me.
  return true;
}


bool ON_ReferencedComponentSettingsImpl::ReadImpl(
  ON_BinaryArchive& binary_archive
  )
{
  InternalDestroyHelper();
  int major_version = 0;
  int minor_version = 0;
  if (!binary_archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version))
    return false;


  bool bSuppressPartiallyReadChunkWarning = false;
  bool rc = false;
  // The layers saved here are not in the active model or archive.
  const bool bReferencedComponentIndexMapping = binary_archive.ReferencedComponentIndexMapping();
  binary_archive.SetReferencedComponentIndexMapping(false);
  for (;;)
  {
    // Read copies of the reference file layers. The name,index,id
    // of these layers are the values from the reference file
    // the last time the linked instance definition or worksession
    // was reference file was read.
    if ( !binary_archive.ReadArray(m_layer_referenced_file_copy) )
      break;

    // Read copies of the runtime model reference layers saved from 
    // the last time "this" model was saved. The name,index,id
    // values are all unset because the can vary with each runtime
    // instance. The m_layer_model_copy[] array should have
    // the same length as m_layer_referenced_file_copy[] and
    // the layers correspond.
    if ( !binary_archive.ReadArray(m_layer_model_copy) )
      break;

    bool bHaveParentLayer = false;
    if ( !binary_archive.ReadBool(&bHaveParentLayer) )
      break;

    if ( bHaveParentLayer )
    {
      ON_Object* p = nullptr;
      if (!binary_archive.ReadObject(&p))
      {
        if (nullptr != p )
          delete p;
        break;
      }
      if ( nullptr == p )
        break;
      m_layer_table_parent_layer = ON_Layer::Cast(p);
      if (nullptr == m_layer_table_parent_layer)
      {
        delete p;
        break;
      }
    }
    
    // end of 1.0 chunk

    
    // max_minor_version = minor_version number used in Write();
    // This suppresses partially read chunk warnings when old code reads new files.
    const int max_minor_version = 0;
    bSuppressPartiallyReadChunkWarning = (minor_version > max_minor_version);
    rc = true;
    break;
  }
  binary_archive.SetReferencedComponentIndexMapping(bReferencedComponentIndexMapping);

  if ( !binary_archive.EndRead3dmChunk(bSuppressPartiallyReadChunkWarning) )
    rc = false;

  if (m_layer_model_copy.Count() != m_layer_referenced_file_copy.Count())
    InternalDestroyListsHelper();

  m_bHasReferenceLayerTableParentLayer = (nullptr != m_layer_table_parent_layer);

  // Prior to August 2017, a bug was saving per view sttings that applied to the 
  // reference model. This for loop will delete those settings
  for (int i = 0; i < m_layer_referenced_file_copy.Count(); i++)
  {
    ON_Layer* layer = m_layer_referenced_file_copy[i];
    if (nullptr != layer)
      layer->DeletePerViewportSettings(ON_nil_uuid);
  }

  return rc;
}

bool ON_ReferencedComponentSettingsImpl::WriteImpl(
  ON_BinaryArchive& binary_archive
  ) const
{
  int major_version = 1;
  int minor_version = 0;
  if (!binary_archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,major_version,minor_version))
    return false;

  // The layers saved here are not in the active model or archive.
  const bool bReferencedComponentIndexMapping = binary_archive.ReferencedComponentIndexMapping();
  binary_archive.SetReferencedComponentIndexMapping(false);
  bool rc = false;
  for (;;)
  {
    unsigned int layers_count = m_layer_referenced_file_copy.UnsignedCount();
    if (layers_count != m_layer_model_copy.UnsignedCount())
      layers_count = 0;

    // Write layers copied from reference file
    ON_Layer*const* layers = (layers_count > 0) ? m_layer_referenced_file_copy.Array() : nullptr;
    if ( !binary_archive.WriteArray(layers_count,layers) )
      break;

    // Write corresponding reference layers in the model.
    layers = (layers_count > 0) ? m_layer_model_copy.Array() : nullptr;
    if (!binary_archive.WriteArray(layers_count, layers))
      break;

    // Write grandparent layer settings.
    bool bHaveParentLayer = ( nullptr != m_layer_table_parent_layer );
    if ( !binary_archive.WriteBool(bHaveParentLayer) )
      break;

    if ( bHaveParentLayer )
    {
      if ( !binary_archive.WriteObject(m_layer_table_parent_layer) )
        break;
    }

    rc = true;
    break;
  }
  if ( !binary_archive.EndWrite3dmChunk() )
    rc = false;
  binary_archive.SetReferencedComponentIndexMapping(bReferencedComponentIndexMapping);
  return rc;
}


bool ON_InstanceDefinition::HasLinkedIdefReferenceComponentSettings() const
{
  return (
    IsLinkedType()
    && nullptr != LinkedIdefReferenceComponentSettings()
    && LinkedIdefReferenceComponentSettings()->IsNotEmpty()
    );
}

void ON_InstanceDefinition::ClearLinkedIdefReferenceComponentSettings()
{
  if (nullptr != m_linked_idef_component_settings)
  {
    delete m_linked_idef_component_settings;
    m_linked_idef_component_settings = nullptr;
    Internal_ContentChanged();
  }
}

const ON_ReferencedComponentSettings* ON_InstanceDefinition::LinkedIdefReferenceComponentSettings() const
{
  return m_linked_idef_component_settings;
}

ON_ReferencedComponentSettings* ON_InstanceDefinition::LinkedIdefReferenceComponentSettings(
  bool bCreateIfNonePresent
)
{
  if (nullptr == m_linked_idef_component_settings && bCreateIfNonePresent)
    m_linked_idef_component_settings = new ON_ReferencedComponentSettings();
  if ( nullptr != m_linked_idef_component_settings )
    Internal_ContentChanged();
  return m_linked_idef_component_settings;
}

//static int compareLayerPtrId(const void* A, const void*B)
//{
//  if ( 0 == A )
//  {
//    return 0 == B ? 0 : -1;
//  }
//  if ( 0 == B )
//  {
//    return 1;
//  }
//
//  const ON_Layer* a = (0!=A) ? ( *((ON_Layer**)A) ) : 0;
//  const ON_Layer* b = (0!=B) ? ( *((ON_Layer**)B) ) : 0;
//  if ( 0 == a )
//  {
//    return (0 == b) ? 0 : -1;
//  }
//  if ( 0 == b )
//  {
//    return 1;
//  }
//
//  // NOTE WELL:
//  //   Compare only m_layer_id.  Other values may differ and
//  //   adding compares to them will break the code that uses
//  //   this function.
//  return ON_UuidCompare(a->Id(),b->Id());
//}
//
//static int compareUuidIndexId(const void* a, const void* b)
//{
//  return ON_UuidIndex::CompareId((const ON_UuidIndex*)a,(const ON_UuidIndex*)b);
//}


///////////////////////////////////////////////////////////////////
class /*NEVER EXPORT THIS CLASS DEFINITION*/ ON_OBSOLETE_IDefAlternativePathUserData : public ON_UserData
{
  // USED IN V4 and V5 files to save relative paths tol linked files.
  // In V6 and later this information is in the m_linked_file_relative_path memember.
  ON_OBJECT_DECLARE(ON_OBSOLETE_IDefAlternativePathUserData);

public:
  ON_OBSOLETE_IDefAlternativePathUserData()
  {
    m_userdata_uuid = ON_CLASS_ID(ON_OBSOLETE_IDefAlternativePathUserData);
    m_application_uuid = ON_opennurbs5_id;
    m_userdata_copycount = 1;
  }
  
  ~ON_OBSOLETE_IDefAlternativePathUserData() = default;

  ON_OBSOLETE_IDefAlternativePathUserData(const ON_OBSOLETE_IDefAlternativePathUserData& src)
    : ON_UserData(src)
  {
    m_userdata_uuid = ON_CLASS_ID(ON_OBSOLETE_IDefAlternativePathUserData);
    m_application_uuid = ON_opennurbs5_id;
    m_alternate_path = src.m_alternate_path;
    m_bRelativePath = src.m_bRelativePath;
  }
  ON_OBSOLETE_IDefAlternativePathUserData& operator=(const ON_OBSOLETE_IDefAlternativePathUserData& src)
  {
    if (this != &src)
    {
      ON_UserData::operator=(src);
      m_alternate_path = src.m_alternate_path;
      m_bRelativePath = src.m_bRelativePath;
    }
    return *this;
  }

public:
  bool IsValid( ON_TextLog* text_log = nullptr ) const override;
  bool Write(ON_BinaryArchive& binary_archive) const override;
  bool Read(ON_BinaryArchive& binary_archive) override;
  bool Archive() const override;
  bool GetDescription( ON_wString& description ) override;

  /*
  ON_OBSOLETE_IDefAlternativePathUserData is obsolete user data and exists  to
  for supporting saving m_linked_file_relative_path in V5 files
  and reading the "alternative" path information from V5 files.
  */
  bool DeleteAfterWrite(
    const class ON_BinaryArchive& archive,
    const class ON_Object* parent_object
    ) const override;

  bool DeleteAfterRead( 
    const class ON_BinaryArchive& archive,
    class ON_Object* parent_object
    ) const override;


public:
  ON_wString m_alternate_path;
  bool m_bRelativePath = false;
};

ON_OBJECT_IMPLEMENT(ON_OBSOLETE_IDefAlternativePathUserData,ON_UserData,"F42D9671-21EB-4692-9B9A-BC3507FF28F5");

bool ON_OBSOLETE_IDefAlternativePathUserData::DeleteAfterWrite(
  const class ON_BinaryArchive& archive,
  const class ON_Object* parent_object
  ) const
{
  // This user data is attached when writing V4 and V5 files and is then deleted after it is written.
  return true;
}

bool ON_OBSOLETE_IDefAlternativePathUserData::DeleteAfterRead(
  const class ON_BinaryArchive& archive,
  class ON_Object* parent_object
  ) const
{
  // This user data is read from V4 and V5 files and is then deleted after
  // the information is transfered to idef->m_linked_file_reference.
  for (;;)
  {
    ON_InstanceDefinition* idef = ON_InstanceDefinition::Cast(parent_object);
    if ( nullptr == idef )
      break;
    if (false == idef->IsLinkedType())
      break;
    ON_wString s = m_alternate_path;
    s.TrimLeftAndRight();
    if (s.IsEmpty())
      break;
    ON_FileReference linked_file_reference = idef->LinkedFileReference();
    if (m_bRelativePath)
    {
      if (linked_file_reference.RelativePath().IsNotEmpty())
        break;
      linked_file_reference.SetRelativePath(s);
      idef->SetLinkedFileReference(idef->InstanceDefinitionType(),linked_file_reference);
    }
    else
    {
      if (linked_file_reference.FullPath().IsNotEmpty())
        break;
      const ON_wString rel_path = linked_file_reference.RelativePath();
      const ON_ContentHash content_hash = linked_file_reference.ContentHash();
      linked_file_reference.SetFullPath(s,false);
      linked_file_reference.SetContentHash(content_hash);
      linked_file_reference.SetRelativePath(rel_path);
      idef->SetLinkedFileReference(idef->InstanceDefinitionType(),linked_file_reference);
    }

    break;
  }
  return true;
}

bool ON_OBSOLETE_IDefAlternativePathUserData::IsValid( ON_TextLog* text_log ) const
{
  return !m_alternate_path.IsEmpty();
}

bool ON_OBSOLETE_IDefAlternativePathUserData::Write(ON_BinaryArchive& binary_archive) const
{
  bool rc = binary_archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);
  if ( !rc )
    return false;

  rc = false;
  for(;;)
  {
    if ( !binary_archive.WriteString(m_alternate_path) )
      break;
    if ( !binary_archive.WriteBool(m_bRelativePath) )
      break;
    rc = true;
    break;
  }

  if ( !binary_archive.EndWrite3dmChunk() )
    rc = false;

  return rc;
}

bool ON_OBSOLETE_IDefAlternativePathUserData::Read(ON_BinaryArchive& binary_archive)
{
  m_alternate_path = ON_wString::EmptyString;
  m_bRelativePath = false;

  int major_version = 0;
  int minor_version = 0;
  bool rc = binary_archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if ( !rc )
    return false;

  rc = false;
  while ( 1 == major_version )
  {
    if ( !binary_archive.ReadString(m_alternate_path) )
      break;
    if ( !binary_archive.ReadBool(&m_bRelativePath) )
      break;
    rc = true;
    break;
  }

  if ( !binary_archive.EndRead3dmChunk() )
    rc = false;

  return rc;
}

// virtual ON_UserData override
bool ON_OBSOLETE_IDefAlternativePathUserData::Archive() const
{
  // don't save empty settings
  return m_alternate_path.IsNotEmpty();
}

// virtual ON_UserData override
bool ON_OBSOLETE_IDefAlternativePathUserData::GetDescription( ON_wString& description )
{
  description = L"OBSOLETE Linked Instance Definition Alternate Path";
  return true;
}

bool ON_InstanceDefinition::Write(
  ON_BinaryArchive& archive
) const
{
  if (archive.Archive3dmVersion() <= 50)
    return Internal_WriteV5(archive);

  return Internal_WriteV6(archive);
}

bool ON_InstanceDefinition::Read(
  ON_BinaryArchive& archive
)
{
  Internal_ContentChanged();

  if (archive.Archive3dmVersion() <= 50)
    return Internal_ReadV5(archive);

  if (archive.Archive3dmVersion() <= 60)
  {
    if ( archive.ArchiveOpenNURBSVersion() <= 2348834153 )
      return Internal_ReadV5(archive);
    //if ( archive.ArchiveOpenNURBSVersion() >= unknown at this time )
    //  return Internal_ReadV6(archive);
    ON__UINT32 typecode = 0;
    ON__INT64 big_value = 0;
    if ( !archive.PeekAt3dmBigChunkType(&typecode, &big_value) )
      return Internal_ReadV5(archive);
    if ( TCODE_ANONYMOUS_CHUNK != typecode )
      return Internal_ReadV5(archive);
  }

  return Internal_ReadV6(archive);
}

bool ON_InstanceDefinition::Internal_WriteV5(
  ON_BinaryArchive& binary_archive
  ) const
{
  bool rc = false;
  ON_wString linked_file_relative_path;

  for (;;)
  {
    const int minor_version_number 
      = (binary_archive.Archive3dmVersion() < 60)
      ? 6 // V5 file
      : 7 // early WIP V6 file.
      ;
    if ( !binary_archive.Write3dmChunkVersion(1, minor_version_number) )
      break;

    // version 1.0 fields
    if (!binary_archive.WriteUuid(Id()))
      break;

    if (binary_archive.Archive3dmVersion() >= 4
      && ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked == InstanceDefinitionType())
    {
      // linked instance definition geometry is never in the file
      ON_SimpleArray<ON_UUID> empty_uuid_list;
      if (!binary_archive.WriteArray(empty_uuid_list))
        break;
    }
    else
    {
      if (!binary_archive.WriteArray(m_object_uuid))
        break;
    }

    if (!binary_archive.WriteModelComponentName(*this))
      break;

    if (!binary_archive.WriteString(m_description))
      break;
    if (!binary_archive.WriteString(m_url))
      break;

    if (!binary_archive.WriteString(m_url_tag))
      break;

    if (!binary_archive.WriteBoundingBox(m_bbox))
      break;

    bool bWriteLinkedFile = false;
    unsigned int idef_type_indicator;
    switch (InstanceDefinitionType())
    {
    case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset:
      idef_type_indicator = ON_UNSET_UINT_INDEX;
      break;
    case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static:
      idef_type_indicator = 0;
      break;
    case ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded:
      bWriteLinkedFile = true;
      idef_type_indicator = 2;
      break;
    case ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked:
      bWriteLinkedFile = true;
      idef_type_indicator = 3;
      break;
    default:
      idef_type_indicator = ON_UNSET_UINT_INDEX;
      break;
    }
    if (!binary_archive.WriteInt(idef_type_indicator))
      break;

    const ON_wString linked_file_path = m_linked_file_reference.FullPath();
    if (!binary_archive.WriteString(bWriteLinkedFile ? linked_file_path : ON_wString::EmptyString))
      break;

    // version 1.1 fields
    if  (
      false ==
      (bWriteLinkedFile 
      ? m_linked_file_V5_checksum.Write(binary_archive) 
      : ON_CheckSum::UnsetCheckSum.Write(binary_archive))
      )
      break;

    // version 1.2 fields
    if (!binary_archive.WriteInt(static_cast<unsigned int>(m_us.UnitSystem())))
      break;

    // version 1.3 fields - added 6 March 2006
    if (!binary_archive.WriteDouble(m_us.MetersPerUnit(ON_DBL_QNAN)))
      break;

    const bool bLegacyBoolThatIsAlwaysFalse = false;
    if (!binary_archive.WriteBool(bLegacyBoolThatIsAlwaysFalse))
      break;

    // version 1.4 fields
    if (!m_us.Write(binary_archive))
      break;

    // version 1.5 fields
    int idef_update_depth = m_bSkipNestedLinkedDefinitions ? 1 : 0;
    if (!binary_archive.WriteInt(idef_update_depth))
      break;

    // version 1.6 fields ( added 14 February 2012 )
    if (!binary_archive.WriteInt(static_cast<unsigned int>(LinkedComponentAppearance())))
      break;

    if (6 == minor_version_number)
    {
      rc = true;
      break;
    }

    // version 1.7 fields ( added 25 Nov 2016 V6 files)
    if ( !binary_archive.WriteBool(bWriteLinkedFile) )
      break;

    if (bWriteLinkedFile)
    {
      if (!m_linked_file_reference.Write(true,binary_archive))
        break;
    }

    const bool bHaveObsoleteLinkedLayerSettings = false;
    if (!binary_archive.WriteBool(bHaveObsoleteLinkedLayerSettings))
      break;

    rc = true;
    break;
  }

  if (rc 
    && this->IsLinkedType()
    && 50 == binary_archive.Archive3dmVersion()
    )
  {
    if (linked_file_relative_path.IsNotEmpty())
    {
      // Attaches a ON_OBSOLETE_IDefAlternativePathUserData that will 
      // be saved in the V5 file and then deleted after it is written.
      ON_OBSOLETE_IDefAlternativePathUserData* ud = new ON_OBSOLETE_IDefAlternativePathUserData();
      if (nullptr != ud)
      {
        ud->m_alternate_path = linked_file_relative_path;
        ud->m_bRelativePath = true;
        const_cast<ON_InstanceDefinition*>(this)->AttachUserData(ud);
      }
    }
  }

  return rc;
}




bool ON_InstanceDefinition::Internal_ReadV5(
  ON_BinaryArchive& binary_archive
  )
{
  *this = ON_InstanceDefinition::Unset;
  Internal_ContentChanged();

  int major_version = 0;
  int minor_version = 0;
  if (!binary_archive.Read3dmChunkVersion(&major_version,&minor_version))
    return false;
  bool rc = false;
  for (;;)
  {
    if ( major_version != 1 )
      break;

    // version 1.0 fields
    ON_UUID idef_id = ON_nil_uuid;
    if ( !binary_archive.ReadUuid( idef_id ) )
      break;
    SetId(idef_id);
    if ( !binary_archive.ReadArray( m_object_uuid ) )
      break;

    ON_wString idef_name;
    if ( !binary_archive.ReadString( idef_name ))
      break;
    SetName(idef_name);
    if ( !binary_archive.ReadString( m_description ))
      break;
    if ( !binary_archive.ReadString( m_url ))
      break;
    if ( !binary_archive.ReadString( m_url_tag ))
      break;

    if ( !binary_archive.ReadBoundingBox( m_bbox ))
      break;

    // m_idef_update_type was an unsigned int and got changed to an enum.  Read and write
    // as an unsigned int to support backwards compatibility
    unsigned int idef_type_indicator = 0;
    if ( !binary_archive.ReadInt(&idef_type_indicator))
      break;

    bool bLinkedFile;
    switch (idef_type_indicator)
    {
    case 0U:
    case 1U:
      m_idef_update_type = ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static;
      bLinkedFile = false;
      break;
    case 2U:
      m_idef_update_type = ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded;
      bLinkedFile = true;
      break;
    case 3U:
      m_idef_update_type = ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked;
      bLinkedFile = true;
      break;
    case ON_UNSET_UINT_INDEX:
      m_idef_update_type = ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset;
      bLinkedFile = false;
      break;
    default:
      m_idef_update_type = ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset;
      bLinkedFile = false;
      break;
    }

    ON_wString linked_file_full_path;
    ON_wString linked_file_relative_path;

    if (!binary_archive.ReadString(linked_file_full_path))
    {
      // when no path can be read, the idef must be converted to static.
      if ( ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset != m_idef_update_type )
        m_idef_update_type = ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static;
      linked_file_full_path = ON_wString::EmptyString;
      break;
    }

    if (linked_file_full_path.IsEmpty())
    {
      bLinkedFile = false;
      if ( ON_InstanceDefinition::IDEF_UPDATE_TYPE::Unset != m_idef_update_type )
        m_idef_update_type = ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static;
    }

    if (bLinkedFile)
    {
      m_linked_file_reference = ON_FileReference(
        linked_file_full_path,
        linked_file_relative_path,
        ON_ContentHash::Unset,
        ON_FileReference::Status::Unknown
        );
    }

    if (minor_version < 1)
    {
      rc = true;
      break;
    }

    // version 1.1 fields
    if (!m_linked_file_V5_checksum.Read(binary_archive))
    {
      m_linked_file_V5_checksum = ON_CheckSum::UnsetCheckSum;
      break;
    }
    if ( false == bLinkedFile )
      m_linked_file_V5_checksum = ON_CheckSum::UnsetCheckSum;
      
    if (minor_version < 2)
    {
      rc = true;
      break;
    }

    // version 1.2 fields
    unsigned int i = ON_UNSET_UINT_INDEX;
    if (!binary_archive.ReadInt(&i))
      break;
    ON::LengthUnitSystem us = ON::LengthUnitSystemFromUnsigned(i);

    if (ON::LengthUnitSystem::CustomUnits == us)
    {
      // If the custom units are valid, then the 1.3 section below
      // will correctly set the custom unit information.
      m_us.SetUnitSystem(ON::LengthUnitSystem::Meters);
    }
    else
      m_us.SetUnitSystem(us);

    if (minor_version < 3)
    {
      rc = true;
      break;
    }

    // version 1.3 fields - added 6 March 2006
    double meters_per_unit = 0.0;
    if (!binary_archive.ReadDouble(&meters_per_unit))
      break;
    if (ON::LengthUnitSystem::CustomUnits == us && meters_per_unit > 0.0)
      m_us.SetCustomUnitSystem(nullptr,meters_per_unit);

    bool bLegacy_m_source_bRelativePath = false;
    if (!binary_archive.ReadBool(&bLegacy_m_source_bRelativePath))
      break;

    if (bLegacy_m_source_bRelativePath)
    {
      linked_file_relative_path = linked_file_full_path;
      linked_file_full_path = ON_wString::EmptyString;
      m_linked_file_reference = ON_FileReference(
        linked_file_full_path,
        linked_file_relative_path,
        ON_ContentHash::Unset,
        ON_FileReference::Status::Unknown
        );
    }

    if (minor_version < 4)
    {
      rc = true;
      break;
    }

    // version 1.4 fields
    if (!m_us.Read(binary_archive))
      break;

    if (minor_version < 5)
    {
      rc = true;
      break;
    }

    // version 1.5 fields
    int idef_update_depth = m_bSkipNestedLinkedDefinitions ? 1 : 0;
    if (!binary_archive.ReadInt(&idef_update_depth))
      break;
    m_bSkipNestedLinkedDefinitions = (1==idef_update_depth);

    if (minor_version < 6)
    {
      rc = true;
      break;
    }

    // version 1.6 fields
    i = 0;
    rc = binary_archive.ReadInt(&i);
    if (i > 0 && i < 256)
      m_linked_component_appearance = ON_InstanceDefinition::LinkedComponentAppearanceFromUnsigned((unsigned char)i);

    if ( minor_version < 7 )
      break;

    // version 1.7 fields;
    bool bReadFileReference = false;
    if ( !binary_archive.ReadBool(&bReadFileReference))
      break;

    if (bReadFileReference)
    {
      if (!m_linked_file_reference.Read(binary_archive))
        break;
      if ( false  == bLinkedFile )
        m_linked_file_reference = ON_FileReference::Unset;
    }

    // skipping the rest of what was in a 1.7 chunk - it didn't work
    // Chunk will be partially read.
    rc = true;
    break;
  }

  if ( ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked == m_idef_update_type )
  {
    if ( LinkedComponentAppearance() != ON_InstanceDefinition::eLinkedComponentAppearance::Active &&  LinkedComponentAppearance() != ON_InstanceDefinition::eLinkedComponentAppearance::Reference )
    {
      // The goal of the next if/else clause is for Rhino users
      // to see what they saw when they created the file.
      if ( binary_archive.Archive3dmVersion() < 50 )
      {
        // V4 linked blocks and early V5 linked blocks treated
        // layers and materials the way newer "active" idefs work,
        // so when I read an archive with version < 50, the
        // default will be 1 for "active".  
        SetLinkedComponentAppearance(ON_InstanceDefinition::eLinkedComponentAppearance::Active);
      }
      else
      {
        // The more recent V5 linked blocks treated layers and materials
        // the way "reference" style idefs work, so when I read an
        // archive with version >= 50 (meaning recent V5), the default
        // will be 2 for "reference".
        SetLinkedComponentAppearance(ON_InstanceDefinition::eLinkedComponentAppearance::Reference);
      }
    }
  }
  else
  {
    SetLinkedComponentAppearance(ON_InstanceDefinition::eLinkedComponentAppearance::Unset);
  }

  return rc;
}

bool ON_InstanceDefinition::Internal_WriteV6(
  ON_BinaryArchive& archive
) const
{
  const int major_version = 1;
  const int minor_version = 0;
  if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, major_version, minor_version))
    return false;

  bool rc = false;
  for (;;)
  {
    const unsigned int attributes_filter
      = ON_ModelComponent::Attributes::IndexAttribute
      | ON_ModelComponent::Attributes::IdAttribute
      | ON_ModelComponent::Attributes::NameAttribute;
    if (!archive.WriteModelComponentAttributes(*this, attributes_filter))
      break;

    if (!archive.WriteInt(static_cast<unsigned int>(InstanceDefinitionType())))
      break;

    if (!m_us.Write(archive))
      break;

    if (!archive.WriteString(m_description))
      break;
    if (!archive.WriteString(m_url))
      break;
    if (!archive.WriteString(m_url_tag))
      break;
    if (!archive.WriteBoundingBox(m_bbox))
      break;


    const bool bWriteInstanceGeometryIdList = (ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked != InstanceDefinitionType());
    if (!archive.WriteBool(bWriteInstanceGeometryIdList))
      break;
    if (bWriteInstanceGeometryIdList)
    {
      if (!archive.WriteArray(m_object_uuid))
        break;
    }
 
    const bool bIsLinkedType = IsLinkedType();
    if (!archive.WriteBool(bIsLinkedType))
      break;
    if (bIsLinkedType)
    {
      const int linked_type_major_version = 1;
      const int linked_type_minor_version = 0;
      if (!archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK, linked_type_major_version, linked_type_minor_version))
        break;

      bool bLinkedType_rc = false;
      for (;;)
      {
        if (!m_linked_file_reference.Write(true, archive))
          break;

        int idef_update_depth = m_bSkipNestedLinkedDefinitions ? 1 : 0;
        if (!archive.WriteInt(idef_update_depth))
          break;

        if (!archive.WriteInt(static_cast<unsigned int>(LinkedComponentAppearance())))
          break;

        const ON_ReferencedComponentSettings* reference_component_settings = LinkedIdefReferenceComponentSettings();
        const bool bHasLinkedIdefReferenceComponentSettings
          = ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked == InstanceDefinitionType()
          && ON_InstanceDefinition::eLinkedComponentAppearance::Reference == LinkedComponentAppearance()
          && HasLinkedIdefReferenceComponentSettings()
          && (nullptr != reference_component_settings)
          && reference_component_settings->IsNotEmpty()
          ;

        if (!archive.WriteBool(bHasLinkedIdefReferenceComponentSettings))
          break;

        if (bHasLinkedIdefReferenceComponentSettings)
        {
          if (!reference_component_settings->Write(archive))
            break;
        }
        
        bLinkedType_rc = true;
        break;
      }
      if (!archive.EndWrite3dmChunk())
        bLinkedType_rc = false;
      if (!bLinkedType_rc)
        break;
    }

    rc = true;
    break;
  }

  if (!archive.EndWrite3dmChunk())
    rc = false;

  return rc;
}

bool ON_InstanceDefinition::Internal_ReadV6(
  ON_BinaryArchive& archive
)
{
  *this = ON_InstanceDefinition::Unset;
  Internal_ContentChanged();

  int major_version = 0;
  int minor_version = 0;
  if (!archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK, &major_version, &minor_version))
    return false;

  bool rc = false;
  for (;;)
  {
    if (1 != major_version)
      break;

    {
      unsigned int attributes_filter = 0;
      if (!archive.ReadModelComponentAttributes(*this, &attributes_filter))
        break;
    }

    {
      unsigned int idef_type_as_unsigned = 0;
      if (!archive.ReadInt(&idef_type_as_unsigned))
        break;
      m_idef_update_type = ON_InstanceDefinition::InstanceDefinitionTypeFromUnsigned(idef_type_as_unsigned);
    }

    if (!m_us.Read(archive))
      break;

    if (!archive.ReadString(m_description))
      break;
    if (!archive.ReadString(m_url))
      break;
    if (!archive.ReadString(m_url_tag))
      break;
    if (!archive.ReadBoundingBox(m_bbox))
      break;

    bool bReadInstanceGeometryIdList = false;
    if (!archive.ReadBool(&bReadInstanceGeometryIdList))
      break;
    if (bReadInstanceGeometryIdList)
    {
      if (!archive.ReadArray(m_object_uuid))
        break;
    }
 
    bool bIsLinkedType = false;
    if (!archive.ReadBool(&bIsLinkedType))
      break;
    if (bIsLinkedType)
    {
      int linked_type_major_version = 0;
      int linked_type_minor_version = 0;
      if (!archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK, &linked_type_major_version, &linked_type_minor_version))
        break;

      bool bLinkedType_rc = false;
      for (;;)
      {
        if (1 != linked_type_major_version)
          break;
        if (!m_linked_file_reference.Read(archive))
          break;

        int idef_update_depth = m_bSkipNestedLinkedDefinitions ? 1 : 0;
        if (!archive.ReadInt(&idef_update_depth))
          break;
        m_bSkipNestedLinkedDefinitions= (1 == idef_update_depth);
        

        unsigned int linked_component_appearance_as_unsigned = 0;
        if (!archive.ReadInt(&linked_component_appearance_as_unsigned))
          break;
        m_linked_component_appearance = ON_InstanceDefinition::LinkedComponentAppearanceFromUnsigned(linked_component_appearance_as_unsigned);

        bool bHasLinkedIdefReferenceComponentSettings = false;
        if (!archive.ReadBool(&bHasLinkedIdefReferenceComponentSettings))
          break;

        if (bHasLinkedIdefReferenceComponentSettings)
        {
          m_linked_idef_component_settings = new ON_ReferencedComponentSettings();
          if (
            false == m_linked_idef_component_settings->Read(archive)
            || ON_InstanceDefinition::IDEF_UPDATE_TYPE::Linked != this->m_idef_update_type
            || ON_InstanceDefinition::eLinkedComponentAppearance::Reference != this->m_linked_component_appearance
            )
          {
            // Read failed or earlier bugs in Rhino and opennurbs saved
            // unneeded m_linked_idef_component_settings.
            delete m_linked_idef_component_settings;
            m_linked_idef_component_settings = nullptr;
            break;
          }
        }

        if (ON_InstanceDefinition::IDEF_UPDATE_TYPE::LinkedAndEmbedded == this->m_idef_update_type
          && m_linked_file_reference.FullPath().IsEmpty()
          && m_linked_file_reference.RelativePath().IsEmpty()
          && archive.ArchiveOpenNURBSVersion() <= ON_VersionNumberConstruct(6, 0, 2016, 9, 27, 0)
          )
        {
          // bug in Rhino WIP failed to set path. Best we can do is convert to a static idef.
          m_idef_update_type = ON_InstanceDefinition::IDEF_UPDATE_TYPE::Static;
        }
        
        bLinkedType_rc = true;
        break;
      }
      if (!archive.EndRead3dmChunk())
        bLinkedType_rc = false;
      if (!bLinkedType_rc)
        break;
    }

    rc = true;
    break;
  }

  if (!archive.EndRead3dmChunk())
    rc = false;

  return rc;
}
