#include "RCustomEntityRegistry.h"
#include "RCustomEntityHandler.h"

QList<RCustomEntityHandler*> RCustomEntityRegistry::handlers;

void RCustomEntityRegistry::registerHandler(RCustomEntityHandler* handler) {
    handlers.append(handler);
}

RCustomEntityHandler* RCustomEntityRegistry::getHandler(RS::EntityType entityType) {
    for (int i=0; i<handlers.size(); ++i) {
        if (handlers.at(i)->getEntityType()==entityType) {
            return handlers.at(i);
        }
    }

    return NULL;
}
