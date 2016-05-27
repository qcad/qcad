/**
 * Simple API, mainly designed for use in the ECMAScript console.
 */

include("library.js");
include("input.js");

// internal:
__simpleUseOp = false;
__simpleOp = undefined;

include("simple_create.js");
include("simple_modify.js");
include("simple_info.js");
include("simple_transaction.js");

/**
 * Returns a pointer to the main application window (RMainWindowQt).
 */
function getMainWindow() {
    return RMainWindowQt.getMainWindow();
}

/**
 * Returns the current RDocumentInterface or undefined.
 */
function getDocumentInterface() {
    var appWin = getMainWindow();
    return appWin.getDocumentInterface();
}

/**
 * Returns the current RDocument or undefined.
 */
function getDocument() {
    var di = getDocumentInterface();
    if (isNull(di)) {
        return undefined;
    }
    return di.getDocument();
}

/**
 * Disables the main application window to prevent user input.
 */
function disableInput() {
    getMainWindow().enabled = false;
    return getMainWindow().enabled;
}

/**
 * Enables the main application window to prevent user input.
 */
function enableInput() {
    getMainWindow().enabled = true;
    return getMainWindow().enabled;
}

/**
 * Returns true if user input is enabled.
 */
function isInputEnabled() {
    return getMainWindow().enabled;
}

/**
 * Prints a warning to stdout.
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
 */
function update() {
    if (isInputEnabled()) {
        warning("User input must be disabled before calling update");
        return false;
    }

    QCoreApplication.processEvents();
    return true;
}
