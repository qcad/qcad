#include <QString>

#include "RBlock.h"

class RStorage;

class RStorageBlockSort {
public:
    RStorageBlockSort(const RStorage* storage) : storage(storage) {}
    bool operator()(RBlock::Id a, RBlock::Id b) const;
    const RStorage* storage;
};

