include('scripts/Pro/Developer/TestingDashboard/TdbTest.js');

function ToggleLayerVisibilityTest00() {
    TdbTest.call(this, 'scripts/Layer/ToggleLayerVisibility/Tests/ToggleLayerVisibilityTest00.js');
}

ToggleLayerVisibilityTest00.prototype = new TdbTest();

ToggleLayerVisibilityTest00.prototype.test00 = function() {
    qDebug('running ToggleLayerVisibilityTest00.test00()...');

    var showFrozen = RSettings.getBoolValue("LayerListPro/ShowFrozen", false);
    var freezeLayer = RSettings.getBoolValue("LayerListPro/FreezeLayer", true);

    this.setUp();

    var di = EAction.getDocumentInterface();
    var doc = di.getDocument();
    var layer;

    addLayer("Layer1", "white", "CONTINOUS", RLineweight.Weight025);
    doc.setCurrentLayer("Layer1");

    //               showFrozen, freezeLayer,    frozen, off,      frozenRes, offRes
    this.testToggle(      false, false,           false, false,        false, true    );
    this.testToggle(      false, false,           false, true,         false, false   );
    this.testToggle(      false, false,            true, false,        false, true    );
    this.testToggle(      false, false,            true, true,         false, false   );

    this.testToggle(      false, true,            false, false,         true, false   );
    this.testToggle(      false, true,            false, true,         false, false   );
    this.testToggle(      false, true,             true, false,        false, false   );
    this.testToggle(      false, true,             true, true,         false, false   );

    this.testToggle(       true, false,           false, false,        false, true    );
    this.testToggle(       true, false,           false, true,         false, false   );
    this.testToggle(       true, false,            true, false,         true, true    );
    this.testToggle(       true, false,            true, true,          true, false   );

    this.testToggle(       true, true,            false, false,        false, true    );
    this.testToggle(       true, true,            false, true,         false, false   );
    this.testToggle(       true, true,             true, false,         true, true    );
    this.testToggle(       true, true,             true, true,          true, false   );

    this.tearDown();

    RSettings.setValue("LayerListPro/ShowFrozen", showFrozen);
    RSettings.setValue("LayerListPro/FreezeLayer", freezeLayer);

    qDebug('finished ToggleLayerVisibilityTest00.test00()');
};

ToggleLayerVisibilityTest00.prototype.testToggle = function(showFrozen, freezeLayer, frozen, off, frozenRes, offRes) {
    var toggleLayerVisibilityAction = RGuiAction.getByScriptFile("scripts/Layer/ToggleLayerVisibility/ToggleLayerVisibility.js");
    var di = EAction.getDocumentInterface();
    var doc = di.getDocument();

//    qDebug("showFrozen: ", showFrozen);
//    qDebug("freezeLayer: ", freezeLayer);
//    qDebug("frozen: ", frozen);
//    qDebug("off: ", off);
//    qDebug("frozenRes: ", frozenRes);
//    qDebug("offRes: ", offRes);

    RSettings.setValue("LayerListPro/ShowFrozen", showFrozen);
    RSettings.setValue("LayerListPro/FreezeLayer", freezeLayer);

    // not frozen, not off -> not frozen, off
    var layer = doc.queryCurrentLayer();
    layer.setFrozen(frozen);
    layer.setOff(off);
    di.applyOperation(new RAddObjectOperation(layer));

    toggleLayerVisibilityAction.slotTrigger();

    layer = doc.queryCurrentLayer();
    this.verify(layer.isFrozen()===frozenRes, "layer frozen should be " + frozenRes);
    this.verify(layer.isOff()===offRes, "layer off should be " + offRes);
};
