#ifndef RSTORAGELAYERSORT_H
#define RSTORAGELAYERSORT_H

#include "RObject.h"

class RStorage;

class RStorageLayerSort {
public:
    RStorageLayerSort(const RStorage* storage) : storage(storage) {}
    bool operator()(RObject::Id a, RObject::Id b) const;
    const RStorage* storage;
};

#endif
