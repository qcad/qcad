/**
 * Menu item handler for recent file menu items.
 */
function RecentFilesHandler(fileName) {
    this.fileName = fileName;
}

RecentFilesHandler.prototype = {};

RecentFilesHandler.prototype.open = function() {
    NewFile.createMdiChild(this.fileName);
};

/**
 * Specialized QMenu class that shows recently used files.
 */
function RecentFilesMenu(basePath) {
    QMenu.call(this);
    this.basePath = basePath;
}

RecentFilesMenu.prototype = new QMenu();

RecentFilesMenu.prototype.refresh = function() {
    var action;
    
    this.clear();
    var files = RSettings.getRecentFiles();
    if (files.length === 0) {
        this.setEnabled(false);
        return;
    }
    
    this.setEnabled(true);
    
    for (var i=files.length-1; i>=0 ; --i) {
        var fi = new QFileInfo(files[i]);
        var text = "";
        if (files.length - i < 10) {
            text = "&";
        }

        var fn = fi.fileName().elidedText(this.font, 300);
        var fp = fi.path().elidedText(this.font, 200);

        // make sure ampersand is not interpreted as shortcut indicator:
        fn = fn.replace("&", "&&");
        fp = fp.replace("&", "&&");

        text += (files.length - i) + " "
                + fn + " ["
                + fp + "]";

        action = this.addAction(text);
        var h = new RecentFilesHandler(files[i]);
        action.triggered.connect(h, "open");
    }

    action = new RGuiAction(qsTranslate("RecentFiles", "&Clear List"), this);
    action.setRequiresDocument(false);
    action.setScriptFile(this.basePath + "/RecentFiles.js");
    action.setGroupSortOrder(1501);
    action.setSortOrder(100);
    action.setWidgetNames(["RecentFilesSubMenu"]);
    RGuiAction.addToWidget(action, this);
};

function init(basePath) {
    var action = new RGuiAction(qsTranslate("RecentFiles", "Open &Recent"), RMainWindowQt.getMainWindow());
    var submenu = new RecentFilesMenu(basePath);
    submenu.objectName = "RecentFilesSubMenu";
    File.getMenu().aboutToShow.connect(submenu, "refresh");
    
    action.setRequiresDocument(false);
    action.checkable = false;
    action.setMenu(submenu);
    action.setGroupSortOrder(1000);
    action.setSortOrder(400);
    action.setWidgetNames(["FileMenu"]);
}
