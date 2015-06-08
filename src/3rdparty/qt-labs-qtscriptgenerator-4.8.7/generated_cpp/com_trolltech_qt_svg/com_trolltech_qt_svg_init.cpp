#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

QScriptValue qtscript_create_QSvgRenderer_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSvgGenerator_class(QScriptEngine *engine);
QScriptValue qtscript_create_QSvgWidget_class(QScriptEngine *engine);

static const char * const qtscript_com_trolltech_qt_svg_class_names[] = {
    "QSvgRenderer"
    , "QSvgGenerator"
    , "QSvgWidget"
};

typedef QScriptValue (*QtBindingCreator)(QScriptEngine *engine);
static const QtBindingCreator qtscript_com_trolltech_qt_svg_class_functions[] = {
    qtscript_create_QSvgRenderer_class
    , qtscript_create_QSvgGenerator_class
    , qtscript_create_QSvgWidget_class
};

void qtscript_initialize_com_trolltech_qt_svg_bindings(QScriptValue &extensionObject)
{
    QScriptEngine *engine = extensionObject.engine();
    for (int i = 0; i < 3; ++i) {
        extensionObject.setProperty(qtscript_com_trolltech_qt_svg_class_names[i],
            qtscript_com_trolltech_qt_svg_class_functions[i](engine),
            QScriptValue::SkipInEnumeration);
    }
}
