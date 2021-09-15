


	// ***** AUTOGENERATED CODE, DO NOT EDIT *****
    
        #ifndef RECMASHELLPROPERTYEDITOR_H
        #define RECMASHELLPROPERTYEDITOR_H

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RPropertyEditor.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class REcmaShellPropertyEditor : public RPropertyEditor {

        public:
      
    // Destructor:
    
            ~REcmaShellPropertyEditor();
        static RPropertyEditor* getSelf(const QString& fName, QScriptContext* context)
    ;static REcmaShellPropertyEditor* getSelfShell(const QString& fName, QScriptContext* context)
    ;
    
    
    
    // Constructors:
    
      REcmaShellPropertyEditor(
                
            );
        
    
    
      RPropertyEditor * getInstance(
                
            );
        
    
    
      void updateFromDocument(
                RDocument * document, bool onlyChanges, RS::EntityType filter
        = RS :: EntityUnknown, bool manual
        = false, bool showOnRequest
        = false
            );
        
    
    
      void updateFromObject(
                RObject * object, RDocument * document
        = NULL
            );
        
    
    
      void clearEditor(
                
            );
        
    
    
      QStringList getFixedCustomPropertyNames(
                const QList < RS::EntityType > & objectTypes
            );
        
    
    
      void updateLayers(
                RDocumentInterface * documentInterface, QList < RLayer::Id > & layerIds
            );
        
      void updateLayers(
                RDocumentInterface * documentInterface
            );
        
    
    
      void setCurrentLayer(
                RDocumentInterface * documentInterface, RLayer::Id previousLayerId
            );
        
    
    
      void clearLayers(
                
            );
        
    
    
      void propertyChanged(
                RPropertyTypeId propertyTypeId, QVariant propertyValue, QVariant::Type typeHint
        = QVariant :: Invalid
            );
        
    
    
      void listPropertyChanged(
                RPropertyTypeId propertyTypeId, int index, QVariant propertyValue
            );
        
    
    
      QStringList getGroupTitles(
                
            );
        
    
    
      QStringList getPropertyTitles(
                const QString & group
            );
        
    
    
      QVariant getPropertyValue(
                const RPropertyTypeId & propertyTypeId
            );
        
      QVariant getPropertyValue(
                const QString & group, const QString & title
            );
        
    
    
      RPropertyAttributes getPropertyAttributes(
                const RPropertyTypeId & propertyTypeId
            );
        
      RPropertyAttributes getPropertyAttributes(
                const QString & group, const QString & title
            );
        
    
    
      RPropertyAttributes getCustomPropertyAttributes(
                const QString & group, const QString & title
            );
        
    
    
      QList < RS::EntityType > getTypes(
                
            );
        
    
    
      int getTypeCount(
                RS::EntityType type
            );
        
    
    
      void setEntityTypeFilter(
                RS::EntityType type
            );
        
    
    
      RS::EntityType getEntityTypeFilter(
                
            );
        
    
    
      bool checkType(
                RS::EntityType type, RS::EntityType filter
            );
        
    
    
      void updateGui(
                bool onlyChanges
        = false
            );
        
    
    
      void updateProperty(
                const RPropertyTypeId & propertyTypeId, RObject & object, RDocument * document, bool showOnRequest
        = false
            );
        
    
    
      void computePropertyValue(
                RProperty & property
            );
        
    
  
        // methods of 1st level base class RPropertyListener:
        
        // methods of 1st level base class RLayerListener:
        

    // protected methods (only available for ECMA shell classes) (generated by xsl2xpp.xsl):
	static  QScriptValue
        updateGui
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        updateProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        computePropertyValue
        (QScriptContext* context, QScriptEngine* engine) 
        ;QScriptValue __qtscript_self;
            };
            Q_DECLARE_METATYPE(REcmaShellPropertyEditor*)
        
	#endif
    