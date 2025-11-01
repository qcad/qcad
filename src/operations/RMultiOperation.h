#ifndef RMULTIOPERATION_H
#define RMULTIOPERATION_H

#include "ROperation.h"
#include <QList>

/**
 * \brief An operation that bundles several ROperation objects into one.
 * This allows grouping multiple edits into a single undo/redo step.
 */
class RMultiOperation : public ROperation {
public:
    RMultiOperation(bool undoable = true)
        : ROperation(undoable) {
    }

    virtual ~RMultiOperation() {
        //qDeleteAll(operations);
    }

    /**
     * Adds an operation to the bundle.
     * Ownership of the operation is transferred to this object.
     */
    void addOperation(ROperation* op);

    /**
     * Executes all bundled operations sequentially.
     * Returns true if all operations succeed.
     */
    virtual RTransaction apply(RDocument& document, bool preview = false);

    /**
     * Combines the results of all sub-operations into one.
     */
    /*
    virtual RTransaction getTransaction() const override {
        RTransaction combined;
        for (const ROperation* op : operations) {
            RTransaction t = op->getTransaction();
            combined.combine(t);
        }
        return combined;
    }
    */

    /**
     * Returns a descriptive name for debugging or UI purposes.
     */
    //virtual QString getName() const override {
    //    return QString("MultiOperation (%1 ops)").arg(operations.size());
    //}

private:
    QList<ROperation*> operations;
};

#endif // RMULTIOPERATION_H

