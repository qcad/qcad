#ifndef RSTORAGEBLOCKSORT_H
#define RSTORAGEBLOCKSORT_H

#include "RObject.h"

class RStorage;

class RStorageBlockSort {
public:
    RStorageBlockSort(const RStorage* storage) : storage(storage) {}
    bool operator()(RObject::Id a, RObject::Id b) const;
    const RStorage* storage;
};

#endif
