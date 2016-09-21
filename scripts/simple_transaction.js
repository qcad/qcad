/**
 * Simple Transaction API, mainly designed for use in the ECMAScript console.
 */

/**
 * Starts a transaction. This can increase performance when adding multiple entities.
 * Entities are added in one transaction when endTransaction is called.
 * \ingroup ecma_simple
 *
 * \param d RDocument or RDocumentInterface to apply the transaction to
 * (defaults to current document).
 *
 * \code
 * startTransaction();
 * for (...) {
 *     addLine(...);
 * }
 * endTransaction();
 * \endcode
 */
function startTransaction(d) {
    __simpleUseOp = true;
    if (isOfType(d, RDocument)) {
        __simpleDoc = d;
        __simpleDi = undefined;
    }
    if (isOfType(d, RDocumentInterface)) {
        __simpleDi = d;
        __simpleDoc = d.getDocument();
    }

    if (!isNull(__simpleOp)) {
        __simpleOp.destroy();
        __simpleOp = undefined;
    }

    return true;
}

/**
 * \see startTransaction
 * \ingroup ecma_simple
 *
 * \return RTransaction object containing information about the transaction.
 */
function endTransaction() {
    var ret = undefined;
    if (!isNull(__simpleOp)) {

        // apply operation to document interface:
        if (!isNull(__simpleDi)) {
            __simpleDi.applyOperation(__simpleOp);
            __simpleDi = undefined;
            __simpleDoc = undefined;
        }

        // apply operation to off-screen document:
        else if (!isNull(__simpleDoc)) {
            ret = __simpleOp.apply(__simpleDoc);
            __simpleDoc = undefined;
        }

        // apply operation to current document:
        else {
            var di = getDocumentInterface();
            if (!isNull(di)) {
                ret = di.applyOperation(__simpleOp);
            }
        }
        __simpleOp = undefined;
    }
    __simpleUseOp = false;
    return ret;
}

/**
 * \return The RDocument the current transaction applies to or the current document or undefined.
 */
function getTransactionDocument() {
    if (!isNull(__simpleDoc)) {
        return __simpleDoc;
    }
    else {
        return getDocument();
    }
}

/**
 * \ingroup ecma_simple
 * \return Current operation if we are in a transaction or a new operation.
 */
function getOperation() {
    if (!isNull(__simpleOp)) {
        return __simpleOp;
    }
    return new RAddObjectsOperation();
}
