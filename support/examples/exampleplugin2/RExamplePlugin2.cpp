#include <QMenuBar>

#include "REcmaHelper.h"
#include "RExamplePlugin2.h"
#include "RSettings.h"
#include "RPluginInfo.h"
#include "RVersion.h"
#include "RMainWindowQt.h"


bool RExamplePlugin2::init() {
    qDebug() << "RExamplePlugin2::init";
    return true;
}

void RExamplePlugin2::postInit(InitStatus status) {
    if (status!=RPluginInterface::AllDone) {
        return;
    }
    RMainWindowQt* appWin = RMainWindowQt::getMainWindow();
    RGuiAction* guiAction = new RGuiAction("My CPP Action", appWin);
    guiAction->setRequiresDocument(true);
    //guiAction->setScriptFile(basePath + "/Line2P.js");
    //guiAction->setIcon(basePath + "/Line2P.svg");
    //guiAction->setStatusTip(qsTranslate("Line2P", "Draw single line or sequence of lines"));
    //guiAction->setDefaultShortcut(new QKeySequence("l,i"));
    guiAction->setGroupSortOrder(100000);
    guiAction->setSortOrder(100);

    QMenuBar* menuBar = appWin->menuBar();
    QMenu* menu = menuBar->findChild<QMenu*>("MiscMenu");
    //menu->addAction(guiAction);
    guiAction->addToMenu(menu);

    guiAction->setFactory(MyAction::factory);
    //MyAction* action = new MyAction(guiAction);


}

void RExamplePlugin2::initScriptExtensions(QScriptEngine& engine) {
    EcmaMyClass::initEcma(engine);
}

RPluginInfo RExamplePlugin2::getPluginInfo() {
    RPluginInfo ret;
    ret.set("Version", R_QCAD_VERSION_STRING);
    ret.set("ID", "EXAMPLE");
    ret.set("Name", "Example Plugin");
    ret.set("License", "GPLv3");
    ret.set("URL", "http://qcad.org");
    return ret;
}



void EcmaMyClass::initEcma(QScriptEngine& engine) {
    QScriptValue* proto = new QScriptValue(engine.newVariant(qVariantFromValue((MyClass*)0)));

    // base class:
    QScriptValue dpt = engine.defaultPrototype(qMetaTypeId<QObject*>());
    proto->setPrototype(dpt);

    REcmaHelper::registerFunction(&engine, proto, myClassToString, "toString");

    engine.setDefaultPrototype(qMetaTypeId<MyClass*>(), *proto);
                        
    QScriptValue ctor = engine.newFunction(createMyClass, *proto, 0);

    engine.globalObject().setProperty("MyClass", ctor, QScriptValue::SkipInEnumeration);

    // register function getInt:
    REcmaHelper::registerFunction(
        &engine, 
        proto,            // prototype
        getInt,           // reference to static function
        "getInt");        // name in ECMAScript

    REcmaHelper::registerFunction(&engine, proto, getDouble, "getDouble");
    REcmaHelper::registerFunction(&engine, proto, getString, "getString");

    REcmaHelper::registerFunction(&engine, proto, setInt,    "setInt");
    REcmaHelper::registerFunction(&engine, proto, setDouble, "setDouble");
    REcmaHelper::registerFunction(&engine, proto, setString, "setString");

    REcmaHelper::registerFunction(&engine, proto, emitSignal, "emitSignal");
}

/**
 * Constructor for MyClass.
 * Allows instantiation in ECMAScript as:
 * 
 * var v = new MyClass();
 */
QScriptValue EcmaMyClass::createMyClass(QScriptContext* context, QScriptEngine* engine) {
    if (context->thisObject().strictlyEquals(engine->globalObject())) {
        return REcmaHelper::throwError(QString::fromLatin1("MyClass(): Did you forget to construct with 'new'?"), context);
    }
    
    // constructor without arguments:
    if(context->argumentCount() == 0) {
        MyClass* cppResult = new MyClass();
        return engine->newQObject(context->thisObject(), cppResult);
    }
    else {
        return REcmaHelper::throwError(QString::fromLatin1("MyClass(): no matching constructor found."), context);
    }
}

/**
 * Allows implicit converstion of MyClass objects to strings:
 *
 * var v = new MyClass();
 * qDebug(v);
 * // MyClass(0x12345678)
 */
QScriptValue EcmaMyClass::myClassToString(QScriptContext *context, QScriptEngine *engine) {
    Q_UNUSED(engine)

    MyClass* self = getSelfMyClass("toString", context);
    if (self!=NULL) {
        return QScriptValue(QString("MyClass(0x%1)").arg((unsigned long int)self, 0, 16));
    }
    return QScriptValue();
}

/**
 * \return MyClass object from given script context. Helper function.
 */
MyClass* EcmaMyClass::getSelfMyClass(const QString& fName, QScriptContext* context) {
    MyClass* self = REcmaHelper::scriptValueTo<MyClass >(context->thisObject());
    if (self == NULL){
        if (fName!="toString") {
            REcmaHelper::throwError(QString("MyClass.%1(): This object is not a MyClass").arg(fName), context);
        }
        return NULL;
    }
    
    return self;
}

/**
 * Binding for getInt.
 */
QScriptValue EcmaMyClass::getInt(QScriptContext* context, QScriptEngine* engine) {
    MyClass* self = getSelfMyClass("getInt", context);
    if (self!=NULL) {
        int i = self->getInt();
        return QScriptValue(engine, i);
    }
    return QScriptValue();
}

/**
 * Binding for getDouble.
 */
QScriptValue EcmaMyClass::getDouble(QScriptContext* context, QScriptEngine* engine) {
    MyClass* self = getSelfMyClass("getDouble", context);
    if (self!=NULL) {
        double d = self->getDouble();
        return QScriptValue(engine, d);
    }
    return QScriptValue();
}

/**
 * Binding for getString.
 */
QScriptValue EcmaMyClass::getString(QScriptContext* context, QScriptEngine* engine) {
    MyClass* self = getSelfMyClass("getString", context);
    if (self!=NULL) {
        QString s = self->getString();
        return QScriptValue(engine, s);
    }
    return QScriptValue();
}

/**
 * Binding for setInt.
 */
QScriptValue EcmaMyClass::setInt(QScriptContext* context, QScriptEngine* engine) {
    MyClass* self = getSelfMyClass("setInt", context);
    if (self!=NULL) {
        if (context->argumentCount()==1 && context->argument(0).isNumber()) {
            int a0 = (int)context->argument(0).toNumber();
            self->setInt(a0);
        } 
        else {
            return REcmaHelper::throwError("Wrong number/types of arguments for EcmaMyClass.setInt().", context);
        }
    }
    return QScriptValue();
}

/**
 * Binding for setDouble.
 */
QScriptValue EcmaMyClass::setDouble(QScriptContext* context, QScriptEngine* engine) {
    MyClass* self = getSelfMyClass("setDouble", context);
    if (self!=NULL) {
        if (context->argumentCount()==1 && context->argument(0).isNumber()) {
            double a0 = (double)context->argument(0).toNumber();
            self->setDouble(a0);
        } 
        else {
            return REcmaHelper::throwError("Wrong number/types of arguments for EcmaMyClass.setDouble().", context);
        }
    }
    return QScriptValue();
}

/**
 * Binding for setString.
 */
QScriptValue EcmaMyClass::setString(QScriptContext* context, QScriptEngine* engine) {
    MyClass* self = getSelfMyClass("setString", context);
    if (self!=NULL) {
        if (context->argumentCount()==1 && context->argument(0).isString()) {
            QString a0 = context->argument(0).toString();
            self->setString(a0);
        } 
        else {
            return REcmaHelper::throwError("Wrong number/types of arguments for EcmaMyClass.setString().", context);
        }
    }
    return QScriptValue();
}

/**
 * Binding for emitSignal.
 */
QScriptValue EcmaMyClass::emitSignal(QScriptContext* context, QScriptEngine* engine) {
    MyClass* self = getSelfMyClass("emitSignal", context);
    if (self!=NULL) {
        if (context->argumentCount()==0) {
            self->emitSignal();
        }
        else {
            return REcmaHelper::throwError("Wrong number/types of arguments for EcmaMyClass.emitSignal().", context);
        }
    }
    return QScriptValue();
}

#if QT_VERSION < 0x050000
QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(example, RExamplePlugin2)
QT_END_NAMESPACE
#endif
