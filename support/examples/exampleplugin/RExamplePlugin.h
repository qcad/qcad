#include <QDebug>
#include <QObject>
#include <QScriptEngine>
#include <QStringList>

#include "RPluginInterface.h"

class MyClass : public QObject {
Q_OBJECT
public:
    MyClass() : QObject() {}
};

Q_DECLARE_METATYPE(MyClass*)

class RExamplePlugin : public QObject, public RPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(RPluginInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qcad.exampleplugin")
#endif

public:
    virtual bool init();
    virtual void uninit(bool) {}
    virtual void postInit() {}
    virtual void initScriptExtensions(QScriptEngine& engine);
    virtual RPluginInfo getPluginInfo();

    static QScriptValue createMyClass(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue myClassToString(QScriptContext *context, QScriptEngine *engine);
    static MyClass* getSelfMyClass(const QString& fName, QScriptContext* context);
};
