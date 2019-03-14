#include <Qt>

#include "RBlock.h"
#include "RLayout.h"
#include "RStorage.h"
#include "RStorageBlockSort.h"

bool RStorageBlockSort::operator()(RBlock::Id a, RBlock::Id b) const {
    QSharedPointer<RBlock> blockA = storage->queryBlockDirect(a);
    QSharedPointer<RBlock> blockB = storage->queryBlockDirect(b);
    if (blockA.isNull() || blockB.isNull()) {
        return false;
    }

    // model space always first:
    if (blockA->getName()==RBlock::modelSpaceName) {
        return true;
    }
    if (blockB->getName()==RBlock::modelSpaceName) {
        return false;
    }

    // layouts always before other blocks:
    bool blockAHasLayout = blockA->hasLayout();
    bool blockBHasLayout = blockB->hasLayout();
    if (blockAHasLayout && !blockBHasLayout) {
        return true;
    }
    if (!blockAHasLayout && blockBHasLayout) {
        return false;
    }


    // sort among layouts by tab order:
    if (blockAHasLayout && blockBHasLayout) {
        QSharedPointer<RLayout> layoutA;
        RLayout::Id layoutAId = blockA->getLayoutId();
        layoutA = storage->queryLayoutDirect(layoutAId);
        QSharedPointer<RLayout> layoutB;
        RLayout::Id layoutBId = blockB->getLayoutId();
        layoutB = storage->queryLayoutDirect(layoutBId);
        if (!layoutA.isNull() && !layoutB.isNull()) {
            return layoutA->getTabOrder() < layoutB->getTabOrder();
        }
    }

    // sort by layout name or block name (ignoring * at start):
    QString blockTitleA = blockA->getName();
//    if (blockAHasLayout) {
//        if (!layoutA.isNull()) {
//            blockTitleA += " (" +  + ")";
//        }
//    }
    QString blockTitleB = blockB->getName();
//    if (blockBHasLayout) {
//        if (!layoutB.isNull()) {
//            blockTitleB += " (" + layoutB->getName() + ")";
//        }
//    }

    if (blockTitleA.startsWith("*")) {
        blockTitleA = blockTitleA.mid(1);
    }
    if (blockTitleB.startsWith("*")) {
        blockTitleB = blockTitleB.mid(1);
    }

    return RS::compareAlphanumerical(blockTitleA, blockTitleB) < 0;
}

