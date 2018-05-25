/**
 * Class MyWidget, derived from QWidget.
 */
function MyWidget(parentWidget) {
    QWidget.call(this, parentWidget);

    // make sure we can receive key events:
    this.focusPolicy = Qt.StrongFocus;

    // load ui file into widget:
    var loader = new QUiLoader();
    loader.setWorkingDirectory(MyWidget.includeBasePath);
    var file = new QFile(MyWidget.includeBasePath + "/MyWidget.ui");
    file.open(new QIODevice.OpenMode(QIODevice.ReadOnly | QIODevice.Text));
    var form = loader.load(file, this);
    file.close();
    loader.destroy();

    // add layout to ensure content scales with widget:
    var layout = new QVBoxLayout();
    layout.addWidget(form, 0, Qt.AlignTop | Qt.AlignLeft);
    this.setLayout(layout);
}

MyWidget.prototype = new QWidget();
MyWidget.includeBasePath = includeBasePath;

/**
 * Reimplement keyPressEvent from QWidget to react to key press events:
 */
MyWidget.prototype.keyPressEvent = function(e) {
    if (e.key()==Qt.Key_A) {
        EAction.handleUserMessage("'A' key pressed");
    }
    QWidget.prototype.keyPressEvent.call(this, e);
};
