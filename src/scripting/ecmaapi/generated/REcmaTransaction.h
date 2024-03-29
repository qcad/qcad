// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is copyable.
        
        #ifndef RECMATRANSACTION_H
        #define RECMATRANSACTION_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RTransaction.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaTransaction {

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
        setRecordAffectedObjects
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setAllowAll
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setAllowInvisible
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setSpatialIndexDisabled
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setExistingBlockDetectionDisabled
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setExistingLayerDetectionDisabled
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setExistingLinetypeDetectionDisabled
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setBlockRecursionDetectionDisabled
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setKeepHandles
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setKeepChildren
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isUndoing
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isRedoing
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isUndoable
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isFailed
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        redo
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        undo
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        end
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        updateAffectedBlockReferences
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setId
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getId
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setGroup
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getGroup
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getText
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        overwriteBlock
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addObject
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addAffectedObject
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        addAffectedObjects
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        deleteObject
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getAffectedObjects
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getStatusChanges
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        hasStatusChange
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getPropertyChanges
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getNewObjectId
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        hasOnlyChanges
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        fail
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        endCycle
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isPreview
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setTypes
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getTypes
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setType
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isType
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue copy
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RTransaction* getSelf(const QString& fName, QScriptContext* context)
    ;static RTransaction* getSelfShell(const QString& fName, QScriptContext* context)
    ;static  QScriptValue toScriptValueEnumType(QScriptEngine* engine, const RTransaction::Type& value)
    ;static  void fromScriptValueEnumType(const QScriptValue& value, RTransaction::Type& out)
    ;};
    #endif
    