#include <QDebug>
#include <QObject>
#include <QScriptEngine>
#include <QStringList>

#include "RActionAdapter.h"
#include "RDocumentInterface.h"
#include "RGuiAction.h"
#include "RMainWindow.h"
#include "RPluginInterface.h"

class MyAction : public RActionAdapter {
public:
    MyAction(RGuiAction* guiAction) : RActionAdapter(guiAction) {}

    static void factory(RGuiAction* guiAction) {
        qDebug() << "MyAction::factory";
        if (guiAction==NULL) {
            qDebug("guiAction is NULL");
            return;
        }
        RDocumentInterface* di = RMainWindow::getDocumentInterfaceStatic();

        if (di==NULL) {
            qDebug("di is NULL");
            return;
        }

        di->setCurrentAction(new MyAction(guiAction));
    }

    virtual void beginEvent() {
        qDebug() << "MyAction::beginEvent";
    }
};

class MyClass : public QObject {
Q_OBJECT
public:
    MyClass() : QObject(), i(0), d(0.0) {}

    virtual int getInt() const {
        return i;
    }

    virtual double getDouble() const {
        return d;
    }

    virtual QString getString() const {
        return s;
    }

    virtual void setInt(int v) {
        i = v;
    }

    virtual void setDouble(int v) {
        d = v;
    }

    virtual void setString(const QString& v) {
        s = v;
    }

    void emitSignal() {
        emit mySignal(i);
    }

signals:
    void mySignal(int code);

private:
    int i;
    double d;
    QString s;
};

Q_DECLARE_METATYPE(MyClass*)

/**
 * Script binding for MyClass.
 */
class EcmaMyClass {
public:
    static void initEcma(QScriptEngine& engine);

    static QScriptValue createMyClass(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue myClassToString(QScriptContext *context, QScriptEngine *engine);
    static MyClass* getSelfMyClass(const QString& fName, QScriptContext* context);

    static QScriptValue getInt(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue getDouble(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue getString(QScriptContext* context, QScriptEngine* engine);

    static QScriptValue setInt(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue setDouble(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue setString(QScriptContext* context, QScriptEngine* engine);

    static QScriptValue emitSignal(QScriptContext* context, QScriptEngine* engine);
};



class RExamplePlugin2 : public QObject, public RPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(RPluginInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qcad.exampleplugin")
#endif

public:
    virtual bool init();
    virtual void uninit(bool) {}
    virtual void postInit(InitStatus status);
    virtual void initScriptExtensions(QScriptEngine& engine);
    virtual RPluginInfo getPluginInfo();
    virtual bool checkLicense() { return true; }
    virtual void initTranslations(){}
};

