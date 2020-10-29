#include <Qt>

#include "RLayer.h"
#include "RLayout.h"
#include "RStorage.h"
#include "RStorageLayerSort.h"

bool RStorageLayerSort::operator()(RLayer::Id a, RLayer::Id b) const {
    QSharedPointer<RLayer> layerA = storage->queryLayerDirect(a);
    QSharedPointer<RLayer> layerB = storage->queryLayerDirect(b);
    if (layerA.isNull() || layerB.isNull()) {
        return false;
    }

    // layers with sort order always first:
    bool aSort = layerA->hasCustomProperty("QCAD", "SortOrder");
    bool bSort = layerB->hasCustomProperty("QCAD", "SortOrder");
    if (aSort && !bSort) {
        return true;
    }
    if (!aSort && bSort) {
        return false;
    }
    if (aSort && bSort) {
        int aSortOrder = layerA->getCustomIntProperty("QCAD", "SortOrder", 0);
        int bSortOrder = layerB->getCustomIntProperty("QCAD", "SortOrder", 0);
        return aSortOrder<bSortOrder;
    }

    return RS::compareAlphanumerical(layerA->getName(), layerB->getName()) < 0;
}

