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
//        RDocumentInterface* di = guiAction->getDocumentInterface();
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
    virtual void postInit();
    virtual void initScriptExtensions(QScriptEngine& engine);
    virtual RPluginInfo getPluginInfo();

    static QScriptValue createMyClass(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue myClassToString(QScriptContext *context, QScriptEngine *engine);
    static MyClass* getSelfMyClass(const QString& fName, QScriptContext* context);
};
