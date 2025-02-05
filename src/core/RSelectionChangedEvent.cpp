#include "RSelectionChangedEvent.h"

RSelectionChangedEvent::RSelectionChangedEvent() 
    : QEvent((QEvent::Type)(QEvent::User+100)) {
}

RSelectionChangedEvent::~RSelectionChangedEvent() {
}
