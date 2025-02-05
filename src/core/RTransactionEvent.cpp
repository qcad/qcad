#include "RTransactionEvent.h"

RTransactionEvent::RTransactionEvent(RTransaction& t, bool onlyChanges, RS::EntityType entityTypeFilter) :
        QEvent((QEvent::Type)(QEvent::User+300)),
        transaction(t),
        onlyChanges(onlyChanges),
        entityTypeFilter(entityTypeFilter) {
}

RTransactionEvent::~RTransactionEvent() {
}

bool RTransactionEvent::hasOnlyChanges() {
    return onlyChanges;
}

RS::EntityType RTransactionEvent::getEntityTypeFilter() const {
    return entityTypeFilter;
}

RTransaction RTransactionEvent::getTransaction() const {
    return transaction;
}
