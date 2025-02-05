#include "RRuler.h"

void RRuler::setGraphicsView(RGraphicsView* view) {
    this->view = view;
    updateViewport();
}

Qt::Orientation RRuler::getOrientation() const {
    return orientation;
}

void RRuler::setOrientation(Qt::Orientation orientation) {
    this->orientation = orientation;
    updateViewport();
}
