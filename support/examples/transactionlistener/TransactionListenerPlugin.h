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

public:
    virtual bool init();
    virtual void uninit(bool remove=false) {}
    virtual void postInit();
    virtual void initScriptExtensions(QScriptEngine& engine);
    virtual RPluginInfo getPluginInfo();

    virtual void updateTransactionListener(RDocument* document, RTransaction* transaction=NULL);
};
