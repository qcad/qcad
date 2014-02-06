#include <QMainWindow>
#include <QDebug>
#include <QScriptEngine>
#include <QUiLoader>

#include "MainWindow.h"

#include "RAddObjectOperation.h"
#include "RLineEntity.h"
#include "RScriptHandlerRegistry.h"
#include "RScriptHandlerEcma.h"
#include "RMemoryStorage.h"
#include "RSpatialIndexNavel.h"
#include "RDocument.h"
#include "RDocumentInterface.h"

MainWindow::MainWindow(QWidget *parent)
     : QMainWindow(parent)
{
    resize(800, 600);
    
    // init script handler for ECMAScript:
    RScriptHandlerRegistry::registerScriptHandler(
        RScriptHandlerEcma::factory,
        RScriptHandlerEcma::getSupportedFileExtensionsStatic()
    );
    RScriptHandlerEcma* handler = 
        dynamic_cast<RScriptHandlerEcma*>(RScriptHandlerRegistry::getGlobalScriptHandler("js"));

    // create central widget from UI file:
    // this widget contains a child called 'Viewport00'. This child
    // widget will be filled with our graphics display with scroll
    // bars, etc.
    QString uiFileName = "support/examples/mainwindow/MyDisplay.ui";
    QFile file(uiFileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open file " << uiFileName;
        return;
    }

    QUiLoader* loader = new QUiLoader();
    QWidget* widget = loader->load(&file, this);
    file.close();

    setCentralWidget(widget);

    // create drawing document with document interface:
    RMemoryStorage* storage = new RMemoryStorage();
    RSpatialIndexNavel* spatialIndex = new RSpatialIndexNavel();
    RDocument* document = new RDocument(*storage, *spatialIndex);
    documentInterface = new RDocumentInterface(*document);

    // import a DXF file into the drawing:
    //documentInterface->importFile("support/examples/mainwindow/drawing_file_to_display.dxf");

    // operation used to add various objects:
    RAddObjectOperation* op;

    // add a layer 'MyLayer':
    QSharedPointer<RLayer> layer = 
        QSharedPointer<RLayer>(
            new RLayer(document, "MyLayer")
        );
    layer->setLinetypeId(document->getLinetypeId("continuous"));
    op = new RAddObjectOperation(layer);
    documentInterface->applyOperation(op);
    RLayer::Id layerId = layer->getId();
    

    // create and add a line entity:
    QSharedPointer<RLineEntity> lineEntity = 
        QSharedPointer<RLineEntity>(
            new RLineEntity(document, RLineData(RVector(0,0), RVector(100,0)))
        );

    // set attributes:
    lineEntity->setLayerId(layerId);
    lineEntity->setColor(RColor(0,128,255));
    lineEntity->setLinetypeId(document->getLinetypeId("dashed"));
    lineEntity->setLineweight(RLineweight::Weight100);

    // set a custom property:
    lineEntity->setCustomProperty("MyApp", "MyIntProperty", 77);
    lineEntity->setCustomProperty("MyApp", "MyStringProperty", "Some text");

    op = new RAddObjectOperation(
        lineEntity, 
        false       // false: don't use current attributes but 
                    //        custom attributes set above
    );

    // add the line entity to the drawing:
    documentInterface->applyOperation(op);


    // make 'widget' and 'documentInterface' available for the script engine:
    QScriptEngine& engine = handler->getScriptEngine();
    QScriptValue globalObject = engine.globalObject();
    globalObject.setProperty("widget", engine.newQObject(widget));
    globalObject.setProperty("documentInterface", qScriptValueFromValue(&engine, documentInterface));

    // call script to initialize viewport (add scroll bars, rulers, etc.):
    handler->doScript("support/examples/mainwindow/init_viewport.js");
}

void MainWindow::showEvent(QShowEvent* event) {
    Q_UNUSED(event)

    // trigger auto zoom on first show only:
    static bool first = true;

    if (first) {
        documentInterface->autoZoom();
        first = false;
    }
}
