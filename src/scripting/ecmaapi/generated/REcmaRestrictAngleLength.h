// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMARESTRICTANGLELENGTH_H
        #define RECMARESTRICTANGLELENGTH_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "REcmaShellRestrictAngleLength.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaRestrictAngleLength {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue createEcma(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getRSnapRestriction(QScriptContext *context,
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
        restrictSnap
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setBaseAngle
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setAngle
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setBaseLength
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setLength
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setRestrictAngle
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setRestrictLength
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setRepeatAngle
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setRepeatLength
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RRestrictAngleLength* getSelf(const QString& fName, QScriptContext* context)
    ;static REcmaShellRestrictAngleLength* getSelfShell(const QString& fName, QScriptContext* context)
    ;static  QScriptValue toScriptValueEnumAngleLengthMode(QScriptEngine* engine, const RRestrictAngleLength::AngleLengthMode& value)
    ;static  void fromScriptValueEnumAngleLengthMode(const QScriptValue& value, RRestrictAngleLength::AngleLengthMode& out)
    ;};
    #endif
    