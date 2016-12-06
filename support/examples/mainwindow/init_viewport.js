include('scripts/Widgets/ViewportWidget/ViewportWidget.js');
var viewports = Viewport.getViewports(widget, documentInterface);

// creates a scene for the view,
// attaches the scene to the document interface,
// sets default navigation,
// adds scrollbars and rulers:
Viewport.initializeViewports(viewports);

// init event handlers for drag and drop and scrolling:
//Viewport.initEventHandler(viewports);
