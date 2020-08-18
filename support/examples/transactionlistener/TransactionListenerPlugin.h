#include <QDebug>
#include <QObject>
#include <QScriptEngine>
#include <QStringList>

#include "RPluginInterface.h"
#include "RTransactionListener.h"

class TransactionListenerPlugin : public QObject, public RPluginInterface, public RTransactionListener
{
    Q_OBJECT
    Q_INTERFACES(RPluginInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qcad.transactionlistener")
#endif

public:
    virtual bool init();
    virtual void uninit(bool remove=false) { Q_UNUSED(remove) }
    virtual void postInit(InitStatus status);
    virtual void initScriptExtensions(QScriptEngine& engine);
    virtual RPluginInfo getPluginInfo();

    virtual void updateTransactionListener(RDocument* document, RTransaction* transaction=NULL);
    virtual bool checkLicense() { return true; }
    virtual void initTranslations(){}
};
