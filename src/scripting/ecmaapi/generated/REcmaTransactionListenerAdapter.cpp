// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #include "REcmaTransactionListenerAdapter.h"
        #include "RMetaTypes.h"
        #include "../REcmaHelper.h"

        // forwards declarations mapped to includes
        
                #include "RDocument.h"
            
                #include "RTransaction.h"
            
                #include "RTransactionListener.h"
            
                #include "RTransactionListenerAdapter.h"
            
            
        // includes for base ecma wrapper classes
        
                  #include "REcmaTransactionListener.h"
                 void REcmaTransactionListenerAdapter::initEcma(QScriptEngine& engine, QScriptValue* proto 
    
    ) 
    
    {

    bool protoCreated = false;
    if(proto == NULL){
        proto = new QScriptValue(engine.newVariant(qVariantFromValue(
                (RTransactionListenerAdapter*) 0)));
        protoCreated = true;
    }

    
        // primary base class QObject:
        
            QScriptValue dpt = engine.defaultPrototype(
                qMetaTypeId<QObject*>());

            if (dpt.isValid()) {
                proto->setPrototype(dpt);
            }
          
        /*
        REcmaTransactionListener::initEcma(engine, proto);
          
        */
    

    QScriptValue fun;

    // toString:
    REcmaHelper::registerFunction(&engine, proto, toString, "toString");
    

    // destroy:
    REcmaHelper::registerFunction(&engine, proto, destroy, "destroy");
    
        // conversion for base class QObject
        REcmaHelper::registerFunction(&engine, proto, getQObject, "getQObject");
        
        // conversion for base class RTransactionListener
        REcmaHelper::registerFunction(&engine, proto, getRTransactionListener, "getRTransactionListener");
        

    // get class name
    REcmaHelper::registerFunction(&engine, proto, getClassName, "getClassName");
    

    // conversion to all base classes (multiple inheritance):
    REcmaHelper::registerFunction(&engine, proto, getBaseClasses, "getBaseClasses");
    

        // properties of secondary base class RTransactionListener:
        

        // methods of secondary base class RTransactionListener:
        

    // properties:
    

    // methods:
    
            REcmaHelper::registerFunction(&engine, proto, updateTransactionListener, "updateTransactionListener");
            
            REcmaHelper::registerFunction(&engine, proto, setCurrentBlock, "setCurrentBlock");
            
        engine.setDefaultPrototype(
            qMetaTypeId<RTransactionListenerAdapter*>(), *proto);

        
                        qScriptRegisterMetaType<
                        RTransactionListenerAdapter*>(
                        &engine, toScriptValue, fromScriptValue, *proto);
                    
    

    QScriptValue ctor = engine.newFunction(createEcma, *proto, 2);
    
    // static methods:
    

    // static properties:
    

    // enum values:
    

    // enum conversions:
    
        
    // init class:
    engine.globalObject().setProperty("RTransactionListenerAdapter",
    ctor, QScriptValue::SkipInEnumeration);
    
    if( protoCreated ){
       delete proto;
    }
    
    }
     QScriptValue REcmaTransactionListenerAdapter::createEcma(QScriptContext* context, QScriptEngine* engine) 
    
    {
    if (context->thisObject().strictlyEquals(
       engine->globalObject())) {
       return REcmaHelper::throwError(
       QString::fromLatin1("RTransactionListenerAdapter(): Did you forget to construct with 'new'?"),
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
            RTransactionListenerAdapter
                    * cppResult =
                    new
                    RTransactionListenerAdapter
                    ();
                
                    result = engine->newQObject(context->thisObject(), cppResult, QScriptEngine::QtOwnership);
                
    } else 

    {
       return REcmaHelper::throwError(
       QString::fromLatin1("RTransactionListenerAdapter(): no matching constructor found."),
           context);
    }
    
    return result;
    }
    

    // conversion functions for base classes:
     QScriptValue REcmaTransactionListenerAdapter::getQObject(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                QObject* cppResult =
                    qscriptvalue_cast<RTransactionListenerAdapter*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
             QScriptValue REcmaTransactionListenerAdapter::getRTransactionListener(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                RTransactionListener* cppResult =
                    qscriptvalue_cast<RTransactionListenerAdapter*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
            

    // returns class name:
     QScriptValue REcmaTransactionListenerAdapter::getClassName(QScriptContext *context, QScriptEngine *engine) 
        
    {
        return qScriptValueFromValue(engine, QString("RTransactionListenerAdapter"));
    }
    

    // returns all base classes (in case of multiple inheritance):
     QScriptValue REcmaTransactionListenerAdapter::getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        
    {
        QStringList list;
        
        list.append("QObject");
    
        list.append("RTransactionListener");
    

        return qScriptValueFromSequence(engine, list);
    }
    
        // properties of secondary base class RTransactionListener:
        

        // methods of secondary base class RTransactionListener:
        

    // properties:
    

    // public methods:
     QScriptValue
        REcmaTransactionListenerAdapter::updateTransactionListener
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaTransactionListenerAdapter::updateTransactionListener", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaTransactionListenerAdapter::updateTransactionListener";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RTransactionListenerAdapter* self = 
                        getSelf("updateTransactionListener", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RDocument * */
    
    ){
    // prepare arguments:
    
                    // argument is pointer
                    RDocument * a0 = NULL;

                    a0 = 
                        REcmaHelper::scriptValueTo<RDocument >(
                            context->argument(0)
                        );
                    
                    if (a0==NULL && 
                        !context->argument(0).isNull()) {
                        return REcmaHelper::throwError("RTransactionListenerAdapter: Argument 0 is not of type RDocument *RDocument *.", context);                    
                    }
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->updateTransactionListener(a0);
    } else


        
    
    if( context->argumentCount() ==
    2 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RDocument * */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: RTransaction * */
    
    ){
    // prepare arguments:
    
                    // argument is pointer
                    RDocument * a0 = NULL;

                    a0 = 
                        REcmaHelper::scriptValueTo<RDocument >(
                            context->argument(0)
                        );
                    
                    if (a0==NULL && 
                        !context->argument(0).isNull()) {
                        return REcmaHelper::throwError("RTransactionListenerAdapter: Argument 0 is not of type RDocument *RDocument *.", context);                    
                    }
                
                    // argument is pointer
                    RTransaction * a1 = NULL;

                    a1 = 
                        REcmaHelper::scriptValueTo<RTransaction >(
                            context->argument(1)
                        );
                    
                    if (a1==NULL && 
                        !context->argument(1).isNull()) {
                        return REcmaHelper::throwError("RTransactionListenerAdapter: Argument 1 is not of type RTransaction *RTransaction *.", context);                    
                    }
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->updateTransactionListener(a0
        ,
    a1);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RTransactionListenerAdapter.updateTransactionListener().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaTransactionListenerAdapter::updateTransactionListener", context, engine);
            return result;
        }
         QScriptValue
        REcmaTransactionListenerAdapter::setCurrentBlock
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaTransactionListenerAdapter::setCurrentBlock", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaTransactionListenerAdapter::setCurrentBlock";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    RTransactionListenerAdapter* self = 
                        getSelf("setCurrentBlock", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: RDocument * */
    
    ){
    // prepare arguments:
    
                    // argument is pointer
                    RDocument * a0 = NULL;

                    a0 = 
                        REcmaHelper::scriptValueTo<RDocument >(
                            context->argument(0)
                        );
                    
                    if (a0==NULL && 
                        !context->argument(0).isNull()) {
                        return REcmaHelper::throwError("RTransactionListenerAdapter: Argument 0 is not of type RDocument *RDocument *.", context);                    
                    }
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->setCurrentBlock(a0);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for RTransactionListenerAdapter.setCurrentBlock().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaTransactionListenerAdapter::setCurrentBlock", context, engine);
            return result;
        }
         QScriptValue REcmaTransactionListenerAdapter::toString
    (QScriptContext *context, QScriptEngine *engine)
    
    {

    RTransactionListenerAdapter* self = getSelf("toString", context);
    
    QString result;
    
            result = QString("RTransactionListenerAdapter(0x%1)").arg((unsigned long int)self, 0, 16);
        
    return QScriptValue(result);
    }
     QScriptValue REcmaTransactionListenerAdapter::destroy(QScriptContext *context, QScriptEngine *engine)
    
    {

        RTransactionListenerAdapter* self = getSelf("RTransactionListenerAdapter", context);
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
    RTransactionListenerAdapter* REcmaTransactionListenerAdapter::getSelf(const QString& fName, QScriptContext* context)
    
        {
            RTransactionListenerAdapter* self = NULL;

            
                // self could be a normal object (e.g. from an UI file) or
                // an ECMA shell object (made from an ECMA script):
                //self = getSelfShell(fName, context);
                

            //if (self==NULL) {
                self = REcmaHelper::scriptValueTo<RTransactionListenerAdapter >(context->thisObject())
                
                ;
            //}

            if (self == NULL){
                // avoid recursion (toString is used by the backtrace):
                if (fName!="toString") {
                    REcmaHelper::throwError(QString("RTransactionListenerAdapter.%1(): "
                        "This object is not a RTransactionListenerAdapter").arg(fName),
                        context);
                }
                return NULL;
            }

            return self;
        }
        RTransactionListenerAdapter* REcmaTransactionListenerAdapter::getSelfShell(const QString& fName, QScriptContext* context)
    
        {
          RTransactionListenerAdapter* selfBase = getSelf(fName, context);
                RTransactionListenerAdapter* self = dynamic_cast<RTransactionListenerAdapter*>(selfBase);
                //return REcmaHelper::scriptValueTo<RTransactionListenerAdapter >(context->thisObject());
            if(self == NULL){
                REcmaHelper::throwError(QString("RTransactionListenerAdapter.%1(): "
                    "This object is not a RTransactionListenerAdapter").arg(fName),
                    context);
            }

            return self;
            


        }
         void fromScriptValue(const QScriptValue& value,
        RTransactionListenerAdapter*
        &out) {
            QObject* o = value.toQObject();
            out = qobject_cast<
            RTransactionListenerAdapter*>(o);
        }
     QScriptValue toScriptValue(QScriptEngine *engine,
        RTransactionListenerAdapter*
        const &in){
            QScriptValue s = engine->newQObject(in, QScriptEngine::QtOwnership,
            QScriptEngine::PreferExistingWrapperObject);
            /*
            if(s.isNull()){
               REcmaHelper::throwError("This object is null.", engine->currentContext());
            }
            */
            return s;
        }
    