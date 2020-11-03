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
    int aSortOrder = layerA->getCustomIntProperty("QCAD", "SortOrder", -1);
    int bSortOrder = layerB->getCustomIntProperty("QCAD", "SortOrder", -1);
    bool aSort = (aSortOrder!=-1);
    bool bSort = (bSortOrder!=-1);

    if (aSort && !bSort) {
        return true;
    }
    if (!aSort && bSort) {
        return false;
    }
    if (aSort && bSort) {
        return aSortOrder<bSortOrder;
    }

    return RS::compareAlphanumerical(layerA->getName(), layerB->getName()) < 0;
}

