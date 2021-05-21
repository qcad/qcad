function ExPostNewAction() {
    EAction.call(this);
}

ExPostNewAction.prototype = new EAction();

ExPostNewAction.prototype.beginEvent = function() {
    var doc = this.getDocument();
    var fileName = doc.getFileName();
    if (fileName.length===0) {
        EAction.handleUserMessage("New file created");
    }
    else {
        EAction.handleUserMessage("Opened file: " + fileName);
    }
    this.terminate();
};
