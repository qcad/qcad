NAME = Scripts
TSDIR = .
include(../translations.pri)
SOURCES = \
    ../EAction.js \
    ../AddOn.js \
    ../Apollonius.js \
    ../WidgetFactory.js \
    ../ShapeAlgorithms.js \
    ../DbConnection.js \
    ../diff.js \
    ../library.js \
    ../stacktrace.js \
    ../autostart.js \
    ../sprintf.js \
    ../map.js \
    ../DefaultAction.js \
    ../lib/hull/grid.js \
    ../lib/hull/hull.js \
    ../lib/hull/intersect.js
OTHER_FILES += ../custom_menu.dox \
    ../memorize_dialog.dox \
    ../scripting.dox \
    ../scripts.dox
