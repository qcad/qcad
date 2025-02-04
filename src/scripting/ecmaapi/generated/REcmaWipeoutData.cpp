// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is copyable.
        
        #include "REcmaWipeoutData.h"
        #include "RMetaTypes.h"
        #include "../REcmaHelper.h"

        // forwards declarations mapped to includes
        
                #include "RBox.h"
            
                #include "RDocument.h"
            
                #include "RPolyline.h"
            
                #include "RPolylineData.h"
            
                #include "RRefPoint.h"
            
                #include "RVector.h"
            
                #include "RWipeoutData.h"
            
                #include "RWipeoutEntity.h"
            
            
        // includes for base ecma wrapper classes
        
                  #include "REcmaPolylineData.h"
                 void REcmaWipeoutData::initEcma(QScriptEngine& engine, QScriptValue* proto 
    
    ) 
    
    {

    bool protoCreated = false;
    if(proto == NULL){
        proto = new QScriptValue(engine.newVariant(qVariantFromValue(
                (RWipeoutData*) 0)));
        protoCreated = true;
    }

    
        // primary base class RPolylineData:
        
            QScriptValue dpt = engine.defaultPrototype(
                qMetaTypeId<RPolylineData*>());

            if (dpt.isValid()) {
                proto->setPrototype(dpt);
            }
          
        /*
        
        */
    

    QScriptValue fun;

    // toString:
    REcmaHelper::registerFunction(&engine, proto, toString, "toString");
    
    // copy:
    REcmaHelper::registerFunction(&engine, proto, copy, "copy");
    

    // destroy:
    REcmaHelper::registerFunction(&engine, proto, destroy, "destroy");
    
        // conversion for base class RPolylineData
        REcmaHelper::registerFunction(&engine, proto, getRPolylineData, "getRPolylineData");
        
        // conversion for base class REntityData
        REcmaHelper::registerFunction(&engine, proto, getREntityData, "getREntityData");
        
        // conversion for base class RPolyline
        REcmaHelper::registerFunction(&engine, proto, getRPolyline, "getRPolyline");
        
        // conversion for base class RShape
        REcmaHelper::registerFunction(&engine, proto, getRShape, "getRShape");
        
        // conversion for base class RExplodable
        REcmaHelper::registerFunction(&engine, proto, getRExplodable, "getRExplodable");
        

    // get class name
    REcmaHelper::registerFunction(&engine, proto, getClassName, "getClassName");
    

    // conversion to all base classes (multiple inheritance):
    REcmaHelper::registerFunction(&engine, proto, getBaseClasses, "getBaseClasses");
    

    // properties:
    

    // methods:
    
            REcmaHelper::registerFunction(&engine, proto, getType, "getType");
            
            REcmaHelper::registerFunction(&engine, proto, getBoundingBoxes, "getBoundingBoxes");
            
            REcmaHelper::registerFunction(&engine, proto, getReferencePoints, "getReferencePoints");
            
            REcmaHelper::registerFunction(&engine, proto, moveReferencePoint, "moveReferencePoint");
            
            REcmaHelper::registerFunction(&engine, proto, getDistanceTo, "getDistanceTo");
            
            REcmaHelper::registerFunction(&engine, proto, getShowFrame, "getShowFrame");
            
            REcmaHelper::registerFunction(&engine, proto, setShowFrame, "setShowFrame");
            
            REcmaHelper::registerFunction(&engine, proto, getBoundary, "getBoundary");
            
        engine.setDefaultPrototype(
            qMetaTypeId<RWipeoutData*>(), *proto);

        
                engine.setDefaultPrototype(qMetaTypeId<
                RWipeoutData
                > (), *proto);
            
    

    QScriptValue ctor = engine.newFunction(createEcma, *proto, 2);
    
    // static methods:
    

    // static properties:
    

    // enum values:
    

    // enum conversions:
    
        
    // init class:
    engine.globalObject().setProperty("RWipeoutData",
    ctor, QScriptValue::SkipInEnumeration);
    
    if( protoCreated ){
       delete proto;
    }
    
    }
     QScriptValue REcmaWipeoutData::createEcma(QScriptContext* context, QScriptEngine* engine) 
    
    {
    if (context->thisObject().strictlyEquals(
       engine->globalObject())) {
       return REcmaHelper::throwError(
       QString::fromLatin1("RWipeoutData(): Did you forget to construct with 'new'?"),
           context);
    }

    QScriptValue result;
        
            // generate constructor variants:
            
    if( context->argumentCount() ==
        0
    ){
    // prepare arguments:
    
    // end of arguments

    // call C++ constructor:
    
            // copyable class:
            RWipeoutData
                    cppResult;
                
            result = engine->newVariant(
            context->thisObject(), qVariantFromValue(cppResult));
        
    } else 

    if( context->argumentCount() ==
        1
                && (
                
                        context->argument(
                        0
                        ).isVariant()
                        ||
                    
                        context->argument(
                        0
                        ).isQObject()
                        ||
                    
                        context->argument(
                        0
                        ).isNull()
                ) /* type: RPolyline */
            
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RPolyline*
                    ap0 =
                    qscriptvalue_cast<
                    RPolyline*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RWipeoutData: Argument 0 is not of type RPolyline.",
                               context);                    
                    }
                    RPolyline 
                    a0 = 
                    *ap0;
                
    // end of arguments

    // call C++ constructor:
    
            // copyable class:
            RWipeoutData
                    cppResult(
                    a0
                    );
                
            result = engine->newVariant(
            context->thisObject(), qVariantFromValue(cppResult));
        
    } else 

    {
       return REcmaHelper::throwError(
       QString::fromLatin1("RWipeoutData(): no matching constructor found."),
           context);
    }
    
    return result;
    }
    

    // conversion functions for base classes:
     QScriptValue REcmaWipeoutData::getRPolylineData(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                RPolylineData* cppResult =
                    qscriptvalue_cast<RWipeoutData*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
             QScriptValue REcmaWipeoutData::getREntityData(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                REntityData* cppResult =
                    qscriptvalue_cast<RWipeoutData*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
             QScriptValue REcmaWipeoutData::getRPolyline(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                RPolyline* cppResult =
                    qscriptvalue_cast<RWipeoutData*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
             QScriptValue REcmaWipeoutData::getRShape(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                RShape* cppResult =
                    qscriptvalue_cast<RWipeoutData*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
             QScriptValue REcmaWipeoutData::getRExplodable(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                RExplodable* cppResult =
                    qscriptvalue_cast<RWipeoutData*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
            

    // returns class name:
     QScriptValue REcmaWipeoutData::getClassName(QScriptContext *context, QScriptEngine *engine) 
        
    {
        return qScriptValueFromValue(engine, QString("RWipeoutData"));
    }
    

    // returns all base classes (in case of multiple inheritance):
     QScriptValue REcmaWipeoutData::getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        
    {
        QStringList list;
        
        list.append("RPolylineData");
    
        list.append("REntityData");
    
        list.append("RPolyline");
    
        list.append("RShape");
    
        list.append("RExplodable");
    

        return qScriptValueFromSequence(engine, list);
    }
    

    // properties:
    

    // public methods:
     QScriptValue
        REcmaWipeoutData::getType
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaWipeoutData::getType", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaWipeoutData::getType";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RWipeoutData* self = 
                        getSelf("getType", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    0
    ){
    // prepare arguments:
    
    // end of arguments

    // call C++ function:
    // return type 'RS::EntityType'
    RS::EntityType cppResult =
        
               self->getType();
        // return type: RS::EntityType
                // standard Type
                result = QScriptValue(cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RWipeoutData.getType().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaWipeoutData::getType", context, engine);
            return result;
        }
         QScriptValue
        REcmaWipeoutData::getBoundingBoxes
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaWipeoutData::getBoundingBoxes", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaWipeoutData::getBoundingBoxes";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RWipeoutData* self = 
                        getSelf("getBoundingBoxes", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isBool()
        ) /* type: bool */
    
    ){
    // prepare arguments:
    
                    // argument isStandardType
                    bool
                    a0 =
                    (bool)
                    
                    context->argument( 0 ).
                    toBool();
                
    // end of arguments

    // call C++ function:
    // return type 'QList < RBox >'
    QList < RBox > cppResult =
        
               self->getBoundingBoxes(a0);
        // return type: QList < RBox >
                // List of ...:
                result = REcmaHelper::listToScriptValue(engine, cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RWipeoutData.getBoundingBoxes().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaWipeoutData::getBoundingBoxes", context, engine);
            return result;
        }
         QScriptValue
        REcmaWipeoutData::getReferencePoints
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaWipeoutData::getReferencePoints", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaWipeoutData::getReferencePoints";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RWipeoutData* self = 
                        getSelf("getReferencePoints", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    0
    ){
    // prepare arguments:
    
    // end of arguments

    // call C++ function:
    // return type 'QList < RRefPoint >'
    QList < RRefPoint > cppResult =
        
               self->getReferencePoints();
        // return type: QList < RRefPoint >
                // List of ...:
                result = REcmaHelper::listToScriptValue(engine, cppResult);
            
    } else


        
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isNumber()
        ) /* type: RS::ProjectionRenderingHint */
    
    ){
    // prepare arguments:
    
                    // argument isStandardType
                    RS::ProjectionRenderingHint
                    a0 =
                    (RS::ProjectionRenderingHint)
                    (int)
                    context->argument( 0 ).
                    toNumber();
                
    // end of arguments

    // call C++ function:
    // return type 'QList < RRefPoint >'
    QList < RRefPoint > cppResult =
        
               self->getReferencePoints(a0);
        // return type: QList < RRefPoint >
                // List of ...:
                result = REcmaHelper::listToScriptValue(engine, cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RWipeoutData.getReferencePoints().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaWipeoutData::getReferencePoints", context, engine);
            return result;
        }
         QScriptValue
        REcmaWipeoutData::moveReferencePoint
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaWipeoutData::moveReferencePoint", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaWipeoutData::moveReferencePoint";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RWipeoutData* self = 
                        getSelf("moveReferencePoint", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    3 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RVector */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: RVector */
     && (
            context->argument(2).isNumber()
        ) /* type: Qt::KeyboardModifiers */
    
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap0 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RWipeoutData: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap1 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        1
                        )
                    );
                    if (ap1 == NULL) {
                           return REcmaHelper::throwError("RWipeoutData: Argument 1 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a1 = 
                    *ap1;
                
                    // argument isStandardType
                    Qt::KeyboardModifiers
                    a2 =
                    (Qt::KeyboardModifiers)
                    (int)
                    context->argument( 2 ).
                    toNumber();
                
    // end of arguments

    // call C++ function:
    // return type 'bool'
    bool cppResult =
        
               self->moveReferencePoint(a0
        ,
    a1
        ,
    a2);
        // return type: bool
                // standard Type
                result = QScriptValue(cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RWipeoutData.moveReferencePoint().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaWipeoutData::moveReferencePoint", context, engine);
            return result;
        }
         QScriptValue
        REcmaWipeoutData::getDistanceTo
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaWipeoutData::getDistanceTo", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaWipeoutData::getDistanceTo";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RWipeoutData* self = 
                        getSelf("getDistanceTo", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RVector */
    
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap0 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RWipeoutData: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
    // end of arguments

    // call C++ function:
    // return type 'double'
    double cppResult =
        
               self->getDistanceTo(a0);
        // return type: double
                // standard Type
                result = QScriptValue(cppResult);
            
    } else


        
    
    if( context->argumentCount() ==
    2 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RVector */
     && (
            context->argument(1).isBool()
        ) /* type: bool */
    
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap0 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RWipeoutData: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
                    // argument isStandardType
                    bool
                    a1 =
                    (bool)
                    
                    context->argument( 1 ).
                    toBool();
                
    // end of arguments

    // call C++ function:
    // return type 'double'
    double cppResult =
        
               self->getDistanceTo(a0
        ,
    a1);
        // return type: double
                // standard Type
                result = QScriptValue(cppResult);
            
    } else


        
    
    if( context->argumentCount() ==
    3 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RVector */
     && (
            context->argument(1).isBool()
        ) /* type: bool */
     && (
            context->argument(2).isNumber()
        ) /* type: double */
    
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap0 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RWipeoutData: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
                    // argument isStandardType
                    bool
                    a1 =
                    (bool)
                    
                    context->argument( 1 ).
                    toBool();
                
                    // argument isStandardType
                    double
                    a2 =
                    (double)
                    
                    context->argument( 2 ).
                    toNumber();
                
    // end of arguments

    // call C++ function:
    // return type 'double'
    double cppResult =
        
               self->getDistanceTo(a0
        ,
    a1
        ,
    a2);
        // return type: double
                // standard Type
                result = QScriptValue(cppResult);
            
    } else


        
    
    if( context->argumentCount() ==
    4 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RVector */
     && (
            context->argument(1).isBool()
        ) /* type: bool */
     && (
            context->argument(2).isNumber()
        ) /* type: double */
     && (
            context->argument(3).isBool()
        ) /* type: bool */
    
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap0 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RWipeoutData: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
                    // argument isStandardType
                    bool
                    a1 =
                    (bool)
                    
                    context->argument( 1 ).
                    toBool();
                
                    // argument isStandardType
                    double
                    a2 =
                    (double)
                    
                    context->argument( 2 ).
                    toNumber();
                
                    // argument isStandardType
                    bool
                    a3 =
                    (bool)
                    
                    context->argument( 3 ).
                    toBool();
                
    // end of arguments

    // call C++ function:
    // return type 'double'
    double cppResult =
        
               self->getDistanceTo(a0
        ,
    a1
        ,
    a2
        ,
    a3);
        // return type: double
                // standard Type
                result = QScriptValue(cppResult);
            
    } else


        
    
    if( context->argumentCount() ==
    5 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RVector */
     && (
            context->argument(1).isBool()
        ) /* type: bool */
     && (
            context->argument(2).isNumber()
        ) /* type: double */
     && (
            context->argument(3).isBool()
        ) /* type: bool */
     && (
            context->argument(4).isNumber()
        ) /* type: double */
    
    ){
    // prepare arguments:
    
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap0 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if (ap0 == NULL) {
                           return REcmaHelper::throwError("RWipeoutData: Argument 0 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a0 = 
                    *ap0;
                
                    // argument isStandardType
                    bool
                    a1 =
                    (bool)
                    
                    context->argument( 1 ).
                    toBool();
                
                    // argument isStandardType
                    double
                    a2 =
                    (double)
                    
                    context->argument( 2 ).
                    toNumber();
                
                    // argument isStandardType
                    bool
                    a3 =
                    (bool)
                    
                    context->argument( 3 ).
                    toBool();
                
                    // argument isStandardType
                    double
                    a4 =
                    (double)
                    
                    context->argument( 4 ).
                    toNumber();
                
    // end of arguments

    // call C++ function:
    // return type 'double'
    double cppResult =
        
               self->getDistanceTo(a0
        ,
    a1
        ,
    a2
        ,
    a3
        ,
    a4);
        // return type: double
                // standard Type
                result = QScriptValue(cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RWipeoutData.getDistanceTo().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaWipeoutData::getDistanceTo", context, engine);
            return result;
        }
         QScriptValue
        REcmaWipeoutData::getShowFrame
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaWipeoutData::getShowFrame", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaWipeoutData::getShowFrame";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RWipeoutData* self = 
                        getSelf("getShowFrame", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    0
    ){
    // prepare arguments:
    
    // end of arguments

    // call C++ function:
    // return type 'bool'
    bool cppResult =
        
               self->getShowFrame();
        // return type: bool
                // standard Type
                result = QScriptValue(cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RWipeoutData.getShowFrame().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaWipeoutData::getShowFrame", context, engine);
            return result;
        }
         QScriptValue
        REcmaWipeoutData::setShowFrame
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaWipeoutData::setShowFrame", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaWipeoutData::setShowFrame";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RWipeoutData* self = 
                        getSelf("setShowFrame", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isBool()
        ) /* type: bool */
    
    ){
    // prepare arguments:
    
                    // argument isStandardType
                    bool
                    a0 =
                    (bool)
                    
                    context->argument( 0 ).
                    toBool();
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->setShowFrame(a0);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RWipeoutData.setShowFrame().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaWipeoutData::setShowFrame", context, engine);
            return result;
        }
         QScriptValue
        REcmaWipeoutData::getBoundary
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaWipeoutData::getBoundary", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaWipeoutData::getBoundary";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RWipeoutData* self = 
                        getSelf("getBoundary", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    0
    ){
    // prepare arguments:
    
    // end of arguments

    // call C++ function:
    // return type 'RPolyline'
    RPolyline cppResult =
        
               self->getBoundary();
        // return type: RPolyline
                // not standard type nor reference
                result = qScriptValueFromValue(engine, cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RWipeoutData.getBoundary().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaWipeoutData::getBoundary", context, engine);
            return result;
        }
         QScriptValue REcmaWipeoutData::toString
    (QScriptContext *context, QScriptEngine *engine)
    
    {

    RWipeoutData* self = getSelf("toString", context);
    
    QString result;
    
            result = QString("RWipeoutData(0x%1)").arg((unsigned long int)self, 0, 16);
        
    return QScriptValue(result);
    }
     QScriptValue REcmaWipeoutData::copy
    (QScriptContext *context, QScriptEngine *engine)
    
    {
        RWipeoutData cp = qscriptvalue_cast<RWipeoutData>(context->thisObject());
        return qScriptValueFromValue(engine, cp);
    }
     QScriptValue REcmaWipeoutData::destroy(QScriptContext *context, QScriptEngine *engine)
    
    {

        RWipeoutData* self = getSelf("RWipeoutData", context);
        //Q_ASSERT(self!=NULL);
        if (self==NULL) {
            return REcmaHelper::throwError("self is NULL", context);
        }
        
    
        delete self;
        context->thisObject().setData(engine->nullValue());
        context->thisObject().prototype().setData(engine->nullValue());
        context->thisObject().setPrototype(engine->nullValue());
        context->thisObject().setScriptClass(NULL);
        return engine->undefinedValue();
    }
    RWipeoutData* REcmaWipeoutData::getSelf(const QString& fName, QScriptContext* context)
    
        {
            RWipeoutData* self = NULL;

            
                // self could be a normal object (e.g. from an UI file) or
                // an ECMA shell object (made from an ECMA script):
                //self = getSelfShell(fName, context);
                

            //if (self==NULL) {
                self = REcmaHelper::scriptValueTo<RWipeoutData >(context->thisObject())
                
                ;
            //}

            if (self == NULL){
                // avoid recursion (toString is used by the backtrace):
                if (fName!="toString") {
                    REcmaHelper::throwError(QString("RWipeoutData.%1(): "
                        "This object is not a RWipeoutData").arg(fName),
                        context);
                }
                return NULL;
            }

            return self;
        }
        RWipeoutData* REcmaWipeoutData::getSelfShell(const QString& fName, QScriptContext* context)
    
        {
          RWipeoutData* selfBase = getSelf(fName, context);
                RWipeoutData* self = dynamic_cast<RWipeoutData*>(selfBase);
                //return REcmaHelper::scriptValueTo<RWipeoutData >(context->thisObject());
            if(self == NULL){
                REcmaHelper::throwError(QString("RWipeoutData.%1(): "
                    "This object is not a RWipeoutData").arg(fName),
                    context);
            }

            return self;
            


        }
        