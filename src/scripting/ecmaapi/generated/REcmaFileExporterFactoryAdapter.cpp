// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #include "REcmaFileExporterFactoryAdapter.h"
        #include "RMetaTypes.h"
        #include "../REcmaHelper.h"

        // forwards declarations mapped to includes
        
                #include "RDocument.h"
            
                #include "RMessageHandler.h"
            
                #include "RProgressHandler.h"
            
            
        // includes for base ecma wrapper classes
        
                  #include "REcmaFileExporterFactory.h"
                 void REcmaFileExporterFactoryAdapter::initEcma(QScriptEngine& engine, QScriptValue* proto 
    
    ) 
    
    {

    bool protoCreated = false;
    if(proto == NULL){
        proto = new QScriptValue(engine.newVariant(qVariantFromValue(
                (RFileExporterFactoryAdapter*) 0)));
        protoCreated = true;
    }

    
        // primary base class RFileExporterFactory:
        
            QScriptValue dpt = engine.defaultPrototype(
                qMetaTypeId<RFileExporterFactory*>());

            if (dpt.isValid()) {
                proto->setPrototype(dpt);
            }
          
        /*
        
        */
    

    QScriptValue fun;

    // toString:
    REcmaHelper::registerFunction(&engine, proto, toString, "toString");
    

    // destroy:
    REcmaHelper::registerFunction(&engine, proto, destroy, "destroy");
    
        // conversion for base class RFileExporterFactory
        REcmaHelper::registerFunction(&engine, proto, getRFileExporterFactory, "getRFileExporterFactory");
        

    // get class name
    REcmaHelper::registerFunction(&engine, proto, getClassName, "getClassName");
    

    // conversion to all base classes (multiple inheritance):
    REcmaHelper::registerFunction(&engine, proto, getBaseClasses, "getBaseClasses");
    

    // properties:
    

    // methods:
    
            REcmaHelper::registerFunction(&engine, proto, getFilterStrings, "getFilterStrings");
            
            REcmaHelper::registerFunction(&engine, proto, canExport, "canExport");
            
            REcmaHelper::registerFunction(&engine, proto, instantiate, "instantiate");
            
        engine.setDefaultPrototype(
            qMetaTypeId<RFileExporterFactoryAdapter*>(), *proto);

        
    

    QScriptValue ctor = engine.newFunction(createEcma, *proto, 2);
    
    // static methods:
    

    // static properties:
    

    // enum values:
    

    // enum conversions:
    
        
    // init class:
    engine.globalObject().setProperty("RFileExporterFactoryAdapter",
    ctor, QScriptValue::SkipInEnumeration);
    
    if( protoCreated ){
       delete proto;
    }
    
    }
     QScriptValue REcmaFileExporterFactoryAdapter::createEcma(QScriptContext* context, QScriptEngine* engine) 
    
    {
    if (context->thisObject().strictlyEquals(
       engine->globalObject())) {
       return REcmaHelper::throwError(
       QString::fromLatin1("RFileExporterFactoryAdapter(): Did you forget to construct with 'new'?"),
           context);
    }

    QScriptValue result;
    
            // constructor without variants:
            
    if( context->argumentCount() ==
        0
    ){
    // prepare arguments:
    
    // end of arguments

    // call C++ constructor:
    
            // non-copyable class:
            REcmaShellFileExporterFactoryAdapter
                    * cppResult =
                    new
                    REcmaShellFileExporterFactoryAdapter
                    ();
                
                    // TODO: triggers: Warning: QScriptEngine::newVariant(): changing class of non-QScriptObject not supported:
                    result = engine->newVariant(context->thisObject(), qVariantFromValue(cppResult));
                
        cppResult->__qtscript_self = result;
    
    } else 

    {
       return REcmaHelper::throwError(
       QString::fromLatin1("RFileExporterFactoryAdapter(): no matching constructor found."),
           context);
    }
    
    return result;
    }
    

    // conversion functions for base classes:
     QScriptValue REcmaFileExporterFactoryAdapter::getRFileExporterFactory(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                RFileExporterFactory* cppResult =
                    qscriptvalue_cast<RFileExporterFactoryAdapter*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
            

    // returns class name:
     QScriptValue REcmaFileExporterFactoryAdapter::getClassName(QScriptContext *context, QScriptEngine *engine) 
        
    {
        return qScriptValueFromValue(engine, QString("RFileExporterFactoryAdapter"));
    }
    

    // returns all base classes (in case of multiple inheritance):
     QScriptValue REcmaFileExporterFactoryAdapter::getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        
    {
        QStringList list;
        
        list.append("RFileExporterFactory");
    

        return qScriptValueFromSequence(engine, list);
    }
    

    // properties:
    

    // public methods:
     QScriptValue
        REcmaFileExporterFactoryAdapter::getFilterStrings
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaFileExporterFactoryAdapter::getFilterStrings", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaFileExporterFactoryAdapter::getFilterStrings";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RFileExporterFactoryAdapter* self = 
                        getSelf("getFilterStrings", context);
                  

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
    // return type 'QStringList'
    QStringList cppResult =
        
               self->getFilterStrings();
        // return type: QStringList
                // not standard type nor reference
                result = qScriptValueFromValue(engine, cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RFileExporterFactoryAdapter.getFilterStrings().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaFileExporterFactoryAdapter::getFilterStrings", context, engine);
            return result;
        }
         QScriptValue
        REcmaFileExporterFactoryAdapter::canExport
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaFileExporterFactoryAdapter::canExport", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaFileExporterFactoryAdapter::canExport";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RFileExporterFactoryAdapter* self = 
                        getSelf("canExport", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isString()
        ) /* type: QString */
    
    ){
    // prepare arguments:
    
                    // argument isStandardType
                    QString
                    a0 =
                    (QString)
                    
                    context->argument( 0 ).
                    toString();
                
    // end of arguments

    // call C++ function:
    // return type 'int'
    int cppResult =
        
               self->canExport(a0);
        // return type: int
                // standard Type
                result = QScriptValue(cppResult);
            
    } else


        
    
    if( context->argumentCount() ==
    2 && (
            context->argument(0).isString()
        ) /* type: QString */
     && (
            context->argument(1).isString()
        ) /* type: QString */
    
    ){
    // prepare arguments:
    
                    // argument isStandardType
                    QString
                    a0 =
                    (QString)
                    
                    context->argument( 0 ).
                    toString();
                
                    // argument isStandardType
                    QString
                    a1 =
                    (QString)
                    
                    context->argument( 1 ).
                    toString();
                
    // end of arguments

    // call C++ function:
    // return type 'int'
    int cppResult =
        
               self->canExport(a0
        ,
    a1);
        // return type: int
                // standard Type
                result = QScriptValue(cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RFileExporterFactoryAdapter.canExport().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaFileExporterFactoryAdapter::canExport", context, engine);
            return result;
        }
         QScriptValue
        REcmaFileExporterFactoryAdapter::instantiate
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaFileExporterFactoryAdapter::instantiate", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaFileExporterFactoryAdapter::instantiate";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RFileExporterFactoryAdapter* self = 
                        getSelf("instantiate", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RDocument */
    
    ){
    // prepare arguments:
    
                    // argument is reference
                    RDocument*
                    ap0 =
                    qscriptvalue_cast<
                    RDocument*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if( ap0 == NULL ){

                           return REcmaHelper::throwError("RFileExporterFactoryAdapter: Argument 0 is not of type RDocument* or QSharedPointer<RDocument>.",
                               context);
                    }
                    RDocument& a0 = *ap0;
                
    // end of arguments

    // call C++ function:
    // return type 'RFileExporter *'
    RFileExporter * cppResult =
        
               self->instantiate(a0);
        // return type: RFileExporter *
                // not standard type nor reference
                result = qScriptValueFromValue(engine, cppResult);
            
    } else


        
    
    if( context->argumentCount() ==
    2 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RDocument */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: RMessageHandler * */
    
    ){
    // prepare arguments:
    
                    // argument is reference
                    RDocument*
                    ap0 =
                    qscriptvalue_cast<
                    RDocument*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if( ap0 == NULL ){

                           return REcmaHelper::throwError("RFileExporterFactoryAdapter: Argument 0 is not of type RDocument* or QSharedPointer<RDocument>.",
                               context);
                    }
                    RDocument& a0 = *ap0;
                
                    // argument is pointer
                    RMessageHandler * a1 = NULL;

                    a1 = 
                        REcmaHelper::scriptValueTo<RMessageHandler >(
                            context->argument(1)
                        );
                    
                    if (a1==NULL && 
                        !context->argument(1).isNull()) {
                        return REcmaHelper::throwError("RFileExporterFactoryAdapter: Argument 1 is not of type RMessageHandler *RMessageHandler *.", context);                    
                    }
                
    // end of arguments

    // call C++ function:
    // return type 'RFileExporter *'
    RFileExporter * cppResult =
        
               self->instantiate(a0
        ,
    a1);
        // return type: RFileExporter *
                // not standard type nor reference
                result = qScriptValueFromValue(engine, cppResult);
            
    } else


        
    
    if( context->argumentCount() ==
    3 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RDocument */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: RMessageHandler * */
     && (
            context->argument(2).isVariant() || 
            context->argument(2).isQObject() || 
            context->argument(2).isNull()
        ) /* type: RProgressHandler * */
    
    ){
    // prepare arguments:
    
                    // argument is reference
                    RDocument*
                    ap0 =
                    qscriptvalue_cast<
                    RDocument*
                        >(
                        context->argument(
                        0
                        )
                    );
                    if( ap0 == NULL ){

                           return REcmaHelper::throwError("RFileExporterFactoryAdapter: Argument 0 is not of type RDocument* or QSharedPointer<RDocument>.",
                               context);
                    }
                    RDocument& a0 = *ap0;
                
                    // argument is pointer
                    RMessageHandler * a1 = NULL;

                    a1 = 
                        REcmaHelper::scriptValueTo<RMessageHandler >(
                            context->argument(1)
                        );
                    
                    if (a1==NULL && 
                        !context->argument(1).isNull()) {
                        return REcmaHelper::throwError("RFileExporterFactoryAdapter: Argument 1 is not of type RMessageHandler *RMessageHandler *.", context);                    
                    }
                
                    // argument is pointer
                    RProgressHandler * a2 = NULL;

                    a2 = 
                        REcmaHelper::scriptValueTo<RProgressHandler >(
                            context->argument(2)
                        );
                    
                    if (a2==NULL && 
                        !context->argument(2).isNull()) {
                        return REcmaHelper::throwError("RFileExporterFactoryAdapter: Argument 2 is not of type RProgressHandler *RProgressHandler *.", context);                    
                    }
                
    // end of arguments

    // call C++ function:
    // return type 'RFileExporter *'
    RFileExporter * cppResult =
        
               self->instantiate(a0
        ,
    a1
        ,
    a2);
        // return type: RFileExporter *
                // not standard type nor reference
                result = qScriptValueFromValue(engine, cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RFileExporterFactoryAdapter.instantiate().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaFileExporterFactoryAdapter::instantiate", context, engine);
            return result;
        }
         QScriptValue REcmaFileExporterFactoryAdapter::toString
    (QScriptContext *context, QScriptEngine *engine)
    
    {

    RFileExporterFactoryAdapter* self = getSelf("toString", context);
    
    QString result;
    
            result = QString("RFileExporterFactoryAdapter(0x%1)").arg((unsigned long int)self, 0, 16);
        
    return QScriptValue(result);
    }
     QScriptValue REcmaFileExporterFactoryAdapter::destroy(QScriptContext *context, QScriptEngine *engine)
    
    {

        RFileExporterFactoryAdapter* self = getSelf("RFileExporterFactoryAdapter", context);
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
    RFileExporterFactoryAdapter* REcmaFileExporterFactoryAdapter::getSelf(const QString& fName, QScriptContext* context)
    
        {
            RFileExporterFactoryAdapter* self = NULL;

            
                // self could be a normal object (e.g. from an UI file) or
                // an ECMA shell object (made from an ECMA script):
                //self = getSelfShell(fName, context);
                

            //if (self==NULL) {
                self = REcmaHelper::scriptValueTo<RFileExporterFactoryAdapter >(context->thisObject())
                
                ;
            //}

            if (self == NULL){
                // avoid recursion (toString is used by the backtrace):
                if (fName!="toString") {
                    REcmaHelper::throwError(QString("RFileExporterFactoryAdapter.%1(): "
                        "This object is not a RFileExporterFactoryAdapter").arg(fName),
                        context);
                }
                return NULL;
            }

            return self;
        }
        REcmaShellFileExporterFactoryAdapter* REcmaFileExporterFactoryAdapter::getSelfShell(const QString& fName, QScriptContext* context)
    
        {
          RFileExporterFactoryAdapter* selfBase = getSelf(fName, context);
                REcmaShellFileExporterFactoryAdapter* self = dynamic_cast<REcmaShellFileExporterFactoryAdapter*>(selfBase);
                //return REcmaHelper::scriptValueTo<REcmaShellFileExporterFactoryAdapter >(context->thisObject());
            if(self == NULL){
                REcmaHelper::throwError(QString("RFileExporterFactoryAdapter.%1(): "
                    "This object is not a RFileExporterFactoryAdapter").arg(fName),
                    context);
            }

            return self;
            


        }
        