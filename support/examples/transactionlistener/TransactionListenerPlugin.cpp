#include <QList>

#include "TransactionListenerPlugin.h"

#include "RDocument.h"
#include "RMainWindowQt.h"
#include "RObject.h"
#include "RPluginInfo.h"
#include "RSettings.h"
#include "RTransaction.h"
#include "RVersion.h"

bool TransactionListenerPlugin::init() {
    qDebug() << "TransactionListenerPlugin::init";

    // add initializations, etc here in C++

    return true;
}

void TransactionListenerPlugin::postInit() {
    qDebug() << "TransactionListenerPlugin::postInit";
    // get notified after objects have changed:
    RMainWindowQt::getMainWindow()->addTransactionListener(this);

    // add your own dock widget, tool bars, etc here in C++:
    // ...
}

void TransactionListenerPlugin::initScriptExtensions(QScriptEngine& engine) {
    Q_UNUSED(engine);
}

/**
 * The information returned from this function is shown in 
 * the about dialog
 */
RPluginInfo TransactionListenerPlugin::getPluginInfo() {
    RPluginInfo ret;
    ret.set("Version", R_QCAD_VERSION_STRING);
    ret.set("Name", "My Plugin");
    ret.set("License", "Proprietary");
    ret.set("URL", "http://mycompany.com");
    return ret;
}

/**
 * Called after every change of at least one object.
 */
void TransactionListenerPlugin::updateTransactionListener(const RDocument* document, const RTransaction* transaction) {
    qDebug() << "got transaction";

    if (transaction==NULL) {
        return;
    }

    QList<RObject::Id> ids = transaction->getAffectedObjects();
    qDebug() << "IDs of objects that were changed: " << ids;

    qDebug() << "List of changed objects:";
    for (int i=0; i<ids.size(); i++) {
        RObject::Id id = ids[i];
        QSharedPointer<RObject> obj = document->queryObject(id);
        if (obj.isNull()) {
            continue;
        }

        qDebug() << "Changed object: " << *obj;
    }
    qDebug() << "End of list";
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(example, TransactionListenerPlugin)
QT_END_NAMESPACE
