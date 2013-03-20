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
    
    for (var i = 0; i < files.length; ++i) {
        var fi = new QFileInfo(files[i]);
        var text = "";
        if (files.length - i < 10) {
            text = "&";
        }
        text += (files.length - i) + " "
                + fi.fileName().elidedText(this.font, 300) + " ["
                + fi.path().elidedText(this.font, 200) + "]";

        action = new RGuiAction(text, this);
        action.setData(files[i]);
        action.setRequiresDocument(false);
        action.setScriptFile(this.basePath + "/../OpenFile/OpenFile.js", true);
        action.setSortOrder(89 - i);
        action.setProperty("hasShortcuts", false);
        action.addToMenu(this);
    }

    var separator = new RGuiAction("", this);
    separator.setSeparator(true);
    separator.setSortOrder(90);
    separator.addToMenu(this);

    action = new RGuiAction(qsTranslate("RecentFiles", "&Clear List"), this);
    action.setRequiresDocument(false);
    action.setScriptFile(this.basePath + "/RecentFiles.js");
    action.setSortOrder(100);
    action.addToMenu(this);
};

function init(basePath) {
    var action = new RGuiAction(qsTranslate("RecentFiles", "Open &Recent"), RMainWindowQt.getMainWindow());
    var submenu = new RecentFilesMenu(basePath);
    File.getMenu().aboutToShow.connect(submenu, "refresh");
    
    action.setRequiresDocument(false);
    action.checkable = false;
    action.setMenu(submenu);
    action.setSortOrder(400);
    EAction.addGuiActionTo(action, File, true);
}
