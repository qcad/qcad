/**
 * Initializes user defined shortcuts and commands.
 */
function postInit() {
    var settings = RSettings.getQSettings();
    var keys = RSettings.getAllKeys("Shortcuts");

    var i, key, action;

    for (i=0; i<keys.length; i++) {
        key = keys[i];
        action = RGuiAction.getByScriptFile(key);
        if (isNull(action)) {
            continue;
        }
        var scStringList = settings.value("Shortcuts/" + key);

        // explicitely no shortcuts:
        if (isNull(scStringList)) {
            action.setShortcuts([]);
            continue;
        }

        var scList = new Array();
        for (var k=0; k<scStringList.length; k++) {
            var sc = new QKeySequence(scStringList[k]);
            scList.push(sc);
        }
        action.setShortcuts(scList);
    }

    keys = RSettings.getAllKeys("Commands");

    for (i=0; i<keys.length; i++) {
        key = keys[i];
        action = RGuiAction.getByScriptFile(key);
        if (isNull(action)) {
            continue;
        }
        var cmStringList = settings.value("Commands/" + key);

        // explicitely no commands:
        if (isNull(cmStringList)) {
            action.setCommands([]);
            continue;
        }

        action.setCommands(cmStringList);
    }
}
