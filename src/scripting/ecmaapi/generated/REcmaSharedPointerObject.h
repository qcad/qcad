// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMASHAREDPOINTEROBJECT_H
        #define RECMASHAREDPOINTEROBJECT_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RObject.h"
            
            typedef QSharedPointer<RObject> RObjectPointer;
        

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaSharedPointerObject {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue createEcma(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    

    // returns class name:
    static  QScriptValue getClassName(QScriptContext *context, QScriptEngine *engine) 
        ;

    // returns all base classes (in case of multiple inheritance):
    static  QScriptValue getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        ;

    // properties:
    

    // public methods:
    static  QScriptValue
        init
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getRtti
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isOfType
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getType
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        clone
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        mustAlwaysClone
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getDocument
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setDocument
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setFlag
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getFlag
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getId
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getHandle
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isProtected
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setProtected
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isInvisible
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setInvisible
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isSelected
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setSelected
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isUndone
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isWorkingSet
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setWorkingSet
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPropertyTypeIds
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getCustomPropertyTypeIds
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        hasPropertyType
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        hasCustomProperties
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        hasCustomProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getCustomProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getCustomDoubleProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getCustomIntProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getCustomBoolProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setCustomProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        removeCustomProperty
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getCustomPropertyTitles
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getCustomPropertyKeys
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        copyCustomPropertiesFrom
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setCustomPropertyAttributes
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getCustomPropertyAttributes
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getComplexity
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setAutoUpdatesBlocked
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        dump
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        validate
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RObject* getSelf(const QString& fName, QScriptContext* context)
    ;static RObject* getSelfShell(const QString& fName, QScriptContext* context)
    ;static  QScriptValue data
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue isNull
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue toScriptValueEnumXYZ(QScriptEngine* engine, const RObject::XYZ& value)
    ;static  void fromScriptValueEnumXYZ(const QScriptValue& value, RObject::XYZ& out)
    ;static  QScriptValue toScriptValueEnumObjectFlag(QScriptEngine* engine, const RObject::ObjectFlag& value)
    ;static  void fromScriptValueEnumObjectFlag(const QScriptValue& value, RObject::ObjectFlag& out)
    ;};
    #endif
    