#include <QMenuBar>

#include "REcmaHelper.h"
#include "RExamplePlugin.h"
#include "RSettings.h"
#include "RPluginInfo.h"
#include "RVersion.h"
#include "RMainWindowQt.h"


bool RExamplePlugin::init() {
    qDebug() << "RExamplePlugin::init";
    return true;
}

void RExamplePlugin::postInit(InitStatus status) {
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

void RExamplePlugin::initScriptExtensions(QScriptEngine& engine) {
    QScriptValue* proto = new QScriptValue(engine.newVariant(qVariantFromValue((MyClass*)0)));

    // base class:
    QScriptValue dpt = engine.defaultPrototype(qMetaTypeId<QObject*>());
    proto->setPrototype(dpt);

    REcmaHelper::registerFunction(&engine, proto, RExamplePlugin::myClassToString, "toString");

    engine.setDefaultPrototype(qMetaTypeId<MyClass*>(), *proto);
                        
    //qScriptRegisterMetaType<MyClass*>(&engine, toScriptValue, fromScriptValue, *proto);

    QScriptValue ctor = engine.newFunction(RExamplePlugin::createMyClass, *proto, 0);

    engine.globalObject().setProperty("MyClass", ctor, QScriptValue::SkipInEnumeration);
}

RPluginInfo RExamplePlugin::getPluginInfo() {
    RPluginInfo ret;
    ret.set("Version", R_QCAD_VERSION_STRING);
    ret.set("Name", "Example Plugin");
    ret.set("License", "GPLv3");
    ret.set("URL", "http://qcad.org");
    return ret;
}

/**
 * Constructor for MyClass:
 */
QScriptValue RExamplePlugin::createMyClass(QScriptContext* context, QScriptEngine* engine) {
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
 * MyClass::toString
 */
QScriptValue RExamplePlugin::myClassToString(QScriptContext *context, QScriptEngine *engine) {
    MyClass* self = getSelfMyClass("toString", context);
    return QScriptValue(QString("MyClass(0x%1)").arg((unsigned long int)self, 0, 16));
}

MyClass* RExamplePlugin::getSelfMyClass(const QString& fName, QScriptContext* context) {
    MyClass* self = REcmaHelper::scriptValueTo<MyClass >(context->thisObject());
    if (self == NULL){
        if (fName!="toString") {
            REcmaHelper::throwError(QString("MyClass.%1(): This object is not a MyClass").arg(fName), context);
        }
        return NULL;
    }
    
    return self;
}

#if QT_VERSION < 0x050000
QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(example, RExamplePlugin)
QT_END_NAMESPACE
#endif
