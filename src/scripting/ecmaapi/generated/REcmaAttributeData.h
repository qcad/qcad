// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is copyable.
        
        #ifndef RECMAATTRIBUTEDATA_H
        #define RECMAATTRIBUTEDATA_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RAttributeData.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaAttributeData {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue createEcma(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getRTextBasedData(QScriptContext *context,
            QScriptEngine *engine)
        ;static  QScriptValue getREntityData(QScriptContext *context,
            QScriptEngine *engine)
        ;static  QScriptValue getRPainterPathSource(QScriptContext *context,
            QScriptEngine *engine)
        ;

    // returns class name:
    static  QScriptValue getClassName(QScriptContext *context, QScriptEngine *engine) 
        ;

    // returns all base classes (in case of multiple inheritance):
    static  QScriptValue getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        ;

    // properties:
    

    // public methods:
    static  QScriptValue
        getType
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getRenderedText
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getTag
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setTag
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        isInvisible
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setInvisible
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getLinetypeId
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getLineweight
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getColor
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getReferencePoints
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue copy
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RAttributeData* getSelf(const QString& fName, QScriptContext* context)
    ;static RAttributeData* getSelfShell(const QString& fName, QScriptContext* context)
    ;};
    #endif
    