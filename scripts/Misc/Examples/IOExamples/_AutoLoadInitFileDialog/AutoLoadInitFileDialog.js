if (typeof(qcadInitFileDialog)==="undefined") {
    qcadInitFileDialog = function(dlg) {
        if (dlg.fileMode===QFileDialog.ExistingFiles) {
            qDebug("Init file open dialog");
            dlg.setNameFilters(["Blah (*.blah)", "Blub (*.blub)"]);
        }
        else if (dlg.fileMode===QFileDialog.AnyFile) {
            qDebug("Init file save as dialog");
        }
    };
}
