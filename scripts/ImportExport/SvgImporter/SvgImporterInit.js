function SvgImporterFactory() {
    RFileImporterFactoryAdapter.call(this);
}

SvgImporterFactory.prototype = new RFileImporterFactoryAdapter();
SvgImporterFactory.includeBasePath = includeBasePath;

SvgImporterFactory.prototype.getFilterStrings = function() {
    return [ qsTr("SVG Files %1").arg("(*.svg)") ];
};

SvgImporterFactory.prototype.canImport = function(fileName, nameFilter) {
    var fi = new QFileInfo(fileName);
    if (fi.suffix().toLowerCase()==="svg") {
        return 1;
    }
    return -1;
};

SvgImporterFactory.prototype.instantiate = function(document, messageHandler, progressHandler) {
    include(SvgImporterFactory.includeBasePath + "/SvgImporter.js");
    return new SvgImporter(document);
};

function init(basePath) {
    RFileImporterRegistry.registerFileImporter(new SvgImporterFactory());
}
