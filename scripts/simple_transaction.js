/**
 * Simple Transaction API, mainly designed for use in the ECMAScript console.
 */

/**
 * Starts a transaction. This can increase performance when adding multiple entities.
 * Entities are added in one transaction when endTransaction is called.
 * \ingroup ecma_simple
 *
 * \code
 * startTransaction();
 * for (...) {
 *     addLine(...);
 * }
 * endTransaction();
 * \endcode
 */
function startTransaction() {
    __simpleUseOp = true;
    if (!isNull(__simpleOp)) {
        __simpleOp.destroy();
        __simpleOp = undefined;
    }
    return true;
}

/**
 * \see startTransaction
 * \ingroup ecma_simple
 * \return RTransaction object containing information about the transaction.
 */
function endTransaction() {
    var ret = undefined;
    if (!isNull(__simpleOp)) {
        var di = getDocumentInterface();
        ret = di.applyOperation(__simpleOp);
        __simpleOp = undefined;
    }
    __simpleUseOp = false;
    return ret;
}
