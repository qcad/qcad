#include "RSnap.h"

#include "RMouseEvent.h"

RSnap::RSnap(RSnap::Status s) : status(s), lastSnap(RVector::invalid) {}

RSnap::~RSnap() = default;

RVector RSnap::snap(RMouseEvent& event) {
    return snap(event.getModelPosition(), event.getGraphicsView());
}
