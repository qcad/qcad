#include "RSnap.h"

#include "RGraphicsScene.h"
#include "RGraphicsView.h"
#include "RMouseEvent.h"
#include "RSettings.h"

RSnap::RSnap(RSnap::Status s) : status(s), lastSnap(RVector::invalid) {}

RSnap::~RSnap() {}

RVector RSnap::snap(RMouseEvent& event) {
    return snap(event.getModelPosition(), event.getGraphicsView());
}

bool RSnap::isThreeDimensionalView(RGraphicsView& view) {
    RGraphicsScene* scene = view.getScene();
    if (scene == NULL) {
        return false;
    }
    return scene->getProjectionRenderingHint() == RS::RenderThreeD;
}

bool RSnap::isInRange(const RVector& snapped, const RVector& position, double range, RGraphicsView& view) {
    if (!snapped.isValid()) {
        return false;
    }
    if (isThreeDimensionalView(view)) {
        RVector s = view.mapToView(snapped);
        RVector p = view.mapToView(position);
        if (!s.isValid() || !p.isValid()) {
            return false;
        }
        return s.getDistanceTo2D(p) < RSettings::getSnapRange();
    }
    return snapped.getDistanceTo2D(position) < range;
}
