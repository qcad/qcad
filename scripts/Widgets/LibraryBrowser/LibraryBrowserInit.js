/**
 * Plugin initialization. This is very fast as the real initialization
 * happens if the library browser dock widget is shown for the first time.
 */
function init(basePath) {
    var appWin = RMainWindowQt.getMainWindow();

    var action = new RGuiAction(qsTranslate("LibraryBrowser", "&Library Browser"), appWin);
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/LibraryBrowser.js");
    action.setIcon(basePath + "/LibraryBrowser.svg");
    action.setDefaultShortcut(new QKeySequence("g,l"));
    action.setDefaultCommands(["gl"]);
    action.setGroupSortOrder(3700);
    action.setSortOrder(300);
    action.setWidgetNames(["ViewMenu", "WidgetsToolBar", "ViewToolsPanel", "WidgetsMatrixPanel"]);

    var formWidget = WidgetFactory.createWidget(basePath, "LibraryBrowser.ui");
    var dock = new RDockWidget(qsTranslate("LibraryBrowser", "Library Browser"), appWin);
    dock.objectName = "LibraryBrowserDock";
    dock.setWidget(formWidget);
    appWin.addDockWidget(Qt.RightDockWidgetArea, dock);
    dock.visible = false;
    dock.floating = true;
    dock.move(appWin.x + appWin.width, appWin.y + appWin.height / 2);
    dock.resize(300, appWin.height / 2);

    dock.shown.connect(function() {
        // make sure LibraryBrowser is loaded if it is shown immediately
        // after startup:
        include("scripts/Widgets/LibraryBrowser/LibraryBrowser.js");
        LibraryBrowser.showFirstTime();
        action.setChecked(true);
    });
    dock.hidden.connect(function() {
        action.setChecked(false);
    });

    // sync button:
    formWidget.findChild("Synchronize").clicked.connect(function() {
        LibraryBrowser.syncWithProgress();
        LibraryBrowser.updateCurrentTab();
    });

    // sync button:
//    formWidget.findChild("Reset").clicked.connect(function() {
//        LibraryBrowser.selectedTagIds = [];
//        LibraryBrowser.openCategoryIds = [];
//        LibraryBrowser.updateTagsTab(true);
//        LibraryBrowser.updateTagsView();
//    });

    // insert button:
    formWidget.findChild("Insert").clicked.connect(function() {
        var tabWidget = formWidget.findChild("TabWidget");
        var itemView;
        if (tabWidget.currentIndex===0) {
            itemView = tabWidget.findChild("FileSystemListView");
        }
        else if (tabWidget.currentIndex===1) {
            itemView = tabWidget.findChild("TagsListView");
        }
        else if (tabWidget.currentIndex===2) {
            itemView = tabWidget.findChild("FavoritesListView");
        }

        LibraryBrowser.insertItem(itemView);
    });

    var createFromSelectionButton = formWidget.findChild("CreateFromSelection");
    var createAction = RGuiAction.getByScriptFile("scripts/Block/CreateLibraryItem/CreateLibraryItem.js");
    createFromSelectionButton.setDefaultAction(createAction);
}

