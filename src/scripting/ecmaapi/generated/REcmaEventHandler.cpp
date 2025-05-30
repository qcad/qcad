// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #include "REcmaEventHandler.h"
        #include "RMetaTypes.h"
        #include "../REcmaHelper.h"

        // forwards declarations mapped to includes
        
                #include <QScrollBar>
            
                #include <QUrl>
            
                #include <QWidget>
            
                #include <QMimeData>
            
                #include <QDragEnterEvent>
            
                #include "RDocumentInterface.h"
            
                #include "RGraphicsView.h"
            
                #include "RRulerQt.h"
            
                #include "RSnap.h"
            
                #include "RVector.h"
            
                #include "RTextLabel.h"
            
                #include "RSnapRestriction.h"
            
                #include "RGraphicsViewWorker.h"
            
            
        // includes for base ecma wrapper classes
         void REcmaEventHandler::initEcma(QScriptEngine& engine, QScriptValue* proto 
    
    ) 
    
    {

    bool protoCreated = false;
    if(proto == NULL){
        proto = new QScriptValue(engine.newVariant(qVariantFromValue(
                (REventHandler*) 0)));
        protoCreated = true;
    }

    
        // primary base class QObject:
        
            QScriptValue dpt = engine.defaultPrototype(
                qMetaTypeId<QObject*>());

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
    
        // conversion for base class QObject
        REcmaHelper::registerFunction(&engine, proto, getQObject, "getQObject");
        

    // get class name
    REcmaHelper::registerFunction(&engine, proto, getClassName, "getClassName");
    

    // conversion to all base classes (multiple inheritance):
    REcmaHelper::registerFunction(&engine, proto, getBaseClasses, "getBaseClasses");
    

    // properties:
    

    // methods:
    
            REcmaHelper::registerFunction(&engine, proto, drawInfoLabel, "drawInfoLabel");
            
            REcmaHelper::registerFunction(&engine, proto, drawSnapLabel, "drawSnapLabel");
            
            REcmaHelper::registerFunction(&engine, proto, dragEnter, "dragEnter");
            
            REcmaHelper::registerFunction(&engine, proto, updateTextLabel, "updateTextLabel");
            
            REcmaHelper::registerFunction(&engine, proto, updateSnapInfo, "updateSnapInfo");
            
            REcmaHelper::registerFunction(&engine, proto, viewportChanged, "viewportChanged");
            
            REcmaHelper::registerFunction(&engine, proto, horizontalScrolled, "horizontalScrolled");
            
            REcmaHelper::registerFunction(&engine, proto, verticalScrolled, "verticalScrolled");
            
        engine.setDefaultPrototype(
            qMetaTypeId<REventHandler*>(), *proto);

        
                        qScriptRegisterMetaType<
                        REventHandler*>(
                        &engine, toScriptValue, fromScriptValue, *proto);
                    
    

    QScriptValue ctor = engine.newFunction(createEcma, *proto, 2);
    
    // static methods:
    
            REcmaHelper::registerFunction(&engine, &ctor, isUrl, "isUrl");
            
            REcmaHelper::registerFunction(&engine, &ctor, getUrlsFromMimeData, "getUrlsFromMimeData");
            

    // static properties:
    

    // enum values:
    

    // enum conversions:
    
        
    // init class:
    engine.globalObject().setProperty("REventHandler",
    ctor, QScriptValue::SkipInEnumeration);
    
    if( protoCreated ){
       delete proto;
    }
    
    }
     QScriptValue REcmaEventHandler::createEcma(QScriptContext* context, QScriptEngine* engine) 
    
    {
    if (context->thisObject().strictlyEquals(
       engine->globalObject())) {
       return REcmaHelper::throwError(
       QString::fromLatin1("REventHandler(): Did you forget to construct with 'new'?"),
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
    
            // non-copyable class:
            REcmaShellEventHandler
                    * cppResult =
                    new
                    REcmaShellEventHandler
                    ();
                
                    result = engine->newQObject(context->thisObject(), cppResult, QScriptEngine::QtOwnership);
                
        cppResult->__qtscript_self = result;
    
    } else 

    if( context->argumentCount() ==
        1
                && (
                
                        context->argument(
                        0
                        ).isQObject()
                        ||
                    
                        context->argument(
                        0
                        ).isNull()
                ) /* type: QWidget * */
            
    ){
    // prepare arguments:
    
            // argument isQObject
            QWidget *
            a0 =
            qobject_cast<
            QWidget *>
            ( context->argument(
            0
            ).
            toQObject()
            );
        
    // end of arguments

    // call C++ constructor:
    
            // non-copyable class:
            REcmaShellEventHandler
                    * cppResult =
                    new
                    REcmaShellEventHandler
                    (
                    a0
                    );
                
                    result = engine->newQObject(context->thisObject(), cppResult, QScriptEngine::QtOwnership);
                
        cppResult->__qtscript_self = result;
    
    } else 

    if( context->argumentCount() ==
        2
                && (
                
                        context->argument(
                        0
                        ).isQObject()
                        ||
                    
                        context->argument(
                        0
                        ).isNull()
                ) /* type: QWidget * */
            
                && (
                
                        context->argument(
                        1
                        ).isVariant()
                        ||
                    
                        context->argument(
                        1
                        ).isQObject()
                        ||
                    
                        context->argument(
                        1
                        ).isNull()
                ) /* type: RDocumentInterface * */
            
    ){
    // prepare arguments:
    
            // argument isQObject
            QWidget *
            a0 =
            qobject_cast<
            QWidget *>
            ( context->argument(
            0
            ).
            toQObject()
            );
        
                    // argument is pointer
                    RDocumentInterface * a1 = NULL;

                    a1 = 
                        REcmaHelper::scriptValueTo<RDocumentInterface >(
                            context->argument(1)
                        );
                    
                    if (a1==NULL && 
                        !context->argument(1).isNull()) {
                        return REcmaHelper::throwError("REventHandler: Argument 1 is not of type RDocumentInterface *RDocumentInterface *.", context);                    
                    }
                
    // end of arguments

    // call C++ constructor:
    
            // non-copyable class:
            REcmaShellEventHandler
                    * cppResult =
                    new
                    REcmaShellEventHandler
                    (
                    a0
        ,
    a1
                    );
                
                    result = engine->newQObject(context->thisObject(), cppResult, QScriptEngine::QtOwnership);
                
        cppResult->__qtscript_self = result;
    
    } else 

    {
       return REcmaHelper::throwError(
       QString::fromLatin1("REventHandler(): no matching constructor found."),
           context);
    }
    
    return result;
    }
    

    // conversion functions for base classes:
     QScriptValue REcmaEventHandler::getQObject(QScriptContext *context,
            QScriptEngine *engine)
        
            {
                QObject* cppResult =
                    qscriptvalue_cast<REventHandler*> (context->thisObject());
                QScriptValue result = qScriptValueFromValue(engine, cppResult);
                return result;
            }
            

    // returns class name:
     QScriptValue REcmaEventHandler::getClassName(QScriptContext *context, QScriptEngine *engine) 
        
    {
        return qScriptValueFromValue(engine, QString("REventHandler"));
    }
    

    // returns all base classes (in case of multiple inheritance):
     QScriptValue REcmaEventHandler::getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        
    {
        QStringList list;
        
        list.append("QObject");
    

        return qScriptValueFromSequence(engine, list);
    }
    

    // properties:
    

    // public methods:
     QScriptValue
        REcmaEventHandler::isUrl
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaEventHandler::isUrl", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaEventHandler::isUrl";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
    
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
    // return type 'bool'
    bool cppResult =
        REventHandler::
       isUrl(a0);
        // return type: bool
                // standard Type
                result = QScriptValue(cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for REventHandler.isUrl().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaEventHandler::isUrl", context, engine);
            return result;
        }
         QScriptValue
        REcmaEventHandler::getUrlsFromMimeData
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaEventHandler::getUrlsFromMimeData", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaEventHandler::getUrlsFromMimeData";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: QMimeData * */
    
    ){
    // prepare arguments:
    
                    // argument is pointer
                    QMimeData * a0 = NULL;

                    a0 = 
                        REcmaHelper::scriptValueTo<QMimeData >(
                            context->argument(0)
                        );
                    
                    if (a0==NULL && 
                        !context->argument(0).isNull()) {
                        return REcmaHelper::throwError("REventHandler: Argument 0 is not of type QMimeData *QMimeData *.", context);                    
                    }
                
    // end of arguments

    // call C++ function:
    // return type 'QList < QUrl >'
    QList < QUrl > cppResult =
        REventHandler::
       getUrlsFromMimeData(a0);
        // return type: QList < QUrl >
                // List of ...:
                result = REcmaHelper::listToScriptValue(engine, cppResult);
            
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for REventHandler.getUrlsFromMimeData().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaEventHandler::getUrlsFromMimeData", context, engine);
            return result;
        }
         QScriptValue
        REcmaEventHandler::drawInfoLabel
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaEventHandler::drawInfoLabel", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaEventHandler::drawInfoLabel";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    REventHandler* self = 
                        getSelf("drawInfoLabel", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    2 && (
            context->argument(0).isQObject()
        ) /* type: RGraphicsViewWorker * */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: RTextLabel */
    
    ){
    // prepare arguments:
    
                    // argument is pointer
                    RGraphicsViewWorker * a0 = NULL;

                    a0 = 
                        REcmaHelper::scriptValueTo<RGraphicsViewWorker >(
                            context->argument(0)
                        );
                    
                    if (a0==NULL && 
                        !context->argument(0).isNull()) {
                        return REcmaHelper::throwError("REventHandler: Argument 0 is not of type RGraphicsViewWorker *RGraphicsViewWorker *.", context);                    
                    }
                
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RTextLabel*
                    ap1 =
                    qscriptvalue_cast<
                    RTextLabel*
                        >(
                        context->argument(
                        1
                        )
                    );
                    if (ap1 == NULL) {
                           return REcmaHelper::throwError("REventHandler: Argument 1 is not of type RTextLabel.",
                               context);                    
                    }
                    RTextLabel 
                    a1 = 
                    *ap1;
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->drawInfoLabel(a0
        ,
    a1);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for REventHandler.drawInfoLabel().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaEventHandler::drawInfoLabel", context, engine);
            return result;
        }
         QScriptValue
        REcmaEventHandler::drawSnapLabel
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaEventHandler::drawSnapLabel", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaEventHandler::drawSnapLabel";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    REventHandler* self = 
                        getSelf("drawSnapLabel", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    4 && (
            context->argument(0).isQObject()
        ) /* type: RGraphicsViewWorker * */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: RVector */
     && (
            context->argument(2).isVariant() || 
            context->argument(2).isQObject() || 
            context->argument(2).isNull()
        ) /* type: RVector */
     && (
            context->argument(3).isString()
        ) /* type: QString */
    
    ){
    // prepare arguments:
    
                    // argument is pointer
                    RGraphicsViewWorker * a0 = NULL;

                    a0 = 
                        REcmaHelper::scriptValueTo<RGraphicsViewWorker >(
                            context->argument(0)
                        );
                    
                    if (a0==NULL && 
                        !context->argument(0).isNull()) {
                        return REcmaHelper::throwError("REventHandler: Argument 0 is not of type RGraphicsViewWorker *RGraphicsViewWorker *.", context);                    
                    }
                
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
                           return REcmaHelper::throwError("REventHandler: Argument 1 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a1 = 
                    *ap1;
                
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RVector*
                    ap2 =
                    qscriptvalue_cast<
                    RVector*
                        >(
                        context->argument(
                        2
                        )
                    );
                    if (ap2 == NULL) {
                           return REcmaHelper::throwError("REventHandler: Argument 2 is not of type RVector.",
                               context);                    
                    }
                    RVector 
                    a2 = 
                    *ap2;
                
                    // argument isStandardType
                    QString
                    a3 =
                    (QString)
                    
                    context->argument( 3 ).
                    toString();
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->drawSnapLabel(a0
        ,
    a1
        ,
    a2
        ,
    a3);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for REventHandler.drawSnapLabel().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaEventHandler::drawSnapLabel", context, engine);
            return result;
        }
         QScriptValue
        REcmaEventHandler::dragEnter
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaEventHandler::dragEnter", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaEventHandler::dragEnter";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    REventHandler* self = 
                        getSelf("dragEnter", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isVariant() || 
            context->argument(0).isQObject() || 
            context->argument(0).isNull()
        ) /* type: QDragEnterEvent * */
    
    ){
    // prepare arguments:
    
                    // argument is pointer
                    QDragEnterEvent * a0 = NULL;

                    a0 = 
                        REcmaHelper::scriptValueTo<QDragEnterEvent >(
                            context->argument(0)
                        );
                    
                    if (a0==NULL && 
                        !context->argument(0).isNull()) {
                        return REcmaHelper::throwError("REventHandler: Argument 0 is not of type QDragEnterEvent *QDragEnterEvent *.", context);                    
                    }
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->dragEnter(a0);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for REventHandler.dragEnter().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaEventHandler::dragEnter", context, engine);
            return result;
        }
         QScriptValue
        REcmaEventHandler::updateTextLabel
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaEventHandler::updateTextLabel", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaEventHandler::updateTextLabel";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    REventHandler* self = 
                        getSelf("updateTextLabel", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    2 && (
            context->argument(0).isQObject()
        ) /* type: RGraphicsViewWorker * */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: RTextLabel */
    
    ){
    // prepare arguments:
    
                    // argument is pointer
                    RGraphicsViewWorker * a0 = NULL;

                    a0 = 
                        REcmaHelper::scriptValueTo<RGraphicsViewWorker >(
                            context->argument(0)
                        );
                    
                    if (a0==NULL && 
                        !context->argument(0).isNull()) {
                        return REcmaHelper::throwError("REventHandler: Argument 0 is not of type RGraphicsViewWorker *RGraphicsViewWorker *.", context);                    
                    }
                
                    // argument isCopyable and has default constructor and isSimpleClass 
                    RTextLabel*
                    ap1 =
                    qscriptvalue_cast<
                    RTextLabel*
                        >(
                        context->argument(
                        1
                        )
                    );
                    if (ap1 == NULL) {
                           return REcmaHelper::throwError("REventHandler: Argument 1 is not of type RTextLabel.",
                               context);                    
                    }
                    RTextLabel 
                    a1 = 
                    *ap1;
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->updateTextLabel(a0
        ,
    a1);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for REventHandler.updateTextLabel().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaEventHandler::updateTextLabel", context, engine);
            return result;
        }
         QScriptValue
        REcmaEventHandler::updateSnapInfo
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaEventHandler::updateSnapInfo", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaEventHandler::updateSnapInfo";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    REventHandler* self = 
                        getSelf("updateSnapInfo", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    3 && (
            context->argument(0).isQObject()
        ) /* type: RGraphicsViewWorker * */
     && (
            context->argument(1).isVariant() || 
            context->argument(1).isQObject() || 
            context->argument(1).isNull()
        ) /* type: RSnap * */
     && (
            context->argument(2).isVariant() || 
            context->argument(2).isQObject() || 
            context->argument(2).isNull()
        ) /* type: RSnapRestriction * */
    
    ){
    // prepare arguments:
    
                    // argument is pointer
                    RGraphicsViewWorker * a0 = NULL;

                    a0 = 
                        REcmaHelper::scriptValueTo<RGraphicsViewWorker >(
                            context->argument(0)
                        );
                    
                    if (a0==NULL && 
                        !context->argument(0).isNull()) {
                        return REcmaHelper::throwError("REventHandler: Argument 0 is not of type RGraphicsViewWorker *RGraphicsViewWorker *.", context);                    
                    }
                
                    // argument is pointer
                    RSnap * a1 = NULL;

                    a1 = 
                        REcmaHelper::scriptValueTo<RSnap >(
                            context->argument(1)
                        );
                    
                    if (a1==NULL && 
                        !context->argument(1).isNull()) {
                        return REcmaHelper::throwError("REventHandler: Argument 1 is not of type RSnap *RSnap *.", context);                    
                    }
                
                    // argument is pointer
                    RSnapRestriction * a2 = NULL;

                    a2 = 
                        REcmaHelper::scriptValueTo<RSnapRestriction >(
                            context->argument(2)
                        );
                    
                    if (a2==NULL && 
                        !context->argument(2).isNull()) {
                        return REcmaHelper::throwError("REventHandler: Argument 2 is not of type RSnapRestriction *RSnapRestriction *.", context);                    
                    }
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->updateSnapInfo(a0
        ,
    a1
        ,
    a2);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for REventHandler.updateSnapInfo().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaEventHandler::updateSnapInfo", context, engine);
            return result;
        }
         QScriptValue
        REcmaEventHandler::viewportChanged
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaEventHandler::viewportChanged", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaEventHandler::viewportChanged";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    REventHandler* self = 
                        getSelf("viewportChanged", context);
                  

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
    // return type 'void'
    
               self->viewportChanged();
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for REventHandler.viewportChanged().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaEventHandler::viewportChanged", context, engine);
            return result;
        }
         QScriptValue
        REcmaEventHandler::horizontalScrolled
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaEventHandler::horizontalScrolled", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaEventHandler::horizontalScrolled";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    REventHandler* self = 
                        getSelf("horizontalScrolled", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isNumber()
        ) /* type: double */
    
    ){
    // prepare arguments:
    
                    // argument isStandardType
                    double
                    a0 =
                    (double)
                    
                    context->argument( 0 ).
                    toNumber();
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->horizontalScrolled(a0);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for REventHandler.horizontalScrolled().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaEventHandler::horizontalScrolled", context, engine);
            return result;
        }
         QScriptValue
        REcmaEventHandler::verticalScrolled
        (QScriptContext* context, QScriptEngine* engine) 
        
        {
            //REcmaHelper::functionStart("REcmaEventHandler::verticalScrolled", context, engine);
            //qDebug() << "ECMAScript WRAPPER: REcmaEventHandler::verticalScrolled";
            //QCoreApplication::processEvents();

            QScriptValue result = engine->undefinedValue();
            
                    // public function: can be called from ECMA wrapper of ECMA shell:
                    REventHandler* self = 
                        getSelf("verticalScrolled", context);
                  

                //Q_ASSERT(self!=NULL);
                if (self==NULL) {
                    return REcmaHelper::throwError("self is NULL", context);
                }
                
    
    if( context->argumentCount() ==
    1 && (
            context->argument(0).isNumber()
        ) /* type: double */
    
    ){
    // prepare arguments:
    
                    // argument isStandardType
                    double
                    a0 =
                    (double)
                    
                    context->argument( 0 ).
                    toNumber();
                
    // end of arguments

    // call C++ function:
    // return type 'void'
    
               self->verticalScrolled(a0);
    } else


        
            {
               return REcmaHelper::throwError("Wrong number/types of arguments for REventHandler.verticalScrolled().",
                   context);
            }
            //REcmaHelper::functionEnd("REcmaEventHandler::verticalScrolled", context, engine);
            return result;
        }
         QScriptValue REcmaEventHandler::toString
    (QScriptContext *context, QScriptEngine *engine)
    
    {

    REventHandler* self = getSelf("toString", context);
    
    QString result;
    
            result = QString("REventHandler(0x%1)").arg((unsigned long int)self, 0, 16);
        
    return QScriptValue(result);
    }
     QScriptValue REcmaEventHandler::destroy(QScriptContext *context, QScriptEngine *engine)
    
    {

        REventHandler* self = getSelf("REventHandler", context);
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
    REventHandler* REcmaEventHandler::getSelf(const QString& fName, QScriptContext* context)
    
        {
            REventHandler* self = NULL;

            
                // self could be a normal object (e.g. from an UI file) or
                // an ECMA shell object (made from an ECMA script):
                //self = getSelfShell(fName, context);
                

            //if (self==NULL) {
                self = REcmaHelper::scriptValueTo<REventHandler >(context->thisObject())
                
                ;
            //}

            if (self == NULL){
                // avoid recursion (toString is used by the backtrace):
                if (fName!="toString") {
                    REcmaHelper::throwError(QString("REventHandler.%1(): "
                        "This object is not a REventHandler").arg(fName),
                        context);
                }
                return NULL;
            }

            return self;
        }
        REcmaShellEventHandler* REcmaEventHandler::getSelfShell(const QString& fName, QScriptContext* context)
    
        {
          REventHandler* selfBase = getSelf(fName, context);
                REcmaShellEventHandler* self = dynamic_cast<REcmaShellEventHandler*>(selfBase);
                //return REcmaHelper::scriptValueTo<REcmaShellEventHandler >(context->thisObject());
            if(self == NULL){
                REcmaHelper::throwError(QString("REventHandler.%1(): "
                    "This object is not a REventHandler").arg(fName),
                    context);
            }

            return self;
            


        }
         void fromScriptValue(const QScriptValue& value,
        REventHandler*
        &out) {
            QObject* o = value.toQObject();
            out = qobject_cast<
            REventHandler*>(o);
        }
     QScriptValue toScriptValue(QScriptEngine *engine,
        REventHandler*
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
    