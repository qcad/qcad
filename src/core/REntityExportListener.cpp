#include "REntityExportListener.h"
#include "REntity.h"
#include "RS.h"

REntityExportListener::~REntityExportListener() {}

bool REntityExportListener::checkCustomProperty(REntity* e) const {
    QSet<QPair<QString, QString> >::const_iterator it;
    for (it=registeredProperties.constBegin(); it!=registeredProperties.constEnd(); it++) {
        if (e->hasCustomProperty((*it).first, QRegularExpression((*it).second))) {
            return true;
        }
    }
    return false;
}
