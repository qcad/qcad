#include <QString>

#include "RLayer.h"

class RStorage;

class RStorageLayerSort {
public:
    RStorageLayerSort(const RStorage* storage) : storage(storage) {}
    bool operator()(RLayer::Id a, RLayer::Id b) const;
    const RStorage* storage;
};

