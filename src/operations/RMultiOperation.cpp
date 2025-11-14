#include "RMultiOperation.h"

void RMultiOperation::addOperation(ROperation* op) {
    if (op != NULL) {
        operations.append(op);
    }
}

/**
 * Executes all bundled operations sequentially.
 * Returns true if all operations succeed.
 */
RTransaction RMultiOperation::apply(RDocument& document, bool preview) {
    RTransaction ret;
    for (int i=0; i<operations.length(); i++) {
        ROperation* op = operations[i];
        ret = op->apply(document, preview);
    }
    return ret;
}

