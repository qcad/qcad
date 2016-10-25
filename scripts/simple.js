/**
 * Simple API, mainly designed for use in the ECMAScript console.
 */

/**
 * \defgroup ecma_simple QCAD Simple API
 * \ingroup ecma_scripts
 *
 * \brief This module defines the QCAD Simple API in ECMAScript.
 */
include("library.js");
include("input.js");

// internal:
__simpleUseOp = false;
__simpleOp = undefined;
__simpleDoc = undefined;
__simpleDi = undefined;

include("simple_create.js");
include("simple_info.js");
include("simple_modify.js");
include("simple_transaction.js");
include("simple_view.js");

/**
 * Returns a pointer to the main application window (RMainWindowQt).
 * \ingroup ecma_simple
 */
function getMainWindow() {
    return RMainWindowQt.getMainWindow();
}

/**
 * Returns the current RDocumentInterface or undefined.
 * \ingroup ecma_simple
 */
function getDocumentInterface() {
    var appWin = getMainWindow();
    if (isNull(appWin)) {
        return undefined;
    }
    return appWin.getDocumentInterface();
}

/**
 * \return the current RDocument or undefined.
 * \ingroup ecma_simple
 */
function getDocument() {
    var di = getDocumentInterface();
    if (isNull(di)) {
        return undefined;
    }
    return di.getDocument();
}

/**
 * \return the current or last active RGraphicsView.
 * \ingroup ecma_simple
 */
function getGraphicsView() {
    var di = getDocumentInterface();
    if (isNull(di)) {
        return undefined;
    }
    return di.getLastKnownViewWithFocus();
}

/**
 * Creates an off-screen document. Such a document can be filled with
 * objects and saved to disk, pasted into the current document, etc.
 * \ingroup ecma_simple
 *
 * \return new empty RDocument with default settings
 */
function createOffScreenDocument() {
    return new RDocument(new RMemoryStorage(), new RSpatialIndexSimple());
}

/**
 * Disables the main application window to prevent user input.
 * \ingroup ecma_simple
 */
function disableInput() {
    getMainWindow().enabled = false;
    return getMainWindow().enabled;
}

/**
 * Enables the main application window to prevent user input.
 * \ingroup ecma_simple
 */
function enableInput() {
    getMainWindow().enabled = true;
    return getMainWindow().enabled;
}

/**
 * Returns true if user input is enabled.
 * \ingroup ecma_simple
 */
function isInputEnabled() {
    return getMainWindow().enabled;
}

/**
 * Prints a warning to stdout.
 * \ingroup ecma_simple
 */
function warning(msg) {
    if (isFunction(warning.handler)) {
        return warning.handler(msg);
    }
    print("WARNING: " + msg);
}

/**
 * Keeps the user interface up to date during long operations.
 * User input must be disabled using disableInput before calling update.
 * \ingroup ecma_simple
 */
function update() {
    if (isInputEnabled()) {
        warning("User input must be disabled before calling update");
        return false;
    }

    var ret = true;
    try {
        QCoreApplication.processEvents(QEventLoop.ExcludeSocketNotifiers, 100);
    } catch (e) {
        qWarning("error: " + e);
        ret = false;
    }

    return ret;
}

/**
 * Sleeps for the indicated time in milliseconds.
 * \ingroup ecma_simple
 */
function sleep(d) {
    if (isInputEnabled()) {
        warning("User input must be disabled before calling sleep");
        return false;
    }

    var t = new QTime();
    t.start();
    while (t.elapsed() < d) {
        if (!update()) {
            return false;
        }
    }

    return true;
}
